// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.WebUI.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_WebuiHPP
#define Winapi_Ui_WebuiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Webui
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ActivatedEventHandler;
typedef System::DelphiInterface<ActivatedEventHandler> _di_ActivatedEventHandler;
__interface DELPHIINTERFACE ResumingEventHandler;
typedef System::DelphiInterface<ResumingEventHandler> _di_ResumingEventHandler;
//-- type declarations -------------------------------------------------------
typedef _di_ActivatedEventHandler *PActivatedEventHandler;

typedef _di_ResumingEventHandler *PResumingEventHandler;

__interface  INTERFACE_UUID("{50F1E730-C5D1-4B6B-9ADB-8A11756BE29C}") ActivatedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_Activation_IActivatedEventArgs eventArgs) = 0 ;
};

__interface  INTERFACE_UUID("{26599BA9-A22D-4806-A728-ACADC1D075FA}") ResumingEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Webui */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_WebuiHPP
