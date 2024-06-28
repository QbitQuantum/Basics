// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Chart3D.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Chart3dHPP
#define Fmxtee_Chart3dHPP

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
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.Layers3D.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.MaterialSources.hpp>
#include <System.RTLConsts.hpp>
#include <FMX.Graphics.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Canvas.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Chart3d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomChart3D;
class DELPHICLASS TChart3D;
class DELPHICLASS TLine3D;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomChart3D : public Fmx::Controls3d::TControl3D
{
	typedef Fmx::Controls3d::TControl3D inherited;
	
public:
	Fmxtee::Engine::TChartSeries* operator[](int Index) { return this->Series[Index]; }
	
private:
	float FFontDepth;
	System::Classes::TNotifyEvent FOnCreateChart;
	Fmxtee::Chart::TChart* __fastcall CreateChartControl();
	Fmxtee::Chart::TChart* __fastcall FirstChart();
	Fmxtee::Chart::TChart* __fastcall GetChart();
	Fmxtee::Engine::TChartSeries* __fastcall GetSeries(int Index);
	void __fastcall SetupChart(Fmxtee::Chart::TChart* const AChart);
	Fmxtee::Chart::TChartWalls* __fastcall GetWalls();
	void __fastcall SetFontDepth(const float Value);
	Fmxtee::Engine::TChartAxes* __fastcall GetAxes();
	Fmxtee::Chart::TChartLegend* __fastcall GetLegend();
	Fmxtee::Chart::TChartTitle* __fastcall GetTitle();
	
protected:
	__property float FontDepth = {read=FFontDepth, write=SetFontDepth};
	virtual void __fastcall ReadState(System::Classes::TReader* Reader);
	virtual void __fastcall Render();
	virtual void __fastcall Resize3D();
	void __fastcall SetChart(Fmxtee::Chart::TChart* const Value);
	
public:
	__fastcall virtual TCustomChart3D(System::Classes::TComponent* AOwner);
	void __fastcall CreateChart();
	Fmx::Controls3d::TControl3D* __fastcall FindControl(const System::UnicodeString AName);
	__property Fmxtee::Engine::TChartAxes* Axes = {read=GetAxes};
	__property Fmxtee::Chart::TChart* Chart = {read=GetChart};
	__property Fmxtee::Chart::TChartLegend* Legend = {read=GetLegend};
	__property Fmxtee::Engine::TChartSeries* Series[int Index] = {read=GetSeries/*, default*/};
	__property Fmxtee::Chart::TChartTitle* Title = {read=GetTitle};
	__property Fmxtee::Chart::TChartWalls* Walls = {read=GetWalls};
	__property System::Classes::TNotifyEvent OnCreateChart = {read=FOnCreateChart, write=FOnCreateChart};
public:
	/* TControl3D.Destroy */ inline __fastcall virtual ~TCustomChart3D() { }
	
};


class PASCALIMPLEMENTATION TChart3D : public TCustomChart3D
{
	typedef TCustomChart3D inherited;
	
__published:
	__property Chart;
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Position;
	__property Scale;
	__property RotationAngle;
	__property Locked = {default=0};
	__property Width = {default=0};
	__property Height = {default=0};
	__property Depth = {default=0};
	__property Opacity;
	__property Projection = {default=0};
	__property HitTest = {default=1};
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=0};
	__property Visible = {default=1};
	__property ZWrite = {default=1};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnRender;
	__property OnCreateChart;
	__property OnMouseEnter;
	__property OnMouseLeave;
public:
	/* TCustomChart3D.Create */ inline __fastcall virtual TChart3D(System::Classes::TComponent* AOwner) : TCustomChart3D(AOwner) { }
	
public:
	/* TControl3D.Destroy */ inline __fastcall virtual ~TChart3D() { }
	
};


typedef System::Math::Vectors::TPoint3D TPoint3D;

class PASCALIMPLEMENTATION TLine3D : public Fmx::Objects3d::TShape3D
{
	typedef Fmx::Objects3d::TShape3D inherited;
	
private:
	System::Math::Vectors::TPoint3D FStart;
	System::Math::Vectors::TPoint3D FEnd;
	void __fastcall SetEnd(const System::Math::Vectors::TPoint3D &Value);
	void __fastcall SetStart(const System::Math::Vectors::TPoint3D &Value);
	
protected:
	virtual void __fastcall Render();
	
public:
	virtual bool __fastcall RayCastIntersect(const System::Math::Vectors::TPoint3D &RayPos, const System::Math::Vectors::TPoint3D &RayDir, System::Math::Vectors::TPoint3D &Intersection);
	__property System::Math::Vectors::TPoint3D StartPoint = {read=FStart, write=SetStart};
	__property System::Math::Vectors::TPoint3D EndPoint = {read=FEnd, write=SetEnd};
public:
	/* TShape3D.Create */ inline __fastcall virtual TLine3D(System::Classes::TComponent* AOwner) : Fmx::Objects3d::TShape3D(AOwner) { }
	/* TShape3D.Destroy */ inline __fastcall virtual ~TLine3D() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Chart3d */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART3D)
using namespace Fmxtee::Chart3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Chart3dHPP
