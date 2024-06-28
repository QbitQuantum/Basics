// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.LoggingService.pas' rev: 34.00 (Windows)

#ifndef Emshosting_LoggingserviceHPP
#define Emshosting_LoggingserviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <EMS.Services.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.LoggingService"

namespace Emshosting
{
namespace Loggingservice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSLoggingService;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSLoggingService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Classes::TStreamWriter* FWriter;
	bool FLogIsEmpty;
	Ems::Services::_di_TEMSLoggingOutputProc FOutputProc;
	System::DelphiInterface<System::Sysutils::TFunc__1<bool> > FEnabledFunc;
	bool FSynchronize;
	
public:
	__fastcall virtual ~TEMSLoggingService();
	bool __fastcall GetLoggingEnabled();
	void __fastcall Log(const System::UnicodeString ACategory, System::Json::TJSONObject* const AJSON);
	void __fastcall SetupCustomOutput(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > AEnabled, const Ems::Services::_di_TEMSLoggingOutputProc AOutput, const bool ASynchronize);
	void __fastcall SetupFileOutput(const System::UnicodeString AFileName, const bool AAppend);
public:
	/* TObject.Create */ inline __fastcall TEMSLoggingService() : System::TInterfacedObject() { }
	
private:
	void *__IEMSLoggingService;	// Ems::Services::IEMSLoggingService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {261E2580-D991-4E1B-9FFF-D68EBD2DEB6F}
	operator Ems::Services::_di_IEMSLoggingService()
	{
		Ems::Services::_di_IEMSLoggingService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Ems::Services::IEMSLoggingService*(void) { return (Ems::Services::IEMSLoggingService*)&__IEMSLoggingService; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Loggingservice */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_LOGGINGSERVICE)
using namespace Emshosting::Loggingservice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_LoggingserviceHPP
