// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ApplicationModel.DataTransfer.pas' rev: 34.00 (Windows)

#ifndef Winapi_Applicationmodel_DatatransferHPP
#define Winapi_Applicationmodel_DatatransferHPP

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
#include <Winapi.Security.hpp>
#include <Winapi.GraphicsRT.hpp>
#include <Winapi.Foundation.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Applicationmodel
{
namespace Datatransfer
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IStandardDataFormatsStatics;
typedef System::DelphiInterface<IStandardDataFormatsStatics> _di_IStandardDataFormatsStatics;
__interface DELPHIINTERFACE IStandardDataFormatsStatics2;
typedef System::DelphiInterface<IStandardDataFormatsStatics2> _di_IStandardDataFormatsStatics2;
__interface DELPHIINTERFACE IDataPackagePropertySetView2;
typedef System::DelphiInterface<IDataPackagePropertySetView2> _di_IDataPackagePropertySetView2;
__interface DELPHIINTERFACE IDataPackagePropertySetView3;
typedef System::DelphiInterface<IDataPackagePropertySetView3> _di_IDataPackagePropertySetView3;
__interface DELPHIINTERFACE IDataPackagePropertySet2;
typedef System::DelphiInterface<IDataPackagePropertySet2> _di_IDataPackagePropertySet2;
__interface DELPHIINTERFACE IDataPackagePropertySet3;
typedef System::DelphiInterface<IDataPackagePropertySet3> _di_IDataPackagePropertySet3;
__interface DELPHIINTERFACE IOperationCompletedEventArgs2;
typedef System::DelphiInterface<IOperationCompletedEventArgs2> _di_IOperationCompletedEventArgs2;
__interface DELPHIINTERFACE IShareProvider;
typedef System::DelphiInterface<IShareProvider> _di_IShareProvider;
__interface DELPHIINTERFACE IShareTargetInfo;
typedef System::DelphiInterface<IShareTargetInfo> _di_IShareTargetInfo;
__interface DELPHIINTERFACE IShareCompletedEventArgs;
typedef System::DelphiInterface<IShareCompletedEventArgs> _di_IShareCompletedEventArgs;
__interface DELPHIINTERFACE IDataPackageView2;
typedef System::DelphiInterface<IDataPackageView2> _di_IDataPackageView2;
__interface DELPHIINTERFACE IDataPackageView3;
typedef System::DelphiInterface<IDataPackageView3> _di_IDataPackageView3;
__interface DELPHIINTERFACE IDataPackageView4;
typedef System::DelphiInterface<IDataPackageView4> _di_IDataPackageView4;
__interface DELPHIINTERFACE IDataPackage2;
typedef System::DelphiInterface<IDataPackage2> _di_IDataPackage2;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs> _di_TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs;
__interface DELPHIINTERFACE IDataPackage3;
typedef System::DelphiInterface<IDataPackage3> _di_IDataPackage3;
__interface DELPHIINTERFACE IHtmlFormatHelperStatics;
typedef System::DelphiInterface<IHtmlFormatHelperStatics> _di_IHtmlFormatHelperStatics;
__interface DELPHIINTERFACE IClipboardStatics;
typedef System::DelphiInterface<IClipboardStatics> _di_IClipboardStatics;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragInfo;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragInfo> _di_DragDrop_Core_ICoreDragInfo;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragInfo2;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragInfo2> _di_DragDrop_Core_ICoreDragInfo2;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragUIOverride;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragUIOverride> _di_DragDrop_Core_ICoreDragUIOverride;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DataPackageOperation_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DataPackageOperation_Delegate_Base> _di_AsyncOperationCompletedHandler_1__DataPackageOperation_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__DataPackageOperation;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__DataPackageOperation> _di_AsyncOperationCompletedHandler_1__DataPackageOperation;
__interface DELPHIINTERFACE IAsyncOperation_1__DataPackageOperation_Base;
typedef System::DelphiInterface<IAsyncOperation_1__DataPackageOperation_Base> _di_IAsyncOperation_1__DataPackageOperation_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__DataPackageOperation;
typedef System::DelphiInterface<IAsyncOperation_1__DataPackageOperation> _di_IAsyncOperation_1__DataPackageOperation;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDropOperationTarget;
typedef System::DelphiInterface<DragDrop_Core_ICoreDropOperationTarget> _di_DragDrop_Core_ICoreDropOperationTarget;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragOperation;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragOperation> _di_DragDrop_Core_ICoreDragOperation;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragOperation2;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragOperation2> _di_DragDrop_Core_ICoreDragOperation2;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;
typedef System::DelphiInterface<DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs> _di_DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs> _di_TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragDropManager;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragDropManager> _di_DragDrop_Core_ICoreDragDropManager;
__interface DELPHIINTERFACE DragDrop_Core_ICoreDragDropManagerStatics;
typedef System::DelphiInterface<DragDrop_Core_ICoreDragDropManagerStatics> _di_DragDrop_Core_ICoreDragDropManagerStatics;
__interface DELPHIINTERFACE IShareUIOptions;
typedef System::DelphiInterface<IShareUIOptions> _di_IShareUIOptions;
__interface DELPHIINTERFACE IDataRequestDeferral;
typedef System::DelphiInterface<IDataRequestDeferral> _di_IDataRequestDeferral;
__interface DELPHIINTERFACE IDataRequest;
typedef System::DelphiInterface<IDataRequest> _di_IDataRequest;
__interface DELPHIINTERFACE IDataRequestedEventArgs;
typedef System::DelphiInterface<IDataRequestedEventArgs> _di_IDataRequestedEventArgs;
__interface DELPHIINTERFACE IIterator_1__IShareProvider_Base;
typedef System::DelphiInterface<IIterator_1__IShareProvider_Base> _di_IIterator_1__IShareProvider_Base;
__interface DELPHIINTERFACE IIterator_1__IShareProvider;
typedef System::DelphiInterface<IIterator_1__IShareProvider> _di_IIterator_1__IShareProvider;
__interface DELPHIINTERFACE IIterable_1__IShareProvider_Base;
typedef System::DelphiInterface<IIterable_1__IShareProvider_Base> _di_IIterable_1__IShareProvider_Base;
__interface DELPHIINTERFACE IIterable_1__IShareProvider;
typedef System::DelphiInterface<IIterable_1__IShareProvider> _di_IIterable_1__IShareProvider;
__interface DELPHIINTERFACE IVectorView_1__IShareProvider;
typedef System::DelphiInterface<IVectorView_1__IShareProvider> _di_IVectorView_1__IShareProvider;
__interface DELPHIINTERFACE IVector_1__IShareProvider;
typedef System::DelphiInterface<IVector_1__IShareProvider> _di_IVector_1__IShareProvider;
__interface DELPHIINTERFACE IShareProvidersRequestedEventArgs;
typedef System::DelphiInterface<IShareProvidersRequestedEventArgs> _di_IShareProvidersRequestedEventArgs;
__interface DELPHIINTERFACE ITargetApplicationChosenEventArgs;
typedef System::DelphiInterface<ITargetApplicationChosenEventArgs> _di_ITargetApplicationChosenEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs> _di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs> _di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs;
__interface DELPHIINTERFACE IDataTransferManager;
typedef System::DelphiInterface<IDataTransferManager> _di_IDataTransferManager;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs> _di_TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs;
__interface DELPHIINTERFACE IDataTransferManager2;
typedef System::DelphiInterface<IDataTransferManager2> _di_IDataTransferManager2;
__interface DELPHIINTERFACE IDataTransferManagerStatics;
typedef System::DelphiInterface<IDataTransferManagerStatics> _di_IDataTransferManagerStatics;
__interface DELPHIINTERFACE IDataTransferManagerStatics2;
typedef System::DelphiInterface<IDataTransferManagerStatics2> _di_IDataTransferManagerStatics2;
__interface DELPHIINTERFACE IDataTransferManagerStatics3;
typedef System::DelphiInterface<IDataTransferManagerStatics3> _di_IDataTransferManagerStatics3;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDataPackage_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDataPackage_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IDataPackage_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IDataPackage;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IDataPackage> _di_AsyncOperationCompletedHandler_1__IDataPackage;
__interface DELPHIINTERFACE IAsyncOperation_1__IDataPackage_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IDataPackage_Base> _di_IAsyncOperation_1__IDataPackage_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IDataPackage;
typedef System::DelphiInterface<IAsyncOperation_1__IDataPackage> _di_IAsyncOperation_1__IDataPackage;
class DELPHICLASS TStandardDataFormats;
class DELPHICLASS TDataPackage;
class DELPHICLASS THtmlFormatHelper;
class DELPHICLASS TClipboard;
class DELPHICLASS TDragDrop_Core_CoreDragDropManager;
class DELPHICLASS TDragDrop_Core_CoreDragOperation;
class DELPHICLASS TShareUIOptions;
__interface DELPHIINTERFACE IDataTransferManagerInterop;
typedef System::DelphiInterface<IDataTransferManagerInterop> _di_IDataTransferManagerInterop;
class DELPHICLASS TDataTransferManager;
//-- type declarations -------------------------------------------------------
;

;

typedef _di_IStandardDataFormatsStatics *PIStandardDataFormatsStatics;

typedef _di_IStandardDataFormatsStatics2 *PIStandardDataFormatsStatics2;

typedef _di_IDataPackagePropertySetView2 *PIDataPackagePropertySetView2;

typedef _di_IDataPackagePropertySetView3 *PIDataPackagePropertySetView3;

typedef _di_IDataPackagePropertySet2 *PIDataPackagePropertySet2;

typedef _di_IDataPackagePropertySet3 *PIDataPackagePropertySet3;

typedef _di_IOperationCompletedEventArgs2 *PIOperationCompletedEventArgs2;

typedef _di_IShareProvider *PIShareProvider;

typedef _di_IShareTargetInfo *PIShareTargetInfo;

typedef _di_IShareCompletedEventArgs *PIShareCompletedEventArgs;

typedef _di_IDataPackageView2 *PIDataPackageView2;

typedef _di_IDataPackageView3 *PIDataPackageView3;

typedef _di_IDataPackageView4 *PIDataPackageView4;

typedef _di_IDataPackage2 *PIDataPackage2;

typedef _di_TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs *PTypedEventHandler_2__IDataPackage__IShareCompletedEventArgs;

typedef _di_IDataPackage3 *PIDataPackage3;

typedef _di_IHtmlFormatHelperStatics *PIHtmlFormatHelperStatics;

typedef _di_IClipboardStatics *PIClipboardStatics;

typedef _di_DragDrop_Core_ICoreDragInfo *PDragDrop_Core_ICoreDragInfo;

typedef _di_DragDrop_Core_ICoreDragInfo2 *PDragDrop_Core_ICoreDragInfo2;

typedef _di_DragDrop_Core_ICoreDragUIOverride *PDragDrop_Core_ICoreDragUIOverride;

typedef _di_AsyncOperationCompletedHandler_1__DataPackageOperation *PAsyncOperationCompletedHandler_1__DataPackageOperation;

typedef _di_IAsyncOperation_1__DataPackageOperation *PIAsyncOperation_1__DataPackageOperation;

typedef _di_DragDrop_Core_ICoreDropOperationTarget *PDragDrop_Core_ICoreDropOperationTarget;

typedef _di_DragDrop_Core_ICoreDragOperation *PDragDrop_Core_ICoreDragOperation;

typedef _di_DragDrop_Core_ICoreDragOperation2 *PDragDrop_Core_ICoreDragOperation2;

typedef _di_DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs *PDragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;

typedef _di_TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs *PTypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs;

typedef _di_DragDrop_Core_ICoreDragDropManager *PDragDrop_Core_ICoreDragDropManager;

typedef _di_DragDrop_Core_ICoreDragDropManagerStatics *PDragDrop_Core_ICoreDragDropManagerStatics;

typedef _di_IShareUIOptions *PIShareUIOptions;

typedef _di_IDataRequestDeferral *PIDataRequestDeferral;

typedef _di_IDataRequest *PIDataRequest;

typedef _di_IDataRequestedEventArgs *PIDataRequestedEventArgs;

typedef _di_IIterator_1__IShareProvider *PIIterator_1__IShareProvider;

typedef _di_IIterable_1__IShareProvider *PIIterable_1__IShareProvider;

typedef _di_IVectorView_1__IShareProvider *PIVectorView_1__IShareProvider;

typedef _di_IVector_1__IShareProvider *PIVector_1__IShareProvider;

typedef _di_IShareProvidersRequestedEventArgs *PIShareProvidersRequestedEventArgs;

typedef _di_ITargetApplicationChosenEventArgs *PITargetApplicationChosenEventArgs;

typedef _di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs *PTypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs;

typedef _di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs *PTypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs;

typedef _di_IDataTransferManager *PIDataTransferManager;

typedef _di_TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs *PTypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs;

typedef _di_IDataTransferManager2 *PIDataTransferManager2;

typedef _di_IDataTransferManagerStatics *PIDataTransferManagerStatics;

typedef _di_IDataTransferManagerStatics2 *PIDataTransferManagerStatics2;

typedef _di_IDataTransferManagerStatics3 *PIDataTransferManagerStatics3;

typedef _di_AsyncOperationCompletedHandler_1__IDataPackage *PAsyncOperationCompletedHandler_1__IDataPackage;

typedef _di_IAsyncOperation_1__IDataPackage *PIAsyncOperation_1__IDataPackage;

__interface  INTERFACE_UUID("{7ED681A1-A880-40C9-B4ED-0BEE1E15F549}") IStandardDataFormatsStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Text(HSTRING &__get_Text_result) = 0 ;
	virtual HRESULT __safecall get_Uri(HSTRING &__get_Uri_result) = 0 ;
	virtual HRESULT __safecall get_Html(HSTRING &__get_Html_result) = 0 ;
	virtual HRESULT __safecall get_Rtf(HSTRING &__get_Rtf_result) = 0 ;
	virtual HRESULT __safecall get_Bitmap(HSTRING &__get_Bitmap_result) = 0 ;
	virtual HRESULT __safecall get_StorageItems(HSTRING &__get_StorageItems_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Bitmap() { HSTRING __r; HRESULT __hr = get_Bitmap(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Bitmap = {read=_scw_get_Bitmap};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Html() { HSTRING __r; HRESULT __hr = get_Html(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Html = {read=_scw_get_Html};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Rtf() { HSTRING __r; HRESULT __hr = get_Rtf(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Rtf = {read=_scw_get_Rtf};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_StorageItems() { HSTRING __r; HRESULT __hr = get_StorageItems(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING StorageItems = {read=_scw_get_StorageItems};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Text() { HSTRING __r; HRESULT __hr = get_Text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Text = {read=_scw_get_Text};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Uri() { HSTRING __r; HRESULT __hr = get_Uri(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Uri = {read=_scw_get_Uri};
};

__interface  INTERFACE_UUID("{42A254F4-9D76-42E8-861B-47C25DD0CF71}") IStandardDataFormatsStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_WebLink(HSTRING &__get_WebLink_result) = 0 ;
	virtual HRESULT __safecall get_ApplicationLink(HSTRING &__get_ApplicationLink_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ApplicationLink() { HSTRING __r; HRESULT __hr = get_ApplicationLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ApplicationLink = {read=_scw_get_ApplicationLink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_WebLink() { HSTRING __r; HRESULT __hr = get_WebLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING WebLink = {read=_scw_get_WebLink};
};

__interface  INTERFACE_UUID("{6054509B-8EBE-4FEB-9C1E-75E69DE54B84}") IDataPackagePropertySetView2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PackageFamilyName(HSTRING &__get_PackageFamilyName_result) = 0 ;
	virtual HRESULT __safecall get_ContentSourceWebLink(Winapi::Commontypes::_di_IUriRuntimeClass &__get_ContentSourceWebLink_result) = 0 ;
	virtual HRESULT __safecall get_ContentSourceApplicationLink(Winapi::Commontypes::_di_IUriRuntimeClass &__get_ContentSourceApplicationLink_result) = 0 ;
	virtual HRESULT __safecall get_Square30x30Logo(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_Square30x30Logo_result) = 0 ;
	virtual HRESULT __safecall get_LogoBackgroundColor(Winapi::Commontypes::Color &__get_LogoBackgroundColor_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_ContentSourceApplicationLink() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_ContentSourceApplicationLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass ContentSourceApplicationLink = {read=_scw_get_ContentSourceApplicationLink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_ContentSourceWebLink() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_ContentSourceWebLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass ContentSourceWebLink = {read=_scw_get_ContentSourceWebLink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_LogoBackgroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_LogoBackgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color LogoBackgroundColor = {read=_scw_get_LogoBackgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PackageFamilyName() { HSTRING __r; HRESULT __hr = get_PackageFamilyName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PackageFamilyName = {read=_scw_get_PackageFamilyName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_Square30x30Logo() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_Square30x30Logo(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference Square30x30Logo = {read=_scw_get_Square30x30Logo};
};

__interface  INTERFACE_UUID("{DB764CE5-D174-495C-84FC-1A51F6AB45D7}") IDataPackagePropertySetView3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_EnterpriseId(HSTRING &__get_EnterpriseId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_EnterpriseId() { HSTRING __r; HRESULT __hr = get_EnterpriseId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING EnterpriseId = {read=_scw_get_EnterpriseId};
};

__interface  INTERFACE_UUID("{EB505D4A-9800-46AA-B181-7B6F0F2B919A}") IDataPackagePropertySet2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ContentSourceWebLink(Winapi::Commontypes::_di_IUriRuntimeClass &__get_ContentSourceWebLink_result) = 0 ;
	virtual HRESULT __safecall put_ContentSourceWebLink(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall get_ContentSourceApplicationLink(Winapi::Commontypes::_di_IUriRuntimeClass &__get_ContentSourceApplicationLink_result) = 0 ;
	virtual HRESULT __safecall put_ContentSourceApplicationLink(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall get_PackageFamilyName(HSTRING &__get_PackageFamilyName_result) = 0 ;
	virtual HRESULT __safecall put_PackageFamilyName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Square30x30Logo(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_Square30x30Logo_result) = 0 ;
	virtual HRESULT __safecall put_Square30x30Logo(Winapi::Commontypes::_di_IRandomAccessStreamReference value) = 0 ;
	virtual HRESULT __safecall get_LogoBackgroundColor(Winapi::Commontypes::Color &__get_LogoBackgroundColor_result) = 0 ;
	virtual HRESULT __safecall put_LogoBackgroundColor(Winapi::Commontypes::Color value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_ContentSourceApplicationLink() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_ContentSourceApplicationLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass ContentSourceApplicationLink = {read=_scw_get_ContentSourceApplicationLink, write=put_ContentSourceApplicationLink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_ContentSourceWebLink() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_ContentSourceWebLink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass ContentSourceWebLink = {read=_scw_get_ContentSourceWebLink, write=put_ContentSourceWebLink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_LogoBackgroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_LogoBackgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color LogoBackgroundColor = {read=_scw_get_LogoBackgroundColor, write=put_LogoBackgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PackageFamilyName() { HSTRING __r; HRESULT __hr = get_PackageFamilyName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PackageFamilyName = {read=_scw_get_PackageFamilyName, write=put_PackageFamilyName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_Square30x30Logo() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_Square30x30Logo(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference Square30x30Logo = {read=_scw_get_Square30x30Logo, write=put_Square30x30Logo};
};

__interface  INTERFACE_UUID("{9E87FD9B-5205-401B-874A-455653BD39E8}") IDataPackagePropertySet3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_EnterpriseId(HSTRING &__get_EnterpriseId_result) = 0 ;
	virtual HRESULT __safecall put_EnterpriseId(HSTRING value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_EnterpriseId() { HSTRING __r; HRESULT __hr = get_EnterpriseId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING EnterpriseId = {read=_scw_get_EnterpriseId, write=put_EnterpriseId};
};

__interface  INTERFACE_UUID("{858FA073-1E19-4105-B2F7-C8478808D562}") IOperationCompletedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AcceptedFormatId(HSTRING &__get_AcceptedFormatId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AcceptedFormatId() { HSTRING __r; HRESULT __hr = get_AcceptedFormatId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AcceptedFormatId = {read=_scw_get_AcceptedFormatId};
};

__interface  INTERFACE_UUID("{2FABE026-443E-4CDA-AF25-8D81070EFD80}") IShareProvider  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Title(HSTRING &__get_Title_result) = 0 ;
	virtual HRESULT __safecall get_DisplayIcon(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_DisplayIcon_result) = 0 ;
	virtual HRESULT __safecall get_BackgroundColor(Winapi::Commontypes::Color &__get_BackgroundColor_result) = 0 ;
	virtual HRESULT __safecall get_Tag(Winapi::Winrt::_di_IInspectable &__get_Tag_result) = 0 ;
	virtual HRESULT __safecall put_Tag(Winapi::Winrt::_di_IInspectable value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_BackgroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_BackgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color BackgroundColor = {read=_scw_get_BackgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_DisplayIcon() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_DisplayIcon(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference DisplayIcon = {read=_scw_get_DisplayIcon};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Tag() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Tag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Tag = {read=_scw_get_Tag, write=put_Tag};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Title() { HSTRING __r; HRESULT __hr = get_Title(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Title = {read=_scw_get_Title};
};

__interface  INTERFACE_UUID("{385BE607-C6E8-4114-B294-28F3BB6F9904}") IShareTargetInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AppUserModelId(HSTRING &__get_AppUserModelId_result) = 0 ;
	virtual HRESULT __safecall get_ShareProvider(_di_IShareProvider &__get_ShareProvider_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AppUserModelId() { HSTRING __r; HRESULT __hr = get_AppUserModelId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AppUserModelId = {read=_scw_get_AppUserModelId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IShareProvider _scw_get_ShareProvider() { _di_IShareProvider __r; HRESULT __hr = get_ShareProvider(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IShareProvider ShareProvider = {read=_scw_get_ShareProvider};
};

__interface  INTERFACE_UUID("{4574C442-F913-4F60-9DF7-CC4060AB1916}") IShareCompletedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ShareTarget(_di_IShareTargetInfo &__get_ShareTarget_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IShareTargetInfo _scw_get_ShareTarget() { _di_IShareTargetInfo __r; HRESULT __hr = get_ShareTarget(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IShareTargetInfo ShareTarget = {read=_scw_get_ShareTarget};
};

__interface  INTERFACE_UUID("{40ECBA95-2450-4C1D-B6B4-ED45463DEE9C}") IDataPackageView2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetApplicationLinkAsync(Winapi::Commontypes::_di_IAsyncOperation_1__IUriRuntimeClass &__GetApplicationLinkAsync_result) = 0 ;
	virtual HRESULT __safecall GetWebLinkAsync(Winapi::Commontypes::_di_IAsyncOperation_1__IUriRuntimeClass &__GetWebLinkAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{D37771A8-DDAD-4288-8428-D1CAE394128B}") IDataPackageView3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall RequestAccessAsync(Winapi::Security::_di_IAsyncOperation_1__EnterpriseData_ProtectionPolicyEvaluationResult &__RequestAccessAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall RequestAccessAsync(HSTRING enterpriseId, Winapi::Security::_di_IAsyncOperation_1__EnterpriseData_ProtectionPolicyEvaluationResult &__RequestAccessAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall UnlockAndAssumeEnterpriseIdentity(Winapi::Commontypes::EnterpriseData_ProtectionPolicyEvaluationResult &__UnlockAndAssumeEnterpriseIdentity_result) = 0 ;
};

__interface  INTERFACE_UUID("{DFE96F1F-E042-4433-A09F-26D6FFDA8B85}") IDataPackageView4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetAcceptedFormatId(HSTRING formatId) = 0 ;
};

__interface  INTERFACE_UUID("{041C1FE9-2409-45E1-A538-4C53EEEE04A7}") IDataPackage2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetApplicationLink(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall SetWebLink(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
};

__interface  INTERFACE_UUID("{F8F7E24A-56FE-58DF-BC15-2365AEC03966}") TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{2B4C35E5-96FD-58E2-82A0-3B40DF89065E}") TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs  : public TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IDataPackage sender, _di_IShareCompletedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{88F31F5D-787B-4D32-965A-A9838105A056}") IDataPackage3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ShareCompleted(_di_TypedEventHandler_2__IDataPackage__IShareCompletedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ShareCompleted_result) = 0 ;
	virtual HRESULT __safecall remove_ShareCompleted(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{E22E7749-DD70-446F-AEFC-61CEE59F655E}") IHtmlFormatHelperStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetStaticFragment(HSTRING htmlFormat, HSTRING &__GetStaticFragment_result) = 0 ;
	virtual HRESULT __safecall CreateHtmlFormat(HSTRING htmlFragment, HSTRING &__CreateHtmlFormat_result) = 0 ;
};

__interface  INTERFACE_UUID("{C627E291-34E2-4963-8EED-93CBB0EA3D70}") IClipboardStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetContent(Winapi::Commontypes::_di_IDataPackageView &__GetContent_result) = 0 ;
	virtual HRESULT __safecall SetContent(Winapi::Commontypes::_di_IDataPackage content) = 0 ;
	virtual HRESULT __safecall Flush() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall add_ContentChanged(Winapi::Graphicsrt::_di_EventHandler_1__IInspectable changeHandler, Winapi::Commontypes::EventRegistrationToken &__add_ContentChanged_result) = 0 ;
	virtual HRESULT __safecall remove_ContentChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{48353A8B-CB50-464E-9575-CD4E3A7AB028}") DragDrop_Core_ICoreDragInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IDataPackageView &__get_Data_result) = 0 ;
	virtual HRESULT __safecall get_Modifiers(Winapi::Commontypes::DragDrop_DragDropModifiers &__get_Modifiers_result) = 0 ;
	virtual HRESULT __safecall get_Position(System::Types::TPointF &__get_Position_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDataPackageView _scw_get_Data() { Winapi::Commontypes::_di_IDataPackageView __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDataPackageView Data = {read=_scw_get_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DragDrop_DragDropModifiers _scw_get_Modifiers() { Winapi::Commontypes::DragDrop_DragDropModifiers __r; HRESULT __hr = get_Modifiers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DragDrop_DragDropModifiers Modifiers = {read=_scw_get_Modifiers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Position() { System::Types::TPointF __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Position = {read=_scw_get_Position};
};

__interface  INTERFACE_UUID("{C54691E5-E6FB-4D74-B4B1-8A3C17F25E9E}") DragDrop_Core_ICoreDragInfo2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AllowedOperations(Winapi::Commontypes::DataPackageOperation &__get_AllowedOperations_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DataPackageOperation _scw_get_AllowedOperations() { Winapi::Commontypes::DataPackageOperation __r; HRESULT __hr = get_AllowedOperations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DataPackageOperation AllowedOperations = {read=_scw_get_AllowedOperations};
};

__interface  INTERFACE_UUID("{89A85064-3389-4F4F-8897-7E8A3FFB3C93}") DragDrop_Core_ICoreDragUIOverride  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetContentFromSoftwareBitmap(Winapi::Graphicsrt::_di_Imaging_ISoftwareBitmap softwareBitmap) = 0 /* overload */;
	virtual HRESULT __safecall SetContentFromSoftwareBitmap(Winapi::Graphicsrt::_di_Imaging_ISoftwareBitmap softwareBitmap, System::Types::TPointF anchorPoint) = 0 /* overload */;
	virtual HRESULT __safecall get_IsContentVisible(bool &__get_IsContentVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsContentVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_Caption(HSTRING &__get_Caption_result) = 0 ;
	virtual HRESULT __safecall put_Caption(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_IsCaptionVisible(bool &__get_IsCaptionVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsCaptionVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_IsGlyphVisible(bool &__get_IsGlyphVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsGlyphVisible(bool value) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Caption() { HSTRING __r; HRESULT __hr = get_Caption(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Caption = {read=_scw_get_Caption, write=put_Caption};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCaptionVisible() { bool __r; HRESULT __hr = get_IsCaptionVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCaptionVisible = {read=_scw_get_IsCaptionVisible, write=put_IsCaptionVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsContentVisible() { bool __r; HRESULT __hr = get_IsContentVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsContentVisible = {read=_scw_get_IsContentVisible, write=put_IsContentVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsGlyphVisible() { bool __r; HRESULT __hr = get_IsGlyphVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsGlyphVisible = {read=_scw_get_IsGlyphVisible, write=put_IsGlyphVisible};
};

__interface  INTERFACE_UUID("{ADD21D46-17DF-5A43-A685-3262FCE84643}") AsyncOperationCompletedHandler_1__DataPackageOperation_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__DataPackageOperation  : public AsyncOperationCompletedHandler_1__DataPackageOperation_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__DataPackageOperation asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{8B98AEA9-64F0-5672-B30E-DFD9C2E4F6FE}") IAsyncOperation_1__DataPackageOperation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__DataPackageOperation  : public IAsyncOperation_1__DataPackageOperation_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__DataPackageOperation handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__DataPackageOperation &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::DataPackageOperation &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__DataPackageOperation _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__DataPackageOperation __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__DataPackageOperation Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{D9126196-4C5B-417D-BB37-76381DEF8DB4}") DragDrop_Core_ICoreDropOperationTarget  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall EnterAsync(_di_DragDrop_Core_ICoreDragInfo dragInfo, _di_DragDrop_Core_ICoreDragUIOverride dragUIOverride, _di_IAsyncOperation_1__DataPackageOperation &__EnterAsync_result) = 0 ;
	virtual HRESULT __safecall OverAsync(_di_DragDrop_Core_ICoreDragInfo dragInfo, _di_DragDrop_Core_ICoreDragUIOverride dragUIOverride, _di_IAsyncOperation_1__DataPackageOperation &__OverAsync_result) = 0 ;
	virtual HRESULT __safecall LeaveAsync(_di_DragDrop_Core_ICoreDragInfo dragInfo, Winapi::Commontypes::_di_IAsyncAction &__LeaveAsync_result) = 0 ;
	virtual HRESULT __safecall DropAsync(_di_DragDrop_Core_ICoreDragInfo dragInfo, _di_IAsyncOperation_1__DataPackageOperation &__DropAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{CC06DE4F-6DB0-4E62-AB1B-A74A02DC6D85}") DragDrop_Core_ICoreDragOperation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IDataPackage &__get_Data_result) = 0 ;
	virtual HRESULT __safecall SetPointerId(unsigned pointerId) = 0 ;
	virtual HRESULT __safecall SetDragUIContentFromSoftwareBitmap(Winapi::Graphicsrt::_di_Imaging_ISoftwareBitmap softwareBitmap) = 0 /* overload */;
	virtual HRESULT __safecall SetDragUIContentFromSoftwareBitmap(Winapi::Graphicsrt::_di_Imaging_ISoftwareBitmap softwareBitmap, System::Types::TPointF anchorPoint) = 0 /* overload */;
	virtual HRESULT __safecall get_DragUIContentMode(Winapi::Commontypes::DragDrop_Core_CoreDragUIContentMode &__get_DragUIContentMode_result) = 0 ;
	virtual HRESULT __safecall put_DragUIContentMode(Winapi::Commontypes::DragDrop_Core_CoreDragUIContentMode value) = 0 ;
	virtual HRESULT __safecall StartAsync(_di_IAsyncOperation_1__DataPackageOperation &__StartAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDataPackage _scw_get_Data() { Winapi::Commontypes::_di_IDataPackage __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDataPackage Data = {read=_scw_get_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DragDrop_Core_CoreDragUIContentMode _scw_get_DragUIContentMode() { Winapi::Commontypes::DragDrop_Core_CoreDragUIContentMode __r; HRESULT __hr = get_DragUIContentMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DragDrop_Core_CoreDragUIContentMode DragUIContentMode = {read=_scw_get_DragUIContentMode, write=put_DragUIContentMode};
};

__interface  INTERFACE_UUID("{824B1E2C-D99A-4FC3-8507-6C182F33B46A}") DragDrop_Core_ICoreDragOperation2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AllowedOperations(Winapi::Commontypes::DataPackageOperation &__get_AllowedOperations_result) = 0 ;
	virtual HRESULT __safecall put_AllowedOperations(Winapi::Commontypes::DataPackageOperation value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DataPackageOperation _scw_get_AllowedOperations() { Winapi::Commontypes::DataPackageOperation __r; HRESULT __hr = get_AllowedOperations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DataPackageOperation AllowedOperations = {read=_scw_get_AllowedOperations, write=put_AllowedOperations};
};

__interface  INTERFACE_UUID("{2ACA929A-5E28-4EA6-829E-29134E665D6D}") DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetTarget(_di_DragDrop_Core_ICoreDropOperationTarget target) = 0 ;
};

__interface  INTERFACE_UUID("{A4C3B1C1-B8AD-58CB-ACC0-8EF37EAE4ED4}") TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{79E5B8A1-F24A-5D72-9E29-0503937617EB}") TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs  : public TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_DragDrop_Core_ICoreDragDropManager sender, _di_DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{7D56D344-8464-4FAF-AA49-37EA6E2D7BD1}") DragDrop_Core_ICoreDragDropManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_TargetRequested(_di_TypedEventHandler_2__DragDrop_Core_ICoreDragDropManager__DragDrop_Core_ICoreDropOperationTargetRequestedEventArgs value, Winapi::Commontypes::EventRegistrationToken &__add_TargetRequested_result) = 0 ;
	virtual HRESULT __safecall remove_TargetRequested(Winapi::Commontypes::EventRegistrationToken value) = 0 ;
	virtual HRESULT __safecall get_AreConcurrentOperationsEnabled(bool &__get_AreConcurrentOperationsEnabled_result) = 0 ;
	virtual HRESULT __safecall put_AreConcurrentOperationsEnabled(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AreConcurrentOperationsEnabled() { bool __r; HRESULT __hr = get_AreConcurrentOperationsEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AreConcurrentOperationsEnabled = {read=_scw_get_AreConcurrentOperationsEnabled, write=put_AreConcurrentOperationsEnabled};
};

__interface  INTERFACE_UUID("{9542FDCA-DA12-4C1C-8D06-041DB29733C3}") DragDrop_Core_ICoreDragDropManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForCurrentView(_di_DragDrop_Core_ICoreDragDropManager &__GetForCurrentView_result) = 0 ;
};

__interface  INTERFACE_UUID("{72FA8A80-342F-4D90-9551-2AE04E37680C}") IShareUIOptions  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Theme(Winapi::Commontypes::ShareUITheme &__get_Theme_result) = 0 ;
	virtual HRESULT __safecall put_Theme(Winapi::Commontypes::ShareUITheme value) = 0 ;
	virtual HRESULT __safecall get_SelectionRect(Winapi::Foundation::_di_IReference_1__Rect &__get_SelectionRect_result) = 0 ;
	virtual HRESULT __safecall put_SelectionRect(Winapi::Foundation::_di_IReference_1__Rect value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::_di_IReference_1__Rect _scw_get_SelectionRect() { Winapi::Foundation::_di_IReference_1__Rect __r; HRESULT __hr = get_SelectionRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::_di_IReference_1__Rect SelectionRect = {read=_scw_get_SelectionRect, write=put_SelectionRect};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ShareUITheme _scw_get_Theme() { Winapi::Commontypes::ShareUITheme __r; HRESULT __hr = get_Theme(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ShareUITheme Theme = {read=_scw_get_Theme, write=put_Theme};
};

__interface  INTERFACE_UUID("{6DC4B89F-0386-4263-87C1-ED7DCE30890E}") IDataRequestDeferral  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Complete() = 0 ;
};

__interface  INTERFACE_UUID("{4341AE3B-FC12-4E53-8C02-AC714C415A27}") IDataRequest  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IDataPackage &__get_Data_result) = 0 ;
	virtual HRESULT __safecall put_Data(Winapi::Commontypes::_di_IDataPackage value) = 0 ;
	virtual HRESULT __safecall get_Deadline(Winapi::Commontypes::DateTime &__get_Deadline_result) = 0 ;
	virtual HRESULT __safecall FailWithDisplayText(HSTRING value) = 0 ;
	virtual HRESULT __safecall GetDeferral(_di_IDataRequestDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDataPackage _scw_get_Data() { Winapi::Commontypes::_di_IDataPackage __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDataPackage Data = {read=_scw_get_Data, write=put_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Deadline() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Deadline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Deadline = {read=_scw_get_Deadline};
};

__interface  INTERFACE_UUID("{CB8BA807-6AC5-43C9-8AC5-9BA232163182}") IDataRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Request(_di_IDataRequest &__get_Request_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDataRequest _scw_get_Request() { _di_IDataRequest __r; HRESULT __hr = get_Request(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDataRequest Request = {read=_scw_get_Request};
};

__interface  INTERFACE_UUID("{886F5642-E9F9-573B-9213-5840B5062B40}") IIterator_1__IShareProvider_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D7A2A7A2-254A-55DA-AE8F-EDF525A5036A}") IIterator_1__IShareProvider  : public IIterator_1__IShareProvider_Base 
{
	virtual HRESULT __safecall get_Current(_di_IShareProvider &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIShareProvider items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IShareProvider _scw_get_Current() { _di_IShareProvider __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IShareProvider Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{0903B218-5CAD-53E6-9A21-6F4B31C4A409}") IIterable_1__IShareProvider_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3C8AA09E-5CC9-5F78-AE2E-04FB0E8C6C48}") IIterable_1__IShareProvider  : public IIterable_1__IShareProvider_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IShareProvider &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{82017F36-CFE0-5FE3-8AB0-6F0055957FB4}") IVectorView_1__IShareProvider  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IShareProvider &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IShareProvider value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIShareProvider items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{2F775C24-EE1E-509C-A4D0-CCC66B046507}") IVector_1__IShareProvider  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IShareProvider &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IShareProvider &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IShareProvider value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IShareProvider value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IShareProvider value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IShareProvider value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIShareProvider items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIShareProvider items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{F888F356-A3F8-4FCE-85E4-8826E63BE799}") IShareProvidersRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Providers(_di_IVector_1__IShareProvider &__get_Providers_result) = 0 ;
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IDataPackageView &__get_Data_result) = 0 ;
	virtual HRESULT __safecall GetDeferral(Winapi::Commontypes::_di_IDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDataPackageView _scw_get_Data() { Winapi::Commontypes::_di_IDataPackageView __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDataPackageView Data = {read=_scw_get_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__IShareProvider _scw_get_Providers() { _di_IVector_1__IShareProvider __r; HRESULT __hr = get_Providers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__IShareProvider Providers = {read=_scw_get_Providers};
};

__interface  INTERFACE_UUID("{CA6FB8AC-2987-4EE3-9C54-D8AFBCB86C1D}") ITargetApplicationChosenEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ApplicationName(HSTRING &__get_ApplicationName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ApplicationName() { HSTRING __r; HRESULT __hr = get_ApplicationName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ApplicationName = {read=_scw_get_ApplicationName};
};

__interface  INTERFACE_UUID("{EC6F9CC8-46D0-5E0E-B4D2-7D7773AE37A0}") TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{041062FC-4655-55C7-A13F-1153F9CA6E51}") TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs  : public TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDataTransferManager sender, _di_IDataRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{C4AC1BA2-7851-5A44-BC8D-3D7C713F1F41}") TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{A3639038-7CA2-5BF9-9657-DDBB0B7C6142}") TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs  : public TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDataTransferManager sender, _di_ITargetApplicationChosenEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{A5CAEE9B-8708-49D1-8D36-67D25A8DA00C}") IDataTransferManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_DataRequested(_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_DataRequested_result) = 0 ;
	virtual HRESULT __safecall remove_DataRequested(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	virtual HRESULT __safecall add_TargetApplicationChosen(_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_TargetApplicationChosen_result) = 0 ;
	virtual HRESULT __safecall remove_TargetApplicationChosen(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
};

__interface  INTERFACE_UUID("{147E2860-7397-582F-80DB-B8685383A937}") TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{AD4E35F1-51EC-5CC1-854F-87BDBB80C810}") TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs  : public TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDataTransferManager sender, _di_IShareProvidersRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{30AE7D71-8BA8-4C02-8E3F-DDB23B388715}") IDataTransferManager2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ShareProvidersRequested(_di_TypedEventHandler_2__IDataTransferManager__IShareProvidersRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ShareProvidersRequested_result) = 0 ;
	virtual HRESULT __safecall remove_ShareProvidersRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{A9DA01AA-E00E-4CFE-AA44-2DD932DCA3D8}") IDataTransferManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ShowShareUI() = 0 ;
	virtual HRESULT __safecall GetForCurrentView(_di_IDataTransferManager &__GetForCurrentView_result) = 0 ;
};

__interface  INTERFACE_UUID("{C54EC2EC-9F97-4D63-9868-395E271AD8F5}") IDataTransferManagerStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IsSupported(bool &__IsSupported_result) = 0 ;
};

__interface  INTERFACE_UUID("{05845473-6C82-4F5C-AC23-62E458361FAC}") IDataTransferManagerStatics3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ShowShareUI(_di_IShareUIOptions options) = 0 ;
};

__interface  INTERFACE_UUID("{A93A3B99-E946-57CE-AAD9-C23D138C353E}") AsyncOperationCompletedHandler_1__IDataPackage_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{926269A5-BCC6-5C70-90E0-79EAF8ECBABC}") AsyncOperationCompletedHandler_1__IDataPackage  : public AsyncOperationCompletedHandler_1__IDataPackage_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IDataPackage asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{A16F2D07-EAD3-53E4-9490-75BDBAEB7A5B}") IAsyncOperation_1__IDataPackage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F5B89375-4322-58CD-9F18-DBCF55147BF3}") IAsyncOperation_1__IDataPackage  : public IAsyncOperation_1__IDataPackage_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IDataPackage handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IDataPackage &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IDataPackage &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IDataPackage _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IDataPackage __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IDataPackage Completed = {read=_scw_get_Completed, write=put_Completed};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStandardDataFormats : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_IStandardDataFormatsStatics,_di_IStandardDataFormatsStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_IStandardDataFormatsStatics,_di_IStandardDataFormatsStatics2> inherited;
	
public:
	static HSTRING __fastcall get_Text();
	static HSTRING __fastcall get_Uri();
	static HSTRING __fastcall get_Html();
	static HSTRING __fastcall get_Rtf();
	static HSTRING __fastcall get_Bitmap();
	static HSTRING __fastcall get_StorageItems();
#ifndef _WIN64
	/* static */ __property HSTRING Bitmap = {read=get_Bitmap, nodefault};
	/* static */ __property HSTRING Html = {read=get_Html, nodefault};
	/* static */ __property HSTRING Rtf = {read=get_Rtf, nodefault};
	/* static */ __property HSTRING StorageItems = {read=get_StorageItems, nodefault};
	/* static */ __property HSTRING Text = {read=get_Text, nodefault};
	/* static */ __property HSTRING Uri = {read=get_Uri, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING Bitmap = {read=get_Bitmap};
	/* static */ __property HSTRING Html = {read=get_Html};
	/* static */ __property HSTRING Rtf = {read=get_Rtf};
	/* static */ __property HSTRING StorageItems = {read=get_StorageItems};
	/* static */ __property HSTRING Text = {read=get_Text};
	/* static */ __property HSTRING Uri = {read=get_Uri};
#endif /* _WIN64 */
	static HSTRING __fastcall get_WebLink();
	static HSTRING __fastcall get_ApplicationLink();
#ifndef _WIN64
	/* static */ __property HSTRING ApplicationLink = {read=get_ApplicationLink, nodefault};
	/* static */ __property HSTRING WebLink = {read=get_WebLink, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING ApplicationLink = {read=get_ApplicationLink};
	/* static */ __property HSTRING WebLink = {read=get_WebLink};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TStandardDataFormats() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_IStandardDataFormatsStatics,_di_IStandardDataFormatsStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStandardDataFormats() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataPackage : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDataPackage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDataPackage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDataPackage() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IDataPackage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDataPackage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THtmlFormatHelper : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IHtmlFormatHelperStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IHtmlFormatHelperStatics> inherited;
	
public:
	static HSTRING __fastcall GetStaticFragment(HSTRING htmlFormat);
	static HSTRING __fastcall CreateHtmlFormat(HSTRING htmlFragment);
public:
	/* TObject.Create */ inline __fastcall THtmlFormatHelper() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IHtmlFormatHelperStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THtmlFormatHelper() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TClipboard : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IClipboardStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IClipboardStatics> inherited;
	
public:
	static Winapi::Commontypes::_di_IDataPackageView __fastcall GetContent();
	static void __fastcall SetContent(Winapi::Commontypes::_di_IDataPackage content);
	static void __fastcall Flush();
	static void __fastcall Clear();
	static Winapi::Commontypes::EventRegistrationToken __fastcall add_ContentChanged(Winapi::Graphicsrt::_di_EventHandler_1__IInspectable changeHandler);
	static void __fastcall remove_ContentChanged(const Winapi::Commontypes::EventRegistrationToken &token);
public:
	/* TObject.Create */ inline __fastcall TClipboard() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IClipboardStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TClipboard() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDragDrop_Core_CoreDragDropManager : public System::Win::Winrt::TWinRTGenericImportS__1<_di_DragDrop_Core_ICoreDragDropManagerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_DragDrop_Core_ICoreDragDropManagerStatics> inherited;
	
public:
	static _di_DragDrop_Core_ICoreDragDropManager __fastcall GetForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TDragDrop_Core_CoreDragDropManager() : System::Win::Winrt::TWinRTGenericImportS__1<_di_DragDrop_Core_ICoreDragDropManagerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDragDrop_Core_CoreDragDropManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDragDrop_Core_CoreDragOperation : public System::Win::Winrt::TWinRTGenericImportI__1<_di_DragDrop_Core_ICoreDragOperation>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_DragDrop_Core_ICoreDragOperation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDragDrop_Core_CoreDragOperation() : System::Win::Winrt::TWinRTGenericImportI__1<_di_DragDrop_Core_ICoreDragOperation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDragDrop_Core_CoreDragOperation() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TShareUIOptions : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IShareUIOptions>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IShareUIOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TShareUIOptions() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IShareUIOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TShareUIOptions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{3A3DCD6C-3EAB-43DC-BCDE-45671CE800C8}") IDataTransferManagerInterop  : public System::IInterface 
{
	virtual HRESULT __safecall GetForWindow(NativeUInt appWindow, const GUID &riid, _di_IDataTransferManager &__GetForWindow_result) = 0 ;
	virtual HRESULT __safecall ShowShareUIForWindow(NativeUInt appWindow) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataTransferManager : public System::Win::Winrt::TWinRTGenericImportS3O__4<_di_IDataTransferManagerStatics,_di_IDataTransferManagerStatics2,_di_IDataTransferManagerStatics3,_di_IDataTransferManagerInterop>
{
	typedef System::Win::Winrt::TWinRTGenericImportS3O__4<_di_IDataTransferManagerStatics,_di_IDataTransferManagerStatics2,_di_IDataTransferManagerStatics3,_di_IDataTransferManagerInterop> inherited;
	
public:
	static bool __fastcall IsSupported();
	static void __fastcall ShowShareUI(_di_IShareUIOptions options)/* overload */;
	static void __fastcall ShowShareUI()/* overload */;
	static _di_IDataTransferManager __fastcall GetForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TDataTransferManager() : System::Win::Winrt::TWinRTGenericImportS3O__4<_di_IDataTransferManagerStatics,_di_IDataTransferManagerStatics2,_di_IDataTransferManagerStatics3,_di_IDataTransferManagerInterop>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDataTransferManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Datatransfer */
}	/* namespace Applicationmodel */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Applicationmodel_DatatransferHPP
