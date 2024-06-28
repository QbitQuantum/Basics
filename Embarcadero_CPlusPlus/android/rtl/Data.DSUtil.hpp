// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DSUtil.pas' rev: 34.00 (Android)

#ifndef Data_DsutilHPP
#define Data_DsutilHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dsutil
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall StrListToVarArray(const System::UnicodeString StrList, /* out */ System::OleVariant &VarArray);
extern DELPHI_PACKAGE void __fastcall VarArrayToStrings(const System::OleVariant &VarData, System::Classes::TStrings* List);
extern DELPHI_PACKAGE void __fastcall VariantToStream(const System::OleVariant &VariantValue, System::Classes::TStream* const Stream);
extern DELPHI_PACKAGE void __fastcall StreamToVariant(System::Classes::TStream* const Stream, /* out */ System::OleVariant &VariantValue);
}	/* namespace Dsutil */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DSUTIL)
using namespace Data::Dsutil;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DsutilHPP
