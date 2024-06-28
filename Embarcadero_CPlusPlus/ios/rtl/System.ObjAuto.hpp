// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.ObjAuto.pas' rev: 34.00 (iOS)

#ifndef System_ObjautoHPP
#define System_ObjautoHPP

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

namespace System
{
namespace Objauto
{
//-- forward type declarations -----------------------------------------------
struct TMethodInfoHeader;
struct TReturnInfo;
struct TParamInfo;
//-- type declarations -------------------------------------------------------
typedef System::Typinfo::TCallConv TCallingConvention _DEPRECATED_ATTRIBUTE1("Use System.TypInfo.TCallConv instead.") ;

using System::Typinfo::TParamFlags;

typedef TMethodInfoHeader *PMethodInfoHeader;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TMethodInfoHeader
{
public:
	System::Word Len;
	void *Addr;
	System::Typinfo::TSymbolName Name;
	System::Typinfo::TTypeInfoFieldAccessor __fastcall NameFld();
};
#pragma pack(pop)


typedef TReturnInfo *PReturnInfo;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TReturnInfo
{
public:
	System::Byte Version;
	System::Typinfo::TCallConv CallingConvention;
	System::Typinfo::PTypeInfo *ReturnType;
	System::Word ParamSize;
	System::Byte ParamCount;
};
#pragma pack(pop)


typedef TParamInfo *PParamInfo;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TParamInfo
{
public:
	System::Typinfo::TParamFlags Flags;
	System::Typinfo::PTypeInfo *ParamType;
	System::Word Access;
	System::Typinfo::TSymbolName Name;
	System::Typinfo::TTypeInfoFieldAccessor __fastcall NameFld();
};
#pragma pack(pop)


typedef System::DynamicArray<PMethodInfoHeader> TMethodInfoArray;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TMethodInfoArray __fastcall GetMethods(System::TClass ClassType);
extern DELPHI_PACKAGE PMethodInfoHeader __fastcall GetMethodInfo(System::TObject* Instance, const System::UnicodeString MethodName)/* overload */;
extern DELPHI_PACKAGE PMethodInfoHeader __fastcall GetMethodInfo _DEPRECATED_ATTRIBUTE1("use String version of GetMethodInfo instead of ShortString version.") (System::TObject* Instance, const System::ShortString &MethodName)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall ObjectInvoke(System::TObject* Instance, PMethodInfoHeader MethodHeader, const int *ParamIndexes, const int ParamIndexes_High, const System::Variant *Params, const int Params_High);
}	/* namespace Objauto */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_OBJAUTO)
using namespace System::Objauto;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_ObjautoHPP
