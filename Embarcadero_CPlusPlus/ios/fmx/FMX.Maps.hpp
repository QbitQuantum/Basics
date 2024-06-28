// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Maps.pas' rev: 34.00 (iOS)

#ifndef Fmx_MapsHPP
#define Fmx_MapsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Maps
{
//-- forward type declarations -----------------------------------------------
struct TMapEpsilon;
struct TMapCoordinate;
struct TMapMarkerDescriptor;
struct TMapCircleDescriptor;
struct TMapPolygonPolyvertex;
struct TMapPolygonDescriptor;
struct TMapPolylineDescriptor;
class DELPHICLASS TMapObjectBase;
template<typename D> class DELPHICLASS TMapObject__1;
class DELPHICLASS TMapMarker;
class DELPHICLASS TMapCircle;
class DELPHICLASS TMapPolygon;
class DELPHICLASS TMapPolyline;
__interface DELPHIINTERFACE ICustomMapView;
typedef System::DelphiInterface<ICustomMapView> _di_ICustomMapView;
__interface DELPHIINTERFACE IFMXMapService;
typedef System::DelphiInterface<IFMXMapService> _di_IFMXMapService;
class DELPHICLASS TCustomMapView;
class DELPHICLASS TMapView;
class DELPHICLASS TMapViewBase;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TMapEpsilon
{
public:
	#define TMapEpsilon_Coordinate  (1.000000E-06)
	
	#define TMapEpsilon_Bearing  (1.000000E-03)
	
	#define TMapEpsilon_Tilt  (1.000000E-02)
	
	#define TMapEpsilon_Zoom  (1.000000E-01)
	
	static constexpr System::Int8 Rotate = System::Int8(0x1);
	
};


enum class DECLSPEC_DENUM TMapType : unsigned char { None, Normal, Satellite, Hybrid, Terrain };

enum class DECLSPEC_DENUM TMapGestureOption : unsigned char { Zoom, Tilt, Scroll, Rotate };

typedef System::Set<TMapGestureOption, _DELPHI_SET_ENUMERATOR(TMapGestureOption::Zoom), _DELPHI_SET_ENUMERATOR(TMapGestureOption::Rotate)> TMapGestureOptions;

enum class DECLSPEC_DENUM TMapControlOption : unsigned char { Zoom, Compass, MyLocation };

typedef System::Set<TMapControlOption, _DELPHI_SET_ENUMERATOR(TMapControlOption::Zoom), _DELPHI_SET_ENUMERATOR(TMapControlOption::MyLocation)> TMapControlOptions;

enum class DECLSPEC_DENUM TMapLayerOption : unsigned char { PointsOfInterest, Buildings, UserLocation, Traffic };

typedef System::Set<TMapLayerOption, _DELPHI_SET_ENUMERATOR(TMapLayerOption::PointsOfInterest), _DELPHI_SET_ENUMERATOR(TMapLayerOption::Traffic)> TMapLayerOptions;

enum class DECLSPEC_DENUM TMapOptionSet : unsigned char { Gesture, Control, Layer };

typedef System::Set<TMapOptionSet, _DELPHI_SET_ENUMERATOR(TMapOptionSet::Gesture), _DELPHI_SET_ENUMERATOR(TMapOptionSet::Layer)> TMapOptionSets;

enum class DECLSPEC_DENUM TMarkerAppearance : unsigned char { Flat, Billboard };

struct DECLSPEC_DRECORD TMapCoordinate
{
public:
	double Latitude;
	double Longitude;
	static TMapCoordinate __fastcall Create(const double Latitude, const double Longitude)/* overload */;
	static TMapCoordinate __fastcall Create(const System::Types::TPointF &Point)/* overload */;
	static TMapCoordinate __fastcall Zero();
	static bool __fastcall _op_Equality(const TMapCoordinate &ACoordinate1, const TMapCoordinate &ACoordinate2);
	static bool __fastcall _op_Inequality(const TMapCoordinate &ACoordinate1, const TMapCoordinate &ACoordinate2);
	System::UnicodeString __fastcall ToString();
	
	friend bool operator ==(const TMapCoordinate &ACoordinate1, const TMapCoordinate &ACoordinate2) { return TMapCoordinate::_op_Equality(ACoordinate1, ACoordinate2); }
	friend bool operator !=(const TMapCoordinate &ACoordinate1, const TMapCoordinate &ACoordinate2) { return TMapCoordinate::_op_Inequality(ACoordinate1, ACoordinate2); }
};


struct DECLSPEC_DRECORD TMapMarkerDescriptor
{
public:
	TMapCoordinate Position;
	float Opacity;
	System::Types::TPointF Origin;
	System::UnicodeString Title;
	System::UnicodeString Snippet;
	Fmx::Graphics::TBitmap* Icon;
	bool Draggable;
	bool Visible;
	TMarkerAppearance Appearance;
	float Rotation;
	static TMapMarkerDescriptor __fastcall Create(const TMapCoordinate &Position, const System::UnicodeString Title = u"Marker Title");
};


struct DECLSPEC_DRECORD TMapCircleDescriptor
{
public:
	TMapCoordinate Center;
	System::Uitypes::TAlphaColor FillColor;
	float Radius;
	float StrokeWidth;
	System::Uitypes::TAlphaColor StrokeColor;
	float ZIndex;
	static TMapCircleDescriptor __fastcall Create(const TMapCoordinate &Center, const float RadiusInMeters);
};


struct DECLSPEC_DRECORD TMapPolygonPolyvertex
{
public:
	System::TArray__1<TMapCoordinate> Points;
};


struct DECLSPEC_DRECORD TMapPolygonDescriptor
{
public:
	TMapPolygonPolyvertex Outline;
	System::TArray__1<TMapPolygonPolyvertex> Holes;
	bool Geodesic;
	System::Uitypes::TAlphaColor FillColor;
	System::Uitypes::TAlphaColor StrokeColor;
	float StrokeWidth;
	float ZIndex;
	static TMapPolygonDescriptor __fastcall Create(const System::TArray__1<TMapCoordinate> Outline);
	void __fastcall AddHole(const System::TArray__1<TMapCoordinate> Points);
};


struct DECLSPEC_DRECORD TMapPolylineDescriptor
{
public:
	TMapPolygonPolyvertex Points;
	bool Geodesic;
	System::Uitypes::TAlphaColor StrokeColor;
	float StrokeWidth;
	float ZIndex;
	static TMapPolylineDescriptor __fastcall Create(const System::TArray__1<TMapCoordinate> Points);
};


class PASCALIMPLEMENTATION TMapObjectBase : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Remove() = 0 ;
	virtual void __fastcall SetVisible(const bool Value) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TMapObjectBase() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMapObjectBase() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename D> class PASCALIMPLEMENTATION TMapObject__1 : public TMapObjectBase
{
	typedef TMapObjectBase inherited;
	
protected:
	D FDescriptor;
	__fastcall virtual TMapObject__1(const D Descriptor);
	
public:
	__property D Descriptor = {read=FDescriptor};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMapObject__1() { }
	
};


class PASCALIMPLEMENTATION TMapMarker : public TMapObject__1<TMapMarkerDescriptor>
{
	typedef TMapObject__1<TMapMarkerDescriptor> inherited;
	
protected:
	/* {FMX_Maps}TMapObject<FMX_Maps_TMapMarkerDescriptor>.Create */ inline __fastcall virtual TMapMarker(const TMapMarkerDescriptor &Descriptor) : TMapObject__1<TMapMarkerDescriptor>(Descriptor) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMapMarker() { }
	
};


class PASCALIMPLEMENTATION TMapCircle : public TMapObject__1<TMapCircleDescriptor>
{
	typedef TMapObject__1<TMapCircleDescriptor> inherited;
	
protected:
	/* {FMX_Maps}TMapObject<FMX_Maps_TMapCircleDescriptor>.Create */ inline __fastcall virtual TMapCircle(const TMapCircleDescriptor &Descriptor) : TMapObject__1<TMapCircleDescriptor>(Descriptor) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMapCircle() { }
	
};


class PASCALIMPLEMENTATION TMapPolygon : public TMapObject__1<TMapPolygonDescriptor>
{
	typedef TMapObject__1<TMapPolygonDescriptor> inherited;
	
protected:
	/* {FMX_Maps}TMapObject<FMX_Maps_TMapPolygonDescriptor>.Create */ inline __fastcall virtual TMapPolygon(const TMapPolygonDescriptor &Descriptor) : TMapObject__1<TMapPolygonDescriptor>(Descriptor) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMapPolygon() { }
	
};


class PASCALIMPLEMENTATION TMapPolyline : public TMapObject__1<TMapPolylineDescriptor>
{
	typedef TMapObject__1<TMapPolylineDescriptor> inherited;
	
protected:
	/* {FMX_Maps}TMapObject<FMX_Maps_TMapPolylineDescriptor>.Create */ inline __fastcall virtual TMapPolyline(const TMapPolylineDescriptor &Descriptor) : TMapObject__1<TMapPolylineDescriptor>(Descriptor) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMapPolyline() { }
	
};


typedef void __fastcall (__closure *TMarkerEvent)(TMapMarker* Marker);

typedef void __fastcall (__closure *TMapClickEvent)(const TMapCoordinate &Position);

typedef void __fastcall (__closure *TMapScreenshotRecipient)(Fmx::Graphics::TBitmap* const Bitmap);

__interface  INTERFACE_UUID("{FC5B1D02-AF69-400B-A734-03E6100FC0B9}") ICustomMapView  : public System::IInterface 
{
	virtual void __fastcall SetHostControl(TCustomMapView* const Host) = 0 ;
	virtual void __fastcall UpdateContentFromControl() = 0 ;
	virtual void __fastcall Show() = 0 ;
	virtual void __fastcall Hide() = 0 ;
	virtual void __fastcall SetLocation(const TMapCoordinate &ALocation) = 0 ;
	virtual TMapCoordinate __fastcall GetLocation() = 0 ;
	virtual void __fastcall SetZoom(const float Zoom) = 0 ;
	virtual float __fastcall GetZoom() = 0 ;
	virtual void __fastcall SetBearing(const float Bearing) = 0 ;
	virtual float __fastcall GetBearing() = 0 ;
	virtual void __fastcall SetTilt(const float Tilt) = 0 ;
	virtual float __fastcall GetTilt() = 0 ;
	virtual void __fastcall SetMapType(const TMapType AValue) = 0 ;
	virtual void __fastcall OptionsChanged(const TMapOptionSets OptionSets) = 0 ;
	virtual TMapMarker* __fastcall AddMarker(const TMapMarkerDescriptor &Descriptor) = 0 ;
	virtual TMapCircle* __fastcall AddCircle(const TMapCircleDescriptor &Descriptor) = 0 ;
	virtual TMapPolygon* __fastcall AddPolygon(const TMapPolygonDescriptor &Descriptor) = 0 ;
	virtual TMapPolyline* __fastcall AddPolyline(const TMapPolylineDescriptor &Descriptor) = 0 ;
	virtual Fmx::Graphics::TBitmap* __fastcall CaptureBitmap() = 0 ;
	virtual void __fastcall Snapshot(const TMapScreenshotRecipient Recipient) = 0 ;
};

__interface  INTERFACE_UUID("{8A1577FF-1C26-40F0-8358-390711E315EA}") IFMXMapService  : public System::IInterface 
{
	virtual _di_ICustomMapView __fastcall CreateMapView() = 0 ;
	virtual void __fastcall DestroyMapView(const _di_ICustomMapView MapView) = 0 ;
	virtual void __fastcall RealignMapViews() = 0 ;
};

class PASCALIMPLEMENTATION TCustomMapView : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
public:
	static TMapGestureOptions DefaultGestureOptions;
	static TMapControlOptions DefaultControlOptions;
	static TMapLayerOptions DefaultLayerOptions;
	
private:
	_di_ICustomMapView FMapView;
	bool FSavedVisible;
	TMapType FMapType;
	TMapGestureOptions FGestureOptions;
	TMapControlOptions FControlOptions;
	TMapLayerOptions FLayerOptions;
	System::Classes::TNotifyEvent FOnCameraChanged;
	TMarkerEvent FOnMarkerClick;
	TMarkerEvent FOnMarkerDoubleClick;
	TMarkerEvent FOnMarkerDragStart;
	TMarkerEvent FOnMarkerDrag;
	TMarkerEvent FOnMarkerDragEnd;
	TMapClickEvent FOnMapClick;
	TMapClickEvent FOnMapDoubleClick;
	TMapClickEvent FOnMapLongClick;
	void __fastcall AdjustToControl();
	
protected:
	void __fastcall SetLocation(const TMapCoordinate &ACoordinate);
	TMapCoordinate __fastcall GetLocation();
	void __fastcall SetZoom(const float Value);
	float __fastcall GetZoom();
	void __fastcall SetTilt(const float Degrees);
	float __fastcall GetTilt();
	void __fastcall SetBearing(const float Bearing);
	float __fastcall GetBearing();
	void __fastcall SetMapType(const TMapType AValue);
	TMapType __fastcall GetMapType();
	void __fastcall SetGestureOptions(const TMapGestureOptions Options);
	TMapGestureOptions __fastcall GetGestureOptions();
	bool __fastcall GestureOptionsStored();
	void __fastcall SetControlOptions(const TMapControlOptions Options);
	TMapControlOptions __fastcall GetControlOptions();
	bool __fastcall ControlOptionsStored();
	void __fastcall SetLayerOptions(const TMapLayerOptions Options);
	TMapLayerOptions __fastcall GetLayerOptions();
	bool __fastcall LayerOptionsStored();
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall ParentChanged();
	virtual void __fastcall Paint();
	virtual void __fastcall ChangeOrder();
	virtual void __fastcall AncestorVisibleChanged(const bool Visible);
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	
public:
	__fastcall virtual TCustomMapView(System::Classes::TComponent* Owner);
	__fastcall virtual ~TCustomMapView();
	virtual void __fastcall Move();
	virtual void __fastcall Show();
	virtual void __fastcall Hide();
	virtual void __fastcall Resize();
	void __fastcall Snapshot(const TMapScreenshotRecipient Recipient);
	TMapMarker* __fastcall AddMarker(const TMapMarkerDescriptor &Descriptor);
	TMapCircle* __fastcall AddCircle(const TMapCircleDescriptor &Descriptor);
	TMapPolygon* __fastcall AddPolygon(const TMapPolygonDescriptor &Descriptor);
	TMapPolyline* __fastcall AddPolyline(const TMapPolylineDescriptor &Descriptor);
	__property TMapCoordinate Location = {read=GetLocation, write=SetLocation};
	__property float Zoom = {read=GetZoom, write=SetZoom};
	__property float Tilt = {read=GetTilt, write=SetTilt};
	__property float Bearing = {read=GetBearing, write=SetBearing};
	__property TMapType MapType = {read=GetMapType, write=SetMapType, default=1};
	__property TMapGestureOptions GestureOptions = {read=GetGestureOptions, write=SetGestureOptions, stored=GestureOptionsStored, nodefault};
	__property TMapControlOptions ControlOptions = {read=GetControlOptions, write=SetControlOptions, stored=ControlOptionsStored, nodefault};
	__property TMapLayerOptions LayerOptions = {read=GetLayerOptions, write=SetLayerOptions, stored=LayerOptionsStored, nodefault};
	void __fastcall DoCameraChanged();
	void __fastcall DoMarkerClick(TMapMarker* const Marker);
	void __fastcall DoMarkerDoubleClick(TMapMarker* const Marker);
	void __fastcall DoMarkerDragStart(TMapMarker* const Marker);
	void __fastcall DoMarkerDrag(TMapMarker* const Marker);
	void __fastcall DoMarkerDragEnd(TMapMarker* const Marker);
	void __fastcall DoMapClick(const TMapCoordinate &Coordinate);
	void __fastcall DoMapDoubleClick(const TMapCoordinate &Coordinate);
	void __fastcall DoMapLongClick(const TMapCoordinate &Coordinate);
	__property System::Classes::TNotifyEvent OnCameraChanged = {read=FOnCameraChanged, write=FOnCameraChanged};
	__property TMarkerEvent OnMarkerClick = {read=FOnMarkerClick, write=FOnMarkerClick};
	__property TMarkerEvent OnMarkerDoubleClick = {read=FOnMarkerDoubleClick, write=FOnMarkerDoubleClick};
	__property TMarkerEvent OnMarkerDragStart = {read=FOnMarkerDragStart, write=FOnMarkerDragStart};
	__property TMarkerEvent OnMarkerDrag = {read=FOnMarkerDrag, write=FOnMarkerDrag};
	__property TMarkerEvent OnMarkerDragEnd = {read=FOnMarkerDragEnd, write=FOnMarkerDragEnd};
	__property TMapClickEvent OnMapClick = {read=FOnMapClick, write=FOnMapClick};
	__property TMapClickEvent OnMapDoubleClick = {read=FOnMapDoubleClick, write=FOnMapDoubleClick};
	__property TMapClickEvent OnMapLongClick = {read=FOnMapLongClick, write=FOnMapLongClick};
};


class PASCALIMPLEMENTATION TMapView : public TCustomMapView
{
	typedef TCustomMapView inherited;
	
__published:
	__property Anchors;
	__property Align = {default=0};
	__property Visible = {default=1};
	__property Position;
	__property Margins;
	__property Size;
	__property Width;
	__property Height;
	
public:
	__property Location;
	
__published:
	__property Zoom = {default=0};
	__property Tilt = {default=0};
	__property Bearing = {default=0};
	__property MapType = {default=1};
	__property GestureOptions;
	__property ControlOptions;
	__property LayerOptions;
	__property OnCameraChanged;
	__property OnMarkerClick;
	__property OnMarkerDoubleClick;
	__property OnMarkerDragStart;
	__property OnMarkerDrag;
	__property OnMarkerDragEnd;
	__property OnMapClick;
	__property OnMapDoubleClick;
	__property OnMapLongClick;
public:
	/* TCustomMapView.Create */ inline __fastcall virtual TMapView(System::Classes::TComponent* Owner) : TCustomMapView(Owner) { }
	/* TCustomMapView.Destroy */ inline __fastcall virtual ~TMapView() { }
	
};


class PASCALIMPLEMENTATION TMapViewBase : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	__fastcall virtual ~TMapViewBase();
	virtual void __fastcall OptionsChanged(const TMapOptionSets OptionSets);
	virtual TMapMarker* __fastcall AddMarker(const TMapMarkerDescriptor &Descriptor);
	virtual TMapCircle* __fastcall AddCircle(const TMapCircleDescriptor &Descriptor);
	virtual TMapPolygon* __fastcall AddPolygon(const TMapPolygonDescriptor &Descriptor);
	virtual TMapPolyline* __fastcall AddPolyline(const TMapPolylineDescriptor &Descriptor);
	virtual Fmx::Graphics::TBitmap* __fastcall CaptureBitmap();
	virtual void __fastcall Snapshot(const TMapScreenshotRecipient Recipient);
public:
	/* TObject.Create */ inline __fastcall TMapViewBase() : System::TInterfacedObject() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Maps */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MAPS)
using namespace Fmx::Maps;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_MapsHPP
