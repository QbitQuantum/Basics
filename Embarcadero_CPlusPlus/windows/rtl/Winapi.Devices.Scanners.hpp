// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Scanners.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_ScannersHPP
#define Winapi_Devices_ScannersHPP

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
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Scanners
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IImageScannerFormatConfiguration;
typedef System::DelphiInterface<IImageScannerFormatConfiguration> _di_IImageScannerFormatConfiguration;
__interface DELPHIINTERFACE IImageScannerSourceConfiguration;
typedef System::DelphiInterface<IImageScannerSourceConfiguration> _di_IImageScannerSourceConfiguration;
__interface DELPHIINTERFACE IImageScannerFeederConfiguration;
typedef System::DelphiInterface<IImageScannerFeederConfiguration> _di_IImageScannerFeederConfiguration;
__interface DELPHIINTERFACE IImageScannerPreviewResult;
typedef System::DelphiInterface<IImageScannerPreviewResult> _di_IImageScannerPreviewResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IImageScannerPreviewResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IImageScannerPreviewResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IImageScannerPreviewResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IImageScannerPreviewResult> _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IImageScannerPreviewResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IImageScannerPreviewResult_Base> _di_IAsyncOperation_1__IImageScannerPreviewResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IImageScannerPreviewResult;
typedef System::DelphiInterface<IAsyncOperation_1__IImageScannerPreviewResult> _di_IAsyncOperation_1__IImageScannerPreviewResult;
__interface DELPHIINTERFACE IImageScanner;
typedef System::DelphiInterface<IImageScanner> _di_IImageScanner;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IImageScanner_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IImageScanner_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IImageScanner_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IImageScanner;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IImageScanner> _di_AsyncOperationCompletedHandler_1__IImageScanner;
__interface DELPHIINTERFACE IAsyncOperation_1__IImageScanner_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IImageScanner_Base> _di_IAsyncOperation_1__IImageScanner_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IImageScanner;
typedef System::DelphiInterface<IAsyncOperation_1__IImageScanner> _di_IAsyncOperation_1__IImageScanner;
__interface DELPHIINTERFACE IImageScannerStatics;
typedef System::DelphiInterface<IImageScannerStatics> _di_IImageScannerStatics;
class DELPHICLASS TImageScanner;
//-- type declarations -------------------------------------------------------
typedef _di_IImageScannerFormatConfiguration *PIImageScannerFormatConfiguration;

typedef _di_IImageScannerSourceConfiguration *PIImageScannerSourceConfiguration;

typedef _di_IImageScannerFeederConfiguration *PIImageScannerFeederConfiguration;

typedef _di_IImageScannerPreviewResult *PIImageScannerPreviewResult;

typedef _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult *PAsyncOperationCompletedHandler_1__IImageScannerPreviewResult;

typedef _di_IAsyncOperation_1__IImageScannerPreviewResult *PIAsyncOperation_1__IImageScannerPreviewResult;

typedef _di_IImageScanner *PIImageScanner;

typedef _di_AsyncOperationCompletedHandler_1__IImageScanner *PAsyncOperationCompletedHandler_1__IImageScanner;

typedef _di_IAsyncOperation_1__IImageScanner *PIAsyncOperation_1__IImageScanner;

typedef _di_IImageScannerStatics *PIImageScannerStatics;

__interface  INTERFACE_UUID("{AE275D11-DADF-4010-BF10-CCA5C83DCBB0}") IImageScannerFormatConfiguration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DefaultFormat(Winapi::Commontypes::ImageScannerFormat &__get_DefaultFormat_result) = 0 ;
	virtual HRESULT __safecall get_Format(Winapi::Commontypes::ImageScannerFormat &__get_Format_result) = 0 ;
	virtual HRESULT __safecall put_Format(Winapi::Commontypes::ImageScannerFormat value) = 0 ;
	virtual HRESULT __safecall IsFormatSupported(Winapi::Commontypes::ImageScannerFormat value, bool &__IsFormatSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerFormat _scw_get_DefaultFormat() { Winapi::Commontypes::ImageScannerFormat __r; HRESULT __hr = get_DefaultFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerFormat DefaultFormat = {read=_scw_get_DefaultFormat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerFormat _scw_get_Format() { Winapi::Commontypes::ImageScannerFormat __r; HRESULT __hr = get_Format(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerFormat Format = {read=_scw_get_Format, write=put_Format};
};

__interface  INTERFACE_UUID("{BFB50055-0B44-4C82-9E89-205F9C234E59}") IImageScannerSourceConfiguration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MinScanArea(System::Types::TSizeF &__get_MinScanArea_result) = 0 ;
	virtual HRESULT __safecall get_MaxScanArea(System::Types::TSizeF &__get_MaxScanArea_result) = 0 ;
	virtual HRESULT __safecall get_SelectedScanRegion(System::Types::TRectF &__get_SelectedScanRegion_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_SelectedScanRegion(System::Types::TRectF value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_SelectedScanRegion(const System::Types::TRectF &value) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall get_AutoCroppingMode(Winapi::Commontypes::ImageScannerAutoCroppingMode &__get_AutoCroppingMode_result) = 0 ;
	virtual HRESULT __safecall put_AutoCroppingMode(Winapi::Commontypes::ImageScannerAutoCroppingMode value) = 0 ;
	virtual HRESULT __safecall IsAutoCroppingModeSupported(Winapi::Commontypes::ImageScannerAutoCroppingMode value, bool &__IsAutoCroppingModeSupported_result) = 0 ;
	virtual HRESULT __safecall get_MinResolution(Winapi::Commontypes::ImageScannerResolution &__get_MinResolution_result) = 0 ;
	virtual HRESULT __safecall get_MaxResolution(Winapi::Commontypes::ImageScannerResolution &__get_MaxResolution_result) = 0 ;
	virtual HRESULT __safecall get_OpticalResolution(Winapi::Commontypes::ImageScannerResolution &__get_OpticalResolution_result) = 0 ;
	virtual HRESULT __safecall get_DesiredResolution(Winapi::Commontypes::ImageScannerResolution &__get_DesiredResolution_result) = 0 ;
	virtual HRESULT __safecall put_DesiredResolution(Winapi::Commontypes::ImageScannerResolution value) = 0 ;
	virtual HRESULT __safecall get_ActualResolution(Winapi::Commontypes::ImageScannerResolution &__get_ActualResolution_result) = 0 ;
	virtual HRESULT __safecall get_DefaultColorMode(Winapi::Commontypes::ImageScannerColorMode &__get_DefaultColorMode_result) = 0 ;
	virtual HRESULT __safecall get_ColorMode(Winapi::Commontypes::ImageScannerColorMode &__get_ColorMode_result) = 0 ;
	virtual HRESULT __safecall put_ColorMode(Winapi::Commontypes::ImageScannerColorMode value) = 0 ;
	virtual HRESULT __safecall IsColorModeSupported(Winapi::Commontypes::ImageScannerColorMode value, bool &__IsColorModeSupported_result) = 0 ;
	virtual HRESULT __safecall get_MinBrightness(int &__get_MinBrightness_result) = 0 ;
	virtual HRESULT __safecall get_MaxBrightness(int &__get_MaxBrightness_result) = 0 ;
	virtual HRESULT __safecall get_BrightnessStep(unsigned &__get_BrightnessStep_result) = 0 ;
	virtual HRESULT __safecall get_DefaultBrightness(int &__get_DefaultBrightness_result) = 0 ;
	virtual HRESULT __safecall get_Brightness(int &__get_Brightness_result) = 0 ;
	virtual HRESULT __safecall put_Brightness(int value) = 0 ;
	virtual HRESULT __safecall get_MinContrast(int &__get_MinContrast_result) = 0 ;
	virtual HRESULT __safecall get_MaxContrast(int &__get_MaxContrast_result) = 0 ;
	virtual HRESULT __safecall get_ContrastStep(unsigned &__get_ContrastStep_result) = 0 ;
	virtual HRESULT __safecall get_DefaultContrast(int &__get_DefaultContrast_result) = 0 ;
	virtual HRESULT __safecall get_Contrast(int &__get_Contrast_result) = 0 ;
	virtual HRESULT __safecall put_Contrast(int value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerResolution _scw_get_ActualResolution() { Winapi::Commontypes::ImageScannerResolution __r; HRESULT __hr = get_ActualResolution(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerResolution ActualResolution = {read=_scw_get_ActualResolution};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerAutoCroppingMode _scw_get_AutoCroppingMode() { Winapi::Commontypes::ImageScannerAutoCroppingMode __r; HRESULT __hr = get_AutoCroppingMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerAutoCroppingMode AutoCroppingMode = {read=_scw_get_AutoCroppingMode, write=put_AutoCroppingMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Brightness() { int __r; HRESULT __hr = get_Brightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Brightness = {read=_scw_get_Brightness, write=put_Brightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_BrightnessStep() { unsigned __r; HRESULT __hr = get_BrightnessStep(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned BrightnessStep = {read=_scw_get_BrightnessStep};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerColorMode _scw_get_ColorMode() { Winapi::Commontypes::ImageScannerColorMode __r; HRESULT __hr = get_ColorMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerColorMode ColorMode = {read=_scw_get_ColorMode, write=put_ColorMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Contrast() { int __r; HRESULT __hr = get_Contrast(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Contrast = {read=_scw_get_Contrast, write=put_Contrast};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ContrastStep() { unsigned __r; HRESULT __hr = get_ContrastStep(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ContrastStep = {read=_scw_get_ContrastStep};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_DefaultBrightness() { int __r; HRESULT __hr = get_DefaultBrightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int DefaultBrightness = {read=_scw_get_DefaultBrightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerColorMode _scw_get_DefaultColorMode() { Winapi::Commontypes::ImageScannerColorMode __r; HRESULT __hr = get_DefaultColorMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerColorMode DefaultColorMode = {read=_scw_get_DefaultColorMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_DefaultContrast() { int __r; HRESULT __hr = get_DefaultContrast(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int DefaultContrast = {read=_scw_get_DefaultContrast};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerResolution _scw_get_DesiredResolution() { Winapi::Commontypes::ImageScannerResolution __r; HRESULT __hr = get_DesiredResolution(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerResolution DesiredResolution = {read=_scw_get_DesiredResolution, write=put_DesiredResolution};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MaxBrightness() { int __r; HRESULT __hr = get_MaxBrightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MaxBrightness = {read=_scw_get_MaxBrightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MaxContrast() { int __r; HRESULT __hr = get_MaxContrast(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MaxContrast = {read=_scw_get_MaxContrast};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerResolution _scw_get_MaxResolution() { Winapi::Commontypes::ImageScannerResolution __r; HRESULT __hr = get_MaxResolution(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerResolution MaxResolution = {read=_scw_get_MaxResolution};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_MaxScanArea() { System::Types::TSizeF __r; HRESULT __hr = get_MaxScanArea(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF MaxScanArea = {read=_scw_get_MaxScanArea};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MinBrightness() { int __r; HRESULT __hr = get_MinBrightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MinBrightness = {read=_scw_get_MinBrightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MinContrast() { int __r; HRESULT __hr = get_MinContrast(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MinContrast = {read=_scw_get_MinContrast};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerResolution _scw_get_MinResolution() { Winapi::Commontypes::ImageScannerResolution __r; HRESULT __hr = get_MinResolution(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerResolution MinResolution = {read=_scw_get_MinResolution};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_MinScanArea() { System::Types::TSizeF __r; HRESULT __hr = get_MinScanArea(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF MinScanArea = {read=_scw_get_MinScanArea};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerResolution _scw_get_OpticalResolution() { Winapi::Commontypes::ImageScannerResolution __r; HRESULT __hr = get_OpticalResolution(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerResolution OpticalResolution = {read=_scw_get_OpticalResolution};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_SelectedScanRegion() { System::Types::TRectF __r; HRESULT __hr = get_SelectedScanRegion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF SelectedScanRegion = {read=_scw_get_SelectedScanRegion, write=put_SelectedScanRegion};
};

__interface  INTERFACE_UUID("{74BDACEE-FA97-4C17-8280-40E39C6DCC67}") IImageScannerFeederConfiguration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CanAutoDetectPageSize(bool &__get_CanAutoDetectPageSize_result) = 0 ;
	virtual HRESULT __safecall get_AutoDetectPageSize(bool &__get_AutoDetectPageSize_result) = 0 ;
	virtual HRESULT __safecall put_AutoDetectPageSize(bool value) = 0 ;
	virtual HRESULT __safecall get_PageSize(Winapi::Commontypes::Printing_PrintMediaSize &__get_PageSize_result) = 0 ;
	virtual HRESULT __safecall put_PageSize(Winapi::Commontypes::Printing_PrintMediaSize value) = 0 ;
	virtual HRESULT __safecall get_PageOrientation(Winapi::Commontypes::Printing_PrintOrientation &__get_PageOrientation_result) = 0 ;
	virtual HRESULT __safecall put_PageOrientation(Winapi::Commontypes::Printing_PrintOrientation value) = 0 ;
	virtual HRESULT __safecall get_PageSizeDimensions(System::Types::TSizeF &__get_PageSizeDimensions_result) = 0 ;
	virtual HRESULT __safecall IsPageSizeSupported(Winapi::Commontypes::Printing_PrintMediaSize pageSize, Winapi::Commontypes::Printing_PrintOrientation pageOrientation, bool &__IsPageSizeSupported_result) = 0 ;
	virtual HRESULT __safecall get_MaxNumberOfPages(unsigned &__get_MaxNumberOfPages_result) = 0 ;
	virtual HRESULT __safecall put_MaxNumberOfPages(unsigned value) = 0 ;
	virtual HRESULT __safecall get_CanScanDuplex(bool &__get_CanScanDuplex_result) = 0 ;
	virtual HRESULT __safecall get_Duplex(bool &__get_Duplex_result) = 0 ;
	virtual HRESULT __safecall put_Duplex(bool value) = 0 ;
	virtual HRESULT __safecall get_CanScanAhead(bool &__get_CanScanAhead_result) = 0 ;
	virtual HRESULT __safecall get_ScanAhead(bool &__get_ScanAhead_result) = 0 ;
	virtual HRESULT __safecall put_ScanAhead(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AutoDetectPageSize() { bool __r; HRESULT __hr = get_AutoDetectPageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AutoDetectPageSize = {read=_scw_get_AutoDetectPageSize, write=put_AutoDetectPageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanAutoDetectPageSize() { bool __r; HRESULT __hr = get_CanAutoDetectPageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanAutoDetectPageSize = {read=_scw_get_CanAutoDetectPageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanScanAhead() { bool __r; HRESULT __hr = get_CanScanAhead(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanScanAhead = {read=_scw_get_CanScanAhead};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanScanDuplex() { bool __r; HRESULT __hr = get_CanScanDuplex(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanScanDuplex = {read=_scw_get_CanScanDuplex};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Duplex() { bool __r; HRESULT __hr = get_Duplex(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Duplex = {read=_scw_get_Duplex, write=put_Duplex};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxNumberOfPages() { unsigned __r; HRESULT __hr = get_MaxNumberOfPages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxNumberOfPages = {read=_scw_get_MaxNumberOfPages, write=put_MaxNumberOfPages};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Printing_PrintOrientation _scw_get_PageOrientation() { Winapi::Commontypes::Printing_PrintOrientation __r; HRESULT __hr = get_PageOrientation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Printing_PrintOrientation PageOrientation = {read=_scw_get_PageOrientation, write=put_PageOrientation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Printing_PrintMediaSize _scw_get_PageSize() { Winapi::Commontypes::Printing_PrintMediaSize __r; HRESULT __hr = get_PageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Printing_PrintMediaSize PageSize = {read=_scw_get_PageSize, write=put_PageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_PageSizeDimensions() { System::Types::TSizeF __r; HRESULT __hr = get_PageSizeDimensions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF PageSizeDimensions = {read=_scw_get_PageSizeDimensions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ScanAhead() { bool __r; HRESULT __hr = get_ScanAhead(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ScanAhead = {read=_scw_get_ScanAhead, write=put_ScanAhead};
};

__interface  INTERFACE_UUID("{08B7FE8E-8891-441D-BE9C-176FA109C8BB}") IImageScannerPreviewResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Succeeded(bool &__get_Succeeded_result) = 0 ;
	virtual HRESULT __safecall get_Format(Winapi::Commontypes::ImageScannerFormat &__get_Format_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerFormat _scw_get_Format() { Winapi::Commontypes::ImageScannerFormat __r; HRESULT __hr = get_Format(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerFormat Format = {read=_scw_get_Format};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Succeeded() { bool __r; HRESULT __hr = get_Succeeded(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Succeeded = {read=_scw_get_Succeeded};
};

__interface  INTERFACE_UUID("{C054A410-AC3C-5353-B1EE-E85E78FAF3F1}") AsyncOperationCompletedHandler_1__IImageScannerPreviewResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{96C784BC-119C-557A-8D28-405AF877D7B2}") AsyncOperationCompletedHandler_1__IImageScannerPreviewResult  : public AsyncOperationCompletedHandler_1__IImageScannerPreviewResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IImageScannerPreviewResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2F74576F-0498-5348-BC3B-A70D1A771718}") IAsyncOperation_1__IImageScannerPreviewResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2EE5CD44-9985-5C27-9C6A-32A92405B896}") IAsyncOperation_1__IImageScannerPreviewResult  : public IAsyncOperation_1__IImageScannerPreviewResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IImageScannerPreviewResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IImageScannerPreviewResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{53A88F78-5298-48A0-8DA3-8087519665E0}") IImageScanner  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_DefaultScanSource(Winapi::Commontypes::ImageScannerScanSource &__get_DefaultScanSource_result) = 0 ;
	virtual HRESULT __safecall IsScanSourceSupported(Winapi::Commontypes::ImageScannerScanSource value, bool &__IsScanSourceSupported_result) = 0 ;
	virtual HRESULT __safecall get_FlatbedConfiguration(_di_IImageScannerFormatConfiguration &__get_FlatbedConfiguration_result) = 0 ;
	virtual HRESULT __safecall get_FeederConfiguration(_di_IImageScannerFormatConfiguration &__get_FeederConfiguration_result) = 0 ;
	virtual HRESULT __safecall get_AutoConfiguration(_di_IImageScannerFormatConfiguration &__get_AutoConfiguration_result) = 0 ;
	virtual HRESULT __safecall IsPreviewSupported(Winapi::Commontypes::ImageScannerScanSource scanSource, bool &__IsPreviewSupported_result) = 0 ;
	virtual HRESULT __safecall ScanPreviewToStreamAsync(Winapi::Commontypes::ImageScannerScanSource scanSource, Winapi::Commontypes::_di_IRandomAccessStream targetStream, _di_IAsyncOperation_1__IImageScannerPreviewResult &__ScanPreviewToStreamAsync_result) = 0 ;
	virtual HRESULT __safecall ScanFilesToFolderAsync(Winapi::Commontypes::ImageScannerScanSource scanSource, Winapi::Commontypes::_di_IStorageFolder storageFolder, Winapi::Commontypes::_di_IAsyncOperationWithProgress_2__IImageScannerScanResult__Cardinal &__ScanFilesToFolderAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IImageScannerFormatConfiguration _scw_get_AutoConfiguration() { _di_IImageScannerFormatConfiguration __r; HRESULT __hr = get_AutoConfiguration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IImageScannerFormatConfiguration AutoConfiguration = {read=_scw_get_AutoConfiguration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ImageScannerScanSource _scw_get_DefaultScanSource() { Winapi::Commontypes::ImageScannerScanSource __r; HRESULT __hr = get_DefaultScanSource(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ImageScannerScanSource DefaultScanSource = {read=_scw_get_DefaultScanSource};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IImageScannerFormatConfiguration _scw_get_FeederConfiguration() { _di_IImageScannerFormatConfiguration __r; HRESULT __hr = get_FeederConfiguration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IImageScannerFormatConfiguration FeederConfiguration = {read=_scw_get_FeederConfiguration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IImageScannerFormatConfiguration _scw_get_FlatbedConfiguration() { _di_IImageScannerFormatConfiguration __r; HRESULT __hr = get_FlatbedConfiguration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IImageScannerFormatConfiguration FlatbedConfiguration = {read=_scw_get_FlatbedConfiguration};
};

__interface  INTERFACE_UUID("{B35AD6B4-0DA0-5241-87FF-EEF3A1883243}") AsyncOperationCompletedHandler_1__IImageScanner_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{60E91BF4-CA9E-57D7-AC8C-BA5180FFAECD}") AsyncOperationCompletedHandler_1__IImageScanner  : public AsyncOperationCompletedHandler_1__IImageScanner_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IImageScanner asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{75D78736-6C52-551E-AB5F-50674F323431}") IAsyncOperation_1__IImageScanner_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{279D0851-470C-54D1-8873-F2C5FD62A1DB}") IAsyncOperation_1__IImageScanner  : public IAsyncOperation_1__IImageScanner_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IImageScanner handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IImageScanner &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IImageScanner &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IImageScanner _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IImageScanner __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IImageScanner Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{BC57E70E-D804-4477-9FB5-B911B5473897}") IImageScannerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IImageScanner &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TImageScanner : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IImageScannerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IImageScannerStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IImageScanner __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector();
public:
	/* TObject.Create */ inline __fastcall TImageScanner() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IImageScannerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TImageScanner() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Scanners */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_ScannersHPP
