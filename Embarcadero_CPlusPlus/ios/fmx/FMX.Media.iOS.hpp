// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Media.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Media_IosHPP
#define Fmx_Media_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CoreMedia.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.AVFoundation.hpp>
#include <FMX.Media.AVFoundation.hpp>
#include <Macapi.ObjectiveC.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Media
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAVVideoSampleDelegate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAVVideoSampleDelegate : public Fmx::Media::Avfoundation::TVideoSampleDelegateBase
{
	typedef Fmx::Media::Avfoundation::TVideoSampleDelegateBase inherited;
	
private:
	Iosapi::Uikit::_di_UIDevice FUIDevice;
	long __fastcall DetectVideoOrientation();
	
public:
	__fastcall TAVVideoSampleDelegate(Fmx::Media::Avfoundation::TAVVideoCaptureDeviceBase* const ACaptureDevice);
	void __cdecl captureOutput(Iosapi::Avfoundation::_di_AVCaptureOutput captureOutput, void * didOutputSampleBuffer, Iosapi::Avfoundation::_di_AVCaptureConnection fromConnection);
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TAVVideoSampleDelegate() { }
	
private:
	void *__AVCaptureVideoDataOutputSampleBufferDelegate;	// Iosapi::Avfoundation::AVCaptureVideoDataOutputSampleBufferDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BC4EABBE-F21F-4592-93B0-0C40415E4A9A}
	operator Iosapi::Avfoundation::_di_AVCaptureVideoDataOutputSampleBufferDelegate()
	{
		Iosapi::Avfoundation::_di_AVCaptureVideoDataOutputSampleBufferDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Avfoundation::AVCaptureVideoDataOutputSampleBufferDelegate*(void) { return (Iosapi::Avfoundation::AVCaptureVideoDataOutputSampleBufferDelegate*)&__AVCaptureVideoDataOutputSampleBufferDelegate; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Media */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIA_IOS)
using namespace Fmx::Media::Ios;
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
#endif	// Fmx_Media_IosHPP
