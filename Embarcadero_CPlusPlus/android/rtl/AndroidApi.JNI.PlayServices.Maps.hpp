// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.PlayServices.Maps.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_Playservices_MapsHPP
#define Androidapi_Jni_Playservices_MapsHPP

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
#include <Androidapi.JNI.Java.Net.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Location.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.PlayServices.hpp>
#include <Androidapi.JNI.Support.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Playservices
{
namespace Maps
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAbstractSafeParcelableClass;
typedef System::DelphiInterface<JAbstractSafeParcelableClass> _di_JAbstractSafeParcelableClass;
__interface DELPHIINTERFACE JAbstractSafeParcelable;
typedef System::DelphiInterface<JAbstractSafeParcelable> _di_JAbstractSafeParcelable;
class DELPHICLASS TJAbstractSafeParcelable;
__interface DELPHIINTERFACE JIObjectWrapperClass;
typedef System::DelphiInterface<JIObjectWrapperClass> _di_JIObjectWrapperClass;
__interface DELPHIINTERFACE JIObjectWrapper;
typedef System::DelphiInterface<JIObjectWrapper> _di_JIObjectWrapper;
class DELPHICLASS TJIObjectWrapper;
__interface DELPHIINTERFACE JCameraUpdateClass;
typedef System::DelphiInterface<JCameraUpdateClass> _di_JCameraUpdateClass;
__interface DELPHIINTERFACE JCameraUpdate;
typedef System::DelphiInterface<JCameraUpdate> _di_JCameraUpdate;
class DELPHICLASS TJCameraUpdate;
__interface DELPHIINTERFACE JCameraUpdateFactoryClass;
typedef System::DelphiInterface<JCameraUpdateFactoryClass> _di_JCameraUpdateFactoryClass;
__interface DELPHIINTERFACE JCameraUpdateFactory;
typedef System::DelphiInterface<JCameraUpdateFactory> _di_JCameraUpdateFactory;
class DELPHICLASS TJCameraUpdateFactory;
__interface DELPHIINTERFACE JGoogleMapClass;
typedef System::DelphiInterface<JGoogleMapClass> _di_JGoogleMapClass;
__interface DELPHIINTERFACE JGoogleMap;
typedef System::DelphiInterface<JGoogleMap> _di_JGoogleMap;
class DELPHICLASS TJGoogleMap;
__interface DELPHIINTERFACE JGoogleMap_CancelableCallbackClass;
typedef System::DelphiInterface<JGoogleMap_CancelableCallbackClass> _di_JGoogleMap_CancelableCallbackClass;
__interface DELPHIINTERFACE JGoogleMap_CancelableCallback;
typedef System::DelphiInterface<JGoogleMap_CancelableCallback> _di_JGoogleMap_CancelableCallback;
class DELPHICLASS TJGoogleMap_CancelableCallback;
__interface DELPHIINTERFACE JGoogleMap_InfoWindowAdapterClass;
typedef System::DelphiInterface<JGoogleMap_InfoWindowAdapterClass> _di_JGoogleMap_InfoWindowAdapterClass;
__interface DELPHIINTERFACE JGoogleMap_InfoWindowAdapter;
typedef System::DelphiInterface<JGoogleMap_InfoWindowAdapter> _di_JGoogleMap_InfoWindowAdapter;
class DELPHICLASS TJGoogleMap_InfoWindowAdapter;
__interface DELPHIINTERFACE JGoogleMap_OnCameraChangeListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCameraChangeListenerClass> _di_JGoogleMap_OnCameraChangeListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCameraChangeListener;
typedef System::DelphiInterface<JGoogleMap_OnCameraChangeListener> _di_JGoogleMap_OnCameraChangeListener;
class DELPHICLASS TJGoogleMap_OnCameraChangeListener;
__interface DELPHIINTERFACE JGoogleMap_OnCameraIdleListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCameraIdleListenerClass> _di_JGoogleMap_OnCameraIdleListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCameraIdleListener;
typedef System::DelphiInterface<JGoogleMap_OnCameraIdleListener> _di_JGoogleMap_OnCameraIdleListener;
class DELPHICLASS TJGoogleMap_OnCameraIdleListener;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveCanceledListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveCanceledListenerClass> _di_JGoogleMap_OnCameraMoveCanceledListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveCanceledListener;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveCanceledListener> _di_JGoogleMap_OnCameraMoveCanceledListener;
class DELPHICLASS TJGoogleMap_OnCameraMoveCanceledListener;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveListenerClass> _di_JGoogleMap_OnCameraMoveListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveListener;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveListener> _di_JGoogleMap_OnCameraMoveListener;
class DELPHICLASS TJGoogleMap_OnCameraMoveListener;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveStartedListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveStartedListenerClass> _di_JGoogleMap_OnCameraMoveStartedListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCameraMoveStartedListener;
typedef System::DelphiInterface<JGoogleMap_OnCameraMoveStartedListener> _di_JGoogleMap_OnCameraMoveStartedListener;
class DELPHICLASS TJGoogleMap_OnCameraMoveStartedListener;
__interface DELPHIINTERFACE JGoogleMap_OnCircleClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnCircleClickListenerClass> _di_JGoogleMap_OnCircleClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnCircleClickListener;
typedef System::DelphiInterface<JGoogleMap_OnCircleClickListener> _di_JGoogleMap_OnCircleClickListener;
class DELPHICLASS TJGoogleMap_OnCircleClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnGroundOverlayClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnGroundOverlayClickListenerClass> _di_JGoogleMap_OnGroundOverlayClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnGroundOverlayClickListener;
typedef System::DelphiInterface<JGoogleMap_OnGroundOverlayClickListener> _di_JGoogleMap_OnGroundOverlayClickListener;
class DELPHICLASS TJGoogleMap_OnGroundOverlayClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnIndoorStateChangeListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnIndoorStateChangeListenerClass> _di_JGoogleMap_OnIndoorStateChangeListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnIndoorStateChangeListener;
typedef System::DelphiInterface<JGoogleMap_OnIndoorStateChangeListener> _di_JGoogleMap_OnIndoorStateChangeListener;
class DELPHICLASS TJGoogleMap_OnIndoorStateChangeListener;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowClickListenerClass> _di_JGoogleMap_OnInfoWindowClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowClickListener;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowClickListener> _di_JGoogleMap_OnInfoWindowClickListener;
class DELPHICLASS TJGoogleMap_OnInfoWindowClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowCloseListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowCloseListenerClass> _di_JGoogleMap_OnInfoWindowCloseListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowCloseListener;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowCloseListener> _di_JGoogleMap_OnInfoWindowCloseListener;
class DELPHICLASS TJGoogleMap_OnInfoWindowCloseListener;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowLongClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowLongClickListenerClass> _di_JGoogleMap_OnInfoWindowLongClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnInfoWindowLongClickListener;
typedef System::DelphiInterface<JGoogleMap_OnInfoWindowLongClickListener> _di_JGoogleMap_OnInfoWindowLongClickListener;
class DELPHICLASS TJGoogleMap_OnInfoWindowLongClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnMapClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMapClickListenerClass> _di_JGoogleMap_OnMapClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMapClickListener;
typedef System::DelphiInterface<JGoogleMap_OnMapClickListener> _di_JGoogleMap_OnMapClickListener;
class DELPHICLASS TJGoogleMap_OnMapClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnMapLoadedCallbackClass;
typedef System::DelphiInterface<JGoogleMap_OnMapLoadedCallbackClass> _di_JGoogleMap_OnMapLoadedCallbackClass;
__interface DELPHIINTERFACE JGoogleMap_OnMapLoadedCallback;
typedef System::DelphiInterface<JGoogleMap_OnMapLoadedCallback> _di_JGoogleMap_OnMapLoadedCallback;
class DELPHICLASS TJGoogleMap_OnMapLoadedCallback;
__interface DELPHIINTERFACE JGoogleMap_OnMapLongClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMapLongClickListenerClass> _di_JGoogleMap_OnMapLongClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMapLongClickListener;
typedef System::DelphiInterface<JGoogleMap_OnMapLongClickListener> _di_JGoogleMap_OnMapLongClickListener;
class DELPHICLASS TJGoogleMap_OnMapLongClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnMarkerClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMarkerClickListenerClass> _di_JGoogleMap_OnMarkerClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMarkerClickListener;
typedef System::DelphiInterface<JGoogleMap_OnMarkerClickListener> _di_JGoogleMap_OnMarkerClickListener;
class DELPHICLASS TJGoogleMap_OnMarkerClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnMarkerDragListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMarkerDragListenerClass> _di_JGoogleMap_OnMarkerDragListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMarkerDragListener;
typedef System::DelphiInterface<JGoogleMap_OnMarkerDragListener> _di_JGoogleMap_OnMarkerDragListener;
class DELPHICLASS TJGoogleMap_OnMarkerDragListener;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationButtonClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationButtonClickListenerClass> _di_JGoogleMap_OnMyLocationButtonClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationButtonClickListener;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationButtonClickListener> _di_JGoogleMap_OnMyLocationButtonClickListener;
class DELPHICLASS TJGoogleMap_OnMyLocationButtonClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationChangeListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationChangeListenerClass> _di_JGoogleMap_OnMyLocationChangeListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationChangeListener;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationChangeListener> _di_JGoogleMap_OnMyLocationChangeListener;
class DELPHICLASS TJGoogleMap_OnMyLocationChangeListener;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationClickListenerClass> _di_JGoogleMap_OnMyLocationClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnMyLocationClickListener;
typedef System::DelphiInterface<JGoogleMap_OnMyLocationClickListener> _di_JGoogleMap_OnMyLocationClickListener;
class DELPHICLASS TJGoogleMap_OnMyLocationClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnPoiClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnPoiClickListenerClass> _di_JGoogleMap_OnPoiClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnPoiClickListener;
typedef System::DelphiInterface<JGoogleMap_OnPoiClickListener> _di_JGoogleMap_OnPoiClickListener;
class DELPHICLASS TJGoogleMap_OnPoiClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnPolygonClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnPolygonClickListenerClass> _di_JGoogleMap_OnPolygonClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnPolygonClickListener;
typedef System::DelphiInterface<JGoogleMap_OnPolygonClickListener> _di_JGoogleMap_OnPolygonClickListener;
class DELPHICLASS TJGoogleMap_OnPolygonClickListener;
__interface DELPHIINTERFACE JGoogleMap_OnPolylineClickListenerClass;
typedef System::DelphiInterface<JGoogleMap_OnPolylineClickListenerClass> _di_JGoogleMap_OnPolylineClickListenerClass;
__interface DELPHIINTERFACE JGoogleMap_OnPolylineClickListener;
typedef System::DelphiInterface<JGoogleMap_OnPolylineClickListener> _di_JGoogleMap_OnPolylineClickListener;
class DELPHICLASS TJGoogleMap_OnPolylineClickListener;
__interface DELPHIINTERFACE JGoogleMap_SnapshotReadyCallbackClass;
typedef System::DelphiInterface<JGoogleMap_SnapshotReadyCallbackClass> _di_JGoogleMap_SnapshotReadyCallbackClass;
__interface DELPHIINTERFACE JGoogleMap_SnapshotReadyCallback;
typedef System::DelphiInterface<JGoogleMap_SnapshotReadyCallback> _di_JGoogleMap_SnapshotReadyCallback;
class DELPHICLASS TJGoogleMap_SnapshotReadyCallback;
__interface DELPHIINTERFACE JGoogleMapOptionsClass;
typedef System::DelphiInterface<JGoogleMapOptionsClass> _di_JGoogleMapOptionsClass;
__interface DELPHIINTERFACE JGoogleMapOptions;
typedef System::DelphiInterface<JGoogleMapOptions> _di_JGoogleMapOptions;
class DELPHICLASS TJGoogleMapOptions;
__interface DELPHIINTERFACE JLocationSourceClass;
typedef System::DelphiInterface<JLocationSourceClass> _di_JLocationSourceClass;
__interface DELPHIINTERFACE JLocationSource;
typedef System::DelphiInterface<JLocationSource> _di_JLocationSource;
class DELPHICLASS TJLocationSource;
__interface DELPHIINTERFACE JLocationSource_OnLocationChangedListenerClass;
typedef System::DelphiInterface<JLocationSource_OnLocationChangedListenerClass> _di_JLocationSource_OnLocationChangedListenerClass;
__interface DELPHIINTERFACE JLocationSource_OnLocationChangedListener;
typedef System::DelphiInterface<JLocationSource_OnLocationChangedListener> _di_JLocationSource_OnLocationChangedListener;
class DELPHICLASS TJLocationSource_OnLocationChangedListener;
__interface DELPHIINTERFACE JMapFragmentClass;
typedef System::DelphiInterface<JMapFragmentClass> _di_JMapFragmentClass;
__interface DELPHIINTERFACE JMapFragment;
typedef System::DelphiInterface<JMapFragment> _di_JMapFragment;
class DELPHICLASS TJMapFragment;
__interface DELPHIINTERFACE JMapViewClass;
typedef System::DelphiInterface<JMapViewClass> _di_JMapViewClass;
__interface DELPHIINTERFACE JMapView;
typedef System::DelphiInterface<JMapView> _di_JMapView;
class DELPHICLASS TJMapView;
__interface DELPHIINTERFACE JMapsInitializerClass;
typedef System::DelphiInterface<JMapsInitializerClass> _di_JMapsInitializerClass;
__interface DELPHIINTERFACE JMapsInitializer;
typedef System::DelphiInterface<JMapsInitializer> _di_JMapsInitializer;
class DELPHICLASS TJMapsInitializer;
__interface DELPHIINTERFACE JOnMapReadyCallbackClass;
typedef System::DelphiInterface<JOnMapReadyCallbackClass> _di_JOnMapReadyCallbackClass;
__interface DELPHIINTERFACE JOnMapReadyCallback;
typedef System::DelphiInterface<JOnMapReadyCallback> _di_JOnMapReadyCallback;
class DELPHICLASS TJOnMapReadyCallback;
__interface DELPHIINTERFACE JOnStreetViewPanoramaReadyCallbackClass;
typedef System::DelphiInterface<JOnStreetViewPanoramaReadyCallbackClass> _di_JOnStreetViewPanoramaReadyCallbackClass;
__interface DELPHIINTERFACE JOnStreetViewPanoramaReadyCallback;
typedef System::DelphiInterface<JOnStreetViewPanoramaReadyCallback> _di_JOnStreetViewPanoramaReadyCallback;
class DELPHICLASS TJOnStreetViewPanoramaReadyCallback;
__interface DELPHIINTERFACE JProjectionClass;
typedef System::DelphiInterface<JProjectionClass> _di_JProjectionClass;
__interface DELPHIINTERFACE JProjection;
typedef System::DelphiInterface<JProjection> _di_JProjection;
class DELPHICLASS TJProjection;
__interface DELPHIINTERFACE JStreetViewPanoramaClass;
typedef System::DelphiInterface<JStreetViewPanoramaClass> _di_JStreetViewPanoramaClass;
__interface DELPHIINTERFACE JStreetViewPanorama;
typedef System::DelphiInterface<JStreetViewPanorama> _di_JStreetViewPanorama;
class DELPHICLASS TJStreetViewPanorama;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass> _di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener> _di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener;
class DELPHICLASS TJStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass> _di_JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaChangeListener;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaChangeListener> _di_JStreetViewPanorama_OnStreetViewPanoramaChangeListener;
class DELPHICLASS TJStreetViewPanorama_OnStreetViewPanoramaChangeListener;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass> _di_JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaClickListener;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaClickListener> _di_JStreetViewPanorama_OnStreetViewPanoramaClickListener;
class DELPHICLASS TJStreetViewPanorama_OnStreetViewPanoramaClickListener;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass> _di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass;
__interface DELPHIINTERFACE JStreetViewPanorama_OnStreetViewPanoramaLongClickListener;
typedef System::DelphiInterface<JStreetViewPanorama_OnStreetViewPanoramaLongClickListener> _di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListener;
class DELPHICLASS TJStreetViewPanorama_OnStreetViewPanoramaLongClickListener;
__interface DELPHIINTERFACE JStreetViewPanoramaFragmentClass;
typedef System::DelphiInterface<JStreetViewPanoramaFragmentClass> _di_JStreetViewPanoramaFragmentClass;
__interface DELPHIINTERFACE JStreetViewPanoramaFragment;
typedef System::DelphiInterface<JStreetViewPanoramaFragment> _di_JStreetViewPanoramaFragment;
class DELPHICLASS TJStreetViewPanoramaFragment;
__interface DELPHIINTERFACE JStreetViewPanoramaOptionsClass;
typedef System::DelphiInterface<JStreetViewPanoramaOptionsClass> _di_JStreetViewPanoramaOptionsClass;
__interface DELPHIINTERFACE JStreetViewPanoramaOptions;
typedef System::DelphiInterface<JStreetViewPanoramaOptions> _di_JStreetViewPanoramaOptions;
class DELPHICLASS TJStreetViewPanoramaOptions;
__interface DELPHIINTERFACE JStreetViewPanoramaViewClass;
typedef System::DelphiInterface<JStreetViewPanoramaViewClass> _di_JStreetViewPanoramaViewClass;
__interface DELPHIINTERFACE JStreetViewPanoramaView;
typedef System::DelphiInterface<JStreetViewPanoramaView> _di_JStreetViewPanoramaView;
class DELPHICLASS TJStreetViewPanoramaView;
__interface DELPHIINTERFACE JSupportMapFragmentClass;
typedef System::DelphiInterface<JSupportMapFragmentClass> _di_JSupportMapFragmentClass;
__interface DELPHIINTERFACE JSupportMapFragment;
typedef System::DelphiInterface<JSupportMapFragment> _di_JSupportMapFragment;
class DELPHICLASS TJSupportMapFragment;
__interface DELPHIINTERFACE JSupportStreetViewPanoramaFragmentClass;
typedef System::DelphiInterface<JSupportStreetViewPanoramaFragmentClass> _di_JSupportStreetViewPanoramaFragmentClass;
__interface DELPHIINTERFACE JSupportStreetViewPanoramaFragment;
typedef System::DelphiInterface<JSupportStreetViewPanoramaFragment> _di_JSupportStreetViewPanoramaFragment;
class DELPHICLASS TJSupportStreetViewPanoramaFragment;
__interface DELPHIINTERFACE JUiSettingsClass;
typedef System::DelphiInterface<JUiSettingsClass> _di_JUiSettingsClass;
__interface DELPHIINTERFACE JUiSettings;
typedef System::DelphiInterface<JUiSettings> _di_JUiSettings;
class DELPHICLASS TJUiSettings;
__interface DELPHIINTERFACE JBitmapDescriptorClass;
typedef System::DelphiInterface<JBitmapDescriptorClass> _di_JBitmapDescriptorClass;
__interface DELPHIINTERFACE JBitmapDescriptor;
typedef System::DelphiInterface<JBitmapDescriptor> _di_JBitmapDescriptor;
class DELPHICLASS TJBitmapDescriptor;
__interface DELPHIINTERFACE JBitmapDescriptorFactoryClass;
typedef System::DelphiInterface<JBitmapDescriptorFactoryClass> _di_JBitmapDescriptorFactoryClass;
__interface DELPHIINTERFACE JBitmapDescriptorFactory;
typedef System::DelphiInterface<JBitmapDescriptorFactory> _di_JBitmapDescriptorFactory;
class DELPHICLASS TJBitmapDescriptorFactory;
__interface DELPHIINTERFACE JCapClass;
typedef System::DelphiInterface<JCapClass> _di_JCapClass;
__interface DELPHIINTERFACE JCap;
typedef System::DelphiInterface<JCap> _di_JCap;
class DELPHICLASS TJCap;
__interface DELPHIINTERFACE JButtCapClass;
typedef System::DelphiInterface<JButtCapClass> _di_JButtCapClass;
__interface DELPHIINTERFACE JButtCap;
typedef System::DelphiInterface<JButtCap> _di_JButtCap;
class DELPHICLASS TJButtCap;
__interface DELPHIINTERFACE JCameraPositionClass;
typedef System::DelphiInterface<JCameraPositionClass> _di_JCameraPositionClass;
__interface DELPHIINTERFACE JCameraPosition;
typedef System::DelphiInterface<JCameraPosition> _di_JCameraPosition;
class DELPHICLASS TJCameraPosition;
__interface DELPHIINTERFACE JCameraPosition_BuilderClass;
typedef System::DelphiInterface<JCameraPosition_BuilderClass> _di_JCameraPosition_BuilderClass;
__interface DELPHIINTERFACE JCameraPosition_Builder;
typedef System::DelphiInterface<JCameraPosition_Builder> _di_JCameraPosition_Builder;
class DELPHICLASS TJCameraPosition_Builder;
__interface DELPHIINTERFACE JCircleClass;
typedef System::DelphiInterface<JCircleClass> _di_JCircleClass;
__interface DELPHIINTERFACE JCircle;
typedef System::DelphiInterface<JCircle> _di_JCircle;
class DELPHICLASS TJCircle;
__interface DELPHIINTERFACE JCircleOptionsClass;
typedef System::DelphiInterface<JCircleOptionsClass> _di_JCircleOptionsClass;
__interface DELPHIINTERFACE JCircleOptions;
typedef System::DelphiInterface<JCircleOptions> _di_JCircleOptions;
class DELPHICLASS TJCircleOptions;
__interface DELPHIINTERFACE JCustomCapClass;
typedef System::DelphiInterface<JCustomCapClass> _di_JCustomCapClass;
__interface DELPHIINTERFACE JCustomCap;
typedef System::DelphiInterface<JCustomCap> _di_JCustomCap;
class DELPHICLASS TJCustomCap;
__interface DELPHIINTERFACE JPatternItemClass;
typedef System::DelphiInterface<JPatternItemClass> _di_JPatternItemClass;
__interface DELPHIINTERFACE JPatternItem;
typedef System::DelphiInterface<JPatternItem> _di_JPatternItem;
class DELPHICLASS TJPatternItem;
__interface DELPHIINTERFACE JDashClass;
typedef System::DelphiInterface<JDashClass> _di_JDashClass;
__interface DELPHIINTERFACE JDash;
typedef System::DelphiInterface<JDash> _di_JDash;
class DELPHICLASS TJDash;
__interface DELPHIINTERFACE JDotClass;
typedef System::DelphiInterface<JDotClass> _di_JDotClass;
__interface DELPHIINTERFACE JDot;
typedef System::DelphiInterface<JDot> _di_JDot;
class DELPHICLASS TJDot;
__interface DELPHIINTERFACE JGapClass;
typedef System::DelphiInterface<JGapClass> _di_JGapClass;
__interface DELPHIINTERFACE JGap;
typedef System::DelphiInterface<JGap> _di_JGap;
class DELPHICLASS TJGap;
__interface DELPHIINTERFACE JGroundOverlayClass;
typedef System::DelphiInterface<JGroundOverlayClass> _di_JGroundOverlayClass;
__interface DELPHIINTERFACE JGroundOverlay;
typedef System::DelphiInterface<JGroundOverlay> _di_JGroundOverlay;
class DELPHICLASS TJGroundOverlay;
__interface DELPHIINTERFACE JGroundOverlayOptionsClass;
typedef System::DelphiInterface<JGroundOverlayOptionsClass> _di_JGroundOverlayOptionsClass;
__interface DELPHIINTERFACE JGroundOverlayOptions;
typedef System::DelphiInterface<JGroundOverlayOptions> _di_JGroundOverlayOptions;
class DELPHICLASS TJGroundOverlayOptions;
__interface DELPHIINTERFACE JIndoorBuildingClass;
typedef System::DelphiInterface<JIndoorBuildingClass> _di_JIndoorBuildingClass;
__interface DELPHIINTERFACE JIndoorBuilding;
typedef System::DelphiInterface<JIndoorBuilding> _di_JIndoorBuilding;
class DELPHICLASS TJIndoorBuilding;
__interface DELPHIINTERFACE JIndoorLevelClass;
typedef System::DelphiInterface<JIndoorLevelClass> _di_JIndoorLevelClass;
__interface DELPHIINTERFACE JIndoorLevel;
typedef System::DelphiInterface<JIndoorLevel> _di_JIndoorLevel;
class DELPHICLASS TJIndoorLevel;
__interface DELPHIINTERFACE JJointTypeClass;
typedef System::DelphiInterface<JJointTypeClass> _di_JJointTypeClass;
__interface DELPHIINTERFACE JJointType;
typedef System::DelphiInterface<JJointType> _di_JJointType;
class DELPHICLASS TJJointType;
__interface DELPHIINTERFACE JLatLngClass;
typedef System::DelphiInterface<JLatLngClass> _di_JLatLngClass;
__interface DELPHIINTERFACE JLatLng;
typedef System::DelphiInterface<JLatLng> _di_JLatLng;
class DELPHICLASS TJLatLng;
__interface DELPHIINTERFACE JLatLngBoundsClass;
typedef System::DelphiInterface<JLatLngBoundsClass> _di_JLatLngBoundsClass;
__interface DELPHIINTERFACE JLatLngBounds;
typedef System::DelphiInterface<JLatLngBounds> _di_JLatLngBounds;
class DELPHICLASS TJLatLngBounds;
__interface DELPHIINTERFACE JLatLngBounds_BuilderClass;
typedef System::DelphiInterface<JLatLngBounds_BuilderClass> _di_JLatLngBounds_BuilderClass;
__interface DELPHIINTERFACE JLatLngBounds_Builder;
typedef System::DelphiInterface<JLatLngBounds_Builder> _di_JLatLngBounds_Builder;
class DELPHICLASS TJLatLngBounds_Builder;
__interface DELPHIINTERFACE JMapStyleOptionsClass;
typedef System::DelphiInterface<JMapStyleOptionsClass> _di_JMapStyleOptionsClass;
__interface DELPHIINTERFACE JMapStyleOptions;
typedef System::DelphiInterface<JMapStyleOptions> _di_JMapStyleOptions;
class DELPHICLASS TJMapStyleOptions;
__interface DELPHIINTERFACE JMarkerClass;
typedef System::DelphiInterface<JMarkerClass> _di_JMarkerClass;
__interface DELPHIINTERFACE JMarker;
typedef System::DelphiInterface<JMarker> _di_JMarker;
class DELPHICLASS TJMarker;
__interface DELPHIINTERFACE JMarkerOptionsClass;
typedef System::DelphiInterface<JMarkerOptionsClass> _di_JMarkerOptionsClass;
__interface DELPHIINTERFACE JMarkerOptions;
typedef System::DelphiInterface<JMarkerOptions> _di_JMarkerOptions;
class DELPHICLASS TJMarkerOptions;
__interface DELPHIINTERFACE JPointOfInterestClass;
typedef System::DelphiInterface<JPointOfInterestClass> _di_JPointOfInterestClass;
__interface DELPHIINTERFACE JPointOfInterest;
typedef System::DelphiInterface<JPointOfInterest> _di_JPointOfInterest;
class DELPHICLASS TJPointOfInterest;
__interface DELPHIINTERFACE JPolygonClass;
typedef System::DelphiInterface<JPolygonClass> _di_JPolygonClass;
__interface DELPHIINTERFACE JPolygon;
typedef System::DelphiInterface<JPolygon> _di_JPolygon;
class DELPHICLASS TJPolygon;
__interface DELPHIINTERFACE JPolygonOptionsClass;
typedef System::DelphiInterface<JPolygonOptionsClass> _di_JPolygonOptionsClass;
__interface DELPHIINTERFACE JPolygonOptions;
typedef System::DelphiInterface<JPolygonOptions> _di_JPolygonOptions;
class DELPHICLASS TJPolygonOptions;
__interface DELPHIINTERFACE JPolylineClass;
typedef System::DelphiInterface<JPolylineClass> _di_JPolylineClass;
__interface DELPHIINTERFACE JPolyline;
typedef System::DelphiInterface<JPolyline> _di_JPolyline;
class DELPHICLASS TJPolyline;
__interface DELPHIINTERFACE JPolylineOptionsClass;
typedef System::DelphiInterface<JPolylineOptionsClass> _di_JPolylineOptionsClass;
__interface DELPHIINTERFACE JPolylineOptions;
typedef System::DelphiInterface<JPolylineOptions> _di_JPolylineOptions;
class DELPHICLASS TJPolylineOptions;
__interface DELPHIINTERFACE JRoundCapClass;
typedef System::DelphiInterface<JRoundCapClass> _di_JRoundCapClass;
__interface DELPHIINTERFACE JRoundCap;
typedef System::DelphiInterface<JRoundCap> _di_JRoundCap;
class DELPHICLASS TJRoundCap;
__interface DELPHIINTERFACE JRuntimeRemoteExceptionClass;
typedef System::DelphiInterface<JRuntimeRemoteExceptionClass> _di_JRuntimeRemoteExceptionClass;
__interface DELPHIINTERFACE JRuntimeRemoteException;
typedef System::DelphiInterface<JRuntimeRemoteException> _di_JRuntimeRemoteException;
class DELPHICLASS TJRuntimeRemoteException;
__interface DELPHIINTERFACE JSquareCapClass;
typedef System::DelphiInterface<JSquareCapClass> _di_JSquareCapClass;
__interface DELPHIINTERFACE JSquareCap;
typedef System::DelphiInterface<JSquareCap> _di_JSquareCap;
class DELPHICLASS TJSquareCap;
__interface DELPHIINTERFACE JStreetViewPanoramaCameraClass;
typedef System::DelphiInterface<JStreetViewPanoramaCameraClass> _di_JStreetViewPanoramaCameraClass;
__interface DELPHIINTERFACE JStreetViewPanoramaCamera;
typedef System::DelphiInterface<JStreetViewPanoramaCamera> _di_JStreetViewPanoramaCamera;
class DELPHICLASS TJStreetViewPanoramaCamera;
__interface DELPHIINTERFACE JStreetViewPanoramaCamera_BuilderClass;
typedef System::DelphiInterface<JStreetViewPanoramaCamera_BuilderClass> _di_JStreetViewPanoramaCamera_BuilderClass;
__interface DELPHIINTERFACE JStreetViewPanoramaCamera_Builder;
typedef System::DelphiInterface<JStreetViewPanoramaCamera_Builder> _di_JStreetViewPanoramaCamera_Builder;
class DELPHICLASS TJStreetViewPanoramaCamera_Builder;
__interface DELPHIINTERFACE JStreetViewPanoramaLinkClass;
typedef System::DelphiInterface<JStreetViewPanoramaLinkClass> _di_JStreetViewPanoramaLinkClass;
__interface DELPHIINTERFACE JStreetViewPanoramaLink;
typedef System::DelphiInterface<JStreetViewPanoramaLink> _di_JStreetViewPanoramaLink;
class DELPHICLASS TJStreetViewPanoramaLink;
__interface DELPHIINTERFACE JStreetViewPanoramaLocationClass;
typedef System::DelphiInterface<JStreetViewPanoramaLocationClass> _di_JStreetViewPanoramaLocationClass;
__interface DELPHIINTERFACE JStreetViewPanoramaLocation;
typedef System::DelphiInterface<JStreetViewPanoramaLocation> _di_JStreetViewPanoramaLocation;
class DELPHICLASS TJStreetViewPanoramaLocation;
__interface DELPHIINTERFACE JStreetViewPanoramaOrientationClass;
typedef System::DelphiInterface<JStreetViewPanoramaOrientationClass> _di_JStreetViewPanoramaOrientationClass;
__interface DELPHIINTERFACE JStreetViewPanoramaOrientation;
typedef System::DelphiInterface<JStreetViewPanoramaOrientation> _di_JStreetViewPanoramaOrientation;
class DELPHICLASS TJStreetViewPanoramaOrientation;
__interface DELPHIINTERFACE JStreetViewPanoramaOrientation_BuilderClass;
typedef System::DelphiInterface<JStreetViewPanoramaOrientation_BuilderClass> _di_JStreetViewPanoramaOrientation_BuilderClass;
__interface DELPHIINTERFACE JStreetViewPanoramaOrientation_Builder;
typedef System::DelphiInterface<JStreetViewPanoramaOrientation_Builder> _di_JStreetViewPanoramaOrientation_Builder;
class DELPHICLASS TJStreetViewPanoramaOrientation_Builder;
__interface DELPHIINTERFACE JStreetViewSourceClass;
typedef System::DelphiInterface<JStreetViewSourceClass> _di_JStreetViewSourceClass;
__interface DELPHIINTERFACE JStreetViewSource;
typedef System::DelphiInterface<JStreetViewSource> _di_JStreetViewSource;
class DELPHICLASS TJStreetViewSource;
__interface DELPHIINTERFACE JTileClass;
typedef System::DelphiInterface<JTileClass> _di_JTileClass;
__interface DELPHIINTERFACE JTile;
typedef System::DelphiInterface<JTile> _di_JTile;
class DELPHICLASS TJTile;
__interface DELPHIINTERFACE JTileOverlayClass;
typedef System::DelphiInterface<JTileOverlayClass> _di_JTileOverlayClass;
__interface DELPHIINTERFACE JTileOverlay;
typedef System::DelphiInterface<JTileOverlay> _di_JTileOverlay;
class DELPHICLASS TJTileOverlay;
__interface DELPHIINTERFACE JTileOverlayOptionsClass;
typedef System::DelphiInterface<JTileOverlayOptionsClass> _di_JTileOverlayOptionsClass;
__interface DELPHIINTERFACE JTileOverlayOptions;
typedef System::DelphiInterface<JTileOverlayOptions> _di_JTileOverlayOptions;
class DELPHICLASS TJTileOverlayOptions;
__interface DELPHIINTERFACE JTileProviderClass;
typedef System::DelphiInterface<JTileProviderClass> _di_JTileProviderClass;
__interface DELPHIINTERFACE JTileProvider;
typedef System::DelphiInterface<JTileProvider> _di_JTileProvider;
class DELPHICLASS TJTileProvider;
__interface DELPHIINTERFACE JUrlTileProviderClass;
typedef System::DelphiInterface<JUrlTileProviderClass> _di_JUrlTileProviderClass;
__interface DELPHIINTERFACE JUrlTileProvider;
typedef System::DelphiInterface<JUrlTileProvider> _di_JUrlTileProvider;
class DELPHICLASS TJUrlTileProvider;
__interface DELPHIINTERFACE JVisibleRegionClass;
typedef System::DelphiInterface<JVisibleRegionClass> _di_JVisibleRegionClass;
__interface DELPHIINTERFACE JVisibleRegion;
typedef System::DelphiInterface<JVisibleRegion> _di_JVisibleRegion;
class DELPHICLASS TJVisibleRegion;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{BC85B4E6-5576-4EB2-A665-AC962376DA97}") JAbstractSafeParcelableClass  : public Androidapi::Jni::Playservices::JSafeParcelableClass 
{
	virtual _di_JAbstractSafeParcelable __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{5D1DC3DA-DE62-426D-A9F1-202B7329489A}") JAbstractSafeParcelable  : public Androidapi::Jni::Playservices::JSafeParcelable 
{
	HIDESBASE virtual int __cdecl describeContents() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbstractSafeParcelable : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractSafeParcelableClass,_di_JAbstractSafeParcelable>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractSafeParcelableClass,_di_JAbstractSafeParcelable> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbstractSafeParcelable() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractSafeParcelableClass,_di_JAbstractSafeParcelable>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbstractSafeParcelable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7658457F-D0AE-4F7E-9742-545C6EABA6B3}") JIObjectWrapperClass  : public Androidapi::Jni::Os::JIInterfaceClass 
{
	
};

__interface  INTERFACE_UUID("{1BE3436C-8B90-4364-8263-9404B8F4FB72}") JIObjectWrapper  : public Androidapi::Jni::Os::JIInterface 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIObjectWrapper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIObjectWrapperClass,_di_JIObjectWrapper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIObjectWrapperClass,_di_JIObjectWrapper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIObjectWrapper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIObjectWrapperClass,_di_JIObjectWrapper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIObjectWrapper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7A21197F-BCBA-493B-B258-0631CADCB0FF}") JCameraUpdateClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{11606994-4F45-4D5B-BA4E-22ABCAFE5A15}") JCameraUpdate  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraUpdate : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateClass,_di_JCameraUpdate>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateClass,_di_JCameraUpdate> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraUpdate() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateClass,_di_JCameraUpdate>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraUpdate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{67303D3C-CEA1-4D27-A15B-64C19309A076}") JCameraUpdateFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JCameraUpdate __cdecl newCameraPosition(_di_JCameraPosition cameraPosition) = 0 ;
	virtual _di_JCameraUpdate __cdecl newLatLng(_di_JLatLng latLng) = 0 ;
	virtual _di_JCameraUpdate __cdecl newLatLngBounds(_di_JLatLngBounds latLngBounds, int i) = 0 /* overload */;
	virtual _di_JCameraUpdate __cdecl newLatLngBounds(_di_JLatLngBounds latLngBounds, int i, int i1, int i2) = 0 /* overload */;
	virtual _di_JCameraUpdate __cdecl newLatLngZoom(_di_JLatLng latLng, float f) = 0 ;
	virtual _di_JCameraUpdate __cdecl scrollBy(float f, float f1) = 0 ;
	virtual _di_JCameraUpdate __cdecl zoomBy(float f) = 0 /* overload */;
	virtual _di_JCameraUpdate __cdecl zoomBy(float f, Androidapi::Jni::Graphicscontentviewtext::_di_JPoint point) = 0 /* overload */;
	virtual _di_JCameraUpdate __cdecl zoomIn() = 0 ;
	virtual _di_JCameraUpdate __cdecl zoomOut() = 0 ;
	virtual _di_JCameraUpdate __cdecl zoomTo(float f) = 0 ;
};

__interface  INTERFACE_UUID("{4E9D6497-D772-4A4C-9E34-48B7B1EED438}") JCameraUpdateFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraUpdateFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateFactoryClass,_di_JCameraUpdateFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateFactoryClass,_di_JCameraUpdateFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraUpdateFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraUpdateFactoryClass,_di_JCameraUpdateFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraUpdateFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{400A62AC-F9F5-403A-91B0-CCA7F0FCFFA2}") JGoogleMapClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetMAP_TYPE_HYBRID() = 0 ;
	virtual int __cdecl _GetMAP_TYPE_NONE() = 0 ;
	virtual int __cdecl _GetMAP_TYPE_NORMAL() = 0 ;
	virtual int __cdecl _GetMAP_TYPE_SATELLITE() = 0 ;
	virtual int __cdecl _GetMAP_TYPE_TERRAIN() = 0 ;
	__property int MAP_TYPE_HYBRID = {read=_GetMAP_TYPE_HYBRID};
	__property int MAP_TYPE_NONE = {read=_GetMAP_TYPE_NONE};
	__property int MAP_TYPE_NORMAL = {read=_GetMAP_TYPE_NORMAL};
	__property int MAP_TYPE_SATELLITE = {read=_GetMAP_TYPE_SATELLITE};
	__property int MAP_TYPE_TERRAIN = {read=_GetMAP_TYPE_TERRAIN};
};

__interface  INTERFACE_UUID("{A525ED9B-BBC7-4848-9D2B-680E9D578195}") JGoogleMap  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JCircle __cdecl addCircle(_di_JCircleOptions circleOptions) = 0 ;
	virtual _di_JGroundOverlay __cdecl addGroundOverlay(_di_JGroundOverlayOptions groundOverlayOptions) = 0 ;
	virtual _di_JMarker __cdecl addMarker(_di_JMarkerOptions markerOptions) = 0 ;
	virtual _di_JPolygon __cdecl addPolygon(_di_JPolygonOptions polygonOptions) = 0 ;
	virtual _di_JPolyline __cdecl addPolyline(_di_JPolylineOptions polylineOptions) = 0 ;
	virtual _di_JTileOverlay __cdecl addTileOverlay(_di_JTileOverlayOptions tileOverlayOptions) = 0 ;
	virtual void __cdecl animateCamera(_di_JCameraUpdate cameraUpdate) = 0 /* overload */;
	virtual void __cdecl animateCamera(_di_JCameraUpdate cameraUpdate, _di_JGoogleMap_CancelableCallback cancelableCallback) = 0 /* overload */;
	virtual void __cdecl animateCamera(_di_JCameraUpdate cameraUpdate, int i, _di_JGoogleMap_CancelableCallback cancelableCallback) = 0 /* overload */;
	virtual void __cdecl clear() = 0 ;
	virtual _di_JCameraPosition __cdecl getCameraPosition() = 0 ;
	virtual _di_JIndoorBuilding __cdecl getFocusedBuilding() = 0 ;
	virtual int __cdecl getMapType() = 0 ;
	virtual float __cdecl getMaxZoomLevel() = 0 ;
	virtual float __cdecl getMinZoomLevel() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocation __cdecl getMyLocation() = 0 ;
	virtual _di_JProjection __cdecl getProjection() = 0 ;
	virtual _di_JUiSettings __cdecl getUiSettings() = 0 ;
	virtual bool __cdecl isBuildingsEnabled() = 0 ;
	virtual bool __cdecl isIndoorEnabled() = 0 ;
	virtual bool __cdecl isMyLocationEnabled() = 0 ;
	virtual bool __cdecl isTrafficEnabled() = 0 ;
	virtual void __cdecl moveCamera(_di_JCameraUpdate cameraUpdate) = 0 ;
	virtual void __cdecl resetMinMaxZoomPreference() = 0 ;
	virtual void __cdecl setBuildingsEnabled(bool b) = 0 ;
	virtual void __cdecl setContentDescription(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual bool __cdecl setIndoorEnabled(bool b) = 0 ;
	virtual void __cdecl setInfoWindowAdapter(_di_JGoogleMap_InfoWindowAdapter infoWindowAdapter) = 0 ;
	virtual void __cdecl setLatLngBoundsForCameraTarget(_di_JLatLngBounds latLngBounds) = 0 ;
	virtual void __cdecl setLocationSource(_di_JLocationSource locationSource) = 0 ;
	virtual bool __cdecl setMapStyle(_di_JMapStyleOptions mapStyleOptions) = 0 ;
	virtual void __cdecl setMapType(int i) = 0 ;
	virtual void __cdecl setMaxZoomPreference(float f) = 0 ;
	virtual void __cdecl setMinZoomPreference(float f) = 0 ;
	virtual void __cdecl setMyLocationEnabled(bool b) = 0 ;
	virtual void __cdecl setOnCameraChangeListener(_di_JGoogleMap_OnCameraChangeListener onCameraChangeListener) = 0 ;
	virtual void __cdecl setOnCameraIdleListener(_di_JGoogleMap_OnCameraIdleListener onCameraIdleListener) = 0 ;
	virtual void __cdecl setOnCameraMoveCanceledListener(_di_JGoogleMap_OnCameraMoveCanceledListener onCameraMoveCanceledListener) = 0 ;
	virtual void __cdecl setOnCameraMoveListener(_di_JGoogleMap_OnCameraMoveListener onCameraMoveListener) = 0 ;
	virtual void __cdecl setOnCameraMoveStartedListener(_di_JGoogleMap_OnCameraMoveStartedListener onCameraMoveStartedListener) = 0 ;
	virtual void __cdecl setOnCircleClickListener(_di_JGoogleMap_OnCircleClickListener onCircleClickListener) = 0 ;
	virtual void __cdecl setOnGroundOverlayClickListener(_di_JGoogleMap_OnGroundOverlayClickListener onGroundOverlayClickListener) = 0 ;
	virtual void __cdecl setOnIndoorStateChangeListener(_di_JGoogleMap_OnIndoorStateChangeListener onIndoorStateChangeListener) = 0 ;
	virtual void __cdecl setOnInfoWindowClickListener(_di_JGoogleMap_OnInfoWindowClickListener onInfoWindowClickListener) = 0 ;
	virtual void __cdecl setOnInfoWindowCloseListener(_di_JGoogleMap_OnInfoWindowCloseListener onInfoWindowCloseListener) = 0 ;
	virtual void __cdecl setOnInfoWindowLongClickListener(_di_JGoogleMap_OnInfoWindowLongClickListener onInfoWindowLongClickListener) = 0 ;
	virtual void __cdecl setOnMapClickListener(_di_JGoogleMap_OnMapClickListener onMapClickListener) = 0 ;
	virtual void __cdecl setOnMapLoadedCallback(_di_JGoogleMap_OnMapLoadedCallback onMapLoadedCallback) = 0 ;
	virtual void __cdecl setOnMapLongClickListener(_di_JGoogleMap_OnMapLongClickListener onMapLongClickListener) = 0 ;
	virtual void __cdecl setOnMarkerClickListener(_di_JGoogleMap_OnMarkerClickListener onMarkerClickListener) = 0 ;
	virtual void __cdecl setOnMarkerDragListener(_di_JGoogleMap_OnMarkerDragListener onMarkerDragListener) = 0 ;
	virtual void __cdecl setOnMyLocationButtonClickListener(_di_JGoogleMap_OnMyLocationButtonClickListener onMyLocationButtonClickListener) = 0 ;
	virtual void __cdecl setOnMyLocationChangeListener(_di_JGoogleMap_OnMyLocationChangeListener onMyLocationChangeListener) = 0 ;
	virtual void __cdecl setOnMyLocationClickListener(_di_JGoogleMap_OnMyLocationClickListener onMyLocationClickListener) = 0 ;
	virtual void __cdecl setOnPoiClickListener(_di_JGoogleMap_OnPoiClickListener onPoiClickListener) = 0 ;
	virtual void __cdecl setOnPolygonClickListener(_di_JGoogleMap_OnPolygonClickListener onPolygonClickListener) = 0 ;
	virtual void __cdecl setOnPolylineClickListener(_di_JGoogleMap_OnPolylineClickListener onPolylineClickListener) = 0 ;
	virtual void __cdecl setPadding(int i, int i1, int i2, int i3) = 0 ;
	virtual void __cdecl setTrafficEnabled(bool b) = 0 ;
	virtual void __cdecl snapshot(_di_JGoogleMap_SnapshotReadyCallback snapshotReadyCallback) = 0 /* overload */;
	virtual void __cdecl snapshot(_di_JGoogleMap_SnapshotReadyCallback snapshotReadyCallback, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 /* overload */;
	virtual void __cdecl stopAnimation() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapClass,_di_JGoogleMap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapClass,_di_JGoogleMap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapClass,_di_JGoogleMap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9614115C-26C0-42A4-BC6B-8C5C07FFE24B}") JGoogleMap_CancelableCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D1AC9707-AC15-4906-A687-B3A628DECC9D}") JGoogleMap_CancelableCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCancel() = 0 ;
	virtual void __cdecl onFinish() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_CancelableCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_CancelableCallbackClass,_di_JGoogleMap_CancelableCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_CancelableCallbackClass,_di_JGoogleMap_CancelableCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_CancelableCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_CancelableCallbackClass,_di_JGoogleMap_CancelableCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_CancelableCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4767E38C-50FA-43D2-A353-6562739F9B82}") JGoogleMap_InfoWindowAdapterClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{DFF8DAEB-2C2B-44CC-9688-B88308CB1025}") JGoogleMap_InfoWindowAdapter  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getInfoContents(_di_JMarker marker) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getInfoWindow(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_InfoWindowAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_InfoWindowAdapterClass,_di_JGoogleMap_InfoWindowAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_InfoWindowAdapterClass,_di_JGoogleMap_InfoWindowAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_InfoWindowAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_InfoWindowAdapterClass,_di_JGoogleMap_InfoWindowAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_InfoWindowAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DCCF80DA-1231-4C0C-9161-93BA6A899D9A}") JGoogleMap_OnCameraChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{599287B7-6F74-4D70-822D-9C55486B2C89}") JGoogleMap_OnCameraChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraChange(_di_JCameraPosition cameraPosition) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCameraChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraChangeListenerClass,_di_JGoogleMap_OnCameraChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraChangeListenerClass,_di_JGoogleMap_OnCameraChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCameraChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraChangeListenerClass,_di_JGoogleMap_OnCameraChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCameraChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CC208FBF-1F35-447B-AB28-45103280A32C}") JGoogleMap_OnCameraIdleListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E248D5E4-9FEF-47EC-A8B8-83F387591B7C}") JGoogleMap_OnCameraIdleListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraIdle() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCameraIdleListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraIdleListenerClass,_di_JGoogleMap_OnCameraIdleListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraIdleListenerClass,_di_JGoogleMap_OnCameraIdleListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCameraIdleListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraIdleListenerClass,_di_JGoogleMap_OnCameraIdleListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCameraIdleListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CB1C3E9C-AA1F-4CC5-84CB-01DED61A27AA}") JGoogleMap_OnCameraMoveCanceledListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{02938C7D-4C39-49A1-ABAD-BF755A1F63C5}") JGoogleMap_OnCameraMoveCanceledListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraMoveCanceled() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCameraMoveCanceledListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveCanceledListenerClass,_di_JGoogleMap_OnCameraMoveCanceledListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveCanceledListenerClass,_di_JGoogleMap_OnCameraMoveCanceledListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCameraMoveCanceledListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveCanceledListenerClass,_di_JGoogleMap_OnCameraMoveCanceledListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCameraMoveCanceledListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{66C0C861-DFDD-457A-9DFC-C47EC44DFBB5}") JGoogleMap_OnCameraMoveListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{76D455BE-93FF-43C1-85E0-2E18D7F432AB}") JGoogleMap_OnCameraMoveListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraMove() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCameraMoveListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveListenerClass,_di_JGoogleMap_OnCameraMoveListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveListenerClass,_di_JGoogleMap_OnCameraMoveListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCameraMoveListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveListenerClass,_di_JGoogleMap_OnCameraMoveListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCameraMoveListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B8FE659B-FD7C-4B26-A902-411E286BA74E}") JGoogleMap_OnCameraMoveStartedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetREASON_API_ANIMATION() = 0 ;
	virtual int __cdecl _GetREASON_DEVELOPER_ANIMATION() = 0 ;
	virtual int __cdecl _GetREASON_GESTURE() = 0 ;
	__property int REASON_API_ANIMATION = {read=_GetREASON_API_ANIMATION};
	__property int REASON_DEVELOPER_ANIMATION = {read=_GetREASON_DEVELOPER_ANIMATION};
	__property int REASON_GESTURE = {read=_GetREASON_GESTURE};
};

__interface  INTERFACE_UUID("{2D047FE1-DB2E-4C52-A4B9-3F497A38A7D0}") JGoogleMap_OnCameraMoveStartedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraMoveStarted(int i) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCameraMoveStartedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveStartedListenerClass,_di_JGoogleMap_OnCameraMoveStartedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveStartedListenerClass,_di_JGoogleMap_OnCameraMoveStartedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCameraMoveStartedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCameraMoveStartedListenerClass,_di_JGoogleMap_OnCameraMoveStartedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCameraMoveStartedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5420A4B2-2F9C-46CE-A7C6-3B26873F0F99}") JGoogleMap_OnCircleClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{63BC1847-5657-4BAD-B66B-EBF152F5FDAA}") JGoogleMap_OnCircleClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCircleClick(_di_JCircle circle) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnCircleClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCircleClickListenerClass,_di_JGoogleMap_OnCircleClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCircleClickListenerClass,_di_JGoogleMap_OnCircleClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnCircleClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnCircleClickListenerClass,_di_JGoogleMap_OnCircleClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnCircleClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D81916A6-D10D-474A-8963-7EAB58D68C7E}") JGoogleMap_OnGroundOverlayClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{9F7BF0D5-A76C-4097-926C-84A851DAD335}") JGoogleMap_OnGroundOverlayClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onGroundOverlayClick(_di_JGroundOverlay groundOverlay) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnGroundOverlayClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnGroundOverlayClickListenerClass,_di_JGoogleMap_OnGroundOverlayClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnGroundOverlayClickListenerClass,_di_JGoogleMap_OnGroundOverlayClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnGroundOverlayClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnGroundOverlayClickListenerClass,_di_JGoogleMap_OnGroundOverlayClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnGroundOverlayClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C1CB6EA4-0F8B-4373-9950-D9F40A990131}") JGoogleMap_OnIndoorStateChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C684287F-B4AC-4F02-81B7-57BA3E55F2B0}") JGoogleMap_OnIndoorStateChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onIndoorBuildingFocused() = 0 ;
	virtual void __cdecl onIndoorLevelActivated(_di_JIndoorBuilding indoorBuilding) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnIndoorStateChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnIndoorStateChangeListenerClass,_di_JGoogleMap_OnIndoorStateChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnIndoorStateChangeListenerClass,_di_JGoogleMap_OnIndoorStateChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnIndoorStateChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnIndoorStateChangeListenerClass,_di_JGoogleMap_OnIndoorStateChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnIndoorStateChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{020474F8-83E2-4E62-A37E-F07D54D4298A}") JGoogleMap_OnInfoWindowClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{FB213E06-A38F-4C91-998D-AB98AF202C29}") JGoogleMap_OnInfoWindowClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onInfoWindowClick(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnInfoWindowClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowClickListenerClass,_di_JGoogleMap_OnInfoWindowClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowClickListenerClass,_di_JGoogleMap_OnInfoWindowClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnInfoWindowClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowClickListenerClass,_di_JGoogleMap_OnInfoWindowClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnInfoWindowClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A591A5F1-7389-44CC-97E3-C29A4F7E1851}") JGoogleMap_OnInfoWindowCloseListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F3E1E561-6C2A-4D91-9637-4CC1497C58BF}") JGoogleMap_OnInfoWindowCloseListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onInfoWindowClose(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnInfoWindowCloseListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowCloseListenerClass,_di_JGoogleMap_OnInfoWindowCloseListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowCloseListenerClass,_di_JGoogleMap_OnInfoWindowCloseListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnInfoWindowCloseListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowCloseListenerClass,_di_JGoogleMap_OnInfoWindowCloseListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnInfoWindowCloseListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C87D0063-F309-41A9-A26D-2CB79742D3A5}") JGoogleMap_OnInfoWindowLongClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E838384E-5ADA-46CB-A1A6-F06BD97A7AF8}") JGoogleMap_OnInfoWindowLongClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onInfoWindowLongClick(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnInfoWindowLongClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowLongClickListenerClass,_di_JGoogleMap_OnInfoWindowLongClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowLongClickListenerClass,_di_JGoogleMap_OnInfoWindowLongClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnInfoWindowLongClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnInfoWindowLongClickListenerClass,_di_JGoogleMap_OnInfoWindowLongClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnInfoWindowLongClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0964A15E-AF26-4F35-8AC8-BB937E0A68B5}") JGoogleMap_OnMapClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B1E14548-02B7-4168-AEB6-26A64E23FC91}") JGoogleMap_OnMapClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMapClick(_di_JLatLng latLng) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMapClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapClickListenerClass,_di_JGoogleMap_OnMapClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapClickListenerClass,_di_JGoogleMap_OnMapClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMapClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapClickListenerClass,_di_JGoogleMap_OnMapClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMapClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9C276FB8-9468-4FD0-99B6-5C75B16448E0}") JGoogleMap_OnMapLoadedCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{0B425EB3-1B2A-4936-851A-0DD6BE9CDD88}") JGoogleMap_OnMapLoadedCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMapLoaded() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMapLoadedCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLoadedCallbackClass,_di_JGoogleMap_OnMapLoadedCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLoadedCallbackClass,_di_JGoogleMap_OnMapLoadedCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMapLoadedCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLoadedCallbackClass,_di_JGoogleMap_OnMapLoadedCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMapLoadedCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{17AD8C33-1410-4CB4-8DCA-9E4FF3A872BA}") JGoogleMap_OnMapLongClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F0789EA1-C5E2-4269-A67A-5FF1B0482CA5}") JGoogleMap_OnMapLongClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMapLongClick(_di_JLatLng latLng) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMapLongClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLongClickListenerClass,_di_JGoogleMap_OnMapLongClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLongClickListenerClass,_di_JGoogleMap_OnMapLongClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMapLongClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMapLongClickListenerClass,_di_JGoogleMap_OnMapLongClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMapLongClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0726010E-E833-4431-B205-F5D1978508F4}") JGoogleMap_OnMarkerClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C3FD23CC-A959-4720-A91D-22074E303764}") JGoogleMap_OnMarkerClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onMarkerClick(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMarkerClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerClickListenerClass,_di_JGoogleMap_OnMarkerClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerClickListenerClass,_di_JGoogleMap_OnMarkerClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMarkerClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerClickListenerClass,_di_JGoogleMap_OnMarkerClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMarkerClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6E1353C5-A89C-4DAD-9613-1029DA10D9E4}") JGoogleMap_OnMarkerDragListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F4D0B32E-859B-47D6-8ECD-573590756CD9}") JGoogleMap_OnMarkerDragListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMarkerDrag(_di_JMarker marker) = 0 ;
	virtual void __cdecl onMarkerDragEnd(_di_JMarker marker) = 0 ;
	virtual void __cdecl onMarkerDragStart(_di_JMarker marker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMarkerDragListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerDragListenerClass,_di_JGoogleMap_OnMarkerDragListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerDragListenerClass,_di_JGoogleMap_OnMarkerDragListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMarkerDragListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMarkerDragListenerClass,_di_JGoogleMap_OnMarkerDragListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMarkerDragListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{69815418-ECFB-4F8B-8CCF-062E5BA9DCAD}") JGoogleMap_OnMyLocationButtonClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BE4965DB-A640-42DA-9AD2-1F96425737F1}") JGoogleMap_OnMyLocationButtonClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onMyLocationButtonClick() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMyLocationButtonClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationButtonClickListenerClass,_di_JGoogleMap_OnMyLocationButtonClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationButtonClickListenerClass,_di_JGoogleMap_OnMyLocationButtonClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMyLocationButtonClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationButtonClickListenerClass,_di_JGoogleMap_OnMyLocationButtonClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMyLocationButtonClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A016AFD3-AE05-4306-80C4-DDED25000E54}") JGoogleMap_OnMyLocationChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{44089694-6E57-4859-939D-97E59C7BAAAE}") JGoogleMap_OnMyLocationChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMyLocationChange(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMyLocationChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationChangeListenerClass,_di_JGoogleMap_OnMyLocationChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationChangeListenerClass,_di_JGoogleMap_OnMyLocationChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMyLocationChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationChangeListenerClass,_di_JGoogleMap_OnMyLocationChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMyLocationChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F27AEAB1-A0DB-4D40-92AB-E209EA44CDC1}") JGoogleMap_OnMyLocationClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{80069797-79A1-481F-AA5D-6EEC22A9C5B0}") JGoogleMap_OnMyLocationClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMyLocationClick(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnMyLocationClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationClickListenerClass,_di_JGoogleMap_OnMyLocationClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationClickListenerClass,_di_JGoogleMap_OnMyLocationClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnMyLocationClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnMyLocationClickListenerClass,_di_JGoogleMap_OnMyLocationClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnMyLocationClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{707F3621-FE40-46E0-889F-EF2143839FFF}") JGoogleMap_OnPoiClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E5BCCD09-DBB2-470C-A231-D42C662B04F6}") JGoogleMap_OnPoiClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onPoiClick(_di_JPointOfInterest pointOfInterest) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnPoiClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPoiClickListenerClass,_di_JGoogleMap_OnPoiClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPoiClickListenerClass,_di_JGoogleMap_OnPoiClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnPoiClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPoiClickListenerClass,_di_JGoogleMap_OnPoiClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnPoiClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B583D43C-6616-4146-9CD9-F5E8223C490A}") JGoogleMap_OnPolygonClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{7666A22B-58B2-41B9-97BD-C682B5D35B76}") JGoogleMap_OnPolygonClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onPolygonClick(_di_JPolygon polygon) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnPolygonClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolygonClickListenerClass,_di_JGoogleMap_OnPolygonClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolygonClickListenerClass,_di_JGoogleMap_OnPolygonClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnPolygonClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolygonClickListenerClass,_di_JGoogleMap_OnPolygonClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnPolygonClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E2ED7D90-D888-4565-8CF3-FB00DCC4F619}") JGoogleMap_OnPolylineClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{5E980422-D8A1-44EF-B3D5-7177578D1EB8}") JGoogleMap_OnPolylineClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onPolylineClick(_di_JPolyline polyline) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_OnPolylineClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolylineClickListenerClass,_di_JGoogleMap_OnPolylineClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolylineClickListenerClass,_di_JGoogleMap_OnPolylineClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_OnPolylineClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_OnPolylineClickListenerClass,_di_JGoogleMap_OnPolylineClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_OnPolylineClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{61B0A354-3EDF-4C4C-AFA1-31C9ECD7E7CD}") JGoogleMap_SnapshotReadyCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{53C58A5E-B8D3-4999-924B-8D053025EA12}") JGoogleMap_SnapshotReadyCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSnapshotReady(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMap_SnapshotReadyCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_SnapshotReadyCallbackClass,_di_JGoogleMap_SnapshotReadyCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_SnapshotReadyCallbackClass,_di_JGoogleMap_SnapshotReadyCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMap_SnapshotReadyCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMap_SnapshotReadyCallbackClass,_di_JGoogleMap_SnapshotReadyCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMap_SnapshotReadyCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6858A5C7-54A7-40DE-9A0C-1DC32ED24A12}") JGoogleMapOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JGoogleMapOptions __cdecl createFromAttributes(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 ;
	HIDESBASE virtual _di_JGoogleMapOptions __cdecl init() = 0 /* overload */;
	virtual _di_JLatLngBounds __cdecl zza(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 ;
	virtual _di_JCameraPosition __cdecl zzb(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{DC638BBD-E6D4-4F74-B531-53B24E101B06}") JGoogleMapOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JGoogleMapOptions __cdecl ambientEnabled(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl camera(_di_JCameraPosition cameraPosition) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl compassEnabled(bool b) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getAmbientEnabled() = 0 ;
	virtual _di_JCameraPosition __cdecl getCamera() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getCompassEnabled() = 0 ;
	virtual _di_JLatLngBounds __cdecl getLatLngBoundsForCameraTarget() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getLiteMode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getMapToolbarEnabled() = 0 ;
	virtual int __cdecl getMapType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFloat __cdecl getMaxZoomPreference() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFloat __cdecl getMinZoomPreference() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getRotateGesturesEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getScrollGesturesEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getScrollGesturesEnabledDuringRotateOrZoom() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getTiltGesturesEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getUseViewLifecycleInFragment() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getZOrderOnTop() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getZoomControlsEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getZoomGesturesEnabled() = 0 ;
	virtual _di_JGoogleMapOptions __cdecl latLngBoundsForCameraTarget(_di_JLatLngBounds latLngBounds) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl liteMode(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl mapToolbarEnabled(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl mapType(int i) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl maxZoomPreference(float f) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl minZoomPreference(float f) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl rotateGesturesEnabled(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl scrollGesturesEnabled(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl scrollGesturesEnabledDuringRotateOrZoom(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl tiltGesturesEnabled(bool b) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual _di_JGoogleMapOptions __cdecl useViewLifecycleInFragment(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl zOrderOnTop(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl zoomControlsEnabled(bool b) = 0 ;
	virtual _di_JGoogleMapOptions __cdecl zoomGesturesEnabled(bool b) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleMapOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapOptionsClass,_di_JGoogleMapOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapOptionsClass,_di_JGoogleMapOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleMapOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleMapOptionsClass,_di_JGoogleMapOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleMapOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DD46DE05-8B4F-47D2-8910-3B19D7FD9939}") JLocationSourceClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{DE211F4A-D940-4E56-AAE3-21F7A885E2FE}") JLocationSource  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl activate(_di_JLocationSource_OnLocationChangedListener onLocationChangedListener) = 0 ;
	virtual void __cdecl deactivate() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocationSource : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSourceClass,_di_JLocationSource>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSourceClass,_di_JLocationSource> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocationSource() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSourceClass,_di_JLocationSource>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocationSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C1885854-F25B-4E28-8AB9-2052BFBAA973}") JLocationSource_OnLocationChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8A25D8FD-F6ED-4D09-A98C-BA569E82D7BB}") JLocationSource_OnLocationChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onLocationChanged(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocationSource_OnLocationChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSource_OnLocationChangedListenerClass,_di_JLocationSource_OnLocationChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSource_OnLocationChangedListenerClass,_di_JLocationSource_OnLocationChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocationSource_OnLocationChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocationSource_OnLocationChangedListenerClass,_di_JLocationSource_OnLocationChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocationSource_OnLocationChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F06BD952-32D9-492A-A0D3-40B2F488D619}") JMapFragmentClass  : public Androidapi::Jni::App::JFragmentClass 
{
	HIDESBASE virtual _di_JMapFragment __cdecl init() = 0 ;
	virtual _di_JMapFragment __cdecl newInstance() = 0 /* overload */;
	virtual _di_JMapFragment __cdecl newInstance(_di_JGoogleMapOptions googleMapOptions) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{DA91ED13-88F8-4FE5-B934-14853D60E7FD}") JMapFragment  : public Androidapi::Jni::App::JFragment 
{
	virtual void __cdecl getMapAsync(_di_JOnMapReadyCallback onMapReadyCallback) = 0 ;
	HIDESBASE virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onAttach(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater layoutInflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup viewGroup, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	virtual void __cdecl onEnterAmbient(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onExitAmbient() = 0 ;
	HIDESBASE virtual void __cdecl onInflate(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onLowMemory() = 0 ;
	HIDESBASE virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	HIDESBASE virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMapFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapFragmentClass,_di_JMapFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapFragmentClass,_di_JMapFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMapFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapFragmentClass,_di_JMapFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMapFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1EE5FDF1-67E7-4FC9-AA41-D5B05E629B84}") JMapViewClass  : public Androidapi::Jni::Widget::JFrameLayoutClass 
{
	HIDESBASE virtual _di_JMapView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JMapView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JGoogleMapOptions googleMapOptions) = 0 /* overload */;
	HIDESBASE virtual _di_JMapView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 /* overload */;
	HIDESBASE virtual _di_JMapView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, int i) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{FDC9DF68-5392-450C-A85C-E33754D8BFAD}") JMapView  : public Androidapi::Jni::Widget::JFrameLayout 
{
	virtual void __cdecl getMapAsync(_di_JOnMapReadyCallback onMapReadyCallback) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onEnterAmbient(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onExitAmbient() = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onPause() = 0 ;
	virtual void __cdecl onResume() = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl onStop() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMapView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewClass,_di_JMapView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewClass,_di_JMapView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMapView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewClass,_di_JMapView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMapView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{589D1A92-1661-448C-9560-8F20ABA1157C}") JMapsInitializerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl initialize(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{8708DF65-6068-4C6E-B345-603FC91F7C6A}") JMapsInitializer  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMapsInitializer : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapsInitializerClass,_di_JMapsInitializer>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapsInitializerClass,_di_JMapsInitializer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMapsInitializer() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapsInitializerClass,_di_JMapsInitializer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMapsInitializer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B19B1560-053F-438D-BA83-9CCC414D09D6}") JOnMapReadyCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C5394813-868D-43FA-8778-71F37DFA699F}") JOnMapReadyCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMapReady(_di_JGoogleMap googleMap) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnMapReadyCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnMapReadyCallbackClass,_di_JOnMapReadyCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnMapReadyCallbackClass,_di_JOnMapReadyCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnMapReadyCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnMapReadyCallbackClass,_di_JOnMapReadyCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnMapReadyCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0895D7C4-D22A-43C0-9280-11E143BA90F4}") JOnStreetViewPanoramaReadyCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{35CF75E6-930A-41C2-BB00-E002699D906B}") JOnStreetViewPanoramaReadyCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStreetViewPanoramaReady(_di_JStreetViewPanorama streetViewPanorama) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnStreetViewPanoramaReadyCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnStreetViewPanoramaReadyCallbackClass,_di_JOnStreetViewPanoramaReadyCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnStreetViewPanoramaReadyCallbackClass,_di_JOnStreetViewPanoramaReadyCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnStreetViewPanoramaReadyCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnStreetViewPanoramaReadyCallbackClass,_di_JOnStreetViewPanoramaReadyCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnStreetViewPanoramaReadyCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39569102-F14D-4DC9-9FC6-CEA9F4431A79}") JProjectionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6B32610E-3FC7-4956-AD4B-3472F4023DC7}") JProjection  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JLatLng __cdecl fromScreenLocation(Androidapi::Jni::Graphicscontentviewtext::_di_JPoint point) = 0 ;
	virtual _di_JVisibleRegion __cdecl getVisibleRegion() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl toScreenLocation(_di_JLatLng latLng) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProjection : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProjectionClass,_di_JProjection>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProjectionClass,_di_JProjection> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProjection() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProjectionClass,_di_JProjection>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProjection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4B3EEDBC-E250-4AC5-902F-D2BEF2E67934}") JStreetViewPanoramaClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6AF2E5ED-8DB8-4477-8160-899CF6215AE6}") JStreetViewPanorama  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl animateTo(_di_JStreetViewPanoramaCamera streetViewPanoramaCamera, __int64 l) = 0 ;
	virtual _di_JStreetViewPanoramaLocation __cdecl getLocation() = 0 ;
	virtual _di_JStreetViewPanoramaCamera __cdecl getPanoramaCamera() = 0 ;
	virtual bool __cdecl isPanningGesturesEnabled() = 0 ;
	virtual bool __cdecl isStreetNamesEnabled() = 0 ;
	virtual bool __cdecl isUserNavigationEnabled() = 0 ;
	virtual bool __cdecl isZoomGesturesEnabled() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl orientationToPoint(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 ;
	virtual _di_JStreetViewPanoramaOrientation __cdecl pointToOrientation(Androidapi::Jni::Graphicscontentviewtext::_di_JPoint point) = 0 ;
	virtual void __cdecl setOnStreetViewPanoramaCameraChangeListener(_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener onStreetViewPanoramaCameraChangeListener) = 0 ;
	virtual void __cdecl setOnStreetViewPanoramaChangeListener(_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListener onStreetViewPanoramaChangeListener) = 0 ;
	virtual void __cdecl setOnStreetViewPanoramaClickListener(_di_JStreetViewPanorama_OnStreetViewPanoramaClickListener onStreetViewPanoramaClickListener) = 0 ;
	virtual void __cdecl setOnStreetViewPanoramaLongClickListener(_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListener onStreetViewPanoramaLongClickListener) = 0 ;
	virtual void __cdecl setPanningGesturesEnabled(bool b) = 0 ;
	virtual void __cdecl setPosition(Androidapi::Jni::Javatypes::_di_JString string_) = 0 /* overload */;
	virtual void __cdecl setPosition(_di_JLatLng latLng) = 0 /* overload */;
	virtual void __cdecl setPosition(_di_JLatLng latLng, int i) = 0 /* overload */;
	virtual void __cdecl setPosition(_di_JLatLng latLng, _di_JStreetViewSource streetViewSource) = 0 /* overload */;
	virtual void __cdecl setPosition(_di_JLatLng latLng, int i, _di_JStreetViewSource streetViewSource) = 0 /* overload */;
	virtual void __cdecl setStreetNamesEnabled(bool b) = 0 ;
	virtual void __cdecl setUserNavigationEnabled(bool b) = 0 ;
	virtual void __cdecl setZoomGesturesEnabled(bool b) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanorama : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaClass,_di_JStreetViewPanorama>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaClass,_di_JStreetViewPanorama> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanorama() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaClass,_di_JStreetViewPanorama>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanorama() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E78AA2D8-2313-4771-8FA0-89C8FD9D7A7C}") JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{0CA48059-25FC-4F3D-94F5-21F89E7837AB}") JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStreetViewPanoramaCameraChange(_di_JStreetViewPanoramaCamera streetViewPanoramaCamera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanorama_OnStreetViewPanoramaCameraChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D4BB4245-1287-47A9-BA0F-2E547DE2B14D}") JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{5AD6D8E2-4241-4F2C-A47A-ADFCE48AD7C7}") JStreetViewPanorama_OnStreetViewPanoramaChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStreetViewPanoramaChange(_di_JStreetViewPanoramaLocation streetViewPanoramaLocation) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanorama_OnStreetViewPanoramaChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanorama_OnStreetViewPanoramaChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanorama_OnStreetViewPanoramaChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A09F8620-BA9A-43E7-B14B-58D64D39955F}") JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{0435D9CA-8C7A-4957-8A98-631D3FCD324C}") JStreetViewPanorama_OnStreetViewPanoramaClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStreetViewPanoramaClick(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanorama_OnStreetViewPanoramaClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanorama_OnStreetViewPanoramaClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanorama_OnStreetViewPanoramaClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ADE613A2-0411-4450-9519-51F68A8B6327}") JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D52E917C-B2C9-4577-A699-F4CAF3935C9B}") JStreetViewPanorama_OnStreetViewPanoramaLongClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onStreetViewPanoramaLongClick(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanorama_OnStreetViewPanoramaLongClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanorama_OnStreetViewPanoramaLongClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListenerClass,_di_JStreetViewPanorama_OnStreetViewPanoramaLongClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanorama_OnStreetViewPanoramaLongClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C702A0A-833A-432D-A174-2640D0EB46AF}") JStreetViewPanoramaFragmentClass  : public Androidapi::Jni::App::JFragmentClass 
{
	HIDESBASE virtual _di_JStreetViewPanoramaFragment __cdecl init() = 0 ;
	virtual _di_JStreetViewPanoramaFragment __cdecl newInstance() = 0 /* overload */;
	virtual _di_JStreetViewPanoramaFragment __cdecl newInstance(_di_JStreetViewPanoramaOptions streetViewPanoramaOptions) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{C73359FA-461E-4856-90A5-31417BE2820C}") JStreetViewPanoramaFragment  : public Androidapi::Jni::App::JFragment 
{
	virtual void __cdecl getStreetViewPanoramaAsync(_di_JOnStreetViewPanoramaReadyCallback onStreetViewPanoramaReadyCallback) = 0 ;
	HIDESBASE virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onAttach(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater layoutInflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup viewGroup, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	HIDESBASE virtual void __cdecl onInflate(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onLowMemory() = 0 ;
	HIDESBASE virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	HIDESBASE virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaFragmentClass,_di_JStreetViewPanoramaFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaFragmentClass,_di_JStreetViewPanoramaFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaFragmentClass,_di_JStreetViewPanoramaFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{963680F2-7BF9-4290-B67F-4619FFEB3693}") JStreetViewPanoramaOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JStreetViewPanoramaOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{2F46B3FD-980C-4BDD-97FE-0A57486B3BE4}") JStreetViewPanoramaOptions  : public JAbstractSafeParcelable 
{
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getPanningGesturesEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPanoramaId() = 0 ;
	virtual _di_JLatLng __cdecl getPosition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInteger __cdecl getRadius() = 0 ;
	virtual _di_JStreetViewSource __cdecl getSource() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getStreetNamesEnabled() = 0 ;
	virtual _di_JStreetViewPanoramaCamera __cdecl getStreetViewPanoramaCamera() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getUseViewLifecycleInFragment() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getUserNavigationEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBoolean __cdecl getZoomGesturesEnabled() = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl panningGesturesEnabled(bool b) = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl panoramaCamera(_di_JStreetViewPanoramaCamera streetViewPanoramaCamera) = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl panoramaId(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl position(_di_JLatLng latLng) = 0 /* overload */;
	virtual _di_JStreetViewPanoramaOptions __cdecl position(_di_JLatLng latLng, Androidapi::Jni::Javatypes::_di_JInteger integer_) = 0 /* overload */;
	virtual _di_JStreetViewPanoramaOptions __cdecl position(_di_JLatLng latLng, _di_JStreetViewSource streetViewSource) = 0 /* overload */;
	virtual _di_JStreetViewPanoramaOptions __cdecl position(_di_JLatLng latLng, Androidapi::Jni::Javatypes::_di_JInteger integer_, _di_JStreetViewSource streetViewSource) = 0 /* overload */;
	virtual _di_JStreetViewPanoramaOptions __cdecl streetNamesEnabled(bool b) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl useViewLifecycleInFragment(bool b) = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl userNavigationEnabled(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JStreetViewPanoramaOptions __cdecl zoomGesturesEnabled(bool b) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOptionsClass,_di_JStreetViewPanoramaOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOptionsClass,_di_JStreetViewPanoramaOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOptionsClass,_di_JStreetViewPanoramaOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5DA877E2-A966-427A-BDE4-CC131CECB6B4}") JStreetViewPanoramaViewClass  : public Androidapi::Jni::Widget::JFrameLayoutClass 
{
	HIDESBASE virtual _di_JStreetViewPanoramaView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JStreetViewPanoramaOptions streetViewPanoramaOptions) = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, int i) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4DCECDD0-E0AE-4C98-AE23-1DE035826762}") JStreetViewPanoramaView  : public Androidapi::Jni::Widget::JFrameLayout 
{
	virtual void __cdecl getStreetViewPanoramaAsync(_di_JOnStreetViewPanoramaReadyCallback onStreetViewPanoramaReadyCallback) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onPause() = 0 ;
	virtual void __cdecl onResume() = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl onStop() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaViewClass,_di_JStreetViewPanoramaView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaViewClass,_di_JStreetViewPanoramaView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaViewClass,_di_JStreetViewPanoramaView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4DCB1F0B-DEE3-47DE-BFB4-5A343A3F2A7C}") JSupportMapFragmentClass  : public Androidapi::Jni::Support::Japp_FragmentClass 
{
	HIDESBASE virtual _di_JSupportMapFragment __cdecl init() = 0 ;
	virtual _di_JSupportMapFragment __cdecl newInstance() = 0 /* overload */;
	virtual _di_JSupportMapFragment __cdecl newInstance(_di_JGoogleMapOptions googleMapOptions) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4E4C9D9E-DDAA-4A2C-9C97-AA1C20C5DA3B}") JSupportMapFragment  : public Androidapi::Jni::Support::Japp_Fragment 
{
	virtual void __cdecl getMapAsync(_di_JOnMapReadyCallback onMapReadyCallback) = 0 ;
	HIDESBASE virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onAttach(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater layoutInflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup viewGroup, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	virtual void __cdecl onEnterAmbient(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	virtual void __cdecl onExitAmbient() = 0 ;
	HIDESBASE virtual void __cdecl onInflate(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onLowMemory() = 0 ;
	HIDESBASE virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	HIDESBASE virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSupportMapFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportMapFragmentClass,_di_JSupportMapFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportMapFragmentClass,_di_JSupportMapFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSupportMapFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportMapFragmentClass,_di_JSupportMapFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSupportMapFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7E6B8BCC-F9DD-4F44-A922-4911E23DC79F}") JSupportStreetViewPanoramaFragmentClass  : public Androidapi::Jni::Support::Japp_FragmentClass 
{
	HIDESBASE virtual _di_JSupportStreetViewPanoramaFragment __cdecl init() = 0 ;
	virtual _di_JSupportStreetViewPanoramaFragment __cdecl newInstance() = 0 /* overload */;
	virtual _di_JSupportStreetViewPanoramaFragment __cdecl newInstance(_di_JStreetViewPanoramaOptions streetViewPanoramaOptions) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{540F2926-5537-4013-AA52-3A33D88382A6}") JSupportStreetViewPanoramaFragment  : public Androidapi::Jni::Support::Japp_Fragment 
{
	virtual void __cdecl getStreetViewPanoramaAsync(_di_JOnStreetViewPanoramaReadyCallback onStreetViewPanoramaReadyCallback) = 0 ;
	HIDESBASE virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onAttach(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater layoutInflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup viewGroup, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	HIDESBASE virtual void __cdecl onInflate(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attributeSet, Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onLowMemory() = 0 ;
	HIDESBASE virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	HIDESBASE virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle bundle) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSupportStreetViewPanoramaFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportStreetViewPanoramaFragmentClass,_di_JSupportStreetViewPanoramaFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportStreetViewPanoramaFragmentClass,_di_JSupportStreetViewPanoramaFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSupportStreetViewPanoramaFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSupportStreetViewPanoramaFragmentClass,_di_JSupportStreetViewPanoramaFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSupportStreetViewPanoramaFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E177867D-1013-41DC-8CC9-61E764F41FC2}") JUiSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C166F17B-4B44-4A09-8542-222C1668594A}") JUiSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl isCompassEnabled() = 0 ;
	virtual bool __cdecl isIndoorLevelPickerEnabled() = 0 ;
	virtual bool __cdecl isMapToolbarEnabled() = 0 ;
	virtual bool __cdecl isMyLocationButtonEnabled() = 0 ;
	virtual bool __cdecl isRotateGesturesEnabled() = 0 ;
	virtual bool __cdecl isScrollGesturesEnabled() = 0 ;
	virtual bool __cdecl isScrollGesturesEnabledDuringRotateOrZoom() = 0 ;
	virtual bool __cdecl isTiltGesturesEnabled() = 0 ;
	virtual bool __cdecl isZoomControlsEnabled() = 0 ;
	virtual bool __cdecl isZoomGesturesEnabled() = 0 ;
	virtual void __cdecl setAllGesturesEnabled(bool b) = 0 ;
	virtual void __cdecl setCompassEnabled(bool b) = 0 ;
	virtual void __cdecl setIndoorLevelPickerEnabled(bool b) = 0 ;
	virtual void __cdecl setMapToolbarEnabled(bool b) = 0 ;
	virtual void __cdecl setMyLocationButtonEnabled(bool b) = 0 ;
	virtual void __cdecl setRotateGesturesEnabled(bool b) = 0 ;
	virtual void __cdecl setScrollGesturesEnabled(bool b) = 0 ;
	virtual void __cdecl setScrollGesturesEnabledDuringRotateOrZoom(bool b) = 0 ;
	virtual void __cdecl setTiltGesturesEnabled(bool b) = 0 ;
	virtual void __cdecl setZoomControlsEnabled(bool b) = 0 ;
	virtual void __cdecl setZoomGesturesEnabled(bool b) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJUiSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUiSettingsClass,_di_JUiSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUiSettingsClass,_di_JUiSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJUiSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUiSettingsClass,_di_JUiSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJUiSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B3AC0084-AD2D-4B7C-A2E6-46E1F05DB7F6}") JBitmapDescriptorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBitmapDescriptor __cdecl init(_di_JIObjectWrapper iObjectWrapper) = 0 ;
};

__interface  INTERFACE_UUID("{650F87E1-F0BF-4270-8ADC-11941A7015AB}") JBitmapDescriptor  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBitmapDescriptor : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorClass,_di_JBitmapDescriptor>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorClass,_di_JBitmapDescriptor> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBitmapDescriptor() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorClass,_di_JBitmapDescriptor>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBitmapDescriptor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{88545E48-00BE-4AEB-BF98-78308F5AB256}") JBitmapDescriptorFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual float __cdecl _GetHUE_AZURE() = 0 ;
	virtual float __cdecl _GetHUE_BLUE() = 0 ;
	virtual float __cdecl _GetHUE_CYAN() = 0 ;
	virtual float __cdecl _GetHUE_GREEN() = 0 ;
	virtual float __cdecl _GetHUE_MAGENTA() = 0 ;
	virtual float __cdecl _GetHUE_ORANGE() = 0 ;
	virtual float __cdecl _GetHUE_RED() = 0 ;
	virtual float __cdecl _GetHUE_ROSE() = 0 ;
	virtual float __cdecl _GetHUE_VIOLET() = 0 ;
	virtual float __cdecl _GetHUE_YELLOW() = 0 ;
	virtual _di_JBitmapDescriptor __cdecl defaultMarker() = 0 /* overload */;
	virtual _di_JBitmapDescriptor __cdecl defaultMarker(float f) = 0 /* overload */;
	virtual _di_JBitmapDescriptor __cdecl fromAsset(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JBitmapDescriptor __cdecl fromBitmap(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 ;
	virtual _di_JBitmapDescriptor __cdecl fromFile(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JBitmapDescriptor __cdecl fromPath(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JBitmapDescriptor __cdecl fromResource(int i) = 0 ;
	__property float HUE_AZURE = {read=_GetHUE_AZURE};
	__property float HUE_BLUE = {read=_GetHUE_BLUE};
	__property float HUE_CYAN = {read=_GetHUE_CYAN};
	__property float HUE_GREEN = {read=_GetHUE_GREEN};
	__property float HUE_MAGENTA = {read=_GetHUE_MAGENTA};
	__property float HUE_ORANGE = {read=_GetHUE_ORANGE};
	__property float HUE_RED = {read=_GetHUE_RED};
	__property float HUE_ROSE = {read=_GetHUE_ROSE};
	__property float HUE_VIOLET = {read=_GetHUE_VIOLET};
	__property float HUE_YELLOW = {read=_GetHUE_YELLOW};
};

__interface  INTERFACE_UUID("{83007807-E8EE-43BD-9312-78943B089FD5}") JBitmapDescriptorFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBitmapDescriptorFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorFactoryClass,_di_JBitmapDescriptorFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorFactoryClass,_di_JBitmapDescriptorFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBitmapDescriptorFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBitmapDescriptorFactoryClass,_di_JBitmapDescriptorFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBitmapDescriptorFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E4FF4EB9-32AD-4122-A174-12366D22DBD7}") JCapClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{3C9469EF-6D13-4243-9DB3-DF335056086B}") JCap  : public JAbstractSafeParcelable 
{
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCapClass,_di_JCap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCapClass,_di_JCap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCapClass,_di_JCap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3477AD23-CB76-4C0F-9822-435FC66516CF}") JButtCapClass  : public JCapClass 
{
	HIDESBASE virtual _di_JButtCap __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{B5A85163-C0A2-42B9-9426-6996A917562C}") JButtCap  : public JCap 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJButtCap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtCapClass,_di_JButtCap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtCapClass,_di_JButtCap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJButtCap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtCapClass,_di_JButtCap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJButtCap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BBC26A98-4E32-43A4-A67C-B0FF586E1071}") JCameraPositionClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JCameraPosition_Builder __cdecl builder() = 0 /* overload */;
	virtual _di_JCameraPosition_Builder __cdecl builder(_di_JCameraPosition cameraPosition) = 0 /* overload */;
	virtual _di_JCameraPosition __cdecl createFromAttributes(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 ;
	virtual _di_JCameraPosition __cdecl fromLatLngZoom(_di_JLatLng latLng, float f) = 0 ;
	HIDESBASE virtual _di_JCameraPosition __cdecl init(_di_JLatLng latLng, float f, float f1, float f2) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{CBD6FBEA-582B-473B-959B-C7EB300574A2}") JCameraPosition  : public JAbstractSafeParcelable 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual _di_JLatLng __cdecl _Gettarget() = 0 ;
	virtual float __cdecl _Gettilt() = 0 ;
	virtual float __cdecl _Getzoom() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property float bearing = {read=_Getbearing};
	__property _di_JLatLng target = {read=_Gettarget};
	__property float tilt = {read=_Gettilt};
	__property float zoom = {read=_Getzoom};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraPosition : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPositionClass,_di_JCameraPosition>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPositionClass,_di_JCameraPosition> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraPosition() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPositionClass,_di_JCameraPosition>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraPosition() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{84517F2E-069C-457D-B297-C29BCEA99D39}") JCameraPosition_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCameraPosition_Builder __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JCameraPosition_Builder __cdecl init(_di_JCameraPosition cameraPosition) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{10539B19-24B1-414A-A8C9-09FF64A805A1}") JCameraPosition_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JCameraPosition_Builder __cdecl bearing(float f) = 0 ;
	virtual _di_JCameraPosition __cdecl build() = 0 ;
	virtual _di_JCameraPosition_Builder __cdecl target(_di_JLatLng latLng) = 0 ;
	virtual _di_JCameraPosition_Builder __cdecl tilt(float f) = 0 ;
	virtual _di_JCameraPosition_Builder __cdecl zoom(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraPosition_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPosition_BuilderClass,_di_JCameraPosition_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPosition_BuilderClass,_di_JCameraPosition_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraPosition_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraPosition_BuilderClass,_di_JCameraPosition_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraPosition_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EEB20939-CDBA-4C8C-BB4E-EA9F3FB16A14}") JCircleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D1408DBE-690F-45FD-A740-8D2FA4E10CED}") JCircle  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual _di_JLatLng __cdecl getCenter() = 0 ;
	virtual int __cdecl getFillColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual double __cdecl getRadius() = 0 ;
	virtual int __cdecl getStrokeColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getStrokePattern() = 0 ;
	virtual float __cdecl getStrokeWidth() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setCenter(_di_JLatLng latLng) = 0 ;
	virtual void __cdecl setClickable(bool b) = 0 ;
	virtual void __cdecl setFillColor(int i) = 0 ;
	virtual void __cdecl setRadius(double d) = 0 ;
	virtual void __cdecl setStrokeColor(int i) = 0 ;
	virtual void __cdecl setStrokePattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setStrokeWidth(float f) = 0 ;
	virtual void __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCircle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleClass,_di_JCircle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleClass,_di_JCircle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCircle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleClass,_di_JCircle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCircle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D055A38E-CD1E-41B4-B6A0-F6EDF0869544}") JCircleOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JCircleOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{5EB2D906-C70F-48BC-A34B-BA102162163A}") JCircleOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JCircleOptions __cdecl center(_di_JLatLng latLng) = 0 ;
	virtual _di_JCircleOptions __cdecl clickable(bool b) = 0 ;
	virtual _di_JCircleOptions __cdecl fillColor(int i) = 0 ;
	virtual _di_JLatLng __cdecl getCenter() = 0 ;
	virtual int __cdecl getFillColor() = 0 ;
	virtual double __cdecl getRadius() = 0 ;
	virtual int __cdecl getStrokeColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getStrokePattern() = 0 ;
	virtual float __cdecl getStrokeWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JCircleOptions __cdecl radius(double d) = 0 ;
	virtual _di_JCircleOptions __cdecl strokeColor(int i) = 0 ;
	virtual _di_JCircleOptions __cdecl strokePattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual _di_JCircleOptions __cdecl strokeWidth(float f) = 0 ;
	virtual _di_JCircleOptions __cdecl visible(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JCircleOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCircleOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleOptionsClass,_di_JCircleOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleOptionsClass,_di_JCircleOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCircleOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCircleOptionsClass,_di_JCircleOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCircleOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D9E2F98F-A397-4C4E-A7B8-6E38AF2D36A8}") JCustomCapClass  : public JCapClass 
{
	HIDESBASE virtual _di_JCustomCap __cdecl init(_di_JBitmapDescriptor bitmapDescriptor) = 0 /* overload */;
	HIDESBASE virtual _di_JCustomCap __cdecl init(_di_JBitmapDescriptor bitmapDescriptor, float f) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{F6E4CE05-8320-4452-BDD1-273F7AF72EAB}") JCustomCap  : public JCap 
{
	virtual _di_JBitmapDescriptor __cdecl _GetbitmapDescriptor() = 0 ;
	virtual float __cdecl _GetrefWidth() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property _di_JBitmapDescriptor bitmapDescriptor = {read=_GetbitmapDescriptor};
	__property float refWidth = {read=_GetrefWidth};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCustomCap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomCapClass,_di_JCustomCap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomCapClass,_di_JCustomCap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCustomCap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomCapClass,_di_JCustomCap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCustomCap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C5B7E8F2-70E8-432A-9807-BDB46FA248E2}") JPatternItemClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JPatternItem __cdecl init(int i, Androidapi::Jni::Javatypes::_di_JFloat Float) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{86F57743-6A69-415C-A7C0-A748E58C5206}") JPatternItem  : public JAbstractSafeParcelable 
{
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPatternItem : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternItemClass,_di_JPatternItem>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternItemClass,_di_JPatternItem> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPatternItem() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternItemClass,_di_JPatternItem>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPatternItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A24797EC-548C-474C-8B5A-E775A75468A6}") JDashClass  : public JPatternItemClass 
{
	HIDESBASE virtual _di_JDash __cdecl init(float f) = 0 ;
};

__interface  INTERFACE_UUID("{7C50AE56-2EDE-4433-B304-CB789C7A391E}") JDash  : public JPatternItem 
{
	virtual float __cdecl _Getlength() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property float length = {read=_Getlength};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDash : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDashClass,_di_JDash>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDashClass,_di_JDash> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDash() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDashClass,_di_JDash>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDash() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0342CC25-6B7B-4B52-AFA6-BA2FFF25F154}") JDotClass  : public JPatternItemClass 
{
	HIDESBASE virtual _di_JDot __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{1897F356-3894-466B-8196-F713CFA4EE7E}") JDot  : public JPatternItem 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDot : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDotClass,_di_JDot>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDotClass,_di_JDot> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDot() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDotClass,_di_JDot>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDot() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3D41E857-2129-4395-AF07-53EB080D51FA}") JGapClass  : public JPatternItemClass 
{
	HIDESBASE virtual _di_JGap __cdecl init(float f) = 0 ;
};

__interface  INTERFACE_UUID("{BC9783A2-54DC-452B-83D9-5D319739538F}") JGap  : public JPatternItem 
{
	virtual float __cdecl _Getlength() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property float length = {read=_Getlength};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGapClass,_di_JGap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGapClass,_di_JGap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGapClass,_di_JGap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{71A8228E-C56A-4DEE-B5DE-600E6FE8F24D}") JGroundOverlayClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D9C7E7CE-26CA-4B65-B2B3-5A1C57E3AE3F}") JGroundOverlay  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual float __cdecl getBearing() = 0 ;
	virtual _di_JLatLngBounds __cdecl getBounds() = 0 ;
	virtual float __cdecl getHeight() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual _di_JLatLng __cdecl getPosition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual float __cdecl getTransparency() = 0 ;
	virtual float __cdecl getWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setBearing(float f) = 0 ;
	virtual void __cdecl setClickable(bool b) = 0 ;
	virtual void __cdecl setDimensions(float f) = 0 /* overload */;
	virtual void __cdecl setDimensions(float f, float f1) = 0 /* overload */;
	virtual void __cdecl setImage(_di_JBitmapDescriptor bitmapDescriptor) = 0 ;
	virtual void __cdecl setPosition(_di_JLatLng latLng) = 0 ;
	virtual void __cdecl setPositionFromBounds(_di_JLatLngBounds latLngBounds) = 0 ;
	virtual void __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual void __cdecl setTransparency(float f) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGroundOverlay : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayClass,_di_JGroundOverlay>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayClass,_di_JGroundOverlay> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGroundOverlay() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayClass,_di_JGroundOverlay>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGroundOverlay() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BAAAFFA3-3D94-421F-A2A0-BAFEC6D6DB68}") JGroundOverlayOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual float __cdecl _GetNO_DIMENSION() = 0 ;
	HIDESBASE virtual _di_JGroundOverlayOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property float NO_DIMENSION = {read=_GetNO_DIMENSION};
};

__interface  INTERFACE_UUID("{9109D62E-A7BA-44ED-9BB3-9460A31F3B94}") JGroundOverlayOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JGroundOverlayOptions __cdecl anchor(float f, float f1) = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl bearing(float f) = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl clickable(bool b) = 0 ;
	virtual float __cdecl getAnchorU() = 0 ;
	virtual float __cdecl getAnchorV() = 0 ;
	virtual float __cdecl getBearing() = 0 ;
	virtual _di_JLatLngBounds __cdecl getBounds() = 0 ;
	virtual float __cdecl getHeight() = 0 ;
	virtual _di_JBitmapDescriptor __cdecl getImage() = 0 ;
	virtual _di_JLatLng __cdecl getLocation() = 0 ;
	virtual float __cdecl getTransparency() = 0 ;
	virtual float __cdecl getWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl image(_di_JBitmapDescriptor bitmapDescriptor) = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl position(_di_JLatLng latLng, float f) = 0 /* overload */;
	virtual _di_JGroundOverlayOptions __cdecl position(_di_JLatLng latLng, float f, float f1) = 0 /* overload */;
	virtual _di_JGroundOverlayOptions __cdecl positionFromBounds(_di_JLatLngBounds latLngBounds) = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl transparency(float f) = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl visible(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JGroundOverlayOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGroundOverlayOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayOptionsClass,_di_JGroundOverlayOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayOptionsClass,_di_JGroundOverlayOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGroundOverlayOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGroundOverlayOptionsClass,_di_JGroundOverlayOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGroundOverlayOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{57086D57-C8B8-451B-8502-399EDE2AC61A}") JIndoorBuildingClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{35D9C33B-E716-406A-BC6B-1D760E6AF36E}") JIndoorBuilding  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl getActiveLevelIndex() = 0 ;
	virtual int __cdecl getDefaultLevelIndex() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getLevels() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isUnderground() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIndoorBuilding : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorBuildingClass,_di_JIndoorBuilding>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorBuildingClass,_di_JIndoorBuilding> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIndoorBuilding() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorBuildingClass,_di_JIndoorBuilding>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIndoorBuilding() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A261DE71-12D6-4383-9956-4B5BF6B3AD67}") JIndoorLevelClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2F76C0DA-FD11-402C-906A-B32F36D9609F}") JIndoorLevel  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl activate() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getShortName() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIndoorLevel : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorLevelClass,_di_JIndoorLevel>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorLevelClass,_di_JIndoorLevel> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIndoorLevel() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIndoorLevelClass,_di_JIndoorLevel>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIndoorLevel() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0E70E2B9-B9AC-4262-AFA6-68DF45137323}") JJointTypeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetBEVEL() = 0 ;
	virtual int __cdecl _GetDEFAULT() = 0 ;
	virtual int __cdecl _GetROUND() = 0 ;
	__property int BEVEL = {read=_GetBEVEL};
	__property int DEFAULT = {read=_GetDEFAULT};
	__property int ROUND = {read=_GetROUND};
};

__interface  INTERFACE_UUID("{2F4EDE05-291C-4FE6-9C44-77CFFB689CEE}") JJointType  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJointType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJointTypeClass,_di_JJointType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJointTypeClass,_di_JJointType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJointType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJointTypeClass,_di_JJointType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJointType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{009A2FD1-2E26-4E50-8D97-FF49B8D3E134}") JLatLngClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JLatLng __cdecl init(double d, double d1) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{1612BD16-050A-4E8E-BBFF-1447D11BED15}") JLatLng  : public JAbstractSafeParcelable 
{
	virtual double __cdecl _Getlatitude() = 0 ;
	virtual double __cdecl _Getlongitude() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property double latitude = {read=_Getlatitude};
	__property double longitude = {read=_Getlongitude};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLatLng : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngClass,_di_JLatLng>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngClass,_di_JLatLng> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLatLng() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngClass,_di_JLatLng>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLatLng() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E18E597F-AE80-4248-A4D1-CE1F3202668C}") JLatLngBoundsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JLatLngBounds_Builder __cdecl builder() = 0 ;
	virtual _di_JLatLngBounds __cdecl createFromAttributes(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attributeSet) = 0 ;
	HIDESBASE virtual _di_JLatLngBounds __cdecl init(_di_JLatLng latLng, _di_JLatLng latLng1) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{65EF16BB-A68A-43E0-BC7D-0FBFE1321A73}") JLatLngBounds  : public JAbstractSafeParcelable 
{
	virtual _di_JLatLng __cdecl _Getnortheast() = 0 ;
	virtual _di_JLatLng __cdecl _Getsouthwest() = 0 ;
	virtual bool __cdecl contains(_di_JLatLng latLng) = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual _di_JLatLng __cdecl getCenter() = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual _di_JLatLngBounds __cdecl including(_di_JLatLng latLng) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property _di_JLatLng northeast = {read=_Getnortheast};
	__property _di_JLatLng southwest = {read=_Getsouthwest};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLatLngBounds : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBoundsClass,_di_JLatLngBounds>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBoundsClass,_di_JLatLngBounds> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLatLngBounds() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBoundsClass,_di_JLatLngBounds>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLatLngBounds() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FD670806-8BF8-4499-A135-6A46A4905B7C}") JLatLngBounds_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLatLngBounds_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{BC10B895-4AAC-4B39-9F7A-207B7D80DFE4}") JLatLngBounds_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JLatLngBounds __cdecl build() = 0 ;
	virtual _di_JLatLngBounds_Builder __cdecl include(_di_JLatLng latLng) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLatLngBounds_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBounds_BuilderClass,_di_JLatLngBounds_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBounds_BuilderClass,_di_JLatLngBounds_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLatLngBounds_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLatLngBounds_BuilderClass,_di_JLatLngBounds_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLatLngBounds_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3D755E6C-A829-4FCE-B660-B04260D7B12F}") JMapStyleOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JMapStyleOptions __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JMapStyleOptions __cdecl loadRawResourceStyle(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int i) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{5CE77666-7040-4F26-BA4F-1DA674E99C90}") JMapStyleOptions  : public JAbstractSafeParcelable 
{
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMapStyleOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapStyleOptionsClass,_di_JMapStyleOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapStyleOptionsClass,_di_JMapStyleOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMapStyleOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapStyleOptionsClass,_di_JMapStyleOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMapStyleOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4A8555E9-4F3A-4C8A-A75E-17FB0015ABBB}") JMarkerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{16BF016C-85CC-4E27-A86A-A066BDDCA0B7}") JMarker  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual float __cdecl getAlpha() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual _di_JLatLng __cdecl getPosition() = 0 ;
	virtual float __cdecl getRotation() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSnippet() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitle() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl hideInfoWindow() = 0 ;
	virtual bool __cdecl isDraggable() = 0 ;
	virtual bool __cdecl isFlat() = 0 ;
	virtual bool __cdecl isInfoWindowShown() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setAlpha(float f) = 0 ;
	virtual void __cdecl setAnchor(float f, float f1) = 0 ;
	virtual void __cdecl setDraggable(bool b) = 0 ;
	virtual void __cdecl setFlat(bool b) = 0 ;
	virtual void __cdecl setIcon(_di_JBitmapDescriptor bitmapDescriptor) = 0 ;
	virtual void __cdecl setInfoWindowAnchor(float f, float f1) = 0 ;
	virtual void __cdecl setPosition(_di_JLatLng latLng) = 0 ;
	virtual void __cdecl setRotation(float f) = 0 ;
	virtual void __cdecl setSnippet(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual void __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
	virtual void __cdecl showInfoWindow() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMarker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerClass,_di_JMarker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerClass,_di_JMarker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMarker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerClass,_di_JMarker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMarker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BDD0C13B-A5CE-4FD0-85E0-268A9170847F}") JMarkerOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JMarkerOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{60B30661-9D1C-4E6F-999B-0F7F13556E9B}") JMarkerOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JMarkerOptions __cdecl alpha(float f) = 0 ;
	virtual _di_JMarkerOptions __cdecl anchor(float f, float f1) = 0 ;
	virtual _di_JMarkerOptions __cdecl draggable(bool b) = 0 ;
	virtual _di_JMarkerOptions __cdecl flat(bool b) = 0 ;
	virtual float __cdecl getAlpha() = 0 ;
	virtual float __cdecl getAnchorU() = 0 ;
	virtual float __cdecl getAnchorV() = 0 ;
	virtual _di_JBitmapDescriptor __cdecl getIcon() = 0 ;
	virtual float __cdecl getInfoWindowAnchorU() = 0 ;
	virtual float __cdecl getInfoWindowAnchorV() = 0 ;
	virtual _di_JLatLng __cdecl getPosition() = 0 ;
	virtual float __cdecl getRotation() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSnippet() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitle() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual _di_JMarkerOptions __cdecl icon(_di_JBitmapDescriptor bitmapDescriptor) = 0 ;
	virtual _di_JMarkerOptions __cdecl infoWindowAnchor(float f, float f1) = 0 ;
	virtual bool __cdecl isDraggable() = 0 ;
	virtual bool __cdecl isFlat() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JMarkerOptions __cdecl position(_di_JLatLng latLng) = 0 ;
	virtual _di_JMarkerOptions __cdecl rotation(float f) = 0 ;
	virtual _di_JMarkerOptions __cdecl snippet(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JMarkerOptions __cdecl title(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual _di_JMarkerOptions __cdecl visible(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JMarkerOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMarkerOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerOptionsClass,_di_JMarkerOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerOptionsClass,_di_JMarkerOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMarkerOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMarkerOptionsClass,_di_JMarkerOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMarkerOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7B83FEBC-C361-47FE-B913-45AB942D4EBB}") JPointOfInterestClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JPointOfInterest __cdecl init(_di_JLatLng latLng, Androidapi::Jni::Javatypes::_di_JString string_, Androidapi::Jni::Javatypes::_di_JString string_1) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{3EDF407A-1827-4087-B218-B9586674DDC5}") JPointOfInterest  : public JAbstractSafeParcelable 
{
	virtual _di_JLatLng __cdecl _GetlatLng() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getname() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetplaceId() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property _di_JLatLng latLng = {read=_GetlatLng};
	__property Androidapi::Jni::Javatypes::_di_JString name = {read=_Getname};
	__property Androidapi::Jni::Javatypes::_di_JString placeId = {read=_GetplaceId};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPointOfInterest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPointOfInterestClass,_di_JPointOfInterest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPointOfInterestClass,_di_JPointOfInterest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPointOfInterest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPointOfInterestClass,_di_JPointOfInterest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPointOfInterest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C32F88C3-3863-4316-AB9E-99F6501F709C}") JPolygonClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{BECE8208-AA23-48F1-AC07-849EBCABB32E}") JPolygon  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl getFillColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getHoles() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPoints() = 0 ;
	virtual int __cdecl getStrokeColor() = 0 ;
	virtual int __cdecl getStrokeJointType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getStrokePattern() = 0 ;
	virtual float __cdecl getStrokeWidth() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isGeodesic() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setClickable(bool b) = 0 ;
	virtual void __cdecl setFillColor(int i) = 0 ;
	virtual void __cdecl setGeodesic(bool b) = 0 ;
	virtual void __cdecl setHoles(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setPoints(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setStrokeColor(int i) = 0 ;
	virtual void __cdecl setStrokeJointType(int i) = 0 ;
	virtual void __cdecl setStrokePattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setStrokeWidth(float f) = 0 ;
	virtual void __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPolygon : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonClass,_di_JPolygon>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonClass,_di_JPolygon> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPolygon() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonClass,_di_JPolygon>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPolygon() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{035017D5-E83D-4EBD-9159-872BB97687F8}") JPolygonOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JPolygonOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{D44C6C92-3D47-4E5F-8BA2-0AF69743B24E}") JPolygonOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JPolygonOptions __cdecl add(_di_JLatLng latLng) = 0 /* overload */;
	virtual _di_JPolygonOptions __cdecl addAll(Androidapi::Jni::Javatypes::_di_JIterable iterable) = 0 ;
	virtual _di_JPolygonOptions __cdecl addHole(Androidapi::Jni::Javatypes::_di_JIterable iterable) = 0 ;
	virtual _di_JPolygonOptions __cdecl clickable(bool b) = 0 ;
	virtual _di_JPolygonOptions __cdecl fillColor(int i) = 0 ;
	virtual _di_JPolygonOptions __cdecl geodesic(bool b) = 0 ;
	virtual int __cdecl getFillColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getHoles() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPoints() = 0 ;
	virtual int __cdecl getStrokeColor() = 0 ;
	virtual int __cdecl getStrokeJointType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getStrokePattern() = 0 ;
	virtual float __cdecl getStrokeWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isGeodesic() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JPolygonOptions __cdecl strokeColor(int i) = 0 ;
	virtual _di_JPolygonOptions __cdecl strokeJointType(int i) = 0 ;
	virtual _di_JPolygonOptions __cdecl strokePattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual _di_JPolygonOptions __cdecl strokeWidth(float f) = 0 ;
	virtual _di_JPolygonOptions __cdecl visible(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JPolygonOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPolygonOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonOptionsClass,_di_JPolygonOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonOptionsClass,_di_JPolygonOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPolygonOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolygonOptionsClass,_di_JPolygonOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPolygonOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E56467A2-5381-457A-B96F-E67567F6FABB}") JPolylineClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{803D778F-39F8-4FF2-B9E5-8EC0BD513133}") JPolyline  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl getColor() = 0 ;
	virtual _di_JCap __cdecl getEndCap() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual int __cdecl getJointType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPattern() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPoints() = 0 ;
	virtual _di_JCap __cdecl getStartCap() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual float __cdecl getWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isGeodesic() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setClickable(bool b) = 0 ;
	virtual void __cdecl setColor(int i) = 0 ;
	virtual void __cdecl setEndCap(_di_JCap cap) = 0 ;
	virtual void __cdecl setGeodesic(bool b) = 0 ;
	virtual void __cdecl setJointType(int i) = 0 ;
	virtual void __cdecl setPattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setPoints(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl setStartCap(_di_JCap cap) = 0 ;
	virtual void __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setWidth(float f) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPolyline : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineClass,_di_JPolyline>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineClass,_di_JPolyline> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPolyline() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineClass,_di_JPolyline>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPolyline() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{73CA0FF0-3ECB-493C-822E-0D9E24EDD021}") JPolylineOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JPolylineOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{029E45C1-C7B8-4FDB-B575-B222EC3DE59F}") JPolylineOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JPolylineOptions __cdecl add(_di_JLatLng latLng) = 0 /* overload */;
	virtual _di_JPolylineOptions __cdecl addAll(Androidapi::Jni::Javatypes::_di_JIterable iterable) = 0 ;
	virtual _di_JPolylineOptions __cdecl clickable(bool b) = 0 ;
	virtual _di_JPolylineOptions __cdecl color(int i) = 0 ;
	virtual _di_JPolylineOptions __cdecl endCap(_di_JCap cap) = 0 ;
	virtual _di_JPolylineOptions __cdecl geodesic(bool b) = 0 ;
	virtual int __cdecl getColor() = 0 ;
	virtual _di_JCap __cdecl getEndCap() = 0 ;
	virtual int __cdecl getJointType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPattern() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getPoints() = 0 ;
	virtual _di_JCap __cdecl getStartCap() = 0 ;
	virtual float __cdecl getWidth() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual bool __cdecl isClickable() = 0 ;
	virtual bool __cdecl isGeodesic() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JPolylineOptions __cdecl jointType(int i) = 0 ;
	virtual _di_JPolylineOptions __cdecl pattern(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual _di_JPolylineOptions __cdecl startCap(_di_JCap cap) = 0 ;
	virtual _di_JPolylineOptions __cdecl visible(bool b) = 0 ;
	virtual _di_JPolylineOptions __cdecl width(float f) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JPolylineOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPolylineOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineOptionsClass,_di_JPolylineOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineOptionsClass,_di_JPolylineOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPolylineOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPolylineOptionsClass,_di_JPolylineOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPolylineOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3BC81636-40B1-4E70-B3B0-FFA62BB95E29}") JRoundCapClass  : public JCapClass 
{
	HIDESBASE virtual _di_JRoundCap __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{D472C801-A9DD-49C7-916B-64F1EECCC356}") JRoundCap  : public JCap 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRoundCap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRoundCapClass,_di_JRoundCap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRoundCapClass,_di_JRoundCap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRoundCap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRoundCapClass,_di_JRoundCap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRoundCap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75B6D1D4-4516-4CE8-9B0A-2BCCDA0A51B5}") JRuntimeRemoteExceptionClass  : public Androidapi::Jni::Javatypes::JRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRuntimeRemoteException __cdecl init(Androidapi::Jni::Os::_di_JRemoteException remoteException) = 0 ;
};

__interface  INTERFACE_UUID("{E6608F23-8EE1-4056-8FB7-CF5C8927EB08}") JRuntimeRemoteException  : public Androidapi::Jni::Javatypes::JRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRuntimeRemoteException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeRemoteExceptionClass,_di_JRuntimeRemoteException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeRemoteExceptionClass,_di_JRuntimeRemoteException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRuntimeRemoteException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeRemoteExceptionClass,_di_JRuntimeRemoteException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRuntimeRemoteException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{407264F5-0E3D-47F9-BFDD-532B0444F8FA}") JSquareCapClass  : public JCapClass 
{
	HIDESBASE virtual _di_JSquareCap __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{5971D21D-C816-43F9-A67A-18D03BAF4B1D}") JSquareCap  : public JCap 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSquareCap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSquareCapClass,_di_JSquareCap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSquareCapClass,_di_JSquareCap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSquareCap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSquareCapClass,_di_JSquareCap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSquareCap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2941288C-701A-418C-ADAC-71C4734C1E54}") JStreetViewPanoramaCameraClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl builder() = 0 /* overload */;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl builder(_di_JStreetViewPanoramaCamera streetViewPanoramaCamera) = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaCamera __cdecl init(float f, float f1, float f2) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{9A6C5A66-667A-469D-A093-D9118C33A999}") JStreetViewPanoramaCamera  : public JAbstractSafeParcelable 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual float __cdecl _Gettilt() = 0 ;
	virtual float __cdecl _Getzoom() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual _di_JStreetViewPanoramaOrientation __cdecl getOrientation() = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property float bearing = {read=_Getbearing};
	__property float tilt = {read=_Gettilt};
	__property float zoom = {read=_Getzoom};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaCamera : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCameraClass,_di_JStreetViewPanoramaCamera>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCameraClass,_di_JStreetViewPanoramaCamera> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaCamera() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCameraClass,_di_JStreetViewPanoramaCamera>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaCamera() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{353A7901-8520-494B-BD8C-ADF297C26957}") JStreetViewPanoramaCamera_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JStreetViewPanoramaCamera_Builder __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaCamera_Builder __cdecl init(_di_JStreetViewPanoramaCamera streetViewPanoramaCamera) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{98643D5C-EE81-482C-8B74-BA15D2029B6A}") JStreetViewPanoramaCamera_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual void __cdecl _Setbearing(float Value) = 0 ;
	virtual float __cdecl _Gettilt() = 0 ;
	virtual void __cdecl _Settilt(float Value) = 0 ;
	virtual float __cdecl _Getzoom() = 0 ;
	virtual void __cdecl _Setzoom(float Value) = 0 ;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl bearing(float f) = 0 ;
	virtual _di_JStreetViewPanoramaCamera __cdecl build() = 0 ;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl orientation(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 ;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl tilt(float f) = 0 ;
	virtual _di_JStreetViewPanoramaCamera_Builder __cdecl zoom(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaCamera_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCamera_BuilderClass,_di_JStreetViewPanoramaCamera_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCamera_BuilderClass,_di_JStreetViewPanoramaCamera_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaCamera_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaCamera_BuilderClass,_di_JStreetViewPanoramaCamera_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaCamera_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{00879990-B421-4C28-A47D-334A120E79FB}") JStreetViewPanoramaLinkClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JStreetViewPanoramaLink __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_, float f) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{9E70259B-E227-4A4B-B2EA-2B4691A783AE}") JStreetViewPanoramaLink  : public JAbstractSafeParcelable 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetpanoId() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property float bearing = {read=_Getbearing};
	__property Androidapi::Jni::Javatypes::_di_JString panoId = {read=_GetpanoId};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaLink : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLinkClass,_di_JStreetViewPanoramaLink>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLinkClass,_di_JStreetViewPanoramaLink> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaLink() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLinkClass,_di_JStreetViewPanoramaLink>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaLink() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A0DA654D-FBDA-461C-B2D0-7C913C109C94}") JStreetViewPanoramaLocationClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JStreetViewPanoramaLocation __cdecl init(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JStreetViewPanoramaLink>* streetViewPanoramaLink, _di_JLatLng latLng, Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{B45FD624-26CE-4DAF-84CC-BD1624855E0B}") JStreetViewPanoramaLocation  : public JAbstractSafeParcelable 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JStreetViewPanoramaLink>* __cdecl _Getlinks() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetpanoId() = 0 ;
	virtual _di_JLatLng __cdecl _Getposition() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property Androidapi::Jnibridge::TJavaObjectArray__1<_di_JStreetViewPanoramaLink>* links = {read=_Getlinks};
	__property Androidapi::Jni::Javatypes::_di_JString panoId = {read=_GetpanoId};
	__property _di_JLatLng position = {read=_Getposition};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaLocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLocationClass,_di_JStreetViewPanoramaLocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLocationClass,_di_JStreetViewPanoramaLocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaLocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaLocationClass,_di_JStreetViewPanoramaLocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaLocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1896E027-69F4-4154-945B-8CF352147DEB}") JStreetViewPanoramaOrientationClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl builder() = 0 /* overload */;
	virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl builder(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaOrientation __cdecl init(float f, float f1) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{BB3F797E-7930-4EC7-B937-45294A5D5FD0}") JStreetViewPanoramaOrientation  : public JAbstractSafeParcelable 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual float __cdecl _Gettilt() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property float bearing = {read=_Getbearing};
	__property float tilt = {read=_Gettilt};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaOrientation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientationClass,_di_JStreetViewPanoramaOrientation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientationClass,_di_JStreetViewPanoramaOrientation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaOrientation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientationClass,_di_JStreetViewPanoramaOrientation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaOrientation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{840613C6-73CC-408A-9851-D081432A7042}") JStreetViewPanoramaOrientation_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl init(_di_JStreetViewPanoramaOrientation streetViewPanoramaOrientation) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4A071D6A-525C-4996-BA97-D113E6984C7B}") JStreetViewPanoramaOrientation_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getbearing() = 0 ;
	virtual void __cdecl _Setbearing(float Value) = 0 ;
	virtual float __cdecl _Gettilt() = 0 ;
	virtual void __cdecl _Settilt(float Value) = 0 ;
	virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl bearing(float f) = 0 ;
	virtual _di_JStreetViewPanoramaOrientation __cdecl build() = 0 ;
	virtual _di_JStreetViewPanoramaOrientation_Builder __cdecl tilt(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewPanoramaOrientation_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientation_BuilderClass,_di_JStreetViewPanoramaOrientation_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientation_BuilderClass,_di_JStreetViewPanoramaOrientation_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewPanoramaOrientation_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewPanoramaOrientation_BuilderClass,_di_JStreetViewPanoramaOrientation_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewPanoramaOrientation_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EC8A0F2C-0AC2-4D2E-B9E4-3973B5587E96}") JStreetViewSourceClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JStreetViewSource __cdecl _GetDEFAULT() = 0 ;
	virtual _di_JStreetViewSource __cdecl _GetOUTDOOR() = 0 ;
	HIDESBASE virtual _di_JStreetViewSource __cdecl init(int i) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property _di_JStreetViewSource DEFAULT = {read=_GetDEFAULT};
	__property _di_JStreetViewSource OUTDOOR = {read=_GetOUTDOOR};
};

__interface  INTERFACE_UUID("{5DAFC726-1A79-46C9-BF97-C133F7044A9E}") JStreetViewSource  : public JAbstractSafeParcelable 
{
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStreetViewSource : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewSourceClass,_di_JStreetViewSource>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewSourceClass,_di_JStreetViewSource> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStreetViewSource() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStreetViewSourceClass,_di_JStreetViewSource>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStreetViewSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{83027546-0EC6-4279-8EE9-9C7D5916EF94}") JTileClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JTile __cdecl init(int i, int i1, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* b) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{B5DD3D4F-FD9D-431B-BD30-919E328BE40C}") JTile  : public JAbstractSafeParcelable 
{
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _Getdata() = 0 ;
	virtual int __cdecl _Getheight() = 0 ;
	virtual int __cdecl _Getwidth() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data = {read=_Getdata};
	__property int height = {read=_Getheight};
	__property int width = {read=_Getwidth};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTile : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileClass,_di_JTile>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileClass,_di_JTile> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTile() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileClass,_di_JTile>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTile() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{048A54CE-D00A-4604-A37D-AD23D52380E8}") JTileOverlayClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{46B2D846-DF98-4A3A-9141-280BBB683586}") JTileOverlay  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl clearTileCache() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual bool __cdecl getFadeIn() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual float __cdecl getTransparency() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl remove() = 0 ;
	virtual void __cdecl setFadeIn(bool b) = 0 ;
	virtual void __cdecl setTransparency(float f) = 0 ;
	virtual void __cdecl setVisible(bool b) = 0 ;
	virtual void __cdecl setZIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTileOverlay : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayClass,_di_JTileOverlay>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayClass,_di_JTileOverlay> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTileOverlay() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayClass,_di_JTileOverlay>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTileOverlay() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C3818656-1176-498F-A0E8-106091DEAE4B}") JTileOverlayOptionsClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JTileOverlayOptions __cdecl init() = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{514FFD3B-E0C2-4AD5-89EE-3EB07D1D03AF}") JTileOverlayOptions  : public JAbstractSafeParcelable 
{
	virtual _di_JTileOverlayOptions __cdecl fadeIn(bool b) = 0 ;
	virtual bool __cdecl getFadeIn() = 0 ;
	virtual _di_JTileProvider __cdecl getTileProvider() = 0 ;
	virtual float __cdecl getTransparency() = 0 ;
	virtual float __cdecl getZIndex() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual _di_JTileOverlayOptions __cdecl tileProvider(_di_JTileProvider tileProvider) = 0 ;
	virtual _di_JTileOverlayOptions __cdecl transparency(float f) = 0 ;
	virtual _di_JTileOverlayOptions __cdecl visible(bool b) = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	virtual _di_JTileOverlayOptions __cdecl zIndex(float f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTileOverlayOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayOptionsClass,_di_JTileOverlayOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayOptionsClass,_di_JTileOverlayOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTileOverlayOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileOverlayOptionsClass,_di_JTileOverlayOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTileOverlayOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D6128829-67DB-49E4-AB8A-D4ED01E19A11}") JTileProviderClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual _di_JTile __cdecl _GetNO_TILE() = 0 ;
	__property _di_JTile NO_TILE = {read=_GetNO_TILE};
};

__interface  INTERFACE_UUID("{C1D85B3E-623F-4F8C-8CAA-8BFBFC944C61}") JTileProvider  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JTile __cdecl getTile(int i, int i1, int i2) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTileProvider : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileProviderClass,_di_JTileProvider>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileProviderClass,_di_JTileProvider> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTileProvider() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTileProviderClass,_di_JTileProvider>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTileProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{34E3DD57-5F4F-4236-99BA-3341D5560F82}") JUrlTileProviderClass  : public JTileProviderClass 
{
	virtual _di_JUrlTileProvider __cdecl init(int i, int i1) = 0 ;
};

__interface  INTERFACE_UUID("{34F7AB9C-B88F-46BB-BFD6-8EC61EB9E58B}") JUrlTileProvider  : public JTileProvider 
{
	HIDESBASE virtual _di_JTile __cdecl getTile(int i, int i1, int i2) = 0 ;
	virtual Androidapi::Jni::Java::Net::_di_JURL __cdecl getTileUrl(int i, int i1, int i2) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJUrlTileProvider : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUrlTileProviderClass,_di_JUrlTileProvider>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUrlTileProviderClass,_di_JUrlTileProvider> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJUrlTileProvider() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUrlTileProviderClass,_di_JUrlTileProvider>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJUrlTileProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C83C8AE5-7C11-407C-A342-3DE928A8E39B}") JVisibleRegionClass  : public JAbstractSafeParcelableClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JVisibleRegion __cdecl init(_di_JLatLng latLng, _di_JLatLng latLng1, _di_JLatLng latLng2, _di_JLatLng latLng3, _di_JLatLngBounds latLngBounds) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{669FB7E8-207E-4C0A-8882-F056813AB68C}") JVisibleRegion  : public JAbstractSafeParcelable 
{
	virtual _di_JLatLng __cdecl _GetfarLeft() = 0 ;
	virtual _di_JLatLng __cdecl _GetfarRight() = 0 ;
	virtual _di_JLatLngBounds __cdecl _GetlatLngBounds() = 0 ;
	virtual _di_JLatLng __cdecl _GetnearLeft() = 0 ;
	virtual _di_JLatLng __cdecl _GetnearRight() = 0 ;
	virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual int __cdecl hashCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int i) = 0 ;
	__property _di_JLatLng farLeft = {read=_GetfarLeft};
	__property _di_JLatLng farRight = {read=_GetfarRight};
	__property _di_JLatLngBounds latLngBounds = {read=_GetlatLngBounds};
	__property _di_JLatLng nearLeft = {read=_GetnearLeft};
	__property _di_JLatLng nearRight = {read=_GetnearRight};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisibleRegion : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibleRegionClass,_di_JVisibleRegion>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibleRegionClass,_di_JVisibleRegion> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisibleRegion() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibleRegionClass,_di_JVisibleRegion>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisibleRegion() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Maps */
}	/* namespace Playservices */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_PLAYSERVICES_MAPS)
using namespace Androidapi::Jni::Playservices::Maps;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_PLAYSERVICES)
using namespace Androidapi::Jni::Playservices;
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
#endif	// Androidapi_Jni_Playservices_MapsHPP
