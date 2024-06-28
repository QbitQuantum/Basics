// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Gestures.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Gestures_AndroidHPP
#define Fmx_Gestures_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Gestures.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Gestures
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformGestureEngine;
class DELPHICLASS TAndroidGestureEngine;
class DELPHICLASS TGestureRecognizer;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPlatformGestureEngine : public Fmx::Gestures::TGestureEngine
{
	typedef Fmx::Gestures::TGestureEngine inherited;
	
private:
	static Fmx::Gestures::TGestureEngineClass FDefaultEngineClass;
	// __classmethod void __fastcall Destroy_();
	// __classmethod void __fastcall Create_();
	System::Classes::TComponent* FControl;
	System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* FGestureList;
	System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* __fastcall GetGestureList();
	
protected:
	__classmethod virtual Fmx::Gestures::TGestureEngine* __fastcall GetGestureEngine(System::Classes::TComponent* const AControl);
	virtual void __fastcall SetInitialPoint(const System::Types::TPointF &Value);
	
public:
	__classmethod void __fastcall CreateEngine(System::Classes::TComponent* const AControl);
	/* static */ __property Fmx::Gestures::TGestureEngineClass DefaultEngineClass = {read=FDefaultEngineClass, write=FDefaultEngineClass};
	__property System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* GestureList = {read=GetGestureList};
	__fastcall virtual TPlatformGestureEngine(System::Classes::TComponent* const AControl);
public:
	/* TGestureEngine.Destroy */ inline __fastcall virtual ~TPlatformGestureEngine() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidGestureEngine : /*[[sealed]]*/ public TPlatformGestureEngine
{
	typedef TPlatformGestureEngine inherited;
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(const bool Value);
	virtual Fmx::Types::TCustomGestureEngine::TGestureEngineFlags __fastcall GetFlags();
public:
	/* TPlatformGestureEngine.Create */ inline __fastcall virtual TAndroidGestureEngine(System::Classes::TComponent* const AControl) : TPlatformGestureEngine(AControl) { }
	
public:
	/* TGestureEngine.Destroy */ inline __fastcall virtual ~TAndroidGestureEngine() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGestureRecognizer : public Fmx::Gestures::TCustomGestureRecognizer
{
	typedef Fmx::Gestures::TCustomGestureRecognizer inherited;
	
public:
	virtual float __fastcall Match(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, const Fmx::Types::TGestureOptions Options, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin);
	virtual void __fastcall Reset();
public:
	/* TObject.Create */ inline __fastcall TGestureRecognizer() : Fmx::Gestures::TCustomGestureRecognizer() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGestureRecognizer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Gestures */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES_ANDROID)
using namespace Fmx::Gestures::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES)
using namespace Fmx::Gestures;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Gestures_AndroidHPP
