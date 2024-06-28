// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.Bluetooth.pas' rev: 34.00 (iOS)

#ifndef Macapi_BluetoothHPP
#define Macapi_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.Consts.hpp>
#include <Macapi.Dispatch.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE CBUUID;
typedef System::DelphiInterface<CBUUID> _di_CBUUID;
__interface DELPHIINTERFACE CBUUIDClass;
typedef System::DelphiInterface<CBUUIDClass> _di_CBUUIDClass;
class DELPHICLASS TCBUUID;
__interface DELPHIINTERFACE CBServiceClass;
typedef System::DelphiInterface<CBServiceClass> _di_CBServiceClass;
__interface DELPHIINTERFACE CBService;
typedef System::DelphiInterface<CBService> _di_CBService;
class DELPHICLASS TCBService;
__interface DELPHIINTERFACE CBCharacteristicClass;
typedef System::DelphiInterface<CBCharacteristicClass> _di_CBCharacteristicClass;
__interface DELPHIINTERFACE CBCharacteristic;
typedef System::DelphiInterface<CBCharacteristic> _di_CBCharacteristic;
class DELPHICLASS TCBCharacteristic;
__interface DELPHIINTERFACE CBMutableCharacteristicClass;
typedef System::DelphiInterface<CBMutableCharacteristicClass> _di_CBMutableCharacteristicClass;
__interface DELPHIINTERFACE CBMutableCharacteristic;
typedef System::DelphiInterface<CBMutableCharacteristic> _di_CBMutableCharacteristic;
class DELPHICLASS TCBMutableCharacteristic;
__interface DELPHIINTERFACE CBDescriptorClass;
typedef System::DelphiInterface<CBDescriptorClass> _di_CBDescriptorClass;
__interface DELPHIINTERFACE CBDescriptor;
typedef System::DelphiInterface<CBDescriptor> _di_CBDescriptor;
class DELPHICLASS TCBDescriptor;
__interface DELPHIINTERFACE CBMutableDescriptorClass;
typedef System::DelphiInterface<CBMutableDescriptorClass> _di_CBMutableDescriptorClass;
__interface DELPHIINTERFACE CBMutableDescriptor;
typedef System::DelphiInterface<CBMutableDescriptor> _di_CBMutableDescriptor;
class DELPHICLASS TCBMutableDescriptor;
__interface DELPHIINTERFACE CBMutableServiceClass;
typedef System::DelphiInterface<CBMutableServiceClass> _di_CBMutableServiceClass;
__interface DELPHIINTERFACE CBMutableService;
typedef System::DelphiInterface<CBMutableService> _di_CBMutableService;
class DELPHICLASS TCBMutableService;
__interface DELPHIINTERFACE CBPeripheralClass;
typedef System::DelphiInterface<CBPeripheralClass> _di_CBPeripheralClass;
__interface DELPHIINTERFACE CBPeripheral;
typedef System::DelphiInterface<CBPeripheral> _di_CBPeripheral;
class DELPHICLASS TCBPeripheral;
__interface DELPHIINTERFACE CBCentralManagerClass;
typedef System::DelphiInterface<CBCentralManagerClass> _di_CBCentralManagerClass;
__interface DELPHIINTERFACE CBCentralManager;
typedef System::DelphiInterface<CBCentralManager> _di_CBCentralManager;
class DELPHICLASS TCBCentralManager;
__interface DELPHIINTERFACE CBCentralManagerDelegate;
typedef System::DelphiInterface<CBCentralManagerDelegate> _di_CBCentralManagerDelegate;
__interface DELPHIINTERFACE CBPeripheralDelegate;
typedef System::DelphiInterface<CBPeripheralDelegate> _di_CBPeripheralDelegate;
__interface DELPHIINTERFACE CBCentralClass;
typedef System::DelphiInterface<CBCentralClass> _di_CBCentralClass;
__interface DELPHIINTERFACE CBCentral;
typedef System::DelphiInterface<CBCentral> _di_CBCentral;
class DELPHICLASS TCBCentralt;
__interface DELPHIINTERFACE CBATTRequestClass;
typedef System::DelphiInterface<CBATTRequestClass> _di_CBATTRequestClass;
__interface DELPHIINTERFACE CBATTRequest;
typedef System::DelphiInterface<CBATTRequest> _di_CBATTRequest;
class DELPHICLASS TCBATTRequest;
__interface DELPHIINTERFACE CBPeripheralManagerClass;
typedef System::DelphiInterface<CBPeripheralManagerClass> _di_CBPeripheralManagerClass;
__interface DELPHIINTERFACE CBPeripheralManager;
typedef System::DelphiInterface<CBPeripheralManager> _di_CBPeripheralManager;
class DELPHICLASS TCBPeripheralManager;
__interface DELPHIINTERFACE CBPeripheralManagerDelegate;
typedef System::DelphiInterface<CBPeripheralManagerDelegate> _di_CBPeripheralManagerDelegate;
//-- type declarations -------------------------------------------------------
typedef void * id;

enum DECLSPEC_DENUM CBCentralManagerState : unsigned char { CBCentralManagerStateUnknown, CBCentralManagerStateResetting, CBCentralManagerStateUnsupported, CBCentralManagerStateUnauthorized, CBCentralManagerStatePoweredOff, CBCentralManagerStatePoweredOn };

enum DECLSPEC_DENUM CBCharacteristicWriteType : unsigned char { CBCharacteristicWriteWithResponse, CBCharacteristicWriteWithoutResponse };

enum DECLSPEC_DENUM CBPeripheralState : unsigned char { CBPeripheralStateDisconnected, CBPeripheralStateConnecting, CBPeripheralStateConnected };

typedef System::Word CBCharacteristicProperties;

typedef System::Byte CBAttributePermissions;

typedef void * CFUUIDRef;

__interface  INTERFACE_UUID("{995CEAD8-892B-4EA7-B627-638C5EF1F4B2}") CBUUID  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSData __cdecl data() = 0 ;
};

__interface  INTERFACE_UUID("{56E591FF-4BC1-4FC6-9FB7-2DC4E6DA8D9C}") CBUUIDClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_CBUUID __cdecl UUIDWithCFUUID(void * theUUID) = 0 ;
	virtual _di_CBUUID __cdecl UUIDWithData(Iosapi::Foundation::_di_NSData theData) = 0 ;
	virtual _di_CBUUID __cdecl UUIDWithNSUUID(Iosapi::Foundation::_di_NSUUID theUUID) = 0 ;
	virtual _di_CBUUID __cdecl UUIDWithString(Iosapi::Foundation::_di_NSString theString) = 0 ;
};

class PASCALIMPLEMENTATION TCBUUID : public Macapi::Objectivec::TOCGenericImport__2<_di_CBUUIDClass,_di_CBUUID>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBUUIDClass,_di_CBUUID> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBUUID(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBUUIDClass,_di_CBUUID>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBUUID() { }
	
};


__interface  INTERFACE_UUID("{772D1637-D6A7-469C-A455-D4573849F7EE}") CBServiceClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5D492AFB-27B2-4156-BAA6-83239A623667}") CBService  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl characteristics() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl includedServices() = 0 ;
	virtual bool __cdecl isPrimary() = 0 ;
	virtual void * __cdecl peripheral() = 0 ;
	virtual _di_CBUUID __cdecl UUID() = 0 ;
};

class PASCALIMPLEMENTATION TCBService : public Macapi::Objectivec::TOCGenericImport__2<_di_CBServiceClass,_di_CBService>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBServiceClass,_di_CBService> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBService(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBServiceClass,_di_CBService>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBService() { }
	
};


__interface  INTERFACE_UUID("{5057C68A-39B5-4F35-AD42-7CA63E8F5A72}") CBCharacteristicClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{189857D0-0AF7-4559-819F-EF98355180FD}") CBCharacteristic  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl descriptors() = 0 ;
	virtual bool __cdecl isBroadcasted() = 0 ;
	virtual bool __cdecl isNotifying() = 0 ;
	virtual System::Word __cdecl properties() = 0 ;
	virtual _di_CBService __cdecl service() = 0 ;
	virtual _di_CBUUID __cdecl UUID() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TCBCharacteristic : public Macapi::Objectivec::TOCGenericImport__2<_di_CBCharacteristicClass,_di_CBCharacteristic>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBCharacteristicClass,_di_CBCharacteristic> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBCharacteristic(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBCharacteristicClass,_di_CBCharacteristic>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBCharacteristic() { }
	
};


__interface  INTERFACE_UUID("{0CFB069D-5DC7-46C9-9844-7424D4B36A4D}") CBMutableCharacteristicClass  : public CBCharacteristicClass 
{
	
};

__interface  INTERFACE_UUID("{73C19465-F2D8-439F-AC5F-BC0AA205E867}") CBMutableCharacteristic  : public CBCharacteristic 
{
	virtual void __cdecl setValue(Iosapi::Foundation::_di_NSData value) = 0 ;
	virtual System::Byte __cdecl permissions() = 0 ;
	virtual void __cdecl setPermissions(System::Byte permissions) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl subscribedCentrals() = 0 ;
	virtual void __cdecl setSubscribedCentrals(Iosapi::Foundation::_di_NSArray subscribedCentrals) = 0 ;
	virtual void __cdecl setDescriptors(Iosapi::Foundation::_di_NSArray descriptors) = 0 ;
	virtual void * __cdecl initWithType(_di_CBUUID UUID, System::Word properties, Iosapi::Foundation::_di_NSData value, System::Byte permissions) = 0 ;
};

class PASCALIMPLEMENTATION TCBMutableCharacteristic : public Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableCharacteristicClass,_di_CBMutableCharacteristic>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableCharacteristicClass,_di_CBMutableCharacteristic> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBMutableCharacteristic(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableCharacteristicClass,_di_CBMutableCharacteristic>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBMutableCharacteristic() { }
	
};


__interface  INTERFACE_UUID("{3C40361F-B981-4F30-A060-42EDFCE97E56}") CBDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{34CE2617-A15D-4EF3-A97E-299A4E7F80EA}") CBDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual _di_CBCharacteristic __cdecl characteristic() = 0 ;
	virtual _di_CBUUID __cdecl UUID() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TCBDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_CBDescriptorClass,_di_CBDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBDescriptorClass,_di_CBDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBDescriptorClass,_di_CBDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBDescriptor() { }
	
};


__interface  INTERFACE_UUID("{D7B6A773-A601-4629-9FF8-9702D49F6988}") CBMutableDescriptorClass  : public CBDescriptorClass 
{
	
};

__interface  INTERFACE_UUID("{BA0E8A73-5673-4AE0-86C0-86DF97BF1D36}") CBMutableDescriptor  : public CBDescriptor 
{
	virtual void * __cdecl initWithType(_di_CBUUID UUID, void * value) = 0 ;
};

class PASCALIMPLEMENTATION TCBMutableDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableDescriptorClass,_di_CBMutableDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableDescriptorClass,_di_CBMutableDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBMutableDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableDescriptorClass,_di_CBMutableDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBMutableDescriptor() { }
	
};


__interface  INTERFACE_UUID("{772D1637-D6A7-469C-A455-D4573849F7EE}") CBMutableServiceClass  : public CBServiceClass 
{
	
};

__interface  INTERFACE_UUID("{40180826-45F8-47AF-940C-17A1FD3391A7}") CBMutableService  : public CBService 
{
	virtual void * __cdecl initWithType(_di_CBUUID UUID, bool primary) = 0 ;
	virtual void __cdecl setCharacteristics(Iosapi::Foundation::_di_NSArray characteristics) = 0 ;
	virtual void __cdecl setIncludedServices(Iosapi::Foundation::_di_NSArray services) = 0 ;
};

class PASCALIMPLEMENTATION TCBMutableService : public Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableServiceClass,_di_CBMutableService>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableServiceClass,_di_CBMutableService> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBMutableService(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBMutableServiceClass,_di_CBMutableService>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBMutableService() { }
	
};


__interface  INTERFACE_UUID("{B1B5C4C9-84A7-4ABE-A82E-66DB0A50392B}") CBPeripheralClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C51D2286-153F-4156-AF4C-F57A029CDD1D}") CBPeripheral  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual Iosapi::Foundation::_di_NSUUID __cdecl identifier() = 0 ;
	virtual bool __cdecl isConnected() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl RSSI() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl services() = 0 ;
	virtual CBPeripheralState __cdecl state() = 0 ;
	virtual void * __cdecl UUID() = 0 ;
	virtual void __cdecl discoverCharacteristics(Iosapi::Foundation::_di_NSArray characteristicUUIDs, _di_CBService forService) = 0 ;
	virtual void __cdecl discoverDescriptorsForCharacteristic(_di_CBCharacteristic characteristic) = 0 ;
	virtual void __cdecl discoverIncludedServices(Iosapi::Foundation::_di_NSArray includedServiceUUIDs, _di_CBService forService) = 0 ;
	virtual void __cdecl discoverServices(Iosapi::Foundation::_di_NSArray serviceUUIDs) = 0 ;
	virtual void __cdecl readRSSI() = 0 ;
	virtual void __cdecl readValueForCharacteristic(_di_CBCharacteristic characteristic) = 0 ;
	virtual void __cdecl readValueForDescriptor(_di_CBDescriptor descriptor) = 0 ;
	virtual void __cdecl setNotifyValue(bool enabled, _di_CBCharacteristic forCharacteristic) = 0 ;
	virtual void __cdecl writeValue(Iosapi::Foundation::_di_NSData data, _di_CBCharacteristic characteristic, CBCharacteristicWriteType type) = 0 /* overload */;
	virtual void __cdecl writeValue(Iosapi::Foundation::_di_NSData data, _di_CBDescriptor forDescriptor) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TCBPeripheral : public Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralClass,_di_CBPeripheral>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralClass,_di_CBPeripheral> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBPeripheral(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralClass,_di_CBPeripheral>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBPeripheral() { }
	
};


__interface  INTERFACE_UUID("{BC305559-F794-4C69-977C-A6F04D5F012B}") CBCentralManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{587D1855-5B53-43DA-91AF-AF9D93FFDB9F}") CBCentralManager  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual CBCentralManagerState __cdecl state() = 0 ;
	virtual void __cdecl cancelPeripheralConnection(_di_CBPeripheral peripheral) = 0 ;
	virtual void __cdecl connectPeripheral(_di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual void * __cdecl initWithDelegate(void * delegate, NativeInt queue) = 0 /* overload */;
	virtual void * __cdecl initWithDelegate(void * delegate, NativeInt queue, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl retrieveConnectedPeripheralsWithServices(Iosapi::Foundation::_di_NSArray identifiers) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl retrievePeripheralsWithServices(Iosapi::Foundation::_di_NSArray identifiers) = 0 ;
	virtual void __cdecl scanForPeripheralsWithServices(Iosapi::Foundation::_di_NSArray serviceUUIDs, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual void __cdecl stopScan() = 0 ;
};

class PASCALIMPLEMENTATION TCBCentralManager : public Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralManagerClass,_di_CBCentralManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralManagerClass,_di_CBCentralManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBCentralManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralManagerClass,_di_CBCentralManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBCentralManager() { }
	
};


__interface  INTERFACE_UUID("{1337817E-92DE-4FA9-8CF2-E00E89125A0F}") CBCentralManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl centralManagerDidUpdateState(_di_CBCentralManager central) = 0 ;
	virtual void __cdecl centralManagerWillRestoreState(_di_CBCentralManager central, Iosapi::Foundation::_di_NSDictionary dict) = 0 ;
	virtual void __cdecl centralManagerDidRetrievePeripherals(_di_CBCentralManager central, Iosapi::Foundation::_di_NSArray peripherals) = 0 ;
	virtual void __cdecl centralManagerDidRetrieveConnectedPeripherals(_di_CBCentralManager central, Iosapi::Foundation::_di_NSArray peripherals) = 0 ;
	virtual void __cdecl centralManagerDidDiscoverPeripheral(_di_CBCentralManager central, _di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSDictionary advertisementData, Iosapi::Foundation::_di_NSNumber RSSI) = 0 ;
	virtual void __cdecl centralManagerDidConnectPeripheral(_di_CBCentralManager central, _di_CBPeripheral peripheral) = 0 ;
	virtual void __cdecl centralManagerDidFailToConnectPeripheral(_di_CBCentralManager central, _di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl centralManagerdidDisconnectPeripheral(_di_CBCentralManager central, _di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSError error) = 0 ;
};

__interface  INTERFACE_UUID("{FD44C8F8-C555-4916-B07C-C0E9ED5033D3}") CBPeripheralDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl peripheralDidUpdateName(_di_CBPeripheral peripheral) = 0 ;
	virtual void __cdecl peripheralDidInvalidateServices _DEPRECATED_ATTRIBUTE0 (_di_CBPeripheral peripheral) = 0 ;
	virtual void __cdecl peripheralDidModifyServices(_di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSArray invalidatedServices) = 0 ;
	virtual void __cdecl peripheralDidUpdateRSSI(_di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidDiscoverServices(_di_CBPeripheral peripheral, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidDiscoverIncludedServicesForService(_di_CBPeripheral peripheral, _di_CBService service, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidDiscoverCharacteristicsForService(_di_CBPeripheral peripheral, _di_CBService service, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidUpdateValueForCharacteristic(_di_CBPeripheral peripheral, _di_CBCharacteristic characteristic, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidWriteValueForCharacteristic(_di_CBPeripheral peripheral, _di_CBCharacteristic characteristic, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidUpdateNotificationStateForCharacteristic(_di_CBPeripheral peripheral, _di_CBCharacteristic characteristic, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidDiscoverDescriptorsForCharacteristic(_di_CBPeripheral peripheral, _di_CBCharacteristic characteristic, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidUpdateValueForDescriptor(_di_CBPeripheral peripheral, _di_CBDescriptor descriptor, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralDidWriteValueForDescriptor(_di_CBPeripheral peripheral, _di_CBDescriptor descriptor, Iosapi::Foundation::_di_NSError error) = 0 ;
};

typedef void __fastcall (__closure *TTimerProc)(void);

enum DECLSPEC_DENUM CBPeripheralAutorizationStatus : unsigned char { CBPeripheralManagerAutorizathionStatusNotDetermined, CBPeripheralManagerAutorizathionStatusRestricted, CBPeripheralManagerAutorizathionStatusDenied, CBPeripheralManagerAutorizathionStatusAuthorized };

enum DECLSPEC_DENUM CBPeripheralManagerState : unsigned char { CBPeripheralManagerStateUnknown, CBPeripheralManagerStateResetting, CBPeripheralManagerStateUnsupported, CBPeripheralManagerStateUnauthorized, CBPeripheralManagerStatePoweredOff, CBPeripheralManagerStatePoweredOn };

enum DECLSPEC_DENUM CBPeripheralManagerConnectionLatency : unsigned char { CBPeripheralManagerConnectionLatencyLow, CBPeripheralManagerConnectionLatencyMedium, CBPeripheralManagerConnectionLatencyHigh };

enum DECLSPEC_DENUM CBATTError : unsigned char { CBATTErrorSuccess, CBATTErrorInvalidHandle, CBATTErrorReadNotPermitted, CBATTErrorWriteNotPermitted, CBATTErrorInvalidPdu, CBATTErrorInsufficientAuthentication, CBATTErrorRequestNotSupported, CBATTErrorInvalidOffset, CBATTErrorInsufficientAuthorization, CBATTErrorPrepareQueueFull, CBATTErrorAttributeNotFound, CBATTErrorAttributeNotLong, CBATTErrorInsufficientEncryptionKeySize, CBATTErrorInvalidAttributeValueLength, CBATTErrorUnlikelyError, CBATTErrorInsufficientEncryption, CBATTErrorUnsupportedGroupType, CBATTErrorInsufficientResources };

__interface  INTERFACE_UUID("{2E8DBDBB-F0E9-4796-A9E6-5AF890623465}") CBCentralClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{28941F23-99FA-4F69-B310-6035E2FA01C2}") CBCentral  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSUUID __cdecl identifier() = 0 ;
	virtual unsigned long __cdecl maximumUpdateValueLength() = 0 ;
};

class PASCALIMPLEMENTATION TCBCentralt : public Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralClass,_di_CBCentral>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralClass,_di_CBCentral> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBCentralt(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBCentralClass,_di_CBCentral>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBCentralt() { }
	
};


__interface  INTERFACE_UUID("{2B959DF5-D8E3-4768-BBC8-0B3351E96CFA}") CBATTRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B385F534-A595-4457-80E3-15B707C29527}") CBATTRequest  : public Iosapi::Foundation::NSObject 
{
	virtual _di_CBCentral __cdecl central() = 0 ;
	virtual _di_CBCharacteristic __cdecl characteristic() = 0 ;
	virtual unsigned long __cdecl offset() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl value() = 0 ;
	virtual void __cdecl setValue(Iosapi::Foundation::_di_NSData value) = 0 ;
};

class PASCALIMPLEMENTATION TCBATTRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_CBATTRequestClass,_di_CBATTRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBATTRequestClass,_di_CBATTRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBATTRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBATTRequestClass,_di_CBATTRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBATTRequest() { }
	
};


__interface  INTERFACE_UUID("{5BDDE7FC-DA35-41A5-98E6-DEEFD2332E89}") CBPeripheralManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual CBPeripheralAutorizationStatus __cdecl autorizathionStatus() = 0 ;
};

__interface  INTERFACE_UUID("{94F24B28-0AB0-4DC3-8158-D7A22CEA81D2}") CBPeripheralManager  : public Iosapi::Foundation::NSObject 
{
	virtual _di_CBPeripheralManagerDelegate __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl isAdvertising() = 0 ;
	virtual CBPeripheralManagerState __cdecl state() = 0 ;
	virtual void __cdecl addService(_di_CBMutableService service) = 0 ;
	virtual void * __cdecl initWithDelegate(void * delegate, NativeInt queue) = 0 /* overload */;
	virtual void * __cdecl initWithDelegate(void * delegate, NativeInt queue, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void __cdecl removeAllServices() = 0 ;
	virtual void __cdecl removeService(_di_CBMutableService service) = 0 ;
	virtual void __cdecl respondToRequest(_di_CBATTRequest request, CBATTError withResult) = 0 ;
	virtual void __cdecl setDesiredConnectionLatency(CBPeripheralManagerConnectionLatency latency, _di_CBCentral central) = 0 ;
	virtual void __cdecl startAdvertising(Iosapi::Foundation::_di_NSDictionary advertisementData) = 0 ;
	virtual void __cdecl stopAdvertising() = 0 ;
	virtual bool __cdecl updateValue(Iosapi::Foundation::_di_NSData value, _di_CBMutableCharacteristic forCharacteristic, Iosapi::Foundation::_di_NSArray onSubscribedCentrals) = 0 ;
};

class PASCALIMPLEMENTATION TCBPeripheralManager : public Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralManagerClass,_di_CBPeripheralManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralManagerClass,_di_CBPeripheralManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCBPeripheralManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CBPeripheralManagerClass,_di_CBPeripheralManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCBPeripheralManager() { }
	
};


__interface  INTERFACE_UUID("{B5D47032-6E56-42AC-BE69-FE5A6E735A94}") CBPeripheralManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl peripheralManagerDidUpdateState(_di_CBPeripheralManager peripheral) = 0 ;
	virtual void __cdecl peripheralManagerDidStartAdvertising(_di_CBPeripheralManager peripheral, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralManagerDidAddService(_di_CBPeripheral peripheral, _di_CBService service, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl peripheralManagerDidSubscribetoCharacteristic(_di_CBPeripheral peripheral, _di_CBCentral central, _di_CBCharacteristic characteristic) = 0 ;
	virtual void __cdecl peripheralManagerDidUnsubscribeFromCharacteristic(_di_CBPeripheralManager peripheral, _di_CBCentral central, _di_CBCharacteristic characteristic) = 0 ;
	virtual void __cdecl peripheralManagerDidReceiveReadRequests(_di_CBPeripheralManager peripheral, _di_CBATTRequest request) = 0 ;
	virtual void __cdecl peripheralManagerDidReceiveWriteRequests(_di_CBPeripheralManager peripheral, Iosapi::Foundation::_di_NSArray requests) = 0 ;
	virtual void __cdecl peripheralManagerIsReadyToUpdateSubscribers(_di_CBPeripheralManager peripheral) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CBCharacteristicPropertyBroadcast = System::Int8(0x1);
static constexpr System::Int8 CBCharacteristicPropertyRead = System::Int8(0x2);
static constexpr System::Int8 CBCharacteristicPropertyWriteWithoutResponse = System::Int8(0x4);
static constexpr System::Int8 CBCharacteristicPropertyWrite = System::Int8(0x8);
static constexpr System::Int8 CBCharacteristicPropertyNotify = System::Int8(0x10);
static constexpr System::Int8 CBCharacteristicPropertyIndicate = System::Int8(0x20);
static constexpr System::Int8 CBCharacteristicPropertyAuthenticatedSignedWrites = System::Int8(0x40);
static constexpr System::Byte CBCharacteristicPropertyExtendedProperties = System::Byte(0x80);
static constexpr System::Word CBCharacteristicPropertyNotifyEncryptionRequired = System::Word(0x100);
static constexpr System::Word CBCharacteristicPropertyIndicateEncryptionRequired = System::Word(0x200);
static constexpr System::Int8 CBAttributePermissionsReadable = System::Int8(0x1);
static constexpr System::Int8 CBAttributePermissionsWriteable = System::Int8(0x2);
static constexpr System::Int8 CBAttributePermissionsReadEncryptionRequired = System::Int8(0x4);
static constexpr System::Int8 CBAttributePermissionsWriteEncryptionRequired = System::Int8(0x8);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBCentralManagerScanOptionSolicitedServiceUUIDsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBCentralManagerScanOptionAllowDuplicatesKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataManufacturerDataKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataLocalNameKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataServiceUUIDsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataServiceDataKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataOverflowServiceUUIDsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataTxPowerLevelKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataIsConnectable(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CBAdvertisementDataSolicitedServiceUUIDsKey(void);
}	/* namespace Bluetooth */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_BLUETOOTH)
using namespace Macapi::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_BluetoothHPP
