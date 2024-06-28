// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.DateUtils.pas' rev: 34.00 (Windows)

#ifndef System_DateutilsHPP
#define System_DateutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.TimeSpan.hpp>

//-- user supplied -----------------------------------------------------------
namespace System
{
namespace Dateutils
{
extern const System::Extended OneHour /*= 4.166667E-02*/;
extern const System::Extended OneMinute /*= 6.944444E-04*/;
extern const System::Extended OneSecond /*= 1.157407E-05*/;
extern const System::Extended OneMillisecond /*= 1.157407E-08*/;
extern const System::Extended EpochAsJulianDate /*= 2.415018E+06*/;
}	/* namespace Dateutils */
}	/* namespace System */

namespace System
{
namespace Dateutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ELocalTimeInvalid;
class DELPHICLASS EDateTimeException;
class DELPHICLASS TTimeZone;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ELocalTimeInvalid : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELocalTimeInvalid(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELocalTimeInvalid(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELocalTimeInvalid(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELocalTimeInvalid(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalTimeInvalid(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalTimeInvalid(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELocalTimeInvalid(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELocalTimeInvalid(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalTimeInvalid(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalTimeInvalid(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalTimeInvalid(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalTimeInvalid(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELocalTimeInvalid() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EDateTimeException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDateTimeException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDateTimeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDateTimeException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDateTimeException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDateTimeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDateTimeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDateTimeException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDateTimeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDateTimeException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDateTimeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDateTimeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDateTimeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDateTimeException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TLocalTimeType : unsigned char { lttStandard, lttDaylight, lttAmbiguous, lttInvalid };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTimeZone : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TTimeZone* FLocal;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
private:
	System::UnicodeString __fastcall GetAbbreviationForNow();
	System::UnicodeString __fastcall GetDisplayNameForNow();
	__int64 __fastcall GetUtcOffsetInSeconds(const System::TDateTime ADateTime, const bool ForceDaylight);
	System::Timespan::TTimeSpan __fastcall GetCurrentUtcOffset();
	
protected:
	virtual void __fastcall DoGetOffsetsAndType(const System::TDateTime ADateTime, /* out */ __int64 &AOffset, /* out */ __int64 &ADstSave, /* out */ TLocalTimeType &AType) = 0 ;
	virtual System::UnicodeString __fastcall DoGetDisplayName(const System::TDateTime ADateTime, const bool ForceDaylight) = 0 ;
	virtual System::UnicodeString __fastcall DoGetID() = 0 ;
	
public:
	System::Timespan::TTimeSpan __fastcall GetUtcOffset(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	System::TDateTime __fastcall ToUniversalTime(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	System::TDateTime __fastcall ToLocalTime(const System::TDateTime ADateTime);
	System::UnicodeString __fastcall GetDisplayName(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	System::UnicodeString __fastcall GetAbbreviation(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	TLocalTimeType __fastcall GetLocalTimeType(const System::TDateTime ADateTime);
	bool __fastcall HasDST(const System::TDateTime AYear)/* overload */;
	bool __fastcall HasDST()/* overload */;
	bool __fastcall IsStandardTime(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	bool __fastcall IsInvalidTime(const System::TDateTime ADateTime);
	bool __fastcall IsAmbiguousTime(const System::TDateTime ADateTime);
	bool __fastcall IsDaylightTime(const System::TDateTime ADateTime, const bool ForceDaylight = false);
	__property System::UnicodeString ID = {read=DoGetID};
	__property System::UnicodeString DisplayName = {read=GetDisplayNameForNow};
	__property System::UnicodeString Abbreviation = {read=GetAbbreviationForNow};
	__property System::Timespan::TTimeSpan UtcOffset = {read=GetCurrentUtcOffset};
	/* static */ __property TTimeZone* Local = {read=FLocal};
public:
	/* TObject.Create */ inline __fastcall TTimeZone() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTimeZone() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 DaysPerWeek = System::Int8(0x7);
static const System::Int8 WeeksPerFortnight = System::Int8(0x2);
static const System::Int8 MonthsPerYear = System::Int8(0xc);
static const System::Int8 YearsPerDecade = System::Int8(0xa);
static const System::Int8 YearsPerCentury = System::Int8(0x64);
static const System::Word YearsPerMillennium = System::Word(0x3e8);
static const System::Int8 DayMonday = System::Int8(0x1);
static const System::Int8 DayTuesday = System::Int8(0x2);
static const System::Int8 DayWednesday = System::Int8(0x3);
static const System::Int8 DayThursday = System::Int8(0x4);
static const System::Int8 DayFriday = System::Int8(0x5);
static const System::Int8 DaySaturday = System::Int8(0x6);
static const System::Int8 DaySunday = System::Int8(0x7);
static const System::Int8 MonthJanuary = System::Int8(0x1);
static const System::Int8 MonthFebruary = System::Int8(0x2);
static const System::Int8 MonthMarch = System::Int8(0x3);
static const System::Int8 MonthApril = System::Int8(0x4);
static const System::Int8 MonthMay = System::Int8(0x5);
static const System::Int8 MonthJune = System::Int8(0x6);
static const System::Int8 MonthJuly = System::Int8(0x7);
static const System::Int8 MonthAugust = System::Int8(0x8);
static const System::Int8 MonthSeptember = System::Int8(0x9);
static const System::Int8 MonthOctober = System::Int8(0xa);
static const System::Int8 MonthNovember = System::Int8(0xb);
static const System::Int8 MonthDecember = System::Int8(0xc);
static const __int64 EpochAsUnixDate = -0x0000000083ad2180LL;
extern DELPHI_PACKAGE System::StaticArray<System::Word, 2> DaysPerYear;
static const System::Word RecodeLeaveFieldAsIs = System::Word(0xffff);
extern DELPHI_PACKAGE double ApproxDaysPerMonth;
extern DELPHI_PACKAGE double ApproxDaysPerYear;
extern DELPHI_PACKAGE System::TDateTime __fastcall DateOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall TimeOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall IsInLeapYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall IsPM(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall IsAM(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall IsValidDate(const System::Word AYear, const System::Word AMonth, const System::Word ADay);
extern DELPHI_PACKAGE bool __fastcall IsValidTime(const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond);
extern DELPHI_PACKAGE bool __fastcall IsValidDateTime(const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond);
extern DELPHI_PACKAGE bool __fastcall IsValidDateMonthWeek(const System::Word AYear, const System::Word AMonth, const System::Word AWeekOfMonth, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE bool __fastcall IsValidDateDay(const System::Word AYear, const System::Word ADayOfYear);
extern DELPHI_PACKAGE bool __fastcall IsValidDateWeek(const System::Word AYear, const System::Word AWeekOfYear, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE System::Word __fastcall DaysInYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall DaysInAYear(const System::Word AYear);
extern DELPHI_PACKAGE System::Word __fastcall DaysInMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall DaysInAMonth(const System::Word AYear, const System::Word AMonth);
extern DELPHI_PACKAGE System::Word __fastcall WeeksInYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall WeeksInAYear(const System::Word AYear);
extern DELPHI_PACKAGE System::TDateTime __fastcall Today(void);
extern DELPHI_PACKAGE System::TDateTime __fastcall Yesterday(void);
extern DELPHI_PACKAGE System::TDateTime __fastcall Tomorrow(void);
extern DELPHI_PACKAGE bool __fastcall IsToday(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall IsSameDay(const System::TDateTime AValue, const System::TDateTime ABasis);
extern DELPHI_PACKAGE System::Word __fastcall YearOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MonthOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall WeekOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall DayOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall HourOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MinuteOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall SecondOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MilliSecondOf(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfAYear(const System::Word AYear);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfAYear(const System::Word AYear);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfAMonth(const System::Word AYear, const System::Word AMonth);
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfAMonth(const System::Word AYear, const System::Word AMonth);
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfAWeek(const System::Word AYear, const System::Word AWeekOfYear, const System::Word ADayOfWeek = (System::Word)(0x1));
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfAWeek(const System::Word AYear, const System::Word AWeekOfYear, const System::Word ADayOfWeek = (System::Word)(0x7));
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfADay(const System::Word AYear, const System::Word ADayOfYear)/* overload */;
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfADay(const System::Word AYear, const System::Word ADayOfYear)/* overload */;
extern DELPHI_PACKAGE System::TDateTime __fastcall StartOfADay(const System::Word AYear, const System::Word AMonth, const System::Word ADay)/* overload */;
extern DELPHI_PACKAGE System::TDateTime __fastcall EndOfADay(const System::Word AYear, const System::Word AMonth, const System::Word ADay)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall MonthOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall WeekOfTheYear(const System::TDateTime AValue)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall WeekOfTheYear(const System::TDateTime AValue, System::Word &AYear)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall DayOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall HourOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MinuteOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall SecondOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE __int64 __fastcall MilliSecondOfTheYear(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall WeekOfTheMonth(const System::TDateTime AValue)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall WeekOfTheMonth(const System::TDateTime AValue, System::Word &AYear, System::Word &AMonth)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall DayOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall HourOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MinuteOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall SecondOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MilliSecondOfTheMonth(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall DayOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall HourOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MinuteOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall SecondOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MilliSecondOfTheWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall HourOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MinuteOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall SecondOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MilliSecondOfTheDay(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MinuteOfTheHour(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall SecondOfTheHour(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MilliSecondOfTheHour(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall SecondOfTheMinute(const System::TDateTime AValue);
extern DELPHI_PACKAGE unsigned __fastcall MilliSecondOfTheMinute(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::Word __fastcall MilliSecondOfTheSecond(const System::TDateTime AValue);
extern DELPHI_PACKAGE bool __fastcall WithinPastYears(const System::TDateTime ANow, const System::TDateTime AThen, const int AYears);
extern DELPHI_PACKAGE bool __fastcall WithinPastMonths(const System::TDateTime ANow, const System::TDateTime AThen, const int AMonths);
extern DELPHI_PACKAGE bool __fastcall WithinPastWeeks(const System::TDateTime ANow, const System::TDateTime AThen, const int AWeeks);
extern DELPHI_PACKAGE bool __fastcall WithinPastDays(const System::TDateTime ANow, const System::TDateTime AThen, const int ADays);
extern DELPHI_PACKAGE bool __fastcall WithinPastHours(const System::TDateTime ANow, const System::TDateTime AThen, const __int64 AHours);
extern DELPHI_PACKAGE bool __fastcall WithinPastMinutes(const System::TDateTime ANow, const System::TDateTime AThen, const __int64 AMinutes);
extern DELPHI_PACKAGE bool __fastcall WithinPastSeconds(const System::TDateTime ANow, const System::TDateTime AThen, const __int64 ASeconds);
extern DELPHI_PACKAGE bool __fastcall WithinPastMilliSeconds(const System::TDateTime ANow, const System::TDateTime AThen, const __int64 AMilliSeconds);
extern DELPHI_PACKAGE __int64 __fastcall DateTimeToMilliseconds(const System::TDateTime ADateTime);
extern DELPHI_PACKAGE int __fastcall TimeToMilliseconds(const System::TTime ATime);
extern DELPHI_PACKAGE int __fastcall YearsBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE int __fastcall MonthsBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE int __fastcall WeeksBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE int __fastcall DaysBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE __int64 __fastcall HoursBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE __int64 __fastcall MinutesBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE __int64 __fastcall SecondsBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE __int64 __fastcall MilliSecondsBetween(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE bool __fastcall DateTimeInRange(System::TDateTime ADateTime, System::TDateTime AStartDateTime, System::TDateTime AEndDateTime, bool aInclusive = true);
extern DELPHI_PACKAGE bool __fastcall TimeInRange(System::TTime ATime, System::TTime AStartTime, System::TTime AEndTime, bool AInclusive = true);
extern DELPHI_PACKAGE bool __fastcall DateInRange(System::TDate ADate, System::TDate AStartDate, System::TDate AEndDate, bool AInclusive = true);
extern DELPHI_PACKAGE double __fastcall YearSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall MonthSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall WeekSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall DaySpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall HourSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall MinuteSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall SecondSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE double __fastcall MilliSecondSpan(const System::TDateTime ANow, const System::TDateTime AThen);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncYear(const System::TDateTime AValue, const int ANumberOfYears = 0x1);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncWeek(const System::TDateTime AValue, const int ANumberOfWeeks = 0x1);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncDay(const System::TDateTime AValue, const int ANumberOfDays = 0x1);
#ifndef _WIN64
extern DELPHI_PACKAGE System::TDateTime __fastcall IncHour(const System::TDateTime AValue, const __int64 ANumberOfHours = 1LL);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncMinute(const System::TDateTime AValue, const __int64 ANumberOfMinutes = 1LL);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncSecond(const System::TDateTime AValue, const __int64 ANumberOfSeconds = 1LL);
extern DELPHI_PACKAGE System::TDateTime __fastcall IncMilliSecond(const System::TDateTime AValue, const __int64 ANumberOfMilliSeconds = 1LL);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::TDateTime __fastcall IncHour(const System::TDateTime AValue, const __int64 ANumberOfHours = (__int64)(1LL));
extern DELPHI_PACKAGE System::TDateTime __fastcall IncMinute(const System::TDateTime AValue, const __int64 ANumberOfMinutes = (__int64)(1LL));
extern DELPHI_PACKAGE System::TDateTime __fastcall IncSecond(const System::TDateTime AValue, const __int64 ANumberOfSeconds = (__int64)(1LL));
extern DELPHI_PACKAGE System::TDateTime __fastcall IncMilliSecond(const System::TDateTime AValue, const __int64 ANumberOfMilliSeconds = (__int64)(1LL));
#endif /* _WIN64 */
extern DELPHI_PACKAGE System::TDateTime __fastcall EncodeDateTime(const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond);
extern DELPHI_PACKAGE void __fastcall DecodeDateTime(const System::TDateTime AValue, /* out */ System::Word &AYear, /* out */ System::Word &AMonth, /* out */ System::Word &ADay, /* out */ System::Word &AHour, /* out */ System::Word &AMinute, /* out */ System::Word &ASecond, /* out */ System::Word &AMilliSecond);
extern DELPHI_PACKAGE System::TDateTime __fastcall EncodeDateWeek(const System::Word AYear, const System::Word AWeekOfYear, const System::Word ADayOfWeek = (System::Word)(0x1));
extern DELPHI_PACKAGE void __fastcall DecodeDateWeek(const System::TDateTime AValue, /* out */ System::Word &AYear, /* out */ System::Word &AWeekOfYear, /* out */ System::Word &ADayOfWeek);
extern DELPHI_PACKAGE System::TDateTime __fastcall EncodeDateDay(const System::Word AYear, const System::Word ADayOfYear);
extern DELPHI_PACKAGE void __fastcall DecodeDateDay(const System::TDateTime AValue, /* out */ System::Word &AYear, /* out */ System::Word &ADayOfYear);
extern DELPHI_PACKAGE System::TDateTime __fastcall EncodeDateMonthWeek(const System::Word AYear, const System::Word AMonth, const System::Word AWeekOfMonth, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE void __fastcall DecodeDateMonthWeek(const System::TDateTime AValue, /* out */ System::Word &AYear, /* out */ System::Word &AMonth, /* out */ System::Word &AWeekOfMonth, /* out */ System::Word &ADayOfWeek);
extern DELPHI_PACKAGE bool __fastcall TryEncodeDateTime(const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond, /* out */ System::TDateTime &AValue);
extern DELPHI_PACKAGE bool __fastcall TryEncodeDateWeek(const System::Word AYear, const System::Word AWeekOfYear, /* out */ System::TDateTime &AValue, const System::Word ADayOfWeek = (System::Word)(0x1));
extern DELPHI_PACKAGE bool __fastcall TryEncodeDateDay(const System::Word AYear, const System::Word ADayOfYear, /* out */ System::TDateTime &AValue);
extern DELPHI_PACKAGE bool __fastcall TryEncodeDateMonthWeek(const System::Word AYear, const System::Word AMonth, const System::Word AWeekOfMonth, const System::Word ADayOfWeek, System::TDateTime &AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeYear(const System::TDateTime AValue, const System::Word AYear);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeMonth(const System::TDateTime AValue, const System::Word AMonth);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeDay(const System::TDateTime AValue, const System::Word ADay);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeHour(const System::TDateTime AValue, const System::Word AHour);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeMinute(const System::TDateTime AValue, const System::Word AMinute);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeSecond(const System::TDateTime AValue, const System::Word ASecond);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeMilliSecond(const System::TDateTime AValue, const System::Word AMilliSecond);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeDate(const System::TDateTime AValue, const System::Word AYear, const System::Word AMonth, const System::Word ADay);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeTime(const System::TDateTime AValue, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond);
extern DELPHI_PACKAGE System::TDateTime __fastcall RecodeDateTime(const System::TDateTime AValue, const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond);
extern DELPHI_PACKAGE bool __fastcall TryRecodeDateTime(const System::TDateTime AValue, const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond, /* out */ System::TDateTime &AResult);
extern DELPHI_PACKAGE System::Types::TValueRelationship __fastcall CompareDateTime(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE bool __fastcall SameDateTime(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE System::Types::TValueRelationship __fastcall CompareDate(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE bool __fastcall SameDate(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE System::Types::TValueRelationship __fastcall CompareTime(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE bool __fastcall SameTime(const System::TDateTime A, const System::TDateTime B);
extern DELPHI_PACKAGE System::Word __fastcall NthDayOfWeek(const System::TDateTime AValue);
extern DELPHI_PACKAGE void __fastcall DecodeDayOfWeekInMonth(const System::TDateTime AValue, /* out */ System::Word &AYear, /* out */ System::Word &AMonth, /* out */ System::Word &ANthDayOfWeek, /* out */ System::Word &ADayOfWeek);
extern DELPHI_PACKAGE System::TDateTime __fastcall EncodeDayOfWeekInMonth(const System::Word AYear, const System::Word AMonth, const System::Word ANthDayOfWeek, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE bool __fastcall TryEncodeDayOfWeekInMonth(const System::Word AYear, const System::Word AMonth, const System::Word ANthDayOfWeek, const System::Word ADayOfWeek, /* out */ System::TDateTime &AValue);
extern DELPHI_PACKAGE double __fastcall DateTimeToJulianDate(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall JulianDateToDateTime(const double AValue);
extern DELPHI_PACKAGE bool __fastcall TryJulianDateToDateTime(const double AValue, /* out */ System::TDateTime &ADateTime);
extern DELPHI_PACKAGE double __fastcall DateTimeToModifiedJulianDate(const System::TDateTime AValue);
extern DELPHI_PACKAGE System::TDateTime __fastcall ModifiedJulianDateToDateTime(const double AValue);
extern DELPHI_PACKAGE bool __fastcall TryModifiedJulianDateToDateTime(const double AValue, /* out */ System::TDateTime &ADateTime);
extern DELPHI_PACKAGE __int64 __fastcall DateTimeToUnix(const System::TDateTime AValue, bool AInputIsUTC = true);
extern DELPHI_PACKAGE System::TDateTime __fastcall UnixToDateTime(const __int64 AValue, bool AReturnUTC = true);
extern DELPHI_PACKAGE void __fastcall InvalidDateTimeError(const System::Word AYear, const System::Word AMonth, const System::Word ADay, const System::Word AHour, const System::Word AMinute, const System::Word ASecond, const System::Word AMilliSecond, const System::TDateTime ABaseDate = 0.000000E+00);
extern DELPHI_PACKAGE void __fastcall InvalidDateWeekError(const System::Word AYear, const System::Word AWeekOfYear, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE void __fastcall InvalidDateDayError(const System::Word AYear, const System::Word ADayOfYear);
extern DELPHI_PACKAGE void __fastcall InvalidDateMonthWeekError(const System::Word AYear, const System::Word AMonth, const System::Word AWeekOfMonth, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE void __fastcall InvalidDayOfWeekInMonthError(const System::Word AYear, const System::Word AMonth, const System::Word ANthDayOfWeek, const System::Word ADayOfWeek);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DateToISO8601(const System::TDateTime ADate, bool AInputIsUTC = true);
extern DELPHI_PACKAGE System::TDateTime __fastcall ISO8601ToDate(const System::UnicodeString AISODate, bool AReturnUTC = true);
extern DELPHI_PACKAGE bool __fastcall TryISO8601ToDate(const System::UnicodeString AISODate, /* out */ System::TDateTime &Value, bool AReturnUTC = true);
extern DELPHI_PACKAGE System::TDateTime __fastcall HttpToDate(const System::UnicodeString AHttpDate, bool AReturnUTC = true);
}	/* namespace Dateutils */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_DATEUTILS)
using namespace System::Dateutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_DateutilsHPP
