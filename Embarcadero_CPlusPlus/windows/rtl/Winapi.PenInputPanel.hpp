// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.PenInputPanel.pas' rev: 34.00 (Windows)

#ifndef Winapi_PeninputpanelHPP
#define Winapi_PeninputpanelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.MsInkAut.hpp>

//-- user supplied -----------------------------------------------------------

#include "peninputpanel.h"

DECLARE_DINTERFACE_TYPE(IPenInputPanel);
DECLARE_DINTERFACE_TYPE(IHandwrittenTextInsertion);
DECLARE_DINTERFACE_TYPE(ITextInputPanelEventSink);
DECLARE_DINTERFACE_TYPE(ITextInputPanel);
DECLARE_DINTERFACE_TYPE(IInputPanelWindowHandle);
DECLARE_DINTERFACE_TYPE(ITextInputPanelRunInfo);

namespace Winapi
{
namespace Peninputpanel
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const System::Int8 PenInputPanelLibMajorVersion = System::Int8(0x1);
static const System::Int8 PenInputPanelLibMinorVersion = System::Int8(0x0);
extern DELPHI_PACKAGE GUID LIBID_PenInputPanelLib;
}	/* namespace Peninputpanel */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_PENINPUTPANEL)
using namespace Winapi::Peninputpanel;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_PeninputpanelHPP
