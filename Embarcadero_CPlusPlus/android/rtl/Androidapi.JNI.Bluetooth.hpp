// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Bluetooth.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_BluetoothHPP
#define Androidapi_Jni_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JBluetoothA2dpClass;
typedef System::DelphiInterface<JBluetoothA2dpClass> _di_JBluetoothA2dpClass;
__interface DELPHIINTERFACE JBluetoothA2dp;
typedef System::DelphiInterface<JBluetoothA2dp> _di_JBluetoothA2dp;
class DELPHICLASS TJBluetoothA2dp;
__interface DELPHIINTERFACE JBluetoothAdapterClass;
typedef System::DelphiInterface<JBluetoothAdapterClass> _di_JBluetoothAdapterClass;
__interface DELPHIINTERFACE JBluetoothAdapter;
typedef System::DelphiInterface<JBluetoothAdapter> _di_JBluetoothAdapter;
class DELPHICLASS TJBluetoothAdapter;
__interface DELPHIINTERFACE JBluetoothAdapter_LeScanCallbackClass;
typedef System::DelphiInterface<JBluetoothAdapter_LeScanCallbackClass> _di_JBluetoothAdapter_LeScanCallbackClass;
__interface DELPHIINTERFACE JBluetoothAdapter_LeScanCallback;
typedef System::DelphiInterface<JBluetoothAdapter_LeScanCallback> _di_JBluetoothAdapter_LeScanCallback;
class DELPHICLASS TJBluetoothAdapter_LeScanCallback;
__interface DELPHIINTERFACE JBluetoothAssignedNumbersClass;
typedef System::DelphiInterface<JBluetoothAssignedNumbersClass> _di_JBluetoothAssignedNumbersClass;
__interface DELPHIINTERFACE JBluetoothAssignedNumbers;
typedef System::DelphiInterface<JBluetoothAssignedNumbers> _di_JBluetoothAssignedNumbers;
class DELPHICLASS TJBluetoothAssignedNumbers;
__interface DELPHIINTERFACE Jbluetooth_BluetoothClassClass;
typedef System::DelphiInterface<Jbluetooth_BluetoothClassClass> _di_Jbluetooth_BluetoothClassClass;
__interface DELPHIINTERFACE Jbluetooth_BluetoothClass;
typedef System::DelphiInterface<Jbluetooth_BluetoothClass> _di_Jbluetooth_BluetoothClass;
class DELPHICLASS TJbluetooth_BluetoothClass;
__interface DELPHIINTERFACE JBluetoothClass_DeviceClass;
typedef System::DelphiInterface<JBluetoothClass_DeviceClass> _di_JBluetoothClass_DeviceClass;
__interface DELPHIINTERFACE JBluetoothClass_Device;
typedef System::DelphiInterface<JBluetoothClass_Device> _di_JBluetoothClass_Device;
class DELPHICLASS TJBluetoothClass_Device;
__interface DELPHIINTERFACE JDevice_MajorClass;
typedef System::DelphiInterface<JDevice_MajorClass> _di_JDevice_MajorClass;
__interface DELPHIINTERFACE JDevice_Major;
typedef System::DelphiInterface<JDevice_Major> _di_JDevice_Major;
class DELPHICLASS TJDevice_Major;
__interface DELPHIINTERFACE JBluetoothClass_ServiceClass;
typedef System::DelphiInterface<JBluetoothClass_ServiceClass> _di_JBluetoothClass_ServiceClass;
__interface DELPHIINTERFACE JBluetoothClass_Service;
typedef System::DelphiInterface<JBluetoothClass_Service> _di_JBluetoothClass_Service;
class DELPHICLASS TJBluetoothClass_Service;
__interface DELPHIINTERFACE JBluetoothDeviceClass;
typedef System::DelphiInterface<JBluetoothDeviceClass> _di_JBluetoothDeviceClass;
__interface DELPHIINTERFACE JBluetoothDevice;
typedef System::DelphiInterface<JBluetoothDevice> _di_JBluetoothDevice;
class DELPHICLASS TJBluetoothDevice;
__interface DELPHIINTERFACE JBluetoothGattClass;
typedef System::DelphiInterface<JBluetoothGattClass> _di_JBluetoothGattClass;
__interface DELPHIINTERFACE JBluetoothGatt;
typedef System::DelphiInterface<JBluetoothGatt> _di_JBluetoothGatt;
class DELPHICLASS TJBluetoothGatt;
__interface DELPHIINTERFACE JBluetoothGattCallbackClass;
typedef System::DelphiInterface<JBluetoothGattCallbackClass> _di_JBluetoothGattCallbackClass;
__interface DELPHIINTERFACE JBluetoothGattCallback;
typedef System::DelphiInterface<JBluetoothGattCallback> _di_JBluetoothGattCallback;
class DELPHICLASS TJBluetoothGattCallback;
__interface DELPHIINTERFACE JBluetoothGattCharacteristicClass;
typedef System::DelphiInterface<JBluetoothGattCharacteristicClass> _di_JBluetoothGattCharacteristicClass;
__interface DELPHIINTERFACE JBluetoothGattCharacteristic;
typedef System::DelphiInterface<JBluetoothGattCharacteristic> _di_JBluetoothGattCharacteristic;
class DELPHICLASS TJBluetoothGattCharacteristic;
__interface DELPHIINTERFACE JBluetoothGattDescriptorClass;
typedef System::DelphiInterface<JBluetoothGattDescriptorClass> _di_JBluetoothGattDescriptorClass;
__interface DELPHIINTERFACE JBluetoothGattDescriptor;
typedef System::DelphiInterface<JBluetoothGattDescriptor> _di_JBluetoothGattDescriptor;
class DELPHICLASS TJBluetoothGattDescriptor;
__interface DELPHIINTERFACE JBluetoothGattServerClass;
typedef System::DelphiInterface<JBluetoothGattServerClass> _di_JBluetoothGattServerClass;
__interface DELPHIINTERFACE JBluetoothGattServer;
typedef System::DelphiInterface<JBluetoothGattServer> _di_JBluetoothGattServer;
class DELPHICLASS TJBluetoothGattServer;
__interface DELPHIINTERFACE JBluetoothGattServerCallbackClass;
typedef System::DelphiInterface<JBluetoothGattServerCallbackClass> _di_JBluetoothGattServerCallbackClass;
__interface DELPHIINTERFACE JBluetoothGattServerCallback;
typedef System::DelphiInterface<JBluetoothGattServerCallback> _di_JBluetoothGattServerCallback;
class DELPHICLASS TJBluetoothGattServerCallback;
__interface DELPHIINTERFACE JBluetoothGattServiceClass;
typedef System::DelphiInterface<JBluetoothGattServiceClass> _di_JBluetoothGattServiceClass;
__interface DELPHIINTERFACE JBluetoothGattService;
typedef System::DelphiInterface<JBluetoothGattService> _di_JBluetoothGattService;
class DELPHICLASS TJBluetoothGattService;
__interface DELPHIINTERFACE JBluetoothHeadsetClass;
typedef System::DelphiInterface<JBluetoothHeadsetClass> _di_JBluetoothHeadsetClass;
__interface DELPHIINTERFACE JBluetoothHeadset;
typedef System::DelphiInterface<JBluetoothHeadset> _di_JBluetoothHeadset;
class DELPHICLASS TJBluetoothHeadset;
__interface DELPHIINTERFACE JBluetoothHealthClass;
typedef System::DelphiInterface<JBluetoothHealthClass> _di_JBluetoothHealthClass;
__interface DELPHIINTERFACE JBluetoothHealth;
typedef System::DelphiInterface<JBluetoothHealth> _di_JBluetoothHealth;
class DELPHICLASS TJBluetoothHealth;
__interface DELPHIINTERFACE JBluetoothHealthAppConfigurationClass;
typedef System::DelphiInterface<JBluetoothHealthAppConfigurationClass> _di_JBluetoothHealthAppConfigurationClass;
__interface DELPHIINTERFACE JBluetoothHealthAppConfiguration;
typedef System::DelphiInterface<JBluetoothHealthAppConfiguration> _di_JBluetoothHealthAppConfiguration;
class DELPHICLASS TJBluetoothHealthAppConfiguration;
__interface DELPHIINTERFACE JBluetoothHealthCallbackClass;
typedef System::DelphiInterface<JBluetoothHealthCallbackClass> _di_JBluetoothHealthCallbackClass;
__interface DELPHIINTERFACE JBluetoothHealthCallback;
typedef System::DelphiInterface<JBluetoothHealthCallback> _di_JBluetoothHealthCallback;
class DELPHICLASS TJBluetoothHealthCallback;
__interface DELPHIINTERFACE JBluetoothManagerClass;
typedef System::DelphiInterface<JBluetoothManagerClass> _di_JBluetoothManagerClass;
__interface DELPHIINTERFACE JBluetoothManager;
typedef System::DelphiInterface<JBluetoothManager> _di_JBluetoothManager;
class DELPHICLASS TJBluetoothManager;
__interface DELPHIINTERFACE JBluetoothProfileClass;
typedef System::DelphiInterface<JBluetoothProfileClass> _di_JBluetoothProfileClass;
__interface DELPHIINTERFACE JBluetoothProfile;
typedef System::DelphiInterface<JBluetoothProfile> _di_JBluetoothProfile;
class DELPHICLASS TJBluetoothProfile;
__interface DELPHIINTERFACE JBluetoothProfile_ServiceListenerClass;
typedef System::DelphiInterface<JBluetoothProfile_ServiceListenerClass> _di_JBluetoothProfile_ServiceListenerClass;
__interface DELPHIINTERFACE JBluetoothProfile_ServiceListener;
typedef System::DelphiInterface<JBluetoothProfile_ServiceListener> _di_JBluetoothProfile_ServiceListener;
class DELPHICLASS TJBluetoothProfile_ServiceListener;
__interface DELPHIINTERFACE JBluetoothServerSocketClass;
typedef System::DelphiInterface<JBluetoothServerSocketClass> _di_JBluetoothServerSocketClass;
__interface DELPHIINTERFACE JBluetoothServerSocket;
typedef System::DelphiInterface<JBluetoothServerSocket> _di_JBluetoothServerSocket;
class DELPHICLASS TJBluetoothServerSocket;
__interface DELPHIINTERFACE JBluetoothSocketClass;
typedef System::DelphiInterface<JBluetoothSocketClass> _di_JBluetoothSocketClass;
__interface DELPHIINTERFACE JBluetoothSocket;
typedef System::DelphiInterface<JBluetoothSocket> _di_JBluetoothSocket;
class DELPHICLASS TJBluetoothSocket;
__interface DELPHIINTERFACE JRTLBluetoothGattCallbackClass;
typedef System::DelphiInterface<JRTLBluetoothGattCallbackClass> _di_JRTLBluetoothGattCallbackClass;
__interface DELPHIINTERFACE JRTLBluetoothGattCallback;
typedef System::DelphiInterface<JRTLBluetoothGattCallback> _di_JRTLBluetoothGattCallback;
class DELPHICLASS TJRTLBluetoothGattCallback;
__interface DELPHIINTERFACE JRTLBluetoothGattListenerClass;
typedef System::DelphiInterface<JRTLBluetoothGattListenerClass> _di_JRTLBluetoothGattListenerClass;
__interface DELPHIINTERFACE JRTLBluetoothGattListener;
typedef System::DelphiInterface<JRTLBluetoothGattListener> _di_JRTLBluetoothGattListener;
class DELPHICLASS TJRTLBluetoothGattListener;
__interface DELPHIINTERFACE JRTLBluetoothGattServerCallbackClass;
typedef System::DelphiInterface<JRTLBluetoothGattServerCallbackClass> _di_JRTLBluetoothGattServerCallbackClass;
__interface DELPHIINTERFACE JRTLBluetoothGattServerCallback;
typedef System::DelphiInterface<JRTLBluetoothGattServerCallback> _di_JRTLBluetoothGattServerCallback;
class DELPHICLASS TJRTLBluetoothGattServerCallback;
__interface DELPHIINTERFACE JRTLBluetoothGattServerListenerClass;
typedef System::DelphiInterface<JRTLBluetoothGattServerListenerClass> _di_JRTLBluetoothGattServerListenerClass;
__interface DELPHIINTERFACE JRTLBluetoothGattServerListener;
typedef System::DelphiInterface<JRTLBluetoothGattServerListener> _di_JRTLBluetoothGattServerListener;
class DELPHICLASS TJRTLBluetoothGattServerListener;
__interface DELPHIINTERFACE JAdvertiseCallbackClass;
typedef System::DelphiInterface<JAdvertiseCallbackClass> _di_JAdvertiseCallbackClass;
__interface DELPHIINTERFACE JAdvertiseCallback;
typedef System::DelphiInterface<JAdvertiseCallback> _di_JAdvertiseCallback;
class DELPHICLASS TJAdvertiseCallback;
__interface DELPHIINTERFACE JAdvertiseDataClass;
typedef System::DelphiInterface<JAdvertiseDataClass> _di_JAdvertiseDataClass;
__interface DELPHIINTERFACE JAdvertiseData;
typedef System::DelphiInterface<JAdvertiseData> _di_JAdvertiseData;
class DELPHICLASS TJAdvertiseData;
__interface DELPHIINTERFACE JAdvertiseData_BuilderClass;
typedef System::DelphiInterface<JAdvertiseData_BuilderClass> _di_JAdvertiseData_BuilderClass;
__interface DELPHIINTERFACE JAdvertiseData_Builder;
typedef System::DelphiInterface<JAdvertiseData_Builder> _di_JAdvertiseData_Builder;
class DELPHICLASS TJAdvertiseData_Builder;
__interface DELPHIINTERFACE JAdvertiseSettingsClass;
typedef System::DelphiInterface<JAdvertiseSettingsClass> _di_JAdvertiseSettingsClass;
__interface DELPHIINTERFACE JAdvertiseSettings;
typedef System::DelphiInterface<JAdvertiseSettings> _di_JAdvertiseSettings;
class DELPHICLASS TJAdvertiseSettings;
__interface DELPHIINTERFACE JAdvertiseSettings_BuilderClass;
typedef System::DelphiInterface<JAdvertiseSettings_BuilderClass> _di_JAdvertiseSettings_BuilderClass;
__interface DELPHIINTERFACE JAdvertiseSettings_Builder;
typedef System::DelphiInterface<JAdvertiseSettings_Builder> _di_JAdvertiseSettings_Builder;
class DELPHICLASS TJAdvertiseSettings_Builder;
__interface DELPHIINTERFACE JAdvertisingSetClass;
typedef System::DelphiInterface<JAdvertisingSetClass> _di_JAdvertisingSetClass;
__interface DELPHIINTERFACE JAdvertisingSet;
typedef System::DelphiInterface<JAdvertisingSet> _di_JAdvertisingSet;
class DELPHICLASS TJAdvertisingSet;
__interface DELPHIINTERFACE JAdvertisingSetCallbackClass;
typedef System::DelphiInterface<JAdvertisingSetCallbackClass> _di_JAdvertisingSetCallbackClass;
__interface DELPHIINTERFACE JAdvertisingSetCallback;
typedef System::DelphiInterface<JAdvertisingSetCallback> _di_JAdvertisingSetCallback;
class DELPHICLASS TJAdvertisingSetCallback;
__interface DELPHIINTERFACE JAdvertisingSetParametersClass;
typedef System::DelphiInterface<JAdvertisingSetParametersClass> _di_JAdvertisingSetParametersClass;
__interface DELPHIINTERFACE JAdvertisingSetParameters;
typedef System::DelphiInterface<JAdvertisingSetParameters> _di_JAdvertisingSetParameters;
class DELPHICLASS TJAdvertisingSetParameters;
__interface DELPHIINTERFACE JAdvertisingSetParameters_BuilderClass;
typedef System::DelphiInterface<JAdvertisingSetParameters_BuilderClass> _di_JAdvertisingSetParameters_BuilderClass;
__interface DELPHIINTERFACE JAdvertisingSetParameters_Builder;
typedef System::DelphiInterface<JAdvertisingSetParameters_Builder> _di_JAdvertisingSetParameters_Builder;
class DELPHICLASS TJAdvertisingSetParameters_Builder;
__interface DELPHIINTERFACE JBluetoothLeAdvertiserClass;
typedef System::DelphiInterface<JBluetoothLeAdvertiserClass> _di_JBluetoothLeAdvertiserClass;
__interface DELPHIINTERFACE JBluetoothLeAdvertiser;
typedef System::DelphiInterface<JBluetoothLeAdvertiser> _di_JBluetoothLeAdvertiser;
class DELPHICLASS TJBluetoothLeAdvertiser;
__interface DELPHIINTERFACE JBluetoothLeScannerClass;
typedef System::DelphiInterface<JBluetoothLeScannerClass> _di_JBluetoothLeScannerClass;
__interface DELPHIINTERFACE JBluetoothLeScanner;
typedef System::DelphiInterface<JBluetoothLeScanner> _di_JBluetoothLeScanner;
class DELPHICLASS TJBluetoothLeScanner;
__interface DELPHIINTERFACE JPeriodicAdvertisingParametersClass;
typedef System::DelphiInterface<JPeriodicAdvertisingParametersClass> _di_JPeriodicAdvertisingParametersClass;
__interface DELPHIINTERFACE JPeriodicAdvertisingParameters;
typedef System::DelphiInterface<JPeriodicAdvertisingParameters> _di_JPeriodicAdvertisingParameters;
class DELPHICLASS TJPeriodicAdvertisingParameters;
__interface DELPHIINTERFACE JPeriodicAdvertisingParameters_BuilderClass;
typedef System::DelphiInterface<JPeriodicAdvertisingParameters_BuilderClass> _di_JPeriodicAdvertisingParameters_BuilderClass;
__interface DELPHIINTERFACE JPeriodicAdvertisingParameters_Builder;
typedef System::DelphiInterface<JPeriodicAdvertisingParameters_Builder> _di_JPeriodicAdvertisingParameters_Builder;
class DELPHICLASS TJPeriodicAdvertisingParameters_Builder;
__interface DELPHIINTERFACE JRTLAdvertiseCallbackClass;
typedef System::DelphiInterface<JRTLAdvertiseCallbackClass> _di_JRTLAdvertiseCallbackClass;
__interface DELPHIINTERFACE JRTLAdvertiseCallback;
typedef System::DelphiInterface<JRTLAdvertiseCallback> _di_JRTLAdvertiseCallback;
class DELPHICLASS TJRTLAdvertiseCallback;
__interface DELPHIINTERFACE JRTLAdvertiseListenerClass;
typedef System::DelphiInterface<JRTLAdvertiseListenerClass> _di_JRTLAdvertiseListenerClass;
__interface DELPHIINTERFACE JRTLAdvertiseListener;
typedef System::DelphiInterface<JRTLAdvertiseListener> _di_JRTLAdvertiseListener;
class DELPHICLASS TJRTLAdvertiseListener;
__interface DELPHIINTERFACE JScanCallbackClass;
typedef System::DelphiInterface<JScanCallbackClass> _di_JScanCallbackClass;
__interface DELPHIINTERFACE JScanCallback;
typedef System::DelphiInterface<JScanCallback> _di_JScanCallback;
class DELPHICLASS TJScanCallback;
__interface DELPHIINTERFACE JRTLScanCallbackClass;
typedef System::DelphiInterface<JRTLScanCallbackClass> _di_JRTLScanCallbackClass;
__interface DELPHIINTERFACE JRTLScanCallback;
typedef System::DelphiInterface<JRTLScanCallback> _di_JRTLScanCallback;
class DELPHICLASS TJRTLScanCallback;
__interface DELPHIINTERFACE JRTLScanListenerClass;
typedef System::DelphiInterface<JRTLScanListenerClass> _di_JRTLScanListenerClass;
__interface DELPHIINTERFACE JRTLScanListener;
typedef System::DelphiInterface<JRTLScanListener> _di_JRTLScanListener;
class DELPHICLASS TJRTLScanListener;
__interface DELPHIINTERFACE JScanFilterClass;
typedef System::DelphiInterface<JScanFilterClass> _di_JScanFilterClass;
__interface DELPHIINTERFACE JScanFilter;
typedef System::DelphiInterface<JScanFilter> _di_JScanFilter;
class DELPHICLASS TJScanFilter;
__interface DELPHIINTERFACE JScanFilter_BuilderClass;
typedef System::DelphiInterface<JScanFilter_BuilderClass> _di_JScanFilter_BuilderClass;
__interface DELPHIINTERFACE JScanFilter_Builder;
typedef System::DelphiInterface<JScanFilter_Builder> _di_JScanFilter_Builder;
class DELPHICLASS TJScanFilter_Builder;
__interface DELPHIINTERFACE JScanRecordClass;
typedef System::DelphiInterface<JScanRecordClass> _di_JScanRecordClass;
__interface DELPHIINTERFACE JScanRecord;
typedef System::DelphiInterface<JScanRecord> _di_JScanRecord;
class DELPHICLASS TJScanRecord;
__interface DELPHIINTERFACE Jle_ScanResultClass;
typedef System::DelphiInterface<Jle_ScanResultClass> _di_Jle_ScanResultClass;
__interface DELPHIINTERFACE Jle_ScanResult;
typedef System::DelphiInterface<Jle_ScanResult> _di_Jle_ScanResult;
class DELPHICLASS TJle_ScanResult;
__interface DELPHIINTERFACE JScanSettingsClass;
typedef System::DelphiInterface<JScanSettingsClass> _di_JScanSettingsClass;
__interface DELPHIINTERFACE JScanSettings;
typedef System::DelphiInterface<JScanSettings> _di_JScanSettings;
class DELPHICLASS TJScanSettings;
__interface DELPHIINTERFACE JScanSettings_BuilderClass;
typedef System::DelphiInterface<JScanSettings_BuilderClass> _di_JScanSettings_BuilderClass;
__interface DELPHIINTERFACE JScanSettings_Builder;
typedef System::DelphiInterface<JScanSettings_Builder> _di_JScanSettings_Builder;
class DELPHICLASS TJScanSettings_Builder;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{2B9E047D-CF63-4A9C-97A9-C4F372207C86}") JBluetoothA2dpClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CONNECTION_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_PLAYING_STATE_CHANGED() = 0 ;
	virtual int __cdecl _GetSTATE_NOT_PLAYING() = 0 ;
	virtual int __cdecl _GetSTATE_PLAYING() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CONNECTION_STATE_CHANGED = {read=_GetACTION_CONNECTION_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_PLAYING_STATE_CHANGED = {read=_GetACTION_PLAYING_STATE_CHANGED};
	__property int STATE_NOT_PLAYING = {read=_GetSTATE_NOT_PLAYING};
	__property int STATE_PLAYING = {read=_GetSTATE_PLAYING};
};

__interface  INTERFACE_UUID("{61C30A48-9578-4FDA-B2A4-B748DB7A55DE}") JBluetoothA2dp  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl finalize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual bool __cdecl isA2dpPlaying(_di_JBluetoothDevice device) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothA2dp : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothA2dpClass,_di_JBluetoothA2dp>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothA2dpClass,_di_JBluetoothA2dp> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothA2dp() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothA2dpClass,_di_JBluetoothA2dp>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothA2dp() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7C08F8A8-7F06-4797-BECA-F5C4564BAEEC}") JBluetoothAdapterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CONNECTION_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DISCOVERY_FINISHED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DISCOVERY_STARTED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_LOCAL_NAME_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_REQUEST_DISCOVERABLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_REQUEST_ENABLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_SCAN_MODE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_STATE_CHANGED() = 0 ;
	virtual int __cdecl _GetERROR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CONNECTION_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_DISCOVERABLE_DURATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LOCAL_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREVIOUS_CONNECTION_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREVIOUS_SCAN_MODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREVIOUS_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SCAN_MODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_CONNECTABLE() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_CONNECTABLE_DISCOVERABLE() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_NONE() = 0 ;
	virtual int __cdecl _GetSTATE_CONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_CONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_DISCONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_DISCONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_OFF() = 0 ;
	virtual int __cdecl _GetSTATE_ON() = 0 ;
	virtual int __cdecl _GetSTATE_TURNING_OFF() = 0 ;
	virtual int __cdecl _GetSTATE_TURNING_ON() = 0 ;
	virtual bool __cdecl checkBluetoothAddress(Androidapi::Jni::Javatypes::_di_JString address) = 0 ;
	virtual _di_JBluetoothAdapter __cdecl getDefaultAdapter() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CONNECTION_STATE_CHANGED = {read=_GetACTION_CONNECTION_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DISCOVERY_FINISHED = {read=_GetACTION_DISCOVERY_FINISHED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DISCOVERY_STARTED = {read=_GetACTION_DISCOVERY_STARTED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_LOCAL_NAME_CHANGED = {read=_GetACTION_LOCAL_NAME_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_REQUEST_DISCOVERABLE = {read=_GetACTION_REQUEST_DISCOVERABLE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_REQUEST_ENABLE = {read=_GetACTION_REQUEST_ENABLE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_SCAN_MODE_CHANGED = {read=_GetACTION_SCAN_MODE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_STATE_CHANGED = {read=_GetACTION_STATE_CHANGED};
	__property int ERROR = {read=_GetERROR};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CONNECTION_STATE = {read=_GetEXTRA_CONNECTION_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_DISCOVERABLE_DURATION = {read=_GetEXTRA_DISCOVERABLE_DURATION};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LOCAL_NAME = {read=_GetEXTRA_LOCAL_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREVIOUS_CONNECTION_STATE = {read=_GetEXTRA_PREVIOUS_CONNECTION_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREVIOUS_SCAN_MODE = {read=_GetEXTRA_PREVIOUS_SCAN_MODE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREVIOUS_STATE = {read=_GetEXTRA_PREVIOUS_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SCAN_MODE = {read=_GetEXTRA_SCAN_MODE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE = {read=_GetEXTRA_STATE};
	__property int SCAN_MODE_CONNECTABLE = {read=_GetSCAN_MODE_CONNECTABLE};
	__property int SCAN_MODE_CONNECTABLE_DISCOVERABLE = {read=_GetSCAN_MODE_CONNECTABLE_DISCOVERABLE};
	__property int SCAN_MODE_NONE = {read=_GetSCAN_MODE_NONE};
	__property int STATE_CONNECTED = {read=_GetSTATE_CONNECTED};
	__property int STATE_CONNECTING = {read=_GetSTATE_CONNECTING};
	__property int STATE_DISCONNECTED = {read=_GetSTATE_DISCONNECTED};
	__property int STATE_DISCONNECTING = {read=_GetSTATE_DISCONNECTING};
	__property int STATE_OFF = {read=_GetSTATE_OFF};
	__property int STATE_ON = {read=_GetSTATE_ON};
	__property int STATE_TURNING_OFF = {read=_GetSTATE_TURNING_OFF};
	__property int STATE_TURNING_ON = {read=_GetSTATE_TURNING_ON};
};

__interface  INTERFACE_UUID("{3C62EC75-B2D5-4F6F-820C-02222EA05B54}") JBluetoothAdapter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl cancelDiscovery() = 0 ;
	virtual void __cdecl closeProfileProxy(int profile, _di_JBluetoothProfile proxy) = 0 ;
	virtual bool __cdecl disable() = 0 ;
	virtual bool __cdecl enable() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAddress() = 0 ;
	virtual _di_JBluetoothLeAdvertiser __cdecl getBluetoothLeAdvertiser() = 0 ;
	virtual _di_JBluetoothLeScanner __cdecl getBluetoothLeScanner() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getBondedDevices() = 0 ;
	virtual int __cdecl getLeMaximumAdvertisingDataLength() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getProfileConnectionState(int profile) = 0 ;
	virtual bool __cdecl getProfileProxy(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JBluetoothProfile_ServiceListener listener, int profile) = 0 ;
	virtual _di_JBluetoothDevice __cdecl getRemoteDevice(Androidapi::Jni::Javatypes::_di_JString address) = 0 /* overload */;
	virtual _di_JBluetoothDevice __cdecl getRemoteDevice(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* address) = 0 /* overload */;
	virtual int __cdecl getScanMode() = 0 ;
	virtual int __cdecl getState() = 0 ;
	virtual bool __cdecl isDiscovering() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isLe2MPhySupported() = 0 ;
	virtual bool __cdecl isLeCodedPhySupported() = 0 ;
	virtual bool __cdecl isLeExtendedAdvertisingSupported() = 0 ;
	virtual bool __cdecl isLePeriodicAdvertisingSupported() = 0 ;
	virtual bool __cdecl isMultipleAdvertisementSupported() = 0 ;
	virtual bool __cdecl isOffloadedFilteringSupported() = 0 ;
	virtual bool __cdecl isOffloadedScanBatchingSupported() = 0 ;
	virtual _di_JBluetoothServerSocket __cdecl listenUsingInsecureRfcommWithServiceRecord(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual _di_JBluetoothServerSocket __cdecl listenUsingRfcommWithServiceRecord(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual bool __cdecl setName(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual bool __cdecl startDiscovery() = 0 ;
	virtual bool __cdecl startLeScan(_di_JBluetoothAdapter_LeScanCallback callback) = 0 /* overload */;
	virtual bool __cdecl startLeScan(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JUUID>* serviceUuids, _di_JBluetoothAdapter_LeScanCallback callback) = 0 /* overload */;
	virtual void __cdecl stopLeScan(_di_JBluetoothAdapter_LeScanCallback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A774D140-5BD1-4EAC-98B8-1124178FFE47}") JBluetoothAdapter_LeScanCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A520E11B-267D-4EA6-850B-3074F1C11D95}") JBluetoothAdapter_LeScanCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onLeScan(_di_JBluetoothDevice device, int rssi, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* scanRecord) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothAdapter_LeScanCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapter_LeScanCallbackClass,_di_JBluetoothAdapter_LeScanCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapter_LeScanCallbackClass,_di_JBluetoothAdapter_LeScanCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothAdapter_LeScanCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapter_LeScanCallbackClass,_di_JBluetoothAdapter_LeScanCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothAdapter_LeScanCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C5F0EBA1-1D77-43F6-B645-EF5A5D248FE7}") JBluetoothAssignedNumbersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAAMP_OF_AMERICA() = 0 ;
	virtual int __cdecl _GetACCEL_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetACE_SENSOR() = 0 ;
	virtual int __cdecl _GetADIDAS() = 0 ;
	virtual int __cdecl _GetADVANCED_PANMOBIL_SYSTEMS() = 0 ;
	virtual int __cdecl _GetAIROHA_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetALCATEL() = 0 ;
	virtual int __cdecl _GetALPWISE() = 0 ;
	virtual int __cdecl _GetAMICCOM_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetAPLIX() = 0 ;
	virtual int __cdecl _GetAPPLE() = 0 ;
	virtual int __cdecl _GetAPT_LICENSING() = 0 ;
	virtual int __cdecl _GetARCHOS() = 0 ;
	virtual int __cdecl _GetARP_DEVICES() = 0 ;
	virtual int __cdecl _GetATHEROS_COMMUNICATIONS() = 0 ;
	virtual int __cdecl _GetATMEL() = 0 ;
	virtual int __cdecl _GetAUSTCO_COMMUNICATION_SYSTEMS() = 0 ;
	virtual int __cdecl _GetAUTONET_MOBILE() = 0 ;
	virtual int __cdecl _GetAVAGO() = 0 ;
	virtual int __cdecl _GetAVM_BERLIN() = 0 ;
	virtual int __cdecl _GetA_AND_D_ENGINEERING() = 0 ;
	virtual int __cdecl _GetA_AND_R_CAMBRIDGE() = 0 ;
	virtual int __cdecl _GetBANDSPEED() = 0 ;
	virtual int __cdecl _GetBAND_XI_INTERNATIONAL() = 0 ;
	virtual int __cdecl _GetBDE_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetBEATS_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetBEAUTIFUL_ENTERPRISE() = 0 ;
	virtual int __cdecl _GetBEKEY() = 0 ;
	virtual int __cdecl _GetBELKIN_INTERNATIONAL() = 0 ;
	virtual int __cdecl _GetBINAURIC() = 0 ;
	virtual int __cdecl _GetBIOSENTRONICS() = 0 ;
	virtual int __cdecl _GetBLUEGIGA() = 0 ;
	virtual int __cdecl _GetBLUERADIOS() = 0 ;
	virtual int __cdecl _GetBLUETOOTH_SIG() = 0 ;
	virtual int __cdecl _GetBLUETREK_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetBOSE() = 0 ;
	virtual int __cdecl _GetBRIARTEK() = 0 ;
	virtual int __cdecl _GetBROADCOM() = 0 ;
	virtual int __cdecl _GetCAEN_RFID() = 0 ;
	virtual int __cdecl _GetCAMBRIDGE_SILICON_RADIO() = 0 ;
	virtual int __cdecl _GetCATC() = 0 ;
	virtual int __cdecl _GetCINETIX() = 0 ;
	virtual int __cdecl _GetCLARINOX_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetCOLORFY() = 0 ;
	virtual int __cdecl _GetCOMMIL() = 0 ;
	virtual int __cdecl _GetCONEXANT_SYSTEMS() = 0 ;
	virtual int __cdecl _GetCONNECTBLUE() = 0 ;
	virtual int __cdecl _GetCONTINENTAL_AUTOMOTIVE() = 0 ;
	virtual int __cdecl _GetCONWISE_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetCREATIVE_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetC_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetDANLERS() = 0 ;
	virtual int __cdecl _GetDELORME_PUBLISHING_COMPANY() = 0 ;
	virtual int __cdecl _GetDEXCOM() = 0 ;
	virtual int __cdecl _GetDIALOG_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetDIGIANSWER() = 0 ;
	virtual int __cdecl _GetECLIPSE() = 0 ;
	virtual int __cdecl _GetECOTEST() = 0 ;
	virtual int __cdecl _GetELGATO_SYSTEMS() = 0 ;
	virtual int __cdecl _GetEM_MICROELECTRONIC_MARIN() = 0 ;
	virtual int __cdecl _GetEQUINOX_AG() = 0 ;
	virtual int __cdecl _GetERICSSON_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetEVLUMA() = 0 ;
	virtual int __cdecl _GetFREE2MOVE() = 0 ;
	virtual int __cdecl _GetFUNAI_ELECTRIC() = 0 ;
	virtual int __cdecl _GetGARMIN_INTERNATIONAL() = 0 ;
	virtual int __cdecl _GetGCT_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetGELO() = 0 ;
	virtual int __cdecl _GetGENEQ() = 0 ;
	virtual int __cdecl _GetGENERAL_MOTORS() = 0 ;
	virtual int __cdecl _GetGENNUM() = 0 ;
	virtual int __cdecl _GetGEOFORCE() = 0 ;
	virtual int __cdecl _GetGIBSON_GUITARS() = 0 ;
	virtual int __cdecl _GetGN_NETCOM() = 0 ;
	virtual int __cdecl _GetGN_RESOUND() = 0 ;
	virtual int __cdecl _GetGOOGLE() = 0 ;
	virtual int __cdecl _GetGREEN_THROTTLE_GAMES() = 0 ;
	virtual int __cdecl _GetGROUP_SENSE() = 0 ;
	virtual int __cdecl _GetHANLYNN_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetHARMAN_INTERNATIONAL() = 0 ;
	virtual int __cdecl _GetHEWLETT_PACKARD() = 0 ;
	virtual int __cdecl _GetHITACHI() = 0 ;
	virtual int __cdecl _GetHOSIDEN() = 0 ;
	virtual int __cdecl _GetIBM() = 0 ;
	virtual int __cdecl _GetINFINEON_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetINGENIEUR_SYSTEMGRUPPE_ZAHN() = 0 ;
	virtual int __cdecl _GetINTEGRATED_SILICON_SOLUTION() = 0 ;
	virtual int __cdecl _GetINTEGRATED_SYSTEM_SOLUTION() = 0 ;
	virtual int __cdecl _GetINTEL() = 0 ;
	virtual int __cdecl _GetINVENTEL() = 0 ;
	virtual int __cdecl _GetIPEXTREME() = 0 ;
	virtual int __cdecl _GetI_TECH_DYNAMIC_GLOBAL_DISTRIBUTION() = 0 ;
	virtual int __cdecl _GetJAWBONE() = 0 ;
	virtual int __cdecl _GetJIANGSU_TOPPOWER_AUTOMOTIVE_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetJOHNSON_CONTROLS() = 0 ;
	virtual int __cdecl _GetJ_AND_M() = 0 ;
	virtual int __cdecl _GetKAWANTECH() = 0 ;
	virtual int __cdecl _GetKC_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetKENSINGTON_COMPUTER_PRODUCTS_GROUP() = 0 ;
	virtual int __cdecl _GetLAIRD_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetLESSWIRE() = 0 ;
	virtual int __cdecl _GetLG_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetLINAK() = 0 ;
	virtual int __cdecl _GetLUCENT() = 0 ;
	virtual int __cdecl _GetLUDUS_HELSINKI() = 0 ;
	virtual int __cdecl _GetMACRONIX() = 0 ;
	virtual int __cdecl _GetMAGNETI_MARELLI() = 0 ;
	virtual int __cdecl _GetMANSELLA() = 0 ;
	virtual int __cdecl _GetMARVELL() = 0 ;
	virtual int __cdecl _GetMATSUSHITA_ELECTRIC() = 0 ;
	virtual int __cdecl _GetMC10() = 0 ;
	virtual int __cdecl _GetMEDIATEK() = 0 ;
	virtual int __cdecl _GetMESO_INTERNATIONAL() = 0 ;
	virtual int __cdecl _GetMETA_WATCH() = 0 ;
	virtual int __cdecl _GetMEWTEL_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetMICOMMAND() = 0 ;
	virtual int __cdecl _GetMICROCHIP_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetMICROSOFT() = 0 ;
	virtual int __cdecl _GetMINDTREE() = 0 ;
	virtual int __cdecl _GetMISFIT_WEARABLES() = 0 ;
	virtual int __cdecl _GetMITEL_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetMITSUBISHI_ELECTRIC() = 0 ;
	virtual int __cdecl _GetMOBILIAN_CORPORATION() = 0 ;
	virtual int __cdecl _GetMONSTER() = 0 ;
	virtual int __cdecl _GetMOTOROLA() = 0 ;
	virtual int __cdecl _GetMSTAR_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetMUZIK() = 0 ;
	virtual int __cdecl _GetNEC() = 0 ;
	virtual int __cdecl _GetNEC_LIGHTING() = 0 ;
	virtual int __cdecl _GetNEWLOGIC() = 0 ;
	virtual int __cdecl _GetNIKE() = 0 ;
	virtual int __cdecl _GetNINE_SOLUTIONS() = 0 ;
	virtual int __cdecl _GetNOKIA_MOBILE_PHONES() = 0 ;
	virtual int __cdecl _GetNORDIC_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetNORWOOD_SYSTEMS() = 0 ;
	virtual int __cdecl _GetODM_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetOMEGAWAVE() = 0 ;
	virtual int __cdecl _GetONSET_COMPUTER() = 0 ;
	virtual int __cdecl _GetOPEN_INTERFACE() = 0 ;
	virtual int __cdecl _GetOTL_DYNAMICS() = 0 ;
	virtual int __cdecl _GetPANDA_OCEAN() = 0 ;
	virtual int __cdecl _GetPARROT() = 0 ;
	virtual int __cdecl _GetPARTHUS_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetPASSIF_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetPETER_SYSTEMTECHNIK() = 0 ;
	virtual int __cdecl _GetPHILIPS_SEMICONDUCTORS() = 0 ;
	virtual int __cdecl _GetPLANTRONICS() = 0 ;
	virtual int __cdecl _GetPOLAR_ELECTRO() = 0 ;
	virtual int __cdecl _GetPOLAR_ELECTRO_EUROPE() = 0 ;
	virtual int __cdecl _GetPROCTER_AND_GAMBLE() = 0 ;
	virtual int __cdecl _GetQUALCOMM() = 0 ;
	virtual int __cdecl _GetQUALCOMM_CONNECTED_EXPERIENCES() = 0 ;
	virtual int __cdecl _GetQUALCOMM_INNOVATION_CENTER() = 0 ;
	virtual int __cdecl _GetQUALCOMM_LABS() = 0 ;
	virtual int __cdecl _GetQUALCOMM_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetQUINTIC() = 0 ;
	virtual int __cdecl _GetQUUPPA() = 0 ;
	virtual int __cdecl _GetRALINK_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetRDA_MICROELECTRONICS() = 0 ;
	virtual int __cdecl _GetREALTEK_SEMICONDUCTOR() = 0 ;
	virtual int __cdecl _GetRED_M() = 0 ;
	virtual int __cdecl _GetRENESAS_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetRESEARCH_IN_MOTION() = 0 ;
	virtual int __cdecl _GetRF_MICRO_DEVICES() = 0 ;
	virtual int __cdecl _GetRIVIERAWAVES() = 0 ;
	virtual int __cdecl _GetROHDE_AND_SCHWARZ() = 0 ;
	virtual int __cdecl _GetRTX_TELECOM() = 0 ;
	virtual int __cdecl _GetSAMSUNG_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetSARIS_CYCLING_GROUP() = 0 ;
	virtual int __cdecl _GetSEERS_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetSEIKO_EPSON() = 0 ;
	virtual int __cdecl _GetSELFLY() = 0 ;
	virtual int __cdecl _GetSEMILINK() = 0 ;
	virtual int __cdecl _GetSENNHEISER_COMMUNICATIONS() = 0 ;
	virtual int __cdecl _GetSHANGHAI_SUPER_SMART_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetSHENZHEN_EXCELSECU_DATA_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetSIGNIA_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetSILICON_WAVE() = 0 ;
	virtual int __cdecl _GetSIRF_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetSOCKET_MOBILE() = 0 ;
	virtual int __cdecl _GetSONY_ERICSSON() = 0 ;
	virtual int __cdecl _GetSOUND_ID() = 0 ;
	virtual int __cdecl _GetSPORTS_TRACKING_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetSR_MEDIZINELEKTRONIK() = 0 ;
	virtual int __cdecl _GetSTACCATO_COMMUNICATIONS() = 0 ;
	virtual int __cdecl _GetSTALMART_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetSTARKEY_LABORATORIES() = 0 ;
	virtual int __cdecl _GetSTOLLMAN_E_PLUS_V() = 0 ;
	virtual int __cdecl _GetSTONESTREET_ONE() = 0 ;
	virtual int __cdecl _GetST_MICROELECTRONICS() = 0 ;
	virtual int __cdecl _GetSUMMIT_DATA_COMMUNICATIONS() = 0 ;
	virtual int __cdecl _GetSUUNTO() = 0 ;
	virtual int __cdecl _GetSWIRL_NETWORKS() = 0 ;
	virtual int __cdecl _GetSYMBOL_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetSYNOPSYS() = 0 ;
	virtual int __cdecl _GetSYSTEMS_AND_CHIPS() = 0 ;
	virtual int __cdecl _GetS_POWER_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetTAIXINGBANG_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetTENOVIS() = 0 ;
	virtual int __cdecl _GetTERAX() = 0 ;
	virtual int __cdecl _GetTEXAS_INSTRUMENTS() = 0 ;
	virtual int __cdecl _GetTHINKOPTICS() = 0 ;
	virtual int __cdecl _GetTHREECOM() = 0 ;
	virtual int __cdecl _GetTHREE_DIJOY() = 0 ;
	virtual int __cdecl _GetTHREE_DSP() = 0 ;
	virtual int __cdecl _GetTIMEKEEPING_SYSTEMS() = 0 ;
	virtual int __cdecl _GetTIMEX_GROUP_USA() = 0 ;
	virtual int __cdecl _GetTOPCORN_POSITIONING_SYSTEMS() = 0 ;
	virtual int __cdecl _GetTOSHIBA() = 0 ;
	virtual int __cdecl _GetTRANSILICA() = 0 ;
	virtual int __cdecl _GetTRELAB() = 0 ;
	virtual int __cdecl _GetTTPCOM() = 0 ;
	virtual int __cdecl _GetTXTR() = 0 ;
	virtual int __cdecl _GetTZERO_TECHNOLOGIES() = 0 ;
	virtual int __cdecl _GetUNIVERSAL_ELECTRONICS() = 0 ;
	virtual int __cdecl _GetVERTU() = 0 ;
	virtual int __cdecl _GetVISTEON() = 0 ;
	virtual int __cdecl _GetVIZIO() = 0 ;
	virtual int __cdecl _GetVOYETRA_TURTLE_BEACH() = 0 ;
	virtual int __cdecl _GetWAVEPLUS_TECHNOLOGY() = 0 ;
	virtual int __cdecl _GetWICENTRIC() = 0 ;
	virtual int __cdecl _GetWIDCOMM() = 0 ;
	virtual int __cdecl _GetWUXI_VIMICRO() = 0 ;
	virtual int __cdecl _GetZEEVO() = 0 ;
	virtual int __cdecl _GetZER01_TV() = 0 ;
	virtual int __cdecl _GetZOMM() = 0 ;
	virtual int __cdecl _GetZSCAN_SOFTWARE() = 0 ;
	__property int AAMP_OF_AMERICA = {read=_GetAAMP_OF_AMERICA};
	__property int ACCEL_SEMICONDUCTOR = {read=_GetACCEL_SEMICONDUCTOR};
	__property int ACE_SENSOR = {read=_GetACE_SENSOR};
	__property int ADIDAS = {read=_GetADIDAS};
	__property int ADVANCED_PANMOBIL_SYSTEMS = {read=_GetADVANCED_PANMOBIL_SYSTEMS};
	__property int AIROHA_TECHNOLOGY = {read=_GetAIROHA_TECHNOLOGY};
	__property int ALCATEL = {read=_GetALCATEL};
	__property int ALPWISE = {read=_GetALPWISE};
	__property int AMICCOM_ELECTRONICS = {read=_GetAMICCOM_ELECTRONICS};
	__property int APLIX = {read=_GetAPLIX};
	__property int APPLE = {read=_GetAPPLE};
	__property int APT_LICENSING = {read=_GetAPT_LICENSING};
	__property int ARCHOS = {read=_GetARCHOS};
	__property int ARP_DEVICES = {read=_GetARP_DEVICES};
	__property int ATHEROS_COMMUNICATIONS = {read=_GetATHEROS_COMMUNICATIONS};
	__property int ATMEL = {read=_GetATMEL};
	__property int AUSTCO_COMMUNICATION_SYSTEMS = {read=_GetAUSTCO_COMMUNICATION_SYSTEMS};
	__property int AUTONET_MOBILE = {read=_GetAUTONET_MOBILE};
	__property int AVAGO = {read=_GetAVAGO};
	__property int AVM_BERLIN = {read=_GetAVM_BERLIN};
	__property int A_AND_D_ENGINEERING = {read=_GetA_AND_D_ENGINEERING};
	__property int A_AND_R_CAMBRIDGE = {read=_GetA_AND_R_CAMBRIDGE};
	__property int BANDSPEED = {read=_GetBANDSPEED};
	__property int BAND_XI_INTERNATIONAL = {read=_GetBAND_XI_INTERNATIONAL};
	__property int BDE_TECHNOLOGY = {read=_GetBDE_TECHNOLOGY};
	__property int BEATS_ELECTRONICS = {read=_GetBEATS_ELECTRONICS};
	__property int BEAUTIFUL_ENTERPRISE = {read=_GetBEAUTIFUL_ENTERPRISE};
	__property int BEKEY = {read=_GetBEKEY};
	__property int BELKIN_INTERNATIONAL = {read=_GetBELKIN_INTERNATIONAL};
	__property int BINAURIC = {read=_GetBINAURIC};
	__property int BIOSENTRONICS = {read=_GetBIOSENTRONICS};
	__property int BLUEGIGA = {read=_GetBLUEGIGA};
	__property int BLUERADIOS = {read=_GetBLUERADIOS};
	__property int BLUETOOTH_SIG = {read=_GetBLUETOOTH_SIG};
	__property int BLUETREK_TECHNOLOGIES = {read=_GetBLUETREK_TECHNOLOGIES};
	__property int BOSE = {read=_GetBOSE};
	__property int BRIARTEK = {read=_GetBRIARTEK};
	__property int BROADCOM = {read=_GetBROADCOM};
	__property int CAEN_RFID = {read=_GetCAEN_RFID};
	__property int CAMBRIDGE_SILICON_RADIO = {read=_GetCAMBRIDGE_SILICON_RADIO};
	__property int CATC = {read=_GetCATC};
	__property int CINETIX = {read=_GetCINETIX};
	__property int CLARINOX_TECHNOLOGIES = {read=_GetCLARINOX_TECHNOLOGIES};
	__property int COLORFY = {read=_GetCOLORFY};
	__property int COMMIL = {read=_GetCOMMIL};
	__property int CONEXANT_SYSTEMS = {read=_GetCONEXANT_SYSTEMS};
	__property int CONNECTBLUE = {read=_GetCONNECTBLUE};
	__property int CONTINENTAL_AUTOMOTIVE = {read=_GetCONTINENTAL_AUTOMOTIVE};
	__property int CONWISE_TECHNOLOGY = {read=_GetCONWISE_TECHNOLOGY};
	__property int CREATIVE_TECHNOLOGY = {read=_GetCREATIVE_TECHNOLOGY};
	__property int C_TECHNOLOGIES = {read=_GetC_TECHNOLOGIES};
	__property int DANLERS = {read=_GetDANLERS};
	__property int DELORME_PUBLISHING_COMPANY = {read=_GetDELORME_PUBLISHING_COMPANY};
	__property int DEXCOM = {read=_GetDEXCOM};
	__property int DIALOG_SEMICONDUCTOR = {read=_GetDIALOG_SEMICONDUCTOR};
	__property int DIGIANSWER = {read=_GetDIGIANSWER};
	__property int ECLIPSE = {read=_GetECLIPSE};
	__property int ECOTEST = {read=_GetECOTEST};
	__property int ELGATO_SYSTEMS = {read=_GetELGATO_SYSTEMS};
	__property int EM_MICROELECTRONIC_MARIN = {read=_GetEM_MICROELECTRONIC_MARIN};
	__property int EQUINOX_AG = {read=_GetEQUINOX_AG};
	__property int ERICSSON_TECHNOLOGY = {read=_GetERICSSON_TECHNOLOGY};
	__property int EVLUMA = {read=_GetEVLUMA};
	__property int FREE2MOVE = {read=_GetFREE2MOVE};
	__property int FUNAI_ELECTRIC = {read=_GetFUNAI_ELECTRIC};
	__property int GARMIN_INTERNATIONAL = {read=_GetGARMIN_INTERNATIONAL};
	__property int GCT_SEMICONDUCTOR = {read=_GetGCT_SEMICONDUCTOR};
	__property int GELO = {read=_GetGELO};
	__property int GENEQ = {read=_GetGENEQ};
	__property int GENERAL_MOTORS = {read=_GetGENERAL_MOTORS};
	__property int GENNUM = {read=_GetGENNUM};
	__property int GEOFORCE = {read=_GetGEOFORCE};
	__property int GIBSON_GUITARS = {read=_GetGIBSON_GUITARS};
	__property int GN_NETCOM = {read=_GetGN_NETCOM};
	__property int GN_RESOUND = {read=_GetGN_RESOUND};
	__property int GOOGLE = {read=_GetGOOGLE};
	__property int GREEN_THROTTLE_GAMES = {read=_GetGREEN_THROTTLE_GAMES};
	__property int GROUP_SENSE = {read=_GetGROUP_SENSE};
	__property int HANLYNN_TECHNOLOGIES = {read=_GetHANLYNN_TECHNOLOGIES};
	__property int HARMAN_INTERNATIONAL = {read=_GetHARMAN_INTERNATIONAL};
	__property int HEWLETT_PACKARD = {read=_GetHEWLETT_PACKARD};
	__property int HITACHI = {read=_GetHITACHI};
	__property int HOSIDEN = {read=_GetHOSIDEN};
	__property int IBM = {read=_GetIBM};
	__property int INFINEON_TECHNOLOGIES = {read=_GetINFINEON_TECHNOLOGIES};
	__property int INGENIEUR_SYSTEMGRUPPE_ZAHN = {read=_GetINGENIEUR_SYSTEMGRUPPE_ZAHN};
	__property int INTEGRATED_SILICON_SOLUTION = {read=_GetINTEGRATED_SILICON_SOLUTION};
	__property int INTEGRATED_SYSTEM_SOLUTION = {read=_GetINTEGRATED_SYSTEM_SOLUTION};
	__property int INTEL = {read=_GetINTEL};
	__property int INVENTEL = {read=_GetINVENTEL};
	__property int IPEXTREME = {read=_GetIPEXTREME};
	__property int I_TECH_DYNAMIC_GLOBAL_DISTRIBUTION = {read=_GetI_TECH_DYNAMIC_GLOBAL_DISTRIBUTION};
	__property int JAWBONE = {read=_GetJAWBONE};
	__property int JIANGSU_TOPPOWER_AUTOMOTIVE_ELECTRONICS = {read=_GetJIANGSU_TOPPOWER_AUTOMOTIVE_ELECTRONICS};
	__property int JOHNSON_CONTROLS = {read=_GetJOHNSON_CONTROLS};
	__property int J_AND_M = {read=_GetJ_AND_M};
	__property int KAWANTECH = {read=_GetKAWANTECH};
	__property int KC_TECHNOLOGY = {read=_GetKC_TECHNOLOGY};
	__property int KENSINGTON_COMPUTER_PRODUCTS_GROUP = {read=_GetKENSINGTON_COMPUTER_PRODUCTS_GROUP};
	__property int LAIRD_TECHNOLOGIES = {read=_GetLAIRD_TECHNOLOGIES};
	__property int LESSWIRE = {read=_GetLESSWIRE};
	__property int LG_ELECTRONICS = {read=_GetLG_ELECTRONICS};
	__property int LINAK = {read=_GetLINAK};
	__property int LUCENT = {read=_GetLUCENT};
	__property int LUDUS_HELSINKI = {read=_GetLUDUS_HELSINKI};
	__property int MACRONIX = {read=_GetMACRONIX};
	__property int MAGNETI_MARELLI = {read=_GetMAGNETI_MARELLI};
	__property int MANSELLA = {read=_GetMANSELLA};
	__property int MARVELL = {read=_GetMARVELL};
	__property int MATSUSHITA_ELECTRIC = {read=_GetMATSUSHITA_ELECTRIC};
	__property int MC10 = {read=_GetMC10};
	__property int MEDIATEK = {read=_GetMEDIATEK};
	__property int MESO_INTERNATIONAL = {read=_GetMESO_INTERNATIONAL};
	__property int META_WATCH = {read=_GetMETA_WATCH};
	__property int MEWTEL_TECHNOLOGY = {read=_GetMEWTEL_TECHNOLOGY};
	__property int MICOMMAND = {read=_GetMICOMMAND};
	__property int MICROCHIP_TECHNOLOGY = {read=_GetMICROCHIP_TECHNOLOGY};
	__property int MICROSOFT = {read=_GetMICROSOFT};
	__property int MINDTREE = {read=_GetMINDTREE};
	__property int MISFIT_WEARABLES = {read=_GetMISFIT_WEARABLES};
	__property int MITEL_SEMICONDUCTOR = {read=_GetMITEL_SEMICONDUCTOR};
	__property int MITSUBISHI_ELECTRIC = {read=_GetMITSUBISHI_ELECTRIC};
	__property int MOBILIAN_CORPORATION = {read=_GetMOBILIAN_CORPORATION};
	__property int MONSTER = {read=_GetMONSTER};
	__property int MOTOROLA = {read=_GetMOTOROLA};
	__property int MSTAR_SEMICONDUCTOR = {read=_GetMSTAR_SEMICONDUCTOR};
	__property int MUZIK = {read=_GetMUZIK};
	__property int NEC = {read=_GetNEC};
	__property int NEC_LIGHTING = {read=_GetNEC_LIGHTING};
	__property int NEWLOGIC = {read=_GetNEWLOGIC};
	__property int NIKE = {read=_GetNIKE};
	__property int NINE_SOLUTIONS = {read=_GetNINE_SOLUTIONS};
	__property int NOKIA_MOBILE_PHONES = {read=_GetNOKIA_MOBILE_PHONES};
	__property int NORDIC_SEMICONDUCTOR = {read=_GetNORDIC_SEMICONDUCTOR};
	__property int NORWOOD_SYSTEMS = {read=_GetNORWOOD_SYSTEMS};
	__property int ODM_TECHNOLOGY = {read=_GetODM_TECHNOLOGY};
	__property int OMEGAWAVE = {read=_GetOMEGAWAVE};
	__property int ONSET_COMPUTER = {read=_GetONSET_COMPUTER};
	__property int OPEN_INTERFACE = {read=_GetOPEN_INTERFACE};
	__property int OTL_DYNAMICS = {read=_GetOTL_DYNAMICS};
	__property int PANDA_OCEAN = {read=_GetPANDA_OCEAN};
	__property int PARROT = {read=_GetPARROT};
	__property int PARTHUS_TECHNOLOGIES = {read=_GetPARTHUS_TECHNOLOGIES};
	__property int PASSIF_SEMICONDUCTOR = {read=_GetPASSIF_SEMICONDUCTOR};
	__property int PETER_SYSTEMTECHNIK = {read=_GetPETER_SYSTEMTECHNIK};
	__property int PHILIPS_SEMICONDUCTORS = {read=_GetPHILIPS_SEMICONDUCTORS};
	__property int PLANTRONICS = {read=_GetPLANTRONICS};
	__property int POLAR_ELECTRO = {read=_GetPOLAR_ELECTRO};
	__property int POLAR_ELECTRO_EUROPE = {read=_GetPOLAR_ELECTRO_EUROPE};
	__property int PROCTER_AND_GAMBLE = {read=_GetPROCTER_AND_GAMBLE};
	__property int QUALCOMM = {read=_GetQUALCOMM};
	__property int QUALCOMM_CONNECTED_EXPERIENCES = {read=_GetQUALCOMM_CONNECTED_EXPERIENCES};
	__property int QUALCOMM_INNOVATION_CENTER = {read=_GetQUALCOMM_INNOVATION_CENTER};
	__property int QUALCOMM_LABS = {read=_GetQUALCOMM_LABS};
	__property int QUALCOMM_TECHNOLOGIES = {read=_GetQUALCOMM_TECHNOLOGIES};
	__property int QUINTIC = {read=_GetQUINTIC};
	__property int QUUPPA = {read=_GetQUUPPA};
	__property int RALINK_TECHNOLOGY = {read=_GetRALINK_TECHNOLOGY};
	__property int RDA_MICROELECTRONICS = {read=_GetRDA_MICROELECTRONICS};
	__property int REALTEK_SEMICONDUCTOR = {read=_GetREALTEK_SEMICONDUCTOR};
	__property int RED_M = {read=_GetRED_M};
	__property int RENESAS_TECHNOLOGY = {read=_GetRENESAS_TECHNOLOGY};
	__property int RESEARCH_IN_MOTION = {read=_GetRESEARCH_IN_MOTION};
	__property int RF_MICRO_DEVICES = {read=_GetRF_MICRO_DEVICES};
	__property int RIVIERAWAVES = {read=_GetRIVIERAWAVES};
	__property int ROHDE_AND_SCHWARZ = {read=_GetROHDE_AND_SCHWARZ};
	__property int RTX_TELECOM = {read=_GetRTX_TELECOM};
	__property int SAMSUNG_ELECTRONICS = {read=_GetSAMSUNG_ELECTRONICS};
	__property int SARIS_CYCLING_GROUP = {read=_GetSARIS_CYCLING_GROUP};
	__property int SEERS_TECHNOLOGY = {read=_GetSEERS_TECHNOLOGY};
	__property int SEIKO_EPSON = {read=_GetSEIKO_EPSON};
	__property int SELFLY = {read=_GetSELFLY};
	__property int SEMILINK = {read=_GetSEMILINK};
	__property int SENNHEISER_COMMUNICATIONS = {read=_GetSENNHEISER_COMMUNICATIONS};
	__property int SHANGHAI_SUPER_SMART_ELECTRONICS = {read=_GetSHANGHAI_SUPER_SMART_ELECTRONICS};
	__property int SHENZHEN_EXCELSECU_DATA_TECHNOLOGY = {read=_GetSHENZHEN_EXCELSECU_DATA_TECHNOLOGY};
	__property int SIGNIA_TECHNOLOGIES = {read=_GetSIGNIA_TECHNOLOGIES};
	__property int SILICON_WAVE = {read=_GetSILICON_WAVE};
	__property int SIRF_TECHNOLOGY = {read=_GetSIRF_TECHNOLOGY};
	__property int SOCKET_MOBILE = {read=_GetSOCKET_MOBILE};
	__property int SONY_ERICSSON = {read=_GetSONY_ERICSSON};
	__property int SOUND_ID = {read=_GetSOUND_ID};
	__property int SPORTS_TRACKING_TECHNOLOGIES = {read=_GetSPORTS_TRACKING_TECHNOLOGIES};
	__property int SR_MEDIZINELEKTRONIK = {read=_GetSR_MEDIZINELEKTRONIK};
	__property int STACCATO_COMMUNICATIONS = {read=_GetSTACCATO_COMMUNICATIONS};
	__property int STALMART_TECHNOLOGY = {read=_GetSTALMART_TECHNOLOGY};
	__property int STARKEY_LABORATORIES = {read=_GetSTARKEY_LABORATORIES};
	__property int STOLLMAN_E_PLUS_V = {read=_GetSTOLLMAN_E_PLUS_V};
	__property int STONESTREET_ONE = {read=_GetSTONESTREET_ONE};
	__property int ST_MICROELECTRONICS = {read=_GetST_MICROELECTRONICS};
	__property int SUMMIT_DATA_COMMUNICATIONS = {read=_GetSUMMIT_DATA_COMMUNICATIONS};
	__property int SUUNTO = {read=_GetSUUNTO};
	__property int SWIRL_NETWORKS = {read=_GetSWIRL_NETWORKS};
	__property int SYMBOL_TECHNOLOGIES = {read=_GetSYMBOL_TECHNOLOGIES};
	__property int SYNOPSYS = {read=_GetSYNOPSYS};
	__property int SYSTEMS_AND_CHIPS = {read=_GetSYSTEMS_AND_CHIPS};
	__property int S_POWER_ELECTRONICS = {read=_GetS_POWER_ELECTRONICS};
	__property int TAIXINGBANG_TECHNOLOGY = {read=_GetTAIXINGBANG_TECHNOLOGY};
	__property int TENOVIS = {read=_GetTENOVIS};
	__property int TERAX = {read=_GetTERAX};
	__property int TEXAS_INSTRUMENTS = {read=_GetTEXAS_INSTRUMENTS};
	__property int THINKOPTICS = {read=_GetTHINKOPTICS};
	__property int THREECOM = {read=_GetTHREECOM};
	__property int THREE_DIJOY = {read=_GetTHREE_DIJOY};
	__property int THREE_DSP = {read=_GetTHREE_DSP};
	__property int TIMEKEEPING_SYSTEMS = {read=_GetTIMEKEEPING_SYSTEMS};
	__property int TIMEX_GROUP_USA = {read=_GetTIMEX_GROUP_USA};
	__property int TOPCORN_POSITIONING_SYSTEMS = {read=_GetTOPCORN_POSITIONING_SYSTEMS};
	__property int TOSHIBA = {read=_GetTOSHIBA};
	__property int TRANSILICA = {read=_GetTRANSILICA};
	__property int TRELAB = {read=_GetTRELAB};
	__property int TTPCOM = {read=_GetTTPCOM};
	__property int TXTR = {read=_GetTXTR};
	__property int TZERO_TECHNOLOGIES = {read=_GetTZERO_TECHNOLOGIES};
	__property int UNIVERSAL_ELECTRONICS = {read=_GetUNIVERSAL_ELECTRONICS};
	__property int VERTU = {read=_GetVERTU};
	__property int VISTEON = {read=_GetVISTEON};
	__property int VIZIO = {read=_GetVIZIO};
	__property int VOYETRA_TURTLE_BEACH = {read=_GetVOYETRA_TURTLE_BEACH};
	__property int WAVEPLUS_TECHNOLOGY = {read=_GetWAVEPLUS_TECHNOLOGY};
	__property int WICENTRIC = {read=_GetWICENTRIC};
	__property int WIDCOMM = {read=_GetWIDCOMM};
	__property int WUXI_VIMICRO = {read=_GetWUXI_VIMICRO};
	__property int ZEEVO = {read=_GetZEEVO};
	__property int ZER01_TV = {read=_GetZER01_TV};
	__property int ZOMM = {read=_GetZOMM};
	__property int ZSCAN_SOFTWARE = {read=_GetZSCAN_SOFTWARE};
};

__interface  INTERFACE_UUID("{FD73BBEE-B1E1-4F52-AF25-AC98D94FA319}") JBluetoothAssignedNumbers  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothAssignedNumbers : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAssignedNumbersClass,_di_JBluetoothAssignedNumbers>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAssignedNumbersClass,_di_JBluetoothAssignedNumbers> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothAssignedNumbers() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAssignedNumbersClass,_di_JBluetoothAssignedNumbers>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothAssignedNumbers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF258AE0-A7F8-4869-B4F6-F061D1AE1264}") Jbluetooth_BluetoothClassClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{5B43837A-0671-4D08-9885-EA58330D393E}") Jbluetooth_BluetoothClass  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual int __cdecl getDeviceClass() = 0 ;
	virtual int __cdecl getMajorDeviceClass() = 0 ;
	virtual bool __cdecl hasService(int service) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJbluetooth_BluetoothClass : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jbluetooth_BluetoothClassClass,_di_Jbluetooth_BluetoothClass>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jbluetooth_BluetoothClassClass,_di_Jbluetooth_BluetoothClass> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJbluetooth_BluetoothClass() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jbluetooth_BluetoothClassClass,_di_Jbluetooth_BluetoothClass>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJbluetooth_BluetoothClass() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38E343FC-1BF6-439D-96B5-C71B4B066930}") JBluetoothClass_DeviceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAUDIO_VIDEO_CAMCORDER() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_CAR_AUDIO() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_HANDSFREE() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_HEADPHONES() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_HIFI_AUDIO() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_LOUDSPEAKER() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_MICROPHONE() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_PORTABLE_AUDIO() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_SET_TOP_BOX() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VCR() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VIDEO_CAMERA() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VIDEO_CONFERENCING() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VIDEO_DISPLAY_AND_LOUDSPEAKER() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VIDEO_GAMING_TOY() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_VIDEO_MONITOR() = 0 ;
	virtual int __cdecl _GetAUDIO_VIDEO_WEARABLE_HEADSET() = 0 ;
	virtual int __cdecl _GetCOMPUTER_DESKTOP() = 0 ;
	virtual int __cdecl _GetCOMPUTER_HANDHELD_PC_PDA() = 0 ;
	virtual int __cdecl _GetCOMPUTER_LAPTOP() = 0 ;
	virtual int __cdecl _GetCOMPUTER_PALM_SIZE_PC_PDA() = 0 ;
	virtual int __cdecl _GetCOMPUTER_SERVER() = 0 ;
	virtual int __cdecl _GetCOMPUTER_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetCOMPUTER_WEARABLE() = 0 ;
	virtual int __cdecl _GetHEALTH_BLOOD_PRESSURE() = 0 ;
	virtual int __cdecl _GetHEALTH_DATA_DISPLAY() = 0 ;
	virtual int __cdecl _GetHEALTH_GLUCOSE() = 0 ;
	virtual int __cdecl _GetHEALTH_PULSE_OXIMETER() = 0 ;
	virtual int __cdecl _GetHEALTH_PULSE_RATE() = 0 ;
	virtual int __cdecl _GetHEALTH_THERMOMETER() = 0 ;
	virtual int __cdecl _GetHEALTH_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetHEALTH_WEIGHING() = 0 ;
	virtual int __cdecl _GetPHONE_CELLULAR() = 0 ;
	virtual int __cdecl _GetPHONE_CORDLESS() = 0 ;
	virtual int __cdecl _GetPHONE_ISDN() = 0 ;
	virtual int __cdecl _GetPHONE_MODEM_OR_GATEWAY() = 0 ;
	virtual int __cdecl _GetPHONE_SMART() = 0 ;
	virtual int __cdecl _GetPHONE_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetTOY_CONTROLLER() = 0 ;
	virtual int __cdecl _GetTOY_DOLL_ACTION_FIGURE() = 0 ;
	virtual int __cdecl _GetTOY_GAME() = 0 ;
	virtual int __cdecl _GetTOY_ROBOT() = 0 ;
	virtual int __cdecl _GetTOY_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetTOY_VEHICLE() = 0 ;
	virtual int __cdecl _GetWEARABLE_GLASSES() = 0 ;
	virtual int __cdecl _GetWEARABLE_HELMET() = 0 ;
	virtual int __cdecl _GetWEARABLE_JACKET() = 0 ;
	virtual int __cdecl _GetWEARABLE_PAGER() = 0 ;
	virtual int __cdecl _GetWEARABLE_UNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetWEARABLE_WRIST_WATCH() = 0 ;
	HIDESBASE virtual _di_JBluetoothClass_Device __cdecl init() = 0 ;
	__property int AUDIO_VIDEO_CAMCORDER = {read=_GetAUDIO_VIDEO_CAMCORDER};
	__property int AUDIO_VIDEO_CAR_AUDIO = {read=_GetAUDIO_VIDEO_CAR_AUDIO};
	__property int AUDIO_VIDEO_HANDSFREE = {read=_GetAUDIO_VIDEO_HANDSFREE};
	__property int AUDIO_VIDEO_HEADPHONES = {read=_GetAUDIO_VIDEO_HEADPHONES};
	__property int AUDIO_VIDEO_HIFI_AUDIO = {read=_GetAUDIO_VIDEO_HIFI_AUDIO};
	__property int AUDIO_VIDEO_LOUDSPEAKER = {read=_GetAUDIO_VIDEO_LOUDSPEAKER};
	__property int AUDIO_VIDEO_MICROPHONE = {read=_GetAUDIO_VIDEO_MICROPHONE};
	__property int AUDIO_VIDEO_PORTABLE_AUDIO = {read=_GetAUDIO_VIDEO_PORTABLE_AUDIO};
	__property int AUDIO_VIDEO_SET_TOP_BOX = {read=_GetAUDIO_VIDEO_SET_TOP_BOX};
	__property int AUDIO_VIDEO_UNCATEGORIZED = {read=_GetAUDIO_VIDEO_UNCATEGORIZED};
	__property int AUDIO_VIDEO_VCR = {read=_GetAUDIO_VIDEO_VCR};
	__property int AUDIO_VIDEO_VIDEO_CAMERA = {read=_GetAUDIO_VIDEO_VIDEO_CAMERA};
	__property int AUDIO_VIDEO_VIDEO_CONFERENCING = {read=_GetAUDIO_VIDEO_VIDEO_CONFERENCING};
	__property int AUDIO_VIDEO_VIDEO_DISPLAY_AND_LOUDSPEAKER = {read=_GetAUDIO_VIDEO_VIDEO_DISPLAY_AND_LOUDSPEAKER};
	__property int AUDIO_VIDEO_VIDEO_GAMING_TOY = {read=_GetAUDIO_VIDEO_VIDEO_GAMING_TOY};
	__property int AUDIO_VIDEO_VIDEO_MONITOR = {read=_GetAUDIO_VIDEO_VIDEO_MONITOR};
	__property int AUDIO_VIDEO_WEARABLE_HEADSET = {read=_GetAUDIO_VIDEO_WEARABLE_HEADSET};
	__property int COMPUTER_DESKTOP = {read=_GetCOMPUTER_DESKTOP};
	__property int COMPUTER_HANDHELD_PC_PDA = {read=_GetCOMPUTER_HANDHELD_PC_PDA};
	__property int COMPUTER_LAPTOP = {read=_GetCOMPUTER_LAPTOP};
	__property int COMPUTER_PALM_SIZE_PC_PDA = {read=_GetCOMPUTER_PALM_SIZE_PC_PDA};
	__property int COMPUTER_SERVER = {read=_GetCOMPUTER_SERVER};
	__property int COMPUTER_UNCATEGORIZED = {read=_GetCOMPUTER_UNCATEGORIZED};
	__property int COMPUTER_WEARABLE = {read=_GetCOMPUTER_WEARABLE};
	__property int HEALTH_BLOOD_PRESSURE = {read=_GetHEALTH_BLOOD_PRESSURE};
	__property int HEALTH_DATA_DISPLAY = {read=_GetHEALTH_DATA_DISPLAY};
	__property int HEALTH_GLUCOSE = {read=_GetHEALTH_GLUCOSE};
	__property int HEALTH_PULSE_OXIMETER = {read=_GetHEALTH_PULSE_OXIMETER};
	__property int HEALTH_PULSE_RATE = {read=_GetHEALTH_PULSE_RATE};
	__property int HEALTH_THERMOMETER = {read=_GetHEALTH_THERMOMETER};
	__property int HEALTH_UNCATEGORIZED = {read=_GetHEALTH_UNCATEGORIZED};
	__property int HEALTH_WEIGHING = {read=_GetHEALTH_WEIGHING};
	__property int PHONE_CELLULAR = {read=_GetPHONE_CELLULAR};
	__property int PHONE_CORDLESS = {read=_GetPHONE_CORDLESS};
	__property int PHONE_ISDN = {read=_GetPHONE_ISDN};
	__property int PHONE_MODEM_OR_GATEWAY = {read=_GetPHONE_MODEM_OR_GATEWAY};
	__property int PHONE_SMART = {read=_GetPHONE_SMART};
	__property int PHONE_UNCATEGORIZED = {read=_GetPHONE_UNCATEGORIZED};
	__property int TOY_CONTROLLER = {read=_GetTOY_CONTROLLER};
	__property int TOY_DOLL_ACTION_FIGURE = {read=_GetTOY_DOLL_ACTION_FIGURE};
	__property int TOY_GAME = {read=_GetTOY_GAME};
	__property int TOY_ROBOT = {read=_GetTOY_ROBOT};
	__property int TOY_UNCATEGORIZED = {read=_GetTOY_UNCATEGORIZED};
	__property int TOY_VEHICLE = {read=_GetTOY_VEHICLE};
	__property int WEARABLE_GLASSES = {read=_GetWEARABLE_GLASSES};
	__property int WEARABLE_HELMET = {read=_GetWEARABLE_HELMET};
	__property int WEARABLE_JACKET = {read=_GetWEARABLE_JACKET};
	__property int WEARABLE_PAGER = {read=_GetWEARABLE_PAGER};
	__property int WEARABLE_UNCATEGORIZED = {read=_GetWEARABLE_UNCATEGORIZED};
	__property int WEARABLE_WRIST_WATCH = {read=_GetWEARABLE_WRIST_WATCH};
};

__interface  INTERFACE_UUID("{075C1041-C493-488E-A668-5D470339A25B}") JBluetoothClass_Device  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothClass_Device : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_DeviceClass,_di_JBluetoothClass_Device>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_DeviceClass,_di_JBluetoothClass_Device> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothClass_Device() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_DeviceClass,_di_JBluetoothClass_Device>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothClass_Device() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5C10CF59-50A2-4C87-B8D9-0BEC242F190C}") JDevice_MajorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAUDIO_VIDEO() = 0 ;
	virtual int __cdecl _GetCOMPUTER() = 0 ;
	virtual int __cdecl _GetHEALTH() = 0 ;
	virtual int __cdecl _GetIMAGING() = 0 ;
	virtual int __cdecl _GetMISC() = 0 ;
	virtual int __cdecl _GetNETWORKING() = 0 ;
	virtual int __cdecl _GetPERIPHERAL() = 0 ;
	virtual int __cdecl _GetPHONE() = 0 ;
	virtual int __cdecl _GetTOY() = 0 ;
	virtual int __cdecl _GetUNCATEGORIZED() = 0 ;
	virtual int __cdecl _GetWEARABLE() = 0 ;
	HIDESBASE virtual _di_JDevice_Major __cdecl init() = 0 ;
	__property int AUDIO_VIDEO = {read=_GetAUDIO_VIDEO};
	__property int COMPUTER = {read=_GetCOMPUTER};
	__property int HEALTH = {read=_GetHEALTH};
	__property int IMAGING = {read=_GetIMAGING};
	__property int MISC = {read=_GetMISC};
	__property int NETWORKING = {read=_GetNETWORKING};
	__property int PERIPHERAL = {read=_GetPERIPHERAL};
	__property int PHONE = {read=_GetPHONE};
	__property int TOY = {read=_GetTOY};
	__property int UNCATEGORIZED = {read=_GetUNCATEGORIZED};
	__property int WEARABLE = {read=_GetWEARABLE};
};

__interface  INTERFACE_UUID("{3BF5E3F7-14A8-4940-AA15-4E41858E41CE}") JDevice_Major  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDevice_Major : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDevice_MajorClass,_di_JDevice_Major>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDevice_MajorClass,_di_JDevice_Major> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDevice_Major() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDevice_MajorClass,_di_JDevice_Major>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDevice_Major() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{119150F9-9A31-46EE-871B-8DB6BDD19F17}") JBluetoothClass_ServiceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAUDIO() = 0 ;
	virtual int __cdecl _GetCAPTURE() = 0 ;
	virtual int __cdecl _GetINFORMATION() = 0 ;
	virtual int __cdecl _GetLIMITED_DISCOVERABILITY() = 0 ;
	virtual int __cdecl _GetNETWORKING() = 0 ;
	virtual int __cdecl _GetOBJECT_TRANSFER() = 0 ;
	virtual int __cdecl _GetPOSITIONING() = 0 ;
	virtual int __cdecl _GetRENDER() = 0 ;
	virtual int __cdecl _GetTELEPHONY() = 0 ;
	HIDESBASE virtual _di_JBluetoothClass_Service __cdecl init() = 0 ;
	__property int AUDIO = {read=_GetAUDIO};
	__property int CAPTURE = {read=_GetCAPTURE};
	__property int INFORMATION = {read=_GetINFORMATION};
	__property int LIMITED_DISCOVERABILITY = {read=_GetLIMITED_DISCOVERABILITY};
	__property int NETWORKING = {read=_GetNETWORKING};
	__property int OBJECT_TRANSFER = {read=_GetOBJECT_TRANSFER};
	__property int POSITIONING = {read=_GetPOSITIONING};
	__property int RENDER = {read=_GetRENDER};
	__property int TELEPHONY = {read=_GetTELEPHONY};
};

__interface  INTERFACE_UUID("{DD0314CB-EE35-4535-81CB-71F4D9E149E9}") JBluetoothClass_Service  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothClass_Service : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_ServiceClass,_di_JBluetoothClass_Service>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_ServiceClass,_di_JBluetoothClass_Service> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothClass_Service() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothClass_ServiceClass,_di_JBluetoothClass_Service>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothClass_Service() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E230F5F8-B398-45A4-8872-9157EBB23736}") JBluetoothDeviceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_ACL_CONNECTED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_ACL_DISCONNECTED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_ACL_DISCONNECT_REQUESTED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_BOND_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CLASS_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_FOUND() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NAME_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_PAIRING_REQUEST() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_UUID() = 0 ;
	virtual int __cdecl _GetBOND_BONDED() = 0 ;
	virtual int __cdecl _GetBOND_BONDING() = 0 ;
	virtual int __cdecl _GetBOND_NONE() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDEVICE_TYPE_CLASSIC() = 0 ;
	virtual int __cdecl _GetDEVICE_TYPE_DUAL() = 0 ;
	virtual int __cdecl _GetDEVICE_TYPE_LE() = 0 ;
	virtual int __cdecl _GetDEVICE_TYPE_UNKNOWN() = 0 ;
	virtual int __cdecl _GetERROR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_BOND_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CLASS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_DEVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PAIRING_KEY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PAIRING_VARIANT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREVIOUS_BOND_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RSSI() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_UUID() = 0 ;
	virtual int __cdecl _GetPAIRING_VARIANT_PASSKEY_CONFIRMATION() = 0 ;
	virtual int __cdecl _GetPAIRING_VARIANT_PIN() = 0 ;
	virtual int __cdecl _GetPHY_LE_1M() = 0 ;
	virtual int __cdecl _GetPHY_LE_1M_MASK() = 0 ;
	virtual int __cdecl _GetPHY_LE_2M() = 0 ;
	virtual int __cdecl _GetPHY_LE_2M_MASK() = 0 ;
	virtual int __cdecl _GetPHY_LE_CODED() = 0 ;
	virtual int __cdecl _GetPHY_LE_CODED_MASK() = 0 ;
	virtual int __cdecl _GetPHY_OPTION_NO_PREFERRED() = 0 ;
	virtual int __cdecl _GetPHY_OPTION_S2() = 0 ;
	virtual int __cdecl _GetPHY_OPTION_S8() = 0 ;
	virtual int __cdecl _GetTRANSPORT_AUTO() = 0 ;
	virtual int __cdecl _GetTRANSPORT_BREDR() = 0 ;
	virtual int __cdecl _GetTRANSPORT_LE() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_ACL_CONNECTED = {read=_GetACTION_ACL_CONNECTED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_ACL_DISCONNECTED = {read=_GetACTION_ACL_DISCONNECTED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_ACL_DISCONNECT_REQUESTED = {read=_GetACTION_ACL_DISCONNECT_REQUESTED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_BOND_STATE_CHANGED = {read=_GetACTION_BOND_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CLASS_CHANGED = {read=_GetACTION_CLASS_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_FOUND = {read=_GetACTION_FOUND};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NAME_CHANGED = {read=_GetACTION_NAME_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_PAIRING_REQUEST = {read=_GetACTION_PAIRING_REQUEST};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_UUID = {read=_GetACTION_UUID};
	__property int BOND_BONDED = {read=_GetBOND_BONDED};
	__property int BOND_BONDING = {read=_GetBOND_BONDING};
	__property int BOND_NONE = {read=_GetBOND_NONE};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DEVICE_TYPE_CLASSIC = {read=_GetDEVICE_TYPE_CLASSIC};
	__property int DEVICE_TYPE_DUAL = {read=_GetDEVICE_TYPE_DUAL};
	__property int DEVICE_TYPE_LE = {read=_GetDEVICE_TYPE_LE};
	__property int DEVICE_TYPE_UNKNOWN = {read=_GetDEVICE_TYPE_UNKNOWN};
	__property int ERROR = {read=_GetERROR};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_BOND_STATE = {read=_GetEXTRA_BOND_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CLASS = {read=_GetEXTRA_CLASS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_DEVICE = {read=_GetEXTRA_DEVICE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NAME = {read=_GetEXTRA_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PAIRING_KEY = {read=_GetEXTRA_PAIRING_KEY};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PAIRING_VARIANT = {read=_GetEXTRA_PAIRING_VARIANT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREVIOUS_BOND_STATE = {read=_GetEXTRA_PREVIOUS_BOND_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RSSI = {read=_GetEXTRA_RSSI};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_UUID = {read=_GetEXTRA_UUID};
	__property int PAIRING_VARIANT_PASSKEY_CONFIRMATION = {read=_GetPAIRING_VARIANT_PASSKEY_CONFIRMATION};
	__property int PAIRING_VARIANT_PIN = {read=_GetPAIRING_VARIANT_PIN};
	__property int PHY_LE_1M = {read=_GetPHY_LE_1M};
	__property int PHY_LE_1M_MASK = {read=_GetPHY_LE_1M_MASK};
	__property int PHY_LE_2M = {read=_GetPHY_LE_2M};
	__property int PHY_LE_2M_MASK = {read=_GetPHY_LE_2M_MASK};
	__property int PHY_LE_CODED = {read=_GetPHY_LE_CODED};
	__property int PHY_LE_CODED_MASK = {read=_GetPHY_LE_CODED_MASK};
	__property int PHY_OPTION_NO_PREFERRED = {read=_GetPHY_OPTION_NO_PREFERRED};
	__property int PHY_OPTION_S2 = {read=_GetPHY_OPTION_S2};
	__property int PHY_OPTION_S8 = {read=_GetPHY_OPTION_S8};
	__property int TRANSPORT_AUTO = {read=_GetTRANSPORT_AUTO};
	__property int TRANSPORT_BREDR = {read=_GetTRANSPORT_BREDR};
	__property int TRANSPORT_LE = {read=_GetTRANSPORT_LE};
};

__interface  INTERFACE_UUID("{1B2DF3AB-7AE0-4EC2-A9AC-94FCFB33FAEA}") JBluetoothDevice  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JBluetoothGatt __cdecl connectGatt(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, bool autoConnect, _di_JBluetoothGattCallback callback) = 0 /* overload */;
	virtual _di_JBluetoothGatt __cdecl connectGatt(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, bool autoConnect, _di_JBluetoothGattCallback callback, int transport) = 0 /* overload */;
	virtual _di_JBluetoothGatt __cdecl connectGatt(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, bool autoConnect, _di_JBluetoothGattCallback callback, int transport, int phy) = 0 /* overload */;
	virtual _di_JBluetoothGatt __cdecl connectGatt(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, bool autoConnect, _di_JBluetoothGattCallback callback, int transport, int phy, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual bool __cdecl createBond() = 0 ;
	virtual _di_JBluetoothSocket __cdecl createInsecureRfcommSocketToServiceRecord(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual _di_JBluetoothSocket __cdecl createRfcommSocketToServiceRecord(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual bool __cdecl fetchUuidsWithSdp() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAddress() = 0 ;
	virtual _di_Jbluetooth_BluetoothClass __cdecl getBluetoothClass() = 0 ;
	virtual int __cdecl getBondState() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getType() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Os::_di_JParcelUuid>* __cdecl getUuids() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl setPairingConfirmation(bool confirm) = 0 ;
	virtual bool __cdecl setPin(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* pin) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothDevice : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothDevice() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothDevice() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1AF3FF11-8E2B-4F62-9634-1027DF298C9C}") JBluetoothGattClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCONNECTION_PRIORITY_BALANCED() = 0 ;
	virtual int __cdecl _GetCONNECTION_PRIORITY_HIGH() = 0 ;
	virtual int __cdecl _GetCONNECTION_PRIORITY_LOW_POWER() = 0 ;
	virtual int __cdecl _GetGATT_CONNECTION_CONGESTED() = 0 ;
	virtual int __cdecl _GetGATT_FAILURE() = 0 ;
	virtual int __cdecl _GetGATT_INSUFFICIENT_AUTHENTICATION() = 0 ;
	virtual int __cdecl _GetGATT_INSUFFICIENT_ENCRYPTION() = 0 ;
	virtual int __cdecl _GetGATT_INVALID_ATTRIBUTE_LENGTH() = 0 ;
	virtual int __cdecl _GetGATT_INVALID_OFFSET() = 0 ;
	virtual int __cdecl _GetGATT_READ_NOT_PERMITTED() = 0 ;
	virtual int __cdecl _GetGATT_REQUEST_NOT_SUPPORTED() = 0 ;
	virtual int __cdecl _GetGATT_SUCCESS() = 0 ;
	virtual int __cdecl _GetGATT_WRITE_NOT_PERMITTED() = 0 ;
	__property int CONNECTION_PRIORITY_BALANCED = {read=_GetCONNECTION_PRIORITY_BALANCED};
	__property int CONNECTION_PRIORITY_HIGH = {read=_GetCONNECTION_PRIORITY_HIGH};
	__property int CONNECTION_PRIORITY_LOW_POWER = {read=_GetCONNECTION_PRIORITY_LOW_POWER};
	__property int GATT_CONNECTION_CONGESTED = {read=_GetGATT_CONNECTION_CONGESTED};
	__property int GATT_FAILURE = {read=_GetGATT_FAILURE};
	__property int GATT_INSUFFICIENT_AUTHENTICATION = {read=_GetGATT_INSUFFICIENT_AUTHENTICATION};
	__property int GATT_INSUFFICIENT_ENCRYPTION = {read=_GetGATT_INSUFFICIENT_ENCRYPTION};
	__property int GATT_INVALID_ATTRIBUTE_LENGTH = {read=_GetGATT_INVALID_ATTRIBUTE_LENGTH};
	__property int GATT_INVALID_OFFSET = {read=_GetGATT_INVALID_OFFSET};
	__property int GATT_READ_NOT_PERMITTED = {read=_GetGATT_READ_NOT_PERMITTED};
	__property int GATT_REQUEST_NOT_SUPPORTED = {read=_GetGATT_REQUEST_NOT_SUPPORTED};
	__property int GATT_SUCCESS = {read=_GetGATT_SUCCESS};
	__property int GATT_WRITE_NOT_PERMITTED = {read=_GetGATT_WRITE_NOT_PERMITTED};
};

__interface  INTERFACE_UUID("{2219308F-B680-4E5A-BF4A-F0B25B3DB5F9}") JBluetoothGatt  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl abortReliableWrite() = 0 /* overload */;
	virtual void __cdecl abortReliableWrite(_di_JBluetoothDevice mDevice) = 0 /* overload */;
	virtual bool __cdecl beginReliableWrite() = 0 ;
	virtual void __cdecl close() = 0 ;
	virtual bool __cdecl connect() = 0 ;
	virtual void __cdecl disconnect() = 0 ;
	virtual bool __cdecl discoverServices() = 0 ;
	virtual bool __cdecl executeReliableWrite() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual _di_JBluetoothDevice __cdecl getDevice() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual _di_JBluetoothGattService __cdecl getService(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getServices() = 0 ;
	virtual bool __cdecl readCharacteristic(_di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual bool __cdecl readDescriptor(_di_JBluetoothGattDescriptor descriptor) = 0 ;
	virtual void __cdecl readPhy() = 0 ;
	virtual bool __cdecl readRemoteRssi() = 0 ;
	virtual bool __cdecl requestConnectionPriority(int connectionPriority) = 0 ;
	virtual bool __cdecl requestMtu(int mtu) = 0 ;
	virtual bool __cdecl setCharacteristicNotification(_di_JBluetoothGattCharacteristic characteristic, bool enable) = 0 ;
	virtual void __cdecl setPreferredPhy(int txPhy, int rxPhy, int phyOptions) = 0 ;
	virtual bool __cdecl writeCharacteristic(_di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual bool __cdecl writeDescriptor(_di_JBluetoothGattDescriptor descriptor) = 0 ;
	virtual bool __cdecl refresh() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGatt : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattClass,_di_JBluetoothGatt>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattClass,_di_JBluetoothGatt> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGatt() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattClass,_di_JBluetoothGatt>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGatt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2E94E69F-765D-47FC-A45C-62182F73CF9B}") JBluetoothGattCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBluetoothGattCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{E07848AC-B968-4C94-9F67-4DC5E62CB8D3}") JBluetoothGattCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onCharacteristicChanged(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual void __cdecl onCharacteristicRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	virtual void __cdecl onCharacteristicWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	virtual void __cdecl onConnectionStateChange(_di_JBluetoothGatt gatt, int status, int newState) = 0 ;
	virtual void __cdecl onDescriptorRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	virtual void __cdecl onDescriptorWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	virtual void __cdecl onMtuChanged(_di_JBluetoothGatt gatt, int mtu, int status) = 0 ;
	virtual void __cdecl onPhyRead(_di_JBluetoothGatt gatt, int txPhy, int rxPhy, int status) = 0 ;
	virtual void __cdecl onPhyUpdate(_di_JBluetoothGatt gatt, int txPhy, int rxPhy, int status) = 0 ;
	virtual void __cdecl onReadRemoteRssi(_di_JBluetoothGatt gatt, int rssi, int status) = 0 ;
	virtual void __cdecl onReliableWriteCompleted(_di_JBluetoothGatt gatt, int status) = 0 ;
	virtual void __cdecl onServicesDiscovered(_di_JBluetoothGatt gatt, int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCallbackClass,_di_JBluetoothGattCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCallbackClass,_di_JBluetoothGattCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCallbackClass,_di_JBluetoothGattCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3BA3788A-A058-43CA-BFE1-BB06896EA7FD}") JBluetoothGattCharacteristicClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetFORMAT_FLOAT() = 0 ;
	virtual int __cdecl _GetFORMAT_SFLOAT() = 0 ;
	virtual int __cdecl _GetFORMAT_SINT16() = 0 ;
	virtual int __cdecl _GetFORMAT_SINT32() = 0 ;
	virtual int __cdecl _GetFORMAT_SINT8() = 0 ;
	virtual int __cdecl _GetFORMAT_UINT16() = 0 ;
	virtual int __cdecl _GetFORMAT_UINT32() = 0 ;
	virtual int __cdecl _GetFORMAT_UINT8() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ_ENCRYPTED() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ_ENCRYPTED_MITM() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_ENCRYPTED() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_ENCRYPTED_MITM() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_SIGNED() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_SIGNED_MITM() = 0 ;
	virtual int __cdecl _GetPROPERTY_BROADCAST() = 0 ;
	virtual int __cdecl _GetPROPERTY_EXTENDED_PROPS() = 0 ;
	virtual int __cdecl _GetPROPERTY_INDICATE() = 0 ;
	virtual int __cdecl _GetPROPERTY_NOTIFY() = 0 ;
	virtual int __cdecl _GetPROPERTY_READ() = 0 ;
	virtual int __cdecl _GetPROPERTY_SIGNED_WRITE() = 0 ;
	virtual int __cdecl _GetPROPERTY_WRITE() = 0 ;
	virtual int __cdecl _GetPROPERTY_WRITE_NO_RESPONSE() = 0 ;
	virtual int __cdecl _GetWRITE_TYPE_DEFAULT() = 0 ;
	virtual int __cdecl _GetWRITE_TYPE_NO_RESPONSE() = 0 ;
	virtual int __cdecl _GetWRITE_TYPE_SIGNED() = 0 ;
	HIDESBASE virtual _di_JBluetoothGattCharacteristic __cdecl init(Androidapi::Jni::Javatypes::_di_JUUID uuid, int properties, int permissions) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int FORMAT_FLOAT = {read=_GetFORMAT_FLOAT};
	__property int FORMAT_SFLOAT = {read=_GetFORMAT_SFLOAT};
	__property int FORMAT_SINT16 = {read=_GetFORMAT_SINT16};
	__property int FORMAT_SINT32 = {read=_GetFORMAT_SINT32};
	__property int FORMAT_SINT8 = {read=_GetFORMAT_SINT8};
	__property int FORMAT_UINT16 = {read=_GetFORMAT_UINT16};
	__property int FORMAT_UINT32 = {read=_GetFORMAT_UINT32};
	__property int FORMAT_UINT8 = {read=_GetFORMAT_UINT8};
	__property int PERMISSION_READ = {read=_GetPERMISSION_READ};
	__property int PERMISSION_READ_ENCRYPTED = {read=_GetPERMISSION_READ_ENCRYPTED};
	__property int PERMISSION_READ_ENCRYPTED_MITM = {read=_GetPERMISSION_READ_ENCRYPTED_MITM};
	__property int PERMISSION_WRITE = {read=_GetPERMISSION_WRITE};
	__property int PERMISSION_WRITE_ENCRYPTED = {read=_GetPERMISSION_WRITE_ENCRYPTED};
	__property int PERMISSION_WRITE_ENCRYPTED_MITM = {read=_GetPERMISSION_WRITE_ENCRYPTED_MITM};
	__property int PERMISSION_WRITE_SIGNED = {read=_GetPERMISSION_WRITE_SIGNED};
	__property int PERMISSION_WRITE_SIGNED_MITM = {read=_GetPERMISSION_WRITE_SIGNED_MITM};
	__property int PROPERTY_BROADCAST = {read=_GetPROPERTY_BROADCAST};
	__property int PROPERTY_EXTENDED_PROPS = {read=_GetPROPERTY_EXTENDED_PROPS};
	__property int PROPERTY_INDICATE = {read=_GetPROPERTY_INDICATE};
	__property int PROPERTY_NOTIFY = {read=_GetPROPERTY_NOTIFY};
	__property int PROPERTY_READ = {read=_GetPROPERTY_READ};
	__property int PROPERTY_SIGNED_WRITE = {read=_GetPROPERTY_SIGNED_WRITE};
	__property int PROPERTY_WRITE = {read=_GetPROPERTY_WRITE};
	__property int PROPERTY_WRITE_NO_RESPONSE = {read=_GetPROPERTY_WRITE_NO_RESPONSE};
	__property int WRITE_TYPE_DEFAULT = {read=_GetWRITE_TYPE_DEFAULT};
	__property int WRITE_TYPE_NO_RESPONSE = {read=_GetWRITE_TYPE_NO_RESPONSE};
	__property int WRITE_TYPE_SIGNED = {read=_GetWRITE_TYPE_SIGNED};
};

__interface  INTERFACE_UUID("{BB707DD3-B74D-4B10-9BD0-C53E4D63FC37}") JBluetoothGattCharacteristic  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl addDescriptor(_di_JBluetoothGattDescriptor descriptor) = 0 ;
	virtual _di_JBluetoothGattDescriptor __cdecl getDescriptor(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDescriptors() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFloat __cdecl getFloatValue(int formatType, int offset) = 0 ;
	virtual int __cdecl getInstanceId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInteger __cdecl getIntValue(int formatType, int offset) = 0 ;
	virtual int __cdecl getPermissions() = 0 ;
	virtual int __cdecl getProperties() = 0 ;
	virtual _di_JBluetoothGattService __cdecl getService() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getStringValue(int offset) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JUUID __cdecl getUuid() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getValue() = 0 ;
	virtual int __cdecl getWriteType() = 0 ;
	virtual bool __cdecl setValue(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 /* overload */;
	virtual bool __cdecl setValue(int value, int formatType, int offset) = 0 /* overload */;
	virtual bool __cdecl setValue(int mantissa, int exponent, int formatType, int offset) = 0 /* overload */;
	virtual bool __cdecl setValue(Androidapi::Jni::Javatypes::_di_JString value) = 0 /* overload */;
	virtual void __cdecl setWriteType(int writeType) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattCharacteristic : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCharacteristicClass,_di_JBluetoothGattCharacteristic>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCharacteristicClass,_di_JBluetoothGattCharacteristic> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattCharacteristic() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattCharacteristicClass,_di_JBluetoothGattCharacteristic>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattCharacteristic() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{28C0B7DC-35A2-4C0B-BF12-377AFB7D767C}") JBluetoothGattDescriptorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetDISABLE_NOTIFICATION_VALUE() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetENABLE_INDICATION_VALUE() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetENABLE_NOTIFICATION_VALUE() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ_ENCRYPTED() = 0 ;
	virtual int __cdecl _GetPERMISSION_READ_ENCRYPTED_MITM() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_ENCRYPTED() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_ENCRYPTED_MITM() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_SIGNED() = 0 ;
	virtual int __cdecl _GetPERMISSION_WRITE_SIGNED_MITM() = 0 ;
	HIDESBASE virtual _di_JBluetoothGattDescriptor __cdecl init(Androidapi::Jni::Javatypes::_di_JUUID uuid, int permissions) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* DISABLE_NOTIFICATION_VALUE = {read=_GetDISABLE_NOTIFICATION_VALUE};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* ENABLE_INDICATION_VALUE = {read=_GetENABLE_INDICATION_VALUE};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* ENABLE_NOTIFICATION_VALUE = {read=_GetENABLE_NOTIFICATION_VALUE};
	__property int PERMISSION_READ = {read=_GetPERMISSION_READ};
	__property int PERMISSION_READ_ENCRYPTED = {read=_GetPERMISSION_READ_ENCRYPTED};
	__property int PERMISSION_READ_ENCRYPTED_MITM = {read=_GetPERMISSION_READ_ENCRYPTED_MITM};
	__property int PERMISSION_WRITE = {read=_GetPERMISSION_WRITE};
	__property int PERMISSION_WRITE_ENCRYPTED = {read=_GetPERMISSION_WRITE_ENCRYPTED};
	__property int PERMISSION_WRITE_ENCRYPTED_MITM = {read=_GetPERMISSION_WRITE_ENCRYPTED_MITM};
	__property int PERMISSION_WRITE_SIGNED = {read=_GetPERMISSION_WRITE_SIGNED};
	__property int PERMISSION_WRITE_SIGNED_MITM = {read=_GetPERMISSION_WRITE_SIGNED_MITM};
};

__interface  INTERFACE_UUID("{E6B635CF-FA07-443D-A538-CD9EB22110BA}") JBluetoothGattDescriptor  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JBluetoothGattCharacteristic __cdecl getCharacteristic() = 0 ;
	virtual int __cdecl getPermissions() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JUUID __cdecl getUuid() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getValue() = 0 ;
	virtual bool __cdecl setValue(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattDescriptor : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattDescriptorClass,_di_JBluetoothGattDescriptor>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattDescriptorClass,_di_JBluetoothGattDescriptor> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattDescriptor() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattDescriptorClass,_di_JBluetoothGattDescriptor>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattDescriptor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FA3AE62C-030E-4325-BDE6-228CA519226A}") JBluetoothGattServerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0C8EE0C3-F591-454A-B1AE-1F7A51CF0762}") JBluetoothGattServer  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl addService(_di_JBluetoothGattService service) = 0 ;
	virtual void __cdecl cancelConnection(_di_JBluetoothDevice device) = 0 ;
	virtual void __cdecl clearServices() = 0 ;
	virtual void __cdecl close() = 0 ;
	virtual bool __cdecl connect(_di_JBluetoothDevice device, bool autoConnect) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual _di_JBluetoothGattService __cdecl getService(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getServices() = 0 ;
	virtual bool __cdecl notifyCharacteristicChanged(_di_JBluetoothDevice device, _di_JBluetoothGattCharacteristic characteristic, bool confirm) = 0 ;
	virtual void __cdecl readPhy(_di_JBluetoothDevice device) = 0 ;
	virtual bool __cdecl removeService(_di_JBluetoothGattService service) = 0 ;
	virtual bool __cdecl sendResponse(_di_JBluetoothDevice device, int requestId, int status, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl setPreferredPhy(_di_JBluetoothDevice device, int txPhy, int rxPhy, int phyOptions) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattServer : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerClass,_di_JBluetoothGattServer>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerClass,_di_JBluetoothGattServer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattServer() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerClass,_di_JBluetoothGattServer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattServer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3AAB7F16-EAFB-42F1-AB0B-B69913D30828}") JBluetoothGattServerCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBluetoothGattServerCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{0DAA40B9-3010-43B9-A8BC-38953BCE641E}") JBluetoothGattServerCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onCharacteristicReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual void __cdecl onCharacteristicWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattCharacteristic characteristic, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl onConnectionStateChange(_di_JBluetoothDevice device, int status, int newState) = 0 ;
	virtual void __cdecl onDescriptorReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattDescriptor descriptor) = 0 ;
	virtual void __cdecl onDescriptorWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattDescriptor descriptor, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl onExecuteWrite(_di_JBluetoothDevice device, int requestId, bool execute) = 0 ;
	virtual void __cdecl onMtuChanged(_di_JBluetoothDevice device, int mtu) = 0 ;
	virtual void __cdecl onNotificationSent(_di_JBluetoothDevice device, int status) = 0 ;
	virtual void __cdecl onPhyRead(_di_JBluetoothDevice device, int txPhy, int rxPhy, int status) = 0 ;
	virtual void __cdecl onPhyUpdate(_di_JBluetoothDevice device, int txPhy, int rxPhy, int status) = 0 ;
	virtual void __cdecl onServiceAdded(int status, _di_JBluetoothGattService service) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattServerCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerCallbackClass,_di_JBluetoothGattServerCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerCallbackClass,_di_JBluetoothGattServerCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattServerCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServerCallbackClass,_di_JBluetoothGattServerCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattServerCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{67244B78-B5BE-473E-B84C-EBE8898975B9}") JBluetoothGattServiceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetSERVICE_TYPE_PRIMARY() = 0 ;
	virtual int __cdecl _GetSERVICE_TYPE_SECONDARY() = 0 ;
	HIDESBASE virtual _di_JBluetoothGattService __cdecl init(Androidapi::Jni::Javatypes::_di_JUUID uuid, int serviceType) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int SERVICE_TYPE_PRIMARY = {read=_GetSERVICE_TYPE_PRIMARY};
	__property int SERVICE_TYPE_SECONDARY = {read=_GetSERVICE_TYPE_SECONDARY};
};

__interface  INTERFACE_UUID("{3EF3B4CF-735C-4DA5-A62B-8B7F3862DEA7}") JBluetoothGattService  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl addCharacteristic(_di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual bool __cdecl addService(_di_JBluetoothGattService service) = 0 ;
	virtual _di_JBluetoothGattCharacteristic __cdecl getCharacteristic(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getCharacteristics() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getIncludedServices() = 0 ;
	virtual int __cdecl getInstanceId() = 0 ;
	virtual int __cdecl getType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JUUID __cdecl getUuid() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothGattService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServiceClass,_di_JBluetoothGattService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServiceClass,_di_JBluetoothGattService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothGattService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothGattServiceClass,_di_JBluetoothGattService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothGattService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1C02789A-AD09-44E2-B844-5AE59B74D108}") JBluetoothHeadsetClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_AUDIO_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CONNECTION_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_VENDOR_SPECIFIC_HEADSET_EVENT() = 0 ;
	virtual int __cdecl _GetAT_CMD_TYPE_ACTION() = 0 ;
	virtual int __cdecl _GetAT_CMD_TYPE_BASIC() = 0 ;
	virtual int __cdecl _GetAT_CMD_TYPE_READ() = 0 ;
	virtual int __cdecl _GetAT_CMD_TYPE_SET() = 0 ;
	virtual int __cdecl _GetAT_CMD_TYPE_TEST() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_ARGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD_TYPE() = 0 ;
	virtual int __cdecl _GetSTATE_AUDIO_CONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_AUDIO_CONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_AUDIO_DISCONNECTED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVENDOR_RESULT_CODE_COMMAND_ANDROID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVENDOR_SPECIFIC_HEADSET_EVENT_COMPANY_ID_CATEGORY() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_AUDIO_STATE_CHANGED = {read=_GetACTION_AUDIO_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CONNECTION_STATE_CHANGED = {read=_GetACTION_CONNECTION_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_VENDOR_SPECIFIC_HEADSET_EVENT = {read=_GetACTION_VENDOR_SPECIFIC_HEADSET_EVENT};
	__property int AT_CMD_TYPE_ACTION = {read=_GetAT_CMD_TYPE_ACTION};
	__property int AT_CMD_TYPE_BASIC = {read=_GetAT_CMD_TYPE_BASIC};
	__property int AT_CMD_TYPE_READ = {read=_GetAT_CMD_TYPE_READ};
	__property int AT_CMD_TYPE_SET = {read=_GetAT_CMD_TYPE_SET};
	__property int AT_CMD_TYPE_TEST = {read=_GetAT_CMD_TYPE_TEST};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_ARGS = {read=_GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_ARGS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD = {read=_GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD_TYPE = {read=_GetEXTRA_VENDOR_SPECIFIC_HEADSET_EVENT_CMD_TYPE};
	__property int STATE_AUDIO_CONNECTED = {read=_GetSTATE_AUDIO_CONNECTED};
	__property int STATE_AUDIO_CONNECTING = {read=_GetSTATE_AUDIO_CONNECTING};
	__property int STATE_AUDIO_DISCONNECTED = {read=_GetSTATE_AUDIO_DISCONNECTED};
	__property Androidapi::Jni::Javatypes::_di_JString VENDOR_RESULT_CODE_COMMAND_ANDROID = {read=_GetVENDOR_RESULT_CODE_COMMAND_ANDROID};
	__property Androidapi::Jni::Javatypes::_di_JString VENDOR_SPECIFIC_HEADSET_EVENT_COMPANY_ID_CATEGORY = {read=_GetVENDOR_SPECIFIC_HEADSET_EVENT_COMPANY_ID_CATEGORY};
};

__interface  INTERFACE_UUID("{F5113343-8748-4A7C-AA6C-BD15197A0953}") JBluetoothHeadset  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual bool __cdecl isAudioConnected(_di_JBluetoothDevice device) = 0 ;
	virtual bool __cdecl sendVendorSpecificResultCode(_di_JBluetoothDevice device, Androidapi::Jni::Javatypes::_di_JString command, Androidapi::Jni::Javatypes::_di_JString arg) = 0 ;
	virtual bool __cdecl startVoiceRecognition(_di_JBluetoothDevice device) = 0 ;
	virtual bool __cdecl stopVoiceRecognition(_di_JBluetoothDevice device) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothHeadset : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHeadsetClass,_di_JBluetoothHeadset>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHeadsetClass,_di_JBluetoothHeadset> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothHeadset() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHeadsetClass,_di_JBluetoothHeadset>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothHeadset() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{300F6FEB-972D-4E7B-A50C-A15F454008B4}") JBluetoothHealthClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAPP_CONFIG_REGISTRATION_FAILURE() = 0 ;
	virtual int __cdecl _GetAPP_CONFIG_REGISTRATION_SUCCESS() = 0 ;
	virtual int __cdecl _GetAPP_CONFIG_UNREGISTRATION_FAILURE() = 0 ;
	virtual int __cdecl _GetAPP_CONFIG_UNREGISTRATION_SUCCESS() = 0 ;
	virtual int __cdecl _GetCHANNEL_TYPE_RELIABLE() = 0 ;
	virtual int __cdecl _GetCHANNEL_TYPE_STREAMING() = 0 ;
	virtual int __cdecl _GetSINK_ROLE() = 0 ;
	virtual int __cdecl _GetSOURCE_ROLE() = 0 ;
	virtual int __cdecl _GetSTATE_CHANNEL_CONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_CHANNEL_CONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_CHANNEL_DISCONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_CHANNEL_DISCONNECTING() = 0 ;
	__property int APP_CONFIG_REGISTRATION_FAILURE = {read=_GetAPP_CONFIG_REGISTRATION_FAILURE};
	__property int APP_CONFIG_REGISTRATION_SUCCESS = {read=_GetAPP_CONFIG_REGISTRATION_SUCCESS};
	__property int APP_CONFIG_UNREGISTRATION_FAILURE = {read=_GetAPP_CONFIG_UNREGISTRATION_FAILURE};
	__property int APP_CONFIG_UNREGISTRATION_SUCCESS = {read=_GetAPP_CONFIG_UNREGISTRATION_SUCCESS};
	__property int CHANNEL_TYPE_RELIABLE = {read=_GetCHANNEL_TYPE_RELIABLE};
	__property int CHANNEL_TYPE_STREAMING = {read=_GetCHANNEL_TYPE_STREAMING};
	__property int SINK_ROLE = {read=_GetSINK_ROLE};
	__property int SOURCE_ROLE = {read=_GetSOURCE_ROLE};
	__property int STATE_CHANNEL_CONNECTED = {read=_GetSTATE_CHANNEL_CONNECTED};
	__property int STATE_CHANNEL_CONNECTING = {read=_GetSTATE_CHANNEL_CONNECTING};
	__property int STATE_CHANNEL_DISCONNECTED = {read=_GetSTATE_CHANNEL_DISCONNECTED};
	__property int STATE_CHANNEL_DISCONNECTING = {read=_GetSTATE_CHANNEL_DISCONNECTING};
};

__interface  INTERFACE_UUID("{2C7C401F-FDC8-4C14-B495-A888A7E63035}") JBluetoothHealth  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl connectChannelToSource(_di_JBluetoothDevice device, _di_JBluetoothHealthAppConfiguration config) = 0 ;
	virtual bool __cdecl disconnectChannel(_di_JBluetoothDevice device, _di_JBluetoothHealthAppConfiguration config, int channelId) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelFileDescriptor __cdecl getMainChannelFd(_di_JBluetoothDevice device, _di_JBluetoothHealthAppConfiguration config) = 0 ;
	virtual bool __cdecl registerSinkAppConfiguration(Androidapi::Jni::Javatypes::_di_JString name, int dataType, _di_JBluetoothHealthCallback callback) = 0 ;
	virtual bool __cdecl unregisterAppConfiguration(_di_JBluetoothHealthAppConfiguration config) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothHealth : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthClass,_di_JBluetoothHealth>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthClass,_di_JBluetoothHealth> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothHealth() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthClass,_di_JBluetoothHealth>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothHealth() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D01FD0E1-8DDC-4F7C-9366-E557F7AA1E5A}") JBluetoothHealthAppConfigurationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{795DED40-D984-43F1-BF05-48D979EE7E32}") JBluetoothHealthAppConfiguration  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual int __cdecl getDataType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getRole() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothHealthAppConfiguration : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthAppConfigurationClass,_di_JBluetoothHealthAppConfiguration>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthAppConfigurationClass,_di_JBluetoothHealthAppConfiguration> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothHealthAppConfiguration() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthAppConfigurationClass,_di_JBluetoothHealthAppConfiguration>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothHealthAppConfiguration() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7B57EB4C-C41D-4E04-A684-7FA1F28947DE}") JBluetoothHealthCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBluetoothHealthCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{0B5BE0DB-6275-4F55-9E86-CF1074072A0A}") JBluetoothHealthCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onHealthAppConfigurationStatusChange(_di_JBluetoothHealthAppConfiguration config, int status) = 0 ;
	virtual void __cdecl onHealthChannelStateChange(_di_JBluetoothHealthAppConfiguration config, _di_JBluetoothDevice device, int prevState, int newState, Androidapi::Jni::Os::_di_JParcelFileDescriptor fd, int channelId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothHealthCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthCallbackClass,_di_JBluetoothHealthCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthCallbackClass,_di_JBluetoothHealthCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothHealthCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothHealthCallbackClass,_di_JBluetoothHealthCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothHealthCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A44BF6BA-ED3D-4136-9C6B-1DF9DAA37178}") JBluetoothManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{67B37813-B270-438B-A23C-F71C37660C75}") JBluetoothManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JBluetoothAdapter __cdecl getAdapter() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices(int profile) = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device, int profile) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(int profile, Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
	virtual _di_JBluetoothGattServer __cdecl openGattServer(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JBluetoothGattServerCallback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothManagerClass,_di_JBluetoothManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothManagerClass,_di_JBluetoothManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothManagerClass,_di_JBluetoothManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D4C874B9-3002-41AB-AE93-FDD3E9A75A66}") JBluetoothProfileClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetA2DP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREVIOUS_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE() = 0 ;
	virtual int __cdecl _GetGATT() = 0 ;
	virtual int __cdecl _GetGATT_SERVER() = 0 ;
	virtual int __cdecl _GetHEADSET() = 0 ;
	virtual int __cdecl _GetHEALTH() = 0 ;
	virtual int __cdecl _GetSAP() = 0 ;
	virtual int __cdecl _GetSTATE_CONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_CONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_DISCONNECTED() = 0 ;
	virtual int __cdecl _GetSTATE_DISCONNECTING() = 0 ;
	__property int A2DP = {read=_GetA2DP};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREVIOUS_STATE = {read=_GetEXTRA_PREVIOUS_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE = {read=_GetEXTRA_STATE};
	__property int GATT = {read=_GetGATT};
	__property int GATT_SERVER = {read=_GetGATT_SERVER};
	__property int HEADSET = {read=_GetHEADSET};
	__property int HEALTH = {read=_GetHEALTH};
	__property int SAP = {read=_GetSAP};
	__property int STATE_CONNECTED = {read=_GetSTATE_CONNECTED};
	__property int STATE_CONNECTING = {read=_GetSTATE_CONNECTING};
	__property int STATE_DISCONNECTED = {read=_GetSTATE_DISCONNECTED};
	__property int STATE_DISCONNECTING = {read=_GetSTATE_DISCONNECTING};
};

__interface  INTERFACE_UUID("{ED35C263-DCA1-4E11-8945-0950AD3EF7A6}") JBluetoothProfile  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getConnectedDevices() = 0 ;
	virtual int __cdecl getConnectionState(_di_JBluetoothDevice device) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getDevicesMatchingConnectionStates(Androidapi::Jnibridge::TJavaArray__1<int>* states) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothProfile : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfileClass,_di_JBluetoothProfile>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfileClass,_di_JBluetoothProfile> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothProfile() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfileClass,_di_JBluetoothProfile>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothProfile() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2601CF0E-06F4-430C-9EAF-498D4CE00504}") JBluetoothProfile_ServiceListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{545ECD2A-6684-4A8E-87BA-62FCA4DDFB73}") JBluetoothProfile_ServiceListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onServiceConnected(int profile, _di_JBluetoothProfile proxy) = 0 ;
	virtual void __cdecl onServiceDisconnected(int profile) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothProfile_ServiceListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfile_ServiceListenerClass,_di_JBluetoothProfile_ServiceListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfile_ServiceListenerClass,_di_JBluetoothProfile_ServiceListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothProfile_ServiceListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothProfile_ServiceListenerClass,_di_JBluetoothProfile_ServiceListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothProfile_ServiceListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0E4C4370-61A3-46AD-B79A-9818D6A86AD3}") JBluetoothServerSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CFA2FCE7-C9B5-4826-806D-5327363840DC}") JBluetoothServerSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JBluetoothSocket __cdecl accept() = 0 /* overload */;
	virtual _di_JBluetoothSocket __cdecl accept(int timeout) = 0 /* overload */;
	virtual void __cdecl close() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothServerSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothServerSocketClass,_di_JBluetoothServerSocket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothServerSocketClass,_di_JBluetoothServerSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothServerSocket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothServerSocketClass,_di_JBluetoothServerSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothServerSocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E282B24F-E194-4C88-A065-B84BEE426B4F}") JBluetoothSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetTYPE_L2CAP() = 0 ;
	virtual int __cdecl _GetTYPE_RFCOMM() = 0 ;
	virtual int __cdecl _GetTYPE_SCO() = 0 ;
	__property int TYPE_L2CAP = {read=_GetTYPE_L2CAP};
	__property int TYPE_RFCOMM = {read=_GetTYPE_RFCOMM};
	__property int TYPE_SCO = {read=_GetTYPE_SCO};
};

__interface  INTERFACE_UUID("{FC81DB7D-A513-4D9D-8BDC-6D852A5BEB34}") JBluetoothSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl connect() = 0 ;
	virtual int __cdecl getConnectionType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getInputStream() = 0 ;
	virtual int __cdecl getMaxReceivePacketSize() = 0 ;
	virtual int __cdecl getMaxTransmitPacketSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JOutputStream __cdecl getOutputStream() = 0 ;
	virtual _di_JBluetoothDevice __cdecl getRemoteDevice() = 0 ;
	virtual bool __cdecl isConnected() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothSocket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothSocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{625DE747-1AC3-4C80-9344-84642E9C6CD1}") JRTLBluetoothGattCallbackClass  : public JBluetoothGattCallbackClass 
{
	HIDESBASE virtual _di_JRTLBluetoothGattCallback __cdecl init(_di_JRTLBluetoothGattListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{F73E6A35-B789-441B-A99D-9B039976671A}") JRTLBluetoothGattCallback  : public JBluetoothGattCallback 
{
	HIDESBASE virtual void __cdecl onCharacteristicChanged(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	HIDESBASE virtual void __cdecl onCharacteristicRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	HIDESBASE virtual void __cdecl onCharacteristicWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	HIDESBASE virtual void __cdecl onConnectionStateChange(_di_JBluetoothGatt gatt, int status, int newState) = 0 ;
	HIDESBASE virtual void __cdecl onDescriptorRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	HIDESBASE virtual void __cdecl onDescriptorWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	HIDESBASE virtual void __cdecl onReadRemoteRssi(_di_JBluetoothGatt gatt, int rssi, int status) = 0 ;
	HIDESBASE virtual void __cdecl onReliableWriteCompleted(_di_JBluetoothGatt gatt, int status) = 0 ;
	HIDESBASE virtual void __cdecl onServicesDiscovered(_di_JBluetoothGatt gatt, int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLBluetoothGattCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattCallbackClass,_di_JRTLBluetoothGattCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattCallbackClass,_di_JRTLBluetoothGattCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLBluetoothGattCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattCallbackClass,_di_JRTLBluetoothGattCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLBluetoothGattCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D15BDFD6-3017-47B1-9B54-5BDA5EEDA874}") JRTLBluetoothGattListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{EA9B991B-935B-4926-BD92-E8EFDB39ADAD}") JRTLBluetoothGattListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCharacteristicChanged(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual void __cdecl onCharacteristicRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	virtual void __cdecl onCharacteristicWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattCharacteristic characteristic, int status) = 0 ;
	virtual void __cdecl onConnectionStateChange(_di_JBluetoothGatt gatt, int status, int newState) = 0 ;
	virtual void __cdecl onDescriptorRead(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	virtual void __cdecl onDescriptorWrite(_di_JBluetoothGatt gatt, _di_JBluetoothGattDescriptor descriptor, int status) = 0 ;
	virtual void __cdecl onReadRemoteRssi(_di_JBluetoothGatt gatt, int rssi, int status) = 0 ;
	virtual void __cdecl onReliableWriteCompleted(_di_JBluetoothGatt gatt, int status) = 0 ;
	virtual void __cdecl onServicesDiscovered(_di_JBluetoothGatt gatt, int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLBluetoothGattListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattListenerClass,_di_JRTLBluetoothGattListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattListenerClass,_di_JRTLBluetoothGattListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLBluetoothGattListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattListenerClass,_di_JRTLBluetoothGattListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLBluetoothGattListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF1E1FD4-CE1D-4B81-8CCB-BF672D420CB2}") JRTLBluetoothGattServerCallbackClass  : public JBluetoothGattServerCallbackClass 
{
	HIDESBASE virtual _di_JRTLBluetoothGattServerCallback __cdecl init(_di_JRTLBluetoothGattServerListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{C7A6B714-4BBA-4877-BEC8-146C2B55BC81}") JRTLBluetoothGattServerCallback  : public JBluetoothGattServerCallback 
{
	HIDESBASE virtual void __cdecl onCharacteristicReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	HIDESBASE virtual void __cdecl onCharacteristicWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattCharacteristic characteristic, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	HIDESBASE virtual void __cdecl onConnectionStateChange(_di_JBluetoothDevice device, int status, int newState) = 0 ;
	HIDESBASE virtual void __cdecl onDescriptorReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattDescriptor descriptor) = 0 ;
	HIDESBASE virtual void __cdecl onDescriptorWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattDescriptor descriptor, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	HIDESBASE virtual void __cdecl onExecuteWrite(_di_JBluetoothDevice device, int requestId, bool execute) = 0 ;
	HIDESBASE virtual void __cdecl onServiceAdded(int status, _di_JBluetoothGattService service) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLBluetoothGattServerCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerCallbackClass,_di_JRTLBluetoothGattServerCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerCallbackClass,_di_JRTLBluetoothGattServerCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLBluetoothGattServerCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerCallbackClass,_di_JRTLBluetoothGattServerCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLBluetoothGattServerCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F666D469-D54E-4AD0-B294-8746F2D68822}") JRTLBluetoothGattServerListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{212A3844-B501-4A9E-A513-BA422AD4F48E}") JRTLBluetoothGattServerListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCharacteristicReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattCharacteristic characteristic) = 0 ;
	virtual void __cdecl onCharacteristicWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattCharacteristic characteristic, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl onConnectionStateChange(_di_JBluetoothDevice device, int status, int newState) = 0 ;
	virtual void __cdecl onDescriptorReadRequest(_di_JBluetoothDevice device, int requestId, int offset, _di_JBluetoothGattDescriptor descriptor) = 0 ;
	virtual void __cdecl onDescriptorWriteRequest(_di_JBluetoothDevice device, int requestId, _di_JBluetoothGattDescriptor descriptor, bool preparedWrite, bool responseNeeded, int offset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl onExecuteWrite(_di_JBluetoothDevice device, int requestId, bool execute) = 0 ;
	virtual void __cdecl onServiceAdded(int status, _di_JBluetoothGattService service) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLBluetoothGattServerListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerListenerClass,_di_JRTLBluetoothGattServerListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerListenerClass,_di_JRTLBluetoothGattServerListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLBluetoothGattServerListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLBluetoothGattServerListenerClass,_di_JRTLBluetoothGattServerListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLBluetoothGattServerListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C0E01FDC-4190-46E5-83D7-A6639511BC81}") JAdvertiseCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetADVERTISE_FAILED_ALREADY_STARTED() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_DATA_TOO_LARGE() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_FEATURE_UNSUPPORTED() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_TOO_MANY_ADVERTISERS() = 0 ;
	HIDESBASE virtual _di_JAdvertiseCallback __cdecl init() = 0 ;
	__property int ADVERTISE_FAILED_ALREADY_STARTED = {read=_GetADVERTISE_FAILED_ALREADY_STARTED};
	__property int ADVERTISE_FAILED_DATA_TOO_LARGE = {read=_GetADVERTISE_FAILED_DATA_TOO_LARGE};
	__property int ADVERTISE_FAILED_FEATURE_UNSUPPORTED = {read=_GetADVERTISE_FAILED_FEATURE_UNSUPPORTED};
	__property int ADVERTISE_FAILED_INTERNAL_ERROR = {read=_GetADVERTISE_FAILED_INTERNAL_ERROR};
	__property int ADVERTISE_FAILED_TOO_MANY_ADVERTISERS = {read=_GetADVERTISE_FAILED_TOO_MANY_ADVERTISERS};
};

__interface  INTERFACE_UUID("{D4C9216C-7F9A-4CBF-8B2B-223023389F7F}") JAdvertiseCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onStartFailure(int errorCode) = 0 ;
	virtual void __cdecl onStartSuccess(_di_JAdvertiseSettings settingsInEffect) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertiseCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseCallbackClass,_di_JAdvertiseCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseCallbackClass,_di_JAdvertiseCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertiseCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseCallbackClass,_di_JAdvertiseCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertiseCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D904B990-967D-4B88-A845-A6D0A3AAB229}") JAdvertiseDataClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{1A692105-2B87-4D48-AA87-AE3D4874D1A6}") JAdvertiseData  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual bool __cdecl getIncludeDeviceName() = 0 ;
	virtual bool __cdecl getIncludeTxPowerLevel() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Util::_di_JSparseArray>* __cdecl getManufacturerSpecificData() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JMap>* __cdecl getServiceData() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getServiceUuids() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertiseData : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseDataClass,_di_JAdvertiseData>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseDataClass,_di_JAdvertiseData> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertiseData() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseDataClass,_di_JAdvertiseData>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertiseData() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{04AD7CFA-5013-49D7-8714-866B66ABCABF}") JAdvertiseData_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAdvertiseData_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{1927C788-38E0-406B-886C-7939CBA10C6F}") JAdvertiseData_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdvertiseData_Builder __cdecl addManufacturerData(int manufacturerId, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* manufacturerSpecificData) = 0 ;
	virtual _di_JAdvertiseData_Builder __cdecl addServiceData(Androidapi::Jni::Os::_di_JParcelUuid serviceDataUuid, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* serviceData) = 0 ;
	virtual _di_JAdvertiseData_Builder __cdecl addServiceUuid(Androidapi::Jni::Os::_di_JParcelUuid serviceUuid) = 0 ;
	virtual _di_JAdvertiseData __cdecl build() = 0 ;
	virtual _di_JAdvertiseData_Builder __cdecl setIncludeDeviceName(bool includeDeviceName) = 0 ;
	virtual _di_JAdvertiseData_Builder __cdecl setIncludeTxPowerLevel(bool includeTxPowerLevel) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertiseData_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseData_BuilderClass,_di_JAdvertiseData_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseData_BuilderClass,_di_JAdvertiseData_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertiseData_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseData_BuilderClass,_di_JAdvertiseData_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertiseData_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5F84BBCE-073D-4CFE-AD88-51313256A925}") JAdvertiseSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetADVERTISE_MODE_BALANCED() = 0 ;
	virtual int __cdecl _GetADVERTISE_MODE_LOW_LATENCY() = 0 ;
	virtual int __cdecl _GetADVERTISE_MODE_LOW_POWER() = 0 ;
	virtual int __cdecl _GetADVERTISE_TX_POWER_HIGH() = 0 ;
	virtual int __cdecl _GetADVERTISE_TX_POWER_LOW() = 0 ;
	virtual int __cdecl _GetADVERTISE_TX_POWER_MEDIUM() = 0 ;
	virtual int __cdecl _GetADVERTISE_TX_POWER_ULTRA_LOW() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property int ADVERTISE_MODE_BALANCED = {read=_GetADVERTISE_MODE_BALANCED};
	__property int ADVERTISE_MODE_LOW_LATENCY = {read=_GetADVERTISE_MODE_LOW_LATENCY};
	__property int ADVERTISE_MODE_LOW_POWER = {read=_GetADVERTISE_MODE_LOW_POWER};
	__property int ADVERTISE_TX_POWER_HIGH = {read=_GetADVERTISE_TX_POWER_HIGH};
	__property int ADVERTISE_TX_POWER_LOW = {read=_GetADVERTISE_TX_POWER_LOW};
	__property int ADVERTISE_TX_POWER_MEDIUM = {read=_GetADVERTISE_TX_POWER_MEDIUM};
	__property int ADVERTISE_TX_POWER_ULTRA_LOW = {read=_GetADVERTISE_TX_POWER_ULTRA_LOW};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{9959EE83-A90F-4A14-9722-F7D1F079621A}") JAdvertiseSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getMode() = 0 ;
	virtual int __cdecl getTimeout() = 0 ;
	virtual int __cdecl getTxPowerLevel() = 0 ;
	virtual bool __cdecl isConnectable() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertiseSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettingsClass,_di_JAdvertiseSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettingsClass,_di_JAdvertiseSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertiseSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettingsClass,_di_JAdvertiseSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertiseSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B83834DB-02C7-47F7-AFEC-D8454A69D8A5}") JAdvertiseSettings_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAdvertiseSettings_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{90BF25C9-3B6B-4859-8FA3-66CDB830089A}") JAdvertiseSettings_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdvertiseSettings __cdecl build() = 0 ;
	virtual _di_JAdvertiseSettings_Builder __cdecl setAdvertiseMode(int advertiseMode) = 0 ;
	virtual _di_JAdvertiseSettings_Builder __cdecl setConnectable(bool connectable) = 0 ;
	virtual _di_JAdvertiseSettings_Builder __cdecl setTimeout(int timeoutMillis) = 0 ;
	virtual _di_JAdvertiseSettings_Builder __cdecl setTxPowerLevel(int txPowerLevel) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertiseSettings_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettings_BuilderClass,_di_JAdvertiseSettings_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettings_BuilderClass,_di_JAdvertiseSettings_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertiseSettings_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertiseSettings_BuilderClass,_di_JAdvertiseSettings_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertiseSettings_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0DD37CF8-1353-4286-98D1-7799F2D490F4}") JAdvertisingSetClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{428985DA-D77E-4628-8A6D-EDDABD8E1B73}") JAdvertisingSet  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl enableAdvertising(bool enable, int duration, int maxExtendedAdvertisingEvents) = 0 ;
	virtual void __cdecl setAdvertisingData(_di_JAdvertiseData advertiseData) = 0 ;
	virtual void __cdecl setAdvertisingParameters(_di_JAdvertisingSetParameters parameters) = 0 ;
	virtual void __cdecl setPeriodicAdvertisingData(_di_JAdvertiseData periodicData) = 0 ;
	virtual void __cdecl setPeriodicAdvertisingEnabled(bool enable) = 0 ;
	virtual void __cdecl setPeriodicAdvertisingParameters(_di_JPeriodicAdvertisingParameters parameters) = 0 ;
	virtual void __cdecl setScanResponseData(_di_JAdvertiseData scanResponse) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertisingSet : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetClass,_di_JAdvertisingSet>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetClass,_di_JAdvertisingSet> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertisingSet() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetClass,_di_JAdvertisingSet>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertisingSet() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4C1FC767-D422-4A72-9EE2-C12F536E8049}") JAdvertisingSetCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetADVERTISE_FAILED_ALREADY_STARTED() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_DATA_TOO_LARGE() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_FEATURE_UNSUPPORTED() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetADVERTISE_FAILED_TOO_MANY_ADVERTISERS() = 0 ;
	virtual int __cdecl _GetADVERTISE_SUCCESS() = 0 ;
	HIDESBASE virtual _di_JAdvertisingSetCallback __cdecl init() = 0 ;
	__property int ADVERTISE_FAILED_ALREADY_STARTED = {read=_GetADVERTISE_FAILED_ALREADY_STARTED};
	__property int ADVERTISE_FAILED_DATA_TOO_LARGE = {read=_GetADVERTISE_FAILED_DATA_TOO_LARGE};
	__property int ADVERTISE_FAILED_FEATURE_UNSUPPORTED = {read=_GetADVERTISE_FAILED_FEATURE_UNSUPPORTED};
	__property int ADVERTISE_FAILED_INTERNAL_ERROR = {read=_GetADVERTISE_FAILED_INTERNAL_ERROR};
	__property int ADVERTISE_FAILED_TOO_MANY_ADVERTISERS = {read=_GetADVERTISE_FAILED_TOO_MANY_ADVERTISERS};
	__property int ADVERTISE_SUCCESS = {read=_GetADVERTISE_SUCCESS};
};

__interface  INTERFACE_UUID("{F90414F7-95C5-4D53-9050-1275567B735C}") JAdvertisingSetCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onAdvertisingDataSet(_di_JAdvertisingSet advertisingSet, int status) = 0 ;
	virtual void __cdecl onAdvertisingEnabled(_di_JAdvertisingSet advertisingSet, bool enable, int status) = 0 ;
	virtual void __cdecl onAdvertisingParametersUpdated(_di_JAdvertisingSet advertisingSet, int txPower, int status) = 0 ;
	virtual void __cdecl onAdvertisingSetStarted(_di_JAdvertisingSet advertisingSet, int txPower, int status) = 0 ;
	virtual void __cdecl onAdvertisingSetStopped(_di_JAdvertisingSet advertisingSet) = 0 ;
	virtual void __cdecl onPeriodicAdvertisingDataSet(_di_JAdvertisingSet advertisingSet, int status) = 0 ;
	virtual void __cdecl onPeriodicAdvertisingEnabled(_di_JAdvertisingSet advertisingSet, bool enable, int status) = 0 ;
	virtual void __cdecl onPeriodicAdvertisingParametersUpdated(_di_JAdvertisingSet advertisingSet, int status) = 0 ;
	virtual void __cdecl onScanResponseDataSet(_di_JAdvertisingSet advertisingSet, int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertisingSetCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetCallbackClass,_di_JAdvertisingSetCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetCallbackClass,_di_JAdvertisingSetCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertisingSetCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetCallbackClass,_di_JAdvertisingSetCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertisingSetCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A118B424-8CFF-478E-AA2A-C7AD4A4B7720}") JAdvertisingSetParametersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetINTERVAL_HIGH() = 0 ;
	virtual int __cdecl _GetINTERVAL_LOW() = 0 ;
	virtual int __cdecl _GetINTERVAL_MAX() = 0 ;
	virtual int __cdecl _GetINTERVAL_MEDIUM() = 0 ;
	virtual int __cdecl _GetINTERVAL_MIN() = 0 ;
	virtual int __cdecl _GetTX_POWER_HIGH() = 0 ;
	virtual int __cdecl _GetTX_POWER_LOW() = 0 ;
	virtual int __cdecl _GetTX_POWER_MAX() = 0 ;
	virtual int __cdecl _GetTX_POWER_MEDIUM() = 0 ;
	virtual int __cdecl _GetTX_POWER_MIN() = 0 ;
	virtual int __cdecl _GetTX_POWER_ULTRA_LOW() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int INTERVAL_HIGH = {read=_GetINTERVAL_HIGH};
	__property int INTERVAL_LOW = {read=_GetINTERVAL_LOW};
	__property int INTERVAL_MAX = {read=_GetINTERVAL_MAX};
	__property int INTERVAL_MEDIUM = {read=_GetINTERVAL_MEDIUM};
	__property int INTERVAL_MIN = {read=_GetINTERVAL_MIN};
	__property int TX_POWER_HIGH = {read=_GetTX_POWER_HIGH};
	__property int TX_POWER_LOW = {read=_GetTX_POWER_LOW};
	__property int TX_POWER_MAX = {read=_GetTX_POWER_MAX};
	__property int TX_POWER_MEDIUM = {read=_GetTX_POWER_MEDIUM};
	__property int TX_POWER_MIN = {read=_GetTX_POWER_MIN};
	__property int TX_POWER_ULTRA_LOW = {read=_GetTX_POWER_ULTRA_LOW};
};

__interface  INTERFACE_UUID("{8C218B5A-714E-4597-8541-EF64EC367A70}") JAdvertisingSetParameters  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getInterval() = 0 ;
	virtual int __cdecl getPrimaryPhy() = 0 ;
	virtual int __cdecl getSecondaryPhy() = 0 ;
	virtual int __cdecl getTxPowerLevel() = 0 ;
	virtual bool __cdecl includeTxPower() = 0 ;
	virtual bool __cdecl isAnonymous() = 0 ;
	virtual bool __cdecl isConnectable() = 0 ;
	virtual bool __cdecl isLegacy() = 0 ;
	virtual bool __cdecl isScannable() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertisingSetParameters : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParametersClass,_di_JAdvertisingSetParameters>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParametersClass,_di_JAdvertisingSetParameters> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertisingSetParameters() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParametersClass,_di_JAdvertisingSetParameters>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertisingSetParameters() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BC2C47DE-8C72-430B-BC4F-8F5B6B1EBAAC}") JAdvertisingSetParameters_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAdvertisingSetParameters_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{580EFC33-4F03-4673-ABA9-4771215EA7F3}") JAdvertisingSetParameters_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdvertisingSetParameters __cdecl build() = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setAnonymous(bool isAnonymous) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setConnectable(bool connectable) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setIncludeTxPower(bool includeTxPower) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setInterval(int interval) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setLegacyMode(bool isLegacy) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setPrimaryPhy(int primaryPhy) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setScannable(bool scannable) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setSecondaryPhy(int secondaryPhy) = 0 ;
	virtual _di_JAdvertisingSetParameters_Builder __cdecl setTxPowerLevel(int txPowerLevel) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdvertisingSetParameters_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParameters_BuilderClass,_di_JAdvertisingSetParameters_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParameters_BuilderClass,_di_JAdvertisingSetParameters_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdvertisingSetParameters_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdvertisingSetParameters_BuilderClass,_di_JAdvertisingSetParameters_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdvertisingSetParameters_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80721D97-DB54-461C-A1D0-A67526BCEF9C}") JBluetoothLeAdvertiserClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{62DF5392-8FFA-4F1A-A801-2DB6DC44C9B3}") JBluetoothLeAdvertiser  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl startAdvertising(_di_JAdvertiseSettings settings, _di_JAdvertiseData advertiseData, _di_JAdvertiseCallback callback) = 0 /* overload */;
	virtual void __cdecl startAdvertising(_di_JAdvertiseSettings settings, _di_JAdvertiseData advertiseData, _di_JAdvertiseData scanResponse, _di_JAdvertiseCallback callback) = 0 /* overload */;
	virtual void __cdecl startAdvertisingSet(_di_JAdvertisingSetParameters parameters, _di_JAdvertiseData advertiseData, _di_JAdvertiseData scanResponse, _di_JPeriodicAdvertisingParameters periodicParameters, _di_JAdvertiseData periodicData, _di_JAdvertisingSetCallback callback) = 0 /* overload */;
	virtual void __cdecl startAdvertisingSet(_di_JAdvertisingSetParameters parameters, _di_JAdvertiseData advertiseData, _di_JAdvertiseData scanResponse, _di_JPeriodicAdvertisingParameters periodicParameters, _di_JAdvertiseData periodicData, _di_JAdvertisingSetCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl startAdvertisingSet(_di_JAdvertisingSetParameters parameters, _di_JAdvertiseData advertiseData, _di_JAdvertiseData scanResponse, _di_JPeriodicAdvertisingParameters periodicParameters, _di_JAdvertiseData periodicData, int duration, int maxExtendedAdvertisingEvents, _di_JAdvertisingSetCallback callback) = 0 /* overload */;
	virtual void __cdecl startAdvertisingSet(_di_JAdvertisingSetParameters parameters, _di_JAdvertiseData advertiseData, _di_JAdvertiseData scanResponse, _di_JPeriodicAdvertisingParameters periodicParameters, _di_JAdvertiseData periodicData, int duration, int maxExtendedAdvertisingEvents, _di_JAdvertisingSetCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl stopAdvertising(_di_JAdvertiseCallback callback) = 0 ;
	virtual void __cdecl stopAdvertisingSet(_di_JAdvertisingSetCallback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothLeAdvertiser : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeAdvertiserClass,_di_JBluetoothLeAdvertiser>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeAdvertiserClass,_di_JBluetoothLeAdvertiser> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothLeAdvertiser() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeAdvertiserClass,_di_JBluetoothLeAdvertiser>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothLeAdvertiser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{037CB52E-670F-4EC0-8036-7B518C73D8D6}") JBluetoothLeScannerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CALLBACK_TYPE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ERROR_CODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LIST_SCAN_RESULT() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CALLBACK_TYPE = {read=_GetEXTRA_CALLBACK_TYPE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ERROR_CODE = {read=_GetEXTRA_ERROR_CODE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LIST_SCAN_RESULT = {read=_GetEXTRA_LIST_SCAN_RESULT};
};

__interface  INTERFACE_UUID("{D9746B62-4BD2-49A5-A756-954FC149B136}") JBluetoothLeScanner  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl flushPendingScanResults(_di_JScanCallback callback) = 0 ;
	virtual void __cdecl startScan(_di_JScanCallback callback) = 0 /* overload */;
	virtual void __cdecl startScan(Androidapi::Jni::Javatypes::_di_JList filters, _di_JScanSettings settings, _di_JScanCallback callback) = 0 /* overload */;
	virtual void __cdecl stopScan(_di_JScanCallback callback) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBluetoothLeScanner : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeScannerClass,_di_JBluetoothLeScanner>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeScannerClass,_di_JBluetoothLeScanner> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBluetoothLeScanner() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothLeScannerClass,_di_JBluetoothLeScanner>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBluetoothLeScanner() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{550E5511-B44F-4EAF-80B9-FCF2C533B094}") JPeriodicAdvertisingParametersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{506432D6-7F07-4E2F-92B2-AF7D1BF1AFA1}") JPeriodicAdvertisingParameters  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual bool __cdecl getIncludeTxPower() = 0 ;
	virtual int __cdecl getInterval() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPeriodicAdvertisingParameters : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParametersClass,_di_JPeriodicAdvertisingParameters>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParametersClass,_di_JPeriodicAdvertisingParameters> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPeriodicAdvertisingParameters() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParametersClass,_di_JPeriodicAdvertisingParameters>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPeriodicAdvertisingParameters() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C2E7C307-018C-47B3-8E49-A8A15C4771E8}") JPeriodicAdvertisingParameters_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPeriodicAdvertisingParameters_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{C9A0174E-DE54-492F-88A7-BFA145CDC9A2}") JPeriodicAdvertisingParameters_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JPeriodicAdvertisingParameters __cdecl build() = 0 ;
	virtual _di_JPeriodicAdvertisingParameters_Builder __cdecl setIncludeTxPower(bool includeTxPower) = 0 ;
	virtual _di_JPeriodicAdvertisingParameters_Builder __cdecl setInterval(int interval) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPeriodicAdvertisingParameters_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParameters_BuilderClass,_di_JPeriodicAdvertisingParameters_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParameters_BuilderClass,_di_JPeriodicAdvertisingParameters_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPeriodicAdvertisingParameters_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPeriodicAdvertisingParameters_BuilderClass,_di_JPeriodicAdvertisingParameters_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPeriodicAdvertisingParameters_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{045C98C0-0048-4C5C-98B2-8623785277B1}") JRTLAdvertiseCallbackClass  : public JAdvertiseCallbackClass 
{
	HIDESBASE virtual _di_JRTLAdvertiseCallback __cdecl init(_di_JRTLAdvertiseListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{65D3084A-3121-4A97-B693-83122D1B1702}") JRTLAdvertiseCallback  : public JAdvertiseCallback 
{
	HIDESBASE virtual void __cdecl onStartFailure(int errorCode) = 0 ;
	HIDESBASE virtual void __cdecl onStartSuccess(_di_JAdvertiseSettings settingsInEffect) = 0 ;
	virtual void __cdecl setListener(_di_JRTLAdvertiseListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLAdvertiseCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseCallbackClass,_di_JRTLAdvertiseCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseCallbackClass,_di_JRTLAdvertiseCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLAdvertiseCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseCallbackClass,_di_JRTLAdvertiseCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLAdvertiseCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F4BB1C50-6C5C-43AD-9BED-578672E9F496}") JRTLAdvertiseListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{2B3AE1FB-DF9C-42BD-9C4A-BFA601B8E74C}") JRTLAdvertiseListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStartFailure(int errorCode) = 0 ;
	virtual void __cdecl onStartSuccess(_di_JAdvertiseSettings settingsInEffect) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLAdvertiseListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseListenerClass,_di_JRTLAdvertiseListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseListenerClass,_di_JRTLAdvertiseListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLAdvertiseListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLAdvertiseListenerClass,_di_JRTLAdvertiseListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLAdvertiseListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{54AC4025-A2D2-4F97-96A8-8B99C58C31C3}") JScanCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetSCAN_FAILED_ALREADY_STARTED() = 0 ;
	virtual int __cdecl _GetSCAN_FAILED_APPLICATION_REGISTRATION_FAILED() = 0 ;
	virtual int __cdecl _GetSCAN_FAILED_FEATURE_UNSUPPORTED() = 0 ;
	virtual int __cdecl _GetSCAN_FAILED_INTERNAL_ERROR() = 0 ;
	HIDESBASE virtual _di_JScanCallback __cdecl init() = 0 ;
	__property int SCAN_FAILED_ALREADY_STARTED = {read=_GetSCAN_FAILED_ALREADY_STARTED};
	__property int SCAN_FAILED_APPLICATION_REGISTRATION_FAILED = {read=_GetSCAN_FAILED_APPLICATION_REGISTRATION_FAILED};
	__property int SCAN_FAILED_FEATURE_UNSUPPORTED = {read=_GetSCAN_FAILED_FEATURE_UNSUPPORTED};
	__property int SCAN_FAILED_INTERNAL_ERROR = {read=_GetSCAN_FAILED_INTERNAL_ERROR};
};

__interface  INTERFACE_UUID("{7EFE6E06-FCDD-448F-92BA-D29B0AC06FF3}") JScanCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onBatchScanResults(Androidapi::Jni::Javatypes::_di_JList results) = 0 ;
	virtual void __cdecl onScanFailed(int errorCode) = 0 ;
	virtual void __cdecl onScanResult(int callbackType, _di_Jle_ScanResult result) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanCallbackClass,_di_JScanCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanCallbackClass,_di_JScanCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanCallbackClass,_di_JScanCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3A14BBCE-97EF-46DA-9A13-0B5AF26A986A}") JRTLScanCallbackClass  : public JScanCallbackClass 
{
	HIDESBASE virtual _di_JRTLScanCallback __cdecl init(_di_JRTLScanListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{80A73669-9B5E-4B84-BB77-9AC8485E3F06}") JRTLScanCallback  : public JScanCallback 
{
	HIDESBASE virtual void __cdecl onBatchScanResults(Androidapi::Jni::Javatypes::_di_JList results) = 0 ;
	HIDESBASE virtual void __cdecl onScanFailed(int errorCode) = 0 ;
	HIDESBASE virtual void __cdecl onScanResult(int callbackType, _di_Jle_ScanResult result) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLScanCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanCallbackClass,_di_JRTLScanCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanCallbackClass,_di_JRTLScanCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLScanCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanCallbackClass,_di_JRTLScanCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLScanCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AA7E0D86-AC68-4A4B-9858-6C85666BB24B}") JRTLScanListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{1607A08B-2DCF-4423-B1F7-CFC3C8DB2331}") JRTLScanListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onBatchScanResults(Androidapi::Jni::Javatypes::_di_JList results) = 0 ;
	virtual void __cdecl onScanFailed(int errorCode) = 0 ;
	virtual void __cdecl onScanResult(int callbackType, _di_Jle_ScanResult result) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLScanListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanListenerClass,_di_JRTLScanListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanListenerClass,_di_JRTLScanListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLScanListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLScanListenerClass,_di_JRTLScanListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLScanListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3F554F98-0D00-4364-8C99-0F69610E404E}") JScanFilterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{6A6D8301-C452-45DB-BE33-A23ABF3564E4}") JScanFilter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceName() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getManufacturerData() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getManufacturerDataMask() = 0 ;
	virtual int __cdecl getManufacturerId() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getServiceData() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getServiceDataMask() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelUuid __cdecl getServiceDataUuid() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelUuid __cdecl getServiceUuid() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelUuid __cdecl getServiceUuidMask() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl matches(_di_Jle_ScanResult scanResult) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanFilter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilterClass,_di_JScanFilter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilterClass,_di_JScanFilter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanFilter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilterClass,_di_JScanFilter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanFilter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CA942A72-9984-418B-9053-FCBFFAEF3C76}") JScanFilter_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScanFilter_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{4A1C4430-A3A5-40D7-9C2D-827357F884DC}") JScanFilter_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JScanFilter __cdecl build() = 0 ;
	virtual _di_JScanFilter_Builder __cdecl setDeviceAddress(Androidapi::Jni::Javatypes::_di_JString deviceAddress) = 0 ;
	virtual _di_JScanFilter_Builder __cdecl setDeviceName(Androidapi::Jni::Javatypes::_di_JString deviceName) = 0 ;
	virtual _di_JScanFilter_Builder __cdecl setManufacturerData(int manufacturerId, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* manufacturerData) = 0 /* overload */;
	virtual _di_JScanFilter_Builder __cdecl setManufacturerData(int manufacturerId, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* manufacturerData, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* manufacturerDataMask) = 0 /* overload */;
	virtual _di_JScanFilter_Builder __cdecl setServiceData(Androidapi::Jni::Os::_di_JParcelUuid serviceDataUuid, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* serviceData) = 0 /* overload */;
	virtual _di_JScanFilter_Builder __cdecl setServiceData(Androidapi::Jni::Os::_di_JParcelUuid serviceDataUuid, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* serviceData, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* serviceDataMask) = 0 /* overload */;
	virtual _di_JScanFilter_Builder __cdecl setServiceUuid(Androidapi::Jni::Os::_di_JParcelUuid serviceUuid) = 0 /* overload */;
	virtual _di_JScanFilter_Builder __cdecl setServiceUuid(Androidapi::Jni::Os::_di_JParcelUuid serviceUuid, Androidapi::Jni::Os::_di_JParcelUuid uuidMask) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanFilter_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilter_BuilderClass,_di_JScanFilter_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilter_BuilderClass,_di_JScanFilter_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanFilter_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanFilter_BuilderClass,_di_JScanFilter_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanFilter_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E8C389F7-8E29-44DD-A897-601E4AA601A1}") JScanRecordClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8EE1B96E-AB84-499C-B9F1-1F656029FEE8}") JScanRecord  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getAdvertiseFlags() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getBytes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceName() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Util::_di_JSparseArray>* __cdecl getManufacturerSpecificData() = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getManufacturerSpecificData(int manufacturerId) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JMap>* __cdecl getServiceData() = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getServiceData(Androidapi::Jni::Os::_di_JParcelUuid serviceDataUuid) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getServiceUuids() = 0 ;
	virtual int __cdecl getTxPowerLevel() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanRecord : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanRecordClass,_di_JScanRecord>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanRecordClass,_di_JScanRecord> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanRecord() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanRecordClass,_di_JScanRecord>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanRecord() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C654A063-A05D-4E45-A116-59736A9EAFA9}") Jle_ScanResultClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDATA_COMPLETE() = 0 ;
	virtual int __cdecl _GetDATA_TRUNCATED() = 0 ;
	virtual int __cdecl _GetPERIODIC_INTERVAL_NOT_PRESENT() = 0 ;
	virtual int __cdecl _GetPHY_UNUSED() = 0 ;
	virtual int __cdecl _GetSID_NOT_PRESENT() = 0 ;
	virtual int __cdecl _GetTX_POWER_NOT_PRESENT() = 0 ;
	HIDESBASE virtual _di_Jle_ScanResult __cdecl init(_di_JBluetoothDevice device, _di_JScanRecord scanRecord, int rssi, __int64 timestampNanos) = 0 /* overload */;
	HIDESBASE virtual _di_Jle_ScanResult __cdecl init(_di_JBluetoothDevice device, int eventType, int primaryPhy, int secondaryPhy, int advertisingSid, int txPower, int rssi, int periodicAdvertisingInterval, _di_JScanRecord scanRecord, __int64 timestampNanos) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DATA_COMPLETE = {read=_GetDATA_COMPLETE};
	__property int DATA_TRUNCATED = {read=_GetDATA_TRUNCATED};
	__property int PERIODIC_INTERVAL_NOT_PRESENT = {read=_GetPERIODIC_INTERVAL_NOT_PRESENT};
	__property int PHY_UNUSED = {read=_GetPHY_UNUSED};
	__property int SID_NOT_PRESENT = {read=_GetSID_NOT_PRESENT};
	__property int TX_POWER_NOT_PRESENT = {read=_GetTX_POWER_NOT_PRESENT};
};

__interface  INTERFACE_UUID("{3277CDD4-F1F2-49A6-96FD-99F6C30C828F}") Jle_ScanResult  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getAdvertisingSid() = 0 ;
	virtual int __cdecl getDataStatus() = 0 ;
	virtual _di_JBluetoothDevice __cdecl getDevice() = 0 ;
	virtual int __cdecl getPeriodicAdvertisingInterval() = 0 ;
	virtual int __cdecl getPrimaryPhy() = 0 ;
	virtual int __cdecl getRssi() = 0 ;
	virtual _di_JScanRecord __cdecl getScanRecord() = 0 ;
	virtual int __cdecl getSecondaryPhy() = 0 ;
	virtual __int64 __cdecl getTimestampNanos() = 0 ;
	virtual int __cdecl getTxPower() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isConnectable() = 0 ;
	virtual bool __cdecl isLegacy() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJle_ScanResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jle_ScanResultClass,_di_Jle_ScanResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jle_ScanResultClass,_di_Jle_ScanResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJle_ScanResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jle_ScanResultClass,_di_Jle_ScanResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJle_ScanResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{71D2996A-A5B7-4EE7-961E-C6E939D3A98D}") JScanSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCALLBACK_TYPE_ALL_MATCHES() = 0 ;
	virtual int __cdecl _GetCALLBACK_TYPE_FIRST_MATCH() = 0 ;
	virtual int __cdecl _GetCALLBACK_TYPE_MATCH_LOST() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetMATCH_MODE_AGGRESSIVE() = 0 ;
	virtual int __cdecl _GetMATCH_MODE_STICKY() = 0 ;
	virtual int __cdecl _GetMATCH_NUM_FEW_ADVERTISEMENT() = 0 ;
	virtual int __cdecl _GetMATCH_NUM_MAX_ADVERTISEMENT() = 0 ;
	virtual int __cdecl _GetMATCH_NUM_ONE_ADVERTISEMENT() = 0 ;
	virtual int __cdecl _GetPHY_LE_ALL_SUPPORTED() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_BALANCED() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_LOW_LATENCY() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_LOW_POWER() = 0 ;
	virtual int __cdecl _GetSCAN_MODE_OPPORTUNISTIC() = 0 ;
	__property int CALLBACK_TYPE_ALL_MATCHES = {read=_GetCALLBACK_TYPE_ALL_MATCHES};
	__property int CALLBACK_TYPE_FIRST_MATCH = {read=_GetCALLBACK_TYPE_FIRST_MATCH};
	__property int CALLBACK_TYPE_MATCH_LOST = {read=_GetCALLBACK_TYPE_MATCH_LOST};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int MATCH_MODE_AGGRESSIVE = {read=_GetMATCH_MODE_AGGRESSIVE};
	__property int MATCH_MODE_STICKY = {read=_GetMATCH_MODE_STICKY};
	__property int MATCH_NUM_FEW_ADVERTISEMENT = {read=_GetMATCH_NUM_FEW_ADVERTISEMENT};
	__property int MATCH_NUM_MAX_ADVERTISEMENT = {read=_GetMATCH_NUM_MAX_ADVERTISEMENT};
	__property int MATCH_NUM_ONE_ADVERTISEMENT = {read=_GetMATCH_NUM_ONE_ADVERTISEMENT};
	__property int PHY_LE_ALL_SUPPORTED = {read=_GetPHY_LE_ALL_SUPPORTED};
	__property int SCAN_MODE_BALANCED = {read=_GetSCAN_MODE_BALANCED};
	__property int SCAN_MODE_LOW_LATENCY = {read=_GetSCAN_MODE_LOW_LATENCY};
	__property int SCAN_MODE_LOW_POWER = {read=_GetSCAN_MODE_LOW_POWER};
	__property int SCAN_MODE_OPPORTUNISTIC = {read=_GetSCAN_MODE_OPPORTUNISTIC};
};

__interface  INTERFACE_UUID("{6EFFF088-8CE9-46CB-80E6-6C44513B07BC}") JScanSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getCallbackType() = 0 ;
	virtual bool __cdecl getLegacy() = 0 ;
	virtual int __cdecl getPhy() = 0 ;
	virtual __int64 __cdecl getReportDelayMillis() = 0 ;
	virtual int __cdecl getScanMode() = 0 ;
	virtual int __cdecl getScanResultType() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettingsClass,_di_JScanSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettingsClass,_di_JScanSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettingsClass,_di_JScanSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EAFEC592-65E5-48F5-98C1-C3FD2DC334CB}") JScanSettings_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScanSettings_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{8AF38CAF-C3A9-4319-B138-7132DAF82175}") JScanSettings_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JScanSettings __cdecl build() = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setCallbackType(int callbackType) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setLegacy(bool legacy) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setMatchMode(int matchMode) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setNumOfMatches(int numOfMatches) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setPhy(int phy) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setReportDelay(__int64 reportDelayMillis) = 0 ;
	virtual _di_JScanSettings_Builder __cdecl setScanMode(int scanMode) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScanSettings_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettings_BuilderClass,_di_JScanSettings_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettings_BuilderClass,_di_JScanSettings_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScanSettings_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScanSettings_BuilderClass,_di_JScanSettings_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScanSettings_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetooth */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_BLUETOOTH)
using namespace Androidapi::Jni::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_BluetoothHPP
