// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.ObjAuto.pas' rev: 34.00 (Windows)

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
#ifndef _WIN64
class DELPHICLASS EObjectInvokeExtendedTypeException;
#endif /* not _WIN64 */
__interface DELPHIINTERFACE IMethodHandler;
typedef System::DelphiInterface<IMethodHandler> _di_IMethodHandler;
struct TParameters;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
enum DECLSPEC_DENUM TCallingConvention _DEPRECATED_ATTRIBUTE1("Use System.TypInfo.TCallConv instead.")  : unsigned char { ccRegister, ccCdecl, ccPascal, ccStdCall, ccSafeCall };
#else /* _WIN64 */
typedef System::Typinfo::TCallConv TCallingConvention _DEPRECATED_ATTRIBUTE1("Use System.TypInfo.TCallConv instead.") ;
#endif /* _WIN64 */

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

#ifndef _WIN64
class PASCALIMPLEMENTATION EObjectInvokeExtendedTypeException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
protected:
	System::Extended FExt;
	
public:
	__fastcall EObjectInvokeExtendedTypeException(const System::UnicodeString Msg, const System::Extended Ext);
	__fastcall EObjectInvokeExtendedTypeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, const System::Extended Ext);
	__property System::Extended Ext = {read=FExt};
public:
	/* Exception.CreateRes */ inline __fastcall EObjectInvokeExtendedTypeException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EObjectInvokeExtendedTypeException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectInvokeExtendedTypeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectInvokeExtendedTypeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EObjectInvokeExtendedTypeException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EObjectInvokeExtendedTypeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectInvokeExtendedTypeException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectInvokeExtendedTypeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectInvokeExtendedTypeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectInvokeExtendedTypeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EObjectInvokeExtendedTypeException() { }
	
};


#endif /* not _WIN64 */
__interface  INTERFACE_UUID("{4E61C8CD-16CC-4830-B1E4-84F86FBC0D23}") IMethodHandler  : public System::IInterface 
{
	virtual System::Variant __fastcall Execute(const System::Variant *Args, const int Args_High) = 0 ;
	virtual System::Variant __fastcall InstanceToVariant(System::TObject* Instance) = 0 ;
};

typedef TParameters *PParameters;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TParameters
{
public:
#ifndef _WIN64
	System::StaticArray<unsigned, 2> Registers;
	unsigned EAXRegister;
	void *ReturnAddress;
#endif /* not _WIN64 */
	System::StaticArray<System::Byte, 1024> Stack;
};
#pragma pack(pop)


typedef void __fastcall (__closure *TDynamicInvokeEvent)(PParameters Params, int StackSize);

//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
static const System::Word paEAX = System::Word(0x0);
static const System::Word paEDX = System::Word(0x1);
static const System::Word paECX = System::Word(0x2);
static const System::Word paStack = System::Word(0x3);
extern DELPHI_PACKAGE bool RaiseExceptionForExtendedType;
#endif /* not _WIN64 */
extern DELPHI_PACKAGE TMethodInfoArray __fastcall GetMethods(System::TClass ClassType);
extern DELPHI_PACKAGE PMethodInfoHeader __fastcall GetMethodInfo(System::TObject* Instance, const System::UnicodeString MethodName)/* overload */;
extern DELPHI_PACKAGE PMethodInfoHeader __fastcall GetMethodInfo _DEPRECATED_ATTRIBUTE1("use String version of GetMethodInfo instead of ShortString version.") (System::TObject* Instance, const System::ShortString &MethodName)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall ObjectInvoke(System::TObject* Instance, PMethodInfoHeader MethodHeader, const int *ParamIndexes, const int ParamIndexes_High, const System::Variant *Params, const int Params_High);
extern DELPHI_PACKAGE System::TMethod __fastcall CreateMethodPointer(const _di_IMethodHandler MethodHandler, System::Typinfo::PTypeData TypeData)/* overload */;
extern DELPHI_PACKAGE System::TMethod __fastcall CreateMethodPointer(const TDynamicInvokeEvent ADynamicInvokeEvent, System::Typinfo::PTypeData TypeData)/* overload */;
extern DELPHI_PACKAGE void __fastcall ReleaseMethodPointer(const System::TMethod &MethodPointer);
extern DELPHI_PACKAGE System::TObject* __fastcall GetInvokeInstance(const System::TMethod &MethodPointer);
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
