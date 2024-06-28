// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TestModules.pas' rev: 34.00 (Windows)

#ifndef TestmodulesHPP
#define TestmodulesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <TestFramework.hpp>
#include <DUnitConsts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Testmodules
{
//-- forward type declarations -----------------------------------------------
struct TModuleRecord;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TModuleRecord
{
public:
	NativeUInt Handle;
	Testframework::_di_ITest Test;
};


typedef Testframework::_di_ITest __fastcall (*TGetTestFunc)(void);

typedef System::DynamicArray<TModuleRecord> Testmodules__1;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
extern DELPHI_PACKAGE Testmodules__1 __Modules;
extern DELPHI_PACKAGE Testframework::_di_ITest __fastcall LoadModuleTests(System::UnicodeString LibName);
extern DELPHI_PACKAGE void __fastcall RegisterModuleTests(System::UnicodeString LibName);
extern DELPHI_PACKAGE void __fastcall UnloadTestModules(void);
}	/* namespace Testmodules */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_TESTMODULES)
using namespace Testmodules;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TestmodulesHPP
