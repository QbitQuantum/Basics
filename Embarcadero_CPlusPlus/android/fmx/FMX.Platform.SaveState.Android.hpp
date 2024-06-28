// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.SaveState.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Savestate_AndroidHPP
#define Fmx_Platform_Savestate_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Platform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Savestate
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidSaveStateService;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidSaveStateService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FSaveStateStoragePath;
	
protected:
	virtual void __fastcall RegisterService();
	virtual void __fastcall UnregisterService();
	
public:
	__fastcall TAndroidSaveStateService();
	__fastcall virtual ~TAndroidSaveStateService();
	bool __fastcall GetBlock(const System::UnicodeString ABlockName, System::Classes::TStream* const ABlockData);
	bool __fastcall SetBlock(const System::UnicodeString ABlockName, System::Classes::TStream* const ABlockData);
	System::UnicodeString __fastcall GetStoragePath();
	void __fastcall SetStoragePath(const System::UnicodeString ANewPath);
	bool __fastcall GetNotifications();
private:
	void *__IFMXSaveStateService;	// Fmx::Platform::IFMXSaveStateService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {34CB784A-E262-4E2C-B3B6-C3A41B722D7A}
	operator Fmx::Platform::_di_IFMXSaveStateService()
	{
		Fmx::Platform::_di_IFMXSaveStateService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXSaveStateService*(void) { return (Fmx::Platform::IFMXSaveStateService*)&__IFMXSaveStateService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Savestate */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_SAVESTATE_ANDROID)
using namespace Fmx::Platform::Savestate::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_SAVESTATE)
using namespace Fmx::Platform::Savestate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_Savestate_AndroidHPP
