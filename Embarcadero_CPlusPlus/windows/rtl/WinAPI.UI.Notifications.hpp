// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.Notifications.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_NotificationsHPP
#define Winapi_Ui_NotificationsHPP

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
#include <Winapi.SystemRT.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Notifications
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ITileNotification;
typedef System::DelphiInterface<ITileNotification> _di_ITileNotification;
__interface DELPHIINTERFACE IBadgeNotification;
typedef System::DelphiInterface<IBadgeNotification> _di_IBadgeNotification;
__interface DELPHIINTERFACE IToastActivatedEventArgs;
typedef System::DelphiInterface<IToastActivatedEventArgs> _di_IToastActivatedEventArgs;
__interface DELPHIINTERFACE IScheduledToastNotification;
typedef System::DelphiInterface<IScheduledToastNotification> _di_IScheduledToastNotification;
__interface DELPHIINTERFACE IIterator_1__IScheduledToastNotification_Base;
typedef System::DelphiInterface<IIterator_1__IScheduledToastNotification_Base> _di_IIterator_1__IScheduledToastNotification_Base;
__interface DELPHIINTERFACE IIterator_1__IScheduledToastNotification;
typedef System::DelphiInterface<IIterator_1__IScheduledToastNotification> _di_IIterator_1__IScheduledToastNotification;
__interface DELPHIINTERFACE IIterable_1__IScheduledToastNotification_Base;
typedef System::DelphiInterface<IIterable_1__IScheduledToastNotification_Base> _di_IIterable_1__IScheduledToastNotification_Base;
__interface DELPHIINTERFACE IIterable_1__IScheduledToastNotification;
typedef System::DelphiInterface<IIterable_1__IScheduledToastNotification> _di_IIterable_1__IScheduledToastNotification;
__interface DELPHIINTERFACE IVectorView_1__IScheduledToastNotification;
typedef System::DelphiInterface<IVectorView_1__IScheduledToastNotification> _di_IVectorView_1__IScheduledToastNotification;
__interface DELPHIINTERFACE IToastNotifier;
typedef System::DelphiInterface<IToastNotifier> _di_IToastNotifier;
__interface DELPHIINTERFACE IToastNotificationManagerStatics;
typedef System::DelphiInterface<IToastNotificationManagerStatics> _di_IToastNotificationManagerStatics;
__interface DELPHIINTERFACE INotificationData;
typedef System::DelphiInterface<INotificationData> _di_INotificationData;
__interface DELPHIINTERFACE IToastNotifier2;
typedef System::DelphiInterface<IToastNotifier2> _di_IToastNotifier2;
__interface DELPHIINTERFACE IToastCollection;
typedef System::DelphiInterface<IToastCollection> _di_IToastCollection;
__interface DELPHIINTERFACE IIterator_1__IToastCollection_Base;
typedef System::DelphiInterface<IIterator_1__IToastCollection_Base> _di_IIterator_1__IToastCollection_Base;
__interface DELPHIINTERFACE IIterator_1__IToastCollection;
typedef System::DelphiInterface<IIterator_1__IToastCollection> _di_IIterator_1__IToastCollection;
__interface DELPHIINTERFACE IIterable_1__IToastCollection_Base;
typedef System::DelphiInterface<IIterable_1__IToastCollection_Base> _di_IIterable_1__IToastCollection_Base;
__interface DELPHIINTERFACE IIterable_1__IToastCollection;
typedef System::DelphiInterface<IIterable_1__IToastCollection> _di_IIterable_1__IToastCollection;
__interface DELPHIINTERFACE IVectorView_1__IToastCollection;
typedef System::DelphiInterface<IVectorView_1__IToastCollection> _di_IVectorView_1__IToastCollection;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IToastCollection_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IToastCollection_Base> _di_IAsyncOperation_1__IVectorView_1__IToastCollection_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IToastCollection;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IToastCollection> _di_IAsyncOperation_1__IVectorView_1__IToastCollection;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastCollection_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastCollection_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IToastCollection_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastCollection;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastCollection> _di_AsyncOperationCompletedHandler_1__IToastCollection;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastCollection_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IToastCollection_Base> _di_IAsyncOperation_1__IToastCollection_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastCollection;
typedef System::DelphiInterface<IAsyncOperation_1__IToastCollection> _di_IAsyncOperation_1__IToastCollection;
__interface DELPHIINTERFACE IToastCollectionManager;
typedef System::DelphiInterface<IToastCollectionManager> _di_IToastCollectionManager;
__interface DELPHIINTERFACE IToastNotificationFactory;
typedef System::DelphiInterface<IToastNotificationFactory> _di_IToastNotificationFactory;
__interface DELPHIINTERFACE IToastNotification2;
typedef System::DelphiInterface<IToastNotification2> _di_IToastNotification2;
__interface DELPHIINTERFACE IToastNotification3;
typedef System::DelphiInterface<IToastNotification3> _di_IToastNotification3;
__interface DELPHIINTERFACE IToastNotification4;
typedef System::DelphiInterface<IToastNotification4> _di_IToastNotification4;
__interface DELPHIINTERFACE IToastCollectionFactory;
typedef System::DelphiInterface<IToastCollectionFactory> _di_IToastCollectionFactory;
__interface DELPHIINTERFACE IToastNotificationHistory;
typedef System::DelphiInterface<IToastNotificationHistory> _di_IToastNotificationHistory;
__interface DELPHIINTERFACE IToastNotificationManagerStatics2;
typedef System::DelphiInterface<IToastNotificationManagerStatics2> _di_IToastNotificationManagerStatics2;
__interface DELPHIINTERFACE IToastNotificationManagerForUser;
typedef System::DelphiInterface<IToastNotificationManagerForUser> _di_IToastNotificationManagerForUser;
__interface DELPHIINTERFACE IToastNotificationManagerStatics4;
typedef System::DelphiInterface<IToastNotificationManagerStatics4> _di_IToastNotificationManagerStatics4;
__interface DELPHIINTERFACE IToastNotificationManagerStatics5;
typedef System::DelphiInterface<IToastNotificationManagerStatics5> _di_IToastNotificationManagerStatics5;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastNotifier_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastNotifier_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IToastNotifier_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastNotifier;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastNotifier> _di_AsyncOperationCompletedHandler_1__IToastNotifier;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastNotifier_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IToastNotifier_Base> _di_IAsyncOperation_1__IToastNotifier_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastNotifier;
typedef System::DelphiInterface<IAsyncOperation_1__IToastNotifier> _di_IAsyncOperation_1__IToastNotifier;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastNotificationHistory_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastNotificationHistory_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IToastNotificationHistory;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IToastNotificationHistory> _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastNotificationHistory_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IToastNotificationHistory_Base> _di_IAsyncOperation_1__IToastNotificationHistory_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IToastNotificationHistory;
typedef System::DelphiInterface<IAsyncOperation_1__IToastNotificationHistory> _di_IAsyncOperation_1__IToastNotificationHistory;
__interface DELPHIINTERFACE IIterator_1__IToastNotification_Base;
typedef System::DelphiInterface<IIterator_1__IToastNotification_Base> _di_IIterator_1__IToastNotification_Base;
__interface DELPHIINTERFACE IIterator_1__IToastNotification;
typedef System::DelphiInterface<IIterator_1__IToastNotification> _di_IIterator_1__IToastNotification;
__interface DELPHIINTERFACE IIterable_1__IToastNotification_Base;
typedef System::DelphiInterface<IIterable_1__IToastNotification_Base> _di_IIterable_1__IToastNotification_Base;
__interface DELPHIINTERFACE IIterable_1__IToastNotification;
typedef System::DelphiInterface<IIterable_1__IToastNotification> _di_IIterable_1__IToastNotification;
__interface DELPHIINTERFACE IVectorView_1__IToastNotification;
typedef System::DelphiInterface<IVectorView_1__IToastNotification> _di_IVectorView_1__IToastNotification;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus> _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus;
__interface DELPHIINTERFACE IAsyncOperation_1__Management_UserNotificationListenerAccessStatus_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Management_UserNotificationListenerAccessStatus_Base> _di_IAsyncOperation_1__Management_UserNotificationListenerAccessStatus_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Management_UserNotificationListenerAccessStatus;
typedef System::DelphiInterface<IAsyncOperation_1__Management_UserNotificationListenerAccessStatus> _di_IAsyncOperation_1__Management_UserNotificationListenerAccessStatus;
class DELPHICLASS TToastNotification;
class DELPHICLASS TToastCollection;
class DELPHICLASS TToastNotificationManager;
//-- type declarations -------------------------------------------------------
typedef _di_ITileNotification *PITileNotification;

typedef _di_IBadgeNotification *PIBadgeNotification;

typedef _di_IToastActivatedEventArgs *PIToastActivatedEventArgs;

typedef _di_IScheduledToastNotification *PIScheduledToastNotification;

typedef _di_IIterator_1__IScheduledToastNotification *PIIterator_1__IScheduledToastNotification;

typedef _di_IIterable_1__IScheduledToastNotification *PIIterable_1__IScheduledToastNotification;

typedef _di_IVectorView_1__IScheduledToastNotification *PIVectorView_1__IScheduledToastNotification;

typedef _di_IToastNotifier *PIToastNotifier;

typedef _di_IToastNotificationManagerStatics *PIToastNotificationManagerStatics;

typedef _di_INotificationData *PINotificationData;

typedef _di_IToastNotifier2 *PIToastNotifier2;

typedef _di_IToastCollection *PIToastCollection;

typedef _di_IIterator_1__IToastCollection *PIIterator_1__IToastCollection;

typedef _di_IIterable_1__IToastCollection *PIIterable_1__IToastCollection;

typedef _di_IVectorView_1__IToastCollection *PIVectorView_1__IToastCollection;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection *PAsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection;

typedef _di_IAsyncOperation_1__IVectorView_1__IToastCollection *PIAsyncOperation_1__IVectorView_1__IToastCollection;

typedef _di_AsyncOperationCompletedHandler_1__IToastCollection *PAsyncOperationCompletedHandler_1__IToastCollection;

typedef _di_IAsyncOperation_1__IToastCollection *PIAsyncOperation_1__IToastCollection;

typedef _di_IToastCollectionManager *PIToastCollectionManager;

typedef _di_IToastNotificationFactory *PIToastNotificationFactory;

typedef _di_IToastNotification2 *PIToastNotification2;

typedef _di_IToastNotification3 *PIToastNotification3;

typedef _di_IToastNotification4 *PIToastNotification4;

typedef _di_IToastCollectionFactory *PIToastCollectionFactory;

typedef _di_IToastNotificationHistory *PIToastNotificationHistory;

typedef _di_IToastNotificationManagerStatics2 *PIToastNotificationManagerStatics2;

typedef _di_IToastNotificationManagerForUser *PIToastNotificationManagerForUser;

typedef _di_IToastNotificationManagerStatics4 *PIToastNotificationManagerStatics4;

typedef _di_IToastNotificationManagerStatics5 *PIToastNotificationManagerStatics5;

typedef _di_AsyncOperationCompletedHandler_1__IToastNotifier *PAsyncOperationCompletedHandler_1__IToastNotifier;

typedef _di_IAsyncOperation_1__IToastNotifier *PIAsyncOperation_1__IToastNotifier;

typedef _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory *PAsyncOperationCompletedHandler_1__IToastNotificationHistory;

typedef _di_IAsyncOperation_1__IToastNotificationHistory *PIAsyncOperation_1__IToastNotificationHistory;

typedef _di_IIterator_1__IToastNotification *PIIterator_1__IToastNotification;

typedef _di_IIterable_1__IToastNotification *PIIterable_1__IToastNotification;

typedef _di_IVectorView_1__IToastNotification *PIVectorView_1__IToastNotification;

typedef _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus *PAsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus;

typedef _di_IAsyncOperation_1__Management_UserNotificationListenerAccessStatus *PIAsyncOperation_1__Management_UserNotificationListenerAccessStatus;

__interface  INTERFACE_UUID("{EBAEC8FA-50EC-4C18-B4D0-3AF02E5540AB}") ITileNotification  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Content(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument &__get_Content_result) = 0 ;
	virtual HRESULT __safecall put_ExpirationTime(Winapi::Commontypes::_di_IReference_1__DateTime value) = 0 ;
	virtual HRESULT __safecall get_ExpirationTime(Winapi::Commontypes::_di_IReference_1__DateTime &__get_ExpirationTime_result) = 0 ;
	virtual HRESULT __safecall put_Tag(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Tag(HSTRING &__get_Tag_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_Xml_Dom_IXmlDocument _scw_get_Content() { Winapi::Commontypes::_di_Xml_Dom_IXmlDocument __r; HRESULT __hr = get_Content(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_Xml_Dom_IXmlDocument Content = {read=_scw_get_Content};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_ExpirationTime() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_ExpirationTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime ExpirationTime = {read=_scw_get_ExpirationTime, write=put_ExpirationTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Tag() { HSTRING __r; HRESULT __hr = get_Tag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Tag = {read=_scw_get_Tag, write=put_Tag};
};

__interface  INTERFACE_UUID("{075CB4CA-D08A-4E2F-9233-7E289C1F7722}") IBadgeNotification  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Content(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument &__get_Content_result) = 0 ;
	virtual HRESULT __safecall put_ExpirationTime(Winapi::Commontypes::_di_IReference_1__DateTime value) = 0 ;
	virtual HRESULT __safecall get_ExpirationTime(Winapi::Commontypes::_di_IReference_1__DateTime &__get_ExpirationTime_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_Xml_Dom_IXmlDocument _scw_get_Content() { Winapi::Commontypes::_di_Xml_Dom_IXmlDocument __r; HRESULT __hr = get_Content(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_Xml_Dom_IXmlDocument Content = {read=_scw_get_Content};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_ExpirationTime() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_ExpirationTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime ExpirationTime = {read=_scw_get_ExpirationTime, write=put_ExpirationTime};
};

__interface  INTERFACE_UUID("{E3BF92F3-C197-436F-8265-0625824F8DAC}") IToastActivatedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Arguments(HSTRING &__get_Arguments_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Arguments() { HSTRING __r; HRESULT __hr = get_Arguments(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Arguments = {read=_scw_get_Arguments};
};

__interface  INTERFACE_UUID("{79F577F8-0DE7-48CD-9740-9B370490C838}") IScheduledToastNotification  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Content(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument &__get_Content_result) = 0 ;
	virtual HRESULT __safecall get_DeliveryTime(Winapi::Commontypes::DateTime &__get_DeliveryTime_result) = 0 ;
	virtual HRESULT __safecall get_SnoozeInterval(Winapi::Commontypes::_di_IReference_1__TimeSpan &__get_SnoozeInterval_result) = 0 ;
	virtual HRESULT __safecall get_MaximumSnoozeCount(unsigned &__get_MaximumSnoozeCount_result) = 0 ;
	virtual HRESULT __safecall put_Id(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_Xml_Dom_IXmlDocument _scw_get_Content() { Winapi::Commontypes::_di_Xml_Dom_IXmlDocument __r; HRESULT __hr = get_Content(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_Xml_Dom_IXmlDocument Content = {read=_scw_get_Content};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_DeliveryTime() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_DeliveryTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime DeliveryTime = {read=_scw_get_DeliveryTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id, write=put_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaximumSnoozeCount() { unsigned __r; HRESULT __hr = get_MaximumSnoozeCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaximumSnoozeCount = {read=_scw_get_MaximumSnoozeCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__TimeSpan _scw_get_SnoozeInterval() { Winapi::Commontypes::_di_IReference_1__TimeSpan __r; HRESULT __hr = get_SnoozeInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__TimeSpan SnoozeInterval = {read=_scw_get_SnoozeInterval};
};

__interface  INTERFACE_UUID("{304238B6-888A-5DD2-96CD-BFCA8927483B}") IIterator_1__IScheduledToastNotification_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6C34AAF7-B3EF-5E61-ADA9-2024702696C6}") IIterator_1__IScheduledToastNotification  : public IIterator_1__IScheduledToastNotification_Base 
{
	virtual HRESULT __safecall get_Current(_di_IScheduledToastNotification &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIScheduledToastNotification items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IScheduledToastNotification _scw_get_Current() { _di_IScheduledToastNotification __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IScheduledToastNotification Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{7A7B2A51-C182-5846-A861-4F9C036F24AD}") IIterable_1__IScheduledToastNotification_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{92B73B0F-5001-54D8-B43C-AAB6D146FBC9}") IIterable_1__IScheduledToastNotification  : public IIterable_1__IScheduledToastNotification_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IScheduledToastNotification &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{762EC9E6-C409-5C27-B61F-C480347C1816}") IVectorView_1__IScheduledToastNotification  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IScheduledToastNotification &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IScheduledToastNotification value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIScheduledToastNotification items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{75927B93-03F3-41EC-91D3-6E5BAC1B38E7}") IToastNotifier  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Show(Winapi::Commontypes::_di_IToastNotification notification) = 0 ;
	virtual HRESULT __safecall Hide(Winapi::Commontypes::_di_IToastNotification notification) = 0 ;
	virtual HRESULT __safecall get_Setting(Winapi::Commontypes::NotificationSetting &__get_Setting_result) = 0 ;
	virtual HRESULT __safecall AddToSchedule(_di_IScheduledToastNotification scheduledToast) = 0 ;
	virtual HRESULT __safecall RemoveFromSchedule(_di_IScheduledToastNotification scheduledToast) = 0 ;
	virtual HRESULT __safecall GetScheduledToastNotifications(_di_IVectorView_1__IScheduledToastNotification &__GetScheduledToastNotifications_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NotificationSetting _scw_get_Setting() { Winapi::Commontypes::NotificationSetting __r; HRESULT __hr = get_Setting(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NotificationSetting Setting = {read=_scw_get_Setting};
};

__interface  INTERFACE_UUID("{50AC103F-D235-4598-BBEF-98FE4D1A3AD4}") IToastNotificationManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateToastNotifier(_di_IToastNotifier &__CreateToastNotifier_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateToastNotifier(HSTRING applicationId, _di_IToastNotifier &__CreateToastNotifier_result) = 0 /* overload */;
	virtual HRESULT __safecall GetTemplateContent(Winapi::Commontypes::ToastTemplateType type, Winapi::Commontypes::_di_Xml_Dom_IXmlDocument &__GetTemplateContent_result) = 0 ;
};

__interface  INTERFACE_UUID("{9FFD2312-9D6A-4AAF-B6AC-FF17F0C1F280}") INotificationData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Values(Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING &__get_Values_result) = 0 ;
	virtual HRESULT __safecall get_SequenceNumber(unsigned &__get_SequenceNumber_result) = 0 ;
	virtual HRESULT __safecall put_SequenceNumber(unsigned value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_SequenceNumber() { unsigned __r; HRESULT __hr = get_SequenceNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned SequenceNumber = {read=_scw_get_SequenceNumber, write=put_SequenceNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING _scw_get_Values() { Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING __r; HRESULT __hr = get_Values(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Systemrt::_di_IMap_2__HSTRING__HSTRING Values = {read=_scw_get_Values};
};

__interface  INTERFACE_UUID("{354389C6-7C01-4BD5-9C20-604340CD2B74}") IToastNotifier2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Update(_di_INotificationData data, HSTRING tag, HSTRING group, Winapi::Commontypes::NotificationUpdateResult &__Update_result) = 0 /* overload */;
	virtual HRESULT __safecall Update(_di_INotificationData data, HSTRING tag, Winapi::Commontypes::NotificationUpdateResult &__Update_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{0A8BC3B0-E0BE-4858-BC2A-89DFE0B32863}") IToastCollection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall put_DisplayName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_LaunchArgs(HSTRING &__get_LaunchArgs_result) = 0 ;
	virtual HRESULT __safecall put_LaunchArgs(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Icon(Winapi::Commontypes::_di_IUriRuntimeClass &__get_Icon_result) = 0 ;
	virtual HRESULT __safecall put_Icon(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName, write=put_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_Icon() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_Icon(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass Icon = {read=_scw_get_Icon, write=put_Icon};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LaunchArgs() { HSTRING __r; HRESULT __hr = get_LaunchArgs(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LaunchArgs = {read=_scw_get_LaunchArgs, write=put_LaunchArgs};
};

__interface  INTERFACE_UUID("{1512ED75-8C74-5520-AC88-134A1403F7AD}") IIterator_1__IToastCollection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C702E18A-98D1-5340-8D67-47A83A883DB4}") IIterator_1__IToastCollection  : public IIterator_1__IToastCollection_Base 
{
	virtual HRESULT __safecall get_Current(_di_IToastCollection &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIToastCollection items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IToastCollection _scw_get_Current() { _di_IToastCollection __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IToastCollection Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{8928D527-DB5D-5A10-AE9B-430FA0906E74}") IIterable_1__IToastCollection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0759B5B7-BD0A-539D-9B28-2F5CD7024463}") IIterable_1__IToastCollection  : public IIterable_1__IToastCollection_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IToastCollection &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{482CB04D-99D2-5D76-92E5-0296B2FA175F}") IVectorView_1__IToastCollection  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IToastCollection &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IToastCollection value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIToastCollection items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{4650E069-3052-530E-BC38-93C411773B77}") AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{7CFB2450-F6AA-5D5E-A493-4E8CB7A6E050}") AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection  : public AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IToastCollection asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{34D4FA14-252B-5CB4-A7DA-971EE5DAEC7C}") IAsyncOperation_1__IVectorView_1__IToastCollection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F69FC18A-04D8-58C0-A4FE-9E26E3CB8B1B}") IAsyncOperation_1__IVectorView_1__IToastCollection  : public IAsyncOperation_1__IVectorView_1__IToastCollection_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IToastCollection &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IToastCollection Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{8D44CA1E-15D7-5BCB-B002-384C87171C74}") AsyncOperationCompletedHandler_1__IToastCollection_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{28FF2BAB-98D8-5909-B9AA-9FDBD29B7DC8}") AsyncOperationCompletedHandler_1__IToastCollection  : public AsyncOperationCompletedHandler_1__IToastCollection_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IToastCollection asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9310EC47-9F0A-5999-80C2-4B31E9F77E8E}") IAsyncOperation_1__IToastCollection_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{962C3201-2826-5C51-BC22-A428E197900F}") IAsyncOperation_1__IToastCollection  : public IAsyncOperation_1__IToastCollection_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IToastCollection handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IToastCollection &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IToastCollection &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IToastCollection _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IToastCollection __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IToastCollection Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{2A1821FE-179D-49BC-B79D-A527920D3665}") IToastCollectionManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SaveToastCollectionAsync(_di_IToastCollection collection, Winapi::Commontypes::_di_IAsyncAction &__SaveToastCollectionAsync_result) = 0 ;
	virtual HRESULT __safecall FindAllToastCollectionsAsync(_di_IAsyncOperation_1__IVectorView_1__IToastCollection &__FindAllToastCollectionsAsync_result) = 0 ;
	virtual HRESULT __safecall GetToastCollectionAsync(HSTRING collectionId, _di_IAsyncOperation_1__IToastCollection &__GetToastCollectionAsync_result) = 0 ;
	virtual HRESULT __safecall RemoveToastCollectionAsync(HSTRING collectionId, Winapi::Commontypes::_di_IAsyncAction &__RemoveToastCollectionAsync_result) = 0 ;
	virtual HRESULT __safecall RemoveAllToastCollectionsAsync(Winapi::Commontypes::_di_IAsyncAction &__RemoveAllToastCollectionsAsync_result) = 0 ;
	virtual HRESULT __safecall get_User(Winapi::Commontypes::_di_IUser &__get_User_result) = 0 ;
	virtual HRESULT __safecall get_AppId(HSTRING &__get_AppId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AppId() { HSTRING __r; HRESULT __hr = get_AppId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AppId = {read=_scw_get_AppId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUser _scw_get_User() { Winapi::Commontypes::_di_IUser __r; HRESULT __hr = get_User(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUser User = {read=_scw_get_User};
};

__interface  INTERFACE_UUID("{04124B20-82C6-4229-B109-FD9ED4662B53}") IToastNotificationFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateToastNotification(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument content, Winapi::Commontypes::_di_IToastNotification &__CreateToastNotification_result) = 0 ;
};

__interface  INTERFACE_UUID("{9DFB9FD1-143A-490E-90BF-B9FBA7132DE7}") IToastNotification2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Tag(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Tag(HSTRING &__get_Tag_result) = 0 ;
	virtual HRESULT __safecall put_Group(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Group(HSTRING &__get_Group_result) = 0 ;
	virtual HRESULT __safecall put_SuppressPopup(bool value) = 0 ;
	virtual HRESULT __safecall get_SuppressPopup(bool &__get_SuppressPopup_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Group() { HSTRING __r; HRESULT __hr = get_Group(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Group = {read=_scw_get_Group, write=put_Group};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SuppressPopup() { bool __r; HRESULT __hr = get_SuppressPopup(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SuppressPopup = {read=_scw_get_SuppressPopup, write=put_SuppressPopup};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Tag() { HSTRING __r; HRESULT __hr = get_Tag(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Tag = {read=_scw_get_Tag, write=put_Tag};
};

__interface  INTERFACE_UUID("{31E8AED8-8141-4F99-BC0A-C4ED21297D77}") IToastNotification3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NotificationMirroring(Winapi::Commontypes::NotificationMirroring &__get_NotificationMirroring_result) = 0 ;
	virtual HRESULT __safecall put_NotificationMirroring(Winapi::Commontypes::NotificationMirroring value) = 0 ;
	virtual HRESULT __safecall get_RemoteId(HSTRING &__get_RemoteId_result) = 0 ;
	virtual HRESULT __safecall put_RemoteId(HSTRING value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NotificationMirroring _scw_get_NotificationMirroring() { Winapi::Commontypes::NotificationMirroring __r; HRESULT __hr = get_NotificationMirroring(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NotificationMirroring NotificationMirroring = {read=_scw_get_NotificationMirroring, write=put_NotificationMirroring};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RemoteId() { HSTRING __r; HRESULT __hr = get_RemoteId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RemoteId = {read=_scw_get_RemoteId, write=put_RemoteId};
};

__interface  INTERFACE_UUID("{15154935-28EA-4727-88E9-C58680E2D118}") IToastNotification4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Data(_di_INotificationData &__get_Data_result) = 0 ;
	virtual HRESULT __safecall put_Data(_di_INotificationData value) = 0 ;
	virtual HRESULT __safecall get_Priority(Winapi::Commontypes::ToastNotificationPriority &__get_Priority_result) = 0 ;
	virtual HRESULT __safecall put_Priority(Winapi::Commontypes::ToastNotificationPriority value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_INotificationData _scw_get_Data() { _di_INotificationData __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_INotificationData Data = {read=_scw_get_Data, write=put_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ToastNotificationPriority _scw_get_Priority() { Winapi::Commontypes::ToastNotificationPriority __r; HRESULT __hr = get_Priority(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ToastNotificationPriority Priority = {read=_scw_get_Priority, write=put_Priority};
};

__interface  INTERFACE_UUID("{164DD3D7-73C4-44F7-B4FF-FB6D4BF1F4C6}") IToastCollectionFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateInstance(HSTRING collectionId, HSTRING displayName, HSTRING launchArgs, Winapi::Commontypes::_di_IUriRuntimeClass iconUri, _di_IToastCollection &__CreateInstance_result) = 0 ;
};

__interface  INTERFACE_UUID("{5CADDC63-01D3-4C97-986F-0533483FEE14}") IToastNotificationHistory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall RemoveGroup(HSTRING group) = 0 /* overload */;
	virtual HRESULT __safecall RemoveGroup(HSTRING group, HSTRING applicationId) = 0 /* overload */;
	virtual HRESULT __safecall Remove(HSTRING tag, HSTRING group, HSTRING applicationId) = 0 /* overload */;
	virtual HRESULT __safecall Remove(HSTRING tag, HSTRING group) = 0 /* overload */;
	virtual HRESULT __safecall Remove(HSTRING tag) = 0 /* overload */;
	virtual HRESULT __safecall Clear() = 0 /* overload */;
	virtual HRESULT __safecall Clear(HSTRING applicationId) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7AB93C52-0E48-4750-BA9D-1A4113981847}") IToastNotificationManagerStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_History(_di_IToastNotificationHistory &__get_History_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IToastNotificationHistory _scw_get_History() { _di_IToastNotificationHistory __r; HRESULT __hr = get_History(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IToastNotificationHistory History = {read=_scw_get_History};
};

__interface  INTERFACE_UUID("{79AB57F6-43FE-487B-8A7F-99567200AE94}") IToastNotificationManagerForUser  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateToastNotifier(_di_IToastNotifier &__CreateToastNotifier_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateToastNotifier(HSTRING applicationId, _di_IToastNotifier &__CreateToastNotifier_result) = 0 /* overload */;
	virtual HRESULT __safecall get_History(_di_IToastNotificationHistory &__get_History_result) = 0 ;
	virtual HRESULT __safecall get_User(Winapi::Commontypes::_di_IUser &__get_User_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IToastNotificationHistory _scw_get_History() { _di_IToastNotificationHistory __r; HRESULT __hr = get_History(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IToastNotificationHistory History = {read=_scw_get_History};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUser _scw_get_User() { Winapi::Commontypes::_di_IUser __r; HRESULT __hr = get_User(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUser User = {read=_scw_get_User};
};

__interface  INTERFACE_UUID("{8F993FD3-E516-45FB-8130-398E93FA52C3}") IToastNotificationManagerStatics4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForUser(Winapi::Commontypes::_di_IUser user, _di_IToastNotificationManagerForUser &__GetForUser_result) = 0 ;
	virtual HRESULT __safecall ConfigureNotificationMirroring(Winapi::Commontypes::NotificationMirroring value) = 0 ;
};

__interface  INTERFACE_UUID("{D6F5F569-D40D-407C-8989-88CAB42CFD14}") IToastNotificationManagerStatics5  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefault(_di_IToastNotificationManagerForUser &__GetDefault_result) = 0 ;
};

__interface  INTERFACE_UUID("{FDE26ED7-BC37-5A7C-B3DA-3E41AC97BBA4}") AsyncOperationCompletedHandler_1__IToastNotifier_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{CB57B7F4-9EAD-55DD-A970-3734A2B0422F}") AsyncOperationCompletedHandler_1__IToastNotifier  : public AsyncOperationCompletedHandler_1__IToastNotifier_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IToastNotifier asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2DDDC10E-38E6-5655-ADF3-820E8FB14DCC}") IAsyncOperation_1__IToastNotifier_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1A0505B2-4770-56F9-8A2D-4BA4CA07FF35}") IAsyncOperation_1__IToastNotifier  : public IAsyncOperation_1__IToastNotifier_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IToastNotifier handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IToastNotifier &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IToastNotifier &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IToastNotifier _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IToastNotifier __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IToastNotifier Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C661D5DA-6762-5D93-9138-E7DACD571056}") AsyncOperationCompletedHandler_1__IToastNotificationHistory_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{18ED286A-90EC-5739-9D48-7D63CD35BD70}") AsyncOperationCompletedHandler_1__IToastNotificationHistory  : public AsyncOperationCompletedHandler_1__IToastNotificationHistory_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IToastNotificationHistory asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2A22FECB-4B96-551F-B7B9-A7B5BEECAD05}") IAsyncOperation_1__IToastNotificationHistory_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0B2F4B97-3174-516B-B03F-CF8F12151E46}") IAsyncOperation_1__IToastNotificationHistory  : public IAsyncOperation_1__IToastNotificationHistory_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IToastNotificationHistory handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IToastNotificationHistory &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IToastNotificationHistory &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IToastNotificationHistory Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{FE1E726A-3AA9-5D98-B19B-97E3E17EEC7B}") IIterator_1__IToastNotification_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{ABA5D40A-4EF1-5090-8A7E-B2B779BCCBB7}") IIterator_1__IToastNotification  : public IIterator_1__IToastNotification_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IToastNotification &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIToastNotification items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IToastNotification _scw_get_Current() { Winapi::Commontypes::_di_IToastNotification __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IToastNotification Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{52C9428B-D37A-554D-BF55-B8685D5F552D}") IIterable_1__IToastNotification_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DD43185C-C276-593B-B076-B598FCD176DB}") IIterable_1__IToastNotification  : public IIterable_1__IToastNotification_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IToastNotification &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{82CB31B6-357F-581F-A6C9-CBCB308BAEC8}") IVectorView_1__IToastNotification  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IToastNotification &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IToastNotification value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIToastNotification items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{F09E843A-13CB-559B-A9FC-015722C2CD57}") AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus  : public AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Management_UserNotificationListenerAccessStatus asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0FBAD8C7-086F-5BF9-81E2-8D79E7184803}") IAsyncOperation_1__Management_UserNotificationListenerAccessStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__Management_UserNotificationListenerAccessStatus  : public IAsyncOperation_1__Management_UserNotificationListenerAccessStatus_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::Management_UserNotificationListenerAccessStatus &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Management_UserNotificationListenerAccessStatus Completed = {read=_scw_get_Completed, write=put_Completed};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TToastNotification : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastNotificationFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastNotificationFactory> inherited;
	
public:
	static Winapi::Commontypes::_di_IToastNotification __fastcall CreateToastNotification(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument content);
public:
	/* TObject.Create */ inline __fastcall TToastNotification() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastNotificationFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TToastNotification() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TToastCollection : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastCollectionFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastCollectionFactory> inherited;
	
public:
	static _di_IToastCollection __fastcall CreateInstance(HSTRING collectionId, HSTRING displayName, HSTRING launchArgs, Winapi::Commontypes::_di_IUriRuntimeClass iconUri);
public:
	/* TObject.Create */ inline __fastcall TToastCollection() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IToastCollectionFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TToastCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TToastNotificationManager : public System::Win::Winrt::TWinRTGenericImportS4__4<_di_IToastNotificationManagerStatics,_di_IToastNotificationManagerStatics2,_di_IToastNotificationManagerStatics4,_di_IToastNotificationManagerStatics5>
{
	typedef System::Win::Winrt::TWinRTGenericImportS4__4<_di_IToastNotificationManagerStatics,_di_IToastNotificationManagerStatics2,_di_IToastNotificationManagerStatics4,_di_IToastNotificationManagerStatics5> inherited;
	
public:
	static _di_IToastNotificationManagerForUser __fastcall GetDefault();
	static _di_IToastNotifier __fastcall CreateToastNotifier()/* overload */;
	static _di_IToastNotifier __fastcall CreateToastNotifier(HSTRING applicationId)/* overload */;
	static Winapi::Commontypes::_di_Xml_Dom_IXmlDocument __fastcall GetTemplateContent(Winapi::Commontypes::ToastTemplateType type);
	static _di_IToastNotificationManagerForUser __fastcall GetForUser(Winapi::Commontypes::_di_IUser user);
	static void __fastcall ConfigureNotificationMirroring(Winapi::Commontypes::NotificationMirroring value);
	static _di_IToastNotificationHistory __fastcall get_History();
	/* static */ __property _di_IToastNotificationHistory History = {read=get_History};
public:
	/* TObject.Create */ inline __fastcall TToastNotificationManager() : System::Win::Winrt::TWinRTGenericImportS4__4<_di_IToastNotificationManagerStatics,_di_IToastNotificationManagerStatics2,_di_IToastNotificationManagerStatics4,_di_IToastNotificationManagerStatics5>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TToastNotificationManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notifications */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_NotificationsHPP
