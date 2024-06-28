// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Chart.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_ChartHPP
#define Fmxtee_ChartHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UIConsts.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <System.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Canvas.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Chart
{
//-- forward type declarations -----------------------------------------------
struct TAxisSavedScales;
class DELPHICLASS TCustomChartWall;
class DELPHICLASS TChartWall;
class DELPHICLASS LegendException;
class DELPHICLASS TLegendSymbol;
class DELPHICLASS TTeeCustomShapePosition;
class DELPHICLASS TTextShape;
class DELPHICLASS TStringsShape;
class DELPHICLASS TLegendTitle;
class DELPHICLASS TLegendItem;
class DELPHICLASS TLegendItems;
class DELPHICLASS TTeeLegendEvent;
class DELPHICLASS TCustomChartLegend;
class DELPHICLASS TChartLegend;
class DELPHICLASS TChartTitle;
class DELPHICLASS TChartFootTitle;
class DELPHICLASS TChartBackWall;
class DELPHICLASS TChartRightWall;
class DELPHICLASS TChartBottomWall;
class DELPHICLASS TChartLeftWall;
class DELPHICLASS TChartWalls;
class DELPHICLASS TCustomChart;
class DELPHICLASS TChart;
class DELPHICLASS TTeeSeriesTypes;
class DELPHICLASS TTeeToolTypes;
class DELPHICLASS TCustomChartLink;
class DELPHICLASS TColorPalettes;
class DELPHICLASS TChartTheme;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TAxisSavedScales
{
public:
	bool Auto;
	bool AutoMin;
	bool AutoMax;
	double Min;
	double Max;
};


typedef System::DynamicArray<TAxisSavedScales> TAllAxisSavedScales;

typedef System::StaticArray<System::UnicodeString, 3> TLegendItemText;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomChartWall : public Fmxtee::Procs::TTeeCustomShape
{
	typedef Fmxtee::Procs::TTeeCustomShape inherited;
	
private:
	bool FAutoHide;
	bool FDark3D;
	int FEnd;
	int FSize;
	int FStart;
	bool __fastcall ApplyDark3D();
	void __fastcall CalcPositions(/* out */ int &ATop, /* out */ int &ABottom);
	Fmxtee::Canvas::TTeePen* __fastcall GetPen();
	void __fastcall InitColor(const System::Uitypes::TAlphaColor AColor);
	bool __fastcall IsColorStored();
	void __fastcall SetAutoHide(const bool Value);
	void __fastcall SetDark3D(const bool Value);
	void __fastcall SetEnd(const int Value);
	HIDESBASE void __fastcall SetPen(Fmxtee::Canvas::TTeePen* const Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetStart(const int Value);
	bool __fastcall TryDrawWall(const int APos1, const int APos2, /* out */ Fmxtee::Canvas::TTeeBlend* &ABlend);
	
protected:
	System::Uitypes::TAlphaColor DefaultColor;
	void __fastcall DoEndBlending(Fmxtee::Canvas::TTeeBlend* const Blend);
	bool __fastcall ShouldDraw();
	
public:
	__fastcall virtual TCustomChartWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property bool AutoHide = {read=FAutoHide, write=SetAutoHide, default=0};
	__property Color = {stored=IsColorStored};
	__property bool Dark3D = {read=FDark3D, write=SetDark3D, default=1};
	__property int EndPosition = {read=FEnd, write=SetEnd, default=100};
	__property Fmxtee::Canvas::TTeePen* Pen = {read=GetPen, write=SetPen};
	__property int Size = {read=FSize, write=SetSize, default=0};
	__property int StartPosition = {read=FStart, write=SetStart, default=0};
	__property Transparency = {default=0};
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TCustomChartWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartWall : public TCustomChartWall
{
	typedef TCustomChartWall inherited;
	
__published:
	__property AutoHide = {default=0};
	__property Brush;
	__property Color;
	__property Dark3D = {default=1};
	__property EndPosition = {default=100};
	__property Gradient;
	__property Pen;
	__property RoundSize = {default=16};
	__property Size = {default=0};
	__property StartPosition = {default=0};
	__property Transparency = {default=0};
	__property Transparent;
	__property Visible = {default=1};
public:
	/* TCustomChartWall.Create */ inline __fastcall virtual TChartWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TCustomChartWall(AOwner) { }
	
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TChartWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TLegendStyle : unsigned char { lsAuto, lsSeries, lsValues, lsLastValues, lsSeriesGroups };

enum DECLSPEC_DENUM TLegendAlignment : unsigned char { laLeft, laRight, laTop, laBottom };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION LegendException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall LegendException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall LegendException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall LegendException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall LegendException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall LegendException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall LegendException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall LegendException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall LegendException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall LegendException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall LegendException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall LegendException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall LegendException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~LegendException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TOnGetLegendText)(Fmxtee::Engine::TCustomAxisPanel* Sender, TLegendStyle LegendStyle, int Index, System::UnicodeString &LegendText);

enum DECLSPEC_DENUM TLegendSymbolSize : unsigned char { lcsPercent, lcsPixels };

enum DECLSPEC_DENUM TLegendSymbolPosition : unsigned char { spLeft, spRight };

typedef void __fastcall (__closure *TSymbolDrawEvent)(System::TObject* Sender, Fmxtee::Engine::TChartSeries* Series, int ValueIndex, const System::Types::TRectF &R);

typedef int __fastcall (__closure *TSymbolCalcHeight)(void);

class PASCALIMPLEMENTATION TLegendSymbol : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FContinuous;
	bool FDefaultPen;
	Fmxtee::Canvas::TTeeEmboss* FEmboss;
	Fmxtee::Canvas::TTeeGradient* FGradient;
	int FHeight;
	TLegendSymbolSize FHeightUnits;
	TSymbolDrawEvent FOnDraw;
	Fmxtee::Canvas::TTeePen* FPen;
	TLegendSymbolPosition FPosition;
	Fmxtee::Canvas::TTeeShadow* FShadow;
	bool FSquared;
	bool FVisible;
	int FWidth;
	TLegendSymbolSize FWidthUnits;
	int __fastcall CalcHeight();
	void __fastcall CanvasChanged(System::TObject* Sender);
	void __fastcall Repaint();
	void __fastcall SetBooleanProperty(bool &Variable, const bool Value);
	void __fastcall SetContinuous(const bool Value);
	void __fastcall SetDefaultPen(const bool Value);
	void __fastcall SetEmboss(Fmxtee::Canvas::TTeeEmboss* const Value);
	void __fastcall SetGradient(Fmxtee::Canvas::TTeeGradient* const Value);
	void __fastcall SetHeight(const int Value);
	void __fastcall SetHeightUnits(const TLegendSymbolSize Value);
	void __fastcall SetPen(Fmxtee::Canvas::TTeePen* const Value);
	void __fastcall SetPosition(const TLegendSymbolPosition Value);
	void __fastcall SetShadow(Fmxtee::Canvas::TTeeShadow* const Value);
	void __fastcall SetSquared(const bool Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetWidth(const int Value);
	void __fastcall SetWidthUnits(const TLegendSymbolSize Value);
	
protected:
	TSymbolCalcHeight CalcItemHeight;
	int __fastcall CalcWidth(int Value);
	void __fastcall Draw(System::Uitypes::TAlphaColor AColor, const System::Types::TRectF &R);
	
public:
	Fmxtee::Procs::TCustomTeePanel* Parent;
	__fastcall TLegendSymbol(Fmxtee::Procs::TCustomTeePanel* const AParent);
	__fastcall virtual ~TLegendSymbol();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool Continuous = {read=FContinuous, write=SetContinuous, default=0};
	__property bool DefaultPen = {read=FDefaultPen, write=SetDefaultPen, default=1};
	__property Fmxtee::Canvas::TTeeEmboss* Emboss = {read=FEmboss, write=SetEmboss};
	__property Fmxtee::Canvas::TTeeGradient* Gradient = {read=FGradient, write=SetGradient};
	__property int Height = {read=FHeight, write=SetHeight, default=100};
	__property TLegendSymbolSize HeightUnits = {read=FHeightUnits, write=SetHeightUnits, default=0};
	__property Fmxtee::Canvas::TTeePen* Pen = {read=FPen, write=SetPen};
	__property TLegendSymbolPosition Position = {read=FPosition, write=SetPosition, default=0};
	__property Fmxtee::Canvas::TTeeShadow* Shadow = {read=FShadow, write=SetShadow};
	__property bool Squared = {read=FSquared, write=SetSquared, default=1};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
	__property int Width = {read=FWidth, write=SetWidth, default=20};
	__property TLegendSymbolSize WidthUnits = {read=FWidthUnits, write=SetWidthUnits, default=0};
	__property TSymbolDrawEvent OnDraw = {read=FOnDraw, write=FOnDraw};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeCustomShapePosition : public Fmxtee::Engine::TCustomTextShape
{
	typedef Fmxtee::Engine::TCustomTextShape inherited;
	
private:
	int __fastcall GetLeft();
	int __fastcall GetTop();
	bool __fastcall IsCustomStored();
	void __fastcall SetCustomPosition(const bool Value);
	void __fastcall SetLeft(const int Value);
	void __fastcall SetTop(const int Value);
	
protected:
	bool FCustomPosition;
	bool DefaultCustom;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property bool CustomPosition = {read=FCustomPosition, write=SetCustomPosition, stored=IsCustomStored, nodefault};
	__property int Left = {read=GetLeft, write=SetLeft, stored=FCustomPosition, nodefault};
	__property int Top = {read=GetTop, write=SetTop, stored=FCustomPosition, nodefault};
public:
	/* TCustomTextShape.Create */ inline __fastcall virtual TTeeCustomShapePosition(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : Fmxtee::Engine::TCustomTextShape(AOwner) { }
	/* TCustomTextShape.Destroy */ inline __fastcall virtual ~TTeeCustomShapePosition() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTextShape : public TTeeCustomShapePosition
{
	typedef TTeeCustomShapePosition inherited;
	
__published:
	__property Alignment = {default=0};
	__property Angle = {default=0};
	__property AutoSize = {default=1};
	__property Bevel = {default=0};
	__property BevelWidth = {default=2};
	__property Brush;
	__property Children;
	__property ChildLayout = {default=0};
	__property ClipText = {default=1};
	__property Color = {default=-1};
	__property Cursor = {default=0};
	__property CustomPosition;
	__property Emboss;
	__property Font;
	__property Frame;
	__property Gradient;
	__property Left;
	__property Margins;
	__property Picture;
	__property Shadow;
	__property ShapeCallout;
	__property ShapeStyle = {default=0};
	__property Text = {default=0};
	__property TextAlignment;
	__property TextFormat = {default=0};
	__property Top;
	__property Transparency = {default=0};
	__property Transparent;
	__property VertTextAlign = {default=0};
	__property Visible;
public:
	/* TCustomTextShape.Create */ inline __fastcall virtual TTextShape(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TTeeCustomShapePosition(AOwner) { }
	/* TCustomTextShape.Destroy */ inline __fastcall virtual ~TTextShape() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStringsShape : public TTextShape
{
	typedef TTextShape inherited;
	
private:
	System::Classes::TStrings* FTitleText;
	bool IChangingText;
	System::UnicodeString __fastcall GetCaption();
	void __fastcall SetCaption(const System::UnicodeString Value);
	HIDESBASE void __fastcall SetText(System::Classes::TStrings* const Value);
	void __fastcall TextChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall ChangedText();
	
public:
	__fastcall virtual TStringsShape(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	__fastcall virtual ~TStringsShape();
	void __fastcall Clear();
	__property System::UnicodeString Caption = {read=GetCaption, write=SetCaption};
	
__published:
	__property System::Classes::TStrings* Text = {read=FTitleText, write=SetText};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TCheckBoxesStyle : unsigned char { cbsCheck, cbsRadio };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLegendTitle : public TStringsShape
{
	typedef TStringsShape inherited;
	
protected:
	DYNAMIC void __fastcall InitEmboss(Fmxtee::Canvas::TTeeEmboss* const AEmboss);
	DYNAMIC void __fastcall InitShadow(Fmxtee::Canvas::TTeeShadow* const AShadow);
	
public:
	__fastcall virtual TLegendTitle(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TextFormat = {default=0};
	__property Transparency = {default=0};
	__property Visible = {default=1};
public:
	/* TStringsShape.Destroy */ inline __fastcall virtual ~TLegendTitle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLegendItem : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FAlign;
	Fmxtee::Canvas::TTeeFont* FFont;
	int FLeft;
	System::Types::TRectF FSymbol;
	System::UnicodeString FText;
	System::UnicodeString FText2;
	System::UnicodeString FText3;
	int FTop;
	TCustomChartLegend* ILegend;
	Fmxtee::Canvas::TTeeFont* __fastcall GetFont();
	void __fastcall SetAlign(const int Value);
	void __fastcall SetCustom(bool SetPos);
	void __fastcall SetFont(Fmxtee::Canvas::TTeeFont* const Value);
	void __fastcall SetLeft(const int Value);
	void __fastcall SetText(const System::UnicodeString Value);
	void __fastcall SetText2(const System::UnicodeString Value);
	void __fastcall SetTextVariable(System::UnicodeString &Variable, const System::UnicodeString Value);
	void __fastcall SetTop(const int Value);
	
public:
	__fastcall virtual ~TLegendItem();
	bool __fastcall HasFont();
	__property System::Types::TRectF SymbolRect = {read=FSymbol, write=FSymbol};
	
__published:
	__property int Align = {read=FAlign, write=SetAlign, nodefault};
	__property Fmxtee::Canvas::TTeeFont* Font = {read=GetFont, write=SetFont};
	__property int Left = {read=FLeft, write=SetLeft, nodefault};
	__property System::UnicodeString Text = {read=FText, write=SetText};
	__property System::UnicodeString Text2 = {read=FText2, write=SetText2};
	__property int Top = {read=FTop, write=SetTop, nodefault};
public:
	/* TObject.Create */ inline __fastcall TLegendItem() : System::Classes::TPersistent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TLegendItems : public System::Generics::Collections::TList__1<TLegendItem*>
{
	typedef System::Generics::Collections::TList__1<TLegendItem*> inherited;
	
public:
	TLegendItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FCustom;
	bool FCustomPosition;
	TCustomChartLegend* ILegend;
	void __fastcall ClearItems();
	HIDESBASE TLegendItem* __fastcall GetItem(int Index);
	void __fastcall SetCustom(const bool Value);
	void __fastcall SetCustomPosition(const bool Value);
	
public:
	__fastcall virtual ~TLegendItems();
	HIDESBASE void __fastcall Clear();
	__property bool Custom = {read=FCustom, write=SetCustom, nodefault};
	__property bool CustomPosition = {read=FCustomPosition, write=SetCustomPosition, nodefault};
	__property TLegendItem* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* {System_Generics_Collections}TList<FMXTee_Chart_TLegendItem>.Create */ inline __fastcall TLegendItems()/* overload */ : System::Generics::Collections::TList__1<TLegendItem*>() { }
	/* {System_Generics_Collections}TList<FMXTee_Chart_TLegendItem>.Create */ inline __fastcall TLegendItems(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TLegendItem*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TLegendItem*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMXTee_Chart_TLegendItem>.Create */ inline __fastcall TLegendItems(System::Generics::Collections::TEnumerable__1<TLegendItem*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TLegendItem*>(Collection) { }
	
};


enum DECLSPEC_DENUM TLegendJustify : unsigned char { ljAutomatic, ljYes, ljNo };

typedef void __fastcall (__closure *TLegendCalcSize)(TCustomChartLegend* Sender, int &ASize);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeLegendEvent : public Fmxtee::Procs::TTeeEvent
{
	typedef Fmxtee::Procs::TTeeEvent inherited;
	
public:
	/* TObject.Create */ inline __fastcall TTeeLegendEvent() : Fmxtee::Procs::TTeeEvent() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeLegendEvent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomChartLegend : public TTeeCustomShapePosition
{
	typedef TTeeCustomShapePosition inherited;
	
	
private:
	typedef System::DynamicArray<TLegendItemText> _TCustomChartLegend__1;
	
	
public:
	TLegendItem* operator[](int Index) { return this->Item[Index]; }
	
private:
	TLegendAlignment FAlignment;
	bool FCheckBoxes;
	TCheckBoxesStyle FCheckBoxesStyle;
	bool FCurrentPage;
	Fmxtee::Canvas::TTeeHiddenPen* FDividingLines;
	bool FDrawBehind;
	int FFirstValue;
	bool FFontSeriesColor;
	Fmxtee::Canvas::TTeeTransparency FGlobalTransp;
	TLegendJustify FHorizJustify;
	int FHorizMargin;
	bool FInverted;
	TLegendItems* FItems;
	int FLeftPercent;
	TLegendStyle FLegendStyle;
	int FMaxNumRows;
	Fmxtee::Procs::TTeeUnits FPosUnits;
	bool FResizeChart;
	Fmxtee::Engine::TTeeSelected* FSelected;
	Fmxtee::Engine::TChartSeries* FSeries;
	TLegendSymbol* FSymbol;
	Fmxtee::Engine::TLegendTextStyle FTextStyle;
	int FTextSymbolGap;
	TLegendTitle* FTitle;
	int FTopLeftPos;
	int FTopPercent;
	int FVertMargin;
	int FVertSpacing;
	int IColorWidth;
	bool ICustomFont;
	int ILastValue;
	int ITotalItems;
	bool IDrawTitle;
	_TCustomChartLegend__1 IItems;
	bool IJustify;
	int IMaxWidth;
	int ISpaceWidth;
	int ItemsTopMargin;
	int ItemHeight;
	int XLegendBox;
	int XLegendText;
	int XLegendColor;
	int __fastcall AllColumnsWidth(const int AIndex);
	System::Uitypes::TCursor __fastcall CalcCursor();
	bool __fastcall CalcInverted();
	int __fastcall CalcItemHeight();
	int __fastcall CalcItemWidth(const int ACol, const int AIndex);
	int __fastcall CalcItemWidthColor(const int AWidth);
	void __fastcall CheckBoxChanged();
	int __fastcall FirstItemTop();
	TLegendItem* __fastcall GetItem(int Index);
	System::Types::TRectF __fastcall GetRectLegend();
	Fmxtee::Engine::TTeeSelected* __fastcall GetSelected();
	int __fastcall GetSymbolWidth();
	TLegendTitle* __fastcall GetTitle();
	bool __fastcall GetVertical();
	bool __fastcall HasCheckBoxes();
	void __fastcall PrepareSymbolPen();
	HIDESBASE void __fastcall SetAlignment(const TLegendAlignment Value);
	void __fastcall SetCheckBoxes(const bool Value);
	void __fastcall SetCheckBoxesStyle(const TCheckBoxesStyle Value);
	void __fastcall SetCurrentPage(const bool Value);
	void __fastcall SetDividingLines(Fmxtee::Canvas::TTeeHiddenPen* const Value);
	void __fastcall SetDrawBehind(const bool Value);
	void __fastcall SetFirstValue(const int Value);
	void __fastcall SetFontSeriesColor(const bool Value);
	void __fastcall SetGlobalTransp(const Fmxtee::Canvas::TTeeTransparency Value);
	void __fastcall SetHorizJustify(const TLegendJustify Value);
	void __fastcall SetHorizMargin(const int Value);
	void __fastcall SetInverted(const bool Value);
	void __fastcall SetLeftPercent(const int Value);
	void __fastcall SetLegendStyle(const TLegendStyle Value);
	void __fastcall SetMaxNumRows(const int Value);
	void __fastcall SetPosUnits(const Fmxtee::Procs::TTeeUnits Value);
	void __fastcall SetResizeChart(const bool Value);
	void __fastcall SetSelected(Fmxtee::Engine::TTeeSelected* const Value);
	void __fastcall SetSeries(Fmxtee::Engine::TChartSeries* const Value);
	void __fastcall SetSymbol(TLegendSymbol* const Value);
	void __fastcall SetSymbolWidth(const int Value);
	void __fastcall SetTextSymbolGap(const int Value);
	void __fastcall SetTextStyle(const Fmxtee::Engine::TLegendTextStyle Value);
	void __fastcall SetTitle(TLegendTitle* const Value);
	void __fastcall SetTopLeftPos(const int Value);
	void __fastcall SetTopPercent(const int Value);
	void __fastcall SetVertMargin(const int Value);
	void __fastcall SetVertSpacing(const int Value);
	int __fastcall TitleWidth();
	
protected:
	TLegendStyle InternalLegendStyle;
	TLegendCalcSize FOnCalcSize;
	void __fastcall CalcRect();
	void __fastcall CalcLegendStyle();
	bool __fastcall DoMouseDown(const int x, const int y, int PointIndex);
	Fmxtee::Engine::TChartSeries* __fastcall GetLegendSeries();
	
public:
	int NumCols;
	int NumRows;
	bool ColumnWidthAuto;
	System::StaticArray<int, 3> ColumnWidths;
	__fastcall virtual TCustomChartLegend(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	__fastcall virtual ~TCustomChartLegend();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall Clicked(int x, int y)/* overload */;
	int __fastcall Clicked(const System::Types::TPointF &P)/* overload */;
	void __fastcall DrawLegend();
	System::UnicodeString __fastcall FormattedValue(Fmxtee::Engine::TChartSeries* const ASeries, int ValueIndex);
	System::UnicodeString __fastcall FormattedLegend(int AIndex);
	bool __fastcall ShouldDraw();
	__property int TotalLegendItems = {read=ITotalItems, nodefault};
	__property System::Types::TRectF RectLegend = {read=GetRectLegend};
	__property bool Vertical = {read=GetVertical, nodefault};
	__property TLegendAlignment Alignment = {read=FAlignment, write=SetAlignment, default=1};
	__property bool CheckBoxes = {read=FCheckBoxes, write=SetCheckBoxes, default=0};
	__property TCheckBoxesStyle CheckBoxesStyle = {read=FCheckBoxesStyle, write=SetCheckBoxesStyle, default=0};
	__property int ColorWidth = {read=GetSymbolWidth, write=SetSymbolWidth, default=20};
	__property bool CurrentPage = {read=FCurrentPage, write=SetCurrentPage, default=1};
	__property Fmxtee::Canvas::TTeeHiddenPen* DividingLines = {read=FDividingLines, write=SetDividingLines};
	__property bool DrawBehind = {read=FDrawBehind, write=SetDrawBehind, default=0};
	__property int FirstValue = {read=FFirstValue, write=SetFirstValue, default=0};
	__property bool FontSeriesColor = {read=FFontSeriesColor, write=SetFontSeriesColor, default=0};
	__property Fmxtee::Canvas::TTeeTransparency GlobalTransparency = {read=FGlobalTransp, write=SetGlobalTransp, default=0};
	__property TLegendJustify HorizJustify = {read=FHorizJustify, write=SetHorizJustify, default=0};
	__property int HorizMargin = {read=FHorizMargin, write=SetHorizMargin, default=0};
	__property bool Inverted = {read=FInverted, write=SetInverted, default=0};
	__property TLegendItem* Item[int Index] = {read=GetItem/*, default*/};
	__property TLegendItems* Items = {read=FItems};
	__property int LastValue = {read=ILastValue, nodefault};
	__property int LeftPercent = {read=FLeftPercent, write=SetLeftPercent, default=0};
	__property TLegendStyle LegendStyle = {read=FLegendStyle, write=SetLegendStyle, default=0};
	__property int MaxNumRows = {read=FMaxNumRows, write=SetMaxNumRows, default=0};
	__property Fmxtee::Procs::TTeeUnits PositionUnits = {read=FPosUnits, write=SetPosUnits, default=1};
	__property bool ResizeChart = {read=FResizeChart, write=SetResizeChart, default=1};
	__property Fmxtee::Engine::TTeeSelected* Selected = {read=GetSelected, write=SetSelected};
	__property Fmxtee::Engine::TChartSeries* Series = {read=FSeries, write=SetSeries};
	__property TLegendSymbol* Symbol = {read=FSymbol, write=SetSymbol};
	__property Fmxtee::Engine::TLegendTextStyle TextStyle = {read=FTextStyle, write=SetTextStyle, default=1};
	__property int TextSymbolGap = {read=FTextSymbolGap, write=SetTextSymbolGap, default=2};
	__property TLegendTitle* Title = {read=GetTitle, write=SetTitle};
	__property int TopPercent = {read=FTopPercent, write=SetTopPercent, default=0};
	__property int TopPos = {read=FTopLeftPos, write=SetTopLeftPos, default=10};
	__property int VertMargin = {read=FVertMargin, write=SetVertMargin, default=0};
	__property int VertSpacing = {read=FVertSpacing, write=SetVertSpacing, default=0};
	__property Visible;
};


class PASCALIMPLEMENTATION TChartLegend : public TCustomChartLegend
{
	typedef TCustomChartLegend inherited;
	
__published:
	__property Alignment = {default=1};
	__property Bevel = {default=0};
	__property BevelWidth = {default=2};
	__property Brush;
	__property CheckBoxes = {default=0};
	__property CheckBoxesStyle = {default=0};
	__property Children;
	__property Color = {default=-1};
	__property ColorWidth = {default=20};
	__property CurrentPage = {default=1};
	__property CustomPosition;
	__property DividingLines;
	__property DrawBehind = {default=0};
	__property Emboss;
	__property FirstValue = {default=0};
	__property Font;
	__property FontSeriesColor = {default=0};
	__property Frame;
	__property GlobalTransparency = {default=0};
	__property Gradient;
	__property HorizJustify = {default=0};
	__property HorizMargin = {default=0};
	__property Inverted = {default=0};
	__property Left;
	__property LeftPercent = {default=0};
	__property LegendStyle = {default=0};
	__property MaxNumRows = {default=0};
	__property Picture;
	__property PositionUnits = {default=1};
	__property ResizeChart = {default=1};
	__property RoundSize = {default=16};
	__property Selected;
	__property Shadow;
	__property ShapeCallout;
	__property ShapeStyle = {default=0};
	__property Symbol;
	__property TextStyle = {default=1};
	__property TextSymbolGap = {default=2};
	__property Title;
	__property Top;
	__property TopPercent = {default=0};
	__property TopPos = {default=10};
	__property Transparency = {default=0};
	__property Transparent;
	__property VertMargin = {default=0};
	__property VertSpacing = {default=0};
	__property Visible;
	__property ClipText = {default=1};
	__property Cursor = {default=0};
	__property Margins;
	__property TextFormat = {default=0};
public:
	/* TCustomChartLegend.Create */ inline __fastcall virtual TChartLegend(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TCustomChartLegend(AOwner) { }
	/* TCustomChartLegend.Destroy */ inline __fastcall virtual ~TChartLegend() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartTitle : public TStringsShape
{
	typedef TStringsShape inherited;
	
private:
	bool FAdjustFrame;
	int FVertMargin;
	bool IOnTop;
	System::Types::TRectF __fastcall GetShapeBounds();
	void __fastcall SetAdjustFrame(bool Value);
	void __fastcall SetVertMargin(const int Value);
	bool __fastcall ShouldDraw();
	
public:
	__fastcall virtual TChartTitle(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall Clicked(int x, int y)/* overload */;
	bool __fastcall Clicked(const System::Types::TPointF &P)/* overload */;
	void __fastcall DrawTitle();
	__property System::Types::TRectF TitleRect = {read=GetShapeBounds};
	
__published:
	__property bool AdjustFrame = {read=FAdjustFrame, write=SetAdjustFrame, default=1};
	__property Alignment = {default=2};
	__property Bevel = {default=0};
	__property BevelWidth = {default=2};
	__property Brush;
	__property Children;
	__property ChildLayout = {default=0};
	__property Color = {default=-1};
	__property CustomPosition;
	__property Emboss;
	__property Font;
	__property Frame;
	__property Gradient;
	__property Left;
	__property Picture;
	__property Shadow;
	__property ShapeCallout;
	__property ShapeStyle = {default=0};
	__property TextFormat = {default=0};
	__property Top;
	__property Transparency = {default=0};
	__property Transparent = {default=1};
	__property int VertMargin = {read=FVertMargin, write=SetVertMargin, default=5};
	__property Visible;
public:
	/* TStringsShape.Destroy */ inline __fastcall virtual ~TChartTitle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartFootTitle : public TChartTitle
{
	typedef TChartTitle inherited;
	
public:
	__fastcall virtual TChartFootTitle(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
public:
	/* TStringsShape.Destroy */ inline __fastcall virtual ~TChartFootTitle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TChartClick)(TCustomChart* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TChartClickAxis)(TCustomChart* Sender, Fmxtee::Engine::TChartAxis* Axis, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TChartClickSeries)(TCustomChart* Sender, Fmxtee::Engine::TChartSeries* Series, int ValueIndex, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TChartClickTitle)(TCustomChart* Sender, TChartTitle* ATitle, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TOnGetLegendPos)(TCustomChart* Sender, int Index, int &X, int &Y, int &XColor);

typedef void __fastcall (__closure *TOnGetLegendRect)(TCustomChart* Sender, System::Types::TRectF &Rect);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartBackWall : public TChartWall
{
	typedef TChartWall inherited;
	
protected:
	DYNAMIC void __fastcall InitEmboss(Fmxtee::Canvas::TTeeEmboss* const AEmboss);
	DYNAMIC void __fastcall InitShadow(Fmxtee::Canvas::TTeeShadow* const AShadow);
	
public:
	__fastcall virtual TChartBackWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */;
	
__published:
	__property Color = {default=-4144960};
	__property Emboss;
	__property Picture;
	__property Shadow;
	__property Transparent = {default=1};
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TChartBackWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartRightWall : public TChartWall
{
	typedef TChartWall inherited;
	
__published:
	__property Color = {default=-4144960};
	__property Picture;
	__property Visible = {default=0};
public:
	/* TCustomChartWall.Create */ inline __fastcall virtual TChartRightWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TChartWall(AOwner) { }
	
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TChartRightWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartBottomWall : public TChartWall
{
	typedef TChartWall inherited;
	
__published:
	__property Picture;
public:
	/* TCustomChartWall.Create */ inline __fastcall virtual TChartBottomWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TChartWall(AOwner) { }
	
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TChartBottomWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartLeftWall : public TChartWall
{
	typedef TChartWall inherited;
	
__published:
	__property Picture;
public:
	/* TCustomChartWall.Create */ inline __fastcall virtual TChartLeftWall(Fmxtee::Procs::TCustomTeePanel* const AOwner)/* overload */ : TChartWall(AOwner) { }
	
public:
	/* TTeeCustomShape.Destroy */ inline __fastcall virtual ~TChartLeftWall() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartWalls : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TChartBackWall* FBack;
	TChartBottomWall* FBottom;
	TCustomChart* FChart;
	TChartLeftWall* FLeft;
	TChartRightWall* FRight;
	TChartRightWall* __fastcall GetRight();
	bool __fastcall GetVisible();
	void __fastcall SetBack(TChartBackWall* const Value);
	void __fastcall SetBottom(TChartBottomWall* const Value);
	void __fastcall SetLeft(TChartLeftWall* const Value);
	void __fastcall SetRight(TChartRightWall* const Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetVisible(const bool Value);
	
public:
	__fastcall TChartWalls(TCustomChart* const Chart);
	__fastcall virtual ~TChartWalls();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Hide();
	void __fastcall Show();
	__property TChartBackWall* Back = {read=FBack, write=SetBack};
	__property TChartBottomWall* Bottom = {read=FBottom, write=SetBottom};
	__property TChartLeftWall* Left = {read=FLeft, write=SetLeft};
	__property TChartRightWall* Right = {read=GetRight, write=SetRight};
	__property int Size = {write=SetSize, nodefault};
	__property bool Visible = {read=GetVisible, write=SetVisible, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TChartAllowScrollEvent)(Fmxtee::Engine::TChartAxis* Sender, double &AMin, double &AMax, bool &AllowScroll);

class PASCALIMPLEMENTATION TCustomChart : public Fmxtee::Engine::TCustomAxisPanel
{
	typedef Fmxtee::Engine::TCustomAxisPanel inherited;
	
private:
	int FColorPaletteIndex;
	TChartTitle* FFoot;
	TChartLegend* FLegend;
	TAllAxisSavedScales FSavedScales;
	TChartTitle* FSubFoot;
	TChartTitle* FSubTitle;
	TChartTitle* FTitle;
	TChartWalls* FWalls;
	TChartAllowScrollEvent FOnAllowScroll;
	TChartClickAxis FOnClickAxis;
	TChartClick FOnClickBackGround;
	TChartClick FOnClickLegend;
	TChartClickSeries FOnClickSeries;
	TChartClickTitle FOnClickTitle;
	TOnGetLegendPos FOnGetLegendPos;
	TOnGetLegendRect FOnGetLegendRect;
	TOnGetLegendText FOnGetLegendText;
	bool __fastcall ActiveSeriesUseAxis();
	bool __fastcall ActiveSeriesCanZoomScroll();
	HIDESBASE void __fastcall BroadcastMouseEvent(Fmxtee::Engine::TChartMouseEvent AEvent, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall BroadcastWheelEvent(Fmxtee::Engine::TWheelMouseEvent AEvent, int WheelDelta, int X, int Y);
	void __fastcall BroadcastDragDropEvent(Fmxtee::Engine::TChartDragDropEvent AEvent, System::TObject* Source, int X, int Y, Fmxtee::Engine::TDragState State, bool &Accept, Fmx::Types::TDragObject &DragObject);
	void __fastcall BroadcastKeyEvent(Fmxtee::Engine::TChartKeyEvent AEvent, System::Word &Key, System::WideChar &Key1, System::Classes::TShiftState Shift);
	Fmxtee::Engine::TChartClickedPart __fastcall CalcNeedClickedPart(const System::Types::TPointF &Pos, bool Needed);
	bool __fastcall CanWheelScroll();
	void __fastcall DrawBackWall();
	void __fastcall DrawLeftWall();
	void __fastcall DrawRightWall();
	bool __fastcall DrawWallFirst(int APos);
	TChartBackWall* __fastcall GetBackWall();
	TChartBottomWall* __fastcall GetBottomWall();
	TChartTitle* __fastcall GetFoot();
	Fmxtee::Canvas::TTeePen* __fastcall GetFrame();
	TChartLeftWall* __fastcall GetLeftWall();
	TChartRightWall* __fastcall GetRightWall();
	TChartTitle* __fastcall GetSubFoot();
	TChartTitle* __fastcall GetSubTitle();
	TChartTitle* __fastcall GetTitle();
	void __fastcall InternalWheel(int WheelDelta);
	void __fastcall PrepareWallCanvas(TChartWall* const AWall);
	void __fastcall ReadBackColor(System::Classes::TReader* Reader);
	void __fastcall ReadColorPalette(System::Classes::TReader* Reader);
	void __fastcall ReadColorPaletteIndex(System::Classes::TReader* Reader);
	void __fastcall RestoreScales(TAllAxisSavedScales &Saved);
	TAllAxisSavedScales __fastcall SaveScales();
	void __fastcall ScrollVerticalAxes(bool Up);
	void __fastcall SetBackColor(System::Uitypes::TAlphaColor Value);
	void __fastcall SetBackWall(TChartBackWall* const Value);
	void __fastcall SetBottomWall(TChartBottomWall* const Value);
	void __fastcall SetColorPaletteIndex(const int Value);
	void __fastcall SetFoot(TChartTitle* const Value);
	void __fastcall SetFrame(Fmxtee::Canvas::TTeePen* const Value);
	void __fastcall SetLeftWall(TChartLeftWall* const Value);
	void __fastcall SetLegend(TChartLegend* const Value);
	void __fastcall SetRightWall(TChartRightWall* const Value);
	void __fastcall SetSubFoot(TChartTitle* const Value);
	void __fastcall SetSubTitle(TChartTitle* const Value);
	void __fastcall SetTitle(TChartTitle* const Value);
	void __fastcall SetWalls(TChartWalls* const Value);
	void __fastcall WriteColorPalette(System::Classes::TWriter* Writer);
	void __fastcall WriteColorPaletteIndex(System::Classes::TWriter* Writer);
	void __fastcall AddZoomSnapshot();
	void __fastcall RemoveZoomSnapshot();
	void __fastcall ZoomBackOne();
	
protected:
	bool RestoredAxisScales;
	virtual void __fastcall CalcWallsRect();
	virtual int __fastcall CalcWallSize(Fmxtee::Engine::TChartAxis* Axis);
	DYNAMIC void __fastcall CalcZoomPoints();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	void __fastcall DoZoom(const double TopI, const double TopF, const double BotI, const double BotF, const double LefI, const double LefF, const double RigI, const double RigF);
	bool __fastcall DrawLeftWallFirst();
	bool __fastcall DrawRightWallAfter();
	virtual void __fastcall DrawLegendShape(const System::Types::TRectF &Rect);
	virtual void __fastcall DrawTitlesAndLegend(bool BeforeSeries);
	virtual void __fastcall DrawWalls();
	DYNAMIC System::TClass __fastcall Form3DClass();
	virtual System::Uitypes::TAlphaColor __fastcall GetBackColor();
	virtual void __fastcall InternalDraw(const System::Types::TRectF &UserRectangle);
	System::UnicodeString __fastcall InternalFormattedLegend(TCustomChartLegend* const ALegend, int SeriesOrValueIndex);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall BeginAutoDrag();
	virtual void __fastcall DragDrop(const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point);
	virtual void __fastcall DragEnd();
	virtual void __fastcall DragOver(const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point, Fmx::Types::TDragOperation &Operation);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall KeyUp(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	__property Action;
	__property Anchors;
	
public:
	__fastcall virtual TCustomChart(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomChart();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::UnicodeString __fastcall AxisTitleOrName(Fmxtee::Engine::TChartAxis* const Axis);
	void __fastcall CalcClickedPart(const System::Types::TPointF &Pos, /* out */ Fmxtee::Engine::TChartClickedPart &Part);
	DYNAMIC void __fastcall FillSeriesSourceItems(Fmxtee::Engine::TChartSeries* ASeries, System::Classes::TGetStrProc Proc);
	DYNAMIC void __fastcall FillValueSourceItems(Fmxtee::Engine::TChartValueList* ValueList, System::Classes::TGetStrProc Proc);
	Fmxtee::Engine::TChartSeries* __fastcall GetASeries();
	DYNAMIC void __fastcall GetChildren(System::Classes::TGetChildProc Proc, System::Classes::TComponent* Root);
	virtual bool __fastcall IsFreeSeriesColor(System::Uitypes::TAlphaColor AColor, bool CheckBackground, Fmxtee::Engine::TChartSeries* ASeries = (Fmxtee::Engine::TChartSeries*)(0x0));
	void __fastcall NextPage();
	void __fastcall PreviousPage();
	void __fastcall RemoveAllSeries();
	void __fastcall ClearChart();
	void __fastcall SeriesDown(Fmxtee::Engine::TChartSeries* const ASeries);
	void __fastcall SeriesUp(Fmxtee::Engine::TChartSeries* const ASeries);
	DYNAMIC void __fastcall UndoZoom();
	void __fastcall ZoomPercent(const double PercentZoom);
	void __fastcall ZoomRect(const System::Types::TRectF &Rect);
	virtual System::UnicodeString __fastcall FormattedValueLegend(Fmxtee::Engine::TChartSeries* ASeries, int ValueIndex);
	System::UnicodeString __fastcall FormattedLegend(int SeriesOrValueIndex);
	__property System::Uitypes::TAlphaColor BackColor = {read=GetBackColor, write=SetBackColor, nodefault};
	__property int ColorPaletteIndex = {read=FColorPaletteIndex, write=SetColorPaletteIndex, default=-1};
	__property TChartWalls* Walls = {read=FWalls, write=SetWalls};
	__property TChartBackWall* BackWall = {read=GetBackWall, write=SetBackWall};
	__property Fmxtee::Canvas::TTeePen* Frame = {read=GetFrame, write=SetFrame};
	__property TChartBottomWall* BottomWall = {read=GetBottomWall, write=SetBottomWall};
	__property TChartTitle* Foot = {read=GetFoot, write=SetFoot};
	__property TChartLeftWall* LeftWall = {read=GetLeftWall, write=SetLeftWall};
	__property TChartLegend* Legend = {read=FLegend, write=SetLegend};
	__property TChartRightWall* RightWall = {read=GetRightWall, write=SetRightWall};
	__property TChartTitle* SubFoot = {read=GetSubFoot, write=SetSubFoot};
	__property TChartTitle* SubTitle = {read=GetSubTitle, write=SetSubTitle};
	__property TChartTitle* Title = {read=GetTitle, write=SetTitle};
	__property TChartAllowScrollEvent OnAllowScroll = {read=FOnAllowScroll, write=FOnAllowScroll};
	__property TChartClickAxis OnClickAxis = {read=FOnClickAxis, write=FOnClickAxis};
	__property TChartClick OnClickBackground = {read=FOnClickBackGround, write=FOnClickBackGround};
	__property TChartClick OnClickLegend = {read=FOnClickLegend, write=FOnClickLegend};
	__property TChartClickSeries OnClickSeries = {read=FOnClickSeries, write=FOnClickSeries};
	__property TChartClickTitle OnClickTitle = {read=FOnClickTitle, write=FOnClickTitle};
	__property TOnGetLegendPos OnGetLegendPos = {read=FOnGetLegendPos, write=FOnGetLegendPos};
	__property TOnGetLegendRect OnGetLegendRect = {read=FOnGetLegendRect, write=FOnGetLegendRect};
	__property TOnGetLegendText OnGetLegendText = {read=FOnGetLegendText, write=FOnGetLegendText};
	__property Align = {default=0};
	__property BevelInner = {default=0};
	__property BevelOuter = {default=2};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property Color = {default=-986896};
	__property DragMode = {default=0};
	__property Enabled;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property Visible = {default=1};
	__property ClipChildren = {default=1};
	__property Locked = {default=0};
	__property OnClick;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnEnter;
	__property OnExit;
	__property OnPainting;
	__property OnPaint;
	__property OnApplyStyleLookup;
	__property OnCanFocus;
	__property OnDblClick;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
};


class PASCALIMPLEMENTATION TChart : public TCustomChart
{
	typedef TCustomChart inherited;
	
__published:
	__property AllowPanning = {default=3};
	__property BackImage;
	__property BackImageInside = {default=0};
	__property BackImageMode = {default=0};
	__property BackImageTransp = {default=1};
	__property BackWall;
	__property Border;
	__property BorderRound = {default=0};
	__property BottomWall;
	__property Foot;
	__property Gradient;
	__property LeftWall;
	__property Legend;
	__property MarginBottom = {index=3, default=4};
	__property MarginLeft = {index=0, default=3};
	__property MarginRight = {index=2, default=3};
	__property MarginTop = {index=1, default=4};
	__property MarginUnits = {default=0};
	__property PrintProportional = {default=1};
	__property RightWall;
	__property ScrollMouseButton = {default=1};
	__property SubFoot;
	__property SubTitle;
	__property Title;
	__property OnAllowScroll;
	__property OnClickAxis;
	__property OnClickBackground;
	__property OnClickLegend;
	__property OnClickSeries;
	__property OnClickTitle;
	__property OnGetLegendPos;
	__property OnGetLegendRect;
	__property OnScroll;
	__property OnUndoZoom;
	__property OnZoom;
	__property Animations;
	__property AxisBehind = {default=1};
	__property AxisVisible = {default=1};
	__property BottomAxis;
	__property Chart3DPercent = {default=15};
	__property ClipPoints = {default=1};
	__property DepthAxis;
	__property DepthTopAxis;
	__property CustomAxes;
	__property Emboss;
	__property Frame;
	__property Hover;
	__property LeftAxis;
	__property Monochrome = {default=0};
	__property Pages;
	__property Panning;
	__property RightAxis;
	__property SeriesGroups;
	__property SeriesList;
	__property Shadow;
	__property Tools;
	__property TopAxis;
	__property View3D = {default=1};
	__property View3DOptions;
	__property View3DWalls = {default=1};
	__property Zoom;
	__property ZoomWheel = {default=2};
	__property OnAddSeries;
	__property OnAfterDraw;
	__property OnBeforeDrawAxes;
	__property OnBeforeDrawChart;
	__property OnBeforeDrawSeries;
	__property OnBeforePrint;
	__property OnGetAxisLabel;
	__property OnGetLegendText;
	__property OnGetNextAxisLabel;
	__property OnPageChange;
	__property OnRemoveSeries;
	__property OnValidDataSource;
	__property Align = {default=0};
	__property BevelInner = {default=0};
	__property BevelOuter = {default=2};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property Color = {default=-986896};
	__property ParentShowHint = {default=1};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnEnter;
	__property OnExit;
	__property OnPainting;
	__property OnPaint;
	__property OnApplyStyleLookup;
	__property OnCanFocus;
	__property ClipChildren = {default=1};
	__property Locked = {default=0};
	__property Enabled;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property Visible = {default=1};
	__property Action;
	__property Anchors;
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Height;
	__property HitTest = {default=1};
	__property Margins;
	__property Opacity;
	__property Padding;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property Width;
	__property OnClick;
	__property OnDblClick;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
	__property OnMouseWheel;
public:
	/* TCustomChart.Create */ inline __fastcall virtual TChart(System::Classes::TComponent* AOwner) : TCustomChart(AOwner) { }
	/* TCustomChart.Destroy */ inline __fastcall virtual ~TChart() { }
	
};


class PASCALIMPLEMENTATION TTeeSeriesTypes : public System::Generics::Collections::TList__1<Fmxtee::Engine::TTeeSeriesType*>
{
	typedef System::Generics::Collections::TList__1<Fmxtee::Engine::TTeeSeriesType*> inherited;
	
public:
	Fmxtee::Engine::TChartSeriesClass __fastcall Find(const System::UnicodeString ASeriesClass)/* overload */;
	Fmxtee::Engine::TTeeSeriesType* __fastcall Find(const Fmxtee::Engine::TChartSeriesClass ASeriesClass, int SubIndex = 0x0)/* overload */;
public:
	/* {System_Generics_Collections}TList<FMXTee_Engine_TTeeSeriesType>.Create */ inline __fastcall TTeeSeriesTypes()/* overload */ : System::Generics::Collections::TList__1<Fmxtee::Engine::TTeeSeriesType*>() { }
	/* {System_Generics_Collections}TList<FMXTee_Engine_TTeeSeriesType>.Create */ inline __fastcall TTeeSeriesTypes(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<Fmxtee::Engine::TTeeSeriesType*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<Fmxtee::Engine::TTeeSeriesType*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMXTee_Engine_TTeeSeriesType>.Create */ inline __fastcall TTeeSeriesTypes(System::Generics::Collections::TEnumerable__1<Fmxtee::Engine::TTeeSeriesType*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<Fmxtee::Engine::TTeeSeriesType*>(Collection) { }
	/* {System_Generics_Collections}TList<FMXTee_Engine_TTeeSeriesType>.Destroy */ inline __fastcall virtual ~TTeeSeriesTypes() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeToolTypes : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
public:
	Fmxtee::Engine::TTeeCustomToolClass operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE Fmxtee::Engine::TTeeCustomToolClass __fastcall Get(int Index);
	
public:
	__property Fmxtee::Engine::TTeeCustomToolClass Items[int Index] = {read=Get/*, default*/};
public:
	/* TList.Destroy */ inline __fastcall virtual ~TTeeToolTypes() { }
	
public:
	/* TObject.Create */ inline __fastcall TTeeToolTypes() : System::Classes::TList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomChartLink : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	void __fastcall SetChart(TCustomChart* const Value);
	
protected:
	TCustomChart* FChart;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__property TCustomChart* Chart = {read=FChart, write=SetChart};
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomChartLink(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomChartLink() { }
	
};


class PASCALIMPLEMENTATION TColorPalettes : public System::Classes::TStringList
{
	typedef System::Classes::TStringList inherited;
	
public:
	__classmethod void __fastcall AddTo(System::Classes::TStrings* const Items, bool AddDefault = false);
	__classmethod void __fastcall ApplyPalette(Fmxtee::Engine::TCustomAxisPanel* const Chart, int Index)/* overload */;
	__classmethod void __fastcall ApplyPalette(Fmxtee::Engine::TCustomAxisPanel* const Chart, const System::Uitypes::TAlphaColor *Palette, const int Palette_High)/* overload */;
	__classmethod void __fastcall GetPalette(int Index, /* out */ Fmxtee::Procs::TColorArray &Palette);
public:
	/* TStringList.Create */ inline __fastcall TColorPalettes()/* overload */ : System::Classes::TStringList() { }
	/* TStringList.Create */ inline __fastcall TColorPalettes(bool OwnsObjects)/* overload */ : System::Classes::TStringList(OwnsObjects) { }
	/* TStringList.Create */ inline __fastcall TColorPalettes(System::WideChar QuoteChar, System::WideChar Delimiter)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter) { }
	/* TStringList.Create */ inline __fastcall TColorPalettes(System::WideChar QuoteChar, System::WideChar Delimiter, System::Classes::TStringsOptions Options)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter, Options) { }
	/* TStringList.Create */ inline __fastcall TColorPalettes(System::Types::TDuplicates Duplicates, bool Sorted, bool CaseSensitive)/* overload */ : System::Classes::TStringList(Duplicates, Sorted, CaseSensitive) { }
	/* TStringList.Destroy */ inline __fastcall virtual ~TColorPalettes() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TTeeCanvasClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TTeeCanvasClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TChartThemeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TChartThemeClass);
#endif /* _WIN64 */

typedef TChartThemeClass __fastcall (*TTeeThemeSelectorProc)(TCustomChart* const Chart);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChartTheme : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	TCustomChart* Chart;
	__fastcall virtual TChartTheme(TCustomChart* AChart);
	virtual void __fastcall Apply();
	virtual System::UnicodeString __fastcall Description();
	virtual void __fastcall SetDefaultValues();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TChartTheme() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define TeeMsg_DefaultFunctionName L"TeeFunction"
#define TeeMsg_DefaultSeriesName L"Series"
#define TeeMsg_DefaultToolName L"ChartTool"
#define TeeMsg_DefaultAnimationName L"ChartAnimation"
#define ChartComponentPalette L"TeeChart"
static const System::Int8 TeeMaxLegendColumns = System::Int8(0x3);
static const System::Int8 TeeDefaultLegendSymbolHeight = System::Int8(0x64);
static const System::Int8 TeeDefaultLegendSymbolWidth = System::Int8(0x14);
static const System::Int8 TeeTitleFootDistance = System::Int8(0x5);
extern DELPHI_PACKAGE double AnimatedZoomFactor;
extern DELPHI_PACKAGE System::Classes::TShiftState TeeScrollKeyShift;
extern DELPHI_PACKAGE TColorPalettes* ColorPalettes;
extern DELPHI_PACKAGE TTeeSeriesTypes* TeeSeriesTypes;
extern DELPHI_PACKAGE TTeeToolTypes* TeeToolTypes;
extern DELPHI_PACKAGE TTeeToolTypes* TeeAnimationTypes;
extern DELPHI_PACKAGE Fmxtee::Engine::TTeeCustomToolClass TeePageNumToolClass;
extern DELPHI_PACKAGE TTeeThemeSelectorProc TeeThemeSelectorHook;
extern DELPHI_PACKAGE TTeeThemeSelectorProc TeeNewChartHook;
extern DELPHI_PACKAGE TTeeCanvasClass TeeAntiAliasCanvas;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 22> ExcelPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 11> VictorianPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 14> PastelsPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 8> SolidPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 12> ClassicPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 9> WebPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 14> ModernPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 25> RainbowPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 13> WindowsXPPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 16> MacOSPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 15> WindowsVistaPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 15> GrayScalePalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 12> OperaPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 8> WarmPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 8> CoolPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 4> OnBlackPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 10> MetroPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 12> iOSPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 15> AndroidPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 12> LookoutPalette;
extern DELPHI_PACKAGE System::StaticArray<System::Uitypes::TAlphaColor, 12> SeawashPalette;
extern DELPHI_PACKAGE void __fastcall PaintSeriesLegend(Fmxtee::Engine::TChartSeries* const ASeries, Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &R);
extern DELPHI_PACKAGE System::Classes::TComponentName __fastcall GetNewSeriesName(System::Classes::TComponent* const AOwner);
extern DELPHI_PACKAGE void __fastcall AssignSeries(Fmxtee::Engine::TChartSeries* &OldSeries, Fmxtee::Engine::TChartSeries* &NewSeries);
extern DELPHI_PACKAGE Fmxtee::Engine::TTeeFunction* __fastcall CreateNewTeeFunction(Fmxtee::Engine::TChartSeries* const ASeries, Fmxtee::Engine::TTeeFunctionClass AClass);
extern DELPHI_PACKAGE Fmxtee::Engine::TChartSeries* __fastcall CreateNewSeries(System::Classes::TComponent* AOwner, Fmxtee::Engine::TCustomAxisPanel* const AChart, Fmxtee::Engine::TChartSeriesClass AClass, Fmxtee::Engine::TTeeFunctionClass AFunctionClass = 0x0);
extern DELPHI_PACKAGE Fmxtee::Engine::TChartSeries* __fastcall CloneChartSeries(Fmxtee::Engine::TChartSeries* const ASeries)/* overload */;
extern DELPHI_PACKAGE Fmxtee::Engine::TChartSeries* __fastcall CloneChartSeries(Fmxtee::Engine::TChartSeries* const ASeries, Fmxtee::Engine::TCustomAxisPanel* const AChart)/* overload */;
extern DELPHI_PACKAGE Fmxtee::Engine::TChartSeries* __fastcall CloneChartSeries(Fmxtee::Engine::TChartSeries* const ASeries, System::Classes::TComponent* const AOwner, Fmxtee::Engine::TCustomAxisPanel* const AChart)/* overload */;
extern DELPHI_PACKAGE Fmxtee::Engine::TTeeCustomTool* __fastcall CloneChartTool(Fmxtee::Engine::TTeeCustomTool* const ATool, System::Classes::TComponent* const AOwner);
extern DELPHI_PACKAGE Fmxtee::Engine::TTeeCustomAnimation* __fastcall CloneChartAnimation(Fmxtee::Engine::TTeeCustomAnimation* const AAnimation, System::Classes::TComponent* const AOwner);
extern DELPHI_PACKAGE void __fastcall CloneChart(TCustomChart* const Dest, TCustomChart* const Origin, System::Classes::TComponent* const AOwner, bool ForceManualData);
extern DELPHI_PACKAGE Fmxtee::Engine::TChartSeries* __fastcall ChangeSeriesType(Fmxtee::Engine::TChartSeries* &ASeries, Fmxtee::Engine::TChartSeriesClass NewType);
extern DELPHI_PACKAGE void __fastcall ChangeAllSeriesType(TCustomChart* const AChart, Fmxtee::Engine::TChartSeriesClass AClass);
extern DELPHI_PACKAGE void __fastcall RegisterTeeSeriesFunction(Fmxtee::Engine::TChartSeriesClass ASeriesClass, Fmxtee::Engine::TTeeFunctionClass AFunctionClass, System::PUnicodeString ADescription, System::PUnicodeString AGalleryPage, int ANumGallerySeries = 0x1, int ASubIndex = 0x0);
extern DELPHI_PACKAGE void __fastcall RegisterTeeSeries(Fmxtee::Engine::TChartSeriesClass ASeriesClass, System::PUnicodeString ADescription, System::PUnicodeString AGalleryPage, int ANumGallerySeries)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterTeeSeries(Fmxtee::Engine::TChartSeriesClass ASeriesClass, System::PUnicodeString ADescription)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterTeeFunction(Fmxtee::Engine::TTeeFunctionClass AFunctionClass, System::PUnicodeString ADescription, System::PUnicodeString AGalleryPage, int ANumGallerySeries = 0x1);
extern DELPHI_PACKAGE void __fastcall RegisterTeeBasicFunction(Fmxtee::Engine::TTeeFunctionClass AFunctionClass, System::PUnicodeString ADescription);
extern DELPHI_PACKAGE void __fastcall UnRegisterTeeSeries(Fmxtee::Engine::TChartSeriesClass const *ASeriesList, const int ASeriesList_High);
extern DELPHI_PACKAGE void __fastcall UnRegisterTeeFunctions(Fmxtee::Engine::TTeeFunctionClass const *AFunctionList, const int AFunctionList_High);
extern DELPHI_PACKAGE void __fastcall RegisterTeeTools(Fmxtee::Engine::TTeeCustomToolClass const *ATools, const int ATools_High);
extern DELPHI_PACKAGE void __fastcall UnRegisterTeeTools(Fmxtee::Engine::TTeeCustomToolClass const *ATools, const int ATools_High);
extern DELPHI_PACKAGE void __fastcall RegisterTeeAnimations(Fmxtee::Engine::TTeeCustomAnimationClass const *AAnimations, const int AAnimations_High);
extern DELPHI_PACKAGE void __fastcall UnRegisterTeeAnimations(Fmxtee::Engine::TTeeCustomAnimationClass const *AAnimations, const int AAnimations_High);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetGallerySeriesName(Fmxtee::Engine::TChartSeries* const ASeries);
}	/* namespace Chart */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART)
using namespace Fmxtee::Chart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_ChartHPP
