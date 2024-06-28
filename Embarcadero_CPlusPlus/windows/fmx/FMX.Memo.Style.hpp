// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Memo.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Memo_StyleHPP
#define Fmx_Memo_StyleHPP

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
#include <FMX.MagnifierGlass.hpp>
#include <FMX.SpellChecker.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Text.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ScrollBox.Style.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Memo
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
struct TEditAction;
class DELPHICLASS TEditActionStack;
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
	TStyledMemo* FOwner;
	
public:
	__fastcall TEditActionStack(TStyledMemo* const AOwner);
	void __fastcall FragmentInserted(const int StartPos, const int FragmentLength, const bool PairedWithPrev, const bool Typed);
	void __fastcall FragmentDeleted(const int StartPos, const System::UnicodeString Fragment, const bool Selected, const bool CaretMoved);
	bool __fastcall RollBackAction();
public:
	/* {System_Generics_Collections}TStack<FMX_Memo_Style_TEditAction>.Destroy */ inline __fastcall virtual ~TEditActionStack() { }
	
};


class PASCALIMPLEMENTATION TStyledMemo : public Fmx::Scrollbox::Style::TStyledCustomScrollBox
{
	typedef Fmx::Scrollbox::Style::TStyledCustomScrollBox inherited;
	
	
protected:
	class DELPHICLASS TLineObject;
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
		
	public:
		void __fastcall FreeLayout();
		bool __fastcall SizeValid();
		void __fastcall InvalidateSize();
		__fastcall TLineObject()/* overload */;
		__fastcall TLineObject(Fmx::Textlayout::TTextLayout* const ALayout, const System::Types::TSizeF &ASize)/* overload */;
		__fastcall virtual ~TLineObject();
		__property System::Types::TSizeF Size = {read=FSize, write=FSize};
		__property System::Types::TRectF Rect = {read=FRect, write=FRect};
		__property Fmx::Textlayout::TTextLayout* Layout = {read=FLayout, write=FLayout};
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TLines;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TLines : public System::TObject
	{
		typedef System::TObject inherited;
		
public:
		TStyledMemo::TLineObject* operator[](const int Index) { return this->Items[Index]; }
		
	private:
		TStyledMemo* FMemo;
		System::Generics::Collections::TObjectList__1<TStyledMemo::TLineObject*>* FLines;
		int FTopLine;
		float FDefaultHeight;
		int FUpdating;
		System::Types::TRectF FNewContentBounds;
		bool FNeedUpdateContentSize;
		Fmx::Textlayout::TTextLayout* __fastcall CreateLayout(const System::UnicodeString S);
		bool __fastcall IsWordWrap();
		void __fastcall UpdateLayoutParams(Fmx::Textlayout::TTextLayout* Layout);
		void __fastcall UpdateLayoutsColor();
		void __fastcall CalculateDefaultLineMetrics();
		float __fastcall GetDefaultLineHeight();
		int __fastcall GetCount();
		TStyledMemo::TLineObject* __fastcall GetItem(const int Index);
		void __fastcall UpdateContentBounds(const System::Types::TRectF &ContentBounds);
		
	public:
		__fastcall TLines(TStyledMemo* Memo);
		__fastcall virtual ~TLines();
		void __fastcall BeginUpdate();
		void __fastcall EndUpdate();
		bool __fastcall IsUpdating();
		void __fastcall InsertLine(const int Index, const System::UnicodeString S);
		void __fastcall DeleteLine(const int Index);
		void __fastcall ReplaceLine(const int Index, const System::UnicodeString S);
		void __fastcall ExchangeLines(const int OldIndex, const int NewIndex);
		Fmx::Text::TCaretPosition __fastcall GetPointPosition(const System::Types::TPointF &Pt, const bool RoundToWord = false);
		Fmx::Graphics::TRegion __fastcall GetRegionForRange(const int ALine, const int APos, const int ALength, const bool RoundToWord = false);
		void __fastcall RenderLayouts();
		__property int Count = {read=GetCount, nodefault};
		__property TStyledMemo::TLineObject* Items[const int Index] = {read=GetItem/*, default*/};
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSpellingWord;
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
		
	public:
		__fastcall TSpellingWord(const Fmx::Text::TCaretPosition &APosition, const int ALength, const Fmx::Graphics::TRegion ABounds);
		bool __fastcall HasBounds();
		bool __fastcall PosAtCurrentPos(const Fmx::Text::TCaretPosition &APosition);
		void __fastcall InvalidateBounds();
		__property Fmx::Text::TCaretPosition Position = {read=FPosition, write=FPosition};
		__property int Length = {read=FLength, write=FLength, nodefault};
		__property Fmx::Graphics::TRegion Bounds = {read=FBounds, write=FBounds};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TSpellingWord() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	Fmx::Text::TTextService* FTextService;
	bool FLMouseSelecting;
	bool FIgnoreMouseMove;
	System::Types::TPointF FDownMPt;
	System::Types::TPointF FOldMPt;
	Fmx::Text::TCaretPosition FCaretPosition;
	Fmx::Menus::TPopupMenu* FMemoPopupMenu;
	TEditActionStack* FActionStack;
	TLines* FLineObjects;
	Fmx::Text::TCaretPosition FSelStart;
	Fmx::Text::TCaretPosition FSelEnd;
	bool FSelected;
	Fmx::Graphics::TBrush* FCursorFill;
	Fmx::Controls::TControl* FContent;
	Fmx::Types::TTimer* FStartAutoScrollTimer;
	Fmx::Types::TTimer* FAutoVScrollTimer;
	Fmx::Types::TTimer* FAutoHScrollTimer;
	bool FNeedAutoVScroll;
	bool FNeedAutoHScroll;
	bool FFollowTheMouse;
	System::UnicodeString FCharsBuffer;
	Fmx::Objects::TSelectionPoint* FLeftSelPt;
	Fmx::Objects::TSelectionPoint* FRightSelPt;
	Fmx::Magnifierglass::_di_ILoupeService FLoupeService;
	float FLineHeight;
	bool FSetFocusOnUp;
	bool FOldWordWrap;
	Fmx::Spellchecker::_di_IFMXSpellCheckerService FSpellService;
	System::Generics::Collections::TList__1<Fmx::Menus::TMenuItem*>* FSpellMenuItems;
	System::Types::TRectF FSpellHightlightRect;
	Fmx::Graphics::TBrush* FSpellFill;
	Fmx::Graphics::TStrokeBrush* FSpellUnderlineBrush;
	System::Generics::Collections::TObjectList__1<TSpellingWord*>* FSpellingWords;
	HIDESBASE Fmx::Memo::TCustomMemoModel* __fastcall GetModel();
	Fmx::Memo::TCustomMemo* __fastcall GetMemo();
	float __fastcall GetPageSize();
	void __fastcall SetCaretPosition(const Fmx::Text::TCaretPosition &Value);
	Fmx::Text::TCaretPosition __fastcall GetNextWordBegin(const Fmx::Text::TCaretPosition &StartPosition);
	Fmx::Text::TCaretPosition __fastcall GetPrevWordBegin(const Fmx::Text::TCaretPosition &StartPosition);
	Fmx::Text::TCaretPosition __fastcall GetPositionShift(const Fmx::Text::TCaretPosition &APos, const int Delta);
	Fmx::Text::TCaretPosition __fastcall GetSelBeg();
	Fmx::Text::TCaretPosition __fastcall GetSelEnd();
	void __fastcall SelPtMouseUpHandler(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall LeftSelPtChangePositionHandler(System::TObject* Sender, float &X, float &Y);
	void __fastcall LeftSelPtMouseDownHandler(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall RightSelPtChangePositionHandler(System::TObject* Sender, float &X, float &Y);
	void __fastcall RightSelPtMouseDownHandler(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall FindSpellingErrorsInLine(const int LineIndex);
	void __fastcall RemoveSpellingErrorsForLine(const int LineIndex);
	void __fastcall DoScroll(const int ADirection);
	void __fastcall HideLoupe();
	void __fastcall ShowLoupe();
	void __fastcall SetLoupePosition(const Fmx::Memo::Types::TSelectionPointType ASelectionPointType)/* overload */;
	void __fastcall SetLoupePosition(const float X, const float Y)/* overload */;
	void __fastcall StartAutoScroll(const float X, const float Y);
	void __fastcall StopAutoScroll();
	void __fastcall StartAutoScrollHandler(System::TObject* Sender);
	void __fastcall AutoScrollUpHandler(System::TObject* Sender);
	void __fastcall AutoScrollDownHandler(System::TObject* Sender);
	void __fastcall AutoScrollLeftHandler(System::TObject* Sender);
	void __fastcall AutoScrollRightHandler(System::TObject* Sender);
	void __fastcall UpdateSpellPopupMenu(const System::Types::TPointF &APoint);
	void __fastcall SpellFixContextMenuHandler(System::TObject* Sender);
	
protected:
	bool FDisableCaretInsideWords;
	MESSAGE void __fastcall MMCharCaseChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TEditCharCase> &Message);
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMHideSelectionOnExitChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMReadOnlyChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMImeModeChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TImeMode> &Message);
	MESSAGE void __fastcall MMSetSelStart(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMLinesInsertLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesPutLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
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
	virtual void __fastcall DoEndUpdate();
	virtual void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	virtual void __fastcall AniMouseDown(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseMove(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseUp(const bool Touch, const float X, const float Y);
	float __fastcall GetLineHeight();
	virtual void __fastcall CreatePopupMenu();
	virtual void __fastcall UpdatePopupMenuItems();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall Resize();
	virtual void __fastcall DoChange();
	void __fastcall DoUndo(System::TObject* Sender);
	void __fastcall DoCut(System::TObject* Sender);
	void __fastcall DoCopy(System::TObject* Sender);
	void __fastcall DoPaste(System::TObject* Sender);
	void __fastcall DoDelete(System::TObject* Sender);
	void __fastcall DoSelectAll(System::TObject* Sender);
	void __fastcall RepaintEdit();
	virtual bool __fastcall ShowContextMenu(const System::Types::TPointF &ScreenPosition);
	virtual void __fastcall DoViewportPositionChange(const System::Types::TPointF &OldViewportPosition, const System::Types::TPointF &NewViewportPosition, const bool ContentSizeChanged);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	void __fastcall LongTap(const float X, const float Y);
	void __fastcall DblTap();
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	void __fastcall UpdateSelectionInModel();
	virtual bool __fastcall GetShowSelection();
	void __fastcall BeginSelection();
	void __fastcall EndSelection();
	void __fastcall GetNormalizedSelectionRange(Fmx::Text::TCaretPosition &ASelStart, Fmx::Text::TCaretPosition &ASelEnd);
	void __fastcall SetNormalizedSelectionRange(const Fmx::Text::TCaretPosition &ASelStart, const Fmx::Text::TCaretPosition &ASelEnd);
	Fmx::Graphics::TRegion __fastcall GetSelectionRegion();
	bool __fastcall HaveSelectionPickers();
	void __fastcall UpdateSelectionPointPositions();
	void __fastcall PutCaretTo(const float X, const float Y, const bool Select = false, const bool PositionByWord = false);
	void __fastcall SelectAtPos(const Fmx::Text::TCaretPosition &APos);
	void __fastcall UpdateCaretPosition(const bool UpdateScrllBars);
	void __fastcall UpdateHScrlBarByCaretPos();
	void __fastcall UpdateVScrlBarByCaretPos();
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
	
public:
	__fastcall virtual TStyledMemo(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledMemo();
	virtual void __fastcall RecalcOpacity();
	void __fastcall MoveCaretBy(const int Delta);
	void __fastcall MoveCaretLeft();
	void __fastcall MoveCaretRight();
	void __fastcall MoveCaretVertical(const int LineDelta);
	void __fastcall MoveCaretDown();
	void __fastcall MoveCaretUp();
	void __fastcall MoveCaretPageUp();
	void __fastcall MoveCaretPageDown();
	System::Types::TPointF __fastcall GetPositionPoint(const Fmx::Text::TCaretPosition &ACaretPos);
	void __fastcall GotoLineBegin();
	void __fastcall GotoLineEnd();
	void __fastcall GotoTextBegin();
	void __fastcall GotoTextEnd();
	__property Fmx::Memo::TCustomMemo* Memo = {read=GetMemo};
	__property Fmx::Memo::TCustomMemoModel* Model = {read=GetModel};
	__property Fmx::Text::TCaretPosition CaretPosition = {read=FCaretPosition, write=SetCaretPosition};
	__property float LineHeight = {read=GetLineHeight};
	__property Fmx::Text::TCaretPosition SelBeg = {read=GetSelBeg};
	__property Fmx::Text::TCaretPosition SelEnd = {read=GetSelEnd};
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
}	/* namespace Style */
}	/* namespace Memo */
}	/* namespace Fmx */
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
#endif	// Fmx_Memo_StyleHPP
