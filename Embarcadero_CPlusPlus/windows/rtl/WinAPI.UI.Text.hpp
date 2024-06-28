// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.Text.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_TextHPP
#define Winapi_Ui_TextHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Text
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ITextCharacterFormat;
typedef System::DelphiInterface<ITextCharacterFormat> _di_ITextCharacterFormat;
__interface DELPHIINTERFACE ITextParagraphFormat;
typedef System::DelphiInterface<ITextParagraphFormat> _di_ITextParagraphFormat;
__interface DELPHIINTERFACE ITextRange;
typedef System::DelphiInterface<ITextRange> _di_ITextRange;
__interface DELPHIINTERFACE ITextSelection;
typedef System::DelphiInterface<ITextSelection> _di_ITextSelection;
__interface DELPHIINTERFACE IReference_1__UnderlineType;
typedef System::DelphiInterface<IReference_1__UnderlineType> _di_IReference_1__UnderlineType;
//-- type declarations -------------------------------------------------------
typedef _di_ITextCharacterFormat *PITextCharacterFormat;

typedef _di_ITextParagraphFormat *PITextParagraphFormat;

typedef _di_ITextRange *PITextRange;

typedef _di_ITextSelection *PITextSelection;

typedef _di_IReference_1__UnderlineType *PIReference_1__UnderlineType;

__interface  INTERFACE_UUID("{5ADEF3DB-05FB-442D-8065-642AFEA02CED}") ITextCharacterFormat  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AllCaps(Winapi::Commontypes::FormatEffect &__get_AllCaps_result) = 0 ;
	virtual HRESULT __safecall put_AllCaps(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_BackgroundColor(Winapi::Commontypes::Color &__get_BackgroundColor_result) = 0 ;
	virtual HRESULT __safecall put_BackgroundColor(Winapi::Commontypes::Color value) = 0 ;
	virtual HRESULT __safecall get_Bold(Winapi::Commontypes::FormatEffect &__get_Bold_result) = 0 ;
	virtual HRESULT __safecall put_Bold(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_FontStretch(Winapi::Commontypes::FontStretch &__get_FontStretch_result) = 0 ;
	virtual HRESULT __safecall put_FontStretch(Winapi::Commontypes::FontStretch value) = 0 ;
	virtual HRESULT __safecall get_FontStyle(Winapi::Commontypes::FontStyle &__get_FontStyle_result) = 0 ;
	virtual HRESULT __safecall put_FontStyle(Winapi::Commontypes::FontStyle value) = 0 ;
	virtual HRESULT __safecall get_ForegroundColor(Winapi::Commontypes::Color &__get_ForegroundColor_result) = 0 ;
	virtual HRESULT __safecall put_ForegroundColor(Winapi::Commontypes::Color value) = 0 ;
	virtual HRESULT __safecall get_Hidden(Winapi::Commontypes::FormatEffect &__get_Hidden_result) = 0 ;
	virtual HRESULT __safecall put_Hidden(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Italic(Winapi::Commontypes::FormatEffect &__get_Italic_result) = 0 ;
	virtual HRESULT __safecall put_Italic(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Kerning(float &__get_Kerning_result) = 0 ;
	virtual HRESULT __safecall put_Kerning(float value) = 0 ;
	virtual HRESULT __safecall get_LanguageTag(HSTRING &__get_LanguageTag_result) = 0 ;
	virtual HRESULT __safecall put_LanguageTag(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_LinkType(Winapi::Commontypes::LinkType &__get_LinkType_result) = 0 ;
	virtual HRESULT __safecall get_Name(HSTRING &__get_Name_result) = 0 ;
	virtual HRESULT __safecall put_Name(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Outline(Winapi::Commontypes::FormatEffect &__get_Outline_result) = 0 ;
	virtual HRESULT __safecall put_Outline(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Position(float &__get_Position_result) = 0 ;
	virtual HRESULT __safecall put_Position(float value) = 0 ;
	virtual HRESULT __safecall get_ProtectedText(Winapi::Commontypes::FormatEffect &__get_ProtectedText_result) = 0 ;
	virtual HRESULT __safecall put_ProtectedText(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Size(float &__get_Size_result) = 0 ;
	virtual HRESULT __safecall put_Size(float value) = 0 ;
	virtual HRESULT __safecall get_SmallCaps(Winapi::Commontypes::FormatEffect &__get_SmallCaps_result) = 0 ;
	virtual HRESULT __safecall put_SmallCaps(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Spacing(float &__get_Spacing_result) = 0 ;
	virtual HRESULT __safecall put_Spacing(float value) = 0 ;
	virtual HRESULT __safecall get_Strikethrough(Winapi::Commontypes::FormatEffect &__get_Strikethrough_result) = 0 ;
	virtual HRESULT __safecall put_Strikethrough(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Subscript(Winapi::Commontypes::FormatEffect &__get_Subscript_result) = 0 ;
	virtual HRESULT __safecall put_Subscript(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Superscript(Winapi::Commontypes::FormatEffect &__get_Superscript_result) = 0 ;
	virtual HRESULT __safecall put_Superscript(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_TextScript(Winapi::Commontypes::TextScript &__get_TextScript_result) = 0 ;
	virtual HRESULT __safecall put_TextScript(Winapi::Commontypes::TextScript value) = 0 ;
	virtual HRESULT __safecall get_Underline(Winapi::Commontypes::UnderlineType &__get_Underline_result) = 0 ;
	virtual HRESULT __safecall put_Underline(Winapi::Commontypes::UnderlineType value) = 0 ;
	virtual HRESULT __safecall get_Weight(int &__get_Weight_result) = 0 ;
	virtual HRESULT __safecall put_Weight(int value) = 0 ;
	virtual HRESULT __safecall SetClone(_di_ITextCharacterFormat value) = 0 ;
	virtual HRESULT __safecall GetClone(_di_ITextCharacterFormat &__GetClone_result) = 0 ;
	virtual HRESULT __safecall IsEqual(_di_ITextCharacterFormat format, bool &__IsEqual_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_AllCaps() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_AllCaps(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect AllCaps = {read=_scw_get_AllCaps, write=put_AllCaps};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_BackgroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_BackgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color BackgroundColor = {read=_scw_get_BackgroundColor, write=put_BackgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Bold() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Bold(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Bold = {read=_scw_get_Bold, write=put_Bold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FontStretch _scw_get_FontStretch() { Winapi::Commontypes::FontStretch __r; HRESULT __hr = get_FontStretch(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FontStretch FontStretch = {read=_scw_get_FontStretch, write=put_FontStretch};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FontStyle _scw_get_FontStyle() { Winapi::Commontypes::FontStyle __r; HRESULT __hr = get_FontStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FontStyle FontStyle = {read=_scw_get_FontStyle, write=put_FontStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_ForegroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_ForegroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color ForegroundColor = {read=_scw_get_ForegroundColor, write=put_ForegroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Hidden() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Hidden(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Hidden = {read=_scw_get_Hidden, write=put_Hidden};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Italic() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Italic(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Italic = {read=_scw_get_Italic, write=put_Italic};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Kerning() { float __r; HRESULT __hr = get_Kerning(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Kerning = {read=_scw_get_Kerning, write=put_Kerning};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LanguageTag() { HSTRING __r; HRESULT __hr = get_LanguageTag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LanguageTag = {read=_scw_get_LanguageTag, write=put_LanguageTag};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::LinkType _scw_get_LinkType() { Winapi::Commontypes::LinkType __r; HRESULT __hr = get_LinkType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::LinkType LinkType = {read=_scw_get_LinkType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Name() { HSTRING __r; HRESULT __hr = get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Name = {read=_scw_get_Name, write=put_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Outline() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Outline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Outline = {read=_scw_get_Outline, write=put_Outline};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Position() { float __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Position = {read=_scw_get_Position, write=put_Position};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_ProtectedText() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_ProtectedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect ProtectedText = {read=_scw_get_ProtectedText, write=put_ProtectedText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Size() { float __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Size = {read=_scw_get_Size, write=put_Size};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_SmallCaps() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_SmallCaps(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect SmallCaps = {read=_scw_get_SmallCaps, write=put_SmallCaps};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Spacing() { float __r; HRESULT __hr = get_Spacing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Spacing = {read=_scw_get_Spacing, write=put_Spacing};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Strikethrough() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Strikethrough(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Strikethrough = {read=_scw_get_Strikethrough, write=put_Strikethrough};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Subscript() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Subscript(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Subscript = {read=_scw_get_Subscript, write=put_Subscript};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_Superscript() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_Superscript(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect Superscript = {read=_scw_get_Superscript, write=put_Superscript};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TextScript _scw_get_TextScript() { Winapi::Commontypes::TextScript __r; HRESULT __hr = get_TextScript(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TextScript TextScript = {read=_scw_get_TextScript, write=put_TextScript};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnderlineType _scw_get_Underline() { Winapi::Commontypes::UnderlineType __r; HRESULT __hr = get_Underline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnderlineType Underline = {read=_scw_get_Underline, write=put_Underline};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Weight() { int __r; HRESULT __hr = get_Weight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Weight = {read=_scw_get_Weight, write=put_Weight};
};

__interface  INTERFACE_UUID("{2CF8CFA6-4676-498A-93F5-BBDBFC0BD883}") ITextParagraphFormat  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Alignment(Winapi::Commontypes::ParagraphAlignment &__get_Alignment_result) = 0 ;
	virtual HRESULT __safecall put_Alignment(Winapi::Commontypes::ParagraphAlignment value) = 0 ;
	virtual HRESULT __safecall get_FirstLineIndent(float &__get_FirstLineIndent_result) = 0 ;
	virtual HRESULT __safecall get_KeepTogether(Winapi::Commontypes::FormatEffect &__get_KeepTogether_result) = 0 ;
	virtual HRESULT __safecall put_KeepTogether(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_KeepWithNext(Winapi::Commontypes::FormatEffect &__get_KeepWithNext_result) = 0 ;
	virtual HRESULT __safecall put_KeepWithNext(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_LeftIndent(float &__get_LeftIndent_result) = 0 ;
	virtual HRESULT __safecall get_LineSpacing(float &__get_LineSpacing_result) = 0 ;
	virtual HRESULT __safecall get_LineSpacingRule(Winapi::Commontypes::LineSpacingRule &__get_LineSpacingRule_result) = 0 ;
	virtual HRESULT __safecall get_ListAlignment(Winapi::Commontypes::MarkerAlignment &__get_ListAlignment_result) = 0 ;
	virtual HRESULT __safecall put_ListAlignment(Winapi::Commontypes::MarkerAlignment value) = 0 ;
	virtual HRESULT __safecall get_ListLevelIndex(int &__get_ListLevelIndex_result) = 0 ;
	virtual HRESULT __safecall put_ListLevelIndex(int value) = 0 ;
	virtual HRESULT __safecall get_ListStart(int &__get_ListStart_result) = 0 ;
	virtual HRESULT __safecall put_ListStart(int value) = 0 ;
	virtual HRESULT __safecall get_ListStyle(Winapi::Commontypes::MarkerStyle &__get_ListStyle_result) = 0 ;
	virtual HRESULT __safecall put_ListStyle(Winapi::Commontypes::MarkerStyle value) = 0 ;
	virtual HRESULT __safecall get_ListTab(float &__get_ListTab_result) = 0 ;
	virtual HRESULT __safecall put_ListTab(float value) = 0 ;
	virtual HRESULT __safecall get_ListType(Winapi::Commontypes::MarkerType &__get_ListType_result) = 0 ;
	virtual HRESULT __safecall put_ListType(Winapi::Commontypes::MarkerType value) = 0 ;
	virtual HRESULT __safecall get_NoLineNumber(Winapi::Commontypes::FormatEffect &__get_NoLineNumber_result) = 0 ;
	virtual HRESULT __safecall put_NoLineNumber(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_PageBreakBefore(Winapi::Commontypes::FormatEffect &__get_PageBreakBefore_result) = 0 ;
	virtual HRESULT __safecall put_PageBreakBefore(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_RightIndent(float &__get_RightIndent_result) = 0 ;
	virtual HRESULT __safecall put_RightIndent(float value) = 0 ;
	virtual HRESULT __safecall get_RightToLeft(Winapi::Commontypes::FormatEffect &__get_RightToLeft_result) = 0 ;
	virtual HRESULT __safecall put_RightToLeft(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_Style(Winapi::Commontypes::ParagraphStyle &__get_Style_result) = 0 ;
	virtual HRESULT __safecall put_Style(Winapi::Commontypes::ParagraphStyle value) = 0 ;
	virtual HRESULT __safecall get_SpaceAfter(float &__get_SpaceAfter_result) = 0 ;
	virtual HRESULT __safecall put_SpaceAfter(float value) = 0 ;
	virtual HRESULT __safecall get_SpaceBefore(float &__get_SpaceBefore_result) = 0 ;
	virtual HRESULT __safecall put_SpaceBefore(float value) = 0 ;
	virtual HRESULT __safecall get_WidowControl(Winapi::Commontypes::FormatEffect &__get_WidowControl_result) = 0 ;
	virtual HRESULT __safecall put_WidowControl(Winapi::Commontypes::FormatEffect value) = 0 ;
	virtual HRESULT __safecall get_TabCount(int &__get_TabCount_result) = 0 ;
	virtual HRESULT __safecall AddTab(float position, Winapi::Commontypes::TabAlignment align, Winapi::Commontypes::TabLeader leader) = 0 ;
	virtual HRESULT __safecall ClearAllTabs() = 0 ;
	virtual HRESULT __safecall DeleteTab(float position) = 0 ;
	virtual HRESULT __safecall GetClone(_di_ITextParagraphFormat &__GetClone_result) = 0 ;
	virtual HRESULT __safecall GetTab(int index, /* out */ float &position, /* out */ Winapi::Commontypes::TabAlignment &align, /* out */ Winapi::Commontypes::TabLeader &leader) = 0 ;
	virtual HRESULT __safecall IsEqual(_di_ITextParagraphFormat format, bool &__IsEqual_result) = 0 ;
	virtual HRESULT __safecall SetClone(_di_ITextParagraphFormat format) = 0 ;
	virtual HRESULT __safecall SetIndents(float start, float left, float right) = 0 ;
	virtual HRESULT __safecall SetLineSpacing(Winapi::Commontypes::LineSpacingRule rule, float spacing) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ParagraphAlignment _scw_get_Alignment() { Winapi::Commontypes::ParagraphAlignment __r; HRESULT __hr = get_Alignment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ParagraphAlignment Alignment = {read=_scw_get_Alignment, write=put_Alignment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_FirstLineIndent() { float __r; HRESULT __hr = get_FirstLineIndent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float FirstLineIndent = {read=_scw_get_FirstLineIndent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_KeepTogether() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_KeepTogether(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect KeepTogether = {read=_scw_get_KeepTogether, write=put_KeepTogether};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_KeepWithNext() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_KeepWithNext(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect KeepWithNext = {read=_scw_get_KeepWithNext, write=put_KeepWithNext};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_LeftIndent() { float __r; HRESULT __hr = get_LeftIndent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float LeftIndent = {read=_scw_get_LeftIndent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_LineSpacing() { float __r; HRESULT __hr = get_LineSpacing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float LineSpacing = {read=_scw_get_LineSpacing};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::LineSpacingRule _scw_get_LineSpacingRule() { Winapi::Commontypes::LineSpacingRule __r; HRESULT __hr = get_LineSpacingRule(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::LineSpacingRule LineSpacingRule = {read=_scw_get_LineSpacingRule};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MarkerAlignment _scw_get_ListAlignment() { Winapi::Commontypes::MarkerAlignment __r; HRESULT __hr = get_ListAlignment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MarkerAlignment ListAlignment = {read=_scw_get_ListAlignment, write=put_ListAlignment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ListLevelIndex() { int __r; HRESULT __hr = get_ListLevelIndex(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ListLevelIndex = {read=_scw_get_ListLevelIndex, write=put_ListLevelIndex};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ListStart() { int __r; HRESULT __hr = get_ListStart(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ListStart = {read=_scw_get_ListStart, write=put_ListStart};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MarkerStyle _scw_get_ListStyle() { Winapi::Commontypes::MarkerStyle __r; HRESULT __hr = get_ListStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MarkerStyle ListStyle = {read=_scw_get_ListStyle, write=put_ListStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_ListTab() { float __r; HRESULT __hr = get_ListTab(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float ListTab = {read=_scw_get_ListTab, write=put_ListTab};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MarkerType _scw_get_ListType() { Winapi::Commontypes::MarkerType __r; HRESULT __hr = get_ListType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MarkerType ListType = {read=_scw_get_ListType, write=put_ListType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_NoLineNumber() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_NoLineNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect NoLineNumber = {read=_scw_get_NoLineNumber, write=put_NoLineNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_PageBreakBefore() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_PageBreakBefore(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect PageBreakBefore = {read=_scw_get_PageBreakBefore, write=put_PageBreakBefore};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_RightIndent() { float __r; HRESULT __hr = get_RightIndent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float RightIndent = {read=_scw_get_RightIndent, write=put_RightIndent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_RightToLeft() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_RightToLeft(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect RightToLeft = {read=_scw_get_RightToLeft, write=put_RightToLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_SpaceAfter() { float __r; HRESULT __hr = get_SpaceAfter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float SpaceAfter = {read=_scw_get_SpaceAfter, write=put_SpaceAfter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_SpaceBefore() { float __r; HRESULT __hr = get_SpaceBefore(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float SpaceBefore = {read=_scw_get_SpaceBefore, write=put_SpaceBefore};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ParagraphStyle _scw_get_Style() { Winapi::Commontypes::ParagraphStyle __r; HRESULT __hr = get_Style(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ParagraphStyle Style = {read=_scw_get_Style, write=put_Style};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_TabCount() { int __r; HRESULT __hr = get_TabCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int TabCount = {read=_scw_get_TabCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FormatEffect _scw_get_WidowControl() { Winapi::Commontypes::FormatEffect __r; HRESULT __hr = get_WidowControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FormatEffect WidowControl = {read=_scw_get_WidowControl, write=put_WidowControl};
};

__interface  INTERFACE_UUID("{5B9E4E57-C072-42A0-8945-AF503EE54768}") ITextRange  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Character(System::WideChar &__get_Character_result) = 0 ;
	virtual HRESULT __safecall put_Character(System::WideChar value) = 0 ;
	virtual HRESULT __safecall get_CharacterFormat(_di_ITextCharacterFormat &__get_CharacterFormat_result) = 0 ;
	virtual HRESULT __safecall put_CharacterFormat(_di_ITextCharacterFormat value) = 0 ;
	virtual HRESULT __safecall get_FormattedText(_di_ITextRange &__get_FormattedText_result) = 0 ;
	virtual HRESULT __safecall put_FormattedText(_di_ITextRange value) = 0 ;
	virtual HRESULT __safecall get_EndPosition(int &__get_EndPosition_result) = 0 ;
	virtual HRESULT __safecall put_EndPosition(int value) = 0 ;
	virtual HRESULT __safecall get_Gravity(Winapi::Commontypes::RangeGravity &__get_Gravity_result) = 0 ;
	virtual HRESULT __safecall put_Gravity(Winapi::Commontypes::RangeGravity value) = 0 ;
	virtual HRESULT __safecall get_Length(int &__get_Length_result) = 0 ;
	virtual HRESULT __safecall get_Link(HSTRING &__get_Link_result) = 0 ;
	virtual HRESULT __safecall put_Link(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_ParagraphFormat(_di_ITextParagraphFormat &__get_ParagraphFormat_result) = 0 ;
	virtual HRESULT __safecall put_ParagraphFormat(_di_ITextParagraphFormat value) = 0 ;
	virtual HRESULT __safecall get_StartPosition(int &__get_StartPosition_result) = 0 ;
	virtual HRESULT __safecall put_StartPosition(int value) = 0 ;
	virtual HRESULT __safecall get_StoryLength(int &__get_StoryLength_result) = 0 ;
	virtual HRESULT __safecall get_Text(HSTRING &__get_Text_result) = 0 ;
	virtual HRESULT __safecall put_Text(HSTRING value) = 0 ;
	virtual HRESULT __safecall CanPaste(int format, bool &__CanPaste_result) = 0 ;
	virtual HRESULT __safecall ChangeCase(Winapi::Commontypes::LetterCase value) = 0 ;
	virtual HRESULT __safecall Collapse(bool value) = 0 ;
	virtual HRESULT __safecall Copy() = 0 ;
	virtual HRESULT __safecall Cut() = 0 ;
	virtual HRESULT __safecall Delete(Winapi::Commontypes::TextRangeUnit unit, int count, int &__Delete_result) = 0 ;
	virtual HRESULT __safecall EndOf(Winapi::Commontypes::TextRangeUnit unit, bool extend, int &__EndOf_result) = 0 ;
	virtual HRESULT __safecall Expand(Winapi::Commontypes::TextRangeUnit unit, int &__Expand_result) = 0 ;
	virtual HRESULT __safecall FindText(HSTRING value, int scanLength, Winapi::Commontypes::FindOptions options, int &__FindText_result) = 0 ;
	virtual HRESULT __safecall GetCharacterUtf32(/* out */ unsigned &value, int offset) = 0 ;
	virtual HRESULT __safecall GetClone(_di_ITextRange &__GetClone_result) = 0 ;
	virtual HRESULT __safecall GetIndex(Winapi::Commontypes::TextRangeUnit unit, int &__GetIndex_result) = 0 ;
	virtual HRESULT __safecall GetPoint(Winapi::Commontypes::HorizontalCharacterAlignment horizontalAlign, Winapi::Commontypes::VerticalCharacterAlignment verticalAlign, Winapi::Commontypes::PointOptions options, /* out */ System::Types::TPointF &point) = 0 ;
	virtual HRESULT __safecall GetRect(Winapi::Commontypes::PointOptions options, /* out */ System::Types::TRectF &rect, /* out */ int &hit) = 0 ;
	virtual HRESULT __safecall GetText(Winapi::Commontypes::TextGetOptions options, /* out */ HSTRING &value) = 0 ;
	virtual HRESULT __safecall GetTextViaStream(Winapi::Commontypes::TextGetOptions options, Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall InRange(_di_ITextRange range, bool &__InRange_result) = 0 ;
	virtual HRESULT __safecall InsertImage(int width, int height, int ascent, Winapi::Commontypes::VerticalCharacterAlignment verticalAlign, HSTRING alternateText, Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall InStory(_di_ITextRange range, bool &__InStory_result) = 0 ;
	virtual HRESULT __safecall IsEqual(_di_ITextRange range, bool &__IsEqual_result) = 0 ;
	virtual HRESULT __safecall Move(Winapi::Commontypes::TextRangeUnit unit, int count, int &__Move_result) = 0 ;
	virtual HRESULT __safecall MoveEnd(Winapi::Commontypes::TextRangeUnit unit, int count, int &__MoveEnd_result) = 0 ;
	virtual HRESULT __safecall MoveStart(Winapi::Commontypes::TextRangeUnit unit, int count, int &__MoveStart_result) = 0 ;
	virtual HRESULT __safecall Paste(int format) = 0 ;
	virtual HRESULT __safecall ScrollIntoView(Winapi::Commontypes::PointOptions value) = 0 ;
	virtual HRESULT __safecall MatchSelection() = 0 ;
	virtual HRESULT __safecall SetIndex(Winapi::Commontypes::TextRangeUnit unit, int index, bool extend) = 0 ;
	virtual HRESULT __safecall SetPoint(System::Types::TPointF point, Winapi::Commontypes::PointOptions options, bool extend) = 0 ;
	virtual HRESULT __safecall SetRange(int startPosition, int endPosition) = 0 ;
	virtual HRESULT __safecall SetText(Winapi::Commontypes::TextSetOptions options, HSTRING value) = 0 ;
	virtual HRESULT __safecall SetTextViaStream(Winapi::Commontypes::TextSetOptions options, Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall StartOf(Winapi::Commontypes::TextRangeUnit unit, bool extend, int &__StartOf_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideChar _scw_get_Character() { System::WideChar __r; HRESULT __hr = get_Character(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideChar Character = {read=_scw_get_Character, write=put_Character};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITextCharacterFormat _scw_get_CharacterFormat() { _di_ITextCharacterFormat __r; HRESULT __hr = get_CharacterFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ITextCharacterFormat CharacterFormat = {read=_scw_get_CharacterFormat, write=put_CharacterFormat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_EndPosition() { int __r; HRESULT __hr = get_EndPosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int EndPosition = {read=_scw_get_EndPosition, write=put_EndPosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITextRange _scw_get_FormattedText() { _di_ITextRange __r; HRESULT __hr = get_FormattedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ITextRange FormattedText = {read=_scw_get_FormattedText, write=put_FormattedText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::RangeGravity _scw_get_Gravity() { Winapi::Commontypes::RangeGravity __r; HRESULT __hr = get_Gravity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::RangeGravity Gravity = {read=_scw_get_Gravity, write=put_Gravity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Length() { int __r; HRESULT __hr = get_Length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Length = {read=_scw_get_Length};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Link() { HSTRING __r; HRESULT __hr = get_Link(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Link = {read=_scw_get_Link, write=put_Link};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITextParagraphFormat _scw_get_ParagraphFormat() { _di_ITextParagraphFormat __r; HRESULT __hr = get_ParagraphFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ITextParagraphFormat ParagraphFormat = {read=_scw_get_ParagraphFormat, write=put_ParagraphFormat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_StartPosition() { int __r; HRESULT __hr = get_StartPosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int StartPosition = {read=_scw_get_StartPosition, write=put_StartPosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_StoryLength() { int __r; HRESULT __hr = get_StoryLength(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int StoryLength = {read=_scw_get_StoryLength};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Text() { HSTRING __r; HRESULT __hr = get_Text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Text = {read=_scw_get_Text, write=put_Text};
};

__interface  INTERFACE_UUID("{A6D36724-F28F-430A-B2CF-C343671EC0E9}") ITextSelection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Options(Winapi::Commontypes::SelectionOptions &__get_Options_result) = 0 ;
	virtual HRESULT __safecall put_Options(Winapi::Commontypes::SelectionOptions value) = 0 ;
	virtual HRESULT __safecall get_Type(Winapi::Commontypes::SelectionType &__get_Type_result) = 0 ;
	virtual HRESULT __safecall EndKey(Winapi::Commontypes::TextRangeUnit unit, bool extend, int &__EndKey_result) = 0 ;
	virtual HRESULT __safecall HomeKey(Winapi::Commontypes::TextRangeUnit unit, bool extend, int &__HomeKey_result) = 0 ;
	virtual HRESULT __safecall MoveDown(Winapi::Commontypes::TextRangeUnit unit, int count, bool extend, int &__MoveDown_result) = 0 ;
	virtual HRESULT __safecall MoveLeft(Winapi::Commontypes::TextRangeUnit unit, int count, bool extend, int &__MoveLeft_result) = 0 ;
	virtual HRESULT __safecall MoveRight(Winapi::Commontypes::TextRangeUnit unit, int count, bool extend, int &__MoveRight_result) = 0 ;
	virtual HRESULT __safecall MoveUp(Winapi::Commontypes::TextRangeUnit unit, int count, bool extend, int &__MoveUp_result) = 0 ;
	virtual HRESULT __safecall TypeText(HSTRING value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SelectionOptions _scw_get_Options() { Winapi::Commontypes::SelectionOptions __r; HRESULT __hr = get_Options(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SelectionOptions Options = {read=_scw_get_Options, write=put_Options};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SelectionType _scw_get_Type() { Winapi::Commontypes::SelectionType __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SelectionType Type = {read=_scw_get_Type};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__UnderlineType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::UnderlineType &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnderlineType _scw_get_Value() { Winapi::Commontypes::UnderlineType __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnderlineType Value = {read=_scw_get_Value};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Text */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_TextHPP
