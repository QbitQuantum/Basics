// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Beacon.pas' rev: 34.00 (iOS)

#ifndef System_BeaconHPP
#define System_BeaconHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bluetooth.hpp>
#include <System.TimeSpan.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Beacon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBeaconException;
class DELPHICLASS EBeaconAdvertiserException;
class DELPHICLASS EBeaconManagerException;
struct TEddystoneUID;
struct TEddysUIDRegion;
struct TiBAltBeaconRegion;
struct TBeaconsRegion;
struct TEddystoneURL;
struct TEddystoneTLM;
struct TEddystoneBeaconInfo;
struct TBeaconInfo;
template<typename T> struct TMeanCalculator__1;
class DELPHICLASS TBeaconManufacturerDataParser;
class DELPHICLASS TBeaconManufacturerParsers;
__interface DELPHIINTERFACE IBeacon;
typedef System::DelphiInterface<IBeacon> _di_IBeacon;
__interface DELPHIINTERFACE IStandardBeacon;
typedef System::DelphiInterface<IStandardBeacon> _di_IStandardBeacon;
__interface DELPHIINTERFACE IiBeacon;
typedef System::DelphiInterface<IiBeacon> _di_IiBeacon;
__interface DELPHIINTERFACE IAltBeacon;
typedef System::DelphiInterface<IAltBeacon> _di_IAltBeacon;
__interface DELPHIINTERFACE IEddystoneBeacon;
typedef System::DelphiInterface<IEddystoneBeacon> _di_IEddystoneBeacon;
class DELPHICLASS TBeaconManager;
class DELPHICLASS TBeaconAdvertiser;
class DELPHICLASS TBeaconManufacturerDataHelper;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TAdvertiseDeviceFormat : unsigned char { adBeacon, adEddystoneUID, adEddystoneURL };

enum DECLSPEC_DENUM TNamespaceGeneratorMethod : unsigned char { ngNone, ngHashFQDN, ngElidedUUID };

enum DECLSPEC_DENUM TBeaconError : unsigned char { IncorrectTxPower, Indefinite };

class PASCALIMPLEMENTATION EBeaconException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBeaconException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBeaconException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBeaconException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBeaconException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBeaconException() { }
	
};


class PASCALIMPLEMENTATION EBeaconAdvertiserException : public EBeaconException
{
	typedef EBeaconException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBeaconAdvertiserException(const System::UnicodeString Msg) : EBeaconException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBeaconAdvertiserException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBeaconException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconAdvertiserException(NativeUInt Ident)/* overload */ : EBeaconException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconAdvertiserException(System::PResStringRec ResStringRec)/* overload */ : EBeaconException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconAdvertiserException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBeaconException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconAdvertiserException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBeaconException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBeaconAdvertiserException(const System::UnicodeString Msg, int AHelpContext) : EBeaconException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBeaconAdvertiserException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBeaconException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconAdvertiserException(NativeUInt Ident, int AHelpContext)/* overload */ : EBeaconException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconAdvertiserException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBeaconException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconAdvertiserException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBeaconException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconAdvertiserException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBeaconException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBeaconAdvertiserException() { }
	
};


class PASCALIMPLEMENTATION EBeaconManagerException : public EBeaconException
{
	typedef EBeaconException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBeaconManagerException(const System::UnicodeString Msg) : EBeaconException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBeaconManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBeaconException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconManagerException(NativeUInt Ident)/* overload */ : EBeaconException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBeaconManagerException(System::PResStringRec ResStringRec)/* overload */ : EBeaconException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBeaconException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBeaconManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBeaconException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBeaconManagerException(const System::UnicodeString Msg, int AHelpContext) : EBeaconException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBeaconManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBeaconException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : EBeaconException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBeaconManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBeaconException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBeaconException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBeaconManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBeaconException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBeaconManagerException() { }
	
};


enum DECLSPEC_DENUM TBeaconProximity : unsigned char { Immediate = 1, Near, Far, Away };

enum class DECLSPEC_DENUM TBeaconScanMode : unsigned char { Standard, Alternative, Eddystone, Extended };

enum DECLSPEC_DENUM TKindofBeacon : unsigned char { iBeacons, AltBeacons, Eddystones, iBAltBeacons };

enum DECLSPEC_DENUM TKindofScanFilter : unsigned char { ManufacturerData, ServiceData, Service, Name, Identifier };

typedef System::Set<TKindofBeacon, TKindofBeacon::iBeacons, TKindofBeacon::iBAltBeacons> TKindofBeacons;

enum DECLSPEC_DENUM TKindofEddystone : unsigned char { UID, URL, TLM };

typedef System::Set<TKindofEddystone, TKindofEddystone::UID, TKindofEddystone::TLM> TKindofEddystones;

enum DECLSPEC_DENUM TBeaconCalcMode : unsigned char { Raw, Stabilized };

typedef System::DynamicArray<System::Byte> TManufacturerRawData;

typedef System::StaticArray<System::Byte, 10> TNamespace;

typedef System::StaticArray<System::Byte, 6> TInstance;

struct DECLSPEC_DRECORD TEddystoneUID
{
public:
	TNamespace Namespace;
	TInstance Instance;
	System::Word RFU;
	bool __fastcall SetNamespace(const System::UnicodeString Value);
	bool __fastcall SetInstance(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetNamespace();
	System::UnicodeString __fastcall GetInstance();
	
private:
	System::UnicodeString __fastcall TBytesToHexString(const System::Byte *AValue, const int AValue_High);
	
public:
	__property System::UnicodeString NamespaceToString = {read=GetNamespace};
	__property System::UnicodeString InstanceToString = {read=GetInstance};
};


struct DECLSPEC_DRECORD TEddysUIDRegion
{
public:
	#define TEddysUIDRegion_EDDY_UID_INSTANCE_ALL u"-1"
	
	
private:
	TEddystoneUID FEddystoneUID;
	bool FAllInstances;
	TNamespace __fastcall GetNamespace();
	TInstance __fastcall GetInstance();
	System::UnicodeString __fastcall GetNamespaceST();
	System::UnicodeString __fastcall GetInstanceST();
	
public:
	void __fastcall Initialize(const TNamespace &ANamespace)/* overload */;
	void __fastcall Initialize(const TNamespace &ANamespace, const TInstance &AInstance)/* overload */;
	void __fastcall Initialize(const System::UnicodeString ANamespaceST)/* overload */;
	void __fastcall Initialize(const System::UnicodeString ANamespaceST, const System::UnicodeString AInstanceST)/* overload */;
	__property bool AllInstances = {read=FAllInstances};
	__property TNamespace Namespace = {read=GetNamespace};
	__property TInstance Instance = {read=GetInstance};
	__property System::UnicodeString NamespaceST = {read=GetNamespaceST};
	__property System::UnicodeString InstanceST = {read=GetInstanceST};
};


struct DECLSPEC_DRECORD TiBAltBeaconRegion
{
private:
	GUID FGUID;
	int FMajor;
	int FMinor;
	int FManufacturerID;
	TKindofBeacon FKindofBeacon;
	void __fastcall SetManufacturerID(int AManufacturerID);
	
public:
	void __fastcall Initialize(const GUID &AGUID, TKindofBeacon AKindofBeacon, int AManufacturerID)/* overload */;
	void __fastcall Initialize(const GUID &AGUID, int AMajor, TKindofBeacon AKindofBeacon, int AManufacturerID)/* overload */;
	void __fastcall Initialize(const GUID &AGUID, int AMajor, int AMinor, TKindofBeacon AKindofBeacon, int AManufacturerID)/* overload */;
	__property GUID GUID = {read=FGUID};
	__property int Major = {read=FMajor};
	__property int Minor = {read=FMinor};
	__property int ManufacturerID = {read=FManufacturerID};
	__property TKindofBeacon KindofBeacon = {read=FKindofBeacon};
};


struct DECLSPEC_DRECORD TBeaconsRegion
{
	
public:
	TKindofBeacon KindofBeacon;
	union
	{
		struct 
		{
			TiBAltBeaconRegion iBAltBeaconRegion;
		};
		struct 
		{
			TEddysUIDRegion EddysUIDRegion;
		};
		
	};
};


struct DECLSPEC_DRECORD TEddystoneURL
{
public:
	System::TArray__1<System::Byte> EncodedURL;
	System::UnicodeString URL;
	System::UnicodeString __fastcall URLToString();
};


struct DECLSPEC_DRECORD TEddystoneTLM
{
public:
	static constexpr System::Int8 EDDY_TLM_LEN = System::Int8(0xe);
	
	static constexpr System::Int8 EDDY_TLM_VERSION_POS = System::Int8(0x1);
	
	System::StaticArray<System::Byte, 13> EncodedTLM;
	System::Word BattVoltage;
	System::Word BeaconTemp;
	unsigned AdvPDUCount;
	unsigned TimeSincePowerOn;
	System::UnicodeString __fastcall BattVoltageToString();
	float __fastcall BeaconTempToSingle();
	System::UnicodeString __fastcall BeaconTempToString();
	System::UnicodeString __fastcall AdvPDUCountToString();
	System::Timespan::TTimeSpan __fastcall TimeSincePowerOnToTTimeSpan();
	System::UnicodeString __fastcall TimeSincePowerOnToString();
};


struct DECLSPEC_DRECORD TEddystoneBeaconInfo
{
public:
	TKindofEddystones KindofEddystones;
	TKindofEddystone LastKindofEddystone;
	TEddystoneUID EddystoneUID;
	TEddystoneURL EddystoneURL;
	TEddystoneTLM EddystoneTLM;
	System::TArray__1<System::Byte> AdditionalData;
};


struct DECLSPEC_DRECORD TBeaconInfo
{
public:
	GUID GUID;
	System::Word Major;
	System::Word Minor;
	System::Word BeaconType;
	int TxPower;
	System::Byte AdditionalData;
	TKindofBeacon KindofBeacon;
	TEddystoneBeaconInfo EddystoneBeacon;
	System::UnicodeString DeviceIdentifier;
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> struct DECLSPEC_DRECORD TMeanCalculator__1
{
	
public:
	typedef System::DynamicArray<T> _1;
	
	
private:
	int FSize;
	int FCenter;
	bool FIsEmpty;
	_1 ArrayRatio;
	int Index;
	bool IsFull;
	void __fastcall SetSize(int ASize);
	void __fastcall AddValue(T AValue);
	
public:
	__fastcall TMeanCalculator__1(const int ASize);
	void __fastcall Reset();
	double __fastcall GetAsDouble();
	int __fastcall GetAsInteger();
	double __fastcall GetMedianAsDouble();
	int __fastcall GetMedianAsInteger();
	T __fastcall GetLast();
	T __fastcall Get();
	T __fastcall AddGetValue(T AValue, bool IsMoving);
	bool __fastcall IsEmpty();
	TMeanCalculator__1() {}
};


class PASCALIMPLEMENTATION TBeaconManufacturerDataParser : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual __classmethod bool __fastcall Parse(const System::TArray__1<System::Byte> AData, TBeaconInfo &BeaconInfo) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TBeaconManufacturerDataParser() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBeaconManufacturerDataParser() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TBeaconManufacturerDataParserClass);

class PASCALIMPLEMENTATION TBeaconManufacturerParsers : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TBeaconManufacturerDataParserClass>* FParsers;
	
public:
	__fastcall TBeaconManufacturerParsers();
	__fastcall virtual ~TBeaconManufacturerParsers();
	void __fastcall RegisterParser(const TBeaconManufacturerDataParserClass AParser, const System::UnicodeString AParserIdentifier);
	void __fastcall UnRegisterParser(const System::UnicodeString AParserIdentifier);
	bool __fastcall Parse(const System::TArray__1<System::Byte> AData, TBeaconInfo &BeaconInfo);
};


__interface  INTERFACE_UUID("{9E2515C0-C3DB-494C-BECB-61B05266C615}") IBeacon  : public System::IInterface 
{
	virtual GUID __fastcall GetGUID() = 0 ;
	virtual System::Word __fastcall GetMajor() = 0 ;
	virtual System::Word __fastcall GetMinor() = 0 ;
	virtual int __fastcall GetRssi() = 0 ;
	virtual double __fastcall GetDistance() = 0 ;
	virtual TBeaconProximity __fastcall GetProximity() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall GetAdditionalData() = 0 ;
	virtual bool __fastcall IsEqualTo(const GUID &AGUID, System::Word AMajor, System::Word AMinor) = 0 /* overload */;
	virtual bool __fastcall IsEqualTo(const TNamespace &ANamespace, const TInstance &AInstance) = 0 /* overload */;
	virtual bool __fastcall IsEqualTo(const _di_IBeacon AIBeacon) = 0 /* overload */;
	virtual bool __fastcall ItsAlive() = 0 ;
	virtual TKindofBeacon __fastcall GetKindofBeacon() = 0 ;
	virtual System::UnicodeString __fastcall GetDeviceIdentifier() = 0 ;
	__property GUID GUID = {read=GetGUID};
	__property System::Word Major = {read=GetMajor};
	__property System::Word Minor = {read=GetMinor};
	__property int Rssi = {read=GetRssi};
	__property double Distance = {read=GetDistance};
	__property TBeaconProximity Proximity = {read=GetProximity};
	__property System::TArray__1<System::Byte> AdditionalData = {read=GetAdditionalData};
	__property TKindofBeacon KindofBeacon = {read=GetKindofBeacon};
	__property System::UnicodeString DeviceIdentifier = {read=GetDeviceIdentifier};
};

__interface  INTERFACE_UUID("{D0673EE7-3919-45D0-874F-40A8E939BD95}") IStandardBeacon  : public IBeacon 
{
	
};

__interface  INTERFACE_UUID("{ABB5CEC4-459D-468C-B2A3-21C5B6FCF18B}") IiBeacon  : public IStandardBeacon 
{
	
};

__interface  INTERFACE_UUID("{15F6C736-B968-4E3D-8FD3-EDED99723D09}") IAltBeacon  : public IStandardBeacon 
{
	virtual System::Byte __fastcall GetAltAdditionalData() = 0 ;
	__property System::Byte AltAdditionalData = {read=GetAltAdditionalData};
};

__interface  INTERFACE_UUID("{5E33BD48-D0C1-4C8E-B6CD-28586995981D}") IEddystoneBeacon  : public IBeacon 
{
	virtual TKindofEddystones __fastcall GetKindofEddystones() = 0 ;
	virtual TEddystoneUID __fastcall GetEddystoneUID() = 0 ;
	virtual TEddystoneURL __fastcall GetEddystoneURL() = 0 ;
	virtual TEddystoneTLM __fastcall GetEddystoneTLM() = 0 ;
	__property TKindofEddystones KindofEddystones = {read=GetKindofEddystones};
	__property TEddystoneUID EddystoneUID = {read=GetEddystoneUID};
	__property TEddystoneURL EddystoneURL = {read=GetEddystoneURL};
	__property TEddystoneTLM EddystoneTLM = {read=GetEddystoneTLM};
};

typedef System::DynamicArray<_di_IBeacon> TBeaconList;

typedef void __fastcall (__closure *TBeaconEnterExitEvent)(System::TObject* const Sender, const _di_IBeacon ABeacon, const TBeaconList CurrentBeaconList);

typedef void __fastcall (__closure *TBeaconProximityEvent)(System::TObject* const Sender, const _di_IBeacon ABeacon, TBeaconProximity Proximity);

typedef void __fastcall (__closure *TBeaconCalcDistanceEvent)(System::TObject* const Sender, const GUID &UUID, System::Word AMajor, System::Word AMinor, int ATxPower, int ARssi, double &NewDistance);

typedef void __fastcall (__closure *TBeaconsCalcDistancesEvent)(System::TObject* const Sender, const _di_IBeacon ABeacon, int ATxPower, int ARssi, double &NewDistance);

typedef void __fastcall (__closure *TBeaconRegionEvent)(System::TObject* const Sender, const GUID &UUID, int AMajor, int AMinor);

typedef void __fastcall (__closure *TBeaconsRegionEvent)(System::TObject* const Sender, const TBeaconsRegion &ABeaconRegion);

typedef void __fastcall (__closure *TBeaconEddystoneURLEvent)(System::TObject* const Sender, const _di_IBeacon ABeacon, const TEddystoneURL &AEddystoneURL);

typedef void __fastcall (__closure *TBeaconEddystoneTLMEvent)(System::TObject* const Sender, const _di_IBeacon ABeacon, const TEddystoneTLM &AEddystoneTLM);

typedef void __fastcall (__closure *TParseManufacturerDataEvent)(System::TObject* const Sender, const TManufacturerRawData AData, TBeaconInfo &BeaconInfo, bool &Handled);

typedef void __fastcall (__closure *TParseServiceDataEvent)(System::TObject* const Sender, const System::Bluetooth::TServiceDataRawData &AData, TBeaconInfo &BeaconInfo, bool &Handled);

typedef void __fastcall (__closure *TNewBLEScanFilterEvent)(System::TObject* const Sender, TKindofScanFilter AKindofScanFilter, System::Bluetooth::TBluetoothLEScanFilter* const ABluetoothLEScanFilter);

typedef void __fastcall (__closure *TBeaconErrorEvent)(System::TObject* const Sender, TBeaconError AError, const System::UnicodeString ErrorMsg, const TBeaconInfo &ABeacon);

class PASCALIMPLEMENTATION TBeaconManager : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static GUID EDDYSTONE_SERVICE_UUID;
	
protected:
	int FBeaconDeathTime;
	int FScanningTime;
	int FScanningSleepingTime;
	float FSPC;
	TBeaconCalcMode FCalcMode;
	TBeaconEnterExitEvent FOnBeaconEnter;
	TBeaconEnterExitEvent FOnBeaconExit;
	TBeaconEddystoneURLEvent FOnNewEddystoneURL;
	TBeaconEddystoneTLMEvent FOnNewEddystoneTLM;
	TBeaconProximityEvent FOnBeaconProximity;
	TBeaconCalcDistanceEvent FOnCalcDistance;
	TBeaconsCalcDistancesEvent FOnCalculateDistances;
	TParseManufacturerDataEvent FOnParseManufacturerData;
	TParseServiceDataEvent FOnParseServiceData;
	TBeaconRegionEvent FOnEnterRegion;
	TBeaconsRegionEvent FOnBeaconsEnterRegion;
	TBeaconRegionEvent FOnExitRegion;
	TBeaconsRegionEvent FOnBeaconsExitRegion;
	TNewBLEScanFilterEvent FOnNewBLEScanFilterEvent;
	TBeaconErrorEvent FOnBeaconErrorEvent;
	System::Word FBeaconType;
	TBeaconScanMode FScanMode;
	TKindofBeacons FKindofBeacons;
	TBeaconManufacturerParsers* FManufacturerDataParsers;
	virtual bool __fastcall DoRegisterBeacon(const GUID &AGUID, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff) = 0 /* overload */;
	virtual bool __fastcall DoRegisterBeacon(const GUID &AGUID, System::Word AMajor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff) = 0 /* overload */;
	virtual bool __fastcall DoRegisterBeacon(const GUID &AGUID, System::Word AMajor, System::Word AMinor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff) = 0 /* overload */;
	virtual bool __fastcall DoRegisterEddyBeacon(const TNamespace &ANamespace) = 0 /* overload */;
	virtual bool __fastcall DoRegisterEddyBeacon(const TNamespace &ANamespace, const TInstance &AInstance) = 0 /* overload */;
	virtual bool __fastcall DoUnregisterBeacon(const GUID &AGUID, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3)) = 0 /* overload */;
	virtual bool __fastcall DoUnregisterBeacon(const GUID &AGUID, System::Word AMajor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3)) = 0 /* overload */;
	virtual bool __fastcall DoUnregisterBeacon(const GUID &AGUID, System::Word AMajor, System::Word AMinor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3)) = 0 /* overload */;
	virtual bool __fastcall DoUnRegisterEddyBeacon(const TNamespace &ANamespace) = 0 /* overload */;
	virtual bool __fastcall DoUnRegisterEddyBeacon(const TNamespace &ANamespace, const TInstance &AInstance) = 0 /* overload */;
	virtual _di_IBeacon __fastcall DoNearest() = 0 ;
	virtual bool __fastcall DoStartScan() = 0 ;
	virtual bool __fastcall DoStopScan() = 0 ;
	virtual void __fastcall SetBeaconType(System::Word AValue) = 0 ;
	virtual void __fastcall SetBeaconDeathTime(int AValue) = 0 ;
	virtual void __fastcall SetScanningSleepingTime(int AValue) = 0 ;
	virtual void __fastcall SetScanningTime(int AValue) = 0 ;
	virtual void __fastcall SetSPC(float AValue) = 0 ;
	virtual TKindofBeacons __fastcall GeTKindofBeacons() = 0 ;
	virtual int __fastcall GetNumberofBeaconsRegistered() = 0 ;
	virtual void __fastcall DoSetKindofBeacons(TKindofBeacons AValue) = 0 ;
	void __fastcall SetKindofBeacons(TKindofBeacons AValue);
	void __fastcall DoBeaconEnter(const _di_IBeacon ABeacon, const TBeaconList CurrentBeaconList);
	void __fastcall DoBeaconChangedProximity(const _di_IBeacon ABeacon, TBeaconProximity CurrentProximity);
	void __fastcall DoBeaconExit(const _di_IBeacon ABeacon, const TBeaconList CurrentBeaconList);
	void __fastcall DoNewEddystoneURL(const _di_IBeacon ABeacon, const TEddystoneURL &AEddystoneURL);
	void __fastcall DoNewEddystoneTLM(const _di_IBeacon ABeacon, const TEddystoneTLM &AEddystoneTLM);
	void __fastcall DoRegionEnter(const GUID &UUID, int AMajor, int AMinor);
	void __fastcall DoBeaconsRegionEnter(const TBeaconsRegion &ABeaconRegion);
	void __fastcall DoRegionExit(const GUID &UUID, int AMajor, int AMinor);
	void __fastcall DoBeaconsRegionExit(const TBeaconsRegion &ABeaconRegion);
	bool __fastcall DoBeaconCalcDistance(const GUID &UUID, System::Word AMajor, System::Word AMinor, int ATxPower, int ARssi, double &NewDistance)/* overload */;
	bool __fastcall DoBeaconCalcDistance(const _di_IBeacon Abeacon, int ATxPower, int ARssi, double &NewDistance)/* overload */;
	void __fastcall DoParseManufacturerData(const System::TArray__1<System::Byte> AData, TBeaconInfo &BeaconInfo, bool &Handled);
	void __fastcall DoParseServiceData(const System::Bluetooth::TServiceDataRawData &AData, TBeaconInfo &BeaconInfo, bool &Handled);
	void __fastcall DoNewBLEScanFilter(TKindofScanFilter AKindofScanFilter, System::Bluetooth::TBluetoothLEScanFilter* const ABluetoothLEScanFilter);
	void __fastcall DoBeaconError(TBeaconError AError, const System::UnicodeString AMsg, const TBeaconInfo &ABeacon);
	virtual __classmethod TBeaconManager* __fastcall GetInstance(TBeaconScanMode AMode) = 0 ;
	
public:
	bool __fastcall RegisterBeacon(const GUID &AGUID, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff)/* overload */;
	bool __fastcall RegisterBeacon(const GUID &AGUID, System::Word AMajor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff)/* overload */;
	bool __fastcall RegisterBeacon(const GUID &AGUID, System::Word AMajor, System::Word AMinor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3), int AManufacturerId = 0xffffffff)/* overload */;
	bool __fastcall RegisterBeacons(const TBeaconsRegion &ABeaconRegion);
	bool __fastcall UnregisterBeacon(const GUID &AGUID, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3))/* overload */;
	bool __fastcall UnregisterBeacon(const GUID &AGUID, System::Word AMajor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3))/* overload */;
	bool __fastcall UnregisterBeacon(const GUID &AGUID, System::Word AMajor, System::Word AMinor, const TKindofBeacon AKindofBeacon = (TKindofBeacon)(0x3))/* overload */;
	bool __fastcall UnRegisterBeacons(const TBeaconsRegion &ABeaconRegion);
	_di_IBeacon __fastcall Nearest();
	bool __fastcall StartScan();
	bool __fastcall StopScan();
	__classmethod TBeaconManager* __fastcall GetBeaconManager(TBeaconScanMode AMode);
	__property TBeaconScanMode ScanMode = {read=FScanMode, nodefault};
	__property System::Word BeaconType = {read=FBeaconType, write=SetBeaconType, nodefault};
	__property TBeaconCalcMode CalcMode = {read=FCalcMode, write=FCalcMode, nodefault};
	__property int BeaconDeathTime = {read=FBeaconDeathTime, write=SetBeaconDeathTime, nodefault};
	__property float SPC = {read=FSPC, write=SetSPC};
	__property int ScanningTime = {read=FScanningTime, write=SetScanningTime, nodefault};
	__property int ScanningSleepingTime = {read=FScanningSleepingTime, write=SetScanningSleepingTime, nodefault};
	__property TBeaconManufacturerParsers* ManufacturerDataParsers = {read=FManufacturerDataParsers};
	__property TKindofBeacons KindofBeacons = {read=GeTKindofBeacons, write=SetKindofBeacons, nodefault};
	__property int NumberofBeaconsRegistered = {read=GetNumberofBeaconsRegistered, nodefault};
	__property TBeaconEnterExitEvent OnBeaconEnter = {read=FOnBeaconEnter, write=FOnBeaconEnter};
	__property TBeaconEnterExitEvent OnBeaconExit = {read=FOnBeaconExit, write=FOnBeaconExit};
	__property TBeaconEddystoneURLEvent OnNewEddystoneURL = {read=FOnNewEddystoneURL, write=FOnNewEddystoneURL};
	__property TBeaconEddystoneTLMEvent OnNewEddystoneTLM = {read=FOnNewEddystoneTLM, write=FOnNewEddystoneTLM};
	__property TBeaconProximityEvent OnBeaconProximity = {read=FOnBeaconProximity, write=FOnBeaconProximity};
	__property TBeaconRegionEvent OnEnterRegion = {read=FOnEnterRegion, write=FOnEnterRegion};
	__property TBeaconRegionEvent OnExitRegion = {read=FOnExitRegion, write=FOnExitRegion};
	__property TBeaconsRegionEvent OnBeaconsEnterRegion = {read=FOnBeaconsEnterRegion, write=FOnBeaconsEnterRegion};
	__property TBeaconsRegionEvent OnBeaconsExitRegion = {read=FOnBeaconsExitRegion, write=FOnBeaconsExitRegion};
	__property TBeaconCalcDistanceEvent OnCalcDistance = {read=FOnCalcDistance, write=FOnCalcDistance};
	__property TBeaconsCalcDistancesEvent OnCalculateDistances = {read=FOnCalculateDistances, write=FOnCalculateDistances};
	__property TParseManufacturerDataEvent OnParseManufacturerData = {read=FOnParseManufacturerData, write=FOnParseManufacturerData};
	__property TParseServiceDataEvent OnParseServiceData = {read=FOnParseServiceData, write=FOnParseServiceData};
	__property TNewBLEScanFilterEvent OnNewBLEScanFilterEvent = {read=FOnNewBLEScanFilterEvent, write=FOnNewBLEScanFilterEvent};
	__property TBeaconErrorEvent OnBeaconError = {read=FOnBeaconErrorEvent, write=FOnBeaconErrorEvent};
public:
	/* TObject.Create */ inline __fastcall TBeaconManager() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBeaconManager() { }
	
};


class PASCALIMPLEMENTATION TBeaconAdvertiser : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::StaticArray<System::UnicodeString, 4> _TBeaconAdvertiser__1;
	
	typedef System::StaticArray<System::UnicodeString, 14> _TBeaconAdvertiser__2;
	
	
public:
	static _TBeaconAdvertiser__1 EDDY_SCHEME_PREFIXES;
	static _TBeaconAdvertiser__2 EDDY_URL_EXPANSIONS;
	
private:
	GUID FGUID;
	System::Word FMajor;
	System::Word FMinor;
	System::Word FBeaconType;
	System::Int8 FTxPower;
	System::Word FManufacturerId;
	System::Byte FMFGReserved;
	System::UnicodeString FEddystoneNamespace;
	System::UnicodeString FEddystoneInstance;
	System::UnicodeString FEddystoneURL;
	TAdvertiseDeviceFormat FDeviceType;
	TNamespaceGeneratorMethod FNamespaceGenerator;
	bool FOwnsGattServer;
	
protected:
	System::Bluetooth::TBluetoothGattServer* FGattServer;
	bool FAdvertiseGattInfo;
	bool __fastcall GetIsAdvertising();
	virtual System::TArray__1<System::Byte> __fastcall GetManufacturerData() = 0 ;
	System::TArray__1<System::Byte> __fastcall GetEddystoneServiceData(TAdvertiseDeviceFormat AFrameType);
	System::TArray__1<System::Byte> __fastcall EncodeEddystoneURL(System::UnicodeString AURL);
	System::TArray__1<System::Byte> __fastcall GetEddyNamespaceBytes();
	System::TArray__1<System::Byte> __fastcall GetEddyInstanceBytes();
	bool __fastcall StartAdvertisingFrames(TAdvertiseDeviceFormat AFrameType);
	virtual __classmethod TBeaconAdvertiser* __fastcall GetInstance(System::Bluetooth::TBluetoothGattServer* const AGattServer = (System::Bluetooth::TBluetoothGattServer*)(0x0)) = 0 ;
	virtual __classmethod TBeaconAdvertiser* __fastcall GetHelperInstance() = 0 ;
	__classmethod TBeaconAdvertiser* __fastcall GetBeaconAdvertiserHelperInstance();
	
public:
	__fastcall TBeaconAdvertiser(System::Bluetooth::TBluetoothGattServer* const AGattServer, bool AHelper);
	__fastcall virtual ~TBeaconAdvertiser();
	bool __fastcall StartAdvertising();
	bool __fastcall StopAdvertising();
	__classmethod TBeaconAdvertiser* __fastcall GetBeaconAdvertiser(System::Bluetooth::TBluetoothGattServer* const AGattServer = (System::Bluetooth::TBluetoothGattServer*)(0x0));
	__property GUID GUID = {read=FGUID, write=FGUID};
	__property System::Word Major = {read=FMajor, write=FMajor, nodefault};
	__property System::Word Minor = {read=FMinor, write=FMinor, nodefault};
	__property System::Int8 TxPower = {read=FTxPower, write=FTxPower, nodefault};
	__property System::Word ManufacturerId = {read=FManufacturerId, write=FManufacturerId, nodefault};
	__property System::Word BeaconType = {read=FBeaconType, write=FBeaconType, nodefault};
	__property bool AdvertiseGattInfo = {read=FAdvertiseGattInfo, write=FAdvertiseGattInfo, nodefault};
	__property System::Byte MFGReserved = {read=FMFGReserved, write=FMFGReserved, nodefault};
	__property bool IsAdvertising = {read=GetIsAdvertising, nodefault};
	__property System::UnicodeString EddystoneNamespace = {read=FEddystoneNamespace, write=FEddystoneNamespace};
	__property System::UnicodeString EddystoneInstance = {read=FEddystoneInstance, write=FEddystoneInstance};
	__property System::UnicodeString EddystoneURL = {read=FEddystoneURL, write=FEddystoneURL};
	__property TAdvertiseDeviceFormat DeviceType = {read=FDeviceType, write=FDeviceType, nodefault};
	__property TNamespaceGeneratorMethod NamespaceGenerator = {read=FNamespaceGenerator, write=FNamespaceGenerator, nodefault};
};


class PASCALIMPLEMENTATION TBeaconManufacturerDataHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::TArray__1<System::Byte> TYPE_OF_BEACON_MASK;
	static System::TArray__1<System::Byte> GUID_MASK;
	static System::TArray__1<System::Byte> GUID_MAJOR_MASK;
	static System::TArray__1<System::Byte> GUID_MINOR_MASK;
	static System::TArray__1<System::Byte> EDDY_UID_NAMESPACE_MASK;
	static System::TArray__1<System::Byte> EDDY_UID_INSTANCE_MASK;
	static System::TArray__1<System::Byte> EDDY_FRAME_UID_MASK;
	static System::TArray__1<System::Byte> EDDY_FRAME_TLM_MASK;
	
private:
	TBeaconAdvertiser* FBeaconAdvertiser;
	System::TArray__1<System::Byte> FMDataMask;
	TBeaconScanMode FScanMode;
	int FManufacturerId;
	
protected:
	void __fastcall SetGUID(const GUID &AUUID);
	GUID __fastcall GetGUID();
	void __fastcall SetMajor(System::Word AMajor);
	System::Word __fastcall GetMajor();
	void __fastcall SetMinor(System::Word AMinor);
	System::Word __fastcall GetMinor();
	void __fastcall SetTxPower(System::Int8 ATxPower);
	System::Int8 __fastcall GetTxPower();
	void __fastcall SetManufacturerId(int AManufactureId);
	int __fastcall GetManufacturerId();
	void __fastcall SetBeaconType(TKindofBeacon ABeaconType);
	TKindofBeacon __fastcall GetBeaconType();
	void __fastcall SetMFGReserved(System::Byte AMFGReserved);
	System::Byte __fastcall GetMFGReserved();
	System::TArray__1<System::Byte> __fastcall GetToByteArray();
	System::TArray__1<System::Byte> __fastcall GetMDataMask();
	bool __fastcall DoRestartHelper();
	__property TBeaconScanMode ScanMode = {read=FScanMode, nodefault};
	
public:
	__fastcall TBeaconManufacturerDataHelper(TBeaconScanMode AScanMode);
	__fastcall virtual ~TBeaconManufacturerDataHelper();
	__property GUID GUID = {read=GetGUID, write=SetGUID};
	__property System::Word Major = {read=GetMajor, write=SetMajor, nodefault};
	__property System::Word Minor = {read=GetMinor, write=SetMinor, nodefault};
	__property System::Int8 TxPower = {read=GetTxPower, write=SetTxPower, nodefault};
	__property int ManufacturerId = {read=GetManufacturerId, write=SetManufacturerId, nodefault};
	__property TKindofBeacon BeaconType = {read=GetBeaconType, write=SetBeaconType, nodefault};
	__property System::Byte MFGReserved = {read=GetMFGReserved, write=SetMFGReserved, nodefault};
	__property System::TArray__1<System::Byte> ToByteArray = {read=GetToByteArray};
	__property System::TArray__1<System::Byte> MDataMask = {read=GetMDataMask};
	__property bool RestartHelper = {read=DoRestartHelper, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Word BEACON_ST_TYPE;
extern DELPHI_PACKAGE System::Word BEACON_AL_TYPE;
extern DELPHI_PACKAGE System::TArray__1<System::Byte> BEACON_PREFIX;
static constexpr System::Int8 APPLEINC = System::Int8(0x4c);
static constexpr System::Int8 TXPOWER_IDETERMINATED = System::Int8(-63);
static constexpr System::Int8 DEFAULT_TXPOWER = System::Int8(0x7f);
static constexpr System::Int8 DISTANCE_DECIMALS = System::Int8(-2);
static constexpr System::Int8 MAJOR_REGION_ALL = System::Int8(-1);
static constexpr System::Int8 MINOR_REGION_ALL = System::Int8(-1);
static constexpr System::Int8 KBEACONDEATHTIME = System::Int8(0x14);
#define SIGNAL_PROPAGATION_CONSTANT  (5.000000E-01)
static constexpr System::Word SCANNING_TIME = System::Word(0x1f4);
static constexpr System::Byte SCANNING_SLEEPINGTIME = System::Byte(0xfa);
static constexpr System::Int8 DIFFERENTIAL_FILTER_BOUNDARY = System::Int8(0x7);
static const double ACCUMMULATE_DIFF_START_VALUE = 3.500000E+00;
static constexpr System::Int8 BEACON_TYPE_POS = System::Int8(0x2);
static constexpr System::Int8 GUID_LENGTH = System::Int8(0x10);
static constexpr System::Int8 MARK_POSITION = System::Int8(0x9);
static constexpr System::Int8 STANDARD_DATA_LENGTH = System::Int8(0x19);
static constexpr System::Int8 ALTERNATIVE_DATA_LENGTH = System::Int8(0x1a);
static constexpr System::Int8 BEACON_MANUFACTURER_ID_POSITION = System::Int8(0x0);
#define PROXIMITY_IMMEDIATE  (5.000000E-01)
static constexpr System::Int8 PROXIMITY_NEAR = System::Int8(0x3);
static constexpr System::Int8 PROXIMITY_FAR = System::Int8(0x1e);
static constexpr System::Int8 RSSI_MEAN_ITEMS = System::Int8(0xa);
static constexpr System::Int8 MANUFATURER_ID_ALL = System::Int8(-1);
static constexpr System::Int8 EDDYSTONE_UID = System::Int8(0x0);
static constexpr System::Int8 EDDYSTONE_URL = System::Int8(0x10);
static constexpr System::Int8 EDDYSTONE_TLM = System::Int8(0x20);
static constexpr System::Int8 EDDY_FRAMETYPE_POS = System::Int8(0x0);
static constexpr System::Int8 EDDY_TX_POS = System::Int8(0x1);
static constexpr System::Int8 EDDY_URL_SCHEME_POS = System::Int8(0x2);
extern DELPHI_PACKAGE System::Byte EDDY_SIGNAL_LOSS_METER;
static constexpr System::Int8 EDDY_UID_LEN = System::Int8(0x14);
static constexpr System::Int8 EDDY_UID_NAMESPACE_POS = System::Int8(0x2);
static constexpr System::Int8 EDDY_UID_NAMESPACE_LEN = System::Int8(0xa);
static constexpr System::Int8 EDDY_UID_INSTANCE_POS = System::Int8(0xc);
static constexpr System::Int8 EDDY_UID_INSTANCE_LEN = System::Int8(0x6);
static constexpr System::Int8 EDDY_TLM_LEN = System::Int8(0xe);
static constexpr System::Int8 EDDY_TLM_VERSION_POS = System::Int8(0x1);
static constexpr System::Int8 EDDY_TLM_BATTVOLTAGE_POS = System::Int8(0x2);
static constexpr System::Int8 EDDY_TLM_BEACONTEMP_POS = System::Int8(0x4);
static constexpr System::Int8 EDDY_TLM_ADVPDUCOUNT_POS = System::Int8(0x6);
static constexpr System::Int8 EDDY_TLM_TIMESINCEPOWERON_POS = System::Int8(0xa);
static constexpr System::Int8 EDDY_RFU_DATA_POS = System::Int8(0x12);
static constexpr System::Int8 EDDY_RFU_DATA_LEN = System::Int8(0x2);
static constexpr System::Int8 EDDY_MIN_URL_LEN = System::Int8(0x3);
static constexpr System::Int8 EDDY_ENCODED_URL_LEN = System::Int8(0x11);
}	/* namespace Beacon */
}	/* namespace System */
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
#endif	// System_BeaconHPP
