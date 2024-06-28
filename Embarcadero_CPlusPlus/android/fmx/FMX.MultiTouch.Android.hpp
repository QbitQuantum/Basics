// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiTouch.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Multitouch_AndroidHPP
#define Fmx_Multitouch_AndroidHPP

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
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiTouchManagerAndroid;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiTouchManagerAndroid : public Fmx::Multitouch::TMultiTouchManager
{
	typedef Fmx::Multitouch::TMultiTouchManager inherited;
	
protected:
	virtual void __fastcall TouchDown();
	virtual void __fastcall TouchUp();
	virtual void __fastcall TouchMove();
	virtual void __fastcall TouchCancel();
	
public:
	__fastcall virtual TMultiTouchManagerAndroid(System::Classes::TComponent* const AParent);
	__fastcall virtual ~TMultiTouchManagerAndroid();
	virtual void __fastcall HandleTouches(const Fmx::Types::TTouches ATouches, const Fmx::Types::TTouchAction Action, const Fmx::Types::_di_IControl Control);
	void __fastcall SetEnabledGestures(const Fmx::Types::TInteractiveGestures AEnabledInteractiveGestures);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Multitouch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTITOUCH_ANDROID)
using namespace Fmx::Multitouch::Android;
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
#endif	// Fmx_Multitouch_AndroidHPP
