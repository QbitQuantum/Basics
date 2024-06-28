// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Helpers.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Helpers_AndroidHPP
#define Fmx_Helpers_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.Helpers.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Helpers
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE TCallBack;
typedef System::DelphiInterface<TCallBack> _di_TCallBack;
class DELPHICLASS TRunnable;
class DELPHICLASS TUIThreadCaller;
template<typename R> class DELPHICLASS _TUIThreadCaller_Call_10__ActRec__1;
template<typename R> class DELPHICLASS _TUIThreadCaller_Call_0__ActRec__1;
template<typename A, typename R> class DELPHICLASS _TUIThreadCaller_Call_1__ActRec__2;
template<typename A, typename B> class DELPHICLASS _TUIThreadCaller_Call_8__ActRec__2;
template<typename A, typename R> class DELPHICLASS _TUIThreadCaller_Call_2__ActRec__2;
template<typename A, typename B, typename R> class DELPHICLASS _TUIThreadCaller_Call_3__ActRec__3;
template<typename A, typename B, typename R> class DELPHICLASS _TUIThreadCaller_Call_4__ActRec__3;
template<typename A> class DELPHICLASS _TUIThreadCaller_Call_5__ActRec__1;
template<typename A> class DELPHICLASS _TUIThreadCaller_Call_6__ActRec__1;
template<typename A, typename B> class DELPHICLASS _TUIThreadCaller_Call_7__ActRec__2;
template<typename A, typename B, typename C> class DELPHICLASS _TUIThreadCaller_Call_9__ActRec__3;
template<typename A> class DELPHICLASS _TUIThreadCaller_InvokeIfNotNil_ActRec__1;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TMethodCallback)(void);

__interface TCallBack  : public System::IInterface 
{
	virtual void __fastcall Invoke() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRunnable : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	Androidapi::Jni::App::_di_JActivity FActivity;
	TMethodCallback FMethodCallback;
	_di_TCallBack FCallback;
	bool FFinished;
	
public:
	__fastcall TRunnable()/* overload */;
	__fastcall TRunnable(_di_TCallBack ACallback)/* overload */;
	__fastcall TRunnable(TMethodCallback AMethodCallback)/* overload */;
	void __fastcall Start();
	void __cdecl run();
	__property bool Finished = {read=FFinished, nodefault};
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TRunnable() { }
	
private:
	void *__JRunnable;	// Androidapi::Jni::Javatypes::JRunnable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BC131B27-7A72-4CAF-BB8E-170B8359B22E}
	operator Androidapi::Jni::Javatypes::_di_JRunnable()
	{
		Androidapi::Jni::Javatypes::_di_JRunnable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Javatypes::JRunnable*(void) { return (Androidapi::Jni::Javatypes::JRunnable*)&__JRunnable; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TUIThreadCaller : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (__closure *TMethodProc)();
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename R> using TMethodFunc__1 = R __fastcall (__closure *)();
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename A, typename R> using TMethodFunc__2 = R __fastcall (__closure *)(A Arg);
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename A, typename B, typename R> using TMethodFunc__3 = R __fastcall (__closure *)(A Arg, B Arg2);
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename A> using TMethodProc__1 = void __fastcall (__closure *)(A Arg);
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename A, typename B> using TMethodProc2__2 = void __fastcall (__closure *)(A Arg1, B Arg2);
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	template<typename A, typename B, typename C> using TMethodProc3__3 = void __fastcall (__closure *)(A Arg1, B Arg2, C Arg3);
	#endif
	
	
public:
	template<typename R> __classmethod R __fastcall Call(System::DelphiInterface<System::Sysutils::TFunc__1<R> > Func)/* overload */;
	template<typename R> __classmethod R __fastcall Call(TMethodFunc__1<R> Func)/* overload */;
	template<typename A, typename R> __classmethod R __fastcall Call(System::DelphiInterface<System::Sysutils::TFunc__2<A,R> > Func, const A Arg)/* overload */;
	template<typename A, typename R> __classmethod R __fastcall Call(TMethodFunc__2<A,R> Func, const A Arg)/* overload */;
	template<typename A, typename B, typename R> __classmethod R __fastcall Call(System::DelphiInterface<System::Sysutils::TFunc__3<A,B,R> > Func, const A Arg1, const B Arg2)/* overload */;
	template<typename A, typename B, typename R> __classmethod R __fastcall Call(TMethodFunc__3<A,B,R> Func, const A Arg1, const B Arg2)/* overload */;
	template<typename A> __classmethod void __fastcall Call(System::DelphiInterface<System::Sysutils::TProc__1<A> > Proc, A Arg)/* overload */;
	template<typename A> __classmethod void __fastcall Call(TMethodProc__1<A> Proc, A Arg)/* overload */;
	template<typename A, typename B> __classmethod void __fastcall Call(TMethodProc2__2<A,B> Proc, A Arg1, B Arg2)/* overload */;
	template<typename A, typename B> __classmethod void __fastcall Call(System::DelphiInterface<System::Sysutils::TProc__2<A,B> > Proc, A Arg1, B Arg2)/* overload */;
	template<typename A, typename B, typename C> __classmethod void __fastcall Call(TMethodProc3__3<A,B,C> Proc, A Arg1, B Arg2, C Arg3)/* overload */;
	template<typename A> __classmethod void __fastcall InvokeIfNotNil(const System::DelphiInterface<System::Sysutils::TProc__1<A> > Proc, const A Arg);
	template<typename A, typename R> __classmethod R __fastcall CallIfNotNil(System::DelphiInterface<System::Sysutils::TFunc__2<A,R> > Func, const A Arg);
	__classmethod void __fastcall CallWithAsyncCallback(_di_TCallBack UIThreadProc, _di_TCallBack SyncProc);
	__classmethod void __fastcall ForceRunnablesCollection();
public:
	/* TObject.Create */ inline __fastcall TUIThreadCaller() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUIThreadCaller() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 UserRequestCodeBase = System::Int8(0xa);
extern DELPHI_PACKAGE int __fastcall GetNativeTheme(void)/* overload */;
extern DELPHI_PACKAGE int __fastcall GetNativeTheme(Fmx::Controls::TControl* const AControl)/* overload */;
extern DELPHI_PACKAGE bool __fastcall JBitmapToSurface(const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap SrcBitmap, Fmx::Surfaces::TBitmapSurface* const DestSurface);
extern DELPHI_PACKAGE bool __fastcall SurfaceToJBitmap(Fmx::Surfaces::TBitmapSurface* const SrcSurface, const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap DestBitmap);
extern DELPHI_PACKAGE bool __fastcall NativeViewToSurface(const Androidapi::Jni::Graphicscontentviewtext::_di_JView ANativeView, Fmx::Surfaces::TBitmapSurface* const ASurface);
extern DELPHI_PACKAGE void __fastcall CallInUIThread(TMethodCallback AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThread(_di_TCallBack AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThreadAndWaitFinishing(TMethodCallback AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThreadAndWaitFinishing(_di_TCallBack AMethod)/* overload */;
extern DELPHI_PACKAGE Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __fastcall CreateJavaStringArray(const System::TVarRec *ASource, const int ASource_High);
}	/* namespace Android */
}	/* namespace Helpers */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS_ANDROID)
using namespace Fmx::Helpers::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS)
using namespace Fmx::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Helpers_AndroidHPP
