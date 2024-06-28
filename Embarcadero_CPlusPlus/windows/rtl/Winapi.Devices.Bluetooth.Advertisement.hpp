// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Bluetooth.Advertisement.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_Bluetooth_AdvertisementHPP
#define Winapi_Devices_Bluetooth_AdvertisementHPP

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
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.Devices.Bluetooth.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Bluetooth
{
namespace Advertisement
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IReference_1__BluetoothLEAdvertisementFlags;
typedef System::DelphiInterface<IReference_1__BluetoothLEAdvertisementFlags> _di_IReference_1__BluetoothLEAdvertisementFlags;
__interface DELPHIINTERFACE IBluetoothLEManufacturerData;
typedef System::DelphiInterface<IBluetoothLEManufacturerData> _di_IBluetoothLEManufacturerData;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEManufacturerData_Base;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEManufacturerData_Base> _di_IIterator_1__IBluetoothLEManufacturerData_Base;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEManufacturerData;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEManufacturerData> _di_IIterator_1__IBluetoothLEManufacturerData;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEManufacturerData_Base;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEManufacturerData_Base> _di_IIterable_1__IBluetoothLEManufacturerData_Base;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEManufacturerData;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEManufacturerData> _di_IIterable_1__IBluetoothLEManufacturerData;
__interface DELPHIINTERFACE IVectorView_1__IBluetoothLEManufacturerData;
typedef System::DelphiInterface<IVectorView_1__IBluetoothLEManufacturerData> _di_IVectorView_1__IBluetoothLEManufacturerData;
__interface DELPHIINTERFACE IVector_1__IBluetoothLEManufacturerData;
typedef System::DelphiInterface<IVector_1__IBluetoothLEManufacturerData> _di_IVector_1__IBluetoothLEManufacturerData;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementDataSection;
typedef System::DelphiInterface<IBluetoothLEAdvertisementDataSection> _di_IBluetoothLEAdvertisementDataSection;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementDataSection_Base;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementDataSection_Base> _di_IIterator_1__IBluetoothLEAdvertisementDataSection_Base;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementDataSection;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementDataSection> _di_IIterator_1__IBluetoothLEAdvertisementDataSection;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementDataSection_Base;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementDataSection_Base> _di_IIterable_1__IBluetoothLEAdvertisementDataSection_Base;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementDataSection;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementDataSection> _di_IIterable_1__IBluetoothLEAdvertisementDataSection;
__interface DELPHIINTERFACE IVectorView_1__IBluetoothLEAdvertisementDataSection;
typedef System::DelphiInterface<IVectorView_1__IBluetoothLEAdvertisementDataSection> _di_IVectorView_1__IBluetoothLEAdvertisementDataSection;
__interface DELPHIINTERFACE IVector_1__IBluetoothLEAdvertisementDataSection;
typedef System::DelphiInterface<IVector_1__IBluetoothLEAdvertisementDataSection> _di_IVector_1__IBluetoothLEAdvertisementDataSection;
__interface DELPHIINTERFACE IBluetoothLEAdvertisement;
typedef System::DelphiInterface<IBluetoothLEAdvertisement> _di_IBluetoothLEAdvertisement;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementBytePattern;
typedef System::DelphiInterface<IBluetoothLEAdvertisementBytePattern> _di_IBluetoothLEAdvertisementBytePattern;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementBytePattern_Base;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementBytePattern_Base> _di_IIterator_1__IBluetoothLEAdvertisementBytePattern_Base;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementBytePattern;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementBytePattern> _di_IIterator_1__IBluetoothLEAdvertisementBytePattern;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementBytePattern_Base;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementBytePattern_Base> _di_IIterable_1__IBluetoothLEAdvertisementBytePattern_Base;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementBytePattern;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementBytePattern> _di_IIterable_1__IBluetoothLEAdvertisementBytePattern;
__interface DELPHIINTERFACE IVectorView_1__IBluetoothLEAdvertisementBytePattern;
typedef System::DelphiInterface<IVectorView_1__IBluetoothLEAdvertisementBytePattern> _di_IVectorView_1__IBluetoothLEAdvertisementBytePattern;
__interface DELPHIINTERFACE IVector_1__IBluetoothLEAdvertisementBytePattern;
typedef System::DelphiInterface<IVector_1__IBluetoothLEAdvertisementBytePattern> _di_IVector_1__IBluetoothLEAdvertisementBytePattern;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementFilter;
typedef System::DelphiInterface<IBluetoothLEAdvertisementFilter> _di_IBluetoothLEAdvertisementFilter;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementWatcherStoppedEventArgs;
typedef System::DelphiInterface<IBluetoothLEAdvertisementWatcherStoppedEventArgs> _di_IBluetoothLEAdvertisementWatcherStoppedEventArgs;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementReceivedEventArgs;
typedef System::DelphiInterface<IBluetoothLEAdvertisementReceivedEventArgs> _di_IBluetoothLEAdvertisementReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs> _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs> _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementWatcher;
typedef System::DelphiInterface<IBluetoothLEAdvertisementWatcher> _di_IBluetoothLEAdvertisementWatcher;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementWatcherFactory;
typedef System::DelphiInterface<IBluetoothLEAdvertisementWatcherFactory> _di_IBluetoothLEAdvertisementWatcherFactory;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementDataSectionFactory;
typedef System::DelphiInterface<IBluetoothLEAdvertisementDataSectionFactory> _di_IBluetoothLEAdvertisementDataSectionFactory;
__interface DELPHIINTERFACE IBluetoothLEManufacturerDataFactory;
typedef System::DelphiInterface<IBluetoothLEManufacturerDataFactory> _di_IBluetoothLEManufacturerDataFactory;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementBytePatternFactory;
typedef System::DelphiInterface<IBluetoothLEAdvertisementBytePatternFactory> _di_IBluetoothLEAdvertisementBytePatternFactory;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementDataTypesStatics;
typedef System::DelphiInterface<IBluetoothLEAdvertisementDataTypesStatics> _di_IBluetoothLEAdvertisementDataTypesStatics;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementPublisherStatusChangedEventArgs;
typedef System::DelphiInterface<IBluetoothLEAdvertisementPublisherStatusChangedEventArgs> _di_IBluetoothLEAdvertisementPublisherStatusChangedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs> _di_TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementPublisher;
typedef System::DelphiInterface<IBluetoothLEAdvertisementPublisher> _di_IBluetoothLEAdvertisementPublisher;
__interface DELPHIINTERFACE IBluetoothLEAdvertisementPublisherFactory;
typedef System::DelphiInterface<IBluetoothLEAdvertisementPublisherFactory> _di_IBluetoothLEAdvertisementPublisherFactory;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs_Base;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs_Base> _di_IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs_Base;
__interface DELPHIINTERFACE IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs;
typedef System::DelphiInterface<IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs> _di_IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs_Base;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs_Base> _di_IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs_Base;
__interface DELPHIINTERFACE IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs;
typedef System::DelphiInterface<IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs> _di_IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs;
__interface DELPHIINTERFACE IVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs;
typedef System::DelphiInterface<IVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs> _di_IVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs;
class DELPHICLASS TBluetoothLEManufacturerData;
class DELPHICLASS TBluetoothLEAdvertisementDataSection;
class DELPHICLASS TBluetoothLEAdvertisement;
class DELPHICLASS TBluetoothLEAdvertisementBytePattern;
class DELPHICLASS TBluetoothLEAdvertisementFilter;
class DELPHICLASS TBluetoothLEAdvertisementWatcher;
class DELPHICLASS TBluetoothLEAdvertisementDataTypes;
class DELPHICLASS TBluetoothLEAdvertisementPublisher;
//-- type declarations -------------------------------------------------------
typedef _di_IReference_1__BluetoothLEAdvertisementFlags *PIReference_1__BluetoothLEAdvertisementFlags;

typedef _di_IBluetoothLEManufacturerData *PIBluetoothLEManufacturerData;

typedef _di_IIterator_1__IBluetoothLEManufacturerData *PIIterator_1__IBluetoothLEManufacturerData;

typedef _di_IIterable_1__IBluetoothLEManufacturerData *PIIterable_1__IBluetoothLEManufacturerData;

typedef _di_IVectorView_1__IBluetoothLEManufacturerData *PIVectorView_1__IBluetoothLEManufacturerData;

typedef _di_IVector_1__IBluetoothLEManufacturerData *PIVector_1__IBluetoothLEManufacturerData;

typedef _di_IBluetoothLEAdvertisementDataSection *PIBluetoothLEAdvertisementDataSection;

typedef _di_IIterator_1__IBluetoothLEAdvertisementDataSection *PIIterator_1__IBluetoothLEAdvertisementDataSection;

typedef _di_IIterable_1__IBluetoothLEAdvertisementDataSection *PIIterable_1__IBluetoothLEAdvertisementDataSection;

typedef _di_IVectorView_1__IBluetoothLEAdvertisementDataSection *PIVectorView_1__IBluetoothLEAdvertisementDataSection;

typedef _di_IVector_1__IBluetoothLEAdvertisementDataSection *PIVector_1__IBluetoothLEAdvertisementDataSection;

typedef _di_IBluetoothLEAdvertisement *PIBluetoothLEAdvertisement;

typedef _di_IBluetoothLEAdvertisementBytePattern *PIBluetoothLEAdvertisementBytePattern;

typedef _di_IIterator_1__IBluetoothLEAdvertisementBytePattern *PIIterator_1__IBluetoothLEAdvertisementBytePattern;

typedef _di_IIterable_1__IBluetoothLEAdvertisementBytePattern *PIIterable_1__IBluetoothLEAdvertisementBytePattern;

typedef _di_IVectorView_1__IBluetoothLEAdvertisementBytePattern *PIVectorView_1__IBluetoothLEAdvertisementBytePattern;

typedef _di_IVector_1__IBluetoothLEAdvertisementBytePattern *PIVector_1__IBluetoothLEAdvertisementBytePattern;

typedef _di_IBluetoothLEAdvertisementFilter *PIBluetoothLEAdvertisementFilter;

typedef _di_IBluetoothLEAdvertisementWatcherStoppedEventArgs *PIBluetoothLEAdvertisementWatcherStoppedEventArgs;

typedef _di_IBluetoothLEAdvertisementReceivedEventArgs *PIBluetoothLEAdvertisementReceivedEventArgs;

typedef _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs *PTypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs;

typedef _di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs *PTypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs;

typedef _di_IBluetoothLEAdvertisementWatcher *PIBluetoothLEAdvertisementWatcher;

typedef _di_IBluetoothLEAdvertisementWatcherFactory *PIBluetoothLEAdvertisementWatcherFactory;

typedef _di_IBluetoothLEAdvertisementDataSectionFactory *PIBluetoothLEAdvertisementDataSectionFactory;

typedef _di_IBluetoothLEManufacturerDataFactory *PIBluetoothLEManufacturerDataFactory;

typedef _di_IBluetoothLEAdvertisementBytePatternFactory *PIBluetoothLEAdvertisementBytePatternFactory;

typedef _di_IBluetoothLEAdvertisementDataTypesStatics *PIBluetoothLEAdvertisementDataTypesStatics;

typedef _di_IBluetoothLEAdvertisementPublisherStatusChangedEventArgs *PIBluetoothLEAdvertisementPublisherStatusChangedEventArgs;

typedef _di_TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs *PTypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs;

typedef _di_IBluetoothLEAdvertisementPublisher *PIBluetoothLEAdvertisementPublisher;

typedef _di_IBluetoothLEAdvertisementPublisherFactory *PIBluetoothLEAdvertisementPublisherFactory;

typedef _di_IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs *PIIterator_1__IBluetoothLEAdvertisementReceivedEventArgs;

typedef _di_IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs *PIIterable_1__IBluetoothLEAdvertisementReceivedEventArgs;

typedef _di_IVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs *PIVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs;

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__BluetoothLEAdvertisementFlags  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::BluetoothLEAdvertisementFlags &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEAdvertisementFlags _scw_get_Value() { Winapi::Commontypes::BluetoothLEAdvertisementFlags __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEAdvertisementFlags Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{912DBA18-6963-4533-B061-4694DAFB34E5}") IBluetoothLEManufacturerData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CompanyId(System::Word &__get_CompanyId_result) = 0 ;
	virtual HRESULT __safecall put_CompanyId(System::Word value) = 0 ;
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IBuffer &__get_Data_result) = 0 ;
	virtual HRESULT __safecall put_Data(Winapi::Commontypes::_di_IBuffer value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_CompanyId() { System::Word __r; HRESULT __hr = get_CompanyId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word CompanyId = {read=_scw_get_CompanyId, write=put_CompanyId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Data() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Data = {read=_scw_get_Data, write=put_Data};
};

__interface  INTERFACE_UUID("{12F158DD-7016-5338-AC5C-7D5503D73274}") IIterator_1__IBluetoothLEManufacturerData_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1AFC1F61-BE0F-5D68-A1B5-002CA2D6339F}") IIterator_1__IBluetoothLEManufacturerData  : public IIterator_1__IBluetoothLEManufacturerData_Base 
{
	virtual HRESULT __safecall get_Current(_di_IBluetoothLEManufacturerData &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIBluetoothLEManufacturerData items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEManufacturerData _scw_get_Current() { _di_IBluetoothLEManufacturerData __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEManufacturerData Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{834A4CAC-BB8B-5F0F-9F28-4DBC98C17907}") IIterable_1__IBluetoothLEManufacturerData_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BB452D0A-A575-5A1A-B77F-4938C6FF9A09}") IIterable_1__IBluetoothLEManufacturerData  : public IIterable_1__IBluetoothLEManufacturerData_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IBluetoothLEManufacturerData &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{362D1A87-BBD6-5B43-A0B8-139A1F132948}") IVectorView_1__IBluetoothLEManufacturerData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEManufacturerData &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEManufacturerData value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEManufacturerData items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A18B4E27-ABEE-502A-B326-87787C366F13}") IVector_1__IBluetoothLEManufacturerData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEManufacturerData &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IBluetoothLEManufacturerData &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEManufacturerData value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IBluetoothLEManufacturerData value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IBluetoothLEManufacturerData value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IBluetoothLEManufacturerData value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEManufacturerData items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIBluetoothLEManufacturerData items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{D7213314-3A43-40F9-B6F0-92BFEFC34AE3}") IBluetoothLEAdvertisementDataSection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DataType(System::Byte &__get_DataType_result) = 0 ;
	virtual HRESULT __safecall put_DataType(System::Byte value) = 0 ;
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IBuffer &__get_Data_result) = 0 ;
	virtual HRESULT __safecall put_Data(Winapi::Commontypes::_di_IBuffer value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Data() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Data = {read=_scw_get_Data, write=put_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_DataType() { System::Byte __r; HRESULT __hr = get_DataType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte DataType = {read=_scw_get_DataType, write=put_DataType};
};

__interface  INTERFACE_UUID("{AF5C0E81-788B-52D4-82A2-1ED28C66A05E}") IIterator_1__IBluetoothLEAdvertisementDataSection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{28C6C337-33E6-5B6B-A8C0-CB101A838EFE}") IIterator_1__IBluetoothLEAdvertisementDataSection  : public IIterator_1__IBluetoothLEAdvertisementDataSection_Base 
{
	virtual HRESULT __safecall get_Current(_di_IBluetoothLEAdvertisementDataSection &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIBluetoothLEAdvertisementDataSection items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisementDataSection _scw_get_Current() { _di_IBluetoothLEAdvertisementDataSection __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisementDataSection Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{DB98B5D1-897E-59CC-B86A-7B8855AC98AF}") IIterable_1__IBluetoothLEAdvertisementDataSection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F68192BA-2B18-58A5-A3BA-1F874813B0B2}") IIterable_1__IBluetoothLEAdvertisementDataSection  : public IIterable_1__IBluetoothLEAdvertisementDataSection_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IBluetoothLEAdvertisementDataSection &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{6619200D-D012-530E-A769-1B060E574B9A}") IVectorView_1__IBluetoothLEAdvertisementDataSection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEAdvertisementDataSection &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEAdvertisementDataSection value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEAdvertisementDataSection items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{27485048-DEEF-57A1-8FF9-90B75BF5E3BD}") IVector_1__IBluetoothLEAdvertisementDataSection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEAdvertisementDataSection &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IBluetoothLEAdvertisementDataSection &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEAdvertisementDataSection value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IBluetoothLEAdvertisementDataSection value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IBluetoothLEAdvertisementDataSection value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IBluetoothLEAdvertisementDataSection value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEAdvertisementDataSection items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIBluetoothLEAdvertisementDataSection items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{066FB2B7-33D1-4E7D-8367-CF81D0F79653}") IBluetoothLEAdvertisement  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Flags(_di_IReference_1__BluetoothLEAdvertisementFlags &__get_Flags_result) = 0 ;
	virtual HRESULT __safecall put_Flags(_di_IReference_1__BluetoothLEAdvertisementFlags value) = 0 ;
	virtual HRESULT __safecall get_LocalName(HSTRING &__get_LocalName_result) = 0 ;
	virtual HRESULT __safecall put_LocalName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_ServiceUuids(Winapi::Applicationmodel::_di_IVector_1__TGuid &__get_ServiceUuids_result) = 0 ;
	virtual HRESULT __safecall get_ManufacturerData(_di_IVector_1__IBluetoothLEManufacturerData &__get_ManufacturerData_result) = 0 ;
	virtual HRESULT __safecall get_DataSections(_di_IVector_1__IBluetoothLEAdvertisementDataSection &__get_DataSections_result) = 0 ;
	virtual HRESULT __safecall GetManufacturerDataByCompanyId(System::Word companyId, _di_IVectorView_1__IBluetoothLEManufacturerData &__GetManufacturerDataByCompanyId_result) = 0 ;
	virtual HRESULT __safecall GetSectionsByType(System::Byte type, _di_IVectorView_1__IBluetoothLEAdvertisementDataSection &__GetSectionsByType_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__IBluetoothLEAdvertisementDataSection _scw_get_DataSections() { _di_IVector_1__IBluetoothLEAdvertisementDataSection __r; HRESULT __hr = get_DataSections(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__IBluetoothLEAdvertisementDataSection DataSections = {read=_scw_get_DataSections};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IReference_1__BluetoothLEAdvertisementFlags _scw_get_Flags() { _di_IReference_1__BluetoothLEAdvertisementFlags __r; HRESULT __hr = get_Flags(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IReference_1__BluetoothLEAdvertisementFlags Flags = {read=_scw_get_Flags, write=put_Flags};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LocalName() { HSTRING __r; HRESULT __hr = get_LocalName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LocalName = {read=_scw_get_LocalName, write=put_LocalName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__IBluetoothLEManufacturerData _scw_get_ManufacturerData() { _di_IVector_1__IBluetoothLEManufacturerData __r; HRESULT __hr = get_ManufacturerData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__IBluetoothLEManufacturerData ManufacturerData = {read=_scw_get_ManufacturerData};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IVector_1__TGuid _scw_get_ServiceUuids() { Winapi::Applicationmodel::_di_IVector_1__TGuid __r; HRESULT __hr = get_ServiceUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IVector_1__TGuid ServiceUuids = {read=_scw_get_ServiceUuids};
};

__interface  INTERFACE_UUID("{FBFAD7F2-B9C5-4A08-BC51-502F8EF68A79}") IBluetoothLEAdvertisementBytePattern  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DataType(System::Byte &__get_DataType_result) = 0 ;
	virtual HRESULT __safecall put_DataType(System::Byte value) = 0 ;
	virtual HRESULT __safecall get_Offset(short &__get_Offset_result) = 0 ;
	virtual HRESULT __safecall put_Offset(short value) = 0 ;
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IBuffer &__get_Data_result) = 0 ;
	virtual HRESULT __safecall put_Data(Winapi::Commontypes::_di_IBuffer value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Data() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Data = {read=_scw_get_Data, write=put_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_DataType() { System::Byte __r; HRESULT __hr = get_DataType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte DataType = {read=_scw_get_DataType, write=put_DataType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_get_Offset() { short __r; HRESULT __hr = get_Offset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property short Offset = {read=_scw_get_Offset, write=put_Offset};
};

__interface  INTERFACE_UUID("{B33E103A-1A61-5107-8813-C0E905C05486}") IIterator_1__IBluetoothLEAdvertisementBytePattern_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{780018BB-FD2E-5FC9-AB41-844D7405DB8A}") IIterator_1__IBluetoothLEAdvertisementBytePattern  : public IIterator_1__IBluetoothLEAdvertisementBytePattern_Base 
{
	virtual HRESULT __safecall get_Current(_di_IBluetoothLEAdvertisementBytePattern &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIBluetoothLEAdvertisementBytePattern items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisementBytePattern _scw_get_Current() { _di_IBluetoothLEAdvertisementBytePattern __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisementBytePattern Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{1E3FADEE-54AC-538B-8777-351AFB78CB74}") IIterable_1__IBluetoothLEAdvertisementBytePattern_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{EB205564-A2C2-591F-AAB5-82EAEBFBC6DA}") IIterable_1__IBluetoothLEAdvertisementBytePattern  : public IIterable_1__IBluetoothLEAdvertisementBytePattern_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IBluetoothLEAdvertisementBytePattern &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{D57CF71B-0B53-5F7B-A0D9-4690FB2588C7}") IVectorView_1__IBluetoothLEAdvertisementBytePattern  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEAdvertisementBytePattern &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEAdvertisementBytePattern value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEAdvertisementBytePattern items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{3E74F04D-A6C9-5DC1-85B1-CE32D80C638A}") IVector_1__IBluetoothLEAdvertisementBytePattern  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEAdvertisementBytePattern &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IBluetoothLEAdvertisementBytePattern &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEAdvertisementBytePattern value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IBluetoothLEAdvertisementBytePattern value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IBluetoothLEAdvertisementBytePattern value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IBluetoothLEAdvertisementBytePattern value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEAdvertisementBytePattern items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIBluetoothLEAdvertisementBytePattern items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{131EB0D3-D04E-47B1-837E-49405BF6F80F}") IBluetoothLEAdvertisementFilter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Advertisement(_di_IBluetoothLEAdvertisement &__get_Advertisement_result) = 0 ;
	virtual HRESULT __safecall put_Advertisement(_di_IBluetoothLEAdvertisement value) = 0 ;
	virtual HRESULT __safecall get_BytePatterns(_di_IVector_1__IBluetoothLEAdvertisementBytePattern &__get_BytePatterns_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisement _scw_get_Advertisement() { _di_IBluetoothLEAdvertisement __r; HRESULT __hr = get_Advertisement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisement Advertisement = {read=_scw_get_Advertisement, write=put_Advertisement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__IBluetoothLEAdvertisementBytePattern _scw_get_BytePatterns() { _di_IVector_1__IBluetoothLEAdvertisementBytePattern __r; HRESULT __hr = get_BytePatterns(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__IBluetoothLEAdvertisementBytePattern BytePatterns = {read=_scw_get_BytePatterns};
};

__interface  INTERFACE_UUID("{DD40F84D-E7B9-43E3-9C04-0685D085FD8C}") IBluetoothLEAdvertisementWatcherStoppedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Error(Winapi::Commontypes::BluetoothError &__get_Error_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothError _scw_get_Error() { Winapi::Commontypes::BluetoothError __r; HRESULT __hr = get_Error(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothError Error = {read=_scw_get_Error};
};

__interface  INTERFACE_UUID("{27987DDF-E596-41BE-8D43-9E6731D4A913}") IBluetoothLEAdvertisementReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RawSignalStrengthInDBm(short &__get_RawSignalStrengthInDBm_result) = 0 ;
	virtual HRESULT __safecall get_BluetoothAddress(unsigned __int64 &__get_BluetoothAddress_result) = 0 ;
	virtual HRESULT __safecall get_AdvertisementType(Winapi::Commontypes::BluetoothLEAdvertisementType &__get_AdvertisementType_result) = 0 ;
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_Advertisement(_di_IBluetoothLEAdvertisement &__get_Advertisement_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisement _scw_get_Advertisement() { _di_IBluetoothLEAdvertisement __r; HRESULT __hr = get_Advertisement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisement Advertisement = {read=_scw_get_Advertisement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEAdvertisementType _scw_get_AdvertisementType() { Winapi::Commontypes::BluetoothLEAdvertisementType __r; HRESULT __hr = get_AdvertisementType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEAdvertisementType AdvertisementType = {read=_scw_get_AdvertisementType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BluetoothAddress() { unsigned __int64 __r; HRESULT __hr = get_BluetoothAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BluetoothAddress = {read=_scw_get_BluetoothAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_get_RawSignalStrengthInDBm() { short __r; HRESULT __hr = get_RawSignalStrengthInDBm(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property short RawSignalStrengthInDBm = {read=_scw_get_RawSignalStrengthInDBm};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
};

__interface  INTERFACE_UUID("{90EB4ECA-D465-5EA0-A61C-033C8C5ECEF2}") TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{FD2452E0-5167-53D2-BADA-405DDF441262}") TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs  : public TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IBluetoothLEAdvertisementWatcher sender, _di_IBluetoothLEAdvertisementReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{9936A4DB-DC99-55C3-9E9B-BF4854BD9EAB}") TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{859B97EB-2DFE-59AD-AD1B-3C93C7512179}") TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs  : public TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IBluetoothLEAdvertisementWatcher sender, _di_IBluetoothLEAdvertisementWatcherStoppedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{A6AC336F-F3D3-4297-8D6C-C81EA6623F40}") IBluetoothLEAdvertisementWatcher  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MinSamplingInterval(Winapi::Commontypes::TimeSpan &__get_MinSamplingInterval_result) = 0 ;
	virtual HRESULT __safecall get_MaxSamplingInterval(Winapi::Commontypes::TimeSpan &__get_MaxSamplingInterval_result) = 0 ;
	virtual HRESULT __safecall get_MinOutOfRangeTimeout(Winapi::Commontypes::TimeSpan &__get_MinOutOfRangeTimeout_result) = 0 ;
	virtual HRESULT __safecall get_MaxOutOfRangeTimeout(Winapi::Commontypes::TimeSpan &__get_MaxOutOfRangeTimeout_result) = 0 ;
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::BluetoothLEAdvertisementWatcherStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_ScanningMode(Winapi::Commontypes::BluetoothLEScanningMode &__get_ScanningMode_result) = 0 ;
	virtual HRESULT __safecall put_ScanningMode(Winapi::Commontypes::BluetoothLEScanningMode value) = 0 ;
	virtual HRESULT __safecall get_SignalStrengthFilter(Winapi::Devices::Bluetooth::_di_IBluetoothSignalStrengthFilter &__get_SignalStrengthFilter_result) = 0 ;
	virtual HRESULT __safecall put_SignalStrengthFilter(Winapi::Devices::Bluetooth::_di_IBluetoothSignalStrengthFilter value) = 0 ;
	virtual HRESULT __safecall get_AdvertisementFilter(_di_IBluetoothLEAdvertisementFilter &__get_AdvertisementFilter_result) = 0 ;
	virtual HRESULT __safecall put_AdvertisementFilter(_di_IBluetoothLEAdvertisementFilter value) = 0 ;
	virtual HRESULT __safecall Start() = 0 ;
	virtual HRESULT __safecall Stop() = 0 ;
	virtual HRESULT __safecall add_Received(_di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementReceivedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Received_result) = 0 ;
	virtual HRESULT __safecall remove_Received(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_Stopped(_di_TypedEventHandler_2__IBluetoothLEAdvertisementWatcher__IBluetoothLEAdvertisementWatcherStoppedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Stopped_result) = 0 ;
	virtual HRESULT __safecall remove_Stopped(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisementFilter _scw_get_AdvertisementFilter() { _di_IBluetoothLEAdvertisementFilter __r; HRESULT __hr = get_AdvertisementFilter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisementFilter AdvertisementFilter = {read=_scw_get_AdvertisementFilter, write=put_AdvertisementFilter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_MaxOutOfRangeTimeout() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_MaxOutOfRangeTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan MaxOutOfRangeTimeout = {read=_scw_get_MaxOutOfRangeTimeout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_MaxSamplingInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_MaxSamplingInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan MaxSamplingInterval = {read=_scw_get_MaxSamplingInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_MinOutOfRangeTimeout() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_MinOutOfRangeTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan MinOutOfRangeTimeout = {read=_scw_get_MinOutOfRangeTimeout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_MinSamplingInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_MinSamplingInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan MinSamplingInterval = {read=_scw_get_MinSamplingInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEScanningMode _scw_get_ScanningMode() { Winapi::Commontypes::BluetoothLEScanningMode __r; HRESULT __hr = get_ScanningMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEScanningMode ScanningMode = {read=_scw_get_ScanningMode, write=put_ScanningMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::Bluetooth::_di_IBluetoothSignalStrengthFilter _scw_get_SignalStrengthFilter() { Winapi::Devices::Bluetooth::_di_IBluetoothSignalStrengthFilter __r; HRESULT __hr = get_SignalStrengthFilter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::Bluetooth::_di_IBluetoothSignalStrengthFilter SignalStrengthFilter = {read=_scw_get_SignalStrengthFilter, write=put_SignalStrengthFilter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEAdvertisementWatcherStatus _scw_get_Status() { Winapi::Commontypes::BluetoothLEAdvertisementWatcherStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEAdvertisementWatcherStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{9AAF2D56-39AC-453E-B32A-85C657E017F1}") IBluetoothLEAdvertisementWatcherFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_IBluetoothLEAdvertisementFilter advertisementFilter, _di_IBluetoothLEAdvertisementWatcher &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{E7A40942-A845-4045-BF7E-3E9971DB8A6B}") IBluetoothLEAdvertisementDataSectionFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(System::Byte dataType, Winapi::Commontypes::_di_IBuffer data, _di_IBluetoothLEAdvertisementDataSection &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{C09B39F8-319A-441E-8DE5-66A81E877A6C}") IBluetoothLEManufacturerDataFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(System::Word companyId, Winapi::Commontypes::_di_IBuffer data, _di_IBluetoothLEManufacturerData &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{C2E24D73-FD5C-4EC3-BE2A-9CA6FA11B7BD}") IBluetoothLEAdvertisementBytePatternFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(System::Byte dataType, short offset, Winapi::Commontypes::_di_IBuffer data, _di_IBluetoothLEAdvertisementBytePattern &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{3BB6472F-0606-434B-A76E-74159F0684D3}") IBluetoothLEAdvertisementDataTypesStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Flags(System::Byte &__get_Flags_result) = 0 ;
	virtual HRESULT __safecall get_IncompleteService16BitUuids(System::Byte &__get_IncompleteService16BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_CompleteService16BitUuids(System::Byte &__get_CompleteService16BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_IncompleteService32BitUuids(System::Byte &__get_IncompleteService32BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_CompleteService32BitUuids(System::Byte &__get_CompleteService32BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_IncompleteService128BitUuids(System::Byte &__get_IncompleteService128BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_CompleteService128BitUuids(System::Byte &__get_CompleteService128BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ShortenedLocalName(System::Byte &__get_ShortenedLocalName_result) = 0 ;
	virtual HRESULT __safecall get_CompleteLocalName(System::Byte &__get_CompleteLocalName_result) = 0 ;
	virtual HRESULT __safecall get_TxPowerLevel(System::Byte &__get_TxPowerLevel_result) = 0 ;
	virtual HRESULT __safecall get_SlaveConnectionIntervalRange(System::Byte &__get_SlaveConnectionIntervalRange_result) = 0 ;
	virtual HRESULT __safecall get_ServiceSolicitation16BitUuids(System::Byte &__get_ServiceSolicitation16BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ServiceSolicitation32BitUuids(System::Byte &__get_ServiceSolicitation32BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ServiceSolicitation128BitUuids(System::Byte &__get_ServiceSolicitation128BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ServiceData16BitUuids(System::Byte &__get_ServiceData16BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ServiceData32BitUuids(System::Byte &__get_ServiceData32BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_ServiceData128BitUuids(System::Byte &__get_ServiceData128BitUuids_result) = 0 ;
	virtual HRESULT __safecall get_PublicTargetAddress(System::Byte &__get_PublicTargetAddress_result) = 0 ;
	virtual HRESULT __safecall get_RandomTargetAddress(System::Byte &__get_RandomTargetAddress_result) = 0 ;
	virtual HRESULT __safecall get_Appearance(System::Byte &__get_Appearance_result) = 0 ;
	virtual HRESULT __safecall get_AdvertisingInterval(System::Byte &__get_AdvertisingInterval_result) = 0 ;
	virtual HRESULT __safecall get_ManufacturerSpecificData(System::Byte &__get_ManufacturerSpecificData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_AdvertisingInterval() { System::Byte __r; HRESULT __hr = get_AdvertisingInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte AdvertisingInterval = {read=_scw_get_AdvertisingInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Appearance() { System::Byte __r; HRESULT __hr = get_Appearance(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Appearance = {read=_scw_get_Appearance};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_CompleteLocalName() { System::Byte __r; HRESULT __hr = get_CompleteLocalName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte CompleteLocalName = {read=_scw_get_CompleteLocalName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_CompleteService128BitUuids() { System::Byte __r; HRESULT __hr = get_CompleteService128BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte CompleteService128BitUuids = {read=_scw_get_CompleteService128BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_CompleteService16BitUuids() { System::Byte __r; HRESULT __hr = get_CompleteService16BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte CompleteService16BitUuids = {read=_scw_get_CompleteService16BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_CompleteService32BitUuids() { System::Byte __r; HRESULT __hr = get_CompleteService32BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte CompleteService32BitUuids = {read=_scw_get_CompleteService32BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Flags() { System::Byte __r; HRESULT __hr = get_Flags(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Flags = {read=_scw_get_Flags};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_IncompleteService128BitUuids() { System::Byte __r; HRESULT __hr = get_IncompleteService128BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte IncompleteService128BitUuids = {read=_scw_get_IncompleteService128BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_IncompleteService16BitUuids() { System::Byte __r; HRESULT __hr = get_IncompleteService16BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte IncompleteService16BitUuids = {read=_scw_get_IncompleteService16BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_IncompleteService32BitUuids() { System::Byte __r; HRESULT __hr = get_IncompleteService32BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte IncompleteService32BitUuids = {read=_scw_get_IncompleteService32BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ManufacturerSpecificData() { System::Byte __r; HRESULT __hr = get_ManufacturerSpecificData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ManufacturerSpecificData = {read=_scw_get_ManufacturerSpecificData};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_PublicTargetAddress() { System::Byte __r; HRESULT __hr = get_PublicTargetAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte PublicTargetAddress = {read=_scw_get_PublicTargetAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_RandomTargetAddress() { System::Byte __r; HRESULT __hr = get_RandomTargetAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte RandomTargetAddress = {read=_scw_get_RandomTargetAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceData128BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceData128BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceData128BitUuids = {read=_scw_get_ServiceData128BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceData16BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceData16BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceData16BitUuids = {read=_scw_get_ServiceData16BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceData32BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceData32BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceData32BitUuids = {read=_scw_get_ServiceData32BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceSolicitation128BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceSolicitation128BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceSolicitation128BitUuids = {read=_scw_get_ServiceSolicitation128BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceSolicitation16BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceSolicitation16BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceSolicitation16BitUuids = {read=_scw_get_ServiceSolicitation16BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ServiceSolicitation32BitUuids() { System::Byte __r; HRESULT __hr = get_ServiceSolicitation32BitUuids(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ServiceSolicitation32BitUuids = {read=_scw_get_ServiceSolicitation32BitUuids};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ShortenedLocalName() { System::Byte __r; HRESULT __hr = get_ShortenedLocalName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ShortenedLocalName = {read=_scw_get_ShortenedLocalName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_SlaveConnectionIntervalRange() { System::Byte __r; HRESULT __hr = get_SlaveConnectionIntervalRange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte SlaveConnectionIntervalRange = {read=_scw_get_SlaveConnectionIntervalRange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_TxPowerLevel() { System::Byte __r; HRESULT __hr = get_TxPowerLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte TxPowerLevel = {read=_scw_get_TxPowerLevel};
};

__interface  INTERFACE_UUID("{09C2BD9F-2DFF-4B23-86EE-0D14FB94AEAE}") IBluetoothLEAdvertisementPublisherStatusChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_Error(Winapi::Commontypes::BluetoothError &__get_Error_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothError _scw_get_Error() { Winapi::Commontypes::BluetoothError __r; HRESULT __hr = get_Error(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothError Error = {read=_scw_get_Error};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus _scw_get_Status() { Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{C2FFA4F1-5893-54A8-BD94-AA1198B05D07}") TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{06B838A8-7B0F-536E-8726-131A41D9D97E}") TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs  : public TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IBluetoothLEAdvertisementPublisher sender, _di_IBluetoothLEAdvertisementPublisherStatusChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{CDE820F9-D9FA-43D6-A264-DDD8B7DA8B78}") IBluetoothLEAdvertisementPublisher  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_Advertisement(_di_IBluetoothLEAdvertisement &__get_Advertisement_result) = 0 ;
	virtual HRESULT __safecall Start() = 0 ;
	virtual HRESULT __safecall Stop() = 0 ;
	virtual HRESULT __safecall add_StatusChanged(_di_TypedEventHandler_2__IBluetoothLEAdvertisementPublisher__IBluetoothLEAdvertisementPublisherStatusChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StatusChanged_result) = 0 ;
	virtual HRESULT __safecall remove_StatusChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisement _scw_get_Advertisement() { _di_IBluetoothLEAdvertisement __r; HRESULT __hr = get_Advertisement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisement Advertisement = {read=_scw_get_Advertisement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus _scw_get_Status() { Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BluetoothLEAdvertisementPublisherStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{5C5F065E-B863-4981-A1AF-1C544D8B0C0D}") IBluetoothLEAdvertisementPublisherFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_IBluetoothLEAdvertisement advertisement, _di_IBluetoothLEAdvertisementPublisher &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{096EDBB8-ECEF-5724-BE62-240DCFF6ACA9}") IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F0FFB2E4-7E87-598B-9639-93EEEC8D41C6}") IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs  : public IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs_Base 
{
	virtual HRESULT __safecall get_Current(_di_IBluetoothLEAdvertisementReceivedEventArgs &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIBluetoothLEAdvertisementReceivedEventArgs items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IBluetoothLEAdvertisementReceivedEventArgs _scw_get_Current() { _di_IBluetoothLEAdvertisementReceivedEventArgs __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IBluetoothLEAdvertisementReceivedEventArgs Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{34F6412F-8314-5205-967C-DB357C9A42A7}") IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DCC7A122-E1B2-5805-8D67-9AF550BC5824}") IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs  : public IIterable_1__IBluetoothLEAdvertisementReceivedEventArgs_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IBluetoothLEAdvertisementReceivedEventArgs &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{DAAAEAA7-D307-5BF1-A0DB-0A811F07970B}") IVectorView_1__IBluetoothLEAdvertisementReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IBluetoothLEAdvertisementReceivedEventArgs &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IBluetoothLEAdvertisementReceivedEventArgs value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIBluetoothLEAdvertisementReceivedEventArgs items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEManufacturerData : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEManufacturerDataFactory,_di_IBluetoothLEManufacturerData>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEManufacturerDataFactory,_di_IBluetoothLEManufacturerData> inherited;
	
public:
	static _di_IBluetoothLEManufacturerData __fastcall Create(System::Word companyId, Winapi::Commontypes::_di_IBuffer data)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEManufacturerData() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEManufacturerDataFactory,_di_IBluetoothLEManufacturerData>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEManufacturerData() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementDataSection : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementDataSectionFactory,_di_IBluetoothLEAdvertisementDataSection>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementDataSectionFactory,_di_IBluetoothLEAdvertisementDataSection> inherited;
	
public:
	static _di_IBluetoothLEAdvertisementDataSection __fastcall Create(System::Byte dataType, Winapi::Commontypes::_di_IBuffer data)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementDataSection() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementDataSectionFactory,_di_IBluetoothLEAdvertisementDataSection>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementDataSection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisement : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisement>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisement> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisement() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisement>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisement() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementBytePattern : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementBytePatternFactory,_di_IBluetoothLEAdvertisementBytePattern>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementBytePatternFactory,_di_IBluetoothLEAdvertisementBytePattern> inherited;
	
public:
	static _di_IBluetoothLEAdvertisementBytePattern __fastcall Create(System::Byte dataType, short offset, Winapi::Commontypes::_di_IBuffer data)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementBytePattern() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementBytePatternFactory,_di_IBluetoothLEAdvertisementBytePattern>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementBytePattern() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementFilter : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisementFilter>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisementFilter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementFilter() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IBluetoothLEAdvertisementFilter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementFilter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementWatcher : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementWatcherFactory,_di_IBluetoothLEAdvertisementWatcher>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementWatcherFactory,_di_IBluetoothLEAdvertisementWatcher> inherited;
	
public:
	static _di_IBluetoothLEAdvertisementWatcher __fastcall Create(_di_IBluetoothLEAdvertisementFilter advertisementFilter)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementWatcher() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementWatcherFactory,_di_IBluetoothLEAdvertisementWatcher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementWatcher() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementDataTypes : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IBluetoothLEAdvertisementDataTypesStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IBluetoothLEAdvertisementDataTypesStatics> inherited;
	
public:
	static System::Byte __fastcall get_Flags();
	static System::Byte __fastcall get_IncompleteService16BitUuids();
	static System::Byte __fastcall get_CompleteService16BitUuids();
	static System::Byte __fastcall get_IncompleteService32BitUuids();
	static System::Byte __fastcall get_CompleteService32BitUuids();
	static System::Byte __fastcall get_IncompleteService128BitUuids();
	static System::Byte __fastcall get_CompleteService128BitUuids();
	static System::Byte __fastcall get_ShortenedLocalName();
	static System::Byte __fastcall get_CompleteLocalName();
	static System::Byte __fastcall get_TxPowerLevel();
	static System::Byte __fastcall get_SlaveConnectionIntervalRange();
	static System::Byte __fastcall get_ServiceSolicitation16BitUuids();
	static System::Byte __fastcall get_ServiceSolicitation32BitUuids();
	static System::Byte __fastcall get_ServiceSolicitation128BitUuids();
	static System::Byte __fastcall get_ServiceData16BitUuids();
	static System::Byte __fastcall get_ServiceData32BitUuids();
	static System::Byte __fastcall get_ServiceData128BitUuids();
	static System::Byte __fastcall get_PublicTargetAddress();
	static System::Byte __fastcall get_RandomTargetAddress();
	static System::Byte __fastcall get_Appearance();
	static System::Byte __fastcall get_AdvertisingInterval();
	static System::Byte __fastcall get_ManufacturerSpecificData();
	/* static */ __property System::Byte AdvertisingInterval = {read=get_AdvertisingInterval, nodefault};
	/* static */ __property System::Byte Appearance = {read=get_Appearance, nodefault};
	/* static */ __property System::Byte CompleteLocalName = {read=get_CompleteLocalName, nodefault};
	/* static */ __property System::Byte CompleteService128BitUuids = {read=get_CompleteService128BitUuids, nodefault};
	/* static */ __property System::Byte CompleteService16BitUuids = {read=get_CompleteService16BitUuids, nodefault};
	/* static */ __property System::Byte CompleteService32BitUuids = {read=get_CompleteService32BitUuids, nodefault};
	/* static */ __property System::Byte Flags = {read=get_Flags, nodefault};
	/* static */ __property System::Byte IncompleteService128BitUuids = {read=get_IncompleteService128BitUuids, nodefault};
	/* static */ __property System::Byte IncompleteService16BitUuids = {read=get_IncompleteService16BitUuids, nodefault};
	/* static */ __property System::Byte IncompleteService32BitUuids = {read=get_IncompleteService32BitUuids, nodefault};
	/* static */ __property System::Byte ManufacturerSpecificData = {read=get_ManufacturerSpecificData, nodefault};
	/* static */ __property System::Byte PublicTargetAddress = {read=get_PublicTargetAddress, nodefault};
	/* static */ __property System::Byte RandomTargetAddress = {read=get_RandomTargetAddress, nodefault};
	/* static */ __property System::Byte ServiceData128BitUuids = {read=get_ServiceData128BitUuids, nodefault};
	/* static */ __property System::Byte ServiceData16BitUuids = {read=get_ServiceData16BitUuids, nodefault};
	/* static */ __property System::Byte ServiceData32BitUuids = {read=get_ServiceData32BitUuids, nodefault};
	/* static */ __property System::Byte ServiceSolicitation128BitUuids = {read=get_ServiceSolicitation128BitUuids, nodefault};
	/* static */ __property System::Byte ServiceSolicitation16BitUuids = {read=get_ServiceSolicitation16BitUuids, nodefault};
	/* static */ __property System::Byte ServiceSolicitation32BitUuids = {read=get_ServiceSolicitation32BitUuids, nodefault};
	/* static */ __property System::Byte ShortenedLocalName = {read=get_ShortenedLocalName, nodefault};
	/* static */ __property System::Byte SlaveConnectionIntervalRange = {read=get_SlaveConnectionIntervalRange, nodefault};
	/* static */ __property System::Byte TxPowerLevel = {read=get_TxPowerLevel, nodefault};
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementDataTypes() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IBluetoothLEAdvertisementDataTypesStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementDataTypes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBluetoothLEAdvertisementPublisher : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementPublisherFactory,_di_IBluetoothLEAdvertisementPublisher>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementPublisherFactory,_di_IBluetoothLEAdvertisementPublisher> inherited;
	
public:
	static _di_IBluetoothLEAdvertisementPublisher __fastcall Create(_di_IBluetoothLEAdvertisement advertisement)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEAdvertisementPublisher() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IBluetoothLEAdvertisementPublisherFactory,_di_IBluetoothLEAdvertisementPublisher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEAdvertisementPublisher() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Advertisement */
}	/* namespace Bluetooth */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_Bluetooth_AdvertisementHPP
