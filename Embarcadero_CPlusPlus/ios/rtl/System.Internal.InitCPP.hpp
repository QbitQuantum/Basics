// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Internal.InitCPP.pas' rev: 34.00 (iOS)

#ifndef System_Internal_InitcppHPP
#define System_Internal_InitcppHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Internal
{
namespace Initcpp
{
//-- forward type declarations -----------------------------------------------
struct TUnitDescriptor;
//-- type declarations -------------------------------------------------------
typedef TUnitDescriptor *PUnitDescriptor;

typedef PUnitDescriptor *PPUnitDescriptor;

typedef void __fastcall (*TUnitInitProc)(PUnitDescriptor desc);

typedef void __fastcall (*TUnitFiniProc)(PUnitDescriptor desc);

typedef System::PPointer PClassCtorDtorProc;

struct DECLSPEC_DRECORD TUnitDescriptor
{
public:
	System::WideChar *UnitName;
	TUnitInitProc InitProc;
	TUnitFiniProc FiniProc;
	System::Word Flags;
	int RefCount;
	PUnitDescriptor *InterfaceUnits;
	PUnitDescriptor *ImplementationUnits;
	void * *ClassCtors;
	void * *ClassDtors;
	TUnitDescriptor *SiblingLink;
	int Degree;
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 F_UNIT_MARKED = System::Int8(0x1);
extern DELPHI_PACKAGE void __fastcall InitializeUnits(PUnitDescriptor StartDesc, PUnitDescriptor EndDesc);
extern DELPHI_PACKAGE void __fastcall FinalizeUnits(PUnitDescriptor StartDesc, PUnitDescriptor EndDesc);
extern DELPHI_PACKAGE void __fastcall CalculateDegree(PUnitDescriptor StartDesc, PUnitDescriptor EndDesc);
extern DELPHI_PACKAGE void __fastcall InitializeRootUnit(PUnitDescriptor Root);
extern DELPHI_PACKAGE void __fastcall FinalizeRootUnit(PUnitDescriptor Root);
}	/* namespace Initcpp */
}	/* namespace Internal */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Internal_InitcppHPP
