// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPMidas.pas' rev: 34.00 (Android)

#ifndef Soap_SoapmidasHPP
#define Soap_SoapmidasHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Datasnap.Midas.hpp>
#include <Soap.InvokeRegistry.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapmidas
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAppServerSOAP;
typedef System::DelphiInterface<IAppServerSOAP> _di_IAppServerSOAP;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{C99F4735-D6D2-495C-8CA2-E53E5A439E61}") IAppServerSOAP  : public System::IInvokable 
{
	virtual System::OleVariant __stdcall SAS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData) = 0 ;
	virtual System::OleVariant __stdcall SAS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData) = 0 ;
	virtual System::OleVariant __stdcall SAS_DataRequest(const System::WideString ProviderName, System::OleVariant Data) = 0 ;
	virtual System::TArray__1<System::WideString> __stdcall SAS_GetProviderNames() = 0 ;
	virtual System::OleVariant __stdcall SAS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData) = 0 ;
	virtual System::OleVariant __stdcall SAS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData) = 0 ;
	virtual void __stdcall SAS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegDefIAppServerInvClass(void);
}	/* namespace Soapmidas */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPMIDAS)
using namespace Soap::Soapmidas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapmidasHPP
