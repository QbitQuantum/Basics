// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DirectSound.pas' rev: 34.00 (Windows)

#ifndef Winapi_DirectsoundHPP
#define Winapi_DirectsoundHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.MMSystem.hpp>
#include <Winapi.DXTypes.hpp>

//-- user supplied -----------------------------------------------------------
#define DIRECTSOUND_VERSION         0x0900
#include "dsound.h"
DECLARE_DINTERFACE_TYPE(IReferenceClock);
DECLARE_DINTERFACE_TYPE(IDirectSound);
DECLARE_DINTERFACE_TYPE(IDirectSound8);
DECLARE_DINTERFACE_TYPE(IDirectSoundBuffer);
DECLARE_DINTERFACE_TYPE(IDirectSoundBuffer8);
DECLARE_DINTERFACE_TYPE(IDirectSound3DListener);
DECLARE_DINTERFACE_TYPE(IDirectSound3DBuffer);
DECLARE_DINTERFACE_TYPE(IDirectSoundCapture);
DECLARE_DINTERFACE_TYPE(IDirectSoundCaptureBuffer);
DECLARE_DINTERFACE_TYPE(IDirectSoundCaptureBuffer8);
DECLARE_DINTERFACE_TYPE(IDirectSoundNotify);
DECLARE_DINTERFACE_TYPE(IKsPropertySet);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXGargle);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXChorus);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXFlanger);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXEcho);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXDistortion);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXCompressor);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXParamEq);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXI3DL2Reverb);
DECLARE_DINTERFACE_TYPE(IDirectSoundFXWavesReverb);
DECLARE_DINTERFACE_TYPE(IDirectSoundCaptureFXAec);
DECLARE_DINTERFACE_TYPE(IDirectSoundCaptureFXNoiseSuppress);
DECLARE_DINTERFACE_TYPE(IDirectSoundFullDuplex);
typedef LPDSENUMCALLBACKA TDSEnumCallbackA;
typedef LPDSENUMCALLBACKW TDSEnumCallbackW;
typedef LPDSENUMCALLBACK TDSEnumCallback;

namespace Winapi
{
namespace Directsound
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void * *PPointer;

typedef char * *PPAnsiChar;

typedef _DSCCAPS *PDSCcaps;

typedef _DSFXGargle *PDSFXGargle;

typedef _DSFXGargle TDSFXGargle;

typedef _DSFXChorus *PDSFXChorus;

typedef _DSFXEcho *PDSFXEcho;

//-- var, const, procedure ---------------------------------------------------
#define DirectSoundDll L"dsound.dll"
extern DELPHI_PACKAGE bool __fastcall DirectSoundLoaded(void);
extern DELPHI_PACKAGE bool __fastcall UnLoadDirectSound(void);
extern DELPHI_PACKAGE bool __fastcall LoadDirectSound(void);
}	/* namespace Directsound */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECTSOUND)
using namespace Winapi::Directsound;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DirectsoundHPP
