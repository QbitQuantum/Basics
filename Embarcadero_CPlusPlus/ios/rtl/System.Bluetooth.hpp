// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bluetooth.pas' rev: 34.00 (iOS)

#ifndef System_BluetoothHPP
#define System_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
namespace System
{
namespace Bluetooth
{
class DELPHICLASS TBluetoothLEAdapter;
class DELPHICLASS TBluetoothLEDevice;
class DELPHICLASS TBluetoothGattService;
class DELPHICLASS TBluetoothGattCharacteristic;
class DELPHICLASS TBluetoothGattDescriptor;
class DELPHICLASS TBluetoothGattServer;
}	/* namespace Bluetooth */
}	/* namespace System */

namespace System
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBluetoothException;
class DELPHICLASS EBluetoothManagerException;
class DELPHICLASS EBluetoothAdapterException;
class DELPHICLASS EBluetoothDeviceException;
class DELPHICLASS EBluetoothServiceException;
class DELPHICLASS EBluetoothFormatException;
struct TServiceDataRawData;
class DELPHICLASS TBluetoothUUIDHelper;
class DELPHICLASS TBluetoothUUIDsList;
struct TBluetoothService;
class DELPHICLASS TBluetoothCustomAdapter;
class DELPHICLASS TBluetoothCustomDevice;
class DELPHICLASS EBluetoothLEAdapterException;
class DELPHICLASS EBluetoothLEDeviceException;
class DELPHICLASS EBluetoothLECharacteristicException;
class DELPHICLASS EBluetoothLEDescriptorException;
class DELPHICLASS EBluetoothLEServiceException;
class DELPHICLASS EBluetoothLEAdvertiseDataException;
class DELPHICLASS TBluetoothLEDeviceList;
class DELPHICLASS TBluetoothLEDeviceDictionary;
class DELPHICLASS TBluetoothLEAdapterList;
class DELPHICLASS TBluetoothGattDeviceList;
class DELPHICLASS TBluetoothGattServiceList;
class DELPHICLASS TBluetoothGattCharacteristicList;
class DELPHICLASS TBluetoothGattDescriptorList;
class DELPHICLASS TScanResponse;
class DELPHICLASS TBluetoothLEServiceData;
class DELPHICLASS TBluetoothLEAdvertiseData;
class DELPHICLASS TBluetoothLEScanFilter;
class DELPHICLASS TBluetoothLEScanFilterList;
class DELPHICLASS TBluetoothLEManager;
class DELPHICLASS TBluetoothLEAdapter;
class DELPHICLASS TBluetoothLEDevice;
class DELPHICLASS TBluetoothGattService;
class DELPHICLASS TBluetoothGattCharacteristic;
class DELPHICLASS TBluetoothGattDescriptor;
class DELPHICLASS TBluetoothGattServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EBluetoothException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothManagerException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothManagerException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothManagerException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothManagerException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothManagerException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothManagerException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothAdapterException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothAdapterException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothAdapterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothAdapterException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothAdapterException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothAdapterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothAdapterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothAdapterException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothAdapterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothAdapterException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothAdapterException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothAdapterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothAdapterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothAdapterException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothDeviceException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothDeviceException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothDeviceException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothDeviceException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothDeviceException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothDeviceException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothDeviceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothDeviceException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothServiceException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothServiceException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothServiceException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothServiceException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothServiceException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothServiceException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothServiceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothServiceException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothFormatException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothFormatException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothFormatException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothFormatException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothFormatException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothFormatException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothFormatException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothFormatException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothFormatException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothFormatException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothFormatException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothFormatException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothFormatException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothFormatException() { }
	
};


typedef System::UnicodeString TBluetoothMacAddress;

enum class DECLSPEC_DENUM TBluetoothAdapterState : unsigned char { Off, On, Discovering };

enum class DECLSPEC_DENUM TBluetoothScanMode : unsigned char { None, Connectable, Discoverable };

enum class DECLSPEC_DENUM TBluetoothConnectionState : unsigned char { Disconnected, Connected };

enum class DECLSPEC_DENUM TBluetoothType : unsigned char { Unknown, Classic, LE, Dual };

enum class DECLSPEC_DENUM TBluetoothDeviceState : unsigned char { None, Paired, Connected };

typedef GUID TBluetoothUUID;

typedef System::Word TBluetooth16bitsUUID;

struct DECLSPEC_DRECORD TServiceDataRawData
{
public:
	GUID Key;
	System::TArray__1<System::Byte> Value;
	__fastcall TServiceDataRawData(const GUID &AKey, const System::TArray__1<System::Byte> AValue)/* overload */;
	__fastcall TServiceDataRawData(const System::Generics::Collections::TPair__2<GUID,System::TArray__1<System::Byte> > &AServiceData)/* overload */;
	TServiceDataRawData() {}
};


class PASCALIMPLEMENTATION TBluetoothUUIDHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod System::Word __fastcall GetBluetooth16bitsUUID(const GUID &AUUID);
	__classmethod GUID __fastcall GetBluetoothUUID(const System::Word A16bitsUUID);
	__classmethod bool __fastcall IsBluetoothBaseUUIDBased(const GUID &AUUID);
public:
	/* TObject.Create */ inline __fastcall TBluetoothUUIDHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothUUIDHelper() { }
	
};


class PASCALIMPLEMENTATION TBluetoothUUIDsList : public System::Generics::Collections::TList__1<GUID>
{
	typedef System::Generics::Collections::TList__1<GUID> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TBluetoothUUIDsList()/* overload */ : System::Generics::Collections::TList__1<GUID>() { }
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TBluetoothUUIDsList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<GUID> > AComparer)/* overload */ : System::Generics::Collections::TList__1<GUID>(AComparer) { }
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TBluetoothUUIDsList(System::Generics::Collections::TEnumerable__1<GUID>* const Collection)/* overload */ : System::Generics::Collections::TList__1<GUID>(Collection) { }
	/* {System_Generics_Collections}TList<System_TGUID>.Destroy */ inline __fastcall virtual ~TBluetoothUUIDsList() { }
	
};


enum class DECLSPEC_DENUM TBluetoothServiceType : unsigned char { Primary, Secondary };

struct DECLSPEC_DRECORD TBluetoothService
{
public:
	System::UnicodeString Name;
	GUID UUID;
};


typedef System::UnicodeString __fastcall (__closure *TIdentifyUUIDEvent)(System::TObject* const Sender, const GUID &AUUID);

class PASCALIMPLEMENTATION TBluetoothCustomAdapter : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetAddress() = 0 ;
	virtual System::UnicodeString __fastcall GetAdapterName() = 0 ;
	virtual void __fastcall SetAdapterName(const System::UnicodeString Value) = 0 ;
	virtual TBluetoothAdapterState __fastcall GetState() = 0 ;
	
public:
	__property System::UnicodeString Address = {read=GetAddress};
	__property System::UnicodeString AdapterName = {read=GetAdapterName, write=SetAdapterName};
	__property TBluetoothAdapterState State = {read=GetState, nodefault};
public:
	/* TObject.Create */ inline __fastcall TBluetoothCustomAdapter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothCustomAdapter() { }
	
};


class PASCALIMPLEMENTATION TBluetoothCustomDevice : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetAddress() = 0 ;
	virtual System::UnicodeString __fastcall GetDeviceName() = 0 ;
	virtual TBluetoothType __fastcall GetBluetoothType() = 0 ;
	
public:
	__property System::UnicodeString Address = {read=GetAddress};
	__property System::UnicodeString DeviceName = {read=GetDeviceName};
	__property TBluetoothType BluetoothType = {read=GetBluetoothType, nodefault};
public:
	/* TObject.Create */ inline __fastcall TBluetoothCustomDevice() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothCustomDevice() { }
	
};


enum class DECLSPEC_DENUM TBluetoothProperty : unsigned char { Broadcast, ExtendedProps, Notify, Indicate, Read, Write, WriteNoResponse, SignedWrite };

typedef System::Set<TBluetoothProperty, _DELPHI_SET_ENUMERATOR(TBluetoothProperty::Broadcast), _DELPHI_SET_ENUMERATOR(TBluetoothProperty::SignedWrite)> TBluetoothPropertyFlags;

enum class DECLSPEC_DENUM TBluetoothGattStatus : unsigned short { Success, ReadNotPermitted = 2, WriteNotPermitted, InsufficientAutentication = 5, RequestNotSupported, InvalidOffset, InvalidAttributeLength = 13, InsufficientEncryption = 15, Failure = 257 };

enum class DECLSPEC_DENUM TBluetoothDescriptorKind : unsigned char { Unknown, ExtendedProperties, UserDescription, ClientConfiguration, ServerConfiguration, PresentationFormat, AggregateFormat, ValidRange, ExternalReportReference, ReportReference, EnvironmentalSensingConfiguration, EnvironmentalSensingMeasurement, EnvironmentalSensingTriggerSetting };

enum class DECLSPEC_DENUM TBluetoothGattFormatType : unsigned char { Reserved, Boolean, Unsigned2bitInteger, Unsigned4bitInteger, Unsigned8bitInteger, Unsigned12bitInteger, Unsigned16bitInteger, Unsigned24bitInteger, Unsigned32bitInteger, Unsigned48bitInteger, Unsigned64bitInteger, Unsigned128bitInteger, Signed8bitInteger, Signed12bitInteger, Signed16bitInteger, Signed24bitInteger, Signed32bitInteger, Signed48bitInteger, Signed64bitInteger, Signed128bitInteger, IEEE754_32bit_floating_point, IEEE754_64bit_floating_point, IEEE11073_16bitSFLOAT, IEEE11073_32bitFLOAT, IEEE20601Format, UTF8String, UTF16String, OpaqueStructure };

class PASCALIMPLEMENTATION EBluetoothLEAdapterException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLEAdapterException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLEAdapterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEAdapterException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEAdapterException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEAdapterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEAdapterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLEAdapterException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLEAdapterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEAdapterException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEAdapterException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEAdapterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEAdapterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLEAdapterException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothLEDeviceException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLEDeviceException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLEDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEDeviceException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEDeviceException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLEDeviceException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLEDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEDeviceException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEDeviceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLEDeviceException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothLECharacteristicException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLECharacteristicException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLECharacteristicException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLECharacteristicException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLECharacteristicException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLECharacteristicException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLECharacteristicException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLECharacteristicException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLECharacteristicException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLECharacteristicException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLECharacteristicException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLECharacteristicException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLECharacteristicException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLECharacteristicException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothLEDescriptorException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLEDescriptorException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLEDescriptorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEDescriptorException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEDescriptorException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEDescriptorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEDescriptorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLEDescriptorException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLEDescriptorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEDescriptorException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEDescriptorException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEDescriptorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEDescriptorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLEDescriptorException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothLEServiceException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLEServiceException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLEServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEServiceException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEServiceException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLEServiceException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLEServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEServiceException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEServiceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLEServiceException() { }
	
};


class PASCALIMPLEMENTATION EBluetoothLEAdvertiseDataException : public EBluetoothException
{
	typedef EBluetoothException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBluetoothLEAdvertiseDataException(const System::UnicodeString Msg) : EBluetoothException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBluetoothLEAdvertiseDataException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBluetoothException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEAdvertiseDataException(NativeUInt Ident)/* overload */ : EBluetoothException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBluetoothLEAdvertiseDataException(System::PResStringRec ResStringRec)/* overload */ : EBluetoothException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEAdvertiseDataException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBluetoothLEAdvertiseDataException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(const System::UnicodeString Msg, int AHelpContext) : EBluetoothException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBluetoothException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(NativeUInt Ident, int AHelpContext)/* overload */ : EBluetoothException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBluetoothLEAdvertiseDataException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBluetoothException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBluetoothLEAdvertiseDataException() { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEDeviceList : public System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEDevice*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList(System::Generics::Collections::TEnumerable__1<TBluetoothLEDevice*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Destroy */ inline __fastcall virtual ~TBluetoothLEDeviceList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEDevice*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceList(System::Generics::Collections::TEnumerable__1<TBluetoothLEDevice*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEDeviceDictionary : public System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>
{
	typedef System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(System::Generics::Collections::TDictionaryOwnerships Ownerships, int ACapacity)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(Ownerships, ACapacity) { }
	/* {System_Generics_Collections}TObjectDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(System::Generics::Collections::TDictionaryOwnerships Ownerships, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<System::UnicodeString> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(Ownerships, AComparer) { }
	/* {System_Generics_Collections}TObjectDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(System::Generics::Collections::TDictionaryOwnerships Ownerships, int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<System::UnicodeString> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(Ownerships, ACapacity, AComparer) { }
	
public:
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary()/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>() { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(int ACapacity)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(ACapacity) { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<System::UnicodeString> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<System::UnicodeString> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(ACapacity, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<System::UnicodeString,TBluetoothLEDevice*> >* const Collection)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(Collection) { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothLEDeviceDictionary(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<System::UnicodeString,TBluetoothLEDevice*> >* const Collection, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<System::UnicodeString> > AComparer)/* overload */ : System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBluetoothLEDevice*>(Collection, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_string,System_Bluetooth_TBluetoothLEDevice>.Destroy */ inline __fastcall virtual ~TBluetoothLEDeviceDictionary() { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEAdapterList : public System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEAdapter*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList(System::Generics::Collections::TEnumerable__1<TBluetoothLEAdapter*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEAdapter>.Destroy */ inline __fastcall virtual ~TBluetoothLEAdapterList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEAdapter*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEAdapter>.Create */ inline __fastcall TBluetoothLEAdapterList(System::Generics::Collections::TEnumerable__1<TBluetoothLEAdapter*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEAdapter*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TBluetoothGattDeviceList : public System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEDevice*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList(System::Generics::Collections::TEnumerable__1<TBluetoothLEDevice*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothLEDevice>.Destroy */ inline __fastcall virtual ~TBluetoothGattDeviceList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEDevice*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEDevice>.Create */ inline __fastcall TBluetoothGattDeviceList(System::Generics::Collections::TEnumerable__1<TBluetoothLEDevice*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothLEDevice*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TBluetoothGattServiceList : public System::Generics::Collections::TObjectList__1<TBluetoothGattService*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothGattService*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattService*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList(System::Generics::Collections::TEnumerable__1<TBluetoothGattService*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattService>.Destroy */ inline __fastcall virtual ~TBluetoothGattServiceList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattService*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattService>.Create */ inline __fastcall TBluetoothGattServiceList(System::Generics::Collections::TEnumerable__1<TBluetoothGattService*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattService*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TBluetoothGattCharacteristicList : public System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattCharacteristic*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList(System::Generics::Collections::TEnumerable__1<TBluetoothGattCharacteristic*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattCharacteristic>.Destroy */ inline __fastcall virtual ~TBluetoothGattCharacteristicList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattCharacteristic*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattCharacteristic>.Create */ inline __fastcall TBluetoothGattCharacteristicList(System::Generics::Collections::TEnumerable__1<TBluetoothGattCharacteristic*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattCharacteristic*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TBluetoothGattDescriptorList : public System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>
{
	typedef System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList()/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>() { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattDescriptor*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList(System::Generics::Collections::TEnumerable__1<TBluetoothGattDescriptor*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<System_Bluetooth_TBluetoothGattDescriptor>.Destroy */ inline __fastcall virtual ~TBluetoothGattDescriptorList() { }
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothGattDescriptor*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothGattDescriptor>.Create */ inline __fastcall TBluetoothGattDescriptorList(System::Generics::Collections::TEnumerable__1<TBluetoothGattDescriptor*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TBluetoothGattDescriptor*>(Collection) { }
	
};


enum class DECLSPEC_DENUM TScanResponseKey : unsigned char { Flags = 1, IncompleteList16SCUUID, CompleteList16SCUUID, IncompleteList32SCUUID, CompleteList32SCUUID, IncompleteList128SCUUID, CompleteList128SCUUID, ShortenedLocalName, CompleteLocalName, TxPowerLevel, ClassOfDevice = 13, SimplePairingHashC, SimplePairingRAndomizerR, DeviceID, SecurityManagerOutOfBandFlags, SlaveConnectionIntervalRange, List16bServiceSolicitationUUIDs = 20, List32bServiceSolicitationUUIDs = 31, List128bServiceSolicitationUUIDs = 21, ServiceData, ServiceData16b = 22, ServiceData32b = 32, ServiceData128b, PublicTargetAddress = 23, RandomTargetAddress, Appearance, AdvertisingInterval, LEBluetoothDeviceAddress, LERole, SimplePairingHashc256, SimplePairingRAndomizerR256, 
	_3DInformationData = 61, ManufacturerSpecificData = 255 };

class PASCALIMPLEMENTATION TScanResponse : public System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >
{
	typedef System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> > inherited;
	
public:
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse()/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >() { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse(int ACapacity)/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >(ACapacity) { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse(const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<TScanResponseKey> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >(AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse(int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<TScanResponseKey> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >(ACapacity, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<TScanResponseKey,System::TArray__1<System::Byte> > >* const Collection)/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >(Collection) { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Create */ inline __fastcall TScanResponse(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<TScanResponseKey,System::TArray__1<System::Byte> > >* const Collection, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<TScanResponseKey> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<TScanResponseKey,System::TArray__1<System::Byte> >(Collection, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_Bluetooth_TScanResponseKey,System_TArray<System_Byte>>.Destroy */ inline __fastcall virtual ~TScanResponse() { }
	
};


typedef void __fastcall (__closure *TConnectLEDeviceEvent)(System::TObject* const Sender, TBluetoothLEDevice* const ADevice);

typedef void __fastcall (__closure *TDiscoveryLEEndEvent)(System::TObject* const Sender, TBluetoothLEDeviceList* const ADeviceList);

typedef void __fastcall (__closure *TDiscoverLEDeviceEvent)(System::TObject* const Sender, TBluetoothLEDevice* const ADevice, int Rssi, TScanResponse* const ScanResponse);

typedef void __fastcall (__closure *TGattOperationResultEvent)(System::TObject* const Sender, TBluetoothGattStatus AGattStatus);

typedef void __fastcall (__closure *TDiscoverServiceEvent)(System::TObject* const Sender, TBluetoothGattService* const AService);

typedef void __fastcall (__closure *TDiscoverServicesEvent)(System::TObject* const Sender, TBluetoothGattServiceList* const AServiceList);

typedef void __fastcall (__closure *TGattCharacteristicEvent)(System::TObject* const Sender, TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus AGattStatus);

typedef void __fastcall (__closure *TGattDescriptorEvent)(System::TObject* const Sender, TBluetoothGattDescriptor* const ADescriptor, TBluetoothGattStatus AGattStatus);

typedef void __fastcall (__closure *TGattDeviceRSSIEvent)(System::TObject* const Sender, int ARssiValue, TBluetoothGattStatus AGattStatus);

typedef void __fastcall (__closure *TGattCharacteristicReadEvent)(System::TObject* const Sender, TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus &AGattStatus);

typedef void __fastcall (__closure *TGattCharacteristicWriteEvent)(System::TObject* const Sender, TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus &AGattStatus, const System::TArray__1<System::Byte> AValue);

typedef void __fastcall (__closure *TGattCharacteristicSubscriptionEvent)(System::TObject* const Sender, const System::UnicodeString AClientId, TBluetoothGattCharacteristic* const ACharacteristic);

typedef void __fastcall (__closure *TGattServiceEvent)(System::TObject* const Sender, TBluetoothGattService* const AService, const TBluetoothGattStatus AGattStatus);

class PASCALIMPLEMENTATION TBluetoothLEServiceData : public System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >
{
	typedef System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> > inherited;
	
public:
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData()/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >() { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData(int ACapacity)/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >(ACapacity) { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData(const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<GUID> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >(AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData(int ACapacity, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<GUID> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >(ACapacity, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<GUID,System::TArray__1<System::Byte> > >* const Collection)/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >(Collection) { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Create */ inline __fastcall TBluetoothLEServiceData(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<GUID,System::TArray__1<System::Byte> > >* const Collection, const System::DelphiInterface<System::Generics::Defaults::IEqualityComparer__1<GUID> > AComparer)/* overload */ : System::Generics::Collections::TDictionary__2<GUID,System::TArray__1<System::Byte> >(Collection, AComparer) { }
	/* {System_Generics_Collections}TDictionary<System_TGUID,System_TArray<System_Byte>>.Destroy */ inline __fastcall virtual ~TBluetoothLEServiceData() { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEAdvertiseData : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::UnicodeString FLocalName;
	int FTxPowerLevel;
	System::TArray__1<System::Byte> FManufacturerSpecificData;
	TBluetoothUUIDsList* FServiceUUIDs;
	TBluetoothLEServiceData* FServiceData;
	virtual System::TArray__1<GUID> __fastcall GetServiceUUIDs() = 0 ;
	virtual System::TArray__1<TServiceDataRawData> __fastcall GetServiceData() = 0 ;
	virtual void __fastcall SetLocalName(const System::UnicodeString ALocalName) = 0 ;
	virtual System::UnicodeString __fastcall GetLocalName() = 0 ;
	virtual void __fastcall SetTxPowerLevel(int ATxPowerLevel) = 0 ;
	virtual int __fastcall GetTxPowerLevel() = 0 ;
	virtual void __fastcall SetManufacturerSpecificData(const System::TArray__1<System::Byte> AManufacturerSpecificData) = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall GetManufacturerSpecificData() = 0 ;
	virtual bool __fastcall DoAddServiceUUID(const GUID &AServiceUUID) = 0 ;
	virtual void __fastcall DoClearServiceUUIDs() = 0 ;
	virtual void __fastcall DoRemoveServiceUUID(const GUID &AServiceUUID) = 0 ;
	virtual void __fastcall DoRemoveServiceData(const GUID &AServiceUUID) = 0 ;
	virtual void __fastcall DoClearServiceData() = 0 ;
	virtual bool __fastcall DoAddServiceData(const GUID &AServiceUUID, const System::TArray__1<System::Byte> AData) = 0 ;
	
public:
	__fastcall TBluetoothLEAdvertiseData();
	__fastcall virtual ~TBluetoothLEAdvertiseData();
	void __fastcall AddServiceUUID(const GUID &AServiceUUID);
	void __fastcall RemoveServiceUUID(const GUID &AServiceUUID);
	void __fastcall ClearServiceUUIDs();
	virtual bool __fastcall ContainsServiceUUID(const GUID &AServiceUUID) = 0 ;
	void __fastcall AddServiceData(const GUID &AServiceUUID, const System::TArray__1<System::Byte> AData);
	void __fastcall RemoveServiceData(const GUID &AServiceUUID);
	virtual System::TArray__1<System::Byte> __fastcall GetDataForService(const GUID &AServiceUUID) = 0 ;
	void __fastcall ClearServiceData();
	__property System::UnicodeString LocalName = {read=GetLocalName, write=SetLocalName};
	__property int TxPowerLevel = {read=GetTxPowerLevel, write=SetTxPowerLevel, nodefault};
	__property System::TArray__1<System::Byte> ManufacturerSpecificData = {read=GetManufacturerSpecificData, write=SetManufacturerSpecificData};
	__property System::TArray__1<GUID> ServiceUUIDs = {read=GetServiceUUIDs};
	__property System::TArray__1<TServiceDataRawData> ServiceData = {read=GetServiceData};
};


class PASCALIMPLEMENTATION TBluetoothLEScanFilter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FLocalName;
	System::UnicodeString FDeviceAddress;
	System::TArray__1<System::Byte> FManufacturerSpecificData;
	System::TArray__1<System::Byte> FManufacturerSpecificDataMask;
	GUID FServiceUUID;
	GUID FServiceUUIDMask;
	TServiceDataRawData FServiceData;
	System::TArray__1<System::Byte> FServiceDataMask;
	
protected:
	void __fastcall SetManufacturerSpecificData(const System::TArray__1<System::Byte> AManufacturerSpecificData);
	void __fastcall SetManufacturerSpecificDataMask(const System::TArray__1<System::Byte> AManufacturerSpecificDataMask);
	void __fastcall SetServiceData(const TServiceDataRawData &AServiceData);
	void __fastcall SetServiceDataMask(const System::TArray__1<System::Byte> AServiceDataMask);
	
public:
	__fastcall TBluetoothLEScanFilter();
	__property System::TArray__1<System::Byte> ManufacturerSpecificData = {read=FManufacturerSpecificData, write=SetManufacturerSpecificData};
	__property System::TArray__1<System::Byte> ManufacturerSpecificDataMask = {read=FManufacturerSpecificDataMask, write=SetManufacturerSpecificDataMask};
	__property GUID ServiceUUID = {read=FServiceUUID, write=FServiceUUID};
	__property GUID ServiceUUIDMask = {read=FServiceUUIDMask, write=FServiceUUIDMask};
	__property TServiceDataRawData ServiceData = {read=FServiceData, write=SetServiceData};
	__property System::TArray__1<System::Byte> ServiceDataMask = {read=FServiceDataMask, write=SetServiceDataMask};
	__property System::UnicodeString LocalName = {read=FLocalName, write=FLocalName};
	__property System::UnicodeString DeviceAddress = {read=FDeviceAddress, write=FDeviceAddress};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEScanFilter() { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEScanFilterList : public System::Generics::Collections::TList__1<TBluetoothLEScanFilter*>
{
	typedef System::Generics::Collections::TList__1<TBluetoothLEScanFilter*> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEScanFilter>.Create */ inline __fastcall TBluetoothLEScanFilterList()/* overload */ : System::Generics::Collections::TList__1<TBluetoothLEScanFilter*>() { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEScanFilter>.Create */ inline __fastcall TBluetoothLEScanFilterList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TBluetoothLEScanFilter*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TBluetoothLEScanFilter*>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEScanFilter>.Create */ inline __fastcall TBluetoothLEScanFilterList(System::Generics::Collections::TEnumerable__1<TBluetoothLEScanFilter*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TBluetoothLEScanFilter*>(Collection) { }
	/* {System_Generics_Collections}TList<System_Bluetooth_TBluetoothLEScanFilter>.Destroy */ inline __fastcall virtual ~TBluetoothLEScanFilterList() { }
	
};


class PASCALIMPLEMENTATION TBluetoothLEManager : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
protected:
	_DECLARE_METACLASS(System::TMetaClass, TBluetoothManagerClass);
	
	
private:
	static TBluetoothLEManager* FCurrentManager;
	static TBluetoothLEManager* __fastcall InternalGetBluetoothManager();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
protected:
	static TBluetoothLEDevice* __fastcall AddDeviceToList(TBluetoothLEDevice* const ADevice, TBluetoothLEDeviceList* const ADeviceList);
	static TBluetoothLEDevice* __fastcall GetDeviceInList(const System::UnicodeString AIdentifier, TBluetoothLEDeviceList* const ADeviceList);
	static void __fastcall ClearDevicesFromList(TBluetoothLEDeviceList* const ADeviceList);
	static void __fastcall ResetDevicesFromList(TBluetoothLEDeviceList* const ADeviceList);
	static System::UnicodeString __fastcall GetKnownServiceName(const GUID &AServiceUUID);
	static TBluetoothManagerClass FBluetoothManagerClass;
	static TIdentifyUUIDEvent FOnIdentifyCustomUUID;
	
private:
	TBluetoothLEAdapter* __fastcall GetCurrentLEAdapter();
	
protected:
	TDiscoveryLEEndEvent FOnDiscoveryLEEnd;
	TDiscoverLEDeviceEvent FOnDiscoverLEDevice;
	TBluetoothLEDeviceList* FAllDiscoveredLEDevices;
	TBluetoothLEDeviceList* FLastDiscoveredLEDevices;
	System::TDateTime FLastDiscoveredLETimeStamp;
	TBluetoothUUIDsList* FFilterUUIDList;
	bool FServicesFilterScan;
	bool FForceRefreshCachedDevices;
	virtual TBluetoothConnectionState __fastcall GetConnectionState() = 0 ;
	virtual TBluetoothLEAdapter* __fastcall DoGetLEAdapter _DEPRECATED_ATTRIBUTE1("Use DoGetAdapter") ();
	virtual TBluetoothLEAdapter* __fastcall DoGetAdapter() = 0 ;
	virtual TBluetoothGattServer* __fastcall DoGetGattServer() = 0 ;
	virtual void __fastcall DoDiscoveryLEEnd _DEPRECATED_ATTRIBUTE1("Use DoDiscoveryEnd") (System::TObject* const Sender, TBluetoothLEDeviceList* const ADeviceList);
	virtual void __fastcall DoDiscoveryEnd(System::TObject* const Sender, TBluetoothLEDeviceList* const ADeviceList);
	virtual void __fastcall DoDiscoverDevice(System::TObject* const Sender, TBluetoothLEDevice* const ADevice, int Rssi, TScanResponse* const ScanResponse);
	virtual __classmethod TBluetoothLEManager* __fastcall GetBluetoothManager() = 0 ;
	virtual bool __fastcall DoGetSupportsGattClient() = 0 ;
	virtual bool __fastcall DoGetSupportsGattServer() = 0 ;
	virtual bool __fastcall DoEnableBluetooth() = 0 ;
	
public:
	__fastcall TBluetoothLEManager();
	__fastcall virtual ~TBluetoothLEManager();
	bool __fastcall StartDiscovery(unsigned Timeout, TBluetoothUUIDsList* const AFilterUUIDList = (TBluetoothUUIDsList*)(0x0), bool ForceConnect = false)/* overload */;
	bool __fastcall StartDiscovery(unsigned Timeout, TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList)/* overload */;
	bool __fastcall StartDiscoveryRaw(TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList = (TBluetoothLEScanFilterList*)(0x0), bool Refresh = true);
	void __fastcall CancelDiscovery();
	double __fastcall RssiToDistance(int ARssi, int ATxPower, float ASignalPropagationConst);
	TBluetoothGattServer* __fastcall GetGattServer();
	bool __fastcall GetSupportsGattClient();
	bool __fastcall GetSupportsGattServer();
	__property bool SupportsGattClient = {read=GetSupportsGattClient, nodefault};
	__property bool SupportsGattServer = {read=GetSupportsGattServer, nodefault};
	__property TBluetoothConnectionState ConnectionState = {read=GetConnectionState, nodefault};
	__property TBluetoothLEAdapter* CurrentAdapter = {read=GetCurrentLEAdapter};
	__property TBluetoothLEDeviceList* AllDiscoveredDevices = {read=FAllDiscoveredLEDevices};
	__property TBluetoothLEDeviceList* LastDiscoveredDevices = {read=FLastDiscoveredLEDevices};
	__property System::TDateTime LastDiscoveredTimeStamp = {read=FLastDiscoveredLETimeStamp};
	__property bool EnableBluetooth = {read=DoEnableBluetooth, nodefault};
	__property TDiscoveryLEEndEvent OnDiscoveryEnd = {read=FOnDiscoveryLEEnd, write=FOnDiscoveryLEEnd};
	__property TDiscoverLEDeviceEvent OnDiscoverLEDevice = {read=FOnDiscoverLEDevice, write=FOnDiscoverLEDevice};
	__property bool ForceRefreshCachedDevices = {read=FForceRefreshCachedDevices, write=FForceRefreshCachedDevices, nodefault};
	__classmethod TBluetoothLEManager* __fastcall CreateInstance();
	/* static */ __property TBluetoothLEManager* Current = {read=InternalGetBluetoothManager};
	/* static */ __property TIdentifyUUIDEvent OnIdentifyCustomUUID = {read=FOnIdentifyCustomUUID, write=FOnIdentifyCustomUUID};
};


class PASCALIMPLEMENTATION TBluetoothLEAdapter : public TBluetoothCustomAdapter
{
	typedef TBluetoothCustomAdapter inherited;
	
protected:
	TBluetoothLEManager* FManager;
	virtual TBluetoothScanMode __fastcall GetScanMode() = 0 ;
	virtual bool __fastcall DoStartDiscovery(unsigned Timeout, TBluetoothUUIDsList* const AFilterUUIDList = (TBluetoothUUIDsList*)(0x0), TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList = (TBluetoothLEScanFilterList*)(0x0)) = 0 ;
	virtual bool __fastcall DoStartDiscoveryRaw(TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList = (TBluetoothLEScanFilterList*)(0x0), bool Refresh = true) = 0 ;
	virtual void __fastcall DoCancelDiscovery() = 0 ;
	virtual void __fastcall DoDiscoveryEnd(System::TObject* const Sender, TBluetoothLEDeviceList* const ADeviceList);
	virtual void __fastcall DoDeviceDiscovered(TBluetoothLEDevice* const ADevice, bool ANewDevice, TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList);
	virtual void __fastcall DoDiscoverDevice(System::TObject* const Sender, TBluetoothLEDevice* const ADevice, int Rssi, TScanResponse* const ScanResponse);
	bool __fastcall StartDiscovery(unsigned Timeout, TBluetoothUUIDsList* const AFilterUUIDList = (TBluetoothUUIDsList*)(0x0), bool ForceConnect = false, TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList = (TBluetoothLEScanFilterList*)(0x0));
	bool __fastcall StartDiscoveryRaw(TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList = (TBluetoothLEScanFilterList*)(0x0), bool Refresh = true);
	void __fastcall CancelDiscovery();
	bool __fastcall DoDeviceOvercomesFilters(TBluetoothLEDevice* const ADevice, TBluetoothLEScanFilterList* const ABluetoothLEScanFilterList);
	
public:
	__fastcall TBluetoothLEAdapter(TBluetoothLEManager* const AManager);
	__fastcall virtual ~TBluetoothLEAdapter();
	__property TBluetoothScanMode ScanMode = {read=GetScanMode, nodefault};
};


class PASCALIMPLEMENTATION TBluetoothLEDevice : public TBluetoothCustomDevice
{
	typedef TBluetoothCustomDevice inherited;
	
private:
	TGattCharacteristicEvent FOnCharacteristicRead;
	TGattDescriptorEvent FOnDescriptorRead;
	TGattCharacteristicEvent FOnCharacteristicWrite;
	TGattDescriptorEvent FOnDescriptorWrite;
	TDiscoverServicesEvent FOnServicesDiscovered;
	TGattDeviceRSSIEvent FOnReadRSSI;
	TGattOperationResultEvent FOnReliableWriteCompleted;
	System::Classes::TNotifyEvent FOnConnect;
	System::Classes::TNotifyEvent FOnDisconnect;
	bool FUpdateOnReconnect;
	
protected:
	bool FAutoConnect;
	TBluetoothGattServiceList* FServices;
	TScanResponse* FAdvertisedData;
	TBluetoothLEAdvertiseData* FScannedAdvertiseData;
	int FLastRSSI;
	bool FForceRefreshCachedServices;
	bool FScanned;
	bool FPaired;
	virtual TBluetoothLEAdvertiseData* __fastcall DoCreateAdvertiseData() = 0 ;
	virtual void __fastcall DoAbortReliableWrite() = 0 ;
	virtual bool __fastcall DoBeginReliableWrite() = 0 ;
	virtual bool __fastcall DoExecuteReliableWrite() = 0 ;
	virtual bool __fastcall DoDiscoverServices() = 0 ;
	virtual void __fastcall DoOnServicesDiscovered(System::TObject* const Sender, TBluetoothGattServiceList* const AServiceList);
	virtual bool __fastcall DoReadCharacteristic(TBluetoothGattCharacteristic* const ACharacteristic) = 0 ;
	virtual bool __fastcall DoReadDescriptor(TBluetoothGattDescriptor* const ADescriptor) = 0 ;
	virtual bool __fastcall DoWriteCharacteristic(TBluetoothGattCharacteristic* const ACharacteristic) = 0 ;
	virtual bool __fastcall DoWriteDescriptor(TBluetoothGattDescriptor* const ADescriptor) = 0 ;
	virtual bool __fastcall DoReadRemoteRSSI() = 0 ;
	virtual bool __fastcall DoSetCharacteristicNotification(TBluetoothGattCharacteristic* const ACharacteristic, bool Enable) = 0 ;
	virtual System::UnicodeString __fastcall GetIdentifier() = 0 ;
	virtual bool __fastcall GetIsConnected() = 0 ;
	virtual bool __fastcall DoDisconnect() = 0 ;
	virtual bool __fastcall DoConnect() = 0 ;
	virtual void __fastcall DoOnCharacteristicRead(TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoOnDescriptorRead(TBluetoothGattDescriptor* const ADescriptor, TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoOnCharacteristicWrite(TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoOnDescriptorWrite(TBluetoothGattDescriptor* const ADescriptor, TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoOnReadRssi(System::TObject* const Sender, int ARssiValue, TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoOnReliableWriteCompleted(TBluetoothGattStatus AStatus);
	
public:
	__fastcall TBluetoothLEDevice(bool AutoConnect);
	__fastcall virtual ~TBluetoothLEDevice();
	__property TBluetoothGattServiceList* Services = {read=FServices};
	void __fastcall AbortReliableWrite();
	bool __fastcall BeginReliableWrite();
	bool __fastcall ExecuteReliableWrite();
	__property TGattOperationResultEvent OnReliableWriteCompleted = {read=FOnReliableWriteCompleted, write=FOnReliableWriteCompleted};
	bool __fastcall DiscoverServices();
	__property TDiscoverServicesEvent OnServicesDiscovered = {read=FOnServicesDiscovered, write=FOnServicesDiscovered};
	TBluetoothGattService* __fastcall GetService(const GUID &AServiceID);
	System::UnicodeString __fastcall GetDescription(TBluetoothGattCharacteristic* const ACharacteristic);
	bool __fastcall ReadRemoteRSSI();
	__property TGattDeviceRSSIEvent OnReadRSSI = {read=FOnReadRSSI, write=FOnReadRSSI};
	bool __fastcall SetCharacteristicNotification(TBluetoothGattCharacteristic* const ACharacteristic, bool Enable);
	bool __fastcall ReadCharacteristic(TBluetoothGattCharacteristic* const ACharacteristic);
	__property TGattCharacteristicEvent OnCharacteristicRead = {read=FOnCharacteristicRead, write=FOnCharacteristicRead};
	bool __fastcall WriteCharacteristic(TBluetoothGattCharacteristic* const ACharacteristic);
	__property TGattCharacteristicEvent OnCharacteristicWrite = {read=FOnCharacteristicWrite, write=FOnCharacteristicWrite};
	bool __fastcall ReadDescriptor(TBluetoothGattDescriptor* const ADescriptor);
	__property TGattDescriptorEvent OnDescriptorRead = {read=FOnDescriptorRead, write=FOnDescriptorRead};
	bool __fastcall WriteDescriptor(TBluetoothGattDescriptor* const ADescriptor);
	__property TGattDescriptorEvent OnDescriptorWrite = {read=FOnDescriptorWrite, write=FOnDescriptorWrite};
	System::UnicodeString __fastcall Identifier();
	__property TScanResponse* AdvertisedData = {read=FAdvertisedData};
	__property TBluetoothLEAdvertiseData* ScannedAdvertiseData = {read=FScannedAdvertiseData, write=FScannedAdvertiseData};
	bool __fastcall IsConnected();
	bool __fastcall Connect();
	bool __fastcall Disconnect();
	__property int LastRSSI = {read=FLastRSSI, nodefault};
	__property bool ForceRefreshCachedServices = {read=FForceRefreshCachedServices, write=FForceRefreshCachedServices, nodefault};
	__property System::Classes::TNotifyEvent OnConnect = {read=FOnConnect, write=FOnConnect};
	__property System::Classes::TNotifyEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property bool UpdateOnReconnect = {read=FUpdateOnReconnect, write=FUpdateOnReconnect, nodefault};
	__property bool Scanned = {read=FScanned, nodefault};
	__property bool Paired = {read=FPaired, nodefault};
};


class PASCALIMPLEMENTATION TBluetoothGattService : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TBluetoothGattCharacteristicList* __fastcall GetCharacteristics();
	TBluetoothGattServiceList* __fastcall GetIncludedServices();
	
protected:
	TBluetoothGattCharacteristicList* FCharacteristics;
	TBluetoothGattServiceList* FIncludedServices;
	virtual TBluetoothServiceType __fastcall GetServiceType() = 0 ;
	virtual GUID __fastcall GetServiceUUID() = 0 ;
	virtual System::UnicodeString __fastcall GetServiceUUIDName();
	virtual TBluetoothGattCharacteristicList* __fastcall DoGetCharacteristics() = 0 ;
	virtual TBluetoothGattServiceList* __fastcall DoGetIncludedServices() = 0 ;
	virtual TBluetoothGattService* __fastcall DoCreateIncludedService(const GUID &AnUUID, TBluetoothServiceType AType) = 0 ;
	virtual TBluetoothGattCharacteristic* __fastcall DoCreateCharacteristic(const GUID &AUuid, TBluetoothPropertyFlags APropertyFlags, const System::UnicodeString ADescription) = 0 ;
	virtual bool __fastcall DoAddIncludedService(TBluetoothGattService* const AService) = 0 ;
	virtual bool __fastcall DoAddCharacteristic(TBluetoothGattCharacteristic* const ACharacteristic) = 0 ;
	
public:
	TBluetoothGattService* __fastcall CreateIncludedService(const GUID &AnUUID, TBluetoothServiceType AType);
	TBluetoothGattCharacteristic* __fastcall CreateCharacteristic(const GUID &AUuid, TBluetoothPropertyFlags APropertyFlags, const System::UnicodeString ADescription);
	__fastcall TBluetoothGattService(const GUID &AnUUID, TBluetoothServiceType AType);
	__fastcall virtual ~TBluetoothGattService();
	TBluetoothGattCharacteristic* __fastcall GetCharacteristic(const GUID &AUUID);
	__property GUID UUID = {read=GetServiceUUID};
	__property System::UnicodeString UUIDName = {read=GetServiceUUIDName};
	__property TBluetoothServiceType ServiceType = {read=GetServiceType, nodefault};
	__property TBluetoothGattCharacteristicList* Characteristics = {read=GetCharacteristics};
	__property TBluetoothGattServiceList* IncludedServices = {read=GetIncludedServices};
};


class PASCALIMPLEMENTATION TBluetoothGattCharacteristic : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString __fastcall GetUUIDName();
	TBluetoothGattDescriptorList* __fastcall GetDescriptors();
	
protected:
	TBluetoothGattService* FService;
	TBluetoothGattDescriptorList* FDescriptors;
	virtual GUID __fastcall GetUUID() = 0 ;
	virtual TBluetoothPropertyFlags __fastcall GetProperties() = 0 ;
	virtual bool __fastcall DoAddDescriptor(TBluetoothGattDescriptor* const ADescriptor) = 0 ;
	virtual TBluetoothGattDescriptorList* __fastcall DoGetDescriptors() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall DoGetValue() = 0 ;
	virtual void __fastcall DoSetValue(const System::TArray__1<System::Byte> AValue) = 0 ;
	bool __fastcall AddDescriptor(TBluetoothGattDescriptor* const ADescriptor);
	virtual TBluetoothGattDescriptor* __fastcall DoCreateDescriptor(const GUID &AUUID) = 0 ;
	TBluetoothGattDescriptor* __fastcall CreateDescriptor(const GUID &AUUID);
	
public:
	__fastcall TBluetoothGattCharacteristic(TBluetoothGattService* const AService)/* overload */;
	__fastcall TBluetoothGattCharacteristic(const GUID &AUuid, TBluetoothPropertyFlags APropertyFlags)/* overload */;
	__fastcall virtual ~TBluetoothGattCharacteristic();
	TBluetoothGattService* __fastcall GetService();
	TBluetoothGattDescriptor* __fastcall GetDescriptor(const GUID &AUuid);
	System::TArray__1<System::Byte> __fastcall GetValue();
	void __fastcall SetValue(const System::TArray__1<System::Byte> AValue);
	template<typename T> T __fastcall GetValueAs(int Offset = 0x0);
	template<typename T> void __fastcall SetValueAs(T AValue, int Offset = 0x0);
	System::Int8 __fastcall GetValueAsInt8(int Offset = 0x0);
	short __fastcall GetValueAsInt16(int Offset = 0x0);
	int __fastcall GetValueAsInt32(int Offset = 0x0);
	__int64 __fastcall GetValueAsInt64(int Offset = 0x0);
	System::Byte __fastcall GetValueAsUInt8(int Offset = 0x0);
	System::Word __fastcall GetValueAsUInt16(int Offset = 0x0);
	unsigned __fastcall GetValueAsUInt32(int Offset = 0x0);
	unsigned __int64 __fastcall GetValueAsUInt64(int Offset = 0x0);
	double __fastcall GetValueAsDouble(int Offset = 0x0);
	void __fastcall SetValueAsInt8(System::Int8 AValue, int Offset = 0x0);
	void __fastcall SetValueAsInt16(short AValue, int Offset = 0x0);
	void __fastcall SetValueAsInt32(int AValue, int Offset = 0x0);
	void __fastcall SetValueAsInt64(__int64 AValue, int Offset = 0x0);
	void __fastcall SetValueAsUInt8(System::Byte AValue, int Offset = 0x0);
	void __fastcall SetValueAsUInt16(System::Word AValue, int Offset = 0x0);
	void __fastcall SetValueAsUInt32(unsigned AValue, int Offset = 0x0);
	void __fastcall SetValueAsUInt64(unsigned __int64 AValue, int Offset = 0x0);
	void __fastcall SetValueAsDouble(double AValue, int Offset = 0x0);
	int __fastcall GetValueAsInteger(int Offset = 0x0, TBluetoothGattFormatType AFormatType = (TBluetoothGattFormatType)(0x10));
	float __fastcall GetValueAsSingle(int Offset = 0x0, TBluetoothGattFormatType AFormatType = (TBluetoothGattFormatType)(0x14));
	System::UnicodeString __fastcall GetValueAsString(int Offset = 0x0, bool IsUTF8 = true);
	void __fastcall SetValueAsInteger(int AValue, int Offset = 0x0, TBluetoothGattFormatType AFormatType = (TBluetoothGattFormatType)(0x10));
	void __fastcall SetValueAsSingle(float AValue, int Offset = 0x0, TBluetoothGattFormatType AFormatType = (TBluetoothGattFormatType)(0x14));
	void __fastcall SetValueAsString(const System::UnicodeString AValue, bool IsUTF8 = true);
	__property GUID UUID = {read=GetUUID};
	__property System::UnicodeString UUIDName = {read=GetUUIDName};
	__property TBluetoothPropertyFlags Properties = {read=GetProperties, nodefault};
	__property TBluetoothGattDescriptorList* Descriptors = {read=GetDescriptors};
	__property System::TArray__1<System::Byte> Value = {read=GetValue, write=SetValue};
};


class PASCALIMPLEMENTATION TBluetoothGattDescriptor : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString __fastcall GetUUIDName();
	TBluetoothDescriptorKind __fastcall GetDescriptorKind();
	void __fastcall SetNotification(const bool AValue);
	bool __fastcall GetNotification();
	bool __fastcall GetIndication();
	void __fastcall SetIndication(const bool AValue);
	bool __fastcall GetReliableWrite();
	bool __fastcall GetWritableAuxiliaries();
	System::UnicodeString __fastcall GetUserDescription();
	void __fastcall SetUserDescription(const System::UnicodeString AValue);
	bool __fastcall GetBroadcasts();
	void __fastcall SetBroadcasts(const bool AValue);
	TBluetoothGattFormatType __fastcall GetFormat();
	System::Int8 __fastcall GetExponent();
	GUID __fastcall GetFormatUnit();
	
protected:
	TBluetoothGattCharacteristic* FCharacteristic;
	virtual System::TArray__1<System::Byte> __fastcall DoGetValue() = 0 ;
	virtual void __fastcall DoSetValue(const System::TArray__1<System::Byte> AValue) = 0 ;
	virtual GUID __fastcall GetUUID() = 0 ;
	virtual bool __fastcall DoGetReliableWrite() = 0 ;
	virtual bool __fastcall DoGetWritableAuxiliaries() = 0 ;
	virtual System::UnicodeString __fastcall DoGetUserDescription() = 0 ;
	virtual void __fastcall DoSetUserDescription(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall DoSetNotification(const bool AValue) = 0 ;
	virtual bool __fastcall DoGetNotification() = 0 ;
	virtual void __fastcall DoSetIndication(const bool AValue) = 0 ;
	virtual bool __fastcall DoGetIndication() = 0 ;
	virtual bool __fastcall DoGetBroadcasts() = 0 ;
	virtual void __fastcall DoSetBroadcasts(const bool AValue) = 0 ;
	virtual TBluetoothGattFormatType __fastcall DoGetFormat() = 0 ;
	virtual System::Int8 __fastcall DoGetExponent() = 0 ;
	virtual GUID __fastcall DoGetFormatUnit() = 0 ;
	
public:
	__fastcall TBluetoothGattDescriptor(TBluetoothGattCharacteristic* const ACharacteristic)/* overload */;
	__fastcall TBluetoothGattDescriptor(TBluetoothGattCharacteristic* const ACharacteristic, const GUID &AUUID)/* overload */;
	__fastcall virtual ~TBluetoothGattDescriptor();
	__classmethod System::UnicodeString __fastcall GetKnownUnitName(const GUID &AnUnit);
	System::TArray__1<System::Byte> __fastcall GetValue();
	void __fastcall SetValue(const System::TArray__1<System::Byte> AValue);
	__property GUID UUID = {read=GetUUID};
	__property System::UnicodeString UUIDName = {read=GetUUIDName};
	__property TBluetoothDescriptorKind Kind = {read=GetDescriptorKind, nodefault};
	TBluetoothGattCharacteristic* __fastcall GetCharacteristic();
	__property bool ReliableWrite = {read=GetReliableWrite, nodefault};
	__property bool WritableAuxiliaries = {read=GetWritableAuxiliaries, nodefault};
	__property System::UnicodeString UserDescription = {read=GetUserDescription, write=SetUserDescription};
	__property bool Notification = {read=GetNotification, write=SetNotification, nodefault};
	__property bool Indication = {read=GetIndication, write=SetIndication, nodefault};
	__property bool Broadcasts = {read=GetBroadcasts, write=SetBroadcasts, nodefault};
	__property TBluetoothGattFormatType Format = {read=GetFormat, nodefault};
	__property System::Int8 Exponent = {read=GetExponent, nodefault};
	__property GUID FormatUnit = {read=GetFormatUnit};
	__property System::TArray__1<System::Byte> Value = {read=GetValue, write=SetValue};
};


class PASCALIMPLEMENTATION TBluetoothGattServer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TConnectLEDeviceEvent FOnConnectedDevice;
	TConnectLEDeviceEvent FOnDisconnectDevice;
	TGattCharacteristicReadEvent FOnCharacteristicRead;
	TGattCharacteristicWriteEvent FOnCharacteristicWrite;
	TGattServiceEvent FOnGattServiceAdded;
	TGattCharacteristicSubscriptionEvent FOnClientSubscribed;
	TGattCharacteristicSubscriptionEvent FOnClientUnsubscribed;
	System::UnicodeString FGattServerName;
	bool FAdvertiseService;
	TBluetoothLEAdvertiseData* FAdvertiseData;
	
protected:
	TBluetoothLEManager* FManager;
	TBluetoothGattServiceList* FServices;
	virtual TBluetoothGattService* __fastcall DoCreateService(const GUID &AnUUID, TBluetoothServiceType AType) = 0 ;
	virtual TBluetoothGattService* __fastcall DoCreateIncludedService(TBluetoothGattService* const AService, const GUID &AnUUID, TBluetoothServiceType AType) = 0 ;
	virtual TBluetoothGattCharacteristic* __fastcall DoCreateCharacteristic(TBluetoothGattService* const AService, const GUID &AnUUID, const TBluetoothPropertyFlags AProps, const System::UnicodeString ADescription = System::UnicodeString()) = 0 ;
	virtual TBluetoothGattDescriptor* __fastcall DoCreateDescriptor(TBluetoothGattCharacteristic* const ACharacteristic, const GUID &AnUUID) = 0 ;
	virtual TBluetoothLEAdvertiseData* __fastcall DoCreateAdvertiseData() = 0 ;
	virtual bool __fastcall DoAddService(TBluetoothGattService* const AService) = 0 ;
	virtual bool __fastcall DoAddCharacteristic(TBluetoothGattService* const AService, TBluetoothGattCharacteristic* const ACharacteristic) = 0 ;
	virtual TBluetoothGattServiceList* __fastcall DoGetServices() = 0 ;
	virtual void __fastcall DoClose() = 0 ;
	virtual void __fastcall DoClearServices() = 0 ;
	virtual void __fastcall DoOnConnectedDevice(System::TObject* const Sender, TBluetoothLEDevice* const ADevice);
	virtual void __fastcall DoOnDisconnectDevice(System::TObject* const Sender, TBluetoothLEDevice* const ADevice);
	virtual void __fastcall DoOnServiceAdded(System::TObject* const Sender, TBluetoothGattService* const AService, const TBluetoothGattStatus AGattStatus);
	virtual void __fastcall DoCharacteristicReadRequest(TBluetoothLEDevice* const ADevice, int ARequestId, int AnOffset, TBluetoothGattCharacteristic* const AGattCharacteristic) = 0 ;
	virtual void __fastcall DoCharacteristicWriteRequest(TBluetoothLEDevice* const ADevice, int ARequestId, TBluetoothGattCharacteristic* const AGattCharacteristic, bool APreparedWrite, bool AResponseNeeded, int AnOffset, const System::TArray__1<System::Byte> AValue) = 0 ;
	virtual void __fastcall DoUpdateCharacteristicValue(TBluetoothGattCharacteristic* const ACharacteristic) = 0 ;
	virtual void __fastcall DoServiceAdded(TBluetoothGattStatus AStatus, TBluetoothGattService* const AService) = 0 ;
	void __fastcall DoOnCharacteristicRead(System::TObject* const Sender, TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus &AGattStatus);
	void __fastcall DoOnCharacteristicWrite(System::TObject* const Sender, TBluetoothGattCharacteristic* const ACharacteristic, TBluetoothGattStatus &AGattStatus, const System::TArray__1<System::Byte> Value);
	virtual void __fastcall DoOnClientSubscribed(System::TObject* const Sender, const System::UnicodeString AClientId, TBluetoothGattCharacteristic* const ACharacteristic);
	virtual void __fastcall DoOnClientUnsubscribed(System::TObject* const Sender, const System::UnicodeString AClientId, TBluetoothGattCharacteristic* const ACharacteristic);
	virtual void __fastcall DoStartAdvertising() = 0 ;
	virtual void __fastcall DoStopAdvertising() = 0 ;
	virtual bool __fastcall DoIsAdvertising() = 0 ;
	bool __fastcall GetIsAdvertising();
	void __fastcall SetGattServerName(System::UnicodeString AName);
	
public:
	__fastcall TBluetoothGattServer(TBluetoothLEManager* const AManager);
	__fastcall virtual ~TBluetoothGattServer();
	bool __fastcall AddService(TBluetoothGattService* const AService, bool ShouldAdvertise = true);
	TBluetoothGattService* __fastcall FindService(const GUID &AUUID);
	TBluetoothGattService* __fastcall CreateService(const GUID &AnUUID, TBluetoothServiceType AType);
	TBluetoothGattService* __fastcall CreateIncludedService(TBluetoothGattService* const AService, const GUID &AnUUID, TBluetoothServiceType AType);
	bool __fastcall AddCharacteristic(TBluetoothGattService* const AService, TBluetoothGattCharacteristic* const ACharacteristic);
	TBluetoothGattCharacteristic* __fastcall CreateCharacteristic(TBluetoothGattService* const AService, const GUID &AnUUID, const TBluetoothPropertyFlags AProps, const System::UnicodeString ADescription = System::UnicodeString());
	TBluetoothGattDescriptor* __fastcall CreateDescriptor(TBluetoothGattCharacteristic* const ACharacteristic, const GUID &AnUUID);
	TBluetoothGattServiceList* __fastcall GetServices();
	void __fastcall ClearServices();
	void __fastcall Close();
	void __fastcall StartAdvertising();
	void __fastcall StopAdvertising();
	__property System::UnicodeString GattServerName = {read=FGattServerName, write=SetGattServerName};
	__property bool IsAdvertising = {read=GetIsAdvertising, nodefault};
	__property bool AdvertiseService = {read=FAdvertiseService, write=FAdvertiseService, nodefault};
	__property TConnectLEDeviceEvent OnConnectedDevice = {read=FOnConnectedDevice, write=FOnConnectedDevice};
	__property TConnectLEDeviceEvent OnDisconnectDevice = {read=FOnDisconnectDevice, write=FOnDisconnectDevice};
	__property TGattCharacteristicReadEvent OnCharacteristicRead = {read=FOnCharacteristicRead, write=FOnCharacteristicRead};
	__property TGattCharacteristicWriteEvent OnCharacteristicWrite = {read=FOnCharacteristicWrite, write=FOnCharacteristicWrite};
	__property TGattServiceEvent OnServiceAdded = {read=FOnGattServiceAdded, write=FOnGattServiceAdded};
	__property TGattCharacteristicSubscriptionEvent OnClientSubscribed = {read=FOnClientSubscribed, write=FOnClientSubscribed};
	__property TGattCharacteristicSubscriptionEvent OnClientUnsubscribed = {read=FOnClientUnsubscribed, write=FOnClientUnsubscribed};
	__property TBluetoothLEAdvertiseData* AdvertiseData = {read=FAdvertiseData};
	void __fastcall UpdateCharacteristicValue(TBluetoothGattCharacteristic* const ACharacteristic);
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE GUID BLUETOOTH_BASE_UUID;
}	/* namespace Bluetooth */
}	/* namespace System */
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
#endif	// System_BluetoothHPP
