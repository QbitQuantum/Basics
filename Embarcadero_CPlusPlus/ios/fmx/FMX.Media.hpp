// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Media.pas' rev: 34.00 (iOS)

#ifndef Fmx_MediaHPP
#define Fmx_MediaHPP

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
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.StdActns.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(_WIN32) && !defined(_WIN64)
#pragma comment(lib, "urlmon")
#endif

namespace Fmx
{
namespace Media
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ECaptureDeviceException;
struct TMediaTimeHelper /* Helper for long '__int64' */;
class DELPHICLASS TCaptureDevice;
class DELPHICLASS TAudioCaptureDevice;
struct TDevicePositionHelper /* Helper for enum 'TDevicePosition' */;
struct TFlashModeHelper /* Helper for enum 'TFlashMode' */;
struct TFocusModeHelper /* Helper for enum 'TFocusMode' */;
struct TTorchModeHelper /* Helper for enum 'TTorchMode' */;
struct TVideoCaptureQualityHelper /* Helper for enum 'TVideoCaptureQuality' */;
struct TVideoCaptureSetting;
class DELPHICLASS TVideoCaptureDevice;
class DELPHICLASS TCaptureDeviceManager;
struct TCameraKindHelper /* Helper for enum 'TCameraKind' */;
class DELPHICLASS TCameraComponent;
class DELPHICLASS EMediaException;
class DELPHICLASS TMedia;
class DELPHICLASS TCustomMediaCodec;
class DELPHICLASS EMediaCodecManagerException;
class DELPHICLASS TMediaCodecManager;
class DELPHICLASS TMediaPlayer;
class DELPHICLASS TMediaPlayerControl;
class DELPHICLASS TCustomMediaPlayerAction;
class DELPHICLASS TMediaPlayerStart;
class DELPHICLASS TMediaPlayerStop;
class DELPHICLASS TMediaPlayerPlayPause;
class DELPHICLASS TMediaPlayerValue;
class DELPHICLASS TMediaPlayerCurrentTime;
class DELPHICLASS TMediaPlayerVolume;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION ECaptureDeviceException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECaptureDeviceException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECaptureDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECaptureDeviceException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECaptureDeviceException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECaptureDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECaptureDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECaptureDeviceException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECaptureDeviceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECaptureDeviceException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECaptureDeviceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECaptureDeviceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECaptureDeviceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECaptureDeviceException() { }
	
};


_DECLARE_ARITH_TYPE_ALIAS(__int64, TMediaTime);

enum class DECLSPEC_DENUM TMediaType : unsigned char { Audio, Video };

enum class DECLSPEC_DENUM TCaptureDeviceState : unsigned char { Capturing, Stopped };

typedef void __fastcall (__closure *TSampleBufferReadyEvent)(System::TObject* Sender, const TMediaTime ATime);

typedef void __fastcall (__closure *TPermissionRequestEvent)(System::TObject* ASender, const System::UnicodeString AMessage, const bool AAccessGranted);

class PASCALIMPLEMENTATION TCaptureDevice : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TProperty : unsigned char { UniqueID, Name, Description };
	
	
private:
	TCaptureDeviceManager* FManager;
	bool FDefault;
	TPermissionRequestEvent FOnPermissionRequest;
	
protected:
	void __fastcall DoPermissionRequest(const System::UnicodeString AMessage, const bool AAccessGranted);
	virtual void __fastcall DoRequestPermission();
	virtual TMediaType __fastcall GetMediaType() = 0 ;
	virtual System::UnicodeString __fastcall GetDeviceProperty(const TProperty Prop);
	virtual TCaptureDeviceState __fastcall GetDeviceState() = 0 ;
	virtual void __fastcall DoStartCapture() = 0 ;
	virtual void __fastcall DoStopCapture() = 0 ;
	
public:
	__fastcall virtual TCaptureDevice(TCaptureDeviceManager* const AManager, const bool ADefault);
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~TCaptureDevice();
	void __fastcall RequestPermission();
	void __fastcall StartCapture();
	void __fastcall StopCapture();
	__property System::UnicodeString Description = {read=GetDeviceProperty, index=2};
	__property bool IsDefault = {read=FDefault, nodefault};
	__property TMediaType MediaType = {read=GetMediaType, nodefault};
	__property System::UnicodeString Name = {read=GetDeviceProperty, index=1};
	__property TCaptureDeviceState State = {read=GetDeviceState, nodefault};
	__property System::UnicodeString UniqueID = {read=GetDeviceProperty, index=0};
	__property TPermissionRequestEvent OnPermissionRequest = {read=FOnPermissionRequest, write=FOnPermissionRequest};
};


_DECLARE_METACLASS(System::TMetaClass, TCaptureDeviceClass);

class PASCALIMPLEMENTATION TAudioCaptureDevice : public TCaptureDevice
{
	typedef TCaptureDevice inherited;
	
private:
	void __fastcall SetFileName(const System::UnicodeString Value);
	
protected:
	System::UnicodeString FFileName;
	virtual TMediaType __fastcall GetMediaType();
	virtual System::UnicodeString __fastcall GetFilterString();
	
public:
	__property System::UnicodeString FilterString = {read=GetFilterString};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
public:
	/* TCaptureDevice.Create */ inline __fastcall virtual TAudioCaptureDevice(TCaptureDeviceManager* const AManager, const bool ADefault) : TCaptureDevice(AManager, ADefault) { }
	/* TCaptureDevice.Destroy */ inline __fastcall virtual ~TAudioCaptureDevice() { }
	
};


enum class DECLSPEC_DENUM TDevicePosition : unsigned char { Unspecified, Front, Back, dpUnspecified _DEPRECATED_ATTRIBUTE3("Use TDevicePosition.Unspecified")  = 0x0, dpFront _DEPRECATED_ATTRIBUTE3("Use TDevicePosition.Front")  = 0x1, dpBack _DEPRECATED_ATTRIBUTE3("Use TDevicePosition.Back")  = 0x2 };

enum class DECLSPEC_DENUM TFlashMode : unsigned char { AutoFlash, FlashOff, FlashOn, fmAutoFlash _DEPRECATED_ATTRIBUTE3("Use TFlashMode.AutoFlash")  = 0x0, fmFlashOff _DEPRECATED_ATTRIBUTE3("Use TFlashMode.FlashOff")  = 0x1, fmFlashOn _DEPRECATED_ATTRIBUTE3("Use TFlashMode.FlashOn")  = 0x2 };

enum class DECLSPEC_DENUM TFocusMode : unsigned char { AutoFocus, ContinuousAutoFocus, Locked, fmAutoFocus _DEPRECATED_ATTRIBUTE3("Use TFocusMode.AutoFocus")  = 0x0, fmContinuousAutoFocus _DEPRECATED_ATTRIBUTE3("Use TFocusMode.ContinuousAutoFocus")  = 0x1, fmLocked _DEPRECATED_ATTRIBUTE3("Use TFocusMode.Locked")  = 0x2 };

enum class DECLSPEC_DENUM TTorchMode : unsigned char { ModeOff, ModeOn, ModeAuto, tmModeOff _DEPRECATED_ATTRIBUTE3("Use TTorchMode.ModeOff")  = 0x0, tmModeOn _DEPRECATED_ATTRIBUTE3("Use TTorchMode.ModeOn")  = 0x1, tmModeAuto _DEPRECATED_ATTRIBUTE3("Use TTorchMode.ModeAuto")  = 0x2 };

enum class DECLSPEC_DENUM TVideoCaptureQuality : unsigned char { PhotoQuality, HighQuality, MediumQuality, LowQuality, CaptureSettings, vcPhotoQuality _DEPRECATED_ATTRIBUTE3("Use TVideoCaptureQuality.PhotoQuality")  = 0, vcHighQuality _DEPRECATED_ATTRIBUTE3("Use TVideoCaptureQuality.HighQuality")  = 1, vcMediumQuality _DEPRECATED_ATTRIBUTE3("Use TVideoCaptureQuality.MediumQuality")  = 2, vcLowQuality _DEPRECATED_ATTRIBUTE3("Use TVideoCaptureQuality.LowQuality")  = 3 };

enum class DECLSPEC_DENUM TVideoCaptureSettingPriority : unsigned char { Resolution, FrameRate };

struct DECLSPEC_DRECORD TVideoCaptureSetting
{
	
private:
	class DELPHICLASS TResolutionComparer;
	class PASCALIMPLEMENTATION TResolutionComparer : public System::Generics::Defaults::TComparer__1<TVideoCaptureSetting>
	{
		typedef System::Generics::Defaults::TComparer__1<TVideoCaptureSetting> inherited;
		
	public:
		virtual int __fastcall Compare(const TVideoCaptureSetting &Left, const TVideoCaptureSetting &Right);
	public:
		/* TObject.Create */ inline __fastcall TResolutionComparer() : System::Generics::Defaults::TComparer__1<TVideoCaptureSetting>() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TResolutionComparer() { }
		
	};
	
	
	class DELPHICLASS TFrameRateComparer;
	class PASCALIMPLEMENTATION TFrameRateComparer : public System::Generics::Defaults::TComparer__1<TVideoCaptureSetting>
	{
		typedef System::Generics::Defaults::TComparer__1<TVideoCaptureSetting> inherited;
		
	public:
		virtual int __fastcall Compare(const TVideoCaptureSetting &Left, const TVideoCaptureSetting &Right);
	public:
		/* TObject.Create */ inline __fastcall TFrameRateComparer() : System::Generics::Defaults::TComparer__1<TVideoCaptureSetting>() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TFrameRateComparer() { }
		
	};
	
	
	
private:
	int FWidth;
	int FHeight;
	double FFrameRate;
	double FMinFrameRate;
	double FMaxFrameRate;
	
public:
	static TVideoCaptureSetting __fastcall Create()/* overload */;
	static TVideoCaptureSetting __fastcall Create(const int AWidth, const int AHeight, const float AFrameRate)/* overload */;
	void __fastcall SetFrameRate(const double AValue, const double AMaxValue)/* overload */;
	void __fastcall SetFrameRate(const double AValue)/* overload */;
	System::Types::TSize __fastcall GetSize();
	bool __fastcall IsSmallerThan(const TVideoCaptureSetting &ASetting, TVideoCaptureSettingPriority APriority);
	__property int Width = {read=FWidth, write=FWidth};
	__property int Height = {read=FHeight, write=FHeight};
	__property double FrameRate = {read=FFrameRate, write=SetFrameRate};
	__property double MaxFrameRate = {read=FMaxFrameRate};
	__property double MinFrameRate = {read=FMinFrameRate};
};


class PASCALIMPLEMENTATION TVideoCaptureDevice : public TCaptureDevice
{
	typedef TCaptureDevice inherited;
	
private:
	TSampleBufferReadyEvent FOnSampleBufferReady;
	TVideoCaptureSettingPriority FCaptureSettingPriority;
	TVideoCaptureQuality FQuality;
	void __fastcall InternalSetCaptureSetting(const TVideoCaptureSetting &ASetting);
	System::TArray__1<TVideoCaptureSetting> __fastcall GetDefaultCanvasCaptureSettings();
	
protected:
	virtual TDevicePosition __fastcall GetPosition();
	virtual TVideoCaptureQuality __fastcall GetQuality();
	void __fastcall SetQuality(const TVideoCaptureQuality Value);
	virtual void __fastcall DoSetQuality(const TVideoCaptureQuality Value);
	virtual bool __fastcall GetHasFlash();
	virtual TFlashMode __fastcall GetFlashMode();
	virtual void __fastcall SetFlashMode(const TFlashMode Value);
	virtual bool __fastcall GetHasTorch();
	virtual TTorchMode __fastcall GetTorchMode();
	virtual void __fastcall SetTorchMode(const TTorchMode Value);
	virtual TFocusMode __fastcall GetFocusMode();
	virtual void __fastcall SetFocusMode(const TFocusMode Value);
	virtual TMediaType __fastcall GetMediaType();
	void __fastcall SampleBufferReady(const TMediaTime ATime);
	virtual void __fastcall DoSampleBufferToBitmap(Fmx::Graphics::TBitmap* const ABitmap, const bool ASetSize) = 0 ;
	virtual TVideoCaptureSetting __fastcall GetCaptureSetting() = 0 ;
	virtual bool __fastcall DoSetCaptureSetting(const TVideoCaptureSetting &ASetting) = 0 ;
	virtual System::TArray__1<TVideoCaptureSetting> __fastcall DoGetAvailableCaptureSettings() = 0 ;
	TVideoCaptureSetting __fastcall CreateCaptureSettings(const int AWidth, const int AHeight, const double AFrameRate, const double AMinFrameRate, const double AMaxFrameRate);
	
public:
	__fastcall virtual TVideoCaptureDevice(TCaptureDeviceManager* const AManager, const bool ADefault);
	void __fastcall SampleBufferToBitmap(Fmx::Graphics::TBitmap* const ABitmap, const bool ASetSize);
	bool __fastcall SetCaptureSetting(const TVideoCaptureSetting &ASetting);
	System::TArray__1<TVideoCaptureSetting> __fastcall GetAvailableCaptureSettings(const Fmx::Graphics::TCanvasClass ACanvasClass);
	__property System::TArray__1<TVideoCaptureSetting> AvailableCaptureSettings = {read=GetDefaultCanvasCaptureSettings};
	__property TVideoCaptureSetting CaptureSetting = {read=GetCaptureSetting, write=InternalSetCaptureSetting};
	__property TVideoCaptureSettingPriority CaptureSettingPriority = {read=FCaptureSettingPriority, write=FCaptureSettingPriority, nodefault};
	__property TDevicePosition Position = {read=GetPosition, nodefault};
	__property TVideoCaptureQuality Quality = {read=GetQuality, write=SetQuality, nodefault};
	__property bool HasFlash = {read=GetHasFlash, nodefault};
	__property bool HasTorch = {read=GetHasTorch, nodefault};
	__property TFlashMode FlashMode = {read=GetFlashMode, write=SetFlashMode, nodefault};
	__property TFocusMode FocusMode = {read=GetFocusMode, write=SetFocusMode, nodefault};
	__property TTorchMode TorchMode = {read=GetTorchMode, write=SetTorchMode, nodefault};
	__property TSampleBufferReadyEvent OnSampleBufferReady = {read=FOnSampleBufferReady, write=FOnSampleBufferReady};
public:
	/* TCaptureDevice.Destroy */ inline __fastcall virtual ~TVideoCaptureDevice() { }
	
};


typedef System::Generics::Collections::TObjectList__1<TCaptureDevice*>* TCaptureDeviceList;

typedef System::Generics::Collections::TList__1<TCaptureDeviceClass>* TCaptureDeviceClassList;

class PASCALIMPLEMENTATION TCaptureDeviceManager : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TCaptureDevice* operator[](int Index) { return this->Devices[Index]; }
	
private:
	static System::Generics::Collections::TList__1<TCaptureDeviceClass>* FCustomDevices;
	static TCaptureDeviceManager* FCurrentManager;
	static TCaptureDeviceManager* __fastcall InternalGetCaptureDeviceManager();
	
protected:
	void __fastcall AddDevice(TCaptureDevice* const Device);
	void __fastcall RemoveDevice(TCaptureDevice* const Device);
	
private:
	System::Generics::Collections::TObjectList__1<TCaptureDevice*>* FDevices;
	System::Generics::Collections::TObjectList__1<TCaptureDevice*>* FDevicesByKind;
	int __fastcall GetCount();
	TCaptureDevice* __fastcall GetDevice(int Index);
	TAudioCaptureDevice* __fastcall GetDefaultAudioCaptureDevice();
	TVideoCaptureDevice* __fastcall GetDefaultVideoCaptureDevice();
	
public:
	__fastcall virtual TCaptureDeviceManager();
	__fastcall virtual ~TCaptureDeviceManager();
	static void __fastcall UnInitialize();
	__classmethod void __fastcall RegisterCaptureDeviceClass(const TCaptureDeviceClass CaptureDeviceClass);
	System::Generics::Collections::TObjectList__1<TCaptureDevice*>* __fastcall GetDevicesByMediaType(TMediaType MediaType);
	TCaptureDevice* __fastcall GetDefaultDeviceByMediaType(TMediaType MediaType);
	TCaptureDevice* __fastcall GetDevicesByName(const System::UnicodeString Name);
	__property int Count = {read=GetCount, nodefault};
	__property TAudioCaptureDevice* DefaultAudioCaptureDevice = {read=GetDefaultAudioCaptureDevice};
	__property TVideoCaptureDevice* DefaultVideoCaptureDevice = {read=GetDefaultVideoCaptureDevice};
	__property TCaptureDevice* Devices[int Index] = {read=GetDevice/*, default*/};
	/* static */ __property TCaptureDeviceManager* Current = {read=InternalGetCaptureDeviceManager};
};


enum class DECLSPEC_DENUM TCameraKind : unsigned char { Default, FrontCamera, BackCamera, ckDefault _DEPRECATED_ATTRIBUTE3("Use TCameraKind.Default")  = 0x0, ckFrontCamera _DEPRECATED_ATTRIBUTE3("Use TCameraKind.FrontCamera")  = 0x1, ckBackCamera _DEPRECATED_ATTRIBUTE3("Use TCameraKind.BackCamera")  = 0x2 };

class PASCALIMPLEMENTATION TCameraComponent : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TSampleBufferReadyEvent FOnSampleBufferReady;
	TCameraKind FCameraKind;
	TVideoCaptureDevice* FDevice;
	bool FActive;
	TVideoCaptureDevice* __fastcall GetDevice();
	void __fastcall SetCameraKind(const TCameraKind Value);
	bool __fastcall GetActive();
	void __fastcall SetActive(const bool Value);
	TFlashMode __fastcall GetFlashMode();
	TFocusMode __fastcall GetFocusMode();
	bool __fastcall GetHasFlash();
	bool __fastcall GetHasTorch();
	TVideoCaptureQuality __fastcall GetQuality();
	TTorchMode __fastcall GetTorchMode();
	void __fastcall SetFlashMode(const TFlashMode Value);
	void __fastcall SetFocusMode(const TFocusMode Value);
	void __fastcall SetQuality(const TVideoCaptureQuality Value);
	void __fastcall SetTorchMode(const TTorchMode Value);
	void __fastcall SetCaptureSettingPriority(const TVideoCaptureSettingPriority APriority);
	TVideoCaptureSettingPriority __fastcall GetCaptureSettingPriority();
	void __fastcall InternalSetCaptureSetting(const TVideoCaptureSetting &ASetting);
	
protected:
	void __fastcall DoStart();
	void __fastcall DoStop();
	void __fastcall DoSampleBufferReady(System::TObject* Sender, const TMediaTime ATime);
	__property TVideoCaptureDevice* Device = {read=GetDevice};
	
public:
	__fastcall virtual TCameraComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCameraComponent();
	void __fastcall SampleBufferToBitmap(Fmx::Graphics::TBitmap* const ABitmap, const bool ASetSize);
	TVideoCaptureSetting __fastcall GetCaptureSetting();
	bool __fastcall SetCaptureSetting(const TVideoCaptureSetting &ASetting);
	System::TArray__1<TVideoCaptureSetting> __fastcall GetDefaultCanvasCaptureSettings();
	System::TArray__1<TVideoCaptureSetting> __fastcall GetAvailableCaptureSettings(const Fmx::Graphics::TCanvasClass ACanvasClass);
	__property System::TArray__1<TVideoCaptureSetting> AvailableCaptureSettings = {read=GetDefaultCanvasCaptureSettings};
	__property TVideoCaptureSetting CaptureSetting = {read=GetCaptureSetting, write=InternalSetCaptureSetting};
	__property TVideoCaptureSettingPriority CaptureSettingPriority = {read=GetCaptureSettingPriority, write=SetCaptureSettingPriority, nodefault};
	__property TVideoCaptureQuality Quality = {read=GetQuality, write=SetQuality, nodefault};
	__property bool HasFlash = {read=GetHasFlash, nodefault};
	__property bool HasTorch = {read=GetHasTorch, nodefault};
	__property TFlashMode FlashMode = {read=GetFlashMode, write=SetFlashMode, nodefault};
	__property TFocusMode FocusMode = {read=GetFocusMode, write=SetFocusMode, nodefault};
	__property TTorchMode TorchMode = {read=GetTorchMode, write=SetTorchMode, nodefault};
	
__published:
	__property bool Active = {read=GetActive, write=SetActive, default=0};
	__property TCameraKind Kind = {read=FCameraKind, write=SetCameraKind, default=0};
	__property TSampleBufferReadyEvent OnSampleBufferReady = {read=FOnSampleBufferReady, write=FOnSampleBufferReady};
};


class PASCALIMPLEMENTATION EMediaException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMediaException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMediaException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMediaException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMediaException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMediaException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMediaException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMediaException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMediaException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMediaException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMediaException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMediaException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMediaException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMediaException() { }
	
};


enum class DECLSPEC_DENUM TMediaState : unsigned char { Unavailable, Playing, Stopped };

class PASCALIMPLEMENTATION TMedia : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FFileName;
	TMediaPlayerControl* FControl;
	void __fastcall SetControl(TMediaPlayerControl* const Value);
	
protected:
	virtual TMediaTime __fastcall GetDuration() = 0 ;
	virtual TMediaTime __fastcall GetCurrent() = 0 ;
	virtual void __fastcall SetCurrent(const TMediaTime Value) = 0 ;
	virtual System::Types::TPointF __fastcall GetVideoSize() = 0 ;
	virtual TMediaState __fastcall GetMediaState() = 0 ;
	virtual float __fastcall GetVolume() = 0 ;
	virtual void __fastcall SetVolume(const float Value) = 0 ;
	virtual void __fastcall UpdateMediaFromControl();
	virtual void __fastcall DoPlay() = 0 ;
	virtual void __fastcall DoStop() = 0 ;
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj) = 0 ;
	
public:
	__fastcall virtual TMedia(const System::UnicodeString AFileName);
	void __fastcall Play();
	void __fastcall Stop();
	__property TMediaPlayerControl* Control = {read=FControl, write=SetControl};
	__property System::UnicodeString FileName = {read=FFileName};
	__property TMediaTime Duration = {read=GetDuration};
	__property TMediaTime CurrentTime = {read=GetCurrent, write=SetCurrent};
	__property System::Types::TPointF VideoSize = {read=GetVideoSize};
	__property float Volume = {read=GetVolume, write=SetVolume};
	__property TMediaState State = {read=GetMediaState, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMedia() { }
	
};


class PASCALIMPLEMENTATION TCustomMediaCodec : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual TMedia* __fastcall CreateFromFile(const System::UnicodeString AFileName) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomMediaCodec() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomMediaCodec() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TCustomMediaCodecClass);

class PASCALIMPLEMENTATION EMediaCodecManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMediaCodecManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMediaCodecManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMediaCodecManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMediaCodecManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMediaCodecManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMediaCodecManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMediaCodecManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMediaCodecManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMediaCodecManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMediaCodecManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMediaCodecManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMediaCodecManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMediaCodecManagerException() { }
	
};


class PASCALIMPLEMENTATION TMediaCodecManager : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	struct DECLSPEC_DRECORD TMediaCodecClassDescriptor
	{
	public:
		System::UnicodeString Extension;
		System::UnicodeString Description;
		TMediaType MediaType;
		TCustomMediaCodecClass MediaCodecClass;
	};
	
	
	
private:
	enum class DECLSPEC_DENUM TMediaCodecDescriptorField : unsigned char { Extension, Description };
	
	
private:
	static System::Generics::Collections::TList__1<TMediaCodecClassDescriptor>* FMediaCodecClassDescriptors;
	__classmethod TMediaCodecClassDescriptor __fastcall FindMediaCodecDescriptor(const System::UnicodeString Name, TMediaCodecDescriptorField Field);
	
public:
	__classmethod void __fastcall UnInitialize();
	__classmethod void __fastcall RegisterMediaCodecClass(const System::UnicodeString Extension, const System::UnicodeString Description, TMediaType MediaType, TCustomMediaCodecClass MediaCodecClass)/* overload */;
	__classmethod System::UnicodeString __fastcall GetFileTypes();
	__classmethod System::UnicodeString __fastcall GetFileTypesByType(TMediaType MediaType);
	__classmethod System::UnicodeString __fastcall GetFilterString();
	__classmethod System::UnicodeString __fastcall GetFilterStringByType(TMediaType MediaType);
	__classmethod bool __fastcall IsCodedExists(const System::UnicodeString AFileName)/* overload */;
	__classmethod TMedia* __fastcall CreateFromFile(const System::UnicodeString AFileName);
public:
	/* TObject.Create */ inline __fastcall TMediaCodecManager() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMediaCodecManager() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayer : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	TMedia* FMedia;
	System::UnicodeString FFileName;
	TMediaPlayerControl* FControl;
	void __fastcall SetControl(TMediaPlayerControl* const Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	TMediaState __fastcall GetMediaState();
	TMediaTime __fastcall GetCurrent();
	TMediaTime __fastcall GetDuration();
	TMedia* __fastcall GetMedia();
	System::Types::TPointF __fastcall GetVideoSize();
	float __fastcall GetVolume();
	void __fastcall SetCurrent(const TMediaTime Value);
	void __fastcall SetVolume(const float Value);
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	
public:
	__fastcall virtual TMediaPlayer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMediaPlayer();
	void __fastcall Play();
	void __fastcall Stop();
	void __fastcall Clear();
	__property TMedia* Media = {read=GetMedia};
	__property TMediaTime Duration = {read=GetDuration};
	__property TMediaTime CurrentTime = {read=GetCurrent, write=SetCurrent};
	__property System::Types::TPointF VideoSize = {read=GetVideoSize};
	__property float Volume = {read=GetVolume, write=SetVolume};
	__property TMediaState State = {read=GetMediaState, nodefault};
	
__published:
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
};


class PASCALIMPLEMENTATION TMediaPlayerControl : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	TMediaPlayer* FMediaPlayer;
	Fmx::Types::TFmxObject* FSavedParent;
	void __fastcall SetMediaPlayer(TMediaPlayer* const Value);
	void __fastcall UpdateMedia();
	void __fastcall FormHandleAfterCreated(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	void __fastcall FormHandleBeforeDestroyed(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	
protected:
	virtual void __fastcall AncestorVisibleChanged(const bool Visible);
	virtual void __fastcall ParentChanged();
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall Move();
	virtual void __fastcall Resize();
	virtual void __fastcall Paint();
	virtual void __fastcall Show();
	virtual void __fastcall Hide();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TMediaPlayerControl(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMediaPlayerControl();
	
__published:
	__property Size;
	__property Align = {default=0};
	__property Anchors;
	__property Height;
	__property Padding;
	__property TMediaPlayer* MediaPlayer = {read=FMediaPlayer, write=SetMediaPlayer};
	__property Margins;
	__property Position;
	__property Visible = {default=1};
	__property Width;
};


class PASCALIMPLEMENTATION TCustomMediaPlayerAction : public Fmx::Actnlist::TCustomAction
{
	typedef Fmx::Actnlist::TCustomAction inherited;
	
private:
	TMediaPlayer* FMediaPlayer;
	void __fastcall SetMediaPlayer(TMediaPlayer* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TCustomMediaPlayerAction(System::Classes::TComponent* AOwner);
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	virtual bool __fastcall Update();
	__property TMediaPlayer* MediaPlayer = {read=FMediaPlayer, write=SetMediaPlayer};
	
__published:
	__property CustomText = {default=0};
	__property ImageIndex = {default=-1};
	__property ShortCut = {default=0};
	__property SecondaryShortCuts;
	__property Visible = {default=1};
	__property UnsupportedArchitectures = {default=0};
	__property OnUpdate;
public:
	/* TContainedAction.Destroy */ inline __fastcall virtual ~TCustomMediaPlayerAction() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerStart : public TCustomMediaPlayerAction
{
	typedef TCustomMediaPlayerAction inherited;
	
protected:
	virtual void __fastcall CustomTextChanged();
	
public:
	virtual bool __fastcall Update();
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property MediaPlayer;
public:
	/* TCustomMediaPlayerAction.Create */ inline __fastcall virtual TMediaPlayerStart(System::Classes::TComponent* AOwner) : TCustomMediaPlayerAction(AOwner) { }
	
public:
	/* TContainedAction.Destroy */ inline __fastcall virtual ~TMediaPlayerStart() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerStop : public TCustomMediaPlayerAction
{
	typedef TCustomMediaPlayerAction inherited;
	
protected:
	virtual void __fastcall CustomTextChanged();
	
public:
	virtual bool __fastcall Update();
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property MediaPlayer;
public:
	/* TCustomMediaPlayerAction.Create */ inline __fastcall virtual TMediaPlayerStop(System::Classes::TComponent* AOwner) : TCustomMediaPlayerAction(AOwner) { }
	
public:
	/* TContainedAction.Destroy */ inline __fastcall virtual ~TMediaPlayerStop() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerPlayPause : public TCustomMediaPlayerAction
{
	typedef TCustomMediaPlayerAction inherited;
	
protected:
	virtual void __fastcall CustomTextChanged();
	
public:
	virtual bool __fastcall Update();
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property MediaPlayer;
public:
	/* TCustomMediaPlayerAction.Create */ inline __fastcall virtual TMediaPlayerPlayPause(System::Classes::TComponent* AOwner) : TCustomMediaPlayerAction(AOwner) { }
	
public:
	/* TContainedAction.Destroy */ inline __fastcall virtual ~TMediaPlayerPlayPause() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerValue : public Fmx::Stdactns::TCustomValueRangeAction
{
	typedef Fmx::Stdactns::TCustomValueRangeAction inherited;
	
	
public:
	enum class DECLSPEC_DENUM TState : unsigned char { Normal, ActionUpdating, ValueUpdating };
	
	
private:
	TMediaPlayer* FMediaPlayer;
	TState FState;
	void __fastcall SetMediaPlayer(TMediaPlayer* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Fmx::Stdactns::TCustomValueRange* __fastcall CreateValueRange();
	__property TState State = {read=FState, nodefault};
	virtual void __fastcall UpdateValueAction();
	virtual void __fastcall UpdateValuePlayer();
	
public:
	__fastcall virtual TMediaPlayerValue(System::Classes::TComponent* AOwner);
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	virtual bool __fastcall Update();
	__property TMediaPlayer* MediaPlayer = {read=FMediaPlayer, write=SetMediaPlayer};
	
__published:
	__property CustomText = {default=0};
	__property ImageIndex = {default=-1};
	__property ShortCut = {default=0};
	__property SecondaryShortCuts;
	__property Visible = {default=1};
	__property UnsupportedArchitectures = {default=0};
	__property OnUpdate;
public:
	/* TCustomValueRangeAction.Destroy */ inline __fastcall virtual ~TMediaPlayerValue() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerCurrentTime : public TMediaPlayerValue
{
	typedef TMediaPlayerValue inherited;
	
protected:
	virtual Fmx::Stdactns::TCustomValueRange* __fastcall CreateValueRange();
	virtual void __fastcall UpdateValueAction();
	virtual void __fastcall UpdateValuePlayer();
	virtual void __fastcall CustomTextChanged();
	
__published:
	__property MediaPlayer;
public:
	/* TMediaPlayerValue.Create */ inline __fastcall virtual TMediaPlayerCurrentTime(System::Classes::TComponent* AOwner) : TMediaPlayerValue(AOwner) { }
	
public:
	/* TCustomValueRangeAction.Destroy */ inline __fastcall virtual ~TMediaPlayerCurrentTime() { }
	
};


class PASCALIMPLEMENTATION TMediaPlayerVolume : public TMediaPlayerValue
{
	typedef TMediaPlayerValue inherited;
	
private:
	static constexpr System::Int8 PrecentCount = System::Int8(0x64);
	
	
protected:
	virtual Fmx::Stdactns::TCustomValueRange* __fastcall CreateValueRange();
	virtual void __fastcall UpdateValueAction();
	virtual void __fastcall UpdateValuePlayer();
	virtual void __fastcall CustomTextChanged();
	
__published:
	__property MediaPlayer;
public:
	/* TMediaPlayerValue.Create */ inline __fastcall virtual TMediaPlayerVolume(System::Classes::TComponent* AOwner) : TMediaPlayerValue(AOwner) { }
	
public:
	/* TCustomValueRangeAction.Destroy */ inline __fastcall virtual ~TMediaPlayerVolume() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr int MediaTimeScale = int(0x989680);
}	/* namespace Media */
}	/* namespace Fmx */
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
#endif	// Fmx_MediaHPP
