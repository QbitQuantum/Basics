// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.QuartzCore.pas' rev: 34.00 (iOS)

#ifndef Iosapi_QuartzcoreHPP
#define Iosapi_QuartzcoreHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Quartzcore
{
//-- forward type declarations -----------------------------------------------
struct CATransform3D;
__interface DELPHIINTERFACE CAAction;
typedef System::DelphiInterface<CAAction> _di_CAAction;
__interface DELPHIINTERFACE CAMediaTiming;
typedef System::DelphiInterface<CAMediaTiming> _di_CAMediaTiming;
__interface DELPHIINTERFACE CATransactionClass;
typedef System::DelphiInterface<CATransactionClass> _di_CATransactionClass;
__interface DELPHIINTERFACE CATransaction;
typedef System::DelphiInterface<CATransaction> _di_CATransaction;
class DELPHICLASS TCATransaction;
__interface DELPHIINTERFACE CAValueFunctionClass;
typedef System::DelphiInterface<CAValueFunctionClass> _di_CAValueFunctionClass;
__interface DELPHIINTERFACE CAValueFunction;
typedef System::DelphiInterface<CAValueFunction> _di_CAValueFunction;
class DELPHICLASS TCAValueFunction;
__interface DELPHIINTERFACE CAMediaTimingFunctionClass;
typedef System::DelphiInterface<CAMediaTimingFunctionClass> _di_CAMediaTimingFunctionClass;
__interface DELPHIINTERFACE CAMediaTimingFunction;
typedef System::DelphiInterface<CAMediaTimingFunction> _di_CAMediaTimingFunction;
class DELPHICLASS TCAMediaTimingFunction;
__interface DELPHIINTERFACE CALayerClass;
typedef System::DelphiInterface<CALayerClass> _di_CALayerClass;
__interface DELPHIINTERFACE CALayer;
typedef System::DelphiInterface<CALayer> _di_CALayer;
class DELPHICLASS TCALayer;
__interface DELPHIINTERFACE CAEAGLLayerClass;
typedef System::DelphiInterface<CAEAGLLayerClass> _di_CAEAGLLayerClass;
__interface DELPHIINTERFACE CAEAGLLayer;
typedef System::DelphiInterface<CAEAGLLayer> _di_CAEAGLLayer;
__interface DELPHIINTERFACE CAEmitterCellClass;
typedef System::DelphiInterface<CAEmitterCellClass> _di_CAEmitterCellClass;
__interface DELPHIINTERFACE CAEmitterCell;
typedef System::DelphiInterface<CAEmitterCell> _di_CAEmitterCell;
class DELPHICLASS TCAEmitterCell;
__interface DELPHIINTERFACE NSValueClass;
typedef System::DelphiInterface<NSValueClass> _di_NSValueClass;
__interface DELPHIINTERFACE NSValue;
typedef System::DelphiInterface<NSValue> _di_NSValue;
class DELPHICLASS TNSValue;
__interface DELPHIINTERFACE CAAnimationClass;
typedef System::DelphiInterface<CAAnimationClass> _di_CAAnimationClass;
__interface DELPHIINTERFACE CAAnimation;
typedef System::DelphiInterface<CAAnimation> _di_CAAnimation;
class DELPHICLASS TCAAnimation;
__interface DELPHIINTERFACE NSObjectClass;
typedef System::DelphiInterface<NSObjectClass> _di_NSObjectClass;
__interface DELPHIINTERFACE NSObject1;
typedef System::DelphiInterface<NSObject1> _di_NSObject1;
class DELPHICLASS TNSObject;
__interface DELPHIINTERFACE CADisplayLinkClass;
typedef System::DelphiInterface<CADisplayLinkClass> _di_CADisplayLinkClass;
__interface DELPHIINTERFACE CADisplayLink;
typedef System::DelphiInterface<CADisplayLink> _di_CADisplayLink;
class DELPHICLASS TCADisplayLink;
__interface DELPHIINTERFACE CATextLayerClass;
typedef System::DelphiInterface<CATextLayerClass> _di_CATextLayerClass;
__interface DELPHIINTERFACE CATextLayer;
typedef System::DelphiInterface<CATextLayer> _di_CATextLayer;
class DELPHICLASS TCATextLayer;
__interface DELPHIINTERFACE CAShapeLayerClass;
typedef System::DelphiInterface<CAShapeLayerClass> _di_CAShapeLayerClass;
__interface DELPHIINTERFACE CAShapeLayer;
typedef System::DelphiInterface<CAShapeLayer> _di_CAShapeLayer;
class DELPHICLASS TCAShapeLayer;
__interface DELPHIINTERFACE CATransitionClass;
typedef System::DelphiInterface<CATransitionClass> _di_CATransitionClass;
__interface DELPHIINTERFACE CATransition;
typedef System::DelphiInterface<CATransition> _di_CATransition;
class DELPHICLASS TCATransition;
__interface DELPHIINTERFACE CATiledLayerClass;
typedef System::DelphiInterface<CATiledLayerClass> _di_CATiledLayerClass;
__interface DELPHIINTERFACE CATiledLayer;
typedef System::DelphiInterface<CATiledLayer> _di_CATiledLayer;
class DELPHICLASS TCATiledLayer;
__interface DELPHIINTERFACE CAAnimationGroupClass;
typedef System::DelphiInterface<CAAnimationGroupClass> _di_CAAnimationGroupClass;
__interface DELPHIINTERFACE CAAnimationGroup;
typedef System::DelphiInterface<CAAnimationGroup> _di_CAAnimationGroup;
class DELPHICLASS TCAAnimationGroup;
__interface DELPHIINTERFACE CAGradientLayerClass;
typedef System::DelphiInterface<CAGradientLayerClass> _di_CAGradientLayerClass;
__interface DELPHIINTERFACE CAGradientLayer;
typedef System::DelphiInterface<CAGradientLayer> _di_CAGradientLayer;
class DELPHICLASS TCAGradientLayer;
__interface DELPHIINTERFACE CAEmitterLayerClass;
typedef System::DelphiInterface<CAEmitterLayerClass> _di_CAEmitterLayerClass;
__interface DELPHIINTERFACE CAEmitterLayer;
typedef System::DelphiInterface<CAEmitterLayer> _di_CAEmitterLayer;
class DELPHICLASS TCAEmitterLayer;
__interface DELPHIINTERFACE CAScrollLayerClass;
typedef System::DelphiInterface<CAScrollLayerClass> _di_CAScrollLayerClass;
__interface DELPHIINTERFACE CAScrollLayer;
typedef System::DelphiInterface<CAScrollLayer> _di_CAScrollLayer;
class DELPHICLASS TCAScrollLayer;
__interface DELPHIINTERFACE CAReplicatorLayerClass;
typedef System::DelphiInterface<CAReplicatorLayerClass> _di_CAReplicatorLayerClass;
__interface DELPHIINTERFACE CAReplicatorLayer;
typedef System::DelphiInterface<CAReplicatorLayer> _di_CAReplicatorLayer;
class DELPHICLASS TCAReplicatorLayer;
__interface DELPHIINTERFACE CAPropertyAnimationClass;
typedef System::DelphiInterface<CAPropertyAnimationClass> _di_CAPropertyAnimationClass;
__interface DELPHIINTERFACE CAPropertyAnimation;
typedef System::DelphiInterface<CAPropertyAnimation> _di_CAPropertyAnimation;
class DELPHICLASS TCAPropertyAnimation;
__interface DELPHIINTERFACE CABasicAnimationClass;
typedef System::DelphiInterface<CABasicAnimationClass> _di_CABasicAnimationClass;
__interface DELPHIINTERFACE CABasicAnimation;
typedef System::DelphiInterface<CABasicAnimation> _di_CABasicAnimation;
class DELPHICLASS TCABasicAnimation;
__interface DELPHIINTERFACE CAKeyframeAnimationClass;
typedef System::DelphiInterface<CAKeyframeAnimationClass> _di_CAKeyframeAnimationClass;
__interface DELPHIINTERFACE CAKeyframeAnimation;
typedef System::DelphiInterface<CAKeyframeAnimation> _di_CAKeyframeAnimation;
class DELPHICLASS TCAKeyframeAnimation;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD CATransform3D
{
public:
	double m11;
	double m12;
	double m13;
	double m14;
	double m21;
	double m22;
	double m23;
	double m24;
	double m31;
	double m32;
	double m33;
	double m34;
	double m41;
	double m42;
	double m43;
	double m44;
};


__interface  INTERFACE_UUID("{15114D7C-C969-4806-B462-2C8FF862C6EB}") CAAction  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{20987BC7-DF3C-43F2-BA93-C24E6860C279}") CAMediaTiming  : public System::IInterface 
{
	virtual bool __cdecl autoreverses() = 0 ;
	virtual double __cdecl beginTime() = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fillMode() = 0 ;
	virtual float __cdecl repeatCount() = 0 ;
	virtual double __cdecl repeatDuration() = 0 ;
	virtual void __cdecl setAutoreverses(bool autoreverses) = 0 ;
	virtual void __cdecl setBeginTime(double beginTime) = 0 ;
	virtual void __cdecl setDuration(double duration) = 0 ;
	virtual void __cdecl setFillMode(Iosapi::Foundation::_di_NSString fillMode) = 0 ;
	virtual void __cdecl setRepeatCount(float repeatCount) = 0 ;
	virtual void __cdecl setRepeatDuration(double repeatDuration) = 0 ;
	virtual void __cdecl setSpeed(float speed) = 0 ;
	virtual void __cdecl setTimeOffset(double timeOffset) = 0 ;
	virtual float __cdecl speed() = 0 ;
	virtual double __cdecl timeOffset() = 0 ;
};

__interface  INTERFACE_UUID("{9CAAECB3-D949-4262-92A7-5E7359D9C8BE}") CATransactionClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual double __cdecl animationDuration() = 0 ;
	virtual _di_CAMediaTimingFunction __cdecl animationTimingFunction() = 0 ;
	virtual void __cdecl commit() = 0 ;
	virtual bool __cdecl disableActions() = 0 ;
	virtual void __cdecl flush() = 0 ;
	virtual void __cdecl lock() = 0 ;
	virtual void __cdecl setAnimationDuration(double dur) = 0 ;
	virtual void __cdecl setAnimationTimingFunction(_di_CAMediaTimingFunction function_) = 0 ;
	virtual void __cdecl setDisableActions(bool flag) = 0 ;
	virtual void __cdecl setValue(void * anObject, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	virtual void __cdecl unlock() = 0 ;
	virtual void * __cdecl valueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
};

__interface  INTERFACE_UUID("{557D88F0-2192-4636-86DC-5B3246DB742B}") CATransaction  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TCATransaction : public Macapi::Objectivec::TOCGenericImport__2<_di_CATransactionClass,_di_CATransaction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CATransactionClass,_di_CATransaction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCATransaction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CATransactionClass,_di_CATransaction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCATransaction() { }
	
};


__interface  INTERFACE_UUID("{BFDA3DBE-5E13-43C4-AC3E-66477865C928}") CAValueFunctionClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl functionWithName(Iosapi::Foundation::_di_NSString name) = 0 ;
};

__interface  INTERFACE_UUID("{708C0B0B-46E7-4DCE-A79C-5880F52D3256}") CAValueFunction  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
};

class PASCALIMPLEMENTATION TCAValueFunction : public Macapi::Objectivec::TOCGenericImport__2<_di_CAValueFunctionClass,_di_CAValueFunction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAValueFunctionClass,_di_CAValueFunction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAValueFunction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAValueFunctionClass,_di_CAValueFunction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAValueFunction() { }
	
};


__interface  INTERFACE_UUID("{5A1E7ED1-6689-46CE-9B00-D9CD6045750E}") CAMediaTimingFunctionClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl functionWithName(Iosapi::Foundation::_di_NSString name) = 0 ;
};

__interface  INTERFACE_UUID("{A18855C9-EC88-40E8-888E-03D16D12479F}") CAMediaTimingFunction  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl getControlPointAtIndex(unsigned long idx, System::PSingle values) = 0 ;
};

class PASCALIMPLEMENTATION TCAMediaTimingFunction : public Macapi::Objectivec::TOCGenericImport__2<_di_CAMediaTimingFunctionClass,_di_CAMediaTimingFunction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAMediaTimingFunctionClass,_di_CAMediaTimingFunction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAMediaTimingFunction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAMediaTimingFunctionClass,_di_CAMediaTimingFunction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAMediaTimingFunction() { }
	
};


__interface  INTERFACE_UUID("{3AA239A4-7FA2-454E-ACA0-FAEEDE874CD9}") CALayerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl defaultActionForKey(Iosapi::Foundation::_di_NSString event) = 0 ;
	virtual void * __cdecl defaultValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void * __cdecl layer() = 0 ;
	virtual bool __cdecl needsDisplayForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
};

__interface  INTERFACE_UUID("{BDD252B7-74C1-4EBC-947C-55D87479E783}") CALayer  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl actionForKey(Iosapi::Foundation::_di_NSString event) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl actions() = 0 ;
	virtual void __cdecl addAnimation(_di_CAAnimation anim, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	virtual void __cdecl addSublayer(_di_CALayer layer) = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl affineTransform() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl anchorPoint() = 0 ;
	virtual double __cdecl anchorPointZ() = 0 ;
	virtual _di_CAAnimation __cdecl animationForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl animationKeys() = 0 ;
	virtual void * __cdecl backgroundColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl backgroundFilters() = 0 ;
	virtual void * __cdecl borderColor() = 0 ;
	virtual double __cdecl borderWidth() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual void * __cdecl compositingFilter() = 0 ;
	virtual bool __cdecl containsPoint(Iosapi::Foundation::NSPoint p) = 0 ;
	virtual void * __cdecl contents() = 0 ;
	virtual bool __cdecl contentsAreFlipped() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl contentsCenter() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl contentsGravity() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl contentsRect() = 0 ;
	virtual double __cdecl contentsScale() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl convertPoint(Iosapi::Foundation::NSPoint p, _di_CALayer fromLayer) = 0 /* overload */;
	virtual Iosapi::Foundation::NSRect __cdecl convertRect(Iosapi::Foundation::NSRect r, _di_CALayer fromLayer) = 0 /* overload */;
	virtual double __cdecl convertTime(double t, _di_CALayer fromLayer) = 0 /* overload */;
	virtual double __cdecl cornerRadius() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl display() = 0 ;
	virtual void __cdecl displayIfNeeded() = 0 ;
	virtual void __cdecl drawInContext(void * ctx) = 0 ;
	virtual unsigned __cdecl edgeAntialiasingMask() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl filters() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl frame() = 0 ;
	virtual _di_CALayer __cdecl hitTest(Iosapi::Foundation::NSPoint p) = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithLayer(void * layer) = 0 ;
	virtual void __cdecl insertSublayer(_di_CALayer layer, _di_CALayer above) = 0 /* overload */;
	virtual void __cdecl insertSublayer(_di_CALayer layer, unsigned atIndex) = 0 /* overload */;
	virtual bool __cdecl isDoubleSided() = 0 ;
	virtual bool __cdecl isGeometryFlipped() = 0 ;
	virtual bool __cdecl isHidden() = 0 ;
	virtual bool __cdecl isOpaque() = 0 ;
	virtual void __cdecl layoutIfNeeded() = 0 ;
	virtual void __cdecl layoutSublayers() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl magnificationFilter() = 0 ;
	virtual _di_CALayer __cdecl mask() = 0 ;
	virtual bool __cdecl masksToBounds() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl minificationFilter() = 0 ;
	virtual float __cdecl minificationFilterBias() = 0 ;
	virtual void * __cdecl modelLayer() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual bool __cdecl needsDisplay() = 0 ;
	virtual bool __cdecl needsDisplayOnBoundsChange() = 0 ;
	virtual bool __cdecl needsLayout() = 0 ;
	virtual float __cdecl opacity() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl position() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl preferredFrameSize() = 0 ;
	virtual void * __cdecl presentationLayer() = 0 ;
	virtual double __cdecl rasterizationScale() = 0 ;
	virtual void __cdecl removeAllAnimations() = 0 ;
	virtual void __cdecl removeAnimationForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl removeFromSuperlayer() = 0 ;
	virtual void __cdecl renderInContext(void * ctx) = 0 ;
	virtual void __cdecl scrollPoint(Iosapi::Foundation::NSPoint p) = 0 ;
	virtual void __cdecl scrollRectToVisible(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void __cdecl setActions(Iosapi::Foundation::_di_NSDictionary actions) = 0 ;
	virtual void __cdecl setAffineTransform(Iosapi::Coregraphics::CGAffineTransform m) = 0 ;
	virtual void __cdecl setAnchorPoint(Iosapi::Foundation::NSPoint anchorPoint) = 0 ;
	virtual void __cdecl setAnchorPointZ(double anchorPointZ) = 0 ;
	virtual void __cdecl setBackgroundColor(void * backgroundColor) = 0 ;
	virtual void __cdecl setBackgroundFilters(Iosapi::Foundation::_di_NSArray backgroundFilters) = 0 ;
	virtual void __cdecl setBorderColor(void * borderColor) = 0 ;
	virtual void __cdecl setBorderWidth(double borderWidth) = 0 ;
	virtual void __cdecl setBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual void __cdecl setCompositingFilter(void * compositingFilter) = 0 ;
	virtual void __cdecl setContents(void * contents) = 0 ;
	virtual void __cdecl setContentsCenter(Iosapi::Foundation::NSRect contentsCenter) = 0 ;
	virtual void __cdecl setContentsGravity(Iosapi::Foundation::_di_NSString contentsGravity) = 0 ;
	virtual void __cdecl setContentsRect(Iosapi::Foundation::NSRect contentsRect) = 0 ;
	virtual void __cdecl setContentsScale(double contentsScale) = 0 ;
	virtual void __cdecl setCornerRadius(double cornerRadius) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDoubleSided(bool doubleSided) = 0 ;
	virtual void __cdecl setEdgeAntialiasingMask(unsigned edgeAntialiasingMask) = 0 ;
	virtual void __cdecl setFilters(Iosapi::Foundation::_di_NSArray filters) = 0 ;
	virtual void __cdecl setFrame(Iosapi::Foundation::NSRect frame) = 0 ;
	virtual void __cdecl setGeometryFlipped(bool geometryFlipped) = 0 ;
	virtual void __cdecl setHidden(bool hidden) = 0 ;
	virtual void __cdecl setMagnificationFilter(Iosapi::Foundation::_di_NSString magnificationFilter) = 0 ;
	virtual void __cdecl setMask(_di_CALayer mask) = 0 ;
	virtual void __cdecl setMasksToBounds(bool masksToBounds) = 0 ;
	virtual void __cdecl setMinificationFilter(Iosapi::Foundation::_di_NSString minificationFilter) = 0 ;
	virtual void __cdecl setMinificationFilterBias(float minificationFilterBias) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setNeedsDisplay() = 0 ;
	virtual void __cdecl setNeedsDisplayInRect(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void __cdecl setNeedsDisplayOnBoundsChange(bool needsDisplayOnBoundsChange) = 0 ;
	virtual void __cdecl setNeedsLayout() = 0 ;
	virtual void __cdecl setOpacity(float opacity) = 0 ;
	virtual void __cdecl setOpaque(bool opaque) = 0 ;
	virtual void __cdecl setPosition(Iosapi::Foundation::NSPoint position) = 0 ;
	virtual void __cdecl setRasterizationScale(double rasterizationScale) = 0 ;
	virtual void __cdecl setShadowColor(void * shadowColor) = 0 ;
	virtual void __cdecl setShadowOffset(Iosapi::Foundation::NSSize shadowOffset) = 0 ;
	virtual void __cdecl setShadowOpacity(float shadowOpacity) = 0 ;
	virtual void __cdecl setShadowPath(void * shadowPath) = 0 ;
	virtual void __cdecl setShadowRadius(double shadowRadius) = 0 ;
	virtual void __cdecl setShouldRasterize(bool shouldRasterize) = 0 ;
	virtual void __cdecl setStyle(Iosapi::Foundation::_di_NSDictionary style) = 0 ;
	virtual void __cdecl setSublayerTransform(CATransform3D sublayerTransform) = 0 ;
	virtual void __cdecl setSublayers(Iosapi::Foundation::_di_NSArray sublayers) = 0 ;
	virtual void __cdecl setTransform(CATransform3D transform) = 0 ;
	virtual void __cdecl setZPosition(double zPosition) = 0 ;
	virtual void * __cdecl shadowColor() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl shadowOffset() = 0 ;
	virtual float __cdecl shadowOpacity() = 0 ;
	virtual void * __cdecl shadowPath() = 0 ;
	virtual double __cdecl shadowRadius() = 0 ;
	virtual bool __cdecl shouldArchiveValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual bool __cdecl shouldRasterize() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl style() = 0 ;
	virtual CATransform3D __cdecl sublayerTransform() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sublayers() = 0 ;
	virtual void * __cdecl superlayer() = 0 ;
	virtual CATransform3D __cdecl transform() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl visibleRect() = 0 ;
	virtual double __cdecl zPosition() = 0 ;
};

class PASCALIMPLEMENTATION TCALayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CALayerClass,_di_CALayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CALayerClass,_di_CALayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCALayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CALayerClass,_di_CALayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCALayer() { }
	
};


__interface  INTERFACE_UUID("{336DF8FF-CFB3-4F69-B529-B4D3019C5FC2}") CAEAGLLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{15CBE04C-122F-40B2-9961-3B764EAAA690}") CAEAGLLayer  : public CALayer 
{
	virtual void __cdecl setDrawableProperties(Iosapi::Foundation::_di_NSDictionary properties) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl drawableProperties() = 0 ;
};

__interface  INTERFACE_UUID("{956AA94F-4E97-46A6-AC0C-79631D800D24}") CAEmitterCellClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl defaultValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void * __cdecl emitterCell() = 0 ;
};

__interface  INTERFACE_UUID("{D0DC64BD-BF10-4FFA-8BF4-A184E6B38BCD}") CAEmitterCell  : public Iosapi::Foundation::NSObject 
{
	virtual float __cdecl alphaRange() = 0 ;
	virtual float __cdecl alphaSpeed() = 0 ;
	virtual float __cdecl birthRate() = 0 ;
	virtual float __cdecl blueRange() = 0 ;
	virtual float __cdecl blueSpeed() = 0 ;
	virtual void * __cdecl color() = 0 ;
	virtual void * __cdecl contents() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl contentsRect() = 0 ;
	virtual double __cdecl emissionLatitude() = 0 ;
	virtual double __cdecl emissionLongitude() = 0 ;
	virtual double __cdecl emissionRange() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl emitterCells() = 0 ;
	virtual float __cdecl greenRange() = 0 ;
	virtual float __cdecl greenSpeed() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual float __cdecl lifetime() = 0 ;
	virtual float __cdecl lifetimeRange() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl magnificationFilter() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl minificationFilter() = 0 ;
	virtual float __cdecl minificationFilterBias() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual float __cdecl redRange() = 0 ;
	virtual float __cdecl redSpeed() = 0 ;
	virtual double __cdecl scale() = 0 ;
	virtual double __cdecl scaleRange() = 0 ;
	virtual double __cdecl scaleSpeed() = 0 ;
	virtual void __cdecl setAlphaRange(float alphaRange) = 0 ;
	virtual void __cdecl setAlphaSpeed(float alphaSpeed) = 0 ;
	virtual void __cdecl setBirthRate(float birthRate) = 0 ;
	virtual void __cdecl setBlueRange(float blueRange) = 0 ;
	virtual void __cdecl setBlueSpeed(float blueSpeed) = 0 ;
	virtual void __cdecl setColor(void * color) = 0 ;
	virtual void __cdecl setContents(void * contents) = 0 ;
	virtual void __cdecl setContentsRect(Iosapi::Foundation::NSRect contentsRect) = 0 ;
	virtual void __cdecl setEmissionLatitude(double emissionLatitude) = 0 ;
	virtual void __cdecl setEmissionLongitude(double emissionLongitude) = 0 ;
	virtual void __cdecl setEmissionRange(double emissionRange) = 0 ;
	virtual void __cdecl setEmitterCells(Iosapi::Foundation::_di_NSArray emitterCells) = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setGreenRange(float greenRange) = 0 ;
	virtual void __cdecl setGreenSpeed(float greenSpeed) = 0 ;
	virtual void __cdecl setLifetime(float lifetime) = 0 ;
	virtual void __cdecl setLifetimeRange(float lifetimeRange) = 0 ;
	virtual void __cdecl setMagnificationFilter(Iosapi::Foundation::_di_NSString magnificationFilter) = 0 ;
	virtual void __cdecl setMinificationFilter(Iosapi::Foundation::_di_NSString minificationFilter) = 0 ;
	virtual void __cdecl setMinificationFilterBias(float minificationFilterBias) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setRedRange(float redRange) = 0 ;
	virtual void __cdecl setRedSpeed(float redSpeed) = 0 ;
	virtual void __cdecl setScale(double scale) = 0 ;
	virtual void __cdecl setScaleRange(double scaleRange) = 0 ;
	virtual void __cdecl setScaleSpeed(double scaleSpeed) = 0 ;
	virtual void __cdecl setSpin(double spin) = 0 ;
	virtual void __cdecl setSpinRange(double spinRange) = 0 ;
	virtual void __cdecl setStyle(Iosapi::Foundation::_di_NSDictionary style) = 0 ;
	virtual void __cdecl setVelocity(double velocity) = 0 ;
	virtual void __cdecl setVelocityRange(double velocityRange) = 0 ;
	virtual void __cdecl setXAcceleration(double xAcceleration) = 0 ;
	virtual void __cdecl setYAcceleration(double yAcceleration) = 0 ;
	virtual void __cdecl setZAcceleration(double zAcceleration) = 0 ;
	virtual bool __cdecl shouldArchiveValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual double __cdecl spin() = 0 ;
	virtual double __cdecl spinRange() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl style() = 0 ;
	virtual double __cdecl velocity() = 0 ;
	virtual double __cdecl velocityRange() = 0 ;
	virtual double __cdecl xAcceleration() = 0 ;
	virtual double __cdecl yAcceleration() = 0 ;
	virtual double __cdecl zAcceleration() = 0 ;
};

class PASCALIMPLEMENTATION TCAEmitterCell : public Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterCellClass,_di_CAEmitterCell>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterCellClass,_di_CAEmitterCell> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAEmitterCell(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterCellClass,_di_CAEmitterCell>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAEmitterCell() { }
	
};


__interface  INTERFACE_UUID("{B3FE5B70-791F-4060-A0C2-6F5697483AAD}") NSValueClass  : public Macapi::Objectivec::IObjectiveCClass 
{
	virtual void * __cdecl valueWithCATransform3D(CATransform3D t) = 0 ;
};

__interface  INTERFACE_UUID("{AB368569-2BC0-4074-B3CC-5BAA1064FD05}") NSValue  : public Macapi::Objectivec::IObjectiveCInstance 
{
	virtual CATransform3D __cdecl CATransform3DValue() = 0 ;
};

class PASCALIMPLEMENTATION TNSValue : public Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSValue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSValue() { }
	
};


__interface  INTERFACE_UUID("{A13D480F-54A2-4669-ABD9-6154CC3B83B3}") CAAnimationClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl animation() = 0 ;
	virtual void * __cdecl defaultValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
};

__interface  INTERFACE_UUID("{8A4FBC87-EF63-4E88-811C-C9CADC8808ED}") CAAnimation  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl isRemovedOnCompletion() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setRemovedOnCompletion(bool removedOnCompletion) = 0 ;
	virtual void __cdecl setTimingFunction(_di_CAMediaTimingFunction timingFunction) = 0 ;
	virtual bool __cdecl shouldArchiveValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual _di_CAMediaTimingFunction __cdecl timingFunction() = 0 ;
};

class PASCALIMPLEMENTATION TCAAnimation : public Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationClass,_di_CAAnimation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationClass,_di_CAAnimation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAAnimation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationClass,_di_CAAnimation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAAnimation() { }
	
};


__interface  INTERFACE_UUID("{BD396613-1D5B-4DFB-A474-FA3AB33D1BD8}") NSObjectClass  : public Macapi::Objectivec::IObjectiveCClass 
{
	
};

__interface  INTERFACE_UUID("{19EE70F5-969A-49A1-8A86-54B2FC95E3F3}") NSObject1  : public Macapi::Objectivec::IObjectiveCInstance 
{
	virtual void * __cdecl actionForLayer(_di_CALayer layer, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	virtual void __cdecl animationDidStart(_di_CAAnimation anim) = 0 ;
	virtual void __cdecl animationDidStop(_di_CAAnimation anim, bool finished) = 0 ;
	virtual bool __cdecl autoreverses() = 0 ;
	virtual double __cdecl beginTime() = 0 ;
	virtual void __cdecl displayLayer(_di_CALayer layer) = 0 ;
	virtual void __cdecl drawLayer(_di_CALayer layer, void * inContext) = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fillMode() = 0 ;
	virtual void __cdecl layoutSublayersOfLayer(_di_CALayer layer) = 0 ;
	virtual float __cdecl repeatCount() = 0 ;
	virtual double __cdecl repeatDuration() = 0 ;
	virtual void __cdecl setAutoreverses(bool autoreverses) = 0 ;
	virtual void __cdecl setBeginTime(double beginTime) = 0 ;
	virtual void __cdecl setDuration(double duration) = 0 ;
	virtual void __cdecl setFillMode(Iosapi::Foundation::_di_NSString fillMode) = 0 ;
	virtual void __cdecl setRepeatCount(float repeatCount) = 0 ;
	virtual void __cdecl setRepeatDuration(double repeatDuration) = 0 ;
	virtual void __cdecl setSpeed(float speed) = 0 ;
	virtual void __cdecl setTimeOffset(double timeOffset) = 0 ;
	virtual float __cdecl speed() = 0 ;
	virtual double __cdecl timeOffset() = 0 ;
};

class PASCALIMPLEMENTATION TNSObject : public Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject1>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject1> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSObject(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject1>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSObject() { }
	
};


__interface  INTERFACE_UUID("{138AFE86-6348-44ED-9ED1-31FB10F07EEC}") CADisplayLinkClass  : public NSObjectClass 
{
	virtual void * __cdecl displayLinkWithTarget(void * target, void * selector) = 0 ;
};

__interface  INTERFACE_UUID("{46F85B6A-015A-4D95-8991-DE2997EA2780}") CADisplayLink  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addToRunLoop(Iosapi::Foundation::_di_NSRunLoop runloop, Iosapi::Foundation::_di_NSString forMode) = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual long __cdecl frameInterval() = 0 ;
	virtual void __cdecl invalidate() = 0 ;
	virtual bool __cdecl isPaused() = 0 ;
	virtual void __cdecl removeFromRunLoop(Iosapi::Foundation::_di_NSRunLoop runloop, Iosapi::Foundation::_di_NSString forMode) = 0 ;
	virtual void __cdecl setFrameInterval(long frameInterval) = 0 ;
	virtual void __cdecl setPaused(bool paused) = 0 ;
	virtual double __cdecl timestamp() = 0 ;
};

class PASCALIMPLEMENTATION TCADisplayLink : public Macapi::Objectivec::TOCGenericImport__2<_di_CADisplayLinkClass,_di_CADisplayLink>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CADisplayLinkClass,_di_CADisplayLink> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCADisplayLink(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CADisplayLinkClass,_di_CADisplayLink>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCADisplayLink() { }
	
};


__interface  INTERFACE_UUID("{687313A9-4AFC-4450-9F58-300D4B8A1623}") CATextLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{25F35865-FFAE-4279-8569-58C31EA137B5}") CATextLayer  : public CALayer 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl alignmentMode() = 0 ;
	virtual void * __cdecl font() = 0 ;
	virtual double __cdecl fontSize() = 0 ;
	virtual void * __cdecl foregroundColor() = 0 ;
	virtual bool __cdecl isWrapped() = 0 ;
	virtual void __cdecl setAlignmentMode(Iosapi::Foundation::_di_NSString alignmentMode) = 0 ;
	virtual void __cdecl setFont(void * font) = 0 ;
	virtual void __cdecl setFontSize(double fontSize) = 0 ;
	virtual void __cdecl setForegroundColor(void * foregroundColor) = 0 ;
	virtual void __cdecl setString(void * string_) = 0 ;
	virtual void __cdecl setTruncationMode(Iosapi::Foundation::_di_NSString truncationMode) = 0 ;
	virtual void __cdecl setWrapped(bool wrapped) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl truncationMode() = 0 ;
};

class PASCALIMPLEMENTATION TCATextLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CATextLayerClass,_di_CATextLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CATextLayerClass,_di_CATextLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCATextLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CATextLayerClass,_di_CATextLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCATextLayer() { }
	
};


__interface  INTERFACE_UUID("{AA8C22CC-95FD-4C06-88E8-97348AEAEAC5}") CAShapeLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{B6F59F15-339C-4FAE-AC85-7BC2E423A586}") CAShapeLayer  : public CALayer 
{
	virtual void * __cdecl fillColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fillRule() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl lineCap() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl lineDashPattern() = 0 ;
	virtual double __cdecl lineDashPhase() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl lineJoin() = 0 ;
	virtual double __cdecl lineWidth() = 0 ;
	virtual double __cdecl miterLimit() = 0 ;
	virtual void * __cdecl path() = 0 ;
	virtual void __cdecl setFillColor(void * fillColor) = 0 ;
	virtual void __cdecl setFillRule(Iosapi::Foundation::_di_NSString fillRule) = 0 ;
	virtual void __cdecl setLineCap(Iosapi::Foundation::_di_NSString lineCap) = 0 ;
	virtual void __cdecl setLineDashPattern(Iosapi::Foundation::_di_NSArray lineDashPattern) = 0 ;
	virtual void __cdecl setLineDashPhase(double lineDashPhase) = 0 ;
	virtual void __cdecl setLineJoin(Iosapi::Foundation::_di_NSString lineJoin) = 0 ;
	virtual void __cdecl setLineWidth(double lineWidth) = 0 ;
	virtual void __cdecl setMiterLimit(double miterLimit) = 0 ;
	virtual void __cdecl setPath(void * path) = 0 ;
	virtual void __cdecl setStrokeColor(void * strokeColor) = 0 ;
	virtual void __cdecl setStrokeEnd(double strokeEnd) = 0 ;
	virtual void __cdecl setStrokeStart(double strokeStart) = 0 ;
	virtual void * __cdecl strokeColor() = 0 ;
	virtual double __cdecl strokeEnd() = 0 ;
	virtual double __cdecl strokeStart() = 0 ;
};

class PASCALIMPLEMENTATION TCAShapeLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAShapeLayerClass,_di_CAShapeLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAShapeLayerClass,_di_CAShapeLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAShapeLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAShapeLayerClass,_di_CAShapeLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAShapeLayer() { }
	
};


__interface  INTERFACE_UUID("{40A33A78-F024-476B-AAA0-219DF6F00B56}") CATransitionClass  : public CAAnimationClass 
{
	
};

__interface  INTERFACE_UUID("{34326C31-0298-47CD-ADE9-0ECEE9660F9F}") CATransition  : public CAAnimation 
{
	virtual float __cdecl endProgress() = 0 ;
	virtual void * __cdecl filter() = 0 ;
	virtual void __cdecl setEndProgress(float endProgress) = 0 ;
	virtual void __cdecl setFilter(void * filter) = 0 ;
	virtual void __cdecl setStartProgress(float startProgress) = 0 ;
	virtual void __cdecl setSubtype(Iosapi::Foundation::_di_NSString subtype) = 0 ;
	virtual void __cdecl setType(Iosapi::Foundation::_di_NSString type_) = 0 ;
	virtual float __cdecl startProgress() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subtype() = 0 ;
};

class PASCALIMPLEMENTATION TCATransition : public Macapi::Objectivec::TOCGenericImport__2<_di_CATransitionClass,_di_CATransition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CATransitionClass,_di_CATransition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCATransition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CATransitionClass,_di_CATransition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCATransition() { }
	
};


__interface  INTERFACE_UUID("{910978CC-7D8B-456C-A254-D64E20E44A88}") CATiledLayerClass  : public CALayerClass 
{
	virtual double __cdecl fadeDuration() = 0 ;
};

__interface  INTERFACE_UUID("{E5AB0E1E-345B-4687-8B19-EE4EF0875C00}") CATiledLayer  : public CALayer 
{
	virtual unsigned long __cdecl levelsOfDetail() = 0 ;
	virtual unsigned long __cdecl levelsOfDetailBias() = 0 ;
	virtual void __cdecl setLevelsOfDetail(unsigned long levelsOfDetail) = 0 ;
	virtual void __cdecl setLevelsOfDetailBias(unsigned long levelsOfDetailBias) = 0 ;
	virtual void __cdecl setTileSize(Iosapi::Foundation::NSSize tileSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl tileSize() = 0 ;
};

class PASCALIMPLEMENTATION TCATiledLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CATiledLayerClass,_di_CATiledLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CATiledLayerClass,_di_CATiledLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCATiledLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CATiledLayerClass,_di_CATiledLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCATiledLayer() { }
	
};


__interface  INTERFACE_UUID("{78096F7D-445C-4CC4-A95A-2241DFD9F3FC}") CAAnimationGroupClass  : public CAAnimationClass 
{
	
};

__interface  INTERFACE_UUID("{470DD04E-AC6A-48A2-ABAC-153B6E9FD495}") CAAnimationGroup  : public CAAnimation 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl animations() = 0 ;
	virtual void __cdecl setAnimations(Iosapi::Foundation::_di_NSArray animations) = 0 ;
};

class PASCALIMPLEMENTATION TCAAnimationGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationGroupClass,_di_CAAnimationGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationGroupClass,_di_CAAnimationGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAAnimationGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAAnimationGroupClass,_di_CAAnimationGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAAnimationGroup() { }
	
};


__interface  INTERFACE_UUID("{A6C3B4B9-1CFD-41BB-8989-F953351C3FFE}") CAGradientLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{6C1A836A-054F-4367-8B9D-ABFB8214ACF0}") CAGradientLayer  : public CALayer 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl colors() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl endPoint() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl locations() = 0 ;
	virtual void __cdecl setColors(Iosapi::Foundation::_di_NSArray colors) = 0 ;
	virtual void __cdecl setEndPoint(Iosapi::Foundation::NSPoint endPoint) = 0 ;
	virtual void __cdecl setLocations(Iosapi::Foundation::_di_NSArray locations) = 0 ;
	virtual void __cdecl setStartPoint(Iosapi::Foundation::NSPoint startPoint) = 0 ;
	virtual void __cdecl setType(Iosapi::Foundation::_di_NSString type_) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl startPoint() = 0 ;
};

class PASCALIMPLEMENTATION TCAGradientLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAGradientLayerClass,_di_CAGradientLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAGradientLayerClass,_di_CAGradientLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAGradientLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAGradientLayerClass,_di_CAGradientLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAGradientLayer() { }
	
};


__interface  INTERFACE_UUID("{C945931C-95FE-4008-AA20-6E3D4B04AA27}") CAEmitterLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{04C6F84D-FDB5-4230-A58D-8BCD310977ED}") CAEmitterLayer  : public CALayer 
{
	virtual float __cdecl birthRate() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl emitterCells() = 0 ;
	virtual double __cdecl emitterDepth() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl emitterMode() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl emitterPosition() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl emitterShape() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl emitterSize() = 0 ;
	virtual double __cdecl emitterZPosition() = 0 ;
	virtual float __cdecl lifetime() = 0 ;
	virtual bool __cdecl preservesDepth() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl renderMode() = 0 ;
	virtual float __cdecl scale() = 0 ;
	virtual unsigned __cdecl seed() = 0 ;
	virtual void __cdecl setBirthRate(float birthRate) = 0 ;
	virtual void __cdecl setEmitterCells(Iosapi::Foundation::_di_NSArray emitterCells) = 0 ;
	virtual void __cdecl setEmitterDepth(double emitterDepth) = 0 ;
	virtual void __cdecl setEmitterMode(Iosapi::Foundation::_di_NSString emitterMode) = 0 ;
	virtual void __cdecl setEmitterPosition(Iosapi::Foundation::NSPoint emitterPosition) = 0 ;
	virtual void __cdecl setEmitterShape(Iosapi::Foundation::_di_NSString emitterShape) = 0 ;
	virtual void __cdecl setEmitterSize(Iosapi::Foundation::NSSize emitterSize) = 0 ;
	virtual void __cdecl setEmitterZPosition(double emitterZPosition) = 0 ;
	virtual void __cdecl setLifetime(float lifetime) = 0 ;
	virtual void __cdecl setPreservesDepth(bool preservesDepth) = 0 ;
	virtual void __cdecl setRenderMode(Iosapi::Foundation::_di_NSString renderMode) = 0 ;
	virtual void __cdecl setScale(float scale) = 0 ;
	virtual void __cdecl setSeed(unsigned seed) = 0 ;
	virtual void __cdecl setSpin(float spin) = 0 ;
	virtual void __cdecl setVelocity(float velocity) = 0 ;
	virtual float __cdecl spin() = 0 ;
	virtual float __cdecl velocity() = 0 ;
};

class PASCALIMPLEMENTATION TCAEmitterLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterLayerClass,_di_CAEmitterLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterLayerClass,_di_CAEmitterLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAEmitterLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAEmitterLayerClass,_di_CAEmitterLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAEmitterLayer() { }
	
};


__interface  INTERFACE_UUID("{53FEC26B-BB49-4329-A18A-F9D21790820C}") CAScrollLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{30D38BE9-8B86-465B-9B3D-AC10FA83EF28}") CAScrollLayer  : public CALayer 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl scrollMode() = 0 ;
	virtual void __cdecl scrollToPoint(Iosapi::Foundation::NSPoint p) = 0 ;
	virtual void __cdecl scrollToRect(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void __cdecl setScrollMode(Iosapi::Foundation::_di_NSString scrollMode) = 0 ;
};

class PASCALIMPLEMENTATION TCAScrollLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAScrollLayerClass,_di_CAScrollLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAScrollLayerClass,_di_CAScrollLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAScrollLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAScrollLayerClass,_di_CAScrollLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAScrollLayer() { }
	
};


__interface  INTERFACE_UUID("{6AF9CCC9-2FC7-47C8-A137-48D219B6EE56}") CAReplicatorLayerClass  : public CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{7056CD88-E37B-42F6-A789-3EF980195483}") CAReplicatorLayer  : public CALayer 
{
	virtual float __cdecl instanceAlphaOffset() = 0 ;
	virtual float __cdecl instanceBlueOffset() = 0 ;
	virtual void * __cdecl instanceColor() = 0 ;
	virtual long __cdecl instanceCount() = 0 ;
	virtual double __cdecl instanceDelay() = 0 ;
	virtual float __cdecl instanceGreenOffset() = 0 ;
	virtual float __cdecl instanceRedOffset() = 0 ;
	virtual CATransform3D __cdecl instanceTransform() = 0 ;
	virtual bool __cdecl preservesDepth() = 0 ;
	virtual void __cdecl setInstanceAlphaOffset(float instanceAlphaOffset) = 0 ;
	virtual void __cdecl setInstanceBlueOffset(float instanceBlueOffset) = 0 ;
	virtual void __cdecl setInstanceColor(void * instanceColor) = 0 ;
	virtual void __cdecl setInstanceCount(long instanceCount) = 0 ;
	virtual void __cdecl setInstanceDelay(double instanceDelay) = 0 ;
	virtual void __cdecl setInstanceGreenOffset(float instanceGreenOffset) = 0 ;
	virtual void __cdecl setInstanceRedOffset(float instanceRedOffset) = 0 ;
	virtual void __cdecl setInstanceTransform(CATransform3D instanceTransform) = 0 ;
	virtual void __cdecl setPreservesDepth(bool preservesDepth) = 0 ;
};

class PASCALIMPLEMENTATION TCAReplicatorLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAReplicatorLayerClass,_di_CAReplicatorLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAReplicatorLayerClass,_di_CAReplicatorLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAReplicatorLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAReplicatorLayerClass,_di_CAReplicatorLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAReplicatorLayer() { }
	
};


__interface  INTERFACE_UUID("{F35A28FD-2177-4445-A0BB-9464EA18E825}") CAPropertyAnimationClass  : public CAAnimationClass 
{
	virtual void * __cdecl animationWithKeyPath(Iosapi::Foundation::_di_NSString path) = 0 ;
};

__interface  INTERFACE_UUID("{92ADB3CB-1066-40B5-8D65-75F9321599DB}") CAPropertyAnimation  : public CAAnimation 
{
	virtual bool __cdecl isAdditive() = 0 ;
	virtual bool __cdecl isCumulative() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl keyPath() = 0 ;
	virtual void __cdecl setAdditive(bool additive) = 0 ;
	virtual void __cdecl setCumulative(bool cumulative) = 0 ;
	virtual void __cdecl setKeyPath(Iosapi::Foundation::_di_NSString keyPath) = 0 ;
	virtual void __cdecl setValueFunction(_di_CAValueFunction valueFunction) = 0 ;
	virtual _di_CAValueFunction __cdecl valueFunction() = 0 ;
};

class PASCALIMPLEMENTATION TCAPropertyAnimation : public Macapi::Objectivec::TOCGenericImport__2<_di_CAPropertyAnimationClass,_di_CAPropertyAnimation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAPropertyAnimationClass,_di_CAPropertyAnimation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAPropertyAnimation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAPropertyAnimationClass,_di_CAPropertyAnimation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAPropertyAnimation() { }
	
};


__interface  INTERFACE_UUID("{14F31E2F-3337-4C7C-9095-CC7A6A2EAB97}") CABasicAnimationClass  : public CAPropertyAnimationClass 
{
	
};

__interface  INTERFACE_UUID("{D9ECBF10-0F2C-4A16-B0D4-8A3AAF407C48}") CABasicAnimation  : public CAPropertyAnimation 
{
	virtual void * __cdecl byValue() = 0 ;
	virtual void * __cdecl fromValue() = 0 ;
	virtual void __cdecl setByValue(void * byValue) = 0 ;
	virtual void __cdecl setFromValue(void * fromValue) = 0 ;
	virtual void __cdecl setToValue(void * toValue) = 0 ;
	virtual void * __cdecl toValue() = 0 ;
};

class PASCALIMPLEMENTATION TCABasicAnimation : public Macapi::Objectivec::TOCGenericImport__2<_di_CABasicAnimationClass,_di_CABasicAnimation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CABasicAnimationClass,_di_CABasicAnimation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCABasicAnimation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CABasicAnimationClass,_di_CABasicAnimation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCABasicAnimation() { }
	
};


__interface  INTERFACE_UUID("{ECA2D5FD-43C5-4F9F-99AA-007DC451BF36}") CAKeyframeAnimationClass  : public CAPropertyAnimationClass 
{
	
};

__interface  INTERFACE_UUID("{43BC07D7-DAAC-49D0-9D7A-9BD9E4410CEA}") CAKeyframeAnimation  : public CAPropertyAnimation 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl biasValues() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl calculationMode() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl continuityValues() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl keyTimes() = 0 ;
	virtual void * __cdecl path() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl rotationMode() = 0 ;
	virtual void __cdecl setBiasValues(Iosapi::Foundation::_di_NSArray biasValues) = 0 ;
	virtual void __cdecl setCalculationMode(Iosapi::Foundation::_di_NSString calculationMode) = 0 ;
	virtual void __cdecl setContinuityValues(Iosapi::Foundation::_di_NSArray continuityValues) = 0 ;
	virtual void __cdecl setKeyTimes(Iosapi::Foundation::_di_NSArray keyTimes) = 0 ;
	virtual void __cdecl setPath(void * path) = 0 ;
	virtual void __cdecl setRotationMode(Iosapi::Foundation::_di_NSString rotationMode) = 0 ;
	virtual void __cdecl setTensionValues(Iosapi::Foundation::_di_NSArray tensionValues) = 0 ;
	virtual void __cdecl setTimingFunctions(Iosapi::Foundation::_di_NSArray timingFunctions) = 0 ;
	virtual void __cdecl setValues(Iosapi::Foundation::_di_NSArray values) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tensionValues() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl timingFunctions() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl values() = 0 ;
};

class PASCALIMPLEMENTATION TCAKeyframeAnimation : public Macapi::Objectivec::TOCGenericImport__2<_di_CAKeyframeAnimationClass,_di_CAKeyframeAnimation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAKeyframeAnimationClass,_di_CAKeyframeAnimation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAKeyframeAnimation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAKeyframeAnimationClass,_di_CAKeyframeAnimation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAKeyframeAnimation() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CA_WARN_DEPRECATED = System::Int8(0x1);
static constexpr System::Int8 kCALayerBottomEdge = System::Int8(0x4);
static constexpr System::Int8 kCALayerLeftEdge = System::Int8(0x1);
static constexpr System::Int8 kCALayerRightEdge = System::Int8(0x2);
static constexpr System::Int8 kCALayerTopEdge = System::Int8(0x8);
#define libQuartzCore u"/System/Library/Frameworks/QuartzCore.framework/QuartzCore"
extern "C" double __cdecl CACurrentMediaTime(void);
extern "C" CATransform3D __cdecl CATransform3DConcat(CATransform3D a, CATransform3D b);
extern "C" int __cdecl CATransform3DEqualToTransform(CATransform3D a, CATransform3D b);
extern "C" Iosapi::Coregraphics::CGAffineTransform __cdecl CATransform3DGetAffineTransform(CATransform3D t);
extern "C" CATransform3D __cdecl CATransform3DInvert(CATransform3D t);
extern "C" int __cdecl CATransform3DIsAffine(CATransform3D t);
extern "C" int __cdecl CATransform3DIsIdentity(CATransform3D t);
extern "C" CATransform3D __cdecl CATransform3DMakeAffineTransform(Iosapi::Coregraphics::CGAffineTransform m);
extern "C" CATransform3D __cdecl CATransform3DMakeRotation(double angle, double x, double y, double z);
extern "C" CATransform3D __cdecl CATransform3DMakeScale(double sx, double sy, double sz);
extern "C" CATransform3D __cdecl CATransform3DMakeTranslation(double tx, double ty, double tz);
extern "C" CATransform3D __cdecl CATransform3DRotate(CATransform3D t, double angle, double x, double y, double z);
extern "C" CATransform3D __cdecl CATransform3DScale(CATransform3D t, double sx, double sy, double sz);
extern "C" CATransform3D __cdecl CATransform3DTranslate(CATransform3D t, double tx, double ty, double tz);
}	/* namespace Quartzcore */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_QUARTZCORE)
using namespace Iosapi::Quartzcore;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_QuartzcoreHPP
