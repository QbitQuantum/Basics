// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.Helpers.pas' rev: 34.00 (iOS)

#ifndef Iosapi_HelpersHPP
#define Iosapi_HelpersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Helpers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TiOSHelper;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TiOSHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Iosapi::Uikit::_di_UIScreen FCachedScreen;
	static Iosapi::Foundation::_di_NSNotificationCenter FCachedDefaultNotificationCenter;
	static Iosapi::Uikit::_di_UIDevice FCachedCurrentDevice;
	static Iosapi::Foundation::_di_NSBundle FCachedBundle;
	
public:
	__classmethod Iosapi::Uikit::_di_UIApplication __fastcall SharedApplication();
	__classmethod Iosapi::Uikit::_di_UIScreen __fastcall MainScreen();
	__classmethod Iosapi::Foundation::_di_NSBundle __fastcall MainBundle();
	__classmethod Iosapi::Foundation::_di_NSNotificationCenter __fastcall DefaultNotificationCenter();
	__classmethod Iosapi::Uikit::_di_UIDevice __fastcall CurrentDevice();
	__classmethod bool __fastcall HasBackgroundMode(const System::UnicodeString AMode);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TiOSHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TiOSHelper() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Helpers */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_HELPERS)
using namespace Iosapi::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_HelpersHPP
