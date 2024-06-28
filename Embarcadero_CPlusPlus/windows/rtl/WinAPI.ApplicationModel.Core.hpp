// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ApplicationModel.Core.pas' rev: 34.00 (Windows)

#ifndef Winapi_Applicationmodel_CoreHPP
#define Winapi_Applicationmodel_CoreHPP

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
namespace Applicationmodel
{
namespace Core
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAppListEntry;
typedef System::DelphiInterface<IAppListEntry> _di_IAppListEntry;
__interface DELPHIINTERFACE IAppListEntry2;
typedef System::DelphiInterface<IAppListEntry2> _di_IAppListEntry2;
__interface DELPHIINTERFACE IIterator_1__IAppListEntry_Base;
typedef System::DelphiInterface<IIterator_1__IAppListEntry_Base> _di_IIterator_1__IAppListEntry_Base;
__interface DELPHIINTERFACE IIterator_1__IAppListEntry;
typedef System::DelphiInterface<IIterator_1__IAppListEntry> _di_IIterator_1__IAppListEntry;
__interface DELPHIINTERFACE IIterable_1__IAppListEntry_Base;
typedef System::DelphiInterface<IIterable_1__IAppListEntry_Base> _di_IIterable_1__IAppListEntry_Base;
__interface DELPHIINTERFACE IIterable_1__IAppListEntry;
typedef System::DelphiInterface<IIterable_1__IAppListEntry> _di_IIterable_1__IAppListEntry;
__interface DELPHIINTERFACE IVectorView_1__IAppListEntry;
typedef System::DelphiInterface<IVectorView_1__IAppListEntry> _di_IVectorView_1__IAppListEntry;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IAppListEntry_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IAppListEntry_Base> _di_IAsyncOperation_1__IVectorView_1__IAppListEntry_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IAppListEntry;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IAppListEntry> _di_IAsyncOperation_1__IVectorView_1__IAppListEntry;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__AppRestartFailureReason_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__AppRestartFailureReason_Delegate_Base> _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__AppRestartFailureReason;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__AppRestartFailureReason> _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason;
__interface DELPHIINTERFACE IAsyncOperation_1__AppRestartFailureReason_Base;
typedef System::DelphiInterface<IAsyncOperation_1__AppRestartFailureReason_Base> _di_IAsyncOperation_1__AppRestartFailureReason_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__AppRestartFailureReason;
typedef System::DelphiInterface<IAsyncOperation_1__AppRestartFailureReason> _di_IAsyncOperation_1__AppRestartFailureReason;
__interface DELPHIINTERFACE IIterator_1__ICoreApplicationView_Base;
typedef System::DelphiInterface<IIterator_1__ICoreApplicationView_Base> _di_IIterator_1__ICoreApplicationView_Base;
__interface DELPHIINTERFACE IIterator_1__ICoreApplicationView;
typedef System::DelphiInterface<IIterator_1__ICoreApplicationView> _di_IIterator_1__ICoreApplicationView;
__interface DELPHIINTERFACE IIterable_1__ICoreApplicationView_Base;
typedef System::DelphiInterface<IIterable_1__ICoreApplicationView_Base> _di_IIterable_1__ICoreApplicationView_Base;
__interface DELPHIINTERFACE IIterable_1__ICoreApplicationView;
typedef System::DelphiInterface<IIterable_1__ICoreApplicationView> _di_IIterable_1__ICoreApplicationView;
__interface DELPHIINTERFACE IVectorView_1__ICoreApplicationView;
typedef System::DelphiInterface<IVectorView_1__ICoreApplicationView> _di_IVectorView_1__ICoreApplicationView;
//-- type declarations -------------------------------------------------------
typedef _di_IAppListEntry *PIAppListEntry;

typedef _di_IAppListEntry2 *PIAppListEntry2;

typedef _di_IIterator_1__IAppListEntry *PIIterator_1__IAppListEntry;

typedef _di_IIterable_1__IAppListEntry *PIIterable_1__IAppListEntry;

typedef _di_IVectorView_1__IAppListEntry *PIVectorView_1__IAppListEntry;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry *PAsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry;

typedef _di_IAsyncOperation_1__IVectorView_1__IAppListEntry *PIAsyncOperation_1__IVectorView_1__IAppListEntry;

typedef _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason *PAsyncOperationCompletedHandler_1__AppRestartFailureReason;

typedef _di_IAsyncOperation_1__AppRestartFailureReason *PIAsyncOperation_1__AppRestartFailureReason;

typedef _di_IIterator_1__ICoreApplicationView *PIIterator_1__ICoreApplicationView;

typedef _di_IIterable_1__ICoreApplicationView *PIIterable_1__ICoreApplicationView;

typedef _di_IVectorView_1__ICoreApplicationView *PIVectorView_1__ICoreApplicationView;

__interface  INTERFACE_UUID("{EF00F07F-2108-490A-877A-8A9F17C25FAD}") IAppListEntry  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DisplayInfo(Winapi::Commontypes::_di_IAppDisplayInfo &__get_DisplayInfo_result) = 0 ;
	virtual HRESULT __safecall LaunchAsync(Winapi::Commontypes::_di_IAsyncOperation_1__Boolean &__LaunchAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IAppDisplayInfo _scw_get_DisplayInfo() { Winapi::Commontypes::_di_IAppDisplayInfo __r; HRESULT __hr = get_DisplayInfo(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IAppDisplayInfo DisplayInfo = {read=_scw_get_DisplayInfo};
};

__interface  INTERFACE_UUID("{D0A618AD-BF35-42AC-AC06-86EEEB41D04B}") IAppListEntry2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AppUserModelId(HSTRING &__get_AppUserModelId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AppUserModelId() { HSTRING __r; HRESULT __hr = get_AppUserModelId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AppUserModelId = {read=_scw_get_AppUserModelId};
};

__interface  INTERFACE_UUID("{B93E2028-50BC-599E-B3D9-427B61D26C01}") IIterator_1__IAppListEntry_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1E94D34D-7C77-50D7-B65A-CA24954EBAFA}") IIterator_1__IAppListEntry  : public IIterator_1__IAppListEntry_Base 
{
	virtual HRESULT __safecall get_Current(_di_IAppListEntry &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIAppListEntry items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAppListEntry _scw_get_Current() { _di_IAppListEntry __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAppListEntry Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{86F4D4EF-D8FD-5FB5-807C-72DA8FC9E544}") IIterable_1__IAppListEntry_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3B58FDB7-ED7D-5B1D-8996-ADED30E93DF9}") IIterable_1__IAppListEntry  : public IIterable_1__IAppListEntry_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IAppListEntry &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{1D8ACCFE-BA75-591F-AF1E-2ACDA21D85C1}") IVectorView_1__IAppListEntry  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IAppListEntry &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IAppListEntry value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIAppListEntry items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{51C74372-9452-57CE-9270-762009FBFE4D}") AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4CB461E4-D1B6-5C09-98B4-583C5EE8ACED}") AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry  : public AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IAppListEntry asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{D3BCF8A0-3538-5DAE-98D7-1F2AB88C3F01}") IAsyncOperation_1__IVectorView_1__IAppListEntry_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A320E67B-2293-546B-B9FE-E80AB59BA643}") IAsyncOperation_1__IVectorView_1__IAppListEntry  : public IAsyncOperation_1__IVectorView_1__IAppListEntry_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IAppListEntry &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAppListEntry Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{DCEC478A-9F27-5C5D-AFDB-C91AEE4F1F02}") AsyncOperationCompletedHandler_1__AppRestartFailureReason_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__AppRestartFailureReason  : public AsyncOperationCompletedHandler_1__AppRestartFailureReason_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__AppRestartFailureReason asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0938905D-54C0-572F-8451-4BFD2B52EDDA}") IAsyncOperation_1__AppRestartFailureReason_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__AppRestartFailureReason  : public IAsyncOperation_1__AppRestartFailureReason_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__AppRestartFailureReason handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__AppRestartFailureReason &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::AppRestartFailureReason &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__AppRestartFailureReason Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{4F5F6944-264B-5868-809E-C7AC1AC5EDAD}") IIterator_1__ICoreApplicationView_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A5D1343F-43AF-53F8-9698-10E77D4C9094}") IIterator_1__ICoreApplicationView  : public IIterator_1__ICoreApplicationView_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_ICoreApplicationView &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PICoreApplicationView items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_ICoreApplicationView _scw_get_Current() { Winapi::Commontypes::_di_ICoreApplicationView __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_ICoreApplicationView Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{32BC12D1-2653-5A41-A55E-88A12AF2026A}") IIterable_1__ICoreApplicationView_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E250C2A8-1628-5D13-9822-344A1D9B7765}") IIterable_1__ICoreApplicationView  : public IIterable_1__ICoreApplicationView_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ICoreApplicationView &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9B43BA8B-9015-5462-9982-C81F5183FC31}") IVectorView_1__ICoreApplicationView  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_ICoreApplicationView &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_ICoreApplicationView value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PICoreApplicationView items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Core */
}	/* namespace Applicationmodel */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Applicationmodel_CoreHPP
