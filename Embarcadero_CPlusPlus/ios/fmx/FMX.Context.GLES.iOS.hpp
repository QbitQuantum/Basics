// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.GLES.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Context_Gles_IosHPP
#define Fmx_Context_Gles_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.OpenGLES.hpp>
#include <iOSapi.GLKit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Filter.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Context.GLES.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Gles
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomContextIOS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomContextIOS : public Fmx::Context::Gles::TCustomContextOpenGL
{
	typedef Fmx::Context::Gles::TCustomContextOpenGL inherited;
	
private:
	static constexpr System::Int8 iOSMaxLightCount = System::Int8(0x4);
	
	
protected:
	static Iosapi::Opengles::_di_EAGLContext FSharedContext;
	static System::Generics::Collections::TDictionary__2<NativeUInt,Iosapi::Opengles::_di_EAGLContext>* FThreadDictionary;
	static Iosapi::Opengles::_di_EAGLContext __fastcall GetSharedContext();
	__classmethod virtual void __fastcall CreateSharedContext();
	__classmethod virtual void __fastcall DestroySharedContext();
	__classmethod void __fastcall CreateThreadDictionary();
	__classmethod void __fastcall DestroyThreadDictionary();
	
public:
	/* static */ __property Iosapi::Opengles::_di_EAGLContext SharedContext = {read=GetSharedContext};
	__classmethod virtual bool __fastcall Valid();
	__classmethod virtual int __fastcall MaxLightCount();
	__classmethod virtual Fmx::Types3d::TContextStyles __fastcall Style();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
protected:
	/* TCustomContextOpenGL.CreateFromTexture */ inline __fastcall virtual TCustomContextIOS(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Context::Gles::TCustomContextOpenGL(ATexture, AMultisample, ADepthStencil) { }
	
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomContextIOS(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Context::Gles::TCustomContextOpenGL(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomContextIOS() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomContextIOS() : Fmx::Context::Gles::TCustomContextOpenGL() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterContextClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterContextClasses(void);
}	/* namespace Ios */
}	/* namespace Gles */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_GLES_IOS)
using namespace Fmx::Context::Gles::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_GLES)
using namespace Fmx::Context::Gles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT)
using namespace Fmx::Context;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Context_Gles_IosHPP
