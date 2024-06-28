// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFilters.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeefiltersHPP
#define Vcltee_TeefiltersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teefilters
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TResizeFilter;
class DELPHICLASS TCropFilter;
class DELPHICLASS TInvertFilter;
class DELPHICLASS TGrayScaleFilter;
class DELPHICLASS TFlipFilter;
class DELPHICLASS TReverseFilter;
class DELPHICLASS TAmountFilter;
class DELPHICLASS TMosaicFilter;
class DELPHICLASS TBrightnessFilter;
class DELPHICLASS TContrastFilter;
class DELPHICLASS TColorFilter;
class DELPHICLASS TColorReplaceFilter;
class DELPHICLASS THueLumSatFilter;
class DELPHICLASS TSharpenFilter;
class DELPHICLASS TEmbossFilter;
class DELPHICLASS TSoftenFilter;
class DELPHICLASS TGammaCorrectionFilter;
class DELPHICLASS TRotateFilter;
class DELPHICLASS TMirrorFilter;
class DELPHICLASS TTileFilter;
class DELPHICLASS TBevelFilter;
class DELPHICLASS TEqualizeFilter;
class DELPHICLASS TZoomFilter;
class DELPHICLASS TSobelFilter;
class DELPHICLASS TSepiaFilter;
class DELPHICLASS TImageFiltered;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TResizeFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FWidth;
	int FHeight;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int Width = {read=FWidth, write=FWidth, default=0};
	__property int Height = {read=FHeight, write=FHeight, default=0};
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TResizeFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TResizeFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TCropFilter : public TResizeFilter
{
	typedef TResizeFilter inherited;
	
private:
	int FLeft;
	bool FSmooth;
	int FTop;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int Left = {read=FLeft, write=FLeft, default=0};
	__property bool Smooth = {read=FSmooth, write=FSmooth, default=0};
	__property int Top = {read=FTop, write=FTop, default=0};
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TCropFilter(System::Classes::TCollection* Collection) : TResizeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TCropFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TInvertFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TInvertFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TInvertFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


enum DECLSPEC_DENUM TGrayMethod : unsigned char { gmSimple, gmEye, gmEye2, gmLight };

class PASCALIMPLEMENTATION TGrayScaleFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	TGrayMethod FMethod;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property TGrayMethod Method = {read=FMethod, write=FMethod, default=0};
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TGrayScaleFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TGrayScaleFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TFlipFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TFlipFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TFlipFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TReverseFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TReverseFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TReverseFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TAmountFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FAmount;
	bool FPercent;
	Vcl::Stdctrls::TScrollBar* FScrollBar;
	bool IOnlyPositive;
	void __fastcall ResetScroll(System::TObject* Sender);
	int __fastcall ScrollMin();
	int __fastcall ScrollMax();
	
public:
	__fastcall virtual TAmountFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	
__published:
	__property bool Percent = {read=FPercent, write=FPercent, default=1};
	__property int Amount = {read=FAmount, write=FAmount, default=5};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TAmountFilter() { }
	
};


class PASCALIMPLEMENTATION TMosaicFilter : public TAmountFilter
{
	typedef TAmountFilter inherited;
	
public:
	__fastcall virtual TMosaicFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property Percent = {default=0};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TMosaicFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TBrightnessFilter : public TAmountFilter
{
	typedef TAmountFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TAmountFilter.Create */ inline __fastcall virtual TBrightnessFilter(System::Classes::TCollection* Collection) : TAmountFilter(Collection) { }
	
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TBrightnessFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TContrastFilter : public TAmountFilter
{
	typedef TAmountFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TAmountFilter.Create */ inline __fastcall virtual TContrastFilter(System::Classes::TCollection* Collection) : TAmountFilter(Collection) { }
	
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TContrastFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TColorFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FBlue;
	int FGreen;
	int FRed;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int Red = {read=FRed, write=FRed, default=0};
	__property int Green = {read=FGreen, write=FGreen, default=0};
	__property int Blue = {read=FBlue, write=FBlue, default=0};
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TColorFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TColorFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


enum DECLSPEC_DENUM TColorMethod : unsigned char { cmHue, cmLum, cmSat };

class PASCALIMPLEMENTATION TColorReplaceFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	System::Byte FTo;
	System::Byte FFrom;
	TColorMethod FMethod;
	System::Uitypes::TColor FColor;
	
public:
	__fastcall virtual TColorReplaceFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=FColor, default=16777215};
	__property System::Byte FromValue = {read=FFrom, write=FFrom, default=0};
	__property TColorMethod Method = {read=FMethod, write=FMethod, default=0};
	__property System::Byte ToValue = {read=FTo, write=FTo, default=0};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TColorReplaceFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION THueLumSatFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FHue;
	int FLum;
	int FSat;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int Hue = {read=FHue, write=FHue, default=0};
	__property int Luminance = {read=FLum, write=FLum, default=0};
	__property int Saturation = {read=FSat, write=FSat, default=0};
public:
	/* TTeeFilter.Create */ inline __fastcall virtual THueLumSatFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~THueLumSatFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TSharpenFilter : public Vcltee::Tecanvas::TConvolveFilter
{
	typedef Vcltee::Tecanvas::TConvolveFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TSharpenFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TConvolveFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TSharpenFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TEmbossFilter : public Vcltee::Tecanvas::TConvolveFilter
{
	typedef Vcltee::Tecanvas::TConvolveFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TEmbossFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TConvolveFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TEmbossFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TSoftenFilter : public Vcltee::Tecanvas::TConvolveFilter
{
	typedef Vcltee::Tecanvas::TConvolveFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TSoftenFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TConvolveFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TSoftenFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TGammaCorrectionFilter : public TAmountFilter
{
	typedef TAmountFilter inherited;
	
public:
	__fastcall virtual TGammaCorrectionFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property Amount = {default=70};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TGammaCorrectionFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TRotateFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	double FAngle;
	bool FAutoSize;
	System::Uitypes::TColor FBackColor;
	void __fastcall SetAngle(const double Value);
	
public:
	__fastcall virtual TRotateFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property double Angle = {read=FAngle, write=SetAngle};
	__property bool AutoSize = {read=FAutoSize, write=FAutoSize, default=1};
	__property System::Uitypes::TColor BackColor = {read=FBackColor, write=FBackColor, default=16777215};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TRotateFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


enum DECLSPEC_DENUM TMirrorDirection : unsigned char { mdDown, mdUp, mdRight, mdLeft };

class PASCALIMPLEMENTATION TMirrorFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	TMirrorDirection FDirection;
	
public:
	__fastcall virtual TMirrorFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property TMirrorDirection Direction = {read=FDirection, write=FDirection, default=0};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TMirrorFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TTileFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FNumCols;
	int FNumRows;
	
public:
	__fastcall virtual TTileFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int NumCols = {read=FNumCols, write=FNumCols, default=3};
	__property int NumRows = {read=FNumRows, write=FNumRows, default=3};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TTileFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TBevelFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	int FBright;
	int FSize;
	
public:
	__fastcall virtual TBevelFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property int Bright = {read=FBright, write=FBright, default=64};
	__property int Size = {read=FSize, write=FSize, default=15};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TBevelFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TEqualizeFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TEqualizeFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TEqualizeFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TZoomFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
private:
	double FPercent;
	bool FSmooth;
	
public:
	__fastcall virtual TZoomFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(Vcltee::Tecanvas::_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property double Percent = {read=FPercent, write=FPercent};
	__property bool Smooth = {read=FSmooth, write=FSmooth, default=0};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TZoomFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TSobelFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TSobelFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TSobelFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TSepiaFilter : public Vcltee::Tecanvas::TTeeFilter
{
	typedef Vcltee::Tecanvas::TTeeFilter inherited;
	
public:
	virtual void __fastcall Apply(Vcl::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TSepiaFilter(System::Classes::TCollection* Collection) : Vcltee::Tecanvas::TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TSepiaFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Vcl::Graphics::TBitmap* const Bitmap){ Vcltee::Tecanvas::TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TImageFiltered : public Vcl::Extctrls::TImage
{
	typedef Vcl::Extctrls::TImage inherited;
	
private:
	Vcltee::Tecanvas::TFilterItems* FFilters;
	bool IAssigning;
	Vcl::Graphics::TBitmap* IFilteredPicture;
	Vcl::Graphics::TCanvas* ICanvas;
	System::Classes::TNotifyEvent InheritedChanged;
	void __fastcall DoPictureChanged(System::TObject* Sender);
	void __fastcall FilterChanged(System::TObject* Sender);
	bool __fastcall FiltersStored();
	void __fastcall ReadFilters(System::Classes::TReader* Reader);
	void __fastcall SetFilters(Vcltee::Tecanvas::TFilterItems* const Value);
	void __fastcall WriteFilters(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall Paint();
	
public:
	__fastcall virtual TImageFiltered(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TImageFiltered();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	Vcl::Graphics::TBitmap* __fastcall Filtered();
	
__published:
	__property Vcltee::Tecanvas::TFilterItems* Filters = {read=FFilters, write=SetFilters, stored=false};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Classes::TStringList* TeeFilterClasses;
extern DELPHI_PACKAGE void __fastcall TeeRegisterFilters(Vcltee::Tecanvas::TFilterClass const *FilterList, const int FilterList_High);
extern DELPHI_PACKAGE void __fastcall TeeUnRegisterFilters(Vcltee::Tecanvas::TFilterClass const *FilterList, const int FilterList_High);
extern DELPHI_PACKAGE void __fastcall ColorToHLS(System::Uitypes::TColor Color, /* out */ System::Word &Hue, /* out */ System::Word &Luminance, /* out */ System::Word &Saturation);
extern DELPHI_PACKAGE void __fastcall RGBToHLS(const Vcltee::Tecanvas::TRGBA Color, /* out */ System::Word &Hue, /* out */ System::Word &Luminance, /* out */ System::Word &Saturation)/* overload */;
extern DELPHI_PACKAGE void __fastcall RGBToHLS(const Vcltee::Tecanvas::TRGB Color, /* out */ System::Word &Hue, /* out */ System::Word &Luminance, /* out */ System::Word &Saturation)/* overload */;
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall HLSToColor(System::Word Hue, System::Word Luminance, System::Word Saturation);
extern DELPHI_PACKAGE void __fastcall HLSToRGB(System::Word Hue, System::Word Luminance, System::Word Saturation, /* out */ Vcltee::Tecanvas::TRGBA &rgb)/* overload */;
extern DELPHI_PACKAGE void __fastcall HLSToRGB(System::Word Hue, System::Word Luminance, System::Word Saturation, /* out */ Vcltee::Tecanvas::TRGB &rgb)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeGrayScale(Vcl::Graphics::TBitmap* const ABitmap, bool Inverted, int AMethod);
}	/* namespace Teefilters */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFILTERS)
using namespace Vcltee::Teefilters;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeefiltersHPP
