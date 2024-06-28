// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Iot.Family.BluetoothLE.GattTypes.pas' rev: 34.00 (Android)

#ifndef Iot_Family_Bluetoothle_GatttypesHPP
#define Iot_Family_Bluetoothle_GatttypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iot
{
namespace Family
{
namespace Bluetoothle
{
namespace Gatttypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIEEE11073Helpers;
struct TGattPeripheralPreferredConnectionParameters;
struct TGattServiceChanged;
struct TGattSystemID;
struct TGattPnPID;
struct TGattHealthInformatics20601;
struct DECLSPEC_DRECORD TGattPosition3D
{
};


struct DECLSPEC_DRECORD TGattScanRefresh
{
};


struct TGattHeartRateMeasurement;
struct TGattHeartRateControlPoint;
struct TGattCyclingSpeedAndCadenceMeasurement;
struct TGattCyclingSpeedAndCadenceFeature;
struct TGattRunningSpeedAndCadenceMeasurement;
struct TGattRunningSpeedAndCadenceFeature;
struct TGattSpeedAndCadenceControlPoint;
struct TGattSpeedAndCadenceResponseCode;
struct TGattTemperatureMeasurement;
struct TGattBloodPressureMeasurement;
struct TGattIntermediateCuffPressure;
struct TGattBloodPressureFeature;
struct TGattDateTime;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIEEE11073Helpers : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod float __fastcall FloatToSingle(const int Mantissa, const int Exponent);
	__classmethod float __fastcall SFloatToSingle(const int Mantissa, const int Exponent);
public:
	/* TObject.Create */ inline __fastcall TIEEE11073Helpers() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIEEE11073Helpers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TGattPeripheralPreferredConnectionParameters
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	float __fastcall GetMinimumConenctionInterval();
	float __fastcall GetMaximumConnectionInterval();
	System::Word __fastcall GetSlaveLatency();
	System::Word __fastcall GetConnectionSupervisionTimeout();
	
public:
	__fastcall TGattPeripheralPreferredConnectionParameters(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property float MinimumConenctionInterval = {read=GetMinimumConenctionInterval};
	__property float MaximumConnectionInterval = {read=GetMaximumConnectionInterval};
	__property System::Word SlaveLatency = {read=GetSlaveLatency};
	__property System::Word ConnectionSupervisionTimeoutMultiplier = {read=GetConnectionSupervisionTimeout};
	TGattPeripheralPreferredConnectionParameters() {}
};


enum class DECLSPEC_DENUM TGattAppearance : unsigned short { Unknown, GenericPhone = 64, GenericComputer = 128, GenericWatch = 192, SportsWatch, GenericClock = 256, GenericDisplay = 320, GenericRemoteControl = 384, GenericEyeGlasses = 448, GenericTag = 512, GenericKeyring = 576, GenericMediaPlayer = 640, GenericBarcodeScanner = 704, GenericThermometer = 768, ThermometerEar, GenericHeartRateSensor = 832, HeartRateSensorBelt, GenericBloodPressure = 896, BloodPressureArm, BloodPressureWrist, HumanInterfaceDevice = 960, Keyboard, Mouse, Joystick, Gamepad, DigitizerTablet, CardReader, DigitalPen, BarcodeScanner, GenericGlucoseMeter = 1024, GenericRunningWalkingSensor = 1088, RunningWalkingSensorInShoe, RunningWalkingSensorOnShoe, RunningWalkingSensorOnHip, 
	GenericCycling = 1152, CyclingComputer, CyclingSpeedSensor, CyclngCadenceSensor, CyclingPowerSensor, CyclingSpeedAndCadenceSensor, GenericPulseOximeter = 3136, Fingertip, WristWorn, GenericWeightScale = 3200, GenericOutdoorSportActivity = 5184, LocationDisplayDevice, LocationAndNavigationDisplayDevice, LocationPod, LocationAndNavigationPod };

struct DECLSPEC_DRECORD TGattServiceChanged
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	System::Word __fastcall GetStartofAffectedAttrHdlRange();
	System::Word __fastcall GetEndofAffectedAttrHdlRange();
	
public:
	__fastcall TGattServiceChanged(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property System::Word StartofAffectedAttrHdlRange = {read=GetStartofAffectedAttrHdlRange};
	__property System::Word EndofAffectedAttrHdlRange = {read=GetEndofAffectedAttrHdlRange};
	TGattServiceChanged() {}
};


struct DECLSPEC_DRECORD TGattSystemID
{
private:
	int FReserved1;
	unsigned __int64 FValue;
	unsigned __int64 __fastcall GetManufacturerIdentifier();
	unsigned __fastcall GetOUID();
	
public:
	__fastcall TGattSystemID(const unsigned __int64 AValue);
	__property unsigned __int64 Value = {read=FValue};
	__property unsigned __int64 ManufacturerIdentifier = {read=GetManufacturerIdentifier};
	__property unsigned OUID = {read=GetOUID};
	TGattSystemID() {}
};


enum class DECLSPEC_DENUM TGattVendorIDSource : unsigned char { BluetoothSIG = 0x1, USBImplementersForum };

struct DECLSPEC_DRECORD TGattPnPID
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattVendorIDSource __fastcall GetVendorIDSource();
	System::Word __fastcall GetVendorID();
	System::Word __fastcall GetProductID();
	System::Word __fastcall GetProductVersion();
	
public:
	__fastcall TGattPnPID(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattVendorIDSource VendorIDSource = {read=GetVendorIDSource};
	__property System::Word VendorID = {read=GetVendorID};
	__property System::Word ProductID = {read=GetProductID};
	__property System::Word ProductVersion = {read=GetProductVersion};
	TGattPnPID() {}
};


struct DECLSPEC_DRECORD TGattHealthInformatics20601
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	
public:
	__fastcall TGattHealthInformatics20601(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	TGattHealthInformatics20601() {}
};


enum class DECLSPEC_DENUM TGattHeartRateValueFormat : unsigned char { Eight, Sixteen };

enum class DECLSPEC_DENUM TGattHeartRateSensorContactStatus : unsigned char { NotSupported, NotDetected, ContactDetected };

enum class DECLSPEC_DENUM TGattHeartRateEnergyExpendedStatus : unsigned char { NotSupported, Present };

enum class DECLSPEC_DENUM TGattHeartRateRRIntervalStatus : unsigned char { NotSupported, Present };

struct DECLSPEC_DRECORD TGattHeartRateMeasurement
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattHeartRateValueFormat __fastcall GetHeartRateValueFormat();
	TGattHeartRateSensorContactStatus __fastcall GetContactStatus();
	TGattHeartRateEnergyExpendedStatus __fastcall GetEnergyExpendedStatus();
	TGattHeartRateRRIntervalStatus __fastcall GetRRIntervalStatus();
	System::Word __fastcall GetHeartRateMeasurement();
	System::Word __fastcall GetEnergyExpended();
	System::Word __fastcall GetRRInterval();
	
public:
	__fastcall TGattHeartRateMeasurement(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattHeartRateValueFormat HeartRateValueFormat = {read=GetHeartRateValueFormat};
	__property TGattHeartRateSensorContactStatus ContactStatus = {read=GetContactStatus};
	__property TGattHeartRateEnergyExpendedStatus EnergyExpendedStatus = {read=GetEnergyExpendedStatus};
	__property TGattHeartRateRRIntervalStatus RRIntervalStatus = {read=GetRRIntervalStatus};
	__property System::Word HeartRateMeasurement = {read=GetHeartRateMeasurement};
	__property System::Word EnergyExpended = {read=GetEnergyExpended};
	__property System::Word RRInterval = {read=GetRRInterval};
	TGattHeartRateMeasurement() {}
};


struct DECLSPEC_DRECORD TGattHeartRateControlPoint
{
private:
	System::Byte FValue;
	void __fastcall SetControlPoint(const System::Byte ControlPoint);
	
public:
	__fastcall TGattHeartRateControlPoint(const System::Byte AValue);
	__property System::Byte Value = {read=FValue};
	__property System::Byte ControlPoint = {write=SetControlPoint};
	TGattHeartRateControlPoint() {}
};


struct DECLSPEC_DRECORD TGattCyclingSpeedAndCadenceMeasurement
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	bool __fastcall GetWheelRevolutionPresent();
	bool __fastcall GetCrankRevolutionPresent();
	int __fastcall GetCumulativeWheelRevolutions();
	System::Word __fastcall GetLastWheelEventTime();
	System::Word __fastcall GetCumulativeCrankRevolutions();
	System::Word __fastcall GetLastCrankEventTime();
	
public:
	__fastcall TGattCyclingSpeedAndCadenceMeasurement(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property bool WheelRevolutionPresent = {read=GetWheelRevolutionPresent};
	__property bool CrankRevolutionPresent = {read=GetCrankRevolutionPresent};
	__property int CumulativeWheelRevolutions = {read=GetCumulativeWheelRevolutions};
	__property System::Word LastWheelEventTime = {read=GetLastWheelEventTime};
	__property System::Word CumulativeCrankRevolutions = {read=GetCumulativeCrankRevolutions};
	__property System::Word LastCrankEventTime = {read=GetLastCrankEventTime};
	TGattCyclingSpeedAndCadenceMeasurement() {}
};


struct DECLSPEC_DRECORD TGattCyclingSpeedAndCadenceFeature
{
private:
	System::Word FValue;
	int FReserved1;
	int FReserved2;
	bool __fastcall GetWheelRevolutionDataSupportStatus();
	bool __fastcall GetCrankRevolutionDataSupportStatus();
	bool __fastcall GetMultipleSensorLocationsSupportStatus();
	
public:
	__fastcall TGattCyclingSpeedAndCadenceFeature(const System::Word AValue);
	__property System::Word Value = {read=FValue};
	__property bool WheelRevolutionDataSupport = {read=GetWheelRevolutionDataSupportStatus};
	__property bool CrankRevolutionDataSupport = {read=GetCrankRevolutionDataSupportStatus};
	__property bool MultipleSensorLocationsSupport = {read=GetMultipleSensorLocationsSupportStatus};
	TGattCyclingSpeedAndCadenceFeature() {}
};


enum class DECLSPEC_DENUM TGattWalkingOrRunningStatus : unsigned char { Walking, Running };

struct DECLSPEC_DRECORD TGattRunningSpeedAndCadenceMeasurement
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	bool __fastcall GetInstantaneousStrideLengthPresent();
	bool __fastcall GetTotalDistancePresent();
	TGattWalkingOrRunningStatus __fastcall GetWalkingOrRunningStatusBits();
	float __fastcall GetInstantaneousSpeed();
	System::Byte __fastcall GetInstantaneousCadence();
	float __fastcall GetInstantaneousStrideLength();
	float __fastcall GetTotalDistance();
	
public:
	__fastcall TGattRunningSpeedAndCadenceMeasurement(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property bool InstantaneousStrideLengthPresent = {read=GetInstantaneousStrideLengthPresent};
	__property bool TotalDistancePresent = {read=GetTotalDistancePresent};
	__property TGattWalkingOrRunningStatus WalkingOrRunningStatusBits = {read=GetWalkingOrRunningStatusBits};
	__property float InstantaneousSpeed = {read=GetInstantaneousSpeed};
	__property System::Byte InstantaneousCadence = {read=GetInstantaneousCadence};
	__property float InstantaneousStrideLength = {read=GetInstantaneousStrideLength};
	__property float TotalDistance = {read=GetTotalDistance};
	TGattRunningSpeedAndCadenceMeasurement() {}
};


struct DECLSPEC_DRECORD TGattRunningSpeedAndCadenceFeature
{
private:
	System::Word FValue;
	bool __fastcall GetInstantaneousStrideLengthMeasurementSupportStatus();
	bool __fastcall GetTotalDistanceMeasurementSupportStatus();
	bool __fastcall GetWalkingOrRunningSupportStatus();
	bool __fastcall GetCalibrationProcedureSupportStatus();
	bool __fastcall GetMultipleSensorLocationsSupportStatus();
	
public:
	__fastcall TGattRunningSpeedAndCadenceFeature(const System::Word AValue);
	__property System::Word Value = {read=FValue};
	__property bool StrideLengthMeasurementSupport = {read=GetInstantaneousStrideLengthMeasurementSupportStatus};
	__property bool TotalDistanceMeasurementSupport = {read=GetTotalDistanceMeasurementSupportStatus};
	__property bool WalkingOrRunningSupport = {read=GetWalkingOrRunningSupportStatus};
	__property bool CalibrationProcedureSupport = {read=GetCalibrationProcedureSupportStatus};
	__property bool MultipleSensorLocationsSupport = {read=GetMultipleSensorLocationsSupportStatus};
	TGattRunningSpeedAndCadenceFeature() {}
};


enum class DECLSPEC_DENUM TGattSpeedAndCadenceSensorLocation: char { Unread = -1, Other, TopOFShoe, InShoe, Hip, FrontWheel, LeftCrank, RightCrank, LeftPedal, RightPedal, FrontHub, RearDropout, Chainstay, RearWheel, RearHub, Chest };

enum class DECLSPEC_DENUM TGattSpeedAndCadenceControlPointOpCode : unsigned char { SetCumulativeValue = 1, SensorCalibration, UpdateSensorLocation, RequestSupportedLocations, ResponseCode = 16 };

enum class DECLSPEC_DENUM TSCCumulativeValueType : unsigned char { CrankRevolutions, WheelRevolutions };

struct DECLSPEC_DRECORD TGattSpeedAndCadenceControlPoint
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TSCCumulativeValueType FCumulativeValueType;
	TGattSpeedAndCadenceControlPointOpCode __fastcall GetRequestOpcode();
	TGattSpeedAndCadenceSensorLocation __fastcall GetSensorLocation();
	unsigned __fastcall GetCumulativeValue();
	
public:
	__fastcall TGattSpeedAndCadenceControlPoint(const System::TArray__1<System::Byte> AValue)/* overload */;
	__fastcall TGattSpeedAndCadenceControlPoint(const TGattSpeedAndCadenceControlPointOpCode AOpcode)/* overload */;
	__fastcall TGattSpeedAndCadenceControlPoint(const TGattSpeedAndCadenceControlPointOpCode AOpcode, const TGattSpeedAndCadenceSensorLocation ASensorLocation)/* overload */;
	__fastcall TGattSpeedAndCadenceControlPoint(const TGattSpeedAndCadenceControlPointOpCode AOpcode, const unsigned ACumulativeValue, const TSCCumulativeValueType ValueType)/* overload */;
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattSpeedAndCadenceControlPointOpCode RequestOpcode = {read=GetRequestOpcode};
	__property TGattSpeedAndCadenceSensorLocation SensorLocation = {read=GetSensorLocation};
	__property unsigned CumulativeValue = {read=GetCumulativeValue};
	__property TSCCumulativeValueType CumulativeValueType = {read=FCumulativeValueType};
	TGattSpeedAndCadenceControlPoint() {}
};


enum class DECLSPEC_DENUM TGattSpeedAndCadenceResponseValue : unsigned char { Success = 1, OpcodeNotSupported, InvalidParameter, OperationFailed };

struct DECLSPEC_DRECORD TGattSpeedAndCadenceResponseCode
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattSpeedAndCadenceControlPointOpCode __fastcall GetRequestCode();
	TGattSpeedAndCadenceResponseValue __fastcall GetResponseValue();
	System::TArray__1<System::Byte> __fastcall GetResponseParameter();
	
public:
	__fastcall TGattSpeedAndCadenceResponseCode(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattSpeedAndCadenceControlPointOpCode RequestCode = {read=GetRequestCode};
	__property TGattSpeedAndCadenceResponseValue ResponseValue = {read=GetResponseValue};
	__property System::TArray__1<System::Byte> ResponseParameter = {read=GetResponseParameter};
	TGattSpeedAndCadenceResponseCode() {}
};


enum class DECLSPEC_DENUM TGattBodySensorLocation: char { Unread = -1, Other, Chest, Wrist, Finger, Hand, EarLobe, Foot };

enum class DECLSPEC_DENUM TGattTemperatureUnits : unsigned char { Celsius, Fahrenheit };

enum class DECLSPEC_DENUM TGattTemperatureType: char { Unread = -1, Armpit = 1, Body, Ear, Finger, GITract, Mouth, Rectum, Toe, Tympanum };

struct DECLSPEC_DRECORD TGattTemperatureMeasurement
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattTemperatureUnits __fastcall GetTemperatureUnits();
	bool __fastcall GetTimeStampPresent();
	bool __fastcall GetTemperatureTypePresent();
	float __fastcall GetTemperatureMeasurement();
	System::TDateTime __fastcall GetTimeStamp();
	TGattTemperatureType __fastcall GetTemperatureLocation();
	
public:
	__fastcall TGattTemperatureMeasurement(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattTemperatureUnits TemperatureUnits = {read=GetTemperatureUnits};
	__property bool TimeStampPresent = {read=GetTimeStampPresent};
	__property bool TemperatureTypePresent = {read=GetTemperatureTypePresent};
	__property float TemperatureMeasurement = {read=GetTemperatureMeasurement};
	__property System::TDateTime TimeStamp = {read=GetTimeStamp};
	__property TGattTemperatureType TemperatureLocation = {read=GetTemperatureLocation};
	TGattTemperatureMeasurement() {}
};


enum class DECLSPEC_DENUM TGattBloodPressureUnits : unsigned char { mmHg, kPa };

enum class DECLSPEC_DENUM TGattBloodPressurePulseRateRange : unsigned char { WithinRange, ExceedsHighLimit, ExceedsLowLimit };

struct DECLSPEC_DRECORD TGattBloodPressureMeasurement
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattBloodPressureUnits __fastcall GetBloodPressureUnits();
	bool __fastcall GetBloodPressureTimeStampPresent();
	bool __fastcall GetBloodPressurePulseRatePresent();
	bool __fastcall GetBloodPressureUserIdPresent();
	bool __fastcall GetBloodPressureMeasurementStatusPresent();
	bool __fastcall GetTestStatusPresent();
	float __fastcall GetBloodPressureMeasurement();
	float __fastcall GetBloodPressureMeasurementSystolic();
	float __fastcall GetBloodPressureMeasurementDiastolic();
	float __fastcall GetBloodPressureMeasurementMAP();
	float __fastcall GetPulseRate();
	System::Word __fastcall GetUserId();
	System::Word __fastcall GetMeasurementStatus();
	System::Word __fastcall GetBytesCount();
	bool __fastcall GetMeasurementStatusBodyMovement();
	bool __fastcall GetMeasurementStatusCuffTooLoose();
	bool __fastcall GetMeasurementStatusIrregularPulse();
	TGattBloodPressurePulseRateRange __fastcall GetMeasurementStatusPulseRateRange();
	bool __fastcall GetMeasurementStatusImproperPosition();
	System::TDateTime __fastcall GetTimeStamp();
	
public:
	__fastcall TGattBloodPressureMeasurement(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattBloodPressureUnits BloodPressureUnits = {read=GetBloodPressureUnits};
	__property bool BloodPressureTimeStampPresent = {read=GetBloodPressureTimeStampPresent};
	__property bool BloodPressurePulseRatePresent = {read=GetBloodPressurePulseRatePresent};
	__property bool BloodPressureUserIdPresent = {read=GetBloodPressureUserIdPresent};
	__property bool BloodPressureMeasurementStatusPresent = {read=GetBloodPressureMeasurementStatusPresent};
	__property float BloodPressureMeasurementSystolic = {read=GetBloodPressureMeasurementSystolic};
	__property float BloodPressureMeasurementDiastolic = {read=GetBloodPressureMeasurementDiastolic};
	__property float BloodPressureMeasurementMAP = {read=GetBloodPressureMeasurementMAP};
	__property float PulseRate = {read=GetPulseRate};
	__property System::Word UserId = {read=GetUserId};
	__property System::Word MeasurementStatus = {read=GetMeasurementStatus};
	__property float BloodPressureMeasurement = {read=GetBloodPressureMeasurement};
	__property System::Word DataBytesCount = {read=GetBytesCount};
	__property bool BodyMovementDetected = {read=GetMeasurementStatusBodyMovement};
	__property bool CuffFitTooLoose = {read=GetMeasurementStatusCuffTooLoose};
	__property bool IrregularPulseDetected = {read=GetMeasurementStatusIrregularPulse};
	__property TGattBloodPressurePulseRateRange PulseRateRange = {read=GetMeasurementStatusPulseRateRange};
	__property bool ImproperMeasurementPositionDetected = {read=GetMeasurementStatusImproperPosition};
	__property System::TDateTime TimeStamp = {read=GetTimeStamp};
	__property bool TestStatusPresent = {read=GetTestStatusPresent};
	TGattBloodPressureMeasurement() {}
};


struct DECLSPEC_DRECORD TGattIntermediateCuffPressure
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	TGattBloodPressureUnits __fastcall GetCuffPressureUnits();
	bool __fastcall GetCuffPressureTimeStampPresent();
	bool __fastcall GetCuffPressurePulseRatePresent();
	bool __fastcall GetCuffPressureUserIdPresent();
	bool __fastcall GetCuffPressureMeasurementStatusPresent();
	bool __fastcall GetTestStatusPresent();
	float __fastcall GetCuffPressureMeasurement();
	float __fastcall GetCurrentCuffPressure();
	float __fastcall GetPulseRate();
	System::Word __fastcall GetUserId();
	System::Word __fastcall GetMeasurementStatus();
	System::Word __fastcall GetBytesCount();
	bool __fastcall GetMeasurementStatusBodyMovement();
	bool __fastcall GetMeasurementStatusCuffTooLoose();
	bool __fastcall GetMeasurementStatusIrregularPulse();
	TGattBloodPressurePulseRateRange __fastcall GetMeasurementStatusPulseRateRange();
	bool __fastcall GetMeasurementStatusImproperPosition();
	System::TDateTime __fastcall GetTimeStamp();
	
public:
	__fastcall TGattIntermediateCuffPressure(const System::TArray__1<System::Byte> AValue);
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property TGattBloodPressureUnits CuffPressureUnits = {read=GetCuffPressureUnits};
	__property bool CuffPressureTimeStampPresent = {read=GetCuffPressureTimeStampPresent};
	__property bool CuffPressurePulseRatePresent = {read=GetCuffPressurePulseRatePresent};
	__property bool CuffPressureUserIdPresent = {read=GetCuffPressureUserIdPresent};
	__property bool CuffPressureMeasurementStatusPresent = {read=GetCuffPressureMeasurementStatusPresent};
	__property float CuffCurrentPressure = {read=GetCurrentCuffPressure};
	__property float PulseRate = {read=GetPulseRate};
	__property System::Word UserId = {read=GetUserId};
	__property System::Word MeasurementStatus = {read=GetMeasurementStatus};
	__property float CuffPressureMeasurement = {read=GetCuffPressureMeasurement};
	__property System::Word DataBytesCount = {read=GetBytesCount};
	__property bool BodyMovementDetected = {read=GetMeasurementStatusBodyMovement};
	__property bool CuffFitTooLoose = {read=GetMeasurementStatusCuffTooLoose};
	__property bool IrregularPulseDetected = {read=GetMeasurementStatusIrregularPulse};
	__property TGattBloodPressurePulseRateRange PulseRateRange = {read=GetMeasurementStatusPulseRateRange};
	__property bool ImproperMeasurementPositionDetected = {read=GetMeasurementStatusImproperPosition};
	__property System::TDateTime TimeStamp = {read=GetTimeStamp};
	__property bool TestStatusPresent = {read=GetTestStatusPresent};
	TGattIntermediateCuffPressure() {}
};


struct DECLSPEC_DRECORD TGattBloodPressureFeature
{
private:
	System::Word FValue;
	bool __fastcall GetBodyMovementDetectionStatus();
	bool __fastcall GetCuffFitDetectionStatus();
	bool __fastcall GetIrregularPulseDetectionStatus();
	bool __fastcall GetPulseRateRangeDetectionStatus();
	bool __fastcall GetMeasurementPositionDetectionStatus();
	bool __fastcall GetMultipleBondStatus();
	
public:
	__fastcall TGattBloodPressureFeature(const System::Word AValue);
	__property System::Word Value = {read=FValue};
	__property bool BodyMovementDetection = {read=GetBodyMovementDetectionStatus};
	__property bool CuffFitDetection = {read=GetCuffFitDetectionStatus};
	__property bool IrregularPulseDetection = {read=GetIrregularPulseDetectionStatus};
	__property bool PulseRateRangeDetection = {read=GetPulseRateRangeDetectionStatus};
	__property bool MeasurementPositionDetection = {read=GetMeasurementPositionDetectionStatus};
	__property bool MultipleBond = {read=GetMultipleBondStatus};
	TGattBloodPressureFeature() {}
};


struct DECLSPEC_DRECORD TGattDateTime
{
private:
	int FReserved1;
	System::TArray__1<System::Byte> FValue;
	System::TDateTime __fastcall GetTimeStamp();
	
public:
	__fastcall TGattDateTime(const System::TArray__1<System::Byte> AValue)/* overload */;
	__fastcall TGattDateTime(const System::TDateTime ATime)/* overload */;
	__property System::TArray__1<System::Byte> Value = {read=FValue};
	__property System::TDateTime TimeStamp = {read=GetTimeStamp};
	TGattDateTime() {}
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gatttypes */
}	/* namespace Bluetoothle */
}	/* namespace Family */
}	/* namespace Iot */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY_BLUETOOTHLE_GATTTYPES)
using namespace Iot::Family::Bluetoothle::Gatttypes;
#endif
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
#endif	// Iot_Family_Bluetoothle_GatttypesHPP
