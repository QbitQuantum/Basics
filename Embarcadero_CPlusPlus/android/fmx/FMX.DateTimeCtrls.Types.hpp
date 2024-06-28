﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DateTimeCtrls.Types.pas' rev: 34.00 (Android)

#ifndef Fmx_Datetimectrls_TypesHPP
#define Fmx_Datetimectrls_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Datetimectrls
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
struct TDTPartHelper /* Helper for enum 'TDTPart' */;
template<typename T> struct TRange__1;
struct TDTFormatPart;
class DELPHICLASS TDateTimeFormatter;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TDTPart : unsigned char { Year, Month, Day, Hour24, Hour12, Minute, Sec, MSec, AMPM, Unknown, tpYear _DEPRECATED_ATTRIBUTE3("Use TDTPart.Year")  = 0, tpMonth _DEPRECATED_ATTRIBUTE3("Use TDTPart.Month")  = 1, tpDay _DEPRECATED_ATTRIBUTE3("Use TDTPart.Day")  = 2, tpHour24 _DEPRECATED_ATTRIBUTE3("Use TDTPart.Hour24")  = 3, tpHour12 _DEPRECATED_ATTRIBUTE3("Use TDTPart.Hour12")  = 4, tpMin _DEPRECATED_ATTRIBUTE3("Use TDTPart.Minute")  = 5, tpSec _DEPRECATED_ATTRIBUTE3("Use TDTPart.Sec")  = 6, tpMSec _DEPRECATED_ATTRIBUTE3("Use TDTPart.MSec")  = 7, tpAMPM _DEPRECATED_ATTRIBUTE3("Use TDTPart.AMPM")  = 8, tpUnknow _DEPRECATED_ATTRIBUTE3("Use TDTPart.Unknown")  = 9 };

typedef TDTPart TDateTimePart _DEPRECATED_ATTRIBUTE1("Use TDTPart instead") ;

// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> struct DECLSPEC_DRECORD TRange__1
{
public:
	T Min;
	T Max;
};


struct DECLSPEC_DRECORD TDTFormatPart
{
public:
	TDTPart Part;
	int Value;
	System::UnicodeString DisplayFormat;
	TRange__1<int> Range;
	__fastcall TDTFormatPart(const TDTPart APart, const int AMin, const int AMax)/* overload */;
	__fastcall TDTFormatPart(const TDTPart APart)/* overload */;
	bool __fastcall IsAM();
	System::UnicodeString __fastcall ToAMPMString();
	bool __fastcall IsShortYearFormat();
	TDTFormatPart() {}
};


typedef TDTFormatPart TDateTimeFormatPart _DEPRECATED_ATTRIBUTE1("Use TDTFormatPart instead") ;

class PASCALIMPLEMENTATION TDateTimeFormatter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TDTFormatPart operator[](int Index) { return this->Parts[Index]; }
	
private:
	System::UnicodeString FFormat;
	System::TDateTime FDateTime;
	System::WideChar FMaskPlaceholder;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetFormat(const System::UnicodeString Value);
	void __fastcall SetDateTime(const System::TDateTime Value);
	TDTFormatPart __fastcall GetPart(int Index);
	int __fastcall GetCount();
	void __fastcall SetValue(int AIndex, const int Value);
	int __fastcall GetValue(int Index);
	System::UnicodeString __fastcall GetDisplayValue(int Index);
	
protected:
	System::Generics::Collections::TList__1<TDTFormatPart>* FParts;
	virtual void __fastcall ParseFormat(const System::UnicodeString AFormat);
	virtual void __fastcall RefreshDayParts(const System::Word AYear, const System::Word AMonth, /* out */ System::Word &NewDay);
	virtual void __fastcall UpdatePartsValues();
	virtual void __fastcall DoChange();
	
public:
	__fastcall TDateTimeFormatter();
	__fastcall virtual ~TDateTimeFormatter();
	__property int Count = {read=GetCount, nodefault};
	__property System::TDateTime DateTime = {read=FDateTime, write=SetDateTime};
	__property System::UnicodeString Format = {read=FFormat, write=SetFormat};
	__property System::WideChar MaskPlaceholder = {read=FMaskPlaceholder, write=FMaskPlaceholder, nodefault};
	__property TDTFormatPart Parts[int Index] = {read=GetPart/*, default*/};
	__property int Values[int Index] = {read=GetValue, write=SetValue};
	__property System::UnicodeString DisplayValues[int Index] = {read=GetDisplayValue};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Types */
}	/* namespace Datetimectrls */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DATETIMECTRLS_TYPES)
using namespace Fmx::Datetimectrls::Types;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DATETIMECTRLS)
using namespace Fmx::Datetimectrls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Datetimectrls_TypesHPP
