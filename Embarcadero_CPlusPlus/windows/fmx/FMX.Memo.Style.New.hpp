// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Memo.Style.New.pas' rev: 34.00 (Windows)

#ifndef Fmx_Memo_Style_NewHPP
#define Fmx_Memo_Style_NewHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.TextLayout.hpp>
#include <FMX.Objects.hpp>
#include <FMX.SpellChecker.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Text.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ScrollBox.Style.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Memo
{
namespace Style
{
namespace New
{
//-- forward type declarations -----------------------------------------------
struct TEditAction;
class DELPHICLASS TEditActionStack;
class DELPHICLASS TSelectionController;
class DELPHICLASS TLineObject;
class DELPHICLASS TLinesLayout;
class DELPHICLASS TSpellingWord;
class DELPHICLASS TMemoSpellingManager;
class DELPHICLASS TContextMenuItem;
class DELPHICLASS TAutoscrollController;
class DELPHICLASS TStyledMemo;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TEditAction
{
public:
	Fmx::Memo::Types::TActionType ActionType;
	bool PairedWithPrev;
	int StartPosition;
	System::UnicodeString DeletedFragment;
	int Length;
	bool Typed;
	bool WasSelected;
	bool CaretMoved;
};


class PASCALIMPLEMENTATION TEditActionStack : public System::Generics::Collections::TStack__1<TEditAction>
{
	typedef System::Generics::Collections::TStack__1<TEditAction> inherited;
	
private:
	Fmx::Memo::TCustomMemoModel* FModel;
	
public:
	__fastcall TEditActionStack(Fmx::Memo::TCustomMemoModel* const AModel);
	void __fastcall FragmentInserted(const int AStartPos, const int AFragmentLength, const bool APairedWithPrev, const bool ATyped);
	void __fastcall FragmentDeleted(const int AStartPos, const System::UnicodeString AFragment, const bool ASelected, const bool ACaretMoved);
	bool __fastcall RollBackAction();
public:
	/* {System_Generics_Collections}TStack<FMX_Memo_Style_New_TEditAction>.Destroy */ inline __fastcall virtual ~TEditActionStack() { }
	
};


typedef void __fastcall (__closure *TOnSelectionChanged)(System::TObject* Sender, const int ASelStart, const int ALength);

class PASCALIMPLEMENTATION TSelectionController : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Text::_di_ITextLinesSource FLineSource;
	Fmx::Text::TCaretPosition FSelStart;
	Fmx::Text::TCaretPosition FSelFinish;
	TOnSelectionChanged FOnChanged;
	void __fastcall SetLength(const int Value);
	void __fastcall SetStartPos(const int Value);
	void __fastcall SetSelStart(const Fmx::Text::TCaretPosition &Value);
	void __fastcall SetSelFinish(const Fmx::Text::TCaretPosition &Value);
	int __fastcall GetLength();
	
protected:
	virtual void __fastcall DoSelectionChanged();
	
public:
	__fastcall TSelectionController(const Fmx::Text::_di_ITextLinesSource ALineSource);
	__fastcall virtual ~TSelectionController();
	void __fastcall SetRange(const Fmx::Text::TCaretPosition &ASelStart, const Fmx::Text::TCaretPosition &ASelEnd)/* overload */;
	void __fastcall SetRange(const int AStartPos, const int ALength)/* overload */;
	void __fastcall Reset();
	Fmx::Text::TCaretPosition __fastcall SelBegin();
	int __fastcall BeginPos();
	Fmx::Text::TCaretPosition __fastcall SelEnd();
	int __fastcall EndPos();
	__property Fmx::Text::TCaretPosition Start = {read=FSelStart, write=SetSelStart};
	__property int StartPos = {write=SetStartPos, nodefault};
	__property Fmx::Text::TCaretPosition Finish = {read=FSelFinish, write=SetSelFinish};
	__property int Length = {read=GetLength, write=SetLength, nodefault};
	bool __fastcall IsSelected();
	__property TOnSelectionChanged OnChanged = {read=FOnChanged, write=FOnChanged};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLineObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Types::TSizeF FSize;
	Fmx::Textlayout::TTextLayout* FLayout;
	System::Types::TRectF FRect;
	void __fastcall SetLocation(const System::Types::TPointF &Value);
	
protected:
	virtual void __fastcall DoRender(Fmx::Graphics::TCanvas* const ACanvas);
	
public:
	__fastcall TLineObject()/* overload */;
	__fastcall TLineObject(Fmx::Textlayout::TTextLayout* const ALayout, const System::Types::TSizeF &ASize)/* overload */;
	__fastcall virtual ~TLineObject();
	void __fastcall FreeLayout();
	bool __fastcall IsSizeValid();
	void __fastcall InvalidateSize();
	void __fastcall Render(Fmx::Graphics::TCanvas* const ACanvas);
	__property System::Types::TSizeF Size = {read=FSize, write=FSize};
	__property System::Types::TRectF Rect = {read=FRect, write=FRect};
	__property System::Types::TPointF Location = {write=SetLocation};
	__property Fmx::Textlayout::TTextLayout* Layout = {read=FLayout, write=FLayout};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLinesLayout : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TLineObject* operator[](const int Index) { return this->Items[Index]; }
	
private:
	Fmx::Text::_di_ITextLinesSource FLineSource;
	Fmx::Scrollbox::Style::_di_IScrollableContent FScrollableContent;
	float FLineHeight;
	System::Generics::Collections::TObjectList__1<TLineObject*>* FLines;
	int FUpdating;
	System::Types::TRectF FNewContentBounds;
	bool FNeedUpdateContentSize;
	Fmx::Graphics::TTextSettings* FTextSettings;
	float FCaretWidth;
	float FOpacity;
	void __fastcall SetOpacity(const float Value);
	void __fastcall SetTextSettings(Fmx::Graphics::TTextSettings* const Value);
	Fmx::Textlayout::TTextLayout* __fastcall CreateLayout(const System::UnicodeString S);
	bool __fastcall IsWordWrap();
	void __fastcall UpdateLayoutParams(Fmx::Textlayout::TTextLayout* const ALayout);
	void __fastcall UpdateLayoutsColor();
	int __fastcall GetCount();
	TLineObject* __fastcall GetItem(const int Index);
	void __fastcall UpdateContentBounds(const System::Types::TRectF &ContentBounds);
	
public:
	__fastcall TLinesLayout(const Fmx::Text::_di_ITextLinesSource ALineSource, const Fmx::Scrollbox::Style::_di_IScrollableContent AScrollableContent);
	__fastcall virtual ~TLinesLayout();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsUpdating();
	void __fastcall InsertLine(const int AIndex, const System::UnicodeString ALine);
	void __fastcall DeleteLine(const int AIndex);
	void __fastcall ReplaceLine(const int AIndex, const System::UnicodeString ALine);
	void __fastcall ExchangeLines(const int AOldIndex, const int ANewIndex);
	void __fastcall Clear();
	void __fastcall RecalculateLines();
	void __fastcall OffsetContent(const System::Types::TPointF &AViewportPosition, const System::Types::TPointF &AOffset);
	float __fastcall GetLineHeight();
	Fmx::Text::TCaretPosition __fastcall GetPointPosition(const System::Types::TPointF &Pt, const bool RoundToWord = false);
	Fmx::Graphics::TRegion __fastcall GetRegionForRange(const int ALine, const int APos, const int ALength, const bool RoundToWord = false);
	void __fastcall RecalculateLayouts();
	void __fastcall Render(Fmx::Graphics::TCanvas* const ACanvas);
	__property int Count = {read=GetCount, nodefault};
	__property TLineObject* Items[const int Index] = {read=GetItem/*, default*/};
	__property float CaretWidth = {read=FCaretWidth, write=FCaretWidth};
	__property float Opacity = {read=FOpacity, write=SetOpacity};
	__property Fmx::Graphics::TTextSettings* TextSettings = {read=FTextSettings, write=SetTextSettings};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSpellingWord : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Text::TCaretPosition FPosition;
	int FLength;
	Fmx::Graphics::TRegion FBounds;
	System::UnicodeString FWord;
	
public:
	__fastcall TSpellingWord(const Fmx::Text::TCaretPosition &APosition, const System::UnicodeString AWord, const Fmx::Graphics::TRegion ABounds);
	bool __fastcall HasBounds();
	bool __fastcall PosAtCurrentPos(const Fmx::Text::TCaretPosition &APosition);
	void __fastcall InvalidateBounds();
	Fmx::Textlayout::TTextRange __fastcall TextRange();
	__property Fmx::Text::TCaretPosition Position = {read=FPosition, write=FPosition};
	__property int Length = {read=FLength, write=FLength, nodefault};
	__property Fmx::Graphics::TRegion Bounds = {read=FBounds, write=FBounds};
	__property System::UnicodeString Word = {read=FWord};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSpellingWord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TOnReplaceWordEvent)(TSpellingWord* const ASpellingWord, const System::UnicodeString ASuggestion);

class PASCALIMPLEMENTATION TMemoSpellingManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Text::_di_ITextLinesSource FLinesSource;
	Fmx::Spellchecker::_di_IFMXSpellCheckerService FSpellService;
	System::Generics::Collections::TObjectList__1<TSpellingWord*>* FSpellingWords;
	System::Generics::Collections::TList__1<Fmx::Menus::TMenuItem*>* FMenuItems;
	System::Types::TRectF FHightlightRect;
	Fmx::Graphics::TBrush* FFill;
	Fmx::Graphics::TStrokeBrush* FUnderlineStroke;
	TOnReplaceWordEvent FOnReplaceWord;
	void __fastcall SetFill(Fmx::Graphics::TBrush* const Value);
	void __fastcall SetStroke(Fmx::Graphics::TStrokeBrush* const Value);
	void __fastcall ClearMenuItems();
	void __fastcall SpellFixContextMenuHandler(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoReplaceWord(TSpellingWord* const ASpellingWord, const System::UnicodeString ASuggestion);
	bool __fastcall FindSpellingWordByCaret(const Fmx::Text::TCaretPosition &ACaretPosition, /* out */ int &AIndex);
	
public:
	__fastcall TMemoSpellingManager(const Fmx::Text::_di_ITextLinesSource ALinesSource);
	__fastcall virtual ~TMemoSpellingManager();
	void __fastcall Spell(Fmx::Text::TCaretPosition &ACaretPosition, const System::UnicodeString AWord);
	bool __fastcall IsWordWrong(const Fmx::Text::TCaretPosition &ACaretPosition);
	void __fastcall FindSpellingErrorsInLines();
	void __fastcall FindSpellingErrorsInLine(const int ALineIndex);
	void __fastcall RemoveSpellingErrorsForLine(const int ALineIndex);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetListOfPrepositions(const Fmx::Text::TCaretPosition &ACaretPosition);
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetListOfPrepositions(const Fmx::Text::TCaretPosition &ACaretPosition);
#endif /* _WIN64 */
	void __fastcall AddSuggestionsToPopupMenu(Fmx::Menus::TPopupMenu* const APopupMenu, const Fmx::Text::TCaretPosition &ACaretPosition);
	void __fastcall Reset();
	void __fastcall ResetBounds();
	void __fastcall HighlightSpell(TLinesLayout* const ALines, const Fmx::Text::TCaretPosition &ACaretPosition);
	void __fastcall HideHighlightSpell();
	void __fastcall UpdateHightlightRect(TLinesLayout* const ALines, const System::Types::TSizeF &AViewportSize, const System::Types::TPointF &AOffset);
	void __fastcall DrawHightlightSpellingWords(TLinesLayout* const ALine, const System::Types::TSizeF &AViewportSize, Fmx::Graphics::TCanvas* const ACanvas, const float AOpacity);
	__property Fmx::Graphics::TBrush* Fill = {read=FFill, write=SetFill};
	__property Fmx::Graphics::TStrokeBrush* Stroke = {read=FUnderlineStroke, write=SetStroke};
	__property System::Generics::Collections::TObjectList__1<TSpellingWord*>* SpellingWords = {read=FSpellingWords};
	__property TOnReplaceWordEvent OnReplaceWord = {read=FOnReplaceWord, write=FOnReplaceWord};
};


enum class DECLSPEC_DENUM TContextAction : unsigned char { Cut, Copy, Paste, Delete, Undo, SelectAll };

class PASCALIMPLEMENTATION TContextMenuItem : public Fmx::Menus::TMenuItem
{
	typedef Fmx::Menus::TMenuItem inherited;
	
private:
	TContextAction FContextAction;
	
public:
	__property TContextAction ContextAction = {read=FContextAction, write=FContextAction, nodefault};
public:
	/* TMenuItem.Create */ inline __fastcall virtual TContextMenuItem(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Menus::TMenuItem(AOwner) { }
	/* TMenuItem.Destroy */ inline __fastcall virtual ~TContextMenuItem() { }
	
};


enum class DECLSPEC_DENUM TAutoscrollDirection : unsigned char { LeftToRight, RightToLeft, TopToBottom, BottomToTop, LeftTopToRightBottom, LeftBottomToRightTop, RightTopToLeftBottom, RightBottomToLeftTop };

typedef void __fastcall (__closure *TOnAutoScrollEvent)(const TAutoscrollDirection ADirection, bool &AStop);

class PASCALIMPLEMENTATION TAutoscrollController : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 DefaultScrollStepInterval = System::Int8(0x64);
	
	static const System::Int8 DefaultStartScrollDelay = System::Int8(0x64);
	
	
private:
	Fmx::Types::TTimer* FStartAutoScrollTimer;
	Fmx::Types::TTimer* FAutoScrollTimer;
	TAutoscrollDirection FScrollDirection;
	TOnAutoScrollEvent FOnScroll;
	void __fastcall SetStartDelay(const int Value);
	int __fastcall GetStartDelay();
	int __fastcall GetScrollInterval();
	void __fastcall SetScrollInterval(const int Value);
	void __fastcall StartAutoScrollHandler(System::TObject* Sender);
	void __fastcall AutoScrollHandler(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoScroll(bool &AStop);
	
public:
	__fastcall TAutoscrollController();
	__fastcall virtual ~TAutoscrollController();
	void __fastcall Start(const TAutoscrollDirection ADirection);
	void __fastcall Stop();
	__property int StartDelay = {read=GetStartDelay, write=SetStartDelay, nodefault};
	__property int ScrollInterval = {read=GetScrollInterval, write=SetScrollInterval, nodefault};
	__property TOnAutoScrollEvent OnScroll = {read=FOnScroll, write=FOnScroll};
};


class PASCALIMPLEMENTATION TStyledMemo : public Fmx::Scrollbox::Style::TStyledCustomScrollBox
{
	typedef Fmx::Scrollbox::Style::TStyledCustomScrollBox inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TSelectionMethod : unsigned char { Keyboard, Mouse };
	
	typedef System::Set<TSelectionMethod, _DELPHI_SET_ENUMERATOR(TSelectionMethod::Keyboard), _DELPHI_SET_ENUMERATOR(TSelectionMethod::Mouse)> TSelectionMethods;
	
	enum class DECLSPEC_DENUM TSelectionOption : unsigned char { SelectWords };
	
	typedef System::Set<TSelectionOption, _DELPHI_SET_ENUMERATOR(TSelectionOption::SelectWords), _DELPHI_SET_ENUMERATOR(TSelectionOption::SelectWords)> TSelectionOptions;
	
	enum class DECLSPEC_DENUM TScrollDirection : unsigned char { Up, Down };
	
	
public:
	static const System::Int8 DefaultEmptySelectionWidth = System::Int8(0x5);
	
	static const System::Int8 IMEWindowGap = System::Int8(0x2);
	
	#define TStyledMemo_MarkedTextBackgroundOpacity  (9.000000E-01)
	
	
private:
	Fmx::Text::TTextService* FTextService;
	Fmx::Text::TCaretPosition FCaretPosition;
	Fmx::Menus::TPopupMenu* FMemoPopupMenu;
	TEditActionStack* FActionStack;
	TLinesLayout* FLinesLayout;
	System::UnicodeString FCharsBuffer;
	bool FSetFocusOnUp;
	TAutoscrollController* FAutoscrollController;
	TSelectionController* FSelectionController;
	TSelectionMethods FSelectionMethods;
	TSelectionOptions FSelectionOptions;
	TMemoSpellingManager* FSpellingManager;
	Fmx::Textlayout::TTextLayout* FImeLayout;
	HIDESBASE Fmx::Memo::TCustomMemoModel* __fastcall GetModel();
	Fmx::Memo::TCustomMemo* __fastcall GetMemo();
	void __fastcall SetCaretPosition(const Fmx::Text::TCaretPosition &Value);
	float __fastcall GetPageSize();
	void __fastcall ReplaceWordHandler(TSpellingWord* const ASpellingWord, const System::UnicodeString ASuggestion);
	void __fastcall SelectionChangedHandler(System::TObject* Sender, const int ASelStart, const int ALength);
	void __fastcall ContextMenuItemClick(System::TObject* Sender);
	void __fastcall AutoScrollHandler(const TAutoscrollDirection ADirection, bool &AStop);
	
protected:
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	void __fastcall UpdateScrollbarsPosition();
	void __fastcall UpdateCaretPosition();
	MESSAGE void __fastcall MMCharCaseChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TEditCharCase> &Message);
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMHideSelectionOnExitChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMReadOnlyChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMImeModeChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TImeMode> &Message);
	MESSAGE void __fastcall MMSetSelStart(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMLinesInsertLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesReplaceLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesDeleteLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesExchangeLines(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesClear(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMUpdateStateChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMGetCaretPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Text::TCaretPosition> &Message);
	MESSAGE void __fastcall MMSetCaretPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Text::TCaretPosition> &Message);
	MESSAGE void __fastcall MMCanSetFocus(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMLinesChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMMaxLengthChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMGetCaretPositionByPoint(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TGetCaretPositionInfo> &Message);
	HIDESBASE MESSAGE void __fastcall PMInit(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMGotoLineBegin(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMGotoLineEnd(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMFragmentInserted(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::Types::TFragmentInserted> &Message);
	MESSAGE void __fastcall PMFragmentDeleted(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::Types::TFragmentDeleted> &Message);
	MESSAGE void __fastcall PMUndo(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMSelectText(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMRootChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::_di_IRoot> &Message);
	Fmx::Text::TTextService* __fastcall GetTextService();
	System::Types::TPointF __fastcall GetTargetClausePointF();
	void __fastcall StartIMEInput();
	void __fastcall EndIMEInput();
	void __fastcall IMEStateUpdated();
	System::UnicodeString __fastcall GetSelection();
	System::Types::TRectF __fastcall GetSelectionRect();
	System::Types::TRect __fastcall GetSelectionBounds();
	System::Types::TSizeF __fastcall GetSelectionPointSize();
	bool __fastcall HasText();
	void __fastcall ContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* ACanvas, const System::Types::TRectF &ARect);
	virtual void __fastcall DrawSelection(Fmx::Graphics::TCanvas* const ACanvas);
	virtual void __fastcall DrawMarkedText(Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &ARect);
	Fmx::Graphics::TRegion __fastcall GetSelectionRegion();
	bool __fastcall IsSelecting();
	virtual bool __fastcall NeedShowSelection();
	void __fastcall StartAutoScroll(const System::Types::TPointF &ALocalPoint);
	bool __fastcall IsSpellCheckEnabled();
	bool __fastcall IsCurrentWordWrong();
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetListOfPrepositions();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetListOfPrepositions();
#endif /* _WIN64 */
	void __fastcall HighlightSpell();
	void __fastcall HideHighlightSpell();
	void __fastcall Spell(const System::UnicodeString AWord);
	virtual void __fastcall ExecuteContextAction(const TContextAction AAction);
	virtual void __fastcall FillPopupMenu(Fmx::Menus::TPopupMenu* const AMenu);
	virtual void __fastcall UpdatePopupMenuItems(Fmx::Menus::TPopupMenu* const AMenu);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall AniMouseDown(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseMove(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseUp(const bool Touch, const float X, const float Y);
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	void __fastcall LongTap(const System::Types::TPointF &ALocalPoint, const Fmx::Types::TInteractiveGestureFlags AFlags);
	void __fastcall DblTap();
	bool __fastcall HasImeMarkedText();
	void __fastcall UpdateTextInTextService();
	virtual bool __fastcall ShowContextMenu(const System::Types::TPointF &ScreenPosition);
	virtual void __fastcall DoViewportPositionChange(const System::Types::TPointF &OldViewportPosition, const System::Types::TPointF &NewViewportPosition, const bool ContentSizeChanged);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall KeyUp(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall DoBeginUpdate();
	virtual void __fastcall DoEndUpdate();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall Resize();
	virtual void __fastcall DoChange();
	virtual void __fastcall FreeNotification(System::TObject* AObject);
	
public:
	__fastcall virtual TStyledMemo(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledMemo();
	virtual void __fastcall RecalcOpacity();
	void __fastcall Undo();
	void __fastcall RepaintEdit();
	void __fastcall GotoLineBegin();
	void __fastcall GotoLineEnd();
	void __fastcall MoveCaretVertical(const int ALineDelta);
	void __fastcall MoveCaretPageUp();
	void __fastcall MoveCaretPageDown();
	System::Types::TPointF __fastcall GetCaretPositionPoint(const Fmx::Text::TCaretPosition &ACaretPos);
	void __fastcall PutCaretTo(const float X, const float Y, const bool APositionByWord = false);
	void __fastcall ScrollOnLine(const TScrollDirection ADirection);
	System::Types::TRectF __fastcall ViewportRect();
	__property Fmx::Memo::TCustomMemoModel* Model = {read=GetModel};
	__property Fmx::Memo::TCustomMemo* Memo = {read=GetMemo};
	__property TLinesLayout* LinesLayout = {read=FLinesLayout};
	__property TAutoscrollController* AutoscrollController = {read=FAutoscrollController};
	__property TSelectionController* SelectionController = {read=FSelectionController};
	__property Fmx::Text::TCaretPosition CaretPosition = {read=FCaretPosition, write=SetCaretPosition};
	__property float PageSize = {read=GetPageSize};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledMemo(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Scrollbox::Style::TStyledCustomScrollBox(AOwner, AModel, AControl) { }
	
private:
	void *__ITextSpellCheckActions;	// Fmx::Text::ITextSpellCheckActions 
	void *__ITextSpellCheck;	// Fmx::Text::ITextSpellCheck 
	void *__ITextInput;	// Fmx::Text::ITextInput 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {82A33171-C825-4B7F-B0C4-A56DDD4FF85C}
	operator Fmx::Text::_di_ITextSpellCheckActions()
	{
		Fmx::Text::_di_ITextSpellCheckActions intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Text::ITextSpellCheckActions*(void) { return (Fmx::Text::ITextSpellCheckActions*)&__ITextSpellCheckActions; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {30AA8C32-5ADA-456C-AAC5-B9F0309AE3A8}
	operator Fmx::Text::_di_ITextSpellCheck()
	{
		Fmx::Text::_di_ITextSpellCheck intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Text::ITextSpellCheck*(void) { return (Fmx::Text::ITextSpellCheck*)&__ITextSpellCheck; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {56D79E74-58D6-4C1E-B832-F133D669B952}
	operator Fmx::Text::_di_ITextInput()
	{
		Fmx::Text::_di_ITextInput intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Text::ITextInput*(void) { return (Fmx::Text::ITextInput*)&__ITextInput; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace New */
}	/* namespace Style */
}	/* namespace Memo */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO_STYLE_NEW)
using namespace Fmx::Memo::Style::New;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO_STYLE)
using namespace Fmx::Memo::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO)
using namespace Fmx::Memo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Memo_Style_NewHPP
