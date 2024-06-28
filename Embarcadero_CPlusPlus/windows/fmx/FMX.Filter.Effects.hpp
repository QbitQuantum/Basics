// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Filter.Effects.pas' rev: 34.00 (Windows)

#ifndef Fmx_Filter_EffectsHPP
#define Fmx_Filter_EffectsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Filter.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FMX.Filter.Effects"

namespace Fmx
{
namespace Filter
{
namespace Effects
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFilterBaseFilter;
class DELPHICLASS TFilterPixelateTransition;
class DELPHICLASS TFilterBrightTransition;
class DELPHICLASS TFilterSwirlTransition;
class DELPHICLASS TFilterDissolveTransition;
class DELPHICLASS TFilterBloodTransition;
class DELPHICLASS TFilterBlurTransition;
class DELPHICLASS TFilterDropTransition;
class DELPHICLASS TFilterCrumpleTransition;
class DELPHICLASS TFilterWaterTransition;
class DELPHICLASS TFilterBandedSwirlTransition;
class DELPHICLASS TFilterSwipeTransition;
class DELPHICLASS TFilterSlideTransition;
class DELPHICLASS TFilterMagnifyTransition;
class DELPHICLASS TFilterLineTransition;
class DELPHICLASS TFilterRotateCrumpleTransition;
class DELPHICLASS TFilterRippleTransition;
class DELPHICLASS TFilterCircleTransition;
class DELPHICLASS TFilterWiggleTransition;
class DELPHICLASS TFilterSaturateTransition;
class DELPHICLASS TFilterWaveTransition;
class DELPHICLASS TFilterFadeTransition;
class DELPHICLASS TFilterBlindTransition;
class DELPHICLASS TFilterShapeTransition;
class DELPHICLASS TFilterPencilStroke;
class DELPHICLASS TFilterSharpen;
class DELPHICLASS TFilterEmboss;
class DELPHICLASS TFilterSepia;
class DELPHICLASS TFilterPaperSketch;
class DELPHICLASS TFilterPixelate;
class DELPHICLASS TFilterToon;
class DELPHICLASS TFilterWave;
class DELPHICLASS TFilterBandedSwirl;
class DELPHICLASS TFilterSmoothMagnify;
class DELPHICLASS TFilterWrap;
class DELPHICLASS TFilterSwirl;
class DELPHICLASS TFilterBands;
class DELPHICLASS TFilterMagnify;
class DELPHICLASS TFilterPinch;
class DELPHICLASS TFilterRipple;
class DELPHICLASS TFilterPerspectiveTransform;
class DELPHICLASS TFilterCrop;
class DELPHICLASS TFilterAffineTransform;
class DELPHICLASS TFilterTiler;
class DELPHICLASS TFilterDirectionalBlur;
class DELPHICLASS TFilterRadialBlur;
class DELPHICLASS TFilterGaussianBlur;
class DELPHICLASS TFilterBoxBlur;
class DELPHICLASS TFilterMaskToAlpha;
class DELPHICLASS TFilterColorKeyAlpha;
class DELPHICLASS TFilterMonochrome;
class DELPHICLASS TFilterInvert;
class DELPHICLASS TFilterGloom;
class DELPHICLASS TFilterHueAdjust;
class DELPHICLASS TFilterBloom;
class DELPHICLASS TFilterContrast;
class DELPHICLASS TFilterFill;
class DELPHICLASS TFilterFillRGB;
class DELPHICLASS TFilterNormalBlend;
class DELPHICLASS TImageFXEffect;
class DELPHICLASS TPixelateTransitionEffect;
class DELPHICLASS TBrightTransitionEffect;
class DELPHICLASS TSwirlTransitionEffect;
class DELPHICLASS TDissolveTransitionEffect;
class DELPHICLASS TBloodTransitionEffect;
class DELPHICLASS TBlurTransitionEffect;
class DELPHICLASS TDropTransitionEffect;
class DELPHICLASS TCrumpleTransitionEffect;
class DELPHICLASS TWaterTransitionEffect;
class DELPHICLASS TBandedSwirlTransitionEffect;
class DELPHICLASS TSwipeTransitionEffect;
class DELPHICLASS TSlideTransitionEffect;
class DELPHICLASS TMagnifyTransitionEffect;
class DELPHICLASS TLineTransitionEffect;
class DELPHICLASS TRotateCrumpleTransitionEffect;
class DELPHICLASS TRippleTransitionEffect;
class DELPHICLASS TCircleTransitionEffect;
class DELPHICLASS TWiggleTransitionEffect;
class DELPHICLASS TSaturateTransitionEffect;
class DELPHICLASS TWaveTransitionEffect;
class DELPHICLASS TFadeTransitionEffect;
class DELPHICLASS TBlindTransitionEffect;
class DELPHICLASS TShapeTransitionEffect;
class DELPHICLASS TPencilStrokeEffect;
class DELPHICLASS TSharpenEffect;
class DELPHICLASS TEmbossEffect;
class DELPHICLASS TSepiaEffect;
class DELPHICLASS TPaperSketchEffect;
class DELPHICLASS TPixelateEffect;
class DELPHICLASS TToonEffect;
class DELPHICLASS TWaveEffect;
class DELPHICLASS TBandedSwirlEffect;
class DELPHICLASS TSmoothMagnifyEffect;
class DELPHICLASS TWrapEffect;
class DELPHICLASS TSwirlEffect;
class DELPHICLASS TBandsEffect;
class DELPHICLASS TMagnifyEffect;
class DELPHICLASS TPinchEffect;
class DELPHICLASS TRippleEffect;
class DELPHICLASS TPerspectiveTransformEffect;
class DELPHICLASS TCropEffect;
class DELPHICLASS TAffineTransformEffect;
class DELPHICLASS TTilerEffect;
class DELPHICLASS TDirectionalBlurEffect;
class DELPHICLASS TRadialBlurEffect;
class DELPHICLASS TGaussianBlurEffect;
class DELPHICLASS TBoxBlurEffect;
class DELPHICLASS TMaskToAlphaEffect;
class DELPHICLASS TColorKeyAlphaEffect;
class DELPHICLASS TMonochromeEffect;
class DELPHICLASS TInvertEffect;
class DELPHICLASS TGloomEffect;
class DELPHICLASS THueAdjustEffect;
class DELPHICLASS TBloomEffect;
class DELPHICLASS TContrastEffect;
class DELPHICLASS TFillEffect;
class DELPHICLASS TFillRGBEffect;
class DELPHICLASS TNormalBlendEffect;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFilterBaseFilter : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	Fmx::Filter::TFilter* FFilter;
	TFilterBaseFilter* FInputFilter;
	Fmx::Graphics::TBitmap* __fastcall GetOutput();
	void __fastcall SetInput(Fmx::Graphics::TBitmap* const AValue);
	void __fastcall SetInputFilter(TFilterBaseFilter* const AValue);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TFilterBaseFilter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFilterBaseFilter();
	__property Fmx::Graphics::TBitmap* Input = {write=SetInput};
	__property Fmx::Graphics::TBitmap* Output = {read=GetOutput};
	
__published:
	__property TFilterBaseFilter* InputFilter = {read=FInputFilter, write=SetInputFilter};
};


class PASCALIMPLEMENTATION TFilterPixelateTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPixelateTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPixelateTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterBrightTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBrightTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBrightTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterSwirlTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float Strength = {read=GetStrength, write=SetStrength};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSwirlTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSwirlTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterDissolveTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterDissolveTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterDissolveTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterBloodTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBloodTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBloodTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterBlurTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBlurTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBlurTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterDropTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterDropTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterDropTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterCrumpleTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterCrumpleTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterCrumpleTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterWaterTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterWaterTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterWaterTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterBandedSwirlTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetFrequency();
	void __fastcall SetFrequency(float AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float Frequency = {read=GetFrequency, write=SetFrequency};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBandedSwirlTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBandedSwirlTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterSwipeTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetMousePoint();
	void __fastcall SetMousePoint(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetCornerPoint();
	void __fastcall SetCornerPoint(const System::Types::TPointF &AValue);
	float __fastcall GetDeep();
	void __fastcall SetDeep(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	Fmx::Graphics::TBitmap* __fastcall GetBack();
	void __fastcall SetBack(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property System::Types::TPointF MousePoint = {read=GetMousePoint, write=SetMousePoint};
	__property System::Types::TPointF CornerPoint = {read=GetCornerPoint, write=SetCornerPoint};
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Back = {read=GetBack, write=SetBack};
	
__published:
	__property float Deep = {read=GetDeep, write=SetDeep};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSwipeTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSwipeTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterSlideTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetSlideAmount();
	void __fastcall SetSlideAmount(const System::Types::TPointF &AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property System::Types::TPointF SlideAmount = {read=GetSlideAmount, write=SetSlideAmount};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSlideTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSlideTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterMagnifyTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterMagnifyTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterMagnifyTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterLineTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetOrigin();
	void __fastcall SetOrigin(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetNormal();
	void __fastcall SetNormal(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetOffsetProp();
	void __fastcall SetOffsetProp(const System::Types::TPointF &AValue);
	float __fastcall GetFuzzyAmount();
	void __fastcall SetFuzzyAmount(float AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property System::Types::TPointF Origin = {read=GetOrigin, write=SetOrigin};
	__property System::Types::TPointF Normal = {read=GetNormal, write=SetNormal};
	__property System::Types::TPointF OffsetProp = {read=GetOffsetProp, write=SetOffsetProp};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float FuzzyAmount = {read=GetFuzzyAmount, write=SetFuzzyAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterLineTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterLineTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterRotateCrumpleTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterRotateCrumpleTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterRotateCrumpleTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterRippleTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterRippleTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterRippleTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterCircleTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetFuzzyAmount();
	void __fastcall SetFuzzyAmount(float AValue);
	float __fastcall GetCircleSize();
	void __fastcall SetCircleSize(float AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float FuzzyAmount = {read=GetFuzzyAmount, write=SetFuzzyAmount};
	__property float CircleSize = {read=GetCircleSize, write=SetCircleSize};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterCircleTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterCircleTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterWiggleTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterWiggleTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterWiggleTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterSaturateTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSaturateTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSaturateTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterWaveTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterWaveTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterWaveTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterFadeTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterFadeTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterFadeTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterBlindTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetNumberOfBlinds();
	void __fastcall SetNumberOfBlinds(float AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float NumberOfBlinds = {read=GetNumberOfBlinds, write=SetNumberOfBlinds};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBlindTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBlindTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterShapeTransition : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	Fmx::Graphics::TBitmap* __fastcall GetSecond();
	void __fastcall SetSecond(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Second = {read=GetSecond, write=SetSecond};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterShapeTransition(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterShapeTransition() { }
	
};


class PASCALIMPLEMENTATION TFilterPencilStroke : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetbrushSize();
	void __fastcall SetbrushSize(float AValue);
	
__published:
	__property float brushSize = {read=GetbrushSize, write=SetbrushSize};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPencilStroke(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPencilStroke() { }
	
};


class PASCALIMPLEMENTATION TFilterSharpen : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSharpen(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSharpen() { }
	
};


class PASCALIMPLEMENTATION TFilterEmboss : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	float __fastcall GetWidth();
	void __fastcall SetWidth(float AValue);
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
	__property float Width = {read=GetWidth, write=SetWidth};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterEmboss(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterEmboss() { }
	
};


class PASCALIMPLEMENTATION TFilterSepia : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSepia(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSepia() { }
	
};


class PASCALIMPLEMENTATION TFilterPaperSketch : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetbrushSize();
	void __fastcall SetbrushSize(float AValue);
	
__published:
	__property float brushSize = {read=GetbrushSize, write=SetbrushSize};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPaperSketch(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPaperSketch() { }
	
};


class PASCALIMPLEMENTATION TFilterPixelate : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBlockCount();
	void __fastcall SetBlockCount(float AValue);
	
__published:
	__property float BlockCount = {read=GetBlockCount, write=SetBlockCount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPixelate(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPixelate() { }
	
};


class PASCALIMPLEMENTATION TFilterToon : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetLevels();
	void __fastcall SetLevels(float AValue);
	
__published:
	__property float Levels = {read=GetLevels, write=SetLevels};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterToon(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterToon() { }
	
};


class PASCALIMPLEMENTATION TFilterWave : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetTime();
	void __fastcall SetTime(float AValue);
	float __fastcall GetWaveSize();
	void __fastcall SetWaveSize(float AValue);
	
__published:
	__property float Time = {read=GetTime, write=SetTime};
	__property float WaveSize = {read=GetWaveSize, write=SetWaveSize};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterWave(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterWave() { }
	
};


class PASCALIMPLEMENTATION TFilterBandedSwirl : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetBands();
	void __fastcall SetBands(float AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Bands = {read=GetBands, write=SetBands};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBandedSwirl(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBandedSwirl() { }
	
};


class PASCALIMPLEMENTATION TFilterSmoothMagnify : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetInnerRadius();
	void __fastcall SetInnerRadius(float AValue);
	float __fastcall GetOuterRadius();
	void __fastcall SetOuterRadius(float AValue);
	float __fastcall GetMagnification();
	void __fastcall SetMagnification(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float InnerRadius = {read=GetInnerRadius, write=SetInnerRadius};
	__property float OuterRadius = {read=GetOuterRadius, write=SetOuterRadius};
	__property float Magnification = {read=GetMagnification, write=SetMagnification};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSmoothMagnify(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSmoothMagnify() { }
	
};


class PASCALIMPLEMENTATION TFilterWrap : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetLeftStart();
	void __fastcall SetLeftStart(float AValue);
	float __fastcall GetLeftControl1();
	void __fastcall SetLeftControl1(float AValue);
	float __fastcall GetLeftControl2();
	void __fastcall SetLeftControl2(float AValue);
	float __fastcall GetLeftEnd();
	void __fastcall SetLeftEnd(float AValue);
	float __fastcall GetRightStart();
	void __fastcall SetRightStart(float AValue);
	float __fastcall GetRightControl1();
	void __fastcall SetRightControl1(float AValue);
	float __fastcall GetRightControl2();
	void __fastcall SetRightControl2(float AValue);
	float __fastcall GetRightEnd();
	void __fastcall SetRightEnd(float AValue);
	
__published:
	__property float LeftStart = {read=GetLeftStart, write=SetLeftStart};
	__property float LeftControl1 = {read=GetLeftControl1, write=SetLeftControl1};
	__property float LeftControl2 = {read=GetLeftControl2, write=SetLeftControl2};
	__property float LeftEnd = {read=GetLeftEnd, write=SetLeftEnd};
	__property float RightStart = {read=GetRightStart, write=SetRightStart};
	__property float RightControl1 = {read=GetRightControl1, write=SetRightControl1};
	__property float RightControl2 = {read=GetRightControl2, write=SetRightControl2};
	__property float RightEnd = {read=GetRightEnd, write=SetRightEnd};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterWrap(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterWrap() { }
	
};


class PASCALIMPLEMENTATION TFilterSwirl : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetSpiralStrength();
	void __fastcall SetSpiralStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float SpiralStrength = {read=GetSpiralStrength, write=SetSpiralStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterSwirl(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterSwirl() { }
	
};


class PASCALIMPLEMENTATION TFilterBands : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBandDensity();
	void __fastcall SetBandDensity(float AValue);
	float __fastcall GetBandIntensity();
	void __fastcall SetBandIntensity(float AValue);
	
__published:
	__property float BandDensity = {read=GetBandDensity, write=SetBandDensity};
	__property float BandIntensity = {read=GetBandIntensity, write=SetBandIntensity};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBands(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBands() { }
	
};


class PASCALIMPLEMENTATION TFilterMagnify : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRadius();
	void __fastcall SetRadius(float AValue);
	float __fastcall GetMagnification();
	void __fastcall SetMagnification(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Radius = {read=GetRadius, write=SetRadius};
	__property float Magnification = {read=GetMagnification, write=SetMagnification};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterMagnify(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterMagnify() { }
	
};


class PASCALIMPLEMENTATION TFilterPinch : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRadius();
	void __fastcall SetRadius(float AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Radius = {read=GetRadius, write=SetRadius};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPinch(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPinch() { }
	
};


class PASCALIMPLEMENTATION TFilterRipple : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetAmplitude();
	void __fastcall SetAmplitude(float AValue);
	float __fastcall GetFrequency();
	void __fastcall SetFrequency(float AValue);
	float __fastcall GetPhase();
	void __fastcall SetPhase(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Amplitude = {read=GetAmplitude, write=SetAmplitude};
	__property float Frequency = {read=GetFrequency, write=SetFrequency};
	__property float Phase = {read=GetPhase, write=SetPhase};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterRipple(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterRipple() { }
	
};


class PASCALIMPLEMENTATION TFilterPerspectiveTransform : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetTopLeft();
	void __fastcall SetTopLeft(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetTopRight();
	void __fastcall SetTopRight(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetBottomRight();
	void __fastcall SetBottomRight(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetBottomLeft();
	void __fastcall SetBottomLeft(const System::Types::TPointF &AValue);
	
public:
	__property System::Types::TPointF TopLeft = {read=GetTopLeft, write=SetTopLeft};
	__property System::Types::TPointF TopRight = {read=GetTopRight, write=SetTopRight};
	__property System::Types::TPointF BottomRight = {read=GetBottomRight, write=SetBottomRight};
	__property System::Types::TPointF BottomLeft = {read=GetBottomLeft, write=SetBottomLeft};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterPerspectiveTransform(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterPerspectiveTransform() { }
	
};


class PASCALIMPLEMENTATION TFilterCrop : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetLeftTop();
	void __fastcall SetLeftTop(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetRightBottom();
	void __fastcall SetRightBottom(const System::Types::TPointF &AValue);
	
public:
	__property System::Types::TPointF LeftTop = {read=GetLeftTop, write=SetLeftTop};
	__property System::Types::TPointF RightBottom = {read=GetRightBottom, write=SetRightBottom};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterCrop(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterCrop() { }
	
};


class PASCALIMPLEMENTATION TFilterAffineTransform : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRotation();
	void __fastcall SetRotation(float AValue);
	float __fastcall GetScale();
	void __fastcall SetScale(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Rotation = {read=GetRotation, write=SetRotation};
	__property float Scale = {read=GetScale, write=SetScale};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterAffineTransform(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterAffineTransform() { }
	
};


class PASCALIMPLEMENTATION TFilterTiler : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetVerticalTileCount();
	void __fastcall SetVerticalTileCount(float AValue);
	float __fastcall GetHorizontalTileCount();
	void __fastcall SetHorizontalTileCount(float AValue);
	float __fastcall GetHorizontalOffset();
	void __fastcall SetHorizontalOffset(float AValue);
	float __fastcall GetVerticalOffset();
	void __fastcall SetVerticalOffset(float AValue);
	
__published:
	__property float VerticalTileCount = {read=GetVerticalTileCount, write=SetVerticalTileCount};
	__property float HorizontalTileCount = {read=GetHorizontalTileCount, write=SetHorizontalTileCount};
	__property float HorizontalOffset = {read=GetHorizontalOffset, write=SetHorizontalOffset};
	__property float VerticalOffset = {read=GetVerticalOffset, write=SetVerticalOffset};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterTiler(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterTiler() { }
	
};


class PASCALIMPLEMENTATION TFilterDirectionalBlur : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetAngle();
	void __fastcall SetAngle(float AValue);
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
__published:
	__property float Angle = {read=GetAngle, write=SetAngle};
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterDirectionalBlur(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterDirectionalBlur() { }
	
};


class PASCALIMPLEMENTATION TFilterRadialBlur : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
public:
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterRadialBlur(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterRadialBlur() { }
	
};


class PASCALIMPLEMENTATION TFilterGaussianBlur : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterGaussianBlur(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterGaussianBlur() { }
	
};


class PASCALIMPLEMENTATION TFilterBoxBlur : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBoxBlur(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBoxBlur() { }
	
};


class PASCALIMPLEMENTATION TFilterMaskToAlpha : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterMaskToAlpha(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterMaskToAlpha() { }
	
};


class PASCALIMPLEMENTATION TFilterColorKeyAlpha : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColorKey();
	void __fastcall SetColorKey(System::Uitypes::TAlphaColor AValue);
	float __fastcall GetTolerance();
	void __fastcall SetTolerance(float AValue);
	
__published:
	__property System::Uitypes::TAlphaColor ColorKey = {read=GetColorKey, write=SetColorKey, nodefault};
	__property float Tolerance = {read=GetTolerance, write=SetTolerance};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterColorKeyAlpha(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterColorKeyAlpha() { }
	
};


class PASCALIMPLEMENTATION TFilterMonochrome : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterMonochrome(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterMonochrome() { }
	
};


class PASCALIMPLEMENTATION TFilterInvert : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterInvert(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterInvert() { }
	
};


class PASCALIMPLEMENTATION TFilterGloom : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetGloomIntensity();
	void __fastcall SetGloomIntensity(float AValue);
	float __fastcall GetBaseIntensity();
	void __fastcall SetBaseIntensity(float AValue);
	float __fastcall GetGloomSaturation();
	void __fastcall SetGloomSaturation(float AValue);
	float __fastcall GetBaseSaturation();
	void __fastcall SetBaseSaturation(float AValue);
	
__published:
	__property float GloomIntensity = {read=GetGloomIntensity, write=SetGloomIntensity};
	__property float BaseIntensity = {read=GetBaseIntensity, write=SetBaseIntensity};
	__property float GloomSaturation = {read=GetGloomSaturation, write=SetGloomSaturation};
	__property float BaseSaturation = {read=GetBaseSaturation, write=SetBaseSaturation};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterGloom(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterGloom() { }
	
};


class PASCALIMPLEMENTATION TFilterHueAdjust : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetHue();
	void __fastcall SetHue(float AValue);
	
__published:
	__property float Hue = {read=GetHue, write=SetHue};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterHueAdjust(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterHueAdjust() { }
	
};


class PASCALIMPLEMENTATION TFilterBloom : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBloomIntensity();
	void __fastcall SetBloomIntensity(float AValue);
	float __fastcall GetBaseIntensity();
	void __fastcall SetBaseIntensity(float AValue);
	float __fastcall GetBloomSaturation();
	void __fastcall SetBloomSaturation(float AValue);
	float __fastcall GetBaseSaturation();
	void __fastcall SetBaseSaturation(float AValue);
	
__published:
	__property float BloomIntensity = {read=GetBloomIntensity, write=SetBloomIntensity};
	__property float BaseIntensity = {read=GetBaseIntensity, write=SetBaseIntensity};
	__property float BloomSaturation = {read=GetBloomSaturation, write=SetBloomSaturation};
	__property float BaseSaturation = {read=GetBaseSaturation, write=SetBaseSaturation};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterBloom(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterBloom() { }
	
};


class PASCALIMPLEMENTATION TFilterContrast : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	float __fastcall GetBrightness();
	void __fastcall SetBrightness(float AValue);
	float __fastcall GetContrast();
	void __fastcall SetContrast(float AValue);
	
__published:
	__property float Brightness = {read=GetBrightness, write=SetBrightness};
	__property float Contrast = {read=GetContrast, write=SetContrast};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterContrast(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterContrast() { }
	
};


class PASCALIMPLEMENTATION TFilterFill : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(System::Uitypes::TAlphaColor AValue);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterFill(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterFill() { }
	
};


class PASCALIMPLEMENTATION TFilterFillRGB : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(System::Uitypes::TAlphaColor AValue);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterFillRGB(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterFillRGB() { }
	
};


class PASCALIMPLEMENTATION TFilterNormalBlend : public TFilterBaseFilter
{
	typedef TFilterBaseFilter inherited;
	
private:
	Fmx::Graphics::TBitmap* __fastcall GetTarget();
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__property Fmx::Graphics::TBitmap* Target = {read=GetTarget, write=SetTarget};
public:
	/* TFilterBaseFilter.Create */ inline __fastcall virtual TFilterNormalBlend(System::Classes::TComponent* AOwner) : TFilterBaseFilter(AOwner) { }
	/* TFilterBaseFilter.Destroy */ inline __fastcall virtual ~TFilterNormalBlend() { }
	
};


class PASCALIMPLEMENTATION TImageFXEffect : public Fmx::Effects::TFilterEffect
{
	typedef Fmx::Effects::TFilterEffect inherited;
	
protected:
	virtual Fmx::Filter::TFilter* __fastcall CreateFilter();
	
__published:
	__property Trigger = {default=0};
	__property Enabled = {default=1};
public:
	/* TFilterEffect.Create */ inline __fastcall virtual TImageFXEffect(System::Classes::TComponent* AOwner) : Fmx::Effects::TFilterEffect(AOwner) { }
	/* TFilterEffect.Destroy */ inline __fastcall virtual ~TImageFXEffect() { }
	
};


class PASCALIMPLEMENTATION TPixelateTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TPixelateTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPixelateTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TBrightTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TBrightTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBrightTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TSwirlTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	
public:
	__fastcall virtual TSwirlTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSwirlTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float Strength = {read=GetStrength, write=SetStrength};
};


class PASCALIMPLEMENTATION TDissolveTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TDissolveTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDissolveTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TBloodTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TBloodTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBloodTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TBlurTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TBlurTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBlurTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TDropTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TDropTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDropTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TCrumpleTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TCrumpleTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCrumpleTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TWaterTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TWaterTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWaterTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TBandedSwirlTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetFrequency();
	void __fastcall SetFrequency(float AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TBandedSwirlTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBandedSwirlTransitionEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float Frequency = {read=GetFrequency, write=SetFrequency};
};


class PASCALIMPLEMENTATION TSwipeTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	Fmx::Graphics::TBitmap* FBack;
	void __fastcall BackChanged(System::TObject* Sender);
	System::Types::TPointF __fastcall GetMousePoint();
	void __fastcall SetMousePoint(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetCornerPoint();
	void __fastcall SetCornerPoint(const System::Types::TPointF &AValue);
	float __fastcall GetDeep();
	void __fastcall SetDeep(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	void __fastcall SetBack(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TSwipeTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSwipeTransitionEffect();
	__property System::Types::TPointF MousePoint = {read=GetMousePoint, write=SetMousePoint};
	__property System::Types::TPointF CornerPoint = {read=GetCornerPoint, write=SetCornerPoint};
	
__published:
	__property float Deep = {read=GetDeep, write=SetDeep};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property Fmx::Graphics::TBitmap* Back = {read=FBack, write=SetBack};
};


class PASCALIMPLEMENTATION TSlideTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetSlideAmount();
	void __fastcall SetSlideAmount(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TSlideTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSlideTransitionEffect();
	__property System::Types::TPointF SlideAmount = {read=GetSlideAmount, write=SetSlideAmount};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TMagnifyTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TMagnifyTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMagnifyTransitionEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TLineTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	System::Types::TPointF __fastcall GetOrigin();
	void __fastcall SetOrigin(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetNormal();
	void __fastcall SetNormal(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetOffsetProp();
	void __fastcall SetOffsetProp(const System::Types::TPointF &AValue);
	float __fastcall GetFuzzyAmount();
	void __fastcall SetFuzzyAmount(float AValue);
	
public:
	__fastcall virtual TLineTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLineTransitionEffect();
	__property System::Types::TPointF Origin = {read=GetOrigin, write=SetOrigin};
	__property System::Types::TPointF Normal = {read=GetNormal, write=SetNormal};
	__property System::Types::TPointF OffsetProp = {read=GetOffsetProp, write=SetOffsetProp};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float FuzzyAmount = {read=GetFuzzyAmount, write=SetFuzzyAmount};
};


class PASCALIMPLEMENTATION TRotateCrumpleTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TRotateCrumpleTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRotateCrumpleTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TRippleTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TRippleTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRippleTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TCircleTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetFuzzyAmount();
	void __fastcall SetFuzzyAmount(float AValue);
	float __fastcall GetCircleSize();
	void __fastcall SetCircleSize(float AValue);
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TCircleTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCircleTransitionEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float FuzzyAmount = {read=GetFuzzyAmount, write=SetFuzzyAmount};
	__property float CircleSize = {read=GetCircleSize, write=SetCircleSize};
};


class PASCALIMPLEMENTATION TWiggleTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TWiggleTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWiggleTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TSaturateTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TSaturateTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSaturateTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TWaveTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TWaveTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWaveTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TFadeTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TFadeTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFadeTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


class PASCALIMPLEMENTATION TBlindTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetNumberOfBlinds();
	void __fastcall SetNumberOfBlinds(float AValue);
	
public:
	__fastcall virtual TBlindTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBlindTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float NumberOfBlinds = {read=GetNumberOfBlinds, write=SetNumberOfBlinds};
};


class PASCALIMPLEMENTATION TShapeTransitionEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	float __fastcall GetProgress();
	void __fastcall SetProgress(float AValue);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	float __fastcall GetRandomSeed();
	void __fastcall SetRandomSeed(float AValue);
	
public:
	__fastcall virtual TShapeTransitionEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TShapeTransitionEffect();
	
__published:
	__property float Progress = {read=GetProgress, write=SetProgress};
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
	__property float RandomSeed = {read=GetRandomSeed, write=SetRandomSeed};
};


class PASCALIMPLEMENTATION TPencilStrokeEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetbrushSize();
	void __fastcall SetbrushSize(float AValue);
	
public:
	__fastcall virtual TPencilStrokeEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPencilStrokeEffect();
	
__published:
	__property float brushSize = {read=GetbrushSize, write=SetbrushSize};
};


class PASCALIMPLEMENTATION TSharpenEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	
public:
	__fastcall virtual TSharpenEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSharpenEffect();
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
};


class PASCALIMPLEMENTATION TEmbossEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	float __fastcall GetWidth();
	void __fastcall SetWidth(float AValue);
	
public:
	__fastcall virtual TEmbossEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TEmbossEffect();
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
	__property float Width = {read=GetWidth, write=SetWidth};
};


class PASCALIMPLEMENTATION TSepiaEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetAmount();
	void __fastcall SetAmount(float AValue);
	
public:
	__fastcall virtual TSepiaEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSepiaEffect();
	
__published:
	__property float Amount = {read=GetAmount, write=SetAmount};
};


class PASCALIMPLEMENTATION TPaperSketchEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetbrushSize();
	void __fastcall SetbrushSize(float AValue);
	
public:
	__fastcall virtual TPaperSketchEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPaperSketchEffect();
	
__published:
	__property float brushSize = {read=GetbrushSize, write=SetbrushSize};
};


class PASCALIMPLEMENTATION TPixelateEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBlockCount();
	void __fastcall SetBlockCount(float AValue);
	
public:
	__fastcall virtual TPixelateEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPixelateEffect();
	
__published:
	__property float BlockCount = {read=GetBlockCount, write=SetBlockCount};
};


class PASCALIMPLEMENTATION TToonEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetLevels();
	void __fastcall SetLevels(float AValue);
	
public:
	__fastcall virtual TToonEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TToonEffect();
	
__published:
	__property float Levels = {read=GetLevels, write=SetLevels};
};


class PASCALIMPLEMENTATION TWaveEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetTime();
	void __fastcall SetTime(float AValue);
	float __fastcall GetWaveSize();
	void __fastcall SetWaveSize(float AValue);
	
public:
	__fastcall virtual TWaveEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWaveEffect();
	
__published:
	__property float Time = {read=GetTime, write=SetTime};
	__property float WaveSize = {read=GetWaveSize, write=SetWaveSize};
};


class PASCALIMPLEMENTATION TBandedSwirlEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetBands();
	void __fastcall SetBands(float AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TBandedSwirlEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBandedSwirlEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Bands = {read=GetBands, write=SetBands};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TSmoothMagnifyEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetInnerRadius();
	void __fastcall SetInnerRadius(float AValue);
	float __fastcall GetOuterRadius();
	void __fastcall SetOuterRadius(float AValue);
	float __fastcall GetMagnification();
	void __fastcall SetMagnification(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TSmoothMagnifyEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSmoothMagnifyEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float InnerRadius = {read=GetInnerRadius, write=SetInnerRadius};
	__property float OuterRadius = {read=GetOuterRadius, write=SetOuterRadius};
	__property float Magnification = {read=GetMagnification, write=SetMagnification};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TWrapEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetLeftStart();
	void __fastcall SetLeftStart(float AValue);
	float __fastcall GetLeftControl1();
	void __fastcall SetLeftControl1(float AValue);
	float __fastcall GetLeftControl2();
	void __fastcall SetLeftControl2(float AValue);
	float __fastcall GetLeftEnd();
	void __fastcall SetLeftEnd(float AValue);
	float __fastcall GetRightStart();
	void __fastcall SetRightStart(float AValue);
	float __fastcall GetRightControl1();
	void __fastcall SetRightControl1(float AValue);
	float __fastcall GetRightControl2();
	void __fastcall SetRightControl2(float AValue);
	float __fastcall GetRightEnd();
	void __fastcall SetRightEnd(float AValue);
	
public:
	__fastcall virtual TWrapEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWrapEffect();
	
__published:
	__property float LeftStart = {read=GetLeftStart, write=SetLeftStart};
	__property float LeftControl1 = {read=GetLeftControl1, write=SetLeftControl1};
	__property float LeftControl2 = {read=GetLeftControl2, write=SetLeftControl2};
	__property float LeftEnd = {read=GetLeftEnd, write=SetLeftEnd};
	__property float RightStart = {read=GetRightStart, write=SetRightStart};
	__property float RightControl1 = {read=GetRightControl1, write=SetRightControl1};
	__property float RightControl2 = {read=GetRightControl2, write=SetRightControl2};
	__property float RightEnd = {read=GetRightEnd, write=SetRightEnd};
};


class PASCALIMPLEMENTATION TSwirlEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetSpiralStrength();
	void __fastcall SetSpiralStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TSwirlEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSwirlEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float SpiralStrength = {read=GetSpiralStrength, write=SetSpiralStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TBandsEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBandDensity();
	void __fastcall SetBandDensity(float AValue);
	float __fastcall GetBandIntensity();
	void __fastcall SetBandIntensity(float AValue);
	
public:
	__fastcall virtual TBandsEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBandsEffect();
	
__published:
	__property float BandDensity = {read=GetBandDensity, write=SetBandDensity};
	__property float BandIntensity = {read=GetBandIntensity, write=SetBandIntensity};
};


class PASCALIMPLEMENTATION TMagnifyEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRadius();
	void __fastcall SetRadius(float AValue);
	float __fastcall GetMagnification();
	void __fastcall SetMagnification(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TMagnifyEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMagnifyEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Radius = {read=GetRadius, write=SetRadius};
	__property float Magnification = {read=GetMagnification, write=SetMagnification};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TPinchEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRadius();
	void __fastcall SetRadius(float AValue);
	float __fastcall GetStrength();
	void __fastcall SetStrength(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TPinchEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPinchEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Radius = {read=GetRadius, write=SetRadius};
	__property float Strength = {read=GetStrength, write=SetStrength};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TRippleEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetAmplitude();
	void __fastcall SetAmplitude(float AValue);
	float __fastcall GetFrequency();
	void __fastcall SetFrequency(float AValue);
	float __fastcall GetPhase();
	void __fastcall SetPhase(float AValue);
	float __fastcall GetAspectRatio();
	void __fastcall SetAspectRatio(float AValue);
	
public:
	__fastcall virtual TRippleEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRippleEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Amplitude = {read=GetAmplitude, write=SetAmplitude};
	__property float Frequency = {read=GetFrequency, write=SetFrequency};
	__property float Phase = {read=GetPhase, write=SetPhase};
	__property float AspectRatio = {read=GetAspectRatio, write=SetAspectRatio};
};


class PASCALIMPLEMENTATION TPerspectiveTransformEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetTopLeft();
	void __fastcall SetTopLeft(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetTopRight();
	void __fastcall SetTopRight(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetBottomRight();
	void __fastcall SetBottomRight(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetBottomLeft();
	void __fastcall SetBottomLeft(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TPerspectiveTransformEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPerspectiveTransformEffect();
	__property System::Types::TPointF TopLeft = {read=GetTopLeft, write=SetTopLeft};
	__property System::Types::TPointF TopRight = {read=GetTopRight, write=SetTopRight};
	__property System::Types::TPointF BottomRight = {read=GetBottomRight, write=SetBottomRight};
	__property System::Types::TPointF BottomLeft = {read=GetBottomLeft, write=SetBottomLeft};
};


class PASCALIMPLEMENTATION TCropEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetLeftTop();
	void __fastcall SetLeftTop(const System::Types::TPointF &AValue);
	System::Types::TPointF __fastcall GetRightBottom();
	void __fastcall SetRightBottom(const System::Types::TPointF &AValue);
	
public:
	__fastcall virtual TCropEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCropEffect();
	__property System::Types::TPointF LeftTop = {read=GetLeftTop, write=SetLeftTop};
	__property System::Types::TPointF RightBottom = {read=GetRightBottom, write=SetRightBottom};
};


class PASCALIMPLEMENTATION TAffineTransformEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetRotation();
	void __fastcall SetRotation(float AValue);
	float __fastcall GetScale();
	void __fastcall SetScale(float AValue);
	
public:
	__fastcall virtual TAffineTransformEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TAffineTransformEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float Rotation = {read=GetRotation, write=SetRotation};
	__property float Scale = {read=GetScale, write=SetScale};
};


class PASCALIMPLEMENTATION TTilerEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetVerticalTileCount();
	void __fastcall SetVerticalTileCount(float AValue);
	float __fastcall GetHorizontalTileCount();
	void __fastcall SetHorizontalTileCount(float AValue);
	float __fastcall GetHorizontalOffset();
	void __fastcall SetHorizontalOffset(float AValue);
	float __fastcall GetVerticalOffset();
	void __fastcall SetVerticalOffset(float AValue);
	
public:
	__fastcall virtual TTilerEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTilerEffect();
	
__published:
	__property float VerticalTileCount = {read=GetVerticalTileCount, write=SetVerticalTileCount};
	__property float HorizontalTileCount = {read=GetHorizontalTileCount, write=SetHorizontalTileCount};
	__property float HorizontalOffset = {read=GetHorizontalOffset, write=SetHorizontalOffset};
	__property float VerticalOffset = {read=GetVerticalOffset, write=SetVerticalOffset};
};


class PASCALIMPLEMENTATION TDirectionalBlurEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetAngle();
	void __fastcall SetAngle(float AValue);
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
public:
	__fastcall virtual TDirectionalBlurEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDirectionalBlurEffect();
	
__published:
	__property float Angle = {read=GetAngle, write=SetAngle};
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
};


class PASCALIMPLEMENTATION TRadialBlurEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Types::TPointF __fastcall GetCenter();
	void __fastcall SetCenter(const System::Types::TPointF &AValue);
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
public:
	__fastcall virtual TRadialBlurEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRadialBlurEffect();
	__property System::Types::TPointF Center = {read=GetCenter, write=SetCenter};
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
};


class PASCALIMPLEMENTATION TGaussianBlurEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
public:
	__fastcall virtual TGaussianBlurEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGaussianBlurEffect();
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
};


class PASCALIMPLEMENTATION TBoxBlurEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBlurAmount();
	void __fastcall SetBlurAmount(float AValue);
	
public:
	__fastcall virtual TBoxBlurEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBoxBlurEffect();
	
__published:
	__property float BlurAmount = {read=GetBlurAmount, write=SetBlurAmount};
};


class PASCALIMPLEMENTATION TMaskToAlphaEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
public:
	__fastcall virtual TMaskToAlphaEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMaskToAlphaEffect();
};


class PASCALIMPLEMENTATION TColorKeyAlphaEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColorKey();
	void __fastcall SetColorKey(System::Uitypes::TAlphaColor AValue);
	float __fastcall GetTolerance();
	void __fastcall SetTolerance(float AValue);
	
public:
	__fastcall virtual TColorKeyAlphaEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TColorKeyAlphaEffect();
	
__published:
	__property System::Uitypes::TAlphaColor ColorKey = {read=GetColorKey, write=SetColorKey, nodefault};
	__property float Tolerance = {read=GetTolerance, write=SetTolerance};
};


class PASCALIMPLEMENTATION TMonochromeEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
public:
	__fastcall virtual TMonochromeEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMonochromeEffect();
};


class PASCALIMPLEMENTATION TInvertEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
public:
	__fastcall virtual TInvertEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TInvertEffect();
};


class PASCALIMPLEMENTATION TGloomEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetGloomIntensity();
	void __fastcall SetGloomIntensity(float AValue);
	float __fastcall GetBaseIntensity();
	void __fastcall SetBaseIntensity(float AValue);
	float __fastcall GetGloomSaturation();
	void __fastcall SetGloomSaturation(float AValue);
	float __fastcall GetBaseSaturation();
	void __fastcall SetBaseSaturation(float AValue);
	
public:
	__fastcall virtual TGloomEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGloomEffect();
	
__published:
	__property float GloomIntensity = {read=GetGloomIntensity, write=SetGloomIntensity};
	__property float BaseIntensity = {read=GetBaseIntensity, write=SetBaseIntensity};
	__property float GloomSaturation = {read=GetGloomSaturation, write=SetGloomSaturation};
	__property float BaseSaturation = {read=GetBaseSaturation, write=SetBaseSaturation};
};


class PASCALIMPLEMENTATION THueAdjustEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetHue();
	void __fastcall SetHue(float AValue);
	
public:
	__fastcall virtual THueAdjustEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~THueAdjustEffect();
	
__published:
	__property float Hue = {read=GetHue, write=SetHue};
};


class PASCALIMPLEMENTATION TBloomEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBloomIntensity();
	void __fastcall SetBloomIntensity(float AValue);
	float __fastcall GetBaseIntensity();
	void __fastcall SetBaseIntensity(float AValue);
	float __fastcall GetBloomSaturation();
	void __fastcall SetBloomSaturation(float AValue);
	float __fastcall GetBaseSaturation();
	void __fastcall SetBaseSaturation(float AValue);
	
public:
	__fastcall virtual TBloomEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBloomEffect();
	
__published:
	__property float BloomIntensity = {read=GetBloomIntensity, write=SetBloomIntensity};
	__property float BaseIntensity = {read=GetBaseIntensity, write=SetBaseIntensity};
	__property float BloomSaturation = {read=GetBloomSaturation, write=SetBloomSaturation};
	__property float BaseSaturation = {read=GetBaseSaturation, write=SetBaseSaturation};
};


class PASCALIMPLEMENTATION TContrastEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	float __fastcall GetBrightness();
	void __fastcall SetBrightness(float AValue);
	float __fastcall GetContrast();
	void __fastcall SetContrast(float AValue);
	
public:
	__fastcall virtual TContrastEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TContrastEffect();
	
__published:
	__property float Brightness = {read=GetBrightness, write=SetBrightness};
	__property float Contrast = {read=GetContrast, write=SetContrast};
};


class PASCALIMPLEMENTATION TFillEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(System::Uitypes::TAlphaColor AValue);
	
public:
	__fastcall virtual TFillEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFillEffect();
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
};


class PASCALIMPLEMENTATION TFillRGBEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(System::Uitypes::TAlphaColor AValue);
	
public:
	__fastcall virtual TFillRGBEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFillRGBEffect();
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
};


class PASCALIMPLEMENTATION TNormalBlendEffect : public TImageFXEffect
{
	typedef TImageFXEffect inherited;
	
private:
	Fmx::Graphics::TBitmap* FTarget;
	void __fastcall TargetChanged(System::TObject* Sender);
	void __fastcall SetTarget(Fmx::Graphics::TBitmap* const AValue);
	
public:
	__fastcall virtual TNormalBlendEffect(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TNormalBlendEffect();
	
__published:
	__property Fmx::Graphics::TBitmap* Target = {read=FTarget, write=SetTarget};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Effects */
}	/* namespace Filter */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FILTER_EFFECTS)
using namespace Fmx::Filter::Effects;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FILTER)
using namespace Fmx::Filter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Filter_EffectsHPP
