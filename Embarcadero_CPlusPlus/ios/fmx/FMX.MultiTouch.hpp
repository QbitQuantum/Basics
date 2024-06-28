// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiTouch.pas' rev: 34.00 (iOS)

#ifndef Fmx_MultitouchHPP
#define Fmx_MultitouchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multitouch
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiTouchManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMultiTouchManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TComponent* FParent;
	System::Classes::TComponent* FGestureControl;
	System::Classes::TComponent* FTouchDownControl;
	Fmx::Types::TTouches FTouches;
	
protected:
	System::Types::TPointF FFirstPointerDownCoordinates;
	System::Types::TPointF FFirstPointer;
	System::Types::TPointF FSecondPointer;
	System::Types::TPointF FOldPoint1;
	System::Types::TPointF FOldPoint2;
	Fmx::Types::TInteractiveGestures FActiveInteractiveGestures;
	Fmx::Types::TInteractiveGestures FEnabledInteractiveGestures;
	float FRotationAngle;
	virtual void __fastcall TouchDown() = 0 ;
	virtual void __fastcall TouchUp() = 0 ;
	virtual void __fastcall TouchMove() = 0 ;
	virtual void __fastcall TouchCancel() = 0 ;
	float __fastcall GetLongTapAllowedMovement();
	__property Fmx::Types::TTouches Touches = {read=FTouches, write=FTouches};
	__property System::Classes::TComponent* GestureControl = {read=FGestureControl, write=FGestureControl};
	__property System::Classes::TComponent* TouchDownControl = {read=FTouchDownControl, write=FTouchDownControl};
	bool __fastcall IsZoom(const System::Types::TPointF &APoint1, const System::Types::TPointF &APoint2);
	bool __fastcall IsRotate(const System::Types::TPointF &APoint1, const System::Types::TPointF &APoint2);
	virtual bool __fastcall SendCMGestureMessage(const Fmx::Types::TGestureEventInfo &AEventInfo);
	virtual Fmx::Types::TGestureEventInfo __fastcall CreateGestureEventInfo(const Fmx::Types::TInteractiveGesture AGesture, const bool AGestureEnded = false);
	bool __fastcall FindAndHandleInteractiveGesture(const Fmx::Types::TInteractiveGestures EffectiveGestureSet, const System::Types::TPointF &APoint, const bool AGestureStarted = false);
	bool __fastcall EndInteractiveGesture(Fmx::Types::TInteractiveGesture AGesture);
	
public:
	__fastcall virtual TMultiTouchManager(System::Classes::TComponent* const AParent);
	virtual void __fastcall HandleTouches(const Fmx::Types::TTouches ATouches, const Fmx::Types::TTouchAction Action, const Fmx::Types::_di_IControl Control);
	__property System::Classes::TComponent* Parent = {read=FParent, write=FParent};
	__property Fmx::Types::TInteractiveGestures ActiveInteractiveGestures = {read=FActiveInteractiveGestures, nodefault};
	__property Fmx::Types::TInteractiveGestures EnabledInteractiveGestures = {read=FEnabledInteractiveGestures, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMultiTouchManager() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Multitouch */
}	/* namespace Fmx */
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
#endif	// Fmx_MultitouchHPP
