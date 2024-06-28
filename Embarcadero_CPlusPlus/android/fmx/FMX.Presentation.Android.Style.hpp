// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Android.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Presentation_Android_StyleHPP
#define Fmx_Presentation_Android_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Presentation.Android.hpp>
#include <FMX.Platform.Android.hpp>
#include <FMX.Platform.UI.Android.hpp>
#include <FMX.Presentation.Style.Common.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Android
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidNativeStyledControl;
class DELPHICLASS TAndroidNativeScene;
class DELPHICLASS TTextureView_SurfaceTextureListener;
class DELPHICLASS TAndroidStyledPresentation;
class DELPHICLASS TAndroidHandle;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidNativeStyledControl : public Fmx::Presentation::Style::Common::TNativeStyledControl
{
	typedef Fmx::Presentation::Style::Common::TNativeStyledControl inherited;
	
private:
	TAndroidNativeScene* __fastcall GetScene();
	
protected:
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall AdjustSize();
	__property TAndroidNativeScene* Scene = {read=GetScene};
public:
	/* TStyledControl.Create */ inline __fastcall virtual TAndroidNativeStyledControl(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Presentation::Style::Common::TNativeStyledControl(AOwner) { }
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TAndroidNativeStyledControl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidNativeScene : public Fmx::Presentation::Style::Common::TNativeScene
{
	typedef Fmx::Presentation::Style::Common::TNativeScene inherited;
	
private:
	Fmx::Graphics::TCanvas* FCanvas;
	TAndroidHandle* __fastcall GetHandle();
	TAndroidStyledPresentation* __fastcall GetPresentation();
	TAndroidNativeStyledControl* __fastcall GetStyledControl();
	
protected:
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R);
	virtual Fmx::Graphics::TCanvas* __fastcall DoGetCanvas();
	virtual float __fastcall DoGetSceneScale();
	virtual Fmx::Controls::TStyleBook* __fastcall DoGetStyleBook();
	virtual System::Types::TPointF __fastcall DoLocalToScreen(const System::Types::TPointF &P);
	virtual System::Types::TPointF __fastcall DoScreenToLocal(const System::Types::TPointF &P);
	virtual void __fastcall DoResized(const System::Types::TSizeF &NewSize);
	virtual Fmx::Controls::TControl* __fastcall GetPresentedControl();
	
public:
	__fastcall TAndroidNativeScene(TAndroidStyledPresentation* APresentation);
	__fastcall virtual ~TAndroidNativeScene();
	void __fastcall Paint();
	void __fastcall Invalidate();
	void __fastcall CreateCanvas(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture Surface, int Width, int Height);
	bool __fastcall DestroyCanvas(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture Surface);
	__property TAndroidStyledPresentation* Presentation = {read=GetPresentation};
	__property TAndroidHandle* Handle = {read=GetHandle};
	__property TAndroidNativeStyledControl* StyledControl = {read=GetStyledControl};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TTextureView_SurfaceTextureListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidNativeScene* FScene;
	
public:
	__fastcall TTextureView_SurfaceTextureListener(TAndroidNativeScene* const AScene);
	void __cdecl onSurfaceTextureAvailable(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture surface, int width, int height);
	bool __cdecl onSurfaceTextureDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture surface);
	void __cdecl onSurfaceTextureSizeChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture surface, int width, int height);
	void __cdecl onSurfaceTextureUpdated(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture surface);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TTextureView_SurfaceTextureListener() { }
	
private:
	void *__JTextureView_SurfaceTextureListener;	// Androidapi::Jni::Graphicscontentviewtext::JTextureView_SurfaceTextureListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1E496A42-F10C-4473-BDE1-43960E671F09}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JTextureView_SurfaceTextureListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JTextureView_SurfaceTextureListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JTextureView_SurfaceTextureListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JTextureView_SurfaceTextureListener*)&__JTextureView_SurfaceTextureListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TAndroidStyledPresentation : public Fmx::Presentation::Android::TAndroidNativeView
{
	typedef Fmx::Presentation::Android::TAndroidNativeView inherited;
	
private:
	TAndroidNativeScene* FNativeScene;
	TTextureView_SurfaceTextureListener* FListener;
	TAndroidNativeStyledControl* __fastcall GetStyledControl();
	void __fastcall ApplicationEventHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
protected:
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall CreateView();
	virtual void __fastcall SetSize(const System::Types::TSizeF &ASize);
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual System::UnicodeString __fastcall GetParentClassStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall DoApplyStyleLookup();
	
public:
	__fastcall virtual TAndroidStyledPresentation()/* overload */;
	__fastcall virtual ~TAndroidStyledPresentation();
	virtual void __fastcall Dispatch(void *Message);
	__property TAndroidNativeStyledControl* StyledControl = {read=GetStyledControl};
public:
	/* TAndroidNativeView.Create */ inline __fastcall TAndroidStyledPresentation(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Android::TAndroidNativeView(AModel, AControl) { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidHandle : public Fmx::Types::TWindowHandle
{
	typedef Fmx::Types::TWindowHandle inherited;
	
private:
	Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture FSurface;
	
protected:
	virtual float __fastcall GetScale();
	
public:
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture Surface = {read=FSurface, write=FSurface};
public:
	/* TObject.Create */ inline __fastcall TAndroidHandle() : Fmx::Types::TWindowHandle() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidHandle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Android */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_ANDROID_STYLE)
using namespace Fmx::Presentation::Android::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_ANDROID)
using namespace Fmx::Presentation::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION)
using namespace Fmx::Presentation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Presentation_Android_StyleHPP
