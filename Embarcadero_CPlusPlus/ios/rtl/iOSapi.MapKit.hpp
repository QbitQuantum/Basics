// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.MapKit.pas' rev: 34.00 (iOS)

#ifndef Iosapi_MapkitHPP
#define Iosapi_MapkitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.Dispatch.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.CoreLocation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Mapkit
{
//-- forward type declarations -----------------------------------------------
struct MKCoordinateSpan;
struct MKCoordinateRegion;
struct MKMapPoint;
struct MKMapSize;
struct MKMapRect;
struct MKTileOverlayPath;
__interface DELPHIINTERFACE MKAnnotationViewClass;
typedef System::DelphiInterface<MKAnnotationViewClass> _di_MKAnnotationViewClass;
__interface DELPHIINTERFACE MKAnnotationView;
typedef System::DelphiInterface<MKAnnotationView> _di_MKAnnotationView;
class DELPHICLASS TMKAnnotationView;
__interface DELPHIINTERFACE MKDistanceFormatterClass;
typedef System::DelphiInterface<MKDistanceFormatterClass> _di_MKDistanceFormatterClass;
__interface DELPHIINTERFACE MKDistanceFormatter;
typedef System::DelphiInterface<MKDistanceFormatter> _di_MKDistanceFormatter;
class DELPHICLASS TMKDistanceFormatter;
__interface DELPHIINTERFACE MKPlacemarkClass;
typedef System::DelphiInterface<MKPlacemarkClass> _di_MKPlacemarkClass;
__interface DELPHIINTERFACE MKPlacemark;
typedef System::DelphiInterface<MKPlacemark> _di_MKPlacemark;
class DELPHICLASS TMKPlacemark;
__interface DELPHIINTERFACE MKMapItemClass;
typedef System::DelphiInterface<MKMapItemClass> _di_MKMapItemClass;
__interface DELPHIINTERFACE MKMapItem;
typedef System::DelphiInterface<MKMapItem> _di_MKMapItem;
class DELPHICLASS TMKMapItem;
__interface DELPHIINTERFACE MKOverlayRendererClass;
typedef System::DelphiInterface<MKOverlayRendererClass> _di_MKOverlayRendererClass;
__interface DELPHIINTERFACE MKOverlayRenderer;
typedef System::DelphiInterface<MKOverlayRenderer> _di_MKOverlayRenderer;
class DELPHICLASS TMKOverlayRenderer;
__interface DELPHIINTERFACE MKOverlayViewClass;
typedef System::DelphiInterface<MKOverlayViewClass> _di_MKOverlayViewClass;
__interface DELPHIINTERFACE MKOverlayView;
typedef System::DelphiInterface<MKOverlayView> _di_MKOverlayView;
class DELPHICLASS TMKOverlayView;
__interface DELPHIINTERFACE MKUserLocationClass;
typedef System::DelphiInterface<MKUserLocationClass> _di_MKUserLocationClass;
__interface DELPHIINTERFACE MKUserLocation;
typedef System::DelphiInterface<MKUserLocation> _di_MKUserLocation;
class DELPHICLASS TMKUserLocation;
__interface DELPHIINTERFACE MKMapCameraClass;
typedef System::DelphiInterface<MKMapCameraClass> _di_MKMapCameraClass;
__interface DELPHIINTERFACE MKMapCamera;
typedef System::DelphiInterface<MKMapCamera> _di_MKMapCamera;
class DELPHICLASS TMKMapCamera;
__interface DELPHIINTERFACE MKMapViewClass;
typedef System::DelphiInterface<MKMapViewClass> _di_MKMapViewClass;
__interface DELPHIINTERFACE MKMapView;
typedef System::DelphiInterface<MKMapView> _di_MKMapView;
class DELPHICLASS TMKMapView;
__interface DELPHIINTERFACE MKPinAnnotationViewClass;
typedef System::DelphiInterface<MKPinAnnotationViewClass> _di_MKPinAnnotationViewClass;
__interface DELPHIINTERFACE MKPinAnnotationView;
typedef System::DelphiInterface<MKPinAnnotationView> _di_MKPinAnnotationView;
class DELPHICLASS TMKPinAnnotationView;
__interface DELPHIINTERFACE MKShapeClass;
typedef System::DelphiInterface<MKShapeClass> _di_MKShapeClass;
__interface DELPHIINTERFACE MKShape;
typedef System::DelphiInterface<MKShape> _di_MKShape;
class DELPHICLASS TMKShape;
__interface DELPHIINTERFACE MKPointAnnotationClass;
typedef System::DelphiInterface<MKPointAnnotationClass> _di_MKPointAnnotationClass;
__interface DELPHIINTERFACE MKPointAnnotation;
typedef System::DelphiInterface<MKPointAnnotation> _di_MKPointAnnotation;
class DELPHICLASS TMKPointAnnotation;
__interface DELPHIINTERFACE MKMultiPointClass;
typedef System::DelphiInterface<MKMultiPointClass> _di_MKMultiPointClass;
__interface DELPHIINTERFACE MKMultiPoint;
typedef System::DelphiInterface<MKMultiPoint> _di_MKMultiPoint;
class DELPHICLASS TMKMultiPoint;
__interface DELPHIINTERFACE MKPolylineClass;
typedef System::DelphiInterface<MKPolylineClass> _di_MKPolylineClass;
__interface DELPHIINTERFACE MKPolyline;
typedef System::DelphiInterface<MKPolyline> _di_MKPolyline;
class DELPHICLASS TMKPolyline;
__interface DELPHIINTERFACE MKPolygonClass;
typedef System::DelphiInterface<MKPolygonClass> _di_MKPolygonClass;
__interface DELPHIINTERFACE MKPolygon;
typedef System::DelphiInterface<MKPolygon> _di_MKPolygon;
class DELPHICLASS TMKPolygon;
__interface DELPHIINTERFACE MKCircleClass;
typedef System::DelphiInterface<MKCircleClass> _di_MKCircleClass;
__interface DELPHIINTERFACE MKCircle;
typedef System::DelphiInterface<MKCircle> _di_MKCircle;
class DELPHICLASS TMKCircle;
__interface DELPHIINTERFACE MKGeodesicPolylineClass;
typedef System::DelphiInterface<MKGeodesicPolylineClass> _di_MKGeodesicPolylineClass;
__interface DELPHIINTERFACE MKGeodesicPolyline;
typedef System::DelphiInterface<MKGeodesicPolyline> _di_MKGeodesicPolyline;
class DELPHICLASS TMKGeodesicPolyline;
__interface DELPHIINTERFACE MKOverlayPathRendererClass;
typedef System::DelphiInterface<MKOverlayPathRendererClass> _di_MKOverlayPathRendererClass;
__interface DELPHIINTERFACE MKOverlayPathRenderer;
typedef System::DelphiInterface<MKOverlayPathRenderer> _di_MKOverlayPathRenderer;
class DELPHICLASS TMKOverlayPathRenderer;
__interface DELPHIINTERFACE MKPolygonRendererClass;
typedef System::DelphiInterface<MKPolygonRendererClass> _di_MKPolygonRendererClass;
__interface DELPHIINTERFACE MKPolygonRenderer;
typedef System::DelphiInterface<MKPolygonRenderer> _di_MKPolygonRenderer;
class DELPHICLASS TMKPolygonRenderer;
__interface DELPHIINTERFACE MKPolylineRendererClass;
typedef System::DelphiInterface<MKPolylineRendererClass> _di_MKPolylineRendererClass;
__interface DELPHIINTERFACE MKPolylineRenderer;
typedef System::DelphiInterface<MKPolylineRenderer> _di_MKPolylineRenderer;
class DELPHICLASS TMKPolylineRenderer;
__interface DELPHIINTERFACE MKCircleRendererClass;
typedef System::DelphiInterface<MKCircleRendererClass> _di_MKCircleRendererClass;
__interface DELPHIINTERFACE MKCircleRenderer;
typedef System::DelphiInterface<MKCircleRenderer> _di_MKCircleRenderer;
class DELPHICLASS TMKCircleRenderer;
__interface DELPHIINTERFACE MKLocalSearchRequestClass;
typedef System::DelphiInterface<MKLocalSearchRequestClass> _di_MKLocalSearchRequestClass;
__interface DELPHIINTERFACE MKLocalSearchRequest;
typedef System::DelphiInterface<MKLocalSearchRequest> _di_MKLocalSearchRequest;
class DELPHICLASS TMKLocalSearchRequest;
__interface DELPHIINTERFACE MKLocalSearchResponseClass;
typedef System::DelphiInterface<MKLocalSearchResponseClass> _di_MKLocalSearchResponseClass;
__interface DELPHIINTERFACE MKLocalSearchResponse;
typedef System::DelphiInterface<MKLocalSearchResponse> _di_MKLocalSearchResponse;
class DELPHICLASS TMKLocalSearchResponse;
__interface DELPHIINTERFACE MKLocalSearchClass;
typedef System::DelphiInterface<MKLocalSearchClass> _di_MKLocalSearchClass;
__interface DELPHIINTERFACE MKLocalSearch;
typedef System::DelphiInterface<MKLocalSearch> _di_MKLocalSearch;
class DELPHICLASS TMKLocalSearch;
__interface DELPHIINTERFACE MKDirectionsRequestClass;
typedef System::DelphiInterface<MKDirectionsRequestClass> _di_MKDirectionsRequestClass;
__interface DELPHIINTERFACE MKDirectionsRequest;
typedef System::DelphiInterface<MKDirectionsRequest> _di_MKDirectionsRequest;
class DELPHICLASS TMKDirectionsRequest;
__interface DELPHIINTERFACE MKDirectionsResponseClass;
typedef System::DelphiInterface<MKDirectionsResponseClass> _di_MKDirectionsResponseClass;
__interface DELPHIINTERFACE MKDirectionsResponse;
typedef System::DelphiInterface<MKDirectionsResponse> _di_MKDirectionsResponse;
class DELPHICLASS TMKDirectionsResponse;
__interface DELPHIINTERFACE MKETAResponseClass;
typedef System::DelphiInterface<MKETAResponseClass> _di_MKETAResponseClass;
__interface DELPHIINTERFACE MKETAResponse;
typedef System::DelphiInterface<MKETAResponse> _di_MKETAResponse;
class DELPHICLASS TMKETAResponse;
__interface DELPHIINTERFACE MKDirectionsClass;
typedef System::DelphiInterface<MKDirectionsClass> _di_MKDirectionsClass;
__interface DELPHIINTERFACE MKDirections;
typedef System::DelphiInterface<MKDirections> _di_MKDirections;
class DELPHICLASS TMKDirections;
__interface DELPHIINTERFACE MKRouteClass;
typedef System::DelphiInterface<MKRouteClass> _di_MKRouteClass;
__interface DELPHIINTERFACE MKRoute;
typedef System::DelphiInterface<MKRoute> _di_MKRoute;
class DELPHICLASS TMKRoute;
__interface DELPHIINTERFACE MKRouteStepClass;
typedef System::DelphiInterface<MKRouteStepClass> _di_MKRouteStepClass;
__interface DELPHIINTERFACE MKRouteStep;
typedef System::DelphiInterface<MKRouteStep> _di_MKRouteStep;
class DELPHICLASS TMKRouteStep;
__interface DELPHIINTERFACE MKMapSnapshotOptionsClass;
typedef System::DelphiInterface<MKMapSnapshotOptionsClass> _di_MKMapSnapshotOptionsClass;
__interface DELPHIINTERFACE MKMapSnapshotOptions;
typedef System::DelphiInterface<MKMapSnapshotOptions> _di_MKMapSnapshotOptions;
class DELPHICLASS TMKMapSnapshotOptions;
__interface DELPHIINTERFACE MKMapSnapshotClass;
typedef System::DelphiInterface<MKMapSnapshotClass> _di_MKMapSnapshotClass;
__interface DELPHIINTERFACE MKMapSnapshot;
typedef System::DelphiInterface<MKMapSnapshot> _di_MKMapSnapshot;
class DELPHICLASS TMKMapSnapshot;
__interface DELPHIINTERFACE MKMapSnapshotterClass;
typedef System::DelphiInterface<MKMapSnapshotterClass> _di_MKMapSnapshotterClass;
__interface DELPHIINTERFACE MKMapSnapshotter;
typedef System::DelphiInterface<MKMapSnapshotter> _di_MKMapSnapshotter;
class DELPHICLASS TMKMapSnapshotter;
__interface DELPHIINTERFACE MKTileOverlayClass;
typedef System::DelphiInterface<MKTileOverlayClass> _di_MKTileOverlayClass;
__interface DELPHIINTERFACE MKTileOverlay;
typedef System::DelphiInterface<MKTileOverlay> _di_MKTileOverlay;
class DELPHICLASS TMKTileOverlay;
__interface DELPHIINTERFACE MKTileOverlayRendererClass;
typedef System::DelphiInterface<MKTileOverlayRendererClass> _di_MKTileOverlayRendererClass;
__interface DELPHIINTERFACE MKTileOverlayRenderer;
typedef System::DelphiInterface<MKTileOverlayRenderer> _di_MKTileOverlayRenderer;
class DELPHICLASS TMKTileOverlayRenderer;
__interface DELPHIINTERFACE MKReverseGeocoderClass;
typedef System::DelphiInterface<MKReverseGeocoderClass> _di_MKReverseGeocoderClass;
__interface DELPHIINTERFACE MKReverseGeocoder;
typedef System::DelphiInterface<MKReverseGeocoder> _di_MKReverseGeocoder;
class DELPHICLASS TMKReverseGeocoder;
__interface DELPHIINTERFACE MKOverlayPathViewClass;
typedef System::DelphiInterface<MKOverlayPathViewClass> _di_MKOverlayPathViewClass;
__interface DELPHIINTERFACE MKOverlayPathView;
typedef System::DelphiInterface<MKOverlayPathView> _di_MKOverlayPathView;
class DELPHICLASS TMKOverlayPathView;
__interface DELPHIINTERFACE MKPolygonViewClass;
typedef System::DelphiInterface<MKPolygonViewClass> _di_MKPolygonViewClass;
__interface DELPHIINTERFACE MKPolygonView;
typedef System::DelphiInterface<MKPolygonView> _di_MKPolygonView;
class DELPHICLASS TMKPolygonView;
__interface DELPHIINTERFACE MKPolylineViewClass;
typedef System::DelphiInterface<MKPolylineViewClass> _di_MKPolylineViewClass;
__interface DELPHIINTERFACE MKPolylineView;
typedef System::DelphiInterface<MKPolylineView> _di_MKPolylineView;
class DELPHICLASS TMKPolylineView;
__interface DELPHIINTERFACE MKCircleViewClass;
typedef System::DelphiInterface<MKCircleViewClass> _di_MKCircleViewClass;
__interface DELPHIINTERFACE MKCircleView;
typedef System::DelphiInterface<MKCircleView> _di_MKCircleView;
class DELPHICLASS TMKCircleView;
__interface DELPHIINTERFACE MKUserTrackingBarButtonItemClass;
typedef System::DelphiInterface<MKUserTrackingBarButtonItemClass> _di_MKUserTrackingBarButtonItemClass;
__interface DELPHIINTERFACE MKUserTrackingBarButtonItem;
typedef System::DelphiInterface<MKUserTrackingBarButtonItem> _di_MKUserTrackingBarButtonItem;
class DELPHICLASS TMKUserTrackingBarButtonItem;
__interface DELPHIINTERFACE MKAnnotation;
typedef System::DelphiInterface<MKAnnotation> _di_MKAnnotation;
__interface DELPHIINTERFACE MKOverlay;
typedef System::DelphiInterface<MKOverlay> _di_MKOverlay;
__interface DELPHIINTERFACE MKMapViewDelegate;
typedef System::DelphiInterface<MKMapViewDelegate> _di_MKMapViewDelegate;
__interface DELPHIINTERFACE MKReverseGeocoderDelegate;
typedef System::DelphiInterface<MKReverseGeocoderDelegate> _di_MKReverseGeocoderDelegate;
//-- type declarations -------------------------------------------------------
typedef unsigned long MKAnnotationViewDragState;

typedef unsigned long MKDistanceFormatterUnits;

typedef unsigned long MKDistanceFormatterUnitStyle;

struct DECLSPEC_DRECORD MKCoordinateSpan
{
public:
	double latitudeDelta;
	double longitudeDelta;
};


typedef MKCoordinateSpan *PMKCoordinateSpan;

struct DECLSPEC_DRECORD MKCoordinateRegion
{
public:
	Iosapi::Corelocation::CLLocationCoordinate2D center;
	MKCoordinateSpan span;
};


typedef MKCoordinateRegion *PMKCoordinateRegion;

struct DECLSPEC_DRECORD MKMapPoint
{
public:
	double x;
	double y;
};


typedef MKMapPoint *PMKMapPoint;

struct DECLSPEC_DRECORD MKMapSize
{
public:
	double width;
	double height;
};


typedef MKMapSize *PMKMapSize;

struct DECLSPEC_DRECORD MKMapRect
{
public:
	MKMapPoint origin;
	MKMapSize size;
};


typedef MKMapRect *PMKMapRect;

typedef double MKZoomScale;

typedef unsigned long MKMapType;

typedef unsigned long MKErrorCode;

typedef long MKUserTrackingMode;

typedef long MKOverlayLevel;

typedef unsigned long MKPinAnnotationColor;

typedef void __fastcall (__closure *MKLocalSearchCompletionHandler)(_di_MKLocalSearchResponse param1, Iosapi::Foundation::_di_NSError param2);

typedef unsigned long MKDirectionsTransportType;

typedef void __fastcall (__closure *MKDirectionsHandler)(_di_MKDirectionsResponse param1, Iosapi::Foundation::_di_NSError param2);

typedef void __fastcall (__closure *MKETAHandler)(_di_MKETAResponse param1, Iosapi::Foundation::_di_NSError param2);

typedef void __fastcall (__closure *MKMapSnapshotCompletionHandler)(_di_MKMapSnapshot snapshot, Iosapi::Foundation::_di_NSError error);

struct DECLSPEC_DRECORD MKTileOverlayPath
{
public:
	long x;
	long y;
	long z;
	double contentScaleFactor;
};


typedef MKTileOverlayPath *PMKTileOverlayPath;

typedef void __fastcall (__closure *TMapKitResult)(Iosapi::Foundation::_di_NSData param1, Iosapi::Foundation::_di_NSError param2);

__interface  INTERFACE_UUID("{A99E7F86-1548-47C0-B153-9F7191CD6B13}") MKAnnotationViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{FA6EE792-31E2-4E88-8B32-7D74F047DCC8}") MKAnnotationView  : public Iosapi::Uikit::UIView 
{
	virtual void * __cdecl initWithAnnotation(void * annotation, Iosapi::Foundation::_di_NSString reuseIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl reuseIdentifier() = 0 ;
	virtual void __cdecl prepareForReuse() = 0 ;
	virtual void __cdecl setAnnotation(void * annotation) = 0 ;
	virtual void * __cdecl annotation() = 0 ;
	virtual void __cdecl setImage(Iosapi::Uikit::_di_UIImage image) = 0 ;
	virtual Iosapi::Uikit::_di_UIImage __cdecl image() = 0 ;
	virtual void __cdecl setCenterOffset(Iosapi::Foundation::NSPoint centerOffset) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl centerOffset() = 0 ;
	virtual void __cdecl setCalloutOffset(Iosapi::Foundation::NSPoint calloutOffset) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl calloutOffset() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	virtual void __cdecl setSelected(bool selected) = 0 ;
	virtual bool __cdecl isSelected() = 0 ;
	virtual void __cdecl setSelectedAnimated(bool selected, bool animated) = 0 ;
	virtual void __cdecl setCanShowCallout(bool canShowCallout) = 0 ;
	virtual bool __cdecl canShowCallout() = 0 ;
	virtual void __cdecl setLeftCalloutAccessoryView(Iosapi::Uikit::_di_UIView leftCalloutAccessoryView) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl leftCalloutAccessoryView() = 0 ;
	virtual void __cdecl setRightCalloutAccessoryView(Iosapi::Uikit::_di_UIView rightCalloutAccessoryView) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl rightCalloutAccessoryView() = 0 ;
	virtual void __cdecl setDraggable(bool draggable) = 0 ;
	virtual bool __cdecl isDraggable() = 0 ;
	virtual void __cdecl setDragState(unsigned long dragState) = 0 ;
	virtual unsigned long __cdecl dragState() = 0 ;
	virtual void __cdecl setDragStateAnimated(unsigned long newDragState, bool animated) = 0 ;
};

class PASCALIMPLEMENTATION TMKAnnotationView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKAnnotationViewClass,_di_MKAnnotationView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKAnnotationViewClass,_di_MKAnnotationView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKAnnotationView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKAnnotationViewClass,_di_MKAnnotationView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKAnnotationView() { }
	
};


__interface  INTERFACE_UUID("{B45509B8-532D-41AA-AAF6-67BBAFB713CD}") MKDistanceFormatterClass  : public Iosapi::Foundation::NSFormatterClass 
{
	
};

__interface  INTERFACE_UUID("{2D7F9109-D75B-4929-BF81-151E51688F72}") MKDistanceFormatter  : public Iosapi::Foundation::NSFormatter 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl stringFromDistance(double distance) = 0 ;
	virtual double __cdecl distanceFromString(Iosapi::Foundation::_di_NSString distance) = 0 ;
	virtual void __cdecl setLocale(Iosapi::Foundation::_di_NSLocale locale) = 0 ;
	virtual Iosapi::Foundation::_di_NSLocale __cdecl locale() = 0 ;
	virtual void __cdecl setUnits(unsigned long units) = 0 ;
	virtual unsigned long __cdecl units() = 0 ;
	virtual void __cdecl setUnitStyle(unsigned long unitStyle) = 0 ;
	virtual unsigned long __cdecl unitStyle() = 0 ;
};

class PASCALIMPLEMENTATION TMKDistanceFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_MKDistanceFormatterClass,_di_MKDistanceFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKDistanceFormatterClass,_di_MKDistanceFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKDistanceFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKDistanceFormatterClass,_di_MKDistanceFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKDistanceFormatter() { }
	
};


__interface  INTERFACE_UUID("{979793F2-6ECA-4B35-89F4-6F0538A7EA99}") MKPlacemarkClass  : public Iosapi::Corelocation::CLPlacemarkClass 
{
	
};

__interface  INTERFACE_UUID("{9F645657-2063-4553-9E48-46001C318F08}") MKPlacemark  : public Iosapi::Corelocation::CLPlacemark 
{
	virtual void * __cdecl initWithCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate, Iosapi::Foundation::_di_NSDictionary addressDictionary) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl countryCode() = 0 ;
};

class PASCALIMPLEMENTATION TMKPlacemark : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPlacemarkClass,_di_MKPlacemark>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPlacemarkClass,_di_MKPlacemark> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPlacemark(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPlacemarkClass,_di_MKPlacemark>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPlacemark() { }
	
};


__interface  INTERFACE_UUID("{557E6EB9-2FE9-461E-B5A6-7E18E0237A2B}") MKMapItemClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MKMapItem __cdecl mapItemForCurrentLocation() = 0 ;
	virtual bool __cdecl openMapsWithItems(Iosapi::Foundation::_di_NSArray mapItems, Iosapi::Foundation::_di_NSDictionary launchOptions) = 0 ;
};

__interface  INTERFACE_UUID("{281F38CB-2702-4145-A689-1E87B259E4CF}") MKMapItem  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MKPlacemark __cdecl placemark() = 0 ;
	virtual bool __cdecl isCurrentLocation() = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setPhoneNumber(Iosapi::Foundation::_di_NSString phoneNumber) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl phoneNumber() = 0 ;
	virtual void __cdecl setUrl(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl url() = 0 ;
	virtual void * __cdecl initWithPlacemark(_di_MKPlacemark placemark) = 0 ;
	virtual bool __cdecl openInMapsWithLaunchOptions(Iosapi::Foundation::_di_NSDictionary launchOptions) = 0 ;
};

class PASCALIMPLEMENTATION TMKMapItem : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapItemClass,_di_MKMapItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapItemClass,_di_MKMapItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapItemClass,_di_MKMapItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapItem() { }
	
};


__interface  INTERFACE_UUID("{CCE87C23-BBB6-4DAA-B4F5-92EB6B5B48C8}") MKOverlayRendererClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{395ACCE8-4980-4D1C-9039-C6A945A77628}") MKOverlayRenderer  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithOverlay(void * overlay) = 0 ;
	virtual void * __cdecl overlay() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl pointForMapPoint(MKMapPoint mapPoint) = 0 ;
	virtual MKMapPoint __cdecl mapPointForPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForMapRect(MKMapRect mapRect) = 0 ;
	virtual MKMapRect __cdecl mapRectForRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual bool __cdecl canDrawMapRect(MKMapRect mapRect, double zoomScale) = 0 ;
	virtual void __cdecl drawMapRect(MKMapRect mapRect, double zoomScale, void * inContext) = 0 ;
	virtual void __cdecl setNeedsDisplay() = 0 ;
	virtual void __cdecl setNeedsDisplayInMapRect(MKMapRect mapRect) = 0 ;
	virtual void __cdecl setNeedsDisplayInMapRectZoomScale(MKMapRect mapRect, double zoomScale) = 0 ;
	virtual void __cdecl setAlpha(double alpha) = 0 ;
	virtual double __cdecl alpha() = 0 ;
	virtual double __cdecl contentScaleFactor() = 0 ;
};

class PASCALIMPLEMENTATION TMKOverlayRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayRendererClass,_di_MKOverlayRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayRendererClass,_di_MKOverlayRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKOverlayRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayRendererClass,_di_MKOverlayRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKOverlayRenderer() { }
	
};


__interface  INTERFACE_UUID("{72917955-824D-4D99-A43A-B96ED45FE055}") MKOverlayViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{99276C14-DCCF-4B0B-A542-54205872D68F}") MKOverlayView  : public Iosapi::Uikit::UIView 
{
	virtual void * __cdecl initWithOverlay(void * overlay) = 0 ;
	virtual void * __cdecl overlay() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl pointForMapPoint(MKMapPoint mapPoint) = 0 ;
	virtual MKMapPoint __cdecl mapPointForPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForMapRect(MKMapRect mapRect) = 0 ;
	virtual MKMapRect __cdecl mapRectForRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual bool __cdecl canDrawMapRect(MKMapRect mapRect, double zoomScale) = 0 ;
	virtual void __cdecl drawMapRect(MKMapRect mapRect, double zoomScale, void * inContext) = 0 ;
	virtual void __cdecl setNeedsDisplayInMapRect(MKMapRect mapRect) = 0 ;
	virtual void __cdecl setNeedsDisplayInMapRectZoomScale(MKMapRect mapRect, double zoomScale) = 0 ;
};

class PASCALIMPLEMENTATION TMKOverlayView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayViewClass,_di_MKOverlayView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayViewClass,_di_MKOverlayView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKOverlayView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayViewClass,_di_MKOverlayView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKOverlayView() { }
	
};


__interface  INTERFACE_UUID("{12FC32D7-0C10-445F-8934-322EB5A29E4C}") MKUserLocationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{655D6A38-F0CC-46E2-84FF-BFAE4AE1B707}") MKUserLocation  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl isUpdating() = 0 ;
	virtual Iosapi::Corelocation::_di_CLLocation __cdecl location() = 0 ;
	virtual Iosapi::Corelocation::_di_CLHeading __cdecl heading() = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual void __cdecl setSubtitle(Iosapi::Foundation::_di_NSString subtitle) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subtitle() = 0 ;
};

class PASCALIMPLEMENTATION TMKUserLocation : public Macapi::Objectivec::TOCGenericImport__2<_di_MKUserLocationClass,_di_MKUserLocation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKUserLocationClass,_di_MKUserLocation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKUserLocation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKUserLocationClass,_di_MKUserLocation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKUserLocation() { }
	
};


__interface  INTERFACE_UUID("{0957DE81-1791-455B-989D-57D72E47A111}") MKMapCameraClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl camera() = 0 ;
	virtual void * __cdecl cameraLookingAtCenterCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D centerCoordinate, Iosapi::Corelocation::CLLocationCoordinate2D fromEyeCoordinate, double eyeAltitude) = 0 ;
};

__interface  INTERFACE_UUID("{8F128711-4D1E-4DA4-8A69-5A8DEA356E2F}") MKMapCamera  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setCenterCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D centerCoordinate) = 0 ;
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl centerCoordinate() = 0 ;
	virtual void __cdecl setHeading(double heading) = 0 ;
	virtual double __cdecl heading() = 0 ;
	virtual void __cdecl setPitch(double pitch) = 0 ;
	virtual double __cdecl pitch() = 0 ;
	virtual void __cdecl setAltitude(double altitude) = 0 ;
	virtual double __cdecl altitude() = 0 ;
};

class PASCALIMPLEMENTATION TMKMapCamera : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapCameraClass,_di_MKMapCamera>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapCameraClass,_di_MKMapCamera> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapCamera(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapCameraClass,_di_MKMapCamera>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapCamera() { }
	
};


__interface  INTERFACE_UUID("{EA188A7C-CA50-4C61-AE70-C595F93EA358}") MKMapViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{BBB29AD7-7E9C-4232-8816-1CA83BBEDA75}") MKMapView  : public Iosapi::Uikit::UIView 
{
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setMapType(unsigned long mapType) = 0 ;
	virtual unsigned long __cdecl mapType() = 0 ;
	virtual void __cdecl setRegion(MKCoordinateRegion region) = 0 ;
	virtual MKCoordinateRegion __cdecl region() = 0 ;
	virtual void __cdecl setRegionAnimated(MKCoordinateRegion region, bool animated) = 0 ;
	virtual void __cdecl setCenterCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D centerCoordinate) = 0 ;
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl centerCoordinate() = 0 ;
	virtual void __cdecl setCenterCoordinateAnimated(Iosapi::Corelocation::CLLocationCoordinate2D coordinate, bool animated) = 0 ;
	virtual MKCoordinateRegion __cdecl regionThatFits(MKCoordinateRegion region) = 0 ;
	virtual void __cdecl setVisibleMapRect(MKMapRect visibleMapRect) = 0 ;
	virtual MKMapRect __cdecl visibleMapRect() = 0 ;
	virtual void __cdecl setVisibleMapRectAnimated(MKMapRect mapRect, bool animated) = 0 ;
	virtual MKMapRect __cdecl mapRectThatFits(MKMapRect mapRect) = 0 ;
	virtual void __cdecl setVisibleMapRectEdgePaddingAnimated(MKMapRect mapRect, Iosapi::Uikit::UIEdgeInsets edgePadding, bool animated) = 0 ;
	virtual MKMapRect __cdecl mapRectThatFitsEdgePadding(MKMapRect mapRect, Iosapi::Uikit::UIEdgeInsets edgePadding) = 0 ;
	virtual void __cdecl setCamera(_di_MKMapCamera camera) = 0 ;
	virtual _di_MKMapCamera __cdecl camera() = 0 ;
	virtual void __cdecl setCameraAnimated(_di_MKMapCamera camera, bool animated) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl convertCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate, Iosapi::Uikit::_di_UIView toPointToView) = 0 ;
	HIDESBASE virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl convertPoint(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIView toCoordinateFromView) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl convertRegion(MKCoordinateRegion region, Iosapi::Uikit::_di_UIView toRectToView) = 0 ;
	HIDESBASE virtual MKCoordinateRegion __cdecl convertRect(Iosapi::Foundation::NSRect rect, Iosapi::Uikit::_di_UIView toRegionFromView) = 0 ;
	virtual void __cdecl setZoomEnabled(bool zoomEnabled) = 0 ;
	virtual bool __cdecl isZoomEnabled() = 0 ;
	virtual void __cdecl setScrollEnabled(bool scrollEnabled) = 0 ;
	virtual bool __cdecl isScrollEnabled() = 0 ;
	virtual void __cdecl setRotateEnabled(bool rotateEnabled) = 0 ;
	virtual bool __cdecl isRotateEnabled() = 0 ;
	virtual void __cdecl setPitchEnabled(bool pitchEnabled) = 0 ;
	virtual bool __cdecl isPitchEnabled() = 0 ;
	virtual void __cdecl setShowsPointsOfInterest(bool showsPointsOfInterest) = 0 ;
	virtual bool __cdecl showsPointsOfInterest() = 0 ;
	virtual void __cdecl setShowsBuildings(bool showsBuildings) = 0 ;
	virtual bool __cdecl showsBuildings() = 0 ;
	virtual void __cdecl setShowsUserLocation(bool showsUserLocation) = 0 ;
	virtual bool __cdecl showsUserLocation() = 0 ;
	virtual _di_MKUserLocation __cdecl userLocation() = 0 ;
	virtual void __cdecl setUserTrackingMode(long userTrackingMode) = 0 ;
	virtual long __cdecl userTrackingMode() = 0 ;
	virtual void __cdecl setUserTrackingModeAnimated(long mode, bool animated) = 0 ;
	virtual bool __cdecl isUserLocationVisible() = 0 ;
	virtual void __cdecl addAnnotation(void * annotation) = 0 ;
	virtual void __cdecl addAnnotations(Iosapi::Foundation::_di_NSArray annotations) = 0 ;
	virtual void __cdecl removeAnnotation(void * annotation) = 0 ;
	virtual void __cdecl removeAnnotations(Iosapi::Foundation::_di_NSArray annotations) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl annotations() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl annotationsInMapRect(MKMapRect mapRect) = 0 ;
	virtual _di_MKAnnotationView __cdecl viewForAnnotation(void * annotation) = 0 ;
	virtual _di_MKAnnotationView __cdecl dequeueReusableAnnotationViewWithIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void __cdecl selectAnnotation(void * annotation, bool animated) = 0 ;
	virtual void __cdecl deselectAnnotation(void * annotation, bool animated) = 0 ;
	virtual void __cdecl setSelectedAnnotations(Iosapi::Foundation::_di_NSArray selectedAnnotations) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl selectedAnnotations() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl annotationVisibleRect() = 0 ;
	virtual void __cdecl showAnnotations(Iosapi::Foundation::_di_NSArray annotations, bool animated) = 0 ;
	virtual void __cdecl addOverlayLevel(void * overlay, long level) = 0 ;
	virtual void __cdecl addOverlaysLevel(Iosapi::Foundation::_di_NSArray overlays, long level) = 0 ;
	virtual void __cdecl removeOverlay(void * overlay) = 0 ;
	virtual void __cdecl removeOverlays(Iosapi::Foundation::_di_NSArray overlays) = 0 ;
	virtual void __cdecl insertOverlayAtIndexLevel(void * overlay, unsigned long atIndex, long level) = 0 ;
	virtual void __cdecl insertOverlayAboveOverlay(void * overlay, void * aboveOverlay) = 0 ;
	virtual void __cdecl insertOverlayBelowOverlay(void * overlay, void * belowOverlay) = 0 ;
	virtual void __cdecl exchangeOverlay(void * overlay1, void * withOverlay) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl overlays() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl overlaysInLevel(long level) = 0 ;
	virtual _di_MKOverlayRenderer __cdecl rendererForOverlay(void * overlay) = 0 ;
	virtual _di_MKOverlayView __cdecl viewForOverlay(void * overlay) = 0 ;
	virtual void __cdecl addOverlay(void * overlay) = 0 ;
	virtual void __cdecl addOverlays(Iosapi::Foundation::_di_NSArray overlays) = 0 ;
	virtual void __cdecl insertOverlayAtIndex(void * overlay, unsigned long atIndex) = 0 ;
	virtual void __cdecl exchangeOverlayAtIndex(unsigned long index1, unsigned long withOverlayAtIndex) = 0 ;
};

class PASCALIMPLEMENTATION TMKMapView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapViewClass,_di_MKMapView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapViewClass,_di_MKMapView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapViewClass,_di_MKMapView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapView() { }
	
};


__interface  INTERFACE_UUID("{340EB683-30F5-4757-94A5-2408523E5721}") MKPinAnnotationViewClass  : public MKAnnotationViewClass 
{
	
};

__interface  INTERFACE_UUID("{B6BC09AB-5844-42C8-91FB-5AAACC6BD697}") MKPinAnnotationView  : public MKAnnotationView 
{
	virtual void __cdecl setPinColor(unsigned long pinColor) = 0 ;
	virtual unsigned long __cdecl pinColor() = 0 ;
	virtual void __cdecl setAnimatesDrop(bool animatesDrop) = 0 ;
	virtual bool __cdecl animatesDrop() = 0 ;
};

class PASCALIMPLEMENTATION TMKPinAnnotationView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPinAnnotationViewClass,_di_MKPinAnnotationView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPinAnnotationViewClass,_di_MKPinAnnotationView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPinAnnotationView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPinAnnotationViewClass,_di_MKPinAnnotationView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPinAnnotationView() { }
	
};


__interface  INTERFACE_UUID("{D04DB8A4-6819-494D-80A1-DA3B27F3BA22}") MKShapeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4EFF3193-D141-48E1-8A2B-DE20CEB8DB20}") MKShape  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual void __cdecl setSubtitle(Iosapi::Foundation::_di_NSString subtitle) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subtitle() = 0 ;
};

class PASCALIMPLEMENTATION TMKShape : public Macapi::Objectivec::TOCGenericImport__2<_di_MKShapeClass,_di_MKShape>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKShapeClass,_di_MKShape> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKShape(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKShapeClass,_di_MKShape>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKShape() { }
	
};


__interface  INTERFACE_UUID("{4B451E3F-9281-4314-A795-7AD9F1B01864}") MKPointAnnotationClass  : public MKShapeClass 
{
	
};

__interface  INTERFACE_UUID("{7DC2AB99-C4B9-474E-AC7B-6A1509F7BA19}") MKPointAnnotation  : public MKShape 
{
	virtual void __cdecl setCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate) = 0 ;
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl coordinate() = 0 ;
};

class PASCALIMPLEMENTATION TMKPointAnnotation : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPointAnnotationClass,_di_MKPointAnnotation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPointAnnotationClass,_di_MKPointAnnotation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPointAnnotation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPointAnnotationClass,_di_MKPointAnnotation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPointAnnotation() { }
	
};


__interface  INTERFACE_UUID("{1A21860D-8841-4C0B-8F77-0CEC970A65BB}") MKMultiPointClass  : public MKShapeClass 
{
	
};

__interface  INTERFACE_UUID("{F5F0ACC8-81EB-4F66-957A-092A071873D9}") MKMultiPoint  : public MKShape 
{
	virtual void * __cdecl points() = 0 ;
	virtual unsigned long __cdecl pointCount() = 0 ;
	virtual void __cdecl getCoordinates(void * coords, Iosapi::Foundation::NSRange range) = 0 ;
};

class PASCALIMPLEMENTATION TMKMultiPoint : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMultiPointClass,_di_MKMultiPoint>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMultiPointClass,_di_MKMultiPoint> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMultiPoint(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMultiPointClass,_di_MKMultiPoint>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMultiPoint() { }
	
};


__interface  INTERFACE_UUID("{8A42CEDB-7387-4233-9F62-4B567CBD5AB7}") MKPolylineClass  : public MKMultiPointClass 
{
	virtual void * __cdecl polylineWithPoints(void * points, unsigned long count) = 0 ;
	virtual void * __cdecl polylineWithCoordinates(void * coords, unsigned long count) = 0 ;
};

__interface  INTERFACE_UUID("{60400075-21CD-4A8A-9E4E-017EA72DD03A}") MKPolyline  : public MKMultiPoint 
{
	
};

class PASCALIMPLEMENTATION TMKPolyline : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineClass,_di_MKPolyline>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineClass,_di_MKPolyline> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolyline(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineClass,_di_MKPolyline>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolyline() { }
	
};


__interface  INTERFACE_UUID("{B1893076-2F05-4DFC-B321-88E956BE3A3B}") MKPolygonClass  : public MKMultiPointClass 
{
	virtual _di_MKPolygon __cdecl polygonWithPointsCount(void * points, unsigned long count) = 0 ;
	virtual _di_MKPolygon __cdecl polygonWithPointsCountInteriorPolygons(void * points, unsigned long count, Iosapi::Foundation::_di_NSArray interiorPolygons) = 0 ;
	virtual _di_MKPolygon __cdecl polygonWithCoordinatesCount(void * coords, unsigned long count) = 0 ;
	virtual _di_MKPolygon __cdecl polygonWithCoordinatesCountInteriorPolygons(void * coords, unsigned long count, Iosapi::Foundation::_di_NSArray interiorPolygons) = 0 ;
};

__interface  INTERFACE_UUID("{91945217-38D3-4ACD-9934-7ABA6A545D28}") MKPolygon  : public MKMultiPoint 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl interiorPolygons() = 0 ;
};

class PASCALIMPLEMENTATION TMKPolygon : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonClass,_di_MKPolygon>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonClass,_di_MKPolygon> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolygon(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonClass,_di_MKPolygon>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolygon() { }
	
};


__interface  INTERFACE_UUID("{3E936ABD-AA5B-4158-86A2-6E76F32C8E77}") MKCircleClass  : public MKShapeClass 
{
	virtual _di_MKCircle __cdecl circleWithCenterCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coord, double radius) = 0 ;
	virtual _di_MKCircle __cdecl circleWithMapRect(MKMapRect mapRect) = 0 ;
};

__interface  INTERFACE_UUID("{55394BD6-6F61-432A-B352-5AD9457670BB}") MKCircle  : public MKShape 
{
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl coordinate() = 0 ;
	virtual double __cdecl radius() = 0 ;
	virtual MKMapRect __cdecl boundingMapRect() = 0 ;
};

class PASCALIMPLEMENTATION TMKCircle : public Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleClass,_di_MKCircle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleClass,_di_MKCircle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKCircle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleClass,_di_MKCircle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKCircle() { }
	
};


__interface  INTERFACE_UUID("{CA818F6E-BE43-4654-A151-E17ACF38D1F8}") MKGeodesicPolylineClass  : public MKPolylineClass 
{
	HIDESBASE virtual void * __cdecl polylineWithPoints(void * points, unsigned long count) = 0 ;
	HIDESBASE virtual void * __cdecl polylineWithCoordinates(void * coords, unsigned long count) = 0 ;
};

__interface  INTERFACE_UUID("{D08E6CAC-A1A5-4204-A621-7C05AA86E453}") MKGeodesicPolyline  : public MKPolyline 
{
	
};

class PASCALIMPLEMENTATION TMKGeodesicPolyline : public Macapi::Objectivec::TOCGenericImport__2<_di_MKGeodesicPolylineClass,_di_MKGeodesicPolyline>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKGeodesicPolylineClass,_di_MKGeodesicPolyline> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKGeodesicPolyline(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKGeodesicPolylineClass,_di_MKGeodesicPolyline>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKGeodesicPolyline() { }
	
};


__interface  INTERFACE_UUID("{05AA904B-9E32-47EE-BD3C-3D361FBA30E4}") MKOverlayPathRendererClass  : public MKOverlayRendererClass 
{
	
};

__interface  INTERFACE_UUID("{00D39B47-094C-495C-9FF0-3A8C7A065344}") MKOverlayPathRenderer  : public MKOverlayRenderer 
{
	virtual void __cdecl setFillColor(Iosapi::Uikit::_di_UIColor fillColor) = 0 ;
	virtual Iosapi::Uikit::_di_UIColor __cdecl fillColor() = 0 ;
	virtual void __cdecl setStrokeColor(Iosapi::Uikit::_di_UIColor strokeColor) = 0 ;
	virtual Iosapi::Uikit::_di_UIColor __cdecl strokeColor() = 0 ;
	virtual void __cdecl setLineWidth(double lineWidth) = 0 ;
	virtual double __cdecl lineWidth() = 0 ;
	virtual void __cdecl setLineJoin(unsigned lineJoin) = 0 ;
	virtual unsigned __cdecl lineJoin() = 0 ;
	virtual void __cdecl setLineCap(unsigned lineCap) = 0 ;
	virtual unsigned __cdecl lineCap() = 0 ;
	virtual void __cdecl setMiterLimit(double miterLimit) = 0 ;
	virtual double __cdecl miterLimit() = 0 ;
	virtual void __cdecl setLineDashPhase(double lineDashPhase) = 0 ;
	virtual double __cdecl lineDashPhase() = 0 ;
	virtual void __cdecl setLineDashPattern(Iosapi::Foundation::_di_NSArray lineDashPattern) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl lineDashPattern() = 0 ;
	virtual void __cdecl createPath() = 0 ;
	virtual void __cdecl setPath(void * path) = 0 ;
	virtual void * __cdecl path() = 0 ;
	virtual void __cdecl invalidatePath() = 0 ;
	virtual void __cdecl applyStrokePropertiesToContext(void * context, double atZoomScale) = 0 ;
	virtual void __cdecl applyFillPropertiesToContext(void * context, double atZoomScale) = 0 ;
	virtual void __cdecl strokePath(void * path, void * inContext) = 0 ;
	virtual void __cdecl fillPath(void * path, void * inContext) = 0 ;
};

class PASCALIMPLEMENTATION TMKOverlayPathRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathRendererClass,_di_MKOverlayPathRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathRendererClass,_di_MKOverlayPathRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKOverlayPathRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathRendererClass,_di_MKOverlayPathRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKOverlayPathRenderer() { }
	
};


__interface  INTERFACE_UUID("{222DCC22-AAFD-4B0E-9CB9-82E6CD2054BC}") MKPolygonRendererClass  : public MKOverlayPathRendererClass 
{
	
};

__interface  INTERFACE_UUID("{E95619DE-45EA-4A4B-8DA1-12AEDE420F69}") MKPolygonRenderer  : public MKOverlayPathRenderer 
{
	virtual void * __cdecl initWithPolygon(_di_MKPolygon polygon) = 0 ;
	virtual _di_MKPolygon __cdecl polygon() = 0 ;
};

class PASCALIMPLEMENTATION TMKPolygonRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonRendererClass,_di_MKPolygonRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonRendererClass,_di_MKPolygonRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolygonRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonRendererClass,_di_MKPolygonRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolygonRenderer() { }
	
};


__interface  INTERFACE_UUID("{695068D9-5314-45D4-B8FC-2E9F9BF106E3}") MKPolylineRendererClass  : public MKOverlayPathRendererClass 
{
	
};

__interface  INTERFACE_UUID("{602EABE3-C17F-4DD1-B3CD-D98E4C03DCDC}") MKPolylineRenderer  : public MKOverlayPathRenderer 
{
	virtual void * __cdecl initWithPolyline(_di_MKPolyline polyline) = 0 ;
	virtual _di_MKPolyline __cdecl polyline() = 0 ;
};

class PASCALIMPLEMENTATION TMKPolylineRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineRendererClass,_di_MKPolylineRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineRendererClass,_di_MKPolylineRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolylineRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineRendererClass,_di_MKPolylineRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolylineRenderer() { }
	
};


__interface  INTERFACE_UUID("{0C597FCC-50D0-44EA-AB41-29BA5BA76052}") MKCircleRendererClass  : public MKOverlayPathRendererClass 
{
	
};

__interface  INTERFACE_UUID("{EC9D4A89-F291-4E5C-BF2A-D11263CC6931}") MKCircleRenderer  : public MKOverlayPathRenderer 
{
	virtual void * __cdecl initWithCircle(_di_MKCircle circle) = 0 ;
	virtual _di_MKCircle __cdecl circle() = 0 ;
};

class PASCALIMPLEMENTATION TMKCircleRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleRendererClass,_di_MKCircleRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleRendererClass,_di_MKCircleRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKCircleRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleRendererClass,_di_MKCircleRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKCircleRenderer() { }
	
};


__interface  INTERFACE_UUID("{065F0486-31C8-4D45-94D8-E97D36DCC780}") MKLocalSearchRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EF610BE8-CB1D-49DE-ADBE-3A8A91245CC4}") MKLocalSearchRequest  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setNaturalLanguageQuery(Iosapi::Foundation::_di_NSString naturalLanguageQuery) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl naturalLanguageQuery() = 0 ;
	virtual void __cdecl setRegion(MKCoordinateRegion region) = 0 ;
	virtual MKCoordinateRegion __cdecl region() = 0 ;
};

class PASCALIMPLEMENTATION TMKLocalSearchRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchRequestClass,_di_MKLocalSearchRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchRequestClass,_di_MKLocalSearchRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKLocalSearchRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchRequestClass,_di_MKLocalSearchRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKLocalSearchRequest() { }
	
};


__interface  INTERFACE_UUID("{13A1778A-DEE7-4B2A-828C-14C8C1C8F01D}") MKLocalSearchResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{89DAE669-9FE2-4233-BE00-76C66507750F}") MKLocalSearchResponse  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl mapItems() = 0 ;
	virtual MKCoordinateRegion __cdecl boundingRegion() = 0 ;
};

class PASCALIMPLEMENTATION TMKLocalSearchResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchResponseClass,_di_MKLocalSearchResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchResponseClass,_di_MKLocalSearchResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKLocalSearchResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchResponseClass,_di_MKLocalSearchResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKLocalSearchResponse() { }
	
};


__interface  INTERFACE_UUID("{E7E7D54A-4769-4763-988B-86AE610CA5AE}") MKLocalSearchClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CBDDC2B7-8779-4E5C-BA6B-C69C8EA874E3}") MKLocalSearch  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithRequest(_di_MKLocalSearchRequest request) = 0 ;
	virtual void __cdecl startWithCompletionHandler(MKLocalSearchCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual bool __cdecl isSearching() = 0 ;
};

class PASCALIMPLEMENTATION TMKLocalSearch : public Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchClass,_di_MKLocalSearch>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchClass,_di_MKLocalSearch> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKLocalSearch(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKLocalSearchClass,_di_MKLocalSearch>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKLocalSearch() { }
	
};


__interface  INTERFACE_UUID("{62610AD5-B092-4FF7-ACC8-F42CBA00087D}") MKDirectionsRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual bool __cdecl isDirectionsRequestURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
};

__interface  INTERFACE_UUID("{B0E4EF63-4A4E-40E4-818B-6F6666C34744}") MKDirectionsRequest  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MKMapItem __cdecl source() = 0 ;
	virtual void __cdecl setSource(_di_MKMapItem source) = 0 ;
	virtual _di_MKMapItem __cdecl destination() = 0 ;
	virtual void __cdecl setDestination(_di_MKMapItem destination) = 0 ;
	virtual void __cdecl setTransportType(unsigned long transportType) = 0 ;
	virtual unsigned long __cdecl transportType() = 0 ;
	virtual void __cdecl setRequestsAlternateRoutes(bool requestsAlternateRoutes) = 0 ;
	virtual bool __cdecl requestsAlternateRoutes() = 0 ;
	virtual void __cdecl setDepartureDate(Iosapi::Foundation::_di_NSDate departureDate) = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl departureDate() = 0 ;
	virtual void __cdecl setArrivalDate(Iosapi::Foundation::_di_NSDate arrivalDate) = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl arrivalDate() = 0 ;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
};

class PASCALIMPLEMENTATION TMKDirectionsRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsRequestClass,_di_MKDirectionsRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsRequestClass,_di_MKDirectionsRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKDirectionsRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsRequestClass,_di_MKDirectionsRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKDirectionsRequest() { }
	
};


__interface  INTERFACE_UUID("{32D4BA64-EB6F-4592-BB63-386D013B305F}") MKDirectionsResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1FC095CB-3E8F-4812-BD4D-3664C8A4414A}") MKDirectionsResponse  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MKMapItem __cdecl source() = 0 ;
	virtual _di_MKMapItem __cdecl destination() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl routes() = 0 ;
};

class PASCALIMPLEMENTATION TMKDirectionsResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsResponseClass,_di_MKDirectionsResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsResponseClass,_di_MKDirectionsResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKDirectionsResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsResponseClass,_di_MKDirectionsResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKDirectionsResponse() { }
	
};


__interface  INTERFACE_UUID("{21F769B3-014E-426A-B8C0-D319C774E8F9}") MKETAResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{9B616C27-0F54-475D-BD27-0419659F39EF}") MKETAResponse  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MKMapItem __cdecl source() = 0 ;
	virtual _di_MKMapItem __cdecl destination() = 0 ;
	virtual double __cdecl expectedTravelTime() = 0 ;
};

class PASCALIMPLEMENTATION TMKETAResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_MKETAResponseClass,_di_MKETAResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKETAResponseClass,_di_MKETAResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKETAResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKETAResponseClass,_di_MKETAResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKETAResponse() { }
	
};


__interface  INTERFACE_UUID("{656A3495-C84E-4DBC-8736-6ACE3F560386}") MKDirectionsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{09C72312-0CE7-43E4-82E3-7A621E95834D}") MKDirections  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithRequest(_di_MKDirectionsRequest request) = 0 ;
	virtual void __cdecl calculateDirectionsWithCompletionHandler(MKDirectionsHandler completionHandler) = 0 ;
	virtual void __cdecl calculateETAWithCompletionHandler(MKETAHandler completionHandler) = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual bool __cdecl isCalculating() = 0 ;
};

class PASCALIMPLEMENTATION TMKDirections : public Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsClass,_di_MKDirections>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsClass,_di_MKDirections> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKDirections(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKDirectionsClass,_di_MKDirections>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKDirections() { }
	
};


__interface  INTERFACE_UUID("{29F2C187-6A02-4596-B994-AE812985C688}") MKRouteClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6EB6BB0D-BDF1-455C-BECB-99732F92CB7C}") MKRoute  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl advisoryNotices() = 0 ;
	virtual double __cdecl distance() = 0 ;
	virtual double __cdecl expectedTravelTime() = 0 ;
	virtual unsigned long __cdecl transportType() = 0 ;
	virtual _di_MKPolyline __cdecl polyline() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl steps() = 0 ;
};

class PASCALIMPLEMENTATION TMKRoute : public Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteClass,_di_MKRoute>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteClass,_di_MKRoute> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKRoute(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteClass,_di_MKRoute>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKRoute() { }
	
};


__interface  INTERFACE_UUID("{E1023629-9A30-4719-9E45-B9824D38FCA6}") MKRouteStepClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7519DCED-725A-43F3-8EEA-A458FDDC7EA5}") MKRouteStep  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl instructions() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl notice() = 0 ;
	virtual _di_MKPolyline __cdecl polyline() = 0 ;
	virtual double __cdecl distance() = 0 ;
	virtual unsigned long __cdecl transportType() = 0 ;
};

class PASCALIMPLEMENTATION TMKRouteStep : public Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteStepClass,_di_MKRouteStep>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteStepClass,_di_MKRouteStep> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKRouteStep(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKRouteStepClass,_di_MKRouteStep>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKRouteStep() { }
	
};


__interface  INTERFACE_UUID("{8E2DB13B-F515-40BB-87D0-07480D79F795}") MKMapSnapshotOptionsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1D394667-FECF-40C2-AF75-772A8DD8FE1A}") MKMapSnapshotOptions  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setCamera(_di_MKMapCamera camera) = 0 ;
	virtual _di_MKMapCamera __cdecl camera() = 0 ;
	virtual void __cdecl setMapRect(MKMapRect mapRect) = 0 ;
	virtual MKMapRect __cdecl mapRect() = 0 ;
	virtual void __cdecl setRegion(MKCoordinateRegion region) = 0 ;
	virtual MKCoordinateRegion __cdecl region() = 0 ;
	virtual void __cdecl setMapType(unsigned long mapType) = 0 ;
	virtual unsigned long __cdecl mapType() = 0 ;
	virtual void __cdecl setShowsPointsOfInterest(bool showsPointsOfInterest) = 0 ;
	virtual bool __cdecl showsPointsOfInterest() = 0 ;
	virtual void __cdecl setShowsBuildings(bool showsBuildings) = 0 ;
	virtual bool __cdecl showsBuildings() = 0 ;
	virtual void __cdecl setSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl size() = 0 ;
	virtual void __cdecl setScale(double scale) = 0 ;
	virtual double __cdecl scale() = 0 ;
};

class PASCALIMPLEMENTATION TMKMapSnapshotOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotOptionsClass,_di_MKMapSnapshotOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotOptionsClass,_di_MKMapSnapshotOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapSnapshotOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotOptionsClass,_di_MKMapSnapshotOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapSnapshotOptions() { }
	
};


__interface  INTERFACE_UUID("{8FFC7DDE-8FC8-4E3F-AC51-2B2E664F6590}") MKMapSnapshotClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FA4AB708-02E4-4DB6-9B8B-1C45A23E9706}") MKMapSnapshot  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Uikit::_di_UIImage __cdecl image() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl pointForCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate) = 0 ;
};

class PASCALIMPLEMENTATION TMKMapSnapshot : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotClass,_di_MKMapSnapshot>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotClass,_di_MKMapSnapshot> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapSnapshot(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotClass,_di_MKMapSnapshot>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapSnapshot() { }
	
};


__interface  INTERFACE_UUID("{EC7C63DC-5FB5-48B8-83B7-D08C9CF95339}") MKMapSnapshotterClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{75CE29DA-AF22-4A45-8EE9-00576371C4EA}") MKMapSnapshotter  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithOptions(_di_MKMapSnapshotOptions options) = 0 ;
	virtual void __cdecl startWithCompletionHandler(MKMapSnapshotCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl startWithQueue(NativeInt queue, MKMapSnapshotCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual bool __cdecl isLoading() = 0 ;
};

class PASCALIMPLEMENTATION TMKMapSnapshotter : public Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotterClass,_di_MKMapSnapshotter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotterClass,_di_MKMapSnapshotter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKMapSnapshotter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKMapSnapshotterClass,_di_MKMapSnapshotter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKMapSnapshotter() { }
	
};


__interface  INTERFACE_UUID("{2EFDD9BD-69D0-427E-80B2-67AE15671C20}") MKTileOverlayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{022FFEB7-8072-4E6B-BB65-C01C7349FC37}") MKTileOverlay  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithURLTemplate(Iosapi::Foundation::_di_NSString URLTemplate) = 0 ;
	virtual void __cdecl setTileSize(Iosapi::Foundation::NSSize tileSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl tileSize() = 0 ;
	virtual void __cdecl setGeometryFlipped(bool geometryFlipped) = 0 ;
	virtual bool __cdecl isGeometryFlipped() = 0 ;
	virtual void __cdecl setMinimumZ(long minimumZ) = 0 ;
	virtual long __cdecl minimumZ() = 0 ;
	virtual void __cdecl setMaximumZ(long maximumZ) = 0 ;
	virtual long __cdecl maximumZ() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl URLTemplate() = 0 ;
	virtual void __cdecl setCanReplaceMapContent(bool canReplaceMapContent) = 0 ;
	virtual bool __cdecl canReplaceMapContent() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl URLForTilePath(MKTileOverlayPath path) = 0 ;
	virtual void __cdecl loadTileAtPath(MKTileOverlayPath path, TMapKitResult result) = 0 ;
};

class PASCALIMPLEMENTATION TMKTileOverlay : public Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayClass,_di_MKTileOverlay>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayClass,_di_MKTileOverlay> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKTileOverlay(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayClass,_di_MKTileOverlay>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKTileOverlay() { }
	
};


__interface  INTERFACE_UUID("{FFCC8271-8C1C-43D1-A7A3-A0DBC9B3457C}") MKTileOverlayRendererClass  : public MKOverlayRendererClass 
{
	
};

__interface  INTERFACE_UUID("{0EDD7D15-065A-4CD8-A5B4-5DD18613E801}") MKTileOverlayRenderer  : public MKOverlayRenderer 
{
	virtual void * __cdecl initWithTileOverlay(_di_MKTileOverlay overlay) = 0 ;
	virtual void __cdecl reloadData() = 0 ;
};

class PASCALIMPLEMENTATION TMKTileOverlayRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayRendererClass,_di_MKTileOverlayRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayRendererClass,_di_MKTileOverlayRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKTileOverlayRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKTileOverlayRendererClass,_di_MKTileOverlayRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKTileOverlayRenderer() { }
	
};


__interface  INTERFACE_UUID("{5F800717-BA22-4F94-9813-1CB747FA0328}") MKReverseGeocoderClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{94B98967-0208-4048-BC69-C74D757A8EF8}") MKReverseGeocoder  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate) = 0 ;
	virtual void __cdecl start() = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl coordinate() = 0 ;
	virtual _di_MKPlacemark __cdecl placemark() = 0 ;
	virtual bool __cdecl isQuerying() = 0 ;
};

class PASCALIMPLEMENTATION TMKReverseGeocoder : public Macapi::Objectivec::TOCGenericImport__2<_di_MKReverseGeocoderClass,_di_MKReverseGeocoder>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKReverseGeocoderClass,_di_MKReverseGeocoder> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKReverseGeocoder(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKReverseGeocoderClass,_di_MKReverseGeocoder>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKReverseGeocoder() { }
	
};


__interface  INTERFACE_UUID("{F6B36F0A-E74E-467C-B50D-A2D3E1E641CF}") MKOverlayPathViewClass  : public MKOverlayViewClass 
{
	
};

__interface  INTERFACE_UUID("{9B775774-6E6C-44F4-BF7E-33A388ED7BCC}") MKOverlayPathView  : public MKOverlayView 
{
	virtual void __cdecl setFillColor(Iosapi::Uikit::_di_UIColor fillColor) = 0 ;
	virtual Iosapi::Uikit::_di_UIColor __cdecl fillColor() = 0 ;
	virtual void __cdecl setStrokeColor(Iosapi::Uikit::_di_UIColor strokeColor) = 0 ;
	virtual Iosapi::Uikit::_di_UIColor __cdecl strokeColor() = 0 ;
	virtual void __cdecl setLineWidth(double lineWidth) = 0 ;
	virtual double __cdecl lineWidth() = 0 ;
	virtual void __cdecl setLineJoin(unsigned lineJoin) = 0 ;
	virtual unsigned __cdecl lineJoin() = 0 ;
	virtual void __cdecl setLineCap(unsigned lineCap) = 0 ;
	virtual unsigned __cdecl lineCap() = 0 ;
	virtual void __cdecl setMiterLimit(double miterLimit) = 0 ;
	virtual double __cdecl miterLimit() = 0 ;
	virtual void __cdecl setLineDashPhase(double lineDashPhase) = 0 ;
	virtual double __cdecl lineDashPhase() = 0 ;
	virtual void __cdecl setLineDashPattern(Iosapi::Foundation::_di_NSArray lineDashPattern) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl lineDashPattern() = 0 ;
	virtual void __cdecl createPath() = 0 ;
	virtual void __cdecl setPath(void * path) = 0 ;
	virtual void * __cdecl path() = 0 ;
	virtual void __cdecl invalidatePath() = 0 ;
	virtual void __cdecl applyStrokePropertiesToContext(void * context, double atZoomScale) = 0 ;
	virtual void __cdecl applyFillPropertiesToContext(void * context, double atZoomScale) = 0 ;
	virtual void __cdecl strokePath(void * path, void * inContext) = 0 ;
	virtual void __cdecl fillPath(void * path, void * inContext) = 0 ;
};

class PASCALIMPLEMENTATION TMKOverlayPathView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathViewClass,_di_MKOverlayPathView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathViewClass,_di_MKOverlayPathView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKOverlayPathView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKOverlayPathViewClass,_di_MKOverlayPathView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKOverlayPathView() { }
	
};


__interface  INTERFACE_UUID("{2DB82DAB-D352-48EE-B33E-B63789BFD80E}") MKPolygonViewClass  : public MKOverlayPathViewClass 
{
	
};

__interface  INTERFACE_UUID("{6D7A5EC8-11D4-4363-AED1-A95B1F851279}") MKPolygonView  : public MKOverlayPathView 
{
	virtual void * __cdecl initWithPolygon(_di_MKPolygon polygon) = 0 ;
	virtual _di_MKPolygon __cdecl polygon() = 0 ;
};

class PASCALIMPLEMENTATION TMKPolygonView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonViewClass,_di_MKPolygonView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonViewClass,_di_MKPolygonView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolygonView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolygonViewClass,_di_MKPolygonView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolygonView() { }
	
};


__interface  INTERFACE_UUID("{A8ED75B7-A805-4F49-BEE4-217D72860377}") MKPolylineViewClass  : public MKOverlayPathViewClass 
{
	
};

__interface  INTERFACE_UUID("{93F65EE8-F8A2-4408-AECD-6116B24ECB5F}") MKPolylineView  : public MKOverlayPathView 
{
	virtual void * __cdecl initWithPolyline(_di_MKPolyline polyline) = 0 ;
	virtual _di_MKPolyline __cdecl polyline() = 0 ;
};

class PASCALIMPLEMENTATION TMKPolylineView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineViewClass,_di_MKPolylineView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineViewClass,_di_MKPolylineView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKPolylineView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKPolylineViewClass,_di_MKPolylineView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKPolylineView() { }
	
};


__interface  INTERFACE_UUID("{6B1583A9-EB00-4DB5-B35F-7B7CC646DADC}") MKCircleViewClass  : public MKOverlayPathViewClass 
{
	
};

__interface  INTERFACE_UUID("{45432614-C9CB-4CA2-8A00-7B65E68B8689}") MKCircleView  : public MKOverlayPathView 
{
	virtual void * __cdecl initWithCircle(_di_MKCircle circle) = 0 ;
	virtual _di_MKCircle __cdecl circle() = 0 ;
};

class PASCALIMPLEMENTATION TMKCircleView : public Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleViewClass,_di_MKCircleView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleViewClass,_di_MKCircleView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKCircleView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKCircleViewClass,_di_MKCircleView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKCircleView() { }
	
};


__interface  INTERFACE_UUID("{166C34AA-CD78-4FA1-A28E-1437AC058476}") MKUserTrackingBarButtonItemClass  : public Iosapi::Uikit::UIBarButtonItemClass 
{
	
};

__interface  INTERFACE_UUID("{9ED89AF6-019C-4B0A-9275-2D83568F3C70}") MKUserTrackingBarButtonItem  : public Iosapi::Uikit::UIBarButtonItem 
{
	virtual void * __cdecl initWithMapView(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl setMapView(_di_MKMapView mapView) = 0 ;
	virtual _di_MKMapView __cdecl mapView() = 0 ;
};

class PASCALIMPLEMENTATION TMKUserTrackingBarButtonItem : public Macapi::Objectivec::TOCGenericImport__2<_di_MKUserTrackingBarButtonItemClass,_di_MKUserTrackingBarButtonItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MKUserTrackingBarButtonItemClass,_di_MKUserTrackingBarButtonItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMKUserTrackingBarButtonItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MKUserTrackingBarButtonItemClass,_di_MKUserTrackingBarButtonItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMKUserTrackingBarButtonItem() { }
	
};


__interface  INTERFACE_UUID("{C50B8AB5-B79A-499F-99C3-71DE8E7DA2B1}") MKAnnotation  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl coordinate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subtitle() = 0 ;
	virtual void __cdecl setCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D newCoordinate) = 0 ;
};

__interface  INTERFACE_UUID("{0520D101-B198-463B-AD46-6199FCD6FDD8}") MKOverlay  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Corelocation::CLLocationCoordinate2D __cdecl coordinate() = 0 ;
	virtual MKMapRect __cdecl boundingMapRect() = 0 ;
	virtual bool __cdecl intersectsMapRect(MKMapRect mapRect) = 0 ;
	virtual bool __cdecl canReplaceMapContent() = 0 ;
};

__interface  INTERFACE_UUID("{29CC14DB-9E65-4332-9B2C-5A54DC28D163}") MKMapViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl mapViewRegionWillChangeAnimated(_di_MKMapView mapView, bool regionWillChangeAnimated) = 0 ;
	virtual void __cdecl mapViewRegionDidChangeAnimated(_di_MKMapView mapView, bool regionDidChangeAnimated) = 0 ;
	virtual void __cdecl mapViewWillStartLoadingMap(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl mapViewDidFinishLoadingMap(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl mapViewDidFailLoadingMap(_di_MKMapView mapView, Iosapi::Foundation::_di_NSError withError) = 0 ;
	virtual void __cdecl mapViewWillStartRenderingMap(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl mapViewDidFinishRenderingMap(_di_MKMapView mapView, bool fullyRendered) = 0 ;
	virtual _di_MKAnnotationView __cdecl mapViewViewForAnnotation(_di_MKMapView mapView, void * viewForAnnotation) = 0 ;
	virtual void __cdecl mapViewDidAddAnnotationViews(_di_MKMapView mapView, Iosapi::Foundation::_di_NSArray didAddAnnotationViews) = 0 ;
	virtual void __cdecl mapViewAnnotationViewCalloutAccessoryControlTapped(_di_MKMapView mapView, _di_MKAnnotationView annotationView, Iosapi::Uikit::_di_UIControl calloutAccessoryControlTapped) = 0 ;
	virtual void __cdecl mapViewDidSelectAnnotationView(_di_MKMapView mapView, _di_MKAnnotationView didSelectAnnotationView) = 0 ;
	virtual void __cdecl mapViewDidDeselectAnnotationView(_di_MKMapView mapView, _di_MKAnnotationView didDeselectAnnotationView) = 0 ;
	virtual void __cdecl mapViewWillStartLocatingUser(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl mapViewDidStopLocatingUser(_di_MKMapView mapView) = 0 ;
	virtual void __cdecl mapViewDidUpdateUserLocation(_di_MKMapView mapView, _di_MKUserLocation didUpdateUserLocation) = 0 ;
	virtual void __cdecl mapViewDidFailToLocateUserWithError(_di_MKMapView mapView, Iosapi::Foundation::_di_NSError didFailToLocateUserWithError) = 0 ;
	virtual void __cdecl mapViewAnnotationViewDidChangeDragStateFromOldState(_di_MKMapView mapView, _di_MKAnnotationView annotationView, unsigned long didChangeDragState, unsigned long fromOldState) = 0 ;
	virtual void __cdecl mapViewDidChangeUserTrackingModeAnimated(_di_MKMapView mapView, long didChangeUserTrackingMode, bool animated) = 0 ;
	virtual _di_MKOverlayRenderer __cdecl mapViewRendererForOverlay(_di_MKMapView mapView, void * rendererForOverlay) = 0 ;
	virtual void __cdecl mapViewDidAddOverlayRenderers(_di_MKMapView mapView, Iosapi::Foundation::_di_NSArray didAddOverlayRenderers) = 0 ;
	virtual _di_MKOverlayView __cdecl mapViewViewForOverlay(_di_MKMapView mapView, void * viewForOverlay) = 0 ;
	virtual void __cdecl mapViewDidAddOverlayViews(_di_MKMapView mapView, Iosapi::Foundation::_di_NSArray didAddOverlayViews) = 0 ;
};

__interface  INTERFACE_UUID("{55B8B010-E213-476F-A656-1A023035697C}") MKReverseGeocoderDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl reverseGeocoderDidFindPlacemark(_di_MKReverseGeocoder geocoder, _di_MKPlacemark didFindPlacemark) = 0 ;
	virtual void __cdecl reverseGeocoderDidFailWithError(_di_MKReverseGeocoder geocoder, Iosapi::Foundation::_di_NSError didFailWithError) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 MKAnnotationViewDragStateNone = System::Int8(0x0);
static constexpr System::Int8 MKAnnotationViewDragStateStarting = System::Int8(0x1);
static constexpr System::Int8 MKAnnotationViewDragStateDragging = System::Int8(0x2);
static constexpr System::Int8 MKAnnotationViewDragStateCanceling = System::Int8(0x3);
static constexpr System::Int8 MKAnnotationViewDragStateEnding = System::Int8(0x4);
static constexpr System::Int8 MKDistanceFormatterUnitsDefault = System::Int8(0x0);
static constexpr System::Int8 MKDistanceFormatterUnitsMetric = System::Int8(0x1);
static constexpr System::Int8 MKDistanceFormatterUnitsImperial = System::Int8(0x2);
static constexpr System::Int8 MKDistanceFormatterUnitsImperialWithYards = System::Int8(0x3);
static constexpr System::Int8 MKDistanceFormatterUnitStyleDefault = System::Int8(0x0);
static constexpr System::Int8 MKDistanceFormatterUnitStyleAbbreviated = System::Int8(0x1);
static constexpr System::Int8 MKDistanceFormatterUnitStyleFull = System::Int8(0x2);
static constexpr System::Int8 MKMapTypeStandard = System::Int8(0x0);
static constexpr System::Int8 MKMapTypeSatellite = System::Int8(0x1);
static constexpr System::Int8 MKMapTypeHybrid = System::Int8(0x2);
static constexpr System::Int8 MKErrorUnknown = System::Int8(0x1);
static constexpr System::Int8 MKErrorServerFailure = System::Int8(0x2);
static constexpr System::Int8 MKErrorLoadingThrottled = System::Int8(0x3);
static constexpr System::Int8 MKErrorPlacemarkNotFound = System::Int8(0x4);
static constexpr System::Int8 MKErrorDirectionsNotFound = System::Int8(0x5);
static constexpr System::Int8 MKUserTrackingModeNone = System::Int8(0x0);
static constexpr System::Int8 MKUserTrackingModeFollow = System::Int8(0x1);
static constexpr System::Int8 MKUserTrackingModeFollowWithHeading = System::Int8(0x2);
static constexpr System::Int8 MKOverlayLevelAboveRoads = System::Int8(0x0);
static constexpr System::Int8 MKOverlayLevelAboveLabels = System::Int8(0x1);
static constexpr System::Int8 MKPinAnnotationColorRed = System::Int8(0x0);
static constexpr System::Int8 MKPinAnnotationColorGreen = System::Int8(0x1);
static constexpr System::Int8 MKPinAnnotationColorPurple = System::Int8(0x2);
static constexpr System::Int8 MKDirectionsTransportTypeAutomobile = System::Int8(0x1);
static constexpr System::Int8 MKDirectionsTransportTypeWalking = System::Int8(0x2);
static constexpr int MKDirectionsTransportTypeAny = int(0xfffffff);
#define libMapKit u"/System/Library/Frameworks/MapKit.framework/MapKit"
extern "C" MKCoordinateSpan __cdecl MKCoordinateSpanMake(double latitudeDelta, double longitudeDelta);
extern "C" MKCoordinateRegion __cdecl MKCoordinateRegionMake(Iosapi::Corelocation::CLLocationCoordinate2D centerCoordinate, MKCoordinateSpan span);
extern "C" MKCoordinateRegion __cdecl MKCoordinateRegionMakeWithDistance(Iosapi::Corelocation::CLLocationCoordinate2D centerCoordinate, double latitudinalMeters, double longitudinalMeters);
extern "C" MKMapPoint __cdecl MKMapPointForCoordinate(Iosapi::Corelocation::CLLocationCoordinate2D coordinate);
extern "C" Iosapi::Corelocation::CLLocationCoordinate2D __cdecl MKCoordinateForMapPoint(MKMapPoint mapPoint);
extern "C" double __cdecl MKMetersPerMapPointAtLatitude(double latitude);
extern "C" double __cdecl MKMapPointsPerMeterAtLatitude(double latitude);
extern "C" double __cdecl MKMetersBetweenMapPoints(MKMapPoint a, MKMapPoint b);
extern "C" MKMapPoint __cdecl MKMapPointMake(double x, double y);
extern "C" MKMapSize __cdecl MKMapSizeMake(double width, double height);
extern "C" MKMapRect __cdecl MKMapRectMake(double x, double y, double width, double height);
extern "C" double __cdecl MKMapRectGetMinX(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetMinY(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetMidX(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetMidY(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetMaxX(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetMaxY(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetWidth(MKMapRect rect);
extern "C" double __cdecl MKMapRectGetHeight(MKMapRect rect);
extern "C" bool __cdecl MKMapPointEqualToPoint(MKMapPoint point1, MKMapPoint point2);
extern "C" bool __cdecl MKMapSizeEqualToSize(MKMapSize size1, MKMapSize size2);
extern "C" bool __cdecl MKMapRectEqualToRect(MKMapRect rect1, MKMapRect rect2);
extern "C" bool __cdecl MKMapRectIsNull(MKMapRect rect);
extern "C" bool __cdecl MKMapRectIsEmpty(MKMapRect rect);
extern "C" Iosapi::Foundation::_di_NSString __cdecl MKStringFromMapPoint(MKMapPoint point);
extern "C" Iosapi::Foundation::_di_NSString __cdecl MKStringFromMapSize(MKMapSize size);
extern "C" Iosapi::Foundation::_di_NSString __cdecl MKStringFromMapRect(MKMapRect rect);
extern "C" MKMapRect __cdecl MKMapRectUnion(MKMapRect rect1, MKMapRect rect2);
extern "C" MKMapRect __cdecl MKMapRectIntersection(MKMapRect rect1, MKMapRect rect2);
extern "C" MKMapRect __cdecl MKMapRectInset(MKMapRect rect, double dx, double dy);
extern "C" MKMapRect __cdecl MKMapRectOffset(MKMapRect rect, double dx, double dy);
extern "C" void __cdecl MKMapRectDivide(MKMapRect rect, void * slice, void * remainder, double amount, unsigned edge);
extern "C" bool __cdecl MKMapRectContainsPoint(MKMapRect rect, MKMapPoint point);
extern "C" bool __cdecl MKMapRectContainsRect(MKMapRect rect1, MKMapRect rect2);
extern "C" bool __cdecl MKMapRectIntersectsRect(MKMapRect rect1, MKMapRect rect2);
extern "C" MKCoordinateRegion __cdecl MKCoordinateRegionForMapRect(MKMapRect rect);
extern "C" bool __cdecl MKMapRectSpans180thMeridian(MKMapRect rect);
extern "C" MKMapRect __cdecl MKMapRectRemainder(MKMapRect rect);
extern "C" double __cdecl MKRoadWidthAtZoomScale(double zoomScale);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKAnnotationCalloutInfoDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsDirectionsModeKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsMapTypeKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsShowsTrafficKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsDirectionsModeDriving(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsDirectionsModeWalking(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsMapCenterKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsMapSpanKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKLaunchOptionsCameraKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MKErrorDomain(void);
}	/* namespace Mapkit */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_MAPKIT)
using namespace Iosapi::Mapkit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_MapkitHPP
