// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreLocation.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CorelocationHPP
#define Iosapi_CorelocationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Corelocation
{
//-- forward type declarations -----------------------------------------------
struct CLLocationCoordinate2D;
__interface DELPHIINTERFACE CLLocationManagerDelegate;
typedef System::DelphiInterface<CLLocationManagerDelegate> _di_CLLocationManagerDelegate;
__interface DELPHIINTERFACE CLPlacemarkClass;
typedef System::DelphiInterface<CLPlacemarkClass> _di_CLPlacemarkClass;
__interface DELPHIINTERFACE CLPlacemark;
typedef System::DelphiInterface<CLPlacemark> _di_CLPlacemark;
class DELPHICLASS TCLPlacemark;
__interface DELPHIINTERFACE CLRegionClass;
typedef System::DelphiInterface<CLRegionClass> _di_CLRegionClass;
__interface DELPHIINTERFACE CLRegion;
typedef System::DelphiInterface<CLRegion> _di_CLRegion;
class DELPHICLASS TCLRegion;
__interface DELPHIINTERFACE CLLocationManagerClass;
typedef System::DelphiInterface<CLLocationManagerClass> _di_CLLocationManagerClass;
__interface DELPHIINTERFACE CLLocationManager;
typedef System::DelphiInterface<CLLocationManager> _di_CLLocationManager;
class DELPHICLASS TCLLocationManager;
__interface DELPHIINTERFACE CLGeocoderClass;
typedef System::DelphiInterface<CLGeocoderClass> _di_CLGeocoderClass;
__interface DELPHIINTERFACE CLGeocoder;
typedef System::DelphiInterface<CLGeocoder> _di_CLGeocoder;
class DELPHICLASS TCLGeocoder;
__interface DELPHIINTERFACE CLHeadingClass;
typedef System::DelphiInterface<CLHeadingClass> _di_CLHeadingClass;
__interface DELPHIINTERFACE CLHeading;
typedef System::DelphiInterface<CLHeading> _di_CLHeading;
class DELPHICLASS TCLHeading;
__interface DELPHIINTERFACE CLLocationClass;
typedef System::DelphiInterface<CLLocationClass> _di_CLLocationClass;
__interface DELPHIINTERFACE CLLocation;
typedef System::DelphiInterface<CLLocation> _di_CLLocation;
class DELPHICLASS TCLLocation;
__interface DELPHIINTERFACE CLBeaconRegionClass;
typedef System::DelphiInterface<CLBeaconRegionClass> _di_CLBeaconRegionClass;
__interface DELPHIINTERFACE CLBeaconRegion;
typedef System::DelphiInterface<CLBeaconRegion> _di_CLBeaconRegion;
class DELPHICLASS TCLBeaconRegion;
__interface DELPHIINTERFACE CLBeaconClass;
typedef System::DelphiInterface<CLBeaconClass> _di_CLBeaconClass;
__interface DELPHIINTERFACE CLBeacon;
typedef System::DelphiInterface<CLBeacon> _di_CLBeacon;
class DELPHICLASS TCLBeacon;
__interface DELPHIINTERFACE CLCircularRegionClass;
typedef System::DelphiInterface<CLCircularRegionClass> _di_CLCircularRegionClass;
__interface DELPHIINTERFACE CLCircularRegion;
typedef System::DelphiInterface<CLCircularRegion> _di_CLCircularRegion;
class DELPHICLASS TCLCircularRegion;
//-- type declarations -------------------------------------------------------
typedef int CLAuthorizationStatus;

typedef int CLDeviceOrientation;

typedef double CLHeadingComponentValue;

typedef double CLLocationAccuracy;

typedef double CLLocationDegrees;

typedef double CLLocationDirection;

typedef double CLLocationDistance;

typedef double CLLocationSpeed;

struct DECLSPEC_DRECORD CLLocationCoordinate2D
{
public:
	double latitude;
	double longitude;
};


typedef CLLocationCoordinate2D *PCLLocationCoordinate2D;

typedef System::Word CLBeaconMajorValue;

typedef System::Word CLBeaconMinorValue;

typedef long CLRegionState;

typedef long CLProximity;

typedef long CLError;

typedef void __fastcall (__closure *CLGeocodeCompletionHandler)(Iosapi::Foundation::_di_NSArray param1, Iosapi::Foundation::_di_NSError param2);

typedef long CLActivityType;

typedef void __fastcall (__closure *TCLGeocodeCompletionHandler)(const Iosapi::Foundation::_di_NSArray placemark, const Iosapi::Foundation::_di_NSError error);

__interface  INTERFACE_UUID("{A1481CE0-8EE2-497A-9132-5309F0DCCA90}") CLLocationManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl locationManager(_di_CLLocationManager manager, Iosapi::Foundation::_di_NSError didFailWithError) = 0 /* overload */;
	virtual void __cdecl locationManager(_di_CLLocationManager manager, _di_CLHeading didUpdateHeading) = 0 /* overload */;
	virtual void __cdecl locationManager(_di_CLLocationManager manager, _di_CLLocation didUpdateToLocation, _di_CLLocation fromLocation) = 0 /* overload */;
	virtual void __cdecl locationManager(_di_CLLocationManager manager, _di_CLRegion monitoringDidFailForRegion, Iosapi::Foundation::_di_NSError withError) = 0 /* overload */;
	virtual void __cdecl locationManager(_di_CLLocationManager manager, int didChangeAuthorizationStatus) = 0 /* overload */;
	virtual void __cdecl locationManagerDidUpdateLocations(_di_CLLocationManager manager, Iosapi::Foundation::_di_NSArray locations) = 0 ;
	virtual bool __cdecl locationManagerShouldDisplayHeadingCalibration(_di_CLLocationManager manager) = 0 ;
	virtual void __cdecl locationManagerDidDetermineStateForRegion(_di_CLLocationManager manager, long state, _di_CLRegion region) = 0 ;
	virtual void __cdecl locationManagerDidRangeBeaconsInRegion(_di_CLLocationManager manager, Iosapi::Foundation::_di_NSArray beacons, _di_CLBeaconRegion region) = 0 ;
	virtual void __cdecl locationManagerRangingBeaconsDidFailForRegionWithError(_di_CLLocationManager manager, _di_CLBeaconRegion region, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl locationManagerDidEnterRegion(_di_CLLocationManager manager, _di_CLRegion region) = 0 ;
	virtual void __cdecl locationManagerDidExitRegion(_di_CLLocationManager manager, _di_CLRegion region) = 0 ;
	virtual void __cdecl locationManagerDidStartMonitoringForRegion(_di_CLLocationManager manager, _di_CLRegion region) = 0 ;
	virtual void __cdecl locationManagerDidPauseLocationUpdates(_di_CLLocationManager manager) = 0 ;
	virtual void __cdecl locationManagerDidResumeLocationUpdates(_di_CLLocationManager manager) = 0 ;
	virtual void __cdecl locationManagerDidFinishDeferredUpdatesWithError(_di_CLLocationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
};

__interface  INTERFACE_UUID("{A0539851-6F72-4A85-A6DF-5ACDAD4DC09E}") CLPlacemarkClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A33A0164-05D6-49DE-A8DB-DC984C948779}") CLPlacemark  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl ISOcountryCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl addressDictionary() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl administrativeArea() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl areasOfInterest() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl country() = 0 ;
	virtual void * __cdecl initWithPlacemark(_di_CLPlacemark placemark) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl inlandWater() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl locality() = 0 ;
	virtual _di_CLLocation __cdecl location() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl ocean() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl postalCode() = 0 ;
	virtual _di_CLRegion __cdecl region() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subAdministrativeArea() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subLocality() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subThoroughfare() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl thoroughfare() = 0 ;
};

class PASCALIMPLEMENTATION TCLPlacemark : public Macapi::Objectivec::TOCGenericImport__2<_di_CLPlacemarkClass,_di_CLPlacemark>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLPlacemarkClass,_di_CLPlacemark> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLPlacemark(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLPlacemarkClass,_di_CLPlacemark>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLPlacemark() { }
	
};


__interface  INTERFACE_UUID("{92664E5E-D93F-4FD5-9A70-7EF649C7DF7E}") CLRegionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DC764906-7A0D-429C-A4B4-C939254AC7C2}") CLRegion  : public Iosapi::Foundation::NSObject 
{
	virtual CLLocationCoordinate2D __cdecl center() = 0 ;
	virtual bool __cdecl containsCoordinate(CLLocationCoordinate2D coordinate) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual void * __cdecl initCircularRegionWithCenter(CLLocationCoordinate2D center, double radius, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual double __cdecl radius() = 0 ;
	virtual void __cdecl setNotifyOnEntry(bool notifyOnEntry) = 0 ;
	virtual bool __cdecl notifyOnEntry() = 0 ;
	virtual void __cdecl setNotifyOnExit(bool notifyOnExit) = 0 ;
	virtual bool __cdecl notifyOnExit() = 0 ;
};

class PASCALIMPLEMENTATION TCLRegion : public Macapi::Objectivec::TOCGenericImport__2<_di_CLRegionClass,_di_CLRegion>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLRegionClass,_di_CLRegion> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLRegion(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLRegionClass,_di_CLRegion>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLRegion() { }
	
};


__interface  INTERFACE_UUID("{4422C248-523F-4237-8966-2A322F58A77C}") CLLocationManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual int __cdecl authorizationStatus() = 0 ;
	virtual bool __cdecl deferredLocationUpdatesAvailable() = 0 ;
	virtual bool __cdecl headingAvailable() = 0 /* overload */;
	virtual bool __cdecl isRangingAvailable() = 0 ;
	virtual bool __cdecl isMonitoringAvailableForClass(void * regionClass) = 0 ;
	virtual bool __cdecl locationServicesEnabled() = 0 /* overload */;
	virtual bool __cdecl regionMonitoringAvailable() = 0 ;
	virtual bool __cdecl regionMonitoringEnabled() = 0 ;
	virtual bool __cdecl significantLocationChangeMonitoringAvailable() = 0 ;
};

__interface  INTERFACE_UUID("{48C6C581-DA14-4444-A65D-896A0EF5E828}") CLLocationManager  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl activityType() = 0 ;
	virtual void __cdecl allowDeferredLocationUpdatesUntilTraveled(double distance, double timeout) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual double __cdecl desiredAccuracy() = 0 ;
	virtual void __cdecl disallowDeferredLocationUpdates() = 0 ;
	virtual void __cdecl dismissHeadingCalibrationDisplay() = 0 ;
	virtual double __cdecl distanceFilter() = 0 ;
	virtual _di_CLHeading __cdecl heading() = 0 ;
	virtual bool __cdecl headingAvailable() = 0 ;
	virtual double __cdecl headingFilter() = 0 ;
	virtual int __cdecl headingOrientation() = 0 ;
	virtual _di_CLLocation __cdecl location() = 0 ;
	virtual bool __cdecl locationServicesEnabled() = 0 ;
	virtual double __cdecl maximumRegionMonitoringDistance() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl monitoredRegions() = 0 ;
	virtual bool __cdecl pausesLocationUpdatesAutomatically() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl purpose() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl rangedRegions() = 0 ;
	virtual bool __cdecl allowsBackgroundLocationUpdates() = 0 ;
	virtual void __cdecl requestStateForRegion(_di_CLRegion region) = 0 ;
	virtual void __cdecl requestAlwaysAuthorization() = 0 ;
	virtual void __cdecl requestWhenInUseAuthorization() = 0 ;
	virtual void __cdecl requestLocation() = 0 ;
	virtual void __cdecl setActivityType(long activityType) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDesiredAccuracy(double desiredAccuracy) = 0 ;
	virtual void __cdecl setDistanceFilter(double distanceFilter) = 0 ;
	virtual void __cdecl setHeadingFilter(double headingFilter) = 0 ;
	virtual void __cdecl setHeadingOrientation(int headingOrientation) = 0 ;
	virtual void __cdecl setPausesLocationUpdatesAutomatically(bool pausesLocationUpdatesAutomatically) = 0 ;
	virtual void __cdecl setPurpose(Iosapi::Foundation::_di_NSString purpose) = 0 ;
	virtual void __cdecl setAllowsBackgroundLocationUpdates(bool AllowsBackgroundLocationUpdates) = 0 ;
	virtual void __cdecl startMonitoringForRegion(_di_CLRegion region) = 0 /* overload */;
	virtual void __cdecl startMonitoringForRegion(_di_CLRegion region, double desiredAccuracy) = 0 /* overload */;
	virtual void __cdecl startMonitoringSignificantLocationChanges() = 0 ;
	virtual void __cdecl startRangingBeaconsInRegion(_di_CLBeaconRegion region) = 0 ;
	virtual void __cdecl startUpdatingHeading() = 0 ;
	virtual void __cdecl startUpdatingLocation() = 0 ;
	virtual void __cdecl stopMonitoringForRegion(_di_CLRegion region) = 0 ;
	virtual void __cdecl stopMonitoringSignificantLocationChanges() = 0 ;
	virtual void __cdecl stopRangingBeaconsInRegion(_di_CLBeaconRegion region) = 0 ;
	virtual void __cdecl stopUpdatingHeading() = 0 ;
	virtual void __cdecl stopUpdatingLocation() = 0 ;
};

class PASCALIMPLEMENTATION TCLLocationManager : public Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationManagerClass,_di_CLLocationManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationManagerClass,_di_CLLocationManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLLocationManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationManagerClass,_di_CLLocationManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLLocationManager() { }
	
};


__interface  INTERFACE_UUID("{995D14FC-7FFA-4523-947D-B7F94E2BBB5E}") CLGeocoderClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{34147362-3DFB-4489-AD97-59BDF0AEE825}") CLGeocoder  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl cancelGeocode() = 0 ;
	virtual bool __cdecl isGeocoding() = 0 ;
	virtual void __cdecl geocodeAddressDictionary(Iosapi::Foundation::_di_NSDictionary addressDictionary, TCLGeocodeCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl geocodeAddressString(Iosapi::Foundation::_di_NSString addressString, TCLGeocodeCompletionHandler completionHandler) = 0 /* overload */;
	virtual void __cdecl geocodeAddressString(Iosapi::Foundation::_di_NSString addressString, _di_CLRegion region, TCLGeocodeCompletionHandler completionHandler) = 0 /* overload */;
	virtual void __cdecl reverseGeocodeLocation(_di_CLLocation location, TCLGeocodeCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl geocodeAddressStringCompletionHandler(Iosapi::Foundation::_di_NSString addressString, CLGeocodeCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl geocodeAddressStringInRegionCompletionHandler(Iosapi::Foundation::_di_NSString addressString, _di_CLRegion region, CLGeocodeCompletionHandler completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TCLGeocoder : public Macapi::Objectivec::TOCGenericImport__2<_di_CLGeocoderClass,_di_CLGeocoder>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLGeocoderClass,_di_CLGeocoder> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLGeocoder(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLGeocoderClass,_di_CLGeocoder>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLGeocoder() { }
	
};


__interface  INTERFACE_UUID("{E160A766-8EB9-4D39-B830-94EF1119CA89}") CLHeadingClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F1C59601-D23E-4D1E-B13B-D1F5AFD9ACE9}") CLHeading  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl description() = 0 ;
	virtual double __cdecl headingAccuracy() = 0 ;
	virtual double __cdecl magneticHeading() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl timestamp() = 0 ;
	virtual double __cdecl trueHeading() = 0 ;
	virtual double __cdecl x() = 0 ;
	virtual double __cdecl y() = 0 ;
	virtual double __cdecl z() = 0 ;
};

class PASCALIMPLEMENTATION TCLHeading : public Macapi::Objectivec::TOCGenericImport__2<_di_CLHeadingClass,_di_CLHeading>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLHeadingClass,_di_CLHeading> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLHeading(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLHeadingClass,_di_CLHeading>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLHeading() { }
	
};


__interface  INTERFACE_UUID("{70F80709-7F9D-4427-A243-32B28792018C}") CLLocationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3285343B-6FDA-4144-87ED-5CF72565212E}") CLLocation  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl altitude() = 0 ;
	virtual CLLocationCoordinate2D __cdecl coordinate() = 0 ;
	virtual double __cdecl course() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl description() = 0 ;
	virtual double __cdecl distanceFromLocation(_di_CLLocation location) = 0 ;
	virtual double __cdecl getDistanceFrom(_di_CLLocation location) = 0 ;
	virtual double __cdecl horizontalAccuracy() = 0 ;
	virtual void * __cdecl initWithCoordinate(CLLocationCoordinate2D coordinate, double altitude, double horizontalAccuracy, double verticalAccuracy, double course, double speed, Iosapi::Foundation::_di_NSDate timestamp) = 0 /* overload */;
	virtual void * __cdecl initWithCoordinate(CLLocationCoordinate2D coordinate, double altitude, double horizontalAccuracy, double verticalAccuracy, Iosapi::Foundation::_di_NSDate timestamp) = 0 /* overload */;
	virtual void * __cdecl initWithLatitude(double latitude, double longitude) = 0 ;
	virtual double __cdecl speed() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl timestamp() = 0 ;
	virtual double __cdecl verticalAccuracy() = 0 ;
};

class PASCALIMPLEMENTATION TCLLocation : public Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationClass,_di_CLLocation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationClass,_di_CLLocation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLLocation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLLocationClass,_di_CLLocation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLLocation() { }
	
};


__interface  INTERFACE_UUID("{E4DFC71D-F5BE-4C90-AAAF-09952242D3A5}") CLBeaconRegionClass  : public CLRegionClass 
{
	
};

__interface  INTERFACE_UUID("{56116AA2-6986-4808-BDAA-DD04F6A96F8C}") CLBeaconRegion  : public CLRegion 
{
	virtual void * __cdecl initWithProximityUUIDIdentifier(Iosapi::Foundation::_di_NSUUID proximityUUID, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void * __cdecl initWithProximityUUIDMajorIdentifier(Iosapi::Foundation::_di_NSUUID proximityUUID, System::Word major, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void * __cdecl initWithProximityUUIDMajorMinorIdentifier(Iosapi::Foundation::_di_NSUUID proximityUUID, System::Word major, System::Word minor, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSMutableDictionary __cdecl peripheralDataWithMeasuredPower(Iosapi::Foundation::_di_NSNumber measuredPower) = 0 ;
	virtual Iosapi::Foundation::_di_NSUUID __cdecl proximityUUID() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl major() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl minor() = 0 ;
	virtual void __cdecl setNotifyEntryStateOnDisplay(bool notifyEntryStateOnDisplay) = 0 ;
	virtual bool __cdecl notifyEntryStateOnDisplay() = 0 ;
};

class PASCALIMPLEMENTATION TCLBeaconRegion : public Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconRegionClass,_di_CLBeaconRegion>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconRegionClass,_di_CLBeaconRegion> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLBeaconRegion(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconRegionClass,_di_CLBeaconRegion>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLBeaconRegion() { }
	
};


__interface  INTERFACE_UUID("{FC079E8A-099B-48DB-ACA5-57CDDECE5F2A}") CLBeaconClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{86AD6390-D5BA-40C1-9043-B826B64F6F83}") CLBeacon  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSUUID __cdecl proximityUUID() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl major() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl minor() = 0 ;
	virtual long __cdecl proximity() = 0 ;
	virtual double __cdecl accuracy() = 0 ;
	virtual long __cdecl rssi() = 0 ;
};

class PASCALIMPLEMENTATION TCLBeacon : public Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconClass,_di_CLBeacon>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconClass,_di_CLBeacon> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLBeacon(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLBeaconClass,_di_CLBeacon>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLBeacon() { }
	
};


__interface  INTERFACE_UUID("{B2E71730-FB37-4DB4-9D49-8A004BB6C62C}") CLCircularRegionClass  : public CLRegionClass 
{
	
};

__interface  INTERFACE_UUID("{FF4DCF91-376B-41BB-B60A-880BEBB5B4EE}") CLCircularRegion  : public CLRegion 
{
	virtual void * __cdecl initWithCenter(CLLocationCoordinate2D center, double radius, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	HIDESBASE virtual CLLocationCoordinate2D __cdecl center() = 0 ;
	HIDESBASE virtual double __cdecl radius() = 0 ;
	HIDESBASE virtual bool __cdecl containsCoordinate(CLLocationCoordinate2D coordinate) = 0 ;
};

class PASCALIMPLEMENTATION TCLCircularRegion : public Macapi::Objectivec::TOCGenericImport__2<_di_CLCircularRegionClass,_di_CLCircularRegion>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CLCircularRegionClass,_di_CLCircularRegion> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCLCircularRegion(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CLCircularRegionClass,_di_CLCircularRegion>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCLCircularRegion() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CLDeviceOrientationFaceDown = System::Int8(0x6);
static constexpr System::Int8 CLDeviceOrientationFaceUp = System::Int8(0x5);
static constexpr System::Int8 CLDeviceOrientationLandscapeLeft = System::Int8(0x3);
static constexpr System::Int8 CLDeviceOrientationLandscapeRight = System::Int8(0x4);
static constexpr System::Int8 CLDeviceOrientationPortrait = System::Int8(0x1);
static constexpr System::Int8 CLDeviceOrientationPortraitUpsideDown = System::Int8(0x2);
static constexpr System::Int8 CLDeviceOrientationUnknown = System::Int8(0x0);
static constexpr System::Int8 kCLAuthorizationStatusAuthorized = System::Int8(0x3);
static constexpr System::Int8 kCLAuthorizationStatusDenied = System::Int8(0x2);
static constexpr System::Int8 kCLAuthorizationStatusNotDetermined = System::Int8(0x0);
static constexpr System::Int8 kCLAuthorizationStatusRestricted = System::Int8(0x1);
static constexpr System::Int8 kCLAuthorizationStatusAuthorizedAlways = System::Int8(0x3);
static constexpr System::Int8 kCLAuthorizationStatusAuthorizedWhenInUse = System::Int8(0x4);
static constexpr System::Int8 kCLErrorDenied = System::Int8(0x1);
static constexpr System::Int8 kCLErrorGeocodeCanceled = System::Int8(0xa);
static constexpr System::Int8 kCLErrorGeocodeFoundNoResult = System::Int8(0x8);
static constexpr System::Int8 kCLErrorGeocodeFoundPartialResult = System::Int8(0x9);
static constexpr System::Int8 kCLErrorHeadingFailure = System::Int8(0x3);
static constexpr System::Int8 kCLErrorLocationUnknown = System::Int8(0x0);
static constexpr System::Int8 kCLErrorNetwork = System::Int8(0x2);
static constexpr System::Int8 kCLErrorRegionMonitoringDenied = System::Int8(0x4);
static constexpr System::Int8 kCLErrorRegionMonitoringFailure = System::Int8(0x5);
static constexpr System::Int8 kCLErrorRegionMonitoringResponseDelayed = System::Int8(0x7);
static constexpr System::Int8 kCLErrorRegionMonitoringSetupDelayed = System::Int8(0x6);
extern DELPHI_PACKAGE double kCLLocationAccuracyThreeKilometers;
extern DELPHI_PACKAGE double kCLLocationAccuracyKilometer;
extern DELPHI_PACKAGE double kCLLocationAccuracyHundredMeters;
extern DELPHI_PACKAGE double kCLLocationAccuracyNearestTenMeters;
extern DELPHI_PACKAGE double kCLLocationAccuracyBest;
extern DELPHI_PACKAGE double kCLLocationAccuracyBestForNavigation;
static constexpr System::Int8 CLRegionStateUnknown = System::Int8(0x0);
static constexpr System::Int8 CLRegionStateInside = System::Int8(0x1);
static constexpr System::Int8 CLRegionStateOutside = System::Int8(0x2);
static constexpr System::Int8 CLProximityUnknown = System::Int8(0x0);
static constexpr System::Int8 CLProximityImmediate = System::Int8(0x1);
static constexpr System::Int8 CLProximityNear = System::Int8(0x2);
static constexpr System::Int8 CLProximityFar = System::Int8(0x3);
static constexpr System::Int8 kCLErrorDeferredFailed = System::Int8(0xb);
static constexpr System::Int8 kCLErrorDeferredNotUpdatingLocation = System::Int8(0xc);
static constexpr System::Int8 kCLErrorDeferredAccuracyTooLow = System::Int8(0xd);
static constexpr System::Int8 kCLErrorDeferredDistanceFiltered = System::Int8(0xe);
static constexpr System::Int8 kCLErrorDeferredCanceled = System::Int8(0xf);
static constexpr System::Int8 kCLErrorRangingUnavailable = System::Int8(0x10);
static constexpr System::Int8 kCLErrorRangingFailure = System::Int8(0x11);
static constexpr System::Int8 CLActivityTypeOther = System::Int8(0x1);
static constexpr System::Int8 CLActivityTypeAutomotiveNavigation = System::Int8(0x2);
static constexpr System::Int8 CLActivityTypeFitness = System::Int8(0x3);
static constexpr System::Int8 CLActivityTypeOtherNavigation = System::Int8(0x4);
#define libCoreLocation u"/System/Library/Frameworks/CoreLocation.framework/CoreLoca"\
	u"tion"
extern "C" bool __cdecl CLLocationCoordinate2DIsValid(CLLocationCoordinate2D coord);
extern "C" CLLocationCoordinate2D __cdecl CLLocationCoordinate2DMake(double latitude, double longitude);
}	/* namespace Corelocation */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_CORELOCATION)
using namespace Iosapi::Corelocation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CorelocationHPP
