﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Graphics.pas' rev: 34.00 (iOS)

#ifndef Fmx_GraphicsHPP
#define Fmx_GraphicsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Messaging.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Types.hpp>
#include <FMX.Surfaces.hpp>
#include <System.Math.Vectors.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Graphics
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGradientPoint;
class DELPHICLASS TGradientPoints;
struct TGradientStyleHelper /* Helper for enum 'TGradientStyle' */;
class DELPHICLASS TGradient;
class DELPHICLASS TBrushResource;
struct TWrapModeHelper /* Helper for enum 'TWrapMode' */;
class DELPHICLASS TBrushBitmap;
struct TBrushKindHelper /* Helper for enum 'TBrushKind' */;
class DELPHICLASS TBrush;
struct TStrokeCapHelper /* Helper for enum 'TStrokeCap' */;
struct TStrokeJoinHelper /* Helper for enum 'TStrokeJoin' */;
struct TStrokeDashHelper /* Helper for enum 'TStrokeDash' */;
class DELPHICLASS TStrokeBrush;
__interface DELPHIINTERFACE IFMXSystemFontService;
typedef System::DelphiInterface<IFMXSystemFontService> _di_IFMXSystemFontService;
struct TFontWeightHelper /* Helper for enum 'TFontWeight' */;
struct TFontSlantHelper /* Helper for enum 'TFontSlant' */;
struct TFontStretchHelper /* Helper for enum 'TFontStretch' */;
struct TFontStyleExt;
class DELPHICLASS TFont;
struct TBitmapCodecSaveParams;
class DELPHICLASS TCustomBitmapCodec;
class DELPHICLASS EBitmapCodecManagerException;
class DELPHICLASS TBitmapCodecManager;
class DELPHICLASS TImageTypeChecker;
__interface DELPHIINTERFACE IBitmapObject;
typedef System::DelphiInterface<IBitmapObject> _di_IBitmapObject;
struct TBitmapData;
struct TMapAccessHelper /* Helper for enum 'TMapAccess' */;
class DELPHICLASS TBitmapImage;
class DELPHICLASS TBitmap;
__interface DELPHIINTERFACE IPathObject;
typedef System::DelphiInterface<IPathObject> _di_IPathObject;
struct TPathPointKindHelper /* Helper for enum 'TPathPointKind' */;
struct TPathPoint;
class DELPHICLASS TPathData;
class DELPHICLASS TCanvasSaveState;
class DELPHICLASS ECanvasException;
struct TFillTextFlagHelper /* Helper for enum 'TFillTextFlag' */;
class DELPHICLASS TAbstractPrinter;
__interface DELPHIINTERFACE ICanvasObject;
typedef System::DelphiInterface<ICanvasObject> _di_ICanvasObject;
__interface DELPHIINTERFACE IModulateCanvas;
typedef System::DelphiInterface<IModulateCanvas> _di_IModulateCanvas;
struct TCanvasQualityHelper /* Helper for enum 'TCanvasQuality' */;
class DELPHICLASS TCanvas;
class DELPHICLASS ECanvasManagerException;
class DELPHICLASS TCanvasDestroyMessage;
class DELPHICLASS TCanvasManager;
class DELPHICLASS TPrinterCanvas;
__interface DELPHIINTERFACE IBrushObject;
typedef System::DelphiInterface<IBrushObject> _di_IBrushObject;
class DELPHICLASS TBrushObject;
__interface DELPHIINTERFACE IFontObject;
typedef System::DelphiInterface<IFontObject> _di_IFontObject;
class DELPHICLASS TFontObject;
class DELPHICLASS TPathObject;
class DELPHICLASS TBitmapObject;
class DELPHICLASS TColorObject;
class DELPHICLASS TFontColorForState;
class DELPHICLASS TTextSettings;
__interface DELPHIINTERFACE ITextSettings;
typedef System::DelphiInterface<ITextSettings> _di_ITextSettings;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TCanvasClass);

class PASCALIMPLEMENTATION TGradientPoint : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	float FOffset;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetOffset(const float Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Uitypes::TAlphaColor IntColor = {read=FColor, write=FColor, nodefault};
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, nodefault};
	__property float Offset = {read=FOffset, write=SetOffset};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TGradientPoint(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TGradientPoint() { }
	
};


class PASCALIMPLEMENTATION TGradientPoints : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TGradientPoint* operator[](int Index) { return this->Points[Index]; }
	
private:
	TGradientPoint* __fastcall GetPoint(int Index);
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__property TGradientPoint* Points[int Index] = {read=GetPoint/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TGradientPoints(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TGradientPoints() { }
	
};


enum class DECLSPEC_DENUM TGradientStyle : unsigned int { Linear, Radial, gsLinear _DEPRECATED_ATTRIBUTE3("Use TGradientStyle.Linear")  = 0x0, gsRadial _DEPRECATED_ATTRIBUTE3("Use TGradientStyle.Radial")  = 0x1 };

class PASCALIMPLEMENTATION TGradient : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TGradientPoints* FPoints;
	System::Classes::TNotifyEvent FOnChanged;
	Fmx::Types::TPosition* FStartPosition;
	Fmx::Types::TPosition* FStopPosition;
	TGradientStyle FStyle;
	Fmx::Types::TTransform* FRadialTransform;
	void __fastcall SetStartPosition(Fmx::Types::TPosition* const Value);
	void __fastcall SetStopPosition(Fmx::Types::TPosition* const Value);
	void __fastcall PositionChanged(System::TObject* Sender);
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetColor1(const System::Uitypes::TAlphaColor Value);
	bool __fastcall IsLinearStored();
	void __fastcall SetStyle(const TGradientStyle Value);
	bool __fastcall IsRadialStored();
	void __fastcall SetRadialTransform(Fmx::Types::TTransform* const Value);
	void __fastcall SetPoints(TGradientPoints* const Value);
	
public:
	__fastcall TGradient();
	__fastcall virtual ~TGradient();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Change();
	void __fastcall ApplyOpacity(const float AOpacity);
	System::Uitypes::TAlphaColor __fastcall InterpolateColor(float Offset)/* overload */;
	System::Uitypes::TAlphaColor __fastcall InterpolateColor(float X, float Y)/* overload */;
	bool __fastcall Equal(TGradient* const AGradient);
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	__property System::Uitypes::TAlphaColor Color = {write=SetColor, nodefault};
	__property System::Uitypes::TAlphaColor Color1 = {write=SetColor1, nodefault};
	
__published:
	__property TGradientPoints* Points = {read=FPoints, write=SetPoints};
	__property TGradientStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Fmx::Types::TPosition* StartPosition = {read=FStartPosition, write=SetStartPosition, stored=IsLinearStored};
	__property Fmx::Types::TPosition* StopPosition = {read=FStopPosition, write=SetStopPosition, stored=IsLinearStored};
	__property Fmx::Types::TTransform* RadialTransform = {read=FRadialTransform, write=SetRadialTransform, stored=IsRadialStored};
};


class PASCALIMPLEMENTATION TBrushResource : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
private:
	TBrushObject* FStyleResource;
	System::UnicodeString FStyleLookup;
	System::Classes::TNotifyEvent FOnChanged;
	TBrush* __fastcall GetBrush();
	void __fastcall SetStyleResource(TBrushObject* const Value);
	System::UnicodeString __fastcall GetStyleLookup();
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	void __fastcall FreeNotification(System::TObject* AObject);
	
public:
	__fastcall virtual ~TBrushResource();
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property TBrush* Brush = {read=GetBrush};
	
__published:
	__property TBrushObject* StyleResource = {read=FStyleResource, write=SetStyleResource, stored=false};
	__property System::UnicodeString StyleLookup = {read=GetStyleLookup, write=SetStyleLookup};
public:
	/* TObject.Create */ inline __fastcall TBrushResource() : System::Classes::TInterfacedPersistent() { }
	
private:
	void *__IFreeNotification;	// Fmx::Types::IFreeNotification 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FEB50EAF-A3B9-4B37-8EDB-1EF9EE2F22D4}
	operator Fmx::Types::_di_IFreeNotification()
	{
		Fmx::Types::_di_IFreeNotification intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IFreeNotification*(void) { return (Fmx::Types::IFreeNotification*)&__IFreeNotification; }
	#endif
	
};


enum class DECLSPEC_DENUM TWrapMode : unsigned int { Tile, TileOriginal, TileStretch, wmTile _DEPRECATED_ATTRIBUTE3("Use TWrapMode.Tile")  = 0x0, wmTileOriginal _DEPRECATED_ATTRIBUTE3("Use TWrapMode.TileOriginal")  = 0x1, wmTileStretch _DEPRECATED_ATTRIBUTE3("Use TWrapMode.TileStretch")  = 0x2 };

class PASCALIMPLEMENTATION TBrushBitmap : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
private:
	System::Classes::TNotifyEvent FOnChanged;
	TBitmap* FBitmap;
	TWrapMode FWrapMode;
	void __fastcall SetWrapMode(const TWrapMode Value);
	void __fastcall SetBitmap(TBitmap* const Value);
	TBitmapImage* __fastcall GetBitmapImage();
	
protected:
	virtual void __fastcall DoChanged();
	
public:
	__fastcall TBrushBitmap();
	__fastcall virtual ~TBrushBitmap();
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property TBitmapImage* Image = {read=GetBitmapImage};
	__property TWrapMode WrapMode = {read=FWrapMode, write=SetWrapMode, nodefault};
};


enum class DECLSPEC_DENUM TBrushKind : unsigned int { None, Solid, Gradient, Bitmap, Resource, bkNone _DEPRECATED_ATTRIBUTE3("Use TBrushKind.None")  = 0, bkSolid _DEPRECATED_ATTRIBUTE3("Use TBrushKind.Solid")  = 1, bkGradient _DEPRECATED_ATTRIBUTE3("Use TBrushKind.Gradient")  = 2, bkBitmap _DEPRECATED_ATTRIBUTE3("Use TBrushKind.Bitmap")  = 3, bkResource _DEPRECATED_ATTRIBUTE3("Use TBrushKind.Resource")  = 4 };

class PASCALIMPLEMENTATION TBrush : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	TBrushKind FKind;
	System::Classes::TNotifyEvent FOnChanged;
	TGradient* FGradient;
	TBrushKind FDefaultKind;
	System::Uitypes::TAlphaColor FDefaultColor;
	TBrushResource* FResource;
	TBrushBitmap* FBitmap;
	System::Classes::TNotifyEvent FOnGradientChanged;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetKind(const TBrushKind Value);
	void __fastcall SetGradient(TGradient* const Value);
	bool __fastcall IsColorStored();
	bool __fastcall IsGradientStored();
	System::Uitypes::TAlphaColor __fastcall GetColor();
	bool __fastcall IsKindStored();
	void __fastcall SetResource(TBrushResource* const Value);
	bool __fastcall IsResourceStored();
	bool __fastcall IsBitmapStored();
	
protected:
	void __fastcall GradientChanged(System::TObject* Sender);
	void __fastcall ResourceChanged(System::TObject* Sender);
	void __fastcall BitmapChanged(System::TObject* Sender);
	
public:
	__fastcall TBrush(const TBrushKind ADefaultKind, const System::Uitypes::TAlphaColor ADefaultColor);
	__fastcall virtual ~TBrush();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	__property System::Classes::TNotifyEvent OnGradientChanged = {read=FOnGradientChanged, write=FOnGradientChanged};
	__property System::Uitypes::TAlphaColor DefaultColor = {read=FDefaultColor, write=FDefaultColor, nodefault};
	__property TBrushKind DefaultKind = {read=FDefaultKind, write=FDefaultKind, nodefault};
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, stored=IsColorStored, nodefault};
	__property TBrushBitmap* Bitmap = {read=FBitmap, write=FBitmap, stored=IsBitmapStored};
	__property TBrushKind Kind = {read=FKind, write=SetKind, stored=IsKindStored, nodefault};
	__property TGradient* Gradient = {read=FGradient, write=SetGradient, stored=IsGradientStored};
	__property TBrushResource* Resource = {read=FResource, write=SetResource, stored=IsResourceStored};
};


enum class DECLSPEC_DENUM TStrokeCap : unsigned int { Flat, Round, scFlat _DEPRECATED_ATTRIBUTE3("Use TStrokeCap.Flat")  = 0x0, scRound _DEPRECATED_ATTRIBUTE3("Use TStrokeCap.Round")  = 0x1 };

enum class DECLSPEC_DENUM TStrokeJoin : unsigned int { Miter, Round, Bevel, sjMiter _DEPRECATED_ATTRIBUTE3("Use TStrokeJoin.Miter")  = 0x0, sjRound _DEPRECATED_ATTRIBUTE3("Use TStrokeJoin.Round")  = 0x1, sjBevel _DEPRECATED_ATTRIBUTE3("Use TStrokeJoin.Bevel")  = 0x2 };

enum class DECLSPEC_DENUM TStrokeDash : unsigned int { Solid, Dash, Dot, DashDot, DashDotDot, Custom, sdSolid _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.Solid")  = 0, sdDash _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.Dash")  = 1, sdDot _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.Dot")  = 2, sdDashDot _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.DashDot")  = 3, sdDashDotDot _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.DashDotDot")  = 4, sdCustom _DEPRECATED_ATTRIBUTE3("Use TStrokeDash.Custom")  = 5 };

typedef System::TArray__1<float> TDashArray;

class PASCALIMPLEMENTATION TStrokeBrush : public TBrush
{
	typedef TBrush inherited;
	
	
public:
	struct DECLSPEC_DRECORD TDashData
	{
	public:
		System::TArray__1<float> DashArray;
		float DashOffset;
		__fastcall TDashData(const System::TArray__1<float> ADashArray, float ADashOffset);
		TDashData() {}
	};
	
	
	enum class DECLSPEC_DENUM TDashDevice : unsigned int { Screen, Printer, ddScreen _DEPRECATED_ATTRIBUTE3("Use TDashDevice.Screen")  = 0x0, ddPrinter _DEPRECATED_ATTRIBUTE3("Use TDashDevice.Printer")  = 0x1 };
	
	struct TDashDeviceHelper /* Helper for enum 'TDashDevice' */;
	typedef System::StaticArray<System::StaticArray<TDashData, 6>, 2> TStdDashes;
	
	
private:
	static TStdDashes FStdDash;
	static bool FStdDashCreated;
	TStrokeJoin FJoin;
	float FThickness;
	TStrokeCap FCap;
	TStrokeDash FDash;
	System::TArray__1<float> FDashArray;
	float FDashOffset;
	bool __fastcall IsThicknessStored();
	void __fastcall SetCap(const TStrokeCap Value);
	void __fastcall SetDash(const TStrokeDash Value);
	void __fastcall SetJoin(const TStrokeJoin Value);
	void __fastcall SetThickness(const float Value);
	System::TArray__1<float> __fastcall GetDashArray();
	static TDashData __fastcall GetStdDash(const TDashDevice Device, const TStrokeDash Dash);
	void __fastcall ReadCustomDash(System::Classes::TStream* AStream);
	void __fastcall WriteCustomDash(System::Classes::TStream* AStream);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall TStrokeBrush(const TBrushKind ADefaultKind, const System::Uitypes::TAlphaColor ADefaultColor);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall SetCustomDash(const float *Dash, const int Dash_High, float Offset);
	__property System::TArray__1<float> DashArray = {read=GetDashArray};
	__property float DashOffset = {read=FDashOffset};
	/* static */ __property TDashData StdDash[const TDashDevice Device][const TStrokeDash Dash] = {read=GetStdDash};
	
__published:
	__property float Thickness = {read=FThickness, write=SetThickness, stored=IsThicknessStored};
	__property TStrokeCap Cap = {read=FCap, write=SetCap, default=0};
	__property TStrokeDash Dash = {read=FDash, write=SetDash, default=0};
	__property TStrokeJoin Join = {read=FJoin, write=SetJoin, default=0};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TBrush.Destroy */ inline __fastcall virtual ~TStrokeBrush() { }
	
};


__interface  INTERFACE_UUID("{62017F22-ADF1-44D9-A21D-796D8C7F3CF0}") IFMXSystemFontService  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetDefaultFontFamilyName() = 0 ;
	virtual float __fastcall GetDefaultFontSize() = 0 ;
};

_DECLARE_METACLASS(System::TMetaClass, TFontClass);

enum class DECLSPEC_DENUM TFontWeight : unsigned int { Thin, UltraLight, Light, SemiLight, Regular, Medium, Semibold, Bold, UltraBold, Black, UltraBlack };

enum class DECLSPEC_DENUM TFontSlant : unsigned int { Regular, Italic, Oblique };

enum class DECLSPEC_DENUM TFontStretch : unsigned int { UltraCondensed, ExtraCondensed, Condensed, SemiCondensed, Regular, SemiExpanded, Expanded, ExtraExpanded, UltraExpanded };

struct DECLSPEC_DRECORD TFontStyleExt
{
public:
	System::Uitypes::TFontStyles SimpleStyle;
	TFontWeight Weight;
	TFontSlant Slant;
	TFontStretch Stretch;
	static TFontStyleExt __fastcall Create(const TFontWeight AWeight = (TFontWeight)(0x4), const TFontSlant AStant = (TFontSlant)(0x0), const TFontStretch AStretch = (TFontStretch)(0x4), const System::Uitypes::TFontStyles AOtherStyles = System::Uitypes::TFontStyles() )/* overload */;
	static TFontStyleExt __fastcall Create(const System::Uitypes::TFontStyles AStyle)/* overload */;
	static TFontStyleExt __fastcall Default();
	static bool __fastcall _op_Equality(const TFontStyleExt &A, const TFontStyleExt &B);
	static bool __fastcall _op_Inequality(const TFontStyleExt &A, const TFontStyleExt &B);
	__fastcall operator System::Uitypes::TFontStyles();
	static TFontStyleExt __fastcall _op_Addition(const TFontStyleExt &A, const TFontStyleExt &B);
	static TFontStyleExt __fastcall _op_Addition(const TFontStyleExt &A, const System::Uitypes::TFontStyle B);
	static TFontStyleExt __fastcall _op_Addition(const TFontStyleExt &A, const System::Uitypes::TFontStyles B);
	static TFontStyleExt __fastcall _op_Subtraction(const TFontStyleExt &A, const System::Uitypes::TFontStyle B);
	static TFontStyleExt __fastcall _op_Subtraction(const TFontStyleExt &A, const System::Uitypes::TFontStyles B);
	static bool __fastcall _op_In(const System::Uitypes::TFontStyle A, const TFontStyleExt &B);
	static System::Uitypes::TFontStyles __fastcall _op_Multiply(const System::Uitypes::TFontStyles A, const TFontStyleExt &B);
	bool __fastcall IsRegular();
	
	friend bool operator ==(const TFontStyleExt &A, const TFontStyleExt &B) { return TFontStyleExt::_op_Equality(A, B); }
	friend bool operator !=(const TFontStyleExt &A, const TFontStyleExt &B) { return TFontStyleExt::_op_Inequality(A, B); }
	friend TFontStyleExt operator +(const TFontStyleExt &A, const TFontStyleExt &B) { return TFontStyleExt::_op_Addition(A, B); }
	friend TFontStyleExt operator +(const TFontStyleExt &A, const System::Uitypes::TFontStyle B) { return TFontStyleExt::_op_Addition(A, B); }
	friend TFontStyleExt operator +(const TFontStyleExt &A, const System::Uitypes::TFontStyles B) { return TFontStyleExt::_op_Addition(A, B); }
	friend TFontStyleExt operator -(const TFontStyleExt &A, const System::Uitypes::TFontStyle B) { return TFontStyleExt::_op_Subtraction(A, B); }
	friend TFontStyleExt operator -(const TFontStyleExt &A, const System::Uitypes::TFontStyles B) { return TFontStyleExt::_op_Subtraction(A, B); }
	friend System::Uitypes::TFontStyles operator *(const System::Uitypes::TFontStyles A, const TFontStyleExt &B) { return TFontStyleExt::_op_Multiply(A, B); }
};


class PASCALIMPLEMENTATION TFont : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	static float DefaultFontSize;
	#define TFont_DefaultFontFamily u"Tahoma"
	
	static float MaxFontSize;
	
public:
	static _di_IFMXSystemFontService FontService;
	
private:
	float FSize;
	System::Uitypes::TFontName FFamily;
	TFontStyleExt FStyleExt;
	bool FUpdating;
	bool FChanged;
	System::Classes::TNotifyEvent FOnChanged;
	void __fastcall SetFamily(const System::Uitypes::TFontName Value);
	void __fastcall SetSize(const float Value);
	System::Uitypes::TFontStyles __fastcall GetStyle();
	void __fastcall SetStyle(const System::Uitypes::TFontStyles Value);
	void __fastcall SetStyleExt(const TFontStyleExt &Value);
	void __fastcall ReadStyleExt(System::Classes::TStream* AStream);
	void __fastcall WriteStyleExt(System::Classes::TStream* AStream);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual System::UnicodeString __fastcall DefaultFamily();
	virtual float __fastcall DefaultSize();
	virtual void __fastcall DoChanged();
	
public:
	__fastcall TFont();
	virtual void __fastcall AfterConstruction();
	void __fastcall Change();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall SetSettings(const System::UnicodeString AFamily, const float ASize, const TFontStyleExt &AStyle);
	virtual bool __fastcall Equals(System::TObject* Obj);
	bool __fastcall IsFamilyStored();
	bool __fastcall IsSizeStored();
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	__property TFontStyleExt StyleExt = {read=FStyleExt, write=SetStyleExt};
	
__published:
	__property System::Uitypes::TFontName Family = {read=FFamily, write=SetFamily, stored=IsFamilyStored};
	__property float Size = {read=FSize, write=SetSize, stored=IsSizeStored};
	__property System::Uitypes::TFontStyles Style = {read=GetStyle, write=SetStyle, stored=false, nodefault};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFont() { }
	
};


typedef TBitmapCodecSaveParams *PBitmapCodecSaveParams;

struct DECLSPEC_DRECORD TBitmapCodecSaveParams
{
public:
	int Quality;
};


class PASCALIMPLEMENTATION TCustomBitmapCodec : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual __classmethod System::Types::TPointF __fastcall GetImageSize(const System::UnicodeString AFileName) = 0 ;
	virtual __classmethod bool __fastcall IsValid(System::Classes::TStream* const AStream) = 0 ;
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const ABitmap, const unsigned AMaxSizeLimit = (unsigned)(0x0)) = 0 ;
	virtual bool __fastcall LoadThumbnailFromFile(const System::UnicodeString AFileName, const float AFitWidth, const float AFitHeight, const bool UseEmbedded, Fmx::Surfaces::TBitmapSurface* const ABitmap) = 0 ;
	virtual bool __fastcall LoadFromStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const ABitmap, const unsigned AMaxSizeLimit = (unsigned)(0x0)) = 0 ;
	virtual bool __fastcall SaveToFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const ABitmap, const PBitmapCodecSaveParams ASaveParams = (PBitmapCodecSaveParams)(0x0)) = 0 ;
	virtual bool __fastcall SaveToStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const ABitmap, const System::UnicodeString AExtension, const PBitmapCodecSaveParams ASaveParams = (PBitmapCodecSaveParams)(0x0)) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomBitmapCodec() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomBitmapCodec() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TCustomBitmapCodecClass);

class PASCALIMPLEMENTATION EBitmapCodecManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBitmapCodecManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBitmapCodecManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBitmapCodecManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBitmapCodecManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBitmapCodecManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBitmapCodecManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBitmapCodecManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBitmapCodecManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBitmapCodecManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBitmapCodecManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBitmapCodecManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBitmapCodecManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBitmapCodecManagerException() { }
	
};


class PASCALIMPLEMENTATION TBitmapCodecManager : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	struct DECLSPEC_DRECORD TCodecDescriptor
	{
	public:
		System::UnicodeString Extension;
		System::UnicodeString Description;
		TCustomBitmapCodecClass CodecClass;
		bool CanSave;
		System::UnicodeString __fastcall ToFilterString();
	};
	
	
	
private:
	static System::Generics::Collections::TList__1<TCodecDescriptor>* FCodecsDescriptors;
	__classmethod bool __fastcall SameExtension(const System::UnicodeString ALeft, const System::UnicodeString ARight);
	__classmethod bool __fastcall FindCodecClass(const System::UnicodeString AFileExtension, TCustomBitmapCodecClass &ACodecClass);
	__classmethod bool __fastcall FindWritableCodecClass(const System::UnicodeString AFileExtension, TCustomBitmapCodecClass &ACodecClass);
	__classmethod TCustomBitmapCodecClass __fastcall GuessCodecClass(const System::UnicodeString AFileExtension);
	static System::Generics::Collections::TList__1<TCodecDescriptor>* __fastcall GetCodecsDescriptors();
	/* static */ __property System::Generics::Collections::TList__1<TCodecDescriptor>* CodecsDescriptors = {read=GetCodecsDescriptors};
	
public:
	__classmethod void __fastcall UnInitialize();
	__classmethod void __fastcall RegisterBitmapCodecClass(const System::UnicodeString AFileExtension, const System::UnicodeString ADescription, const bool ACanSave, const TCustomBitmapCodecClass ACodecClass);
	__classmethod void __fastcall UnregisterBitmapCodecClass(const System::UnicodeString AFileExtension);
	__classmethod System::UnicodeString __fastcall GetFileTypes();
	__classmethod System::UnicodeString __fastcall GetFilterString();
	__classmethod bool __fastcall CodecExists(const System::UnicodeString AFileName)/* overload */;
	__classmethod System::Types::TPointF __fastcall GetImageSize(const System::UnicodeString AFileName);
	__classmethod bool __fastcall LoadFromFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const ABitmap, const unsigned AMaxSizeLimit = (unsigned)(0x0));
	__classmethod bool __fastcall LoadThumbnailFromFile(const System::UnicodeString AFileName, const float AFitWidth, const float AFitHeight, const bool AUseEmbedded, Fmx::Surfaces::TBitmapSurface* const ABitmap);
	__classmethod bool __fastcall LoadFromStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const ABitmap, const unsigned AMaxSizeLimit = (unsigned)(0x0));
	__classmethod bool __fastcall SaveToStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const ABitmap, const System::UnicodeString AExtension, const PBitmapCodecSaveParams ASaveParams = (PBitmapCodecSaveParams)(0x0))/* overload */;
	__classmethod bool __fastcall SaveToFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const ABitmap, const PBitmapCodecSaveParams ASaveParams = (PBitmapCodecSaveParams)(0x0));
public:
	/* TObject.Create */ inline __fastcall TBitmapCodecManager() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBitmapCodecManager() { }
	
};


class PASCALIMPLEMENTATION TImageTypeChecker : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	struct DECLSPEC_DRECORD TImageData
	{
	public:
		System::UnicodeString DataType;
		int Length;
		System::StaticArray<System::Byte, 4> Header;
	};
	
	
	
public:
	__classmethod System::UnicodeString __fastcall GetType(const System::UnicodeString AFileName)/* overload */;
	__classmethod System::UnicodeString __fastcall GetType(System::Classes::TStream* const AData)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TImageTypeChecker() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TImageTypeChecker() { }
	
};


__interface  INTERFACE_UUID("{5C17D001-47C1-462F-856D-8358B7B2C842}") IBitmapObject  : public Fmx::Types::IFreeNotificationBehavior 
{
	virtual TBitmap* __fastcall GetBitmap() = 0 ;
	__property TBitmap* Bitmap = {read=GetBitmap};
};

struct DECLSPEC_DRECORD TBitmapData
{
private:
	Fmx::Types::TPixelFormat FPixelFormat;
	int FWidth;
	int FHeight;
	int __fastcall GetBytesPerPixel();
	int __fastcall GetBytesPerLine();
	
public:
	void *Data;
	int Pitch;
	__fastcall TBitmapData(const int AWidth, const int AHeight, const Fmx::Types::TPixelFormat APixelFormat);
	System::Uitypes::TAlphaColor __fastcall GetPixel(const int X, const int Y);
	void __fastcall SetPixel(const int X, const int Y, const System::Uitypes::TAlphaColor AColor);
	void __fastcall Copy(const TBitmapData &Source);
	void * __fastcall GetScanline(const int I);
	void * __fastcall GetPixelAddr(const int I, const int J);
	__property Fmx::Types::TPixelFormat PixelFormat = {read=FPixelFormat};
	__property int BytesPerPixel = {read=GetBytesPerPixel};
	__property int BytesPerLine = {read=GetBytesPerLine};
	__property int Width = {read=FWidth};
	__property int Height = {read=FHeight};
	TBitmapData() {}
};


enum class DECLSPEC_DENUM TMapAccess : unsigned int { Read, Write, ReadWrite, maRead _DEPRECATED_ATTRIBUTE3("Use TMapAccess.Read")  = 0x0, maWrite _DEPRECATED_ATTRIBUTE3("Use TMapAccess.Write")  = 0x1, maReadWrite _DEPRECATED_ATTRIBUTE3("Use TMapAccess.ReadWrite")  = 0x2 };

class PASCALIMPLEMENTATION TBitmapImage : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FRefCount;
	NativeUInt FHandle;
	TCanvasClass FCanvasClass;
	int FWidth;
	int FHeight;
	float FBitmapScale;
	Fmx::Types::TPixelFormat FPixelFormat;
	void __fastcall CreateHandle();
	void __fastcall FreeHandle();
	TCanvasClass __fastcall GetCanvasClass();
	
public:
	__fastcall TBitmapImage();
	void __fastcall IncreaseRefCount();
	void __fastcall DecreaseRefCount();
	__property int RefCount = {read=FRefCount, nodefault};
	__property TCanvasClass CanvasClass = {read=GetCanvasClass};
	__property NativeUInt Handle = {read=FHandle};
	__property float BitmapScale = {read=FBitmapScale};
	__property Fmx::Types::TPixelFormat PixelFormat = {read=FPixelFormat, nodefault};
	__property int Height = {read=FHeight, nodefault};
	__property int Width = {read=FWidth, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBitmapImage() { }
	
};


class PASCALIMPLEMENTATION TBitmap : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
private:
	TBitmapImage* FImage;
	TCanvas* FCanvas;
	bool FMapped;
	TMapAccess FMapAccess;
	System::Classes::TNotifyEvent FOnChange;
	int __fastcall GetBytesPerLine();
	int __fastcall GetBytesPerPixel();
	TCanvas* __fastcall GetCanvas();
	Fmx::Types::TPixelFormat __fastcall GetPixelFormat();
	TBitmapImage* __fastcall GetImage();
	int __fastcall GetHeight();
	int __fastcall GetWidth();
	float __fastcall GetBitmapScale();
	NativeUInt __fastcall GetHandle();
	void __fastcall SetWidth(const int Value);
	void __fastcall SetHeight(const int Value);
	void __fastcall SetBitmapScale(const float Scale);
	void __fastcall ReadBitmap(System::Classes::TStream* Stream);
	void __fastcall WriteBitmap(System::Classes::TStream* Stream);
	TCanvasClass __fastcall GetCanvasClass();
	System::Types::TRect __fastcall GetBounds();
	System::Types::TSize __fastcall GetSize();
	System::Types::TRectF __fastcall GetBoundsF();
	
protected:
	void __fastcall CreateNewReference();
	void __fastcall CopyToNewReference();
	virtual void __fastcall DestroyResources();
	virtual void __fastcall BitmapChanged();
	void __fastcall AssignFromSurface(Fmx::Surfaces::TBitmapSurface* const Source);
	virtual void __fastcall DoChange();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall ReadStyleLookup(System::Classes::TReader* Reader);
	
public:
	__fastcall virtual TBitmap()/* overload */;
	__fastcall virtual TBitmap(const int AWidth, const int AHeight)/* overload */;
	__fastcall virtual TBitmap(System::Classes::TStream* const AStream);
	__fastcall virtual TBitmap(const System::UnicodeString AFileName);
	__fastcall TBitmap(TBitmap* const Bitmap, TBitmap* const Mask);
	__fastcall virtual ~TBitmap();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall EqualsBitmap(TBitmap* const Bitmap);
	void __fastcall SetSize(const System::Types::TSize &ASize)/* overload */;
	void __fastcall SetSize(const int AWidth, const int AHeight)/* overload */;
	void __fastcall CopyFromBitmap(TBitmap* const Source)/* overload */;
	void __fastcall CopyFromBitmap(TBitmap* const Source, const System::Types::TRect &SrcRect, int DestX, int DestY)/* overload */;
	bool __fastcall IsEmpty();
	bool __fastcall HandleAllocated();
	void __fastcall FreeHandle();
	virtual void __fastcall Clear(const System::Uitypes::TAlphaColor AColor);
	void __fastcall ClearRect(const System::Types::TRectF &ARect, const System::Uitypes::TAlphaColor AColor = (System::Uitypes::TAlphaColor)(0x0));
	void __fastcall Rotate(const float Angle);
	void __fastcall Resize(const int AWidth, const int AHeight);
	void __fastcall FlipHorizontal();
	void __fastcall FlipVertical();
	void __fastcall InvertAlpha();
	void __fastcall ReplaceOpaqueColor(const System::Uitypes::TAlphaColor Color);
	System::Sysutils::PByteArray __fastcall CreateMask();
	void __fastcall ApplyMask(const System::Sysutils::PByteArray Mask, const int DstX = 0x0, const int DstY = 0x0);
	TBitmap* __fastcall CreateThumbnail(const int AWidth, const int AHeight);
	bool __fastcall Map(const TMapAccess Access, TBitmapData &Data);
	void __fastcall Unmap(TBitmapData &Data);
	void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	void __fastcall LoadThumbnailFromFile(const System::UnicodeString AFileName, const float AFitWidth, const float AFitHeight, const bool UseEmbedded = true);
	void __fastcall SaveToFile(const System::UnicodeString AFileName, const PBitmapCodecSaveParams SaveParams = (PBitmapCodecSaveParams)(0x0));
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	void __fastcall SaveToStream(System::Classes::TStream* Stream);
	__property TCanvas* Canvas = {read=GetCanvas};
	__property TCanvasClass CanvasClass = {read=GetCanvasClass};
	__property TBitmapImage* Image = {read=GetImage};
	__property NativeUInt Handle = {read=GetHandle};
	__property Fmx::Types::TPixelFormat PixelFormat = {read=GetPixelFormat, nodefault};
	__property int BytesPerPixel = {read=GetBytesPerPixel, nodefault};
	__property int BytesPerLine = {read=GetBytesPerLine, nodefault};
	__property System::Types::TRect Bounds = {read=GetBounds};
	__property System::Types::TRectF BoundsF = {read=GetBoundsF};
	__property float BitmapScale = {read=GetBitmapScale, write=SetBitmapScale};
	__property int Width = {read=GetWidth, write=SetWidth, nodefault};
	__property int Height = {read=GetHeight, write=SetHeight, nodefault};
	__property System::Types::TSize Size = {read=GetSize, write=SetSize};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
private:
	void *__IStreamPersist;	// System::Classes::IStreamPersist 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B8CD12A3-267A-11D4-83DA-00C04F60B2DD}
	operator System::Classes::_di_IStreamPersist()
	{
		System::Classes::_di_IStreamPersist intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IStreamPersist*(void) { return (System::Classes::IStreamPersist*)&__IStreamPersist; }
	#endif
	
};


__interface  INTERFACE_UUID("{8C014863-4F69-48F2-9CF7-E336BFD3F06B}") IPathObject  : public Fmx::Types::IFreeNotificationBehavior 
{
	virtual TPathData* __fastcall GetPath() = 0 ;
	__property TPathData* Path = {read=GetPath};
};

enum class DECLSPEC_DENUM TPathPointKind : unsigned int { MoveTo, LineTo, CurveTo, Close, ppMoveTo _DEPRECATED_ATTRIBUTE3("Use TPathPointKind.MoveTo")  = 0, ppLineTo _DEPRECATED_ATTRIBUTE3("Use TPathPointKind.LineTo")  = 1, ppCurveTo _DEPRECATED_ATTRIBUTE3("Use TPathPointKind.CurveTo")  = 2, ppClose _DEPRECATED_ATTRIBUTE3("Use TPathPointKind.Close")  = 3 };

#pragma pack(push,1)
struct DECLSPEC_DRECORD TPathPoint
{
public:
	TPathPointKind Kind;
	System::Types::TPointF Point;
	static TPathPoint __fastcall Create(const TPathPointKind AKind, const System::Types::TPointF &APoint);
	static bool __fastcall _op_Equality(const TPathPoint &APoint1, const TPathPoint &APoint2);
	static bool __fastcall _op_Inequality(const TPathPoint &APoint1, const TPathPoint &APoint2);
	
	friend bool operator ==(const TPathPoint &APoint1, const TPathPoint &APoint2) { return TPathPoint::_op_Equality(APoint1, APoint2); }
	friend bool operator !=(const TPathPoint &APoint1, const TPathPoint &APoint2) { return TPathPoint::_op_Inequality(APoint1, APoint2); }
};
#pragma pack(pop)


class PASCALIMPLEMENTATION TPathData : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
public:
	TPathPoint operator[](int AIndex) { return this->Points[AIndex]; }
	
private:
	#define TPathData_MinFlatness  (5.000000E-02)
	
	
public:
	#define TPathData_DefaultFlatness  (2.500000E-01)
	
	
private:
	System::Classes::TNotifyEvent FOnChanged;
	System::TObject* FStyleResource;
	System::UnicodeString FStyleLookup;
	System::Types::TPointF FStartPoint;
	System::Generics::Collections::TList__1<TPathPoint>* FPathData;
	bool FRecalcBounds;
	System::Types::TRectF FBounds;
	System::UnicodeString __fastcall GetPathString();
	void __fastcall SetPathString(const System::UnicodeString Value);
	void __fastcall CalculateBezierCoefficients(const System::Math::Vectors::TCubicBezier &Bezier, /* out */ float &AX, /* out */ float &BX, /* out */ float &CX, /* out */ float &AY, /* out */ float &BY, /* out */ float &CY);
	System::Types::TPointF __fastcall PointOnBezier(const System::Types::TPointF &StartPoint, const float AX, const float BX, const float CX, const float AY, const float BY, const float CY, const float T);
	System::Math::Vectors::TPolygon __fastcall CreateBezier(const System::Math::Vectors::TCubicBezier &Bezier, const int PointCount);
	void __fastcall AddArcSvgPart(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle);
	void __fastcall AddArcSvg(const System::Types::TPointF &P1, const System::Types::TPointF &Radius, float Angle, const bool LargeFlag, const bool SweepFlag, const System::Types::TPointF &P2);
	System::UnicodeString __fastcall GetStyleLookup();
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	TPathData* __fastcall GetPath();
	int __fastcall GetCount();
	TPathPoint __fastcall GetPoint(int AIndex);
	System::UnicodeString __fastcall GetTokensFromString(const System::UnicodeString PathString, int &Pos);
	System::UnicodeString __fastcall GetNumberFromString(const System::UnicodeString PathString, int &Pos);
	System::Types::TPointF __fastcall GetPointFromString(const System::UnicodeString PathString, int &Pos);
	bool __fastcall HasRelativeOffset(const System::UnicodeString PathString, const int Pos);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall ReadPath(System::Classes::TStream* Stream);
	void __fastcall WritePath(System::Classes::TStream* Stream);
	void __fastcall FreeNotification(System::TObject* AObject);
	virtual void __fastcall DoChanged(bool NeedRecalcBounds = true);
	
public:
	__fastcall virtual TPathData();
	__fastcall virtual ~TPathData();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall EqualsPath(TPathData* const Path);
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	System::Types::TPointF __fastcall LastPoint();
	void __fastcall MoveTo(const System::Types::TPointF &P);
	void __fastcall MoveToRel(const System::Types::TPointF &P);
	void __fastcall LineTo(const System::Types::TPointF &P);
	void __fastcall LineToRel(const System::Types::TPointF &P);
	void __fastcall HLineTo(const float X);
	void __fastcall HLineToRel(const float X);
	void __fastcall VLineTo(const float Y);
	void __fastcall VLineToRel(const float Y);
	void __fastcall CurveTo(const System::Types::TPointF &ControlPoint1, const System::Types::TPointF &ControlPoint2, const System::Types::TPointF &EndPoint);
	void __fastcall CurveToRel(const System::Types::TPointF &ControlPoint1, const System::Types::TPointF &ControlPoint2, const System::Types::TPointF &EndPoint);
	void __fastcall SmoothCurveTo(const System::Types::TPointF &ControlPoint2, const System::Types::TPointF &EndPoint);
	void __fastcall SmoothCurveToRel(const System::Types::TPointF &ControlPoint2, const System::Types::TPointF &EndPoint);
	void __fastcall QuadCurveTo(const System::Types::TPointF &ControlPoint, const System::Types::TPointF &EndPoint);
	void __fastcall ClosePath();
	void __fastcall AddEllipse(const System::Types::TRectF &ARect);
	void __fastcall AddRectangle(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0));
	void __fastcall AddArc(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle);
	void __fastcall AddPath(TPathData* APath);
	void __fastcall Clear();
	void __fastcall Flatten(const float Flatness = 2.500000E-01f);
	void __fastcall Scale(const float ScaleX, const float ScaleY)/* overload */;
	void __fastcall Scale(const System::Types::TPointF &AScale)/* overload */;
	void __fastcall Translate(const float DX, const float DY)/* overload */;
	void __fastcall Translate(const System::Types::TPointF &Delta)/* overload */;
	void __fastcall FitToRect(const System::Types::TRectF &ARect);
	void __fastcall ApplyMatrix(const System::Math::Vectors::TMatrix &M);
	System::Types::TRectF __fastcall GetBounds();
	System::Types::TPointF __fastcall FlattenToPolygon(System::Math::Vectors::TPolygon &Polygon, const float Flatness = 2.500000E-01f);
	bool __fastcall IsEmpty();
	__property int Count = {read=GetCount, nodefault};
	__property TPathPoint Points[int AIndex] = {read=GetPoint/*, default*/};
	__property TPathData* ResourcePath = {read=GetPath};
	
__published:
	__property System::UnicodeString Data = {read=GetPathString, write=SetPathString, stored=false};
	__property System::UnicodeString StyleLookup = {read=GetStyleLookup, write=SetStyleLookup};
private:
	void *__IFreeNotification;	// Fmx::Types::IFreeNotification 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FEB50EAF-A3B9-4B37-8EDB-1EF9EE2F22D4}
	operator Fmx::Types::_di_IFreeNotification()
	{
		Fmx::Types::_di_IFreeNotification intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IFreeNotification*(void) { return (Fmx::Types::IFreeNotification*)&__IFreeNotification; }
	#endif
	
};


class PASCALIMPLEMENTATION TCanvasSaveState : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	bool FAssigned;
	TBrush* FFill;
	TStrokeBrush* FStroke;
	System::TArray__1<float> FDash;
	float FDashOffset;
	TFont* FFont;
	System::Math::Vectors::TMatrix FMatrix;
	System::Types::TPointF FOffset;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TCanvasSaveState();
	__fastcall virtual ~TCanvasSaveState();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property bool Assigned = {read=FAssigned, nodefault};
};


typedef System::DynamicArray<System::Types::TRectF> TRegion;

typedef System::DynamicArray<TRegion> TRegionArray;

class PASCALIMPLEMENTATION ECanvasException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECanvasException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECanvasException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECanvasException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECanvasException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECanvasException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECanvasException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECanvasException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECanvasException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECanvasException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECanvasException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECanvasException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECanvasException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECanvasException() { }
	
};


enum class DECLSPEC_DENUM TFillTextFlag : unsigned int { RightToLeft, ftRightToLeft _DEPRECATED_ATTRIBUTE3("Use TFillTextFlag.RightToLeft")  = 0x0 };

typedef System::Set<TFillTextFlag, _DELPHI_SET_ENUMERATOR(TFillTextFlag::RightToLeft), _DELPHI_SET_ENUMERATOR(TFillTextFlag::RightToLeft)> TFillTextFlags;

class PASCALIMPLEMENTATION TAbstractPrinter : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TAbstractPrinter() { }
	
public:
	/* TObject.Create */ inline __fastcall TAbstractPrinter() : System::Classes::TPersistent() { }
	
};


typedef System::DynamicArray<System::Types::TRectF> TClipRects;

typedef TClipRects *PClipRects;

__interface  INTERFACE_UUID("{61166E3B-9BC3-41E3-9D9A-5C6AB6460950}") ICanvasObject  : public System::IInterface 
{
	virtual TCanvas* __fastcall GetCanvas() = 0 ;
	__property TCanvas* Canvas = {read=GetCanvas};
};

__interface  INTERFACE_UUID("{B7CFFA1B-FBCF-4B36-AA32-93856F621F28}") IModulateCanvas  : public System::IInterface 
{
	virtual System::Uitypes::TAlphaColor __fastcall GetModulateColor() = 0 ;
	virtual void __fastcall SetModulateColor(const System::Uitypes::TAlphaColor AColor) = 0 ;
	__property System::Uitypes::TAlphaColor ModulateColor = {read=GetModulateColor, write=SetModulateColor};
};

enum class DECLSPEC_DENUM TCanvasStyle : unsigned int { NeedGPUSurface, SupportClipRects, SupportModulation };

typedef System::Set<TCanvasStyle, _DELPHI_SET_ENUMERATOR(TCanvasStyle::NeedGPUSurface), _DELPHI_SET_ENUMERATOR(TCanvasStyle::SupportModulation)> TCanvasStyles;

enum class DECLSPEC_DENUM TCanvasAttribute : unsigned int { MaxBitmapSize };

enum class DECLSPEC_DENUM TCanvasQuality : unsigned int { SystemDefault, HighPerformance, HighQuality, ccSystemDefault _DEPRECATED_ATTRIBUTE3("Use TCanvasQuality.SystemDefault")  = 0x0, ccHighPerformance _DEPRECATED_ATTRIBUTE3("Use TCanvasQuality.HighPerformance")  = 0x1, ccHighQuality _DEPRECATED_ATTRIBUTE3("Use TCanvasQuality.HighQuality")  = 0x2 };

class PASCALIMPLEMENTATION TCanvas : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TMatrixMeaning : unsigned int { Unknown, Identity, Translate, mmUnknown _DEPRECATED_ATTRIBUTE3("Use TMatrixMeaning.Unknown")  = 0x0, mmIdentity _DEPRECATED_ATTRIBUTE3("Use TMatrixMeaning.Identity")  = 0x1, mmTranslate _DEPRECATED_ATTRIBUTE3("Use TMatrixMeaning.Translate")  = 0x2 };
	
	struct TMatrixMeaningHelper /* Helper for enum 'TMatrixMeaning' */;
	class DELPHICLASS TCustomMetaBrush;
	class PASCALIMPLEMENTATION TCustomMetaBrush : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		bool FValid;
		
	public:
		__property bool Valid = {read=FValid, write=FValid, nodefault};
	public:
		/* TObject.Create */ inline __fastcall TCustomMetaBrush() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TCustomMetaBrush() { }
		
	};
	
	
	class DELPHICLASS TMetaBrush;
	class PASCALIMPLEMENTATION TMetaBrush : public TCanvas::TCustomMetaBrush
	{
		typedef TCanvas::TCustomMetaBrush inherited;
		
	private:
		TBrushKind FKind;
		System::Uitypes::TAlphaColor FColor;
		float FOpacity;
		TGradient* FGradient;
		System::Types::TRectF FRect;
		TBitmapImage* FBitmapImage;
		TWrapMode FWrapMode;
		TGradient* __fastcall GetGradient();
		
	public:
		__fastcall virtual ~TMetaBrush();
		__property TBrushKind Kind = {read=FKind, write=FKind, nodefault};
		__property System::Uitypes::TAlphaColor Color = {read=FColor, write=FColor, nodefault};
		__property float Opacity = {read=FOpacity, write=FOpacity};
		__property System::Types::TRectF Rect = {read=FRect, write=FRect};
		__property TWrapMode WrapMode = {read=FWrapMode, write=FWrapMode, nodefault};
		__property TGradient* Gradient = {read=GetGradient};
		__property TBitmapImage* Image = {read=FBitmapImage, write=FBitmapImage};
	public:
		/* TObject.Create */ inline __fastcall TMetaBrush() : TCanvas::TCustomMetaBrush() { }
		
	};
	
	
	class DELPHICLASS TMetaStrokeBrush;
	class PASCALIMPLEMENTATION TMetaStrokeBrush : public TCanvas::TCustomMetaBrush
	{
		typedef TCanvas::TCustomMetaBrush inherited;
		
	private:
		TStrokeCap FCap;
		TStrokeDash FDash;
		TStrokeJoin FJoin;
		System::TArray__1<float> FDashArray;
		float FDashOffset;
		
	public:
		__property TStrokeCap Cap = {read=FCap, write=FCap, nodefault};
		__property TStrokeDash Dash = {read=FDash, write=FDash, nodefault};
		__property TStrokeJoin Join = {read=FJoin, write=FJoin, nodefault};
		__property System::TArray__1<float> DashArray = {read=FDashArray, write=FDashArray};
		__property float DashOffset = {read=FDashOffset, write=FDashOffset};
	public:
		/* TObject.Create */ inline __fastcall TMetaStrokeBrush() : TCanvas::TCustomMetaBrush() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TMetaStrokeBrush() { }
		
	};
	
	
	
private:
	typedef System::Generics::Collections::TObjectList__1<TCanvasSaveState*>* TCanvasSaveStateList;
	
	
public:
	static constexpr System::Word MaxAllowedBitmapSize = System::Word(0xffff);
	
	static constexpr System::Int8 DefaultScale = System::Int8(0x1);
	
	
protected:
	static System::TObject* FLock;
	
private:
	int FBeginSceneCount;
	TBrush* FFill;
	TStrokeBrush* FStroke;
	Fmx::Types::TWindowHandle* FParent;
	TBitmap* FBitmap;
	float FScale;
	TCanvasQuality FQuality;
	System::Math::Vectors::TMatrix FMatrix;
	void __fastcall SetFill(TBrush* const Value);
	TMatrixMeaning FMatrixMeaning;
	System::Types::TPointF FMatrixTranslate;
	bool FBlending;
	System::Types::TPointF FOffset;
	void __fastcall SetBlending(const bool Value);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
protected:
	int FClippingChangeCount;
	int FSavingStateCount;
	int FWidth;
	int FHeight;
	TFont* FFont;
	System::Generics::Collections::TObjectList__1<TCanvasSaveState*>* FCanvasSaveData;
	TAbstractPrinter* FPrinter;
	virtual void __fastcall FontChanged(System::TObject* Sender);
	virtual TCanvasSaveState* __fastcall CreateSaveState();
	void __fastcall Initialize();
	void __fastcall UnInitialize();
	virtual float __fastcall GetCanvasScale();
	virtual bool __fastcall DoBeginScene(const PClipRects AClipRects = (PClipRects)(0x0), NativeUInt AContextHandle = (NativeUInt)(0ULL));
	virtual void __fastcall DoEndScene();
	virtual void __fastcall DoFlush();
	__fastcall virtual TCanvas(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const TCanvasQuality AQuality);
	__fastcall virtual TCanvas(TBitmap* const ABitmap, const TCanvasQuality AQuality);
	__fastcall virtual TCanvas(TAbstractPrinter* const APrinter);
	virtual __classmethod NativeUInt __fastcall DoInitializeBitmap(const int Width, const int Height, const float Scale, Fmx::Types::TPixelFormat &PixelFormat) = 0 ;
	virtual __classmethod void __fastcall DoFinalizeBitmap(NativeUInt &Bitmap) = 0 ;
	virtual __classmethod bool __fastcall DoMapBitmap(const NativeUInt Bitmap, const TMapAccess Access, TBitmapData &Data) = 0 ;
	virtual __classmethod void __fastcall DoUnmapBitmap(const NativeUInt Bitmap, TBitmapData &Data) = 0 ;
	__classmethod virtual void __fastcall DoCopyBitmap(TBitmap* const Source, TBitmap* const Dest);
	virtual void __fastcall DoBlendingChanged();
	virtual void __fastcall DoSetMatrix(const System::Math::Vectors::TMatrix &M);
	virtual void __fastcall DoFillRect(const System::Types::TRectF &ARect, const float AOpacity, TBrush* const ABrush) = 0 ;
	virtual void __fastcall DoFillRoundRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, TBrush* const ABrush, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0));
	virtual void __fastcall DoFillPath(TPathData* const APath, const float AOpacity, TBrush* const ABrush) = 0 ;
	virtual void __fastcall DoFillEllipse(const System::Types::TRectF &ARect, const float AOpacity, TBrush* const ABrush) = 0 ;
	virtual bool __fastcall DoFillPolygon(const System::Math::Vectors::TPolygon Points, const float AOpacity, TBrush* const ABrush);
	virtual void __fastcall DoDrawBitmap(TBitmap* const ABitmap, const System::Types::TRectF &SrcRect, const System::Types::TRectF &DstRect, const float AOpacity, const bool HighSpeed) = 0 ;
	virtual void __fastcall DoDrawLine(const System::Types::TPointF &APt1, const System::Types::TPointF &APt2, const float AOpacity, TStrokeBrush* const ABrush) = 0 ;
	virtual void __fastcall DoDrawRect(const System::Types::TRectF &ARect, const float AOpacity, TStrokeBrush* const ABrush) = 0 ;
	virtual bool __fastcall DoDrawPolygon(const System::Math::Vectors::TPolygon Points, const float AOpacity, TStrokeBrush* const ABrush);
	virtual void __fastcall DoDrawPath(TPathData* const APath, const float AOpacity, TStrokeBrush* const ABrush) = 0 ;
	virtual void __fastcall DoDrawEllipse(const System::Types::TRectF &ARect, const float AOpacity, TStrokeBrush* const ABrush) = 0 ;
	__property Fmx::Types::TWindowHandle* Parent = {read=FParent};
	System::Types::TPointF __fastcall TransformPoint(const System::Types::TPointF &P);
	System::Types::TRectF __fastcall TransformRect(const System::Types::TRectF &Rect);
	__property TMatrixMeaning MatrixMeaning = {read=FMatrixMeaning, nodefault};
	__property System::Types::TPointF MatrixTranslate = {read=FMatrixTranslate};
	
public:
	__fastcall virtual ~TCanvas();
	__classmethod void __fastcall Lock();
	__classmethod void __fastcall Unlock();
	__classmethod virtual TCanvasStyles __fastcall GetCanvasStyle();
	__classmethod virtual int __fastcall GetAttribute(const TCanvasAttribute Value);
	virtual void __fastcall SetSize(const int AWidth, const int AHeight);
	bool __fastcall BeginScene(PClipRects AClipRects = (PClipRects)(0x0), NativeUInt AContextHandle = (NativeUInt)(0ULL));
	void __fastcall EndScene();
	__property int BeginSceneCount = {read=FBeginSceneCount, nodefault};
	void __fastcall Flush();
	virtual void __fastcall Clear(const System::Uitypes::TAlphaColor Color) = 0 ;
	virtual void __fastcall ClearRect(const System::Types::TRectF &ARect, const System::Uitypes::TAlphaColor AColor = (System::Uitypes::TAlphaColor)(0x0)) = 0 ;
	bool __fastcall IsScaleInteger();
	void __fastcall SetMatrix(const System::Math::Vectors::TMatrix &M);
	void __fastcall MultiplyMatrix(const System::Math::Vectors::TMatrix &M);
	TCanvasSaveState* __fastcall SaveState();
	void __fastcall RestoreState(TCanvasSaveState* const State);
	__classmethod NativeUInt __fastcall InitializeBitmap(const int Width, const int Height, const float Scale, Fmx::Types::TPixelFormat &PixelFormat);
	__classmethod void __fastcall FinalizeBitmap(NativeUInt &Bitmap);
	__classmethod bool __fastcall MapBitmap(const NativeUInt Bitmap, const TMapAccess Access, TBitmapData &Data);
	__classmethod void __fastcall UnmapBitmap(const NativeUInt Bitmap, TBitmapData &Data);
	__classmethod void __fastcall CopyBitmap(TBitmap* const Source, TBitmap* const Dest);
	System::Types::TPointF __fastcall AlignToPixel(const System::Types::TPointF &Value)/* overload */;
	System::Types::TRectF __fastcall AlignToPixel(const System::Types::TRectF &Rect)/* overload */;
	float __fastcall AlignToPixelVertically(const float Value);
	float __fastcall AlignToPixelHorizontally(const float Value);
	virtual void __fastcall IntersectClipRect(const System::Types::TRectF &ARect) = 0 ;
	virtual void __fastcall ExcludeClipRect(const System::Types::TRectF &ARect) = 0 ;
	void __fastcall FillArc(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle, const float AOpacity)/* overload */;
	void __fastcall FillArc(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle, const float AOpacity, TBrush* const ABrush)/* overload */;
	void __fastcall FillRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall FillRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, TBrush* const ABrush, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall FillRect(const System::Types::TRectF &ARect, const float AOpacity)/* overload */;
	void __fastcall FillRect(const System::Types::TRectF &ARect, const float AOpacity, TBrush* const ABrush)/* overload */;
	void __fastcall FillPath(TPathData* const APath, const float AOpacity)/* overload */;
	void __fastcall FillPath(TPathData* const APath, const float AOpacity, TBrush* const ABrush)/* overload */;
	void __fastcall FillEllipse(const System::Types::TRectF &ARect, const float AOpacity)/* overload */;
	void __fastcall FillEllipse(const System::Types::TRectF &ARect, const float AOpacity, TBrush* const ABrush)/* overload */;
	void __fastcall DrawBitmap(TBitmap* const ABitmap, const System::Types::TRectF &SrcRect, const System::Types::TRectF &DstRect, const float AOpacity, const bool HighSpeed = false);
	void __fastcall DrawLine(const System::Types::TPointF &APt1, const System::Types::TPointF &APt2, const float AOpacity)/* overload */;
	void __fastcall DrawLine(const System::Types::TPointF &APt1, const System::Types::TPointF &APt2, const float AOpacity, TStrokeBrush* const ABrush)/* overload */;
	void __fastcall DrawRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall DrawRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, TStrokeBrush* const ABrush, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall DrawPath(TPathData* const APath, const float AOpacity)/* overload */;
	void __fastcall DrawPath(TPathData* const APath, const float AOpacity, TStrokeBrush* const ABrush)/* overload */;
	void __fastcall DrawEllipse(const System::Types::TRectF &ARect, const float AOpacity)/* overload */;
	void __fastcall DrawEllipse(const System::Types::TRectF &ARect, const float AOpacity, TStrokeBrush* const ABrush)/* overload */;
	void __fastcall DrawArc(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle, const float AOpacity)/* overload */;
	void __fastcall DrawArc(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, float StartAngle, float SweepAngle, const float AOpacity, TStrokeBrush* const ABrush)/* overload */;
	virtual bool __fastcall PtInPath(const System::Types::TPointF &APoint, TPathData* const APath) = 0 ;
	void __fastcall DrawRectSides(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, const Fmx::Types::TSides ASides, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall DrawRectSides(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, const Fmx::Types::TSides ASides, TStrokeBrush* const ABrush, const Fmx::Types::TCornerType ACornerType = (Fmx::Types::TCornerType)(0x0))/* overload */;
	void __fastcall DrawDashRect(const System::Types::TRectF &ARect, const float XRadius, const float YRadius, const Fmx::Types::TCorners ACorners, const float AOpacity, const System::Uitypes::TAlphaColor AColor);
	virtual void __fastcall FillPolygon(const System::Math::Vectors::TPolygon Points, const float AOpacity);
	virtual void __fastcall DrawPolygon(const System::Math::Vectors::TPolygon Points, const float AOpacity);
	virtual bool __fastcall LoadFontFromStream(System::Classes::TStream* const AStream);
	virtual void __fastcall FillText(const System::Types::TRectF &ARect, const System::UnicodeString AText, const bool WordWrap, const float AOpacity, const TFillTextFlags Flags, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0));
	virtual void __fastcall MeasureText(System::Types::TRectF &ARect, const System::UnicodeString AText, const bool WordWrap, const TFillTextFlags Flags, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0));
	virtual void __fastcall MeasureLines(Fmx::Types::TLineMetricInfo* const ALines, const System::Types::TRectF &ARect, const System::UnicodeString AText, const bool WordWrap, const TFillTextFlags Flags, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0));
	virtual bool __fastcall TextToPath(TPathData* Path, const System::Types::TRectF &ARect, const System::UnicodeString AText, const bool WordWrap, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0));
	float __fastcall TextWidth(const System::UnicodeString AText);
	float __fastcall TextHeight(const System::UnicodeString AText);
	__property bool Blending = {read=FBlending, write=SetBlending, nodefault};
	__property TCanvasQuality Quality = {read=FQuality, nodefault};
	__property TStrokeBrush* Stroke = {read=FStroke};
	__property TBrush* Fill = {read=FFill, write=SetFill};
	__property TFont* Font = {read=FFont};
	__property System::Math::Vectors::TMatrix Matrix = {read=FMatrix};
	__property int Width = {read=FWidth, nodefault};
	__property int Height = {read=FHeight, nodefault};
	__property TBitmap* Bitmap = {read=FBitmap};
	__property float Scale = {read=FScale};
	__property System::Types::TPointF Offset = {read=FOffset, write=FOffset};
	__property int ClippingChangeCount = {read=FClippingChangeCount, nodefault};
	__property int SavingStateCount = {read=FSavingStateCount, nodefault};
public:
	/* TObject.Create */ inline __fastcall TCanvas() : System::Classes::TInterfacedPersistent() { }
	
};


class PASCALIMPLEMENTATION ECanvasManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECanvasManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECanvasManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECanvasManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECanvasManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECanvasManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECanvasManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECanvasManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECanvasManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECanvasManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECanvasManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECanvasManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECanvasManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECanvasManagerException() { }
	
};


class PASCALIMPLEMENTATION TCanvasDestroyMessage : public System::Messaging::TMessageBase
{
	typedef System::Messaging::TMessageBase inherited;
	
public:
	/* TObject.Create */ inline __fastcall TCanvasDestroyMessage() : System::Messaging::TMessageBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCanvasDestroyMessage() { }
	
};


class PASCALIMPLEMENTATION TCanvasManager : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	struct DECLSPEC_DRECORD TCanvasClassRec
	{
	public:
		TCanvasClass CanvasClass;
		bool Default;
		bool PrinterCanvas;
	};
	
	
	
private:
	static System::Generics::Collections::TList__1<TCanvasClassRec>* FCanvasList;
	static TCanvasClass FDefaultCanvasClass;
	static TCanvasClass FDefaultPrinterCanvasClass;
	static TBitmap* FMeasureBitmap;
	static bool FEnableSoftwareCanvas;
	
private:
	static TCanvasClass __fastcall GetDefaultCanvas();
	static TCanvas* __fastcall GetMeasureCanvas();
	static TCanvasClass __fastcall GetDefaultPrinterCanvas();
	
public:
	__classmethod void __fastcall UnInitialize();
	__classmethod void __fastcall RegisterCanvas(const TCanvasClass CanvasClass, const bool ADefault, const bool APrinterCanvas);
	/* static */ __property TCanvasClass DefaultCanvas = {read=GetDefaultCanvas};
	/* static */ __property TCanvasClass DefaultPrinterCanvas = {read=GetDefaultPrinterCanvas};
	/* static */ __property TCanvas* MeasureCanvas = {read=GetMeasureCanvas};
	__classmethod TCanvas* __fastcall CreateFromWindow(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const TCanvasQuality AQuality = (TCanvasQuality)(0x0));
	__classmethod TCanvas* __fastcall CreateFromBitmap(TBitmap* const ABitmap, const TCanvasQuality AQuality = (TCanvasQuality)(0x0));
	__classmethod TCanvas* __fastcall CreateFromPrinter(TAbstractPrinter* const APrinter);
	__classmethod void __fastcall RecreateFromPrinter(TCanvas* const Canvas, TAbstractPrinter* const APrinter);
	__classmethod void __fastcall EnableSoftwareCanvas(const bool Enable);
public:
	/* TObject.Create */ inline __fastcall TCanvasManager() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCanvasManager() { }
	
};


class PASCALIMPLEMENTATION TPrinterCanvas : public TCanvas
{
	typedef TCanvas inherited;
	
protected:
	/* TCanvas.CreateFromWindow */ inline __fastcall virtual TPrinterCanvas(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const TCanvasQuality AQuality) : TCanvas(AParent, AWidth, AHeight, AQuality) { }
	/* TCanvas.CreateFromBitmap */ inline __fastcall virtual TPrinterCanvas(TBitmap* const ABitmap, const TCanvasQuality AQuality) : TCanvas(ABitmap, AQuality) { }
	/* TCanvas.CreateFromPrinter */ inline __fastcall virtual TPrinterCanvas(TAbstractPrinter* const APrinter) : TCanvas(APrinter) { }
	
public:
	/* TCanvas.Destroy */ inline __fastcall virtual ~TPrinterCanvas() { }
	
public:
	/* TObject.Create */ inline __fastcall TPrinterCanvas() : TCanvas() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TPrinterCanvasClass);

__interface  INTERFACE_UUID("{BB870DB6-0228-4165-9906-CF75BFF8C7CA}") IBrushObject  : public Fmx::Types::IFreeNotificationBehavior 
{
	virtual TBrush* __fastcall GetBrush() = 0 ;
	__property TBrush* Brush = {read=GetBrush};
};

class PASCALIMPLEMENTATION TBrushObject : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TBrush* FBrush;
	TBrush* __fastcall GetBrush();
	
protected:
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	
public:
	__fastcall virtual TBrushObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBrushObject();
	
__published:
	__property TBrush* Brush = {read=FBrush, write=FBrush};
private:
	void *__IBrushObject;	// IBrushObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BB870DB6-0228-4165-9906-CF75BFF8C7CA}
	operator _di_IBrushObject()
	{
		_di_IBrushObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBrushObject*(void) { return (IBrushObject*)&__IBrushObject; }
	#endif
	
};


__interface  INTERFACE_UUID("{F87FBCFE-CE5F-430C-8F46-B20B2E395C1B}") IFontObject  : public Fmx::Types::IFreeNotificationBehavior 
{
	virtual TFont* __fastcall GetFont() = 0 ;
	__property TFont* Font = {read=GetFont};
};

class PASCALIMPLEMENTATION TFontObject : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TFont* FFont;
	TFont* __fastcall GetFont();
	
protected:
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	
public:
	__fastcall virtual TFontObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFontObject();
	
__published:
	__property TFont* Font = {read=FFont, write=FFont};
private:
	void *__IFontObject;	// IFontObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F87FBCFE-CE5F-430C-8F46-B20B2E395C1B}
	operator _di_IFontObject()
	{
		_di_IFontObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFontObject*(void) { return (IFontObject*)&__IFontObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TPathObject : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TPathData* FPath;
	TPathData* __fastcall GetPath();
	
protected:
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	
public:
	__fastcall virtual TPathObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPathObject();
	
__published:
	__property TPathData* Path = {read=FPath, write=FPath};
private:
	void *__IPathObject;	// IPathObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8C014863-4F69-48F2-9CF7-E336BFD3F06B}
	operator _di_IPathObject()
	{
		_di_IPathObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPathObject*(void) { return (IPathObject*)&__IPathObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TBitmapObject : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TBitmap* FBitmap;
	TBitmap* __fastcall GetBitmap();
	
protected:
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	
public:
	__fastcall virtual TBitmapObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBitmapObject();
	
__published:
	__property TBitmap* Bitmap = {read=FBitmap, write=FBitmap};
private:
	void *__IBitmapObject;	// IBitmapObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C17D001-47C1-462F-856D-8358B7B2C842}
	operator _di_IBitmapObject()
	{
		_di_IBitmapObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBitmapObject*(void) { return (IBitmapObject*)&__IBitmapObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TColorObject : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	
protected:
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=FColor, nodefault};
public:
	/* TFmxObject.Create */ inline __fastcall virtual TColorObject(System::Classes::TComponent* AOwner) : Fmx::Types::TFmxObject(AOwner) { }
	/* TFmxObject.Destroy */ inline __fastcall virtual ~TColorObject() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TFontColorForStateClass);

class PASCALIMPLEMENTATION TFontColorForState : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
	
public:
	enum class DECLSPEC_DENUM TIndex : unsigned int { Normal, Hot, Pressed, Focused, Active };
	
	
public:
	System::Uitypes::TAlphaColor operator[](const TIndex Index) { return this->Color[Index]; }
	
private:
	TTextSettings* FOwner;
	System::StaticArray<System::Uitypes::TAlphaColor, 5> FColor;
	int FUpdateCount;
	bool FChanged;
	System::Uitypes::TAlphaColor __fastcall GetColor(const TIndex Index);
	void __fastcall SetColor(const TIndex Index, const System::Uitypes::TAlphaColor Value);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual System::Uitypes::TAlphaColor __fastcall GetCurrentColor(const TIndex Index);
	virtual void __fastcall DoChanged();
	
public:
	__fastcall virtual TFontColorForState(TTextSettings* const AOwner);
	virtual void __fastcall AfterConstruction();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	void __fastcall Change();
	__property TTextSettings* Owner = {read=FOwner};
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual bool __fastcall Equals(System::TObject* Obj);
	__property System::Uitypes::TAlphaColor CurrentColor[const TIndex Index] = {read=GetCurrentColor};
	__property System::Uitypes::TAlphaColor Color[const TIndex Index] = {read=GetColor, write=SetColor/*, default*/};
	__property System::Uitypes::TAlphaColor Normal = {read=GetColor, write=SetColor, index=0, default=0};
	__property System::Uitypes::TAlphaColor Hot = {read=GetColor, write=SetColor, index=1, default=0};
	__property System::Uitypes::TAlphaColor Pressed = {read=GetColor, write=SetColor, index=2, default=0};
	__property System::Uitypes::TAlphaColor Focused = {read=GetColor, write=SetColor, index=3, default=0};
	__property System::Uitypes::TAlphaColor Active = {read=GetColor, write=SetColor, index=4, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFontColorForState() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TTextSettingsClass);

class PASCALIMPLEMENTATION TTextSettings : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TPersistent* FOwner;
	TFont* FFont;
	int FUpdateCount;
	Fmx::Types::TTextAlign FHorzAlign;
	Fmx::Types::TTextAlign FVertAlign;
	bool FWordWrap;
	System::Uitypes::TAlphaColor FFontColor;
	bool FIsChanged;
	bool FIsAdjustChanged;
	System::Classes::TNotifyEvent FOnChanged;
	Fmx::Types::TTextTrimming FTrimming;
	TFontColorForState* FFontColorForState;
	void __fastcall SetFontColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetHorzAlign(const Fmx::Types::TTextAlign Value);
	void __fastcall SetVertAlign(const Fmx::Types::TTextAlign Value);
	void __fastcall SetWordWrap(const bool Value);
	void __fastcall SetTrimming(const Fmx::Types::TTextTrimming Value);
	void __fastcall SetFontColorForState(TFontColorForState* const Value);
	bool __fastcall StoreFontColorForState();
	TFontColorForState* __fastcall CreateFontColorForState();
	
protected:
	virtual void __fastcall DoChanged();
	virtual void __fastcall SetFont(TFont* const Value);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual TFontColorForStateClass __fastcall GetTextColorsClass();
	virtual void __fastcall DoAssign(TTextSettings* const Source);
	virtual void __fastcall DoAssignNotStyled(TTextSettings* const TextSettings, const Fmx::Types::TStyledSettings StyledSettings);
	
public:
	__fastcall virtual TTextSettings(System::Classes::TPersistent* const AOwner);
	__fastcall virtual ~TTextSettings();
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall AssignNotStyled(TTextSettings* const TextSettings, const Fmx::Types::TStyledSettings StyledSettings);
	virtual bool __fastcall Equals(System::TObject* Obj);
	void __fastcall Change();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	virtual void __fastcall UpdateStyledSettings(TTextSettings* const OldTextSettings, TTextSettings* const DefaultTextSettings, Fmx::Types::TStyledSettings &StyledSettings);
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	__property bool IsChanged = {read=FIsChanged, write=FIsChanged, nodefault};
	__property bool IsAdjustChanged = {read=FIsAdjustChanged, write=FIsAdjustChanged, nodefault};
	__property TFont* Font = {read=FFont, write=SetFont};
	__property System::Uitypes::TAlphaColor FontColor = {read=FFontColor, write=SetFontColor, default=-16777216};
	__property TFontColorForState* FontColorForState = {read=FFontColorForState, write=SetFontColorForState, stored=StoreFontColorForState};
	__property Fmx::Types::TTextAlign HorzAlign = {read=FHorzAlign, write=SetHorzAlign, default=1};
	__property Fmx::Types::TTextAlign VertAlign = {read=FVertAlign, write=SetVertAlign, default=0};
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, default=0};
	__property Fmx::Types::TTextTrimming Trimming = {read=FTrimming, write=SetTrimming, default=0};
	__property System::Classes::TPersistent* Owner = {read=FOwner};
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
};


__interface  INTERFACE_UUID("{FD99635D-D8DB-4E26-B36F-97D3AABBCCB3}") ITextSettings  : public System::IInterface 
{
	virtual TTextSettings* __fastcall GetDefaultTextSettings() = 0 ;
	virtual TTextSettings* __fastcall GetTextSettings() = 0 ;
	virtual void __fastcall SetTextSettings(TTextSettings* const Value) = 0 ;
	virtual TTextSettings* __fastcall GetResultingTextSettings() = 0 ;
	virtual Fmx::Types::TStyledSettings __fastcall GetStyledSettings() = 0 ;
	virtual void __fastcall SetStyledSettings(const Fmx::Types::TStyledSettings Value) = 0 ;
	__property TTextSettings* DefaultTextSettings = {read=GetDefaultTextSettings};
	__property TTextSettings* TextSettings = {read=GetTextSettings, write=SetTextSettings};
	__property TTextSettings* ResultingTextSettings = {read=GetResultingTextSettings};
	__property Fmx::Types::TStyledSettings StyledSettings = {read=GetStyledSettings, write=SetStyledSettings};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Graphics */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRAPHICS)
using namespace Fmx::Graphics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_GraphicsHPP
