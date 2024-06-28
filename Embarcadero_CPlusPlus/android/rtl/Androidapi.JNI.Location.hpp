// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Location.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_LocationHPP
#define Androidapi_Jni_LocationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
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
namespace Location
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAddressClass;
typedef System::DelphiInterface<JAddressClass> _di_JAddressClass;
__interface DELPHIINTERFACE JAddress;
typedef System::DelphiInterface<JAddress> _di_JAddress;
class DELPHICLASS TJAddress;
__interface DELPHIINTERFACE JCriteriaClass;
typedef System::DelphiInterface<JCriteriaClass> _di_JCriteriaClass;
__interface DELPHIINTERFACE JCriteria;
typedef System::DelphiInterface<JCriteria> _di_JCriteria;
class DELPHICLASS TJCriteria;
__interface DELPHIINTERFACE JGeocoderClass;
typedef System::DelphiInterface<JGeocoderClass> _di_JGeocoderClass;
__interface DELPHIINTERFACE JGeocoder;
typedef System::DelphiInterface<JGeocoder> _di_JGeocoder;
class DELPHICLASS TJGeocoder;
__interface DELPHIINTERFACE JGnssClockClass;
typedef System::DelphiInterface<JGnssClockClass> _di_JGnssClockClass;
__interface DELPHIINTERFACE JGnssClock;
typedef System::DelphiInterface<JGnssClock> _di_JGnssClock;
class DELPHICLASS TJGnssClock;
__interface DELPHIINTERFACE JGnssMeasurementClass;
typedef System::DelphiInterface<JGnssMeasurementClass> _di_JGnssMeasurementClass;
__interface DELPHIINTERFACE JGnssMeasurement;
typedef System::DelphiInterface<JGnssMeasurement> _di_JGnssMeasurement;
class DELPHICLASS TJGnssMeasurement;
__interface DELPHIINTERFACE JGnssMeasurementsEventClass;
typedef System::DelphiInterface<JGnssMeasurementsEventClass> _di_JGnssMeasurementsEventClass;
__interface DELPHIINTERFACE JGnssMeasurementsEvent;
typedef System::DelphiInterface<JGnssMeasurementsEvent> _di_JGnssMeasurementsEvent;
class DELPHICLASS TJGnssMeasurementsEvent;
__interface DELPHIINTERFACE JGnssMeasurementsEvent_CallbackClass;
typedef System::DelphiInterface<JGnssMeasurementsEvent_CallbackClass> _di_JGnssMeasurementsEvent_CallbackClass;
__interface DELPHIINTERFACE JGnssMeasurementsEvent_Callback;
typedef System::DelphiInterface<JGnssMeasurementsEvent_Callback> _di_JGnssMeasurementsEvent_Callback;
class DELPHICLASS TJGnssMeasurementsEvent_Callback;
__interface DELPHIINTERFACE JGnssNavigationMessageClass;
typedef System::DelphiInterface<JGnssNavigationMessageClass> _di_JGnssNavigationMessageClass;
__interface DELPHIINTERFACE JGnssNavigationMessage;
typedef System::DelphiInterface<JGnssNavigationMessage> _di_JGnssNavigationMessage;
class DELPHICLASS TJGnssNavigationMessage;
__interface DELPHIINTERFACE JGnssNavigationMessage_CallbackClass;
typedef System::DelphiInterface<JGnssNavigationMessage_CallbackClass> _di_JGnssNavigationMessage_CallbackClass;
__interface DELPHIINTERFACE JGnssNavigationMessage_Callback;
typedef System::DelphiInterface<JGnssNavigationMessage_Callback> _di_JGnssNavigationMessage_Callback;
class DELPHICLASS TJGnssNavigationMessage_Callback;
__interface DELPHIINTERFACE JGnssStatusClass;
typedef System::DelphiInterface<JGnssStatusClass> _di_JGnssStatusClass;
__interface DELPHIINTERFACE JGnssStatus;
typedef System::DelphiInterface<JGnssStatus> _di_JGnssStatus;
class DELPHICLASS TJGnssStatus;
__interface DELPHIINTERFACE JGnssStatus_CallbackClass;
typedef System::DelphiInterface<JGnssStatus_CallbackClass> _di_JGnssStatus_CallbackClass;
__interface DELPHIINTERFACE JGnssStatus_Callback;
typedef System::DelphiInterface<JGnssStatus_Callback> _di_JGnssStatus_Callback;
class DELPHICLASS TJGnssStatus_Callback;
__interface DELPHIINTERFACE JGpsSatelliteClass;
typedef System::DelphiInterface<JGpsSatelliteClass> _di_JGpsSatelliteClass;
__interface DELPHIINTERFACE JGpsSatellite;
typedef System::DelphiInterface<JGpsSatellite> _di_JGpsSatellite;
class DELPHICLASS TJGpsSatellite;
__interface DELPHIINTERFACE JGpsStatusClass;
typedef System::DelphiInterface<JGpsStatusClass> _di_JGpsStatusClass;
__interface DELPHIINTERFACE JGpsStatus;
typedef System::DelphiInterface<JGpsStatus> _di_JGpsStatus;
class DELPHICLASS TJGpsStatus;
__interface DELPHIINTERFACE JGpsStatus_ListenerClass;
typedef System::DelphiInterface<JGpsStatus_ListenerClass> _di_JGpsStatus_ListenerClass;
__interface DELPHIINTERFACE JGpsStatus_Listener;
typedef System::DelphiInterface<JGpsStatus_Listener> _di_JGpsStatus_Listener;
class DELPHICLASS TJGpsStatus_Listener;
__interface DELPHIINTERFACE JGpsStatus_NmeaListenerClass;
typedef System::DelphiInterface<JGpsStatus_NmeaListenerClass> _di_JGpsStatus_NmeaListenerClass;
__interface DELPHIINTERFACE JGpsStatus_NmeaListener;
typedef System::DelphiInterface<JGpsStatus_NmeaListener> _di_JGpsStatus_NmeaListener;
class DELPHICLASS TJGpsStatus_NmeaListener;
__interface DELPHIINTERFACE JLocationClass;
typedef System::DelphiInterface<JLocationClass> _di_JLocationClass;
__interface DELPHIINTERFACE JLocation;
typedef System::DelphiInterface<JLocation> _di_JLocation;
class DELPHICLASS TJLocation;
__interface DELPHIINTERFACE JLocationListenerClass;
typedef System::DelphiInterface<JLocationListenerClass> _di_JLocationListenerClass;
__interface DELPHIINTERFACE JLocationListener;
typedef System::DelphiInterface<JLocationListener> _di_JLocationListener;
class DELPHICLASS TJLocationListener;
__interface DELPHIINTERFACE JLocationManagerClass;
typedef System::DelphiInterface<JLocationManagerClass> _di_JLocationManagerClass;
__interface DELPHIINTERFACE JLocationManager;
typedef System::DelphiInterface<JLocationManager> _di_JLocationManager;
class DELPHICLASS TJLocationManager;
__interface DELPHIINTERFACE JLocationProviderClass;
typedef System::DelphiInterface<JLocationProviderClass> _di_JLocationProviderClass;
__interface DELPHIINTERFACE JLocationProvider;
typedef System::DelphiInterface<JLocationProvider> _di_JLocationProvider;
class DELPHICLASS TJLocationProvider;
__interface DELPHIINTERFACE JOnNmeaMessageListenerClass;
typedef System::DelphiInterface<JOnNmeaMessageListenerClass> _di_JOnNmeaMessageListenerClass;
__interface DELPHIINTERFACE JOnNmeaMessageListener;
typedef System::DelphiInterface<JOnNmeaMessageListener> _di_JOnNmeaMessageListener;
class DELPHICLASS TJOnNmeaMessageListener;
__interface DELPHIINTERFACE JSettingInjectorServiceClass;
typedef System::DelphiInterface<JSettingInjectorServiceClass> _di_JSettingInjectorServiceClass;
__interface DELPHIINTERFACE JSettingInjectorService;
typedef System::DelphiInterface<JSettingInjectorService> _di_JSettingInjectorService;
class DELPHICLASS TJSettingInjectorService;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{11E2A62D-94CD-4C84-9BAB-651BDB8AD89F}") JAddressClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAddress __cdecl init(Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{BEDE6B0A-3FCA-4A73-BC74-0FB86CE8E02F}") JAddress  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl clearLatitude() = 0 ;
	virtual void __cdecl clearLongitude() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAddressLine(int index) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdminArea() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCountryCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCountryName() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFeatureName() = 0 ;
	virtual double __cdecl getLatitude() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getLocale() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLocality() = 0 ;
	virtual double __cdecl getLongitude() = 0 ;
	virtual int __cdecl getMaxAddressLineIndex() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPhone() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPostalCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPremises() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSubAdminArea() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSubLocality() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSubThoroughfare() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getThoroughfare() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUrl() = 0 ;
	virtual bool __cdecl hasLatitude() = 0 ;
	virtual bool __cdecl hasLongitude() = 0 ;
	virtual void __cdecl setAddressLine(int index, Androidapi::Jni::Javatypes::_di_JString line) = 0 ;
	virtual void __cdecl setAdminArea(Androidapi::Jni::Javatypes::_di_JString adminArea) = 0 ;
	virtual void __cdecl setCountryCode(Androidapi::Jni::Javatypes::_di_JString countryCode) = 0 ;
	virtual void __cdecl setCountryName(Androidapi::Jni::Javatypes::_di_JString countryName) = 0 ;
	virtual void __cdecl setExtras(Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual void __cdecl setFeatureName(Androidapi::Jni::Javatypes::_di_JString featureName) = 0 ;
	virtual void __cdecl setLatitude(double latitude) = 0 ;
	virtual void __cdecl setLocality(Androidapi::Jni::Javatypes::_di_JString locality) = 0 ;
	virtual void __cdecl setLongitude(double longitude) = 0 ;
	virtual void __cdecl setPhone(Androidapi::Jni::Javatypes::_di_JString phone) = 0 ;
	virtual void __cdecl setPostalCode(Androidapi::Jni::Javatypes::_di_JString postalCode) = 0 ;
	virtual void __cdecl setPremises(Androidapi::Jni::Javatypes::_di_JString premises) = 0 ;
	virtual void __cdecl setSubAdminArea(Androidapi::Jni::Javatypes::_di_JString subAdminArea) = 0 ;
	virtual void __cdecl setSubLocality(Androidapi::Jni::Javatypes::_di_JString sublocality) = 0 ;
	virtual void __cdecl setSubThoroughfare(Androidapi::Jni::Javatypes::_di_JString subthoroughfare) = 0 ;
	virtual void __cdecl setThoroughfare(Androidapi::Jni::Javatypes::_di_JString thoroughfare) = 0 ;
	virtual void __cdecl setUrl(Androidapi::Jni::Javatypes::_di_JString Url) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAddress : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressClass,_di_JAddress>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressClass,_di_JAddress> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAddress() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressClass,_di_JAddress>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5A00B9BC-1915-4D8F-A077-CED7234A64D1}") JCriteriaClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetACCURACY_COARSE() = 0 ;
	virtual int __cdecl _GetACCURACY_FINE() = 0 ;
	virtual int __cdecl _GetACCURACY_HIGH() = 0 ;
	virtual int __cdecl _GetACCURACY_LOW() = 0 ;
	virtual int __cdecl _GetACCURACY_MEDIUM() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetNO_REQUIREMENT() = 0 ;
	virtual int __cdecl _GetPOWER_HIGH() = 0 ;
	virtual int __cdecl _GetPOWER_LOW() = 0 ;
	virtual int __cdecl _GetPOWER_MEDIUM() = 0 ;
	HIDESBASE virtual _di_JCriteria __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JCriteria __cdecl init(_di_JCriteria criteria) = 0 /* overload */;
	__property int ACCURACY_COARSE = {read=_GetACCURACY_COARSE};
	__property int ACCURACY_FINE = {read=_GetACCURACY_FINE};
	__property int ACCURACY_HIGH = {read=_GetACCURACY_HIGH};
	__property int ACCURACY_LOW = {read=_GetACCURACY_LOW};
	__property int ACCURACY_MEDIUM = {read=_GetACCURACY_MEDIUM};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int NO_REQUIREMENT = {read=_GetNO_REQUIREMENT};
	__property int POWER_HIGH = {read=_GetPOWER_HIGH};
	__property int POWER_LOW = {read=_GetPOWER_LOW};
	__property int POWER_MEDIUM = {read=_GetPOWER_MEDIUM};
};

__interface  INTERFACE_UUID("{105327BB-E655-4565-BCB8-796CB73B811C}") JCriteria  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getAccuracy() = 0 ;
	virtual int __cdecl getBearingAccuracy() = 0 ;
	virtual int __cdecl getHorizontalAccuracy() = 0 ;
	virtual int __cdecl getPowerRequirement() = 0 ;
	virtual int __cdecl getSpeedAccuracy() = 0 ;
	virtual int __cdecl getVerticalAccuracy() = 0 ;
	virtual bool __cdecl isAltitudeRequired() = 0 ;
	virtual bool __cdecl isBearingRequired() = 0 ;
	virtual bool __cdecl isCostAllowed() = 0 ;
	virtual bool __cdecl isSpeedRequired() = 0 ;
	virtual void __cdecl setAccuracy(int accuracy) = 0 ;
	virtual void __cdecl setAltitudeRequired(bool altitudeRequired) = 0 ;
	virtual void __cdecl setBearingAccuracy(int accuracy) = 0 ;
	virtual void __cdecl setBearingRequired(bool bearingRequired) = 0 ;
	virtual void __cdecl setCostAllowed(bool costAllowed) = 0 ;
	virtual void __cdecl setHorizontalAccuracy(int accuracy) = 0 ;
	virtual void __cdecl setPowerRequirement(int level) = 0 ;
	virtual void __cdecl setSpeedAccuracy(int accuracy) = 0 ;
	virtual void __cdecl setSpeedRequired(bool speedRequired) = 0 ;
	virtual void __cdecl setVerticalAccuracy(int accuracy) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCriteria : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCriteriaClass,_di_JCriteria>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCriteriaClass,_di_JCriteria> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCriteria() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCriteriaClass,_di_JCriteria>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCriteria() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A21F3CB7-F053-464B-B59B-EDD0E4C784F2}") JGeocoderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JGeocoder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 /* overload */;
	HIDESBASE virtual _di_JGeocoder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual bool __cdecl isPresent() = 0 ;
};

__interface  INTERFACE_UUID("{32343023-DA3D-41DE-9A9A-69935156D5B7}") JGeocoder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFromLocation(double latitude, double longitude, int maxResults) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFromLocationName(Androidapi::Jni::Javatypes::_di_JString locationName, int maxResults) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFromLocationName(Androidapi::Jni::Javatypes::_di_JString locationName, int maxResults, double lowerLeftLatitude, double lowerLeftLongitude, double upperRightLatitude, double upperRightLongitude) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGeocoder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeocoderClass,_di_JGeocoder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeocoderClass,_di_JGeocoder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGeocoder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeocoderClass,_di_JGeocoder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGeocoder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{09A9B58E-63C4-4283-B712-4FF9D704FA66}") JGnssClockClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{97181DBA-438C-4C89-816B-A8BC0B430941}") JGnssClock  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual double __cdecl getBiasNanos() = 0 ;
	virtual double __cdecl getBiasUncertaintyNanos() = 0 ;
	virtual double __cdecl getDriftNanosPerSecond() = 0 ;
	virtual double __cdecl getDriftUncertaintyNanosPerSecond() = 0 ;
	virtual __int64 __cdecl getFullBiasNanos() = 0 ;
	virtual int __cdecl getHardwareClockDiscontinuityCount() = 0 ;
	virtual int __cdecl getLeapSecond() = 0 ;
	virtual __int64 __cdecl getTimeNanos() = 0 ;
	virtual double __cdecl getTimeUncertaintyNanos() = 0 ;
	virtual bool __cdecl hasBiasNanos() = 0 ;
	virtual bool __cdecl hasBiasUncertaintyNanos() = 0 ;
	virtual bool __cdecl hasDriftNanosPerSecond() = 0 ;
	virtual bool __cdecl hasDriftUncertaintyNanosPerSecond() = 0 ;
	virtual bool __cdecl hasFullBiasNanos() = 0 ;
	virtual bool __cdecl hasLeapSecond() = 0 ;
	virtual bool __cdecl hasTimeUncertaintyNanos() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssClock : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssClockClass,_di_JGnssClock>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssClockClass,_di_JGnssClock> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssClock() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssClockClass,_di_JGnssClock>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssClock() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9AFBF9A0-9DE6-4F98-8FBF-5DC142693ECA}") JGnssMeasurementClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetADR_STATE_CYCLE_SLIP() = 0 ;
	virtual int __cdecl _GetADR_STATE_RESET() = 0 ;
	virtual int __cdecl _GetADR_STATE_UNKNOWN() = 0 ;
	virtual int __cdecl _GetADR_STATE_VALID() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetMULTIPATH_INDICATOR_DETECTED() = 0 ;
	virtual int __cdecl _GetMULTIPATH_INDICATOR_NOT_DETECTED() = 0 ;
	virtual int __cdecl _GetMULTIPATH_INDICATOR_UNKNOWN() = 0 ;
	virtual int __cdecl _GetSTATE_BDS_D2_BIT_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_BDS_D2_SUBFRAME_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_BIT_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_CODE_LOCK() = 0 ;
	virtual int __cdecl _GetSTATE_GAL_E1BC_CODE_LOCK() = 0 ;
	virtual int __cdecl _GetSTATE_GAL_E1B_PAGE_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_GAL_E1C_2ND_CODE_LOCK() = 0 ;
	virtual int __cdecl _GetSTATE_GLO_STRING_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_GLO_TOD_DECODED() = 0 ;
	virtual int __cdecl _GetSTATE_GLO_TOD_KNOWN() = 0 ;
	virtual int __cdecl _GetSTATE_MSEC_AMBIGUOUS() = 0 ;
	virtual int __cdecl _GetSTATE_SBAS_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_SUBFRAME_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_SYMBOL_SYNC() = 0 ;
	virtual int __cdecl _GetSTATE_TOW_DECODED() = 0 ;
	virtual int __cdecl _GetSTATE_TOW_KNOWN() = 0 ;
	virtual int __cdecl _GetSTATE_UNKNOWN() = 0 ;
	__property int ADR_STATE_CYCLE_SLIP = {read=_GetADR_STATE_CYCLE_SLIP};
	__property int ADR_STATE_RESET = {read=_GetADR_STATE_RESET};
	__property int ADR_STATE_UNKNOWN = {read=_GetADR_STATE_UNKNOWN};
	__property int ADR_STATE_VALID = {read=_GetADR_STATE_VALID};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int MULTIPATH_INDICATOR_DETECTED = {read=_GetMULTIPATH_INDICATOR_DETECTED};
	__property int MULTIPATH_INDICATOR_NOT_DETECTED = {read=_GetMULTIPATH_INDICATOR_NOT_DETECTED};
	__property int MULTIPATH_INDICATOR_UNKNOWN = {read=_GetMULTIPATH_INDICATOR_UNKNOWN};
	__property int STATE_BDS_D2_BIT_SYNC = {read=_GetSTATE_BDS_D2_BIT_SYNC};
	__property int STATE_BDS_D2_SUBFRAME_SYNC = {read=_GetSTATE_BDS_D2_SUBFRAME_SYNC};
	__property int STATE_BIT_SYNC = {read=_GetSTATE_BIT_SYNC};
	__property int STATE_CODE_LOCK = {read=_GetSTATE_CODE_LOCK};
	__property int STATE_GAL_E1BC_CODE_LOCK = {read=_GetSTATE_GAL_E1BC_CODE_LOCK};
	__property int STATE_GAL_E1B_PAGE_SYNC = {read=_GetSTATE_GAL_E1B_PAGE_SYNC};
	__property int STATE_GAL_E1C_2ND_CODE_LOCK = {read=_GetSTATE_GAL_E1C_2ND_CODE_LOCK};
	__property int STATE_GLO_STRING_SYNC = {read=_GetSTATE_GLO_STRING_SYNC};
	__property int STATE_GLO_TOD_DECODED = {read=_GetSTATE_GLO_TOD_DECODED};
	__property int STATE_GLO_TOD_KNOWN = {read=_GetSTATE_GLO_TOD_KNOWN};
	__property int STATE_MSEC_AMBIGUOUS = {read=_GetSTATE_MSEC_AMBIGUOUS};
	__property int STATE_SBAS_SYNC = {read=_GetSTATE_SBAS_SYNC};
	__property int STATE_SUBFRAME_SYNC = {read=_GetSTATE_SUBFRAME_SYNC};
	__property int STATE_SYMBOL_SYNC = {read=_GetSTATE_SYMBOL_SYNC};
	__property int STATE_TOW_DECODED = {read=_GetSTATE_TOW_DECODED};
	__property int STATE_TOW_KNOWN = {read=_GetSTATE_TOW_KNOWN};
	__property int STATE_UNKNOWN = {read=_GetSTATE_UNKNOWN};
};

__interface  INTERFACE_UUID("{B4FCE543-B01C-4CD6-836F-A4C4D3DC781A}") JGnssMeasurement  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual double __cdecl getAccumulatedDeltaRangeMeters() = 0 ;
	virtual int __cdecl getAccumulatedDeltaRangeState() = 0 ;
	virtual double __cdecl getAccumulatedDeltaRangeUncertaintyMeters() = 0 ;
	virtual double __cdecl getAutomaticGainControlLevelDb() = 0 ;
	virtual __int64 __cdecl getCarrierCycles() = 0 ;
	virtual float __cdecl getCarrierFrequencyHz() = 0 ;
	virtual double __cdecl getCarrierPhase() = 0 ;
	virtual double __cdecl getCarrierPhaseUncertainty() = 0 ;
	virtual double __cdecl getCn0DbHz() = 0 ;
	virtual int __cdecl getConstellationType() = 0 ;
	virtual int __cdecl getMultipathIndicator() = 0 ;
	virtual double __cdecl getPseudorangeRateMetersPerSecond() = 0 ;
	virtual double __cdecl getPseudorangeRateUncertaintyMetersPerSecond() = 0 ;
	virtual __int64 __cdecl getReceivedSvTimeNanos() = 0 ;
	virtual __int64 __cdecl getReceivedSvTimeUncertaintyNanos() = 0 ;
	virtual double __cdecl getSnrInDb() = 0 ;
	virtual int __cdecl getState() = 0 ;
	virtual int __cdecl getSvid() = 0 ;
	virtual double __cdecl getTimeOffsetNanos() = 0 ;
	virtual bool __cdecl hasAutomaticGainControlLevelDb() = 0 ;
	virtual bool __cdecl hasCarrierCycles() = 0 ;
	virtual bool __cdecl hasCarrierFrequencyHz() = 0 ;
	virtual bool __cdecl hasCarrierPhase() = 0 ;
	virtual bool __cdecl hasCarrierPhaseUncertainty() = 0 ;
	virtual bool __cdecl hasSnrInDb() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssMeasurement : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementClass,_di_JGnssMeasurement>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementClass,_di_JGnssMeasurement> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssMeasurement() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementClass,_di_JGnssMeasurement>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssMeasurement() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FFAD31A3-2C5C-4294-9F8E-68DBF2C45D0C}") JGnssMeasurementsEventClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{7ACE27AB-CD55-412D-B025-70B97FE3BED3}") JGnssMeasurementsEvent  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual _di_JGnssClock __cdecl getClock() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCollection __cdecl getMeasurements() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssMeasurementsEvent : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEventClass,_di_JGnssMeasurementsEvent>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEventClass,_di_JGnssMeasurementsEvent> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssMeasurementsEvent() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEventClass,_di_JGnssMeasurementsEvent>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssMeasurementsEvent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1AC5BF62-7467-4D9D-BAF9-AE3D1D426497}") JGnssMeasurementsEvent_CallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetSTATUS_LOCATION_DISABLED() = 0 ;
	virtual int __cdecl _GetSTATUS_NOT_SUPPORTED() = 0 ;
	virtual int __cdecl _GetSTATUS_READY() = 0 ;
	HIDESBASE virtual _di_JGnssMeasurementsEvent_Callback __cdecl init() = 0 ;
	__property int STATUS_LOCATION_DISABLED = {read=_GetSTATUS_LOCATION_DISABLED};
	__property int STATUS_NOT_SUPPORTED = {read=_GetSTATUS_NOT_SUPPORTED};
	__property int STATUS_READY = {read=_GetSTATUS_READY};
};

__interface  INTERFACE_UUID("{391AB985-9C6D-4447-8C2A-B0064DA37B5C}") JGnssMeasurementsEvent_Callback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onGnssMeasurementsReceived(_di_JGnssMeasurementsEvent eventArgs) = 0 ;
	virtual void __cdecl onStatusChanged(int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssMeasurementsEvent_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEvent_CallbackClass,_di_JGnssMeasurementsEvent_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEvent_CallbackClass,_di_JGnssMeasurementsEvent_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssMeasurementsEvent_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssMeasurementsEvent_CallbackClass,_di_JGnssMeasurementsEvent_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssMeasurementsEvent_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0522DC20-3E53-48E7-928F-30D296058D8A}") JGnssNavigationMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetSTATUS_PARITY_PASSED() = 0 ;
	virtual int __cdecl _GetSTATUS_PARITY_REBUILT() = 0 ;
	virtual int __cdecl _GetSTATUS_UNKNOWN() = 0 ;
	virtual int __cdecl _GetTYPE_BDS_D1() = 0 ;
	virtual int __cdecl _GetTYPE_BDS_D2() = 0 ;
	virtual int __cdecl _GetTYPE_GAL_F() = 0 ;
	virtual int __cdecl _GetTYPE_GAL_I() = 0 ;
	virtual int __cdecl _GetTYPE_GLO_L1CA() = 0 ;
	virtual int __cdecl _GetTYPE_GPS_CNAV2() = 0 ;
	virtual int __cdecl _GetTYPE_GPS_L1CA() = 0 ;
	virtual int __cdecl _GetTYPE_GPS_L2CNAV() = 0 ;
	virtual int __cdecl _GetTYPE_GPS_L5CNAV() = 0 ;
	virtual int __cdecl _GetTYPE_UNKNOWN() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int STATUS_PARITY_PASSED = {read=_GetSTATUS_PARITY_PASSED};
	__property int STATUS_PARITY_REBUILT = {read=_GetSTATUS_PARITY_REBUILT};
	__property int STATUS_UNKNOWN = {read=_GetSTATUS_UNKNOWN};
	__property int TYPE_BDS_D1 = {read=_GetTYPE_BDS_D1};
	__property int TYPE_BDS_D2 = {read=_GetTYPE_BDS_D2};
	__property int TYPE_GAL_F = {read=_GetTYPE_GAL_F};
	__property int TYPE_GAL_I = {read=_GetTYPE_GAL_I};
	__property int TYPE_GLO_L1CA = {read=_GetTYPE_GLO_L1CA};
	__property int TYPE_GPS_CNAV2 = {read=_GetTYPE_GPS_CNAV2};
	__property int TYPE_GPS_L1CA = {read=_GetTYPE_GPS_L1CA};
	__property int TYPE_GPS_L2CNAV = {read=_GetTYPE_GPS_L2CNAV};
	__property int TYPE_GPS_L5CNAV = {read=_GetTYPE_GPS_L5CNAV};
	__property int TYPE_UNKNOWN = {read=_GetTYPE_UNKNOWN};
};

__interface  INTERFACE_UUID("{1E4F01B7-72EE-41B4-8C4C-090CBE87DDBD}") JGnssNavigationMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getData() = 0 ;
	virtual int __cdecl getMessageId() = 0 ;
	virtual int __cdecl getStatus() = 0 ;
	virtual int __cdecl getSubmessageId() = 0 ;
	virtual int __cdecl getSvid() = 0 ;
	virtual int __cdecl getType() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssNavigationMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessageClass,_di_JGnssNavigationMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessageClass,_di_JGnssNavigationMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssNavigationMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessageClass,_di_JGnssNavigationMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssNavigationMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0180DD80-296E-4251-B279-DE2C905211AD}") JGnssNavigationMessage_CallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetSTATUS_LOCATION_DISABLED() = 0 ;
	virtual int __cdecl _GetSTATUS_NOT_SUPPORTED() = 0 ;
	virtual int __cdecl _GetSTATUS_READY() = 0 ;
	HIDESBASE virtual _di_JGnssNavigationMessage_Callback __cdecl init() = 0 ;
	__property int STATUS_LOCATION_DISABLED = {read=_GetSTATUS_LOCATION_DISABLED};
	__property int STATUS_NOT_SUPPORTED = {read=_GetSTATUS_NOT_SUPPORTED};
	__property int STATUS_READY = {read=_GetSTATUS_READY};
};

__interface  INTERFACE_UUID("{D79C0144-2BDA-4C7C-A917-08BA125D056F}") JGnssNavigationMessage_Callback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onGnssNavigationMessageReceived(_di_JGnssNavigationMessage event) = 0 ;
	virtual void __cdecl onStatusChanged(int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssNavigationMessage_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessage_CallbackClass,_di_JGnssNavigationMessage_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessage_CallbackClass,_di_JGnssNavigationMessage_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssNavigationMessage_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssNavigationMessage_CallbackClass,_di_JGnssNavigationMessage_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssNavigationMessage_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D36F2CE1-FD1E-4F86-8CB6-87B254273BFA}") JGnssStatusClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCONSTELLATION_BEIDOU() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_GALILEO() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_GLONASS() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_GPS() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_QZSS() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_SBAS() = 0 ;
	virtual int __cdecl _GetCONSTELLATION_UNKNOWN() = 0 ;
	__property int CONSTELLATION_BEIDOU = {read=_GetCONSTELLATION_BEIDOU};
	__property int CONSTELLATION_GALILEO = {read=_GetCONSTELLATION_GALILEO};
	__property int CONSTELLATION_GLONASS = {read=_GetCONSTELLATION_GLONASS};
	__property int CONSTELLATION_GPS = {read=_GetCONSTELLATION_GPS};
	__property int CONSTELLATION_QZSS = {read=_GetCONSTELLATION_QZSS};
	__property int CONSTELLATION_SBAS = {read=_GetCONSTELLATION_SBAS};
	__property int CONSTELLATION_UNKNOWN = {read=_GetCONSTELLATION_UNKNOWN};
};

__interface  INTERFACE_UUID("{7578D1B1-992E-4F52-B963-31559E825D5C}") JGnssStatus  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl getAzimuthDegrees(int satIndex) = 0 ;
	virtual float __cdecl getCarrierFrequencyHz(int satIndex) = 0 ;
	virtual float __cdecl getCn0DbHz(int satIndex) = 0 ;
	virtual int __cdecl getConstellationType(int satIndex) = 0 ;
	virtual float __cdecl getElevationDegrees(int satIndex) = 0 ;
	virtual int __cdecl getSatelliteCount() = 0 ;
	virtual int __cdecl getSvid(int satIndex) = 0 ;
	virtual bool __cdecl hasAlmanacData(int satIndex) = 0 ;
	virtual bool __cdecl hasCarrierFrequencyHz(int satIndex) = 0 ;
	virtual bool __cdecl hasEphemerisData(int satIndex) = 0 ;
	virtual bool __cdecl usedInFix(int satIndex) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssStatus : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatusClass,_di_JGnssStatus>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatusClass,_di_JGnssStatus> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssStatus() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatusClass,_di_JGnssStatus>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssStatus() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9EDE45E7-C6E4-4CCD-B587-13299E1D4E50}") JGnssStatus_CallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JGnssStatus_Callback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{1EFDADBF-4B94-4A50-8671-354EE671CFCB}") JGnssStatus_Callback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onFirstFix(int ttffMillis) = 0 ;
	virtual void __cdecl onSatelliteStatusChanged(_di_JGnssStatus status) = 0 ;
	virtual void __cdecl onStarted() = 0 ;
	virtual void __cdecl onStopped() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGnssStatus_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatus_CallbackClass,_di_JGnssStatus_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatus_CallbackClass,_di_JGnssStatus_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGnssStatus_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGnssStatus_CallbackClass,_di_JGnssStatus_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGnssStatus_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8B2B813E-3F20-40F5-AAFF-CA38016DBF99}") JGpsSatelliteClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{23BDBF98-46F8-46EE-93FB-07D1EB30C7F7}") JGpsSatellite  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl getAzimuth() = 0 ;
	virtual float __cdecl getElevation() = 0 ;
	virtual int __cdecl getPrn() = 0 ;
	virtual float __cdecl getSnr() = 0 ;
	virtual bool __cdecl hasAlmanac() = 0 ;
	virtual bool __cdecl hasEphemeris() = 0 ;
	virtual bool __cdecl usedInFix() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGpsSatellite : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsSatelliteClass,_di_JGpsSatellite>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsSatelliteClass,_di_JGpsSatellite> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGpsSatellite() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsSatelliteClass,_di_JGpsSatellite>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGpsSatellite() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{875EC1CA-A26D-41DD-83C3-4C361DE1EA50}") JGpsStatusClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetGPS_EVENT_FIRST_FIX() = 0 ;
	virtual int __cdecl _GetGPS_EVENT_SATELLITE_STATUS() = 0 ;
	virtual int __cdecl _GetGPS_EVENT_STARTED() = 0 ;
	virtual int __cdecl _GetGPS_EVENT_STOPPED() = 0 ;
	__property int GPS_EVENT_FIRST_FIX = {read=_GetGPS_EVENT_FIRST_FIX};
	__property int GPS_EVENT_SATELLITE_STATUS = {read=_GetGPS_EVENT_SATELLITE_STATUS};
	__property int GPS_EVENT_STARTED = {read=_GetGPS_EVENT_STARTED};
	__property int GPS_EVENT_STOPPED = {read=_GetGPS_EVENT_STOPPED};
};

__interface  INTERFACE_UUID("{6ED3905E-5FBC-4E7C-A363-10A07297FF5E}") JGpsStatus  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getMaxSatellites() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JIterable __cdecl getSatellites() = 0 ;
	virtual int __cdecl getTimeToFirstFix() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGpsStatus : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatusClass,_di_JGpsStatus>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatusClass,_di_JGpsStatus> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGpsStatus() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatusClass,_di_JGpsStatus>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGpsStatus() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1B4E4734-00D1-4DD8-856F-5B15E4BA31F3}") JGpsStatus_ListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{12C48E82-7BEA-4E6E-973D-95CD0B42B3FE}") JGpsStatus_Listener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onGpsStatusChanged(int event) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGpsStatus_Listener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_ListenerClass,_di_JGpsStatus_Listener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_ListenerClass,_di_JGpsStatus_Listener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGpsStatus_Listener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_ListenerClass,_di_JGpsStatus_Listener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGpsStatus_Listener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{19E69909-A8B8-4723-866A-49435EC8D942}") JGpsStatus_NmeaListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{7CEBB6D7-85A9-40EA-9360-BE3E6124336B}") JGpsStatus_NmeaListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onNmeaReceived(__int64 timestamp, Androidapi::Jni::Javatypes::_di_JString nmea) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGpsStatus_NmeaListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_NmeaListenerClass,_di_JGpsStatus_NmeaListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_NmeaListenerClass,_di_JGpsStatus_NmeaListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGpsStatus_NmeaListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGpsStatus_NmeaListenerClass,_di_JGpsStatus_NmeaListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGpsStatus_NmeaListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A0BF1527-8922-4124-94AC-D2361F1EF984}") JLocationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetFORMAT_DEGREES() = 0 ;
	virtual int __cdecl _GetFORMAT_MINUTES() = 0 ;
	virtual int __cdecl _GetFORMAT_SECONDS() = 0 ;
	HIDESBASE virtual _di_JLocation __cdecl init(Androidapi::Jni::Javatypes::_di_JString provider) = 0 /* overload */;
	HIDESBASE virtual _di_JLocation __cdecl init(_di_JLocation l) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl convert(double coordinate, int outputType) = 0 /* overload */;
	virtual double __cdecl convert(Androidapi::Jni::Javatypes::_di_JString coordinate) = 0 /* overload */;
	virtual void __cdecl distanceBetween(double startLatitude, double startLongitude, double endLatitude, double endLongitude, Androidapi::Jnibridge::TJavaArray__1<float>* results) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int FORMAT_DEGREES = {read=_GetFORMAT_DEGREES};
	__property int FORMAT_MINUTES = {read=_GetFORMAT_MINUTES};
	__property int FORMAT_SECONDS = {read=_GetFORMAT_SECONDS};
};

__interface  INTERFACE_UUID("{B6A7FB34-312C-41BC-B02D-0107E6F39395}") JLocation  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl bearingTo(_di_JLocation dest) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual float __cdecl distanceTo(_di_JLocation dest) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Util::_di_JPrinter pw, Androidapi::Jni::Javatypes::_di_JString prefix) = 0 ;
	virtual float __cdecl getAccuracy() = 0 ;
	virtual double __cdecl getAltitude() = 0 ;
	virtual float __cdecl getBearing() = 0 ;
	virtual float __cdecl getBearingAccuracyDegrees() = 0 ;
	virtual __int64 __cdecl getElapsedRealtimeNanos() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual double __cdecl getLatitude() = 0 ;
	virtual double __cdecl getLongitude() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProvider() = 0 ;
	virtual float __cdecl getSpeed() = 0 ;
	virtual float __cdecl getSpeedAccuracyMetersPerSecond() = 0 ;
	virtual __int64 __cdecl getTime() = 0 ;
	virtual float __cdecl getVerticalAccuracyMeters() = 0 ;
	virtual bool __cdecl hasAccuracy() = 0 ;
	virtual bool __cdecl hasAltitude() = 0 ;
	virtual bool __cdecl hasBearing() = 0 ;
	virtual bool __cdecl hasBearingAccuracy() = 0 ;
	virtual bool __cdecl hasSpeed() = 0 ;
	virtual bool __cdecl hasSpeedAccuracy() = 0 ;
	virtual bool __cdecl hasVerticalAccuracy() = 0 ;
	virtual bool __cdecl isFromMockProvider() = 0 ;
	virtual void __cdecl removeAccuracy() = 0 ;
	virtual void __cdecl removeAltitude() = 0 ;
	virtual void __cdecl removeBearing() = 0 ;
	virtual void __cdecl removeBearingAccuracy() = 0 ;
	virtual void __cdecl removeSpeed() = 0 ;
	virtual void __cdecl removeSpeedAccuracy() = 0 ;
	virtual void __cdecl removeVerticalAccuracy() = 0 ;
	virtual void __cdecl reset() = 0 ;
	virtual void __cdecl set(_di_JLocation l) = 0 ;
	virtual void __cdecl setAccuracy(float horizontalAccuracy) = 0 ;
	virtual void __cdecl setAltitude(double altitude) = 0 ;
	virtual void __cdecl setBearing(float bearing) = 0 ;
	virtual void __cdecl setBearingAccuracyDegrees(float bearingAccuracyDegrees) = 0 ;
	virtual void __cdecl setElapsedRealtimeNanos(__int64 time) = 0 ;
	virtual void __cdecl setExtras(Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual void __cdecl setLatitude(double latitude) = 0 ;
	virtual void __cdecl setLongitude(double longitude) = 0 ;
	virtual void __cdecl setProvider(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl setSpeed(float speed) = 0 ;
	virtual void __cdecl setSpeedAccuracyMetersPerSecond(float speedAccuracyMeterPerSecond) = 0 ;
	virtual void __cdecl setTime(__int64 time) = 0 ;
	virtual void __cdecl setVerticalAccuracyMeters(float verticalAccuracyMeters) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationClass,_di_JLocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationClass,_di_JLocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationClass,_di_JLocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C0D51209-3DC1-46D5-91C1-CC77097564DB}") JLocationListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D1CF3FB5-3BCB-4959-98D7-BD4D8F93D839}") JLocationListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onLocationChanged(_di_JLocation location) = 0 ;
	virtual void __cdecl onProviderDisabled(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl onProviderEnabled(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl onStatusChanged(Androidapi::Jni::Javatypes::_di_JString provider, int status, Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocationListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationListenerClass,_di_JLocationListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationListenerClass,_di_JLocationListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocationListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationListenerClass,_di_JLocationListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocationListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{031AE82C-2EEE-41E4-94F8-24C4D7059246}") JLocationManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGPS_PROVIDER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_LOCATION_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PROVIDER_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PROXIMITY_ENTERING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_STATUS_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMODE_CHANGED_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetNETWORK_PROVIDER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPASSIVE_PROVIDER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPROVIDERS_CHANGED_ACTION() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString GPS_PROVIDER = {read=_GetGPS_PROVIDER};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_LOCATION_CHANGED = {read=_GetKEY_LOCATION_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PROVIDER_ENABLED = {read=_GetKEY_PROVIDER_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PROXIMITY_ENTERING = {read=_GetKEY_PROXIMITY_ENTERING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_STATUS_CHANGED = {read=_GetKEY_STATUS_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString MODE_CHANGED_ACTION = {read=_GetMODE_CHANGED_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString NETWORK_PROVIDER = {read=_GetNETWORK_PROVIDER};
	__property Androidapi::Jni::Javatypes::_di_JString PASSIVE_PROVIDER = {read=_GetPASSIVE_PROVIDER};
	__property Androidapi::Jni::Javatypes::_di_JString PROVIDERS_CHANGED_ACTION = {read=_GetPROVIDERS_CHANGED_ACTION};
};

__interface  INTERFACE_UUID("{42C3E256-9370-43B5-93E3-EDF5CE51FB28}") JLocationManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl addGpsStatusListener(_di_JGpsStatus_Listener listener) = 0 ;
	virtual bool __cdecl addNmeaListener(_di_JGpsStatus_NmeaListener listener) = 0 /* overload */;
	virtual bool __cdecl addNmeaListener(_di_JOnNmeaMessageListener listener) = 0 /* overload */;
	virtual bool __cdecl addNmeaListener(_di_JOnNmeaMessageListener listener, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl addProximityAlert(double latitude, double longitude, float radius, __int64 expiration, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
	virtual void __cdecl addTestProvider(Androidapi::Jni::Javatypes::_di_JString name, bool requiresNetwork, bool requiresSatellite, bool requiresCell, bool hasMonetaryCost, bool supportsAltitude, bool supportsSpeed, bool supportsBearing, int powerRequirement, int accuracy) = 0 ;
	virtual void __cdecl clearTestProviderEnabled(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl clearTestProviderLocation(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl clearTestProviderStatus(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getAllProviders() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getBestProvider(_di_JCriteria criteria, bool enabledOnly) = 0 ;
	virtual _di_JGpsStatus __cdecl getGpsStatus(_di_JGpsStatus status) = 0 ;
	virtual _di_JLocation __cdecl getLastKnownLocation(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual _di_JLocationProvider __cdecl getProvider(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getProviders(bool enabledOnly) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getProviders(_di_JCriteria criteria, bool enabledOnly) = 0 /* overload */;
	virtual bool __cdecl isProviderEnabled(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual bool __cdecl registerGnssMeasurementsCallback(_di_JGnssMeasurementsEvent_Callback callback) = 0 /* overload */;
	virtual bool __cdecl registerGnssMeasurementsCallback(_di_JGnssMeasurementsEvent_Callback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual bool __cdecl registerGnssNavigationMessageCallback(_di_JGnssNavigationMessage_Callback callback) = 0 /* overload */;
	virtual bool __cdecl registerGnssNavigationMessageCallback(_di_JGnssNavigationMessage_Callback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual bool __cdecl registerGnssStatusCallback(_di_JGnssStatus_Callback callback) = 0 /* overload */;
	virtual bool __cdecl registerGnssStatusCallback(_di_JGnssStatus_Callback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl removeGpsStatusListener(_di_JGpsStatus_Listener listener) = 0 ;
	virtual void __cdecl removeNmeaListener(_di_JGpsStatus_NmeaListener listener) = 0 /* overload */;
	virtual void __cdecl removeNmeaListener(_di_JOnNmeaMessageListener listener) = 0 /* overload */;
	virtual void __cdecl removeProximityAlert(Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
	virtual void __cdecl removeTestProvider(Androidapi::Jni::Javatypes::_di_JString provider) = 0 ;
	virtual void __cdecl removeUpdates(_di_JLocationListener listener) = 0 /* overload */;
	virtual void __cdecl removeUpdates(Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual void __cdecl requestLocationUpdates(Androidapi::Jni::Javatypes::_di_JString provider, __int64 minTime, float minDistance, _di_JLocationListener listener) = 0 /* overload */;
	virtual void __cdecl requestLocationUpdates(Androidapi::Jni::Javatypes::_di_JString provider, __int64 minTime, float minDistance, _di_JLocationListener listener, Androidapi::Jni::Os::_di_JLooper looper) = 0 /* overload */;
	virtual void __cdecl requestLocationUpdates(__int64 minTime, float minDistance, _di_JCriteria criteria, _di_JLocationListener listener, Androidapi::Jni::Os::_di_JLooper looper) = 0 /* overload */;
	virtual void __cdecl requestLocationUpdates(Androidapi::Jni::Javatypes::_di_JString provider, __int64 minTime, float minDistance, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual void __cdecl requestLocationUpdates(__int64 minTime, float minDistance, _di_JCriteria criteria, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual void __cdecl requestSingleUpdate(Androidapi::Jni::Javatypes::_di_JString provider, _di_JLocationListener listener, Androidapi::Jni::Os::_di_JLooper looper) = 0 /* overload */;
	virtual void __cdecl requestSingleUpdate(_di_JCriteria criteria, _di_JLocationListener listener, Androidapi::Jni::Os::_di_JLooper looper) = 0 /* overload */;
	virtual void __cdecl requestSingleUpdate(Androidapi::Jni::Javatypes::_di_JString provider, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual void __cdecl requestSingleUpdate(_di_JCriteria criteria, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual bool __cdecl sendExtraCommand(Androidapi::Jni::Javatypes::_di_JString provider, Androidapi::Jni::Javatypes::_di_JString command, Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual void __cdecl setTestProviderEnabled(Androidapi::Jni::Javatypes::_di_JString provider, bool enabled) = 0 ;
	virtual void __cdecl setTestProviderLocation(Androidapi::Jni::Javatypes::_di_JString provider, _di_JLocation loc) = 0 ;
	virtual void __cdecl setTestProviderStatus(Androidapi::Jni::Javatypes::_di_JString provider, int status, Androidapi::Jni::Os::_di_JBundle extras, __int64 updateTime) = 0 ;
	virtual void __cdecl unregisterGnssMeasurementsCallback(_di_JGnssMeasurementsEvent_Callback callback) = 0 ;
	virtual void __cdecl unregisterGnssNavigationMessageCallback(_di_JGnssNavigationMessage_Callback callback) = 0 ;
	virtual void __cdecl unregisterGnssStatusCallback(_di_JGnssStatus_Callback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocationManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationManagerClass,_di_JLocationManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationManagerClass,_di_JLocationManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocationManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationManagerClass,_di_JLocationManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocationManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{45951F9E-53D1-428F-9B17-954C136F0DAA}") JLocationProviderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAVAILABLE() = 0 ;
	virtual int __cdecl _GetOUT_OF_SERVICE() = 0 ;
	virtual int __cdecl _GetTEMPORARILY_UNAVAILABLE() = 0 ;
	__property int AVAILABLE = {read=_GetAVAILABLE};
	__property int OUT_OF_SERVICE = {read=_GetOUT_OF_SERVICE};
	__property int TEMPORARILY_UNAVAILABLE = {read=_GetTEMPORARILY_UNAVAILABLE};
};

__interface  INTERFACE_UUID("{1A055914-E219-4691-A746-CBA8DB4BA34F}") JLocationProvider  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getAccuracy() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getPowerRequirement() = 0 ;
	virtual bool __cdecl hasMonetaryCost() = 0 ;
	virtual bool __cdecl meetsCriteria(_di_JCriteria criteria) = 0 ;
	virtual bool __cdecl requiresCell() = 0 ;
	virtual bool __cdecl requiresNetwork() = 0 ;
	virtual bool __cdecl requiresSatellite() = 0 ;
	virtual bool __cdecl supportsAltitude() = 0 ;
	virtual bool __cdecl supportsBearing() = 0 ;
	virtual bool __cdecl supportsSpeed() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocationProvider : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationProviderClass,_di_JLocationProvider>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationProviderClass,_di_JLocationProvider> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocationProvider() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationProviderClass,_di_JLocationProvider>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocationProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CDE9418B-4BB8-4819-ABE5-27E054B8BFE3}") JOnNmeaMessageListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F8E42741-3C9D-4D80-8266-C110606E79E1}") JOnNmeaMessageListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onNmeaMessage(Androidapi::Jni::Javatypes::_di_JString message, __int64 timestamp) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnNmeaMessageListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnNmeaMessageListenerClass,_di_JOnNmeaMessageListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnNmeaMessageListenerClass,_di_JOnNmeaMessageListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnNmeaMessageListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnNmeaMessageListenerClass,_di_JOnNmeaMessageListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnNmeaMessageListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{20191F52-1C01-4EBD-9587-C4D13416FD3A}") JSettingInjectorServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_INJECTED_SETTING_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_SERVICE_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetATTRIBUTES_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMETA_DATA_NAME() = 0 ;
	HIDESBASE virtual _di_JSettingInjectorService __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_INJECTED_SETTING_CHANGED = {read=_GetACTION_INJECTED_SETTING_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_SERVICE_INTENT = {read=_GetACTION_SERVICE_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString ATTRIBUTES_NAME = {read=_GetATTRIBUTES_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString META_DATA_NAME = {read=_GetMETA_DATA_NAME};
};

__interface  INTERFACE_UUID("{739CA798-301B-4FC1-A08A-39CE41189EEA}") JSettingInjectorService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl onStart(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int startId) = 0 ;
	HIDESBASE virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, int startId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSettingInjectorService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSettingInjectorServiceClass,_di_JSettingInjectorService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSettingInjectorServiceClass,_di_JSettingInjectorService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSettingInjectorService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSettingInjectorServiceClass,_di_JSettingInjectorService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSettingInjectorService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Location */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_LOCATION)
using namespace Androidapi::Jni::Location;
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
#endif	// Androidapi_Jni_LocationHPP
