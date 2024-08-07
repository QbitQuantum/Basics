﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDateTimeStamp.pas' rev: 34.00 (Android)

#ifndef IddatetimestampHPP
#define IddatetimestampHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddatetimestamp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDateTimeStamp;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 13> Iddatetimestamp__1;

typedef System::StaticArray<System::UnicodeString, 13> Iddatetimestamp__2;

typedef System::StaticArray<System::UnicodeString, 8> Iddatetimestamp__3;

typedef System::StaticArray<System::UnicodeString, 8> Iddatetimestamp__4;

enum DECLSPEC_DENUM TDays : unsigned char { TDaySun, TDayMon, TDayTue, TDayWed, TDayThu, TDayFri, TDaySat };

enum DECLSPEC_DENUM TMonths : unsigned char { TMthJan, TMthFeb, TMthMar, TMthApr, TMthMay, TMthJun, TMthJul, TMthAug, TMthSep, TMthOct, TMthNov, TMthDec };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDateTimeStamp : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	int FDay;
	bool FIsLeapYear;
	int FMillisecond;
	int FSecond;
	int FTimeZone;
	int FYear;
	void __fastcall CheckLeapYear();
	void __fastcall SetDateFromISO8601(System::UnicodeString AString);
	void __fastcall SetTimeFromISO8601(System::UnicodeString AString);
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall AddDays(unsigned ANumber);
	void __fastcall AddHours(unsigned ANumber);
	void __fastcall AddMilliseconds(unsigned ANumber);
	void __fastcall AddMinutes(unsigned ANumber);
	void __fastcall AddMonths(unsigned ANumber);
	void __fastcall AddSeconds(unsigned ANumber);
	void __fastcall AddTDateTime(System::TDateTime ADateTime);
	void __fastcall AddTIdDateTimeStamp(TIdDateTimeStamp* AIdDateTime);
	void __fastcall AddTTimeStamp(TIdDateTimeStamp* ATimeStamp);
	void __fastcall AddWeeks(unsigned ANumber);
	void __fastcall AddYears(unsigned ANumber);
	System::UnicodeString __fastcall GetAsISO8601Calendar();
	System::UnicodeString __fastcall GetAsISO8601Ordinal();
	System::UnicodeString __fastcall GetAsISO8601Week();
	System::UnicodeString __fastcall GetAsRFC822();
	System::TDateTime __fastcall GetAsTDateTime();
	TIdDateTimeStamp* __fastcall GetAsTTimeStamp();
	System::UnicodeString __fastcall GetAsTimeOfDay();
	int __fastcall GetBeatOfDay();
	int __fastcall GetDaysInYear();
	int __fastcall GetDayOfMonth();
	int __fastcall GetDayOfWeek();
	System::UnicodeString __fastcall GetDayOfWeekName();
	System::UnicodeString __fastcall GetDayOfWeekShortName();
	int __fastcall GetHourOf12Day();
	int __fastcall GetHourOf24Day();
	bool __fastcall GetIsMorning();
	int __fastcall GetMinuteOfDay();
	int __fastcall GetMinuteOfHour();
	int __fastcall GetMonthOfYear();
	System::UnicodeString __fastcall GetMonthName();
	System::UnicodeString __fastcall GetMonthShortName();
	int __fastcall GetSecondsInYear();
	int __fastcall GetSecondOfMinute();
	System::UnicodeString __fastcall GetTimeZoneAsString();
	int __fastcall GetTimeZoneHour();
	int __fastcall GetTimeZoneMinutes();
	int __fastcall GetWeekOfYear();
	void __fastcall SetFromDOSDateTime(System::Word ADate, System::Word ATime);
	void __fastcall SetFromISO8601(System::UnicodeString AString);
	void __fastcall SetFromRFC822(System::UnicodeString AString);
	void __fastcall SetFromTDateTime(System::TDateTime ADateTime);
	void __fastcall SetFromTTimeStamp(TIdDateTimeStamp* ATimeStamp);
	void __fastcall SetDay(int ANumber);
	void __fastcall SetMillisecond(int ANumber);
	void __fastcall SetSecond(int ANumber);
	void __fastcall SetTimeZone(const int Value);
	void __fastcall SetYear(int ANumber);
	void __fastcall SubtractDays(unsigned ANumber);
	void __fastcall SubtractHours(unsigned ANumber);
	void __fastcall SubtractMilliseconds(unsigned ANumber);
	void __fastcall SubtractMinutes(unsigned ANumber);
	void __fastcall SubtractMonths(unsigned ANumber);
	void __fastcall SubtractSeconds(unsigned ANumber);
	void __fastcall SubtractTDateTime(System::TDateTime ADateTime);
	void __fastcall SubtractTIdDateTimeStamp(TIdDateTimeStamp* AIdDateTime);
	void __fastcall SubtractTTimeStamp(TIdDateTimeStamp* ATimeStamp);
	void __fastcall SubtractWeeks(unsigned ANumber);
	void __fastcall SubtractYears(unsigned ANumber);
	void __fastcall Zero();
	void __fastcall ZeroDate();
	void __fastcall ZeroTime();
	__property System::UnicodeString AsISO8601Calendar = {read=GetAsISO8601Calendar};
	__property System::UnicodeString AsISO8601Ordinal = {read=GetAsISO8601Ordinal};
	__property System::UnicodeString AsISO8601Week = {read=GetAsISO8601Week};
	__property System::UnicodeString AsRFC822 = {read=GetAsRFC822};
	__property System::TDateTime AsTDateTime = {read=GetAsTDateTime};
	__property TIdDateTimeStamp* AsTTimeStamp = {read=GetAsTTimeStamp};
	__property System::UnicodeString AsTimeOfDay = {read=GetAsTimeOfDay};
	__property int BeatOfDay = {read=GetBeatOfDay, nodefault};
	__property int Day = {read=FDay, write=SetDay, nodefault};
	__property int DaysInYear = {read=GetDaysInYear, nodefault};
	__property int DayOfMonth = {read=GetDayOfMonth, nodefault};
	__property int DayOfWeek = {read=GetDayOfWeek, nodefault};
	__property System::UnicodeString DayOfWeekName = {read=GetDayOfWeekName};
	__property System::UnicodeString DayOfWeekShortName = {read=GetDayOfWeekShortName};
	__property int HourOf12Day = {read=GetHourOf12Day, nodefault};
	__property int HourOf24Day = {read=GetHourOf24Day, nodefault};
	__property bool IsLeapYear = {read=FIsLeapYear, nodefault};
	__property bool IsMorning = {read=GetIsMorning, nodefault};
	__property int Millisecond = {read=FMillisecond, write=SetMillisecond, nodefault};
	__property int MinuteOfDay = {read=GetMinuteOfDay, nodefault};
	__property int MinuteOfHour = {read=GetMinuteOfHour, nodefault};
	__property int MonthOfYear = {read=GetMonthOfYear, nodefault};
	__property System::UnicodeString MonthName = {read=GetMonthName};
	__property System::UnicodeString MonthShortName = {read=GetMonthShortName};
	__property int Second = {read=FSecond, write=SetSecond, nodefault};
	__property int SecondsInYear = {read=GetSecondsInYear, nodefault};
	__property int SecondOfMinute = {read=GetSecondOfMinute, nodefault};
	__property int TimeZone = {read=FTimeZone, write=SetTimeZone, nodefault};
	__property int TimeZoneHour = {read=GetTimeZoneHour, nodefault};
	__property int TimeZoneMinutes = {read=GetTimeZoneMinutes, nodefault};
	__property System::UnicodeString TimeZoneAsString = {read=GetTimeZoneAsString};
	__property int Year = {read=FYear, write=SetYear, nodefault};
	__property int WeekOfYear = {read=GetWeekOfYear, nodefault};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDateTimeStamp(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDateTimeStamp()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDateTimeStamp() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word IdMilliSecondsInSecond = System::Word(0x3e8);
static constexpr System::Int8 IdSecondsInMinute = System::Int8(0x3c);
static constexpr System::Int8 IdMinutesInHour = System::Int8(0x3c);
static constexpr System::Int8 IdHoursInDay = System::Int8(0x18);
static constexpr System::Int8 IdDaysInWeek = System::Int8(0x7);
static constexpr System::Word IdDaysInYear = System::Word(0x16d);
static constexpr System::Word IdDaysInLeapYear = System::Word(0x16e);
static constexpr System::Int8 IdYearsInShortLeapYearCycle = System::Int8(0x4);
static constexpr System::Word IdDaysInShortLeapYearCycle = System::Word(0x5b5);
static constexpr System::Word IdDaysInShortNonLeapYearCycle = System::Word(0x5b4);
static constexpr System::Word IdDaysInFourYears = System::Word(0x5b5);
static constexpr System::Int8 IdYearsInCentury = System::Int8(0x64);
static constexpr System::Word IdDaysInCentury = System::Word(0x8eac);
static constexpr System::Word IdDaysInLeapCentury = System::Word(0x8ead);
static constexpr System::Word IdYearsInLeapYearCycle = System::Word(0x190);
static constexpr int IdDaysInLeapYearCycle = int(0x23ab1);
static constexpr System::Int8 IdMonthsInYear = System::Int8(0xc);
static constexpr System::Word IdBeatsInDay = System::Word(0x3e8);
static constexpr System::Int8 IdHoursInHalfDay = System::Int8(0xc);
static constexpr System::Word IdSecondsInHour = System::Word(0xe10);
static constexpr int IdSecondsInDay = int(0x15180);
static constexpr System::Word IdSecondsInHalfDay = System::Word(0xa8c0);
static constexpr int IdSecondsInWeek = int(0x93a80);
static constexpr int IdSecondsInYear = int(0x1e13380);
static constexpr int IdSecondsInLeapYear = int(0x1e28500);
static constexpr System::Word IdMillisecondsInMinute = System::Word(0xea60);
static constexpr int IdMillisecondsInHour = int(0x36ee80);
static constexpr int IdMillisecondsInDay = int(0x5265c00);
static constexpr int IdMillisecondsInWeek = int(0x240c8400);
#define SShortMonthNameJan u"Jan"
#define SShortMonthNameFeb u"Feb"
#define SShortMonthNameMar u"Mar"
#define SShortMonthNameApr u"Apr"
#define SShortMonthNameMay u"May"
#define SShortMonthNameJun u"Jun"
#define SShortMonthNameJul u"Jul"
#define SShortMonthNameAug u"Aug"
#define SShortMonthNameSep u"Sep"
#define SShortMonthNameOct u"Oct"
#define SShortMonthNameNov u"Nov"
#define SShortMonthNameDec u"Dec"
#define SLongMonthNameJan u"January"
#define SLongMonthNameFeb u"February"
#define SLongMonthNameMar u"March"
#define SLongMonthNameApr u"April"
#define SLongMonthNameMay u"May"
#define SLongMonthNameJun u"June"
#define SLongMonthNameJul u"July"
#define SLongMonthNameAug u"August"
#define SLongMonthNameSep u"September"
#define SLongMonthNameOct u"October"
#define SLongMonthNameNov u"November"
#define SLongMonthNameDec u"December"
#define SShortDayNameSun u"Sun"
#define SShortDayNameMon u"Mon"
#define SShortDayNameTue u"Tue"
#define SShortDayNameWed u"Wed"
#define SShortDayNameThu u"Thu"
#define SShortDayNameFri u"Fri"
#define SShortDayNameSat u"Sat"
#define SLongDayNameSun u"Sunday"
#define SLongDayNameMon u"Monday"
#define SLongDayNameTue u"Tuesday"
#define SLongDayNameWed u"Wednesday"
#define SLongDayNameThu u"Thursday"
#define SLongDayNameFri u"Friday"
#define SLongDayNameSat u"Saturday"
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 12> IdDaysInMonth;
extern DELPHI_PACKAGE Iddatetimestamp__1 IdMonthNames;
extern DELPHI_PACKAGE Iddatetimestamp__2 IdMonthShortNames;
extern DELPHI_PACKAGE Iddatetimestamp__3 IdDayNames;
extern DELPHI_PACKAGE Iddatetimestamp__4 IdDayShortNames;
static constexpr System::Int8 TZ_NZDT = System::Int8(0xd);
static constexpr System::Int8 TZ_IDLE = System::Int8(0xc);
static constexpr System::Int8 TZ_NZST = System::Int8(0xc);
static constexpr System::Int8 TZ_NZT = System::Int8(0xc);
static constexpr System::Int8 TZ_EADT = System::Int8(0xb);
static constexpr System::Int8 TZ_GST = System::Int8(0xa);
static constexpr System::Int8 TZ_JST = System::Int8(0x9);
static constexpr System::Int8 TZ_CCT = System::Int8(0x8);
static constexpr System::Int8 TZ_WADT = System::Int8(0x8);
static constexpr System::Int8 TZ_WAST = System::Int8(0x7);
static constexpr System::Int8 TZ_ZP6 = System::Int8(0x6);
static constexpr System::Int8 TZ_ZP5 = System::Int8(0x5);
static constexpr System::Int8 TZ_ZP4 = System::Int8(0x4);
static constexpr System::Int8 TZ_BT = System::Int8(0x3);
static constexpr System::Int8 TZ_EET = System::Int8(0x2);
static constexpr System::Int8 TZ_MEST = System::Int8(0x2);
static constexpr System::Int8 TZ_MESZ = System::Int8(0x2);
static constexpr System::Int8 TZ_SST = System::Int8(0x2);
static constexpr System::Int8 TZ_FST = System::Int8(0x2);
static constexpr System::Int8 TZ_CET = System::Int8(0x1);
static constexpr System::Int8 TZ_FWT = System::Int8(0x1);
static constexpr System::Int8 TZ_MET = System::Int8(0x1);
static constexpr System::Int8 TZ_MEWT = System::Int8(0x1);
static constexpr System::Int8 TZ_SWT = System::Int8(0x1);
static constexpr System::Int8 TZ_GMT = System::Int8(0x0);
static constexpr System::Int8 TZ_UT = System::Int8(0x0);
static constexpr System::Int8 TZ_UTC = System::Int8(0x0);
static constexpr System::Int8 TZ_WET = System::Int8(0x0);
static constexpr System::Int8 TZ_WAT = System::Int8(-1);
static constexpr System::Int8 TZ_BST = System::Int8(-1);
static constexpr System::Int8 TZ_AT = System::Int8(-2);
static constexpr System::Int8 TZ_ADT = System::Int8(-3);
static constexpr System::Int8 TZ_AST = System::Int8(-4);
static constexpr System::Int8 TZ_EDT = System::Int8(-4);
static constexpr System::Int8 TZ_EST = System::Int8(-5);
static constexpr System::Int8 TZ_CDT = System::Int8(-5);
static constexpr System::Int8 TZ_CST = System::Int8(-6);
static constexpr System::Int8 TZ_MDT = System::Int8(-6);
static constexpr System::Int8 TZ_MST = System::Int8(-7);
static constexpr System::Int8 TZ_PDT = System::Int8(-7);
static constexpr System::Int8 TZ_PST = System::Int8(-8);
static constexpr System::Int8 TZ_YDT = System::Int8(-8);
static constexpr System::Int8 TZ_YST = System::Int8(-9);
static constexpr System::Int8 TZ_HDT = System::Int8(-9);
static constexpr System::Int8 TZ_AHST = System::Int8(-10);
static constexpr System::Int8 TZ_CAT = System::Int8(-10);
static constexpr System::Int8 TZ_HST = System::Int8(-10);
static constexpr System::Int8 TZ_EAST = System::Int8(-10);
static constexpr System::Int8 TZ_NT = System::Int8(-11);
static constexpr System::Int8 TZ_IDLW = System::Int8(-12);
static constexpr System::Int8 TZM_A = System::Int8(-1);
static constexpr System::Int8 TZM_Alpha = System::Int8(-1);
static constexpr System::Int8 TZM_B = System::Int8(-2);
static constexpr System::Int8 TZM_Bravo = System::Int8(-2);
static constexpr System::Int8 TZM_C = System::Int8(-3);
static constexpr System::Int8 TZM_Charlie = System::Int8(-3);
static constexpr System::Int8 TZM_D = System::Int8(-4);
static constexpr System::Int8 TZM_Delta = System::Int8(-4);
static constexpr System::Int8 TZM_E = System::Int8(-5);
static constexpr System::Int8 TZM_Echo = System::Int8(-5);
static constexpr System::Int8 TZM_F = System::Int8(-6);
static constexpr System::Int8 TZM_Foxtrot = System::Int8(-6);
static constexpr System::Int8 TZM_G = System::Int8(-7);
static constexpr System::Int8 TZM_Golf = System::Int8(-7);
static constexpr System::Int8 TZM_H = System::Int8(-8);
static constexpr System::Int8 TZM_Hotel = System::Int8(-8);
static constexpr System::Int8 TZM_J = System::Int8(-9);
static constexpr System::Int8 TZM_Juliet = System::Int8(-9);
static constexpr System::Int8 TZM_K = System::Int8(-10);
static constexpr System::Int8 TZM_Kilo = System::Int8(-10);
static constexpr System::Int8 TZM_L = System::Int8(-11);
static constexpr System::Int8 TZM_Lima = System::Int8(-11);
static constexpr System::Int8 TZM_M = System::Int8(-12);
static constexpr System::Int8 TZM_Mike = System::Int8(-12);
static constexpr System::Int8 TZM_N = System::Int8(0x1);
static constexpr System::Int8 TZM_November = System::Int8(0x1);
static constexpr System::Int8 TZM_O = System::Int8(0x2);
static constexpr System::Int8 TZM_Oscar = System::Int8(0x2);
static constexpr System::Int8 TZM_P = System::Int8(0x3);
static constexpr System::Int8 TZM_Papa = System::Int8(0x3);
static constexpr System::Int8 TZM_Q = System::Int8(0x4);
static constexpr System::Int8 TZM_Quebec = System::Int8(0x4);
static constexpr System::Int8 TZM_R = System::Int8(0x5);
static constexpr System::Int8 TZM_Romeo = System::Int8(0x5);
static constexpr System::Int8 TZM_S = System::Int8(0x6);
static constexpr System::Int8 TZM_Sierra = System::Int8(0x6);
static constexpr System::Int8 TZM_T = System::Int8(0x7);
static constexpr System::Int8 TZM_Tango = System::Int8(0x7);
static constexpr System::Int8 TZM_U = System::Int8(0x8);
static constexpr System::Int8 TZM_Uniform = System::Int8(0x8);
static constexpr System::Int8 TZM_V = System::Int8(0x9);
static constexpr System::Int8 TZM_Victor = System::Int8(0x9);
static constexpr System::Int8 TZM_W = System::Int8(0xa);
static constexpr System::Int8 TZM_Whiskey = System::Int8(0xa);
static constexpr System::Int8 TZM_X = System::Int8(-11);
static constexpr System::Int8 TZM_XRay = System::Int8(-11);
static constexpr System::Int8 TZM_Y = System::Int8(0xc);
static constexpr System::Int8 TZM_Yankee = System::Int8(0xc);
static constexpr System::Int8 TZM_Z = System::Int8(0x0);
static constexpr System::Int8 TZM_Zulu = System::Int8(0x0);
}	/* namespace Iddatetimestamp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDATETIMESTAMP)
using namespace Iddatetimestamp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddatetimestampHPP
