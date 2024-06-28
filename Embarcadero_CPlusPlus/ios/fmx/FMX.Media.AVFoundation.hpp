// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Media.AVFoundation.pas' rev: 34.00 (iOS)

#ifndef Fmx_Media_AvfoundationHPP
#define Fmx_Media_AvfoundationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <FMX.Media.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Media
{
namespace Avfoundation
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAVCaptureDeviceManager;
class DELPHICLASS TAVVideoCaptureDeviceBase;
class DELPHICLASS TVideoSampleDelegateBase;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAVCaptureDeviceManager : public Fmx::Media::TCaptureDeviceManager
{
	typedef Fmx::Media::TCaptureDeviceManager inherited;
	
public:
	__fastcall virtual TAVCaptureDeviceManager();
public:
	/* TCaptureDeviceManager.Destroy */ inline __fastcall virtual ~TAVCaptureDeviceManager() { }
	
};


class PASCALIMPLEMENTATION TAVVideoCaptureDeviceBase : public Fmx::Media::TVideoCaptureDevice
{
	typedef Fmx::Media::TVideoCaptureDevice inherited;
	
public:
	__fastcall virtual TAVVideoCaptureDeviceBase(Fmx::Media::TCaptureDeviceManager* const AManager, const bool ADefault);
	__fastcall virtual ~TAVVideoCaptureDeviceBase();
	virtual void __fastcall SampleDelegate(void * ASampleBuffer) = 0 ;
};


class PASCALIMPLEMENTATION TVideoSampleDelegateBase : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
protected:
	bool FIsProcessingCapture;
	TAVVideoCaptureDeviceBase* FCaptureDevice;
	
public:
	__fastcall TVideoSampleDelegateBase(TAVVideoCaptureDeviceBase* const ACaptureDevice);
	__property bool IsProcessingCapture = {read=FIsProcessingCapture, nodefault};
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TVideoSampleDelegateBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Avfoundation */
}	/* namespace Media */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIA_AVFOUNDATION)
using namespace Fmx::Media::Avfoundation;
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
#endif	// Fmx_Media_AvfoundationHPP
