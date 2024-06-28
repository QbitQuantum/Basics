// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Styles.Switch.pas' rev: 34.00 (Windows)

#ifndef Fmx_Styles_SwitchHPP
#define Fmx_Styles_SwitchHPP

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
#include <System.UIConsts.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Styles.Objects.hpp>
#include <FMX.Platform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Styles
{
namespace Switch
{
//-- forward type declarations -----------------------------------------------
struct TSwitchTextKindHelper /* Helper for enum 'TSwitchTextKind' */;
class DELPHICLASS TSwitchTextObject;
struct TSwitchKindHelper /* Helper for enum 'TSwitchKind' */;
class DELPHICLASS TCustomSwitchObject;
struct TSwitchShapeHelper /* Helper for enum 'TSwitchShape' */;
class DELPHICLASS TSwitchObject;
class DELPHICLASS TBitmapSwitchObject;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TSwitchTextKind : unsigned char { None, IO, IOandOnOff, Localized, Bitmap, stkNone _DEPRECATED_ATTRIBUTE3("Use TSwitchTextKind.None")  = 0, stkIO _DEPRECATED_ATTRIBUTE3("Use TSwitchTextKind.IO")  = 1, stkIOandOnOff _DEPRECATED_ATTRIBUTE3("Use TSwitchTextKind.IOandOnOff")  = 2, stkLocalized _DEPRECATED_ATTRIBUTE3("Use TSwitchTextKind.Localized")  = 3, stkBitmap _DEPRECATED_ATTRIBUTE3("Use TSwitchTextKind.Bitmap")  = 4 };

class PASCALIMPLEMENTATION TSwitchTextObject : public Fmx::Styles::Objects::TStyleTextObject
{
	typedef Fmx::Styles::Objects::TStyleTextObject inherited;
	
	
public:
	struct DECLSPEC_DRECORD TStatesForLocale
	{
	public:
		System::UnicodeString Locale;
		System::UnicodeString OnText;
		System::UnicodeString OffText;
	};
	
	
	
private:
	typedef System::StaticArray<TStatesForLocale, 7> _TSwitchTextObject__1;
	
	
public:
	static TStatesForLocale DefaultTexts;
	static _TSwitchTextObject__1 LocalizedStates;
	
private:
	TSwitchTextKind FKind;
	System::Uitypes::TAlphaColor FColorOn;
	bool FValue;
	System::UnicodeString FCurrentLang;
	TSwitchTextKind FSavedKind;
	System::UnicodeString __fastcall GetDefaultText(const bool Value);
	System::UnicodeString __fastcall GetTextForLocale(const System::UnicodeString Locale, const bool Value);
	System::UnicodeString __fastcall GetTextForKind(const TSwitchTextKind Kind, const bool Value);
	void __fastcall SetColorOn(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetValue(const bool Value);
	void __fastcall SetKind(const TSwitchTextKind Value);
	
protected:
	virtual bool __fastcall UpdateCurrentProperties();
	virtual System::UnicodeString __fastcall ConvertText(const System::UnicodeString Value);
	virtual bool __fastcall SaveState();
	virtual bool __fastcall RestoreState();
	
public:
	__fastcall virtual TSwitchTextObject(System::Classes::TComponent* AOwner);
	__property bool Value = {read=FValue, write=SetValue, nodefault};
	
__published:
	__property System::Uitypes::TAlphaColor ColorOn = {read=FColorOn, write=SetColorOn, default=0};
	__property TSwitchTextKind Kind = {read=FKind, write=SetKind, nodefault};
public:
	/* TStyleTextObject.Destroy */ inline __fastcall virtual ~TSwitchTextObject() { }
	
};


enum class DECLSPEC_DENUM TSwitchKind : unsigned char { ClippingTracks, FadingTracks, skClippingTracks _DEPRECATED_ATTRIBUTE3("Use TSwitchKind.ClippingTracks")  = 0x0, skFadingTracks _DEPRECATED_ATTRIBUTE3("Use TSwitchKind.FadingTracks")  = 0x1 };

class PASCALIMPLEMENTATION TCustomSwitchObject : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
public:
	#define TCustomSwitchObject_SwitchAnimationDuration  (2.000000E-01)
	
	static const System::Int8 TrackingSensitivity = System::Int8(0x3);
	
	static const System::Int8 TextClipOffset = System::Int8(0x4);
	
	
private:
	Fmx::Controls::TControl* FControl;
	Fmx::Types::TBounds* FThumbRect;
	bool FPressed;
	bool FTracking;
	bool FAnimating;
	System::Types::TPointF FPressedThumbPos;
	System::Types::TPointF FSavedPos;
	Fmx::Ani::TRectAnimation* FClickAnimation;
	bool FValue;
	System::Classes::TNotifyEvent FOnChange;
	float FThumbLength;
	float FTrackingThumbScale;
	Fmx::Types::TBounds* FThumbPadding;
	TSwitchTextObject* FTrackText;
	TSwitchTextObject* FThumbText;
	TSwitchKind FKind;
	void __fastcall DoAnimationEnd(System::TObject* Sender);
	void __fastcall SetThumbRect(Fmx::Types::TBounds* const Value);
	void __fastcall DoThumbRectChanged(System::TObject* Sender);
	void __fastcall SetThumbLength(const float Value);
	void __fastcall SetThumbPadding(Fmx::Types::TBounds* const Value);
	void __fastcall SetTrackingThumbScale(const float Value);
	void __fastcall PaintThumb();
	void __fastcall PaintThumbText();
	void __fastcall PaintTrack();
	void __fastcall PaintTrackText();
	bool __fastcall IsTrackTextStored();
	bool __fastcall IsThumbTextStored();
	void __fastcall PaintClippingTracks();
	void __fastcall PaintFadingTracks();
	
protected:
	virtual System::Classes::TObservers* __fastcall GetObservers();
	void __fastcall AnimateTo(const bool Value);
	float __fastcall GetThumbValue();
	float __fastcall GetThumbCenter();
	float __fastcall GetThumbLength();
	System::Types::TRectF __fastcall GetThumbRect();
	bool __fastcall GetValueByMousePos(const float X, const float Y);
	virtual System::Types::TRectF __fastcall GetThumbRectByValue(const bool Value);
	void __fastcall DoChange();
	virtual bool __fastcall IsThumbTextVisible();
	virtual bool __fastcall IsTrackTextVisible();
	virtual void __fastcall PaintThumbForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintThumbTextForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintTrackForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintTrackTextForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall Paint();
	virtual void __fastcall DoExit();
	virtual void __fastcall DoMouseEnter();
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	__property bool Pressed = {read=FPressed, nodefault};
	__property bool Tracking = {read=FTracking, nodefault};
	__property bool Animating = {read=FAnimating, nodefault};
	void __fastcall SetValue(const bool Value);
	
public:
	__fastcall virtual TCustomSwitchObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomSwitchObject();
	__property Fmx::Controls::TControl* Control = {read=FControl, write=FControl};
	__property Fmx::Types::TBounds* ThumbRect = {read=FThumbRect, write=SetThumbRect};
	__property bool Value = {read=FValue, write=SetValue, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property Action;
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property HitTest = {default=0};
	__property TSwitchKind Kind = {read=FKind, write=FKind, default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TouchTargetExpansion;
	__property TSwitchTextObject* TrackText = {read=FTrackText, stored=IsTrackTextStored};
	__property float TrackingThumbScale = {read=FTrackingThumbScale, write=SetTrackingThumbScale};
	__property float ThumbLength = {read=FThumbLength, write=SetThumbLength};
	__property Fmx::Types::TBounds* ThumbPadding = {read=FThumbPadding, write=SetThumbPadding};
	__property TSwitchTextObject* ThumbText = {read=FThumbText, stored=IsThumbTextStored};
	__property Visible = {default=1};
	__property Width;
	__property OnApplyStyleLookup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};


enum class DECLSPEC_DENUM TSwitchShape : unsigned char { Rectangle, RoundRect, Oval, ssRectangle _DEPRECATED_ATTRIBUTE3("Use TSwitchShape.Rectangle")  = 0x0, ssRoundRect _DEPRECATED_ATTRIBUTE3("Use TSwitchShape.RoundRect")  = 0x1, ssOval _DEPRECATED_ATTRIBUTE3("Use TSwitchShape.Oval")  = 0x2 };

class PASCALIMPLEMENTATION TSwitchObject : public TCustomSwitchObject
{
	typedef TCustomSwitchObject inherited;
	
private:
	Fmx::Graphics::TBrush* FFill;
	Fmx::Graphics::TBrush* FFillOn;
	Fmx::Graphics::TStrokeBrush* FStroke;
	TSwitchShape FShape;
	Fmx::Graphics::TBrush* FThumb;
	Fmx::Graphics::TBrush* FThumbOn;
	Fmx::Graphics::TStrokeBrush* FThumbStroke;
	void __fastcall SetFill(Fmx::Graphics::TBrush* const Value);
	void __fastcall SetFillOn(Fmx::Graphics::TBrush* const Value);
	void __fastcall SetStroke(Fmx::Graphics::TStrokeBrush* const Value);
	void __fastcall SetShape(const TSwitchShape Value);
	void __fastcall SetThumb(Fmx::Graphics::TBrush* const Value);
	void __fastcall SetThumbOn(Fmx::Graphics::TBrush* const Value);
	void __fastcall SetThumbStroke(Fmx::Graphics::TStrokeBrush* const Value);
	
protected:
	virtual void __fastcall PaintThumbForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintTrackForValue(const System::Types::TRectF &R, const bool Value);
	
public:
	__fastcall virtual TSwitchObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSwitchObject();
	
__published:
	__property Fmx::Graphics::TBrush* Fill = {read=FFill, write=SetFill};
	__property Fmx::Graphics::TBrush* FillOn = {read=FFillOn, write=SetFillOn};
	__property Fmx::Graphics::TStrokeBrush* Stroke = {read=FStroke, write=SetStroke};
	__property Fmx::Graphics::TBrush* Thumb = {read=FThumb, write=SetThumb};
	__property Fmx::Graphics::TBrush* ThumbOn = {read=FThumbOn, write=SetThumbOn};
	__property Fmx::Graphics::TStrokeBrush* ThumbStroke = {read=FThumbStroke, write=SetThumbStroke};
	__property TSwitchShape Shape = {read=FShape, write=SetShape, default=0};
};


class PASCALIMPLEMENTATION TBitmapSwitchObject : public TCustomSwitchObject
{
	typedef TCustomSwitchObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TSwitchPart : unsigned char { Track, TrackHot, TrackZoom, Thumb, ThumbPressed, ThumbHot, TextBitmap, TextBitmapEn, TextBitmapJp };
	
	struct DECLSPEC_DRECORD TSwitchRec
	{
	public:
		Fmx::Styles::Objects::TStyleObject* OnObject;
		Fmx::Styles::Objects::TStyleObject* OffObject;
	};
	
	
	
private:
	System::UnicodeString FSourceLookup;
	System::StaticArray<TSwitchRec, 9> FStyleObjects;
	Fmx::Platform::_di_IFMXLocaleService FLocaleService;
	Fmx::Styles::Objects::TBitmapLinks* __fastcall GetOnObject(TSwitchPart Index);
	void __fastcall SetOnObject(TSwitchPart Index, Fmx::Styles::Objects::TBitmapLinks* const Value);
	Fmx::Styles::Objects::TBitmapLinks* __fastcall GetOffObject(TSwitchPart Index);
	void __fastcall SetOffObject(TSwitchPart Index, Fmx::Styles::Objects::TBitmapLinks* const Value);
	System::UnicodeString __fastcall GetSourceLookup();
	void __fastcall SetSourceLookup(const System::UnicodeString Value);
	void __fastcall SetWrapMode(const TSwitchPart Index, const Fmx::Objects::TImageWrapMode Value);
	Fmx::Styles::Objects::TCapWrapMode __fastcall GetCapMode(const TSwitchPart Index);
	Fmx::Objects::TImageWrapMode __fastcall GetWrapMode(const TSwitchPart Index);
	void __fastcall SetCapMode(const TSwitchPart Index, const Fmx::Styles::Objects::TCapWrapMode Value);
	void __fastcall CopyCaps(const TSwitchPart Index)/* overload */;
	void __fastcall CopyCaps(const TSwitchPart Source, const TSwitchPart Dest)/* overload */;
	void __fastcall DefineLinkProperties(const System::UnicodeString SourceRects, const System::UnicodeString CapInsets, Fmx::Styles::Objects::TStyleObject* const StyleObject, System::Classes::TFiler* Filer);
	
protected:
	bool __fastcall PartExists(const TSwitchPart Part, const bool State);
	virtual bool __fastcall IsThumbTextVisible();
	virtual bool __fastcall IsTrackTextVisible();
	virtual void __fastcall PaintThumbForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintThumbTextForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintTrackForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall PaintTrackTextForValue(const System::Types::TRectF &R, const bool Value);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual TBitmapSwitchObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBitmapSwitchObject();
	virtual void __fastcall SetNewScene(Fmx::Controls::_di_IScene AScene);
	
__published:
	__property Fmx::Styles::Objects::TBitmapLinks* Track = {read=GetOffObject, write=SetOffObject, index=0};
	__property Fmx::Styles::Objects::TBitmapLinks* TrackZoom = {read=GetOffObject, write=SetOffObject, index=2};
	__property Fmx::Styles::Objects::TBitmapLinks* TrackOn = {read=GetOnObject, write=SetOnObject, index=0};
	__property Fmx::Styles::Objects::TBitmapLinks* TrackHot = {read=GetOffObject, write=SetOffObject, index=1};
	__property Fmx::Styles::Objects::TBitmapLinks* TrackHotOn = {read=GetOnObject, write=SetOnObject, index=1};
	__property Fmx::Styles::Objects::TCapWrapMode TrackCapMode = {read=GetCapMode, write=SetCapMode, index=0, default=0};
	__property Fmx::Objects::TImageWrapMode TrackWrapMode = {read=GetWrapMode, write=SetWrapMode, index=0, default=2};
	__property Fmx::Styles::Objects::TBitmapLinks* Thumb = {read=GetOffObject, write=SetOffObject, index=3};
	__property Fmx::Styles::Objects::TBitmapLinks* ThumbOn = {read=GetOnObject, write=SetOnObject, index=3};
	__property Fmx::Styles::Objects::TBitmapLinks* ThumbHot = {read=GetOffObject, write=SetOffObject, index=5};
	__property Fmx::Styles::Objects::TBitmapLinks* ThumbHotOn = {read=GetOnObject, write=SetOnObject, index=5};
	__property Fmx::Styles::Objects::TBitmapLinks* ThumbPressed = {read=GetOffObject, write=SetOffObject, index=4};
	__property Fmx::Styles::Objects::TCapWrapMode ThumbCapMode = {read=GetCapMode, write=SetCapMode, index=3, default=0};
	__property Fmx::Objects::TImageWrapMode ThumbWrapMode = {read=GetWrapMode, write=SetWrapMode, index=3, default=2};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmap = {read=GetOffObject, write=SetOffObject, index=6};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmapOn = {read=GetOnObject, write=SetOnObject, index=6};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmapEn = {read=GetOffObject, write=SetOffObject, index=7};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmapEnOn = {read=GetOnObject, write=SetOnObject, index=7};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmapJp = {read=GetOffObject, write=SetOffObject, index=8};
	__property Fmx::Styles::Objects::TBitmapLinks* TextBitmapJpOn = {read=GetOnObject, write=SetOnObject, index=8};
	__property System::UnicodeString SourceLookup = {read=GetSourceLookup, write=SetSourceLookup};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Switch */
}	/* namespace Styles */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_STYLES_SWITCH)
using namespace Fmx::Styles::Switch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_STYLES)
using namespace Fmx::Styles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Styles_SwitchHPP
