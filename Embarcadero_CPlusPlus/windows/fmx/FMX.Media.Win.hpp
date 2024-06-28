// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Media.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Media_WinHPP
#define Fmx_Media_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Win.ComObj.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Math.hpp>
#include <System.Types.hpp>
#include <System.SyncObjs.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.DirectShow9.hpp>
#include <Winapi.Direct3D9.hpp>
#include <Winapi.ActiveX.hpp>
#include <FMX.Context.DX9.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Media.hpp>
#include <FMX.Platform.Win.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Media
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWindowsCaptureDeviceManager;
class DELPHICLASS TWindowsAudioCaptureDevice;
class DELPHICLASS TVMRRenderer;
class DELPHICLASS TWindowsVideoCaptureDevice;
class DELPHICLASS TWindowsMedia;
class DELPHICLASS TWaitMediaCompletionThread;
class DELPHICLASS TWindowsMediaCodec;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWindowsCaptureDeviceManager : public Fmx::Media::TCaptureDeviceManager
{
	typedef Fmx::Media::TCaptureDeviceManager inherited;
	
public:
	__fastcall virtual TWindowsCaptureDeviceManager();
	__fastcall virtual ~TWindowsCaptureDeviceManager();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TWindowsAudioCaptureDevice : public Fmx::Media::TAudioCaptureDevice
{
	typedef Fmx::Media::TAudioCaptureDevice inherited;
	
private:
	_di_IMoniker FMoniker;
	_di_IBaseFilter FBaseFilter;
	_di_IGraphBuilder FGraphBuilder;
	_di_ICaptureGraphBuilder2 FCaptureGraphBuilder;
	_di_IMediaControl FMediaControl;
	
protected:
	virtual void __fastcall DoStartCapture();
	virtual void __fastcall DoStopCapture();
	virtual System::UnicodeString __fastcall GetDeviceProperty(const Fmx::Media::TCaptureDevice::TProperty Prop);
	virtual Fmx::Media::TCaptureDeviceState __fastcall GetDeviceState();
	virtual System::UnicodeString __fastcall GetFilterString();
	
public:
	__fastcall TWindowsAudioCaptureDevice(Fmx::Media::TCaptureDeviceManager* AManager, const _di_IMoniker AMoniker, const bool ADefault);
	__fastcall virtual ~TWindowsAudioCaptureDevice();
};


class PASCALIMPLEMENTATION TVMRRenderer : public System::Classes::TInterfacedPersistent
{
	typedef System::Classes::TInterfacedPersistent inherited;
	
private:
	_di_IDirect3DTexture9 FVideoTexture;
	_di_IDirect3DSurface9 FSysMemSurface;
	_di_IDirect3DSurface9 FSurface;
	_di_IVMRSurfaceAllocatorNotify9 FSurfaceAllocatorNotify;
	_di_IBaseFilter FBaseFilter;
	_di_IVMRFilterConfig9 FVMRFilterConfig;
	Fmx::Media::TSampleBufferReadyEvent FSampleBufferReady;
	bool FRunning;
	bool FIsSkipFrames;
	System::Types::TPoint FRequestedBufferSize;
	Fmx::Media::TMediaTime FBufferLoadTime;
	bool FBufferLoaded;
	System::Syncobjs::TEvent* FIsFinishedProcessingEvent;
	HRESULT __stdcall InitializeDevice(unsigned dwUserID, Winapi::Directshow9::PVMR9AllocationInfo lpAllocInfo, unsigned &lpNumBuffers);
	HRESULT __stdcall TerminateDevice(unsigned dwID);
	HRESULT __stdcall GetSurface(unsigned dwUserID, unsigned SurfaceIndex, unsigned SurfaceFlags, /* out */ _di_IDirect3DSurface9 &lplpSurface);
	HRESULT __stdcall AdviseNotify(_di_IVMRSurfaceAllocatorNotify9 lpIVMRSurfAllocNotify);
	HRESULT __stdcall StartPresenting(unsigned dwUserID);
	HRESULT __stdcall StopPresenting(unsigned dwUserID);
	HRESULT __stdcall PresentImage(unsigned dwUserID, Winapi::Directshow9::PVMR9PresentationInfo lpPresInfo);
	bool __fastcall AddToGraph(const _di_IGraphBuilder FGraphBuilder);
	bool __fastcall LoadBufferToSystemMemory();
	void __fastcall SampleBufferToBitmap(Fmx::Graphics::TBitmap* const ABitmap, const bool ASetSize);
	void __fastcall Sync();
	
public:
	__fastcall TVMRRenderer();
	__fastcall virtual ~TVMRRenderer();
	void __fastcall SetSkipFrames();
private:
	void *__IVMRImagePresenter9;	// IVMRImagePresenter9 
	void *__IVMRSurfaceAllocator9;	// IVMRSurfaceAllocator9 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {69188C61-12A3-40F0-8FFC-342E7B433FD7}
	operator _di_IVMRImagePresenter9()
	{
		_di_IVMRImagePresenter9 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IVMRImagePresenter9*(void) { return (IVMRImagePresenter9*)&__IVMRImagePresenter9; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8D5148EA-3F5D-46CF-9DF1-D1B896EEDB1F}
	operator _di_IVMRSurfaceAllocator9()
	{
		_di_IVMRSurfaceAllocator9 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IVMRSurfaceAllocator9*(void) { return (IVMRSurfaceAllocator9*)&__IVMRSurfaceAllocator9; }
	#endif
	
};


class PASCALIMPLEMENTATION TWindowsVideoCaptureDevice : public Fmx::Media::TVideoCaptureDevice
{
	typedef Fmx::Media::TVideoCaptureDevice inherited;
	
private:
	static const int FrameDurationScale = int(0x989680);
	
	_di_IMoniker FMoniker;
	_di_IBaseFilter FBaseFilter;
	_di_IGraphBuilder FGraphBuilder;
	_di_ICaptureGraphBuilder2 FCaptureGraphBuilder;
	_di_IMediaControl FMediaControl;
	TVMRRenderer* FVMRRenderer;
	void __fastcall VMRRendererSampleReady(System::TObject* Sender, const Fmx::Media::TMediaTime ATime);
	
protected:
	virtual void __fastcall DoStartCapture();
	virtual void __fastcall DoStopCapture();
	virtual void __fastcall DoSampleBufferToBitmap(Fmx::Graphics::TBitmap* const ABitmap, const bool ASetSize);
	virtual System::UnicodeString __fastcall GetDeviceProperty(const Fmx::Media::TCaptureDevice::TProperty Prop);
	virtual Fmx::Media::TCaptureDeviceState __fastcall GetDeviceState();
	virtual Fmx::Media::TVideoCaptureSetting __fastcall GetCaptureSetting();
	virtual bool __fastcall DoSetCaptureSetting(const Fmx::Media::TVideoCaptureSetting &ASetting);
#ifndef _WIN64
	virtual System::DynamicArray<Fmx::Media::TVideoCaptureSetting> __fastcall DoGetAvailableCaptureSettings();
#else /* _WIN64 */
	virtual System::TArray__1<Fmx::Media::TVideoCaptureSetting> __fastcall DoGetAvailableCaptureSettings();
#endif /* _WIN64 */
	virtual void __fastcall DoSetQuality(const Fmx::Media::TVideoCaptureQuality Value);
	
public:
	__fastcall TWindowsVideoCaptureDevice(Fmx::Media::TCaptureDeviceManager* AManager, const _di_IMoniker AMoniker, const bool ADefault);
	__fastcall virtual ~TWindowsVideoCaptureDevice();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWindowsMedia : public Fmx::Media::TMedia
{
	typedef Fmx::Media::TMedia inherited;
	
private:
	_di_IGraphBuilder FGraphBuilder;
	_di_IMediaControl FMediaControl;
	_di_IMediaSeeking FMediaSeeking;
	_di_IBasicAudio FBasicAudio;
	_di_IBaseFilter FVMR;
	_di_IVMRFilterConfig9 FVMRFilterConfig9;
	_di_IVMRWindowlessControl9 FVMRWindowlessControl9;
	_di_IVMRFilterConfig FVMRFilterConfig7;
	_di_IVMRWindowlessControl FVMRWindowlessControl7;
	HWND FWnd;
	System::Classes::TThread* FWaitCompletionThread;
	Fmx::Media::TMediaState FMediaState;
	void __fastcall InitWnd();
	void __fastcall DestroyWnd();
	bool __fastcall InitMediaControl();
	bool __fastcall InitGraphTree();
	bool __fastcall InitVideoMixingRenderer9();
	bool __fastcall LocateVideoMixingRenderer9();
	bool __fastcall InitVideoMixingRenderer7();
	bool __fastcall LocateVideoMixingRenderer7();
	void __fastcall StartWaitCompletionThread();
	void __fastcall StopAndFreeWaitCompletionThread();
	void __fastcall WaitCompletionThreadTerminated(System::TObject* Sender);
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
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
	__fastcall virtual TWindowsMedia(const System::UnicodeString AFileName);
	__fastcall virtual ~TWindowsMedia();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TWaitMediaCompletionThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	_di_IMediaEvent FMediaEvent;
	
protected:
	virtual void __fastcall Execute();
	
public:
	__fastcall TWaitMediaCompletionThread(const _di_IMediaEvent AMediaEvent);
public:
	/* TThread.Destroy */ inline __fastcall virtual ~TWaitMediaCompletionThread() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWindowsMediaCodec : public Fmx::Media::TCustomMediaCodec
{
	typedef Fmx::Media::TCustomMediaCodec inherited;
	
public:
	virtual Fmx::Media::TMedia* __fastcall CreateFromFile(const System::UnicodeString AFileName);
public:
	/* TObject.Create */ inline __fastcall TWindowsMediaCodec() : Fmx::Media::TCustomMediaCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWindowsMediaCodec() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Media */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIA_WIN)
using namespace Fmx::Media::Win;
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
#endif	// Fmx_Media_WinHPP
