// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Sms.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_SmsHPP
#define Winapi_Devices_SmsHPP

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
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.SystemRT.hpp>
#include <Winapi.ServicesRT.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Sms
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__SmsBroadcastType_Base;
typedef System::DelphiInterface<IIterator_1__SmsBroadcastType_Base> _di_IIterator_1__SmsBroadcastType_Base;
__interface DELPHIINTERFACE IIterator_1__SmsBroadcastType;
typedef System::DelphiInterface<IIterator_1__SmsBroadcastType> _di_IIterator_1__SmsBroadcastType;
__interface DELPHIINTERFACE IIterable_1__SmsBroadcastType_Base;
typedef System::DelphiInterface<IIterable_1__SmsBroadcastType_Base> _di_IIterable_1__SmsBroadcastType_Base;
__interface DELPHIINTERFACE IIterable_1__SmsBroadcastType;
typedef System::DelphiInterface<IIterable_1__SmsBroadcastType> _di_IIterable_1__SmsBroadcastType;
__interface DELPHIINTERFACE IVectorView_1__SmsBroadcastType;
typedef System::DelphiInterface<IVectorView_1__SmsBroadcastType> _di_IVectorView_1__SmsBroadcastType;
__interface DELPHIINTERFACE IVector_1__SmsBroadcastType;
typedef System::DelphiInterface<IVector_1__SmsBroadcastType> _di_IVector_1__SmsBroadcastType;
__interface DELPHIINTERFACE ISmsFilterRule;
typedef System::DelphiInterface<ISmsFilterRule> _di_ISmsFilterRule;
__interface DELPHIINTERFACE IIterator_1__ISmsFilterRule_Base;
typedef System::DelphiInterface<IIterator_1__ISmsFilterRule_Base> _di_IIterator_1__ISmsFilterRule_Base;
__interface DELPHIINTERFACE IIterator_1__ISmsFilterRule;
typedef System::DelphiInterface<IIterator_1__ISmsFilterRule> _di_IIterator_1__ISmsFilterRule;
__interface DELPHIINTERFACE IIterable_1__ISmsFilterRule_Base;
typedef System::DelphiInterface<IIterable_1__ISmsFilterRule_Base> _di_IIterable_1__ISmsFilterRule_Base;
__interface DELPHIINTERFACE IIterable_1__ISmsFilterRule;
typedef System::DelphiInterface<IIterable_1__ISmsFilterRule> _di_IIterable_1__ISmsFilterRule;
__interface DELPHIINTERFACE IVectorView_1__ISmsFilterRule;
typedef System::DelphiInterface<IVectorView_1__ISmsFilterRule> _di_IVectorView_1__ISmsFilterRule;
__interface DELPHIINTERFACE IVector_1__ISmsFilterRule;
typedef System::DelphiInterface<IVector_1__ISmsFilterRule> _di_IVector_1__ISmsFilterRule;
__interface DELPHIINTERFACE ISmsFilterRules;
typedef System::DelphiInterface<ISmsFilterRules> _di_ISmsFilterRules;
__interface DELPHIINTERFACE ISmsTextMessage2;
typedef System::DelphiInterface<ISmsTextMessage2> _di_ISmsTextMessage2;
__interface DELPHIINTERFACE ISmsWapMessage;
typedef System::DelphiInterface<ISmsWapMessage> _di_ISmsWapMessage;
__interface DELPHIINTERFACE ISmsAppMessage;
typedef System::DelphiInterface<ISmsAppMessage> _di_ISmsAppMessage;
__interface DELPHIINTERFACE ISmsBroadcastMessage;
typedef System::DelphiInterface<ISmsBroadcastMessage> _di_ISmsBroadcastMessage;
__interface DELPHIINTERFACE ISmsVoicemailMessage;
typedef System::DelphiInterface<ISmsVoicemailMessage> _di_ISmsVoicemailMessage;
__interface DELPHIINTERFACE ISmsStatusMessage;
typedef System::DelphiInterface<ISmsStatusMessage> _di_ISmsStatusMessage;
__interface DELPHIINTERFACE ISmsDevice2Statics;
typedef System::DelphiInterface<ISmsDevice2Statics> _di_ISmsDevice2Statics;
__interface DELPHIINTERFACE ISmsMessageReceivedTriggerDetails;
typedef System::DelphiInterface<ISmsMessageReceivedTriggerDetails> _di_ISmsMessageReceivedTriggerDetails;
__interface DELPHIINTERFACE ISmsFilterRuleFactory;
typedef System::DelphiInterface<ISmsFilterRuleFactory> _di_ISmsFilterRuleFactory;
__interface DELPHIINTERFACE ISmsFilterRulesFactory;
typedef System::DelphiInterface<ISmsFilterRulesFactory> _di_ISmsFilterRulesFactory;
__interface DELPHIINTERFACE TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails_Delegate_Base> _di_TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails;
typedef System::DelphiInterface<TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails> _di_TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails;
__interface DELPHIINTERFACE ISmsMessageRegistration;
typedef System::DelphiInterface<ISmsMessageRegistration> _di_ISmsMessageRegistration;
__interface DELPHIINTERFACE IIterator_1__ISmsMessageRegistration_Base;
typedef System::DelphiInterface<IIterator_1__ISmsMessageRegistration_Base> _di_IIterator_1__ISmsMessageRegistration_Base;
__interface DELPHIINTERFACE IIterator_1__ISmsMessageRegistration;
typedef System::DelphiInterface<IIterator_1__ISmsMessageRegistration> _di_IIterator_1__ISmsMessageRegistration;
__interface DELPHIINTERFACE IIterable_1__ISmsMessageRegistration_Base;
typedef System::DelphiInterface<IIterable_1__ISmsMessageRegistration_Base> _di_IIterable_1__ISmsMessageRegistration_Base;
__interface DELPHIINTERFACE IIterable_1__ISmsMessageRegistration;
typedef System::DelphiInterface<IIterable_1__ISmsMessageRegistration> _di_IIterable_1__ISmsMessageRegistration;
__interface DELPHIINTERFACE IVectorView_1__ISmsMessageRegistration;
typedef System::DelphiInterface<IVectorView_1__ISmsMessageRegistration> _di_IVectorView_1__ISmsMessageRegistration;
__interface DELPHIINTERFACE ISmsMessageRegistrationStatics;
typedef System::DelphiInterface<ISmsMessageRegistrationStatics> _di_ISmsMessageRegistrationStatics;
__interface DELPHIINTERFACE ISmsBinaryMessage;
typedef System::DelphiInterface<ISmsBinaryMessage> _di_ISmsBinaryMessage;
__interface DELPHIINTERFACE IIterator_1__ISmsBinaryMessage_Base;
typedef System::DelphiInterface<IIterator_1__ISmsBinaryMessage_Base> _di_IIterator_1__ISmsBinaryMessage_Base;
__interface DELPHIINTERFACE IIterator_1__ISmsBinaryMessage;
typedef System::DelphiInterface<IIterator_1__ISmsBinaryMessage> _di_IIterator_1__ISmsBinaryMessage;
__interface DELPHIINTERFACE IIterable_1__ISmsBinaryMessage_Base;
typedef System::DelphiInterface<IIterable_1__ISmsBinaryMessage_Base> _di_IIterable_1__ISmsBinaryMessage_Base;
__interface DELPHIINTERFACE IIterable_1__ISmsBinaryMessage;
typedef System::DelphiInterface<IIterable_1__ISmsBinaryMessage> _di_IIterable_1__ISmsBinaryMessage;
__interface DELPHIINTERFACE IVectorView_1__ISmsBinaryMessage;
typedef System::DelphiInterface<IVectorView_1__ISmsBinaryMessage> _di_IVectorView_1__ISmsBinaryMessage;
__interface DELPHIINTERFACE ISmsTextMessage;
typedef System::DelphiInterface<ISmsTextMessage> _di_ISmsTextMessage;
__interface DELPHIINTERFACE ISmsTextMessageStatics;
typedef System::DelphiInterface<ISmsTextMessageStatics> _di_ISmsTextMessageStatics;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ISmsMessage_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ISmsMessage_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ISmsMessage_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ISmsMessage;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ISmsMessage> _di_AsyncOperationCompletedHandler_1__ISmsMessage;
__interface DELPHIINTERFACE IAsyncOperation_1__ISmsMessage_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ISmsMessage_Base> _di_IAsyncOperation_1__ISmsMessage_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ISmsMessage;
typedef System::DelphiInterface<IAsyncOperation_1__ISmsMessage> _di_IAsyncOperation_1__ISmsMessage;
__interface DELPHIINTERFACE IIterator_1__ISmsMessage_Base;
typedef System::DelphiInterface<IIterator_1__ISmsMessage_Base> _di_IIterator_1__ISmsMessage_Base;
__interface DELPHIINTERFACE IIterator_1__ISmsMessage;
typedef System::DelphiInterface<IIterator_1__ISmsMessage> _di_IIterator_1__ISmsMessage;
__interface DELPHIINTERFACE IIterable_1__ISmsMessage_Base;
typedef System::DelphiInterface<IIterable_1__ISmsMessage_Base> _di_IIterable_1__ISmsMessage_Base;
__interface DELPHIINTERFACE IIterable_1__ISmsMessage;
typedef System::DelphiInterface<IIterable_1__ISmsMessage> _di_IIterable_1__ISmsMessage;
__interface DELPHIINTERFACE ISmsDeviceMessageStore;
typedef System::DelphiInterface<ISmsDeviceMessageStore> _di_ISmsDeviceMessageStore;
__interface DELPHIINTERFACE ISmsMessageReceivedEventArgs;
typedef System::DelphiInterface<ISmsMessageReceivedEventArgs> _di_ISmsMessageReceivedEventArgs;
__interface DELPHIINTERFACE SmsDeviceStatusChangedEventHandler;
typedef System::DelphiInterface<SmsDeviceStatusChangedEventHandler> _di_SmsDeviceStatusChangedEventHandler;
__interface DELPHIINTERFACE ISmsDevice;
typedef System::DelphiInterface<ISmsDevice> _di_ISmsDevice;
__interface DELPHIINTERFACE SmsMessageReceivedEventHandler;
typedef System::DelphiInterface<SmsMessageReceivedEventHandler> _di_SmsMessageReceivedEventHandler;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ISmsDevice_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ISmsDevice_Delegate_Base> _di_AsyncOperationCompletedHandler_1__ISmsDevice_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__ISmsDevice;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__ISmsDevice> _di_AsyncOperationCompletedHandler_1__ISmsDevice;
__interface DELPHIINTERFACE IAsyncOperation_1__ISmsDevice_Base;
typedef System::DelphiInterface<IAsyncOperation_1__ISmsDevice_Base> _di_IAsyncOperation_1__ISmsDevice_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__ISmsDevice;
typedef System::DelphiInterface<IAsyncOperation_1__ISmsDevice> _di_IAsyncOperation_1__ISmsDevice;
__interface DELPHIINTERFACE ISmsDeviceStatics;
typedef System::DelphiInterface<ISmsDeviceStatics> _di_ISmsDeviceStatics;
__interface DELPHIINTERFACE ISmsDeviceStatics2;
typedef System::DelphiInterface<ISmsDeviceStatics2> _di_ISmsDeviceStatics2;
__interface DELPHIINTERFACE ISmsReceivedEventDetails;
typedef System::DelphiInterface<ISmsReceivedEventDetails> _di_ISmsReceivedEventDetails;
__interface DELPHIINTERFACE ISmsReceivedEventDetails2;
typedef System::DelphiInterface<ISmsReceivedEventDetails2> _di_ISmsReceivedEventDetails2;
class DELPHICLASS TSmsTextMessage2;
class DELPHICLASS TSmsAppMessage;
class DELPHICLASS TSmsDevice2;
class DELPHICLASS TSmsFilterRule;
class DELPHICLASS TSmsFilterRules;
class DELPHICLASS TSmsMessageRegistration;
class DELPHICLASS TSmsBinaryMessage;
class DELPHICLASS TSmsTextMessage;
class DELPHICLASS TSmsDevice;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__SmsBroadcastType *PIIterator_1__SmsBroadcastType;

typedef _di_IIterable_1__SmsBroadcastType *PIIterable_1__SmsBroadcastType;

typedef _di_IVectorView_1__SmsBroadcastType *PIVectorView_1__SmsBroadcastType;

typedef _di_IVector_1__SmsBroadcastType *PIVector_1__SmsBroadcastType;

typedef _di_ISmsFilterRule *PISmsFilterRule;

typedef _di_IIterator_1__ISmsFilterRule *PIIterator_1__ISmsFilterRule;

typedef _di_IIterable_1__ISmsFilterRule *PIIterable_1__ISmsFilterRule;

typedef _di_IVectorView_1__ISmsFilterRule *PIVectorView_1__ISmsFilterRule;

typedef _di_IVector_1__ISmsFilterRule *PIVector_1__ISmsFilterRule;

typedef _di_ISmsFilterRules *PISmsFilterRules;

typedef _di_ISmsTextMessage2 *PISmsTextMessage2;

typedef _di_ISmsWapMessage *PISmsWapMessage;

typedef _di_ISmsAppMessage *PISmsAppMessage;

typedef _di_ISmsBroadcastMessage *PISmsBroadcastMessage;

typedef _di_ISmsVoicemailMessage *PISmsVoicemailMessage;

typedef _di_ISmsStatusMessage *PISmsStatusMessage;

typedef _di_ISmsDevice2Statics *PISmsDevice2Statics;

typedef _di_ISmsMessageReceivedTriggerDetails *PISmsMessageReceivedTriggerDetails;

typedef _di_ISmsFilterRuleFactory *PISmsFilterRuleFactory;

typedef _di_ISmsFilterRulesFactory *PISmsFilterRulesFactory;

typedef _di_TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails *PTypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails;

typedef _di_ISmsMessageRegistration *PISmsMessageRegistration;

typedef _di_IIterator_1__ISmsMessageRegistration *PIIterator_1__ISmsMessageRegistration;

typedef _di_IIterable_1__ISmsMessageRegistration *PIIterable_1__ISmsMessageRegistration;

typedef _di_IVectorView_1__ISmsMessageRegistration *PIVectorView_1__ISmsMessageRegistration;

typedef _di_ISmsMessageRegistrationStatics *PISmsMessageRegistrationStatics;

typedef _di_ISmsBinaryMessage *PISmsBinaryMessage;

typedef _di_IIterator_1__ISmsBinaryMessage *PIIterator_1__ISmsBinaryMessage;

typedef _di_IIterable_1__ISmsBinaryMessage *PIIterable_1__ISmsBinaryMessage;

typedef _di_IVectorView_1__ISmsBinaryMessage *PIVectorView_1__ISmsBinaryMessage;

typedef _di_ISmsTextMessage *PISmsTextMessage;

typedef _di_ISmsTextMessageStatics *PISmsTextMessageStatics;

typedef _di_AsyncOperationCompletedHandler_1__ISmsMessage *PAsyncOperationCompletedHandler_1__ISmsMessage;

typedef _di_IAsyncOperation_1__ISmsMessage *PIAsyncOperation_1__ISmsMessage;

typedef _di_IIterator_1__ISmsMessage *PIIterator_1__ISmsMessage;

typedef _di_IIterable_1__ISmsMessage *PIIterable_1__ISmsMessage;

typedef _di_ISmsDeviceMessageStore *PISmsDeviceMessageStore;

typedef _di_ISmsMessageReceivedEventArgs *PISmsMessageReceivedEventArgs;

typedef _di_SmsDeviceStatusChangedEventHandler *PSmsDeviceStatusChangedEventHandler;

typedef _di_ISmsDevice *PISmsDevice;

typedef _di_SmsMessageReceivedEventHandler *PSmsMessageReceivedEventHandler;

typedef _di_AsyncOperationCompletedHandler_1__ISmsDevice *PAsyncOperationCompletedHandler_1__ISmsDevice;

typedef _di_IAsyncOperation_1__ISmsDevice *PIAsyncOperation_1__ISmsDevice;

typedef _di_ISmsDeviceStatics *PISmsDeviceStatics;

typedef _di_ISmsDeviceStatics2 *PISmsDeviceStatics2;

typedef _di_ISmsReceivedEventDetails *PISmsReceivedEventDetails;

typedef _di_ISmsReceivedEventDetails2 *PISmsReceivedEventDetails2;

__interface  INTERFACE_UUID("{6448DDEA-C1CD-5143-A422-5FE4F008CC92}") IIterator_1__SmsBroadcastType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__SmsBroadcastType  : public IIterator_1__SmsBroadcastType_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::SmsBroadcastType &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PSmsBroadcastType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsBroadcastType _scw_get_Current() { Winapi::Commontypes::SmsBroadcastType __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsBroadcastType Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{12276B75-173E-514B-98F0-8A7927A9206C}") IIterable_1__SmsBroadcastType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__SmsBroadcastType  : public IIterable_1__SmsBroadcastType_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__SmsBroadcastType &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__SmsBroadcastType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::SmsBroadcastType &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::SmsBroadcastType value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PSmsBroadcastType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A4739064-B54E-55D4-8012-317E2B6A807B}") IVector_1__SmsBroadcastType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::SmsBroadcastType &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__SmsBroadcastType &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::SmsBroadcastType value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::SmsBroadcastType value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::SmsBroadcastType value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::SmsBroadcastType value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PSmsBroadcastType items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PSmsBroadcastType items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{40E32FAE-B049-4FBC-AFE9-E2A610EFF55C}") ISmsFilterRule  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MessageType(Winapi::Commontypes::SmsMessageType &__get_MessageType_result) = 0 ;
	virtual HRESULT __safecall get_ImsiPrefixes(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_ImsiPrefixes_result) = 0 ;
	virtual HRESULT __safecall get_DeviceIds(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_DeviceIds_result) = 0 ;
	virtual HRESULT __safecall get_SenderNumbers(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_SenderNumbers_result) = 0 ;
	virtual HRESULT __safecall get_TextMessagePrefixes(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_TextMessagePrefixes_result) = 0 ;
	virtual HRESULT __safecall get_PortNumbers(Winapi::Applicationmodel::_di_IVector_1__Integer &__get_PortNumbers_result) = 0 ;
	virtual HRESULT __safecall get_CellularClass(Winapi::Commontypes::CellularClass &__get_CellularClass_result) = 0 ;
	virtual HRESULT __safecall put_CellularClass(Winapi::Commontypes::CellularClass value) = 0 ;
	virtual HRESULT __safecall get_ProtocolIds(Winapi::Applicationmodel::_di_IVector_1__Integer &__get_ProtocolIds_result) = 0 ;
	virtual HRESULT __safecall get_TeleserviceIds(Winapi::Applicationmodel::_di_IVector_1__Integer &__get_TeleserviceIds_result) = 0 ;
	virtual HRESULT __safecall get_WapApplicationIds(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_WapApplicationIds_result) = 0 ;
	virtual HRESULT __safecall get_WapContentTypes(Winapi::Servicesrt::_di_IVector_1__HSTRING &__get_WapContentTypes_result) = 0 ;
	virtual HRESULT __safecall get_BroadcastTypes(_di_IVector_1__SmsBroadcastType &__get_BroadcastTypes_result) = 0 ;
	virtual HRESULT __safecall get_BroadcastChannels(Winapi::Applicationmodel::_di_IVector_1__Integer &__get_BroadcastChannels_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IVector_1__Integer _scw_get_BroadcastChannels() { Winapi::Applicationmodel::_di_IVector_1__Integer __r; HRESULT __hr = get_BroadcastChannels(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IVector_1__Integer BroadcastChannels = {read=_scw_get_BroadcastChannels};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__SmsBroadcastType _scw_get_BroadcastTypes() { _di_IVector_1__SmsBroadcastType __r; HRESULT __hr = get_BroadcastTypes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__SmsBroadcastType BroadcastTypes = {read=_scw_get_BroadcastTypes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CellularClass _scw_get_CellularClass() { Winapi::Commontypes::CellularClass __r; HRESULT __hr = get_CellularClass(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CellularClass CellularClass = {read=_scw_get_CellularClass, write=put_CellularClass};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_DeviceIds() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_DeviceIds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING DeviceIds = {read=_scw_get_DeviceIds};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_ImsiPrefixes() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_ImsiPrefixes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING ImsiPrefixes = {read=_scw_get_ImsiPrefixes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsMessageType _scw_get_MessageType() { Winapi::Commontypes::SmsMessageType __r; HRESULT __hr = get_MessageType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsMessageType MessageType = {read=_scw_get_MessageType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IVector_1__Integer _scw_get_PortNumbers() { Winapi::Applicationmodel::_di_IVector_1__Integer __r; HRESULT __hr = get_PortNumbers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IVector_1__Integer PortNumbers = {read=_scw_get_PortNumbers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IVector_1__Integer _scw_get_ProtocolIds() { Winapi::Applicationmodel::_di_IVector_1__Integer __r; HRESULT __hr = get_ProtocolIds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IVector_1__Integer ProtocolIds = {read=_scw_get_ProtocolIds};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_SenderNumbers() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_SenderNumbers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING SenderNumbers = {read=_scw_get_SenderNumbers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IVector_1__Integer _scw_get_TeleserviceIds() { Winapi::Applicationmodel::_di_IVector_1__Integer __r; HRESULT __hr = get_TeleserviceIds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IVector_1__Integer TeleserviceIds = {read=_scw_get_TeleserviceIds};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_TextMessagePrefixes() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_TextMessagePrefixes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING TextMessagePrefixes = {read=_scw_get_TextMessagePrefixes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_WapApplicationIds() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_WapApplicationIds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING WapApplicationIds = {read=_scw_get_WapApplicationIds};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IVector_1__HSTRING _scw_get_WapContentTypes() { Winapi::Servicesrt::_di_IVector_1__HSTRING __r; HRESULT __hr = get_WapContentTypes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IVector_1__HSTRING WapContentTypes = {read=_scw_get_WapContentTypes};
};

__interface  INTERFACE_UUID("{FEC7CAE6-97F5-5A19-B32A-D8F0BA276F34}") IIterator_1__ISmsFilterRule_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CC79B2E6-032B-5700-8B64-E354F2AEC051}") IIterator_1__ISmsFilterRule  : public IIterator_1__ISmsFilterRule_Base 
{
	virtual HRESULT __safecall get_Current(_di_ISmsFilterRule &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PISmsFilterRule items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsFilterRule _scw_get_Current() { _di_ISmsFilterRule __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsFilterRule Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{03ED8267-9C90-5260-8BC0-6C3E3306C964}") IIterable_1__ISmsFilterRule_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{FD505BFC-A0B1-5BFB-96E3-753FB3673F3E}") IIterable_1__ISmsFilterRule  : public IIterable_1__ISmsFilterRule_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ISmsFilterRule &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{5B019FA3-B284-5CA2-B487-859442DBEE50}") IVectorView_1__ISmsFilterRule  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ISmsFilterRule &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ISmsFilterRule value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PISmsFilterRule items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{82744C94-93C9-59B1-9957-505E9000A972}") IVector_1__ISmsFilterRule  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ISmsFilterRule &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ISmsFilterRule &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ISmsFilterRule value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_ISmsFilterRule value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_ISmsFilterRule value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_ISmsFilterRule value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PISmsFilterRule items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PISmsFilterRule items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{4E47EAFB-79CD-4881-9894-55A4135B23FA}") ISmsFilterRules  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ActionType(Winapi::Commontypes::SmsFilterActionType &__get_ActionType_result) = 0 ;
	virtual HRESULT __safecall get_Rules(_di_IVector_1__ISmsFilterRule &__get_Rules_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsFilterActionType _scw_get_ActionType() { Winapi::Commontypes::SmsFilterActionType __r; HRESULT __hr = get_ActionType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsFilterActionType ActionType = {read=_scw_get_ActionType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__ISmsFilterRule _scw_get_Rules() { _di_IVector_1__ISmsFilterRule __r; HRESULT __hr = get_Rules(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__ISmsFilterRule Rules = {read=_scw_get_Rules};
};

__interface  INTERFACE_UUID("{22A0D893-4555-4755-B5A1-E7FD84955F8D}") ISmsTextMessage2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall put_To(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_From(HSTRING &__get_From_result) = 0 ;
	virtual HRESULT __safecall get_Body(HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall put_Body(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Encoding(Winapi::Commontypes::SmsEncoding &__get_Encoding_result) = 0 ;
	virtual HRESULT __safecall put_Encoding(Winapi::Commontypes::SmsEncoding value) = 0 ;
	virtual HRESULT __safecall get_CallbackNumber(HSTRING &__get_CallbackNumber_result) = 0 ;
	virtual HRESULT __safecall put_CallbackNumber(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_IsDeliveryNotificationEnabled(bool &__get_IsDeliveryNotificationEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsDeliveryNotificationEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_RetryAttemptCount(int &__get_RetryAttemptCount_result) = 0 ;
	virtual HRESULT __safecall put_RetryAttemptCount(int value) = 0 ;
	virtual HRESULT __safecall get_TeleserviceId(int &__get_TeleserviceId_result) = 0 ;
	virtual HRESULT __safecall get_ProtocolId(int &__get_ProtocolId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body, write=put_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CallbackNumber() { HSTRING __r; HRESULT __hr = get_CallbackNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CallbackNumber = {read=_scw_get_CallbackNumber, write=put_CallbackNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsEncoding _scw_get_Encoding() { Winapi::Commontypes::SmsEncoding __r; HRESULT __hr = get_Encoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsEncoding Encoding = {read=_scw_get_Encoding, write=put_Encoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_From() { HSTRING __r; HRESULT __hr = get_From(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING From = {read=_scw_get_From};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDeliveryNotificationEnabled() { bool __r; HRESULT __hr = get_IsDeliveryNotificationEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDeliveryNotificationEnabled = {read=_scw_get_IsDeliveryNotificationEnabled, write=put_IsDeliveryNotificationEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ProtocolId() { int __r; HRESULT __hr = get_ProtocolId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ProtocolId = {read=_scw_get_ProtocolId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_RetryAttemptCount() { int __r; HRESULT __hr = get_RetryAttemptCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int RetryAttemptCount = {read=_scw_get_RetryAttemptCount, write=put_RetryAttemptCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_TeleserviceId() { int __r; HRESULT __hr = get_TeleserviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int TeleserviceId = {read=_scw_get_TeleserviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To, write=put_To};
};

__interface  INTERFACE_UUID("{CD937743-7A55-4D3B-9021-F22E022D09C5}") ISmsWapMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall get_From(HSTRING &__get_From_result) = 0 ;
	virtual HRESULT __safecall get_ApplicationId(HSTRING &__get_ApplicationId_result) = 0 ;
	virtual HRESULT __safecall get_ContentType(HSTRING &__get_ContentType_result) = 0 ;
	virtual HRESULT __safecall get_BinaryBody(Winapi::Commontypes::_di_IBuffer &__get_BinaryBody_result) = 0 ;
	virtual HRESULT __safecall get_Headers(Winapi::Servicesrt::_di_IMap_2__HSTRING__HSTRING &__get_Headers_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ApplicationId() { HSTRING __r; HRESULT __hr = get_ApplicationId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ApplicationId = {read=_scw_get_ApplicationId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_BinaryBody() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_BinaryBody(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer BinaryBody = {read=_scw_get_BinaryBody};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ContentType() { HSTRING __r; HRESULT __hr = get_ContentType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ContentType = {read=_scw_get_ContentType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_From() { HSTRING __r; HRESULT __hr = get_From(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING From = {read=_scw_get_From};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IMap_2__HSTRING__HSTRING _scw_get_Headers() { Winapi::Servicesrt::_di_IMap_2__HSTRING__HSTRING __r; HRESULT __hr = get_Headers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IMap_2__HSTRING__HSTRING Headers = {read=_scw_get_Headers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To};
};

__interface  INTERFACE_UUID("{E8BB8494-D3A0-4A0A-86D7-291033A8CF54}") ISmsAppMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall put_To(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_From(HSTRING &__get_From_result) = 0 ;
	virtual HRESULT __safecall get_Body(HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall put_Body(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_CallbackNumber(HSTRING &__get_CallbackNumber_result) = 0 ;
	virtual HRESULT __safecall put_CallbackNumber(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_IsDeliveryNotificationEnabled(bool &__get_IsDeliveryNotificationEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsDeliveryNotificationEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_RetryAttemptCount(int &__get_RetryAttemptCount_result) = 0 ;
	virtual HRESULT __safecall put_RetryAttemptCount(int value) = 0 ;
	virtual HRESULT __safecall get_Encoding(Winapi::Commontypes::SmsEncoding &__get_Encoding_result) = 0 ;
	virtual HRESULT __safecall put_Encoding(Winapi::Commontypes::SmsEncoding value) = 0 ;
	virtual HRESULT __safecall get_PortNumber(int &__get_PortNumber_result) = 0 ;
	virtual HRESULT __safecall put_PortNumber(int value) = 0 ;
	virtual HRESULT __safecall get_TeleserviceId(int &__get_TeleserviceId_result) = 0 ;
	virtual HRESULT __safecall put_TeleserviceId(int value) = 0 ;
	virtual HRESULT __safecall get_ProtocolId(int &__get_ProtocolId_result) = 0 ;
	virtual HRESULT __safecall put_ProtocolId(int value) = 0 ;
	virtual HRESULT __safecall get_BinaryBody(Winapi::Commontypes::_di_IBuffer &__get_BinaryBody_result) = 0 ;
	virtual HRESULT __safecall put_BinaryBody(Winapi::Commontypes::_di_IBuffer value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_BinaryBody() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_BinaryBody(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer BinaryBody = {read=_scw_get_BinaryBody, write=put_BinaryBody};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body, write=put_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_CallbackNumber() { HSTRING __r; HRESULT __hr = get_CallbackNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING CallbackNumber = {read=_scw_get_CallbackNumber, write=put_CallbackNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsEncoding _scw_get_Encoding() { Winapi::Commontypes::SmsEncoding __r; HRESULT __hr = get_Encoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsEncoding Encoding = {read=_scw_get_Encoding, write=put_Encoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_From() { HSTRING __r; HRESULT __hr = get_From(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING From = {read=_scw_get_From};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsDeliveryNotificationEnabled() { bool __r; HRESULT __hr = get_IsDeliveryNotificationEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsDeliveryNotificationEnabled = {read=_scw_get_IsDeliveryNotificationEnabled, write=put_IsDeliveryNotificationEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_PortNumber() { int __r; HRESULT __hr = get_PortNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int PortNumber = {read=_scw_get_PortNumber, write=put_PortNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ProtocolId() { int __r; HRESULT __hr = get_ProtocolId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ProtocolId = {read=_scw_get_ProtocolId, write=put_ProtocolId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_RetryAttemptCount() { int __r; HRESULT __hr = get_RetryAttemptCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int RetryAttemptCount = {read=_scw_get_RetryAttemptCount, write=put_RetryAttemptCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_TeleserviceId() { int __r; HRESULT __hr = get_TeleserviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int TeleserviceId = {read=_scw_get_TeleserviceId, write=put_TeleserviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To, write=put_To};
};

__interface  INTERFACE_UUID("{75AEBBF1-E4B7-4874-A09C-2956E592F957}") ISmsBroadcastMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall get_Body(HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall get_Channel(int &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_GeographicalScope(Winapi::Commontypes::SmsGeographicalScope &__get_GeographicalScope_result) = 0 ;
	virtual HRESULT __safecall get_MessageCode(int &__get_MessageCode_result) = 0 ;
	virtual HRESULT __safecall get_UpdateNumber(int &__get_UpdateNumber_result) = 0 ;
	virtual HRESULT __safecall get_BroadcastType(Winapi::Commontypes::SmsBroadcastType &__get_BroadcastType_result) = 0 ;
	virtual HRESULT __safecall get_IsEmergencyAlert(bool &__get_IsEmergencyAlert_result) = 0 ;
	virtual HRESULT __safecall get_IsUserPopupRequested(bool &__get_IsUserPopupRequested_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsBroadcastType _scw_get_BroadcastType() { Winapi::Commontypes::SmsBroadcastType __r; HRESULT __hr = get_BroadcastType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsBroadcastType BroadcastType = {read=_scw_get_BroadcastType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Channel() { int __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsGeographicalScope _scw_get_GeographicalScope() { Winapi::Commontypes::SmsGeographicalScope __r; HRESULT __hr = get_GeographicalScope(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsGeographicalScope GeographicalScope = {read=_scw_get_GeographicalScope};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsEmergencyAlert() { bool __r; HRESULT __hr = get_IsEmergencyAlert(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsEmergencyAlert = {read=_scw_get_IsEmergencyAlert};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsUserPopupRequested() { bool __r; HRESULT __hr = get_IsUserPopupRequested(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsUserPopupRequested = {read=_scw_get_IsUserPopupRequested};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MessageCode() { int __r; HRESULT __hr = get_MessageCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MessageCode = {read=_scw_get_MessageCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_UpdateNumber() { int __r; HRESULT __hr = get_UpdateNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int UpdateNumber = {read=_scw_get_UpdateNumber};
};

__interface  INTERFACE_UUID("{271AA0A6-95B1-44FF-BCB8-B8FDD7E08BC3}") ISmsVoicemailMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall get_Body(HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall get_MessageCount(Winapi::Servicesrt::_di_IReference_1__Integer &__get_MessageCount_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Servicesrt::_di_IReference_1__Integer _scw_get_MessageCount() { Winapi::Servicesrt::_di_IReference_1__Integer __r; HRESULT __hr = get_MessageCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Servicesrt::_di_IReference_1__Integer MessageCount = {read=_scw_get_MessageCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To};
};

__interface  INTERFACE_UUID("{E6D28342-B70B-4677-9379-C9783FDFF8F4}") ISmsStatusMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_To(HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall get_From(HSTRING &__get_From_result) = 0 ;
	virtual HRESULT __safecall get_Body(HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_MessageReferenceNumber(int &__get_MessageReferenceNumber_result) = 0 ;
	virtual HRESULT __safecall get_ServiceCenterTimestamp(Winapi::Commontypes::DateTime &__get_ServiceCenterTimestamp_result) = 0 ;
	virtual HRESULT __safecall get_DischargeTime(Winapi::Commontypes::DateTime &__get_DischargeTime_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_DischargeTime() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_DischargeTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime DischargeTime = {read=_scw_get_DischargeTime};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_From() { HSTRING __r; HRESULT __hr = get_From(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING From = {read=_scw_get_From};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_MessageReferenceNumber() { int __r; HRESULT __hr = get_MessageReferenceNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MessageReferenceNumber = {read=_scw_get_MessageReferenceNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_ServiceCenterTimestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_ServiceCenterTimestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime ServiceCenterTimestamp = {read=_scw_get_ServiceCenterTimestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To};
};

__interface  INTERFACE_UUID("{65C78325-1031-491E-8FB6-EF9991AFE363}") ISmsDevice2Statics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
	virtual HRESULT __safecall FromId(HSTRING deviceId, Winapi::Commontypes::_di_ISmsDevice2 &__FromId_result) = 0 ;
	virtual HRESULT __safecall GetDefault(Winapi::Commontypes::_di_ISmsDevice2 &__GetDefault_result) = 0 ;
	virtual HRESULT __safecall FromParentId(HSTRING parentDeviceId, Winapi::Commontypes::_di_ISmsDevice2 &__FromParentId_result) = 0 ;
};

__interface  INTERFACE_UUID("{2BCFCBD4-2657-4128-AD5F-E3877132BDB1}") ISmsMessageReceivedTriggerDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MessageType(Winapi::Commontypes::SmsMessageType &__get_MessageType_result) = 0 ;
	virtual HRESULT __safecall get_TextMessage(_di_ISmsTextMessage2 &__get_TextMessage_result) = 0 ;
	virtual HRESULT __safecall get_WapMessage(_di_ISmsWapMessage &__get_WapMessage_result) = 0 ;
	virtual HRESULT __safecall get_AppMessage(_di_ISmsAppMessage &__get_AppMessage_result) = 0 ;
	virtual HRESULT __safecall get_BroadcastMessage(_di_ISmsBroadcastMessage &__get_BroadcastMessage_result) = 0 ;
	virtual HRESULT __safecall get_VoicemailMessage(_di_ISmsVoicemailMessage &__get_VoicemailMessage_result) = 0 ;
	virtual HRESULT __safecall get_StatusMessage(_di_ISmsStatusMessage &__get_StatusMessage_result) = 0 ;
	virtual HRESULT __safecall Drop() = 0 ;
	virtual HRESULT __safecall Accept() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsAppMessage _scw_get_AppMessage() { _di_ISmsAppMessage __r; HRESULT __hr = get_AppMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsAppMessage AppMessage = {read=_scw_get_AppMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsBroadcastMessage _scw_get_BroadcastMessage() { _di_ISmsBroadcastMessage __r; HRESULT __hr = get_BroadcastMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsBroadcastMessage BroadcastMessage = {read=_scw_get_BroadcastMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsMessageType _scw_get_MessageType() { Winapi::Commontypes::SmsMessageType __r; HRESULT __hr = get_MessageType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsMessageType MessageType = {read=_scw_get_MessageType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsStatusMessage _scw_get_StatusMessage() { _di_ISmsStatusMessage __r; HRESULT __hr = get_StatusMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsStatusMessage StatusMessage = {read=_scw_get_StatusMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsTextMessage2 _scw_get_TextMessage() { _di_ISmsTextMessage2 __r; HRESULT __hr = get_TextMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsTextMessage2 TextMessage = {read=_scw_get_TextMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsVoicemailMessage _scw_get_VoicemailMessage() { _di_ISmsVoicemailMessage __r; HRESULT __hr = get_VoicemailMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsVoicemailMessage VoicemailMessage = {read=_scw_get_VoicemailMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsWapMessage _scw_get_WapMessage() { _di_ISmsWapMessage __r; HRESULT __hr = get_WapMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsWapMessage WapMessage = {read=_scw_get_WapMessage};
};

__interface  INTERFACE_UUID("{00C36508-6296-4F29-9AAD-8920CEBA3CE8}") ISmsFilterRuleFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFilterRule(Winapi::Commontypes::SmsMessageType messageType, _di_ISmsFilterRule &__CreateFilterRule_result) = 0 ;
};

__interface  INTERFACE_UUID("{A09924ED-6E2E-4530-9FDE-465D02EED00E}") ISmsFilterRulesFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFilterRules(Winapi::Commontypes::SmsFilterActionType actionType, _di_ISmsFilterRules &__CreateFilterRules_result) = 0 ;
};

__interface  INTERFACE_UUID("{33F985C7-DCFA-531F-9CCE-EE5E6C26B1E6}") TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D0A6E7F7-6387-5382-8E25-E55753669949}") TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails  : public TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_ISmsMessageRegistration sender, _di_ISmsMessageReceivedTriggerDetails args) = 0 ;
};

__interface  INTERFACE_UUID("{1720503E-F34F-446B-83B3-0FF19923B409}") ISmsMessageRegistration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall Unregister() = 0 ;
	virtual HRESULT __safecall add_MessageReceived(_di_TypedEventHandler_2__ISmsMessageRegistration__ISmsMessageReceivedTriggerDetails eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_MessageReceived_result) = 0 ;
	virtual HRESULT __safecall remove_MessageReceived(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
};

__interface  INTERFACE_UUID("{EE1A0675-F3C9-5C12-93E0-F2B01BDCE611}") IIterator_1__ISmsMessageRegistration_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C1985A1F-F4DC-5181-8F1A-C0074A777DE5}") IIterator_1__ISmsMessageRegistration  : public IIterator_1__ISmsMessageRegistration_Base 
{
	virtual HRESULT __safecall get_Current(_di_ISmsMessageRegistration &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PISmsMessageRegistration items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsMessageRegistration _scw_get_Current() { _di_ISmsMessageRegistration __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsMessageRegistration Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{F836FA0A-770D-5E8F-8664-01C43F959EEA}") IIterable_1__ISmsMessageRegistration_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6DE88D72-D08E-5B3B-BAF8-3C4129EAA61B}") IIterable_1__ISmsMessageRegistration  : public IIterable_1__ISmsMessageRegistration_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ISmsMessageRegistration &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{A476AD97-23AC-5525-890F-C514921A1854}") IVectorView_1__ISmsMessageRegistration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ISmsMessageRegistration &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ISmsMessageRegistration value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PISmsMessageRegistration items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{63A05464-2898-4778-A03C-6F994907D63A}") ISmsMessageRegistrationStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AllRegistrations(_di_IVectorView_1__ISmsMessageRegistration &__get_AllRegistrations_result) = 0 ;
	virtual HRESULT __safecall Register(HSTRING id, _di_ISmsFilterRules filterRules, _di_ISmsMessageRegistration &__Register_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__ISmsMessageRegistration _scw_get_AllRegistrations() { _di_IVectorView_1__ISmsMessageRegistration __r; HRESULT __hr = get_AllRegistrations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__ISmsMessageRegistration AllRegistrations = {read=_scw_get_AllRegistrations};
};

__interface  INTERFACE_UUID("{5BF4E813-3B53-4C6E-B61A-D86A63755650}") ISmsBinaryMessage  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Format _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsDataFormat &__get_Format_result) = 0 ;
	virtual HRESULT __safecall put_Format _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsDataFormat value) = 0 ;
	virtual HRESULT __stdcall GetData _DEPRECATED_ATTRIBUTE0 (unsigned resultSize, System::PByte resultValue) = 0 ;
	virtual HRESULT __safecall SetData _DEPRECATED_ATTRIBUTE0 (unsigned valueSize, System::PByte value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsDataFormat _scw_get_Format() { Winapi::Commontypes::SmsDataFormat __r; HRESULT __hr = get_Format(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsDataFormat Format = {read=_scw_get_Format, write=put_Format};
};

__interface  INTERFACE_UUID("{13E60D89-EA0A-5B01-9C2F-0E5B435058E0}") IIterator_1__ISmsBinaryMessage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{13E60D89-EA0A-5B01-9C2F-0E5B435058E0}") IIterator_1__ISmsBinaryMessage  : public IIterator_1__ISmsBinaryMessage_Base 
{
	virtual HRESULT __safecall get_Current(_di_ISmsBinaryMessage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PISmsBinaryMessage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsBinaryMessage _scw_get_Current() { _di_ISmsBinaryMessage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsBinaryMessage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{5678A6A5-4D5A-51C2-A133-4B83BF25D987}") IIterable_1__ISmsBinaryMessage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5678A6A5-4D5A-51C2-A133-4B83BF25D987}") IIterable_1__ISmsBinaryMessage  : public IIterable_1__ISmsBinaryMessage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ISmsBinaryMessage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{6EA176EA-99EA-5C79-876A-F4C437B83DF6}") IVectorView_1__ISmsBinaryMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ISmsBinaryMessage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ISmsBinaryMessage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PISmsBinaryMessage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{D61C904C-A495-487F-9A6F-971548C5BC9F}") ISmsTextMessage  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::DateTime &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_PartReferenceId _DEPRECATED_ATTRIBUTE0 (unsigned &__get_PartReferenceId_result) = 0 ;
	virtual HRESULT __safecall get_PartNumber _DEPRECATED_ATTRIBUTE0 (unsigned &__get_PartNumber_result) = 0 ;
	virtual HRESULT __safecall get_PartCount _DEPRECATED_ATTRIBUTE0 (unsigned &__get_PartCount_result) = 0 ;
	virtual HRESULT __safecall get_To _DEPRECATED_ATTRIBUTE0 (HSTRING &__get_To_result) = 0 ;
	virtual HRESULT __safecall put_To _DEPRECATED_ATTRIBUTE0 (HSTRING value) = 0 ;
	virtual HRESULT __safecall get_From _DEPRECATED_ATTRIBUTE0 (HSTRING &__get_From_result) = 0 ;
	virtual HRESULT __safecall put_From _DEPRECATED_ATTRIBUTE0 (HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Body _DEPRECATED_ATTRIBUTE0 (HSTRING &__get_Body_result) = 0 ;
	virtual HRESULT __safecall put_Body _DEPRECATED_ATTRIBUTE0 (HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Encoding _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsEncoding &__get_Encoding_result) = 0 ;
	virtual HRESULT __safecall put_Encoding _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsEncoding value) = 0 ;
	virtual HRESULT __safecall ToBinaryMessages _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsDataFormat format, _di_IVectorView_1__ISmsBinaryMessage &__ToBinaryMessages_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Body() { HSTRING __r; HRESULT __hr = get_Body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Body = {read=_scw_get_Body, write=put_Body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsEncoding _scw_get_Encoding() { Winapi::Commontypes::SmsEncoding __r; HRESULT __hr = get_Encoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsEncoding Encoding = {read=_scw_get_Encoding, write=put_Encoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_From() { HSTRING __r; HRESULT __hr = get_From(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING From = {read=_scw_get_From, write=put_From};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_PartCount() { unsigned __r; HRESULT __hr = get_PartCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned PartCount = {read=_scw_get_PartCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_PartNumber() { unsigned __r; HRESULT __hr = get_PartNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned PartNumber = {read=_scw_get_PartNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_PartReferenceId() { unsigned __r; HRESULT __hr = get_PartReferenceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned PartReferenceId = {read=_scw_get_PartReferenceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Timestamp() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_To() { HSTRING __r; HRESULT __hr = get_To(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING To = {read=_scw_get_To, write=put_To};
};

__interface  INTERFACE_UUID("{7F68C5ED-3CCC-47A3-8C55-380D3B010892}") ISmsTextMessageStatics  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromBinaryMessage _DEPRECATED_ATTRIBUTE0 (_di_ISmsBinaryMessage binaryMessage, _di_ISmsTextMessage &__FromBinaryMessage_result) = 0 ;
	virtual HRESULT __safecall FromBinaryData _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsDataFormat format, unsigned valueSize, System::PByte value, _di_ISmsTextMessage &__FromBinaryData_result) = 0 ;
};

__interface  INTERFACE_UUID("{4E6C4C86-EBE6-55D9-ADC0-FECC38C82AA2}") AsyncOperationCompletedHandler_1__ISmsMessage_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4E6C4C86-EBE6-55D9-ADC0-FECC38C82AA2}") AsyncOperationCompletedHandler_1__ISmsMessage  : public AsyncOperationCompletedHandler_1__ISmsMessage_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ISmsMessage asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{ABF9B459-48C3-5EAC-9749-4C6DB4D507E6}") IAsyncOperation_1__ISmsMessage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{ABF9B459-48C3-5EAC-9749-4C6DB4D507E6}") IAsyncOperation_1__ISmsMessage  : public IAsyncOperation_1__ISmsMessage_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ISmsMessage handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ISmsMessage &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_ISmsMessage &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ISmsMessage _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ISmsMessage __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ISmsMessage Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{EED04F5C-B2B2-5C83-8B13-C78AF6CA3A18}") IIterator_1__ISmsMessage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{EED04F5C-B2B2-5C83-8B13-C78AF6CA3A18}") IIterator_1__ISmsMessage  : public IIterator_1__ISmsMessage_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_ISmsMessage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PISmsMessage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_ISmsMessage _scw_get_Current() { Winapi::Commontypes::_di_ISmsMessage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_ISmsMessage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{ECABFD70-9601-5E38-83CF-B1046022A244}") IIterable_1__ISmsMessage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{ECABFD70-9601-5E38-83CF-B1046022A244}") IIterable_1__ISmsMessage  : public IIterable_1__ISmsMessage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ISmsMessage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9889F253-F188-4427-8D54-CE0C2423C5C1}") ISmsDeviceMessageStore  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall DeleteMessageAsync _DEPRECATED_ATTRIBUTE0 (unsigned messageId, Winapi::Commontypes::_di_IAsyncAction &__DeleteMessageAsync_result) = 0 ;
	virtual HRESULT __safecall DeleteMessagesAsync _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsMessageFilter messageFilter, Winapi::Commontypes::_di_IAsyncAction &__DeleteMessagesAsync_result) = 0 ;
	virtual HRESULT __safecall GetMessageAsync _DEPRECATED_ATTRIBUTE0 (unsigned messageId, _di_IAsyncOperation_1__ISmsMessage &__GetMessageAsync_result) = 0 ;
	virtual HRESULT __safecall GetMessagesAsync _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsMessageFilter messageFilter, Winapi::Commontypes::_di_IAsyncOperationWithProgress_2__IVectorView_1__ISmsMessage__Integer &__GetMessagesAsync_result) = 0 ;
	virtual HRESULT __safecall get_MaxMessages _DEPRECATED_ATTRIBUTE0 (unsigned &__get_MaxMessages_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxMessages() { unsigned __r; HRESULT __hr = get_MaxMessages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxMessages = {read=_scw_get_MaxMessages};
};

__interface  INTERFACE_UUID("{08E80A98-B8E5-41C1-A3D8-D3ABFAE22675}") ISmsMessageReceivedEventArgs  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_TextMessage _DEPRECATED_ATTRIBUTE0 (_di_ISmsTextMessage &__get_TextMessage_result) = 0 ;
	virtual HRESULT __safecall get_BinaryMessage _DEPRECATED_ATTRIBUTE0 (_di_ISmsBinaryMessage &__get_BinaryMessage_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsBinaryMessage _scw_get_BinaryMessage() { _di_ISmsBinaryMessage __r; HRESULT __hr = get_BinaryMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsBinaryMessage BinaryMessage = {read=_scw_get_BinaryMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsTextMessage _scw_get_TextMessage() { _di_ISmsTextMessage __r; HRESULT __hr = get_TextMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsTextMessage TextMessage = {read=_scw_get_TextMessage};
};

__interface  INTERFACE_UUID("{982B1162-3DD7-4618-AF89-0C272D5D06D8}") SmsDeviceStatusChangedEventHandler  _DEPRECATED_ATTRIBUTE0  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke _DEPRECATED_ATTRIBUTE0 (_di_ISmsDevice sender) = 0 ;
};

__interface  INTERFACE_UUID("{091791ED-872B-4EEC-9C72-AB11627B34EC}") ISmsDevice  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SendMessageAsync _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::_di_ISmsMessage message, Winapi::Commontypes::_di_IAsyncAction &__SendMessageAsync_result) = 0 ;
	virtual HRESULT __safecall CalculateLength _DEPRECATED_ATTRIBUTE0 (_di_ISmsTextMessage message, Winapi::Commontypes::SmsEncodedLength &__CalculateLength_result) = 0 ;
	virtual HRESULT __safecall get_AccountPhoneNumber _DEPRECATED_ATTRIBUTE0 (HSTRING &__get_AccountPhoneNumber_result) = 0 ;
	virtual HRESULT __safecall get_CellularClass _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::CellularClass &__get_CellularClass_result) = 0 ;
	virtual HRESULT __safecall get_MessageStore _DEPRECATED_ATTRIBUTE0 (_di_ISmsDeviceMessageStore &__get_MessageStore_result) = 0 ;
	virtual HRESULT __safecall get_DeviceStatus _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsDeviceStatus &__get_DeviceStatus_result) = 0 ;
	virtual HRESULT __safecall add_SmsMessageReceived _DEPRECATED_ATTRIBUTE0 (_di_SmsMessageReceivedEventHandler eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_SmsMessageReceived_result) = 0 ;
	virtual HRESULT __safecall remove_SmsMessageReceived _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	virtual HRESULT __safecall add_SmsDeviceStatusChanged _DEPRECATED_ATTRIBUTE0 (_di_SmsDeviceStatusChangedEventHandler eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_SmsDeviceStatusChanged_result) = 0 ;
	virtual HRESULT __safecall remove_SmsDeviceStatusChanged _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AccountPhoneNumber() { HSTRING __r; HRESULT __hr = get_AccountPhoneNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AccountPhoneNumber = {read=_scw_get_AccountPhoneNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CellularClass _scw_get_CellularClass() { Winapi::Commontypes::CellularClass __r; HRESULT __hr = get_CellularClass(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CellularClass CellularClass = {read=_scw_get_CellularClass};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsDeviceStatus _scw_get_DeviceStatus() { Winapi::Commontypes::SmsDeviceStatus __r; HRESULT __hr = get_DeviceStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsDeviceStatus DeviceStatus = {read=_scw_get_DeviceStatus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsDeviceMessageStore _scw_get_MessageStore() { _di_ISmsDeviceMessageStore __r; HRESULT __hr = get_MessageStore(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsDeviceMessageStore MessageStore = {read=_scw_get_MessageStore};
};

__interface  INTERFACE_UUID("{0B7AD409-EC2D-47CE-A253-732BEEEBCACD}") SmsMessageReceivedEventHandler  _DEPRECATED_ATTRIBUTE0  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke _DEPRECATED_ATTRIBUTE0 (_di_ISmsDevice sender, _di_ISmsMessageReceivedEventArgs e) = 0 ;
};

__interface  INTERFACE_UUID("{44AA5484-43D0-5893-A4EE-7DB00113AE60}") AsyncOperationCompletedHandler_1__ISmsDevice_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4112847D-E507-5969-A8B8-709FD150970B}") AsyncOperationCompletedHandler_1__ISmsDevice  : public AsyncOperationCompletedHandler_1__ISmsDevice_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__ISmsDevice asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{AB710DE1-FCBB-5BD6-9F2F-285FA9FB44E8}") IAsyncOperation_1__ISmsDevice_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2100FBA5-F2F0-5001-AEFC-7AA0B1B744CC}") IAsyncOperation_1__ISmsDevice  : public IAsyncOperation_1__ISmsDevice_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__ISmsDevice handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__ISmsDevice &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_ISmsDevice &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__ISmsDevice _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__ISmsDevice __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__ISmsDevice Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{F88D07EA-D815-4DD1-A234-4520CE4604A4}") ISmsDeviceStatics  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDeviceSelector _DEPRECATED_ATTRIBUTE0 (HSTRING &__GetDeviceSelector_result) = 0 ;
	virtual HRESULT __safecall FromIdAsync _DEPRECATED_ATTRIBUTE0 (HSTRING deviceId, _di_IAsyncOperation_1__ISmsDevice &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDefaultAsync _DEPRECATED_ATTRIBUTE0 (_di_IAsyncOperation_1__ISmsDevice &__GetDefaultAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{2CA11C87-0873-4CAF-8A7D-BD471E8586D1}") ISmsDeviceStatics2  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromNetworkAccountIdAsync _DEPRECATED_ATTRIBUTE0 (HSTRING networkAccountId, _di_IAsyncOperation_1__ISmsDevice &__FromNetworkAccountIdAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{5BB50F15-E46D-4C82-847D-5A0304C1D53D}") ISmsReceivedEventDetails  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DeviceId _DEPRECATED_ATTRIBUTE0 (HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_MessageIndex _DEPRECATED_ATTRIBUTE0 (unsigned &__get_MessageIndex_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MessageIndex() { unsigned __r; HRESULT __hr = get_MessageIndex(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MessageIndex = {read=_scw_get_MessageIndex};
};

__interface  INTERFACE_UUID("{40E05C86-A7B4-4771-9AE7-0B5FFB12C03A}") ISmsReceivedEventDetails2  _DEPRECATED_ATTRIBUTE0  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MessageClass _DEPRECATED_ATTRIBUTE0 (Winapi::Commontypes::SmsMessageClass &__get_MessageClass_result) = 0 ;
	virtual HRESULT __safecall get_BinaryMessage _DEPRECATED_ATTRIBUTE0 (_di_ISmsBinaryMessage &__get_BinaryMessage_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ISmsBinaryMessage _scw_get_BinaryMessage() { _di_ISmsBinaryMessage __r; HRESULT __hr = get_BinaryMessage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ISmsBinaryMessage BinaryMessage = {read=_scw_get_BinaryMessage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SmsMessageClass _scw_get_MessageClass() { Winapi::Commontypes::SmsMessageClass __r; HRESULT __hr = get_MessageClass(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SmsMessageClass MessageClass = {read=_scw_get_MessageClass};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsTextMessage2 : public System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsTextMessage2>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsTextMessage2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TSmsTextMessage2() : System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsTextMessage2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsTextMessage2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsAppMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsAppMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsAppMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TSmsAppMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsAppMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsAppMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsDevice2 : public System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsDevice2Statics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsDevice2Statics> inherited;
	
public:
	static HSTRING __fastcall GetDeviceSelector();
	static Winapi::Commontypes::_di_ISmsDevice2 __fastcall FromId(HSTRING deviceId);
	static Winapi::Commontypes::_di_ISmsDevice2 __fastcall GetDefault();
	static Winapi::Commontypes::_di_ISmsDevice2 __fastcall FromParentId(HSTRING parentDeviceId);
public:
	/* TObject.Create */ inline __fastcall TSmsDevice2() : System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsDevice2Statics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsDevice2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsFilterRule : public System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRuleFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRuleFactory> inherited;
	
public:
	static _di_ISmsFilterRule __fastcall CreateFilterRule(Winapi::Commontypes::SmsMessageType messageType);
public:
	/* TObject.Create */ inline __fastcall TSmsFilterRule() : System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRuleFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsFilterRule() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsFilterRules : public System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRulesFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRulesFactory> inherited;
	
public:
	static _di_ISmsFilterRules __fastcall CreateFilterRules(Winapi::Commontypes::SmsFilterActionType actionType);
public:
	/* TObject.Create */ inline __fastcall TSmsFilterRules() : System::Win::Winrt::TWinRTGenericImportF__1<_di_ISmsFilterRulesFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsFilterRules() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsMessageRegistration : public System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsMessageRegistrationStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsMessageRegistrationStatics> inherited;
	
public:
	static _di_IVectorView_1__ISmsMessageRegistration __fastcall get_AllRegistrations();
	static _di_ISmsMessageRegistration __fastcall Register(HSTRING id, _di_ISmsFilterRules filterRules);
	/* static */ __property _di_IVectorView_1__ISmsMessageRegistration AllRegistrations = {read=get_AllRegistrations};
public:
	/* TObject.Create */ inline __fastcall TSmsMessageRegistration() : System::Win::Winrt::TWinRTGenericImportS__1<_di_ISmsMessageRegistrationStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsMessageRegistration() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsBinaryMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsBinaryMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsBinaryMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TSmsBinaryMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_ISmsBinaryMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsBinaryMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsTextMessage : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_ISmsTextMessageStatics,_di_ISmsTextMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_ISmsTextMessageStatics,_di_ISmsTextMessage> inherited;
	
public:
	static _di_ISmsTextMessage __fastcall FromBinaryMessage(_di_ISmsBinaryMessage binaryMessage);
	static _di_ISmsTextMessage __fastcall FromBinaryData(Winapi::Commontypes::SmsDataFormat format, unsigned valueSize, System::PByte value);
public:
	/* TObject.Create */ inline __fastcall TSmsTextMessage() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_ISmsTextMessageStatics,_di_ISmsTextMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsTextMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSmsDevice : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_ISmsDeviceStatics,_di_ISmsDeviceStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_ISmsDeviceStatics,_di_ISmsDeviceStatics2> inherited;
	
public:
	static HSTRING __fastcall GetDeviceSelector();
	static _di_IAsyncOperation_1__ISmsDevice __fastcall FromIdAsync(HSTRING deviceId);
	static _di_IAsyncOperation_1__ISmsDevice __fastcall GetDefaultAsync();
	static _di_IAsyncOperation_1__ISmsDevice __fastcall FromNetworkAccountIdAsync(HSTRING networkAccountId);
public:
	/* TObject.Create */ inline __fastcall TSmsDevice() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_ISmsDeviceStatics,_di_ISmsDeviceStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSmsDevice() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sms */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_SmsHPP
