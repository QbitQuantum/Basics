// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DirectInput.pas' rev: 34.00 (Windows)

#ifndef Winapi_DirectinputHPP
#define Winapi_DirectinputHPP

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
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#define DIRECTINPUT_VERSION         0x0800
#include "dinput.h"

DECLARE_DINTERFACE_TYPE(IDirectInputEffect);
DECLARE_DINTERFACE_TYPE(IDirectInputDeviceA);
DECLARE_DINTERFACE_TYPE(IDirectInputDeviceW);
DECLARE_DINTERFACE_TYPE(IDirectInputA);
DECLARE_DINTERFACE_TYPE(IDirectInputW);
DECLARE_DINTERFACE_TYPE(IDirectInput2A);
DECLARE_DINTERFACE_TYPE(IDirectInput2W);
DECLARE_DINTERFACE_TYPE(IDirectInput7A);
DECLARE_DINTERFACE_TYPE(IDirectInput7W);
DECLARE_DINTERFACE_TYPE(IDirectInput8A);
DECLARE_DINTERFACE_TYPE(IDirectInput8W);
DECLARE_DINTERFACE_TYPE(IDirectInputDeviceA);
DECLARE_DINTERFACE_TYPE(IDirectInputDeviceW);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice2A);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice2W);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice7A);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice7W);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice8A);
DECLARE_DINTERFACE_TYPE(IDirectInputDevice8W);
#ifdef UNICODE
typedef _di_IDirectInputW _di_IDirectInput;
typedef _di_IDirectInput2W _di_IDirectInput2;
typedef _di_IDirectInput7W _di_IDirectInput7;
typedef _di_IDirectInput8W _di_IDirectInput8;
typedef _di_IDirectInputDeviceW _di_IDirectInputDevice;
typedef _di_IDirectInputDevice2W _di_IDirectInputDevice2;
typedef _di_IDirectInputDevice7W _di_IDirectInputDevice7;
typedef _di_IDirectInputDevice8W _di_IDirectInputDevice8;
#else
typedef _di_IDirectInputA _di_IDirectInput;
typedef _di_IDirectInput2A _di_IDirectInput2;
typedef _di_IDirectInput7A _di_IDirectInput7;
typedef _di_IDirectInput8A _di_IDirectInput8;
typedef _di_IDirectInputDeviceA _di_IDirectInputDevice;
typedef _di_IDirectInputDevice2A _di_IDirectInputDevice2;
typedef _di_IDirectInputDevice7A _di_IDirectInputDevice7;
typedef _di_IDirectInputDevice8A _di_IDirectInputDevice8;
#endif
typedef LPDIENUMEFFECTSINFILECALLBACK TDIEnumEffectsInFileCallback;
typedef LPDIENUMEFFECTSCALLBACKA TDIEnumEffectsCallbackA;
typedef LPDIENUMEFFECTSCALLBACKW TDIEnumEffectsCallbackW;
typedef LPDIENUMEFFECTSINFILECALLBACK TDIEnumEffectsInFileCallback;
typedef LPDIENUMCREATEDEFFECTOBJECTSCALLBACK TDIEnumCreatedEffectObjectsCallback;

namespace Winapi
{
namespace Directinput
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef DICONSTANTFORCE *PDIConstantForce;

typedef DICONSTANTFORCE TDIConstantForce;

typedef DIRAMPFORCE *PDIRampForce;

typedef DIRAMPFORCE TDIRampForce;

typedef DIPERIODIC *PDIPeriodic;

typedef DIPERIODIC TDIPeriodic;

typedef DICONDITION *PDICondition;

typedef DICONDITION TDICondition;

typedef DICUSTOMFORCE *PDICustomForce;

typedef DICUSTOMFORCE TDICustomForce;

typedef DIENVELOPE *PDIEnvelope;

typedef DIENVELOPE TDIEnvelope;

typedef DIEFFECT_DX5 *PDIEffectDX5;

typedef DIEFFECT_DX5 TDIEffectDX5;

typedef DIEFFECT *PDIEffect;

typedef DIEFFECT TDIEffect;

typedef DIEFFECT TDIEffectDX6;

typedef DIEFFECT *PDIEffectDX6;

typedef DIFILEEFFECT *PDIFileEffect;

typedef DIFILEEFFECT TDIFileEffect;

typedef DIEFFESCAPE *PDIEffEscape;

typedef DIEFFESCAPE TDIEffEscape;

typedef DIDEVCAPS_DX3 *PDIDevCapsDX3;

typedef DIDEVCAPS_DX3 TDIDevCapsDX3;

typedef DIDEVCAPS *PDIDevCaps;

typedef DIDEVCAPS TDIDevCaps;

typedef _DIOBJECTDATAFORMAT *PDIObjectDataFormat;

typedef _DIOBJECTDATAFORMAT TDIObjectDataFormat;

typedef _DIDATAFORMAT *PDIDataFormat;

typedef _DIDATAFORMAT TDIDataFormat;

typedef _DIACTIONA *PDIActionA;

typedef _DIACTIONW *PDIActionW;

typedef PDIActionW PDIAction;

typedef _DIACTIONA TDIActionA;

typedef _DIACTIONW TDIActionW;

typedef _DIACTIONW TDIAction;

typedef _DIACTIONFORMATA *PDIActionFormatA;

typedef _DIACTIONFORMATW *PDIActionFormatW;

typedef PDIActionFormatW PDIActionFormat;

typedef _DIACTIONFORMATA TDIActionFormatA;

typedef _DIACTIONFORMATW TDIActionFormatW;

typedef _DIACTIONFORMATW TDIActionFormat;

typedef _DICOLORSET *PDIColorSet;

typedef _DICOLORSET TDIColorSet;

typedef _DICONFIGUREDEVICESPARAMSA *PDIConfigureDevicesParamsA;

typedef _DICONFIGUREDEVICESPARAMSW *PDIConfigureDevicesParamsW;

typedef PDIConfigureDevicesParamsW PDIConfigureDevicesParams;

typedef _DICONFIGUREDEVICESPARAMSA TDIConfigureDevicesParamsA;

typedef _DICONFIGUREDEVICESPARAMSW TDIConfigureDevicesParamsW;

typedef _DICONFIGUREDEVICESPARAMSW TDIConfigureDevicesParams;

typedef _DIDEVICEIMAGEINFOA *PDIDeviceImageInfoA;

typedef _DIDEVICEIMAGEINFOW *PDIDeviceImageInfoW;

typedef PDIDeviceImageInfoW PDIDeviceImageInfo;

typedef _DIDEVICEIMAGEINFOA TDIDeviceImageInfoA;

typedef _DIDEVICEIMAGEINFOW TDIDeviceImageInfoW;

typedef _DIDEVICEIMAGEINFOW TDIDeviceImageInfo;

typedef _DIDEVICEIMAGEINFOHEADERA *PDIDeviceImageInfoHeaderA;

typedef _DIDEVICEIMAGEINFOHEADERW *PDIDeviceImageInfoHeaderW;

typedef PDIDeviceImageInfoHeaderW PDIDeviceImageInfoHeader;

typedef _DIDEVICEIMAGEINFOHEADERA DIDEVICEIMAGEINFOHEADERA;

typedef _DIDEVICEIMAGEINFOHEADERW DIDEVICEIMAGEINFOHEADERW;

typedef _DIDEVICEIMAGEINFOHEADERW DIDEVICEIMAGEINFOHEADER;

typedef _DIDEVICEIMAGEINFOHEADERA TDIDeviceImageInfoHeaderA;

typedef _DIDEVICEIMAGEINFOHEADERW TDIDeviceImageInfoHeaderW;

typedef _DIDEVICEIMAGEINFOHEADERW TDIDeviceImageInfoHeader;

typedef DIDEVICEOBJECTINSTANCE_DX3A *PDIDeviceObjectInstanceDX3A;

typedef DIDEVICEOBJECTINSTANCE_DX3W *PDIDeviceObjectInstanceDX3W;

typedef PDIDeviceObjectInstanceDX3W PDIDeviceObjectInstanceDX3;

typedef DIDEVICEOBJECTINSTANCE_DX3A TDIDeviceObjectInstanceDX3A;

typedef DIDEVICEOBJECTINSTANCE_DX3W TDIDeviceObjectInstanceDX3W;

typedef DIDEVICEOBJECTINSTANCE_DX3W TDIDeviceObjectInstanceDX3;

typedef DIDEVICEOBJECTINSTANCEA *PDIDeviceObjectInstanceA;

typedef DIDEVICEOBJECTINSTANCEW *PDIDeviceObjectInstanceW;

typedef PDIDeviceObjectInstanceW PDIDeviceObjectInstance;

typedef DIDEVICEOBJECTINSTANCEA TDIDeviceObjectInstanceA;

typedef DIDEVICEOBJECTINSTANCEW TDIDeviceObjectInstanceW;

typedef DIDEVICEOBJECTINSTANCEW TDIDeviceObjectInstance;

typedef DIPROPHEADER *PDIPropHeader;

typedef DIPROPHEADER TDIPropHeader;

typedef DIPROPDWORD *PDIPropDWord;

typedef DIPROPDWORD TDIPropDWord;

typedef DIPROPPOINTER *PDIPropPointer;

typedef DIPROPPOINTER TDIPropPointer;

typedef DIPROPRANGE *PDIPropRange;

typedef DIPROPRANGE TDIPropRange;

typedef DIPROPCAL *PDIPropCal;

typedef DIPROPCAL TDIPropCal;

typedef DIPROPCALPOV *PDIPropCalPov;

typedef DIPROPCALPOV TDIPropCalPov;

typedef DIPROPGUIDANDPATH *PDIPropGuidAndPath;

typedef DIPROPGUIDANDPATH TDIPropGuidAndPath;

typedef DIPROPSTRING *PDIPropString;

typedef DIPROPSTRING TDIPropString;

typedef _CPOINT *PCPoint;

typedef _CPOINT TCPoint;

typedef DIPROPCPOINTS *PDIPropCPoints;

typedef DIPROPCPOINTS TDIPropCPoints;

typedef DIDEVICEOBJECTDATA_DX3 *PDIDeviceObjectDataDX3;

typedef DIDEVICEOBJECTDATA_DX3 TDIDeviceObjectDataDX3;

typedef DIDEVICEOBJECTDATA *PDIDeviceObjectData;

typedef DIDEVICEOBJECTDATA TDIDeviceObjectData;

typedef DIDEVICEINSTANCE_DX3A *PDIDeviceInstanceDX3A;

typedef DIDEVICEINSTANCE_DX3W *PDIDeviceInstanceDX3W;

typedef PDIDeviceInstanceDX3W PDIDeviceInstanceDX3;

typedef DIDEVICEINSTANCE_DX3A TDIDeviceInstanceDX3A;

typedef DIDEVICEINSTANCE_DX3W TDIDeviceInstanceDX3W;

typedef DIDEVICEINSTANCE_DX3W TDIDeviceInstanceDX3;

typedef DIDEVICEINSTANCEA *PDIDeviceInstanceA;

typedef DIDEVICEINSTANCEW *PDIDeviceInstanceW;

typedef PDIDeviceInstanceW PDIDeviceInstance;

typedef DIDEVICEINSTANCEA TDIDeviceInstanceA;

typedef DIDEVICEINSTANCEW TDIDeviceInstanceW;

typedef DIDEVICEINSTANCEW TDIDeviceInstance;

typedef DIEFFECTINFOA *PDIEffectInfoA;

typedef DIEFFECTINFOW *PDIEffectInfoW;

typedef PDIEffectInfoW PDIEffectInfo;

typedef DIEFFECTINFOA TDIEffectInfoA;

typedef DIEFFECTINFOW TDIEffectInfoW;

typedef DIEFFECTINFOW TDIEffectInfo;

typedef _DIMOUSESTATE *PDIMouseState;

typedef _DIMOUSESTATE TDIMouseState;

typedef _DIMOUSESTATE2 *PDIMouseState2;

typedef _DIMOUSESTATE2 TDIMouseState2;

typedef DIJOYSTATE *PDIJoyState;

typedef DIJOYSTATE TDIJoyState;

typedef DIJOYSTATE2 *PDIJoyState2;

typedef DIJOYSTATE2 TDIJoyState2;

typedef System::LongBool __stdcall (*TDIConfigureDevicesCallback)(System::_di_IInterface lpDDSTarget, void * pvRef);

typedef void __stdcall (*TShowJoyCPL)(HWND hWnd);

//-- var, const, procedure ---------------------------------------------------
#define SID_IDirectInputA L"{89521360-AA8A-11CF-BFC7-444553540000}"
#define SID_IDirectInputW L"{89521361-AA8A-11CF-BFC7-444553540000}"
#define SID_IDirectInput2A L"{5944E662-AA8A-11CF-BFC7-444553540000}"
#define SID_IDirectInput2W L"{5944E663-AA8A-11CF-BFC7-444553540000}"
#define SID_IDirectInput7A L"{9A4CB684-236D-11D3-8E9D-00C04F6844AE}"
#define SID_IDirectInput7W L"{9A4CB685-236D-11D3-8E9D-00C04F6844AE}"
#define SID_IDirectInput8A L"{BF798030-483A-4DA2-AA99-5D64ED369700}"
#define SID_IDirectInput8W L"{BF798031-483A-4DA2-AA99-5D64ED369700}"
#define SID_IDirectInputDeviceA L"{5944E680-C92E-11CF-BFC7-444553540000}"
#define SID_IDirectInputDeviceW L"{5944E681-C92E-11CF-BFC7-444553540000}"
#define SID_IDirectInputDevice2A L"{5944E682-C92E-11CF-BFC7-444553540000}"
#define SID_IDirectInputDevice2W L"{5944E683-C92E-11CF-BFC7-444553540000}"
#define SID_IDirectInputDevice7A L"{57D7C6BC-2356-11D3-8E9D-00C04F6844AE}"
#define SID_IDirectInputDevice7W L"{57D7C6BD-2356-11D3-8E9D-00C04F6844AE}"
#define SID_IDirectInputDevice8A L"{54D41080-DC15-4833-A41B-748F73A38179}"
#define SID_IDirectInputDevice8W L"{54D41081-DC15-4833-A41B-748F73A38179}"
#define SID_IDirectInputEffect L"{E7E1F7C0-88D2-11D0-9AD0-00A0C9A06E35}"
static const System::Int8 DIJOFS_BUTTON_ = System::Int8(0x30);
#define DirectInputDll L"dinput.dll"
#define DirectInput8Dll L"dinput8.dll"
#define WinMMDll L"WinMM.dll"
#define JoyCPL L"joy.cpl"
extern DELPHI_PACKAGE bool __fastcall DirectInputLoaded(void);
extern DELPHI_PACKAGE bool __fastcall UnLoadDirectInput(void);
extern DELPHI_PACKAGE bool __fastcall LoadDirectInput(void);
}	/* namespace Directinput */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECTINPUT)
using namespace Winapi::Directinput;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DirectinputHPP
