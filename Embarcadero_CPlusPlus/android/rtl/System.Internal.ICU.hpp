// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Internal.ICU.pas' rev: 34.00 (Android)

#ifndef System_Internal_IcuHPP
#define System_Internal_IcuHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
namespace System
{
#if !defined(__ANDROID__)
    // System::_PPAnsiChar leaks via the PMarshaledAString alias
    typedef char**               _PPAnsiChar;
#endif
}

namespace System
{
namespace Internal
{
namespace Icu
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD USet
{
};


struct DECLSPEC_DRECORD UConverter
{
};


struct UConverterToUnicodeArgs;
struct UConverterFromUnicodeArgs;
struct DECLSPEC_DRECORD UCollator
{
};


struct DECLSPEC_DRECORD ULocaleData
{
};


struct UFieldPosition;
struct UParseError;
struct DECLSPEC_DRECORD UNumberFormat
{
};


struct DECLSPEC_DRECORD UDateFormat
{
};


struct DECLSPEC_DRECORD UCalendar
{
};


struct DECLSPEC_DRECORD UEnumeration
{
};


//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM UErrorCode: int { U_USING_FALLBACK_WARNING = -128, U_ERROR_WARNING_START = -128, U_USING_DEFAULT_WARNING, U_SAFECLONE_ALLOCATED_WARNING, U_STATE_OLD_WARNING, U_STRING_NOT_TERMINATED_WARNING, U_SORT_KEY_TOO_SHORT_WARNING, U_AMBIGUOUS_ALIAS_WARNING, U_DIFFERENT_UCA_VERSION, U_PLUGIN_CHANGED_LEVEL_WARNING, U_ERROR_WARNING_LIMIT, U_ZERO_ERROR = 0, U_ILLEGAL_ARGUMENT_ERROR, U_MISSING_RESOURCE_ERROR, U_INVALID_FORMAT_ERROR, U_FILE_ACCESS_ERROR, U_INTERNAL_PROGRAM_ERROR, U_MESSAGE_PARSE_ERROR, U_MEMORY_ALLOCATION_ERROR, U_INDEX_OUTOFBOUNDS_ERROR, U_PARSE_ERROR, U_INVALID_CHAR_FOUND, U_TRUNCATED_CHAR_FOUND, U_ILLEGAL_CHAR_FOUND, U_INVALID_TABLE_FORMAT, U_INVALID_TABLE_FILE, U_BUFFER_OVERFLOW_ERROR, U_UNSUPPORTED_ERROR, U_RESOURCE_TYPE_MISMATCH, 
	U_ILLEGAL_ESCAPE_SEQUENCE, U_UNSUPPORTED_ESCAPE_SEQUENCE, U_NO_SPACE_AVAILABLE, U_CE_NOT_FOUND_ERROR, U_PRIMARY_TOO_LONG_ERROR, U_STATE_TOO_OLD_ERROR, U_TOO_MANY_ALIASES_ERROR, U_ENUM_OUT_OF_SYNC_ERROR, U_INVARIANT_CONVERSION_ERROR, U_INVALID_STATE_ERROR, U_COLLATOR_VERSION_MISMATCH, U_USELESS_COLLATOR_ERROR, U_NO_WRITE_PERMISSION, U_STANDARD_ERROR_LIMIT, U_BAD_VARIABLE_DEFINITION = 65536, U_PARSE_ERROR_START = 65536, U_MALFORMED_RULE, U_MALFORMED_SET, U_MALFORMED_SYMBOL_REFERENCE, U_MALFORMED_UNICODE_ESCAPE, U_MALFORMED_VARIABLE_DEFINITION, U_MALFORMED_VARIABLE_REFERENCE, U_MISMATCHED_SEGMENT_DELIMITERS, U_MISPLACED_ANCHOR_START, U_MISPLACED_CURSOR_OFFSET, U_MISPLACED_QUANTIFIER, U_MISSING_OPERATOR, U_MISSING_SEGMENT_CLOSE, U_MULTIPLE_ANTE_CONTEXTS, 
	U_MULTIPLE_CURSORS, U_MULTIPLE_POST_CONTEXTS, U_TRAILING_BACKSLASH, U_UNDEFINED_SEGMENT_REFERENCE, U_UNDEFINED_VARIABLE, U_UNQUOTED_SPECIAL, U_UNTERMINATED_QUOTE, U_RULE_MASK_ERROR, U_MISPLACED_COMPOUND_FILTER, U_MULTIPLE_COMPOUND_FILTERS, U_INVALID_RBT_SYNTAX, U_INVALID_PROPERTY_PATTERN, U_MALFORMED_PRAGMA, U_UNCLOSED_SEGMENT, U_ILLEGAL_CHAR_IN_SEGMENT, U_VARIABLE_RANGE_EXHAUSTED, U_VARIABLE_RANGE_OVERLAP, U_ILLEGAL_CHARACTER, U_INTERNAL_TRANSLITERATOR_ERROR, U_INVALID_ID, U_INVALID_FUNCTION, U_PARSE_ERROR_LIMIT, U_UNEXPECTED_TOKEN = 65792, U_FMT_PARSE_ERROR_START = 65792, U_MULTIPLE_DECIMAL_SEPARATORS, U_MULTIPLE_DECIMAL_SEPERATORS = 65793, U_MULTIPLE_EXPONENTIAL_SYMBOLS, U_MALFORMED_EXPONENTIAL_PATTERN, U_MULTIPLE_PERCENT_SYMBOLS, 
	U_MULTIPLE_PERMILL_SYMBOLS, U_MULTIPLE_PAD_SPECIFIERS, U_PATTERN_SYNTAX_ERROR, U_ILLEGAL_PAD_POSITION, U_UNMATCHED_BRACES, U_UNSUPPORTED_PROPERTY, U_UNSUPPORTED_ATTRIBUTE, U_ARGUMENT_TYPE_MISMATCH, U_DUPLICATE_KEYWORD, U_UNDEFINED_KEYWORD, U_DEFAULT_KEYWORD_MISSING, U_DECIMAL_NUMBER_SYNTAX_ERROR, U_FORMAT_INEXACT_ERROR, U_FMT_PARSE_ERROR_LIMIT, U_BRK_INTERNAL_ERROR = 66048, U_BRK_ERROR_START = 66048, U_BRK_HEX_DIGITS_EXPECTED, U_BRK_SEMICOLON_EXPECTED, U_BRK_RULE_SYNTAX, U_BRK_UNCLOSED_SET, U_BRK_ASSIGN_ERROR, U_BRK_VARIABLE_REDFINITION, U_BRK_MISMATCHED_PAREN, U_BRK_NEW_LINE_IN_QUOTED_STRING, U_BRK_UNDEFINED_VARIABLE, U_BRK_INIT_ERROR, U_BRK_RULE_EMPTY_SET, U_BRK_UNRECOGNIZED_OPTION, U_BRK_MALFORMED_RULE_TAG, U_BRK_ERROR_LIMIT, U_REGEX_INTERNAL_ERROR = 66304, 
	U_REGEX_ERROR_START = 66304, U_REGEX_RULE_SYNTAX, U_REGEX_INVALID_STATE, U_REGEX_BAD_ESCAPE_SEQUENCE, U_REGEX_PROPERTY_SYNTAX, U_REGEX_UNIMPLEMENTED, U_REGEX_MISMATCHED_PAREN, U_REGEX_NUMBER_TOO_BIG, U_REGEX_BAD_INTERVAL, U_REGEX_MAX_LT_MIN, U_REGEX_INVALID_BACK_REF, U_REGEX_INVALID_FLAG, U_REGEX_LOOK_BEHIND_LIMIT, U_REGEX_SET_CONTAINS_STRING, U_REGEX_OCTAL_TOO_BIG, U_REGEX_MISSING_CLOSE_BRACKET, U_REGEX_INVALID_RANGE, U_REGEX_STACK_OVERFLOW, U_REGEX_TIME_OUT, U_REGEX_STOPPED_BY_CALLER, U_REGEX_ERROR_LIMIT, U_IDNA_PROHIBITED_ERROR = 66560, U_IDNA_ERROR_START = 66560, U_IDNA_UNASSIGNED_ERROR, U_IDNA_CHECK_BIDI_ERROR, U_IDNA_STD3_ASCII_RULES_ERROR, U_IDNA_ACE_PREFIX_ERROR, U_IDNA_VERIFICATION_ERROR, U_IDNA_LABEL_TOO_LONG_ERROR, U_IDNA_ZERO_LENGTH_LABEL_ERROR, 
	U_IDNA_DOMAIN_NAME_TOO_LONG_ERROR, U_IDNA_ERROR_LIMIT, U_STRINGPREP_PROHIBITED_ERROR = 66560, U_STRINGPREP_UNASSIGNED_ERROR, U_STRINGPREP_CHECK_BIDI_ERROR, U_PLUGIN_ERROR_START = 66816, U_PLUGIN_TOO_HIGH = 66816, U_PLUGIN_DIDNT_SET_LEVEL, U_PLUGIN_ERROR_LIMIT, U_ERROR_LIMIT = 66818 };

typedef System::Int8 UBool;

typedef double UDate;

typedef System::WideChar UChar;

typedef System::WideChar * PUChar;

typedef System::WideChar * *PPUChar;

typedef int UChar32;

typedef UErrorCode *PUErrorCode;

typedef System::DynamicArray<System::Byte> TByteArray;

typedef System::Word UInt16;

typedef int *PInt32;

typedef USet *PUSet;

enum DECLSPEC_DENUM UConverterType: char { UCNV_UNSUPPORTED_CONVERTER = -1, UCNV_SBCS, UCNV_DBCS, UCNV_MBCS, UCNV_LATIN_1, UCNV_UTF8, UCNV_UTF16_BigEndian, UCNV_UTF16_LittleEndian, UCNV_UTF32_BigEndian, UCNV_UTF32_LittleEndian, UCNV_EBCDIC_STATEFUL, UCNV_ISO_2022, UCNV_LMBCS_1, UCNV_LMBCS_2, UCNV_LMBCS_3, UCNV_LMBCS_4, UCNV_LMBCS_5, UCNV_LMBCS_6, UCNV_LMBCS_8, UCNV_LMBCS_11, UCNV_LMBCS_16, UCNV_LMBCS_17, UCNV_LMBCS_18, UCNV_LMBCS_19, UCNV_LMBCS_LAST = 22, UCNV_HZ, UCNV_SCSU, UCNV_ISCII, UCNV_US_ASCII, UCNV_UTF7, UCNV_BOCU1, UCNV_UTF16, UCNV_UTF32, UCNV_CESU8, UCNV_IMAP_MAILBOX, UCNV_COMPOUND_TEXT, UCNV_NUMBER_OF_SUPPORTED_CONVERTER_TYPES };

enum DECLSPEC_DENUM UConverterPlatform: char { UCNV_UNKNOWN = -1, UCNV_IBM };

enum DECLSPEC_DENUM UConverterUnicodeSet : unsigned char { UCNV_ROUNDTRIP_SET, UCNV_ROUNDTRIP_AND_FALLBACK_SET, UCNV_SET_COUNT };

enum DECLSPEC_DENUM UConverterCallbackReason : unsigned char { UCNV_CB_UNASSIGNED, UCNV_CB_ILLEGAL, UCNV_CB_IRREGULAR, UCNV_CB_RESET, UCNV_CB_CLOSE, UCNV_CB_CLONE };

typedef UConverter *PUConverter;

typedef UConverterToUnicodeArgs *PUConverterToUnicodeArgs;

struct DECLSPEC_DRECORD UConverterToUnicodeArgs
{
public:
	System::Word size;
	System::Int8 flush;
	UConverter *converter;
	char *source;
	char *sourceLimit;
	System::WideChar *target;
	System::WideChar *targetLimit;
	int *offsets;
};


typedef UConverterFromUnicodeArgs *PUConverterFromUnicodeArgs;

struct DECLSPEC_DRECORD UConverterFromUnicodeArgs
{
public:
	System::Word size;
	System::Int8 flush;
	UConverter *converter;
	char *source;
	char *sourceLimit;
	System::WideChar *target;
	System::WideChar *targetLimit;
	int *offsets;
};


typedef void __cdecl (*UConverterToUCallback)(const void * context, PUConverterToUnicodeArgs args, const char * codeUnits, int aLength, UConverterCallbackReason reason, UErrorCode &ErrorCode);

typedef void __cdecl (*UConverterFromUCallBack)(const void * context, PUConverterFromUnicodeArgs args, const System::WideChar * codeUnits, int aLength, int codePoint, UConverterCallbackReason reason, UErrorCode &ErrorCode);

enum DECLSPEC_DENUM UCollationResult: char { UCOL_LESS = -1, UCOL_EQUAL, UCOL_GREATER };

typedef UCollator *PUCollator;

enum DECLSPEC_DENUM UColAttributeValue: char { UCOL_DEFAULT = -1, UCOL_PRIMARY, UCOL_SECONDARY, UCOL_TERTIARY, UCOL_DEFAULT_STRENGTH = 2, UCOL_CE_STRENGTH_LIMIT, UCOL_QUATERNARY = 3, UCOL_IDENTICAL = 15, UCOL_STRENGTH_LIMIT, UCOL_OFF = 16, UCOL_ON, UCOL_SHIFTED = 20, UCOL_NON_IGNORABLE, UCOL_LOWER_FIRST = 24, UCOL_UPPER_FIRST, UCOL_ATTRIBUTE_VALUE_COUNT };

typedef UColAttributeValue UCollationStrength;

enum DECLSPEC_DENUM UColReorderCode: short { UCOL_REORDER_CODE_DEFAULT = -1, UCOL_REORDER_CODE_NONE = 103, UCOL_REORDER_CODE_OTHERS = 103, UCOL_REORDER_CODE_SPACE = 4096, UCOL_REORDER_CODE_FIRST = 4096, UCOL_REORDER_CODE_PUNCTUATION, UCOL_REORDER_CODE_SYMBOL, UCOL_REORDER_CODE_CURRENCY, UCOL_REORDER_CODE_DIGIT, UCOL_REORDER_CODE_LIMIT };

enum DECLSPEC_DENUM UColAttribute : unsigned char { UCOL_FRENCH_COLLATION, UCOL_ALTERNATE_HANDLING, UCOL_CASE_FIRST, UCOL_CASE_LEVEL, UCOL_NORMALIZATION_MODE, UCOL_DECOMPOSITION_MODE = 4, UCOL_STRENGTH, UCOL_HIRAGANA_QUATERNARY_MODE, UCOL_NUMERIC_COLLATION, UCOL_ATTRIBUTE_COUNT };

enum DECLSPEC_DENUM UColRuleOption : unsigned char { UCOL_TAILORING_ONLY, UCOL_FULL_RULES };

enum DECLSPEC_DENUM UColBoundMode : unsigned char { UCOL_BOUND_LOWER, UCOL_BOUND_UPPER, UCOL_BOUND_UPPER_LONG, UCOL_BOUND_VALUE_COUNT };

enum DECLSPEC_DENUM ULocDataLocaleType : unsigned char { ULOC_ACTUAL_LOCALE, ULOC_VALID_LOCALE, ULOC_REQUESTED_LOCALE, ULOC_DATA_LOCALE_TYPE_LIMIT };

enum DECLSPEC_DENUM UAcceptResult : unsigned char { ULOC_ACCEPT_FAILED, ULOC_ACCEPT_VALID, ULOC_ACCEPT_FALLBACK };

typedef ULocaleData *PULocaleData;

enum DECLSPEC_DENUM ULocaleDataExemplarSetType : unsigned char { ULOCDATA_ES_STANDARD, ULOCDATA_ES_AUXILIARY, ULOCDATA_ES_INDEX, ULOCDATA_ES_PUNCTUATION, ULOCDATA_ES_COUNT };

enum DECLSPEC_DENUM ULocaleDataDelimiterType : unsigned char { ULOCDATA_QUOTATION_START, ULOCDATA_QUOTATION_END, ULOCDATA_ALT_QUOTATION_START, ULOCDATA_ALT_QUOTATION_END, ULOCDATA_DELIMITER_COUNT };

enum DECLSPEC_DENUM UMeasurementSystem : unsigned char { UMS_SI, UMS_US, UMS_LIMIT };

typedef UFieldPosition *PUFieldPosition;

struct DECLSPEC_DRECORD UFieldPosition
{
public:
	int field;
	int beginIndex;
	int endIndex;
};


typedef UParseError *PUParseError;

struct DECLSPEC_DRECORD UParseError
{
public:
	int line;
	int offset;
	System::StaticArray<System::WideChar, 16> preContext;
	System::StaticArray<System::WideChar, 16> postContext;
};


typedef UNumberFormat *PUNumberFormat;

enum DECLSPEC_DENUM UNumberFormatStyle : unsigned char { UNUM_PATTERN_DECIMAL, UNUM_DECIMAL, UNUM_CURRENCY, UNUM_PERCENT, UNUM_SCIENTIFIC, UNUM_SPELLOUT, UNUM_ORDINAL, UNUM_DURATION, UNUM_NUMBERING_SYSTEM, UNUM_PATTERN_RULEBASED, UNUM_CURRENCY_ISO, UNUM_CURRENCY_PLURAL, UNUM_FORMAT_STYLE_COUNT, UNUM_DEFAULT = 1, UNUM_IGNORE = 0 };

enum DECLSPEC_DENUM UNumberFormatRoundingMode : unsigned char { UNUM_ROUND_CEILING, UNUM_ROUND_FLOOR, UNUM_ROUND_DOWN, UNUM_ROUND_UP, UNUM_ROUND_HALFEVEN, UNUM_FOUND_HALFEVEN = 4, UNUM_ROUND_HALFDOWN, UNUM_ROUND_HALFUP, UNUM_ROUND_UNNECESSARY };

enum DECLSPEC_DENUM UNumberFormatPadPosition : unsigned char { UNUM_PAD_BEFORE_PREFIX, UNUM_PAD_AFTER_PREFIX, UNUM_PAD_BEFORE_SUFFIX, UNUM_PAD_AFTER_SUFFIX };

enum DECLSPEC_DENUM UNumberCompactStyle : unsigned char { UNUM_SHORT, UNUM_LONG };

enum DECLSPEC_DENUM UCurrencySpacing : unsigned char { UNUM_CURRENCY_MATCH, UNUM_CURRENCY_SURROUNDING_MATCH, UNUM_CURRENCY_INSERT, UNUM_CURRENCY_SPACING_COUNT };

enum DECLSPEC_DENUM UNumberFormatFields : unsigned char { UNUM_INTEGER_FIELD, UNUM_FRACTION_FIELD, UNUM_DECIMAL_SEPARATOR_FIELD, UNUM_EXPONENT_SYMBOL_FIELD, UNUM_EXPONENT_SIGN_FIELD, UNUM_EXPONENT_FIELD, UNUM_GROUPING_SEPARATOR_FIELD, UNUM_CURRENCY_FIELD, UNUM_PERCENT_FIELD, UNUM_PERMILL_FIELD, UNUM_SIGN_FIELD, UNUM_FIELD_COUNT };

enum DECLSPEC_DENUM UNumberFormatAttribute : unsigned short { UNUM_PARSE_INT_ONLY, UNUM_GROUPING_USED, UNUM_DECIMAL_ALWAYS_SHOWN, UNUM_MAX_INTEGER_DIGITS, UNUM_MIN_INTEGER_DIGITS, UNUM_INTEGER_DIGITS, UNUM_MAX_FRACTION_DIGITS, UNUM_MIN_FRACTION_DIGITS, UNUM_FRACTION_DIGITS, UNUM_MULTIPLIER, UNUM_GROUPING_SIZE, UNUM_ROUNDING_MODE, UNUM_ROUNDING_INCREMENT, UNUM_FORMAT_WIDTH, UNUM_PADDING_POSITION, UNUM_SECONDARY_GROUPING_SIZE, UNUM_SIGNIFICANT_DIGITS_USED, UNUM_MIN_SIGNIFICANT_DIGITS, UNUM_MAX_SIGNIFICANT_DIGITS, UNUM_LENIENT_PARSE, UNUM_SCALE = 21, UNUM_NUMERIC_ATTRIBUTE_COUNT, UNUM_MAX_NONBOOLEAN_ATTRIBUTE = 4095, UNUM_FORMAT_FAIL_IF_MORE_THAN_MAX_DIGITS, UNUM_PARSE_NO_EXPONENT, UNUM_LIMIT_BOOLEAN_ATTRIBUTE };

enum DECLSPEC_DENUM UNumberFormatTextAttribute : unsigned char { UNUM_POSITIVE_PREFIX, UNUM_POSITIVE_SUFFIX, UNUM_NEGATIVE_PREFIX, UNUM_NEGATIVE_SUFFIX, UNUM_PADDING_CHARACTER, UNUM_CURRENCY_CODE, UNUM_DEFAULT_RULESET, UNUM_PUBLIC_RULESETS };

enum DECLSPEC_DENUM UNumberFormatSymbol : unsigned char { UNUM_DECIMAL_SEPARATOR_SYMBOL, UNUM_GROUPING_SEPARATOR_SYMBOL, UNUM_PATTERN_SEPARATOR_SYMBOL, UNUM_PERCENT_SYMBOL, UNUM_ZERO_DIGIT_SYMBOL, UNUM_DIGIT_SYMBOL, UNUM_MINUS_SIGN_SYMBOL, UNUM_PLUS_SIGN_SYMBOL, UNUM_CURRENCY_SYMBOL, UNUM_INTL_CURRENCY_SYMBOL, UNUM_MONETARY_SEPARATOR_SYMBOL, UNUM_EXPONENTIAL_SYMBOL, UNUM_PERMILL_SYMBOL, UNUM_PAD_ESCAPE_SYMBOL, UNUM_INFINITY_SYMBOL, UNUM_NAN_SYMBOL, UNUM_SIGNIFICANT_DIGIT_SYMBOL, UNUM_MONETARY_GROUPING_SEPARATOR_SYMBOL, UNUM_ONE_DIGIT_SYMBOL, UNUM_TWO_DIGIT_SYMBOL, UNUM_THREE_DIGIT_SYMBOL, UNUM_FOUR_DIGIT_SYMBOL, UNUM_FIVE_DIGIT_SYMBOL, UNUM_SIX_DIGIT_SYMBOL, UNUM_SEVEN_DIGIT_SYMBOL, UNUM_EIGHT_DIGIT_SYMBOL, UNUM_NINE_DIGIT_SYMBOL, UNUM_FORMAT_SYMBOL_COUNT };

typedef UDateFormat *PUDateFormat;

enum DECLSPEC_DENUM UDateFormatStyle: short { UDAT_FULL, UDAT_LONG, UDAT_MEDIUM, UDAT_SHORT, UDAT_DEFAULT = 2, UDAT_RELATIVE = 128, UDAT_FULL_RELATIVE = 128, UDAT_LONG_RELATIVE, UDAT_MEDIUM_RELATIVE, UDAT_SHORT_RELATIVE, UDAT_NONE = -1, UDAT_PATTERN = -2, UDAT_IGNORE = -2 };

enum DECLSPEC_DENUM UDateFormatField : unsigned char { UDAT_ERA_FIELD, UDAT_YEAR_FIELD, UDAT_MONTH_FIELD, UDAT_DATE_FIELD, UDAT_HOUR_OF_DAY1_FIELD, UDAT_HOUR_OF_DAY0_FIELD, UDAT_MINUTE_FIELD, UDAT_SECOND_FIELD, UDAT_FRACTIONAL_SECOND_FIELD, UDAT_DAY_OF_WEEK_FIELD, UDAT_DAY_OF_YEAR_FIELD, UDAT_DAY_OF_WEEK_IN_MONTH_FIELD, UDAT_WEEK_OF_YEAR_FIELD, UDAT_WEEK_OF_MONTH_FIELD, UDAT_AM_PM_FIELD, UDAT_HOUR1_FIELD, UDAT_HOUR0_FIELD, UDAT_TIMEZONE_FIELD, UDAT_YEAR_WOY_FIELD, UDAT_DOW_LOCAL_FIELD, UDAT_EXTENDED_YEAR_FIELD, UDAT_JULIAN_DAY_FIELD, UDAT_MILLISECONDS_IN_DAY_FIELD, UDAT_TIMEZONE_RFC_FIELD, UDAT_TIMEZONE_GENERIC_FIELD, UDAT_STANDALONE_DAY_FIELD, UDAT_STANDALONE_MONTH_FIELD, UDAT_QUARTER_FIELD, UDAT_STANDALONE_QUARTER_FIELD, UDAT_TIMEZONE_SPECIAL_FIELD, 
	UDAT_YEAR_NAME_FIELD, UDAT_TIMEZONE_LOCALIZED_GMT_OFFSET_FIELD, UDAT_TIMEZONE_ISO_FIELD, UDAT_TIMEZONE_ISO_LOCAL_FIELD, UDAT_FIELD_COUNT };

enum DECLSPEC_DENUM UDateFormatSymbolType : unsigned char { UDAT_ERAS, UDAT_MONTHS, UDAT_SHORT_MONTHS, UDAT_WEEKDAYS, UDAT_SHORT_WEEKDAYS, UDAT_AM_PMS, UDAT_LOCALIZED_CHARS, UDAT_ERA_NAMES, UDAT_NARROW_MONTHS, UDAT_NARROW_WEEKDAYS, UDAT_STANDALONE_MONTHS, UDAT_STANDALONE_SHORT_MONTHS, UDAT_STANDALONE_NARROW_MONTHS, UDAT_STANDALONE_WEEKDAYS, UDAT_STANDALONE_SHORT_WEEKDAYS, UDAT_STANDALONE_NARROW_WEEKDAYS, UDAT_QUARTERS, UDAT_SHORT_QUARTERS, UDAT_STANDALONE_QUARTERS, UDAT_STANDALONE_SHORT_QUARTERS, UDAT_SHORTER_WEEKDAYS, UDAT_STANDALONE_SHORTER_WEEKDAYS };

typedef UCalendar *PUCalendar;

enum DECLSPEC_DENUM UCalendarType : unsigned char { UCAL_TRADITIONAL, UCAL_DEFAULT = 0x0, UCAL_GREGORIAN };

enum DECLSPEC_DENUM UCalendarDateFields : unsigned char { UCAL_ERA, UCAL_YEAR, UCAL_MONTH, UCAL_WEEK_OF_YEAR, UCAL_WEEK_OF_MONTH, UCAL_DATE, UCAL_DAY_OF_YEAR, UCAL_DAY_OF_WEEK, UCAL_DAY_OF_WEEK_IN_MONTH, UCAL_AM_PM, UCAL_HOUR, UCAL_HOUR_OF_DAY, UCAL_MINUTE, UCAL_SECOND, UCAL_MILLISECOND, UCAL_ZONE_OFFSET, UCAL_DST_OFFSET, UCAL_YEAR_WOY, UCAL_DOW_LOCAL, UCAL_EXTENDED_YEAR, UCAL_JULIAN_DAY, UCAL_MILLISECONDS_IN_DAY, UCAL_IS_LEAP_MONTH, UCAL_FIELD_COUNT, UCAL_DAY_OF_MONTH = 5 };

enum DECLSPEC_DENUM UCalendarDaysOfWeek : unsigned char { UCAL_SUNDAY = 1, UCAL_MONDAY, UCAL_TUESDAY, UCAL_WEDNESDAY, UCAL_THURSDAY, UCAL_FRIDAY, UCAL_SATURDAY };

enum DECLSPEC_DENUM UCalendarMonths : unsigned char { UCAL_JANUARY, UCAL_FEBRUARY, UCAL_MARCH, UCAL_APRIL, UCAL_MAY, UCAL_JUNE, UCAL_JULY, UCAL_AUGUST, UCAL_SEPTEMBER, UCAL_OCTOBER, UCAL_NOVEMBER, UCAL_DECEMBER, UCAL_UNDECIMBER };

enum DECLSPEC_DENUM UCalendarAMPMs : unsigned char { UCAL_AM, UCAL_PM };

enum DECLSPEC_DENUM USystemTimeZoneType : unsigned char { UCAL_ZONE_TYPE_ANY, UCAL_ZONE_TYPE_CANONICAL, UCAL_ZONE_TYPE_CANONICAL_LOCATION };

enum DECLSPEC_DENUM UCalendarDisplayNameType : unsigned char { UCAL_STANDARD, UCAL_SHORT_STANDARD, UCAL_DST, UCAL_SHORT_DST };

enum DECLSPEC_DENUM UCalendarAttribute : unsigned char { UCAL_LENIENT, UCAL_FIRST_DAY_OF_WEEK, UCAL_MINIMAL_DAYS_IN_FIRST_WEEK, UCAL_REPEATED_WALL_TIME, UCAL_SKIPPED_WALL_TIME };

enum DECLSPEC_DENUM UCalendarWallTimeOption : unsigned char { UCAL_WALLTIME_LAST, UCAL_WALLTIME_FIRST, UCAL_WALLTIME_NEXT_VALID };

enum DECLSPEC_DENUM UCalendarLimitType : unsigned char { UCAL_MINIMUM, UCAL_MAXIMUM, UCAL_GREATEST_MINIMUM, UCAL_LEAST_MAXIMUM, UCAL_ACTUAL_MINIMUM, UCAL_ACTUAL_MAXIMUM };

enum DECLSPEC_DENUM UCalendarWeekdayType : unsigned char { UCAL_WEEKDAY, UCAL_WEEKEND, UCAL_WEEKEND_ONSET, UCAL_WEEKEND_CEASE };

enum DECLSPEC_DENUM UTimeZoneTransitionType : unsigned char { UCAL_TZ_TRANSITION_NEXT, UCAL_TZ_TRANSITION_NEXT_INCLUSIVE, UCAL_TZ_TRANSITION_PREVIOUS, UCAL_TZ_TRANSITION_PREVIOUS_INCLUSIVE };

typedef UEnumeration *PUEnumeration;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 UCNV_MAX_CONVERTER_NAME_LENGTH = System::Int8(0x3c);
static constexpr System::Word UCNV_MAX_FULL_FILE_NAME_LENGTH = System::Word(0x294);
static constexpr System::Int8 UCNV_SI = System::Int8(0xf);
static constexpr System::Int8 UCNV_SO = System::Int8(0xe);
extern DELPHI_PACKAGE System::WideChar UCNV_OPTION_SEP_CHAR;
extern DELPHI_PACKAGE System::UnicodeString UCNV_OPTION_SEP_STRING;
extern DELPHI_PACKAGE System::WideChar UCNV_VALUE_SEP_CHAR;
extern DELPHI_PACKAGE System::UnicodeString UCNV_VALUE_SEP_STRING;
#define UCNV_LOCALE_OPTION_STRING u",locale="
#define UCNV_VERSION_OPTION_STRING u",version="
#define UCNV_SWAP_LFNL_OPTION_STRING u",swaplfnl"
static constexpr System::Word U_CNV_SAFECLONE_BUFFERSIZE = System::Word(0x400);
static constexpr System::Int8 UCNV_PRV_ESCAPE_ICU = System::Int8(0x0);
static constexpr System::Word UCNV_PRV_ESCAPE_C = System::Word(0x43);
static constexpr System::Word UCNV_PRV_ESCAPE_XML_DEC = System::Word(0x44);
static constexpr System::Word UCNV_PRV_ESCAPE_XML_HEX = System::Word(0x58);
static constexpr System::Word UCNV_PRV_ESCAPE_JAVA = System::Word(0x4a);
static constexpr System::Word UCNV_PRV_ESCAPE_UNICODE = System::Word(0x55);
static constexpr System::Word UCNV_PRV_ESCAPE_CSS2 = System::Word(0x53);
static constexpr System::Word UCNV_PRV_STOP_ON_ILLEGAL = System::Word(0x69);
static constexpr System::Int8 USCRIPT_UNKNOWN = System::Int8(0x67);
static constexpr System::Int8 ULOC_LANG_CAPACITY = System::Int8(0xc);
static constexpr System::Int8 ULOC_COUNTRY_CAPACITY = System::Int8(0x4);
static constexpr System::Byte ULOC_FULLNAME_CAPACITY = System::Byte(0x9d);
static constexpr System::Int8 ULOC_SCRIPT_CAPACITY = System::Int8(0x6);
static constexpr System::Int8 ULOC_KEYWORDS_CAPACITY = System::Int8(0x32);
static constexpr System::Int8 ULOC_KEYWORD_AND_VALUES_CAPACITY = System::Int8(0x64);
static constexpr System::WideChar ULOC_KEYWORD_SEPARATOR = (System::WideChar)(0x40);
static constexpr System::Int8 ULOC_KEYWORD_SEPARATOR_UNICODE = System::Int8(0x40);
static constexpr System::WideChar ULOC_KEYWORD_ASSIGN = (System::WideChar)(0x3d);
static constexpr System::Int8 ULOC_KEYWORD_ASSIGN_UNICODE = System::Int8(0x3d);
static constexpr System::WideChar ULOC_KEYWORD_ITEM_SEPARATOR = (System::WideChar)(0x3b);
static constexpr System::Int8 ULOC_KEYWORD_ITEM_SEPARATOR_UNICODE = System::Int8(0x3b);
static constexpr System::Int8 U_PARSE_CONTEXT_LEN = System::Int8(0x10);
extern DELPHI_PACKAGE char * __cdecl (*u_errorName)(UErrorCode code);
extern DELPHI_PACKAGE int __cdecl (*u_strcmp)(const System::WideChar * s1, const System::WideChar * s2);
extern DELPHI_PACKAGE int __cdecl (*u_strToUpper)(System::WideChar * dest, int destCapaciy, const System::WideChar * src, int srcLength, const char * locale, UErrorCode &ErrorCode);
extern DELPHI_PACKAGE int __cdecl (*u_strToLower)(System::WideChar * dest, int destCapaciy, const System::WideChar * src, int srcLength, const char * locale, UErrorCode &ErrorCode);
extern DELPHI_PACKAGE PUConverter __cdecl (*ucnv_open)(char * converterName, UErrorCode &err);
extern DELPHI_PACKAGE void __cdecl (*ucnv_close)(PUConverter converter);
extern DELPHI_PACKAGE System::Int8 __cdecl (*ucnv_getMaxCharSize)(const PUConverter converter);
extern DELPHI_PACKAGE int __cdecl (*ucnv_getDisplayName)(const PUConverter converter, char * displayLocale, System::WideChar * displayName, int displayNameCapacity, UErrorCode &err);
extern DELPHI_PACKAGE char * __cdecl (*ucnv_getName)(const PUConverter converter, UErrorCode &err);
extern DELPHI_PACKAGE char * __cdecl (*ucnv_getStandardName)(char * name, char * standard, UErrorCode &err);
extern DELPHI_PACKAGE int __cdecl (*u_tolower)(int c);
extern DELPHI_PACKAGE int __cdecl (*u_toupper)(int c);
extern DELPHI_PACKAGE int __cdecl (*uloc_canonicalize)(const char * localeID, char * name, int nameCapacity, UErrorCode &err);
extern DELPHI_PACKAGE char * __cdecl (*uloc_getAvailable)(int n);
extern DELPHI_PACKAGE int __cdecl (*uloc_countAvailable)(void);
extern DELPHI_PACKAGE int __cdecl (*uloc_getBaseName)(const char * localeID, char * name, int nameCapacity, UErrorCode &err);
extern DELPHI_PACKAGE int __cdecl (*uloc_toLanguageTag)(const char * localeID, char * langtag, int langtagCapacity, System::Int8 strictCheck, UErrorCode &err);
extern DELPHI_PACKAGE PUCollator __cdecl (*ucol_open)(const char * loc, UErrorCode &status);
extern DELPHI_PACKAGE void __cdecl (*ucol_close)(PUCollator coll);
extern DELPHI_PACKAGE UCollationResult __cdecl (*ucol_strcoll)(const PUCollator coll, const System::WideChar * source, int sourceLength, const System::WideChar * target, int targetLength);
extern DELPHI_PACKAGE void __cdecl (*ucol_setAttribute)(const PUCollator coll, UColAttribute attr, UColAttributeValue value, UErrorCode &status);
extern DELPHI_PACKAGE PUDateFormat __cdecl (*udat_open)(UDateFormatStyle timeStyle, UDateFormatStyle dateStyle, const char * locale, const System::WideChar * tzID, int tzIDLenght, const System::WideChar * pattern, int patternLenght, UErrorCode &status);
extern DELPHI_PACKAGE void __cdecl (*udat_close)(PUDateFormat format);
extern DELPHI_PACKAGE int __cdecl (*udat_getSymbols)(const PUDateFormat fmt, UDateFormatSymbolType aType, int symbolIndex, System::WideChar * aResult, int aResultLen, UErrorCode &status);
extern DELPHI_PACKAGE int __fastcall (*udat_countSymbols)(const PUDateFormat fmt, UDateFormatSymbolType aType);
extern DELPHI_PACKAGE int __cdecl (*udat_toPatternRelativeDate)(const PUDateFormat fmt, System::WideChar * aResult, int aResultLen, UErrorCode &status);
extern DELPHI_PACKAGE int __cdecl (*udat_toPatternRelativeTime)(const PUDateFormat fmt, System::WideChar * aResult, int aResultLen, UErrorCode &status);
extern DELPHI_PACKAGE PUNumberFormat __cdecl (*unum_open)(UNumberFormatStyle style, const System::WideChar * pattern, int patternLength, const char * locale, PUParseError parseErr, UErrorCode &status);
extern DELPHI_PACKAGE void __cdecl (*unum_close)(PUNumberFormat fmt);
extern DELPHI_PACKAGE int __cdecl (*unum_getAttribute)(const PUNumberFormat fmt, UNumberFormatAttribute attr);
extern DELPHI_PACKAGE int __cdecl (*unum_getTextAttribute)(const PUNumberFormat fmt, UNumberFormatTextAttribute tag, System::WideChar * aResult, int aResultLength, UErrorCode &status);
extern DELPHI_PACKAGE int __cdecl (*unum_getSymbol)(const PUNumberFormat fmt, UNumberFormatSymbol symbol, System::WideChar * buffer, int bufferLength, UErrorCode &status);
extern DELPHI_PACKAGE double __cdecl (*ucal_getNow)(void);
extern DELPHI_PACKAGE PUCalendar __cdecl (*ucal_open)(const System::WideChar * zoneID, int len, const char * locale, UCalendarType aType, UErrorCode &status);
extern DELPHI_PACKAGE void __cdecl (*ucal_close)(PUCalendar car);
extern DELPHI_PACKAGE double __cdecl (*ucal_getMillis)(const PUCalendar cal, UErrorCode &status);
extern DELPHI_PACKAGE double __cdecl (*ucal_setMillis)(PUCalendar cal, double dateTime, UErrorCode &status);
extern DELPHI_PACKAGE void __cdecl (*ucal_setDateTime)(PUCalendar cal, int year, int month, int date, int hour, int minute, int second, UErrorCode &status);
extern DELPHI_PACKAGE int __cdecl (*ucal_get)(const PUCalendar cal, UCalendarDateFields field, UErrorCode &status);
extern DELPHI_PACKAGE PUCollator __fastcall GetCollator(const char * ALocaleStr, System::Sysutils::TCompareOptions AOptions);
extern DELPHI_PACKAGE void __fastcall InitHIC(void);
extern DELPHI_PACKAGE void __fastcall ClearCollatorCache(void);
}	/* namespace Icu */
}	/* namespace Internal */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Internal_IcuHPP
