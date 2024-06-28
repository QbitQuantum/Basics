// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.GLES.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Context_Gles_AndroidHPP
#define Fmx_Context_Gles_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Androidapi.Egl.hpp>
#include <Androidapi.Gles2.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Context.GLES.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Gles
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomAndroidContext;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomAndroidContext : public Fmx::Context::Gles::TCustomContextOpenGL
{
	typedef Fmx::Context::Gles::TCustomContextOpenGL inherited;
	
	
protected:
	typedef System::DynamicArray<int> TContextAttributes;
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TContextPair
	{
	public:
		void *Surface;
		void *Context;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	typedef System::Generics::Collections::TDictionary__2<NativeUInt,unsigned>* TFrameBuffers;
	
	typedef System::Generics::Collections::TDictionary__2<NativeUInt,System::Generics::Collections::TDictionary__2<NativeUInt,unsigned>*>* TThreadBuffers;
	
	
private:
	static constexpr System::Int8 AndroidMaxLightCount = System::Int8(0x1);
	
	static System::StaticArray<int, 3> ContextAttributes;
	static int SharedMultisamples;
	
protected:
	static void *FSharedConfig;
	static void *FSharedDisplay;
	static void *FSharedSurface;
	static void *FSharedContext;
	static bool FIsExtensionLoaded;
	static System::Generics::Collections::TDictionary__2<NativeUInt,TContextPair>* FThreadDictionary;
	static System::Generics::Collections::TDictionary__2<NativeUInt,System::Generics::Collections::TDictionary__2<NativeUInt,unsigned>*>* FThreadBuffers;
	static void __fastcall CreateThreadDictionary();
	static void __fastcall DestroyThreadDictionary();
	void *FSurface;
	void *FContext;
	__classmethod virtual void __fastcall CreateSharedContext();
	__classmethod virtual void __fastcall DestroySharedContext();
	__classmethod void * __fastcall CreateSharedConfig();
	__classmethod void __fastcall LoadExtensions();
	virtual Fmx::Types3d::TContext3D::TIndexBufferSupport __fastcall GetIndexBufferSupport();
	
public:
	__classmethod bool __fastcall ActivateSharedContext();
	__classmethod virtual bool __fastcall Valid();
	/* static */ __property void * SharedConfig = {read=FSharedConfig};
	/* static */ __property void * SharedDisplay = {read=FSharedDisplay};
	/* static */ __property void * SharedSurface = {read=FSharedSurface};
	/* static */ __property void * SharedContext = {read=FSharedContext};
	__classmethod virtual int __fastcall MaxLightCount();
	__classmethod virtual Fmx::Types3d::TContextStyles __fastcall Style();
protected:
	/* TCustomContextOpenGL.CreateFromTexture */ inline __fastcall virtual TCustomAndroidContext(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Context::Gles::TCustomContextOpenGL(ATexture, AMultisample, ADepthStencil) { }
	
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomAndroidContext(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Context::Gles::TCustomContextOpenGL(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomAndroidContext() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomAndroidContext() : Fmx::Context::Gles::TCustomContextOpenGL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterContextClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterContextClasses(void);
}	/* namespace Android */
}	/* namespace Gles */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_GLES_ANDROID)
using namespace Fmx::Context::Gles::Android;
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
#endif	// Fmx_Context_Gles_AndroidHPP
