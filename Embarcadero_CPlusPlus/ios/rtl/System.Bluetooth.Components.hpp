// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bluetooth.Components.pas' rev: 34.00 (iOS)

#ifndef System_Bluetooth_ComponentsHPP
#define System_Bluetooth_ComponentsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Bluetooth.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bluetooth
{
namespace Components
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBluetoothLE;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBluetoothLE : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FEnabled;
	bool FForceRefreshCachedDevices;
	System::Bluetooth::TGattCharacteristicEvent FOnCharacteristicRead;
	System::Bluetooth::TGattCharacteristicReadEvent FOnCharacteristicReadRequest;
	System::Bluetooth::TGattCharacteristicEvent FOnCharacteristicWrite;
	System::Bluetooth::TGattCharacteristicWriteEvent FOnCharacteristicWriteRequest;
	System::Bluetooth::TGattCharacteristicSubscriptionEvent FOnCharacteristicSubscribed;
	System::Bluetooth::TGattCharacteristicSubscriptionEvent FOnCharacteristicUnSubscribed;
	System::Bluetooth::TConnectLEDeviceEvent FOnConnectedDevice;
	System::Bluetooth::TGattDescriptorEvent FOnDescriptorRead;
	System::Bluetooth::TGattDescriptorEvent FOnDescriptorWrite;
	System::Classes::TNotifyEvent FOnConnect;
	System::Classes::TNotifyEvent FOnDisconnect;
	System::Bluetooth::TConnectLEDeviceEvent FOnDisconnectDevice;
	System::Bluetooth::TDiscoverLEDeviceEvent FOnDiscoverLEDevice;
	System::Bluetooth::TDiscoveryLEEndEvent FOnEndDiscoverDevices;
	System::Bluetooth::TDiscoverServicesEvent FOnEndDiscoverServices;
	System::Bluetooth::TDiscoverServicesEvent FOnServicesDiscovered;
	System::Bluetooth::TGattDeviceRSSIEvent FOnReadRSSI;
	System::Bluetooth::TGattOperationResultEvent FOnReliableWriteCompleted;
	System::Bluetooth::TGattServiceEvent FOnServiceAdded;
	
protected:
	System::Bluetooth::TBluetoothLEManager* FManager;
	System::Bluetooth::TBluetoothGattServer* FServer;
	void __fastcall DoInternalDiscoverLEDevice(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice, int Rssi, System::Bluetooth::TScanResponse* const ScanResponse)/* overload */;
	void __fastcall DoInternalDiscoveryEnd(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDeviceList* const ADeviceList)/* overload */;
	void __fastcall Setup();
	void __fastcall SetupGattServer();
	void __fastcall DoConnect(System::TObject* Sender);
	void __fastcall DoDisconnect(System::TObject* Sender);
	void __fastcall DoConnectedDevice(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice);
	void __fastcall DoDisconnectDevice(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice);
	void __fastcall DoOnCharacteristicRead(System::TObject* const Sender, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnCharacteristicReadRequest(System::TObject* const Sender, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic, System::Bluetooth::TBluetoothGattStatus &AGattStatus);
	void __fastcall DoOnCharacteristicWrite(System::TObject* const Sender, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnCharacteristicWriteRequest(System::TObject* const Sender, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic, System::Bluetooth::TBluetoothGattStatus &AGattStatus, const System::TArray__1<System::Byte> AValue);
	void __fastcall DoOnCharacteristicSubscribed(System::TObject* const Sender, const System::UnicodeString AClientId, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	void __fastcall DoOnCharacteristicUnSubscribed(System::TObject* const Sender, const System::UnicodeString AClientId, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	void __fastcall DoOnDescriptorRead(System::TObject* const Sender, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnDescriptorReadRequest(System::TObject* const Sender, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor, System::Bluetooth::TBluetoothGattStatus &AGattStatus);
	void __fastcall DoOnDescriptorWrite(System::TObject* const Sender, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnDescriptorWriteRequest(System::TObject* const Sender, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor, System::Bluetooth::TBluetoothGattStatus &AGattStatus, const System::TArray__1<System::Byte> AValue);
	void __fastcall DoOnReadRSSI(System::TObject* const Sender, int ARssiValue, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnReliableWriteCompleted(System::TObject* const Sender, System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoServiceAdded(System::TObject* const Sender, System::Bluetooth::TBluetoothGattService* const AService, const System::Bluetooth::TBluetoothGattStatus AGattStatus);
	void __fastcall DoOnDiscoverLEDevice(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice, int Rssi, System::Bluetooth::TScanResponse* const ScanResponse);
	void __fastcall DoOnServicesDiscovered(System::TObject* const Sender, System::Bluetooth::TBluetoothGattServiceList* const AServiceList);
	void __fastcall DoOnEndDiscoverDevices(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDeviceList* const ADeviceList);
	void __fastcall SetEnabled(bool AEnable);
	bool __fastcall GetSupportsGattClient();
	bool __fastcall GetSupportsGattServer();
	System::Bluetooth::TBluetoothLEDeviceList* __fastcall GetDiscoveredDevices();
	void __fastcall SetForceRefreshCachedDevices(bool Value);
	
public:
	__fastcall virtual TBluetoothLE(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBluetoothLE();
	bool __fastcall AddCharacteristic(System::Bluetooth::TBluetoothGattService* const AService, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	bool __fastcall BeginReliableWrite(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	System::Bluetooth::TBluetoothGattCharacteristic* __fastcall CreateCharacteristic(System::Bluetooth::TBluetoothGattService* const AService, const GUID &AUUID, System::Bluetooth::TBluetoothPropertyFlags APropertyFlags, const System::UnicodeString ADescription);
	System::Bluetooth::TBluetoothGattService* __fastcall CreateIncludedService(System::Bluetooth::TBluetoothGattService* const AService, const GUID &AnUUID, System::Bluetooth::TBluetoothServiceType AType);
	System::Bluetooth::TBluetoothGattService* __fastcall CreateService(const GUID &AnUUID, System::Bluetooth::TBluetoothServiceType AType);
	bool __fastcall DiscoverServices(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	bool __fastcall ExecuteReliableWrite(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	System::Bluetooth::TBluetoothGattCharacteristic* __fastcall GetCharacteristic(System::Bluetooth::TBluetoothGattService* const AService, const GUID &AUUID);
	System::Bluetooth::TBluetoothGattCharacteristicList* __fastcall GetCharacteristics(System::Bluetooth::TBluetoothGattService* const AService);
	System::Bluetooth::TBluetoothConnectionState __fastcall GetConnectionState();
	System::Bluetooth::TBluetoothLEAdapter* __fastcall GetCurrentAdapter();
	System::Bluetooth::TBluetoothLEManager* __fastcall GetCurrentManager();
	System::Bluetooth::TBluetoothGattDescriptorList* __fastcall GetDescriptors(System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	System::Bluetooth::TBluetoothGattServer* __fastcall GetGattServer();
	System::Bluetooth::TBluetoothGattService* __fastcall GetService(System::Bluetooth::TBluetoothLEDevice* const ADevice, const GUID &AServiceID);
	System::Bluetooth::TBluetoothGattServiceList* __fastcall GetServices(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	bool __fastcall ReadCharacteristic(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	bool __fastcall ReadDescriptor(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor);
	bool __fastcall SubscribeToCharacteristic(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	bool __fastcall WriteCharacteristic(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	bool __fastcall WriteDescriptor(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattDescriptor* const ADescriptor);
	void __fastcall AbortReliableWrite(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	void __fastcall CancelDiscovery();
	void __fastcall ClearServices();
	bool __fastcall DiscoverDevices(int ATimeout)/* overload */;
	bool __fastcall DiscoverDevices(int ATimeout, System::Bluetooth::TBluetoothUUIDsList* const AList)/* overload */;
	bool __fastcall DiscoverDevices(int ATimeout, GUID *AList, const int AList_High)/* overload */;
	bool __fastcall DiscoverDevices(unsigned ATimeout, System::Bluetooth::TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList)/* overload */;
	bool __fastcall UnSubscribeToCharacteristic(System::Bluetooth::TBluetoothLEDevice* const ADevice, System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	void __fastcall UpdateCharacteristicValue(System::Bluetooth::TBluetoothGattCharacteristic* const ACharacteristic);
	double __fastcall RssiToDistance(int ARssi, int ATxPower, float ASignalPropagationConst);
	bool __fastcall ReadRemoteRSSI(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	bool __fastcall AddService(System::Bluetooth::TBluetoothGattService* const AService);
	__property System::Bluetooth::TBluetoothConnectionState ConnectionState = {read=GetConnectionState, nodefault};
	__property System::Bluetooth::TBluetoothGattServer* GattServer = {read=GetGattServer};
	__property System::Bluetooth::TBluetoothLEAdapter* CurrentAdapter = {read=GetCurrentAdapter};
	__property System::Bluetooth::TBluetoothLEManager* CurrentManager = {read=GetCurrentManager};
	__property System::Bluetooth::TBluetoothLEDeviceList* DiscoveredDevices = {read=GetDiscoveredDevices};
	__property bool SupportsGattClient = {read=GetSupportsGattClient, nodefault};
	__property bool SupportsGattServer = {read=GetSupportsGattServer, nodefault};
	__property bool ForceRefreshCachedDevices = {read=FForceRefreshCachedDevices, write=SetForceRefreshCachedDevices, nodefault};
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
	__property System::Bluetooth::TGattCharacteristicEvent OnCharacteristicRead = {read=FOnCharacteristicRead, write=FOnCharacteristicRead};
	__property System::Bluetooth::TGattCharacteristicReadEvent OnCharacteristicReadRequest = {read=FOnCharacteristicReadRequest, write=FOnCharacteristicReadRequest};
	__property System::Bluetooth::TGattCharacteristicEvent OnCharacteristicWrite = {read=FOnCharacteristicWrite, write=FOnCharacteristicWrite};
	__property System::Bluetooth::TGattCharacteristicWriteEvent OnCharacteristicWriteRequest = {read=FOnCharacteristicWriteRequest, write=FOnCharacteristicWriteRequest};
	__property System::Bluetooth::TGattCharacteristicSubscriptionEvent OnCharacteristicSubscribed = {read=FOnCharacteristicSubscribed, write=FOnCharacteristicSubscribed};
	__property System::Bluetooth::TGattCharacteristicSubscriptionEvent OnCharacteristicUnSubscribed = {read=FOnCharacteristicUnSubscribed, write=FOnCharacteristicUnSubscribed};
	__property System::Bluetooth::TConnectLEDeviceEvent OnConnectedDevice = {read=FOnConnectedDevice, write=FOnConnectedDevice};
	__property System::Bluetooth::TGattDescriptorEvent OnDescriptorRead = {read=FOnDescriptorRead, write=FOnDescriptorRead};
	__property System::Bluetooth::TGattDescriptorEvent OnDescriptorWrite = {read=FOnDescriptorWrite, write=FOnDescriptorWrite};
	__property System::Classes::TNotifyEvent OnConnect = {read=FOnConnect, write=FOnConnect};
	__property System::Classes::TNotifyEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property System::Bluetooth::TConnectLEDeviceEvent OnDisconnectDevice = {read=FOnDisconnectDevice, write=FOnDisconnectDevice};
	__property System::Bluetooth::TDiscoverLEDeviceEvent OnDiscoverLEDevice = {read=FOnDiscoverLEDevice, write=FOnDiscoverLEDevice};
	__property System::Bluetooth::TDiscoverServicesEvent OnServicesDiscovered = {read=FOnServicesDiscovered, write=FOnServicesDiscovered};
	__property System::Bluetooth::TDiscoveryLEEndEvent OnEndDiscoverDevices = {read=FOnEndDiscoverDevices, write=FOnEndDiscoverDevices};
	__property System::Bluetooth::TDiscoverServicesEvent OnEndDiscoverServices = {read=FOnEndDiscoverServices, write=FOnEndDiscoverServices};
	__property System::Bluetooth::TGattDeviceRSSIEvent OnReadRSSI = {read=FOnReadRSSI, write=FOnReadRSSI};
	__property System::Bluetooth::TGattOperationResultEvent OnReliableWriteCompleted = {read=FOnReliableWriteCompleted, write=FOnReliableWriteCompleted};
	__property System::Bluetooth::TGattServiceEvent OnServiceAdded = {read=FOnServiceAdded, write=FOnServiceAdded};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Components */
}	/* namespace Bluetooth */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BLUETOOTH_COMPONENTS)
using namespace System::Bluetooth::Components;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BLUETOOTH)
using namespace System::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Bluetooth_ComponentsHPP
