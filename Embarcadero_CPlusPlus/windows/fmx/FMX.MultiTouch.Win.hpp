// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiTouch.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Multitouch_WinHPP
#define Fmx_Multitouch_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <FMX.MultiTouch.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multitouch
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiTouchManagerWin;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMultiTouchManagerWin : public Fmx::Multitouch::TMultiTouchManager
{
	typedef Fmx::Multitouch::TMultiTouchManager inherited;
	
private:
	bool FDblTapFirstTouchUp;
	bool FPressAndTapPossible;
	bool FPressAndTapSecondTouchDown;
	NativeUInt FDoubleTapTimer;
	NativeUInt FLongTapTimer;
	Fmx::Types::_di_IFMXTimerService FTimerService;
	void __fastcall StandardGesturesDown(const System::Types::TPointF &APoint);
	void __fastcall StandardGesturesUp(const System::Types::TPointF &APoint);
	void __fastcall StandardGesturesMove(const System::Types::TPointF &APoint);
	void __fastcall StandardGesturesCancel();
	void __fastcall CreateDoubleTapTimer();
	void __fastcall DestroyDoubleTapTimer();
	void __fastcall DoubleTapTimerCall();
	void __fastcall CreateLongTapTimer();
	void __fastcall DestroyLongTapTimer();
	void __fastcall LongTapTimerCall();
	
protected:
	virtual void __fastcall TouchDown();
	virtual void __fastcall TouchUp();
	virtual void __fastcall TouchMove();
	virtual void __fastcall TouchCancel();
	
public:
	__fastcall virtual TMultiTouchManagerWin(System::Classes::TComponent* const AParent);
	__fastcall virtual ~TMultiTouchManagerWin();
	virtual void __fastcall HandleTouches(const Fmx::Types::TTouches ATouches, const Fmx::Types::TTouchAction Action, const Fmx::Types::_di_IControl Control);
	void __fastcall SetEnabledGestures(const Fmx::Types::TInteractiveGestures AEnabledInteractiveGestures);
	void __fastcall HandleMouseGestures(const System::Types::TPointF &APoint, const Fmx::Types::TTouchAction Action, const Fmx::Types::_di_IControl Control);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Multitouch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTITOUCH_WIN)
using namespace Fmx::Multitouch::Win;
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
#endif	// Fmx_Multitouch_WinHPP
