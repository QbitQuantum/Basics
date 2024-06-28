// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Edit.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Edit_StyleHPP
#define Fmx_Edit_StyleHPP

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
#include <FMX.Edit.hpp>
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
#include <FMX.Controls.Model.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Edit
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
struct TSelectionModeHelper /* Helper for enum 'TSelectionMode' */;
struct TSelectionPointTypeHelper /* Helper for enum 'TSelectionPointType' */;
class DELPHICLASS TStyledEdit;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TSelectionMode : unsigned char { None, TextSelection, CursorPosChanging, smNone _DEPRECATED_ATTRIBUTE3("Use TSelectionMode.None")  = 0x0, smTextSelection _DEPRECATED_ATTRIBUTE3("Use TSelectionMode.TextSelection")  = 0x1, smCursorPosChanging _DEPRECATED_ATTRIBUTE3("Use TSelectionMode.CursorPosChanging")  = 0x2 };

enum class DECLSPEC_DENUM TSelectionPointType : unsigned char { Left, Right, sptLeft _DEPRECATED_ATTRIBUTE3("Use TSelectionPointType.Left")  = 0x0, sptRight _DEPRECATED_ATTRIBUTE3("Use TSelectionPointType.Right")  = 0x1 };

class PASCALIMPLEMENTATION TStyledEdit : public Fmx::Presentation::Style::TStyledPresentation
{
	typedef Fmx::Presentation::Style::TStyledPresentation inherited;
	
private:
	Fmx::Text::TTextService* FTextService;
	int FFirstVisibleChar;
	float FInvisibleTextWidth;
	TSelectionMode FSelectionMode;
	Fmx::Graphics::TBrush* FCursorFill;
	Fmx::Controls::TControl* FContent;
	Fmx::Controls::TControl* FLeftLayout;
	Fmx::Controls::TControl* FButtonsLayout;
	Fmx::Controls::TControl* FPrompt;
	float FTextHeight;
	float FLineHeight;
	float FLineTop;
	Fmx::Textlayout::TTextLayout* FTextLayout;
	System::UnicodeString FCharsBuffer;
	Fmx::Objects::TSelectionPoint* FLeftSelPt;
	Fmx::Objects::TSelectionPoint* FRightSelPt;
	Fmx::Magnifierglass::_di_ILoupeService FLoupeService;
	Fmx::Spellchecker::_di_IFMXSpellCheckerService FSpellService;
	bool FUpdateSpelling;
	Fmx::Graphics::TRegion FSpellingRegions;
	System::Generics::Collections::TList__1<Fmx::Menus::TMenuItem*>* FSpellMenuItems;
	System::Types::TRectF FSpellHightlightRect;
	Fmx::Graphics::TBrush* FSpellFill;
	Fmx::Graphics::TStrokeBrush* FSpellUnderlineBrush;
	Fmx::Menus::TPopupMenu* FEditPopupMenu;
	void __fastcall UpdateSpelling();
	void __fastcall InsertText(const System::UnicodeString AText);
	System::UnicodeString __fastcall GetSelText();
	System::Types::TRectF __fastcall GetSelRect();
	void __fastcall SetCaretPosition(const int Value);
	int __fastcall GetCaretPosition()/* overload */;
	int __fastcall GetCaretPosition(const float Value)/* overload */;
	MESSAGE void __fastcall MMCaretPositionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	int __fastcall GetOriginCaretPosition();
	void __fastcall UpdateFirstVisibleChar();
	void __fastcall UpdateCaretPosition();
	HIDESBASE Fmx::Edit::TCustomEditModel* __fastcall GetModel();
	void __fastcall DoCopy(System::TObject* Sender);
	void __fastcall DoCut(System::TObject* Sender);
	void __fastcall DoDelete(System::TObject* Sender);
	void __fastcall DoPaste(System::TObject* Sender);
	void __fastcall DoSelectAll(System::TObject* Sender);
	void __fastcall BeginSelection();
	void __fastcall EndSelection();
	bool __fastcall HaveSelectionPickers();
	void __fastcall UpdateSelectionPointPositions();
	void __fastcall DoSelPtMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall DoLeftSelPtChangePosition(System::TObject* Sender, float &X, float &Y);
	void __fastcall DoLeftSelPtMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall DoRightSelPtChangePosition(System::TObject* Sender, float &X, float &Y);
	void __fastcall DoRightSelPtMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall HideLoupe();
	void __fastcall ShowLoupe();
	void __fastcall SetLoupePosition(const TSelectionPointType ASelectionPointType)/* overload */;
	void __fastcall SetLoupePosition(const float X, const float Y)/* overload */;
	void __fastcall SetSelectionMode(const TSelectionMode AValue);
	void __fastcall UpdateTextHeight();
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
	void __fastcall IMEStateUpdated();
	System::Types::TPointF __fastcall GetTargetClausePointF();
	void __fastcall StartIMEInput();
	void __fastcall EndIMEInput();
	System::Types::TRect __fastcall GetSelectionBounds();
	System::Types::TSizeF __fastcall GetSelectionPointSize();
	bool __fastcall HasText();
	void __fastcall UpdateSpellPopupMenu(const System::Types::TPointF &APoint);
	void __fastcall SpellFixContextMenuHandler(System::TObject* Sender);
	void __fastcall UpdateTextLayout();
	Fmx::Menus::TPopupMenu* __fastcall GetEditPopupMenu();
	void __fastcall UpdatePromptTextSettings();
	
protected:
	bool FNeedChange;
	virtual void __fastcall Change();
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMSelStartChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMPasswordChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMImeModeChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall MMTextChanging(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall MMEditButtonsChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMMaxLengthChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMPromptTextChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMCharCaseChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMFilterCharChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMGetCaretPositionByPoint(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Edit::TCustomEditModel::TGetCaretPositionInfo> &Message);
	MESSAGE void __fastcall PMDoBeforeExit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMGetTextContentRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TRectF> &Message);
	void __fastcall ShowCaret();
	void __fastcall HideCaret();
	Fmx::Types::TCustomCaret* __fastcall GetCaret();
	Fmx::Graphics::TTextSettings* __fastcall GetTextSettings();
	Fmx::Edit::TCustomEdit* __fastcall GetEdit();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	System::Word FLastKey;
	System::WideChar FLastChar;
	Fmx::Platform::_di_IFMXClipboardService FClipboardSvc;
	void __fastcall RepaintEdit();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall Resize();
	virtual void __fastcall DoChangeTracking();
	float __fastcall GetPasswordCharWidth();
	float __fastcall TextWidth(const int AStart, const int ALength);
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	virtual void __fastcall SetTextInternal(const System::UnicodeString Value);
	void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	void __fastcall LongTap(const float X, const float Y);
	void __fastcall DblTap();
	virtual void __fastcall DoRealign();
	virtual void __fastcall DoTyping();
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall RealignContent();
	virtual void __fastcall RealignButtonsContainer();
	void __fastcall UpdateLayoutSize();
	__property float TextHeight = {read=FTextHeight};
	__property float LineHeight = {read=FLineHeight};
	__property float LineTop = {read=FLineTop};
	__property TSelectionMode SelectionMode = {read=FSelectionMode, write=SetSelectionMode, nodefault};
	__property Fmx::Menus::TPopupMenu* EditPopupMenu = {read=GetEditPopupMenu};
	virtual Fmx::Menus::TPopupMenu* __fastcall CreatePopupMenu();
	Fmx::Menus::TMenuItem* __fastcall FindContextMenuItem(const System::UnicodeString AItemName);
	virtual bool __fastcall ShowContextMenu(const System::Types::TPointF &ScreenPosition);
	virtual void __fastcall UpdatePopupMenuItems();
	__property Fmx::Edit::TCustomEdit* Edit = {read=GetEdit};
	__property Fmx::Controls::TControl* ButtonsLayout = {read=FButtonsLayout};
	__property Fmx::Controls::TControl* LeftLayout = {read=FLeftLayout};
	
public:
	__fastcall virtual TStyledEdit(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledEdit();
	float __fastcall GetCharX(int a);
	System::Types::TRectF __fastcall ContentRect();
	__property int CaretPosition = {read=GetCaretPosition, write=SetCaretPosition, nodefault};
	__property Fmx::Edit::TCustomEditModel* Model = {read=GetModel};
	__property System::UnicodeString SelText = {read=GetSelText};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property Fmx::Graphics::TTextSettings* TextSettings = {read=GetTextSettings};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledEdit(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner, AModel, AControl) { }
	
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
}	/* namespace Edit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT_STYLE)
using namespace Fmx::Edit::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT)
using namespace Fmx::Edit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Edit_StyleHPP
