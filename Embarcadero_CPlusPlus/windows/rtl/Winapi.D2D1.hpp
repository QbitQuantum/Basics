// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D2D1.pas' rev: 34.00 (Windows)

#ifndef Winapi_D2d1HPP
#define Winapi_D2d1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Wincodec.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.D3DCommon.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include <d2d1.h>
#include <dwrite.h>

namespace Winapi
{
namespace D2d1
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ID2D1Resource;
typedef System::DelphiInterface<ID2D1Resource> _di_ID2D1Resource;
__interface DELPHIINTERFACE ID2D1Bitmap;
typedef System::DelphiInterface<ID2D1Bitmap> _di_ID2D1Bitmap;
__interface DELPHIINTERFACE ID2D1GradientStopCollection;
typedef System::DelphiInterface<ID2D1GradientStopCollection> _di_ID2D1GradientStopCollection;
__interface DELPHIINTERFACE ID2D1Brush;
typedef System::DelphiInterface<ID2D1Brush> _di_ID2D1Brush;
__interface DELPHIINTERFACE ID2D1BitmapBrush;
typedef System::DelphiInterface<ID2D1BitmapBrush> _di_ID2D1BitmapBrush;
__interface DELPHIINTERFACE ID2D1SolidColorBrush;
typedef System::DelphiInterface<ID2D1SolidColorBrush> _di_ID2D1SolidColorBrush;
__interface DELPHIINTERFACE ID2D1LinearGradientBrush;
typedef System::DelphiInterface<ID2D1LinearGradientBrush> _di_ID2D1LinearGradientBrush;
__interface DELPHIINTERFACE ID2D1RadialGradientBrush;
typedef System::DelphiInterface<ID2D1RadialGradientBrush> _di_ID2D1RadialGradientBrush;
__interface DELPHIINTERFACE ID2D1StrokeStyle;
typedef System::DelphiInterface<ID2D1StrokeStyle> _di_ID2D1StrokeStyle;
__interface DELPHIINTERFACE ID2D1Geometry;
typedef System::DelphiInterface<ID2D1Geometry> _di_ID2D1Geometry;
__interface DELPHIINTERFACE ID2D1RectangleGeometry;
typedef System::DelphiInterface<ID2D1RectangleGeometry> _di_ID2D1RectangleGeometry;
__interface DELPHIINTERFACE ID2D1RoundedRectangleGeometry;
typedef System::DelphiInterface<ID2D1RoundedRectangleGeometry> _di_ID2D1RoundedRectangleGeometry;
__interface DELPHIINTERFACE ID2D1EllipseGeometry;
typedef System::DelphiInterface<ID2D1EllipseGeometry> _di_ID2D1EllipseGeometry;
__interface DELPHIINTERFACE ID2D1GeometryGroup;
typedef System::DelphiInterface<ID2D1GeometryGroup> _di_ID2D1GeometryGroup;
__interface DELPHIINTERFACE ID2D1TransformedGeometry;
typedef System::DelphiInterface<ID2D1TransformedGeometry> _di_ID2D1TransformedGeometry;
__interface DELPHIINTERFACE ID2D1SimplifiedGeometrySink;
typedef System::DelphiInterface<ID2D1SimplifiedGeometrySink> _di_ID2D1SimplifiedGeometrySink;
__interface DELPHIINTERFACE ID2D1GeometrySink;
typedef System::DelphiInterface<ID2D1GeometrySink> _di_ID2D1GeometrySink;
__interface DELPHIINTERFACE ID2D1TessellationSink;
typedef System::DelphiInterface<ID2D1TessellationSink> _di_ID2D1TessellationSink;
__interface DELPHIINTERFACE ID2D1PathGeometry;
typedef System::DelphiInterface<ID2D1PathGeometry> _di_ID2D1PathGeometry;
__interface DELPHIINTERFACE ID2D1Mesh;
typedef System::DelphiInterface<ID2D1Mesh> _di_ID2D1Mesh;
__interface DELPHIINTERFACE ID2D1Layer;
typedef System::DelphiInterface<ID2D1Layer> _di_ID2D1Layer;
__interface DELPHIINTERFACE ID2D1DrawingStateBlock;
typedef System::DelphiInterface<ID2D1DrawingStateBlock> _di_ID2D1DrawingStateBlock;
__interface DELPHIINTERFACE ID2D1RenderTarget;
typedef System::DelphiInterface<ID2D1RenderTarget> _di_ID2D1RenderTarget;
__interface DELPHIINTERFACE ID2D1BitmapRenderTarget;
typedef System::DelphiInterface<ID2D1BitmapRenderTarget> _di_ID2D1BitmapRenderTarget;
__interface DELPHIINTERFACE ID2D1HwndRenderTarget;
typedef System::DelphiInterface<ID2D1HwndRenderTarget> _di_ID2D1HwndRenderTarget;
__interface DELPHIINTERFACE ID2D1GdiInteropRenderTarget;
typedef System::DelphiInterface<ID2D1GdiInteropRenderTarget> _di_ID2D1GdiInteropRenderTarget;
__interface DELPHIINTERFACE ID2D1DCRenderTarget;
typedef System::DelphiInterface<ID2D1DCRenderTarget> _di_ID2D1DCRenderTarget;
__interface DELPHIINTERFACE ID2D1Factory;
typedef System::DelphiInterface<ID2D1Factory> _di_ID2D1Factory;
__interface DELPHIINTERFACE IDWriteFontFileLoader;
typedef System::DelphiInterface<IDWriteFontFileLoader> _di_IDWriteFontFileLoader;
__interface DELPHIINTERFACE IDWriteLocalFontFileLoader;
typedef System::DelphiInterface<IDWriteLocalFontFileLoader> _di_IDWriteLocalFontFileLoader;
__interface DELPHIINTERFACE IDWriteFontFileStream;
typedef System::DelphiInterface<IDWriteFontFileStream> _di_IDWriteFontFileStream;
__interface DELPHIINTERFACE IDWriteFontFile;
typedef System::DelphiInterface<IDWriteFontFile> _di_IDWriteFontFile;
__interface DELPHIINTERFACE IDWriteRenderingParams;
typedef System::DelphiInterface<IDWriteRenderingParams> _di_IDWriteRenderingParams;
__interface DELPHIINTERFACE IDWriteFontFace;
typedef System::DelphiInterface<IDWriteFontFace> _di_IDWriteFontFace;
__interface DELPHIINTERFACE IDWriteFontCollectionLoader;
typedef System::DelphiInterface<IDWriteFontCollectionLoader> _di_IDWriteFontCollectionLoader;
__interface DELPHIINTERFACE IDWriteFontFileEnumerator;
typedef System::DelphiInterface<IDWriteFontFileEnumerator> _di_IDWriteFontFileEnumerator;
__interface DELPHIINTERFACE IDWriteLocalizedStrings;
typedef System::DelphiInterface<IDWriteLocalizedStrings> _di_IDWriteLocalizedStrings;
__interface DELPHIINTERFACE IDWriteFontCollection;
typedef System::DelphiInterface<IDWriteFontCollection> _di_IDWriteFontCollection;
__interface DELPHIINTERFACE IDWriteFontList;
typedef System::DelphiInterface<IDWriteFontList> _di_IDWriteFontList;
__interface DELPHIINTERFACE IDWriteFontFamily;
typedef System::DelphiInterface<IDWriteFontFamily> _di_IDWriteFontFamily;
__interface DELPHIINTERFACE IDWriteFont;
typedef System::DelphiInterface<IDWriteFont> _di_IDWriteFont;
__interface DELPHIINTERFACE IDWriteTextFormat;
typedef System::DelphiInterface<IDWriteTextFormat> _di_IDWriteTextFormat;
__interface DELPHIINTERFACE IDWriteTypography;
typedef System::DelphiInterface<IDWriteTypography> _di_IDWriteTypography;
__interface DELPHIINTERFACE IDWriteNumberSubstitution;
typedef System::DelphiInterface<IDWriteNumberSubstitution> _di_IDWriteNumberSubstitution;
__interface DELPHIINTERFACE IDWriteTextAnalysisSource;
typedef System::DelphiInterface<IDWriteTextAnalysisSource> _di_IDWriteTextAnalysisSource;
__interface DELPHIINTERFACE IDWriteTextAnalysisSink;
typedef System::DelphiInterface<IDWriteTextAnalysisSink> _di_IDWriteTextAnalysisSink;
__interface DELPHIINTERFACE IDWriteTextAnalyzer;
typedef System::DelphiInterface<IDWriteTextAnalyzer> _di_IDWriteTextAnalyzer;
__interface DELPHIINTERFACE IDWriteInlineObject;
typedef System::DelphiInterface<IDWriteInlineObject> _di_IDWriteInlineObject;
__interface DELPHIINTERFACE IDWritePixelSnapping;
typedef System::DelphiInterface<IDWritePixelSnapping> _di_IDWritePixelSnapping;
__interface DELPHIINTERFACE IDWriteTextRenderer;
typedef System::DelphiInterface<IDWriteTextRenderer> _di_IDWriteTextRenderer;
__interface DELPHIINTERFACE IDWriteTextLayout;
typedef System::DelphiInterface<IDWriteTextLayout> _di_IDWriteTextLayout;
__interface DELPHIINTERFACE IDWriteBitmapRenderTarget;
typedef System::DelphiInterface<IDWriteBitmapRenderTarget> _di_IDWriteBitmapRenderTarget;
__interface DELPHIINTERFACE IDWriteGdiInterop;
typedef System::DelphiInterface<IDWriteGdiInterop> _di_IDWriteGdiInterop;
__interface DELPHIINTERFACE IDWriteGlyphRunAnalysis;
typedef System::DelphiInterface<IDWriteGlyphRunAnalysis> _di_IDWriteGlyphRunAnalysis;
__interface DELPHIINTERFACE IDWriteFactory;
typedef System::DelphiInterface<IDWriteFactory> _di_IDWriteFactory;
struct TD2DMatrix3x2FHelper /* Helper for record 'D2D_MATRIX_3X2_F' */;
//-- type declarations -------------------------------------------------------
typedef D3DCOLORVALUE TD3DColorValue;

typedef D3DCOLORVALUE *PD3DColorValue;

typedef D2D_RECT_F TD2DRectF;

typedef D2D_RECT_F *PD2DRectF;

typedef D2D_RECT_U TD2DRectU;

typedef D2D_RECT_U *PD2DRectU;

typedef D2D_SIZE_F TD2DSizeF;

typedef D2D_SIZE_F *PD2DSizeF;

typedef D2D_SIZE_U TD2DSizeU;

typedef D2D_SIZE_U *PD2DSizeU;

typedef D2D_MATRIX_3X2_F TD2DMatrix3x2F;

typedef D2D_MATRIX_3X2_F *PD2DMatrix3x2F;

typedef D2D_POINT_2U TD2DPoint2u;

typedef D2D_POINT_2U *PD2DPoint2u;

typedef D2D_POINT_2F TD2DPoint2f;

typedef D2D_POINT_2F *PD2DPoint2f;

typedef DWRITE_MEASURING_MODE TDWriteMeasuringMode;

typedef DWRITE_MEASURING_MODE *PDWriteMeasuringMode;

typedef D2D1_ALPHA_MODE TD2D1AlphaMode;

typedef D2D1_ALPHA_MODE *PD2D1AlphaMode;

typedef D2D1_GAMMA TD2D1Gamma;

typedef D2D1_GAMMA *PD2D1Gamma;

typedef D2D1_OPACITY_MASK_CONTENT TD2D1OpacityMaskContent;

typedef D2D1_OPACITY_MASK_CONTENT *PD2D1OpacityMaskContent;

typedef D2D1_EXTEND_MODE TD2D1ExtendMode;

typedef D2D1_EXTEND_MODE *PD2D1ExtendMode;

typedef D2D1_ANTIALIAS_MODE TD2D1AntiAliasMode;

typedef D2D1_ANTIALIAS_MODE *PD2D1AntiAliasMode;

typedef D2D1_TEXT_ANTIALIAS_MODE TD2D1TextAntiAliasMode;

typedef D2D1_TEXT_ANTIALIAS_MODE *PD2D1TextAntiAliasMode;

typedef D2D1_BITMAP_INTERPOLATION_MODE TD2D1BitmapInterpolationMode;

typedef D2D1_BITMAP_INTERPOLATION_MODE *PD2D1BitmapInterpolationMode;

typedef D2D1_DRAW_TEXT_OPTIONS TD2D1DrawTextOptions;

typedef D2D1_DRAW_TEXT_OPTIONS *PD2D1DrawTextOptions;

typedef D2D1_ARC_SIZE TD2D1ArcSize;

typedef D2D1_ARC_SIZE *PD2D1ArcSize;

typedef D2D1_CAP_STYLE TD2D1CapStyle;

typedef D2D1_CAP_STYLE *PD2D1CapStyle;

typedef D2D1_DASH_STYLE TD2D1DashStyle;

typedef D2D1_DASH_STYLE *PD2D1DashStyle;

typedef D2D1_LINE_JOIN TD2D1LineJoin;

typedef D2D1_LINE_JOIN *PD2D1LineJoin;

typedef D2D1_COMBINE_MODE TD2D1CombineMode;

typedef D2D1_COMBINE_MODE *PD2D1CombineMode;

typedef D2D1_GEOMETRY_RELATION TD2D1GeometryRelation;

typedef D2D1_GEOMETRY_RELATION *PD2D1GeometryRelation;

typedef D2D1_GEOMETRY_SIMPLIFICATION_OPTION TD2D1GeometrySimplificationOption;

typedef D2D1_GEOMETRY_SIMPLIFICATION_OPTION *PD2D1GeometrySimplificationOption;

typedef D2D1_FIGURE_BEGIN TD2D1FigureBegin;

typedef D2D1_FIGURE_BEGIN *PD2D1FigureBegin;

typedef D2D1_FIGURE_END TD2D1_FigureEnd;

typedef D2D1_FIGURE_END *PD2D1_FigureEnd;

typedef D2D1_PATH_SEGMENT TD2D1PathSegment;

typedef D2D1_PATH_SEGMENT *PD2D1PathSegment;

typedef D2D1_SWEEP_DIRECTION TD2D1SweepDirection;

typedef D2D1_SWEEP_DIRECTION *PD2D1SweepDirection;

typedef D2D1_FILL_MODE TD2D1FillMode;

typedef D2D1_FILL_MODE *PD2D1FillMode;

typedef D2D1_LAYER_OPTIONS TD2D1LayerOptions;

typedef D2D1_LAYER_OPTIONS *PD2D1LayerOptions;

typedef D2D1_WINDOW_STATE TD2D1WindowState;

typedef D2D1_WINDOW_STATE *PD2D1WindowState;

typedef D2D1_RENDER_TARGET_TYPE TD2D1RenderTargetType;

typedef D2D1_RENDER_TARGET_TYPE *PD2D1RenderTargetType;

typedef D2D1_FEATURE_LEVEL TD2D1FeatureLevel;

typedef D2D1_FEATURE_LEVEL *PD2D1FeatureLevel;

typedef D3D10_FEATURE_LEVEL1 TD3D10FeatureLevel1;

typedef D3D10_FEATURE_LEVEL1 *PD3D10FeatureLevel1;

typedef D2D1_RENDER_TARGET_USAGE TD2D1RenderTargetUsage;

typedef D2D1_RENDER_TARGET_USAGE *PD2D1RenderTargetUsage;

typedef D2D1_PRESENT_OPTIONS TD2D1PresentOptions;

typedef D2D1_PRESENT_OPTIONS *PD2D1PresentOptions;

typedef D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS TD2D1CompatibleRenderTargetOptions;

typedef D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS *PD2D1CompatibleRenderTargetOptions;

typedef D2D1_DC_INITIALIZE_MODE TD2D1DCInitializeMode;

typedef D2D1_DC_INITIALIZE_MODE *PD2D1DCInitializeMode;

typedef D2D1_DEBUG_LEVEL TD2D1DebugLevel;

typedef D2D1_DEBUG_LEVEL *PD2D1DebugLevel;

typedef D2D1_FACTORY_TYPE TD2D1FactoryType;

typedef D2D1_FACTORY_TYPE *PD2D1FactoryType;

typedef DWRITE_FONT_FILE_TYPE TDWriteFontFileType;

typedef DWRITE_FONT_FILE_TYPE *PDWriteFontFileType;

typedef DWRITE_FONT_FACE_TYPE TDWriteFontFaceType;

typedef DWRITE_FONT_FACE_TYPE *PDWriteFontFaceType;

typedef DWRITE_FONT_SIMULATIONS TDWriteFontSimulations;

typedef DWRITE_FONT_SIMULATIONS *PDWriteFontSimulations;

typedef DWRITE_FONT_WEIGHT TDWriteFontWeight;

typedef DWRITE_FONT_WEIGHT *PDWriteFontWeight;

typedef DWRITE_FONT_STRETCH TDWriteFontStretch;

typedef DWRITE_FONT_STRETCH *PDWriteFontStretch;

typedef DWRITE_FONT_STYLE TDWriteFontStyle;

typedef DWRITE_FONT_STYLE *PDWriteFontStyle;

typedef DWRITE_INFORMATIONAL_STRING_ID TDWriteInformationalStringID;

typedef DWRITE_INFORMATIONAL_STRING_ID *PDWriteInformationalStringID;

typedef DWRITE_FACTORY_TYPE TDWriteFactoryType;

typedef DWRITE_FACTORY_TYPE *PDWriteFactoryType;

typedef DWRITE_PIXEL_GEOMETRY TDWritePixelGeometry;

typedef DWRITE_PIXEL_GEOMETRY *PDWritePixelGeometry;

typedef DWRITE_RENDERING_MODE TDWriteRenderingMode;

typedef DWRITE_RENDERING_MODE *PDWriteRenderingMode;

typedef DWRITE_READING_DIRECTION TDWriteReadingDirection;

typedef DWRITE_READING_DIRECTION *PDWriteReadingDirection;

typedef DWRITE_FLOW_DIRECTION TDWriteFlowDirection;

typedef DWRITE_FLOW_DIRECTION *PDWriteFlowDirection;

typedef DWRITE_TEXT_ALIGNMENT TDWriteTextAlignment;

typedef DWRITE_TEXT_ALIGNMENT *PDWriteTextAlignment;

typedef DWRITE_PARAGRAPH_ALIGNMENT TDWriteParagraphAlignment;

typedef DWRITE_PARAGRAPH_ALIGNMENT *PDWriteParagraphAlignment;

typedef DWRITE_WORD_WRAPPING TDWriteWordWrapping;

typedef DWRITE_WORD_WRAPPING *PDWriteWordWrapping;

typedef DWRITE_LINE_SPACING_METHOD TDWwriteLineSpacingMethod;

typedef DWRITE_LINE_SPACING_METHOD *PDWwriteLineSpacingMethod;

typedef DWRITE_TRIMMING_GRANULARITY TDWriteTrimmingGranularity;

typedef DWRITE_TRIMMING_GRANULARITY *PDWriteTrimmingGranularity;

typedef DWRITE_FONT_FEATURE_TAG TDWriteFontFeatureTag;

typedef DWRITE_FONT_FEATURE_TAG *PDWriteFontFeatureTag;

typedef DWRITE_SCRIPT_SHAPES TDWriteScriptShapes;

typedef DWRITE_SCRIPT_SHAPES *PDWriteScriptShapes;

typedef DWRITE_BREAK_CONDITION TDWriteBreakCondition;

typedef DWRITE_BREAK_CONDITION *PDWriteBreakCondition;

typedef DWRITE_NUMBER_SUBSTITUTION_METHOD TDWriteNumberSubstitutionMethod;

typedef DWRITE_NUMBER_SUBSTITUTION_METHOD *PDWriteNumberSubstitutionMethod;

typedef DWRITE_TEXTURE_TYPE TDWriteTextureType;

typedef DWRITE_TEXTURE_TYPE *PDWriteTextureType;

typedef D2D1_PIXEL_FORMAT TD2D1PixelFormat;

typedef D2D1_PIXEL_FORMAT *PD2D1PixelFormat;

typedef D2D_POINT_2U TD2D1Point2U;

typedef D2D_POINT_2U *PD2D1Point2U;

typedef D2D_POINT_2F TD2D1Point2F;

typedef D2D_POINT_2F *PD2D1Point2F;

typedef D2D_RECT_F TD2D1RectF;

typedef D2D_RECT_F *PD2D1RectF;

typedef D2D_RECT_U TD2D1RectU;

typedef D2D_RECT_U *PD2D1RectU;

typedef D2D_SIZE_F TD2D1SizeF;

typedef D2D_SIZE_F *PD2D1SizeF;

typedef D2D_SIZE_U TD2D1SizeU;

typedef D2D_SIZE_U *PD2D1SizeU;

typedef D3DCOLORVALUE TD2D1ColorF;

typedef D3DCOLORVALUE *PD2D1ColorF;

typedef D2D_MATRIX_3X2_F TD2D1Matrix3x2F;

typedef D2D_MATRIX_3X2_F *PD2D1Matrix3x2F;

typedef unsigned __int64 TD2D1Tag;

typedef unsigned __int64 *PD2D1Tag;

typedef D2D1_BITMAP_PROPERTIES TD2D1BitmapProperties;

typedef D2D1_BITMAP_PROPERTIES *PD2D1BitmapProperties;

typedef D2D1_GRADIENT_STOP TD2D1GradientStop;

typedef D2D1_GRADIENT_STOP *PD2D1GradientStop;

typedef D2D1_BRUSH_PROPERTIES TD2D1BrushProperties;

typedef D2D1_BRUSH_PROPERTIES *PD2D1BrushProperties;

typedef D2D1_BITMAP_BRUSH_PROPERTIES TD2D1BitmapBrushProperties;

typedef D2D1_BITMAP_BRUSH_PROPERTIES *PD2D1BitmapBrushProperties;

typedef D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES TD2D1LinearGradientBrushProperties;

typedef D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *PD2D1LinearGradientBrushProperties;

typedef D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES TD2D1RadialGradientBrushProperties;

typedef D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *PD2D1RadialGradientBrushProperties;

typedef D2D1_BEZIER_SEGMENT TD2D1BezierSegment;

typedef D2D1_BEZIER_SEGMENT *PD2D1BezierSegment;

typedef D2D1_TRIANGLE TD2D1Triangle;

typedef D2D1_TRIANGLE *PD2D1Triangle;

typedef D2D1_ARC_SEGMENT TD2D1ArcSegment;

typedef D2D1_ARC_SEGMENT *PD2D1ArcSegment;

typedef D2D1_QUADRATIC_BEZIER_SEGMENT TD2D1QuadraticBezierSegment;

typedef D2D1_QUADRATIC_BEZIER_SEGMENT *PD2D1QuadraticBezierSegment;

typedef D2D1_ELLIPSE TD2D1Ellipse;

typedef D2D1_ELLIPSE *PD2D1Ellipse;

typedef D2D1_ROUNDED_RECT TD2D1RoundedRect;

typedef D2D1_ROUNDED_RECT *PD2D1RoundedRect;

typedef D2D1_STROKE_STYLE_PROPERTIES TD2D1StrokeStyleProperties;

typedef D2D1_STROKE_STYLE_PROPERTIES *PD2D1StrokeStyleProperties;

typedef D2D1_RENDER_TARGET_PROPERTIES TD2D1RenderTargetProperties;

typedef D2D1_RENDER_TARGET_PROPERTIES *PD2D1RenderTargetProperties;

typedef D2D1_HWND_RENDER_TARGET_PROPERTIES TD2D1HwndRenderTargetProperties;

typedef D2D1_HWND_RENDER_TARGET_PROPERTIES *PD2D1HwndRenderTargetProperties;

typedef D2D1_DRAWING_STATE_DESCRIPTION TD2D1DrawingStateDescription;

typedef D2D1_DRAWING_STATE_DESCRIPTION *PD2D1DrawingStateDescription;

typedef D2D1_FACTORY_OPTIONS TD2D1FactoryOptions;

typedef D2D1_FACTORY_OPTIONS *PD2D1FactoryOptions;

typedef D2D1_LAYER_PARAMETERS TD2D1LayerParameters;

typedef D2D1_LAYER_PARAMETERS *PD2D1LayerParameters;

typedef DWRITE_FONT_METRICS TDwriteFontMetrics;

typedef DWRITE_FONT_METRICS *PDwriteFontMetrics;

typedef DWRITE_GLYPH_METRICS TDwriteGlyphMetrics;

typedef DWRITE_GLYPH_METRICS *PDwriteGlyphMetrics;

typedef DWRITE_GLYPH_OFFSET TDwriteGlyphOffset;

typedef DWRITE_GLYPH_OFFSET *PDwriteGlyphOffset;

typedef DWRITE_MATRIX TDwriteMatrix;

typedef DWRITE_MATRIX *PDwriteMatrix;

typedef DWRITE_TEXT_RANGE TDwriteTextRange;

typedef DWRITE_TEXT_RANGE *PDwriteTextRange;

typedef DWRITE_FONT_FEATURE TDwriteFontFeature;

typedef DWRITE_FONT_FEATURE *PDwriteFontFeature;

typedef DWRITE_TYPOGRAPHIC_FEATURES TDwriteTypographicFeatures;

typedef DWRITE_TYPOGRAPHIC_FEATURES *PDwriteTypographicFeatures;

typedef DWRITE_TRIMMING TDwriteTrimming;

typedef DWRITE_TRIMMING *PDwriteTrimming;

typedef DWRITE_SCRIPT_ANALYSIS TDwriteScriptAnalysis;

typedef DWRITE_SCRIPT_ANALYSIS *PDwriteScriptAnalysis;

typedef DWRITE_LINE_BREAKPOINT TDwriteLineBreakpoint;

typedef DWRITE_LINE_BREAKPOINT *PDwriteLineBreakpoint;

typedef DWRITE_SHAPING_TEXT_PROPERTIES TDwriteShapingTextProperties;

typedef DWRITE_SHAPING_TEXT_PROPERTIES *PDwriteShapingTextProperties;

typedef DWRITE_SHAPING_GLYPH_PROPERTIES TDwriteShapingGlyphProperties;

typedef DWRITE_SHAPING_GLYPH_PROPERTIES *PDwriteShapingGlyphProperties;

typedef DWRITE_GLYPH_RUN TDwriteGlyphRun;

typedef DWRITE_GLYPH_RUN *PDwriteGlyphRun;

typedef DWRITE_GLYPH_RUN_DESCRIPTION TDwriteGlyphRunDescription;

typedef DWRITE_GLYPH_RUN_DESCRIPTION *PDwriteGlyphRunDescription;

typedef DWRITE_UNDERLINE TDwriteUnderline;

typedef DWRITE_UNDERLINE *PDwriteUnderline;

typedef DWRITE_STRIKETHROUGH TDwriteStrikethrough;

typedef DWRITE_STRIKETHROUGH *PDwriteStrikethrough;

typedef DWRITE_LINE_METRICS TDwriteLineMetrics;

typedef DWRITE_LINE_METRICS *PDwriteLineMetrics;

typedef DWRITE_CLUSTER_METRICS TDwriteClusterMetrics;

typedef DWRITE_CLUSTER_METRICS *PDwriteClusterMetrics;

typedef DWRITE_TEXT_METRICS TDWriteTextMetrics;

typedef DWRITE_TEXT_METRICS *PDWriteTextMetrics;

typedef DWRITE_INLINE_OBJECT_METRICS TDwriteInlineObjectMetrics;

typedef DWRITE_INLINE_OBJECT_METRICS *PDwriteInlineObjectMetrics;

typedef DWRITE_OVERHANG_METRICS TDwriteOverhangMetrics;

typedef DWRITE_OVERHANG_METRICS *PDwriteOverhangMetrics;

typedef DWRITE_HIT_TEST_METRICS TDwriteHitTestMetrics;

typedef DWRITE_HIT_TEST_METRICS *PDwriteHitTestMetrics;

__interface  INTERFACE_UUID("{2CD90691-12E2-11DC-9FED-001143A055F9}") ID2D1Resource  : public System::IInterface 
{
	virtual void __stdcall GetFactory(/* out */ _di_ID2D1Factory &factory) = 0 ;
};

__interface  INTERFACE_UUID("{A2296057-EA42-4099-983B-539FB6505426}") ID2D1Bitmap  : public ID2D1Resource 
{
	virtual void __stdcall GetSize(/* out */ D2D_SIZE_F &size) = 0 ;
	virtual void __stdcall GetPixelSize(/* out */ D2D_SIZE_U &pixelSize) = 0 ;
	virtual void __stdcall GetPixelFormat(/* out */ D2D1_PIXEL_FORMAT &pixelFormat) = 0 ;
	virtual void __stdcall GetDpi(/* out */ float &dpiX, /* out */ float &dpiY) = 0 ;
	virtual HRESULT __stdcall CopyFromBitmap(D2D_POINT_2U &destPoint, const _di_ID2D1Bitmap bitmap, D2D_RECT_U &srcRect) = 0 ;
	virtual HRESULT __stdcall CopyFromRenderTarget(D2D_POINT_2U &destPoint, const _di_ID2D1RenderTarget renderTarget, D2D_RECT_U &srcRect) = 0 ;
	virtual HRESULT __stdcall CopyFromMemory(D2D_RECT_U &dstRect, void * srcData, unsigned pitch) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A7-12E2-11DC-9FED-001143A055F9}") ID2D1GradientStopCollection  : public ID2D1Resource 
{
	virtual unsigned __stdcall GetGradientStopCount() = 0 ;
	virtual void __stdcall GetGradientStops(PD2D1GradientStop gradientStops, unsigned gradientStopsCount) = 0 ;
	virtual D2D1_GAMMA __stdcall GetColorInterpolationGamma() = 0 ;
	virtual D2D1_EXTEND_MODE __stdcall GetExtendMode() = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A8-12E2-11DC-9FED-001143A055F9}") ID2D1Brush  : public ID2D1Resource 
{
	virtual void __stdcall SetOpacity(float opacity) = 0 ;
	virtual void __stdcall SetTransform(const D2D_MATRIX_3X2_F &transform) = 0 ;
	virtual float __stdcall GetOpacity() = 0 ;
	virtual void __stdcall GetTransform(/* out */ D2D_MATRIX_3X2_F &transform) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906AA-12E2-11DC-9FED-001143A055F9}") ID2D1BitmapBrush  : public ID2D1Brush 
{
	virtual void __stdcall SetExtendModeX(D2D1_EXTEND_MODE extendModeX) = 0 ;
	virtual void __stdcall SetExtendModeY(D2D1_EXTEND_MODE extendModeY) = 0 ;
	virtual void __stdcall SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE interpolationMode) = 0 ;
	virtual void __stdcall SetBitmap(const _di_ID2D1Bitmap bitmap) = 0 ;
	virtual D2D1_EXTEND_MODE __stdcall GetExtendModeX() = 0 ;
	virtual D2D1_EXTEND_MODE __stdcall GetExtendModeY() = 0 ;
	virtual D2D1_BITMAP_INTERPOLATION_MODE __stdcall GetInterpolationMode() = 0 ;
	virtual void __stdcall GetBitmap(/* out */ _di_ID2D1Bitmap &bitmap) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A9-12E2-11DC-9FED-001143A055F9}") ID2D1SolidColorBrush  : public ID2D1Brush 
{
	virtual void __stdcall SetColor(const D3DCOLORVALUE &color) = 0 ;
	virtual void __stdcall GetColor(D3DCOLORVALUE &color) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906AB-12E2-11DC-9FED-001143A055F9}") ID2D1LinearGradientBrush  : public ID2D1Brush 
{
	virtual void __stdcall SetStartPoint(D2D_POINT_2F startPoint) = 0 ;
	virtual void __stdcall SetEndPoint(D2D_POINT_2F endPoint) = 0 ;
	virtual void __stdcall GetStartPoint(/* out */ D2D_POINT_2F &startPoint) = 0 ;
	virtual void __stdcall GetEndPoint(/* out */ D2D_POINT_2F &endPoint) = 0 ;
	virtual void __stdcall GetGradientStopCollection(/* out */ _di_ID2D1GradientStopCollection &gradientStopCollection) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906AC-12E2-11DC-9FED-001143A055F9}") ID2D1RadialGradientBrush  : public ID2D1Brush 
{
	virtual void __stdcall SetCenter(D2D_POINT_2F center) = 0 ;
	virtual void __stdcall SetGradientOriginOffset(D2D_POINT_2F gradientOriginOffset) = 0 ;
	virtual void __stdcall SetRadiusX(float radiusX) = 0 ;
	virtual void __stdcall SetRadiusY(float radiusY) = 0 ;
	virtual void __stdcall GetCenter(/* out */ D2D_POINT_2F &center) = 0 ;
	virtual void __stdcall GetGradientOriginOffset(/* out */ D2D_POINT_2F &gradientOriginOffset) = 0 ;
	virtual float __stdcall GetRadiusX() = 0 ;
	virtual float __stdcall GetRadiusY() = 0 ;
	virtual void __stdcall GetGradientStopCollection(/* out */ _di_ID2D1GradientStopCollection &gradientStopCollection) = 0 ;
};

__interface  INTERFACE_UUID("{2CD9069D-12E2-11DC-9FED-001143A055F9}") ID2D1StrokeStyle  : public ID2D1Resource 
{
	virtual D2D1_CAP_STYLE __stdcall GetStartCap() = 0 ;
	virtual D2D1_CAP_STYLE __stdcall GetEndCap() = 0 ;
	virtual D2D1_CAP_STYLE __stdcall GetDashCap() = 0 ;
	virtual float __stdcall GetMiterLimit() = 0 ;
	virtual D2D1_LINE_JOIN __stdcall GetLineJoin() = 0 ;
	virtual float __stdcall GetDashOffset() = 0 ;
	virtual D2D1_DASH_STYLE __stdcall GetDashStyle() = 0 ;
	virtual unsigned __stdcall GetDashesCount() = 0 ;
	virtual void __stdcall GetDashes(Winapi::Windows::PSingle dashes, unsigned dashesCount) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A1-12E2-11DC-9FED-001143A055F9}") ID2D1Geometry  : public ID2D1Resource 
{
	virtual HRESULT __stdcall GetBounds(const D2D_MATRIX_3X2_F &worldTransform, /* out */ D2D_RECT_F &bounds) = 0 ;
	virtual HRESULT __stdcall GetWidenedBounds(float strokeWidth, const _di_ID2D1StrokeStyle strokeStyle, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, /* out */ D2D_RECT_F &bounds) = 0 ;
	virtual HRESULT __stdcall StrokeContainsPoint(D2D_POINT_2F point, float strokeWidth, _di_ID2D1StrokeStyle strokeStyle, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, /* out */ System::LongBool &contains) = 0 ;
	virtual HRESULT __stdcall FillContainsPoint(D2D_POINT_2F point, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, /* out */ System::LongBool &contains) = 0 ;
	virtual HRESULT __stdcall CompareWithGeometry(const _di_ID2D1Geometry inputGeometry, const D2D_MATRIX_3X2_F &inputGeometryTransform, float flatteningTolerance, /* out */ D2D1_GEOMETRY_RELATION &relation) = 0 ;
	virtual HRESULT __stdcall Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, const _di_ID2D1SimplifiedGeometrySink geometrySink) = 0 ;
	virtual HRESULT __stdcall Tessellate(const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, const _di_ID2D1TessellationSink tessellationSink) = 0 ;
	virtual HRESULT __stdcall CombineWithGeometry(const _di_ID2D1Geometry inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D_MATRIX_3X2_F &inputGeometryTransform, float flatteningTolerance, const _di_ID2D1SimplifiedGeometrySink geometrySink) = 0 ;
	virtual HRESULT __stdcall Outline(const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, const _di_ID2D1SimplifiedGeometrySink geometrySink) = 0 ;
	virtual HRESULT __stdcall ComputeArea(const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, /* out */ float &area) = 0 ;
	virtual HRESULT __stdcall ComputeLength(const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, /* out */ float &length) = 0 ;
	virtual HRESULT __stdcall ComputePointAtLength(float length, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, PD2D1Point2F point, PD2D1Point2F unitTangentVector) = 0 ;
	virtual HRESULT __stdcall Widen(float strokeWidth, const _di_ID2D1StrokeStyle strokeStyle, const D2D_MATRIX_3X2_F &worldTransform, float flatteningTolerance, const _di_ID2D1SimplifiedGeometrySink geometrySink) = 0 ;
};

typedef _di_ID2D1Geometry *PID2D1Geometry;

__interface  INTERFACE_UUID("{2CD906A2-12E2-11DC-9FED-001143A055F9}") ID2D1RectangleGeometry  : public ID2D1Geometry 
{
	virtual void __stdcall GetRect(D2D_RECT_F &rect) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A3-12E2-11DC-9FED-001143A055F9}") ID2D1RoundedRectangleGeometry  : public ID2D1Geometry 
{
	virtual void __stdcall GetRoundedRect(D2D1_ROUNDED_RECT &roundedRect) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A4-12E2-11DC-9FED-001143A055F9}") ID2D1EllipseGeometry  : public ID2D1Geometry 
{
	virtual void __stdcall GetEllipse(D2D1_ELLIPSE &ellipse) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A6-12E2-11DC-9FED-001143A055F9}") ID2D1GeometryGroup  : public ID2D1Geometry 
{
	virtual D2D1_FILL_MODE __stdcall GetFillMode() = 0 ;
	virtual unsigned __stdcall GetSourceGeometryCount() = 0 ;
	virtual void __stdcall GetSourceGeometries(PID2D1Geometry geometries, unsigned geometriesCount) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906BB-12E2-11DC-9FED-001143A055F9}") ID2D1TransformedGeometry  : public ID2D1Geometry 
{
	virtual void __stdcall GetSourceGeometry(/* out */ _di_ID2D1Geometry &sourceGeometry) = 0 ;
	virtual void __stdcall GetTransform(/* out */ D2D_MATRIX_3X2_F &transform) = 0 ;
};

__interface  INTERFACE_UUID("{2CD9069E-12E2-11DC-9FED-001143A055F9}") ID2D1SimplifiedGeometrySink  : public System::IInterface 
{
	virtual void __stdcall SetFillMode(D2D1_FILL_MODE fillMode) = 0 ;
	virtual void __stdcall SetSegmentFlags(D2D1_PATH_SEGMENT vertexFlags) = 0 ;
	virtual void __stdcall BeginFigure(D2D_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin) = 0 ;
	virtual void __stdcall AddLines(PD2D1Point2F points, unsigned pointsCount) = 0 ;
	virtual void __stdcall AddBeziers(PD2D1BezierSegment beziers, unsigned beziersCount) = 0 ;
	virtual void __stdcall EndFigure(D2D1_FIGURE_END figureEnd) = 0 ;
	virtual HRESULT __stdcall Close() = 0 ;
};

__interface  INTERFACE_UUID("{2CD9069F-12E2-11DC-9FED-001143A055F9}") ID2D1GeometrySink  : public ID2D1SimplifiedGeometrySink 
{
	virtual void __stdcall AddLine(D2D_POINT_2F point) = 0 ;
	virtual void __stdcall AddBezier(const D2D1_BEZIER_SEGMENT &bezier) = 0 ;
	virtual void __stdcall AddQuadraticBezier(const D2D1_QUADRATIC_BEZIER_SEGMENT &bezier) = 0 ;
	virtual void __stdcall AddQuadraticBeziers(PD2D1QuadraticBezierSegment beziers, unsigned beziersCount) = 0 ;
	virtual void __stdcall AddArc(const D2D1_ARC_SEGMENT &arc) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906C1-12E2-11DC-9FED-001143A055F9}") ID2D1TessellationSink  : public System::IInterface 
{
	virtual void __stdcall AddTriangles(PD2D1Triangle triangles, unsigned trianglesCount) = 0 ;
	virtual HRESULT __stdcall Close() = 0 ;
};

__interface  INTERFACE_UUID("{2CD906A5-12E2-11DC-9FED-001143A055F9}") ID2D1PathGeometry  : public ID2D1Geometry 
{
	virtual HRESULT __stdcall Open(/* out */ _di_ID2D1GeometrySink &geometrySink) = 0 ;
	virtual HRESULT __stdcall Stream(const _di_ID2D1GeometrySink geometrySink) = 0 ;
	virtual HRESULT __stdcall GetSegmentCount(unsigned &count) = 0 ;
	virtual HRESULT __stdcall GetFigureCount(unsigned &count) = 0 ;
};

__interface  INTERFACE_UUID("{2CD906C2-12E2-11DC-9FED-001143A055F9}") ID2D1Mesh  : public ID2D1Resource 
{
	virtual HRESULT __stdcall Open(/* out */ _di_ID2D1TessellationSink &tessellationSink) = 0 ;
};

__interface  INTERFACE_UUID("{2CD9069B-12E2-11DC-9FED-001143A055F9}") ID2D1Layer  : public ID2D1Resource 
{
	virtual void __stdcall GetSize(/* out */ D2D_SIZE_F &size) = 0 ;
};

__interface  INTERFACE_UUID("{28506E39-EBF6-46A1-BB47-FD85565AB957}") ID2D1DrawingStateBlock  : public ID2D1Resource 
{
	virtual void __stdcall GetDescription(D2D1_DRAWING_STATE_DESCRIPTION &stateDescription) = 0 ;
	virtual void __stdcall SetDescription(D2D1_DRAWING_STATE_DESCRIPTION &stateDescription) = 0 ;
	virtual void __stdcall SetTextRenderingParams(const _di_IDWriteRenderingParams textRenderingParams) = 0 ;
	virtual void __stdcall GetTextRenderingParams(/* out */ _di_IDWriteRenderingParams &textRenderingParams) = 0 ;
};

__interface  INTERFACE_UUID("{2CD90694-12E2-11DC-9FED-001143A055F9}") ID2D1RenderTarget  : public ID2D1Resource 
{
	virtual HRESULT __stdcall CreateBitmap(D2D_SIZE_U size, void * srcData, unsigned pitch, const D2D1_BITMAP_PROPERTIES &bitmapProperties, /* out */ _di_ID2D1Bitmap &bitmap) = 0 ;
	virtual HRESULT __stdcall CreateBitmapFromWicBitmap(const _di_IWICBitmapSource wicBitmapSource, PD2D1BitmapProperties bitmapProperties, /* out */ _di_ID2D1Bitmap &bitmap) = 0 ;
	virtual HRESULT __stdcall CreateSharedBitmap(const GUID &riid, void * data, PD2D1BitmapProperties bitmapProperties, /* out */ _di_ID2D1Bitmap &bitmap) = 0 ;
	virtual HRESULT __stdcall CreateBitmapBrush(const _di_ID2D1Bitmap bitmap, PD2D1BitmapBrushProperties bitmapBrushProperties, PD2D1BrushProperties brushProperties, /* out */ _di_ID2D1BitmapBrush &bitmapBrush) = 0 ;
	virtual HRESULT __stdcall CreateSolidColorBrush(const D3DCOLORVALUE &color, PD2D1BrushProperties brushProperties, /* out */ _di_ID2D1SolidColorBrush &solidColorBrush) = 0 ;
	virtual HRESULT __stdcall CreateGradientStopCollection(const PD2D1GradientStop gradientStops, unsigned gradientStopsCount, D2D1_GAMMA colorInterpolationGamma, D2D1_EXTEND_MODE extendMode, /* out */ _di_ID2D1GradientStopCollection &gradientStopCollection) = 0 ;
	virtual HRESULT __stdcall CreateLinearGradientBrush(const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties, PD2D1BrushProperties brushProperties, _di_ID2D1GradientStopCollection gradientStopCollection, /* out */ _di_ID2D1LinearGradientBrush &linearGradientBrush) = 0 ;
	virtual HRESULT __stdcall CreateRadialGradientBrush(const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties, PD2D1BrushProperties brushProperties, _di_ID2D1GradientStopCollection gradientStopCollection, /* out */ _di_ID2D1RadialGradientBrush &radialGradientBrush) = 0 ;
	virtual HRESULT __stdcall CreateCompatibleRenderTarget(PD2D1SizeF desiredSize, PD2D1SizeU desiredPixelSize, PD2D1PixelFormat desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options, /* out */ _di_ID2D1BitmapRenderTarget &bitmapRenderTarget) = 0 ;
	virtual HRESULT __stdcall CreateLayer(PD2D1SizeF size, /* out */ _di_ID2D1Layer &layer) = 0 ;
	virtual HRESULT __stdcall CreateMesh(/* out */ _di_ID2D1Mesh &mesh) = 0 ;
	virtual void __stdcall DrawLine(D2D_POINT_2F point0, D2D_POINT_2F point1, const _di_ID2D1Brush brush, float strokeWidth = 1.000000E+00f, const _di_ID2D1StrokeStyle strokeStyle = _di_ID2D1StrokeStyle()) = 0 ;
	virtual void __stdcall DrawRectangle(const D2D_RECT_F &rect, const _di_ID2D1Brush brush, float strokeWidth = 1.000000E+00f, const _di_ID2D1StrokeStyle strokeStyle = _di_ID2D1StrokeStyle()) = 0 ;
	virtual void __stdcall FillRectangle(const D2D_RECT_F &rect, const _di_ID2D1Brush brush) = 0 ;
	virtual void __stdcall DrawRoundedRectangle(const D2D1_ROUNDED_RECT &roundedRect, const _di_ID2D1Brush brush, float strokeWidth = 1.000000E+00f, const _di_ID2D1StrokeStyle strokeStyle = _di_ID2D1StrokeStyle()) = 0 ;
	virtual void __stdcall FillRoundedRectangle(const D2D1_ROUNDED_RECT &roundedRect, const _di_ID2D1Brush brush) = 0 ;
	virtual void __stdcall DrawEllipse(const D2D1_ELLIPSE &ellipse, const _di_ID2D1Brush brush, float strokeWidth = 1.000000E+00f, const _di_ID2D1StrokeStyle strokeStyle = _di_ID2D1StrokeStyle()) = 0 ;
	virtual void __stdcall FillEllipse(const D2D1_ELLIPSE &ellipse, const _di_ID2D1Brush brush) = 0 ;
	virtual void __stdcall DrawGeometry(_di_ID2D1Geometry geometry, const _di_ID2D1Brush brush, float strokeWidth = 1.000000E+00f, const _di_ID2D1StrokeStyle strokeStyle = _di_ID2D1StrokeStyle()) = 0 ;
	virtual void __stdcall FillGeometry(const _di_ID2D1Geometry geometry, const _di_ID2D1Brush brush, const _di_ID2D1Brush opacityBrush = _di_ID2D1Brush()) = 0 ;
	virtual void __stdcall FillMesh(const _di_ID2D1Mesh mesh, const _di_ID2D1Brush brush) = 0 ;
	virtual void __stdcall FillOpacityMask(_di_ID2D1Bitmap opacityMask, _di_ID2D1Brush brush, D2D1_OPACITY_MASK_CONTENT content, PD2D1RectF destinationRectangle = (PD2D1RectF)(0x0), PD2D1RectF sourceRectangle = (PD2D1RectF)(0x0)) = 0 ;
	virtual void __stdcall DrawBitmap(const _di_ID2D1Bitmap bitmap, PD2D1RectF destinationRectangle = (PD2D1RectF)(0x0), float opacity = 1.000000E+00f, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = (D2D1_BITMAP_INTERPOLATION_MODE)(0x1), PD2D1RectF sourceRectangle = (PD2D1RectF)(0x0)) = 0 ;
	virtual void __stdcall DrawText(System::WideChar * string, unsigned stringLength, const _di_IDWriteTextFormat textFormat, const D2D_RECT_F &layoutRect, const _di_ID2D1Brush defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = (D2D1_DRAW_TEXT_OPTIONS)(0x0), DWRITE_MEASURING_MODE measuringMode = (DWRITE_MEASURING_MODE)(0x0)) = 0 ;
	virtual void __stdcall DrawTextLayout(D2D_POINT_2F origin, const _di_IDWriteTextLayout textLayout, const _di_ID2D1Brush defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = (D2D1_DRAW_TEXT_OPTIONS)(0x0)) = 0 ;
	virtual void __stdcall DrawGlyphRun(D2D_POINT_2F baselineOrigin, DWRITE_GLYPH_RUN &glyphRun, const _di_ID2D1Brush foregroundBrush, DWRITE_MEASURING_MODE measuringMode = (DWRITE_MEASURING_MODE)(0x0)) = 0 ;
	virtual void __stdcall SetTransform(const D2D_MATRIX_3X2_F &transform) = 0 ;
	virtual void __stdcall GetTransform(D2D_MATRIX_3X2_F &transform) = 0 ;
	virtual void __stdcall SetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode) = 0 ;
	virtual D2D1_ANTIALIAS_MODE __stdcall GetAntialiasMode() = 0 ;
	virtual void __stdcall SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode) = 0 ;
	virtual D2D1_TEXT_ANTIALIAS_MODE __stdcall GetTextAntialiasMode() = 0 ;
	virtual void __stdcall SetTextRenderingParams(const _di_IDWriteRenderingParams textRenderingParams) = 0 ;
	virtual void __stdcall GetTextRenderingParams(/* out */ _di_IDWriteRenderingParams &textRenderingParams) = 0 ;
	virtual void __stdcall SetTags(unsigned __int64 tag1, unsigned __int64 tag2) = 0 ;
	virtual void __stdcall GetTags(PD2D1Tag tag1 = (PD2D1Tag)(0x0), PD2D1Tag tag2 = (PD2D1Tag)(0x0)) = 0 ;
	virtual void __stdcall PushLayer(D2D1_LAYER_PARAMETERS &layerParameters, const _di_ID2D1Layer layer) = 0 ;
	virtual void __stdcall PopLayer() = 0 ;
	virtual HRESULT __stdcall Flush(PD2D1Tag tag1 = (PD2D1Tag)(0x0), PD2D1Tag tag2 = (PD2D1Tag)(0x0)) = 0 ;
	virtual void __stdcall SaveDrawingState(_di_ID2D1DrawingStateBlock &drawingStateBlock) = 0 ;
	virtual void __stdcall RestoreDrawingState(const _di_ID2D1DrawingStateBlock drawingStateBlock) = 0 ;
	virtual void __stdcall PushAxisAlignedClip(const D2D_RECT_F &clipRect, D2D1_ANTIALIAS_MODE antialiasMode) = 0 ;
	virtual void __stdcall PopAxisAlignedClip() = 0 ;
	virtual void __stdcall Clear(const D3DCOLORVALUE &clearColor) = 0 ;
	virtual void __stdcall BeginDraw() = 0 ;
	virtual HRESULT __stdcall EndDraw(PD2D1Tag tag1 = (PD2D1Tag)(0x0), PD2D1Tag tag2 = (PD2D1Tag)(0x0)) = 0 ;
	virtual void __stdcall GetPixelFormat(/* out */ D2D1_PIXEL_FORMAT &pixelFormat) = 0 ;
	virtual void __stdcall SetDpi(float dpiX, float dpiY) = 0 ;
	virtual void __stdcall GetDpi(/* out */ float &dpiX, /* out */ float &dpiY) = 0 ;
	virtual void __stdcall GetSize(/* out */ D2D_SIZE_F &size) = 0 ;
	virtual void __stdcall GetPixelSize(/* out */ D2D_SIZE_U &pixelSize) = 0 ;
	virtual unsigned __stdcall GetMaximumBitmapSize() = 0 ;
	virtual System::LongBool __stdcall IsSupported(const D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties) = 0 ;
};

__interface  INTERFACE_UUID("{2CD90695-12E2-11DC-9FED-001143A055F9}") ID2D1BitmapRenderTarget  : public ID2D1RenderTarget 
{
	virtual HRESULT __stdcall GetBitmap(/* out */ _di_ID2D1Bitmap &bitmap) = 0 ;
};

__interface  INTERFACE_UUID("{2CD90698-12E2-11DC-9FED-001143A055F9}") ID2D1HwndRenderTarget  : public ID2D1RenderTarget 
{
	virtual D2D1_WINDOW_STATE __stdcall CheckWindowState() = 0 ;
	virtual HRESULT __stdcall Resize(D2D_SIZE_U &pixelSize) = 0 ;
	virtual HWND __stdcall GetHwnd() = 0 ;
};

__interface  INTERFACE_UUID("{E0DB51C3-6F77-4BAE-B3D5-E47509B35838}") ID2D1GdiInteropRenderTarget  : public System::IInterface 
{
	virtual HRESULT __stdcall GetDC(D2D1_DC_INITIALIZE_MODE mode, /* out */ HDC &hdc) = 0 ;
	virtual HRESULT __stdcall ReleaseDC(const System::Types::TRect &update) = 0 ;
};

__interface  INTERFACE_UUID("{1C51BC64-DE61-46FD-9899-63A5D8F03950}") ID2D1DCRenderTarget  : public ID2D1RenderTarget 
{
	virtual HRESULT __stdcall BindDC(HDC hDC, const System::Types::TRect &pSubRect) = 0 ;
};

__interface  INTERFACE_UUID("{06152247-6F50-465A-9245-118BFD3B6007}") ID2D1Factory  : public System::IInterface 
{
	virtual HRESULT __stdcall ReloadSystemMetrics() = 0 ;
	virtual void __stdcall GetDesktopDpi(float &dpiX, float &dpiY) = 0 ;
	virtual HRESULT __stdcall CreateRectangleGeometry(const D2D_RECT_F &rectangle, /* out */ _di_ID2D1RectangleGeometry &rectangleGeometry) = 0 ;
	virtual HRESULT __stdcall CreateRoundedRectangleGeometry(const D2D1_ROUNDED_RECT &roundedRectangle, /* out */ _di_ID2D1RoundedRectangleGeometry &roundedRectangleGeometry) = 0 ;
	virtual HRESULT __stdcall CreateEllipseGeometry(const D2D1_ELLIPSE &ellipse, /* out */ _di_ID2D1EllipseGeometry &ellipseGeometry) = 0 ;
	virtual HRESULT __stdcall CreateGeometryGroup(D2D1_FILL_MODE fillMode, PID2D1Geometry geometries, unsigned geometriesCount, /* out */ _di_ID2D1GeometryGroup &geometryGroup) = 0 ;
	virtual HRESULT __stdcall CreateTransformedGeometry(const _di_ID2D1Geometry sourceGeometry, const D2D_MATRIX_3X2_F &transform, /* out */ _di_ID2D1TransformedGeometry &transformedGeometry) = 0 ;
	virtual HRESULT __stdcall CreatePathGeometry(/* out */ _di_ID2D1PathGeometry &pathGeometry) = 0 ;
	virtual HRESULT __stdcall CreateStrokeStyle(const D2D1_STROKE_STYLE_PROPERTIES &strokeStyleProperties, const Winapi::Windows::PSingle dashes, unsigned dashesCount, /* out */ _di_ID2D1StrokeStyle &strokeStyle) = 0 ;
	virtual HRESULT __stdcall CreateDrawingStateBlock(PD2D1DrawingStateDescription drawingStateDescription, const _di_IDWriteRenderingParams textRenderingParams, /* out */ _di_ID2D1DrawingStateBlock &drawingStateBlock) = 0 ;
	virtual HRESULT __stdcall CreateWicBitmapRenderTarget(const _di_IWICBitmap target, D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties, /* out */ _di_ID2D1RenderTarget &renderTarget) = 0 ;
	virtual HRESULT __stdcall CreateHwndRenderTarget(const D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES &hwndRenderTargetProperties, /* out */ _di_ID2D1HwndRenderTarget &hwndRenderTarget) = 0 ;
	virtual HRESULT __stdcall CreateDxgiSurfaceRenderTarget(const _di_IDXGISurface dxgiSurface, D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties, /* out */ _di_ID2D1RenderTarget &renderTarget) = 0 ;
	virtual HRESULT __stdcall CreateDCRenderTarget(const D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties, /* out */ _di_ID2D1DCRenderTarget &dcRenderTarget) = 0 ;
};

__interface  INTERFACE_UUID("{727CAD4E-D6AF-4C9E-8A08-D695B11CAA49}") IDWriteFontFileLoader  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateStreamFromKey(void * fontFileReferenceKey, unsigned fontFileReferenceKeySize, /* out */ _di_IDWriteFontFileStream &fontFileStream) = 0 ;
};

__interface  INTERFACE_UUID("{B2D9F3EC-C9FE-4A11-A2EC-D86208F7C0A2}") IDWriteLocalFontFileLoader  : public IDWriteFontFileLoader 
{
	virtual HRESULT __stdcall GetFilePathLengthFromKey(void * fontFileReferenceKey, unsigned fontFileReferenceKeySize, unsigned &filePathLength) = 0 ;
	virtual HRESULT __stdcall GetFilePathFromKey(void * fontFileReferenceKey, unsigned fontFileReferenceKeySize, System::WideChar &filePath, unsigned filePathSize) = 0 ;
	virtual HRESULT __stdcall GetLastWriteTimeFromKey(void * fontFileReferenceKey, unsigned fontFileReferenceKeySize, _FILETIME &lastWriteTime) = 0 ;
};

__interface  INTERFACE_UUID("{6D4865FE-0AB8-4D91-8F62-5DD6BE34A3E0}") IDWriteFontFileStream  : public System::IInterface 
{
	virtual HRESULT __stdcall ReadFileFragment(void * &fragmentStart, unsigned __int64 fileOffset, unsigned __int64 fragmentSize, void * &fragmentContext) = 0 ;
	virtual void __stdcall ReleaseFileFragment(void * fragmentContext) = 0 ;
	virtual HRESULT __stdcall GetFileSize(unsigned __int64 &fileSize) = 0 ;
	virtual HRESULT __stdcall GetLastWriteTime(unsigned __int64 &lastWriteTime) = 0 ;
};

__interface  INTERFACE_UUID("{739D886A-CEF5-47DC-8769-1A8B41BEBBB0}") IDWriteFontFile  : public System::IInterface 
{
	virtual HRESULT __stdcall GetReferenceKey(void * &fontFileReferenceKey, unsigned &fontFileReferenceKeySize) = 0 ;
	virtual HRESULT __stdcall GetLoader(/* out */ _di_IDWriteFontFileLoader &fontFileLoader) = 0 ;
	virtual HRESULT __stdcall Analyze(System::LongBool &isSupportedFontType, DWRITE_FONT_FILE_TYPE &fontFileType, DWRITE_FONT_FACE_TYPE &fontFaceType, unsigned &numberOfFaces) = 0 ;
};

typedef _di_IDWriteFontFile *PIDWriteFontFile;

__interface  INTERFACE_UUID("{2F0DA53A-2ADD-47CD-82EE-D9EC34688E75}") IDWriteRenderingParams  : public System::IInterface 
{
	virtual float __stdcall GetGamma() = 0 ;
	virtual float __stdcall GetEnhancedContrast() = 0 ;
	virtual float __stdcall GetClearTypeLevel() = 0 ;
	virtual DWRITE_PIXEL_GEOMETRY __stdcall GetPixelGeometry() = 0 ;
	virtual DWRITE_RENDERING_MODE __stdcall GetRenderingMode() = 0 ;
};

typedef _di_ID2D1SimplifiedGeometrySink IDWriteGeometrySink;

__interface  INTERFACE_UUID("{5F49804D-7024-4D43-BFA9-D25984F53849}") IDWriteFontFace  : public System::IInterface 
{
	virtual DWRITE_FONT_FACE_TYPE __stdcall GetType() = 0 ;
	virtual HRESULT __stdcall GetFiles(unsigned &numberOfFiles, /* out */ _di_IDWriteFontFile &fontFiles) = 0 ;
	virtual unsigned __stdcall GetIndex() = 0 ;
	virtual DWRITE_FONT_SIMULATIONS __stdcall GetSimulations() = 0 ;
	virtual System::LongBool __stdcall IsSymbolFont() = 0 ;
	virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS &fontFaceMetrics) = 0 ;
	virtual System::Word __stdcall GetGlyphCount() = 0 ;
	virtual HRESULT __stdcall GetDesignGlyphMetrics(PWORD glyphIndices, unsigned glyphCount, PDwriteGlyphMetrics glyphMetrics, System::LongBool isSideways = false) = 0 ;
	virtual HRESULT __stdcall GetGlyphIndices(unsigned &codePoints, unsigned codePointCount, System::Word &glyphIndices) = 0 ;
	virtual HRESULT __stdcall TryGetFontTable(unsigned openTypeTableTag, void * &tableData, unsigned &tableSize, void * &tableContext, System::LongBool &exists) = 0 ;
	virtual void __stdcall ReleaseFontTable(void * tableContext) = 0 ;
	virtual HRESULT __stdcall GetGlyphRunOutline(float emSize, const PWORD glyphIndices, const Winapi::Windows::PSingle glyphAdvances, const PDwriteGlyphOffset glyphOffsets, unsigned glyphCount, System::LongBool isSideways, System::LongBool isRightToLeft, _di_ID2D1SimplifiedGeometrySink geometrySink) = 0 ;
	virtual HRESULT __stdcall GetRecommendedRenderingMode(float emSize, float pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, _di_IDWriteRenderingParams &renderingParams, DWRITE_RENDERING_MODE &renderingMode) = 0 ;
	virtual HRESULT __stdcall GetGdiCompatibleMetrics(float emSize, float pixelsPerDip, const DWRITE_MATRIX &transform, DWRITE_FONT_METRICS &fontFaceMetrics) = 0 ;
	virtual HRESULT __stdcall GetGDICompatibleGlyphMetrics(float emSize, float pixelsPerDip, const DWRITE_MATRIX &transform, System::LongBool useGdiNatural, PWORD glyphIndicies, unsigned glpyhCount) = 0 ;
};

__interface  INTERFACE_UUID("{CCA920E4-52F0-492B-BFA8-29C72EE0A468}") IDWriteFontCollectionLoader  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateEnumeratorFromKey(const _di_IDWriteFactory factory, void * collectionKey, unsigned collectionKeySize, /* out */ _di_IDWriteFontFileEnumerator &fontFileEnumerator) = 0 ;
};

__interface  INTERFACE_UUID("{72755049-5FF7-435D-8348-4BE97CFA6C7C}") IDWriteFontFileEnumerator  : public System::IInterface 
{
	virtual HRESULT __stdcall MoveNext(System::LongBool &hasCurrentFile) = 0 ;
	virtual HRESULT __stdcall GetCurrentFontFile(/* out */ _di_IDWriteFontFile &fontFile) = 0 ;
};

__interface  INTERFACE_UUID("{08256209-099A-4B34-B86D-C22B110E7771}") IDWriteLocalizedStrings  : public System::IInterface 
{
	virtual unsigned __stdcall GetCount() = 0 ;
	virtual HRESULT __stdcall FindLocaleName(System::WideChar * localeName, unsigned &index, System::LongBool &exists) = 0 ;
	virtual HRESULT __stdcall GetLocaleNameLength(unsigned index, unsigned &length) = 0 ;
	virtual HRESULT __stdcall GetLocaleName(unsigned index, System::WideChar &localeName, unsigned size) = 0 ;
	virtual HRESULT __stdcall GetStringLength(unsigned index, unsigned &length) = 0 ;
	virtual HRESULT __stdcall GetString(unsigned index, System::WideChar * stringBuffer, unsigned size) = 0 ;
};

__interface  INTERFACE_UUID("{A84CEE02-3EEA-4EEE-A827-87C1A02A0FCC}") IDWriteFontCollection  : public System::IInterface 
{
	virtual unsigned __stdcall GetFontFamilyCount() = 0 ;
	virtual HRESULT __stdcall GetFontFamily(unsigned index, /* out */ _di_IDWriteFontFamily &fontFamily) = 0 ;
	virtual HRESULT __stdcall FindFamilyName(System::WideChar * familyName, unsigned &index, System::LongBool &exists) = 0 ;
	virtual HRESULT __stdcall GetFontFromFontFace(_di_IDWriteFontFace &fontFace, /* out */ _di_IDWriteFont &font) = 0 ;
};

__interface  INTERFACE_UUID("{1A0D8438-1D97-4EC1-AEF9-A2FB86ED6ACB}") IDWriteFontList  : public System::IInterface 
{
	virtual HRESULT __stdcall GetFontCollection(/* out */ _di_IDWriteFontCollection &fontCollection) = 0 ;
	virtual unsigned __stdcall GetFontCount() = 0 ;
	virtual HRESULT __stdcall GetFont(unsigned index, /* out */ _di_IDWriteFont &font) = 0 ;
};

__interface  INTERFACE_UUID("{DA20D8EF-812A-4C43-9802-62EC4ABD7ADD}") IDWriteFontFamily  : public IDWriteFontList 
{
	virtual HRESULT __stdcall GetFamilyNames(/* out */ _di_IDWriteLocalizedStrings &names) = 0 ;
	virtual HRESULT __stdcall GetFirstMatchingFont(DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, /* out */ _di_IDWriteFont &matchingFont) = 0 ;
	virtual HRESULT __stdcall GetMatchingFonts(DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, /* out */ _di_IDWriteFontList &matchingFonts) = 0 ;
};

__interface  INTERFACE_UUID("{ACD16696-8C14-4F5D-877E-FE3FC1D32737}") IDWriteFont  : public System::IInterface 
{
	virtual HRESULT __stdcall GetFontFamily(/* out */ _di_IDWriteFontFamily &fontFamily) = 0 ;
	virtual DWRITE_FONT_WEIGHT __stdcall GetWeight() = 0 ;
	virtual DWRITE_FONT_STRETCH __stdcall GetStretch() = 0 ;
	virtual DWRITE_FONT_STYLE __stdcall GetStyle() = 0 ;
	virtual System::LongBool __stdcall IsSymbolFont() = 0 ;
	virtual HRESULT __stdcall GetFaceNames(/* out */ _di_IDWriteLocalizedStrings &names) = 0 ;
	virtual HRESULT __stdcall GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_ID informationalStringID, /* out */ _di_IDWriteLocalizedStrings &informationalStrings, System::LongBool &exists) = 0 ;
	virtual DWRITE_FONT_SIMULATIONS __stdcall GetSimulations() = 0 ;
	virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS &fontMetrics) = 0 ;
	virtual HRESULT __stdcall HasCharacter(unsigned unicodeValue, System::LongBool &exists) = 0 ;
	virtual HRESULT __stdcall CreateFontFace(/* out */ _di_IDWriteFontFace &fontFace) = 0 ;
};

__interface  INTERFACE_UUID("{9C906818-31D7-4FD3-A151-7C5E225DB55A}") IDWriteTextFormat  : public System::IInterface 
{
	virtual HRESULT __stdcall SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment) = 0 ;
	virtual HRESULT __stdcall SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment) = 0 ;
	virtual HRESULT __stdcall SetWordWrapping(DWRITE_WORD_WRAPPING wordWrapping) = 0 ;
	virtual HRESULT __stdcall SetReadingDirection(DWRITE_READING_DIRECTION readingDirection) = 0 ;
	virtual HRESULT __stdcall SetFlowDirection(DWRITE_FLOW_DIRECTION flowDirection) = 0 ;
	virtual HRESULT __stdcall SetIncrementalTabStop(float incrementalTabStop) = 0 ;
	virtual HRESULT __stdcall SetTrimming(DWRITE_TRIMMING &trimmingOptions, _di_IDWriteInlineObject trimmingSign) = 0 ;
	virtual HRESULT __stdcall SetLineSpacing(DWRITE_LINE_SPACING_METHOD lineSpacingMethod, float lineSpacing, float baseline) = 0 ;
	virtual DWRITE_TEXT_ALIGNMENT __stdcall GetTextAlignment() = 0 ;
	virtual DWRITE_PARAGRAPH_ALIGNMENT __stdcall GetParagraphAlignment() = 0 ;
	virtual DWRITE_WORD_WRAPPING __stdcall GetWordWrapping() = 0 ;
	virtual DWRITE_READING_DIRECTION __stdcall GetReadingDirection() = 0 ;
	virtual DWRITE_FLOW_DIRECTION __stdcall GetFlowDirection() = 0 ;
	virtual float __stdcall GetIncrementalTabStop() = 0 ;
	virtual HRESULT __stdcall GetTrimming(DWRITE_TRIMMING &trimmingOptions, /* out */ _di_IDWriteInlineObject &trimmingSign) = 0 ;
	virtual HRESULT __stdcall GetLineSpacing(DWRITE_LINE_SPACING_METHOD &lineSpacingMethod, float &lineSpacing, float &baseline) = 0 ;
	virtual HRESULT __stdcall GetFontCollection(/* out */ _di_IDWriteFontCollection &fontCollection) = 0 ;
	virtual unsigned __stdcall GetFontFamilyNameLength() = 0 ;
	virtual HRESULT __stdcall GetFontFamilyName(System::WideChar &fontFamilyName, unsigned nameSize) = 0 ;
	virtual DWRITE_FONT_WEIGHT __stdcall GetFontWeight() = 0 ;
	virtual DWRITE_FONT_STYLE __stdcall GetFontStyle() = 0 ;
	virtual DWRITE_FONT_STRETCH __stdcall GetFontStretch() = 0 ;
	virtual float __stdcall GetFontSize() = 0 ;
	virtual unsigned __stdcall GetLocaleNameLength() = 0 ;
	virtual HRESULT __stdcall GetLocaleName(System::WideChar &localeName, unsigned nameSize) = 0 ;
};

__interface  INTERFACE_UUID("{55F1112B-1DC2-4B3C-9541-F46894ED85B6}") IDWriteTypography  : public System::IInterface 
{
	virtual HRESULT __stdcall AddFontFeature(DWRITE_FONT_FEATURE fontFeature) = 0 ;
	virtual unsigned __stdcall GetFontFeatureCount() = 0 ;
	virtual HRESULT __stdcall GetFontFeature(unsigned fontFeatureIndex, DWRITE_FONT_FEATURE &fontFeature) = 0 ;
};

__interface  INTERFACE_UUID("{14885CC9-BAB0-4F90-B6ED-5C366A2CD03D}") IDWriteNumberSubstitution  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{688E1A58-5094-47C8-ADC8-FBCEA60AE92B}") IDWriteTextAnalysisSource  : public System::IInterface 
{
	virtual HRESULT __stdcall GetTextAtPosition(unsigned textPosition, System::WideChar * &textString, unsigned &textLength) = 0 ;
	virtual HRESULT __stdcall GetTextBeforePosition(unsigned textPosition, System::WideChar * &textString, unsigned &textLength) = 0 ;
	virtual DWRITE_READING_DIRECTION __stdcall GetParagraphReadingDirection() = 0 ;
	virtual HRESULT __stdcall GetLocaleName(unsigned textPosition, unsigned &textLength, System::WideChar * &localeName) = 0 ;
	virtual HRESULT __stdcall GetNumberSubstitution(unsigned textPosition, unsigned &textLength, /* out */ _di_IDWriteNumberSubstitution &numberSubstitution) = 0 ;
};

__interface  INTERFACE_UUID("{5810CD44-0CA0-4701-B3FA-BEC5182AE4F6}") IDWriteTextAnalysisSink  : public System::IInterface 
{
	virtual HRESULT __stdcall SetScriptAnalysis(unsigned textPosition, unsigned textLength, DWRITE_SCRIPT_ANALYSIS &scriptAnalysis) = 0 ;
	virtual HRESULT __stdcall SetLineBreakpoints(unsigned textPosition, unsigned textLength, DWRITE_LINE_BREAKPOINT &lineBreakpoints) = 0 ;
	virtual HRESULT __stdcall SetBidiLevel(unsigned textPosition, unsigned textLength, System::Byte explicitLevel, System::Byte resolvedLevel) = 0 ;
	virtual HRESULT __stdcall SetNumberSubstitution(unsigned textPosition, unsigned textLength, _di_IDWriteNumberSubstitution &numberSubstitution) = 0 ;
};

__interface  INTERFACE_UUID("{B7E6163E-7F46-43B4-84B3-E4E6249C365D}") IDWriteTextAnalyzer  : public System::IInterface 
{
	virtual HRESULT __stdcall AnalyzeScript(_di_IDWriteTextAnalysisSource &analysisSource, unsigned textPosition, unsigned textLength, _di_IDWriteTextAnalysisSink &analysisSink) = 0 ;
	virtual HRESULT __stdcall AnalyzeBidi(_di_IDWriteTextAnalysisSource &analysisSource, unsigned textPosition, unsigned textLength, _di_IDWriteTextAnalysisSink &analysisSink) = 0 ;
	virtual HRESULT __stdcall AnalyzeNumberSubstitution(_di_IDWriteTextAnalysisSource &analysisSource, unsigned textPosition, unsigned textLength, _di_IDWriteTextAnalysisSink &analysisSink) = 0 ;
	virtual HRESULT __stdcall AnalyzeLineBreakpoints(_di_IDWriteTextAnalysisSource &analysisSource, unsigned textPosition, unsigned textLength, _di_IDWriteTextAnalysisSink &analysisSink) = 0 ;
	virtual HRESULT __stdcall GetGlyphs(System::WideChar &textString, unsigned textLength, _di_IDWriteFontFace &fontFace, System::LongBool isSideways, System::LongBool isRightToLeft, DWRITE_SCRIPT_ANALYSIS &scriptAnalysis, System::WideChar &localeName, _di_IDWriteNumberSubstitution &numberSubstitution, PDwriteTypographicFeatures &features, unsigned &featureRangeLengths, unsigned featureRanges, unsigned maxGlyphCount, System::Word &clusterMap, DWRITE_SHAPING_TEXT_PROPERTIES &textProps, System::Word &glyphIndices, DWRITE_SHAPING_GLYPH_PROPERTIES &glyphProps, unsigned &actualGlyphCount) = 0 ;
	virtual HRESULT __stdcall GetGlyphPlacements(System::WideChar &textString, System::Word &clusterMap, DWRITE_SHAPING_TEXT_PROPERTIES &textProps, unsigned textLength, System::Word &glyphIndices, DWRITE_SHAPING_GLYPH_PROPERTIES &glyphProps, unsigned glyphCount, _di_IDWriteFontFace &fontFace, float fontEmSize, System::LongBool isSideways, System::LongBool isRightToLeft, DWRITE_SCRIPT_ANALYSIS &scriptAnalysis, System::WideChar &localeName, PDwriteTypographicFeatures &features, unsigned &featureRangeLengths, unsigned featureRanges, float &glyphAdvances, DWRITE_GLYPH_OFFSET &glyphOffsets) = 0 ;
	virtual HRESULT __stdcall GetGdiCompatibleGlyphPlacements(System::WideChar &textString, System::Word &clusterMap, DWRITE_SHAPING_TEXT_PROPERTIES &textProps, unsigned textLength, System::Word &glyphIndices, DWRITE_SHAPING_GLYPH_PROPERTIES &glyphProps, unsigned glyphCount, _di_IDWriteFontFace &fontFace, float fontEmSize, float pixelsPerDip, const DWRITE_MATRIX &transform, System::LongBool useGdiNatural, System::LongBool isSideways, System::LongBool isRightToLeft, DWRITE_SCRIPT_ANALYSIS &scriptAnalysis, System::WideChar &localeName, PDwriteTypographicFeatures &features, unsigned &featureRangeLengths, unsigned featureRanges, float &glyphAdvances, DWRITE_GLYPH_OFFSET &glyphOffsets) = 0 ;
};

__interface  INTERFACE_UUID("{8339FDE3-106F-47AB-8373-1C6295EB10B3}") IDWriteInlineObject  : public System::IInterface 
{
	virtual HRESULT __stdcall Draw(void * clientDrawingContext, _di_IDWriteTextRenderer &renderer, float originX, float originY, System::LongBool isSideways, System::LongBool isRightToLeft, const System::_di_IInterface clientDrawingEffect) = 0 ;
	virtual HRESULT __stdcall GetMetrics(DWRITE_INLINE_OBJECT_METRICS &metrics) = 0 ;
	virtual HRESULT __stdcall GetOverhangMetrics(DWRITE_OVERHANG_METRICS &overhangs) = 0 ;
	virtual HRESULT __stdcall GetBreakConditions(DWRITE_BREAK_CONDITION &breakConditionBefore, DWRITE_BREAK_CONDITION &breakConditionAfter) = 0 ;
};

__interface  INTERFACE_UUID("{EAF3A2DA-ECF4-4D24-B644-B34F6842024B}") IDWritePixelSnapping  : public System::IInterface 
{
	virtual HRESULT __stdcall IsPixelSnappingDisabled(void * clientDrawingContext, System::LongBool &isDisabled) = 0 ;
	virtual HRESULT __stdcall GetCurrentTransform(void * clientDrawingContext, DWRITE_MATRIX &transform) = 0 ;
	virtual HRESULT __stdcall GetPixelsPerDip(void * clientDrawingContext, float &pixelsPerDip) = 0 ;
};

__interface  INTERFACE_UUID("{EF8A8135-5CC6-45FE-8825-C5A0724EB819}") IDWriteTextRenderer  : public IDWritePixelSnapping 
{
	virtual HRESULT __stdcall DrawGlyphRun(void * clientDrawingContext, float baselineOriginX, float baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN &glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION &glyphRunDescription, const System::_di_IInterface clientDrawingEffect) = 0 ;
	virtual HRESULT __stdcall DrawUnderline(void * clientDrawingContext, float baselineOriginX, float baselineOriginY, DWRITE_UNDERLINE &underline, const System::_di_IInterface clientDrawingEffect) = 0 ;
	virtual HRESULT __stdcall DrawStrikethrough(void * clientDrawingContext, float baselineOriginX, float baselineOriginY, DWRITE_STRIKETHROUGH &strikethrough, const System::_di_IInterface clientDrawingEffect) = 0 ;
	virtual HRESULT __stdcall DrawInlineObject(void * clientDrawingContext, float originX, float originY, _di_IDWriteInlineObject &inlineObject, System::LongBool isSideways, System::LongBool isRightToLeft, const System::_di_IInterface clientDrawingEffect) = 0 ;
};

__interface  INTERFACE_UUID("{53737037-6D14-410B-9BFE-0B182BB70961}") IDWriteTextLayout  : public IDWriteTextFormat 
{
	virtual HRESULT __stdcall SetMaxWidth(float maxWidth) = 0 ;
	virtual HRESULT __stdcall SetMaxHeight(float maxHeight) = 0 ;
	virtual HRESULT __stdcall SetFontCollection(_di_IDWriteFontCollection &fontCollection, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetFontFamilyName(System::WideChar * fontFamilyName, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetFontWeight(DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetFontStyle(DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetFontStretch(DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetFontSize(float fontSize, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetUnderline(System::LongBool hasUnderline, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetStrikethrough(System::LongBool hasStrikethrough, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetDrawingEffect(const System::_di_IInterface drawingEffect, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetInlineObject(const _di_IDWriteInlineObject inlineObject, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetTypography(const _di_IDWriteTypography typography, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual HRESULT __stdcall SetLocaleName(System::WideChar &localeName, DWRITE_TEXT_RANGE textRange) = 0 ;
	virtual float __stdcall GetMaxWidth() = 0 ;
	virtual float __stdcall GetMaxHeight() = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontCollection(unsigned currentPosition, /* out */ _di_IDWriteFontCollection &fontCollection, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontFamilyNameLength(unsigned currentPosition, unsigned &nameLength, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontFamilyName(unsigned currentPosition, System::WideChar &fontFamilyName, unsigned nameSize, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontWeight(unsigned currentPosition, DWRITE_FONT_WEIGHT &fontWeight, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontStyle(unsigned currentPosition, DWRITE_FONT_STYLE &fontStyle, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontStretch(unsigned currentPosition, DWRITE_FONT_STRETCH &fontStretch, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetFontSize(unsigned currentPosition, float &fontSize, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall GetUnderline(unsigned currentPosition, System::LongBool &hasUnderline, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall GetStrikethrough(unsigned currentPosition, System::LongBool &hasStrikethrough, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall GetDrawingEffect(unsigned currentPosition, /* out */ System::_di_IInterface &drawingEffect, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall GetInlineObject(unsigned currentPosition, /* out */ _di_IDWriteInlineObject &inlineObject, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall GetTypography(unsigned currentPosition, /* out */ _di_IDWriteTypography &typography, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetLocaleNameLength(unsigned currentPosition, unsigned &nameLength, DWRITE_TEXT_RANGE &textRange) = 0 ;
	HIDESBASE virtual HRESULT __stdcall GetLocaleName(unsigned currentPosition, System::WideChar &localeName, unsigned nameSize, DWRITE_TEXT_RANGE &textRange) = 0 ;
	virtual HRESULT __stdcall Draw(void * clientDrawingContext, _di_IDWriteTextRenderer renderer, float originX, float originY) = 0 ;
	virtual HRESULT __stdcall GetLineMetrics(PDwriteLineMetrics lineMetrics, unsigned maxLineCount, unsigned &actualLineCount) = 0 ;
	virtual HRESULT __stdcall GetMetrics(DWRITE_TEXT_METRICS &textMetrics) = 0 ;
	virtual HRESULT __stdcall GetOverhangMetrics(DWRITE_OVERHANG_METRICS &overhangs) = 0 ;
	virtual HRESULT __stdcall GetClusterMetrics(PDwriteClusterMetrics clusterMetrics, unsigned maxClusterCount, unsigned &actualClusterCount) = 0 ;
	virtual HRESULT __stdcall DetermineMinWidth(float &minWidth) = 0 ;
	virtual HRESULT __stdcall HitTestPoint(float pointX, float pointY, /* out */ System::LongBool &isTrailingHit, /* out */ System::LongBool &isInside, /* out */ DWRITE_HIT_TEST_METRICS &hitTestMetrics) = 0 ;
	virtual HRESULT __stdcall HitTestTextPosition(unsigned textPosition, System::LongBool isTrailingHit, float &pointX, float &pointY, DWRITE_HIT_TEST_METRICS &hitTestMetrics) = 0 ;
	virtual HRESULT __stdcall HitTestTextRange(unsigned textPosition, unsigned textLength, float originX, float originY, DWRITE_HIT_TEST_METRICS &hitTestMetrics, unsigned maxHitTestMetricsCount, unsigned &actualHitTestMetricsCount) = 0 ;
};

__interface  INTERFACE_UUID("{5E5A32A3-8DFF-4773-9FF6-0696EAB77267}") IDWriteBitmapRenderTarget  : public System::IInterface 
{
	virtual HRESULT __stdcall DrawGlyphRun(float baselineOriginX, float baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN &glyphRun, _di_IDWriteRenderingParams renderingParams, unsigned textColor, System::Types::PRect blackBoxRect) = 0 ;
	virtual HDC __stdcall GetMemoryDC() = 0 ;
	virtual float __stdcall GetPixelsPerDip() = 0 ;
	virtual HRESULT __stdcall SetPixelsPerDip(float pixelsPerDip) = 0 ;
	virtual HRESULT __stdcall GetCurrentTransform(DWRITE_MATRIX &transform) = 0 ;
	virtual HRESULT __stdcall SetCurrentTransform(DWRITE_MATRIX &transform) = 0 ;
	virtual HRESULT __stdcall GetSize(System::Types::TSize &size) = 0 ;
	virtual HRESULT __stdcall Resize(unsigned width, unsigned height) = 0 ;
};

__interface  INTERFACE_UUID("{1EDD9491-9853-4299-898F-6432983B6F3A}") IDWriteGdiInterop  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateFontFromLOGFONT(tagLOGFONTW &logFont, /* out */ _di_IDWriteFont &font) = 0 ;
	virtual HRESULT __stdcall ConvertFontToLOGFONT(_di_IDWriteFont font, tagLOGFONTW &logFont, System::LongBool &isSystemFont) = 0 ;
	virtual HRESULT __stdcall ConvertFontFaceToLOGFONT(_di_IDWriteFontFace &font, tagLOGFONTW &logFont) = 0 ;
	virtual HRESULT __stdcall CreateFontFaceFromHdc(HDC hdc, /* out */ _di_IDWriteFontFace &fontFace) = 0 ;
	virtual HRESULT __stdcall CreateBitmapRenderTarget(HDC hdc, unsigned width, unsigned height, /* out */ _di_IDWriteBitmapRenderTarget &renderTarget) = 0 ;
};

__interface  INTERFACE_UUID("{7D97DBF7-E085-42D4-81E3-6A883BDED118}") IDWriteGlyphRunAnalysis  : public System::IInterface 
{
	virtual HRESULT __stdcall GetAlphaTextureBounds(DWRITE_TEXTURE_TYPE textureType, System::Types::TRect &textureBounds) = 0 ;
	virtual HRESULT __stdcall CreateAlphaTexture(DWRITE_TEXTURE_TYPE textureType, System::Types::TRect &textureBounds, System::Byte &alphaValues, unsigned bufferSize) = 0 ;
	virtual HRESULT __stdcall GetAlphaBlendParams(_di_IDWriteRenderingParams &renderingParams, float &blendGamma, float &blendEnhancedContrast, float &blendClearTypeLevel) = 0 ;
};

__interface  INTERFACE_UUID("{B859EE5A-D838-4B5B-A2E8-1ADC7D93DB48}") IDWriteFactory  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSystemFontCollection(/* out */ _di_IDWriteFontCollection &fontCollection, System::LongBool checkForUpdates = false) = 0 ;
	virtual HRESULT __stdcall CreateCustomFontCollection(const _di_IDWriteFontCollectionLoader collectionLoader, void * collectionKey, unsigned collectionKeySize, /* out */ _di_IDWriteFontCollection &fontCollection) = 0 ;
	virtual HRESULT __stdcall RegisterFontCollectionLoader(const _di_IDWriteFontCollectionLoader fontCollectionLoader) = 0 ;
	virtual HRESULT __stdcall UnregisterFontCollectionLoader(const _di_IDWriteFontCollectionLoader fontCollectionLoader) = 0 ;
	virtual HRESULT __stdcall CreateFontFileReference(const System::WideChar * filePath, Winapi::Windows::PFileTime lpLastWriteTime, /* out */ _di_IDWriteFontFile &fontFile) = 0 ;
	virtual HRESULT __stdcall CreateCustomFontFileReference(void * fontFileReferenceKey, unsigned fontFileReferenceKeySize, const _di_IDWriteFontFileLoader fontFileLoader, /* out */ _di_IDWriteFontFile &fontFile) = 0 ;
	virtual HRESULT __stdcall CreateFontFace(DWRITE_FONT_FACE_TYPE fontFaceType, unsigned numberOfFiles, PIDWriteFontFile fontFiles, unsigned faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, /* out */ _di_IDWriteFontFace &fontFace) = 0 ;
	virtual HRESULT __stdcall CreateRenderingParams(/* out */ _di_IDWriteRenderingParams &renderingParams) = 0 ;
	virtual HRESULT __stdcall CreateMonitorRenderingParams(HMONITOR monitor, /* out */ _di_IDWriteRenderingParams &renderingParams) = 0 ;
	virtual HRESULT __stdcall CreateCustomRenderingParams(float gamma, float enhancedContrast, float clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, /* out */ _di_IDWriteRenderingParams &renderingParams) = 0 ;
	virtual HRESULT __stdcall RegisterFontFileLoader(const _di_IDWriteFontFileLoader fontFileLoader) = 0 ;
	virtual HRESULT __stdcall UnregisterFontFileLoader(const _di_IDWriteFontFileLoader fontFileLoader) = 0 ;
	virtual HRESULT __stdcall CreateTextFormat(const System::WideChar * fontFamilyName, _di_IDWriteFontCollection fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, float fontSize, const System::WideChar * localeName, /* out */ _di_IDWriteTextFormat &textFormat) = 0 ;
	virtual HRESULT __stdcall CreateTypography(/* out */ _di_IDWriteTypography &typography) = 0 ;
	virtual HRESULT __stdcall GetGdiInterop(/* out */ _di_IDWriteGdiInterop &gdiInterop) = 0 ;
	virtual HRESULT __stdcall CreateTextLayout(System::WideChar * _string, unsigned stringLength, const _di_IDWriteTextFormat textFormat, float maxWidth, float maxHeight, /* out */ _di_IDWriteTextLayout &textLayout) = 0 ;
	virtual HRESULT __stdcall CreateGdiCompatibleTextLayout(System::WideChar &_string, unsigned stringLength, _di_IDWriteTextFormat &textFormat, float layoutWidth, float layoutHeight, float pixelsPerDip, DWRITE_MATRIX &transform, System::LongBool useGdiNatural, /* out */ _di_IDWriteTextLayout &textLayout) = 0 ;
	virtual HRESULT __stdcall CreateEllipsisTrimmingSign(_di_IDWriteTextFormat textFormat, /* out */ _di_IDWriteInlineObject &trimmingSign) = 0 ;
	virtual HRESULT __stdcall CreateTextAnalyzer(/* out */ _di_IDWriteTextAnalyzer &textAnalyzer) = 0 ;
	virtual HRESULT __stdcall CreateNumberSubstitution(DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, System::WideString &localeName, System::LongBool ignoreUserOverride, /* out */ _di_IDWriteNumberSubstitution &numberSubstitution) = 0 ;
	virtual HRESULT __stdcall CreateGlyphRunAnalysis(DWRITE_GLYPH_RUN &glyphRun, float pixelsPerDip, DWRITE_MATRIX &transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, float baselineOriginX, float baselineOriginY, /* out */ _di_IDWriteGlyphRunAnalysis &glyphRunAnalysis) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
#define SID_ID2D1Resource L"{2cd90691-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1Bitmap L"{a2296057-ea42-4099-983b-539fb6505426}"
#define SID_ID2D1GradientStopCollection L"{2cd906a7-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1Brush L"{2cd906a8-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1BitmapBrush L"{2cd906aa-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1SolidColorBrush L"{2cd906a9-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1LinearGradientBrush L"{2cd906ab-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1RadialGradientBrush L"{2cd906ac-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1StrokeStyle L"{2cd9069d-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1Geometry L"{2cd906a1-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1RectangleGeometry L"{2cd906a2-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1RoundedRectangleGeometry L"{2cd906a3-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1EllipseGeometry L"{2cd906a4-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1GeometryGroup L"{2cd906a6-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1TransformedGeometry L"{2cd906bb-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1SimplifiedGeometrySink L"{2cd9069e-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1GeometrySink L"{2cd9069f-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1TessellationSink L"{2cd906c1-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1PathGeometry L"{2cd906a5-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1Mesh L"{2cd906c2-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1Layer L"{2cd9069b-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1DrawingStateBlock L"{28506e39-ebf6-46a1-bb47-fd85565ab957}"
#define SID_ID2D1RenderTarget L"{2cd90694-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1BitmapRenderTarget L"{2cd90695-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1HwndRenderTarget L"{2cd90698-12e2-11dc-9fed-001143a055f9}"
#define SID_ID2D1GdiInteropRenderTarget L"{e0db51c3-6f77-4bae-b3d5-e47509b35838}"
#define SID_ID2D1DCRenderTarget L"{1c51bc64-de61-46fd-9899-63a5d8f03950}"
#define SID_ID2D1Factory L"{06152247-6f50-465a-9245-118bfd3b6007}"
#define SID_IDWriteFontFileLoader L"{727cad4e-d6af-4c9e-8a08-d695b11caa49}"
#define SID_IDWriteLocalFontFileLoader L"{b2d9f3ec-c9fe-4a11-a2ec-d86208f7c0a2}"
#define SID_IDWriteFontFileStream L"{6d4865fe-0ab8-4d91-8f62-5dd6be34a3e0}"
#define SID_IDWriteFontFile L"{739d886a-cef5-47dc-8769-1a8b41bebbb0}"
#define SID_IDWriteRenderingParams L"{2f0da53a-2add-47cd-82ee-d9ec34688e75}"
#define SID_IDWriteFontFace L"{5f49804d-7024-4d43-bfa9-d25984f53849}"
#define SID_IDWriteFontCollectionLoader L"{cca920e4-52f0-492b-bfa8-29c72ee0a468}"
#define SID_IDWriteFontFileEnumerator L"{72755049-5ff7-435d-8348-4be97cfa6c7c}"
#define SID_IDWriteLocalizedStrings L"{08256209-099a-4b34-b86d-c22b110e7771}"
#define SID_IDWriteFontCollection L"{a84cee02-3eea-4eee-a827-87c1a02a0fcc}"
#define SID_IDWriteFontList L"{1a0d8438-1d97-4ec1-aef9-a2fb86ed6acb}"
#define SID_IDWriteFontFamily L"{da20d8ef-812a-4c43-9802-62ec4abd7add}"
#define SID_IDWriteFont L"{acd16696-8c14-4f5d-877e-fe3fc1d32737}"
#define SID_IDWriteTextFormat L"{9c906818-31d7-4fd3-a151-7c5e225db55a}"
#define SID_IDWriteTypography L"{55f1112b-1dc2-4b3c-9541-f46894ed85b6}"
#define SID_IDWriteNumberSubstitution L"{14885CC9-BAB0-4f90-B6ED-5C366A2CD03D}"
#define SID_IDWriteTextAnalysisSource L"{688e1a58-5094-47c8-adc8-fbcea60ae92b}"
#define SID_IDWriteTextAnalysisSink L"{5810cd44-0ca0-4701-b3fa-bec5182ae4f6}"
#define SID_IDWriteTextAnalyzer L"{b7e6163e-7f46-43b4-84b3-e4e6249c365d}"
#define SID_IDWriteInlineObject L"{8339FDE3-106F-47ab-8373-1C6295EB10B3}"
#define SID_IDWritePixelSnapping L"{eaf3a2da-ecf4-4d24-b644-b34f6842024b}"
#define SID_IDWriteTextRenderer L"{ef8a8135-5cc6-45fe-8825-c5a0724eb819}"
#define SID_IDWriteTextLayout L"{53737037-6d14-410b-9bfe-0b182bb70961}"
#define SID_IDWriteBitmapRenderTarget L"{5e5a32a3-8dff-4773-9ff6-0696eab77267}"
#define SID_IDWriteGdiInterop L"{1edd9491-9853-4299-898f-6432983b6f3a}"
#define SID_IDWriteGlyphRunAnalysis L"{7d97dbf7-e085-42d4-81e3-6a883bded118}"
#define SID_IDWriteFactory L"{b859ee5a-d838-4b5b-a2e8-1adc7d93db48}"
#define dwritelib L"DWRITE.DLL"
#define d2d1lib L"d2d1.dll"
extern DELPHI_PACKAGE D2D_POINT_2F __fastcall D2D1PointF(const float X, const float Y);
extern DELPHI_PACKAGE D2D_SIZE_F __fastcall D2D1SizeF(const float Width, const float Height);
extern DELPHI_PACKAGE D2D_SIZE_U __fastcall D2D1SizeU(const unsigned Width, const unsigned Height);
extern DELPHI_PACKAGE D2D_RECT_F __fastcall D2D1RectF(const float Left, const float Top, const float Right, const float Bottom)/* overload */;
extern DELPHI_PACKAGE D2D1_ARC_SEGMENT __fastcall D2D1ArcSegment(const D2D_POINT_2F &Point, const D2D_SIZE_F &Size, float RotationAngle, const D2D1_SWEEP_DIRECTION sweepDirection, const D2D1_ARC_SIZE ArcSize);
extern DELPHI_PACKAGE D3DCOLORVALUE __fastcall D2D1ColorF(const float R, const float G, const float B, const float A)/* overload */;
extern DELPHI_PACKAGE D2D1_BEZIER_SEGMENT __fastcall D2D1BezierSegment(const D2D_POINT_2F &A, const D2D_POINT_2F &B, const D2D_POINT_2F &C);
extern DELPHI_PACKAGE D2D1_GRADIENT_STOP __fastcall D2D1GradientStop(const float Position, const D3DCOLORVALUE &Color);
extern DELPHI_PACKAGE D2D1_QUADRATIC_BEZIER_SEGMENT __fastcall D2D1QuadraticBezierSegment(const D2D_POINT_2F &A, const D2D_POINT_2F &B);
extern DELPHI_PACKAGE D2D1_STROKE_STYLE_PROPERTIES __fastcall D2D1StrokeStyleProperties(D2D1_CAP_STYLE StartCap = (D2D1_CAP_STYLE)(0x0), D2D1_CAP_STYLE EndCap = (D2D1_CAP_STYLE)(0x0), D2D1_CAP_STYLE DashCap = (D2D1_CAP_STYLE)(0x0), D2D1_LINE_JOIN LineJoin = (D2D1_LINE_JOIN)(0x0), float MiterLimit = 1.000000E+01f, D2D1_DASH_STYLE DashStyle = (D2D1_DASH_STYLE)(0x0), float DashOffset = 0.000000E+00f);
extern DELPHI_PACKAGE D2D1_ELLIPSE __fastcall D2D1Ellipse(const D2D_POINT_2F &Center, const float Rx, const float Ry);
extern DELPHI_PACKAGE D2D1_ROUNDED_RECT __fastcall D2D1RoundedRect(const D2D_RECT_F &Rect, float RadiusX, float RadiusY);
extern DELPHI_PACKAGE D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES __fastcall D2D1LinearGradientBrushProperties(const D2D_POINT_2F &StartPoint, const D2D_POINT_2F &EndPoint);
extern DELPHI_PACKAGE D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES __fastcall D2D1RadialGradientBrushProperties(const D2D_POINT_2F &Center, const D2D_POINT_2F &GradientOriginOffset, float RadiusX, float RadiusY);
extern DELPHI_PACKAGE D2D1_PIXEL_FORMAT __fastcall D2D1PixelFormat(const DXGI_FORMAT DxgiFormat = (DXGI_FORMAT)(0x0), D2D1_ALPHA_MODE AlphaMode = (D2D1_ALPHA_MODE)(0x0));
extern DELPHI_PACKAGE D2D1_RENDER_TARGET_PROPERTIES __fastcall D2D1RenderTargetProperties(D2D1_RENDER_TARGET_TYPE Type = (D2D1_RENDER_TARGET_TYPE)(0x0))/* overload */;
extern DELPHI_PACKAGE D2D1_RENDER_TARGET_PROPERTIES __fastcall D2D1RenderTargetProperties(D2D1_RENDER_TARGET_TYPE Type, const D2D1_PIXEL_FORMAT &PixelFormat, float DpiX = 0.000000E+00f, float DpiY = 0.000000E+00f, D2D1_RENDER_TARGET_USAGE Usage = (D2D1_RENDER_TARGET_USAGE)(0x0), D2D1_FEATURE_LEVEL MinLevel = (D2D1_FEATURE_LEVEL)(0x0))/* overload */;
extern DELPHI_PACKAGE D2D1_HWND_RENDER_TARGET_PROPERTIES __fastcall D2D1HwndRenderTargetProperties(HWND Hwnd)/* overload */;
extern DELPHI_PACKAGE D2D1_HWND_RENDER_TARGET_PROPERTIES __fastcall D2D1HwndRenderTargetProperties(HWND Hwnd, const D2D_SIZE_U &PixelSize, D2D1_PRESENT_OPTIONS PresentOptions = (D2D1_PRESENT_OPTIONS)(0x0))/* overload */;
extern DELPHI_PACKAGE D2D1_BITMAP_PROPERTIES __fastcall D2D1BitmapProperties(void)/* overload */;
extern DELPHI_PACKAGE D2D1_BITMAP_PROPERTIES __fastcall D2D1BitmapProperties(const D2D1_PIXEL_FORMAT &PixleFormat, float DpiX = 9.600000E+01f, float DpiY = 9.600000E+01f)/* overload */;
}	/* namespace D2d1 */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D2d1HPP
