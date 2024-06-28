// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Enumeration.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_EnumerationHPP
#define Winapi_Devices_EnumerationHPP

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
#include <Winapi.ApplicationModel.Background.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Enumeration
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDeviceAccessChangedEventArgs;
typedef System::DelphiInterface<IDeviceAccessChangedEventArgs> _di_IDeviceAccessChangedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs> _di_TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs;
__interface DELPHIINTERFACE IDeviceAccessInformation;
typedef System::DelphiInterface<IDeviceAccessInformation> _di_IDeviceAccessInformation;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DeviceAccessStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DeviceAccessStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DeviceAccessStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DeviceAccessStatus> _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__DeviceAccessStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__DeviceAccessStatus_Base> _di_IAsyncOperation_1__DeviceAccessStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__DeviceAccessStatus;
typedef System::DelphiInterface<IAsyncOperation_1__DeviceAccessStatus> _di_IAsyncOperation_1__DeviceAccessStatus;
__interface DELPHIINTERFACE IIterator_1__DeviceClass_Base;
typedef System::DelphiInterface<IIterator_1__DeviceClass_Base> _di_IIterator_1__DeviceClass_Base;
__interface DELPHIINTERFACE IIterator_1__DeviceClass;
typedef System::DelphiInterface<IIterator_1__DeviceClass> _di_IIterator_1__DeviceClass;
__interface DELPHIINTERFACE IIterable_1__DeviceClass_Base;
typedef System::DelphiInterface<IIterable_1__DeviceClass_Base> _di_IIterable_1__DeviceClass_Base;
__interface DELPHIINTERFACE IIterable_1__DeviceClass;
typedef System::DelphiInterface<IIterable_1__DeviceClass> _di_IIterable_1__DeviceClass;
__interface DELPHIINTERFACE IEnclosureLocation2;
typedef System::DelphiInterface<IEnclosureLocation2> _di_IEnclosureLocation2;
__interface DELPHIINTERFACE IDeviceInformationUpdate2;
typedef System::DelphiInterface<IDeviceInformationUpdate2> _di_IDeviceInformationUpdate2;
__interface DELPHIINTERFACE IIterator_1__DeviceWatcherEventKind_Base;
typedef System::DelphiInterface<IIterator_1__DeviceWatcherEventKind_Base> _di_IIterator_1__DeviceWatcherEventKind_Base;
__interface DELPHIINTERFACE IIterator_1__DeviceWatcherEventKind;
typedef System::DelphiInterface<IIterator_1__DeviceWatcherEventKind> _di_IIterator_1__DeviceWatcherEventKind;
__interface DELPHIINTERFACE IIterable_1__DeviceWatcherEventKind_Base;
typedef System::DelphiInterface<IIterable_1__DeviceWatcherEventKind_Base> _di_IIterable_1__DeviceWatcherEventKind_Base;
__interface DELPHIINTERFACE IIterable_1__DeviceWatcherEventKind;
typedef System::DelphiInterface<IIterable_1__DeviceWatcherEventKind> _di_IIterable_1__DeviceWatcherEventKind;
__interface DELPHIINTERFACE IDeviceWatcher2;
typedef System::DelphiInterface<IDeviceWatcher2> _di_IDeviceWatcher2;
__interface DELPHIINTERFACE IIterator_1__IDeviceInformation_Base;
typedef System::DelphiInterface<IIterator_1__IDeviceInformation_Base> _di_IIterator_1__IDeviceInformation_Base;
__interface DELPHIINTERFACE IIterator_1__IDeviceInformation;
typedef System::DelphiInterface<IIterator_1__IDeviceInformation> _di_IIterator_1__IDeviceInformation;
__interface DELPHIINTERFACE IIterable_1__IDeviceInformation_Base;
typedef System::DelphiInterface<IIterable_1__IDeviceInformation_Base> _di_IIterable_1__IDeviceInformation_Base;
__interface DELPHIINTERFACE IIterable_1__IDeviceInformation;
typedef System::DelphiInterface<IIterable_1__IDeviceInformation> _di_IIterable_1__IDeviceInformation;
__interface DELPHIINTERFACE IVectorView_1__IDeviceInformation;
typedef System::DelphiInterface<IVectorView_1__IDeviceInformation> _di_IVectorView_1__IDeviceInformation;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IDeviceInformation_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IDeviceInformation_Base> _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IDeviceInformation;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IDeviceInformation> _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation;
__interface DELPHIINTERFACE IDeviceInformationStatics;
typedef System::DelphiInterface<IDeviceInformationStatics> _di_IDeviceInformationStatics;
__interface DELPHIINTERFACE IDeviceInformationStatics2;
typedef System::DelphiInterface<IDeviceInformationStatics2> _di_IDeviceInformationStatics2;
__interface DELPHIINTERFACE IDevicePairingResult;
typedef System::DelphiInterface<IDevicePairingResult> _di_IDevicePairingResult;
__interface DELPHIINTERFACE IDeviceUnpairingResult;
typedef System::DelphiInterface<IDeviceUnpairingResult> _di_IDeviceUnpairingResult;
__interface DELPHIINTERFACE IDevicePairingSettings;
typedef System::DelphiInterface<IDevicePairingSettings> _di_IDevicePairingSettings;
__interface DELPHIINTERFACE IDevicePairingRequestedEventArgs;
typedef System::DelphiInterface<IDevicePairingRequestedEventArgs> _di_IDevicePairingRequestedEventArgs;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDevicePairingResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDevicePairingResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IDevicePairingResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDevicePairingResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDevicePairingResult> _di_AsyncOperationCompletedHandler_1__IDevicePairingResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IDevicePairingResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IDevicePairingResult_Base> _di_IAsyncOperation_1__IDevicePairingResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IDevicePairingResult;
typedef System::DelphiInterface<IAsyncOperation_1__IDevicePairingResult> _di_IAsyncOperation_1__IDevicePairingResult;
__interface DELPHIINTERFACE TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs> _di_TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs;
__interface DELPHIINTERFACE IDeviceInformationCustomPairing;
typedef System::DelphiInterface<IDeviceInformationCustomPairing> _di_IDeviceInformationCustomPairing;
__interface DELPHIINTERFACE IDeviceInformationPairing;
typedef System::DelphiInterface<IDeviceInformationPairing> _di_IDeviceInformationPairing;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDeviceUnpairingResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDeviceUnpairingResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDeviceUnpairingResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDeviceUnpairingResult> _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IDeviceUnpairingResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IDeviceUnpairingResult_Base> _di_IAsyncOperation_1__IDeviceUnpairingResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IDeviceUnpairingResult;
typedef System::DelphiInterface<IAsyncOperation_1__IDeviceUnpairingResult> _di_IAsyncOperation_1__IDeviceUnpairingResult;
__interface DELPHIINTERFACE IDeviceInformationPairing2;
typedef System::DelphiInterface<IDeviceInformationPairing2> _di_IDeviceInformationPairing2;
__interface DELPHIINTERFACE IDeviceInformationPairingStatics;
typedef System::DelphiInterface<IDeviceInformationPairingStatics> _di_IDeviceInformationPairingStatics;
__interface DELPHIINTERFACE IDeviceInformation2;
typedef System::DelphiInterface<IDeviceInformation2> _di_IDeviceInformation2;
__interface DELPHIINTERFACE IDeviceAccessChangedEventArgs2;
typedef System::DelphiInterface<IDeviceAccessChangedEventArgs2> _di_IDeviceAccessChangedEventArgs2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Pnp_IPnpObject_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Pnp_IPnpObject_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Pnp_IPnpObject;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Pnp_IPnpObject> _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE IAsyncOperation_1__Pnp_IPnpObject_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Pnp_IPnpObject_Base> _di_IAsyncOperation_1__Pnp_IPnpObject_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Pnp_IPnpObject;
typedef System::DelphiInterface<IAsyncOperation_1__Pnp_IPnpObject> _di_IAsyncOperation_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE IIterator_1__Pnp_IPnpObject_Base;
typedef System::DelphiInterface<IIterator_1__Pnp_IPnpObject_Base> _di_IIterator_1__Pnp_IPnpObject_Base;
__interface DELPHIINTERFACE IIterator_1__Pnp_IPnpObject;
typedef System::DelphiInterface<IIterator_1__Pnp_IPnpObject> _di_IIterator_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE IIterable_1__Pnp_IPnpObject_Base;
typedef System::DelphiInterface<IIterable_1__Pnp_IPnpObject_Base> _di_IIterable_1__Pnp_IPnpObject_Base;
__interface DELPHIINTERFACE IIterable_1__Pnp_IPnpObject;
typedef System::DelphiInterface<IIterable_1__Pnp_IPnpObject> _di_IIterable_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE IVectorView_1__Pnp_IPnpObject;
typedef System::DelphiInterface<IVectorView_1__Pnp_IPnpObject> _di_IVectorView_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject_Base> _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject> _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject;
__interface DELPHIINTERFACE Pnp_IPnpObjectStatics;
typedef System::DelphiInterface<Pnp_IPnpObjectStatics> _di_Pnp_IPnpObjectStatics;
class DELPHICLASS TDevicePicker;
class DELPHICLASS TDeviceInformation;
class DELPHICLASS TDeviceInformationPairing;
class DELPHICLASS TPnp_PnpObject;
//-- type declarations -------------------------------------------------------
typedef _di_IDeviceAccessChangedEventArgs *PIDeviceAccessChangedEventArgs;

typedef _di_TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs *PTypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs;

typedef _di_IDeviceAccessInformation *PIDeviceAccessInformation;

typedef _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus *PAsyncOperationCompletedHandler_1__DeviceAccessStatus;

typedef _di_IAsyncOperation_1__DeviceAccessStatus *PIAsyncOperation_1__DeviceAccessStatus;

typedef _di_IIterator_1__DeviceClass *PIIterator_1__DeviceClass;

typedef _di_IIterable_1__DeviceClass *PIIterable_1__DeviceClass;

typedef _di_IEnclosureLocation2 *PIEnclosureLocation2;

typedef _di_IDeviceInformationUpdate2 *PIDeviceInformationUpdate2;

typedef _di_IIterator_1__DeviceWatcherEventKind *PIIterator_1__DeviceWatcherEventKind;

typedef _di_IIterable_1__DeviceWatcherEventKind *PIIterable_1__DeviceWatcherEventKind;

typedef _di_IDeviceWatcher2 *PIDeviceWatcher2;

typedef _di_IIterator_1__IDeviceInformation *PIIterator_1__IDeviceInformation;

typedef _di_IIterable_1__IDeviceInformation *PIIterable_1__IDeviceInformation;

typedef _di_IVectorView_1__IDeviceInformation *PIVectorView_1__IDeviceInformation;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation *PAsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation;

typedef _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation *PIAsyncOperation_1__IVectorView_1__IDeviceInformation;

typedef _di_IDeviceInformationStatics *PIDeviceInformationStatics;

typedef _di_IDeviceInformationStatics2 *PIDeviceInformationStatics2;

typedef _di_IDevicePairingResult *PIDevicePairingResult;

typedef _di_IDeviceUnpairingResult *PIDeviceUnpairingResult;

typedef _di_IDevicePairingSettings *PIDevicePairingSettings;

typedef _di_IDevicePairingRequestedEventArgs *PIDevicePairingRequestedEventArgs;

typedef _di_AsyncOperationCompletedHandler_1__IDevicePairingResult *PAsyncOperationCompletedHandler_1__IDevicePairingResult;

typedef _di_IAsyncOperation_1__IDevicePairingResult *PIAsyncOperation_1__IDevicePairingResult;

typedef _di_TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs *PTypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs;

typedef _di_IDeviceInformationCustomPairing *PIDeviceInformationCustomPairing;

typedef _di_IDeviceInformationPairing *PIDeviceInformationPairing;

typedef _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult *PAsyncOperationCompletedHandler_1__IDeviceUnpairingResult;

typedef _di_IAsyncOperation_1__IDeviceUnpairingResult *PIAsyncOperation_1__IDeviceUnpairingResult;

typedef _di_IDeviceInformationPairing2 *PIDeviceInformationPairing2;

typedef _di_IDeviceInformationPairingStatics *PIDeviceInformationPairingStatics;

typedef _di_IDeviceInformation2 *PIDeviceInformation2;

typedef _di_IDeviceAccessChangedEventArgs2 *PIDeviceAccessChangedEventArgs2;

typedef _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject *PAsyncOperationCompletedHandler_1__Pnp_IPnpObject;

typedef _di_IAsyncOperation_1__Pnp_IPnpObject *PIAsyncOperation_1__Pnp_IPnpObject;

typedef _di_IIterator_1__Pnp_IPnpObject *PIIterator_1__Pnp_IPnpObject;

typedef _di_IIterable_1__Pnp_IPnpObject *PIIterable_1__Pnp_IPnpObject;

typedef _di_IVectorView_1__Pnp_IPnpObject *PIVectorView_1__Pnp_IPnpObject;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject *PAsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject;

typedef _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject *PIAsyncOperation_1__IVectorView_1__Pnp_IPnpObject;

typedef _di_Pnp_IPnpObjectStatics *PPnp_IPnpObjectStatics;

__interface  INTERFACE_UUID("{DEDA0BCC-4F9D-4F58-9DBA-A9BC800408D5}") IDeviceAccessChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::DeviceAccessStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceAccessStatus _scw_get_Status() { Winapi::Commontypes::DeviceAccessStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceAccessStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{4C71D028-B793-5BCE-AE59-FA77F45A40D8}") TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6A7B811E-C5D4-55BB-BB7B-99CAA2F420E2}") TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs  : public TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDeviceAccessInformation sender, _di_IDeviceAccessChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{0BAA9A73-6DE5-4915-8DDD-9A0554A6F545}") IDeviceAccessInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_AccessChanged(_di_TypedEventHandler_2__IDeviceAccessInformation__IDeviceAccessChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_AccessChanged_result) = 0 ;
	virtual HRESULT __safecall remove_AccessChanged(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall get_CurrentStatus(Winapi::Commontypes::DeviceAccessStatus &__get_CurrentStatus_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceAccessStatus _scw_get_CurrentStatus() { Winapi::Commontypes::DeviceAccessStatus __r; HRESULT __hr = get_CurrentStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceAccessStatus CurrentStatus = {read=_scw_get_CurrentStatus};
};

__interface  INTERFACE_UUID("{EE154D83-805B-53E8-8469-90715036D013}") AsyncOperationCompletedHandler_1__DeviceAccessStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__DeviceAccessStatus  : public AsyncOperationCompletedHandler_1__DeviceAccessStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__DeviceAccessStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{C00BC2F2-A7F8-5F3F-80D1-2808EF6BCA10}") IAsyncOperation_1__DeviceAccessStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__DeviceAccessStatus  : public IAsyncOperation_1__DeviceAccessStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__DeviceAccessStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__DeviceAccessStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::DeviceAccessStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__DeviceAccessStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C3807283-1416-593C-955C-0B4A286FF7BB}") IIterator_1__DeviceClass_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__DeviceClass  : public IIterator_1__DeviceClass_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::DeviceClass &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PDeviceClass items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceClass _scw_get_Current() { Winapi::Commontypes::DeviceClass __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceClass Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{47D4BE05-58F1-522E-81C6-975EB4131BB9}") IIterable_1__DeviceClass_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__DeviceClass  : public IIterable_1__DeviceClass_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__DeviceClass &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2885995B-E07D-485D-8A9E-BDF29AEF4F66}") IEnclosureLocation2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RotationAngleInDegreesClockwise(unsigned &__get_RotationAngleInDegreesClockwise_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_RotationAngleInDegreesClockwise() { unsigned __r; HRESULT __hr = get_RotationAngleInDegreesClockwise(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned RotationAngleInDegreesClockwise = {read=_scw_get_RotationAngleInDegreesClockwise};
};

__interface  INTERFACE_UUID("{5D9D148C-A873-485E-BAA6-AA620788E3CC}") IDeviceInformationUpdate2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Kind(Winapi::Commontypes::DeviceInformationKind &__get_Kind_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceInformationKind _scw_get_Kind() { Winapi::Commontypes::DeviceInformationKind __r; HRESULT __hr = get_Kind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceInformationKind Kind = {read=_scw_get_Kind};
};

__interface  INTERFACE_UUID("{CB5CA9DB-CCD6-5103-A93D-C925C908838D}") IIterator_1__DeviceWatcherEventKind_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__DeviceWatcherEventKind  : public IIterator_1__DeviceWatcherEventKind_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::DeviceWatcherEventKind &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PDeviceWatcherEventKind items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceWatcherEventKind _scw_get_Current() { Winapi::Commontypes::DeviceWatcherEventKind __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceWatcherEventKind Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{F04365AB-D3F3-5F85-A7DA-DC19CFF73D86}") IIterable_1__DeviceWatcherEventKind_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__DeviceWatcherEventKind  : public IIterable_1__DeviceWatcherEventKind_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__DeviceWatcherEventKind &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{FF08456E-ED14-49E9-9A69-8117C54AE971}") IDeviceWatcher2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetBackgroundTrigger(_di_IIterable_1__DeviceWatcherEventKind requestedEventKinds, Winapi::Winrt::_di_IInspectable &__GetBackgroundTrigger_result) = 0 ;
};

__interface  INTERFACE_UUID("{6F85D843-E8AB-5B46-85D7-327C58D18712}") IIterator_1__IDeviceInformation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F06491A0-6D3D-5A38-B164-AEE6E5B0326C}") IIterator_1__IDeviceInformation  : public IIterator_1__IDeviceInformation_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IDeviceInformation &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIDeviceInformation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDeviceInformation _scw_get_Current() { Winapi::Commontypes::_di_IDeviceInformation __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDeviceInformation Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{DD9F8A5D-EC98-5F4B-A3EA-9C8B5AD53C4B}") IIterable_1__IDeviceInformation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{180E4B06-9936-5D42-A5BF-1BDC08713DBD}") IIterable_1__IDeviceInformation  : public IIterable_1__IDeviceInformation_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IDeviceInformation &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{717AA701-AB02-5C8D-AD35-EE564CF8BB0E}") IVectorView_1__IDeviceInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IDeviceInformation &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IDeviceInformation value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIDeviceInformation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{4A458732-527E-5C73-9A68-A73DA370F782}") AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E2375529-DAC5-52E8-B1DE-7AAE0A9202CC}") AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation  : public AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IDeviceInformation asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{45180254-082E-5274-B2E7-AC0517F44D07}") IAsyncOperation_1__IVectorView_1__IDeviceInformation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{42F4622B-7AB2-59F9-8C91-8235DC44E8F4}") IAsyncOperation_1__IVectorView_1__IDeviceInformation  : public IAsyncOperation_1__IVectorView_1__IDeviceInformation_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IDeviceInformation &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IDeviceInformation Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C17F100E-3A46-4A78-8013-769DC9B97390}") IDeviceInformationStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFromIdAsync(HSTRING deviceId, Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation &__CreateFromIdAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateFromIdAsync(HSTRING deviceId, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation &__CreateFromIdAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall FindAllAsync(_di_IAsyncOperation_1__IVectorView_1__IDeviceInformation &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall FindAllAsync(Winapi::Commontypes::DeviceClass deviceClass, _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall FindAllAsync(HSTRING aqsFilter, _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall FindAllAsync(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(Winapi::Commontypes::_di_IDeviceWatcher &__CreateWatcher_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(Winapi::Commontypes::DeviceClass deviceClass, Winapi::Commontypes::_di_IDeviceWatcher &__CreateWatcher_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(HSTRING aqsFilter, Winapi::Commontypes::_di_IDeviceWatcher &__CreateWatcher_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::_di_IDeviceWatcher &__CreateWatcher_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{493B4F34-A84F-45FD-9167-15D1CB1BD1F9}") IDeviceInformationStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAqsFilterFromDeviceClass(Winapi::Commontypes::DeviceClass deviceClass, HSTRING &__GetAqsFilterFromDeviceClass_result) = 0 ;
	virtual HRESULT __safecall CreateFromIdAsync(HSTRING deviceId, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind, Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation &__CreateFromIdAsync_result) = 0 ;
	virtual HRESULT __safecall FindAllAsync(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind, _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation &__FindAllAsync_result) = 0 ;
	virtual HRESULT __safecall CreateWatcher(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind, Winapi::Commontypes::_di_IDeviceWatcher &__CreateWatcher_result) = 0 ;
};

__interface  INTERFACE_UUID("{072B02BF-DD95-4025-9B37-DE51ADBA37B7}") IDevicePairingResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::DevicePairingResultStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_ProtectionLevelUsed(Winapi::Commontypes::DevicePairingProtectionLevel &__get_ProtectionLevelUsed_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DevicePairingProtectionLevel _scw_get_ProtectionLevelUsed() { Winapi::Commontypes::DevicePairingProtectionLevel __r; HRESULT __hr = get_ProtectionLevelUsed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DevicePairingProtectionLevel ProtectionLevelUsed = {read=_scw_get_ProtectionLevelUsed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DevicePairingResultStatus _scw_get_Status() { Winapi::Commontypes::DevicePairingResultStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DevicePairingResultStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{66F44AD3-79D9-444B-92CF-A92EF72571C7}") IDeviceUnpairingResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::DeviceUnpairingResultStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceUnpairingResultStatus _scw_get_Status() { Winapi::Commontypes::DeviceUnpairingResultStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceUnpairingResultStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{482CB27C-83BB-420E-BE51-6602B222DE54}") IDevicePairingSettings  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F717FC56-DE6B-487F-8376-0180ACA69963}") IDevicePairingRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceInformation(Winapi::Commontypes::_di_IDeviceInformation &__get_DeviceInformation_result) = 0 ;
	virtual HRESULT __safecall get_PairingKind(Winapi::Commontypes::DevicePairingKinds &__get_PairingKind_result) = 0 ;
	virtual HRESULT __safecall get_Pin(HSTRING &__get_Pin_result) = 0 ;
	virtual HRESULT __safecall Accept() = 0 /* overload */;
	virtual HRESULT __safecall Accept(HSTRING pin) = 0 /* overload */;
	virtual HRESULT __safecall GetDeferral(Winapi::Commontypes::_di_IDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDeviceInformation _scw_get_DeviceInformation() { Winapi::Commontypes::_di_IDeviceInformation __r; HRESULT __hr = get_DeviceInformation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDeviceInformation DeviceInformation = {read=_scw_get_DeviceInformation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DevicePairingKinds _scw_get_PairingKind() { Winapi::Commontypes::DevicePairingKinds __r; HRESULT __hr = get_PairingKind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DevicePairingKinds PairingKind = {read=_scw_get_PairingKind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Pin() { HSTRING __r; HRESULT __hr = get_Pin(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Pin = {read=_scw_get_Pin};
};

__interface  INTERFACE_UUID("{7EE0247F-5F57-5CB2-B40E-18B5A211D6C3}") AsyncOperationCompletedHandler_1__IDevicePairingResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{FEE5AE5D-187F-56A3-AFD2-3C5ABCCCBE14}") AsyncOperationCompletedHandler_1__IDevicePairingResult  : public AsyncOperationCompletedHandler_1__IDevicePairingResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IDevicePairingResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{1002DB74-8948-591E-815D-E40B667599A3}") IAsyncOperation_1__IDevicePairingResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{529C658D-8499-557A-A110-7634DDC46275}") IAsyncOperation_1__IDevicePairingResult  : public IAsyncOperation_1__IDevicePairingResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IDevicePairingResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IDevicePairingResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IDevicePairingResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IDevicePairingResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IDevicePairingResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IDevicePairingResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{FA65231F-4178-5DE1-B2CC-03E22D7702B4}") TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{09195B85-D449-5DF4-AE79-5919FDCB9DED}") TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs  : public TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDeviceInformationCustomPairing sender, _di_IDevicePairingRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{85138C02-4EE6-4914-8370-107A39144C0E}") IDeviceInformationCustomPairing  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall PairAsync(Winapi::Commontypes::DevicePairingKinds pairingKindsSupported, _di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall PairAsync(Winapi::Commontypes::DevicePairingKinds pairingKindsSupported, Winapi::Commontypes::DevicePairingProtectionLevel minProtectionLevel, _di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall PairAsync(Winapi::Commontypes::DevicePairingKinds pairingKindsSupported, Winapi::Commontypes::DevicePairingProtectionLevel minProtectionLevel, _di_IDevicePairingSettings devicePairingSettings, _di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall add_PairingRequested(_di_TypedEventHandler_2__IDeviceInformationCustomPairing__IDevicePairingRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_PairingRequested_result) = 0 ;
	virtual HRESULT __safecall remove_PairingRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{2C4769F5-F684-40D5-8469-E8DBAAB70485}") IDeviceInformationPairing  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsPaired(bool &__get_IsPaired_result) = 0 ;
	virtual HRESULT __safecall get_CanPair(bool &__get_CanPair_result) = 0 ;
	virtual HRESULT __safecall PairAsync(_di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall PairAsync(Winapi::Commontypes::DevicePairingProtectionLevel minProtectionLevel, _di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanPair() { bool __r; HRESULT __hr = get_CanPair(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanPair = {read=_scw_get_CanPair};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPaired() { bool __r; HRESULT __hr = get_IsPaired(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPaired = {read=_scw_get_IsPaired};
};

__interface  INTERFACE_UUID("{9BBE6EB9-DB2D-5160-A20C-F0C265F20D8E}") AsyncOperationCompletedHandler_1__IDeviceUnpairingResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{32DA3AD5-F202-544C-94F8-2BC574BE3DA8}") AsyncOperationCompletedHandler_1__IDeviceUnpairingResult  : public AsyncOperationCompletedHandler_1__IDeviceUnpairingResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IDeviceUnpairingResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2BB4DF3D-BD7E-5FE0-9020-56DC0D30B935}") IAsyncOperation_1__IDeviceUnpairingResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{27C0B299-384A-5783-8DC1-60C21161FABB}") IAsyncOperation_1__IDeviceUnpairingResult  : public IAsyncOperation_1__IDeviceUnpairingResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IDeviceUnpairingResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IDeviceUnpairingResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{F68612FD-0AEE-4328-85CC-1C742BB1790D}") IDeviceInformationPairing2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ProtectionLevel(Winapi::Commontypes::DevicePairingProtectionLevel &__get_ProtectionLevel_result) = 0 ;
	virtual HRESULT __safecall get_Custom(_di_IDeviceInformationCustomPairing &__get_Custom_result) = 0 ;
	virtual HRESULT __safecall PairAsync(Winapi::Commontypes::DevicePairingProtectionLevel minProtectionLevel, _di_IDevicePairingSettings devicePairingSettings, _di_IAsyncOperation_1__IDevicePairingResult &__PairAsync_result) = 0 ;
	virtual HRESULT __safecall UnpairAsync(_di_IAsyncOperation_1__IDeviceUnpairingResult &__UnpairAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDeviceInformationCustomPairing _scw_get_Custom() { _di_IDeviceInformationCustomPairing __r; HRESULT __hr = get_Custom(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDeviceInformationCustomPairing Custom = {read=_scw_get_Custom};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DevicePairingProtectionLevel _scw_get_ProtectionLevel() { Winapi::Commontypes::DevicePairingProtectionLevel __r; HRESULT __hr = get_ProtectionLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DevicePairingProtectionLevel ProtectionLevel = {read=_scw_get_ProtectionLevel};
};

__interface  INTERFACE_UUID("{E915C408-36D4-49A1-BF13-514173799B6B}") IDeviceInformationPairingStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall TryRegisterForAllInboundPairingRequests(Winapi::Commontypes::DevicePairingKinds pairingKindsSupported, bool &__TryRegisterForAllInboundPairingRequests_result) = 0 ;
};

__interface  INTERFACE_UUID("{F156A638-7997-48D9-A10C-269D46533F48}") IDeviceInformation2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Kind(Winapi::Commontypes::DeviceInformationKind &__get_Kind_result) = 0 ;
	virtual HRESULT __safecall get_Pairing(_di_IDeviceInformationPairing &__get_Pairing_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DeviceInformationKind _scw_get_Kind() { Winapi::Commontypes::DeviceInformationKind __r; HRESULT __hr = get_Kind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DeviceInformationKind Kind = {read=_scw_get_Kind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDeviceInformationPairing _scw_get_Pairing() { _di_IDeviceInformationPairing __r; HRESULT __hr = get_Pairing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDeviceInformationPairing Pairing = {read=_scw_get_Pairing};
};

__interface  INTERFACE_UUID("{82523262-934B-4B30-A178-ADC39F2F2BE3}") IDeviceAccessChangedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
};

__interface  INTERFACE_UUID("{9D615463-6879-521F-8E97-E66D3DDBC95E}") AsyncOperationCompletedHandler_1__Pnp_IPnpObject_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{863BDB04-0585-5767-A64A-B247CE04BE47}") AsyncOperationCompletedHandler_1__Pnp_IPnpObject  : public AsyncOperationCompletedHandler_1__Pnp_IPnpObject_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Pnp_IPnpObject asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{22B0FB93-30E6-501A-BD3B-9FA3063E9C16}") IAsyncOperation_1__Pnp_IPnpObject_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DCC6CC16-85D7-5A00-8E63-9BC7075C0B08}") IAsyncOperation_1__Pnp_IPnpObject  : public IAsyncOperation_1__Pnp_IPnpObject_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_Pnp_IPnpObject &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Pnp_IPnpObject Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{6BB6D2F1-B5FB-57F0-8251-F20CDE5A6871}") IIterator_1__Pnp_IPnpObject_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DEA7DBDA-BCCA-58DD-96FB-3FBEA7FAF5D8}") IIterator_1__Pnp_IPnpObject  : public IIterator_1__Pnp_IPnpObject_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_Pnp_IPnpObject &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PPnp_IPnpObject items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_Pnp_IPnpObject _scw_get_Current() { Winapi::Commontypes::_di_Pnp_IPnpObject __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_Pnp_IPnpObject Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{30B50092-36EE-53FF-9450-029004436C60}") IIterable_1__Pnp_IPnpObject_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{17677D16-E3DB-51B9-AF2E-D4EDFB202D13}") IIterable_1__Pnp_IPnpObject  : public IIterable_1__Pnp_IPnpObject_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Pnp_IPnpObject &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{5B091106-8910-5FE6-8C50-A27C65BD860C}") IVectorView_1__Pnp_IPnpObject  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_Pnp_IPnpObject &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_Pnp_IPnpObject value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PPnp_IPnpObject items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{811D834C-A15E-5522-B7F4-E53004FC58FF}") AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{43B26CAC-1267-5096-A034-0C4142CDEDF6}") AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject  : public AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{F383C2CC-F326-5BBE-95D1-CBC24714EF86}") IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E4B7CC1B-E86A-53BF-9BD8-D0505EAA62A5}") IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject  : public IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__Pnp_IPnpObject &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__Pnp_IPnpObject Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{B3C32A3D-D168-4660-BBF3-A733B14B6E01}") Pnp_IPnpObjectStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFromIdAsync(Winapi::Commontypes::Pnp_PnpObjectType type, HSTRING id, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, _di_IAsyncOperation_1__Pnp_IPnpObject &__CreateFromIdAsync_result) = 0 ;
	virtual HRESULT __safecall FindAllAsync(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall FindAllAsync(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, HSTRING aqsFilter, _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject &__FindAllAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, Winapi::Commontypes::_di_Pnp_IPnpObjectWatcher &__CreateWatcher_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateWatcher(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, HSTRING aqsFilter, Winapi::Commontypes::_di_Pnp_IPnpObjectWatcher &__CreateWatcher_result) = 0 /* overload */;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDevicePicker : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDevicePicker>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDevicePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDevicePicker() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDevicePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDevicePicker() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDeviceInformation : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_IDeviceInformationStatics,_di_IDeviceInformationStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_IDeviceInformationStatics,_di_IDeviceInformationStatics2> inherited;
	
public:
	static HSTRING __fastcall GetAqsFilterFromDeviceClass(Winapi::Commontypes::DeviceClass deviceClass);
	static Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation __fastcall CreateFromIdAsync(HSTRING deviceId, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation __fastcall FindAllAsync(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind)/* overload */;
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall CreateWatcher(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties, Winapi::Commontypes::DeviceInformationKind kind)/* overload */;
	static Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation __fastcall CreateFromIdAsync(HSTRING deviceId)/* overload */;
	static Winapi::Commontypes::_di_IAsyncOperation_1__IDeviceInformation __fastcall CreateFromIdAsync(HSTRING deviceId, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation __fastcall FindAllAsync()/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation __fastcall FindAllAsync(Winapi::Commontypes::DeviceClass deviceClass)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation __fastcall FindAllAsync(HSTRING aqsFilter)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IDeviceInformation __fastcall FindAllAsync(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties)/* overload */;
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall CreateWatcher()/* overload */;
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall CreateWatcher(Winapi::Commontypes::DeviceClass deviceClass)/* overload */;
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall CreateWatcher(HSTRING aqsFilter)/* overload */;
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall CreateWatcher(HSTRING aqsFilter, Winapi::Commontypes::_di_IIterable_1__HSTRING additionalProperties)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDeviceInformation() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_IDeviceInformationStatics,_di_IDeviceInformationStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDeviceInformation() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDeviceInformationPairing : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IDeviceInformationPairingStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IDeviceInformationPairingStatics> inherited;
	
public:
	static bool __fastcall TryRegisterForAllInboundPairingRequests(Winapi::Commontypes::DevicePairingKinds pairingKindsSupported);
public:
	/* TObject.Create */ inline __fastcall TDeviceInformationPairing() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IDeviceInformationPairingStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDeviceInformationPairing() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPnp_PnpObject : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Pnp_IPnpObjectStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Pnp_IPnpObjectStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__Pnp_IPnpObject __fastcall CreateFromIdAsync(Winapi::Commontypes::Pnp_PnpObjectType type, HSTRING id, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties);
	static _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject __fastcall FindAllAsync(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__Pnp_IPnpObject __fastcall FindAllAsync(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, HSTRING aqsFilter)/* overload */;
	static Winapi::Commontypes::_di_Pnp_IPnpObjectWatcher __fastcall CreateWatcher(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties)/* overload */;
	static Winapi::Commontypes::_di_Pnp_IPnpObjectWatcher __fastcall CreateWatcher(Winapi::Commontypes::Pnp_PnpObjectType type, Winapi::Commontypes::_di_IIterable_1__HSTRING requestedProperties, HSTRING aqsFilter)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TPnp_PnpObject() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Pnp_IPnpObjectStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPnp_PnpObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Enumeration */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_EnumerationHPP
