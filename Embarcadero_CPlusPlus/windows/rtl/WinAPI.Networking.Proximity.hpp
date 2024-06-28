// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Networking.Proximity.pas' rev: 34.00 (Windows)

#ifndef Winapi_Networking_ProximityHPP
#define Winapi_Networking_ProximityHPP

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
namespace Networking
{
namespace Proximity
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IProximityMessage;
typedef System::DelphiInterface<IProximityMessage> _di_IProximityMessage;
__interface DELPHIINTERFACE MessageTransmittedHandler;
typedef System::DelphiInterface<MessageTransmittedHandler> _di_MessageTransmittedHandler;
__interface DELPHIINTERFACE DeviceArrivedEventHandler;
typedef System::DelphiInterface<DeviceArrivedEventHandler> _di_DeviceArrivedEventHandler;
__interface DELPHIINTERFACE DeviceDepartedEventHandler;
typedef System::DelphiInterface<DeviceDepartedEventHandler> _di_DeviceDepartedEventHandler;
__interface DELPHIINTERFACE IProximityDevice;
typedef System::DelphiInterface<IProximityDevice> _di_IProximityDevice;
__interface DELPHIINTERFACE MessageReceivedHandler;
typedef System::DelphiInterface<MessageReceivedHandler> _di_MessageReceivedHandler;
__interface DELPHIINTERFACE IProximityDeviceStatics;
typedef System::DelphiInterface<IProximityDeviceStatics> _di_IProximityDeviceStatics;
class DELPHICLASS TProximityDevice;
//-- type declarations -------------------------------------------------------
typedef _di_IProximityMessage *PIProximityMessage;

typedef _di_MessageTransmittedHandler *PMessageTransmittedHandler;

typedef _di_DeviceArrivedEventHandler *PDeviceArrivedEventHandler;

typedef _di_DeviceDepartedEventHandler *PDeviceDepartedEventHandler;

typedef _di_IProximityDevice *PIProximityDevice;

typedef _di_MessageReceivedHandler *PMessageReceivedHandler;

typedef _di_IProximityDeviceStatics *PIProximityDeviceStatics;

__interface  INTERFACE_UUID("{EFAB0782-F6E1-4675-A045-D8E320C24808}") IProximityMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MessageType(HSTRING &__get_MessageType_result) = 0 ;
	virtual HRESULT __safecall get_SubscriptionId(__int64 &__get_SubscriptionId_result) = 0 ;
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IBuffer &__get_Data_result) = 0 ;
	virtual HRESULT __safecall get_DataAsString(HSTRING &__get_DataAsString_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Data() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Data = {read=_scw_get_Data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DataAsString() { HSTRING __r; HRESULT __hr = get_DataAsString(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DataAsString = {read=_scw_get_DataAsString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MessageType() { HSTRING __r; HRESULT __hr = get_MessageType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MessageType = {read=_scw_get_MessageType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline __int64 _scw_get_SubscriptionId() { __int64 __r; HRESULT __hr = get_SubscriptionId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property __int64 SubscriptionId = {read=_scw_get_SubscriptionId};
};

__interface  INTERFACE_UUID("{EFAA0B4A-F6E2-4D7D-856C-78FC8EFC021E}") MessageTransmittedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IProximityDevice sender, __int64 messageId) = 0 ;
};

__interface  INTERFACE_UUID("{EFA9DA69-F6E1-49C9-A49E-8E0FC58FB911}") DeviceArrivedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IProximityDevice sender) = 0 ;
};

__interface  INTERFACE_UUID("{EFA9DA69-F6E2-49C9-A49E-8E0FC58FB911}") DeviceDepartedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IProximityDevice sender) = 0 ;
};

__interface  INTERFACE_UUID("{EFA8A552-F6E1-4329-A0FC-AB6B0FD28262}") IProximityDevice  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SubscribeForMessage(HSTRING messageType, _di_MessageReceivedHandler messageReceivedHandler, __int64 &__SubscribeForMessage_result) = 0 ;
	virtual HRESULT __safecall PublishMessage(HSTRING messageType, HSTRING message, __int64 &__PublishMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall PublishMessage(HSTRING messageType, HSTRING message, _di_MessageTransmittedHandler messageTransmittedHandler, __int64 &__PublishMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall PublishBinaryMessage(HSTRING messageType, Winapi::Commontypes::_di_IBuffer message, __int64 &__PublishBinaryMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall PublishBinaryMessage(HSTRING messageType, Winapi::Commontypes::_di_IBuffer message, _di_MessageTransmittedHandler messageTransmittedHandler, __int64 &__PublishBinaryMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall PublishUriMessage(Winapi::Commontypes::_di_IUriRuntimeClass message, __int64 &__PublishUriMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall PublishUriMessage(Winapi::Commontypes::_di_IUriRuntimeClass message, _di_MessageTransmittedHandler messageTransmittedHandler, __int64 &__PublishUriMessage_result) = 0 /* overload */;
	virtual HRESULT __safecall StopSubscribingForMessage(__int64 subscriptionId) = 0 ;
	virtual HRESULT __safecall StopPublishingMessage(__int64 messageId) = 0 ;
	virtual HRESULT __safecall add_DeviceArrived(_di_DeviceArrivedEventHandler arrivedHandler, Winapi::Commontypes::EventRegistrationToken &__add_DeviceArrived_result) = 0 ;
	virtual HRESULT __safecall remove_DeviceArrived(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall add_DeviceDeparted(_di_DeviceDepartedEventHandler departedHandler, Winapi::Commontypes::EventRegistrationToken &__add_DeviceDeparted_result) = 0 ;
	virtual HRESULT __safecall remove_DeviceDeparted(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall get_MaxMessageBytes(unsigned &__get_MaxMessageBytes_result) = 0 ;
	virtual HRESULT __safecall get_BitsPerSecond(unsigned __int64 &__get_BitsPerSecond_result) = 0 ;
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BitsPerSecond() { unsigned __int64 __r; HRESULT __hr = get_BitsPerSecond(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BitsPerSecond = {read=_scw_get_BitsPerSecond};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxMessageBytes() { unsigned __r; HRESULT __hr = get_MaxMessageBytes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxMessageBytes = {read=_scw_get_MaxMessageBytes};
};

__interface  INTERFACE_UUID("{EFAB0782-F6E2-4675-A045-D8E320C24808}") MessageReceivedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IProximityDevice sender, _di_IProximityMessage message) = 0 ;
};

__interface  INTERFACE_UUID("{914BA01D-F6E1-47C4-A14C-148A1903D0C6}") IProximityDeviceStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
	virtual HRESULT __safecall GetDefault(_di_IProximityDevice &__GetDefault_result) = 0 ;
	virtual HRESULT __safecall FromId(HSTRING deviceId, _di_IProximityDevice &__FromId_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TProximityDevice : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IProximityDeviceStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IProximityDeviceStatics> inherited;
	
public:
	static HSTRING __fastcall GetDeviceSelector();
	static _di_IProximityDevice __fastcall GetDefault();
	static _di_IProximityDevice __fastcall FromId(HSTRING deviceId);
public:
	/* TObject.Create */ inline __fastcall TProximityDevice() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IProximityDeviceStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TProximityDevice() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Proximity */
}	/* namespace Networking */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Networking_ProximityHPP
