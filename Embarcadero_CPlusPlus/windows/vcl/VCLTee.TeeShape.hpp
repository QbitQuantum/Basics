// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeShape.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeshapeHPP
#define Vcltee_TeeshapeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeshape
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartShape;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TChartShapeXYStyle : unsigned char { xysPixels, xysAxis, xysAxisOrigin };

enum DECLSPEC_DENUM TChartShapeStyle : unsigned char { chasRectangle, chasCircle, chasVertLine, chasHorizLine, chasTriangle, chasInvertTriangle, chasLine, chasDiamond, chasCube, chasCross, chasDiagCross, chasStar, chasPyramid, chasInvertPyramid };

enum DECLSPEC_DENUM TTeeVertAlign : unsigned char { vaTop, vaCenter, vaBottom };

class PASCALIMPLEMENTATION TChartShape : public Vcltee::Teengine::TChartSeries
{
	typedef Vcltee::Teengine::TChartSeries inherited;
	
private:
	System::Classes::TAlignment FAlignment;
	Vcltee::Tecanvas::TTeeFont* FFont;
	bool FRoundRectangle;
	TChartShapeStyle FStyle;
	System::Classes::TStrings* FText;
	bool FTransparent;
	TTeeVertAlign FVertAlign;
	TChartShapeXYStyle FXYStyle;
	void __fastcall AddDefaultPoints();
	void __fastcall ChangeToManual();
	Vcltee::Tecanvas::TTeeGradient* __fastcall GetGradient();
	double __fastcall GetX0();
	double __fastcall GetX1();
	double __fastcall GetY0();
	double __fastcall GetY1();
	void __fastcall SetAlignment(System::Classes::TAlignment Value);
	void __fastcall SetFont(Vcltee::Tecanvas::TTeeFont* Value);
	void __fastcall SetGradient(Vcltee::Tecanvas::TTeeGradient* const Value);
	void __fastcall SetRoundRectangle(bool Value);
	void __fastcall SetShapeRectangle(const System::Types::TRect &ARect);
	void __fastcall SetStyle(TChartShapeStyle Value);
	void __fastcall SetTransparent(bool Value);
	void __fastcall SetVertAlign(TTeeVertAlign Value);
	void __fastcall SetX0(const double Value);
	void __fastcall SetX1(const double Value);
	void __fastcall SetXYStyle(TChartShapeXYStyle Value);
	void __fastcall SetY0(const double Value);
	void __fastcall SetY1(const double Value);
	
protected:
	DYNAMIC void __fastcall AddSampleValues(int NumValues, bool OnlyMandatory = false);
	virtual void __fastcall AssignFormatting(Vcltee::Teengine::TChartSeries* Source);
	virtual void __fastcall CalcZOrder();
	__classmethod virtual void __fastcall CreateSubGallery(Vcltee::Teengine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DrawLegendShape(int ValueIndex, const System::Types::TRect &Rect);
	void __fastcall DrawShape(int ValueIndex, bool Is3D, const System::Types::TRect &R);
	void __fastcall DrawText(const System::Types::TRect &R);
	virtual void __fastcall DrawValue(int ValueIndex);
	System::Types::TRect __fastcall GetAdjustedRectangle();
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual System::Types::TRect __fastcall GetShapeRectangle();
	virtual bool __fastcall MoreSameZOrder();
	DYNAMIC void __fastcall PrepareForGallery();
	virtual void __fastcall SetSeriesColor(System::Uitypes::TColor AColor);
	__classmethod virtual void __fastcall SetSubGallery(Vcltee::Teengine::TChartSeries* ASeries, int Index);
	virtual void __fastcall SetText(System::Classes::TStrings* Value);
	
public:
	__fastcall virtual TChartShape(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TChartShape();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	DYNAMIC bool __fastcall IsValidSourceOf(Vcltee::Teengine::TChartSeries* Value);
	virtual bool __fastcall UseAxis();
	__property System::Types::TRect Bounds = {read=GetShapeRectangle, write=SetShapeRectangle};
	
__published:
	__property Active = {default=1};
	__property Cursor = {default=0};
	__property Depth = {default=-1};
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property SeriesColor;
	__property ShowInLegend = {default=1};
	__property Title = {default=0};
	__property VertAxis = {default=0};
	__property AfterDrawValues;
	__property BeforeDrawValues;
	__property OnClick;
	__property OnDblClick;
	__property OnGetMarkText;
	__property System::Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property Brush;
	__property Vcltee::Tecanvas::TTeeFont* Font = {read=FFont, write=SetFont};
	__property Vcltee::Tecanvas::TTeeGradient* Gradient = {read=GetGradient, write=SetGradient};
	__property System::Classes::TStrings* Text = {read=FText, write=SetText};
	__property Pen;
	__property bool RoundRectangle = {read=FRoundRectangle, write=SetRoundRectangle, default=0};
	__property TChartShapeStyle Style = {read=FStyle, write=SetStyle, default=1};
	__property Transparency = {default=0};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, default=0};
	__property TTeeVertAlign VertAlign = {read=FVertAlign, write=SetVertAlign, default=1};
	__property TChartShapeXYStyle XYStyle = {read=FXYStyle, write=SetXYStyle, default=1};
	__property double X0 = {read=GetX0, write=SetX0};
	__property double X1 = {read=GetX1, write=SetX1};
	__property double Y0 = {read=GetY0, write=SetY0};
	__property double Y1 = {read=GetY1, write=SetY1};
	__property XValues;
	__property YValues;
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Vcltee::Teengine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPoint &P){ return Vcltee::Teengine::TChartSeries::Clicked(P); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeshape */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESHAPE)
using namespace Vcltee::Teeshape;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeshapeHPP
