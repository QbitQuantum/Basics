// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Canvas.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_CanvasHPP
#define Fmxtee_CanvasHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.TextLayout.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Canvas
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFilterRegion;
struct TFloatRect;
struct TRGB;
struct TRGBA;
__interface DELPHIINTERFACE IFormCreator;
typedef System::DelphiInterface<IFormCreator> _di_IFormCreator;
class DELPHICLASS TTeeFilter;
class DELPHICLASS TFilterItems;
class DELPHICLASS TConvolveFilter;
class DELPHICLASS TBlurFilter;
class DELPHICLASS TPicture;
class DELPHICLASS TTeePicture;
class DELPHICLASS TTeeBasePath;
class DELPHICLASS TTeeCorner;
class DELPHICLASS TTeeCorners;
class DELPHICLASS TTeePen;
class DELPHICLASS TTeeHiddenPen;
class DELPHICLASS TDottedGrayPen;
class DELPHICLASS TDarkGrayPen;
class DELPHICLASS TWhitePen;
class DELPHICLASS TTeeBrush;
struct TBrushHelper /* Helper for class 'Fmx::Graphics::TBrush*' */;
class DELPHICLASS TView3DOptions;
class DELPHICLASS TTeeBlend;
class DELPHICLASS TTeeShadow;
class DELPHICLASS TTeeEmboss;
class DELPHICLASS TTeeGradientColor;
class DELPHICLASS TTeeGradientColors;
class DELPHICLASS TCustomTeeGradient;
class DELPHICLASS TSubGradient;
class DELPHICLASS TTeeGradient;
class DELPHICLASS TTeeFont;
class DELPHICLASS TTeeCachedObject;
class DELPHICLASS TTeeCanvas;
struct TFloatPoint;
class DELPHICLASS TFloatXYZ;
struct TPoint3D;
struct TTriangleIndexes;
struct TSurfaceVertex;
class DELPHICLASS TPointBlock;
class DELPHICLASS TPointXYFloat;
class DELPHICLASS TPointXYZFloat;
class DELPHICLASS TVisualBlock;
class DELPHICLASS TTeeTransform;
class DELPHICLASS TCanvas3D;
class DELPHICLASS TTeeCanvas3D;
class DELPHICLASS TTeeNeutralCanvas;
__interface DELPHIINTERFACE ICanvasHyperlinks;
typedef System::DelphiInterface<ICanvasHyperlinks> _di_ICanvasHyperlinks;
__interface DELPHIINTERFACE ICanvasToolTips;
typedef System::DelphiInterface<ICanvasToolTips> _di_ICanvasToolTips;
//-- type declarations -------------------------------------------------------
typedef System::Types::TPointF TPoint;

typedef System::Types::TPointF TPointFloat;

typedef System::Types::TRectF TRect;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFilterRegion : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FHeight;
	int FLeft;
	int FTop;
	int FWidth;
	System::Types::TRectF __fastcall GetRectangle();
	void __fastcall SetRectangle(const System::Types::TRectF &Rect);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Types::TRectF Rectangle = {read=GetRectangle, write=SetRectangle};
	
__published:
	__property int Height = {read=FHeight, write=FHeight, default=0};
	__property int Left = {read=FLeft, write=FLeft, default=0};
	__property int Top = {read=FTop, write=FTop, default=0};
	__property int Width = {read=FWidth, write=FWidth, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFilterRegion() { }
	
public:
	/* TObject.Create */ inline __fastcall TFilterRegion() : System::Classes::TPersistent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#pragma pack(push,1)
struct DECLSPEC_DRECORD TFloatRect
{
public:
	double Left;
	double Top;
	double Right;
	double Bottom;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TRGB
{
public:
	System::Byte Blue;
	System::Byte Green;
	System::Byte Red;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TRGBA
{
public:
	System::Byte Blue;
	System::Byte Green;
	System::Byte Red;
	System::Byte Alpha;
};
#pragma pack(pop)


typedef System::StaticArray<TRGB, 1> TRGBs;

typedef TRGBs *PRGBs;

typedef System::StaticArray<TRGBA, 1> TRGBAs;

typedef TRGBAs *PRGBAs;

typedef System::DynamicArray<PRGBAs> TRGBAArray;

__interface IFormCreator  : public System::IInterface 
{
	virtual Fmx::Stdctrls::TCheckBox* __fastcall AddCheckBox(const System::UnicodeString PropName, const System::UnicodeString ACaption, System::Classes::TNotifyEvent OnChange = 0x0) = 0 ;
	virtual Fmx::Stdctrls::TButton* __fastcall AddColor(const System::UnicodeString PropName, const System::UnicodeString ACaption) = 0 ;
	virtual Fmx::Listbox::TComboBox* __fastcall AddCombo(const System::UnicodeString PropName) = 0 ;
	virtual Fmx::Edit::TEdit* __fastcall AddInteger(const System::UnicodeString PropName, const System::UnicodeString ACaption, int AMin, int AMax) = 0 ;
	virtual Fmx::Stdctrls::TScrollBar* __fastcall AddScroll(const System::UnicodeString PropName, int AMin, int AMax) = 0 ;
};

typedef System::Types::TRect TRectI;

class PASCALIMPLEMENTATION TTeeFilter : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	bool FEnabled;
	TFilterRegion* FRegion;
	TFilterRegion* __fastcall GetRegion();
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetRegion(TFilterRegion* const Value);
	
protected:
	bool AllowRegion;
	System::Classes::TNotifyEvent FChanged;
	bool ReuseLines;
	void __fastcall CalcLines(Fmx::Graphics::TBitmap* const Bitmap);
	bool __fastcall Empty();
	
public:
	bool RGBA;
	TRGBAArray LinesRGBA;
	__fastcall virtual TTeeFilter(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTeeFilter();
	__classmethod void __fastcall ApplyTo(Fmx::Graphics::TBitmap* const Bitmap)/* overload */;
	void __fastcall Apply(Fmx::Graphics::TBitmap* const Bitmap)/* overload */;
	virtual void __fastcall Apply(Fmx::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CreateEditor(_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	DYNAMIC void __fastcall PrepareForGallery();
	__classmethod virtual System::UnicodeString __fastcall Description();
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property TFilterRegion* Region = {read=GetRegion, write=SetRegion};
};


#ifndef _WIN64
typedef System::TMetaClass* TFilterClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TFilterClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TFilterItems : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTeeFilter* operator[](int Index) { return this->Item[Index]; }
	
private:
	System::Classes::TNotifyEvent FOnChange;
	TTeeFilter* __fastcall Get(int Index);
	void __fastcall Put(int Index, TTeeFilter* const Value);
	
protected:
	virtual void __fastcall Notify(System::Classes::TCollectionItem* Item, System::Generics::Collections::TCollectionNotification Action);
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	bool Changed;
	HIDESBASE TTeeFilter* __fastcall Add(TFilterClass Filter);
	void __fastcall ApplyTo(Fmx::Graphics::TBitmap* const ABitmap);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property TTeeFilter* Item[int Index] = {read=Get, write=Put/*, default*/};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TOwnedCollection.Create */ inline __fastcall TFilterItems(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFilterItems() { }
	
};


class PASCALIMPLEMENTATION TConvolveFilter : public TTeeFilter
{
	typedef TTeeFilter inherited;
	
protected:
	Fmx::Graphics::TBitmap* BufferBitmap;
	TTeeFilter* BufferFilter;
	bool KeepBuffer;
	System::Types::TRectF Rect;
	void __fastcall CreateBuffer(int AWidth, int AHeight);
	void __fastcall FreeBuffer();
	
public:
	System::StaticArray<System::StaticArray<float, 3>, 3> Weights;
	virtual void __fastcall Apply(Fmx::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
public:
	/* TTeeFilter.Create */ inline __fastcall virtual TConvolveFilter(System::Classes::TCollection* Collection) : TTeeFilter(Collection) { }
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TConvolveFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Fmx::Graphics::TBitmap* const Bitmap){ TTeeFilter::Apply(Bitmap); }
	
};


class PASCALIMPLEMENTATION TBlurFilter : public TConvolveFilter
{
	typedef TConvolveFilter inherited;
	
private:
	int FAmount;
	int FSteps;
	
public:
	__fastcall virtual TBlurFilter(System::Classes::TCollection* Collection);
	virtual void __fastcall Apply(Fmx::Graphics::TBitmap* const Bitmap, const System::Types::TRect &R)/* overload */;
	__classmethod virtual System::UnicodeString __fastcall Description();
	virtual void __fastcall CreateEditor(_di_IFormCreator Creator, System::Classes::TNotifyEvent AChanged);
	
__published:
	__property int Amount = {read=FAmount, write=FAmount, default=1};
	__property int Steps = {read=FSteps, write=FSteps, default=1};
public:
	/* TTeeFilter.Destroy */ inline __fastcall virtual ~TBlurFilter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Apply(Fmx::Graphics::TBitmap* const Bitmap){ TTeeFilter::Apply(Bitmap); }
	
};


typedef System::Uitypes::TAlphaColor TColor;

class PASCALIMPLEMENTATION TPicture : public Fmx::Graphics::TBitmap
{
	typedef Fmx::Graphics::TBitmap inherited;
	
private:
	Fmx::Graphics::TBitmap* __fastcall GetBitmap();
	void __fastcall SetBitmap(Fmx::Graphics::TBitmap* const Value);
	
public:
	__fastcall TPicture();
	__property Fmx::Graphics::TBitmap* Graphic = {read=GetBitmap, write=SetBitmap};
	__property Fmx::Graphics::TBitmap* Bitmap = {read=GetBitmap, write=SetBitmap};
public:
	/* TBitmap.CreateFromStream */ inline __fastcall virtual TPicture(System::Classes::TStream* const AStream) : Fmx::Graphics::TBitmap(AStream) { }
	/* TBitmap.CreateFromFile */ inline __fastcall virtual TPicture(const System::UnicodeString AFileName) : Fmx::Graphics::TBitmap(AFileName) { }
	/* TBitmap.CreateFromBitmapAndMask */ inline __fastcall TPicture(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Mask) : Fmx::Graphics::TBitmap(Bitmap, Mask) { }
	/* TBitmap.Destroy */ inline __fastcall virtual ~TPicture() { }
	
};


typedef Fmx::Graphics::TBitmap TGraphic;

enum DECLSPEC_DENUM TPenStyle : unsigned char { psSolid, psDash, psDot, psDashDot, psDashDotDot, psClear, psInsideFrame, psUserStyle, psAlternate };

enum DECLSPEC_DENUM TColorDialogOption : unsigned char { cdExtended };

typedef System::Set<TColorDialogOption, TColorDialogOption::cdExtended, TColorDialogOption::cdExtended> TColorDialogOptions;

class PASCALIMPLEMENTATION TTeePicture : public TPicture
{
	typedef TPicture inherited;
	
private:
	TFilterItems* FFilters;
	Fmx::Graphics::TBitmap* IBitmap;
	void __fastcall DoReadFilters(System::Classes::TReader* Reader);
	void __fastcall DoWriteFilters(System::Classes::TWriter* Writer);
	bool __fastcall FiltersStored();
	TFilterItems* __fastcall GetFilters();
	void __fastcall SetFilters(TFilterItems* const Value);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual ~TTeePicture();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__classmethod void __fastcall AssignGraphic(Fmx::Graphics::TBitmap* const ABitmap, Fmx::Graphics::TBitmap* const AGraphic);
	Fmx::Graphics::TBitmap* __fastcall Filtered();
	void __fastcall Repaint();
	bool __fastcall Valid();
	__classmethod void __fastcall ReadFilters(System::Classes::TReader* const Reader, TFilterItems* const Filters);
	__classmethod void __fastcall WriteFilters(System::Classes::TWriter* const Writer, TFilterItems* const Filters);
	
__published:
	__property TFilterItems* Filters = {read=GetFilters, write=SetFilters, stored=false};
public:
	/* TPicture.Create */ inline __fastcall TTeePicture() : TPicture() { }
	
public:
	/* TBitmap.CreateFromStream */ inline __fastcall virtual TTeePicture(System::Classes::TStream* const AStream) : TPicture(AStream) { }
	/* TBitmap.CreateFromFile */ inline __fastcall virtual TTeePicture(const System::UnicodeString AFileName) : TPicture(AFileName) { }
	/* TBitmap.CreateFromBitmapAndMask */ inline __fastcall TTeePicture(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Mask) : TPicture(Bitmap, Mask) { }
	
};


typedef System::DynamicArray<System::Types::TPointF> TPointFloatArray;

typedef System::DynamicArray<System::Byte> TPathPointTypes;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeBasePath : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall ArcTo(const float X, const float Y, const float Width, const float Height, const float StartAngle, const float SweepAngle) = 0 ;
	virtual void __fastcall Close() = 0 ;
	virtual void __fastcall Curve(const System::Types::TPointF *Points, const int Points_High, const float Tension, bool Closed) = 0 ;
	virtual void __fastcall Draw(TTeeCanvas* const ACanvas) = 0 ;
	virtual void __fastcall GetPoints(/* out */ TPathPointTypes &Types, /* out */ TPointFloatArray &Points, /* out */ System::Types::TRectF &Bounds) = 0 ;
	virtual void __fastcall LineTo(const float X, const float Y) = 0 /* overload */;
	void __fastcall LineTo(const System::Types::TPointF &P)/* overload */;
	virtual void __fastcall MoveTo(const float X, const float Y) = 0 /* overload */;
	void __fastcall MoveTo(const System::Types::TPointF &P)/* overload */;
	virtual void __fastcall TextOut(const float X, const float Y, const System::UnicodeString Text) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TTeeBasePath() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeBasePath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TTeeCornerStyle : unsigned char { cosRound, cosBevel, cosNone };

class PASCALIMPLEMENTATION TTeeCorner : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TTeeCornerStyle FStyle;
	System::Classes::TNotifyEvent IChanged;
	void __fastcall SetStyle(const TTeeCornerStyle Value);
	
public:
	__fastcall TTeeCorner(const System::Classes::TNotifyEvent Changed);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TTeeCornerStyle Style = {read=FStyle, write=SetStyle, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTeeCorner() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeCorners : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TTeeCorner* FLeftBottom;
	TTeeCorner* FLeftTop;
	TTeeCorner* FRightBottom;
	TTeeCorner* FRightTop;
	void __fastcall SetLeftBottom(TTeeCorner* const Value);
	void __fastcall SetLeftTop(TTeeCorner* const Value);
	void __fastcall SetRightBottom(TTeeCorner* const Value);
	void __fastcall SetRightTop(TTeeCorner* const Value);
	
protected:
	TTeeBasePath* __fastcall GetPath(TTeeCanvas* const ACanvas, const System::Types::TRectF &R, int X, int Y);
	
public:
	__fastcall TTeeCorners(const System::Classes::TNotifyEvent Changed);
	__fastcall virtual ~TTeeCorners();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TTeeCorner* LeftBottom = {read=FLeftBottom, write=SetLeftBottom};
	__property TTeeCorner* LeftTop = {read=FLeftTop, write=SetLeftTop};
	__property TTeeCorner* RightBottom = {read=FRightBottom, write=SetRightBottom};
	__property TTeeCorner* RightTop = {read=FRightTop, write=SetRightTop};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef float TCoordinate;

enum DECLSPEC_DENUM TPenMode : unsigned char { pmBlack, pmWhite, pmNop, pmNot, pmCopy, pmNotCopy, pmMergePenNot, pmMaskPenNot, pmMergeNotPen, pmMaskNotPen, pmMerge, pmNotMerge, pmMask, pmNotMask, pmXor, pmNotXor };

enum DECLSPEC_DENUM TPenEndStyle : unsigned char { esRound, esSquare, esFlat };

enum DECLSPEC_DENUM TPenJoinStyle : unsigned char { jsRound, jsBevel, jsMitter };

class PASCALIMPLEMENTATION TTeePen : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TPenMode FMode;
	TPenStyle FStyle;
	float FWidth;
	System::Classes::TNotifyEvent FOnChange;
	TPenEndStyle FEndStyle;
	TPenJoinStyle FJoinStyle;
	bool FSmallDots;
	int FSmallSpace;
	bool FVisible;
	bool __fastcall IsEndStored();
	bool __fastcall IsJoinStored();
	bool __fastcall IsVisibleStored();
	bool __fastcall IsWidthStored();
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetStyle(const TPenStyle Value);
	void __fastcall SetWidth(const float Value);
	void __fastcall SetEndStyle(const TPenEndStyle Value);
	void __fastcall SetJoinStyle(const TPenJoinStyle Value);
	void __fastcall SetSmallDots(const bool Value);
	void __fastcall SetSmallSpace(const int Value);
	void __fastcall SetVisible(const bool Value);
	
protected:
	TPenEndStyle DefaultEnd;
	TPenJoinStyle DefaultJoin;
	bool DefaultVisible;
	float DefaultWidth;
	TTeeBrush* FFill;
	void __fastcall Changed();
	TTeeBrush* __fastcall GetPenBrush();
	void __fastcall InitColor(const System::Uitypes::TAlphaColor AColor);
	void __fastcall InitEndStyle(const TPenEndStyle Value);
	void __fastcall SetPenBrush(TTeeBrush* const Value);
	
public:
	__fastcall TTeePen(const System::Classes::TNotifyEvent OnChangeEvent);
	__fastcall virtual ~TTeePen();
	bool __fastcall IsGradientVisible();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall HalfWidth();
	void __fastcall Hide();
	void __fastcall Show();
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, default=-16777216};
	__property TPenMode Mode = {read=FMode, write=FMode, default=4};
	__property TPenStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property float Width = {read=FWidth, write=SetWidth, stored=IsWidthStored};
	__property TPenEndStyle EndStyle = {read=FEndStyle, write=SetEndStyle, stored=IsEndStored, nodefault};
	__property TTeeBrush* Fill = {read=GetPenBrush, write=SetPenBrush};
	__property TPenJoinStyle JoinStyle = {read=FJoinStyle, write=SetJoinStyle, stored=IsJoinStored, nodefault};
	__property bool SmallDots = {read=FSmallDots, write=SetSmallDots, default=0};
	__property int SmallSpace = {read=FSmallSpace, write=SetSmallSpace, default=0};
	__property bool Visible = {read=FVisible, write=SetVisible, stored=IsVisibleStored, nodefault};
};


class PASCALIMPLEMENTATION TTeeHiddenPen : public TTeePen
{
	typedef TTeePen inherited;
	
public:
	__fastcall TTeeHiddenPen(const System::Classes::TNotifyEvent OnChangeEvent);
	
__published:
	__property Visible = {default=0};
public:
	/* TTeePen.Destroy */ inline __fastcall virtual ~TTeeHiddenPen() { }
	
};


class PASCALIMPLEMENTATION TDottedGrayPen : public TTeePen
{
	typedef TTeePen inherited;
	
public:
	__fastcall TDottedGrayPen(const System::Classes::TNotifyEvent OnChangeEvent);
	
__published:
	__property Color = {default=-8355712};
	__property Style = {default=2};
public:
	/* TTeePen.Destroy */ inline __fastcall virtual ~TDottedGrayPen() { }
	
};


class PASCALIMPLEMENTATION TDarkGrayPen : public TTeePen
{
	typedef TTeePen inherited;
	
public:
	__fastcall TDarkGrayPen(const System::Classes::TNotifyEvent OnChangeEvent);
	
__published:
	__property Color = {default=-5658199};
public:
	/* TTeePen.Destroy */ inline __fastcall virtual ~TDarkGrayPen() { }
	
};


class PASCALIMPLEMENTATION TWhitePen : public TTeePen
{
	typedef TTeePen inherited;
	
public:
	__fastcall TWhitePen(const System::Classes::TNotifyEvent OnChangeEvent);
	
__published:
	__property Color = {default=-1};
public:
	/* TTeePen.Destroy */ inline __fastcall virtual ~TWhitePen() { }
	
};


class PASCALIMPLEMENTATION TTeeBrush : public Fmx::Graphics::TBrush
{
	typedef Fmx::Graphics::TBrush inherited;
	
private:
	System::Uitypes::TAlphaColor FBackColor;
	TTeeGradient* FGradient;
	TTeePicture* FImage;
	System::Uitypes::TAlphaColor DefaultColor;
	HIDESBASE bool __fastcall IsColorStored();
	TTeeGradient* __fastcall GetGradient();
	TTeePicture* __fastcall GetImage();
	void __fastcall SetBackColor(const System::Uitypes::TAlphaColor Value);
	HIDESBASE void __fastcall SetGradient(TTeeGradient* const Value);
	void __fastcall SetImage(TTeePicture* const Value);
	Fmx::Graphics::TBrushKind __fastcall GetKind();
	System::Classes::TNotifyEvent __fastcall GetOnChanged();
	HIDESBASE void __fastcall SetKind(const Fmx::Graphics::TBrushKind Value);
	void __fastcall SetOnChanged(const System::Classes::TNotifyEvent Value);
	
protected:
	void __fastcall Changed();
	bool __fastcall HasImage();
	bool __fastcall HasGradient();
	void __fastcall InitColor(const System::Uitypes::TAlphaColor Value);
	
public:
	__fastcall virtual TTeeBrush(const System::Classes::TNotifyEvent OnChangeEvent);
	__fastcall virtual ~TTeeBrush();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Clear();
	__property Fmx::Graphics::TBrushKind Style = {read=GetKind, write=SetKind, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=GetOnChanged, write=SetOnChanged};
	
__published:
	__property System::Uitypes::TAlphaColor BackColor = {read=FBackColor, write=SetBackColor, default=0};
	__property Color = {stored=IsColorStored};
	__property TTeeGradient* Gradient = {read=GetGradient, write=SetGradient};
	__property TTeePicture* Image = {read=GetImage, write=SetImage};
};


typedef TTeeBrush TChartBrush;

enum DECLSPEC_DENUM TCanvasZoomText : unsigned char { ztManual, ztNo, ztAuto };

typedef void __fastcall (__closure *TTeeView3DScrolled)(bool IsHoriz);

typedef void __fastcall (__closure *TTeeView3DChangedZoom)(int NewZoom);

class PASCALIMPLEMENTATION TView3DOptions : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	double FElevation;
	int FFontZoom;
	double FHorizOffset;
	bool FOrthogonal;
	int FOrthoAngle;
	int FPerspective;
	double FRotation;
	double FTilt;
	double FVertOffset;
	double FZOffset;
	double FZoom;
	TCanvasZoomText FZoomText;
	TTeeView3DScrolled FOnScrolled;
	TTeeView3DChangedZoom FOnChangedZoom;
	Fmx::Controls::TControl* FParent;
	int __fastcall GetElevation();
	int __fastcall GetHorizOffset();
	int __fastcall GetRotation();
	int __fastcall GetTilt();
	int __fastcall GetVertOffset();
	int __fastcall GetZoom();
	void __fastcall SetBooleanProperty(bool &Variable, bool Value);
	void __fastcall SetElevationInteger(const int Value);
	void __fastcall SetElevation(const double Value);
	void __fastcall SetFontZoom(int Value);
	void __fastcall SetHorizInteger(const int Value);
	void __fastcall SetHorizOffset(const double Value);
	void __fastcall SetIntegerProperty(int &Variable, int Value);
	void __fastcall SetOrthoAngle(int Value);
	void __fastcall SetOrthogonal(bool Value);
	void __fastcall SetPerspective(int Value);
	void __fastcall SetRotationInteger(const int Value);
	void __fastcall SetRotation(const double Value)/* overload */;
	void __fastcall SetTilt(const double Value);
	void __fastcall SetTiltInteger(int Value);
	void __fastcall SetVertInteger(const int Value);
	void __fastcall SetVertOffset(const double Value);
	void __fastcall SetZOffset(const double Value);
	void __fastcall SetZoomInteger(const int Value);
	void __fastcall SetZoom(const double Value);
	void __fastcall SetZoomText(const TCanvasZoomText Value);
	
protected:
	System::Classes::TNotifyEvent FOnInvalidate;
	double __fastcall CalcOrthoRatio();
	
public:
	__fastcall TView3DOptions(Fmx::Controls::TControl* const AParent);
	bool __fastcall BackFaced();
	void __fastcall Repaint();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property Fmx::Controls::TControl* Parent = {read=FParent, write=FParent};
	__property double ElevationFloat = {read=FElevation, write=SetElevation};
	__property double HorizOffsetFloat = {read=FHorizOffset, write=SetHorizOffset};
	__property double RotationFloat = {read=FRotation, write=SetRotation};
	__property double TiltFloat = {read=FTilt, write=SetTilt};
	__property double VertOffsetFloat = {read=FVertOffset, write=SetVertOffset};
	__property double ZOffset = {read=FZOffset, write=SetZOffset};
	__property double ZoomFloat = {read=FZoom, write=SetZoom};
	__property TTeeView3DChangedZoom OnChangedZoom = {read=FOnChangedZoom, write=FOnChangedZoom};
	__property TTeeView3DScrolled OnScrolled = {read=FOnScrolled, write=FOnScrolled};
	
__published:
	__property int Elevation = {read=GetElevation, write=SetElevationInteger, default=345};
	__property int FontZoom = {read=FFontZoom, write=SetFontZoom, default=100};
	__property int HorizOffset = {read=GetHorizOffset, write=SetHorizInteger, default=0};
	__property int OrthoAngle = {read=FOrthoAngle, write=SetOrthoAngle, default=45};
	__property bool Orthogonal = {read=FOrthogonal, write=SetOrthogonal, default=1};
	__property int Perspective = {read=FPerspective, write=SetPerspective, default=15};
	__property int Rotation = {read=GetRotation, write=SetRotationInteger, default=345};
	__property int Tilt = {read=GetTilt, write=SetTiltInteger, default=0};
	__property int VertOffset = {read=GetVertOffset, write=SetVertInteger, default=0};
	__property int Zoom = {read=GetZoom, write=SetZoomInteger, default=100};
	__property TCanvasZoomText ZoomText = {read=FZoomText, write=SetZoomText, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TView3DOptions() { }
	
};


typedef System::Int8 TTeeTransparency;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeBlend : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Graphics::TBitmap* FBitmap;
	
public:
	__fastcall TTeeBlend(TTeeCanvas* const ACanvas, const System::Types::TRectF &R);
	__fastcall virtual ~TTeeBlend();
	void __fastcall DoBlend(TTeeTransparency Transparency);
	void __fastcall SetRectangle(const System::Types::TRectF &R);
	__property Fmx::Graphics::TBitmap* Bitmap = {read=FBitmap};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<System::Types::TPointF> TPointArray;

typedef System::StaticArray<System::Types::TPointF, 4> TFourPoints;

typedef System::StaticArray<System::Types::TPointF, 4> TFourPointFloats;

enum DECLSPEC_DENUM TShadowDirection : unsigned char { sdLeftTop, sdLeftBottom, sdRightTop, sdRightBottom, sdCenter };

class PASCALIMPLEMENTATION TTeeShadow : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FClip;
	System::Uitypes::TAlphaColor FColor;
	TShadowDirection FDirection;
	int FHorizSize;
	bool FSmooth;
	int FSmoothBlur;
	TTeeTransparency FTransparency;
	int FVertSize;
	bool FVisible;
	System::Classes::TNotifyEvent IOnChange;
	TTeeBlend* IBlend;
	System::Byte ITransp;
	void __fastcall Changed();
	void __fastcall FinishBlending(TTeeCanvas* const ACanvas);
	int __fastcall GetSize();
	bool __fastcall IsColorStored();
	bool __fastcall IsHorizStored();
	bool __fastcall IsVertStored();
	bool __fastcall IsVisibleStored();
	bool __fastcall PrepareCanvas(TCanvas3D* const ACanvas, const System::Types::TRectF &R, int Angle = 0x0);
	void __fastcall SetClip(const bool Value);
	void __fastcall SetColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetDirection(const TShadowDirection Value);
	void __fastcall SetHorizSize(int Value);
	void __fastcall SetIntegerProperty(int &Variable, const int Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetSmooth(const bool Value);
	void __fastcall SetSmoothBlur(const int Value);
	void __fastcall SetTransparency(TTeeTransparency Value);
	void __fastcall SetVertSize(int Value);
	void __fastcall SetVisible(bool Value);
	
protected:
	System::Uitypes::TAlphaColor DefaultColor;
	int DefaultSize;
	bool DefaultVisible;
	void __fastcall InitValues(bool AVisible, System::Uitypes::TAlphaColor AColor, int ASize);
	System::Types::TRectF __fastcall OffsetRectangle(const System::Types::TRectF &R);
	void __fastcall RectToFourPoints(const System::Types::TRectF &ARect, const double Angle, /* out */ TFourPoints &P);
	
public:
	int BlurSize;
	double ZPosition;
	__fastcall TTeeShadow(System::Classes::TNotifyEvent AOnChange);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Draw(TCanvas3D* const ACanvas, const System::Types::TPointF *P, const int P_High)/* overload */;
	void __fastcall Draw(TCanvas3D* const ACanvas, const System::Types::TPointF *P, const int P_High, int Count)/* overload */;
	void __fastcall Draw(TCanvas3D* const ACanvas, const System::Types::TRectF &Rect, int RoundSize = 0x0, int Angle = 0x0)/* overload */;
	virtual void __fastcall DrawEllipse(TCanvas3D* const ACanvas, const System::Types::TRectF &Rect, int DonutPercent = 0x0, const double StartAngle = 0.000000E+00, const double EndAngle = 3.600000E+02);
	void __fastcall Hide();
	bool __fastcall ShouldDraw();
	void __fastcall Show();
	__property int Size = {read=GetSize, write=SetSize, nodefault};
	
__published:
	__property bool Clip = {read=FClip, write=SetClip, default=0};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, stored=IsColorStored, nodefault};
	__property TShadowDirection Direction = {read=FDirection, write=SetDirection, default=3};
	__property int HorizSize = {read=FHorizSize, write=SetHorizSize, stored=IsHorizStored, nodefault};
	__property bool Smooth = {read=FSmooth, write=SetSmooth, default=1};
	__property int SmoothBlur = {read=FSmoothBlur, write=SetSmoothBlur, default=0};
	__property TTeeTransparency Transparency = {read=FTransparency, write=SetTransparency, default=50};
	__property int VertSize = {read=FVertSize, write=SetVertSize, stored=IsVertStored, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, stored=IsVisibleStored, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTeeShadow() { }
	
};


class PASCALIMPLEMENTATION TTeeEmboss : public TTeeShadow
{
	typedef TTeeShadow inherited;
	
public:
	__fastcall TTeeEmboss(System::Classes::TNotifyEvent AOnChange);
	
__published:
	__property Direction = {default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTeeEmboss() { }
	
};


class PASCALIMPLEMENTATION TTeeGradientColor : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	double FOffset;
	TTeeTransparency __fastcall GetTransp();
	bool __fastcall IsTranspStored();
	void __fastcall SetTransp(const TTeeTransparency Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=FColor, default=0};
	__property double Offset = {read=FOffset, write=FOffset};
	__property TTeeTransparency Transparency = {read=GetTransp, write=SetTransp, stored=IsTranspStored, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TTeeGradientColor(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TTeeGradientColor() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeGradientColors : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTeeGradientColor* operator[](int Index) { return this->Item[Index]; }
	
private:
	TTeeGradientColor* __fastcall Get(int Index);
	void __fastcall Put(int Index, TTeeGradientColor* const Value);
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	HIDESBASE TTeeGradientColor* __fastcall Add(const double AOffset, const System::Uitypes::TAlphaColor AColor, TTeeTransparency ATransparency = (TTeeTransparency)(0x0))/* overload */;
	void __fastcall Repaint();
	__property TTeeGradientColor* Item[int Index] = {read=Get, write=Put/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TTeeGradientColors(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTeeGradientColors() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TGradientDirection : unsigned char { gdTopBottom, gdBottomTop, gdLeftRight, gdRightLeft, gdFromCenter, gdFromTopLeft, gdFromBottomLeft, gdRadial, gdDiagonalUp, gdDiagonalDown };

class PASCALIMPLEMENTATION TCustomTeeGradient : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FAngle;
	int FBalance;
	TTeeGradientColors* FColors;
	TGradientDirection FDirection;
	int FRadialX;
	int FRadialY;
	bool FStartIsEnd;
	TSubGradient* FSub;
	bool FVisible;
	System::Types::TRectF FCustomTargetRectangle;
	Fmx::Graphics::TBrush* IBrush;
	void __fastcall DrawRadial(TTeeCanvas* const Canvas, const System::Types::TRectF &Rect);
	void __fastcall DrawSubGradient(TTeeCanvas* const Canvas, const System::Types::TRectF &Rect, int RoundRectSize = 0x0);
	TTeeGradientColors* __fastcall GetColors();
	System::Uitypes::TAlphaColor __fastcall GetEndColor();
	System::Uitypes::TAlphaColor __fastcall GetMidColor();
	System::Uitypes::TAlphaColor __fastcall GetStartColor();
	TSubGradient* __fastcall GetSub();
	bool __fastcall IsColorsStored();
	bool __fastcall IsDirectionStored();
	bool __fastcall IsEndStored();
	bool __fastcall IsMidStored();
	bool __fastcall IsStartStored();
	bool __fastcall IsSubStored();
	bool __fastcall IsVisibleStored();
	void __fastcall SetAngle(int Value);
	void __fastcall SetBalance(int Value);
	void __fastcall SetColors(TTeeGradientColors* const Value);
	void __fastcall SetDirection(TGradientDirection Value);
	void __fastcall SetEndColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetIntegerProperty(int &Variable, int Value);
	void __fastcall SetMidColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetRadialX(const int Value);
	void __fastcall SetRadialY(const int Value);
	void __fastcall SetStartColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetSub(TSubGradient* const Value);
	void __fastcall SetVisible(bool Value);
	
protected:
	System::Classes::TNotifyEvent IChanged;
	TGradientDirection IDefDirection;
	System::Uitypes::TAlphaColor IDefEnd;
	System::Uitypes::TAlphaColor IDefMid;
	System::Uitypes::TAlphaColor IDefStart;
	bool IDefVisible;
	System::Uitypes::TAlphaColor IMidColor;
	void __fastcall DoChanged();
	void __fastcall InitDefaults();
	void __fastcall InitDirection(const TGradientDirection ADirection);
	
public:
	__fastcall virtual TCustomTeeGradient(System::Classes::TNotifyEvent ChangedEvent);
	__fastcall virtual ~TCustomTeeGradient();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Draw(TTeeCanvas* const Canvas, const System::Types::TRectF &Rect, int RoundRectSize = 0x0)/* overload */;
	void __fastcall Draw(TTeeCanvas* const Canvas, TFourPoints &P)/* overload */;
	void __fastcall Draw(TCanvas3D* const Canvas, TFourPoints &P, int Z)/* overload */;
	void __fastcall Draw(TCanvas3D* const Canvas, TPointArray &P, int Z, bool Is3D)/* overload */;
	void __fastcall ResetColors();
	void __fastcall UseMiddleColor();
	__property System::Classes::TNotifyEvent Changed = {read=IChanged, write=IChanged};
	__property int Angle = {read=FAngle, write=SetAngle, default=0};
	__property System::Types::TRectF CustomTargetRectangle = {read=FCustomTargetRectangle, write=FCustomTargetRectangle, stored=false};
	__property int Balance = {read=FBalance, write=SetBalance, default=50};
	__property TTeeGradientColors* Colors = {read=GetColors, write=SetColors, stored=IsColorsStored};
	__property TGradientDirection Direction = {read=FDirection, write=SetDirection, stored=IsDirectionStored, nodefault};
	__property System::Uitypes::TAlphaColor EndColor = {read=GetEndColor, write=SetEndColor, stored=IsEndStored, nodefault};
	__property System::Uitypes::TAlphaColor MidColor = {read=GetMidColor, write=SetMidColor, stored=IsMidStored, nodefault};
	__property int RadialX = {read=FRadialX, write=SetRadialX, default=0};
	__property int RadialY = {read=FRadialY, write=SetRadialY, default=0};
	__property System::Uitypes::TAlphaColor StartColor = {read=GetStartColor, write=SetStartColor, stored=IsStartStored, nodefault};
	__property bool StartIsEnd = {read=FStartIsEnd, write=FStartIsEnd, default=0};
	__property TSubGradient* SubGradient = {read=GetSub, write=SetSub, stored=IsSubStored};
	__property bool Visible = {read=FVisible, write=SetVisible, stored=IsVisibleStored, nodefault};
};


class PASCALIMPLEMENTATION TSubGradient : public TCustomTeeGradient
{
	typedef TCustomTeeGradient inherited;
	
private:
	TTeeTransparency FTransparency;
	void __fastcall SetTransparency(const TTeeTransparency Value);
	
__published:
	__property Angle = {default=0};
	__property Balance = {default=50};
	__property Colors;
	__property Direction;
	__property EndColor;
	__property MidColor;
	__property RadialX = {default=0};
	__property RadialY = {default=0};
	__property StartColor;
	__property TTeeTransparency Transparency = {read=FTransparency, write=SetTransparency, default=50};
	__property Visible;
public:
	/* TCustomTeeGradient.Create */ inline __fastcall virtual TSubGradient(System::Classes::TNotifyEvent ChangedEvent) : TCustomTeeGradient(ChangedEvent) { }
	/* TCustomTeeGradient.Destroy */ inline __fastcall virtual ~TSubGradient() { }
	
};


class PASCALIMPLEMENTATION TTeeGradient : public TCustomTeeGradient
{
	typedef TCustomTeeGradient inherited;
	
__published:
	__property Angle = {default=0};
	__property Balance = {default=50};
	__property Colors;
	__property Direction;
	__property EndColor;
	__property MidColor;
	__property RadialX = {default=0};
	__property RadialY = {default=0};
	__property StartColor;
	__property SubGradient;
	__property Visible;
public:
	/* TCustomTeeGradient.Create */ inline __fastcall virtual TTeeGradient(System::Classes::TNotifyEvent ChangedEvent) : TCustomTeeGradient(ChangedEvent) { }
	/* TCustomTeeGradient.Destroy */ inline __fastcall virtual ~TTeeGradient() { }
	
};


enum DECLSPEC_DENUM TFontQuality : unsigned char { fqBest, fqNormal, fqDefault, fqClearType };

class PASCALIMPLEMENTATION TTeeFont : public Fmx::Graphics::TFont
{
	typedef Fmx::Graphics::TFont inherited;
	
private:
	TTeeBrush* FBrush;
	double FDepth;
	int FInterCharSize;
	TTeeHiddenPen* FOutLine;
	TFontQuality FQuality;
	System::Uitypes::TAlphaColor IDefColor;
	System::Uitypes::TFontStyles IDefStyle;
	void __fastcall Changed();
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	System::UnicodeString __fastcall GetName();
	void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall DoReadHeight(System::Classes::TReader* Reader);
	TTeeEmboss* __fastcall GetEmboss();
	TTeeGradient* __fastcall GetGradient();
	TTeeHiddenPen* __fastcall GetOutLine();
	TTeePicture* __fastcall GetPicture();
	TTeeShadow* __fastcall GetShadow();
	bool __fastcall IsColorStored();
	bool __fastcall IsDepthStored();
	bool __fastcall IsHeightStored();
	bool __fastcall IsNameStored();
	bool __fastcall IsStyleStored();
	void __fastcall SetBrush(TTeeBrush* const Value);
	void __fastcall SetDepth(const double Value);
	void __fastcall SetEmboss(TTeeEmboss* const Value);
	void __fastcall SetGradient(TTeeGradient* const Value);
	void __fastcall SetInterCharSize(int Value);
	void __fastcall SetOutLine(TTeeHiddenPen* const Value);
	void __fastcall SetPicture(TTeePicture* const Value);
	void __fastcall SetQuality(const TFontQuality Value);
	void __fastcall SetShadow(TTeeShadow* const Value);
	float __fastcall GetSizeFloat();
	void __fastcall SetSizeFloat(const float Value);
	bool __fastcall IsSizeFloatStored();
	
protected:
	TTeeEmboss* FEmboss;
	TTeeShadow* FShadow;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall InitColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall InitStyle(const System::Uitypes::TFontStyles Value);
	
public:
	__fastcall TTeeFont(System::Classes::TNotifyEvent ChangedEvent);
	__fastcall virtual ~TTeeFont();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, stored=IsColorStored, nodefault};
	__property System::UnicodeString Name = {read=GetName, write=SetName, stored=false};
	__property Family = {stored=IsNameStored, default=0};
	__property Size = {stored=IsHeightStored};
	__property float SizeFloat = {read=GetSizeFloat, write=SetSizeFloat, stored=IsSizeFloatStored};
	__property TTeeBrush* Brush = {read=FBrush, write=SetBrush};
	__property double Depth = {read=FDepth, write=SetDepth, stored=IsDepthStored};
	__property TTeeEmboss* Emboss = {read=GetEmboss, write=SetEmboss};
	__property TTeeGradient* Gradient = {read=GetGradient, write=SetGradient, stored=false};
	__property int InterCharSize = {read=FInterCharSize, write=SetInterCharSize, default=0};
	__property TTeeHiddenPen* OutLine = {read=GetOutLine, write=SetOutLine};
	__property TTeePicture* Picture = {read=GetPicture, write=SetPicture, stored=false};
	__property TFontQuality Quality = {read=FQuality, write=SetQuality, default=2};
	__property TTeeShadow* Shadow = {read=GetShadow, write=SetShadow};
	__property Style = {stored=IsStyleStored};
};


enum DECLSPEC_DENUM TCanvasStretchQuality : unsigned char { sqHigh, sqLow };

enum DECLSPEC_DENUM TCanvasBackMode : unsigned char { cbmNone, cbmTransparent, cbmOpaque };

typedef int TCanvasTextAlign;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeCachedObject : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall TTeeCachedObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeCachedObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef double TChartValue;

typedef int TTeeCanvasHandle;

class PASCALIMPLEMENTATION TTeeCanvas : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::Byte> _TTeeCanvas__1;
	
	
private:
	TCanvasStretchQuality FStretchQuality;
	bool FMetafiling;
	bool IChangingFont;
	_TTeeCanvas__1 ITranspStack;
	Fmx::Textlayout::TTextLayout* ILayout;
	Fmx::Textlayout::TTextLayout* __fastcall ICachedLayout(const int AX, const int AY, const System::UnicodeString Text);
	void __fastcall AssignFontSize(TTeeFont* const AFont, const float ASize);
	void __fastcall ChangedBrush(System::TObject* Sender);
	void __fastcall ChangedFont(System::TObject* Sender);
	void __fastcall ChangedPen(System::TObject* Sender);
	int __fastcall GetFontHeight();
	TTeeGradient* __fastcall GetGradient();
	void __fastcall InternalDark(const System::Uitypes::TAlphaColor AColor, System::Byte Quantity);
	Fmx::Graphics::TPathData* __fastcall DonutPath(const System::Types::TRectF &R, const float StartAngle, const float EndAngle, const float Percent, const float Thick);
	void __fastcall PrepareGradient(TTeeGradient* const Source, Fmx::Graphics::TGradient* const Dest);
	
protected:
	TTeeBrush* FBrush;
	Fmx::Graphics::TCanvas* FCanvas;
	TTeeFont* FFont;
	TTeePen* FPen;
	System::Types::TRectF FBounds;
	double FFontZoom;
	bool FSupportsAlpha;
	bool FSupportsConcave;
	bool IZoomText;
	bool IUseTextCenter;
	System::Types::TPointF ITextCenter;
	System::Byte Transparency;
	virtual void __fastcall SetCanvas(Fmx::Graphics::TCanvas* const ACanvas);
	void __fastcall CalcArcAngles(const int X1, const int Y1, const int X2, const int Y2, const int X3, const int Y3, const int X4, const int Y4, /* out */ double &StartAngle, /* out */ double &EndAngle);
	virtual void __fastcall DoChangedBrush(TTeeBrush* const ABrush);
	virtual void __fastcall DoChangedFont();
	virtual void __fastcall DoChangedPen();
	virtual void __fastcall FastLineTo(const int X, const int Y);
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor() = 0 ;
	virtual TCanvasBackMode __fastcall GetBackMode() = 0 ;
	virtual bool __fastcall GetIsNoBMPGrid() = 0 ;
	virtual bool __fastcall GetMonochrome() = 0 ;
	virtual System::Uitypes::TAlphaColor __fastcall GetPixel(int x, int y) = 0 ;
	virtual bool __fastcall GetSupportsFullRotation() = 0 ;
	virtual bool __fastcall GetSupportsXORMode() = 0 ;
	virtual int __fastcall GetTextAlign() = 0 ;
	virtual bool __fastcall GetUseBuffer() = 0 ;
	void __fastcall InternalDrawCheck(int x, int y, bool Checked, const System::Uitypes::TAlphaColor ABackColor, bool CheckBox = true);
	bool __fastcall IsGradientVisible();
	void __fastcall PopTransp();
	void __fastcall PushTransp();
	virtual void __fastcall SetAntiAlias(const bool Value);
	virtual void __fastcall SetBackColor(const System::Uitypes::TAlphaColor Value) = 0 ;
	virtual void __fastcall SetBackMode(const TCanvasBackMode Value) = 0 ;
	virtual void __fastcall SetFastLine(const bool Active) = 0 ;
	virtual void __fastcall SetInterCharSize(int ASize);
	virtual void __fastcall SetMonochrome(bool Value) = 0 ;
	virtual void __fastcall SetPenMode(TTeePen* const APen);
	virtual void __fastcall SetPixel(int X, int Y, System::Uitypes::TAlphaColor Value) = 0 ;
	virtual void __fastcall SetTextAlign(const int Value) = 0 ;
	virtual void __fastcall SetUseBuffer(bool Value) = 0 ;
	float __fastcall Opacity();
	
public:
	__fastcall TTeeCanvas();
	__fastcall virtual ~TTeeCanvas();
	void __fastcall AssignBrush(TTeeBrush* const ABrush)/* overload */;
	void __fastcall AssignBrush(TTeeBrush* const ABrush, System::Uitypes::TAlphaColor ABackColor)/* overload */;
	virtual void __fastcall AssignBrush(TTeeBrush* const ABrush, System::Uitypes::TAlphaColor AColor, System::Uitypes::TAlphaColor ABackColor)/* overload */;
	void __fastcall AssignBrushColor _DEPRECATED_ATTRIBUTE1("Please use AssignBrush method.") (TTeeBrush* const ABrush, System::Uitypes::TAlphaColor AColor, System::Uitypes::TAlphaColor ABackColor);
	void __fastcall AssignVisiblePen(TTeePen* const APen);
	virtual void __fastcall AssignVisiblePenColor(TTeePen* const APen, System::Uitypes::TAlphaColor AColor);
	void __fastcall AssignFont(TTeeFont* const AFont);
	void __fastcall ResetState();
	virtual TTeeBlend* __fastcall BeginBlending(const System::Types::TRectF &R, TTeeTransparency Transparency);
	virtual void __fastcall EndBlending(TTeeBlend* const Blend);
	static System::Byte __fastcall ColorAlpha(const System::Uitypes::TAlphaColor AColor);
	static System::Uitypes::TAlphaColor __fastcall ColorFrom(const System::Uitypes::TAlphaColor AColor, const System::Byte Alpha);
	virtual void __fastcall Arc(const int Left, const int Top, const int Right, const int Bottom, const int StartX, const int StartY, const int EndX, const int EndY) = 0 /* overload */;
	virtual void __fastcall Arc(const int Left, const int Top, const int Right, const int Bottom, double StartAngle, double EndAngle)/* overload */;
	virtual void __fastcall ArcTo(const int X1, const int Y1, const int X2, const int Y2, const int X3, const int Y3, const int X4, const int Y4, const bool ClockWise = false);
	void __fastcall Arrow(bool Filled, const double ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight)/* overload */;
	virtual void __fastcall Donut(const System::Types::TRectF &R, const double StartAngle, const double EndAngle, const double HolePercent)/* overload */;
	virtual void __fastcall Donut(int XCenter, int YCenter, int XRadius, int YRadius, const double StartAngle, const double EndAngle, const double HolePercent) = 0 /* overload */;
	virtual void __fastcall Draw(int X, int Y, Fmx::Graphics::TBitmap* const Graphic) = 0 ;
	void __fastcall Ellipse(const System::Types::TRectF &R)/* overload */;
	virtual void __fastcall Ellipse(const float X1, const float Y1, const float X2, const float Y2) = 0 /* overload */;
	virtual void __fastcall FillRect(const System::Types::TRectF &Rect) = 0 ;
	virtual void __fastcall Frame3D(System::Types::TRectF &Rect, System::Uitypes::TAlphaColor TopColor, System::Uitypes::TAlphaColor BottomColor, int Width);
	TPointArray __fastcall GetArrowPoints(const float ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight)/* overload */;
	static bool __fastcall IsConvexPolygon(const TPointArray P)/* overload */;
	virtual void __fastcall LineTo(const float X, const float Y) = 0 /* overload */;
	void __fastcall LineTo(const System::Types::TPointF &P)/* overload */;
	virtual void __fastcall MoveTo(const float X, const float Y) = 0 /* overload */;
	void __fastcall MoveTo(const System::Types::TPointF &P)/* overload */;
	virtual void __fastcall Pie(const System::Types::TRectF &R, const double StartAngle, const double EndAngle) = 0 /* overload */;
	virtual void __fastcall Pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4) = 0 /* overload */;
	void __fastcall Rectangle(const System::Types::TRectF &R)/* overload */;
	virtual void __fastcall Rectangle(const float X0, const float Y0, const float X1, const float Y1) = 0 /* overload */;
	virtual void __fastcall RoundRect(int X1, int Y1, int X2, int Y2, int X3, int Y3) = 0 /* overload */;
	void __fastcall RoundRect(const System::Types::TRectF &R, int X, int Y, TTeeCorners* const ACorners = (TTeeCorners*)(0x0))/* overload */;
	virtual void __fastcall StretchDraw(const System::Types::TRectF &Rect, Fmx::Graphics::TBitmap* const Graphic) = 0 /* overload */;
	void __fastcall TextOut(const float X, const float Y, const System::UnicodeString Text, bool AllowHtml)/* overload */;
	virtual void __fastcall TextOut(const float X, const float Y, const System::UnicodeString Text) = 0 /* overload */;
	virtual int __fastcall TextHeight(const System::UnicodeString St)/* overload */;
	virtual System::Types::TPointF __fastcall TextSize(const System::UnicodeString St)/* overload */;
	virtual int __fastcall TextWidth(const System::UnicodeString St)/* overload */;
	virtual void __fastcall ClipRectangle(const System::Types::TRectF &Rect) = 0 /* overload */;
	virtual void __fastcall ClipRectangle(const System::Types::TRectF &Rect, int RoundX, int RoundY)/* overload */;
	virtual void __fastcall ClipEllipse(const System::Types::TRectF &Rect, bool Inverted = false);
	virtual void __fastcall ClipPolygon(const System::Types::TPointF *Points, const int Points_High, int NumPoints, bool DiffRegion = false);
	static bool __fastcall ConvexHull(TPointArray &Points);
	TTeeBasePath* __fastcall CreatePath()/* overload */;
	virtual TTeeBasePath* __fastcall CreatePath(const TPointFloatArray Points, const TPathPointTypes Types)/* overload */;
	virtual void __fastcall Curve(const System::Types::TPointF *Points, const int Points_High, const float Tension, bool Closed, const float Z);
	virtual void __fastcall DoHorizLine(const float X0, const float X1, const float Y);
	void __fastcall DoRectangle _DEPRECATED_ATTRIBUTE1("Please use Rectangle method.") (const System::Types::TRectF &Rect);
	virtual void __fastcall DoVertLine(const float X, const float Y0, const float Y1);
	virtual void __fastcall DrawCheckBox(int x, int y, bool Checked, const System::Uitypes::TAlphaColor ABackColor, bool CheckBox = true);
	virtual void __fastcall EraseBackground(const System::Types::TRectF &Rect) = 0 ;
	virtual void __fastcall GradientFill(const System::Types::TRectF &Rect, System::Uitypes::TAlphaColor StartColor, System::Uitypes::TAlphaColor EndColor, TGradientDirection Direction, int Balance = 0x32, int RadialX = 0x0, int RadialY = 0x0) = 0 /* overload */;
	virtual void __fastcall Invalidate() = 0 ;
	virtual void __fastcall Line(const float X0, const float Y0, const float X1, const float Y1)/* overload */;
	void __fastcall Line(const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint)/* overload */;
	virtual void __fastcall Polyline(const System::Types::TPointF *Points, const int Points_High) = 0 /* overload */;
	virtual void __fastcall Polygon(const System::Types::TPointF *Points, const int Points_High) = 0 ;
	virtual void __fastcall PolygonConcave(const System::Types::TPointF *Points, const int Points_High)/* overload */;
	virtual void __fastcall RotateLabel(int x, int y, const System::UnicodeString St, double RotDegree, bool AllowHTML = false) = 0 ;
	virtual void __fastcall UnClipRectangle() = 0 ;
	__property System::Uitypes::TAlphaColor BackColor = {read=GetBackColor, write=SetBackColor, nodefault};
	__property TCanvasBackMode BackMode = {read=GetBackMode, write=SetBackMode, nodefault};
	__property System::Types::TRectF Bounds = {read=FBounds};
	__property TTeeBrush* Brush = {read=FBrush};
	__property TTeeFont* Font = {read=FFont};
	__property int FontHeight = {read=GetFontHeight, nodefault};
	__property double FontZoom = {read=FFontZoom, write=FFontZoom};
	__property TTeeGradient* Gradient = {read=GetGradient};
	__property bool IsNoBMPGrid = {read=GetIsNoBMPGrid, nodefault};
	__property bool Metafiling = {read=FMetafiling, write=FMetafiling, nodefault};
	__property bool Monochrome = {read=GetMonochrome, write=SetMonochrome, nodefault};
	__property TTeePen* Pen = {read=FPen};
	__property System::Uitypes::TAlphaColor Pixels[int X][int Y] = {read=GetPixel, write=SetPixel};
	__property Fmx::Graphics::TCanvas* ReferenceCanvas = {read=FCanvas, write=SetCanvas};
	__property TCanvasStretchQuality StretchDrawQuality = {read=FStretchQuality, write=FStretchQuality, default=0};
	__property bool SupportsAlpha = {read=FSupportsAlpha, nodefault};
	__property bool SupportsConcave = {read=FSupportsConcave, nodefault};
	__property bool SupportsFullRotation = {read=GetSupportsFullRotation, nodefault};
	__property bool SupportsXORMode = {read=GetSupportsXORMode, nodefault};
	__property int TextAlign = {read=GetTextAlign, write=SetTextAlign, nodefault};
	__property bool UseBuffer = {read=GetUseBuffer, write=SetUseBuffer, nodefault};
};


#pragma pack(push,1)
struct DECLSPEC_DRECORD TFloatPoint
{
public:
	float X;
	float Y;
};
#pragma pack(pop)


typedef System::Math::Vectors::TPoint3D TPoint3DFloat;

typedef System::DynamicArray<System::Math::Vectors::TPoint3D> TPoint3DArray;

class PASCALIMPLEMENTATION TFloatXYZ : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	float FX;
	float FY;
	float FZ;
	void __fastcall SetSingleProperty(float &Variable, const float Value);
	
protected:
	System::Classes::TNotifyEvent FOnChange;
	System::Math::Vectors::TPoint3D __fastcall Point();
	void __fastcall SetX(const float Value);
	void __fastcall SetY(const float Value);
	void __fastcall SetZ(const float Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property float X = {read=FX, write=SetX};
	__property float Y = {read=FY, write=SetY};
	__property float Z = {read=FZ, write=SetZ};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFloatXYZ() { }
	
public:
	/* TObject.Create */ inline __fastcall TFloatXYZ() : System::Classes::TPersistent() { }
	
};


#pragma pack(push,1)
struct DECLSPEC_DRECORD TPoint3D
{
public:
	int x;
	int y;
	int z;
};
#pragma pack(pop)


typedef System::StaticArray<TPoint3D, 3> TTrianglePoints3D;

typedef System::StaticArray<System::Uitypes::TAlphaColor, 3> TTriangleColors3D;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TTriangleIndexes
{
public:
	int Point0;
	int Point1;
	int Point2;
};
#pragma pack(pop)


struct DECLSPEC_DRECORD TSurfaceVertex
{
public:
	System::Math::Vectors::TPoint3D P0;
	System::Math::Vectors::TPoint3D P1;
	System::Math::Vectors::TPoint3D N0;
	System::Math::Vectors::TPoint3D N1;
	System::Uitypes::TAlphaColor C0;
	System::Uitypes::TAlphaColor C1;
	bool Flag;
};


typedef void __fastcall (__closure *TTeeCanvasCalcPoints)(int x, int z, bool CalcColors, /* out */ TSurfaceVertex &V);

typedef void __fastcall (__closure *TTeeCanvasTriPoints)(int Index, /* out */ TTrianglePoints3D &Points, /* out */ TTriangleColors3D &Colors, /* out */ TTriangleIndexes &Indexes);

enum DECLSPEC_DENUM TTeeCanvasSurfaceStyle : unsigned char { tcsSolid, tcsWire, tcsDot };

enum DECLSPEC_DENUM TCanvas3DPlane : unsigned char { cpX, cpY, cpZ };

typedef System::StaticArray<System::Types::TPointF, 3> TTrianglePoints;

class PASCALIMPLEMENTATION TPointBlock : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TNotifyEvent FOnChanged;
	
protected:
	TVisualBlock* IOwner;
	void __fastcall DoChanged();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPointBlock() { }
	
public:
	/* TObject.Create */ inline __fastcall TPointBlock() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TPointXYFloat : public TPointBlock
{
	typedef TPointBlock inherited;
	
private:
	double IDefault;
	double __fastcall GetX();
	double __fastcall GetY();
	bool __fastcall IsXStored();
	bool __fastcall IsYStored();
	void __fastcall ReadXZero(System::Classes::TReader* Reader);
	void __fastcall ReadYZero(System::Classes::TReader* Reader);
	void __fastcall SetX(const double Value);
	void __fastcall SetY(const double Value);
	void __fastcall WriteXZero(System::Classes::TWriter* Writer);
	void __fastcall WriteYZero(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall InitDefault(const double Value);
	
public:
	System::Types::TPointF Point;
	__fastcall virtual TPointXYFloat(TVisualBlock* const AOwner, const float AValue, const System::Classes::TNotifyEvent ChangedEvent);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property double X = {read=GetX, write=SetX, stored=IsXStored};
	__property double Y = {read=GetY, write=SetY, stored=IsYStored};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPointXYFloat() { }
	
};


class PASCALIMPLEMENTATION TPointXYZFloat : public TPointBlock
{
	typedef TPointBlock inherited;
	
private:
	float IDefault;
	float __fastcall GetValue();
	float __fastcall GetX();
	float __fastcall GetY();
	float __fastcall GetZ();
	bool __fastcall IsXStored();
	bool __fastcall IsYStored();
	bool __fastcall IsZStored();
	void __fastcall ReadZZero(System::Classes::TReader* Reader);
	void __fastcall SetValue(const float Value);
	void __fastcall SetX(const float Value);
	void __fastcall SetY(const float Value);
	void __fastcall SetZ(const float Value);
	void __fastcall WriteZZero(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall InitDefault(const float Value);
	
public:
	System::Math::Vectors::TPoint3D Point;
	__fastcall virtual TPointXYZFloat(TVisualBlock* const AOwner, const double AValue, const System::Classes::TNotifyEvent ChangedEvent);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	TPoint3D __fastcall AsRound();
	void __fastcall SetPoint(const float X, const float Y, const float Z)/* overload */;
	void __fastcall SetPoint(const System::Math::Vectors::TPoint3D &Value)/* overload */;
	
__published:
	__property float Value = {read=GetValue, write=SetValue, stored=false};
	__property float X = {read=GetX, write=SetX, stored=IsXStored};
	__property float Y = {read=GetY, write=SetY, stored=IsYStored};
	__property float Z = {read=GetZ, write=SetZ, stored=IsZStored};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPointXYZFloat() { }
	
};


class PASCALIMPLEMENTATION TVisualBlock : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TPointXYZFloat* FLocation;
	TPointXYZFloat* FSize;
	void __fastcall SetLocation(TPointXYZFloat* const Value);
	void __fastcall SetSize(TPointXYZFloat* const Value);
	
protected:
	bool IsCloneable;
	virtual void __fastcall AddPathPoint(const float X, const float Y, const System::Uitypes::TAlphaColor AColor = (System::Uitypes::TAlphaColor)(0xffffff));
	virtual void __fastcall ClearPath();
	void __fastcall SetBounds(const System::Types::TRectF &R, const float Z0, const float Z1, const float Height);
	virtual void __fastcall SetFormatting(TTeePen* const APen, TTeeBrush* const ABrush, bool SetBrushImage, System::Uitypes::TAlphaColor AColor, System::Byte ATransparency) = 0 ;
	virtual void __fastcall SizeChanged(System::TObject* Sender);
	
public:
	__fastcall virtual TVisualBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TVisualBlock();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Repaint() = 0 ;
	virtual Fmx::Controls::TControl* __fastcall Editor(System::Classes::TComponent* const AOwner, bool Embeddable = false) = 0 ;
	
__published:
	__property TPointXYZFloat* Location = {read=FLocation, write=SetLocation};
	__property TPointXYZFloat* Size = {read=FSize, write=SetSize};
};


enum DECLSPEC_DENUM TEdgeStyle : unsigned char { edFlat, edCurved, edNone };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeTransform : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	bool Enabled;
	System::Math::Vectors::TPoint3D Origin;
	System::Math::Vectors::TPoint3D Translate;
	float Rotate;
	System::Math::Vectors::TPoint3D Scale;
	bool Clip;
	System::Types::TRectF Bounds;
public:
	/* TObject.Create */ inline __fastcall TTeeTransform() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeTransform() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCanvas3D : public TTeeCanvas
{
	typedef TTeeCanvas inherited;
	
	
private:
	struct DECLSPEC_DRECORD TActiveMatrix
	{
	public:
		bool Active;
		System::Math::Vectors::TMatrix Matrix;
	};
	
	
	typedef System::DynamicArray<TActiveMatrix> _TCanvas3D__1;
	
	
private:
	int IDisabledRotation;
	_TCanvas3D__1 ITransform;
	TPointFloatArray __fastcall Calc3DPointsFloat(const System::Types::TPointF *Points, const int Points_High, int Z);
	
protected:
	TView3DOptions* F3DOptions;
	bool FIsNoBMPGrid;
	bool FIsOrthogonal;
	TTeeTransform* FTransform;
	int FXCenter;
	int FYCenter;
	int FZCenter;
	int GradientZ;
	bool SupportsID;
	bool INoFixAlign;
	virtual TVisualBlock* __fastcall BeginEntity(const System::UnicodeString Entity, TVisualBlock* const Visual = (TVisualBlock*)(0x0), TTeeTransform* const Transform = (TTeeTransform*)(0x0));
	virtual void __fastcall EndEntity();
	virtual void __fastcall DrawLighting(TEdgeStyle AEdgeStyle, int ZPos, const System::Types::TRectF &Z0BevelRect, const System::Types::TRectF &Z1BevelRect, const System::Types::TRectF &Z0DonutRect, int IStartAngle, int IEndAngle, const System::Types::TPointF &Middle0, bool IsDonut);
	void __fastcall CalcPieAngles(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4, /* out */ float &Theta, /* out */ float &Theta2);
	virtual bool __fastcall CheckFastBrush();
	virtual System::Uitypes::TAlphaColor __fastcall GetPixel3D(int X, int Y, int Z) = 0 ;
	virtual bool __fastcall GetSupports3DText() = 0 ;
	virtual void __fastcall SetPixel3D(int X, int Y, int Z, System::Uitypes::TAlphaColor Value) = 0 ;
	virtual void __fastcall SmoothShadow(TTeeShadow* const Shadow, const System::Types::TRectF &Rect, bool Ellipse, int RoundSize, const System::Types::TPointF *P, const int P_High, int DonutPercent = 0x0, const double StartAngle = 0.000000E+00, const double EndAngle = 3.600000E+02);
	HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	int __stdcall _AddRef();
	int __stdcall _Release();
	__property TTeeBrush* Brush = {read=FBrush, write=FBrush};
	__property TTeePen* Pen = {read=FPen, write=FPen};
	__property TTeeFont* Font = {read=FFont, write=FFont};
	
public:
	System::Math::Vectors::TPoint3D RotationCenter;
	__fastcall virtual TCanvas3D();
	__classmethod virtual System::UnicodeString __fastcall Description();
	__classmethod virtual System::UnicodeString __fastcall EditorClass();
	System::Types::TRectF __fastcall CalcRect3D(const System::Types::TRectF &R, int Z);
	virtual void __fastcall Calculate2DPosition(int &x, int &y, int z) = 0 /* overload */;
	System::Types::TPointF __fastcall Calculate3DPosition(const TPoint3D &P)/* overload */;
	System::Types::TPointF __fastcall Calculate3DPosition(const System::Types::TPointF &P, int z)/* overload */;
	virtual System::Types::TPointF __fastcall Calculate3DPosition(int x, int y, int z) = 0 /* overload */;
	virtual System::Types::TPointF __fastcall Calculate3DPosition(const float x, const float y, const float z) = 0 /* overload */;
	TPointArray __fastcall Calc3DPoints(const System::Types::TPointF *Points, const int Points_High, int z);
	void __fastcall FourPointsFromRect(const System::Types::TRectF &R, int Z, /* out */ TFourPoints &P);
	System::Types::TRectF __fastcall RectFromRectZ(const System::Types::TRectF &R, int Z);
	System::Types::TPointF __fastcall PointFromCircle(const System::Types::TRectF &Rect, const double Degrees, int zPos = 0x0, bool ClockWise = false);
	static System::Types::TPointF __fastcall PointFromSpiral(const System::Types::TRectF &Rect, const double Degrees, const double Twist);
	virtual System::Types::TRectF __fastcall InitWindow(Fmx::Graphics::TCanvas* const DestCanvas, TView3DOptions* const A3DOptions, System::Uitypes::TAlphaColor ABackColor, bool Is3D, const System::Types::TRectF &UserRect) = 0 ;
	__classmethod virtual bool __fastcall IsAvailable();
	virtual void __fastcall Assign(TCanvas3D* const Source);
	void __fastcall AssignFont3D(TTeeFont* const AFont);
	virtual void __fastcall Projection(int MaxDepth, const System::Types::TRectF &ABounds, const System::Types::TRectF &Rect) = 0 ;
	virtual void __fastcall ShowImage(Fmx::Graphics::TCanvas* const DestCanvas, Fmx::Graphics::TCanvas* const DefaultCanvas, const System::Types::TRectF &UserRect) = 0 ;
	virtual bool __fastcall ReDrawBitmap() = 0 ;
	virtual bool __fastcall RenderToBitmap(Fmx::Graphics::TBitmap* &ABitmap, const System::Types::TRectF &R);
	HIDESBASE void __fastcall Arc(const int Left, const int Top, const int Right, const int Bottom, const int StartX, const int StartY, const int EndX, const int EndY, const int Z)/* overload */;
	HIDESBASE void __fastcall Arrow(bool Filled, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight, int Z)/* overload */;
	HIDESBASE virtual void __fastcall Arrow(bool Filled, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight, int Z0, int Z1, const double ArrowPercent) = 0 /* overload */;
	virtual void __fastcall ClipCube(const System::Types::TRectF &Rect, int MinZ, int MaxZ) = 0 ;
	virtual void __fastcall Cone(bool Vertical, int Left, int Top, int Right, int Bottom, int Z0, int Z1, bool Dark3D, int ConePercent) = 0 ;
	virtual void __fastcall Cube(int Left, int Right, int Top, int Bottom, int Z0, int Z1, bool DarkSides = true, int RoundSize = 0x0) = 0 /* overload */;
	virtual void __fastcall Cube(int Left, int Right, int Top, int Bottom, int Z0, int Z1, int BevelSize, bool DarkSides = true, int RoundSize = 0x0) = 0 /* overload */;
	void __fastcall Cube(const System::Types::TRectF &R, int Z0, int Z1, bool DarkSides = true, int RoundSize = 0x0)/* overload */;
	TPointArray __fastcall CubeHull(const System::Types::TRectF &Rect, int MinZ, int MaxZ);
	virtual void __fastcall Cylinder(bool Vertical, int Left, int Top, int Right, int Bottom, int Z0, int Z1, bool Dark3D = true) = 0 ;
	void __fastcall Diamond(const System::Types::TRectF &R, int Z0, int Z1)/* overload */;
	virtual void __fastcall Diamond(const float Left, const float Top, const float Right, const float Bottom, int Z0, int Z1)/* overload */;
	virtual void __fastcall DisableRotation();
	void __fastcall EllipseWithZ(const System::Types::TRectF &Rect, int Z)/* overload */;
	virtual void __fastcall EllipseWithZ(const float X1, const float Y1, const float X2, const float Y2, const int Z) = 0 /* overload */;
	virtual void __fastcall EnableRotation();
	virtual void __fastcall HorizLine3D(const float Left, const float Right, const float Y, const float Z)/* overload */;
	HIDESBASE virtual void __fastcall RoundRect(const System::Types::TRectF &R, int X, int Y, int Z0, int Z1)/* overload */;
	virtual void __fastcall VertLine3D(const float X, const float Top, const float Bottom, const float Z)/* overload */;
	virtual void __fastcall ZLine3D(const float X, const float Y, const float Z0, const float Z1);
	virtual void __fastcall FrontPlaneBegin();
	virtual void __fastcall FrontPlaneEnd();
	HIDESBASE TPointArray __fastcall GetArrowPoints(const float ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight, int Z)/* overload */;
	virtual void __fastcall LineWithZ(const float X0, const float Y0, const float X1, const float Y1, const float Z)/* overload */;
	void __fastcall LineWithZ(const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int Z)/* overload */;
	virtual void __fastcall MoveTo3D(const float X, const float Y, const float Z)/* overload */;
	void __fastcall MoveTo3D(const TPoint3D &P)/* overload */;
	virtual void __fastcall LineTo3D(const float X, const float Y, const float Z)/* overload */;
	void __fastcall LineTo3D(const TPoint3D &P)/* overload */;
	virtual void __fastcall Pie3D(int XCenter, int YCenter, int XRadius, int YRadius, int Z0, int Z1, const double StartAngle, const double EndAngle, bool DarkSides, bool DrawSides, int DonutPercent = 0x0, TCustomTeeGradient* Gradient = (TCustomTeeGradient*)(0x0), int BevelPercent = 0x0, TEdgeStyle EdgeStyle = (TEdgeStyle)(0x2), TTeeTransparency Transparency = (TTeeTransparency)(0x0), int BevelBright = 0x0, bool BevelBorder = true, bool HideSides = false) = 0 ;
	virtual void __fastcall Plane3D(const System::Types::TPointF &A, const System::Types::TPointF &B, int Z0, int Z1) = 0 ;
	void __fastcall PlaneWithZ(const TFourPoints &P, int Z)/* overload */;
	virtual void __fastcall PlaneWithZ(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, const System::Types::TPointF &P4, int Z) = 0 /* overload */;
	virtual void __fastcall PlaneFour3D(TFourPoints &Points, int Z0, int Z1) = 0 ;
	virtual void __fastcall Polygon3D(const TPoint3D *Points, const int Points_High) = 0 /* overload */;
	virtual void __fastcall Polygon3DConcave(const TPoint3D *Points, const int Points_High, const bool Invert = false)/* overload */;
	virtual void __fastcall PolygonWithZ(const System::Types::TPointF *Points, const int Points_High, int Z);
	HIDESBASE virtual void __fastcall PolygonConcave(const System::Types::TPointF *Points, const int Points_High, int Z)/* overload */;
	HIDESBASE virtual void __fastcall Polyline(const System::Types::TPointF *Points, const int Points_High, int Z)/* overload */;
	void __fastcall PolylineWithZ(const System::Types::TPointF *Points, const int Points_High, int Z);
	virtual void __fastcall Pyramid(bool Vertical, int Left, int Top, int Right, int Bottom, int z0, int z1, bool DarkSides = true) = 0 ;
	virtual void __fastcall PyramidTrunc(const System::Types::TRectF &R, const double StartZ, const double EndZ, const double TruncX, const double TruncZ, bool TopCover = true, bool BottomCover = true);
	HIDESBASE void __fastcall Rectangle(const System::Types::TRectF &R, int Z)/* overload */;
	HIDESBASE void __fastcall Rectangle(const float X0, const float Y0, const float X1, const float Y1, int Z)/* overload */;
	virtual void __fastcall RectangleWithZ(const System::Types::TRectF &Rect, int Z) = 0 ;
	virtual void __fastcall RectangleY(const float Left, const float Top, const float Right, const int Z0, const int Z1) = 0 ;
	virtual void __fastcall RectangleZ(const float Left, const float Top, const float Bottom, const int Z0, const int Z1) = 0 ;
	void __fastcall RotatedEllipse(int Left, int Top, int Right, int Bottom, int Z, const double Angle);
	virtual void __fastcall RotateLabel3D(int x, int y, int z, const System::UnicodeString St, double RotDegree, bool AllowHTML = false) = 0 ;
	virtual void __fastcall RoundRectWithZ(const System::Types::TRectF &R, int X, int Y, int Z);
	virtual void __fastcall Sphere(int x, int y, int z, const double Radius) = 0 /* overload */;
	HIDESBASE virtual void __fastcall StretchDraw(const System::Types::TRectF &Rect, Fmx::Graphics::TBitmap* const Graphic, const double Pos, TCanvas3DPlane Plane = (TCanvas3DPlane)(0x2))/* overload */;
	virtual void __fastcall Surface3D(TTeeCanvasSurfaceStyle Style, bool SameBrush, bool CreateCached, bool AddNormals, int NumXValues, int NumZValues, const TTeeCanvasCalcPoints CalcPoints, TTeeCachedObject* &Cached) = 0 ;
	void __fastcall TextOut3D(int x, int y, int z, const System::UnicodeString Text)/* overload */;
	virtual void __fastcall TextOut3D(int x, int y, int z, const System::UnicodeString Text, bool AllowHTML) = 0 /* overload */;
	virtual void __fastcall Triangle3D(const TTrianglePoints3D &Points, const TTriangleColors3D &Colors) = 0 ;
	void __fastcall TrianglePointsTo2D(const TTrianglePoints3D &P, /* out */ TTrianglePoints &Result);
	virtual void __fastcall Triangles(const TPoint3D *P, const int P_High, bool CreateCached, TTeeCachedObject* &Cached);
	virtual void __fastcall TriangleWithZ(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, int Z) = 0 ;
	virtual void __fastcall TriSurface(int NumTriangles, bool CreateCached, bool AddNormals, TTeeBlend* const Blend, TTeeTransparency Transparency, const TTeeCanvasTriPoints CalcPoints, TTeeCachedObject* &Cached);
	__property System::Uitypes::TAlphaColor Pixels3D[int X][int Y][int Z] = {read=GetPixel3D, write=SetPixel3D};
	__property bool Supports3DText = {read=GetSupports3DText, nodefault};
	__property TView3DOptions* View3DOptions = {read=F3DOptions, write=F3DOptions};
	__property int XCenter = {read=FXCenter, write=FXCenter, nodefault};
	__property int YCenter = {read=FYCenter, write=FYCenter, nodefault};
	__property int ZCenter = {read=FZCenter, write=FZCenter, nodefault};
public:
	/* TTeeCanvas.Destroy */ inline __fastcall virtual ~TCanvas3D() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Arc(const int Left, const int Top, const int Right, const int Bottom, const int StartX, const int StartY, const int EndX, const int EndY){ TTeeCanvas::Arc(Left, Top, Right, Bottom, StartX, StartY, EndX, EndY); }
	inline void __fastcall  Arc(const int Left, const int Top, const int Right, const int Bottom, double StartAngle, double EndAngle){ TTeeCanvas::Arc(Left, Top, Right, Bottom, StartAngle, EndAngle); }
	inline void __fastcall  Arrow(bool Filled, const double ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight){ TTeeCanvas::Arrow(Filled, ArrowPercent, FromPoint, ToPoint, ArrowWidth, ArrowHeight); }
	inline void __fastcall  RoundRect(int X1, int Y1, int X2, int Y2, int X3, int Y3){ TTeeCanvas::RoundRect(X1, Y1, X2, Y2, X3, Y3); }
	inline void __fastcall  RoundRect(const System::Types::TRectF &R, int X, int Y, TTeeCorners* const ACorners = (TTeeCorners*)(0x0)){ TTeeCanvas::RoundRect(R, X, Y, ACorners); }
	inline TPointArray __fastcall  GetArrowPoints(const float ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight){ return TTeeCanvas::GetArrowPoints(ArrowPercent, FromPoint, ToPoint, ArrowWidth, ArrowHeight); }
	inline void __fastcall  PolygonConcave(const System::Types::TPointF *Points, const int Points_High){ TTeeCanvas::PolygonConcave(Points, Points_High); }
	inline void __fastcall  Polyline(const System::Types::TPointF *Points, const int Points_High){ TTeeCanvas::Polyline(Points, Points_High); }
	inline void __fastcall  Rectangle(const System::Types::TRectF &R){ TTeeCanvas::Rectangle(R); }
	inline void __fastcall  Rectangle(const float X0, const float Y0, const float X1, const float Y1){ TTeeCanvas::Rectangle(X0, Y0, X1, Y1); }
	inline void __fastcall  StretchDraw(const System::Types::TRectF &Rect, Fmx::Graphics::TBitmap* const Graphic){ TTeeCanvas::StretchDraw(Rect, Graphic); }
	
private:
	void *__IInterface;	// System::IInterface 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IInterface; }
	#endif
	
};


typedef System::DynamicArray<System::Types::TPointF> TCirclePoints;

class PASCALIMPLEMENTATION TTeeCanvas3D : public TCanvas3D
{
	typedef TCanvas3D inherited;
	
private:
	double s1;
	double s2;
	double s3;
	double c1;
	double c2;
	double c3;
	double c2s3;
	double c2c3;
	double tempXX;
	double tempYX;
	double tempXZ;
	double tempYZ;
	bool FWas3D;
	Fmx::Graphics::TBitmap* FBitmap;
	bool FMonochrome;
	int FTextAlign;
	float FX;
	float FY;
	int IFastLine;
	bool IHasPerspec;
	bool IHasTilt;
	double IOrthoX;
	double IOrthoY;
	double IZoomPerspec;
	void __fastcall DirectTextOut(int AHandle, int x, int y, const System::UnicodeString Text);
	void __fastcall GetCirclePoints(TCirclePoints &P, const float X1, const float Y1, const float X2, const float Y2)/* overload */;
	void __fastcall InternalCylinder(bool Vertical, int Left, int Top, int Right, int Bottom, int Z0, int Z1, bool Dark3D, int ConePercent);
	void __fastcall PrepareBrush();
	
protected:
	bool FBufferedDisplay;
	bool FDirty;
	bool FIs3D;
	bool IKeepBitmap;
	TFourPoints IPoints;
	double IZoomFactor;
	double CharacterAngle;
	int XCenterOffset;
	int YCenterOffset;
	bool Pie3DUsingArcs;
	TFontQuality FontQuality;
	System::TObject* Tag;
	virtual bool __fastcall CheckFastBrush();
	virtual void __fastcall FastLineTo(const int X, const int Y);
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor();
	virtual TCanvasBackMode __fastcall GetBackMode();
	virtual bool __fastcall GetMonochrome();
	virtual System::Uitypes::TAlphaColor __fastcall GetPixel(int X, int Y);
	virtual System::Uitypes::TAlphaColor __fastcall GetPixel3D(int X, int Y, int Z);
	virtual bool __fastcall GetSupports3DText();
	virtual bool __fastcall GetSupportsFullRotation();
	virtual bool __fastcall GetSupportsXORMode();
	virtual bool __fastcall GetIsNoBMPGrid();
	virtual int __fastcall GetTextAlign();
	virtual bool __fastcall GetUseBuffer();
	virtual void __fastcall PolygonFour();
	virtual void __fastcall SetBackColor(const System::Uitypes::TAlphaColor Value);
	virtual void __fastcall SetBackMode(const TCanvasBackMode Value);
	virtual void __fastcall SetBitmap(Fmx::Graphics::TBitmap* ABitmap);
	virtual void __fastcall SetFastLine(const bool Active);
	virtual void __fastcall SetMonochrome(bool Value);
	virtual void __fastcall SetPixel(int X, int Y, System::Uitypes::TAlphaColor Value);
	virtual void __fastcall SetTextAlign(const int Value);
	virtual void __fastcall SetUseBuffer(bool Value);
	virtual void __fastcall DeleteBitmap();
	virtual void __fastcall TransferBitmap(int ALeft, int ATop, Fmx::Graphics::TCanvas* const ACanvas);
	void __fastcall Calc3DTPoint(System::Types::TPointF &P, int z);
	System::Types::TPointF __fastcall Calc3DTPoint3D(const TPoint3D &P);
	void __fastcall Calc3DPoint(/* out */ System::Types::TPointF &P, int x, int y, int z)/* overload */;
	void __fastcall Calc3DPoint(/* out */ System::Types::TPointF &P, float x, float y, float z)/* overload */;
	virtual void __fastcall SetPixel3D(int X, int Y, int Z, System::Uitypes::TAlphaColor Value);
	void __fastcall Calc3DPos(int &x, int &y, int z)/* overload */;
	void __fastcall CalcPerspective(const System::Types::TRectF &Rect);
	void __fastcall CalcTrigValues();
	virtual void __fastcall SmoothShadow(TTeeShadow* const Shadow, const System::Types::TRectF &Rect, bool Ellipse, int RoundSize, const System::Types::TPointF *P, const int P_High, int DonutPercent = 0x0, const double StartAngle = 0.000000E+00, const double EndAngle = 3.600000E+02);
	
public:
	__fastcall virtual TTeeCanvas3D();
	__fastcall virtual ~TTeeCanvas3D();
	__classmethod virtual System::UnicodeString __fastcall Description();
	virtual System::Types::TRectF __fastcall InitWindow(Fmx::Graphics::TCanvas* const DestCanvas, TView3DOptions* const A3DOptions, System::Uitypes::TAlphaColor ABackColor, bool Is3D, const System::Types::TRectF &UserRect);
	virtual bool __fastcall ReDrawBitmap();
	virtual bool __fastcall RenderToBitmap(Fmx::Graphics::TBitmap* &ABitmap, const System::Types::TRectF &R);
	virtual void __fastcall ShowImage(Fmx::Graphics::TCanvas* const DestCanvas, Fmx::Graphics::TCanvas* const DefaultCanvas, const System::Types::TRectF &UserRect);
	virtual void __fastcall Arc(const int Left, const int Top, const int Right, const int Bottom, const int StartX, const int StartY, const int EndX, const int EndY)/* overload */;
	virtual void __fastcall Donut(const System::Types::TRectF &R, const double StartAngle, const double EndAngle, const double HolePercent)/* overload */;
	virtual void __fastcall Donut(int XCenter, int YCenter, int XRadius, int YRadius, const double StartAngle, const double EndAngle, const double HolePercent)/* overload */;
	virtual void __fastcall Draw(int X, int Y, Fmx::Graphics::TBitmap* const Graphic);
	virtual void __fastcall Ellipse(const float X1, const float Y1, const float X2, const float Y2)/* overload */;
	virtual void __fastcall EraseBackground(const System::Types::TRectF &Rect);
	virtual void __fastcall FillRect(const System::Types::TRectF &Rect);
	virtual void __fastcall LineTo(const float X, const float Y)/* overload */;
	virtual void __fastcall MoveTo(const float X, const float Y)/* overload */;
	virtual void __fastcall Pie(const System::Types::TRectF &R, const double StartAngle, const double EndAngle)/* overload */;
	virtual void __fastcall Pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4)/* overload */;
	virtual void __fastcall Rectangle(const float X0, const float Y0, const float X1, const float Y1)/* overload */;
	virtual void __fastcall RoundRect(int X1, int Y1, int X2, int Y2, int X3, int Y3)/* overload */;
	virtual void __fastcall StretchDraw(const System::Types::TRectF &ARect, Fmx::Graphics::TBitmap* const Graphic)/* overload */;
	virtual void __fastcall TextOut(const float X, const float Y, const System::UnicodeString Text)/* overload */;
	virtual void __fastcall ClipRectangle(const System::Types::TRectF &Rect)/* overload */;
	virtual void __fastcall ClipCube(const System::Types::TRectF &Rect, int MinZ, int MaxZ);
	virtual void __fastcall DisableRotation();
	virtual void __fastcall EnableRotation();
	HIDESBASE void __fastcall GradientFill(TCustomTeeGradient* const Gradient, const System::Types::TRectF &Rect)/* overload */;
	virtual void __fastcall GradientFill(const System::Types::TRectF &Rect, System::Uitypes::TAlphaColor StartColor, System::Uitypes::TAlphaColor EndColor, TGradientDirection Direction, int Balance = 0x32, int RadialX = 0x0, int RadialY = 0x0)/* overload */;
	virtual void __fastcall Invalidate();
	virtual void __fastcall Polyline(const System::Types::TPointF *Points, const int Points_High)/* overload */;
	virtual void __fastcall Polygon(const System::Types::TPointF *Points, const int Points_High);
	virtual void __fastcall RotateLabel(int x, int y, const System::UnicodeString St, double RotDegree, bool AllowHTML = false);
	virtual void __fastcall RotateLabel3D(int x, int y, int z, const System::UnicodeString St, double RotDegree, bool AllowHTML = false);
	virtual void __fastcall UnClipRectangle();
	virtual void __fastcall Calculate2DPosition(int &x, int &y, int z)/* overload */;
	virtual System::Types::TPointF __fastcall Calculate3DPosition(int x, int y, int z)/* overload */;
	virtual System::Types::TPointF __fastcall Calculate3DPosition(const float x, const float y, const float z)/* overload */;
	virtual void __fastcall Projection(int MaxDepth, const System::Types::TRectF &ABounds, const System::Types::TRectF &Rect);
	virtual void __fastcall Arrow(bool Filled, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight, int Z0, int Z1, const double ArrowPercent)/* overload */;
	virtual void __fastcall Cone(bool Vertical, int Left, int Top, int Right, int Bottom, int Z0, int Z1, bool Dark3D, int ConePercent);
	virtual void __fastcall Cube(int Left, int Right, int Top, int Bottom, int Z0, int Z1, int BevelSize, bool DarkSides = true, int RoundSize = 0x0)/* overload */;
	virtual void __fastcall Cube(int Left, int Right, int Top, int Bottom, int Z0, int Z1, bool DarkSides = true, int RoundSize = 0x0)/* overload */;
	virtual void __fastcall Cylinder(bool Vertical, int Left, int Top, int Right, int Bottom, int Z0, int Z1, bool Dark3D = true);
	virtual void __fastcall EllipseWithZ(const float X1, const float Y1, const float X2, const float Y2, const int Z)/* overload */;
	void __fastcall GetCirclePoints(TCirclePoints &P, int X1, int Y1, int X2, int Y2, int Z)/* overload */;
	virtual void __fastcall RectangleZ(const float Left, const float Top, const float Bottom, const int Z0, const int Z1);
	virtual void __fastcall RectangleY(const float Left, const float Top, const float Right, const int Z0, const int Z1);
	virtual void __fastcall Pie3D(int XCenter, int YCenter, int XRadius, int YRadius, int Z0, int Z1, const double StartAngle, const double EndAngle, bool DarkSides, bool DrawSides, int DonutPercent = 0x0, TCustomTeeGradient* Gradient = (TCustomTeeGradient*)(0x0), int BevelPercent = 0x0, TEdgeStyle EdgeStyle = (TEdgeStyle)(0x2), TTeeTransparency Transparency = (TTeeTransparency)(0x0), int BevelBright = 0x0, bool BevelBorder = true, bool HideSides = false);
	virtual void __fastcall Plane3D(const System::Types::TPointF &A, const System::Types::TPointF &B, int Z0, int Z1);
	virtual void __fastcall PlaneWithZ(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, const System::Types::TPointF &P4, int Z)/* overload */;
	virtual void __fastcall PlaneFour3D(TFourPoints &Points, int Z0, int Z1);
	virtual void __fastcall Polygon3D(const TPoint3D *Points, const int Points_High)/* overload */;
	virtual void __fastcall Pyramid(bool Vertical, int Left, int Top, int Right, int Bottom, int z0, int z1, bool DarkSides = true);
	virtual void __fastcall RectangleWithZ(const System::Types::TRectF &Rect, int Z);
	virtual void __fastcall Sphere(int x, int y, int z, const double Radius)/* overload */;
	virtual void __fastcall Surface3D(TTeeCanvasSurfaceStyle Style, bool SameBrush, bool CreateCached, bool AddNormals, int NumXValues, int NumZValues, const TTeeCanvasCalcPoints CalcPoints, TTeeCachedObject* &Cached);
	virtual void __fastcall TextOut3D(int x, int y, int z, const System::UnicodeString Text, bool AllowHtml)/* overload */;
	virtual void __fastcall Triangle3D(const TTrianglePoints3D &Points, const TTriangleColors3D &Colors);
	virtual void __fastcall TriangleWithZ(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, int Z);
	__property Fmx::Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Arc(const int Left, const int Top, const int Right, const int Bottom, const int StartX, const int StartY, const int EndX, const int EndY, const int Z){ TCanvas3D::Arc(Left, Top, Right, Bottom, StartX, StartY, EndX, EndY, Z); }
	inline void __fastcall  Arc(const int Left, const int Top, const int Right, const int Bottom, double StartAngle, double EndAngle){ TTeeCanvas::Arc(Left, Top, Right, Bottom, StartAngle, EndAngle); }
	inline void __fastcall  Ellipse(const System::Types::TRectF &R){ TTeeCanvas::Ellipse(R); }
	inline void __fastcall  LineTo(const System::Types::TPointF &P){ TTeeCanvas::LineTo(P); }
	inline void __fastcall  MoveTo(const System::Types::TPointF &P){ TTeeCanvas::MoveTo(P); }
	inline void __fastcall  Rectangle(const System::Types::TRectF &R, int Z){ TCanvas3D::Rectangle(R, Z); }
	inline void __fastcall  Rectangle(const float X0, const float Y0, const float X1, const float Y1, int Z){ TCanvas3D::Rectangle(X0, Y0, X1, Y1, Z); }
	inline void __fastcall  Rectangle(const System::Types::TRectF &R){ TTeeCanvas::Rectangle(R); }
	inline void __fastcall  RoundRect(const System::Types::TRectF &R, int X, int Y, int Z0, int Z1){ TCanvas3D::RoundRect(R, X, Y, Z0, Z1); }
	inline void __fastcall  RoundRect(const System::Types::TRectF &R, int X, int Y, TTeeCorners* const ACorners = (TTeeCorners*)(0x0)){ TTeeCanvas::RoundRect(R, X, Y, ACorners); }
	inline void __fastcall  StretchDraw(const System::Types::TRectF &Rect, Fmx::Graphics::TBitmap* const Graphic, const double Pos, TCanvas3DPlane Plane = (TCanvas3DPlane)(0x2)){ TCanvas3D::StretchDraw(Rect, Graphic, Pos, Plane); }
	inline void __fastcall  TextOut(const float X, const float Y, const System::UnicodeString Text, bool AllowHtml){ TTeeCanvas::TextOut(X, Y, Text, AllowHtml); }
	inline void __fastcall  ClipRectangle(const System::Types::TRectF &Rect, int RoundX, int RoundY){ TTeeCanvas::ClipRectangle(Rect, RoundX, RoundY); }
	inline void __fastcall  Polyline(const System::Types::TPointF *Points, const int Points_High, int Z){ TCanvas3D::Polyline(Points, Points_High, Z); }
	inline System::Types::TPointF __fastcall  Calculate3DPosition(const TPoint3D &P){ return TCanvas3D::Calculate3DPosition(P); }
	inline System::Types::TPointF __fastcall  Calculate3DPosition(const System::Types::TPointF &P, int z){ return TCanvas3D::Calculate3DPosition(P, z); }
	inline void __fastcall  Arrow(bool Filled, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight, int Z){ TCanvas3D::Arrow(Filled, FromPoint, ToPoint, ArrowWidth, ArrowHeight, Z); }
	inline void __fastcall  Arrow(bool Filled, const double ArrowPercent, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, int ArrowWidth, int ArrowHeight){ TTeeCanvas::Arrow(Filled, ArrowPercent, FromPoint, ToPoint, ArrowWidth, ArrowHeight); }
	inline void __fastcall  Cube(const System::Types::TRectF &R, int Z0, int Z1, bool DarkSides = true, int RoundSize = 0x0){ TCanvas3D::Cube(R, Z0, Z1, DarkSides, RoundSize); }
	inline void __fastcall  EllipseWithZ(const System::Types::TRectF &Rect, int Z){ TCanvas3D::EllipseWithZ(Rect, Z); }
	inline void __fastcall  PlaneWithZ(const TFourPoints &P, int Z){ TCanvas3D::PlaneWithZ(P, Z); }
	inline void __fastcall  TextOut3D(int x, int y, int z, const System::UnicodeString Text){ TCanvas3D::TextOut3D(x, y, z, Text); }
	
};


class PASCALIMPLEMENTATION TTeeNeutralCanvas : public TTeeCanvas3D
{
	typedef TTeeCanvas3D inherited;
	
	
private:
	typedef System::DynamicArray<float> _TTeeNeutralCanvas__1;
	
	
private:
	System::Uitypes::TAlphaColor FBackColor;
	TCanvasBackMode FBackMode;
	int FTextAlign;
	_TTeeNeutralCanvas__1 ITranspStack;
	
protected:
	float ITransp;
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor();
	virtual TCanvasBackMode __fastcall GetBackMode();
	virtual int __fastcall GetTextAlign();
	virtual void __fastcall SetBackColor(const System::Uitypes::TAlphaColor Value);
	virtual void __fastcall SetBackMode(const TCanvasBackMode Value);
	virtual void __fastcall SetInterCharSize(int ASize);
	virtual void __fastcall SetPenMode(TTeePen* const APen);
	virtual void __fastcall SetTextAlign(const int Value);
	
public:
	__fastcall virtual TTeeNeutralCanvas();
	virtual TTeeBlend* __fastcall BeginBlending(const System::Types::TRectF &R, TTeeTransparency Transparency);
	virtual void __fastcall ClipPolygon(const System::Types::TPointF *Points, const int Points_High, int NumPoints, bool DiffRegion = false);
	virtual void __fastcall EndBlending(TTeeBlend* const Blend);
	virtual void __fastcall Polyline(const System::Types::TPointF *Points, const int Points_High)/* overload */;
public:
	/* TTeeCanvas3D.Destroy */ inline __fastcall virtual ~TTeeNeutralCanvas() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Polyline(const System::Types::TPointF *Points, const int Points_High, int Z){ TCanvas3D::Polyline(Points, Points_High, Z); }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TCanvas3DClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TCanvas3DClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TTeeFontStyle : unsigned char { fsNormal, fsOutline, fsBitmap };

enum DECLSPEC_DENUM TSmoothStretchOption : unsigned char { ssBestQuality, ssBestPerformance };

__interface  INTERFACE_UUID("{84DBB276-CBD2-4BBB-AC31-AACBF8B6F34C}") ICanvasHyperlinks  : public System::IInterface 
{
	virtual void __fastcall AddLink(int x, int y, const System::UnicodeString Text, const System::UnicodeString URL, const System::UnicodeString Hint) = 0 ;
};

__interface  INTERFACE_UUID("{03EBCB55-D01F-4CA8-8A2F-48EB3BEBC5E3}") ICanvasToolTips  : public System::IInterface 
{
	virtual void __fastcall AddToolTip(const System::UnicodeString Entity, const System::UnicodeString ToolTip) = 0 ;
};

typedef NativeInt TeeNativeInt;

typedef TVisualBlock* __fastcall (*TChangeVisual)(System::Classes::TComponent* AOwner, System::Classes::TComponent* AVisualOwner, TVisualBlock* AVisual);

typedef bool __fastcall (*TEditVisual)(System::Classes::TComponent* AOwner, TVisualBlock* AVisual);

typedef void __fastcall (*TTeeAddFontNames)(System::Classes::TStrings* const Items);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 TeeDefaultPerspective = System::Int8(0xf);
static const System::Word TeeMinAngle = System::Word(0x10e);
static const System::Int8 TeeCheckBoxSize = System::Int8(0xb);
extern DELPHI_PACKAGE System::Types::TRectF TeeZeroRect;
extern DELPHI_PACKAGE System::Types::TRectF TeeZeroRectF;
extern DELPHI_PACKAGE System::Types::TPointF TeeZeroPoint;
#define TeeFontElektra L"Elektra"
#define TeeFontDigital L"DS-Digital"
extern DELPHI_PACKAGE int TeeDefaultConePercent;
extern DELPHI_PACKAGE int NumCirclePoints;
extern DELPHI_PACKAGE bool TeeCheckPenWidth;
static const Fmx::Graphics::TBrushKind bsSolid = (Fmx::Graphics::TBrushKind)(1);
static const Fmx::Graphics::TBrushKind bsClear = (Fmx::Graphics::TBrushKind)(0);
static const unsigned clDkGray = unsigned(0xffa9a9a9);
static const unsigned clNone = unsigned(0x0);
static const System::Uitypes::TAlphaColor clDefault = System::Uitypes::TAlphaColor(0xffffff);
static const System::Int8 pf32Bit = System::Int8(0x0);
static const System::WideChar TeeCharForHeight = (System::WideChar)(0x57);
extern DELPHI_PACKAGE System::Byte DarkerColorQuantity;
extern DELPHI_PACKAGE System::Byte DarkColorQuantity;
extern DELPHI_PACKAGE int GetDefaultFontSize;
extern DELPHI_PACKAGE System::UnicodeString GetDefaultFontName;
static const System::Int8 TeePixelFormat = System::Int8(0x0);
extern DELPHI_PACKAGE int TeeNumCylinderSides;
extern DELPHI_PACKAGE TChangeVisual TeeOnChangeVisual;
extern DELPHI_PACKAGE TEditVisual TeeOnEditVisual;
extern DELPHI_PACKAGE System::Classes::TList* TeeRenderClasses;
extern DELPHI_PACKAGE TTeeAddFontNames TeeAddFontNames;
extern DELPHI_PACKAGE System::Classes::TStrings* TeeCustomEditColors;
extern DELPHI_PACKAGE bool __fastcall EqualRect(const System::Types::TRectF &A, const System::Types::TRectF &B);
extern DELPHI_PACKAGE void __fastcall InflateRectF(System::Types::TRectF &R, const float dX, const float dY)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TeeCull(const System::Types::TPointF &P0, const System::Types::TPointF &P1, const System::Types::TPointF &P2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TeeCull(const TFourPoints &P)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TeeCull(const TFourPointFloats &P)/* overload */;
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall ColorToRGB(const System::Uitypes::TAlphaColor Color);
extern DELPHI_PACKAGE TRGBA __fastcall ColorRGBA(const System::Uitypes::TAlphaColor Color);
extern DELPHI_PACKAGE System::Types::TPointF __fastcall TeePoint(const float aX, const float aY);
extern DELPHI_PACKAGE void __fastcall Offset(System::Types::TPointF &P, const float Amount);
extern DELPHI_PACKAGE bool __fastcall PointInRect(const System::Types::TRectF &Rect, const float x, const float y)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInRect(const System::Types::TRectF &Rect, int x, int y)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInRect(const System::Types::TRectF &Rect, const System::Types::TPointF &P)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall TeeRect(const float Left, const float Top, const float Right, const float Bottom)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall TeeRect(const float Width, const float Height)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsRectEmpty(const System::Types::TRectF &R);
extern DELPHI_PACKAGE System::Types::TRectF __fastcall TeeRect(const System::Types::TRectF &R)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall TeeRect(const int Left, const int Top, const int Right, const int Bottom)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall TeeRect(const int Width, const int Height)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall OrientRectangle(const System::Types::TRectF &R)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall OrientRectangle(const float Left, const float Top, const float Right, const float Bottom)/* overload */;
extern DELPHI_PACKAGE TPoint3D __fastcall Point3D(const int x, const int y, const int z)/* overload */;
extern DELPHI_PACKAGE TPoint3D __fastcall Point3D(const System::Types::TPointF &P, int z)/* overload */;
extern DELPHI_PACKAGE void __fastcall RectSize(const System::Types::TRectF &R, /* out */ int &RectWidth, /* out */ int &RectHeight)/* overload */;
extern DELPHI_PACKAGE void __fastcall RectSize(const System::Types::TRectF &R, /* out */ float &RectWidth, /* out */ float &RectHeight)/* overload */;
extern DELPHI_PACKAGE void __fastcall RectCenter(const System::Types::TRectF &R, /* out */ int &X, /* out */ int &Y)/* overload */;
extern DELPHI_PACKAGE void __fastcall RectCenter(const System::Types::TRectF &R, /* out */ float &X, /* out */ float &Y)/* overload */;
extern DELPHI_PACKAGE System::Types::TPointF __fastcall RectCenter(const System::Types::TRectF &R)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeSetBitmapSize(Fmx::Graphics::TBitmap* const Bitmap, int Width, int Height);
extern DELPHI_PACKAGE void __fastcall TeeSetBitmapDPI(Fmx::Graphics::TBitmap* const Bitmap, int DPI)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TeeSetBitmapDPI(System::Classes::TStream* const Stream, int DPI)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall PolygonBounds(const System::Types::TPointF *P, const int P_High)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PolygonInPolygon(const System::Types::TPointF *A, const int A_High, const System::Types::TPointF *B, const int B_High);
extern DELPHI_PACKAGE double __fastcall PolygonArea(const TPointArray P);
extern DELPHI_PACKAGE System::Types::TPointF __fastcall PolygonCentroid(const TPointArray P)/* overload */;
extern DELPHI_PACKAGE TRGB __fastcall RGBValue(const System::Uitypes::TAlphaColor Color);
extern DELPHI_PACKAGE void __fastcall ClipCanvas(Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &Rect);
extern DELPHI_PACKAGE void __fastcall ClipEllipse _DEPRECATED_ATTRIBUTE1("Please use ACanvas.ClipEllipse method.") (TTeeCanvas* const ACanvas, const System::Types::TRectF &Rect);
extern DELPHI_PACKAGE void __fastcall ClipRoundRectangle _DEPRECATED_ATTRIBUTE1("Please use ACanvas.ClipRectangle method.") (TTeeCanvas* const ACanvas, const System::Types::TRectF &Rect, int RoundSize);
extern DELPHI_PACKAGE void __fastcall ClipPolygon _DEPRECATED_ATTRIBUTE1("Please use ACanvas.ClipPolygon method.") (TTeeCanvas* const ACanvas, const System::Types::TPointF *Points, const int Points_High, int NumPoints);
extern DELPHI_PACKAGE System::Types::TRectF __fastcall RectFromPolygon(const System::Types::TPointF *Points, const int Points_High, int NumPoints);
extern DELPHI_PACKAGE System::Types::TRectF __fastcall RectFromTriangle(const TTrianglePoints &Points);
extern DELPHI_PACKAGE bool __fastcall RectangleInRectangle(const System::Types::TRectF &Small, const System::Types::TRectF &Big);
extern DELPHI_PACKAGE float __fastcall TeeHypot(const int X, const int Y)/* overload */;
extern DELPHI_PACKAGE float __fastcall TeeHypot(const float X, const float Y)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnClipCanvas(Fmx::Graphics::TCanvas* const ACanvas);
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall RGBA(const TRGBA RGBA)/* overload */;
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall RGBA(const int r, const int g, const int b, const int a)/* overload */;
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall ApplyDark(System::Uitypes::TAlphaColor Color, System::Byte HowMuch);
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall ApplyBright(System::Uitypes::TAlphaColor Color, System::Byte HowMuch);
extern DELPHI_PACKAGE int __fastcall TeeGetDeviceCaps(int Handle, int Cap);
extern DELPHI_PACKAGE int __fastcall TeeBitsperPixel(int AHandle);
extern DELPHI_PACKAGE void __fastcall TeeCalcLines(/* out */ TRGBAArray &Lines, Fmx::Graphics::TBitmap* Bitmap)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeShadowSmooth(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Back, int Left, int Top, int Width, int Height, int BlurSize, const float Smoothness, TCanvas3D* ACanvas, bool Clip);
extern DELPHI_PACKAGE void __fastcall SwapExtended(System::Extended &a, System::Extended &b);
extern DELPHI_PACKAGE void __fastcall SwapDouble(double &a, double &b);
extern DELPHI_PACKAGE void __fastcall SwapSingle(float &a, float &b);
extern DELPHI_PACKAGE void __fastcall SwapInteger(int &a, int &b);
extern DELPHI_PACKAGE void __fastcall TeeBlendBitmaps(const double Percent, Fmx::Graphics::TBitmap* ABitmap, Fmx::Graphics::TBitmap* BBitmap, const System::Types::TPointF &BOrigin, Fmx::Graphics::TBitmap* TransparentMask = (Fmx::Graphics::TBitmap*)(0x0));
extern DELPHI_PACKAGE System::Types::TPointF __fastcall PointAtDistance(const System::Types::TPointF &AFrom, const System::Types::TPointF &ATo, const float ADist)/* overload */;
extern DELPHI_PACKAGE double __fastcall TeeDistance(const double x, const double y);
extern DELPHI_PACKAGE void __fastcall SmoothStretch(Fmx::Graphics::TBitmap* Src, Fmx::Graphics::TBitmap* Dst)/* overload */;
extern DELPHI_PACKAGE void __fastcall SmoothStretch(Fmx::Graphics::TBitmap* Src, Fmx::Graphics::TBitmap* Dst, TSmoothStretchOption Option)/* overload */;
extern DELPHI_PACKAGE System::Classes::TResourceStream* __fastcall TeeResourceStream(const System::UnicodeString AName);
extern DELPHI_PACKAGE void __fastcall TeeActivateGroup(void);
extern DELPHI_PACKAGE System::TClass __fastcall TeeGetClass(const System::UnicodeString AClassName);
extern DELPHI_PACKAGE NativeInt __fastcall ObjectToTag(System::TObject* const AObject);
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall EditColor(System::Classes::TComponent* const AOwner, System::Uitypes::TAlphaColor AColor, const TColorDialogOptions AOptions)/* overload */;
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall EditColor(System::Classes::TComponent* const AOwner, System::Uitypes::TAlphaColor AColor)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EditColorDialog(System::Classes::TComponent* const AOwner, System::Uitypes::TAlphaColor &AColor, const TColorDialogOptions AOptions = TColorDialogOptions() );
extern DELPHI_PACKAGE void __fastcall TeeDrawCheckBox(int x, int y, TTeeCanvas* const Canvas, bool Checked, System::Uitypes::TAlphaColor ABackColor, bool CheckBox = true);
}	/* namespace Canvas */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CANVAS)
using namespace Fmxtee::Canvas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_CanvasHPP
