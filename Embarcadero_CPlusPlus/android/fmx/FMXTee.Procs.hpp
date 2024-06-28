// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Procs.pas' rev: 34.00 (Android)

#ifndef Fmxtee_ProcsHPP
#define Fmxtee_ProcsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Stdlib.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <System.Types.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Platform.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.UIConsts.hpp>
#include <System.UITypes.hpp>
#include <FMXTee.Canvas.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Procs
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMetafile;
class DELPHICLASS TCustomPanelNoCaption;
class DELPHICLASS TZoomPanning;
class DELPHICLASS TTeePanning;
class DELPHICLASS TTeeEvent;
__interface DELPHIINTERFACE ITeeEventListener;
typedef System::DelphiInterface<ITeeEventListener> _di_ITeeEventListener;
class DELPHICLASS TTeeMouseEvent;
class DELPHICLASS TTeeView3DEvent;
class DELPHICLASS TTeeDrawEvent;
class DELPHICLASS TCustomTeePanel;
class DELPHICLASS TTeeZoomPen;
class DELPHICLASS TTeeZoomBrush;
class DELPHICLASS TZoomSnapshot;
class DELPHICLASS TTeeZoom;
class DELPHICLASS TBackImage;
class DELPHICLASS TCustomTeePanelExtended;
class DELPHICLASS TTeeCustomShapeBrushPen;
class DELPHICLASS TShapeCallout;
class DELPHICLASS TTeeShapeItem;
class DELPHICLASS TTeeShapes;
class DELPHICLASS TTeeCustomShape;
class DELPHICLASS TTeeShape;
class DELPHICLASS TTeeExportData;
class DELPHICLASS TMouseLeaveEvent;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMetafile : public Fmx::Graphics::TBitmap
{
	typedef Fmx::Graphics::TBitmap inherited;
	
private:
	bool FEnhanced;
	
__published:
	__property bool Enhanced = {read=FEnhanced, write=FEnhanced, nodefault};
public:
	/* TBitmap.Create */ inline __fastcall virtual TMetafile()/* overload */ : Fmx::Graphics::TBitmap() { }
	/* TBitmap.Create */ inline __fastcall virtual TMetafile(const int AWidth, const int AHeight)/* overload */ : Fmx::Graphics::TBitmap(AWidth, AHeight) { }
	/* TBitmap.CreateFromStream */ inline __fastcall virtual TMetafile(System::Classes::TStream* const AStream) : Fmx::Graphics::TBitmap(AStream) { }
	/* TBitmap.CreateFromFile */ inline __fastcall virtual TMetafile(const System::UnicodeString AFileName) : Fmx::Graphics::TBitmap(AFileName) { }
	/* TBitmap.CreateFromBitmapAndMask */ inline __fastcall TMetafile(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Mask) : Fmx::Graphics::TBitmap(Bitmap, Mask) { }
	/* TBitmap.Destroy */ inline __fastcall virtual ~TMetafile() { }
	
};


typedef void __fastcall (__closure *TColorEvent)(const System::Uitypes::TAlphaColor aColor);

enum DECLSPEC_DENUM TDateTimeStep : unsigned char { dtOneMicroSecond, dtOneMillisecond, dtOneSecond, dtFiveSeconds, dtTenSeconds, dtFifteenSeconds, dtThirtySeconds, dtOneMinute, dtFiveMinutes, dtTenMinutes, dtFifteenMinutes, dtThirtyMinutes, dtOneHour, dtTwoHours, dtSixHours, dtTwelveHours, dtOneDay, dtTwoDays, dtThreeDays, dtOneWeek, dtHalfMonth, dtOneMonth, dtTwoMonths, dtThreeMonths, dtFourMonths, dtSixMonths, dtOneYear, dtNone };

typedef Fmx::Controls::TControl TCustomPanel;

enum DECLSPEC_DENUM TBorderStyle : unsigned char { bsNone, bsSingle };

enum DECLSPEC_DENUM TPanelBevel : unsigned char { bvNone, bvLowered, bvRaised };

_DECLARE_ARITH_TYPE_ALIAS(System::Int8, TBevelWidth);

class PASCALIMPLEMENTATION TCustomPanelNoCaption : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
public:
	__fastcall virtual TCustomPanelNoCaption(System::Classes::TComponent* AOwner);
	virtual void __fastcall Invalidate();
	__property ClipChildren = {default=1};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, default=-986896};
	
__published:
	__property Height;
	__property Position;
	__property Width;
public:
	/* TControl.Destroy */ inline __fastcall virtual ~TCustomPanelNoCaption() { }
	
};


class PASCALIMPLEMENTATION TZoomPanning : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FActive;
	
public:
	int X0;
	int Y0;
	int X1;
	int Y1;
	void __fastcall Check();
	void __fastcall Activate(int x, int y);
	__property bool Active = {read=FActive, write=FActive, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TZoomPanning() { }
	
public:
	/* TObject.Create */ inline __fastcall TZoomPanning() : System::Classes::TPersistent() { }
	
};


enum DECLSPEC_DENUM TMouseWheelStyle : unsigned char { pmwNormal, pmwInverted, pmwNone };

typedef TMouseWheelStyle TPanMouseWheel;

class PASCALIMPLEMENTATION TTeePanning : public TZoomPanning
{
	typedef TZoomPanning inherited;
	
private:
	bool FInsideBounds;
	TMouseWheelStyle FMouseWheel;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool InsideBounds = {read=FInsideBounds, write=FInsideBounds, default=0};
	__property TMouseWheelStyle MouseWheel = {read=FMouseWheel, write=FMouseWheel, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTeePanning() { }
	
public:
	/* TObject.Create */ inline __fastcall TTeePanning() : TZoomPanning() { }
	
};


class PASCALIMPLEMENTATION TTeeEvent : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TCustomTeePanel* Sender;
public:
	/* TObject.Create */ inline __fastcall TTeeEvent() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeEvent() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TTeeEventClass);

__interface ITeeEventListener  : public System::IInterface 
{
	virtual void __fastcall TeeEvent(TTeeEvent* Event) = 0 ;
};

typedef System::Generics::Collections::TList__1<_di_ITeeEventListener>* TTeeEventListeners;

enum DECLSPEC_DENUM TTeeMouseEventKind : unsigned char { meDown, meUp, meMove };

class PASCALIMPLEMENTATION TTeeMouseEvent : public TTeeEvent
{
	typedef TTeeEvent inherited;
	
public:
	TTeeMouseEventKind Event;
	System::Uitypes::TMouseButton Button;
	System::Classes::TShiftState Shift;
	float X;
	float Y;
public:
	/* TObject.Create */ inline __fastcall TTeeMouseEvent() : TTeeEvent() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeMouseEvent() { }
	
};


class PASCALIMPLEMENTATION TTeeView3DEvent : public TTeeEvent
{
	typedef TTeeEvent inherited;
	
public:
	/* TObject.Create */ inline __fastcall TTeeView3DEvent() : TTeeEvent() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeView3DEvent() { }
	
};


class PASCALIMPLEMENTATION TTeeDrawEvent : public TTeeEvent
{
	typedef TTeeEvent inherited;
	
public:
	/* TObject.Create */ inline __fastcall TTeeDrawEvent() : TTeeEvent() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeDrawEvent() { }
	
};


enum DECLSPEC_DENUM TTeeUnits : unsigned char { muPercent, muPixels };

typedef void __fastcall (__closure *TTeePrintEvent)(TCustomTeePanel* Sender, Fmx::Graphics::TCanvas* Canvas, System::Types::TRectF &R);

enum DECLSPEC_DENUM TTextFormat : unsigned char { ttfNormal, ttfHtml };

class PASCALIMPLEMENTATION TCustomTeePanel : public TCustomPanelNoCaption
{
	typedef TCustomPanelNoCaption inherited;
	
private:
	bool FApplyZOrder;
	bool FAutoRepaint;
	TPanelBevel FBevelInner;
	TPanelBevel FBevelOuter;
	TBevelWidth FBevelWidth;
	int FBorderWidth;
	Fmxtee::Canvas::TTeeHiddenPen* FBorder;
	int FBorderRound;
	bool FCancelMouse;
	System::Types::TRectF FChartBounds;
	int FChartWidth;
	int FChartHeight;
	int FChartXCenter;
	int FChartYCenter;
	Fmx::Graphics::TCanvas* FDelphiCanvas;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	Fmxtee::Canvas::TTeePicture* FGlobalPicture;
	int FHeight3D;
	System::Types::TRectF FMargins;
	TTeeUnits FMarginUnits;
	TTeePrintEvent FOnBeforePrint;
	System::Uitypes::TCursor FOriginalCursor;
	TTeePanning* FPanning;
	bool FPrinting;
	bool FPrintProportional;
	int FPrintResolution;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	bool FView3D;
	Fmxtee::Canvas::TView3DOptions* FView3DOptions;
	int FWidth3D;
	System::Classes::TComponent* FGLComponent;
	System::Generics::Collections::TList__1<_di_ITeeEventListener>* IEventListeners;
	System::Types::TRectF ICachedChartRect;
	System::Types::TPointF InitialSize;
	System::UnicodeString IDefaultCanvas;
	void __fastcall BroadcastMouseEvent(TTeeMouseEventKind Kind, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall CreateDefaultCanvas();
	int __fastcall FixBorderWidth(System::Types::TRectF &Rect);
	TBorderStyle __fastcall GetBorderStyle();
	bool __fastcall GetBufferedDisplay();
	int __fastcall GetMargin(int Index);
	bool __fastcall GetMonochrome();
	void __fastcall InvalidateEvent(System::TObject* Sender);
	void __fastcall InternalDoMouseLeave();
	void __fastcall NonBufferDraw(Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &R);
	void __fastcall ReadBorderStyle(System::Classes::TReader* Reader);
	void __fastcall ReadDefaultCanvas(System::Classes::TReader* Reader);
	void __fastcall WriteDefaultCanvas(System::Classes::TWriter* Writer);
	void __fastcall SetBevelInner(const TPanelBevel Value);
	void __fastcall SetBevelOuter(const TPanelBevel Value);
	void __fastcall SetBevelWidth(const TBevelWidth Value);
	void __fastcall SetBorderWidth(const int Value);
	void __fastcall SetBorder(Fmxtee::Canvas::TTeeHiddenPen* const Value);
	void __fastcall SetBorderRound(int Value);
	void __fastcall SetBufferedDisplay(bool Value);
	void __fastcall SetControlRounded();
	void __fastcall SetCustomChartRect(bool Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetMargin(int Index, int Value);
	void __fastcall SetMarginUnits(const TTeeUnits Value);
	void __fastcall SetMonochrome(bool Value);
	void __fastcall SetPanning(TTeePanning* const Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetTheBorderStyle(TBorderStyle Value);
	void __fastcall SetView3D(bool Value);
	void __fastcall SetView3DOptions(Fmxtee::Canvas::TView3DOptions* Value);
	
protected:
	bool DontShowImage;
	bool FCustomChartRect;
	bool IsEmbedded;
	Fmxtee::Canvas::TCanvas3D* InternalCanvas;
	void __fastcall ApplyMargins();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	int __fastcall BorderSize();
	TTeeEvent* __fastcall BroadcastTeeEvent(TTeeEvent* const Event);
	void __fastcall BroadcastTeeEventClass(const TTeeEventClass Event);
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DblClick();
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor();
	System::Types::TRectF __fastcall GetClientRect();
	virtual TCustomTeePanel* __fastcall GetEditablePanel();
	Fmxtee::Canvas::TFilterItems* __fastcall Filters();
	System::Types::TRectF __fastcall InternalCalcProportionalMargins(const int AWidth, const int AHeight, const int APageWidth, const int APageHeight, const double APageRatio);
	virtual void __fastcall InternalDraw(const System::Types::TRectF &UserRectangle);
	__property System::Generics::Collections::TList__1<_di_ITeeEventListener>* Listeners = {read=IEventListeners};
	virtual void __fastcall Loaded();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall Paint();
	System::Uitypes::TAlphaColor __fastcall PanelColor(const System::Uitypes::TAlphaColor AColor);
	System::Types::TRectF __fastcall PrintMarginsRect(const int AWidth, const int AHeight);
	virtual void __fastcall ReadState(System::Classes::TReader* Reader);
	void __fastcall AddListener(_di_ITeeEventListener Sender);
	void __fastcall RemoveListener(_di_ITeeEventListener Sender);
	virtual void __fastcall Resize();
	void __fastcall SetBooleanProperty(bool &Variable, bool Value);
	void __fastcall SetColorProperty(System::Uitypes::TAlphaColor &Variable, System::Uitypes::TAlphaColor Value);
	void __fastcall SetDoubleProperty(double &Variable, const double Value);
	void __fastcall SetIntegerProperty(int &Variable, int Value);
	void __fastcall SetSingleProperty(float &Variable, const float Value);
	void __fastcall SetStringProperty(System::UnicodeString &Variable, const System::UnicodeString Value);
	__property System::Classes::TComponent* GLComponent = {read=FGLComponent, write=FGLComponent};
	
public:
	System::Types::TRectF ChartRect;
	System::Types::TRectF PrintMargins;
	TCustomTeePanel* Theme;
	__fastcall virtual TCustomTeePanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomTeePanel();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall CalcMetaBounds(System::Types::TRectF &R, const System::Types::TRectF &AChartRect, /* out */ int &WinWidth, /* out */ int &WinHeight, /* out */ int &ViewWidth, /* out */ int &ViewHeight);
	System::Types::TRectF __fastcall CalcProportionalMargins();
	bool __fastcall CanClip();
	virtual void __fastcall CanvasChanged(System::TObject* Sender);
	System::Types::TRectF __fastcall ChartPrintRect();
	void __fastcall CopyToClipboardBitmap()/* overload */;
	void __fastcall CopyToClipboardBitmap(const System::Types::TRectF &R)/* overload */;
	void __fastcall CopyToClipboardMetafile(bool Enhanced)/* overload */;
	void __fastcall CopyToClipboardMetafile(bool Enhanced, const System::Types::TRectF &R)/* overload */;
	Fmx::Graphics::TBitmap* __fastcall TeeCreateBitmap(System::Uitypes::TAlphaColor ABackColor, const System::Types::TRectF &Rect, int ADpi = 0x0)/* overload */;
	Fmx::Graphics::TBitmap* __fastcall TeeCreateBitmap()/* overload */;
	virtual void __fastcall Draw(Fmx::Graphics::TCanvas* UserCanvas, const System::Types::TRectF &UserRect)/* overload */;
	void __fastcall Draw()/* overload */;
	DYNAMIC void __fastcall DrawPanelBevels(const System::Types::TRectF &Rect);
	void __fastcall DrawToMetaCanvas(Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &Rect);
	System::Types::TPointF __fastcall GetCursorPos();
	virtual System::Types::TRectF __fastcall GetRectangle();
	virtual void __fastcall Invalidate();
	bool __fastcall IsScreenHighColor();
	System::Types::TPointF __fastcall MultiLineTextSize(System::UnicodeString S, const TTextFormat TextFormat, /* out */ int &NumLines);
	int __fastcall MultiLineTextWidth(System::UnicodeString S, /* out */ int &NumLines, const TTextFormat TextFormat = (TTextFormat)(0x0));
	void __fastcall PrepareFont3D(Fmxtee::Canvas::TTeeFont* const AFont);
	void __fastcall Print();
	void __fastcall PrintLandscape();
	void __fastcall PrintOrientation(System::Uitypes::TPrinterOrientation AOrientation);
	void __fastcall PrintPartial(const System::Types::TRectF &PrinterRect);
	void __fastcall PrintPartialCanvas(Fmx::Graphics::TCanvas* const PrintCanvas, const System::Types::TRectF &PrinterRect);
	void __fastcall PrintPortrait();
	void __fastcall PrintRect(const System::Types::TRectF &R);
	void __fastcall SaveToBitmapFile(const System::UnicodeString FileName)/* overload */;
	void __fastcall SaveToBitmapFile(const System::UnicodeString FileName, const System::Types::TRectF &R)/* overload */;
	void __fastcall SaveToMetafile(const System::UnicodeString FileName);
	void __fastcall SaveToMetafileEnh(const System::UnicodeString FileName);
	void __fastcall SaveToMetafileRect(bool Enhanced, const System::UnicodeString FileName, const System::Types::TRectF &Rect);
	void __fastcall SetBrushCanvas(System::Uitypes::TAlphaColor AColor, Fmxtee::Canvas::TTeeBrush* const ABrush, System::Uitypes::TAlphaColor ABackColor);
	void __fastcall SetChartRect(const System::Types::TRectF &ARect);
	void __fastcall SetInternalCanvas(Fmxtee::Canvas::TCanvas3D* const NewCanvas);
	void __fastcall ReCalcWidthHeight();
	TMetafile* __fastcall TeeCreateMetafile(bool Enhanced, const System::Types::TRectF &Rect);
	__property bool ApplyZOrder = {read=FApplyZOrder, write=FApplyZOrder, nodefault};
	__property bool AutoRepaint = {read=FAutoRepaint, write=FAutoRepaint, nodefault};
	__property Fmxtee::Canvas::TTeeHiddenPen* Border = {read=FBorder, write=SetBorder};
	__property int BorderRound = {read=FBorderRound, write=SetBorderRound, default=0};
	__property TBorderStyle BorderStyle = {read=GetBorderStyle, write=SetTheBorderStyle, nodefault};
	__property bool BufferedDisplay = {read=GetBufferedDisplay, write=SetBufferedDisplay, nodefault};
	__property bool CancelMouse = {read=FCancelMouse, write=FCancelMouse, nodefault};
	__property Fmxtee::Canvas::TCanvas3D* Canvas = {read=InternalCanvas, write=SetInternalCanvas};
	__property System::Types::TRectF ChartBounds = {read=FChartBounds};
	__property int ChartHeight = {read=FChartHeight, nodefault};
	__property int ChartWidth = {read=FChartWidth, nodefault};
	__property int ChartXCenter = {read=FChartXCenter, nodefault};
	__property int ChartYCenter = {read=FChartYCenter, nodefault};
	__property bool CustomChartRect = {read=FCustomChartRect, write=SetCustomChartRect, nodefault};
	__property Fmx::Graphics::TCanvas* DelphiCanvas = {read=FDelphiCanvas};
	__property int Height3D = {read=FHeight3D, write=FHeight3D, nodefault};
	__property System::Uitypes::TCursor OriginalCursor = {read=FOriginalCursor, write=FOriginalCursor, nodefault};
	__property TTeePanning* Panning = {read=FPanning, write=SetPanning};
	__property bool Printing = {read=FPrinting, write=FPrinting, nodefault};
	__property int PrintResolution = {read=FPrintResolution, write=FPrintResolution, default=0};
	__property int Width3D = {read=FWidth3D, write=FWidth3D, nodefault};
	__property int MarginLeft = {read=GetMargin, write=SetMargin, index=0, default=3};
	__property int MarginTop = {read=GetMargin, write=SetMargin, index=1, default=4};
	__property int MarginRight = {read=GetMargin, write=SetMargin, index=2, default=3};
	__property int MarginBottom = {read=GetMargin, write=SetMargin, index=3, default=4};
	__property TTeeUnits MarginUnits = {read=FMarginUnits, write=SetMarginUnits, default=0};
	__property bool Monochrome = {read=GetMonochrome, write=SetMonochrome, default=0};
	__property bool PrintProportional = {read=FPrintProportional, write=FPrintProportional, default=1};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property bool View3D = {read=FView3D, write=SetView3D, default=1};
	__property Fmxtee::Canvas::TView3DOptions* View3DOptions = {read=FView3DOptions, write=SetView3DOptions};
	__property Fmxtee::Canvas::TView3DOptions* Aspect = {read=FView3DOptions, write=SetView3DOptions};
	__property Align = {default=0};
	__property Action;
	__property Anchors;
	__property TPanelBevel BevelInner = {read=FBevelInner, write=SetBevelInner, default=0};
	__property TPanelBevel BevelOuter = {read=FBevelOuter, write=SetBevelOuter, default=2};
	__property TBevelWidth BevelWidth = {read=FBevelWidth, write=SetBevelWidth, default=1};
	__property int BorderWidth = {read=FBorderWidth, write=SetBorderWidth, default=0};
	__property DragMode = {default=0};
	__property Enabled;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property Visible = {default=1};
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property TTeePrintEvent OnBeforePrint = {read=FOnBeforePrint, write=FOnBeforePrint};
};


typedef Fmxtee::Canvas::TTeeGradient TChartGradient;

_DECLARE_METACLASS(System::TMetaClass, TChartGradientClass);

enum DECLSPEC_DENUM TPanningMode : unsigned char { pmNone, pmHorizontal, pmVertical, pmBoth };

class PASCALIMPLEMENTATION TTeeZoomPen : public Fmxtee::Canvas::TTeePen
{
	typedef Fmxtee::Canvas::TTeePen inherited;
	
private:
	bool __fastcall IsColorStored();
	
protected:
	System::Uitypes::TAlphaColor DefaultColor;
	
__published:
	__property Color = {stored=IsColorStored};
	__property Width = {default=0};
public:
	/* TTeePen.Create */ inline __fastcall TTeeZoomPen(const System::Classes::TNotifyEvent OnChangeEvent) : Fmxtee::Canvas::TTeePen(OnChangeEvent) { }
	/* TTeePen.Destroy */ inline __fastcall virtual ~TTeeZoomPen() { }
	
};


class PASCALIMPLEMENTATION TTeeZoomBrush : public Fmxtee::Canvas::TTeeBrush
{
	typedef Fmxtee::Canvas::TTeeBrush inherited;
	
__published:
	__property Color = {default=-1};
	__property Style = {default=0};
public:
	/* TTeeBrush.Create */ inline __fastcall virtual TTeeZoomBrush(const System::Classes::TNotifyEvent OnChangeEvent) : Fmxtee::Canvas::TTeeBrush(OnChangeEvent) { }
	/* TTeeBrush.Destroy */ inline __fastcall virtual ~TTeeZoomBrush() { }
	
};


enum DECLSPEC_DENUM TTeeZoomDirection : unsigned char { tzdHorizontal, tzdVertical, tzdBoth };

class PASCALIMPLEMENTATION TZoomSnapshot : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<double> _TZoomSnapshot__1;
	
	typedef System::DynamicArray<double> _TZoomSnapshot__2;
	
	typedef System::DynamicArray<System::DynamicArray<double> > _TZoomSnapshot__3;
	
	
public:
	_TZoomSnapshot__1 AxesMinMax;
	int CustomCount;
	_TZoomSnapshot__3 CustomMinMax;
public:
	/* TObject.Create */ inline __fastcall TZoomSnapshot() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TZoomSnapshot() { }
	
};


typedef System::Generics::Collections::TObjectList__1<TZoomSnapshot*>* TZoomSnapshots;

class PASCALIMPLEMENTATION TTeeZoom : public TZoomPanning
{
	typedef TZoomPanning inherited;
	
private:
	bool FAllow;
	bool FAnimated;
	int FAnimatedSteps;
	System::Generics::Collections::TObjectList__1<TZoomSnapshot*>* FAxesHistory;
	TTeeZoomBrush* FBrush;
	TTeeZoomDirection FDirection;
	bool FFullRepaint;
	bool FHistory;
	bool FKeepAspect;
	System::Classes::TShiftState FKeyShift;
	int FMinimumPixels;
	System::Uitypes::TMouseButton FMouseButton;
	TMouseWheelStyle FMouseWheel;
	TTeeZoomPen* FPen;
	bool FUpLeftZooms;
	System::Generics::Collections::TObjectList__1<TZoomSnapshot*>* __fastcall GetAxesHistory();
	TTeeZoomBrush* __fastcall GetBrush();
	TTeeZoomPen* __fastcall GetPen();
	void __fastcall SetBrush(TTeeZoomBrush* const Value);
	void __fastcall SetHistory(bool Value);
	void __fastcall SetPen(TTeeZoomPen* const Value);
	
public:
	__fastcall TTeeZoom();
	__fastcall virtual ~TTeeZoom();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Generics::Collections::TObjectList__1<TZoomSnapshot*>* AxesHistory = {read=GetAxesHistory};
	
__published:
	__property bool Allow = {read=FAllow, write=FAllow, default=1};
	__property bool Animated = {read=FAnimated, write=FAnimated, default=0};
	__property int AnimatedSteps = {read=FAnimatedSteps, write=FAnimatedSteps, default=8};
	__property TTeeZoomBrush* Brush = {read=GetBrush, write=SetBrush};
	__property TTeeZoomDirection Direction = {read=FDirection, write=FDirection, default=2};
	__property bool FullRepaint = {read=FFullRepaint, write=FFullRepaint, default=1};
	__property bool History = {read=FHistory, write=SetHistory, default=0};
	__property bool KeepAspectRatio = {read=FKeepAspect, write=FKeepAspect, default=0};
	__property System::Classes::TShiftState KeyShift = {read=FKeyShift, write=FKeyShift, default=0};
	__property int MinimumPixels = {read=FMinimumPixels, write=FMinimumPixels, default=16};
	__property System::Uitypes::TMouseButton MouseButton = {read=FMouseButton, write=FMouseButton, default=0};
	__property TMouseWheelStyle MouseWheel = {read=FMouseWheel, write=FMouseWheel, default=2};
	__property TTeeZoomPen* Pen = {read=GetPen, write=SetPen};
	__property bool UpLeftZooms = {read=FUpLeftZooms, write=FUpLeftZooms, default=0};
};


enum DECLSPEC_DENUM TTeeBackImageMode : unsigned char { pbmStretch, pbmTile, pbmCenter, pbmCustom };

class PASCALIMPLEMENTATION TBackImage : public Fmxtee::Canvas::TTeePicture
{
	typedef Fmxtee::Canvas::TTeePicture inherited;
	
private:
	int FBottom;
	Fmxtee::Canvas::TCanvasStretchQuality FDrawQuality;
	bool FInside;
	int FLeft;
	TTeeBackImageMode FMode;
	int FRight;
	int FTop;
	void __fastcall DoChanged();
	HIDESBASE System::Types::TRectF __fastcall GetBounds();
	void __fastcall SetBottom(int Value);
	void __fastcall SetBounds(const System::Types::TRectF &Value);
	void __fastcall SetDrawQuality(const Fmxtee::Canvas::TCanvasStretchQuality Value);
	void __fastcall SetField(int &Variable, const int Value);
	void __fastcall SetInside(const bool Value);
	void __fastcall SetLeft(int Value);
	void __fastcall SetMode(const TTeeBackImageMode Value);
	void __fastcall SetRight(int Value);
	void __fastcall SetTop(int Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Draw(TCustomTeePanelExtended* const Panel, const System::Types::TRectF &Rect, int Z);
	__property System::Types::TRectF Bounds = {read=GetBounds, write=SetBounds};
	
__published:
	__property int Bottom = {read=FBottom, write=SetBottom, default=0};
	__property Fmxtee::Canvas::TCanvasStretchQuality DrawQuality = {read=FDrawQuality, write=SetDrawQuality, default=0};
	__property bool Inside = {read=FInside, write=SetInside, default=0};
	__property int Left = {read=FLeft, write=SetLeft, default=0};
	__property TTeeBackImageMode Mode = {read=FMode, write=SetMode, default=0};
	__property int Right = {read=FRight, write=SetRight, default=0};
	__property int Top = {read=FTop, write=SetTop, default=0};
public:
	/* TTeePicture.Destroy */ inline __fastcall virtual ~TBackImage() { }
	
public:
	/* TPicture.Create */ inline __fastcall TBackImage() : Fmxtee::Canvas::TTeePicture() { }
	
public:
	/* TBitmap.CreateFromStream */ inline __fastcall virtual TBackImage(System::Classes::TStream* const AStream) : Fmxtee::Canvas::TTeePicture(AStream) { }
	/* TBitmap.CreateFromFile */ inline __fastcall virtual TBackImage(const System::UnicodeString AFileName) : Fmxtee::Canvas::TTeePicture(AFileName) { }
	/* TBitmap.CreateFromBitmapAndMask */ inline __fastcall TBackImage(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Mask) : Fmxtee::Canvas::TTeePicture(Bitmap, Mask) { }
	
};


class PASCALIMPLEMENTATION TCustomTeePanelExtended : public TCustomTeePanel
{
	typedef TCustomTeePanel inherited;
	
private:
	TPanningMode FAllowPanning;
	Fmxtee::Canvas::TTeeGradient* FGradient;
	System::Uitypes::TMouseButton FScrollMouse;
	TTeeZoom* FZoom;
	TMouseWheelStyle FZoomWheel;
	bool FZoomed;
	bool __fastcall GetAllowZoom();
	bool __fastcall GetAnimatedZoom();
	int __fastcall GetAnimatedZoomSteps();
	TBackImage* __fastcall GetBackImage();
	bool __fastcall GetBackImageInside();
	TTeeBackImageMode __fastcall GetBackImageMode();
	bool __fastcall GetBackImageTransp();
	Fmxtee::Canvas::TTeeGradient* __fastcall GetGradient();
	void __fastcall ReadAnimatedZoomSteps(System::Classes::TReader* Reader);
	void __fastcall ReadAnimatedZoom(System::Classes::TReader* Reader);
	void __fastcall ReadAllowZoom(System::Classes::TReader* Reader);
	void __fastcall ReadPrintMargins(System::Classes::TReader* Reader);
	void __fastcall SavePrintMargins(System::Classes::TWriter* Writer);
	void __fastcall SetAllowZoom(bool Value);
	void __fastcall SetAnimatedZoom(bool Value);
	void __fastcall SetAnimatedZoomSteps(int Value);
	void __fastcall SetBackImage(TBackImage* const Value);
	void __fastcall SetBackImageInside(const bool Value);
	void __fastcall SetBackImageMode(const TTeeBackImageMode Value);
	void __fastcall SetBackImageTransp(const bool Value);
	void __fastcall SetGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetZoom(TTeeZoom* const Value);
	
protected:
	TBackImage* FBackImage;
	System::Classes::TNotifyEvent FOnAfterDraw;
	System::Classes::TNotifyEvent FOnScroll;
	System::Classes::TNotifyEvent FOnUndoZoom;
	System::Classes::TNotifyEvent FOnZoom;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall DrawBitmap(const System::Types::TRectF &Rect, int Z);
	virtual void __fastcall FillPanelRect(const System::Types::TRectF &Rect);
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor();
	virtual void __fastcall PanelPaint(const System::Types::TRectF &UserRect);
	void __fastcall TryDrawZoom();
	
public:
	__fastcall virtual TCustomTeePanelExtended(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomTeePanelExtended();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall DrawZoomRectangle();
	bool __fastcall HasBackImage();
	DYNAMIC void __fastcall UndoZoom();
	__property bool Zoomed = {read=FZoomed, write=FZoomed, nodefault};
	__property TPanningMode AllowPanning = {read=FAllowPanning, write=FAllowPanning, default=3};
	__property bool AllowZoom = {read=GetAllowZoom, write=SetAllowZoom, default=1};
	__property bool AnimatedZoom = {read=GetAnimatedZoom, write=SetAnimatedZoom, default=0};
	__property int AnimatedZoomSteps = {read=GetAnimatedZoomSteps, write=SetAnimatedZoomSteps, default=8};
	__property TBackImage* BackImage = {read=GetBackImage, write=SetBackImage};
	__property bool BackImageInside = {read=GetBackImageInside, write=SetBackImageInside, default=0};
	__property TTeeBackImageMode BackImageMode = {read=GetBackImageMode, write=SetBackImageMode, default=0};
	__property bool BackImageTransp = {read=GetBackImageTransp, write=SetBackImageTransp, default=1};
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=GetGradient, write=SetGradient};
	__property System::Uitypes::TMouseButton ScrollMouseButton = {read=FScrollMouse, write=FScrollMouse, default=1};
	__property TTeeZoom* Zoom = {read=FZoom, write=SetZoom};
	__property TMouseWheelStyle ZoomWheel = {read=FZoomWheel, write=FZoomWheel, default=2};
	__property System::Classes::TNotifyEvent OnAfterDraw = {read=FOnAfterDraw, write=FOnAfterDraw};
	__property System::Classes::TNotifyEvent OnScroll = {read=FOnScroll, write=FOnScroll};
	__property System::Classes::TNotifyEvent OnUndoZoom = {read=FOnUndoZoom, write=FOnUndoZoom};
	__property System::Classes::TNotifyEvent OnZoom = {read=FOnZoom, write=FOnZoom};
};


_DECLARE_METACLASS(System::TMetaClass, TChartBrushClass);

class PASCALIMPLEMENTATION TTeeCustomShapeBrushPen : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	Fmxtee::Canvas::TTeeBrush* FBrush;
	TCustomTeePanel* FParent;
	Fmxtee::Canvas::TTeePen* FPen;
	bool FVisible;
	bool __fastcall IsVisibleStored();
	void __fastcall SetBrush(Fmxtee::Canvas::TTeeBrush* const Value);
	void __fastcall SetPen(Fmxtee::Canvas::TTeePen* const Value);
	void __fastcall SetVisible(bool Value);
	
protected:
	bool DefaultVisible;
	Fmxtee::Canvas::TTeeTransform* Transform;
	void __fastcall CanvasChanged(System::TObject* Sender);
	DYNAMIC TChartBrushClass __fastcall GetBrushClass();
	virtual void __fastcall SetParent(TCustomTeePanel* Value);
	
public:
	__fastcall TTeeCustomShapeBrushPen();
	__fastcall virtual ~TTeeCustomShapeBrushPen();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Show();
	void __fastcall Hide();
	virtual void __fastcall Repaint();
	__property Fmxtee::Canvas::TTeeBrush* Brush = {read=FBrush, write=SetBrush};
	__property Fmxtee::Canvas::TTeePen* Frame = {read=FPen, write=SetPen};
	__property TCustomTeePanel* ParentChart = {read=FParent, write=SetParent};
	__property Fmxtee::Canvas::TTeePen* Pen = {read=FPen, write=SetPen};
	__property bool Visible = {read=FVisible, write=SetVisible, stored=IsVisibleStored, nodefault};
};


enum DECLSPEC_DENUM TShapeCalloutSide : unsigned char { csNone, csLeft, csTop, csRight, csBottom };

class PASCALIMPLEMENTATION TShapeCallout : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FPointPosition;
	int FPosition;
	TShapeCalloutSide FSide;
	int FSize;
	int FWidth;
	TTeeCustomShape* IOwner;
	void __fastcall SetPosition(const int Value);
	void __fastcall SetSide(const TShapeCalloutSide Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetWidth(const int Value);
	
protected:
	Fmxtee::Canvas::TTeeBasePath* __fastcall GetPath(Fmxtee::Canvas::TTeeCanvas* const ACanvas, const System::Types::TRectF &R, int Corner = 0x0);
	
public:
	__fastcall TShapeCallout(TTeeCustomShape* const AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property int PointPosition = {read=FPointPosition, write=FPointPosition, default=50};
	__property int Position = {read=FPosition, write=SetPosition, default=50};
	__property TShapeCalloutSide Side = {read=FSide, write=SetSide, default=0};
	__property int Size = {read=FSize, write=SetSize, default=25};
	__property int Width = {read=FWidth, write=SetWidth, default=20};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TShapeCallout() { }
	
};


class PASCALIMPLEMENTATION TTeeShapeItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TTeeCustomShape* FShape;
	TTeeCustomShape* __fastcall OwnerShape();
	void __fastcall SetShape(TTeeCustomShape* const Value);
	
public:
	__fastcall virtual TTeeShapeItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTeeShapeItem();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TTeeCustomShape* Shape = {read=FShape, write=SetShape};
};


_DECLARE_METACLASS(System::TMetaClass, TTeeCustomShapeClass);

class PASCALIMPLEMENTATION TTeeShapes : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTeeShapeItem* operator[](int Index) { return this->Item[Index]; }
	
private:
	TTeeCustomShapeClass IShapeClass;
	TTeeShapeItem* __fastcall Get(int Index);
	void __fastcall Put(int Index, TTeeShapeItem* const Value);
	
public:
	HIDESBASE TTeeShapeItem* __fastcall Add();
	__property TTeeShapeItem* Item[int Index] = {read=Get, write=Put/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TTeeShapes(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTeeShapes() { }
	
};


enum DECLSPEC_DENUM TTeeShapeLayout : unsigned char { slTopBottom, slLeftRight };

enum DECLSPEC_DENUM TChartObjectShapeStyle : unsigned char { fosRectangle, fosRoundRectangle, fosEllipse };

class PASCALIMPLEMENTATION TTeeCustomShape : public TTeeCustomShapeBrushPen
{
	typedef TTeeCustomShapeBrushPen inherited;
	
private:
	int FAngle;
	bool FAutoSize;
	TPanelBevel FBevel;
	TBevelWidth FBevelWidth;
	TShapeCallout* FCallout;
	TTeeShapes* FChildren;
	TTeeShapeLayout FChildLayout;
	System::Uitypes::TAlphaColor FColor;
	Fmxtee::Canvas::TTeeCorners* FCorners;
	Fmxtee::Canvas::TTeeFont* FFont;
	int FRoundSize;
	TChartObjectShapeStyle FShapeStyle;
	bool FTransparent;
	Fmxtee::Canvas::TVisualBlock* FVisual;
	TShapeCallout* __fastcall GetCallout();
	Fmxtee::Canvas::TTeeCorners* __fastcall GetCorners();
	Fmxtee::Canvas::TTeeEmboss* __fastcall GetEmboss();
	Fmxtee::Canvas::TTeeGradient* __fastcall GetGradient();
	float __fastcall GetHeight();
	float __fastcall GetWidth();
	TBackImage* __fastcall GetPicture();
	System::Uitypes::TAlphaColor __fastcall GetShadowColor();
	int __fastcall GetShadowSize();
	bool __fastcall IsChildrenStored();
	bool __fastcall IsPictureStored();
	bool __fastcall IsTranspStored();
	void __fastcall ReadShadowColor(System::Classes::TReader* Reader);
	void __fastcall ReadShadowSize(System::Classes::TReader* Reader);
	void __fastcall PictureChanged(System::TObject* Sender);
	void __fastcall SetAlignment(const System::Classes::TAlignment Value);
	void __fastcall SetAngle(const int Value);
	void __fastcall SetAutoSize(const bool Value);
	void __fastcall SetBevel(const TPanelBevel Value);
	void __fastcall SetBevelWidth(TBevelWidth Value);
	void __fastcall SetCallout(TShapeCallout* const Value);
	void __fastcall SetChildren(TTeeShapes* const Value);
	void __fastcall SetColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetCorners(Fmxtee::Canvas::TTeeCorners* const Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetFont(Fmxtee::Canvas::TTeeFont* const Value);
	void __fastcall SetGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetHeight(const float Value);
	void __fastcall SetLayout(const TTeeShapeLayout Value);
	void __fastcall SetPicture(TBackImage* const Value);
	void __fastcall SetRoundSize(int Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetShadowColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetShadowSize(int Value);
	void __fastcall SetShapeStyle(TChartObjectShapeStyle Value);
	void __fastcall SetTransparency(Fmxtee::Canvas::TTeeTransparency Value);
	void __fastcall SetTransparent(bool Value);
	void __fastcall SetWidth(const float Value);
	
protected:
	bool DefaultTransparent;
	System::Classes::TAlignment FAlignment;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	TBackImage* FPicture;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	Fmxtee::Canvas::TTeeTransparency FTransparency;
	bool FDraw3D;
	virtual void __fastcall CalcBounds(TCustomTeePanel* const Panel);
	bool __fastcall ClickedShape(const System::Types::TPointF &P, const System::Types::TRectF &R);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DoDraw(TCustomTeePanel* const Panel, const System::Types::TRectF &Rect, int Angle = 0x0, int AZ = 0x0);
	virtual int __fastcall FirstChildPos();
	virtual TTeeCustomShapeClass __fastcall GetChildClass();
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	bool __fastcall HasCorners();
	void __fastcall InitAngle(const int AAngle);
	DYNAMIC void __fastcall InitEmboss(Fmxtee::Canvas::TTeeEmboss* const AEmboss);
	DYNAMIC void __fastcall InitShadow(Fmxtee::Canvas::TTeeShadow* const AShadow);
	virtual void __fastcall SetParent(TCustomTeePanel* Value);
	__property Fmxtee::Canvas::TTeeTransparency Transparency = {read=FTransparency, write=SetTransparency, default=0};
	void __fastcall InitTransparent(const bool Value);
	__property Fmxtee::Canvas::TVisualBlock* Visual = {read=FVisual, write=FVisual};
	
public:
	System::Types::TRectF ShapeBounds;
	__fastcall virtual TTeeCustomShape(TCustomTeePanel* const AOwner)/* overload */;
	__fastcall virtual ~TTeeCustomShape();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Draw()/* overload */;
	void __fastcall Draw(const System::Types::TRectF &Rect, int Angle = 0x0, int AZ = 0x0)/* overload */;
	void __fastcall Draw(TCustomTeePanel* const Panel, const System::Types::TRectF &Rect, int Angle = 0x0, int AZ = 0x0)/* overload */;
	void __fastcall MoveTo(const System::Types::TPointF &P)/* overload */;
	void __fastcall MoveTo(const float x, const float y)/* overload */;
	__property System::Uitypes::TAlphaColor ShadowColor = {read=GetShadowColor, write=SetShadowColor, default=-16777216};
	__property int ShadowSize = {read=GetShadowSize, write=SetShadowSize, default=3};
	__property float Height = {read=GetHeight, write=SetHeight};
	__property float Width = {read=GetWidth, write=SetWidth};
	__property System::Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=0};
	__property int Angle = {read=FAngle, write=SetAngle, default=0};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=1};
	__property TPanelBevel Bevel = {read=FBevel, write=SetBevel, default=0};
	__property TBevelWidth BevelWidth = {read=FBevelWidth, write=SetBevelWidth, default=2};
	__property TTeeShapes* Children = {read=FChildren, write=SetChildren, stored=IsChildrenStored};
	__property TTeeShapeLayout ChildLayout = {read=FChildLayout, write=SetLayout, default=0};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, default=-1};
	__property Fmxtee::Canvas::TTeeCorners* Corners = {read=GetCorners, write=SetCorners, stored=HasCorners};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=GetEmboss, write=SetEmboss};
	__property Fmxtee::Canvas::TTeeFont* Font = {read=FFont, write=SetFont};
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=GetGradient, write=SetGradient, stored=false};
	__property TBackImage* Picture = {read=GetPicture, write=SetPicture, stored=IsPictureStored};
	__property int RoundSize = {read=FRoundSize, write=SetRoundSize, default=16};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property TShapeCallout* ShapeCallout = {read=GetCallout, write=SetCallout};
	__property TChartObjectShapeStyle ShapeStyle = {read=FShapeStyle, write=SetShapeStyle, default=0};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, stored=IsTranspStored, nodefault};
};


class PASCALIMPLEMENTATION TTeeShape : public TTeeCustomShape
{
	typedef TTeeCustomShape inherited;
	
public:
	__property Transparency = {default=0};
	
__published:
	__property Angle = {default=0};
	__property Bevel = {default=0};
	__property BevelWidth = {default=2};
	__property Children;
	__property ChildLayout = {default=0};
	__property Color = {default=-1};
	__property Corners;
	__property Emboss;
	__property Font;
	__property Gradient;
	__property Picture;
	__property RoundSize = {default=16};
	__property Shadow;
	__property ShapeCallout;
	__property ShapeStyle = {default=0};
	__property Transparent;
	__property Visible;
public:
	/* TTeeCustomShape.Create */ inline __fastcall virtual TTeeShape(TCustomTeePanel* const AOwner)/* overload */ : TTeeCustomShape(AOwner) { }
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TTeeShape() { }
	
};


enum DECLSPEC_DENUM TVertTextAlign : unsigned char { vtaCenter, vtaTop, vtaBottom };

typedef System::StaticArray<System::WideChar, 256> TeeString256;

class PASCALIMPLEMENTATION TTeeExportData : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	System::Sysutils::TEncoding* FileEncoding;
	virtual System::UnicodeString __fastcall AsString();
	DYNAMIC void __fastcall CopyToClipboard();
	DYNAMIC void __fastcall SaveToFile(const System::UnicodeString FileName);
	DYNAMIC void __fastcall SaveToStream(System::Classes::TStream* AStream);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TTeeExportData() { }
	
public:
	/* TObject.Create */ inline __fastcall TTeeExportData() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TMouseLeaveEvent : public TTeeEvent
{
	typedef TTeeEvent inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMouseLeaveEvent() : TTeeEvent() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMouseLeaveEvent() { }
	
};


typedef double TAxisValue;

typedef int __fastcall (__closure *TTeeSortCompare)(int a, int b);

typedef void __fastcall (__closure *TTeeSortSwap)(int a, int b);

typedef System::DynamicArray<System::Uitypes::TAlphaColor> TColorArray;

typedef Fmx::Types::TFmxObject TTranslatable;

typedef void __fastcall (*TTeeTranslateHook)(Fmx::Types::TFmxObject* const AControl, Fmx::Types::TFmxObject* const *ExcludedChilds, const int ExcludedChilds_High);

typedef System::UnicodeString __fastcall (*TTeeTranslateStringHook)(const System::UnicodeString Text);

typedef NativeUInt TeeWindowHandle;

typedef int __fastcall (*TTeeDownloadURLProc)(const System::UnicodeString URL, System::Classes::TStream* const ToStream, bool UseCache/* = false*/);

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 TeeDefVerticalMargin = System::Int8(0x4);
static constexpr System::Int8 TeeDefHorizMargin = System::Int8(0x3);
static constexpr System::Uitypes::TCursor crTeeHand = System::Uitypes::TCursor(2020);
#define TeeMsg_TeeHand u"crTeeHand"
static constexpr System::Int8 TeeNormalPrintDetail = System::Int8(0x0);
static constexpr System::Int8 TeeHighPrintDetail = System::Int8(-100);
static constexpr System::Int8 TeeDefault_PrintMargin = System::Int8(0xf);
static constexpr System::Int8 MaxDefaultColors = System::Int8(0x13);
static constexpr System::WideChar TeeTabDelimiter = (System::WideChar)(0x9);
#define TeeTextLineSeparator u"\r\n"
extern DELPHI_PACKAGE System::WideChar TeeLineSeparator;
extern DELPHI_PACKAGE bool TeeClipWhenPrinting;
extern DELPHI_PACKAGE bool TeeClipWhenMetafiling;
extern DELPHI_PACKAGE bool TeeEraseBack;
extern DELPHI_PACKAGE bool PrintTeePanel;
extern DELPHI_PACKAGE System::UnicodeString TeeDefaultCanvas;
extern DELPHI_PACKAGE System::StaticArray<double, 28> DateTimeStep;
static constexpr System::Int8 bsDialog = System::Int8(0x1);
static constexpr System::Int8 bsSizeable = System::Int8(0x2);
static constexpr unsigned clWhite = unsigned(0xffffffff);
extern DELPHI_PACKAGE System::UnicodeString TeeFieldsSeparator;
extern DELPHI_PACKAGE TColorArray TeeColorPalette;
static constexpr System::Int8 TeeBorderStyle = System::Int8(0x2);
static constexpr System::Int8 TeeKey_Escape = System::Int8(0x1b);
static constexpr System::Int8 TeeKey_Up = System::Int8(0x26);
static constexpr System::Int8 TeeKey_Down = System::Int8(0x28);
static constexpr System::Int8 TeeKey_Insert = System::Int8(0x2d);
static constexpr System::Int8 TeeKey_Delete = System::Int8(0x2e);
static constexpr System::Int8 TeeKey_Left = System::Int8(0x25);
static constexpr System::Int8 TeeKey_Right = System::Int8(0x27);
static constexpr System::Int8 TeeKey_Return = System::Int8(0xd);
static constexpr System::Int8 TeeKey_Space = System::Int8(0x20);
static constexpr System::Int8 TeeKey_Back = System::Int8(0x8);
static constexpr System::Int8 TeeKey_Home = System::Int8(0x24);
static constexpr System::Int8 TeeKey_Prior = System::Int8(0x21);
static constexpr System::Int8 TeeKey_Next = System::Int8(0x22);
static constexpr System::Int8 TeeKey_End = System::Int8(0x23);
static constexpr System::Int8 TeeKey_F1 = System::Int8(0x70);
static constexpr System::Int8 TeeKey_F2 = System::Int8(0x71);
static constexpr System::Int8 TeeKey_F3 = System::Int8(0x72);
static constexpr System::Int8 TeeKey_F4 = System::Int8(0x73);
static constexpr System::Int8 TeeKey_F5 = System::Int8(0x74);
static constexpr System::Int8 TeeKey_F6 = System::Int8(0x75);
static constexpr System::Int8 TeeKey_F7 = System::Int8(0x76);
static constexpr System::Int8 TeeKey_F8 = System::Int8(0x77);
static constexpr System::Int8 TeeKey_F9 = System::Int8(0x78);
static constexpr System::Int8 TeeKey_F10 = System::Int8(0x79);
static constexpr System::Int8 TeeKey_F11 = System::Int8(0x7a);
static constexpr System::Int8 TeeKey_F12 = System::Int8(0x7b);
static constexpr System::Int8 TeeKey_F13 = System::Int8(0x7c);
static constexpr System::Int8 TeeKey_F14 = System::Int8(0x7d);
static constexpr System::Int8 TeeKey_F15 = System::Int8(0x7e);
static constexpr System::Int8 TeeKey_F16 = System::Int8(0x7f);
static constexpr System::Byte TeeKey_F17 = System::Byte(0x80);
static constexpr System::Byte TeeKey_F18 = System::Byte(0x81);
static constexpr System::Byte TeeKey_F19 = System::Byte(0x82);
static constexpr System::Byte TeeKey_F20 = System::Byte(0x83);
static constexpr System::Byte TeeKey_F21 = System::Byte(0x84);
static constexpr System::Byte TeeKey_F22 = System::Byte(0x85);
static constexpr System::Byte TeeKey_F23 = System::Byte(0x86);
static constexpr System::Byte TeeKey_F24 = System::Byte(0x87);
extern DELPHI_PACKAGE TTeeTranslateHook TeeTranslateHook;
extern DELPHI_PACKAGE TTeeTranslateStringHook TeeTranslateStringHook;
#define TeeRADXE2_SpecialWWW u"http://www.steema.com/linkIn/TeeChartForXE2"
#define TeeRADXE2_SpecialOffer u"Upgrade to Standard or Pro version with 100% source code !"
extern DELPHI_PACKAGE TTeeDownloadURLProc TeeDownloadURLProc;
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeStr(const int Num);
extern DELPHI_PACKAGE int __fastcall StringContains(const System::UnicodeString SubStr, const System::UnicodeString S);
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall GetDefaultColor(const int Index);
extern DELPHI_PACKAGE System::Word __fastcall DaysInMonth(const System::Word Year, const System::Word Month);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DateTimeDefaultFormat(const double AStep);
extern DELPHI_PACKAGE double __fastcall NextDateTimeStep(const double AStep);
extern DELPHI_PACKAGE TDateTimeStep __fastcall FindDateTimeStep(const double StepValue);
extern DELPHI_PACKAGE System::Types::TPointF __fastcall TeeGetScreenSize(void);
extern DELPHI_PACKAGE void __fastcall TeeChangeCursor(System::TObject* const AOwner, System::Uitypes::TCursor ACursor);
extern DELPHI_PACKAGE double __fastcall ScreenRatio(Fmxtee::Canvas::TCanvas3D* const ACanvas);
extern DELPHI_PACKAGE void __fastcall DrawBevel(Fmxtee::Canvas::TTeeCanvas* const Canvas, TPanelBevel Bevel, System::Types::TRectF &R, int Width, int Round = 0x0);
extern DELPHI_PACKAGE void __fastcall RectToFourPoints(const System::Types::TRectF &ARect, const double Angle, /* out */ Fmxtee::Canvas::TFourPoints &P);
extern DELPHI_PACKAGE float __fastcall TeeTickCount(void);
extern DELPHI_PACKAGE void __fastcall TeePrepareXorPen(TCustomTeePanelExtended* const APanel, Fmxtee::Canvas::TTeePen* const APen);
extern DELPHI_PACKAGE void __fastcall TeeCopyClipboard(const System::UnicodeString Text);
extern DELPHI_PACKAGE System::Types::TRectF __fastcall RectFromCenter(const System::Types::TPointF &P, int AHalfWidth, int AHalfHeight = 0x0)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall RectFromCenter(const float X, const float Y, int AHalfWidth, int AHalfHeight = 0x0)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInLine(const System::Types::TPointF &P, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint, const int TolerancePixels)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInLine(const System::Types::TPointF &P, const float px, const float py, const float qx, const float qy, const float TolerancePixels)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInLineTolerance _DEPRECATED_ATTRIBUTE1("Please use PointInLine function.") (const System::Types::TPointF &P, const int px, const int py, const int qx, const int qy, const int TolerancePixels);
extern DELPHI_PACKAGE bool __fastcall PointInLine(const System::Types::TPointF &P, const int px, const int py, const int qx, const int qy)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInLine(const System::Types::TPointF &P, const System::Types::TPointF &FromPoint, const System::Types::TPointF &ToPoint)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInPolygon(const System::Types::TPointF &P, const System::Types::TPointF *Poly, const int Poly_High);
extern DELPHI_PACKAGE bool __fastcall PointInTriangle(const System::Types::TPointF &P, const System::Types::TPointF &P0, const System::Types::TPointF &P1, const System::Types::TPointF &P2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInTriangle(const System::Types::TPointF &P, const float X0, const float X1, const float Y0, const float Y1)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInHorizTriangle(const System::Types::TPointF &P, const float Y0, const float Y1, const float X0, const float X1);
extern DELPHI_PACKAGE bool __fastcall PointInEllipse(const System::Types::TPointF &P, const float Left, const float Top, const float Right, const float Bottom)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PointInEllipse(const System::Types::TPointF &P, const System::Types::TRectF &Rect)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall DelphiToLocalFormat(const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall LocalToDelphiFormat(const System::UnicodeString Format);
extern DELPHI_PACKAGE void __fastcall EnableControls(bool Enable, Fmx::Controls::TControl* const *ControlArray, const int ControlArray_High);
extern DELPHI_PACKAGE System::TDateTime __fastcall TeeRoundDate(const System::TDateTime ADate, TDateTimeStep AStep);
extern DELPHI_PACKAGE void __fastcall TeeDateTimeIncrement(bool IsDateTime, bool Increment, double &Value, const double AnIncrement, TDateTimeStep tmpWhichDateTime);
extern DELPHI_PACKAGE void __fastcall TeeSort(int StartIndex, int EndIndex, TTeeSortCompare CompareFunc, TTeeSortSwap SwapFunc);
extern DELPHI_PACKAGE System::Classes::TComponentName __fastcall TeeGetUniqueName(System::Classes::TComponent* const AOwner, const System::UnicodeString AStartName);
extern DELPHI_PACKAGE int __fastcall TeeNumFields(System::UnicodeString St)/* overload */;
extern DELPHI_PACKAGE int __fastcall TeeNumFields(const System::UnicodeString St, const System::UnicodeString Separator)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeExtractField(System::UnicodeString St, int Index)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeExtractField(System::UnicodeString St, int Index, const System::UnicodeString Separator)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeLoadBitmap(Fmx::Graphics::TBitmap* const Bitmap, const System::UnicodeString Name1, const System::UnicodeString Name2 = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall TeeGetBitmapEditor(System::TObject* const AObject, Fmx::Graphics::TBitmap* &Bitmap);
extern DELPHI_PACKAGE bool __fastcall CrossingLines(const double X1, const double Y1, const double X2, const double Y2, const double X3, const double Y3, const double X4, const double Y4, /* out */ double &x, /* out */ double &y);
extern DELPHI_PACKAGE void __fastcall TeeTranslateControl(Fmx::Types::TFmxObject* const AControl, Fmx::Types::TFmxObject* const *ExcludeChilds, const int ExcludeChilds_High)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeTranslateControl(Fmx::Types::TFmxObject* const AControl)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeTranslateString(const System::UnicodeString Text);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ReplaceChar(const System::UnicodeString AString, const System::WideChar Search, const System::WideChar Replace = (System::WideChar)(0x0));
extern DELPHI_PACKAGE Fmx::Graphics::TBitmap* __fastcall TeeAntiAlias(TCustomTeePanel* const Panel, bool ChartRect = false);
extern DELPHI_PACKAGE void __fastcall SetDefaultColorPalette(void)/* overload */;
extern DELPHI_PACKAGE void __fastcall SetDefaultColorPalette(const System::Uitypes::TAlphaColor *Palette, const int Palette_High)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeLoadFormPosition(Fmx::Forms::TForm* const AForm, const System::UnicodeString AKey, bool Position, bool Size);
extern DELPHI_PACKAGE void __fastcall TeeSaveFormPosition(Fmx::Forms::TForm* const AForm, const System::UnicodeString AKey, bool Position, bool Size);
extern DELPHI_PACKAGE bool __fastcall TeeReadBoolOption(const System::UnicodeString AKey, bool DefaultValue);
extern DELPHI_PACKAGE void __fastcall TeeSaveBoolOption(const System::UnicodeString AKey, bool Value);
extern DELPHI_PACKAGE int __fastcall TeeReadIntegerOption(const System::UnicodeString AKey, int DefaultValue);
extern DELPHI_PACKAGE void __fastcall TeeSaveIntegerOption(const System::UnicodeString AKey, int Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeReadStringOption(const System::UnicodeString AKey, const System::UnicodeString DefaultValue);
extern DELPHI_PACKAGE void __fastcall TeeSaveStringOption(const System::UnicodeString AKey, const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeDefaultXMLEncoding(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeXMLHeader(const System::UnicodeString Encoding);
extern DELPHI_PACKAGE void __fastcall ConvertTextToXML(System::Classes::TStream* const Stream, bool XMLHeader = true);
extern DELPHI_PACKAGE System::Classes::TStringList* __fastcall TeeGetFilesFromDir(const System::UnicodeString PathAndWildcards);
extern DELPHI_PACKAGE bool __fastcall TeeIsURL(System::UnicodeString St);
extern DELPHI_PACKAGE void __fastcall TeeGotoURL(NativeUInt Handle, const System::UnicodeString URL);
extern DELPHI_PACKAGE void __fastcall RemoveControls(Fmx::Types::TFmxObject* const AControl);
extern DELPHI_PACKAGE System::UnicodeString __fastcall RemoveFileExtension(const System::UnicodeString S);
extern DELPHI_PACKAGE void __fastcall RegisterSeriesEditor(const System::Classes::TPersistentClass AClass);
}	/* namespace Procs */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_PROCS)
using namespace Fmxtee::Procs;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_ProcsHPP
