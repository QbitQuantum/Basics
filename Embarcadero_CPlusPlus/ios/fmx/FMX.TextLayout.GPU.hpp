// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.TextLayout.GPU.pas' rev: 34.00 (iOS)

#ifndef Fmx_Textlayout_GpuHPP
#define Fmx_Textlayout_GpuHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Types.hpp>
#include <FMX.TextLayout.hpp>
#include <FMX.FontGlyphs.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Textlayout
{
namespace Gpu
{
//-- forward type declarations -----------------------------------------------
struct TCharRec;
class DELPHICLASS TCharDic;
class DELPHICLASS TFamilyDic;
class DELPHICLASS TReusableObject;
template<typename T> class DELPHICLASS TReusableList__1;
class DELPHICLASS TGPUObjectsPool;
class DELPHICLASS TGPURun;
class DELPHICLASS TGPULine;
class DELPHICLASS TGPUFrame;
class DELPHICLASS TGlyphsManager;
class DELPHICLASS TGPUTextLayout;
class DELPHICLASS TPartContext;
class DELPHICLASS TLineReader;
class DELPHICLASS TFrameRender;
//-- type declarations -------------------------------------------------------
typedef TCharRec *PCharRec;

struct DECLSPEC_DRECORD TCharRec
{
public:
	Fmx::Fontglyphs::TFontGlyph* Glyph;
	System::Types::TRectF SrcRect;
	Fmx::Graphics::TBitmap* Bitmap;
	bool BitmapRef;
	__fastcall TCharRec(Fmx::Fontglyphs::TFontGlyph* const AGlyph);
	bool __fastcall HasNoEmptyBitmap();
	TCharRec() {}
};


class PASCALIMPLEMENTATION TCharDic : public System::Generics::Collections::TDictionary__2<System::UCS4String,PCharRec>
{
	typedef System::Generics::Collections::TDictionary__2<System::UCS4String,PCharRec> inherited;
	
private:
	float FBaseline;
	void __fastcall CharRecNotifyHandler(System::TObject* Sender, const PCharRec Value, System::Generics::Collections::TCollectionNotification Action);
	
public:
	__fastcall TCharDic(int ACapacity);
	__property float Baseline = {read=FBaseline, write=FBaseline};
public:
	/* {System_Generics_Collections}TDictionary<System_UCS4String,FMX_TextLayout_GPU_PCharRec>.Destroy */ inline __fastcall virtual ~TCharDic() { }
	
};


class PASCALIMPLEMENTATION TFamilyDic : public System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>
{
	typedef System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(System::Generics::Collections::TDictionaryOwnerships Ownerships, int ACapacity)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(Ownerships, ACapacity) { }
	/* {System_Generics_Collections}TObjectDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(System::Generics::Collections::TDictionaryOwnerships Ownerships, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<__int64> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(Ownerships, AComparer) { }
	/* {System_Generics_Collections}TObjectDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(System::Generics::Collections::TDictionaryOwnerships Ownerships, int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<__int64> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(Ownerships, ACapacity, AComparer) { }
	
public:
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic()/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>() { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(int ACapacity)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(ACapacity) { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<__int64> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<__int64> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(ACapacity, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<__int64,TCharDic*> >* const Collection)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(Collection) { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Create */ inline __fastcall TFamilyDic(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<__int64,TCharDic*> >* const Collection, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<__int64> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<__int64,TCharDic*>(Collection, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Int64,FMX_TextLayout_GPU_TCharDic>.Destroy */ inline __fastcall virtual ~TFamilyDic() { }
	
};


class PASCALIMPLEMENTATION TReusableObject : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall Init();
	
public:
	template<typename T> __classmethod T __fastcall CreateObject();
	void __fastcall DestroyObject();
public:
	/* TObject.Create */ inline __fastcall TReusableObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TReusableObject() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TReusableObjectClass);

// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TReusableList__1 : public TReusableObject
{
	typedef TReusableObject inherited;
	
public:
	T operator[](const int AIndex) { return this->Items[AIndex]; }
	
private:
	System::Generics::Collections::TList__1<T>* FItems;
	int __fastcall GetCount();
	T __fastcall GetItems(const int AIndex);
	void __fastcall NotifyEventHandler(System::TObject* Sender, const T Item, System::Generics::Collections::TCollectionNotification Action);
	
protected:
	virtual void __fastcall Init();
	
public:
	__fastcall TReusableList__1();
	__fastcall virtual ~TReusableList__1();
	T __fastcall Add();
	void __fastcall Delete(const int AIndex);
	void __fastcall DeleteRange(const int AIndex, const int ACount);
	void __fastcall Remove(const T AItem);
	void __fastcall Insert(const int AIndex, const T AItem);
	T __fastcall First();
	T __fastcall Last();
	__property T Items[const int AIndex] = {read=GetItems/*, default*/};
	__property int Count = {read=GetCount, nodefault};
};


class PASCALIMPLEMENTATION TGPUObjectsPool : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TGPUObjectsPool* FInstance;
	static bool FDisabled;
	static TGPUObjectsPool* __fastcall GetInstance();
	static void __fastcall SetDisabled(const bool Value);
	
private:
	// __classmethod void __fastcall Create@();
	
private:
	System::Generics::Collections::TDictionary__2<System::TClass,System::Generics::Collections::TObjectList__1<TReusableObject*>*>* FStorage;
	
public:
	__fastcall TGPUObjectsPool();
	__fastcall virtual ~TGPUObjectsPool();
	template<typename T> T __fastcall GetObject();
	void __fastcall ReturnObject(TReusableObject* const AObject);
	__classmethod bool __fastcall IsAvailable();
	__classmethod void __fastcall Uninitialize();
	/* static */ __property TGPUObjectsPool* Instance = {read=GetInstance};
	/* static */ __property bool Disabled = {read=FDisabled, write=SetDisabled, nodefault};
	
private:
	// __classmethod void __fastcall Destroy@();
};


class PASCALIMPLEMENTATION TGPURun : public TReusableObject
{
	typedef TReusableObject inherited;
	
private:
	System::Generics::Collections::TList__1<System::UCS4String>* FChars;
	System::Generics::Collections::TList__1<System::Types::TSizeF>* FGlyphs;
	int FStartIndex;
	int FLength;
	System::Types::TRectF FImageRect;
	System::Uitypes::TAlphaColor FColor;
	Fmx::Graphics::TFont* FFont;
	bool FIsDefaultColor;
	bool FClipped;
	float FBaseline;
	int __fastcall GetEndIndex();
	float __fastcall GetWidth();
	float __fastcall GetHeight();
	
protected:
	virtual void __fastcall Init();
	
public:
	__fastcall TGPURun();
	__fastcall virtual ~TGPURun();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor AColor, const bool AIsDefault);
	void __fastcall Clip();
	void __fastcall SetText(const System::UnicodeString AText, const int AStartIndex, const int ALength);
	void __fastcall AddChar(const System::UCS4String AChar, const System::Types::TSizeF &AGlyphSize, const int ALength)/* overload */;
	void __fastcall DeleteLastChar();
	void __fastcall NormalizeHeight();
	__property System::Generics::Collections::TList__1<System::UCS4String>* Chars = {read=FChars};
	__property System::Generics::Collections::TList__1<System::Types::TSizeF>* Glyphs = {read=FGlyphs};
	__property int StartIndex = {read=FStartIndex, nodefault};
	__property int EndIndex = {read=GetEndIndex, nodefault};
	__property int Length = {read=FLength, nodefault};
	__property System::Types::TRectF ImageRect = {read=FImageRect, write=FImageRect};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, nodefault};
	__property bool IsDefaultColor = {read=FIsDefaultColor, nodefault};
	__property Fmx::Graphics::TFont* Font = {read=FFont, write=FFont};
	__property bool IsClipped = {read=FClipped, nodefault};
	__property float Baseline = {read=FBaseline, write=FBaseline};
	__property float Width = {read=GetWidth};
	__property float Height = {read=GetHeight};
};


class PASCALIMPLEMENTATION TGPULine : public TReusableList__1<TGPURun*>
{
	typedef TReusableList__1<TGPURun*> inherited;
	
private:
	float FHeight;
	float FWidth;
	System::Types::TPointF FTopLeft;
	
protected:
	virtual void __fastcall Init();
	
public:
	bool __fastcall IsEmpty();
	float __fastcall CalculateBaseline();
	void __fastcall AdjustHeight();
	void __fastcall MarkAsClipped();
	__property float Height = {read=FHeight, write=FHeight};
	__property float Width = {read=FWidth, write=FWidth};
	__property System::Types::TPointF TopLeft = {read=FTopLeft, write=FTopLeft};
public:
	/* {FMX_TextLayout_GPU}TReusableList<FMX_TextLayout_GPU_TGPURun>.Create */ inline __fastcall TGPULine() : TReusableList__1<TGPURun*>() { }
	/* {FMX_TextLayout_GPU}TReusableList<FMX_TextLayout_GPU_TGPURun>.Destroy */ inline __fastcall virtual ~TGPULine() { }
	
};


class PASCALIMPLEMENTATION TGPUFrame : public TReusableList__1<TGPULine*>
{
	typedef TReusableList__1<TGPULine*> inherited;
	
private:
	float FHeight;
	float FWidth;
	System::Types::TPointF FTopLeft;
	
protected:
	virtual void __fastcall Init();
	
public:
	void __fastcall ApplyDefaultColor(const System::Uitypes::TAlphaColor AColor);
	__property System::Types::TPointF TopLeft = {read=FTopLeft, write=FTopLeft};
	__property float Height = {read=FHeight, write=FHeight};
	__property float Width = {read=FWidth, write=FWidth};
public:
	/* {FMX_TextLayout_GPU}TReusableList<FMX_TextLayout_GPU_TGPULine>.Create */ inline __fastcall TGPUFrame() : TReusableList__1<TGPULine*>() { }
	/* {FMX_TextLayout_GPU}TReusableList<FMX_TextLayout_GPU_TGPULine>.Destroy */ inline __fastcall virtual ~TGPUFrame() { }
	
};


class PASCALIMPLEMENTATION TGlyphsManager : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TCharMap;
	class PASCALIMPLEMENTATION TCharMap : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		Fmx::Graphics::TBitmap* Texture;
		Fmx::Types::TGuillotineBinPack* BinPack;
		__fastcall TCharMap(const float AScale);
		__fastcall virtual ~TCharMap();
	};
	
	
	typedef System::Generics::Collections::TObjectList__1<TCharMap*>* TCharMaps;
	
	
public:
	static constexpr System::Int8 AntialiasMargin = System::Int8(0x1);
	
	#define TGlyphsManager_MaxUsefulCharMapOccupancy  (9.500000E-01)
	
	
private:
	static TGlyphsManager* FDefault;
	static TGlyphsManager* __fastcall GetDefault();
	TFamilyDic* FFamilyDic;
	System::Generics::Collections::TObjectList__1<TCharMap*>* FCharMaps;
	int FRendering;
	System::Generics::Collections::TList__1<PCharRec>* FNewGlyphList;
	bool FDisableGlyphPopulation;
	PCharRec __fastcall AddCharacterGlyph(const System::UCS4String ACharacter, Fmx::Graphics::TFont* const AFont, const float AScale, const bool APathPresentation);
	void __fastcall UpdateCharacterGlyph(PCharRec &AGlyphRec, const System::UCS4String ACharacter, Fmx::Graphics::TFont* const AFont, const float AScale, const bool APathPresentation);
	void __fastcall PutGlyphToCharMaps(const PCharRec ACharRec);
	__classmethod __int64 __fastcall FontToId(Fmx::Graphics::TFont* const AFont, const float AScale);
	
public:
	__fastcall TGlyphsManager();
	__fastcall virtual ~TGlyphsManager();
	PCharRec __fastcall GetCharGlyph(const System::UCS4String ACharacter, Fmx::Graphics::TFont* const AFont, const float AScale, const bool APathPresentation = false)/* overload */;
	PCharRec __fastcall GetCharGlyph(TCharDic* const CharDic, const System::UCS4String ACharacter, Fmx::Graphics::TFont* const AFont, const float AScale, const bool APathPresentation = false)/* overload */;
	TCharDic* __fastcall GetCharDictionary(Fmx::Graphics::TFont* const AFont, const float AScale);
	void __fastcall BeginRender();
	void __fastcall EndRender();
	__property bool DisableGlyphPopulation = {read=FDisableGlyphPopulation, write=FDisableGlyphPopulation, nodefault};
	__property System::Generics::Collections::TObjectList__1<TCharMap*>* CharMaps = {read=FCharMaps};
	__classmethod void __fastcall Uninitialize();
	/* static */ __property TGlyphsManager* Default = {read=GetDefault};
};


class PASCALIMPLEMENTATION TGPUTextLayout : public Fmx::Textlayout::TTextLayout
{
	typedef Fmx::Textlayout::TTextLayout inherited;
	
public:
	static bool DebugDrawGlyphBounds;
	static bool DebugDrawTextBounds;
	
private:
	TGPUFrame* FFrame;
	TFrameRender* FRender;
	bool FNeedUpdateColor;
	float FScale;
	float FScaleFactor;
	float __fastcall GetGlyphAdvance(const PCharRec ARec);
	Fmx::Graphics::TRegion __fastcall MeasureRange(int APos, int ALength);
	TCharDic* __fastcall GetCharDictionary(Fmx::Graphics::TFont* const AFont = (Fmx::Graphics::TFont*)(0x0));
	PCharRec __fastcall GetCharGlyph(const System::UCS4String Ch, TCharDic* const CharDic, Fmx::Graphics::TFont* const AFont, const bool NeedPath = false);
	TFrameRender* __fastcall GetRender();
	void __fastcall UpdateDefaultColor();
	
protected:
	virtual void __fastcall DoRenderLayout();
	virtual void __fastcall DoDrawLayout(Fmx::Graphics::TCanvas* const ACanvas);
	virtual void __fastcall DoColorChanaged();
	virtual float __fastcall GetTextHeight();
	virtual float __fastcall GetTextWidth();
	virtual System::Types::TRectF __fastcall GetTextRect();
	virtual int __fastcall DoPositionAtPoint(const System::Types::TPointF &APoint);
	virtual Fmx::Graphics::TRegion __fastcall DoRegionForRange(const Fmx::Textlayout::TTextRange &ARange);
	void __fastcall ReleaseFrames();
	
public:
	__fastcall virtual TGPUTextLayout(Fmx::Graphics::TCanvas* const ACanvas);
	__fastcall virtual ~TGPUTextLayout();
	__classmethod void __fastcall Uninitialize();
	virtual void __fastcall ConvertToPath(Fmx::Graphics::TPathData* const APath);
	__property TFrameRender* Render = {read=GetRender};
};


enum class DECLSPEC_DENUM TGPURunAction : unsigned int { BeginNewRun, Continue };

class PASCALIMPLEMENTATION TPartContext : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int BeginIndex;
	System::Generics::Collections::TList__1<System::Types::TSizeF>* Sizes;
	System::Generics::Collections::TList__1<int>* AttributesIndex;
	System::Generics::Collections::TList__1<TGPURunAction>* RunsActions;
	float Width;
	float TrimmedWidth;
	int LeftSpacesCount;
	bool IsLastSpace;
	__fastcall TPartContext();
	__fastcall virtual ~TPartContext();
	void __fastcall AddSize(const System::Types::TSizeF &ASize, const int AAttributeIndex, const TGPURunAction AAction);
};


class PASCALIMPLEMENTATION TLineReader : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::UCS4String EllipsisChar;
	
private:
	System::Generics::Collections::TList__1<System::UCS4String>* FCharacters;
	System::Generics::Collections::TList__1<int>* FCharactersOffsets;
	System::Generics::Collections::TList__1<int>* FLineBreaks;
	System::Generics::Collections::TList__1<int>* FLineBreaksLength;
	bool FWordWrap;
	Fmx::Types::TTextTrimming FTrimming;
	System::Uitypes::TAlphaColor FDefaultColor;
	float FScale;
	float FScaleFactor;
	Fmx::Graphics::TFont* FDefaultFont;
	System::Types::TSizeF FEllipsisGlyphSize;
	System::Types::TSizeF FDefaultLineSize;
	System::Types::TSizeF FMaxSize;
	System::UCS4String FLineBreakChars;
	int FCharacterIndex;
	int FPreviousLineBreakIndex;
	System::Types::TSizeF FGlyphSize;
	TPartContext* FPartContext;
	System::Generics::Collections::TList__1<void *>* FAttributes;
	int FCurrentAttributeIndex;
	int FSelectedAttributeIndex;
	TGPURunAction FAttributeAction;
	float FCurrentLineWidth;
	float FRemainLineWidth;
	TGPUFrame* FFrame;
	TGPULine* FCurrentLine;
	TGPURun* FCurrentRun;
	void __fastcall SetText(const System::UnicodeString Value);
	Fmx::Textlayout::TTextAttributedRange* __fastcall GetAttribute(const int Index);
	void __fastcall SetScale(const float Value);
	
protected:
	void __fastcall Init();
	System::Types::TSizeF __fastcall GetGlyphSize()/* overload */;
	System::Types::TSizeF __fastcall GetGlyphSize(const System::UCS4String ACharacter)/* overload */;
	float __fastcall GetBaseline(Fmx::Graphics::TFont* const AFont);
	bool __fastcall HasAvailableSpaceInCurrentLine();
	bool __fastcall HasAvailableSpaceInNextLine();
	bool __fastcall IsSplitterBefore();
	bool __fastcall IsSplitterAfter();
	bool __fastcall IsSpace()/* overload */;
	bool __fastcall IsSpace(const int AGlyphIndex)/* overload */;
	bool __fastcall IsSpace(const System::UCS4String ACharacter)/* overload */;
	bool __fastcall IsLineBreak()/* overload */;
	bool __fastcall IsLineBreak(const System::UnicodeString ASource, const int ABeginIndex, int &ALength)/* overload */;
	void __fastcall BeginPart();
	void __fastcall AddCharToPart();
	void __fastcall EndPart();
	void __fastcall CloseCurrentRun();
	void __fastcall CloseCurrentLine();
	void __fastcall BeginNewLine()/* overload */;
	void __fastcall BeginNewLine(const int AStartCharacterIndex)/* overload */;
	void __fastcall BeginNewRun(const int AStartOffset, const int AAttributeIndex = 0xffffffff);
	void __fastcall RollbackGlyph();
	void __fastcall RollbackWord();
	bool __fastcall IsRunEmpty();
	bool __fastcall IsLineEmpty();
	bool __fastcall IsFrameEmpty();
	int __fastcall GetCharacterLength(const int ACharacterIndex);
	void __fastcall NextChar();
	void __fastcall SkipChars(const int ACount);
	void __fastcall SkipLineBreak();
	bool __fastcall IsEOL();
	
public:
	__fastcall TLineReader(Fmx::Graphics::TFont* const ADefaultFont);
	__fastcall virtual ~TLineReader();
	void __fastcall FillLines(TGPUFrame* const AFrame);
	void __fastcall AddAttribute(Fmx::Textlayout::TTextAttributedRange* const AAttribute);
	void __fastcall ClearAttributes();
	__property Fmx::Textlayout::TTextAttributedRange* Attributes[const int Index] = {read=GetAttribute};
	__property float Scale = {read=FScale, write=SetScale};
	__property System::Types::TSizeF MaxSize = {read=FMaxSize, write=FMaxSize};
	__property System::Uitypes::TAlphaColor DefaultColor = {read=FDefaultColor, write=FDefaultColor, nodefault};
	__property Fmx::Graphics::TFont* DefaultFont = {read=FDefaultFont};
	__property System::UnicodeString Text = {write=SetText};
	__property Fmx::Types::TTextTrimming Trimming = {read=FTrimming, write=FTrimming, nodefault};
	__property bool WordWrap = {read=FWordWrap, write=FWordWrap, nodefault};
};


class PASCALIMPLEMENTATION TFrameRender : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TPixelAlignment : unsigned int { Horizontal, Vertical };
	
	typedef System::Set<TPixelAlignment, _DELPHI_SET_ENUMERATOR(TPixelAlignment::Horizontal), _DELPHI_SET_ENUMERATOR(TPixelAlignment::Vertical)> TPixelAlignments;
	
	
private:
	Fmx::Graphics::TFont* FDefaultFont;
	Fmx::Graphics::TStrokeBrush* FStrokeBrush;
	float FScale;
	float FScaleFactor;
	float FOpacity;
	System::Types::TRectF FOutputBounds;
	System::Types::TRectF FCanvasClipRect;
	TPixelAlignments FPixelAlignments;
	TGPUFrame* FFrame;
	Fmx::Graphics::TCanvas* FCanvas;
	void __fastcall SetScale(const float Value);
	System::Types::TSizeF __fastcall GetMaxSize();
	System::Types::TPointF __fastcall GetTopLeft();
	void __fastcall SetMaxSize(const System::Types::TSizeF &Value);
	void __fastcall SetTopLeft(const System::Types::TPointF &Value);
	
protected:
	void __fastcall RecalculateCanvasClipRect();
	void __fastcall DifinePixelAlignment();
	System::Types::TRectF __fastcall CalculateGlyphDestRect(const System::Types::TPointF &APosition, const float ABaselineOffset, const PCharRec AGlyphRec);
	bool __fastcall IsOutOfCanvasArea(const System::Types::TRectF &ARect);
	bool __fastcall IsOutOfOutputArea(const System::Types::TRectF &ARect);
	__classmethod System::Types::TRectF __fastcall ConvexHull(const System::Math::Vectors::TPolygon APolygon);
	void __fastcall DrawTextDecorationIfNeeded(TGPURun* const ARun, const System::Types::TPointF &AFirstGlyphPos, const float ABaselineOffset);
	void __fastcall DrawGlyphBounds(Fmx::Fontglyphs::TFontGlyph* const AGlyph, const System::Types::TRectF &ABounds);
	void __fastcall DrawTextBounds(const System::Types::TRectF &ABounds);
	
public:
	__fastcall TFrameRender(Fmx::Graphics::TFont* const ADefaultFont);
	__fastcall virtual ~TFrameRender();
	void __fastcall Render(TGPUFrame* const AFrame, Fmx::Graphics::TCanvas* const ACanvas, const float AOpacity);
	__property float Scale = {read=FScale, write=SetScale};
	__property System::Types::TSizeF MaxSize = {read=GetMaxSize, write=SetMaxSize};
	__property System::Types::TPointF TopLeft = {read=GetTopLeft, write=SetTopLeft};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UCS4String __fastcall ReadCharacter(const System::UnicodeString AText, const int AStartIndex, int &ARunLength);
}	/* namespace Gpu */
}	/* namespace Textlayout */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_TEXTLAYOUT_GPU)
using namespace Fmx::Textlayout::Gpu;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_TEXTLAYOUT)
using namespace Fmx::Textlayout;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Textlayout_GpuHPP
