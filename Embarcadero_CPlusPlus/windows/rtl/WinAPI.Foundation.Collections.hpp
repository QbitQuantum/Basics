// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Foundation.Collections.pas' rev: 34.00 (Windows)

#ifndef Winapi_Foundation_CollectionsHPP
#define Winapi_Foundation_CollectionsHPP

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
#include <Winapi.SystemRT.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Foundation
{
namespace Collections
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPropertySet;
class DELPHICLASS TValueSet;
class DELPHICLASS TStringMap;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPropertySet : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TPropertySet() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPropertySet() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TValueSet : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TValueSet() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueSet() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStringMap : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TStringMap() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStringMap() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Collections */
}	/* namespace Foundation */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Foundation_CollectionsHPP
