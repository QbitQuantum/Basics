// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Platform_IosHPP
#define Fmx_Platform_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.MetalKit.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.GLKit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ZOrder.iOS.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TiOSWindowHandle;
class DELPHICLASS TiOSOpenApplicationContext;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TiOSWindowHandle : public Fmx::Types::TWindowHandle
{
	typedef Fmx::Types::TWindowHandle inherited;
	
private:
	Macapi::Objectivec::TOCLocal* FHandle;
	Fmx::Zorder::Ios::TiOSZOrderManager* FZOrderManager;
	Fmx::Zorder::Ios::TiOSZOrderManager* __fastcall GetZOrderManager();
	
protected:
	virtual Iosapi::Uikit::_di_UIView __fastcall GetView();
	virtual Iosapi::Glkit::_di_GLKView __fastcall GetGLView();
	virtual Macapi::Metalkit::_di_MTKView __fastcall GetMTView();
	virtual Fmx::Forms::TCommonCustomForm* __fastcall GetForm();
	virtual Iosapi::Uikit::_di_UIWindow __fastcall GetWnd();
	virtual float __fastcall GetScale();
	
public:
	__fastcall TiOSWindowHandle(Macapi::Objectivec::TOCLocal* const AHandle);
	__fastcall virtual ~TiOSWindowHandle();
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property Iosapi::Uikit::_di_UIWindow Wnd = {read=GetWnd};
	__property Iosapi::Glkit::_di_GLKView GLView = {read=GetGLView};
	__property Macapi::Metalkit::_di_MTKView MTView = {read=GetMTView};
	__property Fmx::Forms::TCommonCustomForm* Form = {read=GetForm};
	__property Macapi::Objectivec::TOCLocal* Handle = {read=FHandle};
	__property Fmx::Zorder::Ios::TiOSZOrderManager* ZOrderManager = {read=GetZOrderManager};
};


class PASCALIMPLEMENTATION TiOSOpenApplicationContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FSourceApp;
	System::UnicodeString FURL;
	void *FContext;
	
public:
	__fastcall TiOSOpenApplicationContext(System::UnicodeString ASourceApp, System::UnicodeString AURL, void * AContext);
	__property System::UnicodeString SourceApp = {read=FSourceApp};
	__property System::UnicodeString URL = {read=FURL};
	__property void * Context = {read=FContext};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TiOSOpenApplicationContext() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define FMXViewControllerFrameChanged u"FMXViewControllerFrameChanged"
extern DELPHI_PACKAGE void __fastcall RegisterCorePlatformServices(void);
extern DELPHI_PACKAGE TiOSWindowHandle* __fastcall WindowHandleToPlatform(Fmx::Types::TWindowHandle* const AHandle);
}	/* namespace Ios */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_IOS)
using namespace Fmx::Platform::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_IosHPP
