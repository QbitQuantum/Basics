// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Geolocation.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_GeolocationHPP
#define Winapi_Devices_GeolocationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Geolocation
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IGeoshape;
typedef System::DelphiInterface<IGeoshape> _di_IGeoshape;
__interface DELPHIINTERFACE IGeocoordinate;
typedef System::DelphiInterface<IGeocoordinate> _di_IGeocoordinate;
__interface DELPHIINTERFACE ICivicAddress;
typedef System::DelphiInterface<ICivicAddress> _di_ICivicAddress;
__interface DELPHIINTERFACE IGeoposition;
typedef System::DelphiInterface<IGeoposition> _di_IGeoposition;
__interface DELPHIINTERFACE IGeopoint;
typedef System::DelphiInterface<IGeopoint> _di_IGeopoint;
__interface DELPHIINTERFACE IGeopointFactory;
typedef System::DelphiInterface<IGeopointFactory> _di_IGeopointFactory;
__interface DELPHIINTERFACE IIterator_1__BasicGeoposition_Base;
typedef System::DelphiInterface<IIterator_1__BasicGeoposition_Base> _di_IIterator_1__BasicGeoposition_Base;
__interface DELPHIINTERFACE IIterator_1__BasicGeoposition;
typedef System::DelphiInterface<IIterator_1__BasicGeoposition> _di_IIterator_1__BasicGeoposition;
__interface DELPHIINTERFACE IIterable_1__BasicGeoposition_Base;
typedef System::DelphiInterface<IIterable_1__BasicGeoposition_Base> _di_IIterable_1__BasicGeoposition_Base;
__interface DELPHIINTERFACE IIterable_1__BasicGeoposition;
typedef System::DelphiInterface<IIterable_1__BasicGeoposition> _di_IIterable_1__BasicGeoposition;
__interface DELPHIINTERFACE IVectorView_1__BasicGeoposition;
typedef System::DelphiInterface<IVectorView_1__BasicGeoposition> _di_IVectorView_1__BasicGeoposition;
__interface DELPHIINTERFACE IGeopath;
typedef System::DelphiInterface<IGeopath> _di_IGeopath;
__interface DELPHIINTERFACE IGeopathFactory;
typedef System::DelphiInterface<IGeopathFactory> _di_IGeopathFactory;
__interface DELPHIINTERFACE IGeoboundingBox;
typedef System::DelphiInterface<IGeoboundingBox> _di_IGeoboundingBox;
__interface DELPHIINTERFACE IGeoboundingBoxFactory;
typedef System::DelphiInterface<IGeoboundingBoxFactory> _di_IGeoboundingBoxFactory;
__interface DELPHIINTERFACE IGeoboundingBoxStatics;
typedef System::DelphiInterface<IGeoboundingBoxStatics> _di_IGeoboundingBoxStatics;
__interface DELPHIINTERFACE IGeocoordinateSatelliteData;
typedef System::DelphiInterface<IGeocoordinateSatelliteData> _di_IGeocoordinateSatelliteData;
__interface DELPHIINTERFACE IVenueData;
typedef System::DelphiInterface<IVenueData> _di_IVenueData;
__interface DELPHIINTERFACE IGeocoordinateWithPositionData;
typedef System::DelphiInterface<IGeocoordinateWithPositionData> _di_IGeocoordinateWithPositionData;
__interface DELPHIINTERFACE IGeocoordinateWithPoint;
typedef System::DelphiInterface<IGeocoordinateWithPoint> _di_IGeocoordinateWithPoint;
__interface DELPHIINTERFACE IGeocoordinateWithPositionSourceTimestamp;
typedef System::DelphiInterface<IGeocoordinateWithPositionSourceTimestamp> _di_IGeocoordinateWithPositionSourceTimestamp;
__interface DELPHIINTERFACE IGeoposition2;
typedef System::DelphiInterface<IGeoposition2> _di_IGeoposition2;
__interface DELPHIINTERFACE IPositionChangedEventArgs;
typedef System::DelphiInterface<IPositionChangedEventArgs> _di_IPositionChangedEventArgs;
__interface DELPHIINTERFACE IStatusChangedEventArgs;
typedef System::DelphiInterface<IStatusChangedEventArgs> _di_IStatusChangedEventArgs;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeoposition_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeoposition_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IGeoposition_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeoposition;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeoposition> _di_AsyncOperationCompletedHandler_1__IGeoposition;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeoposition_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IGeoposition_Base> _di_IAsyncOperation_1__IGeoposition_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeoposition;
typedef System::DelphiInterface<IAsyncOperation_1__IGeoposition> _di_IAsyncOperation_1__IGeoposition;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs> _di_TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs> _di_TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs;
__interface DELPHIINTERFACE IGeolocator;
typedef System::DelphiInterface<IGeolocator> _di_IGeolocator;
__interface DELPHIINTERFACE IGeolocatorWithScalarAccuracy;
typedef System::DelphiInterface<IGeolocatorWithScalarAccuracy> _di_IGeolocatorWithScalarAccuracy;
__interface DELPHIINTERFACE IGeolocator2;
typedef System::DelphiInterface<IGeolocator2> _di_IGeolocator2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__GeolocationAccessStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__GeolocationAccessStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__GeolocationAccessStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__GeolocationAccessStatus> _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__GeolocationAccessStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__GeolocationAccessStatus_Base> _di_IAsyncOperation_1__GeolocationAccessStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__GeolocationAccessStatus;
typedef System::DelphiInterface<IAsyncOperation_1__GeolocationAccessStatus> _di_IAsyncOperation_1__GeolocationAccessStatus;
__interface DELPHIINTERFACE IIterator_1__IGeoposition_Base;
typedef System::DelphiInterface<IIterator_1__IGeoposition_Base> _di_IIterator_1__IGeoposition_Base;
__interface DELPHIINTERFACE IIterator_1__IGeoposition;
typedef System::DelphiInterface<IIterator_1__IGeoposition> _di_IIterator_1__IGeoposition;
__interface DELPHIINTERFACE IIterable_1__IGeoposition_Base;
typedef System::DelphiInterface<IIterable_1__IGeoposition_Base> _di_IIterable_1__IGeoposition_Base;
__interface DELPHIINTERFACE IIterable_1__IGeoposition;
typedef System::DelphiInterface<IIterable_1__IGeoposition> _di_IIterable_1__IGeoposition;
__interface DELPHIINTERFACE IVectorView_1__IGeoposition;
typedef System::DelphiInterface<IVectorView_1__IGeoposition> _di_IVectorView_1__IGeoposition;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IGeoposition_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IGeoposition_Base> _di_IAsyncOperation_1__IVectorView_1__IGeoposition_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IGeoposition;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IGeoposition> _di_IAsyncOperation_1__IVectorView_1__IGeoposition;
__interface DELPHIINTERFACE IGeolocatorStatics;
typedef System::DelphiInterface<IGeolocatorStatics> _di_IGeolocatorStatics;
__interface DELPHIINTERFACE IReference_1__BasicGeoposition;
typedef System::DelphiInterface<IReference_1__BasicGeoposition> _di_IReference_1__BasicGeoposition;
__interface DELPHIINTERFACE IGeolocatorStatics2;
typedef System::DelphiInterface<IGeolocatorStatics2> _di_IGeolocatorStatics2;
__interface DELPHIINTERFACE IGeocircle;
typedef System::DelphiInterface<IGeocircle> _di_IGeocircle;
__interface DELPHIINTERFACE IGeocircleFactory;
typedef System::DelphiInterface<IGeocircleFactory> _di_IGeocircleFactory;
__interface DELPHIINTERFACE IGeovisit;
typedef System::DelphiInterface<IGeovisit> _di_IGeovisit;
__interface DELPHIINTERFACE IGeovisitStateChangedEventArgs;
typedef System::DelphiInterface<IGeovisitStateChangedEventArgs> _di_IGeovisitStateChangedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs> _di_TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs;
__interface DELPHIINTERFACE IGeovisitMonitor;
typedef System::DelphiInterface<IGeovisitMonitor> _di_IGeovisitMonitor;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeovisit_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeovisit_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IGeovisit_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeovisit;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeovisit> _di_AsyncOperationCompletedHandler_1__IGeovisit;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeovisit_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IGeovisit_Base> _di_IAsyncOperation_1__IGeovisit_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeovisit;
typedef System::DelphiInterface<IAsyncOperation_1__IGeovisit> _di_IAsyncOperation_1__IGeovisit;
__interface DELPHIINTERFACE IGeovisitMonitorStatics;
typedef System::DelphiInterface<IGeovisitMonitorStatics> _di_IGeovisitMonitorStatics;
__interface DELPHIINTERFACE IIterator_1__IGeovisit_Base;
typedef System::DelphiInterface<IIterator_1__IGeovisit_Base> _di_IIterator_1__IGeovisit_Base;
__interface DELPHIINTERFACE IIterator_1__IGeovisit;
typedef System::DelphiInterface<IIterator_1__IGeovisit> _di_IIterator_1__IGeovisit;
__interface DELPHIINTERFACE IIterable_1__IGeovisit_Base;
typedef System::DelphiInterface<IIterable_1__IGeovisit_Base> _di_IIterable_1__IGeovisit_Base;
__interface DELPHIINTERFACE IIterable_1__IGeovisit;
typedef System::DelphiInterface<IIterable_1__IGeovisit> _di_IIterable_1__IGeovisit;
__interface DELPHIINTERFACE IVectorView_1__IGeovisit;
typedef System::DelphiInterface<IVectorView_1__IGeovisit> _di_IVectorView_1__IGeovisit;
__interface DELPHIINTERFACE IGeovisitTriggerDetails;
typedef System::DelphiInterface<IGeovisitTriggerDetails> _di_IGeovisitTriggerDetails;
__interface DELPHIINTERFACE IIterator_1__IGeopoint_Base;
typedef System::DelphiInterface<IIterator_1__IGeopoint_Base> _di_IIterator_1__IGeopoint_Base;
__interface DELPHIINTERFACE IIterator_1__IGeopoint;
typedef System::DelphiInterface<IIterator_1__IGeopoint> _di_IIterator_1__IGeopoint;
__interface DELPHIINTERFACE IIterable_1__IGeopoint_Base;
typedef System::DelphiInterface<IIterable_1__IGeopoint_Base> _di_IIterable_1__IGeopoint_Base;
__interface DELPHIINTERFACE IIterable_1__IGeopoint;
typedef System::DelphiInterface<IIterable_1__IGeopoint> _di_IIterable_1__IGeopoint;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeopoint_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeopoint_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IGeopoint_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IGeopoint;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IGeopoint> _di_AsyncOperationCompletedHandler_1__IGeopoint;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeopoint_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IGeopoint_Base> _di_IAsyncOperation_1__IGeopoint_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IGeopoint;
typedef System::DelphiInterface<IAsyncOperation_1__IGeopoint> _di_IAsyncOperation_1__IGeopoint;
__interface DELPHIINTERFACE IIterator_1__IGeopath_Base;
typedef System::DelphiInterface<IIterator_1__IGeopath_Base> _di_IIterator_1__IGeopath_Base;
__interface DELPHIINTERFACE IIterator_1__IGeopath;
typedef System::DelphiInterface<IIterator_1__IGeopath> _di_IIterator_1__IGeopath;
__interface DELPHIINTERFACE IIterable_1__IGeopath_Base;
typedef System::DelphiInterface<IIterable_1__IGeopath_Base> _di_IIterable_1__IGeopath_Base;
__interface DELPHIINTERFACE IIterable_1__IGeopath;
typedef System::DelphiInterface<IIterable_1__IGeopath> _di_IIterable_1__IGeopath;
__interface DELPHIINTERFACE IVectorView_1__IGeopath;
typedef System::DelphiInterface<IVectorView_1__IGeopath> _di_IVectorView_1__IGeopath;
__interface DELPHIINTERFACE IVector_1__IGeopath;
typedef System::DelphiInterface<IVector_1__IGeopath> _di_IVector_1__IGeopath;
class DELPHICLASS TGeopoint;
class DELPHICLASS TGeopath;
class DELPHICLASS TGeoboundingBox;
class DELPHICLASS TGeolocator;
class DELPHICLASS TGeocircle;
class DELPHICLASS TGeovisitMonitor;
//-- type declarations -------------------------------------------------------
typedef _di_IGeoshape *PIGeoshape;

typedef _di_IGeocoordinate *PIGeocoordinate;

typedef _di_ICivicAddress *PICivicAddress;

typedef _di_IGeoposition *PIGeoposition;

typedef _di_IGeopoint *PIGeopoint;

typedef _di_IGeopointFactory *PIGeopointFactory;

typedef _di_IIterator_1__BasicGeoposition *PIIterator_1__BasicGeoposition;

typedef _di_IIterable_1__BasicGeoposition *PIIterable_1__BasicGeoposition;

typedef _di_IVectorView_1__BasicGeoposition *PIVectorView_1__BasicGeoposition;

typedef _di_IGeopath *PIGeopath;

typedef _di_IGeopathFactory *PIGeopathFactory;

typedef _di_IGeoboundingBox *PIGeoboundingBox;

typedef _di_IGeoboundingBoxFactory *PIGeoboundingBoxFactory;

typedef _di_IGeoboundingBoxStatics *PIGeoboundingBoxStatics;

typedef _di_IGeocoordinateSatelliteData *PIGeocoordinateSatelliteData;

typedef _di_IVenueData *PIVenueData;

typedef _di_IGeocoordinateWithPositionData *PIGeocoordinateWithPositionData;

typedef _di_IGeocoordinateWithPoint *PIGeocoordinateWithPoint;

typedef _di_IGeocoordinateWithPositionSourceTimestamp *PIGeocoordinateWithPositionSourceTimestamp;

typedef _di_IGeoposition2 *PIGeoposition2;

typedef _di_IPositionChangedEventArgs *PIPositionChangedEventArgs;

typedef _di_IStatusChangedEventArgs *PIStatusChangedEventArgs;

typedef _di_AsyncOperationCompletedHandler_1__IGeoposition *PAsyncOperationCompletedHandler_1__IGeoposition;

typedef _di_IAsyncOperation_1__IGeoposition *PIAsyncOperation_1__IGeoposition;

typedef _di_TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs *PTypedEventHandler_2__IGeolocator__IPositionChangedEventArgs;

typedef _di_TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs *PTypedEventHandler_2__IGeolocator__IStatusChangedEventArgs;

typedef _di_IGeolocator *PIGeolocator;

typedef _di_IGeolocatorWithScalarAccuracy *PIGeolocatorWithScalarAccuracy;

typedef _di_IGeolocator2 *PIGeolocator2;

typedef _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus *PAsyncOperationCompletedHandler_1__GeolocationAccessStatus;

typedef _di_IAsyncOperation_1__GeolocationAccessStatus *PIAsyncOperation_1__GeolocationAccessStatus;

typedef _di_IIterator_1__IGeoposition *PIIterator_1__IGeoposition;

typedef _di_IIterable_1__IGeoposition *PIIterable_1__IGeoposition;

typedef _di_IVectorView_1__IGeoposition *PIVectorView_1__IGeoposition;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition *PAsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition;

typedef _di_IAsyncOperation_1__IVectorView_1__IGeoposition *PIAsyncOperation_1__IVectorView_1__IGeoposition;

typedef _di_IGeolocatorStatics *PIGeolocatorStatics;

typedef _di_IReference_1__BasicGeoposition *PIReference_1__BasicGeoposition;

typedef _di_IGeolocatorStatics2 *PIGeolocatorStatics2;

typedef _di_IGeocircle *PIGeocircle;

typedef _di_IGeocircleFactory *PIGeocircleFactory;

typedef _di_IGeovisit *PIGeovisit;

typedef _di_IGeovisitStateChangedEventArgs *PIGeovisitStateChangedEventArgs;

typedef _di_TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs *PTypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs;

typedef _di_IGeovisitMonitor *PIGeovisitMonitor;

typedef _di_AsyncOperationCompletedHandler_1__IGeovisit *PAsyncOperationCompletedHandler_1__IGeovisit;

typedef _di_IAsyncOperation_1__IGeovisit *PIAsyncOperation_1__IGeovisit;

typedef _di_IGeovisitMonitorStatics *PIGeovisitMonitorStatics;

typedef _di_IIterator_1__IGeovisit *PIIterator_1__IGeovisit;

typedef _di_IIterable_1__IGeovisit *PIIterable_1__IGeovisit;

typedef _di_IVectorView_1__IGeovisit *PIVectorView_1__IGeovisit;

typedef _di_IGeovisitTriggerDetails *PIGeovisitTriggerDetails;

typedef _di_IIterator_1__IGeopoint *PIIterator_1__IGeopoint;

typedef _di_IIterable_1__IGeopoint *PIIterable_1__IGeopoint;

typedef _di_AsyncOperationCompletedHandler_1__IGeopoint *PAsyncOperationCompletedHandler_1__IGeopoint;

typedef _di_IAsyncOperation_1__IGeopoint *PIAsyncOperation_1__IGeopoint;

typedef _di_IIterator_1__IGeopath *PIIterator_1__IGeopath;

typedef _di_IIterable_1__IGeopath *PIIterable_1__IGeopath;

typedef _di_IVectorView_1__IGeopath *PIVectorView_1__IGeopath;

typedef _di_IVector_1__IGeopath *PIVector_1__IGeopath;

__interface  INTERFACE_UUID("{C99CA2AF-C729-43C1-8FAB-D6DEC914DF7E}") IGeoshape  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_GeoshapeType(Winapi::Commontypes::GeoshapeType &__get_GeoshapeType_result) = 0 ;
	virtual HRESULT __safecall get_SpatialReferenceId(unsigned &__get_SpatialReferenceId_result) = 0 ;
	virtual HRESULT __safecall get_AltitudeReferenceSystem(Winapi::Commontypes::AltitudeReferenceSystem &__get_AltitudeReferenceSystem_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AltitudeReferenceSystem _scw_get_AltitudeReferenceSystem() { Winapi::Commontypes::AltitudeReferenceSystem __r; HRESULT __hr = get_AltitudeReferenceSystem(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AltitudeReferenceSystem AltitudeReferenceSystem = {read=_scw_get_AltitudeReferenceSystem};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::GeoshapeType _scw_get_GeoshapeType() { Winapi::Commontypes::GeoshapeType __r; HRESULT __hr = get_GeoshapeType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::GeoshapeType GeoshapeType = {read=_scw_get_GeoshapeType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SpatialReferenceId() { unsigned __r; HRESULT __hr = get_SpatialReferenceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SpatialReferenceId = {read=_scw_get_SpatialReferenceId};
};

__interface  INTERFACE_UUID("{EE21A3AA-976A-4C70-803D-083EA55BCBC4}") IGeocoordinate  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Latitude(double &__get_Latitude_result) = 0 ;
	virtual HRESULT __safecall get_Longitude(double &__get_Longitude_result) = 0 ;
	virtual HRESULT __safecall get_Altitude(Winapi::Commontypes::_di_IReference_1__Double &__get_Altitude_result) = 0 ;
	virtual HRESULT __safecall get_Accuracy(double &__get_Accuracy_result) = 0 ;
	virtual HRESULT __safecall get_AltitudeAccuracy(Winapi::Commontypes::_di_IReference_1__Double &__get_AltitudeAccuracy_result) = 0 ;
	virtual HRESULT __safecall get_Heading(Winapi::Commontypes::_di_IReference_1__Double &__get_Heading_result) = 0 ;
	virtual HRESULT __safecall get_Speed(Winapi::Commontypes::_di_IReference_1__Double &__get_Speed_result) = 0 ;
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Accuracy() { double __r; HRESULT __hr = get_Accuracy(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Accuracy = {read=_scw_get_Accuracy};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_Altitude() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_Altitude(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double Altitude = {read=_scw_get_Altitude};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_AltitudeAccuracy() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_AltitudeAccuracy(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double AltitudeAccuracy = {read=_scw_get_AltitudeAccuracy};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_Heading() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_Heading(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double Heading = {read=_scw_get_Heading};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Latitude() { double __r; HRESULT __hr = get_Latitude(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Latitude = {read=_scw_get_Latitude};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Longitude() { double __r; HRESULT __hr = get_Longitude(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Longitude = {read=_scw_get_Longitude};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_Speed() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_Speed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double Speed = {read=_scw_get_Speed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
};

__interface  INTERFACE_UUID("{A8567A1A-64F4-4D48-BCEA-F6B008ECA34C}") ICivicAddress  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Country(HSTRING &__get_Country_result) = 0 ;
	virtual HRESULT __safecall get_State(HSTRING &__get_State_result) = 0 ;
	virtual HRESULT __safecall get_City(HSTRING &__get_City_result) = 0 ;
	virtual HRESULT __safecall get_PostalCode(HSTRING &__get_PostalCode_result) = 0 ;
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_City() { HSTRING __r; HRESULT __hr = get_City(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING City = {read=_scw_get_City};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Country() { HSTRING __r; HRESULT __hr = get_Country(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Country = {read=_scw_get_Country};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PostalCode() { HSTRING __r; HRESULT __hr = get_PostalCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PostalCode = {read=_scw_get_PostalCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_State() { HSTRING __r; HRESULT __hr = get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING State = {read=_scw_get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
};

__interface  INTERFACE_UUID("{C18D0454-7D41-4FF7-A957-9DFFB4EF7F5B}") IGeoposition  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Coordinate(_di_IGeocoordinate &__get_Coordinate_result) = 0 ;
	virtual HRESULT __safecall get_CivicAddress(_di_ICivicAddress &__get_CivicAddress_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICivicAddress _scw_get_CivicAddress() { _di_ICivicAddress __r; HRESULT __hr = get_CivicAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICivicAddress CivicAddress = {read=_scw_get_CivicAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeocoordinate _scw_get_Coordinate() { _di_IGeocoordinate __r; HRESULT __hr = get_Coordinate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeocoordinate Coordinate = {read=_scw_get_Coordinate};
};

__interface  INTERFACE_UUID("{6BFA00EB-E56E-49BB-9CAF-CBAA78A8BCEF}") IGeopoint  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Position(Winapi::Commontypes::BasicGeoposition &__get_Position_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_Position() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition Position = {read=_scw_get_Position};
};

__interface  INTERFACE_UUID("{DB6B8D33-76BD-4E30-8AF7-A844DC37B7A0}") IGeopointFactory  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall Create(Winapi::Commontypes::BasicGeoposition position, _di_IGeopoint &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystem(Winapi::Commontypes::BasicGeoposition position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeopoint &__CreateWithAltitudeReferenceSystem_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(Winapi::Commontypes::BasicGeoposition position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeopoint &__CreateWithAltitudeReferenceSystemAndSpatialReferenceId_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall Create(const Winapi::Commontypes::BasicGeoposition &position, _di_IGeopoint &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystem(const Winapi::Commontypes::BasicGeoposition &position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeopoint &__CreateWithAltitudeReferenceSystem_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(const Winapi::Commontypes::BasicGeoposition &position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeopoint &__CreateWithAltitudeReferenceSystemAndSpatialReferenceId_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{1B4E26A1-88E4-5872-BB2D-4F31700828B2}") IIterator_1__BasicGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__BasicGeoposition  : public IIterator_1__BasicGeoposition_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::BasicGeoposition &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PBasicGeoposition items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_Current() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{922399A8-0093-5009-A8D2-F87B0EAE75F5}") IIterable_1__BasicGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__BasicGeoposition  : public IIterable_1__BasicGeoposition_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__BasicGeoposition &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__BasicGeoposition  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::BasicGeoposition &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::BasicGeoposition value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall IndexOf(const Winapi::Commontypes::BasicGeoposition &value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PBasicGeoposition items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{E53FD7B9-2DA4-4714-A652-DE8593289898}") IGeopath  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Positions(_di_IVectorView_1__BasicGeoposition &__get_Positions_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__BasicGeoposition _scw_get_Positions() { _di_IVectorView_1__BasicGeoposition __r; HRESULT __hr = get_Positions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__BasicGeoposition Positions = {read=_scw_get_Positions};
};

__interface  INTERFACE_UUID("{27BEA9C8-C7E7-4359-9B9B-FCA3E05EF593}") IGeopathFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_IIterable_1__BasicGeoposition positions, _di_IGeopath &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReference(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeopath &__CreateWithAltitudeReference_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceAndSpatialReference(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeopath &__CreateWithAltitudeReferenceAndSpatialReference_result) = 0 ;
};

__interface  INTERFACE_UUID("{0896C80B-274F-43DA-9A06-CBFCDAEB4EC2}") IGeoboundingBox  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NorthwestCorner(Winapi::Commontypes::BasicGeoposition &__get_NorthwestCorner_result) = 0 ;
	virtual HRESULT __safecall get_SoutheastCorner(Winapi::Commontypes::BasicGeoposition &__get_SoutheastCorner_result) = 0 ;
	virtual HRESULT __safecall get_Center(Winapi::Commontypes::BasicGeoposition &__get_Center_result) = 0 ;
	virtual HRESULT __safecall get_MinAltitude(double &__get_MinAltitude_result) = 0 ;
	virtual HRESULT __safecall get_MaxAltitude(double &__get_MaxAltitude_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_Center() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_Center(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition Center = {read=_scw_get_Center};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_MaxAltitude() { double __r; HRESULT __hr = get_MaxAltitude(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double MaxAltitude = {read=_scw_get_MaxAltitude};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_MinAltitude() { double __r; HRESULT __hr = get_MinAltitude(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double MinAltitude = {read=_scw_get_MinAltitude};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_NorthwestCorner() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_NorthwestCorner(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition NorthwestCorner = {read=_scw_get_NorthwestCorner};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_SoutheastCorner() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_SoutheastCorner(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition SoutheastCorner = {read=_scw_get_SoutheastCorner};
};

__interface  INTERFACE_UUID("{4DFBA589-0411-4ABC-B3B5-5BBCCB57D98C}") IGeoboundingBoxFactory  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall Create(Winapi::Commontypes::BasicGeoposition northwestCorner, Winapi::Commontypes::BasicGeoposition southeastCorner, _di_IGeoboundingBox &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReference(Winapi::Commontypes::BasicGeoposition northwestCorner, Winapi::Commontypes::BasicGeoposition southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeoboundingBox &__CreateWithAltitudeReference_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceAndSpatialReference(Winapi::Commontypes::BasicGeoposition northwestCorner, Winapi::Commontypes::BasicGeoposition southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeoboundingBox &__CreateWithAltitudeReferenceAndSpatialReference_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall Create(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner, _di_IGeoboundingBox &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReference(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeoboundingBox &__CreateWithAltitudeReference_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceAndSpatialReference(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeoboundingBox &__CreateWithAltitudeReferenceAndSpatialReference_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{67B80708-E61A-4CD0-841B-93233792B5CA}") IGeoboundingBoxStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall TryCompute(_di_IIterable_1__BasicGeoposition positions, _di_IGeoboundingBox &__TryCompute_result) = 0 /* overload */;
	virtual HRESULT __safecall TryCompute(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeRefSystem, _di_IGeoboundingBox &__TryCompute_result) = 0 /* overload */;
	virtual HRESULT __safecall TryCompute(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeRefSystem, unsigned spatialReferenceId, _di_IGeoboundingBox &__TryCompute_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{C32A74D9-2608-474C-912C-06DD490F4AF7}") IGeocoordinateSatelliteData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PositionDilutionOfPrecision(Winapi::Commontypes::_di_IReference_1__Double &__get_PositionDilutionOfPrecision_result) = 0 ;
	virtual HRESULT __safecall get_HorizontalDilutionOfPrecision(Winapi::Commontypes::_di_IReference_1__Double &__get_HorizontalDilutionOfPrecision_result) = 0 ;
	virtual HRESULT __safecall get_VerticalDilutionOfPrecision(Winapi::Commontypes::_di_IReference_1__Double &__get_VerticalDilutionOfPrecision_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_HorizontalDilutionOfPrecision() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_HorizontalDilutionOfPrecision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double HorizontalDilutionOfPrecision = {read=_scw_get_HorizontalDilutionOfPrecision};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_PositionDilutionOfPrecision() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_PositionDilutionOfPrecision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double PositionDilutionOfPrecision = {read=_scw_get_PositionDilutionOfPrecision};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Double _scw_get_VerticalDilutionOfPrecision() { Winapi::Commontypes::_di_IReference_1__Double __r; HRESULT __hr = get_VerticalDilutionOfPrecision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Double VerticalDilutionOfPrecision = {read=_scw_get_VerticalDilutionOfPrecision};
};

__interface  INTERFACE_UUID("{66F39187-60E3-4B2F-B527-4F53F1C3C677}") IVenueData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_Level(HSTRING &__get_Level_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Level() { HSTRING __r; HRESULT __hr = get_Level(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Level = {read=_scw_get_Level};
};

__interface  INTERFACE_UUID("{95E634BE-DBD6-40AC-B8F2-A65C0340D9A6}") IGeocoordinateWithPositionData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PositionSource(Winapi::Commontypes::PositionSource &__get_PositionSource_result) = 0 ;
	virtual HRESULT __safecall get_SatelliteData(_di_IGeocoordinateSatelliteData &__get_SatelliteData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PositionSource _scw_get_PositionSource() { Winapi::Commontypes::PositionSource __r; HRESULT __hr = get_PositionSource(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PositionSource PositionSource = {read=_scw_get_PositionSource};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeocoordinateSatelliteData _scw_get_SatelliteData() { _di_IGeocoordinateSatelliteData __r; HRESULT __hr = get_SatelliteData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeocoordinateSatelliteData SatelliteData = {read=_scw_get_SatelliteData};
};

__interface  INTERFACE_UUID("{FEEA0525-D22C-4D46-B527-0B96066FC7DB}") IGeocoordinateWithPoint  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Point(_di_IGeopoint &__get_Point_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeopoint _scw_get_Point() { _di_IGeopoint __r; HRESULT __hr = get_Point(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeopoint Point = {read=_scw_get_Point};
};

__interface  INTERFACE_UUID("{8543FC02-C9F1-4610-AFE0-8BC3A6A87036}") IGeocoordinateWithPositionSourceTimestamp  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PositionSourceTimestamp(Winapi::Commontypes::_di_IReference_1__DateTime &__get_PositionSourceTimestamp_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_PositionSourceTimestamp() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_PositionSourceTimestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime PositionSourceTimestamp = {read=_scw_get_PositionSourceTimestamp};
};

__interface  INTERFACE_UUID("{7F62F697-8671-4B0D-86F8-474A8496187C}") IGeoposition2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_VenueData(_di_IVenueData &__get_VenueData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVenueData _scw_get_VenueData() { _di_IVenueData __r; HRESULT __hr = get_VenueData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVenueData VenueData = {read=_scw_get_VenueData};
};

__interface  INTERFACE_UUID("{37859CE5-9D1E-46C5-BF3B-6AD8CAC1A093}") IPositionChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Position(_di_IGeoposition &__get_Position_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeoposition _scw_get_Position() { _di_IGeoposition __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeoposition Position = {read=_scw_get_Position};
};

__interface  INTERFACE_UUID("{3453D2DA-8C93-4111-A205-9AECFC9BE5C0}") IStatusChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::PositionStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PositionStatus _scw_get_Status() { Winapi::Commontypes::PositionStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PositionStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{7668A704-244E-5E12-8DCB-92A3299EBA26}") AsyncOperationCompletedHandler_1__IGeoposition_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{7B8AE52A-070D-5658-B3CA-1B394091EA48}") AsyncOperationCompletedHandler_1__IGeoposition  : public AsyncOperationCompletedHandler_1__IGeoposition_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IGeoposition asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{EE73ECF0-099D-57E5-8407-5B32E5AF1CC4}") IAsyncOperation_1__IGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{9223B88D-2C6D-50F5-BD0F-F2C9928EECD3}") IAsyncOperation_1__IGeoposition  : public IAsyncOperation_1__IGeoposition_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IGeoposition handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IGeoposition &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IGeoposition &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IGeoposition _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IGeoposition __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IGeoposition Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{DF3C6164-4E7B-5E8E-9A7E-13DA059DEC1E}") TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{04806A98-49FF-53B3-AF96-93269759D5C2}") TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs  : public TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IGeolocator sender, _di_IPositionChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{97FCF582-DE6B-5CD3-9690-E2ECBB66DA4D}") TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B9F039C6-759A-5E7D-BB48-6D1B1BBB9023}") TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs  : public TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IGeolocator sender, _di_IStatusChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{A9C3BF62-4524-4989-8AA9-DE019D2E551F}") IGeolocator  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DesiredAccuracy(Winapi::Commontypes::PositionAccuracy &__get_DesiredAccuracy_result) = 0 ;
	virtual HRESULT __safecall put_DesiredAccuracy(Winapi::Commontypes::PositionAccuracy value) = 0 ;
	virtual HRESULT __safecall get_MovementThreshold(double &__get_MovementThreshold_result) = 0 ;
	virtual HRESULT __safecall put_MovementThreshold(double value) = 0 ;
	virtual HRESULT __safecall get_ReportInterval(unsigned &__get_ReportInterval_result) = 0 ;
	virtual HRESULT __safecall put_ReportInterval(unsigned value) = 0 ;
	virtual HRESULT __safecall get_LocationStatus(Winapi::Commontypes::PositionStatus &__get_LocationStatus_result) = 0 ;
	virtual HRESULT __safecall GetGeopositionAsync(_di_IAsyncOperation_1__IGeoposition &__GetGeopositionAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetGeopositionAsync(Winapi::Commontypes::TimeSpan maximumAge, Winapi::Commontypes::TimeSpan timeout, _di_IAsyncOperation_1__IGeoposition &__GetGeopositionAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall add_PositionChanged(_di_TypedEventHandler_2__IGeolocator__IPositionChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_PositionChanged_result) = 0 ;
	virtual HRESULT __safecall remove_PositionChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_StatusChanged(_di_TypedEventHandler_2__IGeolocator__IStatusChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StatusChanged_result) = 0 ;
	virtual HRESULT __safecall remove_StatusChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PositionAccuracy _scw_get_DesiredAccuracy() { Winapi::Commontypes::PositionAccuracy __r; HRESULT __hr = get_DesiredAccuracy(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PositionAccuracy DesiredAccuracy = {read=_scw_get_DesiredAccuracy, write=put_DesiredAccuracy};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PositionStatus _scw_get_LocationStatus() { Winapi::Commontypes::PositionStatus __r; HRESULT __hr = get_LocationStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PositionStatus LocationStatus = {read=_scw_get_LocationStatus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_MovementThreshold() { double __r; HRESULT __hr = get_MovementThreshold(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double MovementThreshold = {read=_scw_get_MovementThreshold, write=put_MovementThreshold};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ReportInterval() { unsigned __r; HRESULT __hr = get_ReportInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ReportInterval = {read=_scw_get_ReportInterval, write=put_ReportInterval};
};

__interface  INTERFACE_UUID("{96F5D3C1-B80F-460A-994D-A96C47A51AA4}") IGeolocatorWithScalarAccuracy  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DesiredAccuracyInMeters(Winapi::Commontypes::_di_IReference_1__Cardinal &__get_DesiredAccuracyInMeters_result) = 0 ;
	virtual HRESULT __safecall put_DesiredAccuracyInMeters(Winapi::Commontypes::_di_IReference_1__Cardinal value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Cardinal _scw_get_DesiredAccuracyInMeters() { Winapi::Commontypes::_di_IReference_1__Cardinal __r; HRESULT __hr = get_DesiredAccuracyInMeters(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Cardinal DesiredAccuracyInMeters = {read=_scw_get_DesiredAccuracyInMeters, write=put_DesiredAccuracyInMeters};
};

__interface  INTERFACE_UUID("{D1B42E6D-8891-43B4-AD36-27C6FE9A97B1}") IGeolocator2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AllowFallbackToConsentlessPositions() = 0 ;
};

__interface  INTERFACE_UUID("{F3524C93-E5C7-5B88-BEDB-D3E637CFF271}") AsyncOperationCompletedHandler_1__GeolocationAccessStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__GeolocationAccessStatus  : public AsyncOperationCompletedHandler_1__GeolocationAccessStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__GeolocationAccessStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{DE2B24D0-B726-57B1-A7C5-E5A13932B7DE}") IAsyncOperation_1__GeolocationAccessStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__GeolocationAccessStatus  : public IAsyncOperation_1__GeolocationAccessStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::GeolocationAccessStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__GeolocationAccessStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{A99B4206-263E-5308-82F2-31315C65135C}") IIterator_1__IGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D414D676-75D3-52FB-AA22-5829AD9FC4FF}") IIterator_1__IGeoposition  : public IIterator_1__IGeoposition_Base 
{
	virtual HRESULT __safecall get_Current(_di_IGeoposition &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIGeoposition items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeoposition _scw_get_Current() { _di_IGeoposition __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeoposition Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{135ED72D-75B1-5881-BE41-6FFEAA202044}") IIterable_1__IGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{FCB45D3B-0B5C-5C0D-82E9-4CFB295147B9}") IIterable_1__IGeoposition  : public IIterable_1__IGeoposition_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IGeoposition &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{C9FFE173-AC85-50AD-B262-90DCC4CA5165}") IVectorView_1__IGeoposition  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IGeoposition &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IGeoposition value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIGeoposition items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{6C67A1D1-9441-5AEE-B625-E3C1B5676A6D}") AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{272FE546-D773-5C98-867B-B7084A054EC5}") AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition  : public AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IGeoposition asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9454B533-EFB4-5385-8D3A-437FABC32D91}") IAsyncOperation_1__IVectorView_1__IGeoposition_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4E4265BF-AAF7-5109-A9E3-0CEDD1D201D0}") IAsyncOperation_1__IVectorView_1__IGeoposition  : public IAsyncOperation_1__IVectorView_1__IGeoposition_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IGeoposition &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IGeoposition Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9A8E7571-2DF5-4591-9F87-EB5FD894E9B7}") IGeolocatorStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall RequestAccessAsync(_di_IAsyncOperation_1__GeolocationAccessStatus &__RequestAccessAsync_result) = 0 ;
	virtual HRESULT __safecall GetGeopositionHistoryAsync(Winapi::Commontypes::DateTime startTime, _di_IAsyncOperation_1__IVectorView_1__IGeoposition &__GetGeopositionHistoryAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetGeopositionHistoryAsync(Winapi::Commontypes::DateTime startTime, Winapi::Commontypes::TimeSpan duration, _di_IAsyncOperation_1__IVectorView_1__IGeoposition &__GetGeopositionHistoryAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__BasicGeoposition  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::BasicGeoposition &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_Value() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{993011A2-FA1C-4631-A71D-0DBEB1250D9C}") IGeolocatorStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsDefaultGeopositionRecommended(bool &__get_IsDefaultGeopositionRecommended_result) = 0 ;
	virtual HRESULT __safecall put_DefaultGeoposition(_di_IReference_1__BasicGeoposition value) = 0 ;
	virtual HRESULT __safecall get_DefaultGeoposition(_di_IReference_1__BasicGeoposition &__get_DefaultGeoposition_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IReference_1__BasicGeoposition _scw_get_DefaultGeoposition() { _di_IReference_1__BasicGeoposition __r; HRESULT __hr = get_DefaultGeoposition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IReference_1__BasicGeoposition DefaultGeoposition = {read=_scw_get_DefaultGeoposition, write=put_DefaultGeoposition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDefaultGeopositionRecommended() { bool __r; HRESULT __hr = get_IsDefaultGeopositionRecommended(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDefaultGeopositionRecommended = {read=_scw_get_IsDefaultGeopositionRecommended};
};

__interface  INTERFACE_UUID("{39E45843-A7F9-4E63-92A7-BA0C28D124B1}") IGeocircle  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Center(Winapi::Commontypes::BasicGeoposition &__get_Center_result) = 0 ;
	virtual HRESULT __safecall get_Radius(double &__get_Radius_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BasicGeoposition _scw_get_Center() { Winapi::Commontypes::BasicGeoposition __r; HRESULT __hr = get_Center(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BasicGeoposition Center = {read=_scw_get_Center};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Radius() { double __r; HRESULT __hr = get_Radius(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Radius = {read=_scw_get_Radius};
};

__interface  INTERFACE_UUID("{AFD6531F-72B1-4F7D-87CC-4ED4C9849C05}") IGeocircleFactory  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall Create(Winapi::Commontypes::BasicGeoposition position, double radius, _di_IGeocircle &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystem(Winapi::Commontypes::BasicGeoposition position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeocircle &__CreateWithAltitudeReferenceSystem_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(Winapi::Commontypes::BasicGeoposition position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeocircle &__CreateWithAltitudeReferenceSystemAndSpatialReferenceId_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall Create(const Winapi::Commontypes::BasicGeoposition &position, double radius, _di_IGeocircle &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystem(const Winapi::Commontypes::BasicGeoposition &position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, _di_IGeocircle &__CreateWithAltitudeReferenceSystem_result) = 0 ;
	virtual HRESULT __safecall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(const Winapi::Commontypes::BasicGeoposition &position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId, _di_IGeocircle &__CreateWithAltitudeReferenceSystemAndSpatialReferenceId_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{B1877A76-9EF6-41AB-A0DD-793ECE76E2DE}") IGeovisit  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Position(_di_IGeoposition &__get_Position_result) = 0 ;
	virtual HRESULT __safecall get_StateChange(Winapi::Commontypes::VisitStateChange &__get_StateChange_result) = 0 ;
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeoposition _scw_get_Position() { _di_IGeoposition __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeoposition Position = {read=_scw_get_Position};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::VisitStateChange _scw_get_StateChange() { Winapi::Commontypes::VisitStateChange __r; HRESULT __hr = get_StateChange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::VisitStateChange StateChange = {read=_scw_get_StateChange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
};

__interface  INTERFACE_UUID("{CEB4D1FF-8B53-4968-BEED-4CECD029CE15}") IGeovisitStateChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Visit(_di_IGeovisit &__get_Visit_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeovisit _scw_get_Visit() { _di_IGeovisit __r; HRESULT __hr = get_Visit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeovisit Visit = {read=_scw_get_Visit};
};

__interface  INTERFACE_UUID("{76ABC5EA-EE4F-5391-9B50-DECA5D4311C9}") TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6654804C-3E53-5184-B739-3424F1648A6F}") TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs  : public TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IGeovisitMonitor sender, _di_IGeovisitStateChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{80118AAF-5944-4591-83C1-396647F54F2C}") IGeovisitMonitor  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MonitoringScope(Winapi::Commontypes::VisitMonitoringScope &__get_MonitoringScope_result) = 0 ;
	virtual HRESULT __safecall Start(Winapi::Commontypes::VisitMonitoringScope value) = 0 ;
	virtual HRESULT __safecall Stop() = 0 ;
	virtual HRESULT __safecall add_VisitStateChanged(_di_TypedEventHandler_2__IGeovisitMonitor__IGeovisitStateChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_VisitStateChanged_result) = 0 ;
	virtual HRESULT __safecall remove_VisitStateChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::VisitMonitoringScope _scw_get_MonitoringScope() { Winapi::Commontypes::VisitMonitoringScope __r; HRESULT __hr = get_MonitoringScope(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::VisitMonitoringScope MonitoringScope = {read=_scw_get_MonitoringScope};
};

__interface  INTERFACE_UUID("{B9BCE8CB-2E04-5269-9B03-1614D0C00B01}") AsyncOperationCompletedHandler_1__IGeovisit_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B303AADF-C706-506A-96CC-A3668EA00702}") AsyncOperationCompletedHandler_1__IGeovisit  : public AsyncOperationCompletedHandler_1__IGeovisit_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IGeovisit asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{8D1C950A-EFB9-5440-A6A7-820A839BE07B}") IAsyncOperation_1__IGeovisit_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0B367603-F91D-5148-94F8-036C96D33EB7}") IAsyncOperation_1__IGeovisit  : public IAsyncOperation_1__IGeovisit_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IGeovisit handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IGeovisit &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IGeovisit &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IGeovisit _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IGeovisit __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IGeovisit Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{BCF976A7-BBF2-4CDD-95CF-554C82EDFB87}") IGeovisitMonitorStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetLastReportAsync(_di_IAsyncOperation_1__IGeovisit &__GetLastReportAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{F525FC34-B058-5345-8E28-3E69E5F59070}") IIterator_1__IGeovisit_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3B4BC333-AA44-553D-8941-1203922ECB46}") IIterator_1__IGeovisit  : public IIterator_1__IGeovisit_Base 
{
	virtual HRESULT __safecall get_Current(_di_IGeovisit &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIGeovisit items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeovisit _scw_get_Current() { _di_IGeovisit __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeovisit Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D5800189-0F3F-54A0-A749-6000C1E12E58}") IIterable_1__IGeovisit_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CDB92F84-3EF7-54E8-B085-C64BBC02DA8E}") IIterable_1__IGeovisit  : public IIterable_1__IGeovisit_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IGeovisit &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{D80376A4-25FC-591D-A791-422EEE8C4414}") IVectorView_1__IGeovisit  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IGeovisit &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IGeovisit value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIGeovisit items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{EA770D9E-D1C9-454B-99B7-B2F8CDD2482F}") IGeovisitTriggerDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ReadReports(_di_IVectorView_1__IGeovisit &__ReadReports_result) = 0 ;
};

__interface  INTERFACE_UUID("{88225B39-8BE9-5C03-9714-8F1642D8A43F}") IIterator_1__IGeopoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A11ECDF0-F895-592E-992D-497BEAA6E362}") IIterator_1__IGeopoint  : public IIterator_1__IGeopoint_Base 
{
	virtual HRESULT __safecall get_Current(_di_IGeopoint &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIGeopoint items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeopoint _scw_get_Current() { _di_IGeopoint __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeopoint Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E7617FC9-2CC7-5BD1-BC5A-F47260834ED8}") IIterable_1__IGeopoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{768FFCFF-2CDA-53B3-ABE6-39C5CCE15163}") IIterable_1__IGeopoint  : public IIterable_1__IGeopoint_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IGeopoint &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{4B5F2F60-19B1-5566-9DF6-92A42235CBF9}") AsyncOperationCompletedHandler_1__IGeopoint_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{7B608E60-1D1C-54F7-AC4C-21521D88B0D0}") AsyncOperationCompletedHandler_1__IGeopoint  : public AsyncOperationCompletedHandler_1__IGeopoint_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IGeopoint asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{3723E070-C2AE-538F-846E-0F9D280310C0}") IAsyncOperation_1__IGeopoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{791AAF1D-97B7-58A5-BC49-226231EE1F08}") IAsyncOperation_1__IGeopoint  : public IAsyncOperation_1__IGeopoint_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IGeopoint handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IGeopoint &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IGeopoint &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IGeopoint _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IGeopoint __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IGeopoint Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{CF1D4402-4754-57E7-AAE0-69CA42CBD8F2}") IIterator_1__IGeopath_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BAA6EA4D-009D-53B3-8E2C-150C91322020}") IIterator_1__IGeopath  : public IIterator_1__IGeopath_Base 
{
	virtual HRESULT __safecall get_Current(_di_IGeopath &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIGeopath items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IGeopath _scw_get_Current() { _di_IGeopath __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IGeopath Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{246FCFBD-A881-5E8E-9908-C1B9EBDFEC78}") IIterable_1__IGeopath_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E5DA8BA4-E9D2-513A-9047-4CBF50B2B110}") IIterable_1__IGeopath  : public IIterable_1__IGeopath_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IGeopath &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{51CA54FA-7BF2-5ED8-AB08-E524017DCB41}") IVectorView_1__IGeopath  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IGeopath &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IGeopath value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIGeopath items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{5FB15268-9174-52C4-BEB4-2BC8E7098895}") IVector_1__IGeopath  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IGeopath &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IGeopath &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IGeopath value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IGeopath value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IGeopath value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IGeopath value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIGeopath items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIGeopath items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeopoint : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopointFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopointFactory> inherited;
	
public:
	static _di_IGeopoint __fastcall Create(const Winapi::Commontypes::BasicGeoposition &position);
	static _di_IGeopoint __fastcall CreateWithAltitudeReferenceSystem(const Winapi::Commontypes::BasicGeoposition &position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem);
	static _di_IGeopoint __fastcall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(const Winapi::Commontypes::BasicGeoposition &position, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId);
public:
	/* TObject.Create */ inline __fastcall TGeopoint() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopointFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeopoint() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeopath : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopathFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopathFactory> inherited;
	
public:
	static _di_IGeopath __fastcall Create(_di_IIterable_1__BasicGeoposition positions);
	static _di_IGeopath __fastcall CreateWithAltitudeReference(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem);
	static _di_IGeopath __fastcall CreateWithAltitudeReferenceAndSpatialReference(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId);
public:
	/* TObject.Create */ inline __fastcall TGeopath() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeopathFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeopath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeoboundingBox : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_IGeoboundingBoxFactory,_di_IGeoboundingBoxStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_IGeoboundingBoxFactory,_di_IGeoboundingBoxStatics> inherited;
	
public:
	static _di_IGeoboundingBox __fastcall TryCompute(_di_IIterable_1__BasicGeoposition positions)/* overload */;
	static _di_IGeoboundingBox __fastcall TryCompute(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeRefSystem)/* overload */;
	static _di_IGeoboundingBox __fastcall TryCompute(_di_IIterable_1__BasicGeoposition positions, Winapi::Commontypes::AltitudeReferenceSystem altitudeRefSystem, unsigned spatialReferenceId)/* overload */;
	static _di_IGeoboundingBox __fastcall Create(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner);
	static _di_IGeoboundingBox __fastcall CreateWithAltitudeReference(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem);
	static _di_IGeoboundingBox __fastcall CreateWithAltitudeReferenceAndSpatialReference(const Winapi::Commontypes::BasicGeoposition &northwestCorner, const Winapi::Commontypes::BasicGeoposition &southeastCorner, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId);
public:
	/* TObject.Create */ inline __fastcall TGeoboundingBox() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_IGeoboundingBoxFactory,_di_IGeoboundingBoxStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeoboundingBox() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeolocator : public System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IGeolocatorStatics,_di_IGeolocatorStatics2,_di_IGeolocator>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IGeolocatorStatics,_di_IGeolocatorStatics2,_di_IGeolocator> inherited;
	
public:
	static _di_IAsyncOperation_1__GeolocationAccessStatus __fastcall RequestAccessAsync();
	static _di_IAsyncOperation_1__IVectorView_1__IGeoposition __fastcall GetGeopositionHistoryAsync(const Winapi::Commontypes::DateTime &startTime)/* overload */;
	static _di_IAsyncOperation_1__IVectorView_1__IGeoposition __fastcall GetGeopositionHistoryAsync(const Winapi::Commontypes::DateTime &startTime, const Winapi::Commontypes::TimeSpan &duration)/* overload */;
	static bool __fastcall get_IsDefaultGeopositionRecommended();
	static void __fastcall put_DefaultGeoposition(_di_IReference_1__BasicGeoposition value);
	static _di_IReference_1__BasicGeoposition __fastcall get_DefaultGeoposition();
	/* static */ __property _di_IReference_1__BasicGeoposition DefaultGeoposition = {read=get_DefaultGeoposition, write=put_DefaultGeoposition};
	/* static */ __property bool IsDefaultGeopositionRecommended = {read=get_IsDefaultGeopositionRecommended, nodefault};
public:
	/* TObject.Create */ inline __fastcall TGeolocator() : System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IGeolocatorStatics,_di_IGeolocatorStatics2,_di_IGeolocator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeolocator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeocircle : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeocircleFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeocircleFactory> inherited;
	
public:
	static _di_IGeocircle __fastcall Create(const Winapi::Commontypes::BasicGeoposition &position, double radius);
	static _di_IGeocircle __fastcall CreateWithAltitudeReferenceSystem(const Winapi::Commontypes::BasicGeoposition &position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem);
	static _di_IGeocircle __fastcall CreateWithAltitudeReferenceSystemAndSpatialReferenceId(const Winapi::Commontypes::BasicGeoposition &position, double radius, Winapi::Commontypes::AltitudeReferenceSystem altitudeReferenceSystem, unsigned spatialReferenceId);
public:
	/* TObject.Create */ inline __fastcall TGeocircle() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IGeocircleFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeocircle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGeovisitMonitor : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_IGeovisitMonitorStatics,_di_IGeovisitMonitor>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_IGeovisitMonitorStatics,_di_IGeovisitMonitor> inherited;
	
public:
	static _di_IAsyncOperation_1__IGeovisit __fastcall GetLastReportAsync();
public:
	/* TObject.Create */ inline __fastcall TGeovisitMonitor() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_IGeovisitMonitorStatics,_di_IGeovisitMonitor>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGeovisitMonitor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Geolocation */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_GeolocationHPP
