// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Media.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Media_AndroidHPP
#define Fmx_Media_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Messaging.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNI.Media.hpp>
#include <Androidapi.JNI.VideoView.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <FMX.Media.hpp>
#include <FMX.Platform.Android.hpp>
#include <FMX.ZOrder.Android.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Media
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidCaptureDeviceManager;
class DELPHICLASS TAndroidMedia;
class DELPHICLASS TAndroidMediaCodec;
class DELPHICLASS TAndroidVideo;
class DELPHICLASS TAndroidVideoCodec;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidCaptureDeviceManager : public Fmx::Media::TCaptureDeviceManager
{
	typedef Fmx::Media::TCaptureDeviceManager inherited;
	
public:
	__fastcall virtual TAndroidCaptureDeviceManager();
public:
	/* TCaptureDeviceManager.Destroy */ inline __fastcall virtual ~TAndroidCaptureDeviceManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidMedia : public Fmx::Media::TMedia
{
	typedef Fmx::Media::TMedia inherited;
	
private:
	Androidapi::Jni::Media::_di_JMediaPlayer FPlayer;
	float FVolume;
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	void __fastcall SeekToBegin();
	virtual Fmx::Media::TMediaTime __fastcall GetDuration();
	virtual Fmx::Media::TMediaTime __fastcall GetCurrent();
	virtual void __fastcall SetCurrent(const Fmx::Media::TMediaTime Value);
	virtual System::Types::TPointF __fastcall GetVideoSize();
	virtual Fmx::Media::TMediaState __fastcall GetMediaState();
	virtual float __fastcall GetVolume();
	virtual void __fastcall SetVolume(const float Value);
	virtual void __fastcall UpdateMediaFromControl();
	virtual void __fastcall DoPlay();
	virtual void __fastcall DoStop();
	
public:
	__fastcall virtual TAndroidMedia(const System::UnicodeString AFileName);
	__fastcall virtual ~TAndroidMedia();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidMediaCodec : public Fmx::Media::TCustomMediaCodec
{
	typedef Fmx::Media::TCustomMediaCodec inherited;
	
public:
	virtual Fmx::Media::TMedia* __fastcall CreateFromFile(const System::UnicodeString AFileName);
public:
	/* TObject.Create */ inline __fastcall TAndroidMediaCodec() : Fmx::Media::TCustomMediaCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidMediaCodec() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidVideo : public Fmx::Media::TMedia
{
	typedef Fmx::Media::TMedia inherited;
	
	
private:
	class DELPHICLASS TCommonVolume;
	class PASCALIMPLEMENTATION TCommonVolume : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		Androidapi::Jni::Javatypes::_di_JObject FAudioService;
		Androidapi::Jni::Media::_di_JAudioManager FAudioManager;
		int FMaxVolume;
		void __fastcall SetVolume(const float Value);
		float __fastcall GetVolume();
		
	public:
		__fastcall TCommonVolume();
		__property float Value = {read=GetVolume, write=SetVolume};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TCommonVolume() { }
		
	};
	
	
	
private:
	TCommonVolume* FVolume;
	float FScale;
	TAndroidMedia* FJustAudio;
	Androidapi::Jni::Videoview::_di_JVideoView FVideoPlayer;
	System::Types::TSize FVideoSize;
	bool FVideoEnabled;
	bool __fastcall AllAssigned();
	void __fastcall RealignView();
	void __fastcall RetreiveVideoSize();
	void __fastcall CheckVideo();
	HIDESBASE void __fastcall InitInstance();
	bool __fastcall InstanceCreated();
	bool __fastcall IsVideoEnabled();
	Fmx::Zorder::Android::TAndroidZOrderManager* __fastcall GetZOrderManager();
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	void __fastcall SeekToBegin();
	virtual Fmx::Media::TMediaTime __fastcall GetDuration();
	virtual Fmx::Media::TMediaTime __fastcall GetCurrent();
	virtual void __fastcall SetCurrent(const Fmx::Media::TMediaTime Value);
	virtual System::Types::TPointF __fastcall GetVideoSize();
	virtual Fmx::Media::TMediaState __fastcall GetMediaState();
	virtual float __fastcall GetVolume();
	virtual void __fastcall SetVolume(const float Value);
	virtual void __fastcall UpdateMediaFromControl();
	virtual void __fastcall DoPlay();
	virtual void __fastcall DoStop();
	
public:
	__fastcall virtual TAndroidVideo(const System::UnicodeString AFileName);
	__fastcall virtual ~TAndroidVideo();
	__property Fmx::Zorder::Android::TAndroidZOrderManager* ZOrderManager = {read=GetZOrderManager};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidVideoCodec : public Fmx::Media::TCustomMediaCodec
{
	typedef Fmx::Media::TCustomMediaCodec inherited;
	
public:
	virtual Fmx::Media::TMedia* __fastcall CreateFromFile(const System::UnicodeString AFileName);
public:
	/* TObject.Create */ inline __fastcall TAndroidVideoCodec() : Fmx::Media::TCustomMediaCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidVideoCodec() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word AndroidMediaTimeScale = System::Word(0x2710);
}	/* namespace Android */
}	/* namespace Media */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIA_ANDROID)
using namespace Fmx::Media::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIA)
using namespace Fmx::Media;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Media_AndroidHPP
