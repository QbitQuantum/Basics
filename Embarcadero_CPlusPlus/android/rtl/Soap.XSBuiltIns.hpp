// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.XSBuiltIns.pas' rev: 34.00 (Android)

#ifndef Soap_XsbuiltinsHPP
#define Soap_XsbuiltinsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <Data.FmtBcd.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Xsbuiltins
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXSTime;
class DELPHICLASS TXSDate;
class DELPHICLASS TXSCustomDateTime;
class DELPHICLASS TXSDateTime;
class DELPHICLASS TXSDuration;
class DELPHICLASS EXSDateTimeException;
class DELPHICLASS EXSDecimalException;
class DELPHICLASS EXSHexBinaryException;
class DELPHICLASS TXSHexBinary;
class DELPHICLASS TXSDecimal;
class DELPHICLASS TXSString;
class DELPHICLASS TXSBoolean;
class DELPHICLASS TXSInteger;
class DELPHICLASS TXSLong;
class DELPHICLASS TXMLData;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSTime : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	System::UnicodeString FTimeValue;
	bool FUseZeroMilliseconds;
	
protected:
	System::TDateTime __fastcall GetAsTime();
	double __fastcall GetFractionalSeconds();
	System::UnicodeString __fastcall GetFractionalSecondString();
	short __fastcall GetHourOffset();
	System::Word __fastcall GetHour();
	System::Word __fastcall GetMillisecond();
	System::Word __fastcall GetMinute();
	short __fastcall GetMinuteOffset();
	System::Word __fastcall GetSecond();
	void __fastcall SetAsTime(const System::TDateTime Value);
	void __fastcall SetFractionalSeconds(const double Value);
	void __fastcall SetHour(const System::Word Value);
	void __fastcall SetHourOffset(const short Value);
	void __fastcall SetMillisecond(const System::Word Value);
	void __fastcall SetMinute(const System::Word Value);
	void __fastcall SetMinuteOffset(const short Value);
	void __fastcall SetSecond(const System::Word Value);
	__property System::UnicodeString FractionalSecondString = {read=GetFractionalSecondString};
	
public:
	__property System::TDateTime AsTime = {read=GetAsTime, write=SetAsTime};
	__property double FractionalSeconds = {read=GetFractionalSeconds, write=SetFractionalSeconds};
	__property System::Word Hour = {read=GetHour, write=SetHour, default=0};
	__property short HourOffset = {read=GetHourOffset, write=SetHourOffset, default=0};
	__property System::Word Millisecond = {read=GetMillisecond, write=SetMillisecond, default=0};
	__property System::Word Minute = {read=GetMinute, write=SetMinute, default=0};
	__property short MinuteOffset = {read=GetMinuteOffset, write=SetMinuteOffset, nodefault};
	__property System::Word Second = {read=GetSecond, write=SetSecond, default=0};
	__property bool UseZeroMilliseconds = {read=FUseZeroMilliseconds, write=FUseZeroMilliseconds, nodefault};
	TXSTime* __fastcall Clone();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSTime() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSTime() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSDate : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	System::UnicodeString FDateValue;
	
protected:
	System::TDateTime __fastcall GetAsDate();
	System::Word __fastcall GetDay();
	System::Word __fastcall GetMonth();
	int __fastcall GetYear();
	void __fastcall SetAsDate(const System::TDateTime Value);
	void __fastcall SetMonth(const System::Word Value);
	void __fastcall SetDay(const System::Word Value);
	void __fastcall SetYear(const int Value);
	
public:
	__fastcall virtual TXSDate();
	__property System::Word Month = {read=GetMonth, write=SetMonth, default=0};
	__property System::Word Day = {read=GetDay, write=SetDay, default=0};
	__property int Year = {read=GetYear, write=SetYear, default=0};
	TXSDate* __fastcall Clone();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
	__property System::TDateTime AsDate = {read=GetAsDate, write=SetAsDate};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSDate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSCustomDateTime : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
protected:
	System::UnicodeString FDateTime;
	System::TDateTime __fastcall GetAsDateTime();
	System::TDateTime __fastcall GetAsUTCDateTime();
	System::Word __fastcall GetDay();
	double __fastcall GetFractionalSeconds();
	System::Word __fastcall GetHour();
	short __fastcall GetHourOffset();
	System::Word __fastcall GetMonth();
	System::Word __fastcall GetMillisecond();
	System::Word __fastcall GetMinute();
	short __fastcall GetMinuteOffset();
	System::Word __fastcall GetSecond();
	bool __fastcall GetUseZeroMilliseconds();
	int __fastcall GetYear();
	void __fastcall SetAsDateTime(const System::TDateTime Value);
	void __fastcall SetAsUTCDateTime(const System::TDateTime Value);
	void __fastcall SetFractionalSeconds(const double Value);
	virtual void __fastcall SetDay(const System::Word Value);
	virtual void __fastcall SetHour(const System::Word Value);
	virtual void __fastcall SetHourOffset(const short Value);
	virtual void __fastcall SetMillisecond(const System::Word Value);
	virtual void __fastcall SetMinute(const System::Word Value);
	virtual void __fastcall SetMinuteOffset(const short Value);
	virtual void __fastcall SetMonth(const System::Word Value);
	virtual void __fastcall SetSecond(const System::Word Value);
	void __fastcall SetUseZeroMilliseconds(const bool Value);
	virtual void __fastcall SetYear(const int Value);
	__property System::Word Millisecond = {read=GetMillisecond, write=SetMillisecond, default=0};
	
public:
	__fastcall virtual TXSCustomDateTime();
	__fastcall virtual ~TXSCustomDateTime();
	__property System::TDateTime AsDateTime = {read=GetAsDateTime, write=SetAsDateTime};
	__property System::TDateTime AsUTCDateTime = {read=GetAsUTCDateTime, write=SetAsUTCDateTime};
	__property double FractionalSeconds = {read=GetFractionalSeconds, write=SetFractionalSeconds};
	__property System::Word Hour = {read=GetHour, write=SetHour, default=0};
	__property short HourOffset = {read=GetHourOffset, write=SetHourOffset, default=0};
	__property System::Word Minute = {read=GetMinute, write=SetMinute, default=0};
	__property short MinuteOffset = {read=GetMinuteOffset, write=SetMinuteOffset, default=0};
	__property System::Word Second = {read=GetSecond, write=SetSecond, default=0};
	__property System::Word Month = {read=GetMonth, write=SetMonth, default=0};
	__property System::Word Day = {read=GetDay, write=SetDay, default=0};
	__property int Year = {read=GetYear, write=SetYear, default=0};
	__property bool UseZeroMilliseconds = {read=GetUseZeroMilliseconds, write=SetUseZeroMilliseconds, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSDateTime : public TXSCustomDateTime
{
	typedef TXSCustomDateTime inherited;
	
public:
	TXSDateTime* __fastcall Clone();
	virtual System::UnicodeString __fastcall NativeToXS();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	static TXSDuration* __fastcall CompareDateTimeParam(TXSDateTime* const Value1, TXSDateTime* const Value2);
	__property System::Word Millisecond = {read=GetMillisecond, write=SetMillisecond, default=0};
public:
	/* TXSCustomDateTime.Create */ inline __fastcall virtual TXSDateTime() : TXSCustomDateTime() { }
	/* TXSCustomDateTime.Destroy */ inline __fastcall virtual ~TXSDateTime() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TXSDuration : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
	
protected:
	struct DECLSPEC_DRECORD TDurationData
	{
	public:
		int Year;
		int Month;
		int Day;
		int Hour;
		int Minute;
		double Second;
		bool Negative;
	};
	
	
	
protected:
	TDurationData FData;
	int __fastcall GetSecond();
	void __fastcall SetSecond(const int Value);
	
public:
	__fastcall virtual TXSDuration();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
	static System::UnicodeString __fastcall EncodeDuration(const TDurationData &Data);
	static void __fastcall DecodeDuration(const System::UnicodeString ADuration, /* out */ TDurationData &Data);
	__property int Year = {read=FData.Year, write=FData.Year, nodefault};
	__property int Month = {read=FData.Month, write=FData.Month, nodefault};
	__property int Day = {read=FData.Day, write=FData.Day, nodefault};
	__property int Hour = {read=FData.Hour, write=FData.Hour, nodefault};
	__property int Minute = {read=FData.Minute, write=FData.Minute, nodefault};
	__property int Second = {read=GetSecond, write=SetSecond, nodefault};
	__property double DecimalSecond = {read=FData.Second, write=FData.Second};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSDuration() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXSDateTimeException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXSDateTimeException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXSDateTimeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXSDateTimeException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXSDateTimeException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSDateTimeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSDateTimeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXSDateTimeException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXSDateTimeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSDateTimeException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSDateTimeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSDateTimeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSDateTimeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXSDateTimeException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXSDecimalException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXSDecimalException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXSDecimalException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXSDecimalException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXSDecimalException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSDecimalException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSDecimalException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXSDecimalException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXSDecimalException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSDecimalException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSDecimalException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSDecimalException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSDecimalException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXSDecimalException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXSHexBinaryException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXSHexBinaryException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXSHexBinaryException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXSHexBinaryException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXSHexBinaryException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSHexBinaryException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXSHexBinaryException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXSHexBinaryException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXSHexBinaryException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSHexBinaryException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXSHexBinaryException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSHexBinaryException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXSHexBinaryException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXSHexBinaryException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSHexBinary : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	System::UnicodeString FHexBinaryString;
	void __fastcall SetAsByteArray(const System::TArray__1<System::Byte> Value);
	System::TArray__1<System::Byte> __fastcall GetAsByteArray();
	
public:
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
	__property System::UnicodeString HexBinaryString = {read=FHexBinaryString, write=FHexBinaryString};
	__property System::TArray__1<System::Byte> AsByteArray = {read=GetAsByteArray, write=SetAsByteArray};
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSHexBinary() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSHexBinary() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSDecimal : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	System::UnicodeString FDecimalString;
	Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	
public:
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
	__property System::UnicodeString DecimalString = {read=FDecimalString, write=FDecimalString};
	__property Data::Fmtbcd::TBcd AsBcd = {read=GetAsBcd, write=SetAsBcd};
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSDecimal() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSDecimal() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSString : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	System::UnicodeString FString;
	
public:
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall NativeToXS();
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSString() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSString() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef TXSDateTime TXSTimeInstant;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSBoolean : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	bool FBoolean;
	
public:
	virtual System::UnicodeString __fastcall NativeToXS();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	__property bool AsBoolean = {read=FBoolean, write=FBoolean, nodefault};
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSBoolean() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSBoolean() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXSInteger : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	int FInteger;
	
public:
	virtual System::UnicodeString __fastcall NativeToXS();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	__property int AsInteger = {read=FInteger, write=FInteger, nodefault};
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSInteger() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSInteger() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TXSLong : public Soap::Invokeregistry::TRemotableXS
{
	typedef Soap::Invokeregistry::TRemotableXS inherited;
	
private:
	__int64 FLong;
	
public:
	virtual System::UnicodeString __fastcall NativeToXS();
	virtual void __fastcall XSToNative(const System::UnicodeString Value);
	__property __int64 AsLong = {read=FLong, write=FLong};
public:
	/* TRemotable.Create */ inline __fastcall virtual TXSLong() : Soap::Invokeregistry::TRemotableXS() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TXSLong() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLData : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Xml::Xmlintf::_di_IXMLDocument FXMLDocument;
	Xml::Xmlintf::_di_IXMLNode FXMLNode;
	
public:
	__fastcall virtual TXMLData();
	__fastcall virtual ~TXMLData();
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjectToSOAP(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const Soap::Invokeregistry::_di_IObjConverter ObjConverter, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, Soap::Invokeregistry::TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	virtual void __fastcall SOAPToObject(const Xml::Xmlintf::_di_IXMLNode RootNode, const Xml::Xmlintf::_di_IXMLNode Node, const Soap::Invokeregistry::_di_IObjConverter ObjConverter);
	void __fastcall LoadFromXML(const System::UnicodeString XML)/* overload */;
	void __fastcall LoadFromXML(const System::WideString XML)/* overload */;
	__property Xml::Xmlintf::_di_IXMLNode XMLNode = {read=FXMLNode};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::WideChar SHexMarker = (System::WideChar)(0x24);
extern DELPHI_PACKAGE System::UnicodeString SoapTimePrefix;
static constexpr System::WideChar XMLDateSeparator = (System::WideChar)(0x2d);
static constexpr System::WideChar XMLHourOffsetMinusMarker = (System::WideChar)(0x2d);
static constexpr System::WideChar XMLHourOffsetPlusMarker = (System::WideChar)(0x2b);
static constexpr System::WideChar XMLTimeSeparator = (System::WideChar)(0x3a);
static constexpr System::Int8 XMLMonthPos = System::Int8(0x6);
static constexpr System::Int8 XMLDayPos = System::Int8(0x9);
static constexpr System::Int8 XMLYearPos = System::Int8(0x1);
static constexpr System::Int8 XMLMilSecPos = System::Int8(0xa);
static constexpr System::Int8 XMLDefaultYearDigits = System::Int8(0x4);
static constexpr System::WideChar XMLDurationStart = (System::WideChar)(0x50);
static constexpr System::WideChar XMLDurationYear = (System::WideChar)(0x59);
static constexpr System::WideChar XMLDurationMonth = (System::WideChar)(0x4d);
static constexpr System::WideChar XMLDurationDay = (System::WideChar)(0x44);
static constexpr System::WideChar XMLDurationHour = (System::WideChar)(0x48);
static constexpr System::WideChar XMLDurationMinute = (System::WideChar)(0x4d);
static constexpr System::WideChar XMLDurationSecond = (System::WideChar)(0x53);
extern DELPHI_PACKAGE System::UnicodeString SNAN;
extern DELPHI_PACKAGE System::WideChar SSciNotationMarker;
extern DELPHI_PACKAGE System::WideChar SDecimal;
extern DELPHI_PACKAGE System::WideChar SNegative;
extern DELPHI_PACKAGE System::WideChar SPlus;
static constexpr System::WideChar SLocalTimeMarker = (System::WideChar)(0x5a);
static constexpr System::Int8 MaxMonth = System::Int8(0xc);
static constexpr System::Int8 MinMonth = System::Int8(0x1);
static constexpr System::Int8 MaxDay = System::Int8(0x1f);
static constexpr System::Int8 MinDay = System::Int8(0x1);
static constexpr System::WideChar SoapDecimalSeparator = (System::WideChar)(0x2e);
extern DELPHI_PACKAGE System::StaticArray<int, 2> IncrementAmount;
extern DELPHI_PACKAGE System::UnicodeString __fastcall SoapFloatToStr(double Value);
extern DELPHI_PACKAGE double __fastcall SoapStrToFloat(System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DateTimeToXMLTime(System::TDateTime Value, bool ApplyLocalBias = true);
extern DELPHI_PACKAGE System::TDateTime __fastcall XMLTimeToDateTime(const System::UnicodeString XMLDateTime, bool AsUTCTime = false);
extern DELPHI_PACKAGE TXSDateTime* __fastcall DateTimeToXSDateTime(const System::TDateTime Value, bool ApplyLocalBias = false);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetDataFromFile(System::UnicodeString AFileName);
extern DELPHI_PACKAGE void __fastcall InitXSTypes(void);
}	/* namespace Xsbuiltins */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_XSBUILTINS)
using namespace Soap::Xsbuiltins;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_XsbuiltinsHPP
