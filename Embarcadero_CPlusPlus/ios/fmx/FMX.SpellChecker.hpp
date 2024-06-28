// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.SpellChecker.pas' rev: 34.00 (iOS)

#ifndef Fmx_SpellcheckerHPP
#define Fmx_SpellcheckerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Spellchecker
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXSpellCheckerService;
typedef System::DelphiInterface<IFMXSpellCheckerService> _di_IFMXSpellCheckerService;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{A956ACEC-9CFA-4FEC-B631-A1AEB2FAAA79}") IFMXSpellCheckerService  : public System::IInterface 
{
	virtual System::TArray__1<System::UnicodeString> __fastcall CheckSpelling(System::UnicodeString Word) = 0 ;
	virtual System::TArray__1<System::UnicodeString> __fastcall GuessCompletions(System::UnicodeString Word) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Spellchecker */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SPELLCHECKER)
using namespace Fmx::Spellchecker;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_SpellcheckerHPP
