// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiTouch.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Multitouch_IosHPP
#define Fmx_Multitouch_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <FMX.MultiTouch.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multitouch
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiTouchManagerIOS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMultiTouchManagerIOS : public Fmx::Multitouch::TMultiTouchManager
{
	typedef Fmx::Multitouch::TMultiTouchManager inherited;
	
protected:
	virtual void __fastcall TouchDown();
	virtual void __fastcall TouchUp();
	virtual void __fastcall TouchMove();
	virtual void __fastcall TouchCancel();
	virtual bool __fastcall SendCMGestureMessage(const Fmx::Types::TGestureEventInfo &AEventInfo);
	bool __fastcall CreateEventInfo(Fmx::Types::TGestureEventInfo &EventInfo, const Fmx::Types::TInteractiveGesture AGesture, const System::Types::TPointF &ALocation, const Fmx::Types::TInteractiveGestureFlags AState);
	
public:
	void __fastcall HandlePan(const System::Types::TPointF &Location, const int Distance, const Fmx::Types::TInteractiveGestureFlags State, const int TouchCount);
	void __fastcall HandleZoom(const System::Types::TPointF &Location, const int Distance, const Fmx::Types::TInteractiveGestureFlags State, const int TouchCount);
	void __fastcall HandleRotate(const System::Types::TPointF &Location, const double Angle, const Fmx::Types::TInteractiveGestureFlags State, const int TouchCount);
	void __fastcall HandleTwoFingerTap(const System::Types::TPointF &Location, const Fmx::Types::TInteractiveGestureFlags State, const int TouchCount);
public:
	/* TMultiTouchManager.Create */ inline __fastcall virtual TMultiTouchManagerIOS(System::Classes::TComponent* const AParent) : Fmx::Multitouch::TMultiTouchManager(AParent) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMultiTouchManagerIOS() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Multitouch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTITOUCH_IOS)
using namespace Fmx::Multitouch::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTITOUCH)
using namespace Fmx::Multitouch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Multitouch_IosHPP
