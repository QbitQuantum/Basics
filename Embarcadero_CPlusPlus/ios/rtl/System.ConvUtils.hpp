// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.ConvUtils.pas' rev: 34.00 (iOS)

#ifndef System_ConvutilsHPP
#define System_ConvutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Convutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EConversionError;
class DELPHICLASS TConvTypeInfo;
class DELPHICLASS TConvTypeFactor;
class DELPHICLASS TConvTypeProcs;
//-- type declarations -------------------------------------------------------
_DECLARE_ARITH_TYPE_ALIAS(System::Word, TConvFamily);

_DECLARE_ARITH_TYPE_ALIAS(System::Word, TConvType);

typedef double __fastcall (*TConversionProc)(const double AValue);

typedef System::DynamicArray<TConvType> TConvTypeArray;

typedef System::DynamicArray<TConvFamily> TConvFamilyArray;

class PASCALIMPLEMENTATION EConversionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EConversionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EConversionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EConversionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EConversionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EConversionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EConversionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EConversionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EConversionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EConversionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EConversionError() { }
	
};


class PASCALIMPLEMENTATION TConvTypeInfo : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FDescription;
	TConvFamily FConvFamily;
	TConvType FConvType;
	
public:
	__fastcall TConvTypeInfo(const TConvFamily AConvFamily, const System::UnicodeString ADescription);
	virtual double __fastcall ToCommon(const double AValue) = 0 ;
	virtual double __fastcall FromCommon(const double AValue) = 0 ;
	__property TConvFamily ConvFamily = {read=FConvFamily, nodefault};
	__property TConvType ConvType = {read=FConvType, nodefault};
	__property System::UnicodeString Description = {read=FDescription};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TConvTypeInfo() { }
	
};


typedef System::DynamicArray<TConvTypeInfo*> TConvTypeList;

class PASCALIMPLEMENTATION TConvTypeFactor : public TConvTypeInfo
{
	typedef TConvTypeInfo inherited;
	
private:
	double FFactor;
	
protected:
	__property double Factor = {read=FFactor};
	
public:
	__fastcall TConvTypeFactor(const TConvFamily AConvFamily, const System::UnicodeString ADescription, const double AFactor);
	virtual double __fastcall ToCommon(const double AValue);
	virtual double __fastcall FromCommon(const double AValue);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TConvTypeFactor() { }
	
};


class PASCALIMPLEMENTATION TConvTypeProcs : public TConvTypeInfo
{
	typedef TConvTypeInfo inherited;
	
private:
	TConversionProc FToCommonProc;
	TConversionProc FFromCommonProc;
	
public:
	__fastcall TConvTypeProcs(const TConvFamily AConvFamily, const System::UnicodeString ADescription, const TConversionProc AToCommonProc, const TConversionProc AFromCommonProc);
	virtual double __fastcall ToCommon(const double AValue);
	virtual double __fastcall FromCommon(const double AValue);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TConvTypeProcs() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TConvFamily CIllegalConvFamily;
extern DELPHI_PACKAGE TConvType CIllegalConvType;
extern DELPHI_PACKAGE System::UnicodeString GConvUnitToStrFmt;
extern DELPHI_PACKAGE void __fastcall RaiseConversionError(const System::UnicodeString AText)/* overload */;
extern DELPHI_PACKAGE void __fastcall RaiseConversionError(const System::UnicodeString AText, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
extern DELPHI_PACKAGE void __fastcall RaiseConversionRegError(TConvFamily AFamily, const System::UnicodeString ADescription);
extern DELPHI_PACKAGE TConvFamily __fastcall ConvTypeToFamily(const TConvType AType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TryConvTypeToFamily(const TConvType AType, /* out */ TConvFamily &AFamily)/* overload */;
extern DELPHI_PACKAGE TConvFamily __fastcall ConvTypeToFamily(const TConvType AFrom, const TConvType ATo)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TryConvTypeToFamily(const TConvType AFrom, const TConvType ATo, /* out */ TConvFamily &AFamily)/* overload */;
extern DELPHI_PACKAGE bool __fastcall CompatibleConversionTypes(const TConvType AFrom, const TConvType ATo);
extern DELPHI_PACKAGE bool __fastcall CompatibleConversionType(const TConvType AType, const TConvFamily AFamily);
extern DELPHI_PACKAGE double __fastcall Convert(const double AValue, const TConvType AFrom, const TConvType ATo)/* overload */;
extern DELPHI_PACKAGE double __fastcall Convert(const double AValue, const TConvType AFrom1, const TConvType AFrom2, const TConvType ATo1, const TConvType ATo2)/* overload */;
extern DELPHI_PACKAGE double __fastcall ConvertFrom(const TConvType AFrom, const double AValue);
extern DELPHI_PACKAGE double __fastcall ConvertTo(const double AValue, const TConvType ATo);
extern DELPHI_PACKAGE double __fastcall ConvUnitAdd(const double AValue1, const TConvType AType1, const double AValue2, const TConvType AType2, const TConvType AResultType);
extern DELPHI_PACKAGE double __fastcall ConvUnitDiff(const double AValue1, const TConvType AType1, const double AValue2, const TConvType AType2, const TConvType AResultType);
extern DELPHI_PACKAGE double __fastcall ConvUnitInc(const double AValue, const TConvType AType, const TConvType AAmountType)/* overload */;
extern DELPHI_PACKAGE double __fastcall ConvUnitInc(const double AValue, const TConvType AType, const double AAmount, const TConvType AAmountType)/* overload */;
extern DELPHI_PACKAGE double __fastcall ConvUnitDec(const double AValue, const TConvType AType, const TConvType AAmountType)/* overload */;
extern DELPHI_PACKAGE double __fastcall ConvUnitDec(const double AValue, const TConvType AType, const double AAmount, const TConvType AAmountType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall ConvUnitWithinPrevious(const double AValue, const double ATest, const TConvType AType, const double AAmount, const TConvType AAmountType);
extern DELPHI_PACKAGE bool __fastcall ConvUnitWithinNext(const double AValue, const double ATest, const TConvType AType, const double AAmount, const TConvType AAmountType);
extern DELPHI_PACKAGE System::Types::TValueRelationship __fastcall ConvUnitCompareValue(const double AValue1, const TConvType AType1, const double AValue2, const TConvType AType2);
extern DELPHI_PACKAGE bool __fastcall ConvUnitSameValue(const double AValue1, const TConvType AType1, const double AValue2, const TConvType AType2);
extern DELPHI_PACKAGE bool __fastcall RegisterConversionType(TConvTypeInfo* AConvTypeInfo, /* out */ TConvType &AType)/* overload */;
extern DELPHI_PACKAGE TConvType __fastcall RegisterConversionType(const TConvFamily AFamily, const System::UnicodeString ADescription, const double AFactor)/* overload */;
extern DELPHI_PACKAGE TConvType __fastcall RegisterConversionType(const TConvFamily AFamily, const System::UnicodeString ADescription, const TConversionProc AToCommonProc, const TConversionProc AFromCommonProc)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnregisterConversionType(const TConvType AType);
extern DELPHI_PACKAGE TConvFamily __fastcall RegisterConversionFamily(const System::UnicodeString ADescription);
extern DELPHI_PACKAGE void __fastcall UnregisterConversionFamily(const TConvFamily AFamily);
extern DELPHI_PACKAGE double __fastcall StrToConvUnit(System::UnicodeString AText, /* out */ TConvType &AType);
extern DELPHI_PACKAGE bool __fastcall TryStrToConvUnit(System::UnicodeString AText, /* out */ double &AValue, /* out */ TConvType &AType);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ConvUnitToStr(const double AValue, const TConvType AType);
extern DELPHI_PACKAGE void __fastcall GetConvTypes(const TConvFamily AFamily, /* out */ TConvTypeArray &ATypes);
extern DELPHI_PACKAGE void __fastcall GetConvFamilies(/* out */ TConvFamilyArray &AFamilies);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ConvTypeToDescription(const TConvType AType);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ConvFamilyToDescription(const TConvFamily AFamily);
extern DELPHI_PACKAGE bool __fastcall DescriptionToConvType(const System::UnicodeString ADescription, /* out */ TConvType &AType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall DescriptionToConvType(const TConvFamily AFamily, const System::UnicodeString ADescription, /* out */ TConvType &AType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall DescriptionToConvFamily(const System::UnicodeString ADescription, /* out */ TConvFamily &AFamily);
}	/* namespace Convutils */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_CONVUTILS)
using namespace System::Convutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_ConvutilsHPP
