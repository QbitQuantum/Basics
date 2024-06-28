// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Series.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_SeriesHPP
#define Fmxtee_SeriesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <FMX.Types.hpp>
#include <System.UIConsts.hpp>
#include <FMX.Graphics.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Procs.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Series
{
//-- forward type declarations -----------------------------------------------
struct TPieAngle;
class DELPHICLASS TCustomLineSeries;
class DELPHICLASS TSeriesPointerItems;
class DELPHICLASS TCustomSeries;
class DELPHICLASS TLineSeries;
class DELPHICLASS THorizLineSeries;
class DELPHICLASS TPointSeries;
class DELPHICLASS TAreaSeries;
class DELPHICLASS THorizAreaSeries;
class DELPHICLASS TCustomBarSeries;
class DELPHICLASS TBarSeries;
class DELPHICLASS THorizBarSeries;
class DELPHICLASS TFrameBrush;
class DELPHICLASS TFramedBorder;
class DELPHICLASS TCircularFrame;
class DELPHICLASS TCircledSeries;
class DELPHICLASS TSliceValueList;
class DELPHICLASS TPieOtherSlice;
class DELPHICLASS TPieMarks;
class DELPHICLASS TPieBevel;
class DELPHICLASS TPieSeries;
class DELPHICLASS TFastLineSeries;
//-- type declarations -------------------------------------------------------
#pragma pack(push,1)
struct DECLSPEC_DRECORD TPieAngle
{
public:
	double StartAngle;
	double MidAngle;
	double EndAngle;
};
#pragma pack(pop)


typedef System::DynamicArray<TPieAngle> TPieAngles;

class PASCALIMPLEMENTATION TCustomLineSeries : public Fmxtee::Engine::TChartSeries
{
	typedef Fmxtee::Engine::TChartSeries inherited;
	
protected:
	Fmxtee::Canvas::TTeePen* __fastcall GetLinePen();
	
public:
	__property Fmxtee::Canvas::TTeePen* LinePen = {read=GetLinePen, write=SetPen};
public:
	/* TChartSeries.Create */ inline __fastcall virtual TCustomLineSeries(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TChartSeries(AOwner) { }
	/* TChartSeries.Destroy */ inline __fastcall virtual ~TCustomLineSeries() { }
	
};


class PASCALIMPLEMENTATION TSeriesPointerItems : public Fmxtee::Engine::TSeriesPointer
{
	typedef Fmxtee::Engine::TSeriesPointer inherited;
	
public:
	Fmxtee::Engine::TSeriesPointer* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Generics::Collections::TList__1<Fmxtee::Engine::TSeriesPointer*>* IList;
	void __fastcall Delete(int Index);
	void __fastcall Ensure(int Index);
	Fmxtee::Engine::TSeriesPointer* __fastcall Get(int Index);
	void __fastcall InternalPut(int Index, Fmxtee::Engine::TSeriesPointer* const Value);
	void __fastcall Put(int Index, Fmxtee::Engine::TSeriesPointer* const Value);
	
protected:
	Fmxtee::Engine::TSeriesPointer* __fastcall InternalGet(int Index);
	
public:
	__fastcall virtual ~TSeriesPointerItems();
	void __fastcall Clear();
	int __fastcall Count();
	__property Fmxtee::Engine::TSeriesPointer* Items[int Index] = {read=Get, write=Put/*, default*/};
public:
	/* TSeriesPointer.Create */ inline __fastcall TSeriesPointerItems(Fmxtee::Engine::TChartSeries* const AOwner) : Fmxtee::Engine::TSeriesPointer(AOwner) { }
	
};


typedef void __fastcall (__closure *TSeriesClickPointerEvent)(TCustomSeries* Sender, int ValueIndex, int X, int Y);

enum DECLSPEC_DENUM TCustomSeriesStack : unsigned char { cssNone, cssOverlap, cssStack, cssStack100 };

typedef Fmxtee::Engine::TSeriesPointerStyle __fastcall (__closure *TOnGetPointerStyle)(Fmxtee::Engine::TChartSeries* Sender, int ValueIndex);

enum DECLSPEC_DENUM TCustomSeriesDrawStyle : unsigned char { dsSegments, dsAll, dsCurve };

class PASCALIMPLEMENTATION TCustomSeries : public TCustomLineSeries
{
	typedef TCustomLineSeries inherited;
	
private:
	Fmxtee::Canvas::TTeeBrush* FAreaBrush;
	System::Uitypes::TAlphaColor FAreaColor;
	Fmxtee::Canvas::TTeePen* FAreaLinesPen;
	bool FClickableLine;
	int FClickTolerance;
	bool FColorEachLine;
	bool FDark3D;
	bool FDrawArea;
	bool FDrawLine;
	TCustomSeriesDrawStyle FDrawStyle;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	bool FInflateMargins;
	bool FInvertedStairs;
	int FLineHeight;
	Fmxtee::Canvas::TTeeHiddenPen* FOutLine;
	TSeriesPointerItems* FPointer;
	bool FPointerBehind;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	TCustomSeriesStack FStacked;
	bool FStairs;
	bool FDirty;
	TSeriesClickPointerEvent FOnClickPointer;
	TOnGetPointerStyle FOnGetPointerStyle;
	int BottomPos;
	int OldBottomPos;
	int OldX;
	int OldY;
	System::Uitypes::TAlphaColor OldColor;
	double tmpDark3DRatio;
	bool HasTemplate;
	System::Types::TRectF IClientRect;
	int __fastcall CalcPosLeftRight(const double ALimit, int ValueIndex, int AnotherIndex);
	int __fastcall CalcStackedPos(int ValueIndex, double Value);
	void __fastcall ChangedBrush(System::TObject* Sender);
	bool __fastcall DoDrawAll(Fmxtee::Canvas::TTeePen* const APen, System::Uitypes::TAlphaColor AColor, bool DrawPoints);
	Fmx::Graphics::TBrushKind __fastcall GetAreaBrush();
	Fmx::Graphics::TBrushKind __fastcall GetLineBrush();
	Fmxtee::Canvas::TTeeHiddenPen* __fastcall GetOutLine();
	void __fastcall InternalCalcMargin(bool SameSide, bool Horizontal, int &A, int &B);
	double __fastcall PointOrigin(int ValueIndex, bool SumAll);
	void __fastcall SetAreaBrush(Fmxtee::Canvas::TTeeBrush* const Value);
	void __fastcall SetAreaBrushStyle(const Fmx::Graphics::TBrushKind Value);
	void __fastcall SetAreaColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetAreaLinesPen(Fmxtee::Canvas::TTeePen* const Value);
	void __fastcall SetColorEachLine(const bool Value);
	void __fastcall SetDark3D(bool Value);
	void __fastcall SetDrawArea(bool Value);
	void __fastcall SetDrawStyle(const TCustomSeriesDrawStyle Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetInflateMargins(bool Value);
	void __fastcall SetInvertedStairs(bool Value);
	void __fastcall SetLineBrush(const Fmx::Graphics::TBrushKind Value);
	void __fastcall SetLineHeight(int Value);
	void __fastcall SetOutLine(Fmxtee::Canvas::TTeeHiddenPen* const Value);
	void __fastcall SetPointer(TSeriesPointerItems* const Value);
	void __fastcall SetPointerBehind(const bool Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetStacked(const TCustomSeriesStack Value);
	void __fastcall SetStairs(bool Value);
	
protected:
	float DisplayLast;
	virtual void __fastcall AssignFormatting(Fmxtee::Engine::TChartSeries* Source);
	virtual void __fastcall CalcHorizMargins(int &LeftMargin, int &RightMargin);
	virtual int __fastcall CalcMarkLength();
	virtual double __fastcall CalcMinMaxValue(bool IsMin);
	virtual void __fastcall CalcVerticalMargins(int &TopMargin, int &BottomMargin);
	virtual void __fastcall CalcZOrder();
	virtual bool __fastcall ClickedPointer(int ValueIndex, int tmpX, int tmpY, int x, int y)/* overload */;
	virtual void __fastcall DoBeforeDrawChart();
	Fmxtee::Engine::TSeriesPointerStyle __fastcall DoGetPointerStyle(int ValueIndex);
	virtual void __fastcall DrawAllValues();
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRectF &Rect);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	DYNAMIC void __fastcall DrawPointer(int AX, int AY, System::Uitypes::TAlphaColor AColor, int ValueIndex);
	virtual void __fastcall DrawValue(int ValueIndex);
	virtual void __fastcall DrawHiddenValue(int ValueIndex, const double StartValue, const double EndValue, int GapSize, Fmxtee::Engine::TChartAxis* Axis);
	System::Uitypes::TAlphaColor __fastcall GetAreaBrushColor(System::Uitypes::TAlphaColor AColor);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual Fmxtee::Canvas::TTeeGradient* __fastcall GetGradient();
	void __fastcall InitDrawValue(int ValueIndex);
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=GetGradient, write=SetGradient};
	void __fastcall LinePrepareCanvas(Fmxtee::Canvas::TCanvas3D* const ACanvas, System::Uitypes::TAlphaColor tmpColor);
	virtual void __fastcall MouseDown(int ValueIndex, bool AtPointer, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall PreparePointer(int ValueIndex);
	virtual bool __fastcall SameClassOrigin(Fmxtee::Engine::TChartSeries* ASeries);
	virtual void __fastcall SetParentChart(Fmxtee::Engine::TCustomAxisPanel* const Value);
	__property TCustomSeriesStack Stacked = {read=FStacked, write=SetStacked, default=0};
	__property Transparency = {default=0};
	virtual bool __fastcall IsPointInChartRect(int ValueIndex);
	virtual bool __fastcall RaiseClicked();
	
public:
	__fastcall virtual TCustomSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomSeries();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CalcFirstLastVisibleIndex();
	virtual int __fastcall CalcXPos(int ValueIndex);
	virtual int __fastcall CalcYPos(int ValueIndex);
	virtual void __fastcall Clear();
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	virtual void __fastcall Delete(int ValueIndex)/* overload */;
	virtual int __fastcall GetOriginPos(int ValueIndex);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	virtual void __fastcall ResetBrush();
	DYNAMIC void __fastcall SwapValueIndex(int a, int b);
	__property Fmx::Graphics::TBrushKind AreaBrush = {read=GetAreaBrush, write=SetAreaBrushStyle, default=1};
	__property Fmxtee::Canvas::TTeeBrush* AreaChartBrush = {read=FAreaBrush, write=SetAreaBrush};
	__property System::Uitypes::TAlphaColor AreaColor = {read=FAreaColor, write=SetAreaColor, default=16777215};
	__property Fmxtee::Canvas::TTeePen* AreaLinesPen = {read=FAreaLinesPen, write=SetAreaLinesPen};
	__property bool ClickableLine = {read=FClickableLine, write=FClickableLine, default=1};
	__property int ClickTolerance = {read=FClickTolerance, write=FClickTolerance, default=0};
	__property bool ColorEachLine = {read=FColorEachLine, write=SetColorEachLine, default=1};
	__property bool Dark3D = {read=FDark3D, write=SetDark3D, default=1};
	__property bool DrawArea = {read=FDrawArea, write=SetDrawArea, default=0};
	__property TCustomSeriesDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=0};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property bool InflateMargins = {read=FInflateMargins, write=SetInflateMargins, default=1};
	__property bool InvertedStairs = {read=FInvertedStairs, write=SetInvertedStairs, default=0};
	__property Fmx::Graphics::TBrushKind LineBrush = {read=GetLineBrush, write=SetLineBrush, default=1};
	__property int LineHeight = {read=FLineHeight, write=SetLineHeight, default=0};
	__property Fmxtee::Canvas::TTeeHiddenPen* OutLine = {read=GetOutLine, write=SetOutLine};
	__property TSeriesPointerItems* Pointer = {read=FPointer, write=SetPointer};
	__property bool PointerBehind = {read=FPointerBehind, write=SetPointerBehind, default=0};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property bool Stairs = {read=FStairs, write=SetStairs, default=0};
	__property TSeriesClickPointerEvent OnClickPointer = {read=FOnClickPointer, write=FOnClickPointer};
	
__published:
	__property TOnGetPointerStyle OnGetPointerStyle = {read=FOnGetPointerStyle, write=FOnGetPointerStyle};
	/* Hoisted overloads: */
	
protected:
	inline bool __fastcall  ClickedPointer(int ValueIndex, int tmpX, int tmpY, const System::Types::TPointF &P){ return Fmxtee::Engine::TChartSeries::ClickedPointer(ValueIndex, tmpX, tmpY, P); }
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Fmxtee::Engine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPointF &P){ return Fmxtee::Engine::TChartSeries::Clicked(P); }
	inline void __fastcall  Delete(int Start, int Quantity, bool RemoveGap = false){ Fmxtee::Engine::TChartSeries::Delete(Start, Quantity, RemoveGap); }
	
};


class PASCALIMPLEMENTATION TLineSeries : public TCustomSeries
{
	typedef TCustomSeries inherited;
	
protected:
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	
public:
	__fastcall virtual TLineSeries(System::Classes::TComponent* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property Active = {default=1};
	__property ColorEachLine = {default=1};
	__property ColorEachPoint = {default=0};
	__property ColorSource = {default=0};
	__property Cursor = {default=0};
	__property Depth = {default=-1};
	__property Emboss;
	__property Gradient;
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property SeriesColor;
	__property Shadow;
	__property ShowInLegend = {default=1};
	__property Stacked = {default=0};
	__property Title = {default=0};
	__property ValueFormat = {default=0};
	__property VertAxis = {default=0};
	__property XLabelsSource = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property Brush;
	__property ClickableLine = {default=1};
	__property ClickTolerance = {default=0};
	__property Dark3D = {default=1};
	__property DrawStyle = {default=0};
	__property InflateMargins = {default=1};
	__property InvertedStairs = {default=0};
	__property LineBrush = {default=1};
	__property LineHeight = {default=0};
	__property LinePen;
	__property OutLine;
	__property Pointer;
	__property PointerBehind = {default=0};
	__property Stairs = {default=0};
	__property TreatNulls = {default=0};
	__property XValues;
	__property YValues;
	__property Transparency = {default=0};
	__property OnClickPointer;
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~TLineSeries() { }
	
};


class PASCALIMPLEMENTATION THorizLineSeries : public TLineSeries
{
	typedef TLineSeries inherited;
	
protected:
	virtual int __fastcall CalcMarkLength();
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	
public:
	__fastcall virtual THorizLineSeries(System::Classes::TComponent* AOwner);
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~THorizLineSeries() { }
	
};


class PASCALIMPLEMENTATION TPointSeries : public TCustomSeries
{
	typedef TCustomSeries inherited;
	
private:
	void __fastcall SetFixed();
	
protected:
	__classmethod virtual bool __fastcall CanDoExtra();
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	DYNAMIC void __fastcall PrepareForGallery();
	virtual void __fastcall SetColorEachPoint(bool Value);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	virtual void __fastcall SetTransparency(const Fmxtee::Canvas::TTeeTransparency Value);
	
public:
	__fastcall virtual TPointSeries(System::Classes::TComponent* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property Active = {default=1};
	__property ColorEachPoint = {default=0};
	__property ColorSource = {default=0};
	__property Cursor = {default=0};
	__property Depth = {default=-1};
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Stacked = {default=0};
	__property Title = {default=0};
	__property ValueFormat = {default=0};
	__property VertAxis = {default=0};
	__property XLabelsSource = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property ClickableLine = {default=1};
	__property ClickTolerance = {default=0};
	__property Pointer;
	__property Transparency = {default=0};
	__property XValues;
	__property YValues;
	__property OnClickPointer;
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~TPointSeries() { }
	
};


enum DECLSPEC_DENUM TMultiArea : unsigned char { maNone, maStacked, maStacked100 };

class PASCALIMPLEMENTATION TAreaSeries : public TCustomSeries
{
	typedef TCustomSeries inherited;
	
private:
	double FOrigin;
	int FStackGroup;
	bool FUseOrigin;
	TMultiArea __fastcall GetMultiArea();
	void __fastcall SetMultiArea(TMultiArea Value);
	void __fastcall SetOrigin(const double Value);
	void __fastcall SetStackGroup(const int Value);
	void __fastcall SetUseOrigin(bool Value);
	
protected:
	virtual void __fastcall CalcZOrder();
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRectF &Rect);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	virtual bool __fastcall SameClassOrigin(Fmxtee::Engine::TChartSeries* ASeries);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	
public:
	__fastcall virtual TAreaSeries(System::Classes::TComponent* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual bool __fastcall DrawSeriesForward(int ValueIndex);
	virtual int __fastcall GetOriginPos(int ValueIndex);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	virtual void __fastcall ResetBrush();
	
__published:
	__property Active = {default=1};
	__property ColorEachLine = {default=1};
	__property ColorEachPoint = {default=0};
	__property ColorSource = {default=0};
	__property Cursor = {default=0};
	__property Depth = {default=-1};
	__property Gradient;
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Title = {default=0};
	__property ValueFormat = {default=0};
	__property VertAxis = {default=0};
	__property XLabelsSource = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property AreaBrush = {default=1};
	__property AreaChartBrush;
	__property AreaColor = {default=16777215};
	__property AreaLinesPen;
	__property ClickableLine = {default=1};
	__property ClickTolerance = {default=0};
	__property Dark3D = {default=1};
	__property DrawArea = {default=0};
	__property DrawStyle = {default=0};
	__property InflateMargins = {default=1};
	__property InvertedStairs = {default=0};
	__property LinePen;
	__property TMultiArea MultiArea = {read=GetMultiArea, write=SetMultiArea, default=0};
	__property Pointer;
	__property PointerBehind = {default=0};
	__property Stairs = {default=0};
	__property int StackGroup = {read=FStackGroup, write=SetStackGroup, default=0};
	__property Transparency = {default=0};
	__property TreatNulls = {default=0};
	__property bool UseYOrigin = {read=FUseOrigin, write=SetUseOrigin, default=0};
	__property XValues;
	__property double YOrigin = {read=FOrigin, write=SetOrigin};
	__property YValues;
	__property OnClickPointer;
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~TAreaSeries() { }
	
};


class PASCALIMPLEMENTATION THorizAreaSeries : public TAreaSeries
{
	typedef TAreaSeries inherited;
	
protected:
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	
public:
	__fastcall virtual THorizAreaSeries(System::Classes::TComponent* AOwner);
	DYNAMIC int __fastcall NumSampleValues();
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~THorizAreaSeries() { }
	
};


enum DECLSPEC_DENUM TMultiBar : unsigned char { mbNone, mbSide, mbStacked, mbStacked100, mbSideAll, mbSelfStack };

enum DECLSPEC_DENUM TBarStyle : unsigned char { bsRectangle, bsPyramid, bsInvPyramid, bsCilinder, bsEllipse, bsArrow, bsRectGradient, bsCone, bsBevel, bsSlantCube, bsDiamond, bsInvArrow, bsInvCone, bsCustom, bsRoundRectangle };

enum DECLSPEC_DENUM TBarRound : unsigned char { brNone, brAtValue, brBothEnds };

typedef void __fastcall (__closure *TGetBarBoundsEvent)(TCustomBarSeries* Sender, int ValueIndex, System::Types::TRectF &Rect);

typedef void __fastcall (__closure *TGetBarStyleEvent)(TCustomBarSeries* Sender, int ValueIndex, TBarStyle &TheBarStyle);

enum DECLSPEC_DENUM TMarksLocation : unsigned char { mlStart, mlCenter, mlEnd };

class PASCALIMPLEMENTATION TCustomBarSeries : public Fmxtee::Engine::TChartSeries
{
	typedef Fmxtee::Engine::TChartSeries inherited;
	
private:
	bool FAutoBarSize;
	TBarRound FBarRound;
	TBarStyle FBarStyle;
	int FBarWidthPercent;
	int FBevelSize;
	int FConePercent;
	bool FDark3D;
	int FDarkPen;
	int FDepthPercent;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	bool FGradientRelative;
	TMarksLocation FMarksLocation;
	bool FMarksOnBar;
	TMultiBar FMultiBar;
	int FOffsetPercent;
	double FOrigin;
	int FRoundSize;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	bool FSideMargins;
	int FSides;
	int FStackGroup;
	Fmxtee::Canvas::TTeeHiddenPen* FTickLines;
	bool FUseOrigin;
	TGetBarStyleEvent FOnGetBarStyle;
	System::Types::TRectF FBarBounds;
	int INumBars;
	int IMaxBarPoints;
	int IOrderPos;
	int IPreviousCount;
	Fmxtee::Canvas::TTeeBlend* __fastcall CreateBlend(int Transp);
	void __fastcall DrawBevel();
	bool __fastcall GetAutoMarkPosition();
	Fmxtee::Canvas::TTeeBrush* __fastcall GetBarBrush();
	Fmxtee::Canvas::TTeePen* __fastcall GetBarPen();
	TBarStyle __fastcall GetBarStyle(int ValueIndex);
	Fmxtee::Canvas::TTeeGradient* __fastcall GetGradient();
	Fmxtee::Canvas::TTeeHiddenPen* __fastcall GetTickLines();
	bool __fastcall PointInCube(const System::Types::TPointF &P, const System::Types::TRectF &R, int Z1, int Z2);
	bool __fastcall PointInDiamond(const System::Types::TPointF &P, int X1, int Y1, int X2, int Y2);
	void __fastcall PrepareBarPen(int ValueIndex);
	void __fastcall SetAutoBarSize(bool Value);
	void __fastcall SetAutoMarkPosition(bool Value);
	void __fastcall SetBarWidthPercent(int Value);
	void __fastcall SetOffsetPercent(int Value);
	void __fastcall SetBarRound(TBarRound Value);
	void __fastcall SetBarStyle(TBarStyle Value);
	void __fastcall SetBevelSize(const int Value);
	void __fastcall SetConePercent(const int Value);
	void __fastcall SetDark3D(bool Value);
	void __fastcall SetDarkPen(int Value);
	void __fastcall SetDepthPercent(int Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetGradientRelative(const bool Value);
	void __fastcall SetMarksOnBar(bool Value);
	void __fastcall SetMarksLocation(const TMarksLocation Value);
	void __fastcall SetMultiBar(TMultiBar Value);
	void __fastcall SetOrigin(const double Value);
	void __fastcall SetOtherBars(bool SetOthers);
	void __fastcall SetRoundSize(int Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetSideMargins(bool Value);
	void __fastcall SetSides(const int Value);
	void __fastcall SetStackGroup(int Value);
	void __fastcall SetTickLines(Fmxtee::Canvas::TTeeHiddenPen* const Value);
	void __fastcall SetUseOrigin(bool Value);
	bool __fastcall CalcBarGradient(int ValueIndex);
	void __fastcall CalcBarWidth();
	void __fastcall InternalApplyBarMargin(int &MarginA, int &MarginB);
	int __fastcall InternalGetOriginPos(int ValueIndex, int DefaultOrigin);
	double __fastcall MaxMandatoryValue(const double Value);
	double __fastcall MinMandatoryValue(const double Value);
	Fmxtee::Engine::TChartAxis* __fastcall NotMandatoryAxis();
	void __fastcall SwapGradientColors();
	
protected:
	int IBarSize;
	int FCustomBarSize;
	TGetBarBoundsEvent FOnCalcBounds;
	DYNAMIC void __fastcall AddSampleValues(int NumValues, bool Sequential = false);
	virtual void __fastcall AssignFormatting(Fmxtee::Engine::TChartSeries* Series);
	virtual void __fastcall CalcDepthPositions();
	virtual void __fastcall CalcZOrder();
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DoBeforeDrawChart();
	virtual void __fastcall DoBeforeDrawValues();
	void __fastcall DrawCylinderTicks(int TickPos);
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRectF &Rect);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	virtual bool __fastcall DrawSeriesAscending();
	DYNAMIC void __fastcall DrawTickLine(int TickPos, TBarStyle AStyle);
	void __fastcall DrawTickLines(int StartPos, int EndPos, TBarStyle AStyle);
	virtual void __fastcall DrawValue(int ValueIndex);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual int __fastcall InternalCalcMarkLength(int ValueIndex);
	virtual bool __fastcall InternalClicked(int ValueIndex, const System::Types::TPointF &P);
	virtual bool __fastcall MoreSameZOrder();
	DYNAMIC void __fastcall PrepareForGallery();
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	void __fastcall SetCustomBarSize(int Value);
	virtual void __fastcall SetParentChart(Fmxtee::Engine::TCustomAxisPanel* const Value);
	virtual void __fastcall SetPen(Fmxtee::Canvas::TTeePen* const Value);
	virtual Fmxtee::Engine::TIntArray __fastcall SortDrawPoints(int FirstPoint, int LastPoint, bool SingleSeries);
	virtual Fmxtee::Engine::TIntArray __fastcall SortDrawSeries(int FirstSeries, int LastSeries, int ValueIndex);
	virtual bool __fastcall IsPointInChartRect(int ValueIndex);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	__classmethod virtual bool __fastcall SubGalleryStack();
	
public:
	System::Uitypes::TAlphaColor NormalBarColor;
	__fastcall virtual TCustomBarSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBarSeries();
	int __fastcall AddBar(const double AValue, const System::UnicodeString ALabel, System::Uitypes::TAlphaColor AColor);
	int __fastcall ApplyBarOffset(int Position);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall BarMargin();
	void __fastcall BarRectangle(System::Uitypes::TAlphaColor BarColor, int ALeft, int ATop, int ARight, int ABottom, bool Rounded = false)/* overload */;
	void __fastcall BarRectangle(System::Uitypes::TAlphaColor BarColor, const System::Types::TRectF &R, bool Rounded = false)/* overload */;
	virtual System::Types::TRectF __fastcall CalcBarBounds(int ValueIndex) = 0 ;
	int __fastcall CalcMarkLength(int ValueIndex);
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	virtual void __fastcall DrawBar(int BarIndex, int StartPos, int EndPos) = 0 ;
	virtual bool __fastcall DrawValuesForward();
	DYNAMIC int __fastcall NumSampleValues();
	virtual double __fastcall PointOrigin(int ValueIndex, bool SumAll);
	void __fastcall SetPenBrushBar(System::Uitypes::TAlphaColor BarColor, int ValueIndex = 0xffffffff);
	virtual void __fastcall CalcFirstLastVisibleIndex();
	__property System::Types::TRectF BarBounds = {read=FBarBounds};
	
__published:
	__property Active = {default=1};
	__property Fmxtee::Canvas::TTeeBrush* BarBrush = {read=GetBarBrush, write=SetBrush};
	__property Fmxtee::Canvas::TTeePen* BarPen = {read=GetBarPen, write=SetPen};
	__property int BevelSize = {read=FBevelSize, write=SetBevelSize, default=1};
	__property ColorEachPoint = {default=0};
	__property ColorSource = {default=0};
	__property int ConePercent = {read=FConePercent, write=SetConePercent, default=0};
	__property Cursor = {default=0};
	__property int DarkPen = {read=FDarkPen, write=SetDarkPen, default=0};
	__property Depth = {default=-1};
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property int RoundSize = {read=FRoundSize, write=SetRoundSize, default=16};
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Title = {default=0};
	__property Transparency = {default=0};
	__property ValueFormat = {default=0};
	__property VertAxis = {default=0};
	__property XLabelsSource = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property bool AutoBarSize = {read=FAutoBarSize, write=SetAutoBarSize, default=0};
	__property bool AutoMarkPosition = {read=GetAutoMarkPosition, write=SetAutoMarkPosition, stored=false, nodefault};
	__property TBarRound BarRound = {read=FBarRound, write=SetBarRound, default=1};
	__property TBarStyle BarStyle = {read=FBarStyle, write=SetBarStyle, default=0};
	__property int BarWidthPercent = {read=FBarWidthPercent, write=SetBarWidthPercent, default=70};
	__property bool Dark3D = {read=FDark3D, write=SetDark3D, default=1};
	__property int DepthPercent = {read=FDepthPercent, write=SetDepthPercent, default=100};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=GetGradient, write=SetGradient};
	__property bool GradientRelative = {read=FGradientRelative, write=SetGradientRelative, default=0};
	__property TMarksLocation MarksLocation = {read=FMarksLocation, write=SetMarksLocation, default=2};
	__property bool MarksOnBar = {read=FMarksOnBar, write=SetMarksOnBar, default=0};
	__property TMultiBar MultiBar = {read=FMultiBar, write=SetMultiBar, default=1};
	__property int OffsetPercent = {read=FOffsetPercent, write=SetOffsetPercent, default=0};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property bool SideMargins = {read=FSideMargins, write=SetSideMargins, default=1};
	__property int Sides = {read=FSides, write=SetSides, default=32};
	__property int StackGroup = {read=FStackGroup, write=SetStackGroup, default=0};
	__property Fmxtee::Canvas::TTeeHiddenPen* TickLines = {read=GetTickLines, write=SetTickLines};
	__property bool UseYOrigin = {read=FUseOrigin, write=SetUseOrigin, default=1};
	__property double YOrigin = {read=FOrigin, write=SetOrigin};
	__property XValues;
	__property YValues;
	__property TGetBarStyleEvent OnGetBarStyle = {read=FOnGetBarStyle, write=FOnGetBarStyle};
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Fmxtee::Engine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPointF &P){ return Fmxtee::Engine::TChartSeries::Clicked(P); }
	
};


class PASCALIMPLEMENTATION TBarSeries : public TCustomBarSeries
{
	typedef TCustomBarSeries inherited;
	
protected:
	virtual void __fastcall CalcHorizMargins(int &LeftMargin, int &RightMargin);
	virtual void __fastcall CalcSelectionPos(int ValueIndex, /* out */ int &X, /* out */ int &Y);
	virtual void __fastcall CalcVerticalMargins(int &TopMargin, int &BottomMargin);
	DYNAMIC void __fastcall DrawTickLine(int TickPos, TBarStyle AStyle);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	virtual int __fastcall InternalCalcMarkLength(int ValueIndex);
	virtual bool __fastcall InternalClicked(int ValueIndex, const System::Types::TPointF &P);
	
public:
	__fastcall virtual TBarSeries(System::Classes::TComponent* AOwner);
	virtual System::Types::TRectF __fastcall CalcBarBounds(int ValueIndex);
	virtual int __fastcall CalcXPos(int ValueIndex);
	virtual int __fastcall CalcYPos(int ValueIndex);
	virtual void __fastcall DrawBar(int BarIndex, int StartPos, int EndPos);
	virtual bool __fastcall DrawSeriesForward(int ValueIndex);
	int __fastcall GetOriginPos(int ValueIndex);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	__property int BarWidth = {read=IBarSize, nodefault};
	
__published:
	__property int CustomBarWidth = {read=FCustomBarSize, write=SetCustomBarSize, default=0};
public:
	/* TCustomBarSeries.Destroy */ inline __fastcall virtual ~TBarSeries() { }
	
};


class PASCALIMPLEMENTATION THorizBarSeries : public TCustomBarSeries
{
	typedef TCustomBarSeries inherited;
	
protected:
	virtual void __fastcall CalcHorizMargins(int &LeftMargin, int &RightMargin);
	virtual void __fastcall CalcSelectionPos(int ValueIndex, /* out */ int &X, /* out */ int &Y);
	virtual void __fastcall CalcVerticalMargins(int &TopMargin, int &BottomMargin);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	virtual bool __fastcall DrawSeriesAscending();
	DYNAMIC void __fastcall DrawTickLine(int TickPos, TBarStyle AStyle);
	virtual int __fastcall InternalCalcMarkLength(int ValueIndex);
	virtual bool __fastcall InternalClicked(int ValueIndex, const System::Types::TPointF &P);
	virtual bool __fastcall InvertedLegend();
	
public:
	__fastcall virtual THorizBarSeries(System::Classes::TComponent* AOwner);
	virtual System::Types::TRectF __fastcall CalcBarBounds(int ValueIndex);
	virtual int __fastcall CalcXPos(int ValueIndex);
	virtual int __fastcall CalcYPos(int ValueIndex);
	virtual void __fastcall DrawBar(int BarIndex, int StartPos, int EndPos);
	virtual bool __fastcall DrawSeriesForward(int ValueIndex);
	virtual bool __fastcall DrawValuesForward();
	int __fastcall GetOriginPos(int ValueIndex);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	__property int BarHeight = {read=IBarSize, nodefault};
	
__published:
	__property int CustomBarHeight = {read=FCustomBarSize, write=SetCustomBarSize, default=0};
public:
	/* TCustomBarSeries.Destroy */ inline __fastcall virtual ~THorizBarSeries() { }
	
};


class PASCALIMPLEMENTATION TFrameBrush : public Fmxtee::Canvas::TTeeBrush
{
	typedef Fmxtee::Canvas::TTeeBrush inherited;
	
private:
	float FSize;
	float IDefault;
	bool __fastcall IsSizeStored();
	void __fastcall InitSize(const float ASize);
	void __fastcall SetSize(const float Value);
	
__published:
	__property float Size = {read=FSize, write=SetSize, stored=IsSizeStored};
public:
	/* TTeeBrush.Create */ inline __fastcall virtual TFrameBrush(const System::Classes::TNotifyEvent OnChangeEvent) : Fmxtee::Canvas::TTeeBrush(OnChangeEvent) { }
	/* TTeeBrush.Destroy */ inline __fastcall virtual ~TFrameBrush() { }
	
};


class PASCALIMPLEMENTATION TFramedBorder : public Fmxtee::Procs::TTeeCustomShapeBrushPen
{
	typedef Fmxtee::Procs::TTeeCustomShapeBrushPen inherited;
	
private:
	bool FCircled;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	TFrameBrush* FInner;
	TFrameBrush* FMiddle;
	TFrameBrush* FOuter;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	int FWidth;
	void __fastcall GetPalette();
	bool __fastcall IsCircledStored();
	HIDESBASE bool __fastcall IsVisibleStored();
	void __fastcall ReadParentSeries(System::Classes::TReader* Reader);
	void __fastcall SetCircled(const bool Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetInner(TFrameBrush* const Value);
	void __fastcall SetMiddle(TFrameBrush* const Value);
	void __fastcall SetOuter(TFrameBrush* const Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetWidth(const int Value);
	
protected:
	bool INoBrush;
	bool DefaultCircled;
	bool DefaultVisible;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TFramedBorder()/* overload */;
	__fastcall virtual ~TFramedBorder();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	float __fastcall CalcWidth(const System::Types::TRectF &R);
	virtual void __fastcall Draw(const System::Types::TRectF &R);
	void __fastcall SetDefaultCircled(const bool Value);
	
__published:
	__property Brush;
	__property bool Circled = {read=FCircled, write=SetCircled, stored=IsCircledStored, nodefault};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property TFrameBrush* InnerBrush = {read=FInner, write=SetInner};
	__property TFrameBrush* MiddleBrush = {read=FMiddle, write=SetMiddle};
	__property TFrameBrush* OuterBrush = {read=FOuter, write=SetOuter};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property Visible = {stored=IsVisibleStored};
	__property int Width = {read=FWidth, write=SetWidth, default=10};
};


class PASCALIMPLEMENTATION TCircularFrame : public TFramedBorder
{
	typedef TFramedBorder inherited;
	
private:
	int FRotationAngle;
	int FTotalAngle;
	void __fastcall SetRotationAngle(const int Value);
	void __fastcall SetTotalAngle(const int Value);
	
public:
	System::StaticArray<double, 3> FrameElementWidths;
	__fastcall virtual TCircularFrame()/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Draw(const System::Types::TRectF &R);
	
__published:
	__property int RotationAngle = {read=FRotationAngle, write=SetRotationAngle, default=0};
	__property int TotalAngle = {read=FTotalAngle, write=SetTotalAngle, default=360};
public:
	/* TFramedBorder.Destroy */ inline __fastcall virtual ~TCircularFrame() { }
	
};


class PASCALIMPLEMENTATION TCircledSeries : public Fmxtee::Engine::TChartSeries
{
	typedef Fmxtee::Engine::TChartSeries inherited;
	
private:
	Fmxtee::Canvas::TTeeBrush* FCircleBrush;
	bool FCircled;
	int FCustomXRadius;
	int FCustomYRadius;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	TFramedBorder* FFrame;
	int FRotationAngle;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	bool FUniqueCustomRadius;
	int FXRadius;
	int FYRadius;
	Fmxtee::Canvas::TView3DOptions* IBack3D;
	int FCircleWidth;
	int FCircleHeight;
	int FCircleXCenter;
	int FCircleYCenter;
	System::Types::TRectF FCircleRect;
	System::Uitypes::TAlphaColor __fastcall GetCircleBackColor();
	TFramedBorder* __fastcall GetFrame();
	bool __fastcall HasFrame();
	void __fastcall SetBackupProperties();
	void __fastcall SetCircleBackColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetCircleBrush(Fmxtee::Canvas::TTeeBrush* const Value);
	void __fastcall SetCircled(bool Value);
	void __fastcall SetCustomXRadius(int Value);
	void __fastcall SetCustomYRadius(int Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetFrame(TFramedBorder* const Value);
	void __fastcall SetOtherCustomRadius(bool IsXRadius, int Value);
	void __fastcall SetUniqueCustomRadius(bool Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	
protected:
	double IRotDegree;
	bool IAdjustCircleForMarks;
	void __fastcall AdjustCircleRect();
	virtual void __fastcall AssignFormatting(Fmxtee::Engine::TChartSeries* Source);
	System::Uitypes::TAlphaColor __fastcall CalcCircleBackColor();
	virtual void __fastcall CalcRadius();
	DYNAMIC void __fastcall CheckOtherSeriesMarks();
	virtual void __fastcall DoBeforeDrawValues();
	void __fastcall DrawCircleShadow();
	void __fastcall DrawFrame();
	Fmxtee::Canvas::TTeeGradient* __fastcall GetCircleGradient();
	DYNAMIC void __fastcall InitCustom3DOptions();
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	virtual void __fastcall SetActive(bool Value);
	void __fastcall SetCircleGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetCircleRect(const System::Types::TRectF &ARect);
	virtual void __fastcall SetParentChart(Fmxtee::Engine::TCustomAxisPanel* const Value);
	DYNAMIC void __fastcall SetParentProperties(bool EnableParentProps);
	void __fastcall SetRotationAngle(const int Value);
	virtual bool __fastcall IsPointInChartRect(int ValueIndex);
	__property Fmxtee::Canvas::TTeeGradient* CircleGradient = {read=GetCircleGradient, write=SetCircleGradient};
	
public:
	__fastcall virtual TCircledSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCircledSeries();
	__classmethod void __fastcall AdjustScreenRatio(Fmxtee::Canvas::TCanvas3D* const ACanvas, int AXRadius, int AYRadius, System::Types::TRectF &R);
	void __fastcall AngleToPos(const double Angle, const double AXRadius, const double AYRadius, /* out */ int &X, /* out */ int &Y)/* overload */;
	void __fastcall AngleToPos(const double Angle, const double AXRadius, const double AYRadius, /* out */ float &X, /* out */ float &Y)/* overload */;
	virtual bool __fastcall AssociatedToAxis(Fmxtee::Engine::TChartAxis* const Axis);
	double __fastcall PointToAngle(int x, int y);
	double __fastcall PointToRadius(int x, int y);
	void __fastcall Rotate(const int Angle);
	virtual bool __fastcall UseAxis();
	__property System::Uitypes::TAlphaColor CircleBackColor = {read=GetCircleBackColor, write=SetCircleBackColor, default=16777215};
	__property Fmxtee::Canvas::TTeeBrush* CircleBrush = {read=FCircleBrush, write=SetCircleBrush};
	__property int CircleHeight = {read=FCircleHeight, nodefault};
	__property System::Types::TRectF CircleRect = {read=FCircleRect, write=SetCircleRect};
	__property int CircleWidth = {read=FCircleWidth, nodefault};
	__property int CircleXCenter = {read=FCircleXCenter, nodefault};
	__property int CircleYCenter = {read=FCircleYCenter, nodefault};
	__property int RotationAngle = {read=FRotationAngle, write=SetRotationAngle, default=0};
	__property int XRadius = {read=FXRadius, nodefault};
	__property int YRadius = {read=FYRadius, nodefault};
	
__published:
	__property ColorSource = {default=0};
	__property Cursor = {default=0};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Title = {default=0};
	__property ValueFormat = {default=0};
	__property XLabelsSource = {default=0};
	__property XValues;
	__property YValues;
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property bool Circled = {read=FCircled, write=SetCircled, default=1};
	__property int CustomXRadius = {read=FCustomXRadius, write=SetCustomXRadius, default=0};
	__property int CustomYRadius = {read=FCustomYRadius, write=SetCustomYRadius, default=0};
	__property TFramedBorder* Frame = {read=GetFrame, write=SetFrame, stored=HasFrame};
	__property bool UniqueCustomRadius = {read=FUniqueCustomRadius, write=SetUniqueCustomRadius, default=1};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
};


class PASCALIMPLEMENTATION TSliceValueList : public System::Generics::Collections::TList__1<int>
{
	typedef System::Generics::Collections::TList__1<int> inherited;
	
public:
	int operator[](int Index) { return this->Value[Index]; }
	
private:
	int __fastcall Get(int Index);
	void __fastcall Put(int Index, int Value);
	
protected:
	Fmxtee::Engine::TChartSeries* OwnerSeries;
	
public:
	void __fastcall Assign(TSliceValueList* const Source);
	__property int Value[int Index] = {read=Get, write=Put/*, default*/};
public:
	/* {System_Generics_Collections}TList<System_Integer>.Create */ inline __fastcall TSliceValueList()/* overload */ : System::Generics::Collections::TList__1<int>() { }
	/* {System_Generics_Collections}TList<System_Integer>.Create */ inline __fastcall TSliceValueList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<int> > AComparer)/* overload */ : System::Generics::Collections::TList__1<int>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Integer>.Create */ inline __fastcall TSliceValueList(System::Generics::Collections::TEnumerable__1<int>* const Collection)/* overload */ : System::Generics::Collections::TList__1<int>(Collection) { }
	/* {System_Generics_Collections}TList<System_Integer>.Destroy */ inline __fastcall virtual ~TSliceValueList() { }
	
};


enum DECLSPEC_DENUM TPieOtherStyle : unsigned char { poNone, poBelowPercent, poBelowValue };

class PASCALIMPLEMENTATION TPieOtherSlice : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	Fmxtee::Chart::TChartLegend* FLegend;
	TPieOtherStyle FStyle;
	System::UnicodeString FText;
	double FValue;
	Fmxtee::Engine::TChartSeries* FOwner;
	Fmxtee::Chart::TChartLegend* __fastcall GetLegend();
	System::UnicodeString __fastcall GetText();
	bool __fastcall IsTextStored();
	void __fastcall SetColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetLegend(Fmxtee::Chart::TChartLegend* const Value);
	void __fastcall SetStyle(TPieOtherStyle Value);
	void __fastcall SetText(const System::UnicodeString Value);
	void __fastcall SetValue(const double Value);
	
public:
	__fastcall TPieOtherSlice(Fmxtee::Engine::TChartSeries* const AOwner);
	__fastcall virtual ~TPieOtherSlice();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, default=16777215};
	__property Fmxtee::Chart::TChartLegend* Legend = {read=GetLegend, write=SetLegend};
	__property TPieOtherStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property System::UnicodeString Text = {read=GetText, write=SetText, stored=IsTextStored};
	__property double Value = {read=FValue, write=SetValue};
};


class PASCALIMPLEMENTATION TPieMarks : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FEmptySlice;
	bool FInsideSlice;
	int FLegSize;
	bool FRotated;
	bool FVertCenter;
	Fmxtee::Engine::TChartSeries* IParent;
	void __fastcall SetEmptySlice(const bool Value);
	void __fastcall SetInsideSlice(const bool Value);
	void __fastcall SetLegSize(const int Value);
	void __fastcall SetRotated(const bool Value);
	void __fastcall SetVertCenter(const bool Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool EmptySlice = {read=FEmptySlice, write=SetEmptySlice, default=0};
	__property bool InsideSlice = {read=FInsideSlice, write=SetInsideSlice, default=0};
	__property int LegSize = {read=FLegSize, write=SetLegSize, default=0};
	__property bool Rotated = {read=FRotated, write=SetRotated, default=0};
	__property bool VertCenter = {read=FVertCenter, write=SetVertCenter, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPieMarks() { }
	
public:
	/* TObject.Create */ inline __fastcall TPieMarks() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TPieBevel : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FBright;
	int FPercent;
	bool FUseBorder;
	Fmxtee::Engine::TChartSeries* ISeries;
	void __fastcall SetBright(const int Value);
	void __fastcall SetPercent(const int Value);
	void __fastcall SetUseBorder(const bool Value);
	
public:
	__fastcall TPieBevel(Fmxtee::Engine::TChartSeries* const AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property int Bright = {read=FBright, write=SetBright, default=32};
	__property int Percent = {read=FPercent, write=SetPercent, default=0};
	__property bool UseBorder = {read=FUseBorder, write=SetUseBorder, default=1};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPieBevel() { }
	
};


enum DECLSPEC_DENUM TMultiPie : unsigned char { mpAutomatic, mpDisabled, mpConcentric };

class PASCALIMPLEMENTATION TPieSeries : public TCircledSeries
{
	typedef TCircledSeries inherited;
	
private:
	int FAngleSize;
	TPieBevel* FBevel;
	System::Types::TRectF FCustomBounds;
	bool FDark3D;
	int FDarkPen;
	int FDonutPercent;
	Fmxtee::Canvas::TEdgeStyle FEdgeStyle;
	TSliceValueList* FExplodedSlice;
	int FExplodeBiggest;
	int FGradientBright;
	TMultiPie FMultiPie;
	TPieOtherSlice* FOtherSlice;
	TPieMarks* FPieMarks;
	TSliceValueList* FSliceHeights;
	bool FUsePatterns;
	Fmxtee::Engine::TIntArray ISortedSlice;
	System::Types::TRectF IOldChartRect;
	int IOldDonut;
	bool IHideSides;
	void __fastcall CalcExplodeBiggest();
	System::Uitypes::TAlphaColor __fastcall ChangeColor(const System::Uitypes::TAlphaColor AColor, int ABright);
	int __fastcall CompareSlice(int A, int B);
	void __fastcall DisableRotation();
	bool __fastcall GetAutoMarkPosition();
	int __fastcall GetBevelPercent();
	Fmxtee::Canvas::TTeePen* __fastcall GetPiePen();
	Fmxtee::Engine::TChartValueList* __fastcall GetPieValues();
	int __fastcall PieCount();
	void __fastcall PreparePiePen(int ValueIndex);
	void __fastcall RemoveOtherSlice();
	void __fastcall SetAngleSize(int Value);
	void __fastcall SetAutoMarkPosition(bool Value);
	void __fastcall SetBevel(TPieBevel* const Value);
	void __fastcall SetBevelPercent(int Value);
	void __fastcall SetDark3D(bool Value);
	void __fastcall SetDarkPen(const int Value);
	void __fastcall SetEdgeStyle(Fmxtee::Canvas::TEdgeStyle Value);
	void __fastcall SetExplodeBiggest(int Value);
	void __fastcall SetGradientBright(int Value);
	void __fastcall SetGradientColor(Fmxtee::Canvas::TTeeGradient* const AGradient, System::Uitypes::TAlphaColor AColor);
	void __fastcall SetMultiPie(const TMultiPie Value);
	void __fastcall SetOtherSlice(TPieOtherSlice* Value);
	void __fastcall SetPieMarks(TPieMarks* const Value);
	void __fastcall SetPieValues(Fmxtee::Engine::TChartValueList* const Value);
	void __fastcall SetUsePatterns(bool Value);
	Fmx::Graphics::TBrushKind __fastcall SliceBrushStyle(int ValueIndex);
	int __fastcall SliceEndZ(int ValueIndex);
	void __fastcall SwapSlice(int a, int b);
	
protected:
	TPieAngles FAngles;
	bool IsExploded;
	DYNAMIC void __fastcall AddSampleValues(int NumValues, bool Sequential = false);
	virtual void __fastcall AssignFormatting(Fmxtee::Engine::TChartSeries* Source);
	void __fastcall CalcAngles();
	void __fastcall CalcExplodedOffset(int ValueIndex, /* out */ int &OffsetX, /* out */ int &OffsetY);
	void __fastcall CalcExplodedRadius(int ValueIndex, /* out */ int &AXRadius, /* out */ int &AYRadius);
	virtual void __fastcall CalcSelectionPos(int ValueIndex, /* out */ int &X, /* out */ int &Y);
	virtual void __fastcall CalcZOrder();
	void __fastcall CheckAngles();
	DYNAMIC void __fastcall CheckOtherSeriesMarks();
	virtual void __fastcall ClearLists();
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DoAfterDrawValues();
	virtual void __fastcall DoBeforeDrawChart();
	virtual void __fastcall DoBeforeDrawValues();
	virtual void __fastcall DrawAllValues();
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRectF &Rect);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	virtual void __fastcall DrawPie(int ValueIndex);
	virtual void __fastcall DrawValue(int ValueIndex);
	DYNAMIC void __fastcall GalleryChanged3D(bool Is3D);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	DYNAMIC void __fastcall InitCustom3DOptions();
	virtual bool __fastcall MoreSameZOrder();
	DYNAMIC void __fastcall PrepareForGallery();
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	void __fastcall SetDonutPercent(int Value);
	virtual void __fastcall SetParentChart(Fmxtee::Engine::TCustomAxisPanel* const Value);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	DYNAMIC void __fastcall WriteData(System::Classes::TStream* Stream);
	
public:
	__fastcall virtual TPieSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPieSeries();
	int __fastcall AddPie(const double AValue, const System::UnicodeString ALabel = System::UnicodeString(), System::Uitypes::TAlphaColor AColor = (System::Uitypes::TAlphaColor)(0xffffff));
	bool __fastcall BelongsToOtherSlice(int ValueIndex);
	int __fastcall CalcClickedPie(int x, int y, bool Exploded = true);
	virtual void __fastcall CalcFirstLastVisibleIndex();
	virtual int __fastcall CalcXPos(int ValueIndex);
	DYNAMIC void __fastcall CheckOrder();
	virtual void __fastcall Clear();
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	virtual int __fastcall CountLegendItems();
	virtual void __fastcall Delete(int ValueIndex)/* overload */;
	virtual int __fastcall LegendToValueIndex(int LegendIndex);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	DYNAMIC int __fastcall NumSampleValues();
	DYNAMIC void __fastcall SwapValueIndex(int a, int b);
	__property TPieAngles Angles = {read=FAngles};
	__property int DonutPercent = {read=FDonutPercent, write=SetDonutPercent, nodefault};
	__property TSliceValueList* ExplodedSlice = {read=FExplodedSlice};
	__property TSliceValueList* SliceHeight = {read=FSliceHeights};
	
__published:
	__property Active = {default=1};
	__property int AngleSize = {read=FAngleSize, write=SetAngleSize, default=360};
	__property bool AutoMarkPosition = {read=GetAutoMarkPosition, write=SetAutoMarkPosition, stored=false, nodefault};
	__property TPieBevel* Bevel = {read=FBevel, write=SetBevel};
	__property int BevelPercent = {read=GetBevelPercent, write=SetBevelPercent, default=0};
	__property CircleBackColor = {default=16777215};
	__property ColorEachPoint = {default=1};
	__property bool Dark3D = {read=FDark3D, write=SetDark3D, default=1};
	__property int DarkPen = {read=FDarkPen, write=SetDarkPen, default=0};
	__property Fmxtee::Canvas::TEdgeStyle EdgeStyle = {read=FEdgeStyle, write=SetEdgeStyle, default=2};
	__property int ExplodeBiggest = {read=FExplodeBiggest, write=SetExplodeBiggest, default=0};
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=GetCircleGradient, write=SetCircleGradient};
	__property int GradientBright = {read=FGradientBright, write=SetGradientBright, default=0};
	__property TMultiPie MultiPie = {read=FMultiPie, write=SetMultiPie, default=0};
	__property TPieOtherSlice* OtherSlice = {read=FOtherSlice, write=SetOtherSlice};
	__property TPieMarks* PieMarks = {read=FPieMarks, write=SetPieMarks};
	__property Fmxtee::Canvas::TTeePen* PiePen = {read=GetPiePen, write=SetPen};
	__property Fmxtee::Engine::TChartValueList* PieValues = {read=GetPieValues, write=SetPieValues, stored=false};
	__property RotationAngle = {default=0};
	__property Transparency = {default=0};
	__property bool UsePatterns = {read=FUsePatterns, write=SetUsePatterns, default=0};
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Fmxtee::Engine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPointF &P){ return Fmxtee::Engine::TChartSeries::Clicked(P); }
	inline void __fastcall  Delete(int Start, int Quantity, bool RemoveGap = false){ Fmxtee::Engine::TChartSeries::Delete(Start, Quantity, RemoveGap); }
	
};


enum DECLSPEC_DENUM TDrawAllPointsStyle : unsigned char { daFirst, daMinMax };

enum DECLSPEC_DENUM TFastLineDrawStyle : unsigned char { flSegments, flAll };

class PASCALIMPLEMENTATION TFastLineSeries : public TCustomLineSeries
{
	typedef TCustomLineSeries inherited;
	
private:
	bool FAutoRepaint;
	int FClickTolerance;
	TDrawAllPointsStyle FDAPStyle;
	bool FDrawAll;
	TFastLineDrawStyle FDrawStyle;
	bool FFastPen;
	bool FIgnoreNulls;
	bool FInvertedStairs;
	bool FStairs;
	bool IFastPenInit;
	int OldX;
	int OldY;
	int IMin;
	int IMax;
	bool ISameX;
	Fmxtee::Canvas::TPointArray IPoints;
	void __fastcall DoMove(const int X, const int Y);
	void __fastcall SetDAPStyle(const TDrawAllPointsStyle Value);
	void __fastcall SetDrawAll(const bool Value);
	void __fastcall SetDrawStyle(const TFastLineDrawStyle Value);
	void __fastcall SetFastPen(const bool Value);
	void __fastcall SetIgnoreNulls(const bool Value);
	void __fastcall SetInvertedStairs(const bool Value);
	void __fastcall SetStairs(const bool Value);
	bool __fastcall ShouldDrawAsPolyline();
	
protected:
	bool ReuseXValues;
	bool ReuseYValues;
	virtual void __fastcall AssignFormatting(Fmxtee::Engine::TChartSeries* Source);
	virtual void __fastcall CalcHorizMargins(int &LeftMargin, int &RightMargin);
	void __fastcall CalcPosition(int ValueIndex, /* out */ int &x, /* out */ int &y);
	virtual void __fastcall CalcVerticalMargins(int &TopMargin, int &BottomMargin);
	virtual bool __fastcall CanBeforeParallel();
	__classmethod virtual void __fastcall CreateSubGallery(Fmxtee::Engine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DoBeforeParallel();
	virtual void __fastcall DrawAllValues();
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRectF &Rect);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Fmxtee::Engine::TSeriesMarkPosition* APosition);
	virtual void __fastcall DrawValue(int ValueIndex);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall NotifyNewValue(Fmxtee::Engine::TChartSeries* Sender, int ValueIndex);
	void __fastcall PrepareCanvas();
	virtual void __fastcall PrepareLegendCanvas(int ValueIndex, System::Uitypes::TAlphaColor &BackColor, Fmx::Graphics::TBrushKind &BrushStyle);
	virtual void __fastcall SetPen(Fmxtee::Canvas::TTeePen* const Value);
	virtual void __fastcall SetSeriesColor(System::Uitypes::TAlphaColor AColor);
	__classmethod virtual void __fastcall SetSubGallery(Fmxtee::Engine::TChartSeries* ASeries, int Index);
	
public:
	__fastcall virtual TFastLineSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFastLineSeries();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CalcFirstLastVisibleIndex();
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	
__published:
	__property Active = {default=1};
	__property Cursor = {default=0};
	__property Depth = {default=-1};
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Title = {default=0};
	__property ValueFormat = {default=0};
	__property VertAxis = {default=0};
	__property XLabelsSource = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnAfterAdd;
	__property OnBeforeAdd;
	__property OnClearValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property bool AutoRepaint = {read=FAutoRepaint, write=FAutoRepaint, default=1};
	__property int ClickTolerance = {read=FClickTolerance, write=FClickTolerance, default=0};
	__property bool DrawAllPoints = {read=FDrawAll, write=SetDrawAll, default=1};
	__property TDrawAllPointsStyle DrawAllPointsStyle = {read=FDAPStyle, write=SetDAPStyle, default=0};
	__property TFastLineDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=0};
	__property bool FastPen = {read=FFastPen, write=SetFastPen, default=0};
	__property bool IgnoreNulls = {read=FIgnoreNulls, write=SetIgnoreNulls, default=1};
	__property bool InvertedStairs = {read=FInvertedStairs, write=SetInvertedStairs, default=0};
	__property LinePen;
	__property bool Stairs = {read=FStairs, write=SetStairs, default=0};
	__property TreatNulls = {default=2};
	__property XValues;
	__property YValues;
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Fmxtee::Engine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPointF &P){ return Fmxtee::Engine::TChartSeries::Clicked(P); }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Uitypes::TAlphaColor Tee_CircledShadowColor = System::Uitypes::TAlphaColor(0xa0a0a0);
static constexpr System::Uitypes::TAlphaColor Tee_CircledEmbossColor = System::Uitypes::TAlphaColor(0xa0a0a0);
static const TBarStyle bsCylinder = (TBarStyle)(3);
extern DELPHI_PACKAGE void __fastcall TeePointerDrawLegend(Fmxtee::Engine::TSeriesPointer* const Pointer, System::Uitypes::TAlphaColor AColor, const System::Types::TRectF &Rect, bool DrawPen, Fmxtee::Engine::TSeriesPointerStyle AStyle);
extern DELPHI_PACKAGE void __fastcall RegisterTeeStandardSeries(void);
}	/* namespace Series */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_SERIES)
using namespace Fmxtee::Series;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_SeriesHPP
