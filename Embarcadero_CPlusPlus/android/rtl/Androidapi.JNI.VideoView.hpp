// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.VideoView.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_VideoviewHPP
#define Androidapi_Jni_VideoviewHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Media.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Widget.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Videoview
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JMediaControllerClass;
typedef System::DelphiInterface<JMediaControllerClass> _di_JMediaControllerClass;
__interface DELPHIINTERFACE JMediaController;
typedef System::DelphiInterface<JMediaController> _di_JMediaController;
class DELPHICLASS TJMediaController;
__interface DELPHIINTERFACE JMediaController_MediaPlayerControlClass;
typedef System::DelphiInterface<JMediaController_MediaPlayerControlClass> _di_JMediaController_MediaPlayerControlClass;
__interface DELPHIINTERFACE JMediaController_MediaPlayerControl;
typedef System::DelphiInterface<JMediaController_MediaPlayerControl> _di_JMediaController_MediaPlayerControl;
class DELPHICLASS TJMediaController_MediaPlayerControl;
__interface DELPHIINTERFACE JVideoViewClass;
typedef System::DelphiInterface<JVideoViewClass> _di_JVideoViewClass;
__interface DELPHIINTERFACE JVideoView;
typedef System::DelphiInterface<JVideoView> _di_JVideoView;
class DELPHICLASS TJVideoView;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{DF006611-A831-4E6D-92EF-9D03B98C99E0}") JMediaControllerClass  : public Androidapi::Jni::Widget::JFrameLayoutClass 
{
	HIDESBASE virtual _di_JMediaController __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JMediaController __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, bool useFastForward) = 0 /* overload */;
	HIDESBASE virtual _di_JMediaController __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{18253CF1-90C2-43A0-A928-490468F4DD1A}") JMediaController  : public Androidapi::Jni::Widget::JFrameLayout 
{
	HIDESBASE virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual void __cdecl hide() = 0 ;
	virtual bool __cdecl isShowing() = 0 ;
	virtual void __cdecl onFinishInflate() = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual void __cdecl setAnchorView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	HIDESBASE virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setMediaPlayer(_di_JMediaController_MediaPlayerControl player) = 0 ;
	virtual void __cdecl setPrevNextListeners(Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnClickListener next, Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnClickListener prev) = 0 ;
	virtual void __cdecl show() = 0 /* overload */;
	virtual void __cdecl show(int timeout) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMediaController : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaControllerClass,_di_JMediaController>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaControllerClass,_di_JMediaController> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMediaController() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaControllerClass,_di_JMediaController>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMediaController() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{31BC739A-5B96-48E4-B4D9-7486683FA117}") JMediaController_MediaPlayerControlClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{57C4DECE-8BAC-4153-ACEB-919DF5FE6844}") JMediaController_MediaPlayerControl  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl canPause() = 0 ;
	virtual bool __cdecl canSeekBackward() = 0 ;
	virtual bool __cdecl canSeekForward() = 0 ;
	virtual int __cdecl getAudioSessionId() = 0 ;
	virtual int __cdecl getBufferPercentage() = 0 ;
	virtual int __cdecl getCurrentPosition() = 0 ;
	virtual int __cdecl getDuration() = 0 ;
	virtual bool __cdecl isPlaying() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl seekTo(int pos) = 0 ;
	virtual void __cdecl start() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMediaController_MediaPlayerControl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaController_MediaPlayerControlClass,_di_JMediaController_MediaPlayerControl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaController_MediaPlayerControlClass,_di_JMediaController_MediaPlayerControl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMediaController_MediaPlayerControl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMediaController_MediaPlayerControlClass,_di_JMediaController_MediaPlayerControl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMediaController_MediaPlayerControl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E393C1DD-943D-4190-B984-25FF211E020F}") JVideoViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceViewClass 
{
	HIDESBASE virtual _di_JVideoView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JVideoView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JVideoView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JVideoView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{03A73FEC-6252-431B-904E-67581CD109DF}") JVideoView  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceView 
{
	virtual void __cdecl addSubtitleSource(Androidapi::Jni::Javatypes::_di_JInputStream is_, Androidapi::Jni::Media::_di_JMediaFormat format) = 0 ;
	virtual bool __cdecl canPause() = 0 ;
	virtual bool __cdecl canSeekBackward() = 0 ;
	virtual bool __cdecl canSeekForward() = 0 ;
	HIDESBASE virtual void __cdecl draw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual int __cdecl getAudioSessionId() = 0 ;
	virtual int __cdecl getBufferPercentage() = 0 ;
	virtual int __cdecl getCurrentPosition() = 0 ;
	virtual int __cdecl getDuration() = 0 ;
	virtual bool __cdecl isPlaying() = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	HIDESBASE virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual int __cdecl resolveAdjustedSize(int desiredSize, int measureSpec) = 0 ;
	virtual void __cdecl resume() = 0 ;
	virtual void __cdecl seekTo(int msec) = 0 ;
	virtual void __cdecl setAudioAttributes(Androidapi::Jni::Media::_di_JAudioAttributes attributes) = 0 ;
	virtual void __cdecl setAudioFocusRequest(int focusGain) = 0 ;
	virtual void __cdecl setMediaController(_di_JMediaController controller) = 0 ;
	virtual void __cdecl setOnCompletionListener(Androidapi::Jni::Media::_di_JMediaPlayer_OnCompletionListener l) = 0 ;
	virtual void __cdecl setOnErrorListener(Androidapi::Jni::Media::_di_JMediaPlayer_OnErrorListener l) = 0 ;
	virtual void __cdecl setOnInfoListener(Androidapi::Jni::Media::_di_JMediaPlayer_OnInfoListener l) = 0 ;
	virtual void __cdecl setOnPreparedListener(Androidapi::Jni::Media::_di_JMediaPlayer_OnPreparedListener l) = 0 ;
	virtual void __cdecl setVideoPath(Androidapi::Jni::Javatypes::_di_JString path) = 0 ;
	virtual void __cdecl setVideoURI(Androidapi::Jni::Net::_di_Jnet_Uri uri) = 0 /* overload */;
	virtual void __cdecl setVideoURI(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JMap headers) = 0 /* overload */;
	virtual void __cdecl start() = 0 ;
	virtual void __cdecl stopPlayback() = 0 ;
	virtual void __cdecl suspend() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVideoView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVideoViewClass,_di_JVideoView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVideoViewClass,_di_JVideoView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVideoView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVideoViewClass,_di_JVideoView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVideoView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Videoview */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_VIDEOVIEW)
using namespace Androidapi::Jni::Videoview;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_VideoviewHPP
