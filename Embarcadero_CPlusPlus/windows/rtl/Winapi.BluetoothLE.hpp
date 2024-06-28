// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.BluetoothLE.pas' rev: 34.00 (Windows)

#ifndef Winapi_BluetoothleHPP
#define Winapi_BluetoothleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
// The "BlueTooth Low Energy" interface requires that you install the Windows 8 SDK
#include <no_sal2.h>         // Header available from the "Windows SDK for Windows 8"
#include <bthledef.h>        // Header available from the "Windows SDK for Windows 8"
#include <bluetoothleapis.h> // Header available from the "Windows SDK for Windows 8"

namespace Winapi
{
namespace Bluetoothle
{
//-- forward type declarations -----------------------------------------------
struct AuxGattDescriptorType;
struct _BTH_LE_GATT_DESCRIPTOR_VALUE;
//-- type declarations -------------------------------------------------------
typedef NativeUInt TBluetoothGattEventHandle;

typedef NativeUInt *PBluetoothGattEventHandle;

typedef _BTH_LE_UUID TBthLeUuid;

typedef _BTH_LE_UUID *PBthLeUuid;

typedef _BTH_LE_GATT_SERVICE TBthLeGattService;

typedef _BTH_LE_GATT_SERVICE *PBthLeGattService;

typedef BTH_LE_GATT_DESCRIPTOR_TYPE TBthLeGattDescriptorType;

typedef BTH_LE_GATT_DESCRIPTOR_TYPE *PBthLeGattDescriptorType;

typedef _BTH_LE_GATT_CHARACTERISTIC TBthLeGattCharacteristic;

typedef _BTH_LE_GATT_CHARACTERISTIC *PBthLeGattCharacteristic;

typedef _BTH_LE_GATT_CHARACTERISTIC_VALUE TBthLeGattCharacteristicValue;

typedef _BTH_LE_GATT_CHARACTERISTIC_VALUE *PBthLeGattCharacteristicValue;

typedef BTH_LE_GATT_DESCRIPTOR _BTH_LE_GATT_DESCRIPTOR;

typedef BTH_LE_GATT_DESCRIPTOR TBthLeGattDescriptor;

typedef BTH_LE_GATT_DESCRIPTOR *PBthLeGattDescriptor;

struct DECLSPEC_DRECORD AuxGattDescriptorType
{
	
public:
	union
	{
		struct 
		{
			System::Byte Format;
			System::Int8 Exponent;
			_BTH_LE_UUID Unit;
			System::Byte NameSpace;
			_BTH_LE_UUID Description;
		};
		struct 
		{
			bool IsBroadcast;
		};
		struct 
		{
			bool IsSubscribeToNotification;
			bool IsSubscribeToIndication;
		};
		struct 
		{
			bool IsReliableWriteEnabled;
			bool IsAuxiliariesWritable;
		};
		
	};
};


struct DECLSPEC_DRECORD _BTH_LE_GATT_DESCRIPTOR_VALUE
{
public:
	BTH_LE_GATT_DESCRIPTOR_TYPE DescriptorType;
	_BTH_LE_UUID DescriptorUuid;
	AuxGattDescriptorType DescriptorInfo;
	unsigned DataSize;
	System::StaticArray<System::Byte, 1> Data;
};


typedef _BTH_LE_GATT_DESCRIPTOR_VALUE TBthLeGattDescriptorValue;

typedef _BTH_LE_GATT_DESCRIPTOR_VALUE *PBthLeGattDescriptorValue;

typedef BTH_LE_GATT_EVENT_TYPE TBthLeGattEventType;

typedef PFNBLUETOOTH_GATT_EVENT_CALLBACK PFnBluetoothGattEventCallback;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION *PBluetoothGattValueChangedEventRegistration;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION _BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION TBluetoothGattValueChangedEventRegistration;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT _BLUETOOTH_GATT_VALUE_CHANGED_EVENT;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT TBluetoothGattValueChangedEvent;

typedef BLUETOOTH_GATT_VALUE_CHANGED_EVENT *PBluetoothGattValueChangedEvent;

typedef unsigned __int64 TBthLeGattReliableWriteContext;

typedef unsigned __int64 *PBthLeGattReliableWriteContext;

//-- var, const, procedure ---------------------------------------------------
#define bthapile L"BluetoothApis.dll"
}	/* namespace Bluetoothle */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_BLUETOOTHLE)
using namespace Winapi::Bluetoothle;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_BluetoothleHPP
