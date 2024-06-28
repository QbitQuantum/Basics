// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Logger.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Platform_Logger_IosHPP
#define Fmx_Platform_Logger_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Platform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Logger
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCocoaTouchLoggerService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCocoaTouchLoggerService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	void __fastcall RegisterService();
	void __fastcall UnregisterService();
	
public:
	__fastcall TCocoaTouchLoggerService();
	__fastcall virtual ~TCocoaTouchLoggerService();
	void __fastcall Log(const System::UnicodeString AFormat, const System::TVarRec *AParams, const int AParams_High);
private:
	void *__IFMXLoggingService;	// Fmx::Platform::IFMXLoggingService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {01BFC200-0493-4B3B-9D7E-E3CDB1242795}
	operator Fmx::Platform::_di_IFMXLoggingService()
	{
		Fmx::Platform::_di_IFMXLoggingService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXLoggingService*(void) { return (Fmx::Platform::IFMXLoggingService*)&__IFMXLoggingService; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Logger */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_LOGGER_IOS)
using namespace Fmx::Platform::Logger::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_LOGGER)
using namespace Fmx::Platform::Logger;
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
#endif	// Fmx_Platform_Logger_IosHPP
