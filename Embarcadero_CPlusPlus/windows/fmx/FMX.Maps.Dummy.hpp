// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Maps.Dummy.pas' rev: 34.00 (Windows)

#ifndef Fmx_Maps_DummyHPP
#define Fmx_Maps_DummyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Maps.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Maps
{
namespace Dummy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDummyMapService;
class DELPHICLASS TDummyMapView;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDummyMapService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	Fmx::Maps::_di_ICustomMapView __fastcall CreateMapView();
	void __fastcall DestroyMapView(const Fmx::Maps::_di_ICustomMapView MapView);
	void __fastcall RealignMapViews();
public:
	/* TObject.Create */ inline __fastcall TDummyMapService() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDummyMapService() { }
	
private:
	void *__IFMXMapService;	// Fmx::Maps::IFMXMapService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8A1577FF-1C26-40F0-8358-390711E315EA}
	operator Fmx::Maps::_di_IFMXMapService()
	{
		Fmx::Maps::_di_IFMXMapService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Maps::IFMXMapService*(void) { return (Fmx::Maps::IFMXMapService*)&__IFMXMapService; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDummyMapView : public Fmx::Maps::TMapViewBase
{
	typedef Fmx::Maps::TMapViewBase inherited;
	
private:
	float FTilt;
	float FBearing;
	float FZoom;
	Fmx::Maps::TMapCoordinate FLocation;
	
public:
	__fastcall TDummyMapView();
	void __fastcall SetHostControl(Fmx::Maps::TCustomMapView* const Host);
	void __fastcall UpdateContentFromControl();
	void __fastcall DestroyView();
	void __fastcall UpdateNativeBounds();
	void __fastcall Hide();
	void __fastcall Show();
	void __fastcall SetLocation(const Fmx::Maps::TMapCoordinate &ACoordinate);
	Fmx::Maps::TMapCoordinate __fastcall GetLocation();
	void __fastcall SetZoom(const float Zoom);
	float __fastcall GetZoom();
	void __fastcall SetBearing(const float Bearing);
	float __fastcall GetBearing();
	void __fastcall SetTilt(const float Tilt);
	float __fastcall GetTilt();
	void __fastcall SetMapType(const Fmx::Maps::TMapType AValue);
public:
	/* TMapViewBase.Destroy */ inline __fastcall virtual ~TDummyMapView() { }
	
private:
	void *__ICustomMapView;	// Fmx::Maps::ICustomMapView 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FC5B1D02-AF69-400B-A734-03E6100FC0B9}
	operator Fmx::Maps::_di_ICustomMapView()
	{
		Fmx::Maps::_di_ICustomMapView intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Maps::ICustomMapView*(void) { return (Fmx::Maps::ICustomMapView*)&__ICustomMapView; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterMapService(void);
}	/* namespace Dummy */
}	/* namespace Maps */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MAPS_DUMMY)
using namespace Fmx::Maps::Dummy;
#endif
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
#endif	// Fmx_Maps_DummyHPP
