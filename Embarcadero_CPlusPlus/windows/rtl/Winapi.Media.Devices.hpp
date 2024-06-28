// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Media.Devices.pas' rev: 34.00 (Windows)

#ifndef Winapi_Media_DevicesHPP
#define Winapi_Media_DevicesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.Foundation.Types.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Media.MediaProperties.hpp>
#include <Winapi.Perception.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Media
{
namespace Devices
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE Core_ICameraIntrinsics;
typedef System::DelphiInterface<Core_ICameraIntrinsics> _di_Core_ICameraIntrinsics;
__interface DELPHIINTERFACE IMediaDeviceController;
typedef System::DelphiInterface<IMediaDeviceController> _di_IMediaDeviceController;
__interface DELPHIINTERFACE IAudioDeviceController;
typedef System::DelphiInterface<IAudioDeviceController> _di_IAudioDeviceController;
__interface DELPHIINTERFACE IMediaDeviceControlCapabilities;
typedef System::DelphiInterface<IMediaDeviceControlCapabilities> _di_IMediaDeviceControlCapabilities;
__interface DELPHIINTERFACE IMediaDeviceControl;
typedef System::DelphiInterface<IMediaDeviceControl> _di_IMediaDeviceControl;
__interface DELPHIINTERFACE IVideoDeviceController;
typedef System::DelphiInterface<IVideoDeviceController> _di_IVideoDeviceController;
__interface DELPHIINTERFACE IReference_1__CaptureSceneMode;
typedef System::DelphiInterface<IReference_1__CaptureSceneMode> _di_IReference_1__CaptureSceneMode;
__interface DELPHIINTERFACE Core_IDepthCorrelatedCoordinateMapper;
typedef System::DelphiInterface<Core_IDepthCorrelatedCoordinateMapper> _di_Core_IDepthCorrelatedCoordinateMapper;
__interface DELPHIINTERFACE IReference_1__MediaCaptureFocusState;
typedef System::DelphiInterface<IReference_1__MediaCaptureFocusState> _di_IReference_1__MediaCaptureFocusState;
__interface DELPHIINTERFACE IModuleCommandResult;
typedef System::DelphiInterface<IModuleCommandResult> _di_IModuleCommandResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IModuleCommandResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IModuleCommandResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IModuleCommandResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IModuleCommandResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IModuleCommandResult> _di_AsyncOperationCompletedHandler_1__IModuleCommandResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IModuleCommandResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IModuleCommandResult_Base> _di_IAsyncOperation_1__IModuleCommandResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IModuleCommandResult;
typedef System::DelphiInterface<IAsyncOperation_1__IModuleCommandResult> _di_IAsyncOperation_1__IModuleCommandResult;
__interface DELPHIINTERFACE IAudioDeviceModule;
typedef System::DelphiInterface<IAudioDeviceModule> _di_IAudioDeviceModule;
__interface DELPHIINTERFACE IAudioDeviceModuleNotificationEventArgs;
typedef System::DelphiInterface<IAudioDeviceModuleNotificationEventArgs> _di_IAudioDeviceModuleNotificationEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs> _di_TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs;
__interface DELPHIINTERFACE IIterator_1__IAudioDeviceModule_Base;
typedef System::DelphiInterface<IIterator_1__IAudioDeviceModule_Base> _di_IIterator_1__IAudioDeviceModule_Base;
__interface DELPHIINTERFACE IIterator_1__IAudioDeviceModule;
typedef System::DelphiInterface<IIterator_1__IAudioDeviceModule> _di_IIterator_1__IAudioDeviceModule;
__interface DELPHIINTERFACE IIterable_1__IAudioDeviceModule_Base;
typedef System::DelphiInterface<IIterable_1__IAudioDeviceModule_Base> _di_IIterable_1__IAudioDeviceModule_Base;
__interface DELPHIINTERFACE IIterable_1__IAudioDeviceModule;
typedef System::DelphiInterface<IIterable_1__IAudioDeviceModule> _di_IIterable_1__IAudioDeviceModule;
__interface DELPHIINTERFACE IVectorView_1__IAudioDeviceModule;
typedef System::DelphiInterface<IVectorView_1__IAudioDeviceModule> _di_IVectorView_1__IAudioDeviceModule;
__interface DELPHIINTERFACE IAudioDeviceModulesManager;
typedef System::DelphiInterface<IAudioDeviceModulesManager> _di_IAudioDeviceModulesManager;
__interface DELPHIINTERFACE IAudioDeviceModulesManagerFactory;
typedef System::DelphiInterface<IAudioDeviceModulesManagerFactory> _di_IAudioDeviceModulesManagerFactory;
__interface DELPHIINTERFACE IIterator_1__CaptureSceneMode_Base;
typedef System::DelphiInterface<IIterator_1__CaptureSceneMode_Base> _di_IIterator_1__CaptureSceneMode_Base;
__interface DELPHIINTERFACE IIterator_1__CaptureSceneMode;
typedef System::DelphiInterface<IIterator_1__CaptureSceneMode> _di_IIterator_1__CaptureSceneMode;
__interface DELPHIINTERFACE IIterable_1__CaptureSceneMode_Base;
typedef System::DelphiInterface<IIterable_1__CaptureSceneMode_Base> _di_IIterable_1__CaptureSceneMode_Base;
__interface DELPHIINTERFACE IIterable_1__CaptureSceneMode;
typedef System::DelphiInterface<IIterable_1__CaptureSceneMode> _di_IIterable_1__CaptureSceneMode;
__interface DELPHIINTERFACE IVectorView_1__CaptureSceneMode;
typedef System::DelphiInterface<IVectorView_1__CaptureSceneMode> _di_IVectorView_1__CaptureSceneMode;
__interface DELPHIINTERFACE ISceneModeControl;
typedef System::DelphiInterface<ISceneModeControl> _di_ISceneModeControl;
__interface DELPHIINTERFACE ITorchControl;
typedef System::DelphiInterface<ITorchControl> _di_ITorchControl;
__interface DELPHIINTERFACE IFlashControl;
typedef System::DelphiInterface<IFlashControl> _di_IFlashControl;
__interface DELPHIINTERFACE IFlashControl2;
typedef System::DelphiInterface<IFlashControl2> _di_IFlashControl2;
__interface DELPHIINTERFACE IExposureCompensationControl;
typedef System::DelphiInterface<IExposureCompensationControl> _di_IExposureCompensationControl;
__interface DELPHIINTERFACE IIterator_1__IsoSpeedPreset_Base;
typedef System::DelphiInterface<IIterator_1__IsoSpeedPreset_Base> _di_IIterator_1__IsoSpeedPreset_Base;
__interface DELPHIINTERFACE IIterator_1__IsoSpeedPreset;
typedef System::DelphiInterface<IIterator_1__IsoSpeedPreset> _di_IIterator_1__IsoSpeedPreset;
__interface DELPHIINTERFACE IIterable_1__IsoSpeedPreset_Base;
typedef System::DelphiInterface<IIterable_1__IsoSpeedPreset_Base> _di_IIterable_1__IsoSpeedPreset_Base;
__interface DELPHIINTERFACE IIterable_1__IsoSpeedPreset;
typedef System::DelphiInterface<IIterable_1__IsoSpeedPreset> _di_IIterable_1__IsoSpeedPreset;
__interface DELPHIINTERFACE IVectorView_1__IsoSpeedPreset;
typedef System::DelphiInterface<IVectorView_1__IsoSpeedPreset> _di_IVectorView_1__IsoSpeedPreset;
__interface DELPHIINTERFACE IIsoSpeedControl;
typedef System::DelphiInterface<IIsoSpeedControl> _di_IIsoSpeedControl;
__interface DELPHIINTERFACE IIsoSpeedControl2;
typedef System::DelphiInterface<IIsoSpeedControl2> _di_IIsoSpeedControl2;
__interface DELPHIINTERFACE IWhiteBalanceControl;
typedef System::DelphiInterface<IWhiteBalanceControl> _di_IWhiteBalanceControl;
__interface DELPHIINTERFACE IExposureControl;
typedef System::DelphiInterface<IExposureControl> _di_IExposureControl;
__interface DELPHIINTERFACE IZoomSettings;
typedef System::DelphiInterface<IZoomSettings> _di_IZoomSettings;
__interface DELPHIINTERFACE IZoomControl;
typedef System::DelphiInterface<IZoomControl> _di_IZoomControl;
__interface DELPHIINTERFACE IIterator_1__ZoomTransitionMode_Base;
typedef System::DelphiInterface<IIterator_1__ZoomTransitionMode_Base> _di_IIterator_1__ZoomTransitionMode_Base;
__interface DELPHIINTERFACE IIterator_1__ZoomTransitionMode;
typedef System::DelphiInterface<IIterator_1__ZoomTransitionMode> _di_IIterator_1__ZoomTransitionMode;
__interface DELPHIINTERFACE IIterable_1__ZoomTransitionMode_Base;
typedef System::DelphiInterface<IIterable_1__ZoomTransitionMode_Base> _di_IIterable_1__ZoomTransitionMode_Base;
__interface DELPHIINTERFACE IIterable_1__ZoomTransitionMode;
typedef System::DelphiInterface<IIterable_1__ZoomTransitionMode> _di_IIterable_1__ZoomTransitionMode;
__interface DELPHIINTERFACE IVectorView_1__ZoomTransitionMode;
typedef System::DelphiInterface<IVectorView_1__ZoomTransitionMode> _di_IVectorView_1__ZoomTransitionMode;
__interface DELPHIINTERFACE IZoomControl2;
typedef System::DelphiInterface<IZoomControl2> _di_IZoomControl2;
__interface DELPHIINTERFACE IReference_1__ManualFocusDistance;
typedef System::DelphiInterface<IReference_1__ManualFocusDistance> _di_IReference_1__ManualFocusDistance;
__interface DELPHIINTERFACE IFocusSettings;
typedef System::DelphiInterface<IFocusSettings> _di_IFocusSettings;
__interface DELPHIINTERFACE IIterator_1__FocusPreset_Base;
typedef System::DelphiInterface<IIterator_1__FocusPreset_Base> _di_IIterator_1__FocusPreset_Base;
__interface DELPHIINTERFACE IIterator_1__FocusPreset;
typedef System::DelphiInterface<IIterator_1__FocusPreset> _di_IIterator_1__FocusPreset;
__interface DELPHIINTERFACE IIterable_1__FocusPreset_Base;
typedef System::DelphiInterface<IIterable_1__FocusPreset_Base> _di_IIterable_1__FocusPreset_Base;
__interface DELPHIINTERFACE IIterable_1__FocusPreset;
typedef System::DelphiInterface<IIterable_1__FocusPreset> _di_IIterable_1__FocusPreset;
__interface DELPHIINTERFACE IVectorView_1__FocusPreset;
typedef System::DelphiInterface<IVectorView_1__FocusPreset> _di_IVectorView_1__FocusPreset;
__interface DELPHIINTERFACE IFocusControl;
typedef System::DelphiInterface<IFocusControl> _di_IFocusControl;
__interface DELPHIINTERFACE IIterator_1__FocusMode_Base;
typedef System::DelphiInterface<IIterator_1__FocusMode_Base> _di_IIterator_1__FocusMode_Base;
__interface DELPHIINTERFACE IIterator_1__FocusMode;
typedef System::DelphiInterface<IIterator_1__FocusMode> _di_IIterator_1__FocusMode;
__interface DELPHIINTERFACE IIterable_1__FocusMode_Base;
typedef System::DelphiInterface<IIterable_1__FocusMode_Base> _di_IIterable_1__FocusMode_Base;
__interface DELPHIINTERFACE IIterable_1__FocusMode;
typedef System::DelphiInterface<IIterable_1__FocusMode> _di_IIterable_1__FocusMode;
__interface DELPHIINTERFACE IVectorView_1__FocusMode;
typedef System::DelphiInterface<IVectorView_1__FocusMode> _di_IVectorView_1__FocusMode;
__interface DELPHIINTERFACE IIterator_1__ManualFocusDistance_Base;
typedef System::DelphiInterface<IIterator_1__ManualFocusDistance_Base> _di_IIterator_1__ManualFocusDistance_Base;
__interface DELPHIINTERFACE IIterator_1__ManualFocusDistance;
typedef System::DelphiInterface<IIterator_1__ManualFocusDistance> _di_IIterator_1__ManualFocusDistance;
__interface DELPHIINTERFACE IIterable_1__ManualFocusDistance_Base;
typedef System::DelphiInterface<IIterable_1__ManualFocusDistance_Base> _di_IIterable_1__ManualFocusDistance_Base;
__interface DELPHIINTERFACE IIterable_1__ManualFocusDistance;
typedef System::DelphiInterface<IIterable_1__ManualFocusDistance> _di_IIterable_1__ManualFocusDistance;
__interface DELPHIINTERFACE IVectorView_1__ManualFocusDistance;
typedef System::DelphiInterface<IVectorView_1__ManualFocusDistance> _di_IVectorView_1__ManualFocusDistance;
__interface DELPHIINTERFACE IIterator_1__AutoFocusRange_Base;
typedef System::DelphiInterface<IIterator_1__AutoFocusRange_Base> _di_IIterator_1__AutoFocusRange_Base;
__interface DELPHIINTERFACE IIterator_1__AutoFocusRange;
typedef System::DelphiInterface<IIterator_1__AutoFocusRange> _di_IIterator_1__AutoFocusRange;
__interface DELPHIINTERFACE IIterable_1__AutoFocusRange_Base;
typedef System::DelphiInterface<IIterable_1__AutoFocusRange_Base> _di_IIterable_1__AutoFocusRange_Base;
__interface DELPHIINTERFACE IIterable_1__AutoFocusRange;
typedef System::DelphiInterface<IIterable_1__AutoFocusRange> _di_IIterable_1__AutoFocusRange;
__interface DELPHIINTERFACE IVectorView_1__AutoFocusRange;
typedef System::DelphiInterface<IVectorView_1__AutoFocusRange> _di_IVectorView_1__AutoFocusRange;
__interface DELPHIINTERFACE IFocusControl2;
typedef System::DelphiInterface<IFocusControl2> _di_IFocusControl2;
__interface DELPHIINTERFACE IRegionOfInterest;
typedef System::DelphiInterface<IRegionOfInterest> _di_IRegionOfInterest;
__interface DELPHIINTERFACE IRegionOfInterest2;
typedef System::DelphiInterface<IRegionOfInterest2> _di_IRegionOfInterest2;
__interface DELPHIINTERFACE IIterator_1__IRegionOfInterest_Base;
typedef System::DelphiInterface<IIterator_1__IRegionOfInterest_Base> _di_IIterator_1__IRegionOfInterest_Base;
__interface DELPHIINTERFACE IIterator_1__IRegionOfInterest;
typedef System::DelphiInterface<IIterator_1__IRegionOfInterest> _di_IIterator_1__IRegionOfInterest;
__interface DELPHIINTERFACE IIterable_1__IRegionOfInterest_Base;
typedef System::DelphiInterface<IIterable_1__IRegionOfInterest_Base> _di_IIterable_1__IRegionOfInterest_Base;
__interface DELPHIINTERFACE IIterable_1__IRegionOfInterest;
typedef System::DelphiInterface<IIterable_1__IRegionOfInterest> _di_IIterable_1__IRegionOfInterest;
__interface DELPHIINTERFACE IRegionsOfInterestControl;
typedef System::DelphiInterface<IRegionsOfInterestControl> _di_IRegionsOfInterestControl;
__interface DELPHIINTERFACE IExposurePriorityVideoControl;
typedef System::DelphiInterface<IExposurePriorityVideoControl> _di_IExposurePriorityVideoControl;
__interface DELPHIINTERFACE IIterator_1__HdrVideoMode_Base;
typedef System::DelphiInterface<IIterator_1__HdrVideoMode_Base> _di_IIterator_1__HdrVideoMode_Base;
__interface DELPHIINTERFACE IIterator_1__HdrVideoMode;
typedef System::DelphiInterface<IIterator_1__HdrVideoMode> _di_IIterator_1__HdrVideoMode;
__interface DELPHIINTERFACE IIterable_1__HdrVideoMode_Base;
typedef System::DelphiInterface<IIterable_1__HdrVideoMode_Base> _di_IIterable_1__HdrVideoMode_Base;
__interface DELPHIINTERFACE IIterable_1__HdrVideoMode;
typedef System::DelphiInterface<IIterable_1__HdrVideoMode> _di_IIterable_1__HdrVideoMode;
__interface DELPHIINTERFACE IVectorView_1__HdrVideoMode;
typedef System::DelphiInterface<IVectorView_1__HdrVideoMode> _di_IVectorView_1__HdrVideoMode;
__interface DELPHIINTERFACE IHdrVideoControl;
typedef System::DelphiInterface<IHdrVideoControl> _di_IHdrVideoControl;
__interface DELPHIINTERFACE IAdvancedPhotoCaptureSettings;
typedef System::DelphiInterface<IAdvancedPhotoCaptureSettings> _di_IAdvancedPhotoCaptureSettings;
__interface DELPHIINTERFACE IIterator_1__AdvancedPhotoMode_Base;
typedef System::DelphiInterface<IIterator_1__AdvancedPhotoMode_Base> _di_IIterator_1__AdvancedPhotoMode_Base;
__interface DELPHIINTERFACE IIterator_1__AdvancedPhotoMode;
typedef System::DelphiInterface<IIterator_1__AdvancedPhotoMode> _di_IIterator_1__AdvancedPhotoMode;
__interface DELPHIINTERFACE IIterable_1__AdvancedPhotoMode_Base;
typedef System::DelphiInterface<IIterable_1__AdvancedPhotoMode_Base> _di_IIterable_1__AdvancedPhotoMode_Base;
__interface DELPHIINTERFACE IIterable_1__AdvancedPhotoMode;
typedef System::DelphiInterface<IIterable_1__AdvancedPhotoMode> _di_IIterable_1__AdvancedPhotoMode;
__interface DELPHIINTERFACE IVectorView_1__AdvancedPhotoMode;
typedef System::DelphiInterface<IVectorView_1__AdvancedPhotoMode> _di_IVectorView_1__AdvancedPhotoMode;
__interface DELPHIINTERFACE IAdvancedPhotoControl;
typedef System::DelphiInterface<IAdvancedPhotoControl> _di_IAdvancedPhotoControl;
__interface DELPHIINTERFACE IIterator_1__OpticalImageStabilizationMode_Base;
typedef System::DelphiInterface<IIterator_1__OpticalImageStabilizationMode_Base> _di_IIterator_1__OpticalImageStabilizationMode_Base;
__interface DELPHIINTERFACE IIterator_1__OpticalImageStabilizationMode;
typedef System::DelphiInterface<IIterator_1__OpticalImageStabilizationMode> _di_IIterator_1__OpticalImageStabilizationMode;
__interface DELPHIINTERFACE IIterable_1__OpticalImageStabilizationMode_Base;
typedef System::DelphiInterface<IIterable_1__OpticalImageStabilizationMode_Base> _di_IIterable_1__OpticalImageStabilizationMode_Base;
__interface DELPHIINTERFACE IIterable_1__OpticalImageStabilizationMode;
typedef System::DelphiInterface<IIterable_1__OpticalImageStabilizationMode> _di_IIterable_1__OpticalImageStabilizationMode;
__interface DELPHIINTERFACE IVectorView_1__OpticalImageStabilizationMode;
typedef System::DelphiInterface<IVectorView_1__OpticalImageStabilizationMode> _di_IVectorView_1__OpticalImageStabilizationMode;
__interface DELPHIINTERFACE IOpticalImageStabilizationControl;
typedef System::DelphiInterface<IOpticalImageStabilizationControl> _di_IOpticalImageStabilizationControl;
__interface DELPHIINTERFACE ILowLagPhotoSequenceControl;
typedef System::DelphiInterface<ILowLagPhotoSequenceControl> _di_ILowLagPhotoSequenceControl;
__interface DELPHIINTERFACE ILowLagPhotoControl;
typedef System::DelphiInterface<ILowLagPhotoControl> _di_ILowLagPhotoControl;
__interface DELPHIINTERFACE IAdvancedVideoCaptureDeviceController2;
typedef System::DelphiInterface<IAdvancedVideoCaptureDeviceController2> _di_IAdvancedVideoCaptureDeviceController2;
__interface DELPHIINTERFACE Core_IFrameExposureCapabilities;
typedef System::DelphiInterface<Core_IFrameExposureCapabilities> _di_Core_IFrameExposureCapabilities;
__interface DELPHIINTERFACE Core_IFrameExposureCompensationCapabilities;
typedef System::DelphiInterface<Core_IFrameExposureCompensationCapabilities> _di_Core_IFrameExposureCompensationCapabilities;
__interface DELPHIINTERFACE Core_IFrameIsoSpeedCapabilities;
typedef System::DelphiInterface<Core_IFrameIsoSpeedCapabilities> _di_Core_IFrameIsoSpeedCapabilities;
__interface DELPHIINTERFACE Core_IFrameFocusCapabilities;
typedef System::DelphiInterface<Core_IFrameFocusCapabilities> _di_Core_IFrameFocusCapabilities;
__interface DELPHIINTERFACE Core_IFrameControlCapabilities;
typedef System::DelphiInterface<Core_IFrameControlCapabilities> _di_Core_IFrameControlCapabilities;
__interface DELPHIINTERFACE Core_IFrameExposureControl;
typedef System::DelphiInterface<Core_IFrameExposureControl> _di_Core_IFrameExposureControl;
__interface DELPHIINTERFACE Core_IFrameExposureCompensationControl;
typedef System::DelphiInterface<Core_IFrameExposureCompensationControl> _di_Core_IFrameExposureCompensationControl;
__interface DELPHIINTERFACE Core_IFrameIsoSpeedControl;
typedef System::DelphiInterface<Core_IFrameIsoSpeedControl> _di_Core_IFrameIsoSpeedControl;
__interface DELPHIINTERFACE Core_IFrameFocusControl;
typedef System::DelphiInterface<Core_IFrameFocusControl> _di_Core_IFrameFocusControl;
__interface DELPHIINTERFACE Core_IFrameController;
typedef System::DelphiInterface<Core_IFrameController> _di_Core_IFrameController;
__interface DELPHIINTERFACE IIterator_1__Core_IFrameController_Base;
typedef System::DelphiInterface<IIterator_1__Core_IFrameController_Base> _di_IIterator_1__Core_IFrameController_Base;
__interface DELPHIINTERFACE IIterator_1__Core_IFrameController;
typedef System::DelphiInterface<IIterator_1__Core_IFrameController> _di_IIterator_1__Core_IFrameController;
__interface DELPHIINTERFACE IIterable_1__Core_IFrameController_Base;
typedef System::DelphiInterface<IIterable_1__Core_IFrameController_Base> _di_IIterable_1__Core_IFrameController_Base;
__interface DELPHIINTERFACE IIterable_1__Core_IFrameController;
typedef System::DelphiInterface<IIterable_1__Core_IFrameController> _di_IIterable_1__Core_IFrameController;
__interface DELPHIINTERFACE IVectorView_1__Core_IFrameController;
typedef System::DelphiInterface<IVectorView_1__Core_IFrameController> _di_IVectorView_1__Core_IFrameController;
__interface DELPHIINTERFACE IVector_1__Core_IFrameController;
typedef System::DelphiInterface<IVector_1__Core_IFrameController> _di_IVector_1__Core_IFrameController;
__interface DELPHIINTERFACE Core_IVariablePhotoSequenceController;
typedef System::DelphiInterface<Core_IVariablePhotoSequenceController> _di_Core_IVariablePhotoSequenceController;
__interface DELPHIINTERFACE IPhotoConfirmationControl;
typedef System::DelphiInterface<IPhotoConfirmationControl> _di_IPhotoConfirmationControl;
__interface DELPHIINTERFACE IAdvancedVideoCaptureDeviceController3;
typedef System::DelphiInterface<IAdvancedVideoCaptureDeviceController3> _di_IAdvancedVideoCaptureDeviceController3;
__interface DELPHIINTERFACE IAdvancedVideoCaptureDeviceController4;
typedef System::DelphiInterface<IAdvancedVideoCaptureDeviceController4> _di_IAdvancedVideoCaptureDeviceController4;
__interface DELPHIINTERFACE IVideoDeviceControllerGetDevicePropertyResult;
typedef System::DelphiInterface<IVideoDeviceControllerGetDevicePropertyResult> _di_IVideoDeviceControllerGetDevicePropertyResult;
__interface DELPHIINTERFACE IAdvancedVideoCaptureDeviceController5;
typedef System::DelphiInterface<IAdvancedVideoCaptureDeviceController5> _di_IAdvancedVideoCaptureDeviceController5;
__interface DELPHIINTERFACE IAdvancedVideoCaptureDeviceController;
typedef System::DelphiInterface<IAdvancedVideoCaptureDeviceController> _di_IAdvancedVideoCaptureDeviceController;
__interface DELPHIINTERFACE Core_IFrameFlashCapabilities;
typedef System::DelphiInterface<Core_IFrameFlashCapabilities> _di_Core_IFrameFlashCapabilities;
__interface DELPHIINTERFACE Core_IFrameControlCapabilities2;
typedef System::DelphiInterface<Core_IFrameControlCapabilities2> _di_Core_IFrameControlCapabilities2;
__interface DELPHIINTERFACE Core_IFrameFlashControl;
typedef System::DelphiInterface<Core_IFrameFlashControl> _di_Core_IFrameFlashControl;
__interface DELPHIINTERFACE Core_IFrameController2;
typedef System::DelphiInterface<Core_IFrameController2> _di_Core_IFrameController2;
__interface DELPHIINTERFACE Core_ICameraIntrinsicsFactory;
typedef System::DelphiInterface<Core_ICameraIntrinsicsFactory> _di_Core_ICameraIntrinsicsFactory;
__interface DELPHIINTERFACE Core_ICameraIntrinsics2;
typedef System::DelphiInterface<Core_ICameraIntrinsics2> _di_Core_ICameraIntrinsics2;
__interface DELPHIINTERFACE IDialRequestedEventArgs;
typedef System::DelphiInterface<IDialRequestedEventArgs> _di_IDialRequestedEventArgs;
__interface DELPHIINTERFACE IRedialRequestedEventArgs;
typedef System::DelphiInterface<IRedialRequestedEventArgs> _di_IRedialRequestedEventArgs;
__interface DELPHIINTERFACE IKeypadPressedEventArgs;
typedef System::DelphiInterface<IKeypadPressedEventArgs> _di_IKeypadPressedEventArgs;
__interface DELPHIINTERFACE DialRequestedEventHandler;
typedef System::DelphiInterface<DialRequestedEventHandler> _di_DialRequestedEventHandler;
__interface DELPHIINTERFACE RedialRequestedEventHandler;
typedef System::DelphiInterface<RedialRequestedEventHandler> _di_RedialRequestedEventHandler;
__interface DELPHIINTERFACE KeypadPressedEventHandler;
typedef System::DelphiInterface<KeypadPressedEventHandler> _di_KeypadPressedEventHandler;
__interface DELPHIINTERFACE ICallControl;
typedef System::DelphiInterface<ICallControl> _di_ICallControl;
__interface DELPHIINTERFACE CallControlEventHandler;
typedef System::DelphiInterface<CallControlEventHandler> _di_CallControlEventHandler;
__interface DELPHIINTERFACE ICallControlStatics;
typedef System::DelphiInterface<ICallControlStatics> _di_ICallControlStatics;
class DELPHICLASS TAudioDeviceModulesManager;
class DELPHICLASS TZoomSettings;
class DELPHICLASS TFocusSettings;
class DELPHICLASS TRegionOfInterest;
class DELPHICLASS TAdvancedPhotoCaptureSettings;
class DELPHICLASS TCore_FrameController;
class DELPHICLASS TCallControl;
//-- type declarations -------------------------------------------------------
typedef _di_Core_ICameraIntrinsics *PCore_ICameraIntrinsics;

typedef _di_IMediaDeviceController *PIMediaDeviceController;

typedef _di_IAudioDeviceController *PIAudioDeviceController;

typedef _di_IMediaDeviceControlCapabilities *PIMediaDeviceControlCapabilities;

typedef _di_IMediaDeviceControl *PIMediaDeviceControl;

typedef _di_IVideoDeviceController *PIVideoDeviceController;

typedef _di_IReference_1__CaptureSceneMode *PIReference_1__CaptureSceneMode;

typedef _di_Core_IDepthCorrelatedCoordinateMapper *PCore_IDepthCorrelatedCoordinateMapper;

typedef _di_IReference_1__MediaCaptureFocusState *PIReference_1__MediaCaptureFocusState;

typedef _di_IModuleCommandResult *PIModuleCommandResult;

typedef _di_AsyncOperationCompletedHandler_1__IModuleCommandResult *PAsyncOperationCompletedHandler_1__IModuleCommandResult;

typedef _di_IAsyncOperation_1__IModuleCommandResult *PIAsyncOperation_1__IModuleCommandResult;

typedef _di_IAudioDeviceModule *PIAudioDeviceModule;

typedef _di_IAudioDeviceModuleNotificationEventArgs *PIAudioDeviceModuleNotificationEventArgs;

typedef _di_TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs *PTypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs;

typedef _di_IIterator_1__IAudioDeviceModule *PIIterator_1__IAudioDeviceModule;

typedef _di_IIterable_1__IAudioDeviceModule *PIIterable_1__IAudioDeviceModule;

typedef _di_IVectorView_1__IAudioDeviceModule *PIVectorView_1__IAudioDeviceModule;

typedef _di_IAudioDeviceModulesManager *PIAudioDeviceModulesManager;

typedef _di_IAudioDeviceModulesManagerFactory *PIAudioDeviceModulesManagerFactory;

typedef _di_IIterator_1__CaptureSceneMode *PIIterator_1__CaptureSceneMode;

typedef _di_IIterable_1__CaptureSceneMode *PIIterable_1__CaptureSceneMode;

typedef _di_IVectorView_1__CaptureSceneMode *PIVectorView_1__CaptureSceneMode;

typedef _di_ISceneModeControl *PISceneModeControl;

typedef _di_ITorchControl *PITorchControl;

typedef _di_IFlashControl *PIFlashControl;

typedef _di_IFlashControl2 *PIFlashControl2;

typedef _di_IExposureCompensationControl *PIExposureCompensationControl;

typedef _di_IIterator_1__IsoSpeedPreset *PIIterator_1__IsoSpeedPreset;

typedef _di_IIterable_1__IsoSpeedPreset *PIIterable_1__IsoSpeedPreset;

typedef _di_IVectorView_1__IsoSpeedPreset *PIVectorView_1__IsoSpeedPreset;

typedef _di_IIsoSpeedControl *PIIsoSpeedControl;

typedef _di_IIsoSpeedControl2 *PIIsoSpeedControl2;

typedef _di_IWhiteBalanceControl *PIWhiteBalanceControl;

typedef _di_IExposureControl *PIExposureControl;

typedef _di_IZoomSettings *PIZoomSettings;

typedef _di_IZoomControl *PIZoomControl;

typedef _di_IIterator_1__ZoomTransitionMode *PIIterator_1__ZoomTransitionMode;

typedef _di_IIterable_1__ZoomTransitionMode *PIIterable_1__ZoomTransitionMode;

typedef _di_IVectorView_1__ZoomTransitionMode *PIVectorView_1__ZoomTransitionMode;

typedef _di_IZoomControl2 *PIZoomControl2;

typedef _di_IReference_1__ManualFocusDistance *PIReference_1__ManualFocusDistance;

typedef _di_IFocusSettings *PIFocusSettings;

typedef _di_IIterator_1__FocusPreset *PIIterator_1__FocusPreset;

typedef _di_IIterable_1__FocusPreset *PIIterable_1__FocusPreset;

typedef _di_IVectorView_1__FocusPreset *PIVectorView_1__FocusPreset;

typedef _di_IFocusControl *PIFocusControl;

typedef _di_IIterator_1__FocusMode *PIIterator_1__FocusMode;

typedef _di_IIterable_1__FocusMode *PIIterable_1__FocusMode;

typedef _di_IVectorView_1__FocusMode *PIVectorView_1__FocusMode;

typedef _di_IIterator_1__ManualFocusDistance *PIIterator_1__ManualFocusDistance;

typedef _di_IIterable_1__ManualFocusDistance *PIIterable_1__ManualFocusDistance;

typedef _di_IVectorView_1__ManualFocusDistance *PIVectorView_1__ManualFocusDistance;

typedef _di_IIterator_1__AutoFocusRange *PIIterator_1__AutoFocusRange;

typedef _di_IIterable_1__AutoFocusRange *PIIterable_1__AutoFocusRange;

typedef _di_IVectorView_1__AutoFocusRange *PIVectorView_1__AutoFocusRange;

typedef _di_IFocusControl2 *PIFocusControl2;

typedef _di_IRegionOfInterest *PIRegionOfInterest;

typedef _di_IRegionOfInterest2 *PIRegionOfInterest2;

typedef _di_IIterator_1__IRegionOfInterest *PIIterator_1__IRegionOfInterest;

typedef _di_IIterable_1__IRegionOfInterest *PIIterable_1__IRegionOfInterest;

typedef _di_IRegionsOfInterestControl *PIRegionsOfInterestControl;

typedef _di_IExposurePriorityVideoControl *PIExposurePriorityVideoControl;

typedef _di_IIterator_1__HdrVideoMode *PIIterator_1__HdrVideoMode;

typedef _di_IIterable_1__HdrVideoMode *PIIterable_1__HdrVideoMode;

typedef _di_IVectorView_1__HdrVideoMode *PIVectorView_1__HdrVideoMode;

typedef _di_IHdrVideoControl *PIHdrVideoControl;

typedef _di_IAdvancedPhotoCaptureSettings *PIAdvancedPhotoCaptureSettings;

typedef _di_IIterator_1__AdvancedPhotoMode *PIIterator_1__AdvancedPhotoMode;

typedef _di_IIterable_1__AdvancedPhotoMode *PIIterable_1__AdvancedPhotoMode;

typedef _di_IVectorView_1__AdvancedPhotoMode *PIVectorView_1__AdvancedPhotoMode;

typedef _di_IAdvancedPhotoControl *PIAdvancedPhotoControl;

typedef _di_IIterator_1__OpticalImageStabilizationMode *PIIterator_1__OpticalImageStabilizationMode;

typedef _di_IIterable_1__OpticalImageStabilizationMode *PIIterable_1__OpticalImageStabilizationMode;

typedef _di_IVectorView_1__OpticalImageStabilizationMode *PIVectorView_1__OpticalImageStabilizationMode;

typedef _di_IOpticalImageStabilizationControl *PIOpticalImageStabilizationControl;

typedef _di_ILowLagPhotoSequenceControl *PILowLagPhotoSequenceControl;

typedef _di_ILowLagPhotoControl *PILowLagPhotoControl;

typedef _di_IAdvancedVideoCaptureDeviceController2 *PIAdvancedVideoCaptureDeviceController2;

typedef _di_Core_IFrameExposureCapabilities *PCore_IFrameExposureCapabilities;

typedef _di_Core_IFrameExposureCompensationCapabilities *PCore_IFrameExposureCompensationCapabilities;

typedef _di_Core_IFrameIsoSpeedCapabilities *PCore_IFrameIsoSpeedCapabilities;

typedef _di_Core_IFrameFocusCapabilities *PCore_IFrameFocusCapabilities;

typedef _di_Core_IFrameControlCapabilities *PCore_IFrameControlCapabilities;

typedef _di_Core_IFrameExposureControl *PCore_IFrameExposureControl;

typedef _di_Core_IFrameExposureCompensationControl *PCore_IFrameExposureCompensationControl;

typedef _di_Core_IFrameIsoSpeedControl *PCore_IFrameIsoSpeedControl;

typedef _di_Core_IFrameFocusControl *PCore_IFrameFocusControl;

typedef _di_Core_IFrameController *PCore_IFrameController;

typedef _di_IIterator_1__Core_IFrameController *PIIterator_1__Core_IFrameController;

typedef _di_IIterable_1__Core_IFrameController *PIIterable_1__Core_IFrameController;

typedef _di_IVectorView_1__Core_IFrameController *PIVectorView_1__Core_IFrameController;

typedef _di_IVector_1__Core_IFrameController *PIVector_1__Core_IFrameController;

typedef _di_Core_IVariablePhotoSequenceController *PCore_IVariablePhotoSequenceController;

typedef _di_IPhotoConfirmationControl *PIPhotoConfirmationControl;

typedef _di_IAdvancedVideoCaptureDeviceController3 *PIAdvancedVideoCaptureDeviceController3;

typedef _di_IAdvancedVideoCaptureDeviceController4 *PIAdvancedVideoCaptureDeviceController4;

typedef _di_IVideoDeviceControllerGetDevicePropertyResult *PIVideoDeviceControllerGetDevicePropertyResult;

typedef _di_IAdvancedVideoCaptureDeviceController5 *PIAdvancedVideoCaptureDeviceController5;

typedef _di_IAdvancedVideoCaptureDeviceController *PIAdvancedVideoCaptureDeviceController;

typedef _di_Core_IFrameFlashCapabilities *PCore_IFrameFlashCapabilities;

typedef _di_Core_IFrameControlCapabilities2 *PCore_IFrameControlCapabilities2;

typedef _di_Core_IFrameFlashControl *PCore_IFrameFlashControl;

typedef _di_Core_IFrameController2 *PCore_IFrameController2;

typedef _di_Core_ICameraIntrinsicsFactory *PCore_ICameraIntrinsicsFactory;

typedef _di_Core_ICameraIntrinsics2 *PCore_ICameraIntrinsics2;

typedef _di_IDialRequestedEventArgs *PIDialRequestedEventArgs;

typedef _di_IRedialRequestedEventArgs *PIRedialRequestedEventArgs;

typedef _di_IKeypadPressedEventArgs *PIKeypadPressedEventArgs;

typedef _di_DialRequestedEventHandler *PDialRequestedEventHandler;

typedef _di_RedialRequestedEventHandler *PRedialRequestedEventHandler;

typedef _di_KeypadPressedEventHandler *PKeypadPressedEventHandler;

typedef _di_ICallControl *PICallControl;

typedef _di_CallControlEventHandler *PCallControlEventHandler;

typedef _di_ICallControlStatics *PICallControlStatics;

__interface  INTERFACE_UUID("{0AA6ED32-6589-49DA-AFDE-594270CA0AAC}") Core_ICameraIntrinsics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_FocalLength(Winapi::Foundation::Types::Numerics_Vector2 &__get_FocalLength_result) = 0 ;
	virtual HRESULT __safecall get_PrincipalPoint(Winapi::Foundation::Types::Numerics_Vector2 &__get_PrincipalPoint_result) = 0 ;
	virtual HRESULT __safecall get_RadialDistortion(Winapi::Commontypes::Numerics_Vector3 &__get_RadialDistortion_result) = 0 ;
	virtual HRESULT __safecall get_TangentialDistortion(Winapi::Foundation::Types::Numerics_Vector2 &__get_TangentialDistortion_result) = 0 ;
	virtual HRESULT __safecall get_ImageWidth(unsigned &__get_ImageWidth_result) = 0 ;
	virtual HRESULT __safecall get_ImageHeight(unsigned &__get_ImageHeight_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall ProjectOntoFrame(Winapi::Commontypes::Numerics_Vector3 coordinate, System::Types::TPointF &__ProjectOntoFrame_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall ProjectOntoFrame(const Winapi::Commontypes::Numerics_Vector3 &coordinate, System::Types::TPointF &__ProjectOntoFrame_result) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall UnprojectAtUnitDepth(System::Types::TPointF pixelCoordinate, Winapi::Foundation::Types::Numerics_Vector2 &__UnprojectAtUnitDepth_result) = 0 ;
	virtual HRESULT __safecall ProjectManyOntoFrame(unsigned coordinatesSize, Winapi::Commontypes::PNumerics_Vector3 coordinates, /* out */ System::Types::TPointF &results) = 0 ;
	virtual HRESULT __safecall UnprojectPixelsAtUnitDepth(unsigned pixelCoordinatesSize, System::Types::PPointF pixelCoordinates, /* out */ Winapi::Foundation::Types::Numerics_Vector2 &results) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Vector2 _scw_get_FocalLength() { Winapi::Foundation::Types::Numerics_Vector2 __r; HRESULT __hr = get_FocalLength(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Vector2 FocalLength = {read=_scw_get_FocalLength};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ImageHeight() { unsigned __r; HRESULT __hr = get_ImageHeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ImageHeight = {read=_scw_get_ImageHeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ImageWidth() { unsigned __r; HRESULT __hr = get_ImageWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ImageWidth = {read=_scw_get_ImageWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Vector2 _scw_get_PrincipalPoint() { Winapi::Foundation::Types::Numerics_Vector2 __r; HRESULT __hr = get_PrincipalPoint(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Vector2 PrincipalPoint = {read=_scw_get_PrincipalPoint};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Numerics_Vector3 _scw_get_RadialDistortion() { Winapi::Commontypes::Numerics_Vector3 __r; HRESULT __hr = get_RadialDistortion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Numerics_Vector3 RadialDistortion = {read=_scw_get_RadialDistortion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Vector2 _scw_get_TangentialDistortion() { Winapi::Foundation::Types::Numerics_Vector2 __r; HRESULT __hr = get_TangentialDistortion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Vector2 TangentialDistortion = {read=_scw_get_TangentialDistortion};
};

__interface  INTERFACE_UUID("{F6F8F5CE-209A-48FB-86FC-D44578F317E6}") IMediaDeviceController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAvailableMediaStreamProperties(Winapi::Commontypes::Capture_MediaStreamType mediaStreamType, Winapi::Media::Mediaproperties::_di_IVectorView_1__IMediaEncodingProperties &__GetAvailableMediaStreamProperties_result) = 0 ;
	virtual HRESULT __safecall GetMediaStreamProperties(Winapi::Commontypes::Capture_MediaStreamType mediaStreamType, Winapi::Media::Mediaproperties::_di_IMediaEncodingProperties &__GetMediaStreamProperties_result) = 0 ;
	virtual HRESULT __safecall SetMediaStreamPropertiesAsync(Winapi::Commontypes::Capture_MediaStreamType mediaStreamType, Winapi::Media::Mediaproperties::_di_IMediaEncodingProperties mediaEncodingProperties, Winapi::Commontypes::_di_IAsyncAction &__SetMediaStreamPropertiesAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{EDD4A388-79C7-4F7C-90E8-EF934B21580A}") IAudioDeviceController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Muted(bool value) = 0 ;
	virtual HRESULT __safecall get_Muted(bool &__get_Muted_result) = 0 ;
	virtual HRESULT __safecall put_VolumePercent(float value) = 0 ;
	virtual HRESULT __safecall get_VolumePercent(float &__get_VolumePercent_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Muted() { bool __r; HRESULT __hr = get_Muted(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Muted = {read=_scw_get_Muted, write=put_Muted};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_VolumePercent() { float __r; HRESULT __hr = get_VolumePercent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float VolumePercent = {read=_scw_get_VolumePercent, write=put_VolumePercent};
};

__interface  INTERFACE_UUID("{23005816-EB85-43E2-B92B-8240D5EE70EC}") IMediaDeviceControlCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(double &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(double &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(double &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Default(double &__get_Default_result) = 0 ;
	virtual HRESULT __safecall get_AutoModeSupported(bool &__get_AutoModeSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoModeSupported() { bool __r; HRESULT __hr = get_AutoModeSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoModeSupported = {read=_scw_get_AutoModeSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Default() { double __r; HRESULT __hr = get_Default(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Default = {read=_scw_get_Default};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Max() { double __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Min() { double __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Step() { double __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{EFA8DFA9-6F75-4863-BA0B-583F3036B4DE}") IMediaDeviceControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Capabilities(_di_IMediaDeviceControlCapabilities &__get_Capabilities_result) = 0 ;
	virtual HRESULT __safecall TryGetValue(/* out */ double &value, bool &__TryGetValue_result) = 0 ;
	virtual HRESULT __safecall TrySetValue(double value, bool &__TrySetValue_result) = 0 ;
	virtual HRESULT __safecall TryGetAuto(/* out */ bool &value, bool &__TryGetAuto_result) = 0 ;
	virtual HRESULT __safecall TrySetAuto(bool value, bool &__TrySetAuto_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControlCapabilities _scw_get_Capabilities() { _di_IMediaDeviceControlCapabilities __r; HRESULT __hr = get_Capabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControlCapabilities Capabilities = {read=_scw_get_Capabilities};
};

__interface  INTERFACE_UUID("{99555575-2E2E-40B8-B6C7-F82D10013210}") IVideoDeviceController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Brightness(_di_IMediaDeviceControl &__get_Brightness_result) = 0 ;
	virtual HRESULT __safecall get_Contrast(_di_IMediaDeviceControl &__get_Contrast_result) = 0 ;
	virtual HRESULT __safecall get_Hue(_di_IMediaDeviceControl &__get_Hue_result) = 0 ;
	virtual HRESULT __safecall get_WhiteBalance(_di_IMediaDeviceControl &__get_WhiteBalance_result) = 0 ;
	virtual HRESULT __safecall get_BacklightCompensation(_di_IMediaDeviceControl &__get_BacklightCompensation_result) = 0 ;
	virtual HRESULT __safecall get_Pan(_di_IMediaDeviceControl &__get_Pan_result) = 0 ;
	virtual HRESULT __safecall get_Tilt(_di_IMediaDeviceControl &__get_Tilt_result) = 0 ;
	virtual HRESULT __safecall get_Zoom(_di_IMediaDeviceControl &__get_Zoom_result) = 0 ;
	virtual HRESULT __safecall get_Roll(_di_IMediaDeviceControl &__get_Roll_result) = 0 ;
	virtual HRESULT __safecall get_Exposure(_di_IMediaDeviceControl &__get_Exposure_result) = 0 ;
	virtual HRESULT __safecall get_Focus(_di_IMediaDeviceControl &__get_Focus_result) = 0 ;
	virtual HRESULT __safecall TrySetPowerlineFrequency(Winapi::Commontypes::Capture_PowerlineFrequency value, bool &__TrySetPowerlineFrequency_result) = 0 ;
	virtual HRESULT __safecall TryGetPowerlineFrequency(/* out */ Winapi::Commontypes::Capture_PowerlineFrequency &value, bool &__TryGetPowerlineFrequency_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_BacklightCompensation() { _di_IMediaDeviceControl __r; HRESULT __hr = get_BacklightCompensation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl BacklightCompensation = {read=_scw_get_BacklightCompensation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Brightness() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Brightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Brightness = {read=_scw_get_Brightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Contrast() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Contrast(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Contrast = {read=_scw_get_Contrast};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Exposure() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Exposure(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Exposure = {read=_scw_get_Exposure};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Focus() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Focus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Focus = {read=_scw_get_Focus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Hue() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Hue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Hue = {read=_scw_get_Hue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Pan() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Pan(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Pan = {read=_scw_get_Pan};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Roll() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Roll(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Roll = {read=_scw_get_Roll};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Tilt() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Tilt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Tilt = {read=_scw_get_Tilt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_WhiteBalance() { _di_IMediaDeviceControl __r; HRESULT __hr = get_WhiteBalance(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl WhiteBalance = {read=_scw_get_WhiteBalance};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaDeviceControl _scw_get_Zoom() { _di_IMediaDeviceControl __r; HRESULT __hr = get_Zoom(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaDeviceControl Zoom = {read=_scw_get_Zoom};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__CaptureSceneMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::CaptureSceneMode &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CaptureSceneMode _scw_get_Value() { Winapi::Commontypes::CaptureSceneMode __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CaptureSceneMode Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{F95D89FB-8AF0-4CB0-926D-696866E5046A}") Core_IDepthCorrelatedCoordinateMapper  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall UnprojectPoint(System::Types::TPointF sourcePoint, Winapi::Perception::_di_Spatial_ISpatialCoordinateSystem targetCoordinateSystem, Winapi::Commontypes::Numerics_Vector3 &__UnprojectPoint_result) = 0 ;
	virtual HRESULT __safecall UnprojectPoints(unsigned sourcePointsSize, System::Types::PPointF sourcePoints, unsigned targetCoordinateSystemSize, System::Types::PPointF targetCoordinateSystem, unsigned resultsSize, Winapi::Commontypes::PNumerics_Vector3 results) = 0 ;
	virtual HRESULT __safecall MapPoint(System::Types::TPointF sourcePoint, Winapi::Perception::_di_Spatial_ISpatialCoordinateSystem targetCoordinateSystem, _di_Core_ICameraIntrinsics targetCameraIntrinsics, System::Types::TPointF &__MapPoint_result) = 0 ;
	virtual HRESULT __safecall MapPoints(unsigned sourcePointsSize, System::Types::PPointF sourcePoints, unsigned targetCoordinateSystemSize, System::Types::PPointF targetCoordinateSystem, _di_Core_ICameraIntrinsics targetCameraIntrinsics, unsigned resultsSize, System::Types::PPointF results) = 0 ;
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__MediaCaptureFocusState  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::MediaCaptureFocusState &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaCaptureFocusState _scw_get_Value() { Winapi::Commontypes::MediaCaptureFocusState __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaCaptureFocusState Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{520D1EB4-1374-4C7D-B1E4-39DCDF3EAE4E}") IModuleCommandResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::SendCommandStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_Result(Winapi::Commontypes::_di_IBuffer &__get_Result_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Result() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Result(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Result = {read=_scw_get_Result};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SendCommandStatus _scw_get_Status() { Winapi::Commontypes::SendCommandStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SendCommandStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{CB786404-F2E8-5E0B-BF12-39E31483CFAE}") AsyncOperationCompletedHandler_1__IModuleCommandResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{AF62931E-6AE4-5655-9FDC-4E5F25C939DF}") AsyncOperationCompletedHandler_1__IModuleCommandResult  : public AsyncOperationCompletedHandler_1__IModuleCommandResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IModuleCommandResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2E1F3D72-A58D-5B0A-B42D-3660C04CFEEB}") IAsyncOperation_1__IModuleCommandResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2C6BF221-7556-53C2-A367-F1A5BB3819BD}") IAsyncOperation_1__IModuleCommandResult  : public IAsyncOperation_1__IModuleCommandResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IModuleCommandResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IModuleCommandResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IModuleCommandResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IModuleCommandResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IModuleCommandResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IModuleCommandResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{86CFAC36-47C1-4B33-9852-8773EC4BE123}") IAudioDeviceModule  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ClassId(HSTRING &__get_ClassId_result) = 0 ;
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall get_InstanceId(unsigned &__get_InstanceId_result) = 0 ;
	virtual HRESULT __safecall get_MajorVersion(unsigned &__get_MajorVersion_result) = 0 ;
	virtual HRESULT __safecall get_MinorVersion(unsigned &__get_MinorVersion_result) = 0 ;
	virtual HRESULT __safecall SendCommandAsync(Winapi::Commontypes::_di_IBuffer Command, _di_IAsyncOperation_1__IModuleCommandResult &__SendCommandAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ClassId() { HSTRING __r; HRESULT __hr = get_ClassId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ClassId = {read=_scw_get_ClassId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_InstanceId() { unsigned __r; HRESULT __hr = get_InstanceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned InstanceId = {read=_scw_get_InstanceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MajorVersion() { unsigned __r; HRESULT __hr = get_MajorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MajorVersion = {read=_scw_get_MajorVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MinorVersion() { unsigned __r; HRESULT __hr = get_MinorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MinorVersion = {read=_scw_get_MinorVersion};
};

__interface  INTERFACE_UUID("{E3E3CCAF-224C-48BE-956B-9A13134E96E8}") IAudioDeviceModuleNotificationEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Module(_di_IAudioDeviceModule &__get_Module_result) = 0 ;
	virtual HRESULT __safecall get_NotificationData(Winapi::Commontypes::_di_IBuffer &__get_NotificationData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAudioDeviceModule _scw_get_Module() { _di_IAudioDeviceModule __r; HRESULT __hr = get_Module(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAudioDeviceModule Module = {read=_scw_get_Module};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_NotificationData() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_NotificationData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer NotificationData = {read=_scw_get_NotificationData};
};

__interface  INTERFACE_UUID("{B2F6B1FD-7092-5724-B2CE-91B1176E80E1}") TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{DBAEA1CD-E1B1-5484-96FC-8EFF3A2AEEB8}") TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs  : public TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAudioDeviceModulesManager sender, _di_IAudioDeviceModuleNotificationEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{B4CBBFB7-9851-56C9-839D-A10A8B1BB234}") IIterator_1__IAudioDeviceModule_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{97A6CDC2-0590-5937-8D32-9A68D3D90DCA}") IIterator_1__IAudioDeviceModule  : public IIterator_1__IAudioDeviceModule_Base 
{
	virtual HRESULT __safecall get_Current(_di_IAudioDeviceModule &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIAudioDeviceModule items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAudioDeviceModule _scw_get_Current() { _di_IAudioDeviceModule __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAudioDeviceModule Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{7EEB51C3-D70E-548A-85C2-3CF71B4A124C}") IIterable_1__IAudioDeviceModule_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{574EF793-9855-53DC-883D-F358ADA53082}") IIterable_1__IAudioDeviceModule  : public IIterable_1__IAudioDeviceModule_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IAudioDeviceModule &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{CECC9411-B8C8-5BDD-9F4E-447D433667F2}") IVectorView_1__IAudioDeviceModule  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IAudioDeviceModule &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IAudioDeviceModule value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIAudioDeviceModule items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{6AA40C4D-960A-4D1C-B318-0022604547ED}") IAudioDeviceModulesManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ModuleNotificationReceived(_di_TypedEventHandler_2__IAudioDeviceModulesManager__IAudioDeviceModuleNotificationEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ModuleNotificationReceived_result) = 0 ;
	virtual HRESULT __safecall remove_ModuleNotificationReceived(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall FindAllById(HSTRING moduleId, _di_IVectorView_1__IAudioDeviceModule &__FindAllById_result) = 0 ;
	virtual HRESULT __safecall FindAll(_di_IVectorView_1__IAudioDeviceModule &__FindAll_result) = 0 ;
};

__interface  INTERFACE_UUID("{8DB03670-E64D-4773-96C0-BC7EBF0E063F}") IAudioDeviceModulesManagerFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING deviceId, _di_IAudioDeviceModulesManager &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{AAFA6D7A-2F7F-5DD7-AA0A-265731A2B3B3}") IIterator_1__CaptureSceneMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__CaptureSceneMode  : public IIterator_1__CaptureSceneMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::CaptureSceneMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PCaptureSceneMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CaptureSceneMode _scw_get_Current() { Winapi::Commontypes::CaptureSceneMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CaptureSceneMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{16D26B98-2CBC-52F0-AB64-1723714418E9}") IIterable_1__CaptureSceneMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__CaptureSceneMode  : public IIterable_1__CaptureSceneMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__CaptureSceneMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__CaptureSceneMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::CaptureSceneMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::CaptureSceneMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PCaptureSceneMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{D48E5AF7-8D59-4854-8C62-12C70BA89B7C}") ISceneModeControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SupportedModes(_di_IVectorView_1__CaptureSceneMode &__get_SupportedModes_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::CaptureSceneMode &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(Winapi::Commontypes::CaptureSceneMode sceneMode, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__CaptureSceneMode _scw_get_SupportedModes() { _di_IVectorView_1__CaptureSceneMode __r; HRESULT __hr = get_SupportedModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__CaptureSceneMode SupportedModes = {read=_scw_get_SupportedModes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CaptureSceneMode _scw_get_Value() { Winapi::Commontypes::CaptureSceneMode __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CaptureSceneMode Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{A6053665-8250-416C-919A-724296AFA306}") ITorchControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_PowerSupported(bool &__get_PowerSupported_result) = 0 ;
	virtual HRESULT __safecall get_Enabled(bool &__get_Enabled_result) = 0 ;
	virtual HRESULT __safecall put_Enabled(bool value) = 0 ;
	virtual HRESULT __safecall get_PowerPercent(float &__get_PowerPercent_result) = 0 ;
	virtual HRESULT __safecall put_PowerPercent(float value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Enabled() { bool __r; HRESULT __hr = get_Enabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Enabled = {read=_scw_get_Enabled, write=put_Enabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_PowerPercent() { float __r; HRESULT __hr = get_PowerPercent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float PowerPercent = {read=_scw_get_PowerPercent, write=put_PowerPercent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_PowerSupported() { bool __r; HRESULT __hr = get_PowerSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool PowerSupported = {read=_scw_get_PowerSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{DEF41DBE-7D68-45E3-8C0F-BE7BB32837D0}") IFlashControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_PowerSupported(bool &__get_PowerSupported_result) = 0 ;
	virtual HRESULT __safecall get_RedEyeReductionSupported(bool &__get_RedEyeReductionSupported_result) = 0 ;
	virtual HRESULT __safecall get_Enabled(bool &__get_Enabled_result) = 0 ;
	virtual HRESULT __safecall put_Enabled(bool value) = 0 ;
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall put_Auto(bool value) = 0 ;
	virtual HRESULT __safecall get_RedEyeReduction(bool &__get_RedEyeReduction_result) = 0 ;
	virtual HRESULT __safecall put_RedEyeReduction(bool value) = 0 ;
	virtual HRESULT __safecall get_PowerPercent(float &__get_PowerPercent_result) = 0 ;
	virtual HRESULT __safecall put_PowerPercent(float value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto, write=put_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Enabled() { bool __r; HRESULT __hr = get_Enabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Enabled = {read=_scw_get_Enabled, write=put_Enabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_PowerPercent() { float __r; HRESULT __hr = get_PowerPercent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float PowerPercent = {read=_scw_get_PowerPercent, write=put_PowerPercent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_PowerSupported() { bool __r; HRESULT __hr = get_PowerSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool PowerSupported = {read=_scw_get_PowerSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_RedEyeReduction() { bool __r; HRESULT __hr = get_RedEyeReduction(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool RedEyeReduction = {read=_scw_get_RedEyeReduction, write=put_RedEyeReduction};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_RedEyeReductionSupported() { bool __r; HRESULT __hr = get_RedEyeReductionSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool RedEyeReductionSupported = {read=_scw_get_RedEyeReductionSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{7D29CC9E-75E1-4AF7-BD7D-4E38E1C06CD6}") IFlashControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AssistantLightSupported(bool &__get_AssistantLightSupported_result) = 0 ;
	virtual HRESULT __safecall get_AssistantLightEnabled(bool &__get_AssistantLightEnabled_result) = 0 ;
	virtual HRESULT __safecall put_AssistantLightEnabled(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AssistantLightEnabled() { bool __r; HRESULT __hr = get_AssistantLightEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AssistantLightEnabled = {read=_scw_get_AssistantLightEnabled, write=put_AssistantLightEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AssistantLightSupported() { bool __r; HRESULT __hr = get_AssistantLightSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AssistantLightSupported = {read=_scw_get_AssistantLightSupported};
};

__interface  INTERFACE_UUID("{81C8E834-DCEC-4011-A610-1F3847E64ACA}") IExposureCompensationControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(float &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(float &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(float &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(float &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(float value, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Max() { float __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Min() { float __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Step() { float __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Value() { float __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{1B33AF76-980B-5348-916A-793F61B555A0}") IIterator_1__IsoSpeedPreset_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__IsoSpeedPreset  : public IIterator_1__IsoSpeedPreset_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::IsoSpeedPreset &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIsoSpeedPreset items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::IsoSpeedPreset _scw_get_Current() { Winapi::Commontypes::IsoSpeedPreset __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::IsoSpeedPreset Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{94839ABE-9712-545A-A94D-A567A3E8DFB7}") IIterable_1__IsoSpeedPreset_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__IsoSpeedPreset  : public IIterable_1__IsoSpeedPreset_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IsoSpeedPreset &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__IsoSpeedPreset  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::IsoSpeedPreset &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::IsoSpeedPreset value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIsoSpeedPreset items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{27B6C322-25AD-4F1B-AAAB-524AB376CA33}") IIsoSpeedControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedPresets(_di_IVectorView_1__IsoSpeedPreset &__get_SupportedPresets_result) = 0 ;
	virtual HRESULT __safecall get_Preset(Winapi::Commontypes::IsoSpeedPreset &__get_Preset_result) = 0 ;
	virtual HRESULT __safecall SetPresetAsync(Winapi::Commontypes::IsoSpeedPreset preset, Winapi::Commontypes::_di_IAsyncAction &__SetPresetAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::IsoSpeedPreset _scw_get_Preset() { Winapi::Commontypes::IsoSpeedPreset __r; HRESULT __hr = get_Preset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::IsoSpeedPreset Preset = {read=_scw_get_Preset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__IsoSpeedPreset _scw_get_SupportedPresets() { _di_IVectorView_1__IsoSpeedPreset __r; HRESULT __hr = get_SupportedPresets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__IsoSpeedPreset SupportedPresets = {read=_scw_get_SupportedPresets};
};

__interface  INTERFACE_UUID("{6F1578F2-6D77-4F8A-8C2F-6130B6395053}") IIsoSpeedControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Min(unsigned &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(unsigned &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(unsigned &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(unsigned &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(unsigned isoSpeed, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall SetAutoAsync(Winapi::Commontypes::_di_IAsyncAction &__SetAutoAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Max() { unsigned __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Min() { unsigned __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Step() { unsigned __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Value() { unsigned __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{781F047E-7162-49C8-A8F9-9481C565363E}") IWhiteBalanceControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Preset(Winapi::Commontypes::ColorTemperaturePreset &__get_Preset_result) = 0 ;
	virtual HRESULT __safecall SetPresetAsync(Winapi::Commontypes::ColorTemperaturePreset preset, Winapi::Commontypes::_di_IAsyncAction &__SetPresetAsync_result) = 0 ;
	virtual HRESULT __safecall get_Min(unsigned &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(unsigned &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(unsigned &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(unsigned &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(unsigned temperature, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Max() { unsigned __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Min() { unsigned __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ColorTemperaturePreset _scw_get_Preset() { Winapi::Commontypes::ColorTemperaturePreset __r; HRESULT __hr = get_Preset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ColorTemperaturePreset Preset = {read=_scw_get_Preset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Step() { unsigned __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Value() { unsigned __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{09E8CBE2-AD96-4F28-A0E0-96ED7E1B5FD2}") IExposureControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall SetAutoAsync(bool value, Winapi::Commontypes::_di_IAsyncAction &__SetAutoAsync_result) = 0 ;
	virtual HRESULT __safecall get_Min(Winapi::Commontypes::TimeSpan &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(Winapi::Commontypes::TimeSpan &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(Winapi::Commontypes::TimeSpan &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::TimeSpan &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(Winapi::Commontypes::TimeSpan shutterDuration, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Max() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Min() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Step() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Value() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{6AD66B24-14B4-4BFD-B18F-88FE24463B52}") IZoomSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::ZoomTransitionMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::ZoomTransitionMode value) = 0 ;
	virtual HRESULT __safecall get_Value(float &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(float value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ZoomTransitionMode _scw_get_Mode() { Winapi::Commontypes::ZoomTransitionMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ZoomTransitionMode Mode = {read=_scw_get_Mode, write=put_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Value() { float __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{3A1E0B12-32DA-4C17-BFD7-8D0C73C8F5A5}") IZoomControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(float &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(float &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(float &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(float &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(float value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Max() { float __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Min() { float __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Step() { float __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Value() { float __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{80EB468A-FDC4-5C89-99B8-8D476264E211}") IIterator_1__ZoomTransitionMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__ZoomTransitionMode  : public IIterator_1__ZoomTransitionMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::ZoomTransitionMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PZoomTransitionMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ZoomTransitionMode _scw_get_Current() { Winapi::Commontypes::ZoomTransitionMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ZoomTransitionMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{DB656915-8FAC-5FB2-98E0-0E97421656C5}") IIterable_1__ZoomTransitionMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__ZoomTransitionMode  : public IIterable_1__ZoomTransitionMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ZoomTransitionMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__ZoomTransitionMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::ZoomTransitionMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::ZoomTransitionMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PZoomTransitionMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{69843DB0-2E99-4641-8529-184F319D1671}") IZoomControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SupportedModes(_di_IVectorView_1__ZoomTransitionMode &__get_SupportedModes_result) = 0 ;
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::ZoomTransitionMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall Configure(_di_IZoomSettings settings) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ZoomTransitionMode _scw_get_Mode() { Winapi::Commontypes::ZoomTransitionMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ZoomTransitionMode Mode = {read=_scw_get_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__ZoomTransitionMode _scw_get_SupportedModes() { _di_IVectorView_1__ZoomTransitionMode __r; HRESULT __hr = get_SupportedModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__ZoomTransitionMode SupportedModes = {read=_scw_get_SupportedModes};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__ManualFocusDistance  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::ManualFocusDistance &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ManualFocusDistance _scw_get_Value() { Winapi::Commontypes::ManualFocusDistance __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ManualFocusDistance Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{79958F6B-3263-4275-85D6-AEAE891C96EE}") IFocusSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::FocusMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::FocusMode value) = 0 ;
	virtual HRESULT __safecall get_AutoFocusRange(Winapi::Commontypes::AutoFocusRange &__get_AutoFocusRange_result) = 0 ;
	virtual HRESULT __safecall put_AutoFocusRange(Winapi::Commontypes::AutoFocusRange value) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Perception::_di_IReference_1__Cardinal &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(Winapi::Perception::_di_IReference_1__Cardinal value) = 0 ;
	virtual HRESULT __safecall get_Distance(_di_IReference_1__ManualFocusDistance &__get_Distance_result) = 0 ;
	virtual HRESULT __safecall put_Distance(_di_IReference_1__ManualFocusDistance value) = 0 ;
	virtual HRESULT __safecall get_WaitForFocus(bool &__get_WaitForFocus_result) = 0 ;
	virtual HRESULT __safecall put_WaitForFocus(bool value) = 0 ;
	virtual HRESULT __safecall get_DisableDriverFallback(bool &__get_DisableDriverFallback_result) = 0 ;
	virtual HRESULT __safecall put_DisableDriverFallback(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AutoFocusRange _scw_get_AutoFocusRange() { Winapi::Commontypes::AutoFocusRange __r; HRESULT __hr = get_AutoFocusRange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AutoFocusRange AutoFocusRange = {read=_scw_get_AutoFocusRange, write=put_AutoFocusRange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_DisableDriverFallback() { bool __r; HRESULT __hr = get_DisableDriverFallback(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool DisableDriverFallback = {read=_scw_get_DisableDriverFallback, write=put_DisableDriverFallback};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IReference_1__ManualFocusDistance _scw_get_Distance() { _di_IReference_1__ManualFocusDistance __r; HRESULT __hr = get_Distance(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IReference_1__ManualFocusDistance Distance = {read=_scw_get_Distance, write=put_Distance};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FocusMode _scw_get_Mode() { Winapi::Commontypes::FocusMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FocusMode Mode = {read=_scw_get_Mode, write=put_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Perception::_di_IReference_1__Cardinal _scw_get_Value() { Winapi::Perception::_di_IReference_1__Cardinal __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Perception::_di_IReference_1__Cardinal Value = {read=_scw_get_Value, write=put_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_WaitForFocus() { bool __r; HRESULT __hr = get_WaitForFocus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool WaitForFocus = {read=_scw_get_WaitForFocus, write=put_WaitForFocus};
};

__interface  INTERFACE_UUID("{D3EBC8E9-F0C5-51C0-BB86-BDEA0A6946FB}") IIterator_1__FocusPreset_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__FocusPreset  : public IIterator_1__FocusPreset_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::FocusPreset &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PFocusPreset items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FocusPreset _scw_get_Current() { Winapi::Commontypes::FocusPreset __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FocusPreset Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{26BA711B-3A32-5216-BC34-61ECAFBEBDC1}") IIterable_1__FocusPreset_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__FocusPreset  : public IIterable_1__FocusPreset_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__FocusPreset &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__FocusPreset  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::FocusPreset &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::FocusPreset value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PFocusPreset items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{C0D889F6-5228-4453-B153-85606592B238}") IFocusControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedPresets(_di_IVectorView_1__FocusPreset &__get_SupportedPresets_result) = 0 ;
	virtual HRESULT __safecall get_Preset(Winapi::Commontypes::FocusPreset &__get_Preset_result) = 0 ;
	virtual HRESULT __safecall SetPresetAsync(Winapi::Commontypes::FocusPreset preset, Winapi::Commontypes::_di_IAsyncAction &__SetPresetAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall SetPresetAsync(Winapi::Commontypes::FocusPreset preset, bool completeBeforeFocus, Winapi::Commontypes::_di_IAsyncAction &__SetPresetAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall get_Min(unsigned &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(unsigned &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(unsigned &__get_Step_result) = 0 ;
	virtual HRESULT __safecall get_Value(unsigned &__get_Value_result) = 0 ;
	virtual HRESULT __safecall SetValueAsync(unsigned focus, Winapi::Commontypes::_di_IAsyncAction &__SetValueAsync_result) = 0 ;
	virtual HRESULT __safecall FocusAsync(Winapi::Commontypes::_di_IAsyncAction &__FocusAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Max() { unsigned __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Min() { unsigned __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FocusPreset _scw_get_Preset() { Winapi::Commontypes::FocusPreset __r; HRESULT __hr = get_Preset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FocusPreset Preset = {read=_scw_get_Preset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Step() { unsigned __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__FocusPreset _scw_get_SupportedPresets() { _di_IVectorView_1__FocusPreset __r; HRESULT __hr = get_SupportedPresets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__FocusPreset SupportedPresets = {read=_scw_get_SupportedPresets};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Value() { unsigned __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{F9A43CD4-B300-541F-AF79-3DE3400E16AF}") IIterator_1__FocusMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__FocusMode  : public IIterator_1__FocusMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::FocusMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PFocusMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FocusMode _scw_get_Current() { Winapi::Commontypes::FocusMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FocusMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{561BC21F-4AE2-580A-A216-0AD48F373A4C}") IIterable_1__FocusMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__FocusMode  : public IIterable_1__FocusMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__FocusMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__FocusMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::FocusMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::FocusMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PFocusMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{B02944E1-F649-511E-80DD-2E2B20379DEB}") IIterator_1__ManualFocusDistance_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__ManualFocusDistance  : public IIterator_1__ManualFocusDistance_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::ManualFocusDistance &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PManualFocusDistance items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ManualFocusDistance _scw_get_Current() { Winapi::Commontypes::ManualFocusDistance __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ManualFocusDistance Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{CF8CBEB1-2A4C-522D-962F-84C31A598D68}") IIterable_1__ManualFocusDistance_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__ManualFocusDistance  : public IIterable_1__ManualFocusDistance_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ManualFocusDistance &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__ManualFocusDistance  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::ManualFocusDistance &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::ManualFocusDistance value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PManualFocusDistance items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{07489AC5-3C71-59C6-B7DC-7F21341C2F71}") IIterator_1__AutoFocusRange_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__AutoFocusRange  : public IIterator_1__AutoFocusRange_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::AutoFocusRange &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PAutoFocusRange items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AutoFocusRange _scw_get_Current() { Winapi::Commontypes::AutoFocusRange __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AutoFocusRange Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{751664C6-F8D6-50A3-AB80-137C6D908C55}") IIterable_1__AutoFocusRange_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__AutoFocusRange  : public IIterable_1__AutoFocusRange_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__AutoFocusRange &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__AutoFocusRange  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::AutoFocusRange &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::AutoFocusRange value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PAutoFocusRange items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{3F7CFF48-C534-4E9E-94C3-52EF2AFD5D07}") IFocusControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_FocusChangedSupported(bool &__get_FocusChangedSupported_result) = 0 ;
	virtual HRESULT __safecall get_WaitForFocusSupported(bool &__get_WaitForFocusSupported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedFocusModes(_di_IVectorView_1__FocusMode &__get_SupportedFocusModes_result) = 0 ;
	virtual HRESULT __safecall get_SupportedFocusDistances(_di_IVectorView_1__ManualFocusDistance &__get_SupportedFocusDistances_result) = 0 ;
	virtual HRESULT __safecall get_SupportedFocusRanges(_di_IVectorView_1__AutoFocusRange &__get_SupportedFocusRanges_result) = 0 ;
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::FocusMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall get_FocusState(Winapi::Commontypes::MediaCaptureFocusState &__get_FocusState_result) = 0 ;
	virtual HRESULT __safecall UnlockAsync(Winapi::Commontypes::_di_IAsyncAction &__UnlockAsync_result) = 0 ;
	virtual HRESULT __safecall LockAsync(Winapi::Commontypes::_di_IAsyncAction &__LockAsync_result) = 0 ;
	virtual HRESULT __safecall Configure(_di_IFocusSettings settings) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_FocusChangedSupported() { bool __r; HRESULT __hr = get_FocusChangedSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool FocusChangedSupported = {read=_scw_get_FocusChangedSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaCaptureFocusState _scw_get_FocusState() { Winapi::Commontypes::MediaCaptureFocusState __r; HRESULT __hr = get_FocusState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaCaptureFocusState FocusState = {read=_scw_get_FocusState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::FocusMode _scw_get_Mode() { Winapi::Commontypes::FocusMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::FocusMode Mode = {read=_scw_get_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__ManualFocusDistance _scw_get_SupportedFocusDistances() { _di_IVectorView_1__ManualFocusDistance __r; HRESULT __hr = get_SupportedFocusDistances(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__ManualFocusDistance SupportedFocusDistances = {read=_scw_get_SupportedFocusDistances};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__FocusMode _scw_get_SupportedFocusModes() { _di_IVectorView_1__FocusMode __r; HRESULT __hr = get_SupportedFocusModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__FocusMode SupportedFocusModes = {read=_scw_get_SupportedFocusModes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__AutoFocusRange _scw_get_SupportedFocusRanges() { _di_IVectorView_1__AutoFocusRange __r; HRESULT __hr = get_SupportedFocusRanges(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__AutoFocusRange SupportedFocusRanges = {read=_scw_get_SupportedFocusRanges};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_WaitForFocusSupported() { bool __r; HRESULT __hr = get_WaitForFocusSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool WaitForFocusSupported = {read=_scw_get_WaitForFocusSupported};
};

__interface  INTERFACE_UUID("{E5ECC834-CE66-4E05-A78F-CF391A5EC2D1}") IRegionOfInterest  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AutoFocusEnabled(bool &__get_AutoFocusEnabled_result) = 0 ;
	virtual HRESULT __safecall put_AutoFocusEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_AutoWhiteBalanceEnabled(bool &__get_AutoWhiteBalanceEnabled_result) = 0 ;
	virtual HRESULT __safecall put_AutoWhiteBalanceEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_AutoExposureEnabled(bool &__get_AutoExposureEnabled_result) = 0 ;
	virtual HRESULT __safecall put_AutoExposureEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_Bounds(System::Types::TRectF &__get_Bounds_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_Bounds(System::Types::TRectF value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_Bounds(const System::Types::TRectF &value) = 0 ;
#endif /* _WIN64 */
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoExposureEnabled() { bool __r; HRESULT __hr = get_AutoExposureEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoExposureEnabled = {read=_scw_get_AutoExposureEnabled, write=put_AutoExposureEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoFocusEnabled() { bool __r; HRESULT __hr = get_AutoFocusEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoFocusEnabled = {read=_scw_get_AutoFocusEnabled, write=put_AutoFocusEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoWhiteBalanceEnabled() { bool __r; HRESULT __hr = get_AutoWhiteBalanceEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoWhiteBalanceEnabled = {read=_scw_get_AutoWhiteBalanceEnabled, write=put_AutoWhiteBalanceEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_Bounds() { System::Types::TRectF __r; HRESULT __hr = get_Bounds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF Bounds = {read=_scw_get_Bounds, write=put_Bounds};
};

__interface  INTERFACE_UUID("{19FE2A91-73AA-4D51-8A9D-56CCF7DB7F54}") IRegionOfInterest2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Type(Winapi::Commontypes::RegionOfInterestType &__get_Type_result) = 0 ;
	virtual HRESULT __safecall put_Type(Winapi::Commontypes::RegionOfInterestType value) = 0 ;
	virtual HRESULT __safecall get_BoundsNormalized(bool &__get_BoundsNormalized_result) = 0 ;
	virtual HRESULT __safecall put_BoundsNormalized(bool value) = 0 ;
	virtual HRESULT __safecall get_Weight(unsigned &__get_Weight_result) = 0 ;
	virtual HRESULT __safecall put_Weight(unsigned value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_BoundsNormalized() { bool __r; HRESULT __hr = get_BoundsNormalized(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool BoundsNormalized = {read=_scw_get_BoundsNormalized, write=put_BoundsNormalized};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::RegionOfInterestType _scw_get_Type() { Winapi::Commontypes::RegionOfInterestType __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::RegionOfInterestType Type = {read=_scw_get_Type, write=put_Type};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Weight() { unsigned __r; HRESULT __hr = get_Weight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Weight = {read=_scw_get_Weight, write=put_Weight};
};

__interface  INTERFACE_UUID("{8EB80E4E-9691-594F-8B3D-F52ECC0F7837}") IIterator_1__IRegionOfInterest_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1FC1158F-A90B-583F-803A-71B3C22D2686}") IIterator_1__IRegionOfInterest  : public IIterator_1__IRegionOfInterest_Base 
{
	virtual HRESULT __safecall get_Current(_di_IRegionOfInterest &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIRegionOfInterest items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IRegionOfInterest _scw_get_Current() { _di_IRegionOfInterest __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IRegionOfInterest Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D73144C7-9D75-5DFB-8040-626202DCF454}") IIterable_1__IRegionOfInterest_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{69260AC6-4C37-527E-A1AB-2EBCF083DE2B}") IIterable_1__IRegionOfInterest  : public IIterable_1__IRegionOfInterest_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IRegionOfInterest &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{C323F527-AB0B-4558-8B5B-DF5693DB0378}") IRegionsOfInterestControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MaxRegions(unsigned &__get_MaxRegions_result) = 0 ;
	virtual HRESULT __safecall SetRegionsAsync(_di_IIterable_1__IRegionOfInterest regions, Winapi::Commontypes::_di_IAsyncAction &__SetRegionsAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall SetRegionsAsync(_di_IIterable_1__IRegionOfInterest regions, bool lockValues, Winapi::Commontypes::_di_IAsyncAction &__SetRegionsAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall ClearRegionsAsync(Winapi::Commontypes::_di_IAsyncAction &__ClearRegionsAsync_result) = 0 ;
	virtual HRESULT __safecall get_AutoFocusSupported(bool &__get_AutoFocusSupported_result) = 0 ;
	virtual HRESULT __safecall get_AutoWhiteBalanceSupported(bool &__get_AutoWhiteBalanceSupported_result) = 0 ;
	virtual HRESULT __safecall get_AutoExposureSupported(bool &__get_AutoExposureSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoExposureSupported() { bool __r; HRESULT __hr = get_AutoExposureSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoExposureSupported = {read=_scw_get_AutoExposureSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoFocusSupported() { bool __r; HRESULT __hr = get_AutoFocusSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoFocusSupported = {read=_scw_get_AutoFocusSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoWhiteBalanceSupported() { bool __r; HRESULT __hr = get_AutoWhiteBalanceSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoWhiteBalanceSupported = {read=_scw_get_AutoWhiteBalanceSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxRegions() { unsigned __r; HRESULT __hr = get_MaxRegions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxRegions = {read=_scw_get_MaxRegions};
};

__interface  INTERFACE_UUID("{2CB240A3-5168-4271-9EA5-47621A98A352}") IExposurePriorityVideoControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Enabled(bool &__get_Enabled_result) = 0 ;
	virtual HRESULT __safecall put_Enabled(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Enabled() { bool __r; HRESULT __hr = get_Enabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Enabled = {read=_scw_get_Enabled, write=put_Enabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{3DB61D13-0F30-5D2D-99CB-30C7B9009878}") IIterator_1__HdrVideoMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__HdrVideoMode  : public IIterator_1__HdrVideoMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::HdrVideoMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PHdrVideoMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::HdrVideoMode _scw_get_Current() { Winapi::Commontypes::HdrVideoMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::HdrVideoMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{1D9679A7-2D06-5294-AC67-F9CD3561DCB8}") IIterable_1__HdrVideoMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__HdrVideoMode  : public IIterable_1__HdrVideoMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__HdrVideoMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__HdrVideoMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::HdrVideoMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::HdrVideoMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PHdrVideoMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{55D8E2D0-30C0-43BF-9B9A-9799D70CED94}") IHdrVideoControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedModes(_di_IVectorView_1__HdrVideoMode &__get_SupportedModes_result) = 0 ;
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::HdrVideoMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::HdrVideoMode value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::HdrVideoMode _scw_get_Mode() { Winapi::Commontypes::HdrVideoMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::HdrVideoMode Mode = {read=_scw_get_Mode, write=put_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__HdrVideoMode _scw_get_SupportedModes() { _di_IVectorView_1__HdrVideoMode __r; HRESULT __hr = get_SupportedModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__HdrVideoMode SupportedModes = {read=_scw_get_SupportedModes};
};

__interface  INTERFACE_UUID("{08F3863A-0018-445B-93D2-646D1C5ED05C}") IAdvancedPhotoCaptureSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::AdvancedPhotoMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::AdvancedPhotoMode value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AdvancedPhotoMode _scw_get_Mode() { Winapi::Commontypes::AdvancedPhotoMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AdvancedPhotoMode Mode = {read=_scw_get_Mode, write=put_Mode};
};

__interface  INTERFACE_UUID("{E6D0BC9D-E1CB-5ED0-8EDE-7D037BCC2E07}") IIterator_1__AdvancedPhotoMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__AdvancedPhotoMode  : public IIterator_1__AdvancedPhotoMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::AdvancedPhotoMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PAdvancedPhotoMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AdvancedPhotoMode _scw_get_Current() { Winapi::Commontypes::AdvancedPhotoMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AdvancedPhotoMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{7D090784-70A9-570C-BE82-0D0890318975}") IIterable_1__AdvancedPhotoMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__AdvancedPhotoMode  : public IIterable_1__AdvancedPhotoMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__AdvancedPhotoMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__AdvancedPhotoMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::AdvancedPhotoMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::AdvancedPhotoMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PAdvancedPhotoMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{C5B15486-9001-4682-9309-68EAE0080EEC}") IAdvancedPhotoControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedModes(_di_IVectorView_1__AdvancedPhotoMode &__get_SupportedModes_result) = 0 ;
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::AdvancedPhotoMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall Configure(_di_IAdvancedPhotoCaptureSettings settings) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AdvancedPhotoMode _scw_get_Mode() { Winapi::Commontypes::AdvancedPhotoMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AdvancedPhotoMode Mode = {read=_scw_get_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__AdvancedPhotoMode _scw_get_SupportedModes() { _di_IVectorView_1__AdvancedPhotoMode __r; HRESULT __hr = get_SupportedModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__AdvancedPhotoMode SupportedModes = {read=_scw_get_SupportedModes};
};

__interface  INTERFACE_UUID("{4A165D46-CF19-5A03-BB54-63FC2B4ED39B}") IIterator_1__OpticalImageStabilizationMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__OpticalImageStabilizationMode  : public IIterator_1__OpticalImageStabilizationMode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::OpticalImageStabilizationMode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::POpticalImageStabilizationMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::OpticalImageStabilizationMode _scw_get_Current() { Winapi::Commontypes::OpticalImageStabilizationMode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::OpticalImageStabilizationMode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{323D7734-94C2-544D-A560-56560FE68819}") IIterable_1__OpticalImageStabilizationMode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__OpticalImageStabilizationMode  : public IIterable_1__OpticalImageStabilizationMode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__OpticalImageStabilizationMode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__OpticalImageStabilizationMode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::OpticalImageStabilizationMode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::OpticalImageStabilizationMode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::POpticalImageStabilizationMode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{BFAD9C1D-00BC-423B-8EB2-A0178CA94247}") IOpticalImageStabilizationControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedModes(_di_IVectorView_1__OpticalImageStabilizationMode &__get_SupportedModes_result) = 0 ;
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::OpticalImageStabilizationMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::OpticalImageStabilizationMode value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::OpticalImageStabilizationMode _scw_get_Mode() { Winapi::Commontypes::OpticalImageStabilizationMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::OpticalImageStabilizationMode Mode = {read=_scw_get_Mode, write=put_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__OpticalImageStabilizationMode _scw_get_SupportedModes() { _di_IVectorView_1__OpticalImageStabilizationMode __r; HRESULT __hr = get_SupportedModes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__OpticalImageStabilizationMode SupportedModes = {read=_scw_get_SupportedModes};
};

__interface  INTERFACE_UUID("{3DCF909D-6D16-409C-BAFE-B9A594C6FDE6}") ILowLagPhotoSequenceControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_MaxPastPhotos(unsigned &__get_MaxPastPhotos_result) = 0 ;
	virtual HRESULT __safecall get_MaxPhotosPerSecond(float &__get_MaxPhotosPerSecond_result) = 0 ;
	virtual HRESULT __safecall get_PastPhotoLimit(unsigned &__get_PastPhotoLimit_result) = 0 ;
	virtual HRESULT __safecall put_PastPhotoLimit(unsigned value) = 0 ;
	virtual HRESULT __safecall get_PhotosPerSecondLimit(float &__get_PhotosPerSecondLimit_result) = 0 ;
	virtual HRESULT __safecall put_PhotosPerSecondLimit(float value) = 0 ;
	virtual HRESULT __safecall GetHighestConcurrentFrameRate(Winapi::Media::Mediaproperties::_di_IMediaEncodingProperties captureProperties, Winapi::Commontypes::_di_IMediaRatio &__GetHighestConcurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall GetCurrentFrameRate(Winapi::Commontypes::_di_IMediaRatio &__GetCurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall get_ThumbnailEnabled(bool &__get_ThumbnailEnabled_result) = 0 ;
	virtual HRESULT __safecall put_ThumbnailEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_ThumbnailFormat(Winapi::Commontypes::MediaThumbnailFormat &__get_ThumbnailFormat_result) = 0 ;
	virtual HRESULT __safecall put_ThumbnailFormat(Winapi::Commontypes::MediaThumbnailFormat value) = 0 ;
	virtual HRESULT __safecall get_DesiredThumbnailSize(unsigned &__get_DesiredThumbnailSize_result) = 0 ;
	virtual HRESULT __safecall put_DesiredThumbnailSize(unsigned value) = 0 ;
	virtual HRESULT __safecall get_HardwareAcceleratedThumbnailSupported(unsigned &__get_HardwareAcceleratedThumbnailSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_DesiredThumbnailSize() { unsigned __r; HRESULT __hr = get_DesiredThumbnailSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned DesiredThumbnailSize = {read=_scw_get_DesiredThumbnailSize, write=put_DesiredThumbnailSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_HardwareAcceleratedThumbnailSupported() { unsigned __r; HRESULT __hr = get_HardwareAcceleratedThumbnailSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned HardwareAcceleratedThumbnailSupported = {read=_scw_get_HardwareAcceleratedThumbnailSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxPastPhotos() { unsigned __r; HRESULT __hr = get_MaxPastPhotos(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxPastPhotos = {read=_scw_get_MaxPastPhotos};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_MaxPhotosPerSecond() { float __r; HRESULT __hr = get_MaxPhotosPerSecond(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float MaxPhotosPerSecond = {read=_scw_get_MaxPhotosPerSecond};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_PastPhotoLimit() { unsigned __r; HRESULT __hr = get_PastPhotoLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned PastPhotoLimit = {read=_scw_get_PastPhotoLimit, write=put_PastPhotoLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_PhotosPerSecondLimit() { float __r; HRESULT __hr = get_PhotosPerSecondLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float PhotosPerSecondLimit = {read=_scw_get_PhotosPerSecondLimit, write=put_PhotosPerSecondLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ThumbnailEnabled() { bool __r; HRESULT __hr = get_ThumbnailEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ThumbnailEnabled = {read=_scw_get_ThumbnailEnabled, write=put_ThumbnailEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaThumbnailFormat _scw_get_ThumbnailFormat() { Winapi::Commontypes::MediaThumbnailFormat __r; HRESULT __hr = get_ThumbnailFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaThumbnailFormat ThumbnailFormat = {read=_scw_get_ThumbnailFormat, write=put_ThumbnailFormat};
};

__interface  INTERFACE_UUID("{6D5C4DD0-FADF-415D-AEE6-3BAA529300C9}") ILowLagPhotoControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetHighestConcurrentFrameRate(Winapi::Media::Mediaproperties::_di_IMediaEncodingProperties captureProperties, Winapi::Commontypes::_di_IMediaRatio &__GetHighestConcurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall GetCurrentFrameRate(Winapi::Commontypes::_di_IMediaRatio &__GetCurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall get_ThumbnailEnabled(bool &__get_ThumbnailEnabled_result) = 0 ;
	virtual HRESULT __safecall put_ThumbnailEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_ThumbnailFormat(Winapi::Commontypes::MediaThumbnailFormat &__get_ThumbnailFormat_result) = 0 ;
	virtual HRESULT __safecall put_ThumbnailFormat(Winapi::Commontypes::MediaThumbnailFormat value) = 0 ;
	virtual HRESULT __safecall get_DesiredThumbnailSize(unsigned &__get_DesiredThumbnailSize_result) = 0 ;
	virtual HRESULT __safecall put_DesiredThumbnailSize(unsigned value) = 0 ;
	virtual HRESULT __safecall get_HardwareAcceleratedThumbnailSupported(unsigned &__get_HardwareAcceleratedThumbnailSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_DesiredThumbnailSize() { unsigned __r; HRESULT __hr = get_DesiredThumbnailSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned DesiredThumbnailSize = {read=_scw_get_DesiredThumbnailSize, write=put_DesiredThumbnailSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_HardwareAcceleratedThumbnailSupported() { unsigned __r; HRESULT __hr = get_HardwareAcceleratedThumbnailSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned HardwareAcceleratedThumbnailSupported = {read=_scw_get_HardwareAcceleratedThumbnailSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ThumbnailEnabled() { bool __r; HRESULT __hr = get_ThumbnailEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ThumbnailEnabled = {read=_scw_get_ThumbnailEnabled, write=put_ThumbnailEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaThumbnailFormat _scw_get_ThumbnailFormat() { Winapi::Commontypes::MediaThumbnailFormat __r; HRESULT __hr = get_ThumbnailFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaThumbnailFormat ThumbnailFormat = {read=_scw_get_ThumbnailFormat, write=put_ThumbnailFormat};
};

__interface  INTERFACE_UUID("{8BB94F8F-F11A-43DB-B402-11930B80AE56}") IAdvancedVideoCaptureDeviceController2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LowLagPhotoSequence(_di_ILowLagPhotoSequenceControl &__get_LowLagPhotoSequence_result) = 0 ;
	virtual HRESULT __safecall get_LowLagPhoto(_di_ILowLagPhotoControl &__get_LowLagPhoto_result) = 0 ;
	virtual HRESULT __safecall get_SceneModeControl(_di_ISceneModeControl &__get_SceneModeControl_result) = 0 ;
	virtual HRESULT __safecall get_TorchControl(_di_ITorchControl &__get_TorchControl_result) = 0 ;
	virtual HRESULT __safecall get_FlashControl(_di_IFlashControl &__get_FlashControl_result) = 0 ;
	virtual HRESULT __safecall get_WhiteBalanceControl(_di_IWhiteBalanceControl &__get_WhiteBalanceControl_result) = 0 ;
	virtual HRESULT __safecall get_ExposureControl(_di_IExposureControl &__get_ExposureControl_result) = 0 ;
	virtual HRESULT __safecall get_FocusControl(_di_IFocusControl &__get_FocusControl_result) = 0 ;
	virtual HRESULT __safecall get_ExposureCompensationControl(_di_IExposureCompensationControl &__get_ExposureCompensationControl_result) = 0 ;
	virtual HRESULT __safecall get_IsoSpeedControl(_di_IIsoSpeedControl &__get_IsoSpeedControl_result) = 0 ;
	virtual HRESULT __safecall get_RegionsOfInterestControl(_di_IRegionsOfInterestControl &__get_RegionsOfInterestControl_result) = 0 ;
	virtual HRESULT __safecall get_PrimaryUse(Winapi::Commontypes::CaptureUse &__get_PrimaryUse_result) = 0 ;
	virtual HRESULT __safecall put_PrimaryUse(Winapi::Commontypes::CaptureUse value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IExposureCompensationControl _scw_get_ExposureCompensationControl() { _di_IExposureCompensationControl __r; HRESULT __hr = get_ExposureCompensationControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IExposureCompensationControl ExposureCompensationControl = {read=_scw_get_ExposureCompensationControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IExposureControl _scw_get_ExposureControl() { _di_IExposureControl __r; HRESULT __hr = get_ExposureControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IExposureControl ExposureControl = {read=_scw_get_ExposureControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IFlashControl _scw_get_FlashControl() { _di_IFlashControl __r; HRESULT __hr = get_FlashControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IFlashControl FlashControl = {read=_scw_get_FlashControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IFocusControl _scw_get_FocusControl() { _di_IFocusControl __r; HRESULT __hr = get_FocusControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IFocusControl FocusControl = {read=_scw_get_FocusControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IIsoSpeedControl _scw_get_IsoSpeedControl() { _di_IIsoSpeedControl __r; HRESULT __hr = get_IsoSpeedControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IIsoSpeedControl IsoSpeedControl = {read=_scw_get_IsoSpeedControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILowLagPhotoControl _scw_get_LowLagPhoto() { _di_ILowLagPhotoControl __r; HRESULT __hr = get_LowLagPhoto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILowLagPhotoControl LowLagPhoto = {read=_scw_get_LowLagPhoto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILowLagPhotoSequenceControl _scw_get_LowLagPhotoSequence() { _di_ILowLagPhotoSequenceControl __r; HRESULT __hr = get_LowLagPhotoSequence(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILowLagPhotoSequenceControl LowLagPhotoSequence = {read=_scw_get_LowLagPhotoSequence};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CaptureUse _scw_get_PrimaryUse() { Winapi::Commontypes::CaptureUse __r; HRESULT __hr = get_PrimaryUse(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CaptureUse PrimaryUse = {read=_scw_get_PrimaryUse, write=put_PrimaryUse};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IRegionsOfInterestControl _scw_get_RegionsOfInterestControl() { _di_IRegionsOfInterestControl __r; HRESULT __hr = get_RegionsOfInterestControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IRegionsOfInterestControl RegionsOfInterestControl = {read=_scw_get_RegionsOfInterestControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISceneModeControl _scw_get_SceneModeControl() { _di_ISceneModeControl __r; HRESULT __hr = get_SceneModeControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISceneModeControl SceneModeControl = {read=_scw_get_SceneModeControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ITorchControl _scw_get_TorchControl() { _di_ITorchControl __r; HRESULT __hr = get_TorchControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ITorchControl TorchControl = {read=_scw_get_TorchControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWhiteBalanceControl _scw_get_WhiteBalanceControl() { _di_IWhiteBalanceControl __r; HRESULT __hr = get_WhiteBalanceControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWhiteBalanceControl WhiteBalanceControl = {read=_scw_get_WhiteBalanceControl};
};

__interface  INTERFACE_UUID("{BDBE9CE3-3985-4E72-97C2-0590D61307A1}") Core_IFrameExposureCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(Winapi::Commontypes::TimeSpan &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(Winapi::Commontypes::TimeSpan &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(Winapi::Commontypes::TimeSpan &__get_Step_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Max() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Min() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Step() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{B988A823-8065-41EE-B04F-722265954500}") Core_IFrameExposureCompensationCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(float &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(float &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(float &__get_Step_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Max() { float __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Min() { float __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Step() { float __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{16BDFF61-6DF6-4AC9-B92A-9F6ECD1AD2FA}") Core_IFrameIsoSpeedCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(unsigned &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(unsigned &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(unsigned &__get_Step_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Max() { unsigned __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Min() { unsigned __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Step() { unsigned __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{7B25CD58-01C0-4065-9C40-C1A721425C1A}") Core_IFrameFocusCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Min(unsigned &__get_Min_result) = 0 ;
	virtual HRESULT __safecall get_Max(unsigned &__get_Max_result) = 0 ;
	virtual HRESULT __safecall get_Step(unsigned &__get_Step_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Max() { unsigned __r; HRESULT __hr = get_Max(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Max = {read=_scw_get_Max};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Min() { unsigned __r; HRESULT __hr = get_Min(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Min = {read=_scw_get_Min};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Step() { unsigned __r; HRESULT __hr = get_Step(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Step = {read=_scw_get_Step};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{A8FFAE60-4E9E-4377-A789-E24C4AE7E544}") Core_IFrameControlCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Exposure(_di_Core_IFrameExposureCapabilities &__get_Exposure_result) = 0 ;
	virtual HRESULT __safecall get_ExposureCompensation(_di_Core_IFrameExposureCompensationCapabilities &__get_ExposureCompensation_result) = 0 ;
	virtual HRESULT __safecall get_IsoSpeed(_di_Core_IFrameIsoSpeedCapabilities &__get_IsoSpeed_result) = 0 ;
	virtual HRESULT __safecall get_Focus(_di_Core_IFrameFocusCapabilities &__get_Focus_result) = 0 ;
	virtual HRESULT __safecall get_PhotoConfirmationSupported(bool &__get_PhotoConfirmationSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameExposureCapabilities _scw_get_Exposure() { _di_Core_IFrameExposureCapabilities __r; HRESULT __hr = get_Exposure(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameExposureCapabilities Exposure = {read=_scw_get_Exposure};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameExposureCompensationCapabilities _scw_get_ExposureCompensation() { _di_Core_IFrameExposureCompensationCapabilities __r; HRESULT __hr = get_ExposureCompensation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameExposureCompensationCapabilities ExposureCompensation = {read=_scw_get_ExposureCompensation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameFocusCapabilities _scw_get_Focus() { _di_Core_IFrameFocusCapabilities __r; HRESULT __hr = get_Focus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameFocusCapabilities Focus = {read=_scw_get_Focus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameIsoSpeedCapabilities _scw_get_IsoSpeed() { _di_Core_IFrameIsoSpeedCapabilities __r; HRESULT __hr = get_IsoSpeed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameIsoSpeedCapabilities IsoSpeed = {read=_scw_get_IsoSpeed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_PhotoConfirmationSupported() { bool __r; HRESULT __hr = get_PhotoConfirmationSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool PhotoConfirmationSupported = {read=_scw_get_PhotoConfirmationSupported};
};

__interface  INTERFACE_UUID("{B1605A61-FFAF-4752-B621-F5B6F117F432}") Core_IFrameExposureControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall put_Auto(bool value) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IReference_1__TimeSpan &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(Winapi::Commontypes::_di_IReference_1__TimeSpan value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto, write=put_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__TimeSpan _scw_get_Value() { Winapi::Commontypes::_di_IReference_1__TimeSpan __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__TimeSpan Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{E95896C9-F7F9-48CA-8591-A26531CB1578}") Core_IFrameExposureCompensationControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IReference_1__Single &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(Winapi::Commontypes::_di_IReference_1__Single value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Single _scw_get_Value() { Winapi::Commontypes::_di_IReference_1__Single __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Single Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{1A03EFED-786A-4C75-A557-7AB9A85F588C}") Core_IFrameIsoSpeedControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall put_Auto(bool value) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Perception::_di_IReference_1__Cardinal &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(Winapi::Perception::_di_IReference_1__Cardinal value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto, write=put_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Perception::_di_IReference_1__Cardinal _scw_get_Value() { Winapi::Perception::_di_IReference_1__Cardinal __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Perception::_di_IReference_1__Cardinal Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{272DF1D0-D912-4214-A67B-E38A8D48D8C6}") Core_IFrameFocusControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Perception::_di_IReference_1__Cardinal &__get_Value_result) = 0 ;
	virtual HRESULT __safecall put_Value(Winapi::Perception::_di_IReference_1__Cardinal value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Perception::_di_IReference_1__Cardinal _scw_get_Value() { Winapi::Perception::_di_IReference_1__Cardinal __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Perception::_di_IReference_1__Cardinal Value = {read=_scw_get_Value, write=put_Value};
};

__interface  INTERFACE_UUID("{C16459D9-BAEF-4052-9177-48AFF2AF7522}") Core_IFrameController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ExposureControl(_di_Core_IFrameExposureControl &__get_ExposureControl_result) = 0 ;
	virtual HRESULT __safecall get_ExposureCompensationControl(_di_Core_IFrameExposureCompensationControl &__get_ExposureCompensationControl_result) = 0 ;
	virtual HRESULT __safecall get_IsoSpeedControl(_di_Core_IFrameIsoSpeedControl &__get_IsoSpeedControl_result) = 0 ;
	virtual HRESULT __safecall get_FocusControl(_di_Core_IFrameFocusControl &__get_FocusControl_result) = 0 ;
	virtual HRESULT __safecall get_PhotoConfirmationEnabled(Winapi::Commontypes::_di_IReference_1__Boolean &__get_PhotoConfirmationEnabled_result) = 0 ;
	virtual HRESULT __safecall put_PhotoConfirmationEnabled(Winapi::Commontypes::_di_IReference_1__Boolean value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameExposureCompensationControl _scw_get_ExposureCompensationControl() { _di_Core_IFrameExposureCompensationControl __r; HRESULT __hr = get_ExposureCompensationControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameExposureCompensationControl ExposureCompensationControl = {read=_scw_get_ExposureCompensationControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameExposureControl _scw_get_ExposureControl() { _di_Core_IFrameExposureControl __r; HRESULT __hr = get_ExposureControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameExposureControl ExposureControl = {read=_scw_get_ExposureControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameFocusControl _scw_get_FocusControl() { _di_Core_IFrameFocusControl __r; HRESULT __hr = get_FocusControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameFocusControl FocusControl = {read=_scw_get_FocusControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameIsoSpeedControl _scw_get_IsoSpeedControl() { _di_Core_IFrameIsoSpeedControl __r; HRESULT __hr = get_IsoSpeedControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameIsoSpeedControl IsoSpeedControl = {read=_scw_get_IsoSpeedControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Boolean _scw_get_PhotoConfirmationEnabled() { Winapi::Commontypes::_di_IReference_1__Boolean __r; HRESULT __hr = get_PhotoConfirmationEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Boolean PhotoConfirmationEnabled = {read=_scw_get_PhotoConfirmationEnabled, write=put_PhotoConfirmationEnabled};
};

__interface  INTERFACE_UUID("{1440DC88-63FF-5A01-BB93-390C76742488}") IIterator_1__Core_IFrameController_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B2B33445-0C84-5AA7-AF4A-C56B687CA08A}") IIterator_1__Core_IFrameController  : public IIterator_1__Core_IFrameController_Base 
{
	virtual HRESULT __safecall get_Current(_di_Core_IFrameController &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PCore_IFrameController items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameController _scw_get_Current() { _di_Core_IFrameController __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameController Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{BD8EEADC-2DD9-5AD8-AC5D-F3B13B94B9C2}") IIterable_1__Core_IFrameController_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{8AA6E634-4356-5E6C-84B1-77741B100001}") IIterable_1__Core_IFrameController  : public IIterable_1__Core_IFrameController_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Core_IFrameController &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{D7EBCF7F-B0F6-5389-A44D-FCDA72ACC22E}") IVectorView_1__Core_IFrameController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Core_IFrameController &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Core_IFrameController value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PCore_IFrameController items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{717903F3-0AAD-5328-B195-8F974C549255}") IVector_1__Core_IFrameController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Core_IFrameController &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__Core_IFrameController &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Core_IFrameController value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_Core_IFrameController value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_Core_IFrameController value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_Core_IFrameController value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PCore_IFrameController items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PCore_IFrameController items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{7FBFF880-ED8C-43FD-A7C3-B35809E4229A}") Core_IVariablePhotoSequenceController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_MaxPhotosPerSecond(float &__get_MaxPhotosPerSecond_result) = 0 ;
	virtual HRESULT __safecall get_PhotosPerSecondLimit(float &__get_PhotosPerSecondLimit_result) = 0 ;
	virtual HRESULT __safecall put_PhotosPerSecondLimit(float value) = 0 ;
	virtual HRESULT __safecall GetHighestConcurrentFrameRate(Winapi::Media::Mediaproperties::_di_IMediaEncodingProperties captureProperties, Winapi::Commontypes::_di_IMediaRatio &__GetHighestConcurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall GetCurrentFrameRate(Winapi::Commontypes::_di_IMediaRatio &__GetCurrentFrameRate_result) = 0 ;
	virtual HRESULT __safecall get_FrameCapabilities(_di_Core_IFrameControlCapabilities &__get_FrameCapabilities_result) = 0 ;
	virtual HRESULT __safecall get_DesiredFrameControllers(_di_IVector_1__Core_IFrameController &__get_DesiredFrameControllers_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__Core_IFrameController _scw_get_DesiredFrameControllers() { _di_IVector_1__Core_IFrameController __r; HRESULT __hr = get_DesiredFrameControllers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__Core_IFrameController DesiredFrameControllers = {read=_scw_get_DesiredFrameControllers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameControlCapabilities _scw_get_FrameCapabilities() { _di_Core_IFrameControlCapabilities __r; HRESULT __hr = get_FrameCapabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameControlCapabilities FrameCapabilities = {read=_scw_get_FrameCapabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_MaxPhotosPerSecond() { float __r; HRESULT __hr = get_MaxPhotosPerSecond(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float MaxPhotosPerSecond = {read=_scw_get_MaxPhotosPerSecond};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_PhotosPerSecondLimit() { float __r; HRESULT __hr = get_PhotosPerSecondLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float PhotosPerSecondLimit = {read=_scw_get_PhotosPerSecondLimit, write=put_PhotosPerSecondLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{C8F3F363-FF5E-4582-A9A8-0550F85A4A76}") IPhotoConfirmationControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_Enabled(bool &__get_Enabled_result) = 0 ;
	virtual HRESULT __safecall put_Enabled(bool value) = 0 ;
	virtual HRESULT __safecall get_PixelFormat(Winapi::Commontypes::MediaPixelFormat &__get_PixelFormat_result) = 0 ;
	virtual HRESULT __safecall put_PixelFormat(Winapi::Commontypes::MediaPixelFormat format) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Enabled() { bool __r; HRESULT __hr = get_Enabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Enabled = {read=_scw_get_Enabled, write=put_Enabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaPixelFormat _scw_get_PixelFormat() { Winapi::Commontypes::MediaPixelFormat __r; HRESULT __hr = get_PixelFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaPixelFormat PixelFormat = {read=_scw_get_PixelFormat, write=put_PixelFormat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{A98B8F34-EE0D-470C-B9F0-4229C4BBD089}") IAdvancedVideoCaptureDeviceController3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_VariablePhotoSequenceController(_di_Core_IVariablePhotoSequenceController &__get_VariablePhotoSequenceController_result) = 0 ;
	virtual HRESULT __safecall get_PhotoConfirmationControl(_di_IPhotoConfirmationControl &__get_PhotoConfirmationControl_result) = 0 ;
	virtual HRESULT __safecall get_ZoomControl(_di_IZoomControl &__get_ZoomControl_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPhotoConfirmationControl _scw_get_PhotoConfirmationControl() { _di_IPhotoConfirmationControl __r; HRESULT __hr = get_PhotoConfirmationControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPhotoConfirmationControl PhotoConfirmationControl = {read=_scw_get_PhotoConfirmationControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IVariablePhotoSequenceController _scw_get_VariablePhotoSequenceController() { _di_Core_IVariablePhotoSequenceController __r; HRESULT __hr = get_VariablePhotoSequenceController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IVariablePhotoSequenceController VariablePhotoSequenceController = {read=_scw_get_VariablePhotoSequenceController};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IZoomControl _scw_get_ZoomControl() { _di_IZoomControl __r; HRESULT __hr = get_ZoomControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IZoomControl ZoomControl = {read=_scw_get_ZoomControl};
};

__interface  INTERFACE_UUID("{EA9FBFAF-D371-41C3-9A17-824A87EBDFD2}") IAdvancedVideoCaptureDeviceController4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ExposurePriorityVideoControl(_di_IExposurePriorityVideoControl &__get_ExposurePriorityVideoControl_result) = 0 ;
	virtual HRESULT __safecall get_DesiredOptimization(Winapi::Commontypes::MediaCaptureOptimization &__get_DesiredOptimization_result) = 0 ;
	virtual HRESULT __safecall put_DesiredOptimization(Winapi::Commontypes::MediaCaptureOptimization value) = 0 ;
	virtual HRESULT __safecall get_HdrVideoControl(_di_IHdrVideoControl &__get_HdrVideoControl_result) = 0 ;
	virtual HRESULT __safecall get_OpticalImageStabilizationControl(_di_IOpticalImageStabilizationControl &__get_OpticalImageStabilizationControl_result) = 0 ;
	virtual HRESULT __safecall get_AdvancedPhotoControl(_di_IAdvancedPhotoControl &__get_AdvancedPhotoControl_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAdvancedPhotoControl _scw_get_AdvancedPhotoControl() { _di_IAdvancedPhotoControl __r; HRESULT __hr = get_AdvancedPhotoControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAdvancedPhotoControl AdvancedPhotoControl = {read=_scw_get_AdvancedPhotoControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MediaCaptureOptimization _scw_get_DesiredOptimization() { Winapi::Commontypes::MediaCaptureOptimization __r; HRESULT __hr = get_DesiredOptimization(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MediaCaptureOptimization DesiredOptimization = {read=_scw_get_DesiredOptimization, write=put_DesiredOptimization};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IExposurePriorityVideoControl _scw_get_ExposurePriorityVideoControl() { _di_IExposurePriorityVideoControl __r; HRESULT __hr = get_ExposurePriorityVideoControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IExposurePriorityVideoControl ExposurePriorityVideoControl = {read=_scw_get_ExposurePriorityVideoControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHdrVideoControl _scw_get_HdrVideoControl() { _di_IHdrVideoControl __r; HRESULT __hr = get_HdrVideoControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHdrVideoControl HdrVideoControl = {read=_scw_get_HdrVideoControl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IOpticalImageStabilizationControl _scw_get_OpticalImageStabilizationControl() { _di_IOpticalImageStabilizationControl __r; HRESULT __hr = get_OpticalImageStabilizationControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IOpticalImageStabilizationControl OpticalImageStabilizationControl = {read=_scw_get_OpticalImageStabilizationControl};
};

__interface  INTERFACE_UUID("{C5D88395-6ED5-4790-8B5D-0EF13935D0F8}") IVideoDeviceControllerGetDevicePropertyResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::VideoDeviceControllerGetDevicePropertyStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Winrt::_di_IInspectable &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::VideoDeviceControllerGetDevicePropertyStatus _scw_get_Status() { Winapi::Commontypes::VideoDeviceControllerGetDevicePropertyStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::VideoDeviceControllerGetDevicePropertyStatus Status = {read=_scw_get_Status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Value() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{33512B17-B9CB-4A23-B875-F9EAAB535492}") IAdvancedVideoCaptureDeviceController5  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall GetDevicePropertyById(HSTRING propertyId, Winapi::Perception::_di_IReference_1__Cardinal maxPropertyValueSize, _di_IVideoDeviceControllerGetDevicePropertyResult &__GetDevicePropertyById_result) = 0 ;
	virtual HRESULT __safecall SetDevicePropertyById(HSTRING propertyId, Winapi::Winrt::_di_IInspectable propertyValue, Winapi::Commontypes::VideoDeviceControllerSetDevicePropertyStatus &__SetDevicePropertyById_result) = 0 ;
	virtual HRESULT __safecall GetDevicePropertyByExtendedId(unsigned extendedPropertyIdSize, System::PByte extendedPropertyId, Winapi::Perception::_di_IReference_1__Cardinal maxPropertyValueSize, _di_IVideoDeviceControllerGetDevicePropertyResult &__GetDevicePropertyByExtendedId_result) = 0 ;
	virtual HRESULT __safecall SetDevicePropertyByExtendedId(unsigned extendedPropertyIdSize, System::PByte extendedPropertyId, System::Byte propertyValue, Winapi::Commontypes::VideoDeviceControllerSetDevicePropertyStatus &__SetDevicePropertyByExtendedId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
};

__interface  INTERFACE_UUID("{DE6FF4D3-2B96-4583-80AB-B5B01DC6A8D7}") IAdvancedVideoCaptureDeviceController  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetDeviceProperty(HSTRING propertyId, Winapi::Winrt::_di_IInspectable propertyValue) = 0 ;
	virtual HRESULT __safecall GetDeviceProperty(HSTRING propertyId, Winapi::Winrt::_di_IInspectable &__GetDeviceProperty_result) = 0 ;
};

__interface  INTERFACE_UUID("{BB9341A2-5EBE-4F62-8223-0E2B05BFBBD0}") Core_IFrameFlashCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Supported(bool &__get_Supported_result) = 0 ;
	virtual HRESULT __safecall get_RedEyeReductionSupported(bool &__get_RedEyeReductionSupported_result) = 0 ;
	virtual HRESULT __safecall get_PowerSupported(bool &__get_PowerSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_PowerSupported() { bool __r; HRESULT __hr = get_PowerSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool PowerSupported = {read=_scw_get_PowerSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_RedEyeReductionSupported() { bool __r; HRESULT __hr = get_RedEyeReductionSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool RedEyeReductionSupported = {read=_scw_get_RedEyeReductionSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Supported() { bool __r; HRESULT __hr = get_Supported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Supported = {read=_scw_get_Supported};
};

__interface  INTERFACE_UUID("{CE9B0464-4730-440F-BD3E-EFE8A8F230A8}") Core_IFrameControlCapabilities2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Flash(_di_Core_IFrameFlashCapabilities &__get_Flash_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameFlashCapabilities _scw_get_Flash() { _di_Core_IFrameFlashCapabilities __r; HRESULT __hr = get_Flash(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameFlashCapabilities Flash = {read=_scw_get_Flash};
};

__interface  INTERFACE_UUID("{75D5F6C7-BD45-4FAB-9375-45AC04B332C2}") Core_IFrameFlashControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::Core_FrameFlashMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::Core_FrameFlashMode value) = 0 ;
	virtual HRESULT __safecall get_Auto(bool &__get_Auto_result) = 0 ;
	virtual HRESULT __safecall put_Auto(bool value) = 0 ;
	virtual HRESULT __safecall get_RedEyeReduction(bool &__get_RedEyeReduction_result) = 0 ;
	virtual HRESULT __safecall put_RedEyeReduction(bool value) = 0 ;
	virtual HRESULT __safecall get_PowerPercent(float &__get_PowerPercent_result) = 0 ;
	virtual HRESULT __safecall put_PowerPercent(float value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Auto() { bool __r; HRESULT __hr = get_Auto(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Auto = {read=_scw_get_Auto, write=put_Auto};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Core_FrameFlashMode _scw_get_Mode() { Winapi::Commontypes::Core_FrameFlashMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Core_FrameFlashMode Mode = {read=_scw_get_Mode, write=put_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_PowerPercent() { float __r; HRESULT __hr = get_PowerPercent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float PowerPercent = {read=_scw_get_PowerPercent, write=put_PowerPercent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_RedEyeReduction() { bool __r; HRESULT __hr = get_RedEyeReduction(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool RedEyeReduction = {read=_scw_get_RedEyeReduction, write=put_RedEyeReduction};
};

__interface  INTERFACE_UUID("{00D3BC75-D87C-485B-8A09-5C358568B427}") Core_IFrameController2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_FlashControl(_di_Core_IFrameFlashControl &__get_FlashControl_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Core_IFrameFlashControl _scw_get_FlashControl() { _di_Core_IFrameFlashControl __r; HRESULT __hr = get_FlashControl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Core_IFrameFlashControl FlashControl = {read=_scw_get_FlashControl};
};

__interface  INTERFACE_UUID("{C0DDC486-2132-4A34-A659-9BFE2A055712}") Core_ICameraIntrinsicsFactory  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall Create(Winapi::Foundation::Types::Numerics_Vector2 focalLength, Winapi::Foundation::Types::Numerics_Vector2 principalPoint, Winapi::Commontypes::Numerics_Vector3 radialDistortion, Winapi::Foundation::Types::Numerics_Vector2 tangentialDistortion, unsigned imageWidth, unsigned imageHeight, _di_Core_ICameraIntrinsics &__Create_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall Create(Winapi::Foundation::Types::Numerics_Vector2 focalLength, Winapi::Foundation::Types::Numerics_Vector2 principalPoint, const Winapi::Commontypes::Numerics_Vector3 &radialDistortion, Winapi::Foundation::Types::Numerics_Vector2 tangentialDistortion, unsigned imageWidth, unsigned imageHeight, _di_Core_ICameraIntrinsics &__Create_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{0CDAA447-0798-4B4D-839F-C5EC414DB27A}") Core_ICameraIntrinsics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UndistortedProjectionTransform(Winapi::Commontypes::Numerics_Matrix4x4 &__get_UndistortedProjectionTransform_result) = 0 ;
	virtual HRESULT __safecall DistortPoint(System::Types::TPointF input, System::Types::TPointF &__DistortPoint_result) = 0 ;
	virtual HRESULT __safecall DistortPoints(unsigned inputsSize, System::Types::PPointF inputs, /* out */ System::Types::TPointF &results) = 0 ;
	virtual HRESULT __safecall UndistortPoint(System::Types::TPointF input, System::Types::TPointF &__UndistortPoint_result) = 0 ;
	virtual HRESULT __safecall UndistortPoints(unsigned inputsSize, System::Types::PPointF inputs, /* out */ System::Types::TPointF &results) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Numerics_Matrix4x4 _scw_get_UndistortedProjectionTransform() { Winapi::Commontypes::Numerics_Matrix4x4 __r; HRESULT __hr = get_UndistortedProjectionTransform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Numerics_Matrix4x4 UndistortedProjectionTransform = {read=_scw_get_UndistortedProjectionTransform};
};

__interface  INTERFACE_UUID("{037B929E-953C-4286-8866-4F0F376C855A}") IDialRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Handled() = 0 ;
	virtual HRESULT __safecall get_Contact(Winapi::Winrt::_di_IInspectable &__get_Contact_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Contact() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Contact(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Contact = {read=_scw_get_Contact};
};

__interface  INTERFACE_UUID("{7EB55209-76AB-4C31-B40E-4B58379D580C}") IRedialRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Handled() = 0 ;
};

__interface  INTERFACE_UUID("{D3A43900-B4FA-49CD-9442-89AF6568F601}") IKeypadPressedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_TelephonyKey(Winapi::Commontypes::TelephonyKey &__get_TelephonyKey_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TelephonyKey _scw_get_TelephonyKey() { Winapi::Commontypes::TelephonyKey __r; HRESULT __hr = get_TelephonyKey(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TelephonyKey TelephonyKey = {read=_scw_get_TelephonyKey};
};

__interface  INTERFACE_UUID("{5ABBFFDB-C21F-4BC4-891B-257E28C1B1A4}") DialRequestedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ICallControl sender, _di_IDialRequestedEventArgs e) = 0 ;
};

__interface  INTERFACE_UUID("{BAF257D1-4EBD-4B84-9F47-6EC43D75D8B1}") RedialRequestedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ICallControl sender, _di_IRedialRequestedEventArgs e) = 0 ;
};

__interface  INTERFACE_UUID("{E637A454-C527-422C-8926-C9AF83B559A0}") KeypadPressedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ICallControl sender, _di_IKeypadPressedEventArgs e) = 0 ;
};

__interface  INTERFACE_UUID("{A520D0D6-AE8D-45DB-8011-CA49D3B3E578}") ICallControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IndicateNewIncomingCall(bool enableRinger, HSTRING callerId, unsigned __int64 &__IndicateNewIncomingCall_result) = 0 ;
	virtual HRESULT __safecall IndicateNewOutgoingCall(unsigned __int64 &__IndicateNewOutgoingCall_result) = 0 ;
	virtual HRESULT __safecall IndicateActiveCall(unsigned __int64 callToken) = 0 ;
	virtual HRESULT __safecall EndCall(unsigned __int64 callToken) = 0 ;
	virtual HRESULT __safecall get_HasRinger(bool &__get_HasRinger_result) = 0 ;
	virtual HRESULT __safecall add_AnswerRequested(_di_CallControlEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_AnswerRequested_result) = 0 ;
	virtual HRESULT __safecall remove_AnswerRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_HangUpRequested(_di_CallControlEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_HangUpRequested_result) = 0 ;
	virtual HRESULT __safecall remove_HangUpRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_DialRequested(_di_DialRequestedEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_DialRequested_result) = 0 ;
	virtual HRESULT __safecall remove_DialRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_RedialRequested(_di_RedialRequestedEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_RedialRequested_result) = 0 ;
	virtual HRESULT __safecall remove_RedialRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_KeypadPressed(_di_KeypadPressedEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_KeypadPressed_result) = 0 ;
	virtual HRESULT __safecall remove_KeypadPressed(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_AudioTransferRequested(_di_CallControlEventHandler handler, Winapi::Commontypes::EventRegistrationToken &__add_AudioTransferRequested_result) = 0 ;
	virtual HRESULT __safecall remove_AudioTransferRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasRinger() { bool __r; HRESULT __hr = get_HasRinger(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasRinger = {read=_scw_get_HasRinger};
};

__interface  INTERFACE_UUID("{596F759F-50DF-4454-BC63-4D3D01B61958}") CallControlEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ICallControl sender) = 0 ;
};

__interface  INTERFACE_UUID("{03945AD5-85AB-40E1-AF19-56C94303B019}") ICallControlStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefault(_di_ICallControl &__GetDefault_result) = 0 ;
	virtual HRESULT __safecall FromId(HSTRING deviceId, _di_ICallControl &__FromId_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAudioDeviceModulesManager : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAudioDeviceModulesManagerFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAudioDeviceModulesManagerFactory> inherited;
	
public:
	static _di_IAudioDeviceModulesManager __fastcall Create(HSTRING deviceId);
public:
	/* TObject.Create */ inline __fastcall TAudioDeviceModulesManager() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAudioDeviceModulesManagerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAudioDeviceModulesManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TZoomSettings : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IZoomSettings>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IZoomSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TZoomSettings() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IZoomSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TZoomSettings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFocusSettings : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IFocusSettings>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IFocusSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TFocusSettings() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IFocusSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFocusSettings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRegionOfInterest : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IRegionOfInterest>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IRegionOfInterest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TRegionOfInterest() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IRegionOfInterest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRegionOfInterest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAdvancedPhotoCaptureSettings : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IAdvancedPhotoCaptureSettings>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IAdvancedPhotoCaptureSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TAdvancedPhotoCaptureSettings() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IAdvancedPhotoCaptureSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAdvancedPhotoCaptureSettings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_FrameController : public System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_IFrameController>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_IFrameController> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TCore_FrameController() : System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_IFrameController>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_FrameController() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCallControl : public System::Win::Winrt::TWinRTGenericImportS__1<_di_ICallControlStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_ICallControlStatics> inherited;
	
public:
	static _di_ICallControl __fastcall GetDefault();
	static _di_ICallControl __fastcall FromId(HSTRING deviceId);
public:
	/* TObject.Create */ inline __fastcall TCallControl() : System::Win::Winrt::TWinRTGenericImportS__1<_di_ICallControlStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCallControl() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Devices */
}	/* namespace Media */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Media_DevicesHPP
