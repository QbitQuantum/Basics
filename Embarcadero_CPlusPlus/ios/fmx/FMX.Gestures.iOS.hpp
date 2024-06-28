// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Gestures.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Gestures_IosHPP
#define Fmx_Gestures_IosHPP

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
#include <FMX.Gestures.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Gestures
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformGestureEngine;
class DELPHICLASS TIOSGestureEngine;
class DELPHICLASS TGestureRecognizer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformGestureEngine : public Fmx::Gestures::TGestureEngine
{
	typedef Fmx::Gestures::TGestureEngine inherited;
	
private:
	static Fmx::Gestures::TGestureEngineClass FDefaultEngineClass;
	// __classmethod void __fastcall Destroy@();
	// __classmethod void __fastcall Create@();
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


class PASCALIMPLEMENTATION TIOSGestureEngine : /*[[sealed]]*/ public TPlatformGestureEngine
{
	typedef TPlatformGestureEngine inherited;
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(const bool Value);
	virtual Fmx::Types::TCustomGestureEngine::TGestureEngineFlags __fastcall GetFlags();
	
public:
	__fastcall virtual TIOSGestureEngine(System::Classes::TComponent* const AControl);
public:
	/* TGestureEngine.Destroy */ inline __fastcall virtual ~TIOSGestureEngine() { }
	
};


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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Gestures */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES_IOS)
using namespace Fmx::Gestures::Ios;
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
#endif	// Fmx_Gestures_IosHPP
