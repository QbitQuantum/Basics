// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Networking.Vpn.pas' rev: 34.00 (Windows)

#ifndef Winapi_Networking_VpnHPP
#define Winapi_Networking_VpnHPP

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
namespace Networking
{
namespace Vpn
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__VpnManagementErrorStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__VpnManagementErrorStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__VpnManagementErrorStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__VpnManagementErrorStatus> _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__VpnManagementErrorStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__VpnManagementErrorStatus_Base> _di_IAsyncOperation_1__VpnManagementErrorStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__VpnManagementErrorStatus;
typedef System::DelphiInterface<IAsyncOperation_1__VpnManagementErrorStatus> _di_IAsyncOperation_1__VpnManagementErrorStatus;
//-- type declarations -------------------------------------------------------
typedef _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus *PAsyncOperationCompletedHandler_1__VpnManagementErrorStatus;

typedef _di_IAsyncOperation_1__VpnManagementErrorStatus *PIAsyncOperation_1__VpnManagementErrorStatus;

__interface  INTERFACE_UUID("{31229F8C-709D-5017-8629-57EF1289E616}") AsyncOperationCompletedHandler_1__VpnManagementErrorStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__VpnManagementErrorStatus  : public AsyncOperationCompletedHandler_1__VpnManagementErrorStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__VpnManagementErrorStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{E99B86DC-6B65-5F23-9419-90B55852F283}") IAsyncOperation_1__VpnManagementErrorStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__VpnManagementErrorStatus  : public IAsyncOperation_1__VpnManagementErrorStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::VpnManagementErrorStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__VpnManagementErrorStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Vpn */
}	/* namespace Networking */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Networking_VpnHPP
