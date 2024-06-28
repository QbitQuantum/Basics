// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Internal.DebugUtils.pas' rev: 34.00 (Android)

#ifndef System_Internal_DebugutilsHPP
#define System_Internal_DebugutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Internal
{
namespace Debugutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDebugUtils;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDebugUtils : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::UnicodeString EnvSeparator;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,bool>* EnabledConditionMap;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,bool>* UnenabledConditionMap;
	static System::TArray__1<System::UnicodeString> DEBUG_CLASS;
	__classmethod void __fastcall ParseEnv(System::UnicodeString Env);
	__classmethod bool __fastcall SubMatch(System::UnicodeString Cond, System::UnicodeString Category);
	__classmethod bool __fastcall Match(System::UnicodeString Cond);
	__classmethod bool __fastcall CheckDebugClass(System::UnicodeString Cond);
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
public:
	__classmethod void __fastcall DebugPrint(System::UnicodeString Cond, System::UnicodeString Fmt, const System::TVarRec *Args, const int Args_High)/* overload */;
	__classmethod void __fastcall DebugPrint(System::UnicodeString Cond, System::UnicodeString Fmt)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDebugUtils() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDebugUtils() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Debugutils */
}	/* namespace Internal */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_INTERNAL_DEBUGUTILS)
using namespace System::Internal::Debugutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_INTERNAL)
using namespace System::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Internal_DebugutilsHPP
