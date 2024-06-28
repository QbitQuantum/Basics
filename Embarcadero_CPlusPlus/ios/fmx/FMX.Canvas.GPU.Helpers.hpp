// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Canvas.GPU.Helpers.pas' rev: 34.00 (iOS)

#ifndef Fmx_Canvas_Gpu_HelpersHPP
#define Fmx_Canvas_Gpu_HelpersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Materials.Canvas.hpp>
#include <FMX.Graphics.hpp>
#include <System.Math.Vectors.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Canvas
{
namespace Gpu
{
namespace Helpers
{
//-- forward type declarations -----------------------------------------------
struct TDrawingModeHelper /* Helper for enum 'TDrawingMode' */;
class DELPHICLASS TCanvasHelper;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TDrawingMode : unsigned char { Normal, WriteStencilInvert, ReadStencil, ClearStencil, dmNormal _DEPRECATED_ATTRIBUTE3("Use TDrawingMode.Normal")  = 0, dmWriteStencilInvert _DEPRECATED_ATTRIBUTE3("Use TDrawingMode.WriteStencilInvert")  = 1, dmReadStencil _DEPRECATED_ATTRIBUTE3("Use TDrawingMode.ReadStencil")  = 2, dmClearStencil _DEPRECATED_ATTRIBUTE3("Use TDrawingMode.ClearStencil")  = 3 };

class PASCALIMPLEMENTATION TCanvasHelper : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::DynamicArray<System::Types::TPointF> TVertexArray;
	
	typedef System::DynamicArray<System::Uitypes::TAlphaColor> TAlphaColorArray;
	
	typedef System::DynamicArray<int> TIndexArray;
	
	typedef void __fastcall (__closure *TTransformCallback)(System::Types::TPointF &Position);
	
	
private:
	struct TVertexBufferItem;
	typedef TVertexBufferItem *PVertexBufferItem;
	
	#pragma pack(push,1)
	struct DECLSPEC_DRECORD TVertexBufferItem
	{
	public:
		System::Math::Vectors::TPoint3D Position;
		System::Types::TPointF TexCoord;
		System::Uitypes::TAlphaColor VtxColor;
	};
	#pragma pack(pop)
	
	
	typedef System::Word TIndexBufferItem;
	
	typedef System::StaticArray<TVertexBufferItem, 24576> TBatchVertexBuffer;
	
	typedef System::StaticArray<System::Word, 36864> TBatchIndexBuffer;
	
	enum class DECLSPEC_DENUM TBatchingTopology : unsigned char { None, Pixels, Lines, Triangles };
	
	
private:
	static System::Types::TPointF ZeroPt;
	static constexpr System::Word MaxBatchedVertices = System::Word(0x6000);
	
	static constexpr System::Word MaxBatchedIndices = System::Word(0x9000);
	
	Fmx::Types3d::TTexture* FCurrentTexture;
	TBatchingTopology FCurrentTopology;
	Fmx::Types3d::TMaterial* FCurrentMaterial;
	int FBatchedVertices;
	int FBatchedIndices;
	TBatchVertexBuffer FBatchVertexBuffer;
	TBatchIndexBuffer FBatchIndexBuffer;
	int FFlushCountPerFrame;
	Fmx::Materials::Canvas::TCanvasTextureMaterial* FTexMat;
	Fmx::Materials::Canvas::TCanvasSolidMaterial* FSolidMat;
	Fmx::Materials::Canvas::TCanvasGradientMaterial* FGradientMat;
	Fmx::Types3d::TContext3D* FContext;
	TDrawingMode FDrawingMode;
	TVertexArray TempVertices4;
	TVertexArray TempTexCoords4;
	TAlphaColorArray TempColors4;
	TIndexArray TempIndices6;
	int FPrimitiveCountPerFrame;
	void __fastcall SetDrawingMode(const TDrawingMode Value);
	void __fastcall InsertIndex(const int Value);
	void __fastcall InsertVertex(const System::Types::TPointF &Position, const System::Types::TPointF &TexCoord, const System::Uitypes::TAlphaColor Color);
	void __fastcall ResetBatchingStatus(const TBatchingTopology Topology, Fmx::Types3d::TTexture* const Texture, Fmx::Types3d::TMaterial* const Material);
	void __fastcall UpdateBatchingStatus(const TBatchingTopology Topology, const int MinVertexCount, const int MinIndexCount, Fmx::Types3d::TTexture* const Texture, Fmx::Types3d::TMaterial* const Material);
	void __fastcall UpdateScissorRect();
	void __fastcall DrawBuffers();
	System::Types::TPointF __fastcall CalculateTopLeft(const System::Types::TRectF &ARect, const TTransformCallback TransformCallback);
	void __fastcall FillTrianglesMultiBatch(const TVertexArray Vertices, const TAlphaColorArray Colors, const TIndexArray Indices, const int VertexCount, const int PrimitiveCount);
	
protected:
	System::Types::TRect FScissorRect;
	void __fastcall SetScissorRect(const System::Types::TRect &Value);
	void __fastcall DoClearStencil(const unsigned StencilValue);
	
public:
	__fastcall virtual TCanvasHelper();
	__fastcall virtual ~TCanvasHelper();
	void __fastcall BeginRender();
	void __fastcall EndRender();
	void __fastcall UpdateDrawingMode();
	void __fastcall Flush();
	void __fastcall FillTriangles(const TVertexArray Vertices, const TAlphaColorArray Colors, const TIndexArray Indices, const int VertexCount, const int PrimitiveCount);
	void __fastcall FillRect(const Fmx::Types::TCornersF &Corners, const System::Uitypes::TAlphaColor Color1, const System::Uitypes::TAlphaColor Color2, const System::Uitypes::TAlphaColor Color3, const System::Uitypes::TAlphaColor Color4)/* overload */;
	void __fastcall FillRect(const Fmx::Types::TCornersF &Corners, const System::Uitypes::TAlphaColor Color)/* overload */;
	void __fastcall FillRect(const float X, const float Y, const float Width, const float Height, const System::Uitypes::TAlphaColor Color)/* overload */;
	void __fastcall FillEllipse(const System::Types::TRectF &ARect, const System::Uitypes::TAlphaColor AColor, const TTransformCallback TransformCallback = 0x0);
	void __fastcall FillQuad(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, const System::Types::TPointF &P4, const System::Uitypes::TAlphaColor AColor);
	void __fastcall TexTriangles(Fmx::Types3d::TTexture* const Texture, const TVertexArray Vertices, const TVertexArray TexCoords, const TAlphaColorArray Colors, const TIndexArray Indices, const int VertexCount, const int PrimitiveCount);
	void __fastcall TexRect(const Fmx::Types::TCornersF &DestCorners, const Fmx::Types::TCornersF &SrcCorners, Fmx::Types3d::TTexture* const Texture, const System::Uitypes::TAlphaColor Color1, const System::Uitypes::TAlphaColor Color2, const System::Uitypes::TAlphaColor Color3, const System::Uitypes::TAlphaColor Color4)/* overload */;
	void __fastcall TexRect(const Fmx::Types::TCornersF &DestCorners, const Fmx::Types::TCornersF &SrcCorners, Fmx::Types3d::TTexture* const Texture, const System::Uitypes::TAlphaColor Color)/* overload */;
	void __fastcall TexRect(const Fmx::Types::TCornersF &Corners, Fmx::Types3d::TTexture* const Texture, const System::Uitypes::TAlphaColor Color)/* overload */;
	void __fastcall TexRect(const float X, const float Y, const float Width, const float Height, Fmx::Types3d::TTexture* const Texture, const System::Uitypes::TAlphaColor Color)/* overload */;
	void __fastcall TexQuad(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, const System::Types::TPointF &P4, const System::Types::TPointF &TC1, const System::Types::TPointF &TC2, const System::Types::TPointF &TC3, const System::Types::TPointF &TC4, const System::Uitypes::TAlphaColor AColor, Fmx::Types3d::TTexture* const ATexture);
	void __fastcall TexEllipse(const System::Types::TRectF &ARect, const System::Uitypes::TAlphaColor AColor, Fmx::Types3d::TTexture* const ATexture, const TTransformCallback TransformCallback = 0x0)/* overload */;
	void __fastcall TexEllipse(const System::Types::TRectF &ARect, const System::Types::TRectF &ATexCoord, const System::Uitypes::TAlphaColor AColor, Fmx::Types3d::TTexture* const ATexture, const TTransformCallback TransformCallback = 0x0)/* overload */;
	void __fastcall GradientRect(const Fmx::Types::TCornersF &DestCorners, Fmx::Graphics::TGradient* const AGradient)/* overload */;
	void __fastcall GradientEllipse(const System::Types::TRectF &ARect, Fmx::Graphics::TGradient* const AGradient, const TTransformCallback TransformCallback = 0x0);
	void __fastcall GradientQuad(const System::Types::TPointF &P1, const System::Types::TPointF &P2, const System::Types::TPointF &P3, const System::Types::TPointF &P4, Fmx::Graphics::TGradient* const AGradient);
	void __fastcall GradientTriangles(Fmx::Graphics::TGradient* const AGradient, const TVertexArray Vertices, const TVertexArray TexCoords, const TIndexArray Indices, const int VertexCount, const int PrimitiveCount);
	void __fastcall ResetScissorRect();
	void __fastcall SetScissorRectWithoutUpdate(const System::Types::TRect &R);
	void __fastcall SetContext(Fmx::Types3d::TContext3D* const Context);
	__property System::Types::TRect ScissorRect = {read=FScissorRect, write=SetScissorRect};
	__property TDrawingMode DrawingMode = {read=FDrawingMode, write=SetDrawingMode, nodefault};
	__property int FlushCountPerFrame = {read=FFlushCountPerFrame, nodefault};
	__property int PrimitiveCountPerFrame = {read=FPrimitiveCountPerFrame, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Helpers */
}	/* namespace Gpu */
}	/* namespace Canvas */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS_GPU_HELPERS)
using namespace Fmx::Canvas::Gpu::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS_GPU)
using namespace Fmx::Canvas::Gpu;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS)
using namespace Fmx::Canvas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Canvas_Gpu_HelpersHPP
