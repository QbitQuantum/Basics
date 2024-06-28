// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Mtx.pas' rev: 34.00 (Windows)

#ifndef Winapi_MtxHPP
#define Winapi_MtxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <comsvcs.h>
DECLARE_DINTERFACE_TYPE(ITransactionContext);
DECLARE_DINTERFACE_TYPE(ITransactionContextEx);
DECLARE_DINTERFACE_TYPE(ISharedPropertyGroupManager);
DECLARE_DINTERFACE_TYPE(ISharedPropertyGroup);
DECLARE_DINTERFACE_TYPE(IObjectContext);
DECLARE_DINTERFACE_TYPE(IObjectControl);

namespace Winapi
{
namespace Mtx
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE _di_ITransactionContext __fastcall CreateTransactionContext(void);
extern DELPHI_PACKAGE _di_ITransactionContextEx __fastcall CreateTransactionContextEx(void);
extern DELPHI_PACKAGE _di_ISharedPropertyGroupManager __fastcall CreateSharedPropertyGroupManager(void);
extern DELPHI_PACKAGE _di_ISharedPropertyGroup __fastcall CreateSharedPropertyGroup(const System::WideString Name);
}	/* namespace Mtx */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MTX)
using namespace Winapi::Mtx;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MtxHPP
