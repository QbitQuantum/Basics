// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Beacon.Components.pas' rev: 34.00 (Android)

#ifndef System_Beacon_ComponentsHPP
#define System_Beacon_ComponentsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Beacon.hpp>
#include <System.Bluetooth.hpp>
#include <System.NetConsts.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Beacon
{
namespace Components
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBeaconComponentException;
class DELPHICLASS TBeaconRegionItem;
class DELPHICLASS TBeaconRegionCollection;
class DELPHICLASS TCustomBeacon;
class DELPHICLASS TBeacon;
class DELPHICLASS TCustomBeaconDevice;
class DELPHICLASS TBeaconDevice;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EBeaconComponentException : public System::Classes::EComponentError
{
	typedef System::Classes::EComponentError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBeaconComponentException(const System::UnicodeString Msg) : System::Classes::EComponentError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBeaconComponentException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Classes::EComponentError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconComponentException(NativeUInt Ident)/* overload */ : System::Classes::EComponentError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconComponentException(System::PResStringRec ResStringRec)/* overload */ : System::Classes::EComponentError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconComponentException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Classes::EComponentError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconComponentException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Classes::EComponentError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBeaconComponentException(const System::UnicodeString Msg, int AHelpContext) : System::Classes::EComponentError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBeaconComponentException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Classes::EComponentError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconComponentException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Classes::EComponentError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconComponentException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Classes::EComponentError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconComponentException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Classes::EComponentError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconComponentException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Classes::EComponentError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBeaconComponentException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBeaconRegionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	int FMinor;
	int FMajor;
	GUID FGUID;
	System::Beacon::TKindofBeacon FKindofBeacon;
	System::Beacon::TEddystoneUID FEddyUID;
	System::UnicodeString FEddyStInstance;
	int FManufacturerID;
	void __fastcall SetGUID(const GUID &AValue);
	void __fastcall SetMajor(int AValue);
	void __fastcall SetMinor(int AValue);
	void __fastcall SetUUID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetUUID();
	System::UnicodeString __fastcall GetEddyNamespace();
	void __fastcall SetEddyNamespace(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetEddyInstance();
	void __fastcall SetEddyInstance(const System::UnicodeString AValue);
	void __fastcall SetManufacturerID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetManufacturerID();
	
public:
	__fastcall virtual TBeaconRegionItem(System::Classes::TCollection* Collection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property GUID GUID = {read=FGUID, write=SetGUID};
	__property int ManufacturerIdToInt = {read=FManufacturerID, default=-1};
	
__published:
	__property System::UnicodeString UUID = {read=GetUUID, write=SetUUID};
	__property int Major = {read=FMajor, write=SetMajor, default=-1};
	__property int Minor = {read=FMinor, write=SetMinor, default=-1};
	__property System::Beacon::TKindofBeacon KindofBeacon = {read=FKindofBeacon, write=FKindofBeacon, default=3};
	__property System::UnicodeString EddyNamespace = {read=GetEddyNamespace, write=SetEddyNamespace};
	__property System::UnicodeString EddyInstance = {read=GetEddyInstance, write=SetEddyInstance};
	__property System::UnicodeString IDManufacturer = {read=GetManufacturerID, write=SetManufacturerID};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TBeaconRegionItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBeaconRegionCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TBeaconRegionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TNotifyEvent FOnChange;
	HIDESBASE TBeaconRegionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TBeaconRegionItem* const Value);
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__property TBeaconRegionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TOwnedCollection.Create */ inline __fastcall TBeaconRegionCollection(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TBeaconRegionCollection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomBeacon : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	#define TCustomBeacon_EDDY_UID_INSTANCE_ALL u"-1"
	
	
private:
	System::Beacon::TBeaconManager* FBeaconManager;
	bool FEnabled;
	System::Beacon::TBeaconEnterExitEvent FOnBeaconEnter;
	System::Beacon::TBeaconCalcDistanceEvent FOnCalcDistance;
	System::Beacon::TBeaconsCalcDistancesEvent FOnCalculateDistances;
	System::Beacon::TBeaconProximityEvent FOnBeaconProximity;
	System::Beacon::TBeaconEnterExitEvent FOnBeaconExit;
	System::Beacon::TBeaconRegionEvent FOnEnterRegion;
	System::Beacon::TBeaconsRegionEvent FOnBeaconsEnterRegion;
	TBeaconRegionCollection* FMonitorizedRegions;
	TBeaconRegionCollection* FOldMonitorizedRegions;
	System::Beacon::TBeaconRegionEvent FOnExitRegion;
	System::Beacon::TBeaconsRegionEvent FOnBeaconsExitRegion;
	System::Beacon::TParseManufacturerDataEvent FOnParseManufacturerData;
	System::Beacon::TParseServiceDataEvent FOnParseServiceData;
	System::Beacon::TNewBLEScanFilterEvent FOnNewBLEScanFilter;
	System::Beacon::TBeaconEddystoneURLEvent FOnBeaconEddystoneURL;
	System::Beacon::TBeaconEddystoneTLMEvent FOnBeaconEddystoneTLM;
	System::Beacon::TBeaconErrorEvent FOnBeaconError;
	System::TObject* FLock;
	System::Beacon::TBeaconScanMode FMode;
	System::Beacon::TKindofBeacons FKindofBeacons;
	System::Beacon::TBeaconList FCurrentList;
	int FBeaconDeathTime;
	int FScanningTime;
	int FScanningSleepingTime;
	float FSPC;
	System::Beacon::TBeaconCalcMode FCalcMode;
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetMonitorizedRegions(TBeaconRegionCollection* const Value);
	void __fastcall OnListChange(System::TObject* Sender);
	void __fastcall CheckEvents();
	void __fastcall SetMode(const System::Beacon::TBeaconScanMode Value);
	void __fastcall SetKindofBeacons(const System::Beacon::TKindofBeacons Value);
	void __fastcall DoBeaconEnter(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, const System::Beacon::TBeaconList CurrentBeaconList);
	void __fastcall DoBeaconExit(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, const System::Beacon::TBeaconList CurrentBeaconList);
	void __fastcall DoParseManufacturerData(System::TObject* const Sender, const System::Beacon::TManufacturerRawData AData, System::Beacon::TBeaconInfo &BeaconInfo, bool &Handled);
	void __fastcall DoParseServiceData(System::TObject* const Sender, const System::Bluetooth::TServiceDataRawData &AData, System::Beacon::TBeaconInfo &BeaconInfo, bool &Handled);
	void __fastcall DoNewEddystoneURL(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, const System::Beacon::TEddystoneURL &AEddystoneURL);
	void __fastcall DoNewEddystoneTLM(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, const System::Beacon::TEddystoneTLM &AEddystoneTLM);
	void __fastcall DoBeaconCalcDistance(System::TObject* const Sender, const GUID &UUID, System::Word AMajor, System::Word AMinor, int ATxPower, int ARssi, double &NewDistance)/* overload */;
	void __fastcall DoBeaconCalcDistance(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, int ATxPower, int ARssi, double &NewDistance)/* overload */;
	void __fastcall DoBeaconChangedProximity(System::TObject* const Sender, const System::Beacon::_di_IBeacon ABeacon, System::Beacon::TBeaconProximity CurrentProximity);
	void __fastcall DoRegionEnter(System::TObject* const Sender, const GUID &UUID, int AMajor, int AMinor);
	void __fastcall DoBeaconsRegionEnter(System::TObject* const Sender, const System::Beacon::TBeaconsRegion &ABeaconRegion);
	void __fastcall DoRegionExit(System::TObject* const Sender, const GUID &UUID, int AMajor, int AMinor);
	void __fastcall DoBeaconsRegionExit(System::TObject* const Sender, const System::Beacon::TBeaconsRegion &ABeaconRegion);
	void __fastcall DoNewBLEScanFilter(System::TObject* const Sender, System::Beacon::TKindofScanFilter AKindofScanFilter, System::Bluetooth::TBluetoothLEScanFilter* const ABluetoothLEScanFilter);
	void __fastcall DoBeaconError(System::TObject* const Sender, System::Beacon::TBeaconError ABeaconError, const System::UnicodeString AMsg, const System::Beacon::TBeaconInfo &ABeacon);
	void __fastcall SaveBeaconList(const System::Beacon::TBeaconList CurrentBeaconList);
	System::Beacon::TBeaconList __fastcall GetBeaconList();
	void __fastcall SetBeaconDeathTime(const int Value);
	void __fastcall SetScanningSleepingTime(const int Value);
	void __fastcall SetScanningTime(const int Value);
	void __fastcall SetSPC(const float Value);
	System::Beacon::TBeaconCalcMode __fastcall GetCalcMode();
	void __fastcall SetCalcMode(const System::Beacon::TBeaconCalcMode Value);
	
protected:
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual TCustomBeacon(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBeacon();
	void __fastcall StartScan();
	void __fastcall StopScan();
	System::Beacon::_di_IBeacon __fastcall Nearest();
	__property System::Beacon::TBeaconList BeaconList = {read=GetBeaconList};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=0};
	__property System::Beacon::TBeaconScanMode Mode = {read=FMode, write=SetMode, default=3};
	__property System::Beacon::TKindofBeacons ModeExtended = {read=FKindofBeacons, write=SetKindofBeacons, nodefault};
	__property TBeaconRegionCollection* MonitorizedRegions = {read=FMonitorizedRegions, write=SetMonitorizedRegions};
	__property int BeaconDeathTime = {read=FBeaconDeathTime, write=SetBeaconDeathTime, default=20};
	__property float SPC = {read=FSPC, write=SetSPC};
	__property int ScanningTime = {read=FScanningTime, write=SetScanningTime, default=500};
	__property int ScanningSleepingTime = {read=FScanningSleepingTime, write=SetScanningSleepingTime, default=250};
	__property System::Beacon::TBeaconCalcMode CalcMode = {read=GetCalcMode, write=SetCalcMode, default=1};
	__property System::Beacon::TBeaconEnterExitEvent OnBeaconEnter = {read=FOnBeaconEnter, write=FOnBeaconEnter};
	__property System::Beacon::TBeaconEnterExitEvent OnBeaconExit = {read=FOnBeaconExit, write=FOnBeaconExit};
	__property System::Beacon::TBeaconProximityEvent OnBeaconProximity = {read=FOnBeaconProximity, write=FOnBeaconProximity};
	__property System::Beacon::TBeaconRegionEvent OnEnterRegion = {read=FOnEnterRegion, write=FOnEnterRegion};
	__property System::Beacon::TBeaconsRegionEvent OnBeaconsEnterRegion = {read=FOnBeaconsEnterRegion, write=FOnBeaconsEnterRegion};
	__property System::Beacon::TBeaconRegionEvent OnExitRegion = {read=FOnExitRegion, write=FOnExitRegion};
	__property System::Beacon::TBeaconsRegionEvent OnBeaconsExitRegion = {read=FOnBeaconsExitRegion, write=FOnBeaconsExitRegion};
	__property System::Beacon::TBeaconCalcDistanceEvent OnCalcDistance = {read=FOnCalcDistance, write=FOnCalcDistance};
	__property System::Beacon::TBeaconsCalcDistancesEvent OnCalculateDistances = {read=FOnCalculateDistances, write=FOnCalculateDistances};
	__property System::Beacon::TParseManufacturerDataEvent OnParseManufacturerData = {read=FOnParseManufacturerData, write=FOnParseManufacturerData};
	__property System::Beacon::TParseServiceDataEvent OnParseServiceData = {read=FOnParseServiceData, write=FOnParseServiceData};
	__property System::Beacon::TNewBLEScanFilterEvent OnNewBLEScanFilter = {read=FOnNewBLEScanFilter, write=FOnNewBLEScanFilter};
	__property System::Beacon::TBeaconEddystoneURLEvent OnNewEddystoneURL = {read=FOnBeaconEddystoneURL, write=FOnBeaconEddystoneURL};
	__property System::Beacon::TBeaconEddystoneTLMEvent OnNewEddystoneTLM = {read=FOnBeaconEddystoneTLM, write=FOnBeaconEddystoneTLM};
	__property System::Beacon::TBeaconErrorEvent OnBeaconError = {read=FOnBeaconError, write=FOnBeaconError};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBeacon : public TCustomBeacon
{
	typedef TCustomBeacon inherited;
	
__published:
	__property Enabled = {default=0};
	__property Mode = {default=3};
	__property ModeExtended;
	__property MonitorizedRegions;
	__property BeaconDeathTime = {default=20};
	__property SPC = {default=0};
	__property ScanningTime = {default=500};
	__property ScanningSleepingTime = {default=250};
	__property CalcMode = {default=1};
	__property OnBeaconEnter;
	__property OnBeaconExit;
	__property OnBeaconProximity;
	__property OnEnterRegion;
	__property OnExitRegion;
	__property OnBeaconsEnterRegion;
	__property OnBeaconsExitRegion;
	__property OnCalcDistance;
	__property OnCalculateDistances;
	__property OnParseManufacturerData;
	__property OnParseServiceData;
	__property OnNewBLEScanFilter;
	__property OnNewEddystoneURL;
	__property OnNewEddystoneTLM;
	__property OnBeaconError;
public:
	/* TCustomBeacon.Create */ inline __fastcall virtual TBeacon(System::Classes::TComponent* AOwner) : TCustomBeacon(AOwner) { }
	/* TCustomBeacon.Destroy */ inline __fastcall virtual ~TBeacon() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum class DECLSPEC_DENUM TBeaconDeviceMode : unsigned char { Standard, Alternative, EddystoneUID, EddystoneURL };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomBeaconDevice : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Beacon::TBeaconAdvertiser* FBeaconAdvertiser;
	bool FEnabled;
	TBeaconDeviceMode FBeaconDeviceMode;
	System::Word FManufacturerId;
	System::Word FBeaconType;
	GUID FGUID;
	int FMinor;
	int FMajor;
	System::Int8 FTxPower;
	System::Byte FMFGReserved;
	System::UnicodeString FEddystoneNamespace;
	System::UnicodeString FEddystoneInstance;
	System::UnicodeString FEddystoneURL;
	System::Beacon::TAdvertiseDeviceFormat FDeviceType;
	System::Beacon::TNamespaceGeneratorMethod FNamespaceGenerator;
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetMID(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetMID();
	void __fastcall SetType(const TBeaconDeviceMode Value);
	TBeaconDeviceMode __fastcall GetType();
	void __fastcall SetGUID(const GUID &Value);
	void __fastcall SetMajor(const int Value);
	void __fastcall SetMinor(const int Value);
	void __fastcall SetUUID(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetUUID();
	void __fastcall SetTxPower(const System::Int8 Value);
	void __fastcall SetMFGReserved(const System::Byte Value);
	System::Byte __fastcall GetMFGReserved();
	
protected:
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual TCustomBeaconDevice(System::Classes::TComponent* AOwner);
	void __fastcall InitWithGattServer(System::Bluetooth::TBluetoothGattServer* AGattServer);
	void __fastcall StartAdvertise();
	void __fastcall StopAdvertise();
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=0};
	__property System::UnicodeString ManufacturerId = {read=GetMID, write=SetMID};
	__property TBeaconDeviceMode BeaconType = {read=GetType, write=SetType, default=0};
	__property GUID GUID = {read=FGUID, write=SetGUID};
	__property System::UnicodeString UUID = {read=GetUUID, write=SetUUID};
	__property int Major = {read=FMajor, write=SetMajor, default=0};
	__property int Minor = {read=FMinor, write=SetMinor, default=0};
	__property System::Int8 TxPower = {read=FTxPower, write=SetTxPower, default=-63};
	__property System::Byte MFGReserved = {read=GetMFGReserved, write=SetMFGReserved, default=0};
	__property System::UnicodeString EddystoneNamespace = {read=FEddystoneNamespace, write=FEddystoneNamespace};
	__property System::UnicodeString EddystoneInstance = {read=FEddystoneInstance, write=FEddystoneInstance};
	__property System::UnicodeString EddystoneURL = {read=FEddystoneURL, write=FEddystoneURL};
	__property System::Beacon::TNamespaceGeneratorMethod NamespaceGenerator = {read=FNamespaceGenerator, write=FNamespaceGenerator, default=1};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomBeaconDevice() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBeaconDevice : public TCustomBeaconDevice
{
	typedef TCustomBeaconDevice inherited;
	
__published:
	__property Enabled = {default=0};
	__property ManufacturerId = {default=0};
	__property BeaconType = {default=0};
	__property UUID = {default=0};
	__property Major = {default=0};
	__property Minor = {default=0};
	__property TxPower = {default=-63};
	__property MFGReserved = {default=0};
	__property EddystoneNamespace = {default=0};
	__property EddystoneInstance = {default=0};
	__property EddystoneURL = {default=0};
	__property NamespaceGenerator = {default=1};
public:
	/* TCustomBeaconDevice.Create */ inline __fastcall virtual TBeaconDevice(System::Classes::TComponent* AOwner) : TCustomBeaconDevice(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TBeaconDevice() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Components */
}	/* namespace Beacon */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BEACON_COMPONENTS)
using namespace System::Beacon::Components;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BEACON)
using namespace System::Beacon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Beacon_ComponentsHPP
