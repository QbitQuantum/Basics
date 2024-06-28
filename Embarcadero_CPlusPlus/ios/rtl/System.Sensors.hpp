// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Sensors.pas' rev: 34.00 (iOS)

#ifndef System_SensorsHPP
#define System_SensorsHPP

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
#include <System.RTLConsts.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Sensors
{
//-- forward type declarations -----------------------------------------------
struct TLocationCoord2D;
struct THeading;
struct TLocationRegion;
struct TGpsSatellite;
class DELPHICLASS TCivicAddress;
class DELPHICLASS ESensorManagerException;
class DELPHICLASS ESensorException;
class DELPHICLASS ELocationSensorException;
class DELPHICLASS EGeocoderException;
class DELPHICLASS EGpsStatusException;
class DELPHICLASS TCustomSensor;
class DELPHICLASS TCustomLocationSensor;
class DELPHICLASS TCustomEnvironmentalSensor;
class DELPHICLASS TCustomMotionSensor;
class DELPHICLASS TCustomOrientationSensor;
class DELPHICLASS TCustomElectricalSensor;
class DELPHICLASS TCustomMechanicalSensor;
class DELPHICLASS TCustomBiometricSensor;
class DELPHICLASS TCustomLightSensor;
class DELPHICLASS TCustomScannerSensor;
__interface DELPHIINTERFACE TSensorFilter;
typedef System::DelphiInterface<TSensorFilter> _di_TSensorFilter;
class DELPHICLASS TSensorManager;
class DELPHICLASS TGeocoder;
class DELPHICLASS TGpsStatus;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TGeocoderClass);

_DECLARE_METACLASS(System::TMetaClass, TGpsStatusClass);

typedef double TLocationDegrees;

typedef double TLocationDistance;

typedef double TLocationAccuracy;

enum class DECLSPEC_DENUM TPowerConsumption : unsigned char { pcNotSpecified, pcLow, pcMedium, pcHigh };

enum class DECLSPEC_DENUM TAuthorizationType : unsigned char { atNotSpecified, atUnauthorized, atAuthorized };

enum class DECLSPEC_DENUM TLocationChangeType : unsigned char { lctSmall, lctLarge };

enum class DECLSPEC_DENUM TSensorCategory : unsigned char { Location, Environmental, Motion, Orientation, Mechanical, Electrical, Biometric, Light, Scanner };

typedef System::Set<TSensorCategory, _DELPHI_SET_ENUMERATOR(TSensorCategory::Location), _DELPHI_SET_ENUMERATOR(TSensorCategory::Scanner)> TSensorCategories;

enum class DECLSPEC_DENUM TLocationSensorType : unsigned char { GPS, Static, Lookup, Triangulation, Broadcast, DeadReckoning, Other };

enum class DECLSPEC_DENUM TLocationUsageAuthorization : unsigned char { WhenInUse, Always };

enum class DECLSPEC_DENUM TLocationActivityType : unsigned char { Other, Automotive, Fitness, Navigation };

enum class DECLSPEC_DENUM TEnvironmentalSensorType : unsigned char { Temperature, AtmosphericPressure, Humidity, WindSpeed, WindDirection };

enum class DECLSPEC_DENUM TMotionSensorType : unsigned char { Accelerometer1D, Accelerometer2D, Accelerometer3D, MotionDetector, Gyrometer1D, Gyrometer2D, Gyrometer3D, Speedometer, LinearAccelerometer3D, GravityAccelerometer3D };

enum class DECLSPEC_DENUM TOrientationSensorType : unsigned char { Compass1D, Compass2D, Compass3D, Inclinometer1D, Inclinometer2D, Inclinometer3D, Distance1D, Distance2D, Distance3D };

enum class DECLSPEC_DENUM TElectricalSensorType : unsigned char { Voltage, Current, Capacitance, Resistance, Inductance, ElectricalPower, Potentiometer };

enum class DECLSPEC_DENUM TMechanicalSensorType : unsigned char { BooleanSwitch, BooleanSwitchArray, MultiValueSwitch, Force, Scale, Pressure, Strain };

enum class DECLSPEC_DENUM TBiometricSensorType : unsigned char { HumanPresence, HumanProximity, Touch };

enum class DECLSPEC_DENUM TLightSensorType : unsigned char { AmbientLight };

enum class DECLSPEC_DENUM TScannerSensorType : unsigned char { RFID, Barcode };

enum class DECLSPEC_DENUM TSensorState : unsigned char { Added, Removed, Initializing, Ready, NoData, AccessDenied, Error };

struct DECLSPEC_DRECORD TLocationCoord2D
{
public:
	double Latitude;
	double Longitude;
	__fastcall TLocationCoord2D(double ALatitude, double ALongitude);
	TLocationCoord2D() {}
};


struct DECLSPEC_DRECORD THeading
{
public:
	double Azimuth;
};


struct DECLSPEC_DRECORD TLocationRegion
{
private:
	System::UnicodeString FID;
	TLocationCoord2D FCenter;
	double FRadius;
	
public:
	__fastcall TLocationRegion(const TLocationCoord2D &ACenter, double ARadius)/* overload */;
	__fastcall TLocationRegion(const TLocationCoord2D &ACenter, double ARadius, const System::UnicodeString AID)/* overload */;
	__property System::UnicodeString ID = {read=FID};
	__property TLocationCoord2D Center = {read=FCenter};
	__property double Radius = {read=FRadius};
	static TLocationRegion __fastcall Empty();
	TLocationRegion() {}
};


struct DECLSPEC_DRECORD TGpsSatellite
{
private:
	double FElevation;
	double FSnr;
	int FPrn;
	bool FUsedInFix;
	bool FHasAlmanac;
	double FAzimuth;
	bool FHasEphemeris;
	
public:
	__property double Azimuth = {read=FAzimuth};
	__property double Elevation = {read=FElevation};
	__property int Prn = {read=FPrn};
	__property double Snr = {read=FSnr};
	__property bool HasAlmanac = {read=FHasAlmanac};
	__property bool HasEphemeris = {read=FHasEphemeris};
	__property bool UsedInFix = {read=FUsedInFix};
	__fastcall TGpsSatellite(double Azimuth, double Elevation, int Prn, double Snr, bool HasAlmanac, bool HasEphemeris, bool UsedInFix);
	TGpsSatellite() {}
};


typedef void __fastcall (*TConvertAddressEvent)(TCivicAddress* const Address, /* out */ System::UnicodeString &Value, bool &Handled);

class PASCALIMPLEMENTATION TCivicAddress : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TLocationCoord2D FCoord;
	System::UnicodeString FAddress;
	System::UnicodeString FAdminArea;
	System::UnicodeString FCountryCode;
	System::UnicodeString FCountryName;
	System::UnicodeString FFeatureName;
	System::UnicodeString FLocale;
	System::UnicodeString FLocality;
	System::UnicodeString FPhone;
	System::UnicodeString FPostalCode;
	System::UnicodeString FPremises;
	System::UnicodeString FSubAdminArea;
	System::UnicodeString FSubLocality;
	System::UnicodeString FSubThoroughfare;
	System::UnicodeString FThoroughfare;
	System::UnicodeString FURL;
	TConvertAddressEvent FOnConvertAddress;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	System::UnicodeString __fastcall ConcatAddrStrings(const System::UnicodeString *Strings, const int Strings_High);
	
public:
	__property TLocationCoord2D Coord = {read=FCoord, write=FCoord};
	__property System::UnicodeString Address = {read=FAddress, write=FAddress};
	__property System::UnicodeString AdminArea = {read=FAdminArea, write=FAdminArea};
	__property System::UnicodeString CountryCode = {read=FCountryCode, write=FCountryCode};
	__property System::UnicodeString CountryName = {read=FCountryName, write=FCountryName};
	__property System::UnicodeString FeatureName = {read=FFeatureName, write=FFeatureName};
	__property System::UnicodeString Locale = {read=FLocale, write=FLocale};
	__property System::UnicodeString Locality = {read=FLocality, write=FLocality};
	__property System::UnicodeString Phone = {read=FPhone, write=FPhone};
	__property System::UnicodeString PostalCode = {read=FPostalCode, write=FPostalCode};
	__property System::UnicodeString Premises = {read=FPremises, write=FPremises};
	__property System::UnicodeString SubAdminArea = {read=FSubAdminArea, write=FSubAdminArea};
	__property System::UnicodeString SubLocality = {read=FSubLocality, write=FSubLocality};
	__property System::UnicodeString SubThoroughfare = {read=FSubThoroughfare, write=FSubThoroughfare};
	__property System::UnicodeString Thoroughfare = {read=FThoroughfare, write=FThoroughfare};
	__property System::UnicodeString URL = {read=FURL, write=FURL};
	virtual System::UnicodeString __fastcall ToString();
	__property TConvertAddressEvent OnConvertAddress = {read=FOnConvertAddress, write=FOnConvertAddress};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TCivicAddress() { }
	
public:
	/* TObject.Create */ inline __fastcall TCivicAddress() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION ESensorManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESensorManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESensorManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESensorManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESensorManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESensorManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESensorManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESensorManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESensorManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESensorManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESensorManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESensorManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESensorManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESensorManagerException() { }
	
};


class PASCALIMPLEMENTATION ESensorException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESensorException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESensorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESensorException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESensorException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESensorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESensorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESensorException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESensorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESensorException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESensorException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESensorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESensorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESensorException() { }
	
};


class PASCALIMPLEMENTATION ELocationSensorException : public ESensorException
{
	typedef ESensorException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELocationSensorException(const System::UnicodeString Msg) : ESensorException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELocationSensorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESensorException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELocationSensorException(NativeUInt Ident)/* overload */ : ESensorException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELocationSensorException(System::PResStringRec ResStringRec)/* overload */ : ESensorException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocationSensorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESensorException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocationSensorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESensorException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELocationSensorException(const System::UnicodeString Msg, int AHelpContext) : ESensorException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELocationSensorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESensorException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocationSensorException(NativeUInt Ident, int AHelpContext)/* overload */ : ESensorException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocationSensorException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESensorException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocationSensorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESensorException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocationSensorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESensorException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELocationSensorException() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, ESensorExceptionClass);

class PASCALIMPLEMENTATION EGeocoderException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EGeocoderException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EGeocoderException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EGeocoderException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EGeocoderException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EGeocoderException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EGeocoderException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EGeocoderException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EGeocoderException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGeocoderException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGeocoderException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGeocoderException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGeocoderException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EGeocoderException() { }
	
};


class PASCALIMPLEMENTATION EGpsStatusException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EGpsStatusException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EGpsStatusException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EGpsStatusException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EGpsStatusException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EGpsStatusException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EGpsStatusException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EGpsStatusException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EGpsStatusException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGpsStatusException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGpsStatusException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGpsStatusException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGpsStatusException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EGpsStatusException() { }
	
};


class PASCALIMPLEMENTATION TCustomSensor : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { UniqueID, Manufacturer, Model, SerialNo, Name, Description };
	
	
private:
	System::Classes::TNotifyEvent FOnDataChanged;
	System::Classes::TNotifyEvent FOnSensorRemoved;
	System::Classes::TNotifyEvent FOnStateChanged;
	TSensorManager* FManager;
	bool FStarted;
	
protected:
	__classmethod virtual ESensorExceptionClass __fastcall ErrorClass();
	__classmethod void __fastcall SensorError(const System::UnicodeString Msg, System::TVarRec *Params, const int Params_High)/* overload */;
	__classmethod void __fastcall SensorError(const System::UnicodeString Msg)/* overload */;
	virtual void __fastcall DataChanged();
	virtual System::Variant __fastcall GetCustomData(const void *Data);
	virtual System::Variant __fastcall GetCustomProperty(const void *Prop);
	virtual bool __fastcall GetHasCustomProperty(const void *Prop);
	virtual bool __fastcall GetHasCustomData(const void *Data);
	virtual TSensorCategory __fastcall GetSensorCategory() = 0 ;
	virtual System::UnicodeString __fastcall GetSensorProperty(TProperty Prop);
	virtual TSensorState __fastcall GetState() = 0 ;
	virtual System::TDateTime __fastcall GetTimeStamp() = 0 ;
	void __fastcall RemoveSensor();
	virtual void __fastcall SensorRemoved();
	virtual void __fastcall StateChanged();
	virtual void __fastcall SetCustomProperty(const void *Prop, const System::Variant &Value);
	__fastcall virtual TCustomSensor(TSensorManager* AManager);
	virtual bool __fastcall DoStart();
	virtual void __fastcall DoStop();
	virtual HRESULT __fastcall DoGetInterface(const GUID &IID, /* out */ void *Obj) = 0 ;
	
public:
	HIDESBASE HRESULT __fastcall GetInterface(const GUID &IID, /* out */ void *Obj);
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~TCustomSensor();
	void __fastcall Start();
	void __fastcall Stop();
	__property bool Started = {read=FStarted, nodefault};
	__property TSensorCategory Category = {read=GetSensorCategory, nodefault};
	__property System::Variant CustomData[const void *Data] = {read=GetCustomData};
	__property System::Variant CustomProperty[const void *Prop] = {read=GetCustomProperty, write=SetCustomProperty};
	__property System::UnicodeString Description = {read=GetSensorProperty, index=5};
	__property bool HasCustomData[const void *Data] = {read=GetHasCustomData};
	__property bool HasCustomProperty[const void *Prop] = {read=GetHasCustomProperty};
	__property TSensorManager* Manager = {read=FManager};
	__property System::UnicodeString Manufacturer = {read=GetSensorProperty, index=1};
	__property System::UnicodeString Model = {read=GetSensorProperty, index=2};
	__property System::UnicodeString Name = {read=GetSensorProperty, index=4};
	__property System::UnicodeString SerialNo = {read=GetSensorProperty, index=3};
	__property TSensorState State = {read=GetState, nodefault};
	__property System::TDateTime TimeStamp = {read=GetTimeStamp};
	__property System::UnicodeString UniqueID = {read=GetSensorProperty, index=0};
	__property System::Classes::TNotifyEvent OnDataChanged = {read=FOnDataChanged, write=FOnDataChanged};
	__property System::Classes::TNotifyEvent OnSensorRemoved = {read=FOnSensorRemoved, write=FOnSensorRemoved};
	__property System::Classes::TNotifyEvent OnStateChanged = {read=FOnStateChanged, write=FOnStateChanged};
};


typedef void __fastcall (__closure *TLocationChangedEvent)(System::TObject* Sender, const TLocationCoord2D &OldLocation, const TLocationCoord2D &NewLocation);

typedef void __fastcall (__closure *THeadingChangedEvent)(System::TObject* Sender, const THeading &AHeading);

typedef void __fastcall (__closure *TRegionProximityEvent)(System::TObject* Sender, const TLocationRegion &Region);

typedef void __fastcall (__closure *TLocationUpdatesPausedChangedEvent)(System::TObject* Sender, const bool Paused);

class PASCALIMPLEMENTATION TCustomLocationSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { Latitude, Longitude, ErrorRadius, Altitude, Speed, TrueHeading, MagneticHeading, Address1, Address2, City, StateProvince, PostalCode, CountryRegion };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::Latitude), _DELPHI_SET_ENUMERATOR(TProperty::CountryRegion)> TProperties;
	
	class DELPHICLASS TRegionList;
	class PASCALIMPLEMENTATION TRegionList : public System::Generics::Collections::TList__1<TLocationRegion>
	{
		typedef System::Generics::Collections::TList__1<TLocationRegion> inherited;
		
	public:
		__fastcall TRegionList();
	public:
		/* {System_Generics_Collections}TList<System_Sensors_TLocationRegion>.Destroy */ inline __fastcall virtual ~TRegionList() { }
		
	};
	
	
	
private:
	TRegionList* FRegions;
	TLocationChangeType FLocationChange;
	bool FOptimize;
	TLocationChangedEvent FOnLocationChanged;
	THeadingChangedEvent FOnHeadingChanged;
	TRegionProximityEvent FOnEnterRegion;
	TRegionProximityEvent FOnExitRegion;
	TLocationUpdatesPausedChangedEvent FOnLocationUpdatesPausedChanged;
	
protected:
	virtual TLocationSensorType __fastcall GetLocationSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual System::UnicodeString __fastcall GetStringProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	virtual TAuthorizationType __fastcall GetAuthorized() = 0 ;
	virtual double __fastcall GetAccuracy() = 0 ;
	virtual TLocationActivityType __fastcall GetActivityType() = 0 ;
	virtual double __fastcall GetDistance() = 0 ;
	virtual TPowerConsumption __fastcall GetPowerConsumption() = 0 ;
	virtual TLocationUsageAuthorization __fastcall GetUsageAuthorization() = 0 ;
	virtual void __fastcall SetAccuracy(const double Value) = 0 ;
	virtual void __fastcall SetActivityType(const TLocationActivityType Value) = 0 ;
	virtual void __fastcall SetDistance(const double Value) = 0 ;
	void __fastcall SetLocationChange(TLocationChangeType Value);
	void __fastcall SetOptimize(const bool Value);
	virtual void __fastcall SetUsageAuthorization(const TLocationUsageAuthorization Value) = 0 ;
	virtual void __fastcall DoLocationChangeType() = 0 ;
	virtual void __fastcall DoOptimize() = 0 ;
	virtual void __fastcall DoLocationChanged(const TLocationCoord2D &OldLocation, const TLocationCoord2D &NewLocation);
	virtual void __fastcall DoHeadingChanged(const THeading &AHeading);
	virtual void __fastcall DoEnterRegion(const TLocationRegion &Region);
	virtual void __fastcall DoExitRegion(const TLocationRegion &Region);
	virtual void __fastcall DoLocationUpdatesPausedChanged(const bool APaused);
	void __fastcall RegionNotify(System::TObject* Sender, const TLocationRegion &Item, System::Generics::Collections::TCollectionNotification Action);
	virtual void __fastcall RegionAdded(const TLocationRegion &Item);
	virtual void __fastcall RegionRemoved(const TLocationRegion &Item);
	__fastcall virtual TCustomLocationSensor(TSensorManager* AManager);
	
public:
	__fastcall virtual ~TCustomLocationSensor();
	__property TLocationSensorType SensorType = {read=GetLocationSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property TAuthorizationType Authorized = {read=GetAuthorized, nodefault};
	__property double Accuracy = {read=GetAccuracy, write=SetAccuracy};
	__property TLocationActivityType ActivityType = {read=GetActivityType, write=SetActivityType, nodefault};
	__property double Distance = {read=GetDistance, write=SetDistance};
	__property bool Optimize = {read=FOptimize, write=SetOptimize, nodefault};
	__property TPowerConsumption PowerConsumption = {read=GetPowerConsumption, nodefault};
	__property TLocationUsageAuthorization UsageAuthorization = {read=GetUsageAuthorization, write=SetUsageAuthorization, nodefault};
	__property TLocationChangeType LocationChange = {read=FLocationChange, write=SetLocationChange, nodefault};
	__property TRegionList* Regions = {read=FRegions};
	__property double Latitude = {read=GetDoubleProperty, index=0};
	__property double Longitude = {read=GetDoubleProperty, index=1};
	__property double ErrorRadius = {read=GetDoubleProperty, index=2};
	__property double Altitude = {read=GetDoubleProperty, index=3};
	__property double Speed = {read=GetDoubleProperty, index=4};
	__property double TrueHeading = {read=GetDoubleProperty, index=5};
	__property double MagneticHeading = {read=GetDoubleProperty, index=6};
	__property System::UnicodeString Address1 = {read=GetStringProperty, index=7};
	__property System::UnicodeString Address2 = {read=GetStringProperty, index=8};
	__property System::UnicodeString City = {read=GetStringProperty, index=9};
	__property System::UnicodeString StateProvince = {read=GetStringProperty, index=10};
	__property System::UnicodeString PostalCode = {read=GetStringProperty, index=11};
	__property System::UnicodeString CountryRegion = {read=GetStringProperty, index=12};
	__property TLocationChangedEvent OnLocationChanged = {read=FOnLocationChanged, write=FOnLocationChanged};
	__property THeadingChangedEvent OnHeadingChanged = {read=FOnHeadingChanged, write=FOnHeadingChanged};
	__property TRegionProximityEvent OnEnterRegion = {read=FOnEnterRegion, write=FOnEnterRegion};
	__property TRegionProximityEvent OnExitRegion = {read=FOnExitRegion, write=FOnExitRegion};
	__property TLocationUpdatesPausedChangedEvent OnLocationUpdatesPausedChanged = {read=FOnLocationUpdatesPausedChanged, write=FOnLocationUpdatesPausedChanged};
};


class PASCALIMPLEMENTATION TCustomEnvironmentalSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { Temperature, Pressure, Humidity, WindDirection, WindSpeed };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::Temperature), _DELPHI_SET_ENUMERATOR(TProperty::WindSpeed)> TProperties;
	
	
protected:
	virtual TEnvironmentalSensorType __fastcall GetEnvironmentalSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TEnvironmentalSensorType SensorType = {read=GetEnvironmentalSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property double Temperature = {read=GetDoubleProperty, index=0};
	__property double Pressure = {read=GetDoubleProperty, index=1};
	__property double Humidity = {read=GetDoubleProperty, index=2};
	__property double WindDirection = {read=GetDoubleProperty, index=3};
	__property double WindSpeed = {read=GetDoubleProperty, index=4};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomEnvironmentalSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomEnvironmentalSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomMotionSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { AccelerationX, AccelerationY, AccelerationZ, AngleAccelX, AngleAccelY, AngleAccelZ, Motion, Speed };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::AccelerationX), _DELPHI_SET_ENUMERATOR(TProperty::Speed)> TProperties;
	
	
protected:
	virtual TMotionSensorType __fastcall GetMotionSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	virtual double __fastcall GetUpdateInterval() = 0 ;
	virtual void __fastcall SetUpdateInterval(double AInterval) = 0 ;
	__fastcall virtual TCustomMotionSensor(TSensorManager* AManager);
	
public:
	__property TMotionSensorType SensorType = {read=GetMotionSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property double AccelerationX = {read=GetDoubleProperty, index=0};
	__property double AccelerationY = {read=GetDoubleProperty, index=1};
	__property double AccelerationZ = {read=GetDoubleProperty, index=2};
	__property double AngleAccelX = {read=GetDoubleProperty, index=3};
	__property double AngleAccelY = {read=GetDoubleProperty, index=4};
	__property double AngleAccelZ = {read=GetDoubleProperty, index=5};
	__property double Motion = {read=GetDoubleProperty, index=6};
	__property double Speed = {read=GetDoubleProperty, index=7};
	__property double UpdateInterval = {read=GetUpdateInterval, write=SetUpdateInterval};
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomMotionSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomOrientationSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { TiltX, TiltY, TiltZ, DistanceX, DistanceY, DistanceZ, HeadingX, HeadingY, HeadingZ, MagHeading, TrueHeading, CompMagHeading, CompTrueHeading };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::TiltX), _DELPHI_SET_ENUMERATOR(TProperty::CompTrueHeading)> TProperties;
	
	
protected:
	virtual TOrientationSensorType __fastcall GetOrientationSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	virtual double __fastcall GetUpdateInterval() = 0 ;
	virtual void __fastcall SetUpdateInterval(double AInterval) = 0 ;
	__fastcall virtual TCustomOrientationSensor(TSensorManager* AManager);
	
public:
	__property TOrientationSensorType SensorType = {read=GetOrientationSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property double TiltX = {read=GetDoubleProperty, index=0};
	__property double TiltY = {read=GetDoubleProperty, index=1};
	__property double TiltZ = {read=GetDoubleProperty, index=2};
	__property double DistanceX = {read=GetDoubleProperty, index=3};
	__property double DistanceY = {read=GetDoubleProperty, index=4};
	__property double DistanceZ = {read=GetDoubleProperty, index=5};
	__property double HeadingX = {read=GetDoubleProperty, index=6};
	__property double HeadingY = {read=GetDoubleProperty, index=7};
	__property double HeadingZ = {read=GetDoubleProperty, index=8};
	__property double MagHeading = {read=GetDoubleProperty, index=9};
	__property double TrueHeading = {read=GetDoubleProperty, index=10};
	__property double CompMagHeading = {read=GetDoubleProperty, index=11};
	__property double CompTrueHeading = {read=GetDoubleProperty, index=12};
	__property double UpdateInterval = {read=GetUpdateInterval, write=SetUpdateInterval};
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomOrientationSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomElectricalSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { Capacitance, Resistance, Inductance, Current, Voltage, Power };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::Capacitance), _DELPHI_SET_ENUMERATOR(TProperty::Power)> TProperties;
	
	
protected:
	virtual TElectricalSensorType __fastcall GetElectricalSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TElectricalSensorType SensorType = {read=GetElectricalSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property double Capacitance = {read=GetDoubleProperty, index=0};
	__property double Resistance = {read=GetDoubleProperty, index=1};
	__property double Inductance = {read=GetDoubleProperty, index=2};
	__property double Current = {read=GetDoubleProperty, index=3};
	__property double Voltage = {read=GetDoubleProperty, index=4};
	__property double Power = {read=GetDoubleProperty, index=5};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomElectricalSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomElectricalSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomMechanicalSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { SwitchState, SwitchArrayState, MultiValueState, Force, AbsPressure, GaugePressure, Strain, Weight };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::SwitchState), _DELPHI_SET_ENUMERATOR(TProperty::Weight)> TProperties;
	
	
protected:
	virtual TMechanicalSensorType __fastcall GetMechanicalSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual bool __fastcall GetBooleanProperty(TProperty Prop);
	virtual unsigned __fastcall GetStateProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TMechanicalSensorType SensorType = {read=GetMechanicalSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property bool SwitchState = {read=GetBooleanProperty, index=0, nodefault};
	__property unsigned SwitchArrayState = {read=GetStateProperty, index=1, nodefault};
	__property double MultiValueState = {read=GetDoubleProperty, index=2};
	__property double Force = {read=GetDoubleProperty, index=3};
	__property double AbsPressure = {read=GetDoubleProperty, index=4};
	__property double GaugePressure = {read=GetDoubleProperty, index=5};
	__property double Strain = {read=GetDoubleProperty, index=6};
	__property double Weight = {read=GetDoubleProperty, index=7};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomMechanicalSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomMechanicalSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomBiometricSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { HumanPresence, HumanProximity, Touch };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::HumanPresence), _DELPHI_SET_ENUMERATOR(TProperty::Touch)> TProperties;
	
	
protected:
	virtual TBiometricSensorType __fastcall GetBiometricSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual bool __fastcall GetBooleanProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TBiometricSensorType SensorType = {read=GetBiometricSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property bool HumanPresence = {read=GetBooleanProperty, index=0, nodefault};
	__property double HumanProximity = {read=GetDoubleProperty, index=1};
	__property bool Touch = {read=GetBooleanProperty, index=2, nodefault};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomBiometricSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomBiometricSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomLightSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { Lux, Temperature, Chromacity };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::Lux), _DELPHI_SET_ENUMERATOR(TProperty::Chromacity)> TProperties;
	
	
protected:
	virtual TLightSensorType __fastcall GetLightSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual double __fastcall GetDoubleProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TLightSensorType SensorType = {read=GetLightSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property double Lux = {read=GetDoubleProperty, index=0};
	__property double Temperature = {read=GetDoubleProperty, index=1};
	__property double Chromacity = {read=GetDoubleProperty, index=2};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomLightSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomLightSensor() { }
	
};


class PASCALIMPLEMENTATION TCustomScannerSensor : public TCustomSensor
{
	typedef TCustomSensor inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { RFIDTag, BarcodeData };
	
	typedef System::Set<TProperty, _DELPHI_SET_ENUMERATOR(TProperty::RFIDTag), _DELPHI_SET_ENUMERATOR(TProperty::BarcodeData)> TProperties;
	
	
protected:
	virtual TScannerSensorType __fastcall GetScannerSensorType() = 0 ;
	virtual TProperties __fastcall GetAvailableProperties() = 0 ;
	virtual unsigned __int64 __fastcall GetUInt64Property(TProperty Prop);
	virtual System::UnicodeString __fastcall GetStringProperty(TProperty Prop);
	virtual TSensorCategory __fastcall GetSensorCategory();
	
public:
	__property TScannerSensorType SensorType = {read=GetScannerSensorType, nodefault};
	__property TProperties AvailableProperties = {read=GetAvailableProperties, nodefault};
	__property unsigned __int64 RFIDTag = {read=GetUInt64Property, index=0};
	__property System::UnicodeString BarcodeData = {read=GetStringProperty, index=1};
protected:
	/* TCustomSensor.Create */ inline __fastcall virtual TCustomScannerSensor(TSensorManager* AManager) : TCustomSensor(AManager) { }
	
public:
	/* TCustomSensor.Destroy */ inline __fastcall virtual ~TCustomScannerSensor() { }
	
};


typedef void __fastcall (__closure *TSensorManagerEvent)(System::TObject* Sender, TCustomSensor* Sensor, TSensorState State);

typedef System::DynamicArray<TCustomSensor*> TSensorArray;

__interface TSensorFilter  : public System::IInterface 
{
	virtual bool __fastcall Invoke(TCustomSensor* Sensor) = 0 ;
};

class PASCALIMPLEMENTATION TSensorManager : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,_di_TSensorFilter>* TFilters;
	
	
protected:
	_DECLARE_METACLASS(System::TMetaClass, TSensorManagerType);
	
	
public:
	TCustomSensor* operator[](int Index) { return this->Sensors[Index]; }
	
private:
	static TSensorManager* FCurrentManager;
	static TSensorManager* __fastcall InternalGetSensorManager();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
protected:
	static TSensorManagerType FSensorManagerType;
	
private:
	System::Generics::Collections::TList__1<TSensorManagerEvent>* FSensorManagerEvents;
	System::Generics::Collections::TObjectList__1<TCustomSensor*>* FSensors;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,_di_TSensorFilter>* FFilters;
	int __fastcall GetCount();
	TCustomSensor* __fastcall GetSensor(int Index)/* overload */;
	
protected:
	virtual __classmethod TSensorManager* __fastcall GetSensorManager() = 0 ;
	void __fastcall AddSensor(TCustomSensor* Sensor);
	void __fastcall SensorManagerEvent(TCustomSensor* Sensor, TSensorState State);
	virtual bool __fastcall GetCanActivate() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(bool Value);
	void __fastcall RemoveSensor(TCustomSensor* Sensor);
	__fastcall TSensorManager();
	
public:
	__fastcall virtual ~TSensorManager();
	virtual void __fastcall Activate() = 0 ;
	void __fastcall AddSensorManagerEvent(TSensorManagerEvent Event);
	virtual void __fastcall Deactivate() = 0 ;
	TSensorArray __fastcall GetSensorsByCategory(TSensorCategory Category);
	TSensorArray __fastcall GetSensorsByFilter(_di_TSensorFilter Filter);
	void __fastcall RemoveSensorManagerEvent(TSensorManagerEvent Event);
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property bool CanActivate = {read=GetCanActivate, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property TCustomSensor* Sensors[int Index] = {read=GetSensor/*, default*/};
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,_di_TSensorFilter>* Filters = {read=FFilters};
	/* static */ __property TSensorManager* Current = {read=InternalGetSensorManager};
};


typedef void __fastcall (__closure *TGeocodeEvent)(const System::TArray__1<TLocationCoord2D> Coords);

typedef void __fastcall (__closure *TGeocodeReverseEvent)(TCivicAddress* const Address);

class PASCALIMPLEMENTATION TGeocoder : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TGeocoderClass FCurrent;
	static bool FGeocoding;
	static TGeocodeEvent FOnGeocode;
	static TGeocodeReverseEvent FOnGeocodeReverse;
	static TGeocoderClass __fastcall GetCurrent();
	
protected:
	static System::TArray__1<TLocationCoord2D> FGeoFwdCoords;
	static TCivicAddress* FGeoRevAddress;
	
private:
	__classmethod TGeocoderClass __fastcall GeocoderImplementer();
	
protected:
	__classmethod void __fastcall GeocodeError(const System::UnicodeString Msg);
	virtual __classmethod TGeocoderClass __fastcall GetGeocoderImplementer() = 0 ;
	virtual __classmethod void __fastcall GeocodeRequest(TCivicAddress* const Address) = 0 ;
	virtual __classmethod void __fastcall GeocodeReverseRequest(const TLocationCoord2D &Coords) = 0 ;
	__classmethod virtual void __fastcall DoGeocode(const System::TArray__1<TLocationCoord2D> Coords);
	__classmethod virtual void __fastcall DoGeocodeReverse(TCivicAddress* const Address);
	__classmethod virtual void __fastcall Initialize();
	
public:
	virtual __classmethod bool __fastcall Supported() = 0 ;
	virtual __classmethod TAuthorizationType __fastcall Authorized() = 0 ;
	virtual __classmethod void __fastcall Cancel() = 0 ;
	__classmethod bool __fastcall Geocoding();
	__classmethod void __fastcall Geocode(TCivicAddress* const Address);
	__classmethod void __fastcall GeocodeReverse(const TLocationCoord2D &Coords);
	/* static */ __property TGeocoderClass Current = {read=GetCurrent};
	/* static */ __property TGeocodeEvent OnGeocode = {read=FOnGeocode, write=FOnGeocode};
	/* static */ __property TGeocodeReverseEvent OnGeocodeReverse = {read=FOnGeocodeReverse, write=FOnGeocodeReverse};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TGeocoder() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeocoder() { }
	
};


class PASCALIMPLEMENTATION TGpsStatus : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TGpsStatusClass FCurrent;
	static TGpsStatusClass __fastcall GetCurrent();
	
protected:
	__classmethod void __fastcall GpsStatusError(const System::UnicodeString Msg);
	virtual __classmethod TGpsStatusClass __fastcall GetGpsStatusImplementer() = 0 ;
	__classmethod virtual void __fastcall Initialize();
	
public:
	virtual __classmethod bool __fastcall Supported() = 0 ;
	virtual __classmethod TAuthorizationType __fastcall Authorized() = 0 ;
	virtual __classmethod TGpsSatellite __fastcall Satellites(int Index) = 0 ;
	virtual __classmethod int __fastcall SatelliteCount() = 0 ;
	virtual __classmethod int __fastcall SatelliteFirstFixTime() = 0 ;
	/* static */ __property TGpsStatusClass Current = {read=GetCurrent};
public:
	/* TObject.Create */ inline __fastcall TGpsStatus() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGpsStatus() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sensors */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_SENSORS)
using namespace System::Sensors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_SensorsHPP
