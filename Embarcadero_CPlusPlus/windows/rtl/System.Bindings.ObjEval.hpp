// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.ObjEval.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_ObjevalHPP
#define System_Bindings_ObjevalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <System.Rtti.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Bindings.EvalProtocol.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Objeval
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall (*IsProxyClassProc)(System::TClass ClassType);
extern DELPHI_PACKAGE System::Bindings::Evalprotocol::_di_IScope __fastcall WrapObject(System::TObject* AObject);
}	/* namespace Objeval */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_OBJEVAL)
using namespace System::Bindings::Objeval;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS)
using namespace System::Bindings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Bindings_ObjevalHPP
