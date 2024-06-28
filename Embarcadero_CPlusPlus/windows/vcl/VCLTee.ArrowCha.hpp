// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.ArrowCha.pas' rev: 34.00 (Windows)

#ifndef Vcltee_ArrowchaHPP
#define Vcltee_ArrowchaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Series.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Arrowcha
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TArrowSeries;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TArrowSeries : public Vcltee::Series::TPointSeries
{
	typedef Vcltee::Series::TPointSeries inherited;
	
private:
	Vcltee::Teengine::TChartValueList* FEndXValues;
	Vcltee::Teengine::TChartValueList* FEndYValues;
	bool FFill2D;
	int FPercent;
	int __fastcall GetArrowHeight();
	int __fastcall GetArrowWidth();
	void __fastcall GetArrowPoints(int ValueIndex, /* out */ System::Types::TPoint &P0, /* out */ System::Types::TPoint &P1);
	Vcltee::Teengine::TChartValueList* __fastcall GetStartXValues();
	Vcltee::Teengine::TChartValueList* __fastcall GetStartYValues();
	void __fastcall SetArrowHeight(int Value);
	void __fastcall SetArrowWidth(int Value);
	void __fastcall SetEndXValues(Vcltee::Teengine::TChartValueList* Value);
	void __fastcall SetEndYValues(Vcltee::Teengine::TChartValueList* Value);
	void __fastcall SetFill2D(bool Value);
	void __fastcall SetPercent(const int Value);
	void __fastcall SetStartXValues(Vcltee::Teengine::TChartValueList* Value);
	void __fastcall SetStartYValues(Vcltee::Teengine::TChartValueList* Value);
	
protected:
	DYNAMIC void __fastcall AddSampleValues(int NumValues, bool OnlyMandatory = false);
	virtual void __fastcall AssignFormatting(Vcltee::Teengine::TChartSeries* Source);
	__classmethod virtual bool __fastcall CanDoExtra();
	__classmethod virtual void __fastcall CreateSubGallery(Vcltee::Teengine::TChartSubGalleryProc AddSubChart);
	virtual void __fastcall DrawValue(int ValueIndex);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	DYNAMIC void __fastcall PrepareForGallery();
	
public:
	__fastcall virtual TArrowSeries(System::Classes::TComponent* AOwner);
	int __fastcall AddArrow(const double X0, const double Y0, const double X1, const double Y1, const System::UnicodeString ALabel = System::UnicodeString(), System::Uitypes::TColor AColor = (System::Uitypes::TColor)(0x20000000));
	virtual int __fastcall Clicked(int x, int y)/* overload */;
	DYNAMIC bool __fastcall IsValidSourceOf(Vcltee::Teengine::TChartSeries* Value);
	virtual double __fastcall MaxXValue();
	virtual double __fastcall MinXValue();
	virtual double __fastcall MaxYValue();
	virtual double __fastcall MinYValue();
	
__published:
	__property Active = {default=1};
	__property ColorEachPoint = {default=0};
	__property ColorSource = {default=0};
	__property Cursor = {default=0};
	__property HorizAxis = {default=1};
	__property Marks;
	__property ParentChart;
	__property DataSource;
	__property PercentFormat = {default=0};
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
	__property int ArrowHeight = {read=GetArrowHeight, write=SetArrowHeight, stored=false, nodefault};
	__property int ArrowPercent = {read=FPercent, write=SetPercent, default=50};
	__property int ArrowWidth = {read=GetArrowWidth, write=SetArrowWidth, stored=false, nodefault};
	__property Vcltee::Teengine::TChartValueList* EndXValues = {read=FEndXValues, write=SetEndXValues};
	__property Vcltee::Teengine::TChartValueList* EndYValues = {read=FEndYValues, write=SetEndYValues};
	__property bool Fill2D = {read=FFill2D, write=SetFill2D, default=0};
	__property Vcltee::Teengine::TChartValueList* StartXValues = {read=GetStartXValues, write=SetStartXValues};
	__property Vcltee::Teengine::TChartValueList* StartYValues = {read=GetStartYValues, write=SetStartYValues};
public:
	/* TCustomSeries.Destroy */ inline __fastcall virtual ~TArrowSeries() { }
	
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  Clicked(const float X, const float Y){ return Vcltee::Teengine::TChartSeries::Clicked(X, Y); }
	inline int __fastcall  Clicked(const System::Types::TPoint &P){ return Vcltee::Teengine::TChartSeries::Clicked(P); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Arrowcha */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_ARROWCHA)
using namespace Vcltee::Arrowcha;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_ArrowchaHPP
