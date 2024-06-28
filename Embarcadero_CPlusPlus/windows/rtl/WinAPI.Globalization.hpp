// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Globalization.pas' rev: 34.00 (Windows)

#ifndef Winapi_GlobalizationHPP
#define Winapi_GlobalizationHPP

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
namespace Globalization
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ILanguage;
typedef System::DelphiInterface<ILanguage> _di_ILanguage;
__interface DELPHIINTERFACE IIterator_1__ILanguage_Base;
typedef System::DelphiInterface<IIterator_1__ILanguage_Base> _di_IIterator_1__ILanguage_Base;
__interface DELPHIINTERFACE IIterator_1__ILanguage;
typedef System::DelphiInterface<IIterator_1__ILanguage> _di_IIterator_1__ILanguage;
__interface DELPHIINTERFACE IIterable_1__ILanguage_Base;
typedef System::DelphiInterface<IIterable_1__ILanguage_Base> _di_IIterable_1__ILanguage_Base;
__interface DELPHIINTERFACE IIterable_1__ILanguage;
typedef System::DelphiInterface<IIterable_1__ILanguage> _di_IIterable_1__ILanguage;
__interface DELPHIINTERFACE IVectorView_1__ILanguage;
typedef System::DelphiInterface<IVectorView_1__ILanguage> _di_IVectorView_1__ILanguage;
__interface DELPHIINTERFACE Fonts_ILanguageFont;
typedef System::DelphiInterface<Fonts_ILanguageFont> _di_Fonts_ILanguageFont;
__interface DELPHIINTERFACE Fonts_ILanguageFontGroup;
typedef System::DelphiInterface<Fonts_ILanguageFontGroup> _di_Fonts_ILanguageFontGroup;
__interface DELPHIINTERFACE Fonts_ILanguageFontGroupFactory;
typedef System::DelphiInterface<Fonts_ILanguageFontGroupFactory> _di_Fonts_ILanguageFontGroupFactory;
__interface DELPHIINTERFACE ICalendarIdentifiersStatics;
typedef System::DelphiInterface<ICalendarIdentifiersStatics> _di_ICalendarIdentifiersStatics;
__interface DELPHIINTERFACE ICalendarIdentifiersStatics2;
typedef System::DelphiInterface<ICalendarIdentifiersStatics2> _di_ICalendarIdentifiersStatics2;
__interface DELPHIINTERFACE ICalendarIdentifiersStatics3;
typedef System::DelphiInterface<ICalendarIdentifiersStatics3> _di_ICalendarIdentifiersStatics3;
__interface DELPHIINTERFACE IClockIdentifiersStatics;
typedef System::DelphiInterface<IClockIdentifiersStatics> _di_IClockIdentifiersStatics;
__interface DELPHIINTERFACE INumeralSystemIdentifiersStatics;
typedef System::DelphiInterface<INumeralSystemIdentifiersStatics> _di_INumeralSystemIdentifiersStatics;
__interface DELPHIINTERFACE INumeralSystemIdentifiersStatics2;
typedef System::DelphiInterface<INumeralSystemIdentifiersStatics2> _di_INumeralSystemIdentifiersStatics2;
__interface DELPHIINTERFACE ICurrencyIdentifiersStatics;
typedef System::DelphiInterface<ICurrencyIdentifiersStatics> _di_ICurrencyIdentifiersStatics;
__interface DELPHIINTERFACE ICurrencyIdentifiersStatics2;
typedef System::DelphiInterface<ICurrencyIdentifiersStatics2> _di_ICurrencyIdentifiersStatics2;
__interface DELPHIINTERFACE IIterator_1__HSTRING;
typedef System::DelphiInterface<IIterator_1__HSTRING> _di_IIterator_1__HSTRING;
__interface DELPHIINTERFACE IIterable_1__HSTRING;
typedef System::DelphiInterface<IIterable_1__HSTRING> _di_IIterable_1__HSTRING;
__interface DELPHIINTERFACE IVectorView_1__HSTRING;
typedef System::DelphiInterface<IVectorView_1__HSTRING> _di_IVectorView_1__HSTRING;
__interface DELPHIINTERFACE IGeographicRegion;
typedef System::DelphiInterface<IGeographicRegion> _di_IGeographicRegion;
__interface DELPHIINTERFACE IGeographicRegionFactory;
typedef System::DelphiInterface<IGeographicRegionFactory> _di_IGeographicRegionFactory;
__interface DELPHIINTERFACE IGeographicRegionStatics;
typedef System::DelphiInterface<IGeographicRegionStatics> _di_IGeographicRegionStatics;
__interface DELPHIINTERFACE ILanguageExtensionSubtags;
typedef System::DelphiInterface<ILanguageExtensionSubtags> _di_ILanguageExtensionSubtags;
__interface DELPHIINTERFACE ILanguageFactory;
typedef System::DelphiInterface<ILanguageFactory> _di_ILanguageFactory;
__interface DELPHIINTERFACE ILanguageStatics;
typedef System::DelphiInterface<ILanguageStatics> _di_ILanguageStatics;
__interface DELPHIINTERFACE ILanguageStatics2;
typedef System::DelphiInterface<ILanguageStatics2> _di_ILanguageStatics2;
__interface DELPHIINTERFACE DateTimeFormatting_IDateTimeFormatter;
typedef System::DelphiInterface<DateTimeFormatting_IDateTimeFormatter> _di_DateTimeFormatting_IDateTimeFormatter;
__interface DELPHIINTERFACE DateTimeFormatting_IDateTimeFormatterFactory;
typedef System::DelphiInterface<DateTimeFormatting_IDateTimeFormatterFactory> _di_DateTimeFormatting_IDateTimeFormatterFactory;
__interface DELPHIINTERFACE DateTimeFormatting_IDateTimeFormatterStatics;
typedef System::DelphiInterface<DateTimeFormatting_IDateTimeFormatterStatics> _di_DateTimeFormatting_IDateTimeFormatterStatics;
__interface DELPHIINTERFACE DateTimeFormatting_IDateTimeFormatter2;
typedef System::DelphiInterface<DateTimeFormatting_IDateTimeFormatter2> _di_DateTimeFormatting_IDateTimeFormatter2;
__interface DELPHIINTERFACE ICalendar;
typedef System::DelphiInterface<ICalendar> _di_ICalendar;
__interface DELPHIINTERFACE ICalendarFactory2;
typedef System::DelphiInterface<ICalendarFactory2> _di_ICalendarFactory2;
__interface DELPHIINTERFACE ITimeZoneOnCalendar;
typedef System::DelphiInterface<ITimeZoneOnCalendar> _di_ITimeZoneOnCalendar;
__interface DELPHIINTERFACE ICalendarFactory;
typedef System::DelphiInterface<ICalendarFactory> _di_ICalendarFactory;
__interface DELPHIINTERFACE NumberFormatting_INumberRounder;
typedef System::DelphiInterface<NumberFormatting_INumberRounder> _di_NumberFormatting_INumberRounder;
__interface DELPHIINTERFACE NumberFormatting_ISignificantDigitsNumberRounder;
typedef System::DelphiInterface<NumberFormatting_ISignificantDigitsNumberRounder> _di_NumberFormatting_ISignificantDigitsNumberRounder;
__interface DELPHIINTERFACE NumberFormatting_IIncrementNumberRounder;
typedef System::DelphiInterface<NumberFormatting_IIncrementNumberRounder> _di_NumberFormatting_IIncrementNumberRounder;
__interface DELPHIINTERFACE NumberFormatting_INumberFormatter;
typedef System::DelphiInterface<NumberFormatting_INumberFormatter> _di_NumberFormatting_INumberFormatter;
__interface DELPHIINTERFACE NumberFormatting_INumberFormatter2;
typedef System::DelphiInterface<NumberFormatting_INumberFormatter2> _di_NumberFormatting_INumberFormatter2;
__interface DELPHIINTERFACE IReference_1__Int64;
typedef System::DelphiInterface<IReference_1__Int64> _di_IReference_1__Int64;
__interface DELPHIINTERFACE IReference_1__UInt64;
typedef System::DelphiInterface<IReference_1__UInt64> _di_IReference_1__UInt64;
__interface DELPHIINTERFACE IReference_1__Double;
typedef System::DelphiInterface<IReference_1__Double> _di_IReference_1__Double;
__interface DELPHIINTERFACE NumberFormatting_INumberParser;
typedef System::DelphiInterface<NumberFormatting_INumberParser> _di_NumberFormatting_INumberParser;
__interface DELPHIINTERFACE NumberFormatting_INumberFormatterOptions;
typedef System::DelphiInterface<NumberFormatting_INumberFormatterOptions> _di_NumberFormatting_INumberFormatterOptions;
__interface DELPHIINTERFACE NumberFormatting_ISignificantDigitsOption;
typedef System::DelphiInterface<NumberFormatting_ISignificantDigitsOption> _di_NumberFormatting_ISignificantDigitsOption;
__interface DELPHIINTERFACE NumberFormatting_INumberRounderOption;
typedef System::DelphiInterface<NumberFormatting_INumberRounderOption> _di_NumberFormatting_INumberRounderOption;
__interface DELPHIINTERFACE NumberFormatting_ISignedZeroOption;
typedef System::DelphiInterface<NumberFormatting_ISignedZeroOption> _di_NumberFormatting_ISignedZeroOption;
__interface DELPHIINTERFACE NumberFormatting_IDecimalFormatterFactory;
typedef System::DelphiInterface<NumberFormatting_IDecimalFormatterFactory> _di_NumberFormatting_IDecimalFormatterFactory;
__interface DELPHIINTERFACE NumberFormatting_IPercentFormatterFactory;
typedef System::DelphiInterface<NumberFormatting_IPercentFormatterFactory> _di_NumberFormatting_IPercentFormatterFactory;
__interface DELPHIINTERFACE NumberFormatting_IPermilleFormatterFactory;
typedef System::DelphiInterface<NumberFormatting_IPermilleFormatterFactory> _di_NumberFormatting_IPermilleFormatterFactory;
__interface DELPHIINTERFACE NumberFormatting_ICurrencyFormatter;
typedef System::DelphiInterface<NumberFormatting_ICurrencyFormatter> _di_NumberFormatting_ICurrencyFormatter;
__interface DELPHIINTERFACE NumberFormatting_ICurrencyFormatterFactory;
typedef System::DelphiInterface<NumberFormatting_ICurrencyFormatterFactory> _di_NumberFormatting_ICurrencyFormatterFactory;
__interface DELPHIINTERFACE NumberFormatting_ICurrencyFormatter2;
typedef System::DelphiInterface<NumberFormatting_ICurrencyFormatter2> _di_NumberFormatting_ICurrencyFormatter2;
__interface DELPHIINTERFACE NumberFormatting_INumeralSystemTranslator;
typedef System::DelphiInterface<NumberFormatting_INumeralSystemTranslator> _di_NumberFormatting_INumeralSystemTranslator;
__interface DELPHIINTERFACE NumberFormatting_INumeralSystemTranslatorFactory;
typedef System::DelphiInterface<NumberFormatting_INumeralSystemTranslatorFactory> _di_NumberFormatting_INumeralSystemTranslatorFactory;
__interface DELPHIINTERFACE Collation_ICharacterGrouping;
typedef System::DelphiInterface<Collation_ICharacterGrouping> _di_Collation_ICharacterGrouping;
__interface DELPHIINTERFACE IIterator_1__Collation_ICharacterGrouping_Base;
typedef System::DelphiInterface<IIterator_1__Collation_ICharacterGrouping_Base> _di_IIterator_1__Collation_ICharacterGrouping_Base;
__interface DELPHIINTERFACE IIterator_1__Collation_ICharacterGrouping;
typedef System::DelphiInterface<IIterator_1__Collation_ICharacterGrouping> _di_IIterator_1__Collation_ICharacterGrouping;
__interface DELPHIINTERFACE IIterable_1__Collation_ICharacterGrouping_Base;
typedef System::DelphiInterface<IIterable_1__Collation_ICharacterGrouping_Base> _di_IIterable_1__Collation_ICharacterGrouping_Base;
__interface DELPHIINTERFACE IIterable_1__Collation_ICharacterGrouping;
typedef System::DelphiInterface<IIterable_1__Collation_ICharacterGrouping> _di_IIterable_1__Collation_ICharacterGrouping;
__interface DELPHIINTERFACE IVectorView_1__Collation_ICharacterGrouping;
typedef System::DelphiInterface<IVectorView_1__Collation_ICharacterGrouping> _di_IVectorView_1__Collation_ICharacterGrouping;
__interface DELPHIINTERFACE Collation_ICharacterGroupings;
typedef System::DelphiInterface<Collation_ICharacterGroupings> _di_Collation_ICharacterGroupings;
__interface DELPHIINTERFACE Collation_ICharacterGroupingsFactory;
typedef System::DelphiInterface<Collation_ICharacterGroupingsFactory> _di_Collation_ICharacterGroupingsFactory;
__interface DELPHIINTERFACE IVector_1__ILanguage;
typedef System::DelphiInterface<IVector_1__ILanguage> _di_IVector_1__ILanguage;
class DELPHICLASS TFonts_LanguageFontGroup;
class DELPHICLASS TCalendarIdentifiers;
class DELPHICLASS TClockIdentifiers;
class DELPHICLASS TNumeralSystemIdentifiers;
class DELPHICLASS TCurrencyIdentifiers;
class DELPHICLASS TGeographicRegion;
class DELPHICLASS TLanguage;
class DELPHICLASS TDateTimeFormatting_DateTimeFormatter;
class DELPHICLASS TCalendar;
class DELPHICLASS TNumberFormatting_SignificantDigitsNumberRounder;
class DELPHICLASS TNumberFormatting_IncrementNumberRounder;
class DELPHICLASS TNumberFormatting_DecimalFormatter;
class DELPHICLASS TNumberFormatting_PercentFormatter;
class DELPHICLASS TNumberFormatting_PermilleFormatter;
class DELPHICLASS TNumberFormatting_CurrencyFormatter;
class DELPHICLASS TNumberFormatting_NumeralSystemTranslator;
class DELPHICLASS TCollation_CharacterGroupings;
//-- type declarations -------------------------------------------------------
typedef _di_ILanguage *PILanguage;

typedef _di_IIterator_1__ILanguage *PIIterator_1__ILanguage;

typedef _di_IIterable_1__ILanguage *PIIterable_1__ILanguage;

typedef _di_IVectorView_1__ILanguage *PIVectorView_1__ILanguage;

typedef _di_Fonts_ILanguageFont *PFonts_ILanguageFont;

typedef _di_Fonts_ILanguageFontGroup *PFonts_ILanguageFontGroup;

typedef _di_Fonts_ILanguageFontGroupFactory *PFonts_ILanguageFontGroupFactory;

typedef _di_ICalendarIdentifiersStatics *PICalendarIdentifiersStatics;

typedef _di_ICalendarIdentifiersStatics2 *PICalendarIdentifiersStatics2;

typedef _di_ICalendarIdentifiersStatics3 *PICalendarIdentifiersStatics3;

typedef _di_IClockIdentifiersStatics *PIClockIdentifiersStatics;

typedef _di_INumeralSystemIdentifiersStatics *PINumeralSystemIdentifiersStatics;

typedef _di_INumeralSystemIdentifiersStatics2 *PINumeralSystemIdentifiersStatics2;

typedef _di_ICurrencyIdentifiersStatics *PICurrencyIdentifiersStatics;

typedef _di_ICurrencyIdentifiersStatics2 *PICurrencyIdentifiersStatics2;

typedef _di_IIterator_1__HSTRING *PIIterator_1__HSTRING;

typedef _di_IIterable_1__HSTRING *PIIterable_1__HSTRING;

typedef _di_IVectorView_1__HSTRING *PIVectorView_1__HSTRING;

typedef _di_IGeographicRegion *PIGeographicRegion;

typedef _di_IGeographicRegionFactory *PIGeographicRegionFactory;

typedef _di_IGeographicRegionStatics *PIGeographicRegionStatics;

typedef _di_ILanguageExtensionSubtags *PILanguageExtensionSubtags;

typedef _di_ILanguageFactory *PILanguageFactory;

typedef _di_ILanguageStatics *PILanguageStatics;

typedef _di_ILanguageStatics2 *PILanguageStatics2;

typedef _di_DateTimeFormatting_IDateTimeFormatter *PDateTimeFormatting_IDateTimeFormatter;

typedef _di_DateTimeFormatting_IDateTimeFormatterFactory *PDateTimeFormatting_IDateTimeFormatterFactory;

typedef _di_DateTimeFormatting_IDateTimeFormatterStatics *PDateTimeFormatting_IDateTimeFormatterStatics;

typedef _di_DateTimeFormatting_IDateTimeFormatter2 *PDateTimeFormatting_IDateTimeFormatter2;

typedef _di_ICalendar *PICalendar;

typedef _di_ICalendarFactory2 *PICalendarFactory2;

typedef _di_ITimeZoneOnCalendar *PITimeZoneOnCalendar;

typedef _di_ICalendarFactory *PICalendarFactory;

typedef _di_NumberFormatting_INumberRounder *PNumberFormatting_INumberRounder;

typedef _di_NumberFormatting_ISignificantDigitsNumberRounder *PNumberFormatting_ISignificantDigitsNumberRounder;

typedef _di_NumberFormatting_IIncrementNumberRounder *PNumberFormatting_IIncrementNumberRounder;

typedef _di_NumberFormatting_INumberFormatter *PNumberFormatting_INumberFormatter;

typedef _di_NumberFormatting_INumberFormatter2 *PNumberFormatting_INumberFormatter2;

typedef _di_IReference_1__Int64 *PIReference_1__Int64;

typedef _di_IReference_1__UInt64 *PIReference_1__UInt64;

typedef _di_IReference_1__Double *PIReference_1__Double;

typedef _di_NumberFormatting_INumberParser *PNumberFormatting_INumberParser;

typedef _di_NumberFormatting_INumberFormatterOptions *PNumberFormatting_INumberFormatterOptions;

typedef _di_NumberFormatting_ISignificantDigitsOption *PNumberFormatting_ISignificantDigitsOption;

typedef _di_NumberFormatting_INumberRounderOption *PNumberFormatting_INumberRounderOption;

typedef _di_NumberFormatting_ISignedZeroOption *PNumberFormatting_ISignedZeroOption;

typedef _di_NumberFormatting_IDecimalFormatterFactory *PNumberFormatting_IDecimalFormatterFactory;

typedef _di_NumberFormatting_IPercentFormatterFactory *PNumberFormatting_IPercentFormatterFactory;

typedef _di_NumberFormatting_IPermilleFormatterFactory *PNumberFormatting_IPermilleFormatterFactory;

typedef _di_NumberFormatting_ICurrencyFormatter *PNumberFormatting_ICurrencyFormatter;

typedef _di_NumberFormatting_ICurrencyFormatterFactory *PNumberFormatting_ICurrencyFormatterFactory;

typedef _di_NumberFormatting_ICurrencyFormatter2 *PNumberFormatting_ICurrencyFormatter2;

typedef _di_NumberFormatting_INumeralSystemTranslator *PNumberFormatting_INumeralSystemTranslator;

typedef _di_NumberFormatting_INumeralSystemTranslatorFactory *PNumberFormatting_INumeralSystemTranslatorFactory;

typedef _di_Collation_ICharacterGrouping *PCollation_ICharacterGrouping;

typedef _di_IIterator_1__Collation_ICharacterGrouping *PIIterator_1__Collation_ICharacterGrouping;

typedef _di_IIterable_1__Collation_ICharacterGrouping *PIIterable_1__Collation_ICharacterGrouping;

typedef _di_IVectorView_1__Collation_ICharacterGrouping *PIVectorView_1__Collation_ICharacterGrouping;

typedef _di_Collation_ICharacterGroupings *PCollation_ICharacterGroupings;

typedef _di_Collation_ICharacterGroupingsFactory *PCollation_ICharacterGroupingsFactory;

typedef _di_IVector_1__ILanguage *PIVector_1__ILanguage;

__interface  INTERFACE_UUID("{EA79A752-F7C2-4265-B1BD-C4DEC4E4F080}") ILanguage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LanguageTag(HSTRING &__get_LanguageTag_result) = 0 ;
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall get_NativeName(HSTRING &__get_NativeName_result) = 0 ;
	virtual HRESULT __safecall get_Script(HSTRING &__get_Script_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LanguageTag() { HSTRING __r; HRESULT __hr = get_LanguageTag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LanguageTag = {read=_scw_get_LanguageTag};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NativeName() { HSTRING __r; HRESULT __hr = get_NativeName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NativeName = {read=_scw_get_NativeName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Script() { HSTRING __r; HRESULT __hr = get_Script(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Script = {read=_scw_get_Script};
};

__interface  INTERFACE_UUID("{30E99AE6-F414-5243-8DB2-AAB38EA3F1F1}") IIterator_1__ILanguage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C694EAFE-7DDE-5F3B-8EEB-6CAEC9334596}") IIterator_1__ILanguage  : public IIterator_1__ILanguage_Base 
{
	virtual HRESULT __safecall get_Current(_di_ILanguage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PILanguage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILanguage _scw_get_Current() { _di_ILanguage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILanguage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{48409A10-61B6-5DB1-A69D-8ABC46AC608A}") IIterable_1__ILanguage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D2AC9471-BA9D-5DE8-8E64-8B7FE5FBBA15}") IIterable_1__ILanguage  : public IIterable_1__ILanguage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ILanguage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9026F0A6-FDC5-55A7-BEE7-500E55ECBC3F}") IVectorView_1__ILanguage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ILanguage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ILanguage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PILanguage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{B12E5C3A-B76D-459B-BEEB-901151CD77D1}") Fonts_ILanguageFont  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_FontFamily(HSTRING &__get_FontFamily_result) = 0 ;
	virtual HRESULT __safecall get_FontWeight(Winapi::Commontypes::FontWeight &__get_FontWeight_result) = 0 ;
	virtual HRESULT __safecall get_FontStretch(Winapi::Commontypes::FontStretch &__get_FontStretch_result) = 0 ;
	virtual HRESULT __safecall get_FontStyle(Winapi::Commontypes::FontStyle &__get_FontStyle_result) = 0 ;
	virtual HRESULT __safecall get_ScaleFactor(double &__get_ScaleFactor_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_FontFamily() { HSTRING __r; HRESULT __hr = get_FontFamily(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING FontFamily = {read=_scw_get_FontFamily};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FontStretch _scw_get_FontStretch() { Winapi::Commontypes::FontStretch __r; HRESULT __hr = get_FontStretch(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FontStretch FontStretch = {read=_scw_get_FontStretch};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FontStyle _scw_get_FontStyle() { Winapi::Commontypes::FontStyle __r; HRESULT __hr = get_FontStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FontStyle FontStyle = {read=_scw_get_FontStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FontWeight _scw_get_FontWeight() { Winapi::Commontypes::FontWeight __r; HRESULT __hr = get_FontWeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FontWeight FontWeight = {read=_scw_get_FontWeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_ScaleFactor() { double __r; HRESULT __hr = get_ScaleFactor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double ScaleFactor = {read=_scw_get_ScaleFactor};
};

__interface  INTERFACE_UUID("{F33A7FC3-3A5C-4AEA-B9FF-B39FB242F7F6}") Fonts_ILanguageFontGroup  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UITextFont(_di_Fonts_ILanguageFont &__get_UITextFont_result) = 0 ;
	virtual HRESULT __safecall get_UIHeadingFont(_di_Fonts_ILanguageFont &__get_UIHeadingFont_result) = 0 ;
	virtual HRESULT __safecall get_UITitleFont(_di_Fonts_ILanguageFont &__get_UITitleFont_result) = 0 ;
	virtual HRESULT __safecall get_UICaptionFont(_di_Fonts_ILanguageFont &__get_UICaptionFont_result) = 0 ;
	virtual HRESULT __safecall get_UINotificationHeadingFont(_di_Fonts_ILanguageFont &__get_UINotificationHeadingFont_result) = 0 ;
	virtual HRESULT __safecall get_TraditionalDocumentFont(_di_Fonts_ILanguageFont &__get_TraditionalDocumentFont_result) = 0 ;
	virtual HRESULT __safecall get_ModernDocumentFont(_di_Fonts_ILanguageFont &__get_ModernDocumentFont_result) = 0 ;
	virtual HRESULT __safecall get_DocumentHeadingFont(_di_Fonts_ILanguageFont &__get_DocumentHeadingFont_result) = 0 ;
	virtual HRESULT __safecall get_FixedWidthTextFont(_di_Fonts_ILanguageFont &__get_FixedWidthTextFont_result) = 0 ;
	virtual HRESULT __safecall get_DocumentAlternate1Font(_di_Fonts_ILanguageFont &__get_DocumentAlternate1Font_result) = 0 ;
	virtual HRESULT __safecall get_DocumentAlternate2Font(_di_Fonts_ILanguageFont &__get_DocumentAlternate2Font_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_DocumentAlternate1Font() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_DocumentAlternate1Font(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont DocumentAlternate1Font = {read=_scw_get_DocumentAlternate1Font};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_DocumentAlternate2Font() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_DocumentAlternate2Font(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont DocumentAlternate2Font = {read=_scw_get_DocumentAlternate2Font};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_DocumentHeadingFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_DocumentHeadingFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont DocumentHeadingFont = {read=_scw_get_DocumentHeadingFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_FixedWidthTextFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_FixedWidthTextFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont FixedWidthTextFont = {read=_scw_get_FixedWidthTextFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_ModernDocumentFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_ModernDocumentFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont ModernDocumentFont = {read=_scw_get_ModernDocumentFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_TraditionalDocumentFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_TraditionalDocumentFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont TraditionalDocumentFont = {read=_scw_get_TraditionalDocumentFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_UICaptionFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_UICaptionFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont UICaptionFont = {read=_scw_get_UICaptionFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_UIHeadingFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_UIHeadingFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont UIHeadingFont = {read=_scw_get_UIHeadingFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_UINotificationHeadingFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_UINotificationHeadingFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont UINotificationHeadingFont = {read=_scw_get_UINotificationHeadingFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_UITextFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_UITextFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont UITextFont = {read=_scw_get_UITextFont};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fonts_ILanguageFont _scw_get_UITitleFont() { _di_Fonts_ILanguageFont __r; HRESULT __hr = get_UITitleFont(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fonts_ILanguageFont UITitleFont = {read=_scw_get_UITitleFont};
};

__interface  INTERFACE_UUID("{FCAEAC67-4E77-49C7-B856-DDE934FC735B}") Fonts_ILanguageFontGroupFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateLanguageFontGroup(HSTRING languageTag, _di_Fonts_ILanguageFontGroup &__CreateLanguageFontGroup_result) = 0 ;
};

__interface  INTERFACE_UUID("{80653F68-2CB2-4C1F-B590-F0F52BF4FD1A}") ICalendarIdentifiersStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Gregorian(HSTRING &__get_Gregorian_result) = 0 ;
	virtual HRESULT __safecall get_Hebrew(HSTRING &__get_Hebrew_result) = 0 ;
	virtual HRESULT __safecall get_Hijri(HSTRING &__get_Hijri_result) = 0 ;
	virtual HRESULT __safecall get_Japanese(HSTRING &__get_Japanese_result) = 0 ;
	virtual HRESULT __safecall get_Julian(HSTRING &__get_Julian_result) = 0 ;
	virtual HRESULT __safecall get_Korean(HSTRING &__get_Korean_result) = 0 ;
	virtual HRESULT __safecall get_Taiwan(HSTRING &__get_Taiwan_result) = 0 ;
	virtual HRESULT __safecall get_Thai(HSTRING &__get_Thai_result) = 0 ;
	virtual HRESULT __safecall get_UmAlQura(HSTRING &__get_UmAlQura_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Gregorian() { HSTRING __r; HRESULT __hr = get_Gregorian(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Gregorian = {read=_scw_get_Gregorian};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Hebrew() { HSTRING __r; HRESULT __hr = get_Hebrew(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Hebrew = {read=_scw_get_Hebrew};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Hijri() { HSTRING __r; HRESULT __hr = get_Hijri(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Hijri = {read=_scw_get_Hijri};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Japanese() { HSTRING __r; HRESULT __hr = get_Japanese(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Japanese = {read=_scw_get_Japanese};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Julian() { HSTRING __r; HRESULT __hr = get_Julian(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Julian = {read=_scw_get_Julian};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Korean() { HSTRING __r; HRESULT __hr = get_Korean(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Korean = {read=_scw_get_Korean};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Taiwan() { HSTRING __r; HRESULT __hr = get_Taiwan(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Taiwan = {read=_scw_get_Taiwan};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Thai() { HSTRING __r; HRESULT __hr = get_Thai(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Thai = {read=_scw_get_Thai};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UmAlQura() { HSTRING __r; HRESULT __hr = get_UmAlQura(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UmAlQura = {read=_scw_get_UmAlQura};
};

__interface  INTERFACE_UUID("{7DF4D488-5FD0-42A7-95B5-7D98D823075F}") ICalendarIdentifiersStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Persian(HSTRING &__get_Persian_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Persian() { HSTRING __r; HRESULT __hr = get_Persian(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Persian = {read=_scw_get_Persian};
};

__interface  INTERFACE_UUID("{2C225423-1FAD-40C0-9334-A8EB90DB04F5}") ICalendarIdentifiersStatics3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ChineseLunar(HSTRING &__get_ChineseLunar_result) = 0 ;
	virtual HRESULT __safecall get_JapaneseLunar(HSTRING &__get_JapaneseLunar_result) = 0 ;
	virtual HRESULT __safecall get_KoreanLunar(HSTRING &__get_KoreanLunar_result) = 0 ;
	virtual HRESULT __safecall get_TaiwanLunar(HSTRING &__get_TaiwanLunar_result) = 0 ;
	virtual HRESULT __safecall get_VietnameseLunar(HSTRING &__get_VietnameseLunar_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ChineseLunar() { HSTRING __r; HRESULT __hr = get_ChineseLunar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ChineseLunar = {read=_scw_get_ChineseLunar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_JapaneseLunar() { HSTRING __r; HRESULT __hr = get_JapaneseLunar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING JapaneseLunar = {read=_scw_get_JapaneseLunar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KoreanLunar() { HSTRING __r; HRESULT __hr = get_KoreanLunar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KoreanLunar = {read=_scw_get_KoreanLunar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TaiwanLunar() { HSTRING __r; HRESULT __hr = get_TaiwanLunar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TaiwanLunar = {read=_scw_get_TaiwanLunar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_VietnameseLunar() { HSTRING __r; HRESULT __hr = get_VietnameseLunar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING VietnameseLunar = {read=_scw_get_VietnameseLunar};
};

__interface  INTERFACE_UUID("{523805BB-12EC-4F83-BC31-B1B4376B0808}") IClockIdentifiersStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_TwelveHour(HSTRING &__get_TwelveHour_result) = 0 ;
	virtual HRESULT __safecall get_TwentyFourHour(HSTRING &__get_TwentyFourHour_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TwelveHour() { HSTRING __r; HRESULT __hr = get_TwelveHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TwelveHour = {read=_scw_get_TwelveHour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TwentyFourHour() { HSTRING __r; HRESULT __hr = get_TwentyFourHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TwentyFourHour = {read=_scw_get_TwentyFourHour};
};

__interface  INTERFACE_UUID("{A5C662C3-68C9-4D3D-B765-972029E21DEC}") INumeralSystemIdentifiersStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Arab(HSTRING &__get_Arab_result) = 0 ;
	virtual HRESULT __safecall get_ArabExt(HSTRING &__get_ArabExt_result) = 0 ;
	virtual HRESULT __safecall get_Bali(HSTRING &__get_Bali_result) = 0 ;
	virtual HRESULT __safecall get_Beng(HSTRING &__get_Beng_result) = 0 ;
	virtual HRESULT __safecall get_Cham(HSTRING &__get_Cham_result) = 0 ;
	virtual HRESULT __safecall get_Deva(HSTRING &__get_Deva_result) = 0 ;
	virtual HRESULT __safecall get_FullWide(HSTRING &__get_FullWide_result) = 0 ;
	virtual HRESULT __safecall get_Gujr(HSTRING &__get_Gujr_result) = 0 ;
	virtual HRESULT __safecall get_Guru(HSTRING &__get_Guru_result) = 0 ;
	virtual HRESULT __safecall get_HaniDec(HSTRING &__get_HaniDec_result) = 0 ;
	virtual HRESULT __safecall get_Java(HSTRING &__get_Java_result) = 0 ;
	virtual HRESULT __safecall get_Kali(HSTRING &__get_Kali_result) = 0 ;
	virtual HRESULT __safecall get_Khmr(HSTRING &__get_Khmr_result) = 0 ;
	virtual HRESULT __safecall get_Knda(HSTRING &__get_Knda_result) = 0 ;
	virtual HRESULT __safecall get_Lana(HSTRING &__get_Lana_result) = 0 ;
	virtual HRESULT __safecall get_LanaTham(HSTRING &__get_LanaTham_result) = 0 ;
	virtual HRESULT __safecall get_Laoo(HSTRING &__get_Laoo_result) = 0 ;
	virtual HRESULT __safecall get_Latn(HSTRING &__get_Latn_result) = 0 ;
	virtual HRESULT __safecall get_Lepc(HSTRING &__get_Lepc_result) = 0 ;
	virtual HRESULT __safecall get_Limb(HSTRING &__get_Limb_result) = 0 ;
	virtual HRESULT __safecall get_Mlym(HSTRING &__get_Mlym_result) = 0 ;
	virtual HRESULT __safecall get_Mong(HSTRING &__get_Mong_result) = 0 ;
	virtual HRESULT __safecall get_Mtei(HSTRING &__get_Mtei_result) = 0 ;
	virtual HRESULT __safecall get_Mymr(HSTRING &__get_Mymr_result) = 0 ;
	virtual HRESULT __safecall get_MymrShan(HSTRING &__get_MymrShan_result) = 0 ;
	virtual HRESULT __safecall get_Nkoo(HSTRING &__get_Nkoo_result) = 0 ;
	virtual HRESULT __safecall get_Olck(HSTRING &__get_Olck_result) = 0 ;
	virtual HRESULT __safecall get_Orya(HSTRING &__get_Orya_result) = 0 ;
	virtual HRESULT __safecall get_Saur(HSTRING &__get_Saur_result) = 0 ;
	virtual HRESULT __safecall get_Sund(HSTRING &__get_Sund_result) = 0 ;
	virtual HRESULT __safecall get_Talu(HSTRING &__get_Talu_result) = 0 ;
	virtual HRESULT __safecall get_TamlDec(HSTRING &__get_TamlDec_result) = 0 ;
	virtual HRESULT __safecall get_Telu(HSTRING &__get_Telu_result) = 0 ;
	virtual HRESULT __safecall get_Thai(HSTRING &__get_Thai_result) = 0 ;
	virtual HRESULT __safecall get_Tibt(HSTRING &__get_Tibt_result) = 0 ;
	virtual HRESULT __safecall get_Vaii(HSTRING &__get_Vaii_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Arab() { HSTRING __r; HRESULT __hr = get_Arab(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Arab = {read=_scw_get_Arab};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ArabExt() { HSTRING __r; HRESULT __hr = get_ArabExt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ArabExt = {read=_scw_get_ArabExt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Bali() { HSTRING __r; HRESULT __hr = get_Bali(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Bali = {read=_scw_get_Bali};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Beng() { HSTRING __r; HRESULT __hr = get_Beng(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Beng = {read=_scw_get_Beng};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Cham() { HSTRING __r; HRESULT __hr = get_Cham(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Cham = {read=_scw_get_Cham};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Deva() { HSTRING __r; HRESULT __hr = get_Deva(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Deva = {read=_scw_get_Deva};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_FullWide() { HSTRING __r; HRESULT __hr = get_FullWide(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING FullWide = {read=_scw_get_FullWide};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Gujr() { HSTRING __r; HRESULT __hr = get_Gujr(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Gujr = {read=_scw_get_Gujr};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Guru() { HSTRING __r; HRESULT __hr = get_Guru(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Guru = {read=_scw_get_Guru};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HaniDec() { HSTRING __r; HRESULT __hr = get_HaniDec(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HaniDec = {read=_scw_get_HaniDec};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Java() { HSTRING __r; HRESULT __hr = get_Java(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Java = {read=_scw_get_Java};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Kali() { HSTRING __r; HRESULT __hr = get_Kali(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Kali = {read=_scw_get_Kali};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Khmr() { HSTRING __r; HRESULT __hr = get_Khmr(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Khmr = {read=_scw_get_Khmr};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Knda() { HSTRING __r; HRESULT __hr = get_Knda(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Knda = {read=_scw_get_Knda};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Lana() { HSTRING __r; HRESULT __hr = get_Lana(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Lana = {read=_scw_get_Lana};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LanaTham() { HSTRING __r; HRESULT __hr = get_LanaTham(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LanaTham = {read=_scw_get_LanaTham};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Laoo() { HSTRING __r; HRESULT __hr = get_Laoo(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Laoo = {read=_scw_get_Laoo};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Latn() { HSTRING __r; HRESULT __hr = get_Latn(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Latn = {read=_scw_get_Latn};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Lepc() { HSTRING __r; HRESULT __hr = get_Lepc(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Lepc = {read=_scw_get_Lepc};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Limb() { HSTRING __r; HRESULT __hr = get_Limb(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Limb = {read=_scw_get_Limb};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Mlym() { HSTRING __r; HRESULT __hr = get_Mlym(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Mlym = {read=_scw_get_Mlym};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Mong() { HSTRING __r; HRESULT __hr = get_Mong(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Mong = {read=_scw_get_Mong};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Mtei() { HSTRING __r; HRESULT __hr = get_Mtei(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Mtei = {read=_scw_get_Mtei};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Mymr() { HSTRING __r; HRESULT __hr = get_Mymr(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Mymr = {read=_scw_get_Mymr};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MymrShan() { HSTRING __r; HRESULT __hr = get_MymrShan(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MymrShan = {read=_scw_get_MymrShan};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Nkoo() { HSTRING __r; HRESULT __hr = get_Nkoo(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Nkoo = {read=_scw_get_Nkoo};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Olck() { HSTRING __r; HRESULT __hr = get_Olck(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Olck = {read=_scw_get_Olck};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Orya() { HSTRING __r; HRESULT __hr = get_Orya(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Orya = {read=_scw_get_Orya};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Saur() { HSTRING __r; HRESULT __hr = get_Saur(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Saur = {read=_scw_get_Saur};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Sund() { HSTRING __r; HRESULT __hr = get_Sund(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Sund = {read=_scw_get_Sund};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Talu() { HSTRING __r; HRESULT __hr = get_Talu(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Talu = {read=_scw_get_Talu};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TamlDec() { HSTRING __r; HRESULT __hr = get_TamlDec(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TamlDec = {read=_scw_get_TamlDec};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Telu() { HSTRING __r; HRESULT __hr = get_Telu(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Telu = {read=_scw_get_Telu};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Thai() { HSTRING __r; HRESULT __hr = get_Thai(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Thai = {read=_scw_get_Thai};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Tibt() { HSTRING __r; HRESULT __hr = get_Tibt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Tibt = {read=_scw_get_Tibt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Vaii() { HSTRING __r; HRESULT __hr = get_Vaii(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Vaii = {read=_scw_get_Vaii};
};

__interface  INTERFACE_UUID("{7F003228-9DDB-4A34-9104-0260C091A7C7}") INumeralSystemIdentifiersStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Brah(HSTRING &__get_Brah_result) = 0 ;
	virtual HRESULT __safecall get_Osma(HSTRING &__get_Osma_result) = 0 ;
	virtual HRESULT __safecall get_MathBold(HSTRING &__get_MathBold_result) = 0 ;
	virtual HRESULT __safecall get_MathDbl(HSTRING &__get_MathDbl_result) = 0 ;
	virtual HRESULT __safecall get_MathSans(HSTRING &__get_MathSans_result) = 0 ;
	virtual HRESULT __safecall get_MathSanb(HSTRING &__get_MathSanb_result) = 0 ;
	virtual HRESULT __safecall get_MathMono(HSTRING &__get_MathMono_result) = 0 ;
	virtual HRESULT __safecall get_ZmthBold(HSTRING &__get_ZmthBold_result) = 0 ;
	virtual HRESULT __safecall get_ZmthDbl(HSTRING &__get_ZmthDbl_result) = 0 ;
	virtual HRESULT __safecall get_ZmthSans(HSTRING &__get_ZmthSans_result) = 0 ;
	virtual HRESULT __safecall get_ZmthSanb(HSTRING &__get_ZmthSanb_result) = 0 ;
	virtual HRESULT __safecall get_ZmthMono(HSTRING &__get_ZmthMono_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Brah() { HSTRING __r; HRESULT __hr = get_Brah(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Brah = {read=_scw_get_Brah};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MathBold() { HSTRING __r; HRESULT __hr = get_MathBold(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MathBold = {read=_scw_get_MathBold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MathDbl() { HSTRING __r; HRESULT __hr = get_MathDbl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MathDbl = {read=_scw_get_MathDbl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MathMono() { HSTRING __r; HRESULT __hr = get_MathMono(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MathMono = {read=_scw_get_MathMono};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MathSanb() { HSTRING __r; HRESULT __hr = get_MathSanb(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MathSanb = {read=_scw_get_MathSanb};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MathSans() { HSTRING __r; HRESULT __hr = get_MathSans(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MathSans = {read=_scw_get_MathSans};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Osma() { HSTRING __r; HRESULT __hr = get_Osma(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Osma = {read=_scw_get_Osma};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZmthBold() { HSTRING __r; HRESULT __hr = get_ZmthBold(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZmthBold = {read=_scw_get_ZmthBold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZmthDbl() { HSTRING __r; HRESULT __hr = get_ZmthDbl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZmthDbl = {read=_scw_get_ZmthDbl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZmthMono() { HSTRING __r; HRESULT __hr = get_ZmthMono(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZmthMono = {read=_scw_get_ZmthMono};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZmthSanb() { HSTRING __r; HRESULT __hr = get_ZmthSanb(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZmthSanb = {read=_scw_get_ZmthSanb};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZmthSans() { HSTRING __r; HRESULT __hr = get_ZmthSans(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZmthSans = {read=_scw_get_ZmthSans};
};

__interface  INTERFACE_UUID("{9F1D091B-D586-4913-9B6A-A9BD2DC12874}") ICurrencyIdentifiersStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AED(HSTRING &__get_AED_result) = 0 ;
	virtual HRESULT __safecall get_AFN(HSTRING &__get_AFN_result) = 0 ;
	virtual HRESULT __safecall get_ALL(HSTRING &__get_ALL_result) = 0 ;
	virtual HRESULT __safecall get_AMD(HSTRING &__get_AMD_result) = 0 ;
	virtual HRESULT __safecall get_ANG(HSTRING &__get_ANG_result) = 0 ;
	virtual HRESULT __safecall get_AOA(HSTRING &__get_AOA_result) = 0 ;
	virtual HRESULT __safecall get_ARS(HSTRING &__get_ARS_result) = 0 ;
	virtual HRESULT __safecall get_AUD(HSTRING &__get_AUD_result) = 0 ;
	virtual HRESULT __safecall get_AWG(HSTRING &__get_AWG_result) = 0 ;
	virtual HRESULT __safecall get_AZN(HSTRING &__get_AZN_result) = 0 ;
	virtual HRESULT __safecall get_BAM(HSTRING &__get_BAM_result) = 0 ;
	virtual HRESULT __safecall get_BBD(HSTRING &__get_BBD_result) = 0 ;
	virtual HRESULT __safecall get_BDT(HSTRING &__get_BDT_result) = 0 ;
	virtual HRESULT __safecall get_BGN(HSTRING &__get_BGN_result) = 0 ;
	virtual HRESULT __safecall get_BHD(HSTRING &__get_BHD_result) = 0 ;
	virtual HRESULT __safecall get_BIF(HSTRING &__get_BIF_result) = 0 ;
	virtual HRESULT __safecall get_BMD(HSTRING &__get_BMD_result) = 0 ;
	virtual HRESULT __safecall get_BND(HSTRING &__get_BND_result) = 0 ;
	virtual HRESULT __safecall get_BOB(HSTRING &__get_BOB_result) = 0 ;
	virtual HRESULT __safecall get_BRL(HSTRING &__get_BRL_result) = 0 ;
	virtual HRESULT __safecall get_BSD(HSTRING &__get_BSD_result) = 0 ;
	virtual HRESULT __safecall get_BTN(HSTRING &__get_BTN_result) = 0 ;
	virtual HRESULT __safecall get_BWP(HSTRING &__get_BWP_result) = 0 ;
	virtual HRESULT __safecall get_BYR(HSTRING &__get_BYR_result) = 0 ;
	virtual HRESULT __safecall get_BZD(HSTRING &__get_BZD_result) = 0 ;
	virtual HRESULT __safecall get_CAD(HSTRING &__get_CAD_result) = 0 ;
	virtual HRESULT __safecall get_CDF(HSTRING &__get_CDF_result) = 0 ;
	virtual HRESULT __safecall get_CHF(HSTRING &__get_CHF_result) = 0 ;
	virtual HRESULT __safecall get_CLP(HSTRING &__get_CLP_result) = 0 ;
	virtual HRESULT __safecall get_CNY(HSTRING &__get_CNY_result) = 0 ;
	virtual HRESULT __safecall get_COP(HSTRING &__get_COP_result) = 0 ;
	virtual HRESULT __safecall get_CRC(HSTRING &__get_CRC_result) = 0 ;
	virtual HRESULT __safecall get_CUP(HSTRING &__get_CUP_result) = 0 ;
	virtual HRESULT __safecall get_CVE(HSTRING &__get_CVE_result) = 0 ;
	virtual HRESULT __safecall get_CZK(HSTRING &__get_CZK_result) = 0 ;
	virtual HRESULT __safecall get_DJF(HSTRING &__get_DJF_result) = 0 ;
	virtual HRESULT __safecall get_DKK(HSTRING &__get_DKK_result) = 0 ;
	virtual HRESULT __safecall get_DOP(HSTRING &__get_DOP_result) = 0 ;
	virtual HRESULT __safecall get_DZD(HSTRING &__get_DZD_result) = 0 ;
	virtual HRESULT __safecall get_EGP(HSTRING &__get_EGP_result) = 0 ;
	virtual HRESULT __safecall get_ERN(HSTRING &__get_ERN_result) = 0 ;
	virtual HRESULT __safecall get_ETB(HSTRING &__get_ETB_result) = 0 ;
	virtual HRESULT __safecall get_EUR(HSTRING &__get_EUR_result) = 0 ;
	virtual HRESULT __safecall get_FJD(HSTRING &__get_FJD_result) = 0 ;
	virtual HRESULT __safecall get_FKP(HSTRING &__get_FKP_result) = 0 ;
	virtual HRESULT __safecall get_GBP(HSTRING &__get_GBP_result) = 0 ;
	virtual HRESULT __safecall get_GEL(HSTRING &__get_GEL_result) = 0 ;
	virtual HRESULT __safecall get_GHS(HSTRING &__get_GHS_result) = 0 ;
	virtual HRESULT __safecall get_GIP(HSTRING &__get_GIP_result) = 0 ;
	virtual HRESULT __safecall get_GMD(HSTRING &__get_GMD_result) = 0 ;
	virtual HRESULT __safecall get_GNF(HSTRING &__get_GNF_result) = 0 ;
	virtual HRESULT __safecall get_GTQ(HSTRING &__get_GTQ_result) = 0 ;
	virtual HRESULT __safecall get_GYD(HSTRING &__get_GYD_result) = 0 ;
	virtual HRESULT __safecall get_HKD(HSTRING &__get_HKD_result) = 0 ;
	virtual HRESULT __safecall get_HNL(HSTRING &__get_HNL_result) = 0 ;
	virtual HRESULT __safecall get_HRK(HSTRING &__get_HRK_result) = 0 ;
	virtual HRESULT __safecall get_HTG(HSTRING &__get_HTG_result) = 0 ;
	virtual HRESULT __safecall get_HUF(HSTRING &__get_HUF_result) = 0 ;
	virtual HRESULT __safecall get_IDR(HSTRING &__get_IDR_result) = 0 ;
	virtual HRESULT __safecall get_ILS(HSTRING &__get_ILS_result) = 0 ;
	virtual HRESULT __safecall get_INR(HSTRING &__get_INR_result) = 0 ;
	virtual HRESULT __safecall get_IQD(HSTRING &__get_IQD_result) = 0 ;
	virtual HRESULT __safecall get_IRR(HSTRING &__get_IRR_result) = 0 ;
	virtual HRESULT __safecall get_ISK(HSTRING &__get_ISK_result) = 0 ;
	virtual HRESULT __safecall get_JMD(HSTRING &__get_JMD_result) = 0 ;
	virtual HRESULT __safecall get_JOD(HSTRING &__get_JOD_result) = 0 ;
	virtual HRESULT __safecall get_JPY(HSTRING &__get_JPY_result) = 0 ;
	virtual HRESULT __safecall get_KES(HSTRING &__get_KES_result) = 0 ;
	virtual HRESULT __safecall get_KGS(HSTRING &__get_KGS_result) = 0 ;
	virtual HRESULT __safecall get_KHR(HSTRING &__get_KHR_result) = 0 ;
	virtual HRESULT __safecall get_KMF(HSTRING &__get_KMF_result) = 0 ;
	virtual HRESULT __safecall get_KPW(HSTRING &__get_KPW_result) = 0 ;
	virtual HRESULT __safecall get_KRW(HSTRING &__get_KRW_result) = 0 ;
	virtual HRESULT __safecall get_KWD(HSTRING &__get_KWD_result) = 0 ;
	virtual HRESULT __safecall get_KYD(HSTRING &__get_KYD_result) = 0 ;
	virtual HRESULT __safecall get_KZT(HSTRING &__get_KZT_result) = 0 ;
	virtual HRESULT __safecall get_LAK(HSTRING &__get_LAK_result) = 0 ;
	virtual HRESULT __safecall get_LBP(HSTRING &__get_LBP_result) = 0 ;
	virtual HRESULT __safecall get_LKR(HSTRING &__get_LKR_result) = 0 ;
	virtual HRESULT __safecall get_LRD(HSTRING &__get_LRD_result) = 0 ;
	virtual HRESULT __safecall get_LSL(HSTRING &__get_LSL_result) = 0 ;
	virtual HRESULT __safecall get_LTL(HSTRING &__get_LTL_result) = 0 ;
	virtual HRESULT __safecall get_LVL(HSTRING &__get_LVL_result) = 0 ;
	virtual HRESULT __safecall get_LYD(HSTRING &__get_LYD_result) = 0 ;
	virtual HRESULT __safecall get_MAD(HSTRING &__get_MAD_result) = 0 ;
	virtual HRESULT __safecall get_MDL(HSTRING &__get_MDL_result) = 0 ;
	virtual HRESULT __safecall get_MGA(HSTRING &__get_MGA_result) = 0 ;
	virtual HRESULT __safecall get_MKD(HSTRING &__get_MKD_result) = 0 ;
	virtual HRESULT __safecall get_MMK(HSTRING &__get_MMK_result) = 0 ;
	virtual HRESULT __safecall get_MNT(HSTRING &__get_MNT_result) = 0 ;
	virtual HRESULT __safecall get_MOP(HSTRING &__get_MOP_result) = 0 ;
	virtual HRESULT __safecall get_MRO(HSTRING &__get_MRO_result) = 0 ;
	virtual HRESULT __safecall get_MUR(HSTRING &__get_MUR_result) = 0 ;
	virtual HRESULT __safecall get_MVR(HSTRING &__get_MVR_result) = 0 ;
	virtual HRESULT __safecall get_MWK(HSTRING &__get_MWK_result) = 0 ;
	virtual HRESULT __safecall get_MXN(HSTRING &__get_MXN_result) = 0 ;
	virtual HRESULT __safecall get_MYR(HSTRING &__get_MYR_result) = 0 ;
	virtual HRESULT __safecall get_MZN(HSTRING &__get_MZN_result) = 0 ;
	virtual HRESULT __safecall get_NAD(HSTRING &__get_NAD_result) = 0 ;
	virtual HRESULT __safecall get_NGN(HSTRING &__get_NGN_result) = 0 ;
	virtual HRESULT __safecall get_NIO(HSTRING &__get_NIO_result) = 0 ;
	virtual HRESULT __safecall get_NOK(HSTRING &__get_NOK_result) = 0 ;
	virtual HRESULT __safecall get_NPR(HSTRING &__get_NPR_result) = 0 ;
	virtual HRESULT __safecall get_NZD(HSTRING &__get_NZD_result) = 0 ;
	virtual HRESULT __safecall get_OMR(HSTRING &__get_OMR_result) = 0 ;
	virtual HRESULT __safecall get_PAB(HSTRING &__get_PAB_result) = 0 ;
	virtual HRESULT __safecall get_PEN(HSTRING &__get_PEN_result) = 0 ;
	virtual HRESULT __safecall get_PGK(HSTRING &__get_PGK_result) = 0 ;
	virtual HRESULT __safecall get_PHP(HSTRING &__get_PHP_result) = 0 ;
	virtual HRESULT __safecall get_PKR(HSTRING &__get_PKR_result) = 0 ;
	virtual HRESULT __safecall get_PLN(HSTRING &__get_PLN_result) = 0 ;
	virtual HRESULT __safecall get_PYG(HSTRING &__get_PYG_result) = 0 ;
	virtual HRESULT __safecall get_QAR(HSTRING &__get_QAR_result) = 0 ;
	virtual HRESULT __safecall get_RON(HSTRING &__get_RON_result) = 0 ;
	virtual HRESULT __safecall get_RSD(HSTRING &__get_RSD_result) = 0 ;
	virtual HRESULT __safecall get_RUB(HSTRING &__get_RUB_result) = 0 ;
	virtual HRESULT __safecall get_RWF(HSTRING &__get_RWF_result) = 0 ;
	virtual HRESULT __safecall get_SAR(HSTRING &__get_SAR_result) = 0 ;
	virtual HRESULT __safecall get_SBD(HSTRING &__get_SBD_result) = 0 ;
	virtual HRESULT __safecall get_SCR(HSTRING &__get_SCR_result) = 0 ;
	virtual HRESULT __safecall get_SDG(HSTRING &__get_SDG_result) = 0 ;
	virtual HRESULT __safecall get_SEK(HSTRING &__get_SEK_result) = 0 ;
	virtual HRESULT __safecall get_SGD(HSTRING &__get_SGD_result) = 0 ;
	virtual HRESULT __safecall get_SHP(HSTRING &__get_SHP_result) = 0 ;
	virtual HRESULT __safecall get_SLL(HSTRING &__get_SLL_result) = 0 ;
	virtual HRESULT __safecall get_SOS(HSTRING &__get_SOS_result) = 0 ;
	virtual HRESULT __safecall get_SRD(HSTRING &__get_SRD_result) = 0 ;
	virtual HRESULT __safecall get_STD(HSTRING &__get_STD_result) = 0 ;
	virtual HRESULT __safecall get_SYP(HSTRING &__get_SYP_result) = 0 ;
	virtual HRESULT __safecall get_SZL(HSTRING &__get_SZL_result) = 0 ;
	virtual HRESULT __safecall get_THB(HSTRING &__get_THB_result) = 0 ;
	virtual HRESULT __safecall get_TJS(HSTRING &__get_TJS_result) = 0 ;
	virtual HRESULT __safecall get_TMT(HSTRING &__get_TMT_result) = 0 ;
	virtual HRESULT __safecall get_TND(HSTRING &__get_TND_result) = 0 ;
	virtual HRESULT __safecall get_TOP(HSTRING &__get_TOP_result) = 0 ;
	virtual HRESULT __safecall get_TRY(HSTRING &__get_TRY_result) = 0 ;
	virtual HRESULT __safecall get_TTD(HSTRING &__get_TTD_result) = 0 ;
	virtual HRESULT __safecall get_TWD(HSTRING &__get_TWD_result) = 0 ;
	virtual HRESULT __safecall get_TZS(HSTRING &__get_TZS_result) = 0 ;
	virtual HRESULT __safecall get_UAH(HSTRING &__get_UAH_result) = 0 ;
	virtual HRESULT __safecall get_UGX(HSTRING &__get_UGX_result) = 0 ;
	virtual HRESULT __safecall get_USD(HSTRING &__get_USD_result) = 0 ;
	virtual HRESULT __safecall get_UYU(HSTRING &__get_UYU_result) = 0 ;
	virtual HRESULT __safecall get_UZS(HSTRING &__get_UZS_result) = 0 ;
	virtual HRESULT __safecall get_VEF(HSTRING &__get_VEF_result) = 0 ;
	virtual HRESULT __safecall get_VND(HSTRING &__get_VND_result) = 0 ;
	virtual HRESULT __safecall get_VUV(HSTRING &__get_VUV_result) = 0 ;
	virtual HRESULT __safecall get_WST(HSTRING &__get_WST_result) = 0 ;
	virtual HRESULT __safecall get_XAF(HSTRING &__get_XAF_result) = 0 ;
	virtual HRESULT __safecall get_XCD(HSTRING &__get_XCD_result) = 0 ;
	virtual HRESULT __safecall get_XOF(HSTRING &__get_XOF_result) = 0 ;
	virtual HRESULT __safecall get_XPF(HSTRING &__get_XPF_result) = 0 ;
	virtual HRESULT __safecall get_XXX(HSTRING &__get_XXX_result) = 0 ;
	virtual HRESULT __safecall get_YER(HSTRING &__get_YER_result) = 0 ;
	virtual HRESULT __safecall get_ZAR(HSTRING &__get_ZAR_result) = 0 ;
	virtual HRESULT __safecall get_ZMW(HSTRING &__get_ZMW_result) = 0 ;
	virtual HRESULT __safecall get_ZWL(HSTRING &__get_ZWL_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AED() { HSTRING __r; HRESULT __hr = get_AED(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AED = {read=_scw_get_AED};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AFN() { HSTRING __r; HRESULT __hr = get_AFN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AFN = {read=_scw_get_AFN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ALL() { HSTRING __r; HRESULT __hr = get_ALL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ALL = {read=_scw_get_ALL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AMD() { HSTRING __r; HRESULT __hr = get_AMD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AMD = {read=_scw_get_AMD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ANG() { HSTRING __r; HRESULT __hr = get_ANG(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ANG = {read=_scw_get_ANG};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AOA() { HSTRING __r; HRESULT __hr = get_AOA(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AOA = {read=_scw_get_AOA};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ARS() { HSTRING __r; HRESULT __hr = get_ARS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ARS = {read=_scw_get_ARS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AUD() { HSTRING __r; HRESULT __hr = get_AUD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AUD = {read=_scw_get_AUD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AWG() { HSTRING __r; HRESULT __hr = get_AWG(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AWG = {read=_scw_get_AWG};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AZN() { HSTRING __r; HRESULT __hr = get_AZN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AZN = {read=_scw_get_AZN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BAM() { HSTRING __r; HRESULT __hr = get_BAM(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BAM = {read=_scw_get_BAM};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BBD() { HSTRING __r; HRESULT __hr = get_BBD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BBD = {read=_scw_get_BBD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BDT() { HSTRING __r; HRESULT __hr = get_BDT(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BDT = {read=_scw_get_BDT};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BGN() { HSTRING __r; HRESULT __hr = get_BGN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BGN = {read=_scw_get_BGN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BHD() { HSTRING __r; HRESULT __hr = get_BHD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BHD = {read=_scw_get_BHD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BIF() { HSTRING __r; HRESULT __hr = get_BIF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BIF = {read=_scw_get_BIF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BMD() { HSTRING __r; HRESULT __hr = get_BMD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BMD = {read=_scw_get_BMD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BND() { HSTRING __r; HRESULT __hr = get_BND(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BND = {read=_scw_get_BND};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BOB() { HSTRING __r; HRESULT __hr = get_BOB(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BOB = {read=_scw_get_BOB};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BRL() { HSTRING __r; HRESULT __hr = get_BRL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BRL = {read=_scw_get_BRL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BSD() { HSTRING __r; HRESULT __hr = get_BSD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BSD = {read=_scw_get_BSD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BTN() { HSTRING __r; HRESULT __hr = get_BTN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BTN = {read=_scw_get_BTN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BWP() { HSTRING __r; HRESULT __hr = get_BWP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BWP = {read=_scw_get_BWP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BYR() { HSTRING __r; HRESULT __hr = get_BYR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BYR = {read=_scw_get_BYR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BZD() { HSTRING __r; HRESULT __hr = get_BZD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BZD = {read=_scw_get_BZD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CAD() { HSTRING __r; HRESULT __hr = get_CAD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CAD = {read=_scw_get_CAD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CDF() { HSTRING __r; HRESULT __hr = get_CDF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CDF = {read=_scw_get_CDF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CHF() { HSTRING __r; HRESULT __hr = get_CHF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CHF = {read=_scw_get_CHF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CLP() { HSTRING __r; HRESULT __hr = get_CLP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CLP = {read=_scw_get_CLP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CNY() { HSTRING __r; HRESULT __hr = get_CNY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CNY = {read=_scw_get_CNY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_COP() { HSTRING __r; HRESULT __hr = get_COP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING COP = {read=_scw_get_COP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CRC() { HSTRING __r; HRESULT __hr = get_CRC(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CRC = {read=_scw_get_CRC};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CUP() { HSTRING __r; HRESULT __hr = get_CUP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CUP = {read=_scw_get_CUP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CVE() { HSTRING __r; HRESULT __hr = get_CVE(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CVE = {read=_scw_get_CVE};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CZK() { HSTRING __r; HRESULT __hr = get_CZK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CZK = {read=_scw_get_CZK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DJF() { HSTRING __r; HRESULT __hr = get_DJF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DJF = {read=_scw_get_DJF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DKK() { HSTRING __r; HRESULT __hr = get_DKK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DKK = {read=_scw_get_DKK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DOP() { HSTRING __r; HRESULT __hr = get_DOP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DOP = {read=_scw_get_DOP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DZD() { HSTRING __r; HRESULT __hr = get_DZD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DZD = {read=_scw_get_DZD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_EGP() { HSTRING __r; HRESULT __hr = get_EGP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING EGP = {read=_scw_get_EGP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ERN() { HSTRING __r; HRESULT __hr = get_ERN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ERN = {read=_scw_get_ERN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ETB() { HSTRING __r; HRESULT __hr = get_ETB(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ETB = {read=_scw_get_ETB};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_EUR() { HSTRING __r; HRESULT __hr = get_EUR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING EUR = {read=_scw_get_EUR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_FJD() { HSTRING __r; HRESULT __hr = get_FJD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING FJD = {read=_scw_get_FJD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_FKP() { HSTRING __r; HRESULT __hr = get_FKP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING FKP = {read=_scw_get_FKP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GBP() { HSTRING __r; HRESULT __hr = get_GBP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GBP = {read=_scw_get_GBP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GEL() { HSTRING __r; HRESULT __hr = get_GEL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GEL = {read=_scw_get_GEL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GHS() { HSTRING __r; HRESULT __hr = get_GHS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GHS = {read=_scw_get_GHS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GIP() { HSTRING __r; HRESULT __hr = get_GIP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GIP = {read=_scw_get_GIP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GMD() { HSTRING __r; HRESULT __hr = get_GMD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GMD = {read=_scw_get_GMD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GNF() { HSTRING __r; HRESULT __hr = get_GNF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GNF = {read=_scw_get_GNF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GTQ() { HSTRING __r; HRESULT __hr = get_GTQ(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GTQ = {read=_scw_get_GTQ};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GYD() { HSTRING __r; HRESULT __hr = get_GYD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GYD = {read=_scw_get_GYD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HKD() { HSTRING __r; HRESULT __hr = get_HKD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HKD = {read=_scw_get_HKD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HNL() { HSTRING __r; HRESULT __hr = get_HNL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HNL = {read=_scw_get_HNL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HRK() { HSTRING __r; HRESULT __hr = get_HRK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HRK = {read=_scw_get_HRK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HTG() { HSTRING __r; HRESULT __hr = get_HTG(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HTG = {read=_scw_get_HTG};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HUF() { HSTRING __r; HRESULT __hr = get_HUF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HUF = {read=_scw_get_HUF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_IDR() { HSTRING __r; HRESULT __hr = get_IDR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING IDR = {read=_scw_get_IDR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ILS() { HSTRING __r; HRESULT __hr = get_ILS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ILS = {read=_scw_get_ILS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_INR() { HSTRING __r; HRESULT __hr = get_INR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING INR = {read=_scw_get_INR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_IQD() { HSTRING __r; HRESULT __hr = get_IQD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING IQD = {read=_scw_get_IQD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_IRR() { HSTRING __r; HRESULT __hr = get_IRR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING IRR = {read=_scw_get_IRR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ISK() { HSTRING __r; HRESULT __hr = get_ISK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ISK = {read=_scw_get_ISK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_JMD() { HSTRING __r; HRESULT __hr = get_JMD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING JMD = {read=_scw_get_JMD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_JOD() { HSTRING __r; HRESULT __hr = get_JOD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING JOD = {read=_scw_get_JOD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_JPY() { HSTRING __r; HRESULT __hr = get_JPY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING JPY = {read=_scw_get_JPY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KES() { HSTRING __r; HRESULT __hr = get_KES(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KES = {read=_scw_get_KES};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KGS() { HSTRING __r; HRESULT __hr = get_KGS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KGS = {read=_scw_get_KGS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KHR() { HSTRING __r; HRESULT __hr = get_KHR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KHR = {read=_scw_get_KHR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KMF() { HSTRING __r; HRESULT __hr = get_KMF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KMF = {read=_scw_get_KMF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KPW() { HSTRING __r; HRESULT __hr = get_KPW(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KPW = {read=_scw_get_KPW};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KRW() { HSTRING __r; HRESULT __hr = get_KRW(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KRW = {read=_scw_get_KRW};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KWD() { HSTRING __r; HRESULT __hr = get_KWD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KWD = {read=_scw_get_KWD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KYD() { HSTRING __r; HRESULT __hr = get_KYD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KYD = {read=_scw_get_KYD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_KZT() { HSTRING __r; HRESULT __hr = get_KZT(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING KZT = {read=_scw_get_KZT};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LAK() { HSTRING __r; HRESULT __hr = get_LAK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LAK = {read=_scw_get_LAK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LBP() { HSTRING __r; HRESULT __hr = get_LBP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LBP = {read=_scw_get_LBP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LKR() { HSTRING __r; HRESULT __hr = get_LKR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LKR = {read=_scw_get_LKR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LRD() { HSTRING __r; HRESULT __hr = get_LRD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LRD = {read=_scw_get_LRD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LSL() { HSTRING __r; HRESULT __hr = get_LSL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LSL = {read=_scw_get_LSL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LTL() { HSTRING __r; HRESULT __hr = get_LTL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LTL = {read=_scw_get_LTL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LVL() { HSTRING __r; HRESULT __hr = get_LVL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LVL = {read=_scw_get_LVL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LYD() { HSTRING __r; HRESULT __hr = get_LYD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LYD = {read=_scw_get_LYD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MAD() { HSTRING __r; HRESULT __hr = get_MAD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MAD = {read=_scw_get_MAD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MDL() { HSTRING __r; HRESULT __hr = get_MDL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MDL = {read=_scw_get_MDL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MGA() { HSTRING __r; HRESULT __hr = get_MGA(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MGA = {read=_scw_get_MGA};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MKD() { HSTRING __r; HRESULT __hr = get_MKD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MKD = {read=_scw_get_MKD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MMK() { HSTRING __r; HRESULT __hr = get_MMK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MMK = {read=_scw_get_MMK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MNT() { HSTRING __r; HRESULT __hr = get_MNT(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MNT = {read=_scw_get_MNT};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MOP() { HSTRING __r; HRESULT __hr = get_MOP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MOP = {read=_scw_get_MOP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MRO() { HSTRING __r; HRESULT __hr = get_MRO(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MRO = {read=_scw_get_MRO};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MUR() { HSTRING __r; HRESULT __hr = get_MUR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MUR = {read=_scw_get_MUR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MVR() { HSTRING __r; HRESULT __hr = get_MVR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MVR = {read=_scw_get_MVR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MWK() { HSTRING __r; HRESULT __hr = get_MWK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MWK = {read=_scw_get_MWK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MXN() { HSTRING __r; HRESULT __hr = get_MXN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MXN = {read=_scw_get_MXN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MYR() { HSTRING __r; HRESULT __hr = get_MYR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MYR = {read=_scw_get_MYR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MZN() { HSTRING __r; HRESULT __hr = get_MZN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MZN = {read=_scw_get_MZN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NAD() { HSTRING __r; HRESULT __hr = get_NAD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NAD = {read=_scw_get_NAD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NGN() { HSTRING __r; HRESULT __hr = get_NGN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NGN = {read=_scw_get_NGN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NIO() { HSTRING __r; HRESULT __hr = get_NIO(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NIO = {read=_scw_get_NIO};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NOK() { HSTRING __r; HRESULT __hr = get_NOK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NOK = {read=_scw_get_NOK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NPR() { HSTRING __r; HRESULT __hr = get_NPR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NPR = {read=_scw_get_NPR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NZD() { HSTRING __r; HRESULT __hr = get_NZD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NZD = {read=_scw_get_NZD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_OMR() { HSTRING __r; HRESULT __hr = get_OMR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING OMR = {read=_scw_get_OMR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PAB() { HSTRING __r; HRESULT __hr = get_PAB(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PAB = {read=_scw_get_PAB};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PEN() { HSTRING __r; HRESULT __hr = get_PEN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PEN = {read=_scw_get_PEN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PGK() { HSTRING __r; HRESULT __hr = get_PGK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PGK = {read=_scw_get_PGK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PHP() { HSTRING __r; HRESULT __hr = get_PHP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PHP = {read=_scw_get_PHP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PKR() { HSTRING __r; HRESULT __hr = get_PKR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PKR = {read=_scw_get_PKR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PLN() { HSTRING __r; HRESULT __hr = get_PLN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PLN = {read=_scw_get_PLN};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PYG() { HSTRING __r; HRESULT __hr = get_PYG(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PYG = {read=_scw_get_PYG};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_QAR() { HSTRING __r; HRESULT __hr = get_QAR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING QAR = {read=_scw_get_QAR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RON() { HSTRING __r; HRESULT __hr = get_RON(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RON = {read=_scw_get_RON};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RSD() { HSTRING __r; HRESULT __hr = get_RSD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RSD = {read=_scw_get_RSD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RUB() { HSTRING __r; HRESULT __hr = get_RUB(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RUB = {read=_scw_get_RUB};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RWF() { HSTRING __r; HRESULT __hr = get_RWF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RWF = {read=_scw_get_RWF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SAR() { HSTRING __r; HRESULT __hr = get_SAR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SAR = {read=_scw_get_SAR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SBD() { HSTRING __r; HRESULT __hr = get_SBD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SBD = {read=_scw_get_SBD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SCR() { HSTRING __r; HRESULT __hr = get_SCR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SCR = {read=_scw_get_SCR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SDG() { HSTRING __r; HRESULT __hr = get_SDG(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SDG = {read=_scw_get_SDG};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SEK() { HSTRING __r; HRESULT __hr = get_SEK(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SEK = {read=_scw_get_SEK};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SGD() { HSTRING __r; HRESULT __hr = get_SGD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SGD = {read=_scw_get_SGD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SHP() { HSTRING __r; HRESULT __hr = get_SHP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SHP = {read=_scw_get_SHP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SLL() { HSTRING __r; HRESULT __hr = get_SLL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SLL = {read=_scw_get_SLL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SOS() { HSTRING __r; HRESULT __hr = get_SOS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SOS = {read=_scw_get_SOS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SRD() { HSTRING __r; HRESULT __hr = get_SRD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SRD = {read=_scw_get_SRD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_STD() { HSTRING __r; HRESULT __hr = get_STD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING STD = {read=_scw_get_STD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SYP() { HSTRING __r; HRESULT __hr = get_SYP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SYP = {read=_scw_get_SYP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SZL() { HSTRING __r; HRESULT __hr = get_SZL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SZL = {read=_scw_get_SZL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_THB() { HSTRING __r; HRESULT __hr = get_THB(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING THB = {read=_scw_get_THB};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TJS() { HSTRING __r; HRESULT __hr = get_TJS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TJS = {read=_scw_get_TJS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TMT() { HSTRING __r; HRESULT __hr = get_TMT(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TMT = {read=_scw_get_TMT};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TND() { HSTRING __r; HRESULT __hr = get_TND(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TND = {read=_scw_get_TND};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TOP() { HSTRING __r; HRESULT __hr = get_TOP(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TOP = {read=_scw_get_TOP};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TRY() { HSTRING __r; HRESULT __hr = get_TRY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TRY = {read=_scw_get_TRY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TTD() { HSTRING __r; HRESULT __hr = get_TTD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TTD = {read=_scw_get_TTD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TWD() { HSTRING __r; HRESULT __hr = get_TWD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TWD = {read=_scw_get_TWD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_TZS() { HSTRING __r; HRESULT __hr = get_TZS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING TZS = {read=_scw_get_TZS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UAH() { HSTRING __r; HRESULT __hr = get_UAH(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UAH = {read=_scw_get_UAH};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UGX() { HSTRING __r; HRESULT __hr = get_UGX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UGX = {read=_scw_get_UGX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_USD() { HSTRING __r; HRESULT __hr = get_USD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING USD = {read=_scw_get_USD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UYU() { HSTRING __r; HRESULT __hr = get_UYU(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UYU = {read=_scw_get_UYU};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UZS() { HSTRING __r; HRESULT __hr = get_UZS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UZS = {read=_scw_get_UZS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_VEF() { HSTRING __r; HRESULT __hr = get_VEF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING VEF = {read=_scw_get_VEF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_VND() { HSTRING __r; HRESULT __hr = get_VND(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING VND = {read=_scw_get_VND};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_VUV() { HSTRING __r; HRESULT __hr = get_VUV(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING VUV = {read=_scw_get_VUV};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_WST() { HSTRING __r; HRESULT __hr = get_WST(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING WST = {read=_scw_get_WST};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_XAF() { HSTRING __r; HRESULT __hr = get_XAF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING XAF = {read=_scw_get_XAF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_XCD() { HSTRING __r; HRESULT __hr = get_XCD(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING XCD = {read=_scw_get_XCD};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_XOF() { HSTRING __r; HRESULT __hr = get_XOF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING XOF = {read=_scw_get_XOF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_XPF() { HSTRING __r; HRESULT __hr = get_XPF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING XPF = {read=_scw_get_XPF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_XXX() { HSTRING __r; HRESULT __hr = get_XXX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING XXX = {read=_scw_get_XXX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_YER() { HSTRING __r; HRESULT __hr = get_YER(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING YER = {read=_scw_get_YER};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZAR() { HSTRING __r; HRESULT __hr = get_ZAR(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZAR = {read=_scw_get_ZAR};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZMW() { HSTRING __r; HRESULT __hr = get_ZMW(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZMW = {read=_scw_get_ZMW};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ZWL() { HSTRING __r; HRESULT __hr = get_ZWL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ZWL = {read=_scw_get_ZWL};
};

__interface  INTERFACE_UUID("{1814797F-C3B2-4C33-9591-980011950D37}") ICurrencyIdentifiersStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_BYN(HSTRING &__get_BYN_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_BYN() { HSTRING __r; HRESULT __hr = get_BYN(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING BYN = {read=_scw_get_BYN};
};

__interface  INTERFACE_UUID("{8C304EBB-6615-50A4-8829-879ECD443236}") IIterator_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(HSTRING &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Current() { HSTRING __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E2FCC7C1-3BFC-5A0B-B2B0-72E769D1CB7E}") IIterable_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__HSTRING &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2F13C006-A03A-5F69-B090-75A43E33423E}") IVectorView_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, HSTRING &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(HSTRING value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{01E9A621-4A64-4ED9-954F-9EDEB07BD903}") IGeographicRegion  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Code(HSTRING &__get_Code_result) = 0 ;
	virtual HRESULT __safecall get_CodeTwoLetter(HSTRING &__get_CodeTwoLetter_result) = 0 ;
	virtual HRESULT __safecall get_CodeThreeLetter(HSTRING &__get_CodeThreeLetter_result) = 0 ;
	virtual HRESULT __safecall get_CodeThreeDigit(HSTRING &__get_CodeThreeDigit_result) = 0 ;
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall get_NativeName(HSTRING &__get_NativeName_result) = 0 ;
	virtual HRESULT __safecall get_CurrenciesInUse(_di_IVectorView_1__HSTRING &__get_CurrenciesInUse_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Code() { HSTRING __r; HRESULT __hr = get_Code(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Code = {read=_scw_get_Code};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CodeThreeDigit() { HSTRING __r; HRESULT __hr = get_CodeThreeDigit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CodeThreeDigit = {read=_scw_get_CodeThreeDigit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CodeThreeLetter() { HSTRING __r; HRESULT __hr = get_CodeThreeLetter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CodeThreeLetter = {read=_scw_get_CodeThreeLetter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CodeTwoLetter() { HSTRING __r; HRESULT __hr = get_CodeTwoLetter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CodeTwoLetter = {read=_scw_get_CodeTwoLetter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_CurrenciesInUse() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_CurrenciesInUse(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING CurrenciesInUse = {read=_scw_get_CurrenciesInUse};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NativeName() { HSTRING __r; HRESULT __hr = get_NativeName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NativeName = {read=_scw_get_NativeName};
};

__interface  INTERFACE_UUID("{53425270-77B4-426B-859F-81E19D512546}") IGeographicRegionFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateGeographicRegion(HSTRING geographicRegionCode, _di_IGeographicRegion &__CreateGeographicRegion_result) = 0 ;
};

__interface  INTERFACE_UUID("{29E28974-7AD9-4EF4-8799-B3B44FADEC08}") IGeographicRegionStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IsSupported(HSTRING geographicRegionCode, bool &__IsSupported_result) = 0 ;
};

__interface  INTERFACE_UUID("{7D7DAF45-368D-4364-852B-DEC927037B85}") ILanguageExtensionSubtags  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetExtensionSubtags(HSTRING singleton, _di_IVectorView_1__HSTRING &__GetExtensionSubtags_result) = 0 ;
};

__interface  INTERFACE_UUID("{9B0252AC-0C27-44F8-B792-9793FB66C63E}") ILanguageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateLanguage(HSTRING languageTag, _di_ILanguage &__CreateLanguage_result) = 0 ;
};

__interface  INTERFACE_UUID("{B23CD557-0865-46D4-89B8-D59BE8990F0D}") ILanguageStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IsWellFormed(HSTRING languageTag, bool &__IsWellFormed_result) = 0 ;
	virtual HRESULT __safecall get_CurrentInputMethodLanguageTag(HSTRING &__get_CurrentInputMethodLanguageTag_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CurrentInputMethodLanguageTag() { HSTRING __r; HRESULT __hr = get_CurrentInputMethodLanguageTag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CurrentInputMethodLanguageTag = {read=_scw_get_CurrentInputMethodLanguageTag};
};

__interface  INTERFACE_UUID("{30199F6E-914B-4B2A-9D6E-E3B0E27DBE4F}") ILanguageStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall TrySetInputMethodLanguageTag(HSTRING languageTag, bool &__TrySetInputMethodLanguageTag_result) = 0 ;
};

__interface  INTERFACE_UUID("{95EECA10-73E0-4E4B-A183-3D6AD0BA35EC}") DateTimeFormatting_IDateTimeFormatter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Languages(_di_IVectorView_1__HSTRING &__get_Languages_result) = 0 ;
	virtual HRESULT __safecall get_GeographicRegion(HSTRING &__get_GeographicRegion_result) = 0 ;
	virtual HRESULT __safecall get_Calendar(HSTRING &__get_Calendar_result) = 0 ;
	virtual HRESULT __safecall get_Clock(HSTRING &__get_Clock_result) = 0 ;
	virtual HRESULT __safecall get_NumeralSystem(HSTRING &__get_NumeralSystem_result) = 0 ;
	virtual HRESULT __safecall put_NumeralSystem(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Patterns(_di_IVectorView_1__HSTRING &__get_Patterns_result) = 0 ;
	virtual HRESULT __safecall get_Template(HSTRING &__get_Template_result) = 0 ;
	virtual HRESULT __safecall Format(Winapi::Commontypes::DateTime value, HSTRING &__Format_result) = 0 ;
	virtual HRESULT __safecall get_IncludeYear(Winapi::Commontypes::DateTimeFormatting_YearFormat &__get_IncludeYear_result) = 0 ;
	virtual HRESULT __safecall get_IncludeMonth(Winapi::Commontypes::DateTimeFormatting_MonthFormat &__get_IncludeMonth_result) = 0 ;
	virtual HRESULT __safecall get_IncludeDayOfWeek(Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat &__get_IncludeDayOfWeek_result) = 0 ;
	virtual HRESULT __safecall get_IncludeDay(Winapi::Commontypes::DateTimeFormatting_DayFormat &__get_IncludeDay_result) = 0 ;
	virtual HRESULT __safecall get_IncludeHour(Winapi::Commontypes::DateTimeFormatting_HourFormat &__get_IncludeHour_result) = 0 ;
	virtual HRESULT __safecall get_IncludeMinute(Winapi::Commontypes::DateTimeFormatting_MinuteFormat &__get_IncludeMinute_result) = 0 ;
	virtual HRESULT __safecall get_IncludeSecond(Winapi::Commontypes::DateTimeFormatting_SecondFormat &__get_IncludeSecond_result) = 0 ;
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall get_ResolvedGeographicRegion(HSTRING &__get_ResolvedGeographicRegion_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Calendar() { HSTRING __r; HRESULT __hr = get_Calendar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Calendar = {read=_scw_get_Calendar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Clock() { HSTRING __r; HRESULT __hr = get_Clock(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Clock = {read=_scw_get_Clock};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GeographicRegion() { HSTRING __r; HRESULT __hr = get_GeographicRegion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GeographicRegion = {read=_scw_get_GeographicRegion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_DayFormat _scw_get_IncludeDay() { Winapi::Commontypes::DateTimeFormatting_DayFormat __r; HRESULT __hr = get_IncludeDay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_DayFormat IncludeDay = {read=_scw_get_IncludeDay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat _scw_get_IncludeDayOfWeek() { Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat __r; HRESULT __hr = get_IncludeDayOfWeek(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat IncludeDayOfWeek = {read=_scw_get_IncludeDayOfWeek};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_HourFormat _scw_get_IncludeHour() { Winapi::Commontypes::DateTimeFormatting_HourFormat __r; HRESULT __hr = get_IncludeHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_HourFormat IncludeHour = {read=_scw_get_IncludeHour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_MinuteFormat _scw_get_IncludeMinute() { Winapi::Commontypes::DateTimeFormatting_MinuteFormat __r; HRESULT __hr = get_IncludeMinute(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_MinuteFormat IncludeMinute = {read=_scw_get_IncludeMinute};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_MonthFormat _scw_get_IncludeMonth() { Winapi::Commontypes::DateTimeFormatting_MonthFormat __r; HRESULT __hr = get_IncludeMonth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_MonthFormat IncludeMonth = {read=_scw_get_IncludeMonth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_SecondFormat _scw_get_IncludeSecond() { Winapi::Commontypes::DateTimeFormatting_SecondFormat __r; HRESULT __hr = get_IncludeSecond(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_SecondFormat IncludeSecond = {read=_scw_get_IncludeSecond};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTimeFormatting_YearFormat _scw_get_IncludeYear() { Winapi::Commontypes::DateTimeFormatting_YearFormat __r; HRESULT __hr = get_IncludeYear(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTimeFormatting_YearFormat IncludeYear = {read=_scw_get_IncludeYear};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_Languages() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_Languages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING Languages = {read=_scw_get_Languages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NumeralSystem() { HSTRING __r; HRESULT __hr = get_NumeralSystem(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NumeralSystem = {read=_scw_get_NumeralSystem, write=put_NumeralSystem};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_Patterns() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_Patterns(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING Patterns = {read=_scw_get_Patterns};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedGeographicRegion() { HSTRING __r; HRESULT __hr = get_ResolvedGeographicRegion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedGeographicRegion = {read=_scw_get_ResolvedGeographicRegion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Template() { HSTRING __r; HRESULT __hr = get_Template(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Template = {read=_scw_get_Template};
};

__interface  INTERFACE_UUID("{EC8D8A53-1A2E-412D-8815-3B745FB1A2A0}") DateTimeFormatting_IDateTimeFormatterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateDateTimeFormatter(HSTRING formatTemplate, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatter_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterLanguages(HSTRING formatTemplate, _di_IIterable_1__HSTRING languages, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterLanguages_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterContext(HSTRING formatTemplate, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion, HSTRING calendar, HSTRING clock, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterContext_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterDate(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterDate_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterTime(Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterTime_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterDateTimeLanguages(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat, Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat, _di_IIterable_1__HSTRING languages, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterDateTimeLanguages_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeFormatterDateTimeContext(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat, Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion, HSTRING calendar, HSTRING clock, _di_DateTimeFormatting_IDateTimeFormatter &__CreateDateTimeFormatterDateTimeContext_result) = 0 ;
};

__interface  INTERFACE_UUID("{BFCDE7C0-DF4C-4A2E-9012-F47DAF3F1212}") DateTimeFormatting_IDateTimeFormatterStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LongDate(_di_DateTimeFormatting_IDateTimeFormatter &__get_LongDate_result) = 0 ;
	virtual HRESULT __safecall get_LongTime(_di_DateTimeFormatting_IDateTimeFormatter &__get_LongTime_result) = 0 ;
	virtual HRESULT __safecall get_ShortDate(_di_DateTimeFormatting_IDateTimeFormatter &__get_ShortDate_result) = 0 ;
	virtual HRESULT __safecall get_ShortTime(_di_DateTimeFormatting_IDateTimeFormatter &__get_ShortTime_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_DateTimeFormatting_IDateTimeFormatter _scw_get_LongDate() { _di_DateTimeFormatting_IDateTimeFormatter __r; HRESULT __hr = get_LongDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_DateTimeFormatting_IDateTimeFormatter LongDate = {read=_scw_get_LongDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_DateTimeFormatting_IDateTimeFormatter _scw_get_LongTime() { _di_DateTimeFormatting_IDateTimeFormatter __r; HRESULT __hr = get_LongTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_DateTimeFormatting_IDateTimeFormatter LongTime = {read=_scw_get_LongTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_DateTimeFormatting_IDateTimeFormatter _scw_get_ShortDate() { _di_DateTimeFormatting_IDateTimeFormatter __r; HRESULT __hr = get_ShortDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_DateTimeFormatting_IDateTimeFormatter ShortDate = {read=_scw_get_ShortDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_DateTimeFormatting_IDateTimeFormatter _scw_get_ShortTime() { _di_DateTimeFormatting_IDateTimeFormatter __r; HRESULT __hr = get_ShortTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_DateTimeFormatting_IDateTimeFormatter ShortTime = {read=_scw_get_ShortTime};
};

__interface  INTERFACE_UUID("{27C91A86-BDAA-4FD0-9E36-671D5AA5EE03}") DateTimeFormatting_IDateTimeFormatter2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Format(Winapi::Commontypes::DateTime datetime, HSTRING timeZoneId, HSTRING &__Format_result) = 0 ;
};

__interface  INTERFACE_UUID("{CA30221D-86D9-40FB-A26B-D44EB7CF08EA}") ICalendar  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Clone(_di_ICalendar &__Clone_result) = 0 ;
	virtual HRESULT __safecall SetToMin() = 0 ;
	virtual HRESULT __safecall SetToMax() = 0 ;
	virtual HRESULT __safecall get_Languages(_di_IVectorView_1__HSTRING &__get_Languages_result) = 0 ;
	virtual HRESULT __safecall get_NumeralSystem(HSTRING &__get_NumeralSystem_result) = 0 ;
	virtual HRESULT __safecall put_NumeralSystem(HSTRING value) = 0 ;
	virtual HRESULT __safecall GetCalendarSystem(HSTRING &__GetCalendarSystem_result) = 0 ;
	virtual HRESULT __safecall ChangeCalendarSystem(HSTRING value) = 0 ;
	virtual HRESULT __safecall GetClock(HSTRING &__GetClock_result) = 0 ;
	virtual HRESULT __safecall ChangeClock(HSTRING value) = 0 ;
	virtual HRESULT __safecall GetDateTime(Winapi::Commontypes::DateTime &__GetDateTime_result) = 0 ;
	virtual HRESULT __safecall SetDateTime(Winapi::Commontypes::DateTime value) = 0 ;
	virtual HRESULT __safecall SetToNow() = 0 ;
	virtual HRESULT __safecall get_FirstEra(int &__get_FirstEra_result) = 0 ;
	virtual HRESULT __safecall get_LastEra(int &__get_LastEra_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfEras(int &__get_NumberOfEras_result) = 0 ;
	virtual HRESULT __safecall get_Era(int &__get_Era_result) = 0 ;
	virtual HRESULT __safecall put_Era(int value) = 0 ;
	virtual HRESULT __safecall AddEras(int eras) = 0 ;
	virtual HRESULT __safecall EraAsString(HSTRING &__EraAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall EraAsString(int idealLength, HSTRING &__EraAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall get_FirstYearInThisEra(int &__get_FirstYearInThisEra_result) = 0 ;
	virtual HRESULT __safecall get_LastYearInThisEra(int &__get_LastYearInThisEra_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfYearsInThisEra(int &__get_NumberOfYearsInThisEra_result) = 0 ;
	virtual HRESULT __safecall get_Year(int &__get_Year_result) = 0 ;
	virtual HRESULT __safecall put_Year(int value) = 0 ;
	virtual HRESULT __safecall AddYears(int years) = 0 ;
	virtual HRESULT __safecall YearAsString(HSTRING &__YearAsString_result) = 0 ;
	virtual HRESULT __safecall YearAsTruncatedString(int remainingDigits, HSTRING &__YearAsTruncatedString_result) = 0 ;
	virtual HRESULT __safecall YearAsPaddedString(int minDigits, HSTRING &__YearAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall get_FirstMonthInThisYear(int &__get_FirstMonthInThisYear_result) = 0 ;
	virtual HRESULT __safecall get_LastMonthInThisYear(int &__get_LastMonthInThisYear_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfMonthsInThisYear(int &__get_NumberOfMonthsInThisYear_result) = 0 ;
	virtual HRESULT __safecall get_Month(int &__get_Month_result) = 0 ;
	virtual HRESULT __safecall put_Month(int value) = 0 ;
	virtual HRESULT __safecall AddMonths(int months) = 0 ;
	virtual HRESULT __safecall MonthAsString(HSTRING &__MonthAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall MonthAsString(int idealLength, HSTRING &__MonthAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall MonthAsSoloString(HSTRING &__MonthAsSoloString_result) = 0 /* overload */;
	virtual HRESULT __safecall MonthAsSoloString(int idealLength, HSTRING &__MonthAsSoloString_result) = 0 /* overload */;
	virtual HRESULT __safecall MonthAsNumericString(HSTRING &__MonthAsNumericString_result) = 0 ;
	virtual HRESULT __safecall MonthAsPaddedNumericString(int minDigits, HSTRING &__MonthAsPaddedNumericString_result) = 0 ;
	virtual HRESULT __safecall AddWeeks(int weeks) = 0 ;
	virtual HRESULT __safecall get_FirstDayInThisMonth(int &__get_FirstDayInThisMonth_result) = 0 ;
	virtual HRESULT __safecall get_LastDayInThisMonth(int &__get_LastDayInThisMonth_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfDaysInThisMonth(int &__get_NumberOfDaysInThisMonth_result) = 0 ;
	virtual HRESULT __safecall get_Day(int &__get_Day_result) = 0 ;
	virtual HRESULT __safecall put_Day(int value) = 0 ;
	virtual HRESULT __safecall AddDays(int days) = 0 ;
	virtual HRESULT __safecall DayAsString(HSTRING &__DayAsString_result) = 0 ;
	virtual HRESULT __safecall DayAsPaddedString(int minDigits, HSTRING &__DayAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall get_DayOfWeek(Winapi::Commontypes::DayOfWeek &__get_DayOfWeek_result) = 0 ;
	virtual HRESULT __safecall DayOfWeekAsString(HSTRING &__DayOfWeekAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall DayOfWeekAsString(int idealLength, HSTRING &__DayOfWeekAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall DayOfWeekAsSoloString(HSTRING &__DayOfWeekAsSoloString_result) = 0 /* overload */;
	virtual HRESULT __safecall DayOfWeekAsSoloString(int idealLength, HSTRING &__DayOfWeekAsSoloString_result) = 0 /* overload */;
	virtual HRESULT __safecall get_FirstPeriodInThisDay(int &__get_FirstPeriodInThisDay_result) = 0 ;
	virtual HRESULT __safecall get_LastPeriodInThisDay(int &__get_LastPeriodInThisDay_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfPeriodsInThisDay(int &__get_NumberOfPeriodsInThisDay_result) = 0 ;
	virtual HRESULT __safecall get_Period(int &__get_Period_result) = 0 ;
	virtual HRESULT __safecall put_Period(int value) = 0 ;
	virtual HRESULT __safecall AddPeriods(int periods) = 0 ;
	virtual HRESULT __safecall PeriodAsString(HSTRING &__PeriodAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall PeriodAsString(int idealLength, HSTRING &__PeriodAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall get_FirstHourInThisPeriod(int &__get_FirstHourInThisPeriod_result) = 0 ;
	virtual HRESULT __safecall get_LastHourInThisPeriod(int &__get_LastHourInThisPeriod_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfHoursInThisPeriod(int &__get_NumberOfHoursInThisPeriod_result) = 0 ;
	virtual HRESULT __safecall get_Hour(int &__get_Hour_result) = 0 ;
	virtual HRESULT __safecall put_Hour(int value) = 0 ;
	virtual HRESULT __safecall AddHours(int hours) = 0 ;
	virtual HRESULT __safecall HourAsString(HSTRING &__HourAsString_result) = 0 ;
	virtual HRESULT __safecall HourAsPaddedString(int minDigits, HSTRING &__HourAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall get_Minute(int &__get_Minute_result) = 0 ;
	virtual HRESULT __safecall put_Minute(int value) = 0 ;
	virtual HRESULT __safecall AddMinutes(int minutes) = 0 ;
	virtual HRESULT __safecall MinuteAsString(HSTRING &__MinuteAsString_result) = 0 ;
	virtual HRESULT __safecall MinuteAsPaddedString(int minDigits, HSTRING &__MinuteAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall get_Second(int &__get_Second_result) = 0 ;
	virtual HRESULT __safecall put_Second(int value) = 0 ;
	virtual HRESULT __safecall AddSeconds(int seconds) = 0 ;
	virtual HRESULT __safecall SecondAsString(HSTRING &__SecondAsString_result) = 0 ;
	virtual HRESULT __safecall SecondAsPaddedString(int minDigits, HSTRING &__SecondAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall get_Nanosecond(int &__get_Nanosecond_result) = 0 ;
	virtual HRESULT __safecall put_Nanosecond(int value) = 0 ;
	virtual HRESULT __safecall AddNanoseconds(int nanoseconds) = 0 ;
	virtual HRESULT __safecall NanosecondAsString(HSTRING &__NanosecondAsString_result) = 0 ;
	virtual HRESULT __safecall NanosecondAsPaddedString(int minDigits, HSTRING &__NanosecondAsPaddedString_result) = 0 ;
	virtual HRESULT __safecall Compare(_di_ICalendar other, int &__Compare_result) = 0 ;
	virtual HRESULT __safecall CompareDateTime(Winapi::Commontypes::DateTime other, int &__CompareDateTime_result) = 0 ;
	virtual HRESULT __safecall CopyTo(_di_ICalendar other) = 0 ;
	virtual HRESULT __safecall get_FirstMinuteInThisHour(int &__get_FirstMinuteInThisHour_result) = 0 ;
	virtual HRESULT __safecall get_LastMinuteInThisHour(int &__get_LastMinuteInThisHour_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfMinutesInThisHour(int &__get_NumberOfMinutesInThisHour_result) = 0 ;
	virtual HRESULT __safecall get_FirstSecondInThisMinute(int &__get_FirstSecondInThisMinute_result) = 0 ;
	virtual HRESULT __safecall get_LastSecondInThisMinute(int &__get_LastSecondInThisMinute_result) = 0 ;
	virtual HRESULT __safecall get_NumberOfSecondsInThisMinute(int &__get_NumberOfSecondsInThisMinute_result) = 0 ;
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall get_IsDaylightSavingTime(bool &__get_IsDaylightSavingTime_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Day() { int __r; HRESULT __hr = get_Day(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Day = {read=_scw_get_Day, write=put_Day};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DayOfWeek _scw_get_DayOfWeek() { Winapi::Commontypes::DayOfWeek __r; HRESULT __hr = get_DayOfWeek(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DayOfWeek DayOfWeek = {read=_scw_get_DayOfWeek};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Era() { int __r; HRESULT __hr = get_Era(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Era = {read=_scw_get_Era, write=put_Era};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstDayInThisMonth() { int __r; HRESULT __hr = get_FirstDayInThisMonth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstDayInThisMonth = {read=_scw_get_FirstDayInThisMonth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstEra() { int __r; HRESULT __hr = get_FirstEra(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstEra = {read=_scw_get_FirstEra};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstHourInThisPeriod() { int __r; HRESULT __hr = get_FirstHourInThisPeriod(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstHourInThisPeriod = {read=_scw_get_FirstHourInThisPeriod};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstMinuteInThisHour() { int __r; HRESULT __hr = get_FirstMinuteInThisHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstMinuteInThisHour = {read=_scw_get_FirstMinuteInThisHour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstMonthInThisYear() { int __r; HRESULT __hr = get_FirstMonthInThisYear(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstMonthInThisYear = {read=_scw_get_FirstMonthInThisYear};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstPeriodInThisDay() { int __r; HRESULT __hr = get_FirstPeriodInThisDay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstPeriodInThisDay = {read=_scw_get_FirstPeriodInThisDay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstSecondInThisMinute() { int __r; HRESULT __hr = get_FirstSecondInThisMinute(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstSecondInThisMinute = {read=_scw_get_FirstSecondInThisMinute};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FirstYearInThisEra() { int __r; HRESULT __hr = get_FirstYearInThisEra(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FirstYearInThisEra = {read=_scw_get_FirstYearInThisEra};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Hour() { int __r; HRESULT __hr = get_Hour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Hour = {read=_scw_get_Hour, write=put_Hour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDaylightSavingTime() { bool __r; HRESULT __hr = get_IsDaylightSavingTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDaylightSavingTime = {read=_scw_get_IsDaylightSavingTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_Languages() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_Languages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING Languages = {read=_scw_get_Languages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastDayInThisMonth() { int __r; HRESULT __hr = get_LastDayInThisMonth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastDayInThisMonth = {read=_scw_get_LastDayInThisMonth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastEra() { int __r; HRESULT __hr = get_LastEra(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastEra = {read=_scw_get_LastEra};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastHourInThisPeriod() { int __r; HRESULT __hr = get_LastHourInThisPeriod(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastHourInThisPeriod = {read=_scw_get_LastHourInThisPeriod};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastMinuteInThisHour() { int __r; HRESULT __hr = get_LastMinuteInThisHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastMinuteInThisHour = {read=_scw_get_LastMinuteInThisHour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastMonthInThisYear() { int __r; HRESULT __hr = get_LastMonthInThisYear(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastMonthInThisYear = {read=_scw_get_LastMonthInThisYear};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastPeriodInThisDay() { int __r; HRESULT __hr = get_LastPeriodInThisDay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastPeriodInThisDay = {read=_scw_get_LastPeriodInThisDay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastSecondInThisMinute() { int __r; HRESULT __hr = get_LastSecondInThisMinute(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastSecondInThisMinute = {read=_scw_get_LastSecondInThisMinute};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_LastYearInThisEra() { int __r; HRESULT __hr = get_LastYearInThisEra(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int LastYearInThisEra = {read=_scw_get_LastYearInThisEra};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Minute() { int __r; HRESULT __hr = get_Minute(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Minute = {read=_scw_get_Minute, write=put_Minute};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Month() { int __r; HRESULT __hr = get_Month(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Month = {read=_scw_get_Month, write=put_Month};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Nanosecond() { int __r; HRESULT __hr = get_Nanosecond(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Nanosecond = {read=_scw_get_Nanosecond, write=put_Nanosecond};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfDaysInThisMonth() { int __r; HRESULT __hr = get_NumberOfDaysInThisMonth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfDaysInThisMonth = {read=_scw_get_NumberOfDaysInThisMonth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfEras() { int __r; HRESULT __hr = get_NumberOfEras(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfEras = {read=_scw_get_NumberOfEras};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfHoursInThisPeriod() { int __r; HRESULT __hr = get_NumberOfHoursInThisPeriod(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfHoursInThisPeriod = {read=_scw_get_NumberOfHoursInThisPeriod};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfMinutesInThisHour() { int __r; HRESULT __hr = get_NumberOfMinutesInThisHour(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfMinutesInThisHour = {read=_scw_get_NumberOfMinutesInThisHour};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfMonthsInThisYear() { int __r; HRESULT __hr = get_NumberOfMonthsInThisYear(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfMonthsInThisYear = {read=_scw_get_NumberOfMonthsInThisYear};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfPeriodsInThisDay() { int __r; HRESULT __hr = get_NumberOfPeriodsInThisDay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfPeriodsInThisDay = {read=_scw_get_NumberOfPeriodsInThisDay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfSecondsInThisMinute() { int __r; HRESULT __hr = get_NumberOfSecondsInThisMinute(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfSecondsInThisMinute = {read=_scw_get_NumberOfSecondsInThisMinute};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_NumberOfYearsInThisEra() { int __r; HRESULT __hr = get_NumberOfYearsInThisEra(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NumberOfYearsInThisEra = {read=_scw_get_NumberOfYearsInThisEra};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NumeralSystem() { HSTRING __r; HRESULT __hr = get_NumeralSystem(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NumeralSystem = {read=_scw_get_NumeralSystem, write=put_NumeralSystem};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Period() { int __r; HRESULT __hr = get_Period(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Period = {read=_scw_get_Period, write=put_Period};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Second() { int __r; HRESULT __hr = get_Second(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Second = {read=_scw_get_Second, write=put_Second};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Year() { int __r; HRESULT __hr = get_Year(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Year = {read=_scw_get_Year, write=put_Year};
};

__interface  INTERFACE_UUID("{B44B378C-CA7E-4590-9E72-EA2BEC1A5115}") ICalendarFactory2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateCalendarWithTimeZone(_di_IIterable_1__HSTRING languages, HSTRING calendar, HSTRING clock, HSTRING timeZoneId, _di_ICalendar &__CreateCalendarWithTimeZone_result) = 0 ;
};

__interface  INTERFACE_UUID("{BB3C25E5-46CF-4317-A3F5-02621AD54478}") ITimeZoneOnCalendar  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetTimeZone(HSTRING &__GetTimeZone_result) = 0 ;
	virtual HRESULT __safecall ChangeTimeZone(HSTRING timeZoneId) = 0 ;
	virtual HRESULT __safecall TimeZoneAsString(HSTRING &__TimeZoneAsString_result) = 0 /* overload */;
	virtual HRESULT __safecall TimeZoneAsString(int idealLength, HSTRING &__TimeZoneAsString_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{83F58412-E56B-4C75-A66E-0F63D57758A6}") ICalendarFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateCalendarDefaultCalendarAndClock(_di_IIterable_1__HSTRING languages, _di_ICalendar &__CreateCalendarDefaultCalendarAndClock_result) = 0 ;
	virtual HRESULT __safecall CreateCalendar(_di_IIterable_1__HSTRING languages, HSTRING calendar, HSTRING clock, _di_ICalendar &__CreateCalendar_result) = 0 ;
};

__interface  INTERFACE_UUID("{5473C375-38ED-4631-B80C-EF34FC48B7F5}") NumberFormatting_INumberRounder  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall RoundInt32(int value, int &__RoundInt32_result) = 0 ;
	virtual HRESULT __safecall RoundUInt32(unsigned value, unsigned &__RoundUInt32_result) = 0 ;
	virtual HRESULT __safecall RoundInt64(__int64 value, __int64 &__RoundInt64_result) = 0 ;
	virtual HRESULT __safecall RoundUInt64(unsigned __int64 value, unsigned __int64 &__RoundUInt64_result) = 0 ;
	virtual HRESULT __safecall RoundSingle(float value, float &__RoundSingle_result) = 0 ;
	virtual HRESULT __safecall RoundDouble(double value, double &__RoundDouble_result) = 0 ;
};

__interface  INTERFACE_UUID("{F5941BCA-6646-4913-8C76-1B191FF94DFD}") NumberFormatting_ISignificantDigitsNumberRounder  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RoundingAlgorithm(Winapi::Commontypes::NumberFormatting_RoundingAlgorithm &__get_RoundingAlgorithm_result) = 0 ;
	virtual HRESULT __safecall put_RoundingAlgorithm(Winapi::Commontypes::NumberFormatting_RoundingAlgorithm value) = 0 ;
	virtual HRESULT __safecall get_SignificantDigits(unsigned &__get_SignificantDigits_result) = 0 ;
	virtual HRESULT __safecall put_SignificantDigits(unsigned value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NumberFormatting_RoundingAlgorithm _scw_get_RoundingAlgorithm() { Winapi::Commontypes::NumberFormatting_RoundingAlgorithm __r; HRESULT __hr = get_RoundingAlgorithm(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NumberFormatting_RoundingAlgorithm RoundingAlgorithm = {read=_scw_get_RoundingAlgorithm, write=put_RoundingAlgorithm};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SignificantDigits() { unsigned __r; HRESULT __hr = get_SignificantDigits(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SignificantDigits = {read=_scw_get_SignificantDigits, write=put_SignificantDigits};
};

__interface  INTERFACE_UUID("{70A64FF8-66AB-4155-9DA1-739E46764543}") NumberFormatting_IIncrementNumberRounder  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RoundingAlgorithm(Winapi::Commontypes::NumberFormatting_RoundingAlgorithm &__get_RoundingAlgorithm_result) = 0 ;
	virtual HRESULT __safecall put_RoundingAlgorithm(Winapi::Commontypes::NumberFormatting_RoundingAlgorithm value) = 0 ;
	virtual HRESULT __safecall get_Increment(double &__get_Increment_result) = 0 ;
	virtual HRESULT __safecall put_Increment(double value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Increment() { double __r; HRESULT __hr = get_Increment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Increment = {read=_scw_get_Increment, write=put_Increment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NumberFormatting_RoundingAlgorithm _scw_get_RoundingAlgorithm() { Winapi::Commontypes::NumberFormatting_RoundingAlgorithm __r; HRESULT __hr = get_RoundingAlgorithm(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NumberFormatting_RoundingAlgorithm RoundingAlgorithm = {read=_scw_get_RoundingAlgorithm, write=put_RoundingAlgorithm};
};

__interface  INTERFACE_UUID("{A5007C49-7676-4DB7-8631-1B6FF265CAA9}") NumberFormatting_INumberFormatter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Format(__int64 value, HSTRING &__Format_result) = 0 /* overload */;
	virtual HRESULT __safecall Format(unsigned __int64 value, HSTRING &__Format_result) = 0 /* overload */;
	virtual HRESULT __safecall Format(double value, HSTRING &__Format_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D4A8C1F0-80D0-4B0D-A89E-882C1E8F8310}") NumberFormatting_INumberFormatter2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FormatInt(__int64 value, HSTRING &__FormatInt_result) = 0 ;
	virtual HRESULT __safecall FormatUInt(unsigned __int64 value, HSTRING &__FormatUInt_result) = 0 ;
	virtual HRESULT __safecall FormatDouble(double value, HSTRING &__FormatDouble_result) = 0 ;
};

__interface  INTERFACE_UUID("{4DDA9E24-E69F-5C6A-A0A6-93427365AF2A}") IReference_1__Int64  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(__int64 &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline __int64 _scw_get_Value() { __int64 __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property __int64 Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{6755E376-53BB-568B-A11D-17239868309E}") IReference_1__UInt64  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(unsigned __int64 &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_Value() { unsigned __int64 __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{2F2D6C29-5473-5F3E-92E7-96572BB990E2}") IReference_1__Double  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(double &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Value() { double __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{E6659412-4A13-4A53-83A1-392FBE4CFF9F}") NumberFormatting_INumberParser  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ParseInt(HSTRING text, _di_IReference_1__Int64 &__ParseInt_result) = 0 ;
	virtual HRESULT __safecall ParseUInt(HSTRING text, _di_IReference_1__UInt64 &__ParseUInt_result) = 0 ;
	virtual HRESULT __safecall ParseDouble(HSTRING text, _di_IReference_1__Double &__ParseDouble_result) = 0 ;
};

__interface  INTERFACE_UUID("{80332D21-AEE1-4A39-BAA2-07ED8C96DAF6}") NumberFormatting_INumberFormatterOptions  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Languages(_di_IVectorView_1__HSTRING &__get_Languages_result) = 0 ;
	virtual HRESULT __safecall get_GeographicRegion(HSTRING &__get_GeographicRegion_result) = 0 ;
	virtual HRESULT __safecall get_IntegerDigits(int &__get_IntegerDigits_result) = 0 ;
	virtual HRESULT __safecall put_IntegerDigits(int value) = 0 ;
	virtual HRESULT __safecall get_FractionDigits(int &__get_FractionDigits_result) = 0 ;
	virtual HRESULT __safecall put_FractionDigits(int value) = 0 ;
	virtual HRESULT __safecall get_IsGrouped(bool &__get_IsGrouped_result) = 0 ;
	virtual HRESULT __safecall put_IsGrouped(bool value) = 0 ;
	virtual HRESULT __safecall get_IsDecimalPointAlwaysDisplayed(bool &__get_IsDecimalPointAlwaysDisplayed_result) = 0 ;
	virtual HRESULT __safecall put_IsDecimalPointAlwaysDisplayed(bool value) = 0 ;
	virtual HRESULT __safecall get_NumeralSystem(HSTRING &__get_NumeralSystem_result) = 0 ;
	virtual HRESULT __safecall put_NumeralSystem(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall get_ResolvedGeographicRegion(HSTRING &__get_ResolvedGeographicRegion_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_FractionDigits() { int __r; HRESULT __hr = get_FractionDigits(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int FractionDigits = {read=_scw_get_FractionDigits, write=put_FractionDigits};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_GeographicRegion() { HSTRING __r; HRESULT __hr = get_GeographicRegion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING GeographicRegion = {read=_scw_get_GeographicRegion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_IntegerDigits() { int __r; HRESULT __hr = get_IntegerDigits(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int IntegerDigits = {read=_scw_get_IntegerDigits, write=put_IntegerDigits};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDecimalPointAlwaysDisplayed() { bool __r; HRESULT __hr = get_IsDecimalPointAlwaysDisplayed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDecimalPointAlwaysDisplayed = {read=_scw_get_IsDecimalPointAlwaysDisplayed, write=put_IsDecimalPointAlwaysDisplayed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsGrouped() { bool __r; HRESULT __hr = get_IsGrouped(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsGrouped = {read=_scw_get_IsGrouped, write=put_IsGrouped};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_Languages() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_Languages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING Languages = {read=_scw_get_Languages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NumeralSystem() { HSTRING __r; HRESULT __hr = get_NumeralSystem(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NumeralSystem = {read=_scw_get_NumeralSystem, write=put_NumeralSystem};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedGeographicRegion() { HSTRING __r; HRESULT __hr = get_ResolvedGeographicRegion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedGeographicRegion = {read=_scw_get_ResolvedGeographicRegion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
};

__interface  INTERFACE_UUID("{1D4DFCDD-2D43-4EE8-BBF1-C1B26A711A58}") NumberFormatting_ISignificantDigitsOption  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SignificantDigits(int &__get_SignificantDigits_result) = 0 ;
	virtual HRESULT __safecall put_SignificantDigits(int value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_SignificantDigits() { int __r; HRESULT __hr = get_SignificantDigits(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int SignificantDigits = {read=_scw_get_SignificantDigits, write=put_SignificantDigits};
};

__interface  INTERFACE_UUID("{3B088433-646F-4EFE-8D48-66EB2E49E736}") NumberFormatting_INumberRounderOption  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NumberRounder(_di_NumberFormatting_INumberRounder &__get_NumberRounder_result) = 0 ;
	virtual HRESULT __safecall put_NumberRounder(_di_NumberFormatting_INumberRounder value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_NumberFormatting_INumberRounder _scw_get_NumberRounder() { _di_NumberFormatting_INumberRounder __r; HRESULT __hr = get_NumberRounder(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_NumberFormatting_INumberRounder NumberRounder = {read=_scw_get_NumberRounder, write=put_NumberRounder};
};

__interface  INTERFACE_UUID("{FD1CDD31-0A3C-49C4-A642-96A1564F4F30}") NumberFormatting_ISignedZeroOption  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsZeroSigned(bool &__get_IsZeroSigned_result) = 0 ;
	virtual HRESULT __safecall put_IsZeroSigned(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsZeroSigned() { bool __r; HRESULT __hr = get_IsZeroSigned(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsZeroSigned = {read=_scw_get_IsZeroSigned, write=put_IsZeroSigned};
};

__interface  INTERFACE_UUID("{0D018C9A-E393-46B8-B830-7A69C8F89FBB}") NumberFormatting_IDecimalFormatterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateDecimalFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion, _di_NumberFormatting_INumberFormatterOptions &__CreateDecimalFormatter_result) = 0 ;
};

__interface  INTERFACE_UUID("{B7828AEF-FED4-4018-A6E2-E09961E03765}") NumberFormatting_IPercentFormatterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreatePercentFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion, _di_NumberFormatting_INumberFormatterOptions &__CreatePercentFormatter_result) = 0 ;
};

__interface  INTERFACE_UUID("{2B37B4AC-E638-4ED5-A998-62F6B06A49AE}") NumberFormatting_IPermilleFormatterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreatePermilleFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion, _di_NumberFormatting_INumberFormatterOptions &__CreatePermilleFormatter_result) = 0 ;
};

__interface  INTERFACE_UUID("{11730CA5-4B00-41B2-B332-73B12A497D54}") NumberFormatting_ICurrencyFormatter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Currency(HSTRING &__get_Currency_result) = 0 ;
	virtual HRESULT __safecall put_Currency(HSTRING value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Currency() { HSTRING __r; HRESULT __hr = get_Currency(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Currency = {read=_scw_get_Currency, write=put_Currency};
};

__interface  INTERFACE_UUID("{86C7537E-B938-4AA2-84B0-2C33DC5B1450}") NumberFormatting_ICurrencyFormatterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateCurrencyFormatterCode(HSTRING currencyCode, _di_NumberFormatting_ICurrencyFormatter &__CreateCurrencyFormatterCode_result) = 0 ;
	virtual HRESULT __safecall CreateCurrencyFormatterCodeContext(HSTRING currencyCode, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion, _di_NumberFormatting_ICurrencyFormatter &__CreateCurrencyFormatterCodeContext_result) = 0 ;
};

__interface  INTERFACE_UUID("{072C2F1D-E7BA-4197-920E-247C92F7DEA6}") NumberFormatting_ICurrencyFormatter2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::NumberFormatting_CurrencyFormatterMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::NumberFormatting_CurrencyFormatterMode value) = 0 ;
	virtual HRESULT __safecall ApplyRoundingForCurrency(Winapi::Commontypes::NumberFormatting_RoundingAlgorithm roundingAlgorithm) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NumberFormatting_CurrencyFormatterMode _scw_get_Mode() { Winapi::Commontypes::NumberFormatting_CurrencyFormatterMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NumberFormatting_CurrencyFormatterMode Mode = {read=_scw_get_Mode, write=put_Mode};
};

__interface  INTERFACE_UUID("{28F5BC2C-8C23-4234-AD2E-FA5A3A426E9B}") NumberFormatting_INumeralSystemTranslator  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Languages(_di_IVectorView_1__HSTRING &__get_Languages_result) = 0 ;
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall get_NumeralSystem(HSTRING &__get_NumeralSystem_result) = 0 ;
	virtual HRESULT __safecall put_NumeralSystem(HSTRING value) = 0 ;
	virtual HRESULT __safecall TranslateNumerals(HSTRING value, HSTRING &__TranslateNumerals_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HSTRING _scw_get_Languages() { _di_IVectorView_1__HSTRING __r; HRESULT __hr = get_Languages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HSTRING Languages = {read=_scw_get_Languages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_NumeralSystem() { HSTRING __r; HRESULT __hr = get_NumeralSystem(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING NumeralSystem = {read=_scw_get_NumeralSystem, write=put_NumeralSystem};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
};

__interface  INTERFACE_UUID("{9630C8DA-36EF-4D88-A85C-6F0D98D620A6}") NumberFormatting_INumeralSystemTranslatorFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_IIterable_1__HSTRING languages, _di_NumberFormatting_INumeralSystemTranslator &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{FAE761BB-805D-4BB0-95BB-C1F7C3E8EB8E}") Collation_ICharacterGrouping  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_First(HSTRING &__get_First_result) = 0 ;
	virtual HRESULT __safecall get_Label(HSTRING &__get_Label_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_First() { HSTRING __r; HRESULT __hr = get_First(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING First = {read=_scw_get_First};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Label() { HSTRING __r; HRESULT __hr = get_Label(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Label = {read=_scw_get_Label};
};

__interface  INTERFACE_UUID("{57E89BBC-9220-5DF2-844B-DDFE6605DB5F}") IIterator_1__Collation_ICharacterGrouping_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{72DBD788-D8AC-5771-A0D3-8FE1310D6DA5}") IIterator_1__Collation_ICharacterGrouping  : public IIterator_1__Collation_ICharacterGrouping_Base 
{
	virtual HRESULT __safecall get_Current(_di_Collation_ICharacterGrouping &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PCollation_ICharacterGrouping items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Collation_ICharacterGrouping _scw_get_Current() { _di_Collation_ICharacterGrouping __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Collation_ICharacterGrouping Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{82E3ABF0-06E3-5609-BA39-C51EB2F5FAE6}") IIterable_1__Collation_ICharacterGrouping_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E6888E87-68AA-5C9E-ABBF-C0679E2CB1E9}") IIterable_1__Collation_ICharacterGrouping  : public IIterable_1__Collation_ICharacterGrouping_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Collation_ICharacterGrouping &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{88F5643A-E4DB-58AE-8CF5-B6343D0B60F9}") IVectorView_1__Collation_ICharacterGrouping  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Collation_ICharacterGrouping &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Collation_ICharacterGrouping value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PCollation_ICharacterGrouping items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{B8D20A75-D4CF-4055-80E5-CE169C226496}") Collation_ICharacterGroupings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING text, HSTRING &__Lookup_result) = 0 ;
};

__interface  INTERFACE_UUID("{99EA9FD9-886D-4401-9F98-69C82D4C2F78}") Collation_ICharacterGroupingsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING language, _di_Collation_ICharacterGroupings &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{8E7A7A79-0CC1-5193-90EA-55EE2A4D96DD}") IVector_1__ILanguage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ILanguage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ILanguage &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ILanguage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_ILanguage value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_ILanguage value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_ILanguage value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PILanguage items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PILanguage items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFonts_LanguageFontGroup : public System::Win::Winrt::TWinRTGenericImportF__1<_di_Fonts_ILanguageFontGroupFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_Fonts_ILanguageFontGroupFactory> inherited;
	
public:
	static _di_Fonts_ILanguageFontGroup __fastcall CreateLanguageFontGroup(HSTRING languageTag);
public:
	/* TObject.Create */ inline __fastcall TFonts_LanguageFontGroup() : System::Win::Winrt::TWinRTGenericImportF__1<_di_Fonts_ILanguageFontGroupFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFonts_LanguageFontGroup() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCalendarIdentifiers : public System::Win::Winrt::TWinRTGenericImportS3__3<_di_ICalendarIdentifiersStatics,_di_ICalendarIdentifiersStatics2,_di_ICalendarIdentifiersStatics3>
{
	typedef System::Win::Winrt::TWinRTGenericImportS3__3<_di_ICalendarIdentifiersStatics,_di_ICalendarIdentifiersStatics2,_di_ICalendarIdentifiersStatics3> inherited;
	
public:
	static HSTRING __fastcall get_Persian();
#ifndef _WIN64
	/* static */ __property HSTRING Persian = {read=get_Persian, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING Persian = {read=get_Persian};
#endif /* _WIN64 */
	static HSTRING __fastcall get_Gregorian();
	static HSTRING __fastcall get_Hebrew();
	static HSTRING __fastcall get_Hijri();
	static HSTRING __fastcall get_Japanese();
	static HSTRING __fastcall get_Julian();
	static HSTRING __fastcall get_Korean();
	static HSTRING __fastcall get_Taiwan();
	static HSTRING __fastcall get_Thai();
	static HSTRING __fastcall get_UmAlQura();
#ifndef _WIN64
	/* static */ __property HSTRING Gregorian = {read=get_Gregorian, nodefault};
	/* static */ __property HSTRING Hebrew = {read=get_Hebrew, nodefault};
	/* static */ __property HSTRING Hijri = {read=get_Hijri, nodefault};
	/* static */ __property HSTRING Japanese = {read=get_Japanese, nodefault};
	/* static */ __property HSTRING Julian = {read=get_Julian, nodefault};
	/* static */ __property HSTRING Korean = {read=get_Korean, nodefault};
	/* static */ __property HSTRING Taiwan = {read=get_Taiwan, nodefault};
	/* static */ __property HSTRING Thai = {read=get_Thai, nodefault};
	/* static */ __property HSTRING UmAlQura = {read=get_UmAlQura, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING Gregorian = {read=get_Gregorian};
	/* static */ __property HSTRING Hebrew = {read=get_Hebrew};
	/* static */ __property HSTRING Hijri = {read=get_Hijri};
	/* static */ __property HSTRING Japanese = {read=get_Japanese};
	/* static */ __property HSTRING Julian = {read=get_Julian};
	/* static */ __property HSTRING Korean = {read=get_Korean};
	/* static */ __property HSTRING Taiwan = {read=get_Taiwan};
	/* static */ __property HSTRING Thai = {read=get_Thai};
	/* static */ __property HSTRING UmAlQura = {read=get_UmAlQura};
#endif /* _WIN64 */
	static HSTRING __fastcall get_ChineseLunar();
	static HSTRING __fastcall get_JapaneseLunar();
	static HSTRING __fastcall get_KoreanLunar();
	static HSTRING __fastcall get_TaiwanLunar();
	static HSTRING __fastcall get_VietnameseLunar();
#ifndef _WIN64
	/* static */ __property HSTRING ChineseLunar = {read=get_ChineseLunar, nodefault};
	/* static */ __property HSTRING JapaneseLunar = {read=get_JapaneseLunar, nodefault};
	/* static */ __property HSTRING KoreanLunar = {read=get_KoreanLunar, nodefault};
	/* static */ __property HSTRING TaiwanLunar = {read=get_TaiwanLunar, nodefault};
	/* static */ __property HSTRING VietnameseLunar = {read=get_VietnameseLunar, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING ChineseLunar = {read=get_ChineseLunar};
	/* static */ __property HSTRING JapaneseLunar = {read=get_JapaneseLunar};
	/* static */ __property HSTRING KoreanLunar = {read=get_KoreanLunar};
	/* static */ __property HSTRING TaiwanLunar = {read=get_TaiwanLunar};
	/* static */ __property HSTRING VietnameseLunar = {read=get_VietnameseLunar};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TCalendarIdentifiers() : System::Win::Winrt::TWinRTGenericImportS3__3<_di_ICalendarIdentifiersStatics,_di_ICalendarIdentifiersStatics2,_di_ICalendarIdentifiersStatics3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCalendarIdentifiers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TClockIdentifiers : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IClockIdentifiersStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IClockIdentifiersStatics> inherited;
	
public:
	static HSTRING __fastcall get_TwelveHour();
	static HSTRING __fastcall get_TwentyFourHour();
#ifndef _WIN64
	/* static */ __property HSTRING TwelveHour = {read=get_TwelveHour, nodefault};
	/* static */ __property HSTRING TwentyFourHour = {read=get_TwentyFourHour, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING TwelveHour = {read=get_TwelveHour};
	/* static */ __property HSTRING TwentyFourHour = {read=get_TwentyFourHour};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TClockIdentifiers() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IClockIdentifiersStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TClockIdentifiers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumeralSystemIdentifiers : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_INumeralSystemIdentifiersStatics,_di_INumeralSystemIdentifiersStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_INumeralSystemIdentifiersStatics,_di_INumeralSystemIdentifiersStatics2> inherited;
	
public:
	static HSTRING __fastcall get_Arab();
	static HSTRING __fastcall get_ArabExt();
	static HSTRING __fastcall get_Bali();
	static HSTRING __fastcall get_Beng();
	static HSTRING __fastcall get_Cham();
	static HSTRING __fastcall get_Deva();
	static HSTRING __fastcall get_FullWide();
	static HSTRING __fastcall get_Gujr();
	static HSTRING __fastcall get_Guru();
	static HSTRING __fastcall get_HaniDec();
	static HSTRING __fastcall get_Java();
	static HSTRING __fastcall get_Kali();
	static HSTRING __fastcall get_Khmr();
	static HSTRING __fastcall get_Knda();
	static HSTRING __fastcall get_Lana();
	static HSTRING __fastcall get_LanaTham();
	static HSTRING __fastcall get_Laoo();
	static HSTRING __fastcall get_Latn();
	static HSTRING __fastcall get_Lepc();
	static HSTRING __fastcall get_Limb();
	static HSTRING __fastcall get_Mlym();
	static HSTRING __fastcall get_Mong();
	static HSTRING __fastcall get_Mtei();
	static HSTRING __fastcall get_Mymr();
	static HSTRING __fastcall get_MymrShan();
	static HSTRING __fastcall get_Nkoo();
	static HSTRING __fastcall get_Olck();
	static HSTRING __fastcall get_Orya();
	static HSTRING __fastcall get_Saur();
	static HSTRING __fastcall get_Sund();
	static HSTRING __fastcall get_Talu();
	static HSTRING __fastcall get_TamlDec();
	static HSTRING __fastcall get_Telu();
	static HSTRING __fastcall get_Thai();
	static HSTRING __fastcall get_Tibt();
	static HSTRING __fastcall get_Vaii();
#ifndef _WIN64
	/* static */ __property HSTRING Arab = {read=get_Arab, nodefault};
	/* static */ __property HSTRING ArabExt = {read=get_ArabExt, nodefault};
	/* static */ __property HSTRING Bali = {read=get_Bali, nodefault};
	/* static */ __property HSTRING Beng = {read=get_Beng, nodefault};
	/* static */ __property HSTRING Cham = {read=get_Cham, nodefault};
	/* static */ __property HSTRING Deva = {read=get_Deva, nodefault};
	/* static */ __property HSTRING FullWide = {read=get_FullWide, nodefault};
	/* static */ __property HSTRING Gujr = {read=get_Gujr, nodefault};
	/* static */ __property HSTRING Guru = {read=get_Guru, nodefault};
	/* static */ __property HSTRING HaniDec = {read=get_HaniDec, nodefault};
	/* static */ __property HSTRING Java = {read=get_Java, nodefault};
	/* static */ __property HSTRING Kali = {read=get_Kali, nodefault};
	/* static */ __property HSTRING Khmr = {read=get_Khmr, nodefault};
	/* static */ __property HSTRING Knda = {read=get_Knda, nodefault};
	/* static */ __property HSTRING Lana = {read=get_Lana, nodefault};
	/* static */ __property HSTRING LanaTham = {read=get_LanaTham, nodefault};
	/* static */ __property HSTRING Laoo = {read=get_Laoo, nodefault};
	/* static */ __property HSTRING Latn = {read=get_Latn, nodefault};
	/* static */ __property HSTRING Lepc = {read=get_Lepc, nodefault};
	/* static */ __property HSTRING Limb = {read=get_Limb, nodefault};
	/* static */ __property HSTRING Mlym = {read=get_Mlym, nodefault};
	/* static */ __property HSTRING Mong = {read=get_Mong, nodefault};
	/* static */ __property HSTRING Mtei = {read=get_Mtei, nodefault};
	/* static */ __property HSTRING Mymr = {read=get_Mymr, nodefault};
	/* static */ __property HSTRING MymrShan = {read=get_MymrShan, nodefault};
	/* static */ __property HSTRING Nkoo = {read=get_Nkoo, nodefault};
	/* static */ __property HSTRING Olck = {read=get_Olck, nodefault};
	/* static */ __property HSTRING Orya = {read=get_Orya, nodefault};
	/* static */ __property HSTRING Saur = {read=get_Saur, nodefault};
	/* static */ __property HSTRING Sund = {read=get_Sund, nodefault};
	/* static */ __property HSTRING Talu = {read=get_Talu, nodefault};
	/* static */ __property HSTRING TamlDec = {read=get_TamlDec, nodefault};
	/* static */ __property HSTRING Telu = {read=get_Telu, nodefault};
	/* static */ __property HSTRING Thai = {read=get_Thai, nodefault};
	/* static */ __property HSTRING Tibt = {read=get_Tibt, nodefault};
	/* static */ __property HSTRING Vaii = {read=get_Vaii, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING Arab = {read=get_Arab};
	/* static */ __property HSTRING ArabExt = {read=get_ArabExt};
	/* static */ __property HSTRING Bali = {read=get_Bali};
	/* static */ __property HSTRING Beng = {read=get_Beng};
	/* static */ __property HSTRING Cham = {read=get_Cham};
	/* static */ __property HSTRING Deva = {read=get_Deva};
	/* static */ __property HSTRING FullWide = {read=get_FullWide};
	/* static */ __property HSTRING Gujr = {read=get_Gujr};
	/* static */ __property HSTRING Guru = {read=get_Guru};
	/* static */ __property HSTRING HaniDec = {read=get_HaniDec};
	/* static */ __property HSTRING Java = {read=get_Java};
	/* static */ __property HSTRING Kali = {read=get_Kali};
	/* static */ __property HSTRING Khmr = {read=get_Khmr};
	/* static */ __property HSTRING Knda = {read=get_Knda};
	/* static */ __property HSTRING Lana = {read=get_Lana};
	/* static */ __property HSTRING LanaTham = {read=get_LanaTham};
	/* static */ __property HSTRING Laoo = {read=get_Laoo};
	/* static */ __property HSTRING Latn = {read=get_Latn};
	/* static */ __property HSTRING Lepc = {read=get_Lepc};
	/* static */ __property HSTRING Limb = {read=get_Limb};
	/* static */ __property HSTRING Mlym = {read=get_Mlym};
	/* static */ __property HSTRING Mong = {read=get_Mong};
	/* static */ __property HSTRING Mtei = {read=get_Mtei};
	/* static */ __property HSTRING Mymr = {read=get_Mymr};
	/* static */ __property HSTRING MymrShan = {read=get_MymrShan};
	/* static */ __property HSTRING Nkoo = {read=get_Nkoo};
	/* static */ __property HSTRING Olck = {read=get_Olck};
	/* static */ __property HSTRING Orya = {read=get_Orya};
	/* static */ __property HSTRING Saur = {read=get_Saur};
	/* static */ __property HSTRING Sund = {read=get_Sund};
	/* static */ __property HSTRING Talu = {read=get_Talu};
	/* static */ __property HSTRING TamlDec = {read=get_TamlDec};
	/* static */ __property HSTRING Telu = {read=get_Telu};
	/* static */ __property HSTRING Thai = {read=get_Thai};
	/* static */ __property HSTRING Tibt = {read=get_Tibt};
	/* static */ __property HSTRING Vaii = {read=get_Vaii};
#endif /* _WIN64 */
	static HSTRING __fastcall get_Brah();
	static HSTRING __fastcall get_Osma();
	static HSTRING __fastcall get_MathBold();
	static HSTRING __fastcall get_MathDbl();
	static HSTRING __fastcall get_MathSans();
	static HSTRING __fastcall get_MathSanb();
	static HSTRING __fastcall get_MathMono();
	static HSTRING __fastcall get_ZmthBold();
	static HSTRING __fastcall get_ZmthDbl();
	static HSTRING __fastcall get_ZmthSans();
	static HSTRING __fastcall get_ZmthSanb();
	static HSTRING __fastcall get_ZmthMono();
#ifndef _WIN64
	/* static */ __property HSTRING Brah = {read=get_Brah, nodefault};
	/* static */ __property HSTRING MathBold = {read=get_MathBold, nodefault};
	/* static */ __property HSTRING MathDbl = {read=get_MathDbl, nodefault};
	/* static */ __property HSTRING MathMono = {read=get_MathMono, nodefault};
	/* static */ __property HSTRING MathSanb = {read=get_MathSanb, nodefault};
	/* static */ __property HSTRING MathSans = {read=get_MathSans, nodefault};
	/* static */ __property HSTRING Osma = {read=get_Osma, nodefault};
	/* static */ __property HSTRING ZmthBold = {read=get_ZmthBold, nodefault};
	/* static */ __property HSTRING ZmthDbl = {read=get_ZmthDbl, nodefault};
	/* static */ __property HSTRING ZmthMono = {read=get_ZmthMono, nodefault};
	/* static */ __property HSTRING ZmthSanb = {read=get_ZmthSanb, nodefault};
	/* static */ __property HSTRING ZmthSans = {read=get_ZmthSans, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING Brah = {read=get_Brah};
	/* static */ __property HSTRING MathBold = {read=get_MathBold};
	/* static */ __property HSTRING MathDbl = {read=get_MathDbl};
	/* static */ __property HSTRING MathMono = {read=get_MathMono};
	/* static */ __property HSTRING MathSanb = {read=get_MathSanb};
	/* static */ __property HSTRING MathSans = {read=get_MathSans};
	/* static */ __property HSTRING Osma = {read=get_Osma};
	/* static */ __property HSTRING ZmthBold = {read=get_ZmthBold};
	/* static */ __property HSTRING ZmthDbl = {read=get_ZmthDbl};
	/* static */ __property HSTRING ZmthMono = {read=get_ZmthMono};
	/* static */ __property HSTRING ZmthSanb = {read=get_ZmthSanb};
	/* static */ __property HSTRING ZmthSans = {read=get_ZmthSans};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TNumeralSystemIdentifiers() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_INumeralSystemIdentifiersStatics,_di_INumeralSystemIdentifiersStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumeralSystemIdentifiers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCurrencyIdentifiers : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICurrencyIdentifiersStatics,_di_ICurrencyIdentifiersStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICurrencyIdentifiersStatics,_di_ICurrencyIdentifiersStatics2> inherited;
	
public:
	static HSTRING __fastcall get_BYN();
#ifndef _WIN64
	/* static */ __property HSTRING BYN = {read=get_BYN, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING BYN = {read=get_BYN};
#endif /* _WIN64 */
	static HSTRING __fastcall get_AED();
	static HSTRING __fastcall get_AFN();
	static HSTRING __fastcall get_ALL();
	static HSTRING __fastcall get_AMD();
	static HSTRING __fastcall get_ANG();
	static HSTRING __fastcall get_AOA();
	static HSTRING __fastcall get_ARS();
	static HSTRING __fastcall get_AUD();
	static HSTRING __fastcall get_AWG();
	static HSTRING __fastcall get_AZN();
	static HSTRING __fastcall get_BAM();
	static HSTRING __fastcall get_BBD();
	static HSTRING __fastcall get_BDT();
	static HSTRING __fastcall get_BGN();
	static HSTRING __fastcall get_BHD();
	static HSTRING __fastcall get_BIF();
	static HSTRING __fastcall get_BMD();
	static HSTRING __fastcall get_BND();
	static HSTRING __fastcall get_BOB();
	static HSTRING __fastcall get_BRL();
	static HSTRING __fastcall get_BSD();
	static HSTRING __fastcall get_BTN();
	static HSTRING __fastcall get_BWP();
	static HSTRING __fastcall get_BYR();
	static HSTRING __fastcall get_BZD();
	static HSTRING __fastcall get_CAD();
	static HSTRING __fastcall get_CDF();
	static HSTRING __fastcall get_CHF();
	static HSTRING __fastcall get_CLP();
	static HSTRING __fastcall get_CNY();
	static HSTRING __fastcall get_COP();
	static HSTRING __fastcall get_CRC();
	static HSTRING __fastcall get_CUP();
	static HSTRING __fastcall get_CVE();
	static HSTRING __fastcall get_CZK();
	static HSTRING __fastcall get_DJF();
	static HSTRING __fastcall get_DKK();
	static HSTRING __fastcall get_DOP();
	static HSTRING __fastcall get_DZD();
	static HSTRING __fastcall get_EGP();
	static HSTRING __fastcall get_ERN();
	static HSTRING __fastcall get_ETB();
	static HSTRING __fastcall get_EUR();
	static HSTRING __fastcall get_FJD();
	static HSTRING __fastcall get_FKP();
	static HSTRING __fastcall get_GBP();
	static HSTRING __fastcall get_GEL();
	static HSTRING __fastcall get_GHS();
	static HSTRING __fastcall get_GIP();
	static HSTRING __fastcall get_GMD();
	static HSTRING __fastcall get_GNF();
	static HSTRING __fastcall get_GTQ();
	static HSTRING __fastcall get_GYD();
	static HSTRING __fastcall get_HKD();
	static HSTRING __fastcall get_HNL();
	static HSTRING __fastcall get_HRK();
	static HSTRING __fastcall get_HTG();
	static HSTRING __fastcall get_HUF();
	static HSTRING __fastcall get_IDR();
	static HSTRING __fastcall get_ILS();
	static HSTRING __fastcall get_INR();
	static HSTRING __fastcall get_IQD();
	static HSTRING __fastcall get_IRR();
	static HSTRING __fastcall get_ISK();
	static HSTRING __fastcall get_JMD();
	static HSTRING __fastcall get_JOD();
	static HSTRING __fastcall get_JPY();
	static HSTRING __fastcall get_KES();
	static HSTRING __fastcall get_KGS();
	static HSTRING __fastcall get_KHR();
	static HSTRING __fastcall get_KMF();
	static HSTRING __fastcall get_KPW();
	static HSTRING __fastcall get_KRW();
	static HSTRING __fastcall get_KWD();
	static HSTRING __fastcall get_KYD();
	static HSTRING __fastcall get_KZT();
	static HSTRING __fastcall get_LAK();
	static HSTRING __fastcall get_LBP();
	static HSTRING __fastcall get_LKR();
	static HSTRING __fastcall get_LRD();
	static HSTRING __fastcall get_LSL();
	static HSTRING __fastcall get_LTL();
	static HSTRING __fastcall get_LVL();
	static HSTRING __fastcall get_LYD();
	static HSTRING __fastcall get_MAD();
	static HSTRING __fastcall get_MDL();
	static HSTRING __fastcall get_MGA();
	static HSTRING __fastcall get_MKD();
	static HSTRING __fastcall get_MMK();
	static HSTRING __fastcall get_MNT();
	static HSTRING __fastcall get_MOP();
	static HSTRING __fastcall get_MRO();
	static HSTRING __fastcall get_MUR();
	static HSTRING __fastcall get_MVR();
	static HSTRING __fastcall get_MWK();
	static HSTRING __fastcall get_MXN();
	static HSTRING __fastcall get_MYR();
	static HSTRING __fastcall get_MZN();
	static HSTRING __fastcall get_NAD();
	static HSTRING __fastcall get_NGN();
	static HSTRING __fastcall get_NIO();
	static HSTRING __fastcall get_NOK();
	static HSTRING __fastcall get_NPR();
	static HSTRING __fastcall get_NZD();
	static HSTRING __fastcall get_OMR();
	static HSTRING __fastcall get_PAB();
	static HSTRING __fastcall get_PEN();
	static HSTRING __fastcall get_PGK();
	static HSTRING __fastcall get_PHP();
	static HSTRING __fastcall get_PKR();
	static HSTRING __fastcall get_PLN();
	static HSTRING __fastcall get_PYG();
	static HSTRING __fastcall get_QAR();
	static HSTRING __fastcall get_RON();
	static HSTRING __fastcall get_RSD();
	static HSTRING __fastcall get_RUB();
	static HSTRING __fastcall get_RWF();
	static HSTRING __fastcall get_SAR();
	static HSTRING __fastcall get_SBD();
	static HSTRING __fastcall get_SCR();
	static HSTRING __fastcall get_SDG();
	static HSTRING __fastcall get_SEK();
	static HSTRING __fastcall get_SGD();
	static HSTRING __fastcall get_SHP();
	static HSTRING __fastcall get_SLL();
	static HSTRING __fastcall get_SOS();
	static HSTRING __fastcall get_SRD();
	static HSTRING __fastcall get_STD();
	static HSTRING __fastcall get_SYP();
	static HSTRING __fastcall get_SZL();
	static HSTRING __fastcall get_THB();
	static HSTRING __fastcall get_TJS();
	static HSTRING __fastcall get_TMT();
	static HSTRING __fastcall get_TND();
	static HSTRING __fastcall get_TOP();
	static HSTRING __fastcall get_TRY();
	static HSTRING __fastcall get_TTD();
	static HSTRING __fastcall get_TWD();
	static HSTRING __fastcall get_TZS();
	static HSTRING __fastcall get_UAH();
	static HSTRING __fastcall get_UGX();
	static HSTRING __fastcall get_USD();
	static HSTRING __fastcall get_UYU();
	static HSTRING __fastcall get_UZS();
	static HSTRING __fastcall get_VEF();
	static HSTRING __fastcall get_VND();
	static HSTRING __fastcall get_VUV();
	static HSTRING __fastcall get_WST();
	static HSTRING __fastcall get_XAF();
	static HSTRING __fastcall get_XCD();
	static HSTRING __fastcall get_XOF();
	static HSTRING __fastcall get_XPF();
	static HSTRING __fastcall get_XXX();
	static HSTRING __fastcall get_YER();
	static HSTRING __fastcall get_ZAR();
	static HSTRING __fastcall get_ZMW();
	static HSTRING __fastcall get_ZWL();
#ifndef _WIN64
	/* static */ __property HSTRING AED = {read=get_AED, nodefault};
	/* static */ __property HSTRING AFN = {read=get_AFN, nodefault};
	/* static */ __property HSTRING ALL = {read=get_ALL, nodefault};
	/* static */ __property HSTRING AMD = {read=get_AMD, nodefault};
	/* static */ __property HSTRING ANG = {read=get_ANG, nodefault};
	/* static */ __property HSTRING AOA = {read=get_AOA, nodefault};
	/* static */ __property HSTRING ARS = {read=get_ARS, nodefault};
	/* static */ __property HSTRING AUD = {read=get_AUD, nodefault};
	/* static */ __property HSTRING AWG = {read=get_AWG, nodefault};
	/* static */ __property HSTRING AZN = {read=get_AZN, nodefault};
	/* static */ __property HSTRING BAM = {read=get_BAM, nodefault};
	/* static */ __property HSTRING BBD = {read=get_BBD, nodefault};
	/* static */ __property HSTRING BDT = {read=get_BDT, nodefault};
	/* static */ __property HSTRING BGN = {read=get_BGN, nodefault};
	/* static */ __property HSTRING BHD = {read=get_BHD, nodefault};
	/* static */ __property HSTRING BIF = {read=get_BIF, nodefault};
	/* static */ __property HSTRING BMD = {read=get_BMD, nodefault};
	/* static */ __property HSTRING BND = {read=get_BND, nodefault};
	/* static */ __property HSTRING BOB = {read=get_BOB, nodefault};
	/* static */ __property HSTRING BRL = {read=get_BRL, nodefault};
	/* static */ __property HSTRING BSD = {read=get_BSD, nodefault};
	/* static */ __property HSTRING BTN = {read=get_BTN, nodefault};
	/* static */ __property HSTRING BWP = {read=get_BWP, nodefault};
	/* static */ __property HSTRING BYR = {read=get_BYR, nodefault};
	/* static */ __property HSTRING BZD = {read=get_BZD, nodefault};
	/* static */ __property HSTRING CAD = {read=get_CAD, nodefault};
	/* static */ __property HSTRING CDF = {read=get_CDF, nodefault};
	/* static */ __property HSTRING CHF = {read=get_CHF, nodefault};
	/* static */ __property HSTRING CLP = {read=get_CLP, nodefault};
	/* static */ __property HSTRING CNY = {read=get_CNY, nodefault};
	/* static */ __property HSTRING COP = {read=get_COP, nodefault};
	/* static */ __property HSTRING CRC = {read=get_CRC, nodefault};
	/* static */ __property HSTRING CUP = {read=get_CUP, nodefault};
	/* static */ __property HSTRING CVE = {read=get_CVE, nodefault};
	/* static */ __property HSTRING CZK = {read=get_CZK, nodefault};
	/* static */ __property HSTRING DJF = {read=get_DJF, nodefault};
	/* static */ __property HSTRING DKK = {read=get_DKK, nodefault};
	/* static */ __property HSTRING DOP = {read=get_DOP, nodefault};
	/* static */ __property HSTRING DZD = {read=get_DZD, nodefault};
	/* static */ __property HSTRING EGP = {read=get_EGP, nodefault};
	/* static */ __property HSTRING ERN = {read=get_ERN, nodefault};
	/* static */ __property HSTRING ETB = {read=get_ETB, nodefault};
	/* static */ __property HSTRING EUR = {read=get_EUR, nodefault};
	/* static */ __property HSTRING FJD = {read=get_FJD, nodefault};
	/* static */ __property HSTRING FKP = {read=get_FKP, nodefault};
	/* static */ __property HSTRING GBP = {read=get_GBP, nodefault};
	/* static */ __property HSTRING GEL = {read=get_GEL, nodefault};
	/* static */ __property HSTRING GHS = {read=get_GHS, nodefault};
	/* static */ __property HSTRING GIP = {read=get_GIP, nodefault};
	/* static */ __property HSTRING GMD = {read=get_GMD, nodefault};
	/* static */ __property HSTRING GNF = {read=get_GNF, nodefault};
	/* static */ __property HSTRING GTQ = {read=get_GTQ, nodefault};
	/* static */ __property HSTRING GYD = {read=get_GYD, nodefault};
	/* static */ __property HSTRING HKD = {read=get_HKD, nodefault};
	/* static */ __property HSTRING HNL = {read=get_HNL, nodefault};
	/* static */ __property HSTRING HRK = {read=get_HRK, nodefault};
	/* static */ __property HSTRING HTG = {read=get_HTG, nodefault};
	/* static */ __property HSTRING HUF = {read=get_HUF, nodefault};
	/* static */ __property HSTRING IDR = {read=get_IDR, nodefault};
	/* static */ __property HSTRING ILS = {read=get_ILS, nodefault};
	/* static */ __property HSTRING INR = {read=get_INR, nodefault};
	/* static */ __property HSTRING IQD = {read=get_IQD, nodefault};
	/* static */ __property HSTRING IRR = {read=get_IRR, nodefault};
	/* static */ __property HSTRING ISK = {read=get_ISK, nodefault};
	/* static */ __property HSTRING JMD = {read=get_JMD, nodefault};
	/* static */ __property HSTRING JOD = {read=get_JOD, nodefault};
	/* static */ __property HSTRING JPY = {read=get_JPY, nodefault};
	/* static */ __property HSTRING KES = {read=get_KES, nodefault};
	/* static */ __property HSTRING KGS = {read=get_KGS, nodefault};
	/* static */ __property HSTRING KHR = {read=get_KHR, nodefault};
	/* static */ __property HSTRING KMF = {read=get_KMF, nodefault};
	/* static */ __property HSTRING KPW = {read=get_KPW, nodefault};
	/* static */ __property HSTRING KRW = {read=get_KRW, nodefault};
	/* static */ __property HSTRING KWD = {read=get_KWD, nodefault};
	/* static */ __property HSTRING KYD = {read=get_KYD, nodefault};
	/* static */ __property HSTRING KZT = {read=get_KZT, nodefault};
	/* static */ __property HSTRING LAK = {read=get_LAK, nodefault};
	/* static */ __property HSTRING LBP = {read=get_LBP, nodefault};
	/* static */ __property HSTRING LKR = {read=get_LKR, nodefault};
	/* static */ __property HSTRING LRD = {read=get_LRD, nodefault};
	/* static */ __property HSTRING LSL = {read=get_LSL, nodefault};
	/* static */ __property HSTRING LTL = {read=get_LTL, nodefault};
	/* static */ __property HSTRING LVL = {read=get_LVL, nodefault};
	/* static */ __property HSTRING LYD = {read=get_LYD, nodefault};
	/* static */ __property HSTRING MAD = {read=get_MAD, nodefault};
	/* static */ __property HSTRING MDL = {read=get_MDL, nodefault};
	/* static */ __property HSTRING MGA = {read=get_MGA, nodefault};
	/* static */ __property HSTRING MKD = {read=get_MKD, nodefault};
	/* static */ __property HSTRING MMK = {read=get_MMK, nodefault};
	/* static */ __property HSTRING MNT = {read=get_MNT, nodefault};
	/* static */ __property HSTRING MOP = {read=get_MOP, nodefault};
	/* static */ __property HSTRING MRO = {read=get_MRO, nodefault};
	/* static */ __property HSTRING MUR = {read=get_MUR, nodefault};
	/* static */ __property HSTRING MVR = {read=get_MVR, nodefault};
	/* static */ __property HSTRING MWK = {read=get_MWK, nodefault};
	/* static */ __property HSTRING MXN = {read=get_MXN, nodefault};
	/* static */ __property HSTRING MYR = {read=get_MYR, nodefault};
	/* static */ __property HSTRING MZN = {read=get_MZN, nodefault};
	/* static */ __property HSTRING NAD = {read=get_NAD, nodefault};
	/* static */ __property HSTRING NGN = {read=get_NGN, nodefault};
	/* static */ __property HSTRING NIO = {read=get_NIO, nodefault};
	/* static */ __property HSTRING NOK = {read=get_NOK, nodefault};
	/* static */ __property HSTRING NPR = {read=get_NPR, nodefault};
	/* static */ __property HSTRING NZD = {read=get_NZD, nodefault};
	/* static */ __property HSTRING OMR = {read=get_OMR, nodefault};
	/* static */ __property HSTRING PAB = {read=get_PAB, nodefault};
	/* static */ __property HSTRING PEN = {read=get_PEN, nodefault};
	/* static */ __property HSTRING PGK = {read=get_PGK, nodefault};
	/* static */ __property HSTRING PHP = {read=get_PHP, nodefault};
	/* static */ __property HSTRING PKR = {read=get_PKR, nodefault};
	/* static */ __property HSTRING PLN = {read=get_PLN, nodefault};
	/* static */ __property HSTRING PYG = {read=get_PYG, nodefault};
	/* static */ __property HSTRING QAR = {read=get_QAR, nodefault};
	/* static */ __property HSTRING RON = {read=get_RON, nodefault};
	/* static */ __property HSTRING RSD = {read=get_RSD, nodefault};
	/* static */ __property HSTRING RUB = {read=get_RUB, nodefault};
	/* static */ __property HSTRING RWF = {read=get_RWF, nodefault};
	/* static */ __property HSTRING SAR = {read=get_SAR, nodefault};
	/* static */ __property HSTRING SBD = {read=get_SBD, nodefault};
	/* static */ __property HSTRING SCR = {read=get_SCR, nodefault};
	/* static */ __property HSTRING SDG = {read=get_SDG, nodefault};
	/* static */ __property HSTRING SEK = {read=get_SEK, nodefault};
	/* static */ __property HSTRING SGD = {read=get_SGD, nodefault};
	/* static */ __property HSTRING SHP = {read=get_SHP, nodefault};
	/* static */ __property HSTRING SLL = {read=get_SLL, nodefault};
	/* static */ __property HSTRING SOS = {read=get_SOS, nodefault};
	/* static */ __property HSTRING SRD = {read=get_SRD, nodefault};
	/* static */ __property HSTRING STD = {read=get_STD, nodefault};
	/* static */ __property HSTRING SYP = {read=get_SYP, nodefault};
	/* static */ __property HSTRING SZL = {read=get_SZL, nodefault};
	/* static */ __property HSTRING THB = {read=get_THB, nodefault};
	/* static */ __property HSTRING TJS = {read=get_TJS, nodefault};
	/* static */ __property HSTRING TMT = {read=get_TMT, nodefault};
	/* static */ __property HSTRING TND = {read=get_TND, nodefault};
	/* static */ __property HSTRING TOP = {read=get_TOP, nodefault};
	/* static */ __property HSTRING TRY = {read=get_TRY, nodefault};
	/* static */ __property HSTRING TTD = {read=get_TTD, nodefault};
	/* static */ __property HSTRING TWD = {read=get_TWD, nodefault};
	/* static */ __property HSTRING TZS = {read=get_TZS, nodefault};
	/* static */ __property HSTRING UAH = {read=get_UAH, nodefault};
	/* static */ __property HSTRING UGX = {read=get_UGX, nodefault};
	/* static */ __property HSTRING USD = {read=get_USD, nodefault};
	/* static */ __property HSTRING UYU = {read=get_UYU, nodefault};
	/* static */ __property HSTRING UZS = {read=get_UZS, nodefault};
	/* static */ __property HSTRING VEF = {read=get_VEF, nodefault};
	/* static */ __property HSTRING VND = {read=get_VND, nodefault};
	/* static */ __property HSTRING VUV = {read=get_VUV, nodefault};
	/* static */ __property HSTRING WST = {read=get_WST, nodefault};
	/* static */ __property HSTRING XAF = {read=get_XAF, nodefault};
	/* static */ __property HSTRING XCD = {read=get_XCD, nodefault};
	/* static */ __property HSTRING XOF = {read=get_XOF, nodefault};
	/* static */ __property HSTRING XPF = {read=get_XPF, nodefault};
	/* static */ __property HSTRING XXX = {read=get_XXX, nodefault};
	/* static */ __property HSTRING YER = {read=get_YER, nodefault};
	/* static */ __property HSTRING ZAR = {read=get_ZAR, nodefault};
	/* static */ __property HSTRING ZMW = {read=get_ZMW, nodefault};
	/* static */ __property HSTRING ZWL = {read=get_ZWL, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING AED = {read=get_AED};
	/* static */ __property HSTRING AFN = {read=get_AFN};
	/* static */ __property HSTRING ALL = {read=get_ALL};
	/* static */ __property HSTRING AMD = {read=get_AMD};
	/* static */ __property HSTRING ANG = {read=get_ANG};
	/* static */ __property HSTRING AOA = {read=get_AOA};
	/* static */ __property HSTRING ARS = {read=get_ARS};
	/* static */ __property HSTRING AUD = {read=get_AUD};
	/* static */ __property HSTRING AWG = {read=get_AWG};
	/* static */ __property HSTRING AZN = {read=get_AZN};
	/* static */ __property HSTRING BAM = {read=get_BAM};
	/* static */ __property HSTRING BBD = {read=get_BBD};
	/* static */ __property HSTRING BDT = {read=get_BDT};
	/* static */ __property HSTRING BGN = {read=get_BGN};
	/* static */ __property HSTRING BHD = {read=get_BHD};
	/* static */ __property HSTRING BIF = {read=get_BIF};
	/* static */ __property HSTRING BMD = {read=get_BMD};
	/* static */ __property HSTRING BND = {read=get_BND};
	/* static */ __property HSTRING BOB = {read=get_BOB};
	/* static */ __property HSTRING BRL = {read=get_BRL};
	/* static */ __property HSTRING BSD = {read=get_BSD};
	/* static */ __property HSTRING BTN = {read=get_BTN};
	/* static */ __property HSTRING BWP = {read=get_BWP};
	/* static */ __property HSTRING BYR = {read=get_BYR};
	/* static */ __property HSTRING BZD = {read=get_BZD};
	/* static */ __property HSTRING CAD = {read=get_CAD};
	/* static */ __property HSTRING CDF = {read=get_CDF};
	/* static */ __property HSTRING CHF = {read=get_CHF};
	/* static */ __property HSTRING CLP = {read=get_CLP};
	/* static */ __property HSTRING CNY = {read=get_CNY};
	/* static */ __property HSTRING COP = {read=get_COP};
	/* static */ __property HSTRING CRC = {read=get_CRC};
	/* static */ __property HSTRING CUP = {read=get_CUP};
	/* static */ __property HSTRING CVE = {read=get_CVE};
	/* static */ __property HSTRING CZK = {read=get_CZK};
	/* static */ __property HSTRING DJF = {read=get_DJF};
	/* static */ __property HSTRING DKK = {read=get_DKK};
	/* static */ __property HSTRING DOP = {read=get_DOP};
	/* static */ __property HSTRING DZD = {read=get_DZD};
	/* static */ __property HSTRING EGP = {read=get_EGP};
	/* static */ __property HSTRING ERN = {read=get_ERN};
	/* static */ __property HSTRING ETB = {read=get_ETB};
	/* static */ __property HSTRING EUR = {read=get_EUR};
	/* static */ __property HSTRING FJD = {read=get_FJD};
	/* static */ __property HSTRING FKP = {read=get_FKP};
	/* static */ __property HSTRING GBP = {read=get_GBP};
	/* static */ __property HSTRING GEL = {read=get_GEL};
	/* static */ __property HSTRING GHS = {read=get_GHS};
	/* static */ __property HSTRING GIP = {read=get_GIP};
	/* static */ __property HSTRING GMD = {read=get_GMD};
	/* static */ __property HSTRING GNF = {read=get_GNF};
	/* static */ __property HSTRING GTQ = {read=get_GTQ};
	/* static */ __property HSTRING GYD = {read=get_GYD};
	/* static */ __property HSTRING HKD = {read=get_HKD};
	/* static */ __property HSTRING HNL = {read=get_HNL};
	/* static */ __property HSTRING HRK = {read=get_HRK};
	/* static */ __property HSTRING HTG = {read=get_HTG};
	/* static */ __property HSTRING HUF = {read=get_HUF};
	/* static */ __property HSTRING IDR = {read=get_IDR};
	/* static */ __property HSTRING ILS = {read=get_ILS};
	/* static */ __property HSTRING INR = {read=get_INR};
	/* static */ __property HSTRING IQD = {read=get_IQD};
	/* static */ __property HSTRING IRR = {read=get_IRR};
	/* static */ __property HSTRING ISK = {read=get_ISK};
	/* static */ __property HSTRING JMD = {read=get_JMD};
	/* static */ __property HSTRING JOD = {read=get_JOD};
	/* static */ __property HSTRING JPY = {read=get_JPY};
	/* static */ __property HSTRING KES = {read=get_KES};
	/* static */ __property HSTRING KGS = {read=get_KGS};
	/* static */ __property HSTRING KHR = {read=get_KHR};
	/* static */ __property HSTRING KMF = {read=get_KMF};
	/* static */ __property HSTRING KPW = {read=get_KPW};
	/* static */ __property HSTRING KRW = {read=get_KRW};
	/* static */ __property HSTRING KWD = {read=get_KWD};
	/* static */ __property HSTRING KYD = {read=get_KYD};
	/* static */ __property HSTRING KZT = {read=get_KZT};
	/* static */ __property HSTRING LAK = {read=get_LAK};
	/* static */ __property HSTRING LBP = {read=get_LBP};
	/* static */ __property HSTRING LKR = {read=get_LKR};
	/* static */ __property HSTRING LRD = {read=get_LRD};
	/* static */ __property HSTRING LSL = {read=get_LSL};
	/* static */ __property HSTRING LTL = {read=get_LTL};
	/* static */ __property HSTRING LVL = {read=get_LVL};
	/* static */ __property HSTRING LYD = {read=get_LYD};
	/* static */ __property HSTRING MAD = {read=get_MAD};
	/* static */ __property HSTRING MDL = {read=get_MDL};
	/* static */ __property HSTRING MGA = {read=get_MGA};
	/* static */ __property HSTRING MKD = {read=get_MKD};
	/* static */ __property HSTRING MMK = {read=get_MMK};
	/* static */ __property HSTRING MNT = {read=get_MNT};
	/* static */ __property HSTRING MOP = {read=get_MOP};
	/* static */ __property HSTRING MRO = {read=get_MRO};
	/* static */ __property HSTRING MUR = {read=get_MUR};
	/* static */ __property HSTRING MVR = {read=get_MVR};
	/* static */ __property HSTRING MWK = {read=get_MWK};
	/* static */ __property HSTRING MXN = {read=get_MXN};
	/* static */ __property HSTRING MYR = {read=get_MYR};
	/* static */ __property HSTRING MZN = {read=get_MZN};
	/* static */ __property HSTRING NAD = {read=get_NAD};
	/* static */ __property HSTRING NGN = {read=get_NGN};
	/* static */ __property HSTRING NIO = {read=get_NIO};
	/* static */ __property HSTRING NOK = {read=get_NOK};
	/* static */ __property HSTRING NPR = {read=get_NPR};
	/* static */ __property HSTRING NZD = {read=get_NZD};
	/* static */ __property HSTRING OMR = {read=get_OMR};
	/* static */ __property HSTRING PAB = {read=get_PAB};
	/* static */ __property HSTRING PEN = {read=get_PEN};
	/* static */ __property HSTRING PGK = {read=get_PGK};
	/* static */ __property HSTRING PHP = {read=get_PHP};
	/* static */ __property HSTRING PKR = {read=get_PKR};
	/* static */ __property HSTRING PLN = {read=get_PLN};
	/* static */ __property HSTRING PYG = {read=get_PYG};
	/* static */ __property HSTRING QAR = {read=get_QAR};
	/* static */ __property HSTRING RON = {read=get_RON};
	/* static */ __property HSTRING RSD = {read=get_RSD};
	/* static */ __property HSTRING RUB = {read=get_RUB};
	/* static */ __property HSTRING RWF = {read=get_RWF};
	/* static */ __property HSTRING SAR = {read=get_SAR};
	/* static */ __property HSTRING SBD = {read=get_SBD};
	/* static */ __property HSTRING SCR = {read=get_SCR};
	/* static */ __property HSTRING SDG = {read=get_SDG};
	/* static */ __property HSTRING SEK = {read=get_SEK};
	/* static */ __property HSTRING SGD = {read=get_SGD};
	/* static */ __property HSTRING SHP = {read=get_SHP};
	/* static */ __property HSTRING SLL = {read=get_SLL};
	/* static */ __property HSTRING SOS = {read=get_SOS};
	/* static */ __property HSTRING SRD = {read=get_SRD};
	/* static */ __property HSTRING STD = {read=get_STD};
	/* static */ __property HSTRING SYP = {read=get_SYP};
	/* static */ __property HSTRING SZL = {read=get_SZL};
	/* static */ __property HSTRING THB = {read=get_THB};
	/* static */ __property HSTRING TJS = {read=get_TJS};
	/* static */ __property HSTRING TMT = {read=get_TMT};
	/* static */ __property HSTRING TND = {read=get_TND};
	/* static */ __property HSTRING TOP = {read=get_TOP};
	/* static */ __property HSTRING TRY = {read=get_TRY};
	/* static */ __property HSTRING TTD = {read=get_TTD};
	/* static */ __property HSTRING TWD = {read=get_TWD};
	/* static */ __property HSTRING TZS = {read=get_TZS};
	/* static */ __property HSTRING UAH = {read=get_UAH};
	/* static */ __property HSTRING UGX = {read=get_UGX};
	/* static */ __property HSTRING USD = {read=get_USD};
	/* static */ __property HSTRING UYU = {read=get_UYU};
	/* static */ __property HSTRING UZS = {read=get_UZS};
	/* static */ __property HSTRING VEF = {read=get_VEF};
	/* static */ __property HSTRING VND = {read=get_VND};
	/* static */ __property HSTRING VUV = {read=get_VUV};
	/* static */ __property HSTRING WST = {read=get_WST};
	/* static */ __property HSTRING XAF = {read=get_XAF};
	/* static */ __property HSTRING XCD = {read=get_XCD};
	/* static */ __property HSTRING XOF = {read=get_XOF};
	/* static */ __property HSTRING XPF = {read=get_XPF};
	/* static */ __property HSTRING XXX = {read=get_XXX};
	/* static */ __property HSTRING YER = {read=get_YER};
	/* static */ __property HSTRING ZAR = {read=get_ZAR};
	/* static */ __property HSTRING ZMW = {read=get_ZMW};
	/* static */ __property HSTRING ZWL = {read=get_ZWL};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TCurrencyIdentifiers() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICurrencyIdentifiersStatics,_di_ICurrencyIdentifiersStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCurrencyIdentifiers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeographicRegion : public System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IGeographicRegionFactory,_di_IGeographicRegionStatics,_di_IGeographicRegion>
{
	typedef System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IGeographicRegionFactory,_di_IGeographicRegionStatics,_di_IGeographicRegion> inherited;
	
public:
	static bool __fastcall IsSupported(HSTRING geographicRegionCode);
	static _di_IGeographicRegion __fastcall CreateGeographicRegion(HSTRING geographicRegionCode);
public:
	/* TObject.Create */ inline __fastcall TGeographicRegion() : System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IGeographicRegionFactory,_di_IGeographicRegionStatics,_di_IGeographicRegion>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeographicRegion() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLanguage : public System::Win::Winrt::TWinRTGenericImportFS2__3<_di_ILanguageFactory,_di_ILanguageStatics,_di_ILanguageStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS2__3<_di_ILanguageFactory,_di_ILanguageStatics,_di_ILanguageStatics2> inherited;
	
public:
	static bool __fastcall TrySetInputMethodLanguageTag(HSTRING languageTag);
	static bool __fastcall IsWellFormed(HSTRING languageTag);
	static HSTRING __fastcall get_CurrentInputMethodLanguageTag();
#ifndef _WIN64
	/* static */ __property HSTRING CurrentInputMethodLanguageTag = {read=get_CurrentInputMethodLanguageTag, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING CurrentInputMethodLanguageTag = {read=get_CurrentInputMethodLanguageTag};
#endif /* _WIN64 */
	static _di_ILanguage __fastcall CreateLanguage(HSTRING languageTag);
public:
	/* TObject.Create */ inline __fastcall TLanguage() : System::Win::Winrt::TWinRTGenericImportFS2__3<_di_ILanguageFactory,_di_ILanguageStatics,_di_ILanguageStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLanguage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDateTimeFormatting_DateTimeFormatter : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_DateTimeFormatting_IDateTimeFormatterFactory,_di_DateTimeFormatting_IDateTimeFormatterStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_DateTimeFormatting_IDateTimeFormatterFactory,_di_DateTimeFormatting_IDateTimeFormatterStatics> inherited;
	
public:
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall get_LongDate();
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall get_LongTime();
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall get_ShortDate();
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall get_ShortTime();
	/* static */ __property _di_DateTimeFormatting_IDateTimeFormatter LongDate = {read=get_LongDate};
	/* static */ __property _di_DateTimeFormatting_IDateTimeFormatter LongTime = {read=get_LongTime};
	/* static */ __property _di_DateTimeFormatting_IDateTimeFormatter ShortDate = {read=get_ShortDate};
	/* static */ __property _di_DateTimeFormatting_IDateTimeFormatter ShortTime = {read=get_ShortTime};
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatter(HSTRING formatTemplate);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterLanguages(HSTRING formatTemplate, _di_IIterable_1__HSTRING languages);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterContext(HSTRING formatTemplate, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion, HSTRING calendar, HSTRING clock);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterDate(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterTime(Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterDateTimeLanguages(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat, Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat, _di_IIterable_1__HSTRING languages);
	static _di_DateTimeFormatting_IDateTimeFormatter __fastcall CreateDateTimeFormatterDateTimeContext(Winapi::Commontypes::DateTimeFormatting_YearFormat yearFormat, Winapi::Commontypes::DateTimeFormatting_MonthFormat monthFormat, Winapi::Commontypes::DateTimeFormatting_DayFormat dayFormat, Winapi::Commontypes::DateTimeFormatting_DayOfWeekFormat dayOfWeekFormat, Winapi::Commontypes::DateTimeFormatting_HourFormat hourFormat, Winapi::Commontypes::DateTimeFormatting_MinuteFormat minuteFormat, Winapi::Commontypes::DateTimeFormatting_SecondFormat secondFormat, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion, HSTRING calendar, HSTRING clock);
public:
	/* TObject.Create */ inline __fastcall TDateTimeFormatting_DateTimeFormatter() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_DateTimeFormatting_IDateTimeFormatterFactory,_di_DateTimeFormatting_IDateTimeFormatterStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDateTimeFormatting_DateTimeFormatter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCalendar : public System::Win::Winrt::TWinRTGenericImportF2I__3<_di_ICalendarFactory,_di_ICalendarFactory2,_di_ICalendar>
{
	typedef System::Win::Winrt::TWinRTGenericImportF2I__3<_di_ICalendarFactory,_di_ICalendarFactory2,_di_ICalendar> inherited;
	
public:
	static _di_ICalendar __fastcall CreateCalendarWithTimeZone(_di_IIterable_1__HSTRING languages, HSTRING calendar, HSTRING clock, HSTRING timeZoneId);
	static _di_ICalendar __fastcall CreateCalendarDefaultCalendarAndClock(_di_IIterable_1__HSTRING languages);
	static _di_ICalendar __fastcall CreateCalendar(_di_IIterable_1__HSTRING languages, HSTRING calendar, HSTRING clock);
public:
	/* TObject.Create */ inline __fastcall TCalendar() : System::Win::Winrt::TWinRTGenericImportF2I__3<_di_ICalendarFactory,_di_ICalendarFactory2,_di_ICalendar>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCalendar() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_SignificantDigitsNumberRounder : public System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_ISignificantDigitsNumberRounder>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_ISignificantDigitsNumberRounder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_SignificantDigitsNumberRounder() : System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_ISignificantDigitsNumberRounder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_SignificantDigitsNumberRounder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_IncrementNumberRounder : public System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_IIncrementNumberRounder>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_IIncrementNumberRounder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_IncrementNumberRounder() : System::Win::Winrt::TWinRTGenericImportI__1<_di_NumberFormatting_IIncrementNumberRounder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_IncrementNumberRounder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_DecimalFormatter : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IDecimalFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IDecimalFormatterFactory,_di_NumberFormatting_INumberFormatterOptions> inherited;
	
public:
	static _di_NumberFormatting_INumberFormatterOptions __fastcall CreateDecimalFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion);
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_DecimalFormatter() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IDecimalFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_DecimalFormatter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_PercentFormatter : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPercentFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPercentFormatterFactory,_di_NumberFormatting_INumberFormatterOptions> inherited;
	
public:
	static _di_NumberFormatting_INumberFormatterOptions __fastcall CreatePercentFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion);
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_PercentFormatter() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPercentFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_PercentFormatter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_PermilleFormatter : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPermilleFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPermilleFormatterFactory,_di_NumberFormatting_INumberFormatterOptions> inherited;
	
public:
	static _di_NumberFormatting_INumberFormatterOptions __fastcall CreatePermilleFormatter(_di_IIterable_1__HSTRING languages, HSTRING geographicRegion);
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_PermilleFormatter() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_IPermilleFormatterFactory,_di_NumberFormatting_INumberFormatterOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_PermilleFormatter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_CurrencyFormatter : public System::Win::Winrt::TWinRTGenericImportF__1<_di_NumberFormatting_ICurrencyFormatterFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_NumberFormatting_ICurrencyFormatterFactory> inherited;
	
public:
	static _di_NumberFormatting_ICurrencyFormatter __fastcall CreateCurrencyFormatterCode(HSTRING currencyCode);
	static _di_NumberFormatting_ICurrencyFormatter __fastcall CreateCurrencyFormatterCodeContext(HSTRING currencyCode, _di_IIterable_1__HSTRING languages, HSTRING geographicRegion);
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_CurrencyFormatter() : System::Win::Winrt::TWinRTGenericImportF__1<_di_NumberFormatting_ICurrencyFormatterFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_CurrencyFormatter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNumberFormatting_NumeralSystemTranslator : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_INumeralSystemTranslatorFactory,_di_NumberFormatting_INumeralSystemTranslator>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_INumeralSystemTranslatorFactory,_di_NumberFormatting_INumeralSystemTranslator> inherited;
	
public:
	static _di_NumberFormatting_INumeralSystemTranslator __fastcall Create(_di_IIterable_1__HSTRING languages)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TNumberFormatting_NumeralSystemTranslator() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_NumberFormatting_INumeralSystemTranslatorFactory,_di_NumberFormatting_INumeralSystemTranslator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNumberFormatting_NumeralSystemTranslator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCollation_CharacterGroupings : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_Collation_ICharacterGroupingsFactory,_di_Collation_ICharacterGroupings>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_Collation_ICharacterGroupingsFactory,_di_Collation_ICharacterGroupings> inherited;
	
public:
	static _di_Collation_ICharacterGroupings __fastcall Create(HSTRING language)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TCollation_CharacterGroupings() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_Collation_ICharacterGroupingsFactory,_di_Collation_ICharacterGroupings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCollation_CharacterGroupings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Globalization */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_GlobalizationHPP
