// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ApplicationModel.Background.pas' rev: 34.00 (Windows)

#ifndef Winapi_Applicationmodel_BackgroundHPP
#define Winapi_Applicationmodel_BackgroundHPP

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
namespace Applicationmodel
{
namespace Background
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__BackgroundAccessStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__BackgroundAccessStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__BackgroundAccessStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__BackgroundAccessStatus> _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__BackgroundAccessStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__BackgroundAccessStatus_Base> _di_IAsyncOperation_1__BackgroundAccessStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__BackgroundAccessStatus;
typedef System::DelphiInterface<IAsyncOperation_1__BackgroundAccessStatus> _di_IAsyncOperation_1__BackgroundAccessStatus;
__interface DELPHIINTERFACE IBackgroundTaskInstance2;
typedef System::DelphiInterface<IBackgroundTaskInstance2> _di_IBackgroundTaskInstance2;
__interface DELPHIINTERFACE IBackgroundTaskInstance4;
typedef System::DelphiInterface<IBackgroundTaskInstance4> _di_IBackgroundTaskInstance4;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ApplicationTriggerResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ApplicationTriggerResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ApplicationTriggerResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ApplicationTriggerResult> _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult;
__interface DELPHIINTERFACE IAsyncOperation_1__ApplicationTriggerResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ApplicationTriggerResult_Base> _di_IAsyncOperation_1__ApplicationTriggerResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ApplicationTriggerResult;
typedef System::DelphiInterface<IAsyncOperation_1__ApplicationTriggerResult> _di_IAsyncOperation_1__ApplicationTriggerResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult> _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult;
__interface DELPHIINTERFACE IAsyncOperation_1__MediaProcessingTriggerResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__MediaProcessingTriggerResult_Base> _di_IAsyncOperation_1__MediaProcessingTriggerResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__MediaProcessingTriggerResult;
typedef System::DelphiInterface<IAsyncOperation_1__MediaProcessingTriggerResult> _di_IAsyncOperation_1__MediaProcessingTriggerResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DeviceTriggerResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DeviceTriggerResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DeviceTriggerResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DeviceTriggerResult> _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult;
__interface DELPHIINTERFACE IAsyncOperation_1__DeviceTriggerResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__DeviceTriggerResult_Base> _di_IAsyncOperation_1__DeviceTriggerResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__DeviceTriggerResult;
typedef System::DelphiInterface<IAsyncOperation_1__DeviceTriggerResult> _di_IAsyncOperation_1__DeviceTriggerResult;
__interface DELPHIINTERFACE IDeviceWatcherTrigger;
typedef System::DelphiInterface<IDeviceWatcherTrigger> _di_IDeviceWatcherTrigger;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__AlarmAccessStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__AlarmAccessStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__AlarmAccessStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__AlarmAccessStatus> _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__AlarmAccessStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__AlarmAccessStatus_Base> _di_IAsyncOperation_1__AlarmAccessStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__AlarmAccessStatus;
typedef System::DelphiInterface<IAsyncOperation_1__AlarmAccessStatus> _di_IAsyncOperation_1__AlarmAccessStatus;
//-- type declarations -------------------------------------------------------
typedef _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus *PAsyncOperationCompletedHandler_1__BackgroundAccessStatus;

typedef _di_IAsyncOperation_1__BackgroundAccessStatus *PIAsyncOperation_1__BackgroundAccessStatus;

typedef _di_IBackgroundTaskInstance2 *PIBackgroundTaskInstance2;

typedef _di_IBackgroundTaskInstance4 *PIBackgroundTaskInstance4;

typedef _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult *PAsyncOperationCompletedHandler_1__ApplicationTriggerResult;

typedef _di_IAsyncOperation_1__ApplicationTriggerResult *PIAsyncOperation_1__ApplicationTriggerResult;

typedef _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult *PAsyncOperationCompletedHandler_1__MediaProcessingTriggerResult;

typedef _di_IAsyncOperation_1__MediaProcessingTriggerResult *PIAsyncOperation_1__MediaProcessingTriggerResult;

typedef _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult *PAsyncOperationCompletedHandler_1__DeviceTriggerResult;

typedef _di_IAsyncOperation_1__DeviceTriggerResult *PIAsyncOperation_1__DeviceTriggerResult;

typedef _di_IDeviceWatcherTrigger *PIDeviceWatcherTrigger;

typedef _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus *PAsyncOperationCompletedHandler_1__AlarmAccessStatus;

typedef _di_IAsyncOperation_1__AlarmAccessStatus *PIAsyncOperation_1__AlarmAccessStatus;

__interface  INTERFACE_UUID("{26DD26E3-3F47-5709-B2F2-D6D0AD3288F0}") AsyncOperationCompletedHandler_1__BackgroundAccessStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__BackgroundAccessStatus  : public AsyncOperationCompletedHandler_1__BackgroundAccessStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__BackgroundAccessStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{7B44E581-CFA9-5763-BED7-6A65739F0DBF}") IAsyncOperation_1__BackgroundAccessStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__BackgroundAccessStatus  : public IAsyncOperation_1__BackgroundAccessStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::BackgroundAccessStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__BackgroundAccessStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{4F7D0176-0C76-4FB4-896D-5DE1864122F6}") IBackgroundTaskInstance2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetThrottleCount(Winapi::Commontypes::BackgroundTaskThrottleCounter counter, unsigned &__GetThrottleCount_result) = 0 ;
};

__interface  INTERFACE_UUID("{7F29F23C-AA04-4B08-97B0-06D874CDABF5}") IBackgroundTaskInstance4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_User(Winapi::Commontypes::_di_IUser &__get_User_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUser _scw_get_User() { Winapi::Commontypes::_di_IUser __r; HRESULT __hr = get_User(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUser User = {read=_scw_get_User};
};

__interface  INTERFACE_UUID("{D0065EF6-EE9D-55F8-AC2B-53A91FF96D2E}") AsyncOperationCompletedHandler_1__ApplicationTriggerResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__ApplicationTriggerResult  : public AsyncOperationCompletedHandler_1__ApplicationTriggerResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ApplicationTriggerResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{47CBD985-0F08-5A3D-92CF-B27960506ED6}") IAsyncOperation_1__ApplicationTriggerResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__ApplicationTriggerResult  : public IAsyncOperation_1__ApplicationTriggerResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::ApplicationTriggerResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ApplicationTriggerResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{3814C6A5-2AD1-5875-BED5-5031CD1F50A2}") AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult  : public AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__MediaProcessingTriggerResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2595482C-1CBF-5691-A30D-2164909C6712}") IAsyncOperation_1__MediaProcessingTriggerResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__MediaProcessingTriggerResult  : public IAsyncOperation_1__MediaProcessingTriggerResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::MediaProcessingTriggerResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__MediaProcessingTriggerResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{D5AA9506-1464-57D4-859D-7EE9B26CB1F9}") AsyncOperationCompletedHandler_1__DeviceTriggerResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__DeviceTriggerResult  : public AsyncOperationCompletedHandler_1__DeviceTriggerResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__DeviceTriggerResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B5136C46-2F2E-511D-9E8E-5EF4DECB1DA7}") IAsyncOperation_1__DeviceTriggerResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__DeviceTriggerResult  : public IAsyncOperation_1__DeviceTriggerResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__DeviceTriggerResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__DeviceTriggerResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::DeviceTriggerResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__DeviceTriggerResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{A4617FDD-8573-4260-BEFC-5BEC89CB693D}") IDeviceWatcherTrigger  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{84108017-A8E7-5449-B713-DF48503A953E}") AsyncOperationCompletedHandler_1__AlarmAccessStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__AlarmAccessStatus  : public AsyncOperationCompletedHandler_1__AlarmAccessStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__AlarmAccessStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{A55A747D-59F6-5CB6-B439-C8AAD670905C}") IAsyncOperation_1__AlarmAccessStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__AlarmAccessStatus  : public IAsyncOperation_1__AlarmAccessStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__AlarmAccessStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__AlarmAccessStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::AlarmAccessStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__AlarmAccessStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Background */
}	/* namespace Applicationmodel */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Applicationmodel_BackgroundHPP
