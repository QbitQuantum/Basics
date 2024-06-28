// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Midas.pas' rev: 34.00 (iOS)

#ifndef Datasnap_MidasHPP
#define Datasnap_MidasHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Midas
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAppServer;
typedef System::DelphiInterface<IAppServer> _di_IAppServer;
__dispinterface IAppServerDisp;
typedef System::DelphiInterface<IAppServerDisp> _di_IAppServerDisp;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}") IAppServer  : public System::IDispatch 
{
	virtual HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result) = 0 ;
	virtual HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result) = 0 ;
	virtual HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result) = 0 ;
	virtual HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result) = 0 ;
	virtual HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result) = 0 ;
	virtual HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result) = 0 ;
	virtual HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData) = 0 ;
};

__dispinterface  INTERFACE_UUID("{1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}") IAppServerDisp  : public System::IDispatch 
{
	
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE GUID LIBID_Midas;
extern DELPHI_PACKAGE GUID IID_IAppServer;
}	/* namespace Midas */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_MIDAS)
using namespace Datasnap::Midas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_MidasHPP
