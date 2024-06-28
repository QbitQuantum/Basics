// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.StrokeBuilder.pas' rev: 34.00 (Windows)

#ifndef Fmx_StrokebuilderHPP
#define Fmx_StrokebuilderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Canvas.GPU.Helpers.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Strokebuilder
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStrokeBuilder;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStrokeBuilder : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Math::Vectors::TMatrix FMatrix;
	Fmx::Graphics::TStrokeBrush* FBrush;
	Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TVertexArray FVertices;
	Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TAlphaColorArray FColors;
	Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TIndexArray FIndices;
	int FCurrentVertex;
	int FCurrentIndex;
	int FSegmentCount;
	float FLastSegmentFraction;
	int FExtraPieces;
	bool FLastDashExtend;
	float FThickness;
	float FHalfThickness;
	System::Uitypes::TAlphaColor FStrokeColor;
	System::Types::TPointF FEllipseCenter;
	System::Types::TPointF FEllipseRadius;
	float FEllipseCircumf;
	System::Types::TPointF FEllipseTransfCenter;
	bool FUndeterminedMode;
	System::Types::TPointF __fastcall GetMatrixScale();
	void __fastcall ArrayFillCheck();
	void __fastcall InitArrays(const int VertexCount, const int IndexCount);
	void __fastcall FinalizeArrays();
	void __fastcall InitArrayPointers();
	void __fastcall InsertVertex(const System::Types::TPointF &VertexPos, const System::Uitypes::TAlphaColor Color);
	void __fastcall InsertIndex(const int Value);
	int __fastcall GetCapDivisions();
	void __fastcall GetDashEstimate(/* out */ int &VertexCount, /* out */ int &IndexCount);
	void __fastcall InsertDash(const System::Types::TPointF &SrcPos, const System::Types::TPointF &DestPos, const System::Types::TPointF &DashDirVec, const System::Types::TPointF &ThickPerp);
	void __fastcall GetDotEstimate(/* out */ int &VertexCount, /* out */ int &IndexCount);
	void __fastcall InsertDot(const System::Types::TPointF &MidPos, const System::Types::TPointF &DotDirVec, const System::Types::TPointF &ThickPerp);
	int __fastcall GetPatternStepCount();
	void __fastcall ComputeBuildEstimates(const float TentSegmentCount, /* out */ int &VertexCount, /* out */ int &IndexCount);
	void __fastcall InsertSegment(const System::Types::TPointF &SegmentPos, const System::Types::TPointF &SegDirVec, const System::Types::TPointF &ThickPerp, const System::Types::TPointF &DestPos, bool IsLast);
	System::Types::TPointF __fastcall GetEllipseTransfAt(const float Delta);
	void __fastcall InsertEllipseSegment(const float SegInitDist, bool IsLast);
	
public:
	void __fastcall BuildLine(const System::Types::TPointF &SrcPos, const System::Types::TPointF &DestPos, const float Opacity);
	void __fastcall BuildIntermEllipse(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, const float Opacity);
	void __fastcall BuildSolidEllipse(const System::Types::TPointF &Center, const System::Types::TPointF &Radius, const float Opacity);
	void __fastcall BuildIntermPolygon(const System::Math::Vectors::TPolygon Points, const float Opacity, bool BreakAtEnd = false);
	void __fastcall BuildSolidPolygon(const System::Math::Vectors::TPolygon Points, const float Opacity, bool BreakAtEnd = false);
	void __fastcall BuildIntermPath(Fmx::Graphics::TPathData* const Path, const float Opacity);
	void __fastcall BuildSolidPath(Fmx::Graphics::TPathData* const Path, const float Opacity);
	void __fastcall ResetArrays();
	__property System::Math::Vectors::TMatrix Matrix = {read=FMatrix, write=FMatrix};
	__property Fmx::Graphics::TStrokeBrush* Brush = {read=FBrush, write=FBrush};
	__property Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TVertexArray Vertices = {read=FVertices};
	__property Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TAlphaColorArray Colors = {read=FColors};
	__property Fmx::Canvas::Gpu::Helpers::TCanvasHelper::TIndexArray Indices = {read=FIndices};
public:
	/* TObject.Create */ inline __fastcall TStrokeBuilder() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStrokeBuilder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Strokebuilder */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_STROKEBUILDER)
using namespace Fmx::Strokebuilder;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_StrokebuilderHPP
