// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.IntfInfo.pas' rev: 34.00 (Android)

#ifndef Soap_IntfinfoHPP
#define Soap_IntfinfoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Intfinfo
{
//-- forward type declarations -----------------------------------------------
struct TIntfParamEntry;
struct TIntfMethEntry;
struct TIntfMetaData;
class DELPHICLASS EInterfaceRTTIException;
//-- type declarations -------------------------------------------------------
typedef TIntfParamEntry *PIntfParamEntry;

struct DECLSPEC_DRECORD TIntfParamEntry
{
public:
	System::Typinfo::TParamFlags Flags;
	System::UnicodeString Name;
	System::Typinfo::TTypeInfo *Info;
};


typedef System::DynamicArray<TIntfParamEntry> TIntfParamEntryArray;

using System::Typinfo::TCallConv;

typedef TIntfMethEntry *PIntfMethEntry;

struct DECLSPEC_DRECORD TIntfMethEntry
{
public:
	System::UnicodeString Name;
	System::Typinfo::TCallConv CC;
	int Pos;
	int ParamCount;
	System::Typinfo::TTypeInfo *ResultInfo;
	System::Typinfo::TTypeInfo *SelfInfo;
	TIntfParamEntryArray Params;
	bool HasRTTI;
};


typedef System::DynamicArray<TIntfMethEntry> TIntfMethEntryArray;

typedef System::DynamicArray<PIntfMethEntry> TPIntfMethEntryArray;

enum DECLSPEC_DENUM TFillMethodArrayOpt : unsigned char { fmoAllBaseMethods, fmoRTTIBaseMethods, fmoNoBaseMethods };

typedef TIntfMetaData *PIntfMetaData;

struct DECLSPEC_DRECORD TIntfMetaData
{
public:
	System::UnicodeString Name;
	System::UnicodeString UnitName;
	TIntfMethEntryArray MDA;
	GUID IID;
	System::Typinfo::TTypeInfo *Info;
	System::Typinfo::TTypeInfo *AncInfo;
	int NumAnc;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EInterfaceRTTIException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInterfaceRTTIException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInterfaceRTTIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInterfaceRTTIException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInterfaceRTTIException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInterfaceRTTIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInterfaceRTTIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInterfaceRTTIException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInterfaceRTTIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInterfaceRTTIException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInterfaceRTTIException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInterfaceRTTIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInterfaceRTTIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInterfaceRTTIException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::StaticArray<System::UnicodeString, 5> Soap_Intfinfo__2;

typedef System::StaticArray<System::UnicodeString, 38> Soap_Intfinfo__3;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Soap_Intfinfo__2 CallingConventionName;
extern DELPHI_PACKAGE Soap_Intfinfo__3 TypeInfoNames;
extern DELPHI_PACKAGE int __fastcall GetMethNum(const TIntfMetaData &IntfMD, const System::UnicodeString MethName, int ParamCount = 0xffffffff);
extern DELPHI_PACKAGE void __fastcall GetIntfMetaData(System::Typinfo::PTypeInfo Info, TIntfMetaData &IntfMD, TFillMethodArrayOpt MethodArrayOpt)/* overload */;
extern DELPHI_PACKAGE void __fastcall GetIntfMetaData(System::Typinfo::PTypeInfo Info, TIntfMetaData &IntfMD, bool IncludeAllAncMethods = false)/* overload */;
extern DELPHI_PACKAGE void __fastcall GetDynArrayElTypeInfo(System::Typinfo::PTypeInfo typeInfo, System::Typinfo::PTypeInfo &EltInfo, int &Dims);
extern DELPHI_PACKAGE System::Typinfo::PTypeInfo __fastcall GetDynArrayNextInfo(System::Typinfo::PTypeInfo typeInfo);
extern DELPHI_PACKAGE System::Typinfo::PTypeInfo __fastcall GetDynArrayNextInfo2(System::Typinfo::PTypeInfo typeInfo, System::UnicodeString &Name);
extern DELPHI_PACKAGE bool __fastcall SameTypeInfo(const System::Typinfo::PTypeInfo RegInfo, const System::Typinfo::PTypeInfo OtherInfo);
extern DELPHI_PACKAGE bool __fastcall TypeNamesMatch(const System::UnicodeString RegName, const System::UnicodeString OtherName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall OtherTypeName(const System::UnicodeString TypeName);
extern DELPHI_PACKAGE int __fastcall GetPropListFlat(System::Typinfo::PTypeInfo TypeInfo, /* out */ System::Typinfo::PPropList &PropList);
extern DELPHI_PACKAGE bool __fastcall IsStoredPropConst(System::TObject* Instance, System::Typinfo::PPropInfo PropInfo);
extern DELPHI_PACKAGE System::Typinfo::PTypeInfo __fastcall GetClsMemberTypeInfo(const System::Typinfo::PTypeInfo ObjectTypeInfo, const System::UnicodeString MemberName = System::UnicodeString());
}	/* namespace Intfinfo */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_INTFINFO)
using namespace Soap::Intfinfo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_IntfinfoHPP
