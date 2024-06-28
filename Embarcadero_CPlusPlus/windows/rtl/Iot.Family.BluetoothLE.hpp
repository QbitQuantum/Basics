// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Iot.Family.BluetoothLE.pas' rev: 34.00 (Windows)

#ifndef Iot_Family_BluetoothleHPP
#define Iot_Family_BluetoothleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bluetooth.hpp>
#include <Iot.Family.BluetoothLE.GattTypes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iot
{
namespace Family
{
namespace Bluetoothle
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBluetoothDiscoverDevicesException;
class DELPHICLASS TBluetoothDeviceDiscoveryManager;
class DELPHICLASS TGeneratedBluetoothLEDevice;
class DELPHICLASS TCustomGeneratedBluetoothLEComponent;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBluetoothDiscoverDevicesException : public System::Bluetooth::EBluetoothException
{
	typedef System::Bluetooth::EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothDiscoverDevicesException(const System::UnicodeString Msg) : System::Bluetooth::EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothDiscoverDevicesException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Bluetooth::EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothDiscoverDevicesException(NativeUInt Ident)/* overload */ : System::Bluetooth::EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothDiscoverDevicesException(System::PResStringRec ResStringRec)/* overload */ : System::Bluetooth::EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothDiscoverDevicesException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Bluetooth::EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothDiscoverDevicesException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Bluetooth::EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothDiscoverDevicesException(const System::UnicodeString Msg, int AHelpContext) : System::Bluetooth::EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothDiscoverDevicesException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Bluetooth::EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothDiscoverDevicesException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Bluetooth::EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothDiscoverDevicesException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Bluetooth::EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothDiscoverDevicesException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Bluetooth::EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothDiscoverDevicesException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Bluetooth::EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothDiscoverDevicesException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef unsigned __int64 UnsignedInt64;

typedef System::DelphiInterface<System::Sysutils::TProc__1<Iot::Family::Bluetoothle::Gatttypes::TGattSystemID> > TGattSystemIDEvent;

typedef System::DelphiInterface<System::Sysutils::TProc__1<System::UnicodeString> > TGattStringEvent;

typedef System::Generics::Collections::TList__1<System::Bluetooth::TBluetoothLEDevice*>* TDeviceDiscoveredList;

typedef void __fastcall (__closure *TDeviceDiscoveryEvent)(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice);

typedef void __fastcall (__closure *TDeviceListDiscoveredEvent)(System::TObject* const Sender, const int ADiscoveredDeviceCount);

typedef void __fastcall (__closure *TDeviceConnectionErrorEvent)(System::TObject* const Sender, TGeneratedBluetoothLEDevice* const ADevice);

typedef void __fastcall (__closure *TGeneralDiscoveryErrorEvent)(System::TObject* const Sender, System::Sysutils::Exception* const AException, bool &Handled);

typedef void __fastcall (__closure *TComponentConnectionEvent)(TCustomGeneratedBluetoothLEComponent* const Sender);

typedef void __fastcall (__closure *TCharacteristicWriteResultEvent)(const System::Bluetooth::TBluetoothGattStatus Status);

typedef void __fastcall (__closure *TDeviceConnectedEvent)(void);

enum class DECLSPEC_DENUM TServicesLengthType : unsigned char { Undefined, S16B = 0x2, S32B = 0x4, S128B = 0x10 };

enum class DECLSPEC_DENUM TDiscoveryMethod : unsigned char { ScanResponse, ScanResponseAllDevices, Connect };

enum class DECLSPEC_DENUM TDeviceConnectionStates : unsigned char { Discovering, Connected };

typedef System::Set<TDeviceConnectionStates, _DELPHI_SET_ENUMERATOR(TDeviceConnectionStates::Discovering), _DELPHI_SET_ENUMERATOR(TDeviceConnectionStates::Connected)> TDeviceConnectionState;

class PASCALIMPLEMENTATION TBluetoothDeviceDiscoveryManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	int FTimeout;
	int FRetries;
	TDiscoveryMethod FDiscoveryMethod;
	System::Generics::Collections::TList__1<TCustomGeneratedBluetoothLEComponent*>* FRegisteredDevices;
	TGeneralDiscoveryErrorEvent FOnGeneralDiscoveryError;
	void __fastcall EndDeviceDiscovery(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDeviceList* const ADeviceList);
	void __fastcall DeviceDiscovered(System::TObject* const Sender, System::Bluetooth::TBluetoothLEDevice* const ADevice, int Rssi, System::Bluetooth::TScanResponse* const ScanResponse);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TBluetoothDeviceDiscoveryManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBluetoothDeviceDiscoveryManager();
	void __fastcall RegisterDevice(TCustomGeneratedBluetoothLEComponent* const Device);
	void __fastcall UnregisterDevice(TCustomGeneratedBluetoothLEComponent* const Device);
	void __fastcall DiscoverDevices();
	
__published:
	__property TGeneralDiscoveryErrorEvent OnGeneralDiscoveryError = {read=FOnGeneralDiscoveryError, write=FOnGeneralDiscoveryError};
	__property int DiscoveryTimeout = {read=FTimeout, write=FTimeout, default=5000};
	__property int DiscoveryRetries = {read=FRetries, write=FRetries, default=5};
	__property TDiscoveryMethod DiscoveryMethod = {read=FDiscoveryMethod, write=FDiscoveryMethod, default=0};
};


typedef void __fastcall (__closure *TBluetoothLEDeviceNotifyEvent)(TGeneratedBluetoothLEDevice* const Sender);

class PASCALIMPLEMENTATION TGeneratedBluetoothLEDevice : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Bluetooth::TBluetoothLEDevice* FDevice;
	TDeviceConnectionState FConnectionState;
	TDeviceConnectionErrorEvent FOnDeviceConnectionError;
	TBluetoothLEDeviceNotifyEvent FOnDeviceDisconnect;
	void __fastcall DeviceDisconnected(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoDiscoveryError();
	virtual void __fastcall DoOnDeviceDisconnected();
	
public:
	__fastcall TGeneratedBluetoothLEDevice(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	virtual __classmethod GUID __fastcall GetPrimaryService() = 0 ;
	System::Bluetooth::TBluetoothGattCharacteristic* __fastcall CharacteristicDiscovered(const GUID &ServiceGUID, const GUID &CharacteristicGUID);
	__property TDeviceConnectionState ConnectionState = {read=FConnectionState, nodefault};
	bool __fastcall Disconnect();
	__property System::Bluetooth::TBluetoothLEDevice* Device = {read=FDevice};
	__property TDeviceConnectionErrorEvent OnDeviceConnectionError = {read=FOnDeviceConnectionError, write=FOnDeviceConnectionError};
	__property TBluetoothLEDeviceNotifyEvent OnDeviceDisconnect = {read=FOnDeviceDisconnect, write=FOnDeviceDisconnect};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGeneratedBluetoothLEDevice() { }
	
};


class PASCALIMPLEMENTATION TCustomGeneratedBluetoothLEComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TBluetoothDeviceDiscoveryManager* FDiscoveryManager;
	TDeviceConnectionErrorEvent FOnDeviceConnectionError;
	TDeviceConnectedEvent FOnDeviceConnected;
	TDeviceDiscoveryEvent FOnDeviceDiscovered;
	TDeviceListDiscoveredEvent FOnDeviceListDiscovered;
	System::Generics::Collections::TList__1<System::Bluetooth::TBluetoothLEDevice*>* FDeviceDiscoveredList;
	TComponentConnectionEvent FOnDeviceDisconnect;
	System::UnicodeString FIdentifier;
	System::UnicodeString FDeviceName;
	void __fastcall EndServiceDiscovery(System::TObject* const Sender, System::Bluetooth::TBluetoothGattServiceList* const AServiceList);
	void __fastcall SetDiscoveryManager(TBluetoothDeviceDiscoveryManager* const Value);
	TDeviceConnectionState __fastcall GetConnectionState();
	void __fastcall AddDeviceDiscoveredToList(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	System::Bluetooth::TBluetoothLEDevice* __fastcall GetDiscoveredDevice(int Index);
	int __fastcall GetDiscoveredDeviceCount();
	
protected:
	TGeneratedBluetoothLEDevice* FDevice;
	virtual TGeneratedBluetoothLEDevice* __fastcall CreateDevice(System::Bluetooth::TBluetoothLEDevice* ADevice) = 0 ;
	virtual GUID __fastcall GetPrimaryServiceGuid() = 0 ;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall HandleDisconnectNotification(TGeneratedBluetoothLEDevice* const Sender);
	
public:
	__fastcall virtual TCustomGeneratedBluetoothLEComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomGeneratedBluetoothLEComponent();
	void __fastcall BeginDiscovery();
	void __fastcall EndDiscovery();
	bool __fastcall ConnectDevice(System::Bluetooth::TBluetoothLEDevice* const ADevice);
	bool __fastcall Disconnect();
	__property System::UnicodeString DeviceName = {read=FDeviceName, write=FDeviceName};
	__property System::UnicodeString Identifier = {read=FIdentifier, write=FIdentifier};
	__property TDeviceConnectionState ConnectionState = {read=GetConnectionState, nodefault};
	__property int DiscoveredDeviceCount = {read=GetDiscoveredDeviceCount, nodefault};
	__property System::Bluetooth::TBluetoothLEDevice* DiscoveredDevice[int Index] = {read=GetDiscoveredDevice};
	__property TDeviceConnectedEvent OnDeviceConnected = {read=FOnDeviceConnected, write=FOnDeviceConnected};
	__property TDeviceDiscoveryEvent OnDeviceDiscovered = {read=FOnDeviceDiscovered, write=FOnDeviceDiscovered};
	__property TDeviceListDiscoveredEvent OnDeviceListDiscovered = {read=FOnDeviceListDiscovered, write=FOnDeviceListDiscovered};
	__property TBluetoothDeviceDiscoveryManager* DiscoveryManager = {read=FDiscoveryManager, write=SetDiscoveryManager};
	__property TDeviceConnectionErrorEvent OnDeviceConnectionError = {read=FOnDeviceConnectionError, write=FOnDeviceConnectionError};
	__property TComponentConnectionEvent OnDeviceDisconnect = {read=FOnDeviceDisconnect, write=FOnDeviceDisconnect};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetoothle */
}	/* namespace Family */
}	/* namespace Iot */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY_BLUETOOTHLE)
using namespace Iot::Family::Bluetoothle;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY)
using namespace Iot::Family;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT)
using namespace Iot;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iot_Family_BluetoothleHPP
