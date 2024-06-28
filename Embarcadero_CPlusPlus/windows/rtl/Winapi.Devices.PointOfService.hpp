// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.PointOfService.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_PointofserviceHPP
#define Winapi_Devices_PointofserviceHPP

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
#include <Winapi.GraphicsRT.hpp>
#include <Winapi.Foundation.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Pointofservice
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IBarcodeSymbologyAttributes;
typedef System::DelphiInterface<IBarcodeSymbologyAttributes> _di_IBarcodeSymbologyAttributes;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes> _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes;
__interface DELPHIINTERFACE IAsyncOperation_1__IBarcodeSymbologyAttributes_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IBarcodeSymbologyAttributes_Base> _di_IAsyncOperation_1__IBarcodeSymbologyAttributes_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IBarcodeSymbologyAttributes;
typedef System::DelphiInterface<IAsyncOperation_1__IBarcodeSymbologyAttributes> _di_IAsyncOperation_1__IBarcodeSymbologyAttributes;
__interface DELPHIINTERFACE IPosPrinterCharacterSetIdsStatics;
typedef System::DelphiInterface<IPosPrinterCharacterSetIdsStatics> _di_IPosPrinterCharacterSetIdsStatics;
__interface DELPHIINTERFACE ICommonPosPrintStationCapabilities;
typedef System::DelphiInterface<ICommonPosPrintStationCapabilities> _di_ICommonPosPrintStationCapabilities;
__interface DELPHIINTERFACE IIterator_1__PosPrinterRotation_Base;
typedef System::DelphiInterface<IIterator_1__PosPrinterRotation_Base> _di_IIterator_1__PosPrinterRotation_Base;
__interface DELPHIINTERFACE IIterator_1__PosPrinterRotation;
typedef System::DelphiInterface<IIterator_1__PosPrinterRotation> _di_IIterator_1__PosPrinterRotation;
__interface DELPHIINTERFACE IIterable_1__PosPrinterRotation_Base;
typedef System::DelphiInterface<IIterable_1__PosPrinterRotation_Base> _di_IIterable_1__PosPrinterRotation_Base;
__interface DELPHIINTERFACE IIterable_1__PosPrinterRotation;
typedef System::DelphiInterface<IIterable_1__PosPrinterRotation> _di_IIterable_1__PosPrinterRotation;
__interface DELPHIINTERFACE IVectorView_1__PosPrinterRotation;
typedef System::DelphiInterface<IVectorView_1__PosPrinterRotation> _di_IVectorView_1__PosPrinterRotation;
__interface DELPHIINTERFACE ICommonReceiptSlipCapabilities;
typedef System::DelphiInterface<ICommonReceiptSlipCapabilities> _di_ICommonReceiptSlipCapabilities;
__interface DELPHIINTERFACE IReceiptPrinterCapabilities;
typedef System::DelphiInterface<IReceiptPrinterCapabilities> _di_IReceiptPrinterCapabilities;
__interface DELPHIINTERFACE ISlipPrinterCapabilities;
typedef System::DelphiInterface<ISlipPrinterCapabilities> _di_ISlipPrinterCapabilities;
__interface DELPHIINTERFACE IJournalPrinterCapabilities;
typedef System::DelphiInterface<IJournalPrinterCapabilities> _di_IJournalPrinterCapabilities;
__interface DELPHIINTERFACE IPosPrinterCapabilities;
typedef System::DelphiInterface<IPosPrinterCapabilities> _di_IPosPrinterCapabilities;
__interface DELPHIINTERFACE IPosPrinterStatus;
typedef System::DelphiInterface<IPosPrinterStatus> _di_IPosPrinterStatus;
__interface DELPHIINTERFACE IPosPrinterStatusUpdatedEventArgs;
typedef System::DelphiInterface<IPosPrinterStatusUpdatedEventArgs> _di_IPosPrinterStatusUpdatedEventArgs;
__interface DELPHIINTERFACE IPosPrinterReleaseDeviceRequestedEventArgs;
typedef System::DelphiInterface<IPosPrinterReleaseDeviceRequestedEventArgs> _di_IPosPrinterReleaseDeviceRequestedEventArgs;
__interface DELPHIINTERFACE ICommonClaimedPosPrinterStation;
typedef System::DelphiInterface<ICommonClaimedPosPrinterStation> _di_ICommonClaimedPosPrinterStation;
__interface DELPHIINTERFACE IPosPrinterJob;
typedef System::DelphiInterface<IPosPrinterJob> _di_IPosPrinterJob;
__interface DELPHIINTERFACE IReceiptOrSlipJob;
typedef System::DelphiInterface<IReceiptOrSlipJob> _di_IReceiptOrSlipJob;
__interface DELPHIINTERFACE IReceiptPrintJob;
typedef System::DelphiInterface<IReceiptPrintJob> _di_IReceiptPrintJob;
__interface DELPHIINTERFACE IClaimedReceiptPrinter;
typedef System::DelphiInterface<IClaimedReceiptPrinter> _di_IClaimedReceiptPrinter;
__interface DELPHIINTERFACE IClaimedSlipPrinter;
typedef System::DelphiInterface<IClaimedSlipPrinter> _di_IClaimedSlipPrinter;
__interface DELPHIINTERFACE IClaimedJournalPrinter;
typedef System::DelphiInterface<IClaimedJournalPrinter> _di_IClaimedJournalPrinter;
__interface DELPHIINTERFACE TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs> _di_TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs;
__interface DELPHIINTERFACE IClaimedPosPrinter;
typedef System::DelphiInterface<IClaimedPosPrinter> _di_IClaimedPosPrinter;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedPosPrinter_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedPosPrinter_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedPosPrinter;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedPosPrinter> _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedPosPrinter_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedPosPrinter_Base> _di_IAsyncOperation_1__IClaimedPosPrinter_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedPosPrinter;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedPosPrinter> _di_IAsyncOperation_1__IClaimedPosPrinter;
__interface DELPHIINTERFACE TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs> _di_TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs;
__interface DELPHIINTERFACE IPosPrinter;
typedef System::DelphiInterface<IPosPrinter> _di_IPosPrinter;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IPosPrinter_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IPosPrinter_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IPosPrinter_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IPosPrinter;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IPosPrinter> _di_AsyncOperationCompletedHandler_1__IPosPrinter;
__interface DELPHIINTERFACE IAsyncOperation_1__IPosPrinter_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IPosPrinter_Base> _di_IAsyncOperation_1__IPosPrinter_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IPosPrinter;
typedef System::DelphiInterface<IAsyncOperation_1__IPosPrinter> _di_IAsyncOperation_1__IPosPrinter;
__interface DELPHIINTERFACE IPosPrinterStatics;
typedef System::DelphiInterface<IPosPrinterStatics> _di_IPosPrinterStatics;
__interface DELPHIINTERFACE IPosPrinterStatics2;
typedef System::DelphiInterface<IPosPrinterStatics2> _di_IPosPrinterStatics2;
__interface DELPHIINTERFACE ICashDrawerStatus;
typedef System::DelphiInterface<ICashDrawerStatus> _di_ICashDrawerStatus;
__interface DELPHIINTERFACE ICashDrawerStatusUpdatedEventArgs;
typedef System::DelphiInterface<ICashDrawerStatusUpdatedEventArgs> _di_ICashDrawerStatusUpdatedEventArgs;
__interface DELPHIINTERFACE ICashDrawerCapabilities;
typedef System::DelphiInterface<ICashDrawerCapabilities> _di_ICashDrawerCapabilities;
__interface DELPHIINTERFACE TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs> _di_TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs;
__interface DELPHIINTERFACE ICashDrawerEventSource;
typedef System::DelphiInterface<ICashDrawerEventSource> _di_ICashDrawerEventSource;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedCashDrawer_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedCashDrawer_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedCashDrawer;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedCashDrawer> _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedCashDrawer_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedCashDrawer_Base> _di_IAsyncOperation_1__IClaimedCashDrawer_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedCashDrawer;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedCashDrawer> _di_IAsyncOperation_1__IClaimedCashDrawer;
__interface DELPHIINTERFACE TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs_Delegate_Base> _di_TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs> _di_TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs;
__interface DELPHIINTERFACE ICashDrawer;
typedef System::DelphiInterface<ICashDrawer> _di_ICashDrawer;
__interface DELPHIINTERFACE ICashDrawerEventSourceEventArgs;
typedef System::DelphiInterface<ICashDrawerEventSourceEventArgs> _di_ICashDrawerEventSourceEventArgs;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ICashDrawer_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ICashDrawer_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ICashDrawer_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ICashDrawer;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ICashDrawer> _di_AsyncOperationCompletedHandler_1__ICashDrawer;
__interface DELPHIINTERFACE IAsyncOperation_1__ICashDrawer_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ICashDrawer_Base> _di_IAsyncOperation_1__ICashDrawer_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ICashDrawer;
typedef System::DelphiInterface<IAsyncOperation_1__ICashDrawer> _di_IAsyncOperation_1__ICashDrawer;
__interface DELPHIINTERFACE ICashDrawerStatics;
typedef System::DelphiInterface<ICashDrawerStatics> _di_ICashDrawerStatics;
__interface DELPHIINTERFACE ICashDrawerStatics2;
typedef System::DelphiInterface<ICashDrawerStatics2> _di_ICashDrawerStatics2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedLineDisplay_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedLineDisplay_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IClaimedLineDisplay;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IClaimedLineDisplay> _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedLineDisplay_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedLineDisplay_Base> _di_IAsyncOperation_1__IClaimedLineDisplay_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IClaimedLineDisplay;
typedef System::DelphiInterface<IAsyncOperation_1__IClaimedLineDisplay> _di_IAsyncOperation_1__IClaimedLineDisplay;
__interface DELPHIINTERFACE ILineDisplay;
typedef System::DelphiInterface<ILineDisplay> _di_ILineDisplay;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplay_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplay_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ILineDisplay_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplay;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplay> _di_AsyncOperationCompletedHandler_1__ILineDisplay;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplay_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplay_Base> _di_IAsyncOperation_1__ILineDisplay_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplay;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplay> _di_IAsyncOperation_1__ILineDisplay;
__interface DELPHIINTERFACE ILineDisplayStatics;
typedef System::DelphiInterface<ILineDisplayStatics> _di_ILineDisplayStatics;
__interface DELPHIINTERFACE ILineDisplayStatisticsCategorySelector;
typedef System::DelphiInterface<ILineDisplayStatisticsCategorySelector> _di_ILineDisplayStatisticsCategorySelector;
__interface DELPHIINTERFACE ILineDisplayStatics2;
typedef System::DelphiInterface<ILineDisplayStatics2> _di_ILineDisplayStatics2;
__interface DELPHIINTERFACE IClaimedLineDisplayStatics;
typedef System::DelphiInterface<IClaimedLineDisplayStatics> _di_IClaimedLineDisplayStatics;
__interface DELPHIINTERFACE ILineDisplayCursorAttributes;
typedef System::DelphiInterface<ILineDisplayCursorAttributes> _di_ILineDisplayCursorAttributes;
__interface DELPHIINTERFACE ILineDisplayCursor;
typedef System::DelphiInterface<ILineDisplayCursor> _di_ILineDisplayCursor;
__interface DELPHIINTERFACE ILineDisplayMarquee;
typedef System::DelphiInterface<ILineDisplayMarquee> _di_ILineDisplayMarquee;
__interface DELPHIINTERFACE ILineDisplayStoredBitmap;
typedef System::DelphiInterface<ILineDisplayStoredBitmap> _di_ILineDisplayStoredBitmap;
__interface DELPHIINTERFACE ILineDisplayWindow2;
typedef System::DelphiInterface<ILineDisplayWindow2> _di_ILineDisplayWindow2;
__interface DELPHIINTERFACE ILineDisplayCustomGlyphs;
typedef System::DelphiInterface<ILineDisplayCustomGlyphs> _di_ILineDisplayCustomGlyphs;
__interface DELPHIINTERFACE ILineDisplayStatusUpdatedEventArgs;
typedef System::DelphiInterface<ILineDisplayStatusUpdatedEventArgs> _di_ILineDisplayStatusUpdatedEventArgs;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__LineDisplayPowerStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__LineDisplayPowerStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__LineDisplayPowerStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__LineDisplayPowerStatus> _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__LineDisplayPowerStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__LineDisplayPowerStatus_Base> _di_IAsyncOperation_1__LineDisplayPowerStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__LineDisplayPowerStatus;
typedef System::DelphiInterface<IAsyncOperation_1__LineDisplayPowerStatus> _di_IAsyncOperation_1__LineDisplayPowerStatus;
__interface DELPHIINTERFACE ILineDisplay2;
typedef System::DelphiInterface<ILineDisplay2> _di_ILineDisplay2;
__interface DELPHIINTERFACE ILineDisplayAttributes;
typedef System::DelphiInterface<ILineDisplayAttributes> _di_ILineDisplayAttributes;
__interface DELPHIINTERFACE TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs> _di_TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplayWindow_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplayWindow_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplayWindow;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplayWindow> _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplayWindow_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplayWindow_Base> _di_IAsyncOperation_1__ILineDisplayWindow_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplayWindow;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplayWindow> _di_IAsyncOperation_1__ILineDisplayWindow;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap> _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplayStoredBitmap_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplayStoredBitmap_Base> _di_IAsyncOperation_1__ILineDisplayStoredBitmap_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ILineDisplayStoredBitmap;
typedef System::DelphiInterface<IAsyncOperation_1__ILineDisplayStoredBitmap> _di_IAsyncOperation_1__ILineDisplayStoredBitmap;
__interface DELPHIINTERFACE IClaimedLineDisplay2;
typedef System::DelphiInterface<IClaimedLineDisplay2> _di_IClaimedLineDisplay2;
class DELPHICLASS TPosPrinterCharacterSetIds;
class DELPHICLASS TPosPrinter;
class DELPHICLASS TCashDrawer;
class DELPHICLASS TLineDisplay;
class DELPHICLASS TClaimedLineDisplay;
//-- type declarations -------------------------------------------------------
typedef _di_IBarcodeSymbologyAttributes *PIBarcodeSymbologyAttributes;

typedef _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes *PAsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes;

typedef _di_IAsyncOperation_1__IBarcodeSymbologyAttributes *PIAsyncOperation_1__IBarcodeSymbologyAttributes;

typedef _di_IPosPrinterCharacterSetIdsStatics *PIPosPrinterCharacterSetIdsStatics;

typedef _di_ICommonPosPrintStationCapabilities *PICommonPosPrintStationCapabilities;

typedef _di_IIterator_1__PosPrinterRotation *PIIterator_1__PosPrinterRotation;

typedef _di_IIterable_1__PosPrinterRotation *PIIterable_1__PosPrinterRotation;

typedef _di_IVectorView_1__PosPrinterRotation *PIVectorView_1__PosPrinterRotation;

typedef _di_ICommonReceiptSlipCapabilities *PICommonReceiptSlipCapabilities;

typedef _di_IReceiptPrinterCapabilities *PIReceiptPrinterCapabilities;

typedef _di_ISlipPrinterCapabilities *PISlipPrinterCapabilities;

typedef _di_IJournalPrinterCapabilities *PIJournalPrinterCapabilities;

typedef _di_IPosPrinterCapabilities *PIPosPrinterCapabilities;

typedef _di_IPosPrinterStatus *PIPosPrinterStatus;

typedef _di_IPosPrinterStatusUpdatedEventArgs *PIPosPrinterStatusUpdatedEventArgs;

typedef _di_IPosPrinterReleaseDeviceRequestedEventArgs *PIPosPrinterReleaseDeviceRequestedEventArgs;

typedef _di_ICommonClaimedPosPrinterStation *PICommonClaimedPosPrinterStation;

typedef _di_IPosPrinterJob *PIPosPrinterJob;

typedef _di_IReceiptOrSlipJob *PIReceiptOrSlipJob;

typedef _di_IReceiptPrintJob *PIReceiptPrintJob;

typedef _di_IClaimedReceiptPrinter *PIClaimedReceiptPrinter;

typedef _di_IClaimedSlipPrinter *PIClaimedSlipPrinter;

typedef _di_IClaimedJournalPrinter *PIClaimedJournalPrinter;

typedef _di_TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs *PTypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs;

typedef _di_IClaimedPosPrinter *PIClaimedPosPrinter;

typedef _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter *PAsyncOperationCompletedHandler_1__IClaimedPosPrinter;

typedef _di_IAsyncOperation_1__IClaimedPosPrinter *PIAsyncOperation_1__IClaimedPosPrinter;

typedef _di_TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs *PTypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs;

typedef _di_IPosPrinter *PIPosPrinter;

typedef _di_AsyncOperationCompletedHandler_1__IPosPrinter *PAsyncOperationCompletedHandler_1__IPosPrinter;

typedef _di_IAsyncOperation_1__IPosPrinter *PIAsyncOperation_1__IPosPrinter;

typedef _di_IPosPrinterStatics *PIPosPrinterStatics;

typedef _di_IPosPrinterStatics2 *PIPosPrinterStatics2;

typedef _di_ICashDrawerStatus *PICashDrawerStatus;

typedef _di_ICashDrawerStatusUpdatedEventArgs *PICashDrawerStatusUpdatedEventArgs;

typedef _di_ICashDrawerCapabilities *PICashDrawerCapabilities;

typedef _di_TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs *PTypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs;

typedef _di_ICashDrawerEventSource *PICashDrawerEventSource;

typedef _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer *PAsyncOperationCompletedHandler_1__IClaimedCashDrawer;

typedef _di_IAsyncOperation_1__IClaimedCashDrawer *PIAsyncOperation_1__IClaimedCashDrawer;

typedef _di_TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs *PTypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs;

typedef _di_ICashDrawer *PICashDrawer;

typedef _di_ICashDrawerEventSourceEventArgs *PICashDrawerEventSourceEventArgs;

typedef _di_AsyncOperationCompletedHandler_1__ICashDrawer *PAsyncOperationCompletedHandler_1__ICashDrawer;

typedef _di_IAsyncOperation_1__ICashDrawer *PIAsyncOperation_1__ICashDrawer;

typedef _di_ICashDrawerStatics *PICashDrawerStatics;

typedef _di_ICashDrawerStatics2 *PICashDrawerStatics2;

typedef _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay *PAsyncOperationCompletedHandler_1__IClaimedLineDisplay;

typedef _di_IAsyncOperation_1__IClaimedLineDisplay *PIAsyncOperation_1__IClaimedLineDisplay;

typedef _di_ILineDisplay *PILineDisplay;

typedef _di_AsyncOperationCompletedHandler_1__ILineDisplay *PAsyncOperationCompletedHandler_1__ILineDisplay;

typedef _di_IAsyncOperation_1__ILineDisplay *PIAsyncOperation_1__ILineDisplay;

typedef _di_ILineDisplayStatics *PILineDisplayStatics;

typedef _di_ILineDisplayStatisticsCategorySelector *PILineDisplayStatisticsCategorySelector;

typedef _di_ILineDisplayStatics2 *PILineDisplayStatics2;

typedef _di_IClaimedLineDisplayStatics *PIClaimedLineDisplayStatics;

typedef _di_ILineDisplayCursorAttributes *PILineDisplayCursorAttributes;

typedef _di_ILineDisplayCursor *PILineDisplayCursor;

typedef _di_ILineDisplayMarquee *PILineDisplayMarquee;

typedef _di_ILineDisplayStoredBitmap *PILineDisplayStoredBitmap;

typedef _di_ILineDisplayWindow2 *PILineDisplayWindow2;

typedef _di_ILineDisplayCustomGlyphs *PILineDisplayCustomGlyphs;

typedef _di_ILineDisplayStatusUpdatedEventArgs *PILineDisplayStatusUpdatedEventArgs;

typedef _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus *PAsyncOperationCompletedHandler_1__LineDisplayPowerStatus;

typedef _di_IAsyncOperation_1__LineDisplayPowerStatus *PIAsyncOperation_1__LineDisplayPowerStatus;

typedef _di_ILineDisplay2 *PILineDisplay2;

typedef _di_ILineDisplayAttributes *PILineDisplayAttributes;

typedef _di_TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs *PTypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs;

typedef _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow *PAsyncOperationCompletedHandler_1__ILineDisplayWindow;

typedef _di_IAsyncOperation_1__ILineDisplayWindow *PIAsyncOperation_1__ILineDisplayWindow;

typedef _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap *PAsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap;

typedef _di_IAsyncOperation_1__ILineDisplayStoredBitmap *PIAsyncOperation_1__ILineDisplayStoredBitmap;

typedef _di_IClaimedLineDisplay2 *PIClaimedLineDisplay2;

__interface  INTERFACE_UUID("{66413A78-AB7A-4ADA-8ECE-936014B2EAD7}") IBarcodeSymbologyAttributes  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsCheckDigitValidationEnabled(bool &__get_IsCheckDigitValidationEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsCheckDigitValidationEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_IsCheckDigitValidationSupported(bool &__get_IsCheckDigitValidationSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsCheckDigitTransmissionEnabled(bool &__get_IsCheckDigitTransmissionEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsCheckDigitTransmissionEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_IsCheckDigitTransmissionSupported(bool &__get_IsCheckDigitTransmissionSupported_result) = 0 ;
	virtual HRESULT __safecall get_DecodeLength1(unsigned &__get_DecodeLength1_result) = 0 ;
	virtual HRESULT __safecall put_DecodeLength1(unsigned value) = 0 ;
	virtual HRESULT __safecall get_DecodeLength2(unsigned &__get_DecodeLength2_result) = 0 ;
	virtual HRESULT __safecall put_DecodeLength2(unsigned value) = 0 ;
	virtual HRESULT __safecall get_DecodeLengthKind(Winapi::Commontypes::BarcodeSymbologyDecodeLengthKind &__get_DecodeLengthKind_result) = 0 ;
	virtual HRESULT __safecall put_DecodeLengthKind(Winapi::Commontypes::BarcodeSymbologyDecodeLengthKind value) = 0 ;
	virtual HRESULT __safecall get_IsDecodeLengthSupported(bool &__get_IsDecodeLengthSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_DecodeLength1() { unsigned __r; HRESULT __hr = get_DecodeLength1(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned DecodeLength1 = {read=_scw_get_DecodeLength1, write=put_DecodeLength1};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_DecodeLength2() { unsigned __r; HRESULT __hr = get_DecodeLength2(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned DecodeLength2 = {read=_scw_get_DecodeLength2, write=put_DecodeLength2};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BarcodeSymbologyDecodeLengthKind _scw_get_DecodeLengthKind() { Winapi::Commontypes::BarcodeSymbologyDecodeLengthKind __r; HRESULT __hr = get_DecodeLengthKind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BarcodeSymbologyDecodeLengthKind DecodeLengthKind = {read=_scw_get_DecodeLengthKind, write=put_DecodeLengthKind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCheckDigitTransmissionEnabled() { bool __r; HRESULT __hr = get_IsCheckDigitTransmissionEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCheckDigitTransmissionEnabled = {read=_scw_get_IsCheckDigitTransmissionEnabled, write=put_IsCheckDigitTransmissionEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCheckDigitTransmissionSupported() { bool __r; HRESULT __hr = get_IsCheckDigitTransmissionSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCheckDigitTransmissionSupported = {read=_scw_get_IsCheckDigitTransmissionSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCheckDigitValidationEnabled() { bool __r; HRESULT __hr = get_IsCheckDigitValidationEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCheckDigitValidationEnabled = {read=_scw_get_IsCheckDigitValidationEnabled, write=put_IsCheckDigitValidationEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCheckDigitValidationSupported() { bool __r; HRESULT __hr = get_IsCheckDigitValidationSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCheckDigitValidationSupported = {read=_scw_get_IsCheckDigitValidationSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDecodeLengthSupported() { bool __r; HRESULT __hr = get_IsDecodeLengthSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDecodeLengthSupported = {read=_scw_get_IsDecodeLengthSupported};
};

__interface  INTERFACE_UUID("{F8FC5A52-2F45-5E46-A82E-3DA009573B5C}") AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6AF8902C-E82F-5911-BB12-560BE52961F7}") AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes  : public AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IBarcodeSymbologyAttributes asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{461550CA-7BB3-5ADE-A642-61B8FEF2E35C}") IAsyncOperation_1__IBarcodeSymbologyAttributes_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F101BC12-1822-5F55-8F20-4CEEA844E880}") IAsyncOperation_1__IBarcodeSymbologyAttributes  : public IAsyncOperation_1__IBarcodeSymbologyAttributes_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IBarcodeSymbologyAttributes &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IBarcodeSymbologyAttributes Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{5C709EFF-709A-4FE7-B215-06A748A38B39}") IPosPrinterCharacterSetIdsStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Utf16LE(unsigned &__get_Utf16LE_result) = 0 ;
	virtual HRESULT __safecall get_Ascii(unsigned &__get_Ascii_result) = 0 ;
	virtual HRESULT __safecall get_Ansi(unsigned &__get_Ansi_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Ansi() { unsigned __r; HRESULT __hr = get_Ansi(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Ansi = {read=_scw_get_Ansi};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Ascii() { unsigned __r; HRESULT __hr = get_Ascii(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Ascii = {read=_scw_get_Ascii};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Utf16LE() { unsigned __r; HRESULT __hr = get_Utf16LE(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Utf16LE = {read=_scw_get_Utf16LE};
};

__interface  INTERFACE_UUID("{DE5B52CA-E02E-40E9-9E5E-1B488E6AACFC}") ICommonPosPrintStationCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsPrinterPresent(bool &__get_IsPrinterPresent_result) = 0 ;
	virtual HRESULT __safecall get_IsDualColorSupported(bool &__get_IsDualColorSupported_result) = 0 ;
	virtual HRESULT __safecall get_ColorCartridgeCapabilities(Winapi::Commontypes::PosPrinterColorCapabilities &__get_ColorCartridgeCapabilities_result) = 0 ;
	virtual HRESULT __safecall get_CartridgeSensors(Winapi::Commontypes::PosPrinterCartridgeSensors &__get_CartridgeSensors_result) = 0 ;
	virtual HRESULT __safecall get_IsBoldSupported(bool &__get_IsBoldSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsItalicSupported(bool &__get_IsItalicSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsUnderlineSupported(bool &__get_IsUnderlineSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsDoubleHighPrintSupported(bool &__get_IsDoubleHighPrintSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsDoubleWidePrintSupported(bool &__get_IsDoubleWidePrintSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsDoubleHighDoubleWidePrintSupported(bool &__get_IsDoubleHighDoubleWidePrintSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsPaperEmptySensorSupported(bool &__get_IsPaperEmptySensorSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsPaperNearEndSensorSupported(bool &__get_IsPaperNearEndSensorSupported_result) = 0 ;
	virtual HRESULT __safecall get_SupportedCharactersPerLine(Winapi::Graphicsrt::_di_IVectorView_1__Cardinal &__get_SupportedCharactersPerLine_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterCartridgeSensors _scw_get_CartridgeSensors() { Winapi::Commontypes::PosPrinterCartridgeSensors __r; HRESULT __hr = get_CartridgeSensors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterCartridgeSensors CartridgeSensors = {read=_scw_get_CartridgeSensors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterColorCapabilities _scw_get_ColorCartridgeCapabilities() { Winapi::Commontypes::PosPrinterColorCapabilities __r; HRESULT __hr = get_ColorCartridgeCapabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterColorCapabilities ColorCartridgeCapabilities = {read=_scw_get_ColorCartridgeCapabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBoldSupported() { bool __r; HRESULT __hr = get_IsBoldSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBoldSupported = {read=_scw_get_IsBoldSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDoubleHighDoubleWidePrintSupported() { bool __r; HRESULT __hr = get_IsDoubleHighDoubleWidePrintSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDoubleHighDoubleWidePrintSupported = {read=_scw_get_IsDoubleHighDoubleWidePrintSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDoubleHighPrintSupported() { bool __r; HRESULT __hr = get_IsDoubleHighPrintSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDoubleHighPrintSupported = {read=_scw_get_IsDoubleHighPrintSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDoubleWidePrintSupported() { bool __r; HRESULT __hr = get_IsDoubleWidePrintSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDoubleWidePrintSupported = {read=_scw_get_IsDoubleWidePrintSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDualColorSupported() { bool __r; HRESULT __hr = get_IsDualColorSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDualColorSupported = {read=_scw_get_IsDualColorSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsItalicSupported() { bool __r; HRESULT __hr = get_IsItalicSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsItalicSupported = {read=_scw_get_IsItalicSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPaperEmptySensorSupported() { bool __r; HRESULT __hr = get_IsPaperEmptySensorSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPaperEmptySensorSupported = {read=_scw_get_IsPaperEmptySensorSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPaperNearEndSensorSupported() { bool __r; HRESULT __hr = get_IsPaperNearEndSensorSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPaperNearEndSensorSupported = {read=_scw_get_IsPaperNearEndSensorSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPrinterPresent() { bool __r; HRESULT __hr = get_IsPrinterPresent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPrinterPresent = {read=_scw_get_IsPrinterPresent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsUnderlineSupported() { bool __r; HRESULT __hr = get_IsUnderlineSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsUnderlineSupported = {read=_scw_get_IsUnderlineSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Graphicsrt::_di_IVectorView_1__Cardinal _scw_get_SupportedCharactersPerLine() { Winapi::Graphicsrt::_di_IVectorView_1__Cardinal __r; HRESULT __hr = get_SupportedCharactersPerLine(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Graphicsrt::_di_IVectorView_1__Cardinal SupportedCharactersPerLine = {read=_scw_get_SupportedCharactersPerLine};
};

__interface  INTERFACE_UUID("{F687EF7C-B11E-56C3-9158-E6BA15BD521B}") IIterator_1__PosPrinterRotation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__PosPrinterRotation  : public IIterator_1__PosPrinterRotation_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::PosPrinterRotation &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PPosPrinterRotation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterRotation _scw_get_Current() { Winapi::Commontypes::PosPrinterRotation __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterRotation Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{1B1E4D8D-15F5-5802-9B23-8B75CE2A58C5}") IIterable_1__PosPrinterRotation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__PosPrinterRotation  : public IIterable_1__PosPrinterRotation_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__PosPrinterRotation &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__PosPrinterRotation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::PosPrinterRotation &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::PosPrinterRotation value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PPosPrinterRotation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{09286B8B-9873-4D05-BFBE-4727A6038F69}") ICommonReceiptSlipCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsBarcodeSupported(bool &__get_IsBarcodeSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsBitmapSupported(bool &__get_IsBitmapSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsLeft90RotationSupported(bool &__get_IsLeft90RotationSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsRight90RotationSupported(bool &__get_IsRight90RotationSupported_result) = 0 ;
	virtual HRESULT __safecall get_Is180RotationSupported(bool &__get_Is180RotationSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsPrintAreaSupported(bool &__get_IsPrintAreaSupported_result) = 0 ;
	virtual HRESULT __safecall get_RuledLineCapabilities(Winapi::Commontypes::PosPrinterRuledLineCapabilities &__get_RuledLineCapabilities_result) = 0 ;
	virtual HRESULT __safecall get_SupportedBarcodeRotations(_di_IVectorView_1__PosPrinterRotation &__get_SupportedBarcodeRotations_result) = 0 ;
	virtual HRESULT __safecall get_SupportedBitmapRotations(_di_IVectorView_1__PosPrinterRotation &__get_SupportedBitmapRotations_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Is180RotationSupported() { bool __r; HRESULT __hr = get_Is180RotationSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Is180RotationSupported = {read=_scw_get_Is180RotationSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBarcodeSupported() { bool __r; HRESULT __hr = get_IsBarcodeSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBarcodeSupported = {read=_scw_get_IsBarcodeSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBitmapSupported() { bool __r; HRESULT __hr = get_IsBitmapSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBitmapSupported = {read=_scw_get_IsBitmapSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsLeft90RotationSupported() { bool __r; HRESULT __hr = get_IsLeft90RotationSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsLeft90RotationSupported = {read=_scw_get_IsLeft90RotationSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPrintAreaSupported() { bool __r; HRESULT __hr = get_IsPrintAreaSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPrintAreaSupported = {read=_scw_get_IsPrintAreaSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsRight90RotationSupported() { bool __r; HRESULT __hr = get_IsRight90RotationSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsRight90RotationSupported = {read=_scw_get_IsRight90RotationSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterRuledLineCapabilities _scw_get_RuledLineCapabilities() { Winapi::Commontypes::PosPrinterRuledLineCapabilities __r; HRESULT __hr = get_RuledLineCapabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterRuledLineCapabilities RuledLineCapabilities = {read=_scw_get_RuledLineCapabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__PosPrinterRotation _scw_get_SupportedBarcodeRotations() { _di_IVectorView_1__PosPrinterRotation __r; HRESULT __hr = get_SupportedBarcodeRotations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__PosPrinterRotation SupportedBarcodeRotations = {read=_scw_get_SupportedBarcodeRotations};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__PosPrinterRotation _scw_get_SupportedBitmapRotations() { _di_IVectorView_1__PosPrinterRotation __r; HRESULT __hr = get_SupportedBitmapRotations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__PosPrinterRotation SupportedBitmapRotations = {read=_scw_get_SupportedBitmapRotations};
};

__interface  INTERFACE_UUID("{B8F0B58F-51A8-43FC-9BD5-8DE272A6415B}") IReceiptPrinterCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CanCutPaper(bool &__get_CanCutPaper_result) = 0 ;
	virtual HRESULT __safecall get_IsStampSupported(bool &__get_IsStampSupported_result) = 0 ;
	virtual HRESULT __safecall get_MarkFeedCapabilities(Winapi::Commontypes::PosPrinterMarkFeedCapabilities &__get_MarkFeedCapabilities_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanCutPaper() { bool __r; HRESULT __hr = get_CanCutPaper(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanCutPaper = {read=_scw_get_CanCutPaper};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStampSupported() { bool __r; HRESULT __hr = get_IsStampSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStampSupported = {read=_scw_get_IsStampSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterMarkFeedCapabilities _scw_get_MarkFeedCapabilities() { Winapi::Commontypes::PosPrinterMarkFeedCapabilities __r; HRESULT __hr = get_MarkFeedCapabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterMarkFeedCapabilities MarkFeedCapabilities = {read=_scw_get_MarkFeedCapabilities};
};

__interface  INTERFACE_UUID("{99B16399-488C-4157-8AC2-9F57F708D3DB}") ISlipPrinterCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsFullLengthSupported(bool &__get_IsFullLengthSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsBothSidesPrintingSupported(bool &__get_IsBothSidesPrintingSupported_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBothSidesPrintingSupported() { bool __r; HRESULT __hr = get_IsBothSidesPrintingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBothSidesPrintingSupported = {read=_scw_get_IsBothSidesPrintingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsFullLengthSupported() { bool __r; HRESULT __hr = get_IsFullLengthSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsFullLengthSupported = {read=_scw_get_IsFullLengthSupported};
};

__interface  INTERFACE_UUID("{3B5CCC43-E047-4463-BB58-17B5BA1D8056}") IJournalPrinterCapabilities  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CDE95721-4380-4985-ADC5-39DB30CD93BC}") IPosPrinterCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PowerReportingType(Winapi::Commontypes::UnifiedPosPowerReportingType &__get_PowerReportingType_result) = 0 ;
	virtual HRESULT __safecall get_IsStatisticsReportingSupported(bool &__get_IsStatisticsReportingSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsStatisticsUpdatingSupported(bool &__get_IsStatisticsUpdatingSupported_result) = 0 ;
	virtual HRESULT __safecall get_DefaultCharacterSet(unsigned &__get_DefaultCharacterSet_result) = 0 ;
	virtual HRESULT __safecall get_HasCoverSensor(bool &__get_HasCoverSensor_result) = 0 ;
	virtual HRESULT __safecall get_CanMapCharacterSet(bool &__get_CanMapCharacterSet_result) = 0 ;
	virtual HRESULT __safecall get_IsTransactionSupported(bool &__get_IsTransactionSupported_result) = 0 ;
	virtual HRESULT __safecall get_Receipt(_di_IReceiptPrinterCapabilities &__get_Receipt_result) = 0 ;
	virtual HRESULT __safecall get_Slip(_di_ISlipPrinterCapabilities &__get_Slip_result) = 0 ;
	virtual HRESULT __safecall get_Journal(_di_IJournalPrinterCapabilities &__get_Journal_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanMapCharacterSet() { bool __r; HRESULT __hr = get_CanMapCharacterSet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanMapCharacterSet = {read=_scw_get_CanMapCharacterSet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_DefaultCharacterSet() { unsigned __r; HRESULT __hr = get_DefaultCharacterSet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned DefaultCharacterSet = {read=_scw_get_DefaultCharacterSet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCoverSensor() { bool __r; HRESULT __hr = get_HasCoverSensor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCoverSensor = {read=_scw_get_HasCoverSensor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatisticsReportingSupported() { bool __r; HRESULT __hr = get_IsStatisticsReportingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatisticsReportingSupported = {read=_scw_get_IsStatisticsReportingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatisticsUpdatingSupported() { bool __r; HRESULT __hr = get_IsStatisticsUpdatingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatisticsUpdatingSupported = {read=_scw_get_IsStatisticsUpdatingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsTransactionSupported() { bool __r; HRESULT __hr = get_IsTransactionSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsTransactionSupported = {read=_scw_get_IsTransactionSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IJournalPrinterCapabilities _scw_get_Journal() { _di_IJournalPrinterCapabilities __r; HRESULT __hr = get_Journal(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IJournalPrinterCapabilities Journal = {read=_scw_get_Journal};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnifiedPosPowerReportingType _scw_get_PowerReportingType() { Winapi::Commontypes::UnifiedPosPowerReportingType __r; HRESULT __hr = get_PowerReportingType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnifiedPosPowerReportingType PowerReportingType = {read=_scw_get_PowerReportingType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IReceiptPrinterCapabilities _scw_get_Receipt() { _di_IReceiptPrinterCapabilities __r; HRESULT __hr = get_Receipt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IReceiptPrinterCapabilities Receipt = {read=_scw_get_Receipt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISlipPrinterCapabilities _scw_get_Slip() { _di_ISlipPrinterCapabilities __r; HRESULT __hr = get_Slip(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISlipPrinterCapabilities Slip = {read=_scw_get_Slip};
};

__interface  INTERFACE_UUID("{D1F0C730-DA40-4328-BF76-5156FA33B747}") IPosPrinterStatus  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_StatusKind(Winapi::Commontypes::PosPrinterStatusKind &__get_StatusKind_result) = 0 ;
	virtual HRESULT __safecall get_ExtendedStatus(unsigned &__get_ExtendedStatus_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ExtendedStatus() { unsigned __r; HRESULT __hr = get_ExtendedStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ExtendedStatus = {read=_scw_get_ExtendedStatus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterStatusKind _scw_get_StatusKind() { Winapi::Commontypes::PosPrinterStatusKind __r; HRESULT __hr = get_StatusKind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterStatusKind StatusKind = {read=_scw_get_StatusKind};
};

__interface  INTERFACE_UUID("{2EDB87DF-13A6-428D-BA81-B0E7C3E5A3CD}") IPosPrinterStatusUpdatedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(_di_IPosPrinterStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPosPrinterStatus _scw_get_Status() { _di_IPosPrinterStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPosPrinterStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{2BCBA359-1CEF-40B2-9ECB-F927F856AE3C}") IPosPrinterReleaseDeviceRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B7EB66A8-FE8A-4CFB-8B42-E35B280CB27C}") ICommonClaimedPosPrinterStation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_CharactersPerLine(unsigned value) = 0 ;
	virtual HRESULT __safecall get_CharactersPerLine(unsigned &__get_CharactersPerLine_result) = 0 ;
	virtual HRESULT __safecall put_LineHeight(unsigned value) = 0 ;
	virtual HRESULT __safecall get_LineHeight(unsigned &__get_LineHeight_result) = 0 ;
	virtual HRESULT __safecall put_LineSpacing(unsigned value) = 0 ;
	virtual HRESULT __safecall get_LineSpacing(unsigned &__get_LineSpacing_result) = 0 ;
	virtual HRESULT __safecall get_LineWidth(unsigned &__get_LineWidth_result) = 0 ;
	virtual HRESULT __safecall put_IsLetterQuality(bool value) = 0 ;
	virtual HRESULT __safecall get_IsLetterQuality(bool &__get_IsLetterQuality_result) = 0 ;
	virtual HRESULT __safecall get_IsPaperNearEnd(bool &__get_IsPaperNearEnd_result) = 0 ;
	virtual HRESULT __safecall put_ColorCartridge(Winapi::Commontypes::PosPrinterColorCartridge value) = 0 ;
	virtual HRESULT __safecall get_ColorCartridge(Winapi::Commontypes::PosPrinterColorCartridge &__get_ColorCartridge_result) = 0 ;
	virtual HRESULT __safecall get_IsCoverOpen(bool &__get_IsCoverOpen_result) = 0 ;
	virtual HRESULT __safecall get_IsCartridgeRemoved(bool &__get_IsCartridgeRemoved_result) = 0 ;
	virtual HRESULT __safecall get_IsCartridgeEmpty(bool &__get_IsCartridgeEmpty_result) = 0 ;
	virtual HRESULT __safecall get_IsHeadCleaning(bool &__get_IsHeadCleaning_result) = 0 ;
	virtual HRESULT __safecall get_IsPaperEmpty(bool &__get_IsPaperEmpty_result) = 0 ;
	virtual HRESULT __safecall get_IsReadyToPrint(bool &__get_IsReadyToPrint_result) = 0 ;
	virtual HRESULT __safecall ValidateData(HSTRING data, bool &__ValidateData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_CharactersPerLine() { unsigned __r; HRESULT __hr = get_CharactersPerLine(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned CharactersPerLine = {read=_scw_get_CharactersPerLine, write=put_CharactersPerLine};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterColorCartridge _scw_get_ColorCartridge() { Winapi::Commontypes::PosPrinterColorCartridge __r; HRESULT __hr = get_ColorCartridge(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterColorCartridge ColorCartridge = {read=_scw_get_ColorCartridge, write=put_ColorCartridge};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCartridgeEmpty() { bool __r; HRESULT __hr = get_IsCartridgeEmpty(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCartridgeEmpty = {read=_scw_get_IsCartridgeEmpty};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCartridgeRemoved() { bool __r; HRESULT __hr = get_IsCartridgeRemoved(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCartridgeRemoved = {read=_scw_get_IsCartridgeRemoved};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCoverOpen() { bool __r; HRESULT __hr = get_IsCoverOpen(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCoverOpen = {read=_scw_get_IsCoverOpen};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsHeadCleaning() { bool __r; HRESULT __hr = get_IsHeadCleaning(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsHeadCleaning = {read=_scw_get_IsHeadCleaning};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsLetterQuality() { bool __r; HRESULT __hr = get_IsLetterQuality(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsLetterQuality = {read=_scw_get_IsLetterQuality, write=put_IsLetterQuality};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPaperEmpty() { bool __r; HRESULT __hr = get_IsPaperEmpty(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPaperEmpty = {read=_scw_get_IsPaperEmpty};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPaperNearEnd() { bool __r; HRESULT __hr = get_IsPaperNearEnd(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPaperNearEnd = {read=_scw_get_IsPaperNearEnd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsReadyToPrint() { bool __r; HRESULT __hr = get_IsReadyToPrint(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsReadyToPrint = {read=_scw_get_IsReadyToPrint};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_LineHeight() { unsigned __r; HRESULT __hr = get_LineHeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned LineHeight = {read=_scw_get_LineHeight, write=put_LineHeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_LineSpacing() { unsigned __r; HRESULT __hr = get_LineSpacing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned LineSpacing = {read=_scw_get_LineSpacing, write=put_LineSpacing};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_LineWidth() { unsigned __r; HRESULT __hr = get_LineWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned LineWidth = {read=_scw_get_LineWidth};
};

__interface  INTERFACE_UUID("{9A94005C-0615-4591-A58F-30F87EDFE2E4}") IPosPrinterJob  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Print(HSTRING data) = 0 ;
	virtual HRESULT __safecall PrintLine(HSTRING data) = 0 /* overload */;
	virtual HRESULT __safecall PrintLine() = 0 /* overload */;
	virtual HRESULT __safecall ExecuteAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__ExecuteAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{532199BE-C8C3-4DC2-89E9-5C4A37B34DDC}") IReceiptOrSlipJob  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetBarcodeRotation(Winapi::Commontypes::PosPrinterRotation value) = 0 ;
	virtual HRESULT __safecall SetPrintRotation(Winapi::Commontypes::PosPrinterRotation value, bool includeBitmaps) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall SetPrintArea(System::Types::TRectF value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall SetPrintArea(const System::Types::TRectF &value) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall SetBitmap(unsigned bitmapNumber, Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, Winapi::Commontypes::PosPrinterAlignment alignment) = 0 /* overload */;
	virtual HRESULT __safecall SetBitmap(unsigned bitmapNumber, Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, Winapi::Commontypes::PosPrinterAlignment alignment, unsigned width) = 0 /* overload */;
	virtual HRESULT __safecall SetCustomAlignedBitmap(unsigned bitmapNumber, Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, unsigned alignmentDistance) = 0 /* overload */;
	virtual HRESULT __safecall SetCustomAlignedBitmap(unsigned bitmapNumber, Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, unsigned alignmentDistance, unsigned width) = 0 /* overload */;
	virtual HRESULT __safecall PrintSavedBitmap(unsigned bitmapNumber) = 0 ;
	virtual HRESULT __safecall DrawRuledLine(HSTRING positionList, Winapi::Commontypes::PosPrinterLineDirection lineDirection, unsigned lineWidth, Winapi::Commontypes::PosPrinterLineStyle lineStyle, unsigned lineColor) = 0 ;
	virtual HRESULT __safecall PrintBarcode(HSTRING data, unsigned symbology, unsigned height, unsigned width, Winapi::Commontypes::PosPrinterBarcodeTextPosition textPosition, Winapi::Commontypes::PosPrinterAlignment alignment) = 0 ;
	virtual HRESULT __safecall PrintBarcodeCustomAlign(HSTRING data, unsigned symbology, unsigned height, unsigned width, Winapi::Commontypes::PosPrinterBarcodeTextPosition textPosition, unsigned alignmentDistance) = 0 ;
	virtual HRESULT __safecall PrintBitmap(Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, Winapi::Commontypes::PosPrinterAlignment alignment) = 0 /* overload */;
	virtual HRESULT __safecall PrintBitmap(Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, Winapi::Commontypes::PosPrinterAlignment alignment, unsigned width) = 0 /* overload */;
	virtual HRESULT __safecall PrintCustomAlignedBitmap(Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, unsigned alignmentDistance) = 0 /* overload */;
	virtual HRESULT __safecall PrintCustomAlignedBitmap(Winapi::Graphicsrt::_di_Imaging_IBitmapFrame bitmap, unsigned alignmentDistance, unsigned width) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{AA96066E-ACAD-4B79-9D0F-C0CFC08DC77B}") IReceiptPrintJob  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall MarkFeed(Winapi::Commontypes::PosPrinterMarkFeedKind kind) = 0 ;
	virtual HRESULT __safecall CutPaper(double percentage) = 0 /* overload */;
	virtual HRESULT __safecall CutPaper() = 0 /* overload */;
};

__interface  INTERFACE_UUID("{9AD27A74-DD61-4EE2-9837-5B5D72D538B9}") IClaimedReceiptPrinter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SidewaysMaxLines(unsigned &__get_SidewaysMaxLines_result) = 0 ;
	virtual HRESULT __safecall get_SidewaysMaxChars(unsigned &__get_SidewaysMaxChars_result) = 0 ;
	virtual HRESULT __safecall get_LinesToPaperCut(unsigned &__get_LinesToPaperCut_result) = 0 ;
	virtual HRESULT __safecall get_PageSize(System::Types::TSizeF &__get_PageSize_result) = 0 ;
	virtual HRESULT __safecall get_PrintArea(System::Types::TRectF &__get_PrintArea_result) = 0 ;
	virtual HRESULT __safecall CreateJob(_di_IReceiptPrintJob &__CreateJob_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_LinesToPaperCut() { unsigned __r; HRESULT __hr = get_LinesToPaperCut(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned LinesToPaperCut = {read=_scw_get_LinesToPaperCut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_PageSize() { System::Types::TSizeF __r; HRESULT __hr = get_PageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF PageSize = {read=_scw_get_PageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_PrintArea() { System::Types::TRectF __r; HRESULT __hr = get_PrintArea(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF PrintArea = {read=_scw_get_PrintArea};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SidewaysMaxChars() { unsigned __r; HRESULT __hr = get_SidewaysMaxChars(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SidewaysMaxChars = {read=_scw_get_SidewaysMaxChars};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SidewaysMaxLines() { unsigned __r; HRESULT __hr = get_SidewaysMaxLines(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SidewaysMaxLines = {read=_scw_get_SidewaysMaxLines};
};

__interface  INTERFACE_UUID("{BD5DEFF2-AF90-4E8A-B77B-E3AE9CA63A7F}") IClaimedSlipPrinter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SidewaysMaxLines(unsigned &__get_SidewaysMaxLines_result) = 0 ;
	virtual HRESULT __safecall get_SidewaysMaxChars(unsigned &__get_SidewaysMaxChars_result) = 0 ;
	virtual HRESULT __safecall get_MaxLines(unsigned &__get_MaxLines_result) = 0 ;
	virtual HRESULT __safecall get_LinesNearEndToEnd(unsigned &__get_LinesNearEndToEnd_result) = 0 ;
	virtual HRESULT __safecall get_PrintSide(Winapi::Commontypes::PosPrinterPrintSide &__get_PrintSide_result) = 0 ;
	virtual HRESULT __safecall get_PageSize(System::Types::TSizeF &__get_PageSize_result) = 0 ;
	virtual HRESULT __safecall get_PrintArea(System::Types::TRectF &__get_PrintArea_result) = 0 ;
	virtual HRESULT __safecall OpenJaws() = 0 ;
	virtual HRESULT __safecall CloseJaws() = 0 ;
	virtual HRESULT __safecall InsertSlipAsync(Winapi::Commontypes::TimeSpan timeout, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__InsertSlipAsync_result) = 0 ;
	virtual HRESULT __safecall RemoveSlipAsync(Winapi::Commontypes::TimeSpan timeout, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__RemoveSlipAsync_result) = 0 ;
	virtual HRESULT __safecall ChangePrintSide(Winapi::Commontypes::PosPrinterPrintSide printSide) = 0 ;
	virtual HRESULT __safecall CreateJob(_di_IReceiptOrSlipJob &__CreateJob_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_LinesNearEndToEnd() { unsigned __r; HRESULT __hr = get_LinesNearEndToEnd(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned LinesNearEndToEnd = {read=_scw_get_LinesNearEndToEnd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxLines() { unsigned __r; HRESULT __hr = get_MaxLines(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxLines = {read=_scw_get_MaxLines};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_PageSize() { System::Types::TSizeF __r; HRESULT __hr = get_PageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF PageSize = {read=_scw_get_PageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_PrintArea() { System::Types::TRectF __r; HRESULT __hr = get_PrintArea(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF PrintArea = {read=_scw_get_PrintArea};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterPrintSide _scw_get_PrintSide() { Winapi::Commontypes::PosPrinterPrintSide __r; HRESULT __hr = get_PrintSide(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterPrintSide PrintSide = {read=_scw_get_PrintSide};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SidewaysMaxChars() { unsigned __r; HRESULT __hr = get_SidewaysMaxChars(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SidewaysMaxChars = {read=_scw_get_SidewaysMaxChars};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SidewaysMaxLines() { unsigned __r; HRESULT __hr = get_SidewaysMaxLines(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SidewaysMaxLines = {read=_scw_get_SidewaysMaxLines};
};

__interface  INTERFACE_UUID("{67EA0630-517D-487F-9FDF-D2E0A0A264A5}") IClaimedJournalPrinter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateJob(_di_IPosPrinterJob &__CreateJob_result) = 0 ;
};

__interface  INTERFACE_UUID("{31424F6F-CFEB-5031-8A95-BEA59B09E584}") TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{2651A22A-9DCF-598E-B807-BE46B471C78C}") TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs  : public TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IClaimedPosPrinter sender, _di_IPosPrinterReleaseDeviceRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{6D64CE0C-E03E-4B14-A38E-C28C34B86353}") IClaimedPosPrinter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_IsEnabled(bool &__get_IsEnabled_result) = 0 ;
	virtual HRESULT __safecall put_CharacterSet(unsigned value) = 0 ;
	virtual HRESULT __safecall get_CharacterSet(unsigned &__get_CharacterSet_result) = 0 ;
	virtual HRESULT __safecall get_IsCoverOpen(bool &__get_IsCoverOpen_result) = 0 ;
	virtual HRESULT __safecall put_IsCharacterSetMappingEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_IsCharacterSetMappingEnabled(bool &__get_IsCharacterSetMappingEnabled_result) = 0 ;
	virtual HRESULT __safecall put_MapMode(Winapi::Commontypes::PosPrinterMapMode value) = 0 ;
	virtual HRESULT __safecall get_MapMode(Winapi::Commontypes::PosPrinterMapMode &__get_MapMode_result) = 0 ;
	virtual HRESULT __safecall get_Receipt(_di_IClaimedReceiptPrinter &__get_Receipt_result) = 0 ;
	virtual HRESULT __safecall get_Slip(_di_IClaimedSlipPrinter &__get_Slip_result) = 0 ;
	virtual HRESULT __safecall get_Journal(_di_IClaimedJournalPrinter &__get_Journal_result) = 0 ;
	virtual HRESULT __safecall EnableAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__EnableAsync_result) = 0 ;
	virtual HRESULT __safecall DisableAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__DisableAsync_result) = 0 ;
	virtual HRESULT __safecall RetainDeviceAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__RetainDeviceAsync_result) = 0 ;
	virtual HRESULT __safecall ResetStatisticsAsync(Winapi::Graphicsrt::_di_IIterable_1__HSTRING statisticsCategories, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__ResetStatisticsAsync_result) = 0 ;
	virtual HRESULT __safecall UpdateStatisticsAsync(Winapi::Graphicsrt::_di_IIterable_1__IKeyValuePair_2__HSTRING__HSTRING statistics, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__UpdateStatisticsAsync_result) = 0 ;
	virtual HRESULT __safecall add_ReleaseDeviceRequested(_di_TypedEventHandler_2__IClaimedPosPrinter__IPosPrinterReleaseDeviceRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ReleaseDeviceRequested_result) = 0 ;
	virtual HRESULT __safecall remove_ReleaseDeviceRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_CharacterSet() { unsigned __r; HRESULT __hr = get_CharacterSet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned CharacterSet = {read=_scw_get_CharacterSet, write=put_CharacterSet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCharacterSetMappingEnabled() { bool __r; HRESULT __hr = get_IsCharacterSetMappingEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCharacterSetMappingEnabled = {read=_scw_get_IsCharacterSetMappingEnabled, write=put_IsCharacterSetMappingEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCoverOpen() { bool __r; HRESULT __hr = get_IsCoverOpen(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCoverOpen = {read=_scw_get_IsCoverOpen};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsEnabled() { bool __r; HRESULT __hr = get_IsEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsEnabled = {read=_scw_get_IsEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IClaimedJournalPrinter _scw_get_Journal() { _di_IClaimedJournalPrinter __r; HRESULT __hr = get_Journal(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IClaimedJournalPrinter Journal = {read=_scw_get_Journal};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::PosPrinterMapMode _scw_get_MapMode() { Winapi::Commontypes::PosPrinterMapMode __r; HRESULT __hr = get_MapMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::PosPrinterMapMode MapMode = {read=_scw_get_MapMode, write=put_MapMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IClaimedReceiptPrinter _scw_get_Receipt() { _di_IClaimedReceiptPrinter __r; HRESULT __hr = get_Receipt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IClaimedReceiptPrinter Receipt = {read=_scw_get_Receipt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IClaimedSlipPrinter _scw_get_Slip() { _di_IClaimedSlipPrinter __r; HRESULT __hr = get_Slip(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IClaimedSlipPrinter Slip = {read=_scw_get_Slip};
};

__interface  INTERFACE_UUID("{01EB0DC3-3C30-5EEA-9FCE-EFB398E0BE34}") AsyncOperationCompletedHandler_1__IClaimedPosPrinter_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{DCC034BC-9B93-5E70-B7F3-5E11F87E91C7}") AsyncOperationCompletedHandler_1__IClaimedPosPrinter  : public AsyncOperationCompletedHandler_1__IClaimedPosPrinter_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IClaimedPosPrinter asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B4476F95-355A-503D-B844-1756C8CFDA98}") IAsyncOperation_1__IClaimedPosPrinter_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2A715D99-81DD-5476-AC64-BD33873E6B59}") IAsyncOperation_1__IClaimedPosPrinter  : public IAsyncOperation_1__IClaimedPosPrinter_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IClaimedPosPrinter &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IClaimedPosPrinter Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{20B0C66A-5F41-5A32-B45A-344F12E70A34}") TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B8F0D464-440B-5A73-A838-BCF474C8C9B2}") TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs  : public TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IPosPrinter sender, _di_IPosPrinterStatusUpdatedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{2A03C10E-9A19-4A01-994F-12DFAD6ADCBF}") IPosPrinter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_Capabilities(_di_IPosPrinterCapabilities &__get_Capabilities_result) = 0 ;
	virtual HRESULT __safecall get_SupportedCharacterSets(Winapi::Graphicsrt::_di_IVectorView_1__Cardinal &__get_SupportedCharacterSets_result) = 0 ;
	virtual HRESULT __safecall get_SupportedTypeFaces(Winapi::Graphicsrt::_di_IVectorView_1__HSTRING &__get_SupportedTypeFaces_result) = 0 ;
	virtual HRESULT __safecall get_Status(_di_IPosPrinterStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall ClaimPrinterAsync(_di_IAsyncOperation_1__IClaimedPosPrinter &__ClaimPrinterAsync_result) = 0 ;
	virtual HRESULT __safecall CheckHealthAsync(Winapi::Commontypes::UnifiedPosHealthCheckLevel level, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__CheckHealthAsync_result) = 0 ;
	virtual HRESULT __safecall GetStatisticsAsync(Winapi::Graphicsrt::_di_IIterable_1__HSTRING statisticsCategories, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__GetStatisticsAsync_result) = 0 ;
	virtual HRESULT __safecall add_StatusUpdated(_di_TypedEventHandler_2__IPosPrinter__IPosPrinterStatusUpdatedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StatusUpdated_result) = 0 ;
	virtual HRESULT __safecall remove_StatusUpdated(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPosPrinterCapabilities _scw_get_Capabilities() { _di_IPosPrinterCapabilities __r; HRESULT __hr = get_Capabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPosPrinterCapabilities Capabilities = {read=_scw_get_Capabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPosPrinterStatus _scw_get_Status() { _di_IPosPrinterStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPosPrinterStatus Status = {read=_scw_get_Status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Graphicsrt::_di_IVectorView_1__Cardinal _scw_get_SupportedCharacterSets() { Winapi::Graphicsrt::_di_IVectorView_1__Cardinal __r; HRESULT __hr = get_SupportedCharacterSets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Graphicsrt::_di_IVectorView_1__Cardinal SupportedCharacterSets = {read=_scw_get_SupportedCharacterSets};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Graphicsrt::_di_IVectorView_1__HSTRING _scw_get_SupportedTypeFaces() { Winapi::Graphicsrt::_di_IVectorView_1__HSTRING __r; HRESULT __hr = get_SupportedTypeFaces(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Graphicsrt::_di_IVectorView_1__HSTRING SupportedTypeFaces = {read=_scw_get_SupportedTypeFaces};
};

__interface  INTERFACE_UUID("{5E8DBBC8-8B60-5881-8B6E-F699B4949DBA}") AsyncOperationCompletedHandler_1__IPosPrinter_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4DE49EF9-FF09-5C67-85BE-85D97904662B}") AsyncOperationCompletedHandler_1__IPosPrinter  : public AsyncOperationCompletedHandler_1__IPosPrinter_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IPosPrinter asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{024F77CE-51C3-5AFC-9F30-24B3C0F3B25A}") IAsyncOperation_1__IPosPrinter_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{57F34381-BA47-5A19-B7FE-8E940C7C0FCB}") IAsyncOperation_1__IPosPrinter  : public IAsyncOperation_1__IPosPrinter_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IPosPrinter handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IPosPrinter &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IPosPrinter &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IPosPrinter _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IPosPrinter __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IPosPrinter Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{8CE0D4EA-132F-4CDF-A64A-2D0D7C96A85B}") IPosPrinterStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefaultAsync(_di_IAsyncOperation_1__IPosPrinter &__GetDefaultAsync_result) = 0 ;
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IPosPrinter &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{EECD2C1C-B0D0-42E7-B137-B89B16244D41}") IPosPrinterStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes, HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{6BBD78BF-DCA1-4E06-99EB-5AF6A5AEC108}") ICashDrawerStatus  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_StatusKind(Winapi::Commontypes::CashDrawerStatusKind &__get_StatusKind_result) = 0 ;
	virtual HRESULT __safecall get_ExtendedStatus(unsigned &__get_ExtendedStatus_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_ExtendedStatus() { unsigned __r; HRESULT __hr = get_ExtendedStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned ExtendedStatus = {read=_scw_get_ExtendedStatus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CashDrawerStatusKind _scw_get_StatusKind() { Winapi::Commontypes::CashDrawerStatusKind __r; HRESULT __hr = get_StatusKind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CashDrawerStatusKind StatusKind = {read=_scw_get_StatusKind};
};

__interface  INTERFACE_UUID("{30AAE98A-0D70-459C-9553-87E124C52488}") ICashDrawerStatusUpdatedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(_di_ICashDrawerStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICashDrawerStatus _scw_get_Status() { _di_ICashDrawerStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICashDrawerStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{0BC6DE0B-E8E7-4B1F-B1D1-3E501AD08247}") ICashDrawerCapabilities  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PowerReportingType(Winapi::Commontypes::UnifiedPosPowerReportingType &__get_PowerReportingType_result) = 0 ;
	virtual HRESULT __safecall get_IsStatisticsReportingSupported(bool &__get_IsStatisticsReportingSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsStatisticsUpdatingSupported(bool &__get_IsStatisticsUpdatingSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsStatusReportingSupported(bool &__get_IsStatusReportingSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsStatusMultiDrawerDetectSupported(bool &__get_IsStatusMultiDrawerDetectSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsDrawerOpenSensorAvailable(bool &__get_IsDrawerOpenSensorAvailable_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDrawerOpenSensorAvailable() { bool __r; HRESULT __hr = get_IsDrawerOpenSensorAvailable(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDrawerOpenSensorAvailable = {read=_scw_get_IsDrawerOpenSensorAvailable};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatisticsReportingSupported() { bool __r; HRESULT __hr = get_IsStatisticsReportingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatisticsReportingSupported = {read=_scw_get_IsStatisticsReportingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatisticsUpdatingSupported() { bool __r; HRESULT __hr = get_IsStatisticsUpdatingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatisticsUpdatingSupported = {read=_scw_get_IsStatisticsUpdatingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatusMultiDrawerDetectSupported() { bool __r; HRESULT __hr = get_IsStatusMultiDrawerDetectSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatusMultiDrawerDetectSupported = {read=_scw_get_IsStatusMultiDrawerDetectSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsStatusReportingSupported() { bool __r; HRESULT __hr = get_IsStatusReportingSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsStatusReportingSupported = {read=_scw_get_IsStatusReportingSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnifiedPosPowerReportingType _scw_get_PowerReportingType() { Winapi::Commontypes::UnifiedPosPowerReportingType __r; HRESULT __hr = get_PowerReportingType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnifiedPosPowerReportingType PowerReportingType = {read=_scw_get_PowerReportingType};
};

__interface  INTERFACE_UUID("{D1995B24-A22E-5BB0-8C77-00AE74F2AB29}") TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ICashDrawerEventSource sender, _di_ICashDrawerEventSourceEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{E006E46C-F2F9-442F-8DD6-06C10A4227BA}") ICashDrawerEventSource  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_DrawerClosed(_di_TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_DrawerClosed_result) = 0 ;
	virtual HRESULT __safecall remove_DrawerClosed(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_DrawerOpened(_di_TypedEventHandler_2__ICashDrawerEventSource__ICashDrawerEventSourceEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_DrawerOpened_result) = 0 ;
	virtual HRESULT __safecall remove_DrawerOpened(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{E68C3736-FDE7-5CFB-B22F-92119723E729}") AsyncOperationCompletedHandler_1__IClaimedCashDrawer_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E8192C0D-7D61-53CB-AC73-B8619B1C0121}") AsyncOperationCompletedHandler_1__IClaimedCashDrawer  : public AsyncOperationCompletedHandler_1__IClaimedCashDrawer_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IClaimedCashDrawer asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9230E7AA-20A0-5752-9C20-4BF44934A87E}") IAsyncOperation_1__IClaimedCashDrawer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DD547670-8167-5132-B38F-2B2590B3D847}") IAsyncOperation_1__IClaimedCashDrawer  : public IAsyncOperation_1__IClaimedCashDrawer_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IClaimedCashDrawer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IClaimedCashDrawer Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{64662EF4-CB0E-5C6F-A820-7D0A769554C9}") TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{518BE39A-2654-5D10-8426-B50C2B52B087}") TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs  : public TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_ICashDrawer sender, _di_ICashDrawerStatusUpdatedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{9F88F5C8-DE54-4AEE-A890-920BCBFE30FC}") ICashDrawer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_Capabilities(_di_ICashDrawerCapabilities &__get_Capabilities_result) = 0 ;
	virtual HRESULT __safecall get_Status(_di_ICashDrawerStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_IsDrawerOpen(bool &__get_IsDrawerOpen_result) = 0 ;
	virtual HRESULT __safecall get_DrawerEventSource(_di_ICashDrawerEventSource &__get_DrawerEventSource_result) = 0 ;
	virtual HRESULT __safecall ClaimDrawerAsync(_di_IAsyncOperation_1__IClaimedCashDrawer &__ClaimDrawerAsync_result) = 0 ;
	virtual HRESULT __safecall CheckHealthAsync(Winapi::Commontypes::UnifiedPosHealthCheckLevel level, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__CheckHealthAsync_result) = 0 ;
	virtual HRESULT __safecall GetStatisticsAsync(Winapi::Graphicsrt::_di_IIterable_1__HSTRING statisticsCategories, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__GetStatisticsAsync_result) = 0 ;
	virtual HRESULT __safecall add_StatusUpdated(_di_TypedEventHandler_2__ICashDrawer__ICashDrawerStatusUpdatedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StatusUpdated_result) = 0 ;
	virtual HRESULT __safecall remove_StatusUpdated(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICashDrawerCapabilities _scw_get_Capabilities() { _di_ICashDrawerCapabilities __r; HRESULT __hr = get_Capabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICashDrawerCapabilities Capabilities = {read=_scw_get_Capabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICashDrawerEventSource _scw_get_DrawerEventSource() { _di_ICashDrawerEventSource __r; HRESULT __hr = get_DrawerEventSource(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICashDrawerEventSource DrawerEventSource = {read=_scw_get_DrawerEventSource};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDrawerOpen() { bool __r; HRESULT __hr = get_IsDrawerOpen(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDrawerOpen = {read=_scw_get_IsDrawerOpen};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICashDrawerStatus _scw_get_Status() { _di_ICashDrawerStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICashDrawerStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{69CB3BC1-147F-421C-9C23-090123BB786C}") ICashDrawerEventSourceEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CashDrawer(_di_ICashDrawer &__get_CashDrawer_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ICashDrawer _scw_get_CashDrawer() { _di_ICashDrawer __r; HRESULT __hr = get_CashDrawer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ICashDrawer CashDrawer = {read=_scw_get_CashDrawer};
};

__interface  INTERFACE_UUID("{57836710-F186-5636-891D-F8C5398EA6DF}") AsyncOperationCompletedHandler_1__ICashDrawer_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{2B5A22BA-CB98-5A1C-BED6-09440AC4C5D9}") AsyncOperationCompletedHandler_1__ICashDrawer  : public AsyncOperationCompletedHandler_1__ICashDrawer_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ICashDrawer asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{45007467-92F2-5BFF-B191-AA5000FEDD9E}") IAsyncOperation_1__ICashDrawer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F0126938-62B0-590E-AE08-DA21554EAD22}") IAsyncOperation_1__ICashDrawer  : public IAsyncOperation_1__ICashDrawer_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ICashDrawer handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ICashDrawer &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_ICashDrawer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ICashDrawer _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ICashDrawer __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ICashDrawer Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{DFA0955A-D437-4FFF-B547-DDA969A4F883}") ICashDrawerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefaultAsync(_di_IAsyncOperation_1__ICashDrawer &__GetDefaultAsync_result) = 0 ;
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__ICashDrawer &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{3E818121-8C42-40E8-9C0E-40297048104C}") ICashDrawerStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes, HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{4E1A79F1-DFF2-5B18-BEBE-2ACA010BBFCC}") AsyncOperationCompletedHandler_1__IClaimedLineDisplay_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E6E53C79-74CE-5295-ACD8-26F252E31920}") AsyncOperationCompletedHandler_1__IClaimedLineDisplay  : public AsyncOperationCompletedHandler_1__IClaimedLineDisplay_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IClaimedLineDisplay asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{4BD0A904-1AAA-545A-8CBC-1D45C3E80E5E}") IAsyncOperation_1__IClaimedLineDisplay_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E22B8EFE-315E-5EFD-A8B9-62A55C61450C}") IAsyncOperation_1__IClaimedLineDisplay  : public IAsyncOperation_1__IClaimedLineDisplay_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IClaimedLineDisplay &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IClaimedLineDisplay Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{24F5DF4E-3C99-44E2-B73F-E51BE3637A8C}") ILineDisplay  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_Capabilities(Winapi::Commontypes::_di_ILineDisplayCapabilities &__get_Capabilities_result) = 0 ;
	virtual HRESULT __safecall get_PhysicalDeviceName(HSTRING &__get_PhysicalDeviceName_result) = 0 ;
	virtual HRESULT __safecall get_PhysicalDeviceDescription(HSTRING &__get_PhysicalDeviceDescription_result) = 0 ;
	virtual HRESULT __safecall get_DeviceControlDescription(HSTRING &__get_DeviceControlDescription_result) = 0 ;
	virtual HRESULT __safecall get_DeviceControlVersion(HSTRING &__get_DeviceControlVersion_result) = 0 ;
	virtual HRESULT __safecall get_DeviceServiceVersion(HSTRING &__get_DeviceServiceVersion_result) = 0 ;
	virtual HRESULT __safecall ClaimAsync(_di_IAsyncOperation_1__IClaimedLineDisplay &__ClaimAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_ILineDisplayCapabilities _scw_get_Capabilities() { Winapi::Commontypes::_di_ILineDisplayCapabilities __r; HRESULT __hr = get_Capabilities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_ILineDisplayCapabilities Capabilities = {read=_scw_get_Capabilities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceControlDescription() { HSTRING __r; HRESULT __hr = get_DeviceControlDescription(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceControlDescription = {read=_scw_get_DeviceControlDescription};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceControlVersion() { HSTRING __r; HRESULT __hr = get_DeviceControlVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceControlVersion = {read=_scw_get_DeviceControlVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceServiceVersion() { HSTRING __r; HRESULT __hr = get_DeviceServiceVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceServiceVersion = {read=_scw_get_DeviceServiceVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PhysicalDeviceDescription() { HSTRING __r; HRESULT __hr = get_PhysicalDeviceDescription(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PhysicalDeviceDescription = {read=_scw_get_PhysicalDeviceDescription};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PhysicalDeviceName() { HSTRING __r; HRESULT __hr = get_PhysicalDeviceName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PhysicalDeviceName = {read=_scw_get_PhysicalDeviceName};
};

__interface  INTERFACE_UUID("{B5C4D476-4F46-53C4-8A45-89DBE6D6F286}") AsyncOperationCompletedHandler_1__ILineDisplay_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{248C7CFC-53A4-5693-ADF6-1BF1EF697D41}") AsyncOperationCompletedHandler_1__ILineDisplay  : public AsyncOperationCompletedHandler_1__ILineDisplay_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ILineDisplay asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{40FFDAE9-E7C1-5C44-91B4-BD84EBF8539B}") IAsyncOperation_1__ILineDisplay_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E873119A-5068-5970-BFFD-410AB56DF875}") IAsyncOperation_1__ILineDisplay  : public IAsyncOperation_1__ILineDisplay_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplay handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplay &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_ILineDisplay &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ILineDisplay _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ILineDisplay __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ILineDisplay Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{022DC0B6-11B0-4690-9547-0B39C5AF2114}") ILineDisplayStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__ILineDisplay &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDefaultAsync(_di_IAsyncOperation_1__ILineDisplay &__GetDefaultAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 /* overload */;
	virtual HRESULT __safecall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes, HSTRING &__GetDeviceSelector_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{B521C46B-9274-4D24-94F3-B6017B832444}") ILineDisplayStatisticsCategorySelector  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AllStatistics(HSTRING &__get_AllStatistics_result) = 0 ;
	virtual HRESULT __safecall get_UnifiedPosStatistics(HSTRING &__get_UnifiedPosStatistics_result) = 0 ;
	virtual HRESULT __safecall get_ManufacturerStatistics(HSTRING &__get_ManufacturerStatistics_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AllStatistics() { HSTRING __r; HRESULT __hr = get_AllStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AllStatistics = {read=_scw_get_AllStatistics};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ManufacturerStatistics() { HSTRING __r; HRESULT __hr = get_ManufacturerStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ManufacturerStatistics = {read=_scw_get_ManufacturerStatistics};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UnifiedPosStatistics() { HSTRING __r; HRESULT __hr = get_UnifiedPosStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UnifiedPosStatistics = {read=_scw_get_UnifiedPosStatistics};
};

__interface  INTERFACE_UUID("{600C3F1C-77AB-4968-A7DE-C02FF169F2CC}") ILineDisplayStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_StatisticsCategorySelector(_di_ILineDisplayStatisticsCategorySelector &__get_StatisticsCategorySelector_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILineDisplayStatisticsCategorySelector _scw_get_StatisticsCategorySelector() { _di_ILineDisplayStatisticsCategorySelector __r; HRESULT __hr = get_StatisticsCategorySelector(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILineDisplayStatisticsCategorySelector StatisticsCategorySelector = {read=_scw_get_StatisticsCategorySelector};
};

__interface  INTERFACE_UUID("{78CA98FB-8B6B-4973-86F0-3E570C351825}") IClaimedLineDisplayStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IClaimedLineDisplay &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 /* overload */;
	virtual HRESULT __safecall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes, HSTRING &__GetDeviceSelector_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4E2D54FE-4FFD-4190-AAE1-CE285F20C896}") ILineDisplayCursorAttributes  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsBlinkEnabled(bool &__get_IsBlinkEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsBlinkEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_CursorType(Winapi::Commontypes::LineDisplayCursorType &__get_CursorType_result) = 0 ;
	virtual HRESULT __safecall put_CursorType(Winapi::Commontypes::LineDisplayCursorType value) = 0 ;
	virtual HRESULT __safecall get_IsAutoAdvanceEnabled(bool &__get_IsAutoAdvanceEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsAutoAdvanceEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_Position(System::Types::TPointF &__get_Position_result) = 0 ;
	virtual HRESULT __safecall put_Position(System::Types::TPointF value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::LineDisplayCursorType _scw_get_CursorType() { Winapi::Commontypes::LineDisplayCursorType __r; HRESULT __hr = get_CursorType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::LineDisplayCursorType CursorType = {read=_scw_get_CursorType, write=put_CursorType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsAutoAdvanceEnabled() { bool __r; HRESULT __hr = get_IsAutoAdvanceEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsAutoAdvanceEnabled = {read=_scw_get_IsAutoAdvanceEnabled, write=put_IsAutoAdvanceEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBlinkEnabled() { bool __r; HRESULT __hr = get_IsBlinkEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBlinkEnabled = {read=_scw_get_IsBlinkEnabled, write=put_IsBlinkEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Position() { System::Types::TPointF __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Position = {read=_scw_get_Position, write=put_Position};
};

__interface  INTERFACE_UUID("{ECDFFC45-754A-4E3B-AB2B-151181085605}") ILineDisplayCursor  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CanCustomize(bool &__get_CanCustomize_result) = 0 ;
	virtual HRESULT __safecall get_IsBlinkSupported(bool &__get_IsBlinkSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsBlockSupported(bool &__get_IsBlockSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsHalfBlockSupported(bool &__get_IsHalfBlockSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsUnderlineSupported(bool &__get_IsUnderlineSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsReverseSupported(bool &__get_IsReverseSupported_result) = 0 ;
	virtual HRESULT __safecall get_IsOtherSupported(bool &__get_IsOtherSupported_result) = 0 ;
	virtual HRESULT __safecall GetAttributes(_di_ILineDisplayCursorAttributes &__GetAttributes_result) = 0 ;
	virtual HRESULT __safecall TryUpdateAttributesAsync(_di_ILineDisplayCursorAttributes attributes, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryUpdateAttributesAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanCustomize() { bool __r; HRESULT __hr = get_CanCustomize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanCustomize = {read=_scw_get_CanCustomize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBlinkSupported() { bool __r; HRESULT __hr = get_IsBlinkSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBlinkSupported = {read=_scw_get_IsBlinkSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsBlockSupported() { bool __r; HRESULT __hr = get_IsBlockSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsBlockSupported = {read=_scw_get_IsBlockSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsHalfBlockSupported() { bool __r; HRESULT __hr = get_IsHalfBlockSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsHalfBlockSupported = {read=_scw_get_IsHalfBlockSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsOtherSupported() { bool __r; HRESULT __hr = get_IsOtherSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsOtherSupported = {read=_scw_get_IsOtherSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsReverseSupported() { bool __r; HRESULT __hr = get_IsReverseSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsReverseSupported = {read=_scw_get_IsReverseSupported};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsUnderlineSupported() { bool __r; HRESULT __hr = get_IsUnderlineSupported(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsUnderlineSupported = {read=_scw_get_IsUnderlineSupported};
};

__interface  INTERFACE_UUID("{A3D33E3E-F46A-4B7A-BC21-53EB3B57F8B4}") ILineDisplayMarquee  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Format(Winapi::Commontypes::LineDisplayMarqueeFormat &__get_Format_result) = 0 ;
	virtual HRESULT __safecall put_Format(Winapi::Commontypes::LineDisplayMarqueeFormat value) = 0 ;
	virtual HRESULT __safecall get_RepeatWaitInterval(Winapi::Commontypes::TimeSpan &__get_RepeatWaitInterval_result) = 0 ;
	virtual HRESULT __safecall put_RepeatWaitInterval(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall get_ScrollWaitInterval(Winapi::Commontypes::TimeSpan &__get_ScrollWaitInterval_result) = 0 ;
	virtual HRESULT __safecall put_ScrollWaitInterval(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall TryStartScrollingAsync(Winapi::Commontypes::LineDisplayScrollDirection direction, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryStartScrollingAsync_result) = 0 ;
	virtual HRESULT __safecall TryStopScrollingAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryStopScrollingAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::LineDisplayMarqueeFormat _scw_get_Format() { Winapi::Commontypes::LineDisplayMarqueeFormat __r; HRESULT __hr = get_Format(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::LineDisplayMarqueeFormat Format = {read=_scw_get_Format, write=put_Format};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_RepeatWaitInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_RepeatWaitInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan RepeatWaitInterval = {read=_scw_get_RepeatWaitInterval, write=put_RepeatWaitInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_ScrollWaitInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_ScrollWaitInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan ScrollWaitInterval = {read=_scw_get_ScrollWaitInterval, write=put_ScrollWaitInterval};
};

__interface  INTERFACE_UUID("{F621515B-D81E-43BA-BF1B-BCFA3C785BA0}") ILineDisplayStoredBitmap  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_EscapeSequence(HSTRING &__get_EscapeSequence_result) = 0 ;
	virtual HRESULT __safecall TryDeleteAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDeleteAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_EscapeSequence() { HSTRING __r; HRESULT __hr = get_EscapeSequence(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING EscapeSequence = {read=_scw_get_EscapeSequence};
};

__interface  INTERFACE_UUID("{A95CE2E6-BDD8-4365-8E11-DE94DE8DFF02}") ILineDisplayWindow2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Cursor(_di_ILineDisplayCursor &__get_Cursor_result) = 0 ;
	virtual HRESULT __safecall get_Marquee(_di_ILineDisplayMarquee &__get_Marquee_result) = 0 ;
	virtual HRESULT __safecall ReadCharacterAtCursorAsync(Winapi::Commontypes::_di_IAsyncOperation_1__Cardinal &__ReadCharacterAtCursorAsync_result) = 0 ;
	virtual HRESULT __safecall TryDisplayStoredBitmapAtCursorAsync(_di_ILineDisplayStoredBitmap bitmap, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStoredBitmapAtCursorAsync_result) = 0 ;
	virtual HRESULT __safecall TryDisplayStorageFileBitmapAtCursorAsync(Winapi::Commontypes::_di_IStorageFile bitmap, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStorageFileBitmapAtCursorAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryDisplayStorageFileBitmapAtCursorAsync(Winapi::Commontypes::_di_IStorageFile bitmap, Winapi::Commontypes::LineDisplayHorizontalAlignment horizontalAlignment, Winapi::Commontypes::LineDisplayVerticalAlignment verticalAlignment, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStorageFileBitmapAtCursorAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryDisplayStorageFileBitmapAtCursorAsync(Winapi::Commontypes::_di_IStorageFile bitmap, Winapi::Commontypes::LineDisplayHorizontalAlignment horizontalAlignment, Winapi::Commontypes::LineDisplayVerticalAlignment verticalAlignment, int widthInPixels, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStorageFileBitmapAtCursorAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryDisplayStorageFileBitmapAtPointAsync(Winapi::Commontypes::_di_IStorageFile bitmap, System::Types::TPointF offsetInPixels, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStorageFileBitmapAtPointAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryDisplayStorageFileBitmapAtPointAsync(Winapi::Commontypes::_di_IStorageFile bitmap, System::Types::TPointF offsetInPixels, int widthInPixels, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryDisplayStorageFileBitmapAtPointAsync_result) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILineDisplayCursor _scw_get_Cursor() { _di_ILineDisplayCursor __r; HRESULT __hr = get_Cursor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILineDisplayCursor Cursor = {read=_scw_get_Cursor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILineDisplayMarquee _scw_get_Marquee() { _di_ILineDisplayMarquee __r; HRESULT __hr = get_Marquee(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILineDisplayMarquee Marquee = {read=_scw_get_Marquee};
};

__interface  INTERFACE_UUID("{2257F63C-F263-44F1-A1A0-E750A6A0EC54}") ILineDisplayCustomGlyphs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SizeInPixels(System::Types::TSizeF &__get_SizeInPixels_result) = 0 ;
	virtual HRESULT __safecall get_SupportedGlyphCodes(Winapi::Graphicsrt::_di_IVectorView_1__Cardinal &__get_SupportedGlyphCodes_result) = 0 ;
	virtual HRESULT __safecall TryRedefineAsync(unsigned glyphCode, Winapi::Commontypes::_di_IBuffer glyphData, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryRedefineAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_SizeInPixels() { System::Types::TSizeF __r; HRESULT __hr = get_SizeInPixels(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF SizeInPixels = {read=_scw_get_SizeInPixels};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Graphicsrt::_di_IVectorView_1__Cardinal _scw_get_SupportedGlyphCodes() { Winapi::Graphicsrt::_di_IVectorView_1__Cardinal __r; HRESULT __hr = get_SupportedGlyphCodes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Graphicsrt::_di_IVectorView_1__Cardinal SupportedGlyphCodes = {read=_scw_get_SupportedGlyphCodes};
};

__interface  INTERFACE_UUID("{DDD57C1A-86FB-4EBA-93D1-6F5EDA52B752}") ILineDisplayStatusUpdatedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::LineDisplayPowerStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::LineDisplayPowerStatus _scw_get_Status() { Winapi::Commontypes::LineDisplayPowerStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::LineDisplayPowerStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{ABBA6D19-D81F-5D85-A900-66B96B6D2B32}") AsyncOperationCompletedHandler_1__LineDisplayPowerStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__LineDisplayPowerStatus  : public AsyncOperationCompletedHandler_1__LineDisplayPowerStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__LineDisplayPowerStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{363EEDCD-7922-5503-9009-1C631C9E3653}") IAsyncOperation_1__LineDisplayPowerStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__LineDisplayPowerStatus  : public IAsyncOperation_1__LineDisplayPowerStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::LineDisplayPowerStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__LineDisplayPowerStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C296A628-EF44-40F3-BD1C-B04C6A5CDC7D}") ILineDisplay2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CheckPowerStatusAsync(_di_IAsyncOperation_1__LineDisplayPowerStatus &__CheckPowerStatusAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{C17DE99C-229A-4C14-A6F1-B4E4B1FEAD92}") ILineDisplayAttributes  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsPowerNotifyEnabled(bool &__get_IsPowerNotifyEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsPowerNotifyEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_Brightness(int &__get_Brightness_result) = 0 ;
	virtual HRESULT __safecall put_Brightness(int value) = 0 ;
	virtual HRESULT __safecall get_BlinkRate(Winapi::Commontypes::TimeSpan &__get_BlinkRate_result) = 0 ;
	virtual HRESULT __safecall put_BlinkRate(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall get_ScreenSizeInCharacters(System::Types::TSizeF &__get_ScreenSizeInCharacters_result) = 0 ;
	virtual HRESULT __safecall put_ScreenSizeInCharacters(System::Types::TSizeF value) = 0 ;
	virtual HRESULT __safecall get_CharacterSet(int &__get_CharacterSet_result) = 0 ;
	virtual HRESULT __safecall put_CharacterSet(int value) = 0 ;
	virtual HRESULT __safecall get_IsCharacterSetMappingEnabled(bool &__get_IsCharacterSetMappingEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsCharacterSetMappingEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_CurrentWindow(Winapi::Commontypes::_di_ILineDisplayWindow &__get_CurrentWindow_result) = 0 ;
	virtual HRESULT __safecall put_CurrentWindow(Winapi::Commontypes::_di_ILineDisplayWindow value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_BlinkRate() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_BlinkRate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan BlinkRate = {read=_scw_get_BlinkRate, write=put_BlinkRate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Brightness() { int __r; HRESULT __hr = get_Brightness(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Brightness = {read=_scw_get_Brightness, write=put_Brightness};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_CharacterSet() { int __r; HRESULT __hr = get_CharacterSet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int CharacterSet = {read=_scw_get_CharacterSet, write=put_CharacterSet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_ILineDisplayWindow _scw_get_CurrentWindow() { Winapi::Commontypes::_di_ILineDisplayWindow __r; HRESULT __hr = get_CurrentWindow(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_ILineDisplayWindow CurrentWindow = {read=_scw_get_CurrentWindow, write=put_CurrentWindow};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCharacterSetMappingEnabled() { bool __r; HRESULT __hr = get_IsCharacterSetMappingEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCharacterSetMappingEnabled = {read=_scw_get_IsCharacterSetMappingEnabled, write=put_IsCharacterSetMappingEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsPowerNotifyEnabled() { bool __r; HRESULT __hr = get_IsPowerNotifyEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsPowerNotifyEnabled = {read=_scw_get_IsPowerNotifyEnabled, write=put_IsPowerNotifyEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_ScreenSizeInCharacters() { System::Types::TSizeF __r; HRESULT __hr = get_ScreenSizeInCharacters(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF ScreenSizeInCharacters = {read=_scw_get_ScreenSizeInCharacters, write=put_ScreenSizeInCharacters};
};

__interface  INTERFACE_UUID("{25D178FF-3069-536C-A0C2-88E0250E8A29}") TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{675A25E3-19A3-55E0-990E-CFBD632632F5}") TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs  : public TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IClaimedLineDisplay sender, _di_ILineDisplayStatusUpdatedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{E4D37B02-B65A-5AEC-A219-D1E0B7F3F912}") AsyncOperationCompletedHandler_1__ILineDisplayWindow_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{112D7900-B341-5267-ABCA-9A98C793E3ED}") AsyncOperationCompletedHandler_1__ILineDisplayWindow  : public AsyncOperationCompletedHandler_1__ILineDisplayWindow_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ILineDisplayWindow asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9755F05B-64CC-5051-8350-4ACF1FFCBE58}") IAsyncOperation_1__ILineDisplayWindow_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CCD6F7A8-3DA3-5281-AFF2-38347C529B11}") IAsyncOperation_1__ILineDisplayWindow  : public IAsyncOperation_1__ILineDisplayWindow_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplayWindow handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplayWindow &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_ILineDisplayWindow &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ILineDisplayWindow Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{A576FA69-9988-5A23-844C-F8A69F48A429}") AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1E9170AB-D6FE-5ED2-A6BC-3F00D962A9E8}") AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap  : public AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ILineDisplayStoredBitmap asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{DDA5D77D-B7A1-541D-A480-3D46BED98E9D}") IAsyncOperation_1__ILineDisplayStoredBitmap_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{06E90F61-7265-5591-ADFE-DB01986232F7}") IAsyncOperation_1__ILineDisplayStoredBitmap  : public IAsyncOperation_1__ILineDisplayStoredBitmap_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_ILineDisplayStoredBitmap &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ILineDisplayStoredBitmap Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{A31C75ED-41F5-4E76-A074-795E47A46E97}") IClaimedLineDisplay2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetStatisticsAsync(Winapi::Graphicsrt::_di_IIterable_1__HSTRING statisticsCategories, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__GetStatisticsAsync_result) = 0 ;
	virtual HRESULT __safecall CheckHealthAsync(Winapi::Commontypes::UnifiedPosHealthCheckLevel level, Winapi::Commontypes::_di_IAsyncOperation_1__HSTRING &__CheckHealthAsync_result) = 0 ;
	virtual HRESULT __safecall CheckPowerStatusAsync(_di_IAsyncOperation_1__LineDisplayPowerStatus &__CheckPowerStatusAsync_result) = 0 ;
	virtual HRESULT __safecall add_StatusUpdated(_di_TypedEventHandler_2__IClaimedLineDisplay__ILineDisplayStatusUpdatedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StatusUpdated_result) = 0 ;
	virtual HRESULT __safecall remove_StatusUpdated(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall get_SupportedScreenSizesInCharacters(Winapi::Foundation::_di_IVectorView_1__Size &__get_SupportedScreenSizesInCharacters_result) = 0 ;
	virtual HRESULT __safecall get_MaxBitmapSizeInPixels(System::Types::TSizeF &__get_MaxBitmapSizeInPixels_result) = 0 ;
	virtual HRESULT __safecall get_SupportedCharacterSets(Winapi::Commontypes::_di_IVectorView_1__Integer &__get_SupportedCharacterSets_result) = 0 ;
	virtual HRESULT __safecall get_CustomGlyphs(_di_ILineDisplayCustomGlyphs &__get_CustomGlyphs_result) = 0 ;
	virtual HRESULT __safecall GetAttributes(_di_ILineDisplayAttributes &__GetAttributes_result) = 0 ;
	virtual HRESULT __safecall TryUpdateAttributesAsync(_di_ILineDisplayAttributes attributes, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryUpdateAttributesAsync_result) = 0 ;
	virtual HRESULT __safecall TrySetDescriptorAsync(unsigned descriptor, Winapi::Commontypes::LineDisplayDescriptorState descriptorState, Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TrySetDescriptorAsync_result) = 0 ;
	virtual HRESULT __safecall TryClearDescriptorsAsync(Winapi::Graphicsrt::_di_IAsyncOperation_1__Boolean &__TryClearDescriptorsAsync_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall TryCreateWindowAsync(System::Types::TRectF viewport, System::Types::TSizeF windowSize, _di_IAsyncOperation_1__ILineDisplayWindow &__TryCreateWindowAsync_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall TryCreateWindowAsync(const System::Types::TRectF &viewport, System::Types::TSizeF windowSize, _di_IAsyncOperation_1__ILineDisplayWindow &__TryCreateWindowAsync_result) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall TryStoreStorageFileBitmapAsync(Winapi::Commontypes::_di_IStorageFile bitmap, _di_IAsyncOperation_1__ILineDisplayStoredBitmap &__TryStoreStorageFileBitmapAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryStoreStorageFileBitmapAsync(Winapi::Commontypes::_di_IStorageFile bitmap, Winapi::Commontypes::LineDisplayHorizontalAlignment horizontalAlignment, Winapi::Commontypes::LineDisplayVerticalAlignment verticalAlignment, _di_IAsyncOperation_1__ILineDisplayStoredBitmap &__TryStoreStorageFileBitmapAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall TryStoreStorageFileBitmapAsync(Winapi::Commontypes::_di_IStorageFile bitmap, Winapi::Commontypes::LineDisplayHorizontalAlignment horizontalAlignment, Winapi::Commontypes::LineDisplayVerticalAlignment verticalAlignment, int widthInPixels, _di_IAsyncOperation_1__ILineDisplayStoredBitmap &__TryStoreStorageFileBitmapAsync_result) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILineDisplayCustomGlyphs _scw_get_CustomGlyphs() { _di_ILineDisplayCustomGlyphs __r; HRESULT __hr = get_CustomGlyphs(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILineDisplayCustomGlyphs CustomGlyphs = {read=_scw_get_CustomGlyphs};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_MaxBitmapSizeInPixels() { System::Types::TSizeF __r; HRESULT __hr = get_MaxBitmapSizeInPixels(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF MaxBitmapSizeInPixels = {read=_scw_get_MaxBitmapSizeInPixels};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IVectorView_1__Integer _scw_get_SupportedCharacterSets() { Winapi::Commontypes::_di_IVectorView_1__Integer __r; HRESULT __hr = get_SupportedCharacterSets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IVectorView_1__Integer SupportedCharacterSets = {read=_scw_get_SupportedCharacterSets};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::_di_IVectorView_1__Size _scw_get_SupportedScreenSizesInCharacters() { Winapi::Foundation::_di_IVectorView_1__Size __r; HRESULT __hr = get_SupportedScreenSizesInCharacters(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::_di_IVectorView_1__Size SupportedScreenSizesInCharacters = {read=_scw_get_SupportedScreenSizesInCharacters};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPosPrinterCharacterSetIds : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IPosPrinterCharacterSetIdsStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IPosPrinterCharacterSetIdsStatics> inherited;
	
public:
	static unsigned __fastcall get_Utf16LE();
	static unsigned __fastcall get_Ascii();
	static unsigned __fastcall get_Ansi();
	/* static */ __property unsigned Ansi = {read=get_Ansi, nodefault};
	/* static */ __property unsigned Ascii = {read=get_Ascii, nodefault};
	/* static */ __property unsigned Utf16LE = {read=get_Utf16LE, nodefault};
public:
	/* TObject.Create */ inline __fastcall TPosPrinterCharacterSetIds() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IPosPrinterCharacterSetIdsStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPosPrinterCharacterSetIds() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPosPrinter : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_IPosPrinterStatics,_di_IPosPrinterStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_IPosPrinterStatics,_di_IPosPrinterStatics2> inherited;
	
public:
	static _di_IAsyncOperation_1__IPosPrinter __fastcall GetDefaultAsync();
	static _di_IAsyncOperation_1__IPosPrinter __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector()/* overload */;
	static HSTRING __fastcall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TPosPrinter() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_IPosPrinterStatics,_di_IPosPrinterStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPosPrinter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCashDrawer : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICashDrawerStatics,_di_ICashDrawerStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICashDrawerStatics,_di_ICashDrawerStatics2> inherited;
	
public:
	static _di_IAsyncOperation_1__ICashDrawer __fastcall GetDefaultAsync();
	static _di_IAsyncOperation_1__ICashDrawer __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector()/* overload */;
	static HSTRING __fastcall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TCashDrawer() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_ICashDrawerStatics,_di_ICashDrawerStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCashDrawer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLineDisplay : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_ILineDisplayStatics,_di_ILineDisplayStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_ILineDisplayStatics,_di_ILineDisplayStatics2> inherited;
	
public:
	static _di_ILineDisplayStatisticsCategorySelector __fastcall get_StatisticsCategorySelector();
	/* static */ __property _di_ILineDisplayStatisticsCategorySelector StatisticsCategorySelector = {read=get_StatisticsCategorySelector};
	static _di_IAsyncOperation_1__ILineDisplay __fastcall FromIdAsync(HSTRING deviceId);
	static _di_IAsyncOperation_1__ILineDisplay __fastcall GetDefaultAsync();
	static HSTRING __fastcall GetDeviceSelector()/* overload */;
	static HSTRING __fastcall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TLineDisplay() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_ILineDisplayStatics,_di_ILineDisplayStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLineDisplay() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TClaimedLineDisplay : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IClaimedLineDisplayStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IClaimedLineDisplayStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IClaimedLineDisplay __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector()/* overload */;
	static HSTRING __fastcall GetDeviceSelector(Winapi::Commontypes::PosConnectionTypes connectionTypes)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TClaimedLineDisplay() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IClaimedLineDisplayStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TClaimedLineDisplay() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pointofservice */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_PointofserviceHPP
