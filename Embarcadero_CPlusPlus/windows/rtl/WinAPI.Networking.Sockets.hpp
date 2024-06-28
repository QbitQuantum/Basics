// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Networking.Sockets.pas' rev: 34.00 (Windows)

#ifndef Winapi_Networking_SocketsHPP
#define Winapi_Networking_SocketsHPP

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
#include <Winapi.Networking.hpp>
#include <Winapi.Storage.Streams.hpp>
#include <Winapi.Security.Cryptography.hpp>
#include <Winapi.Security.Credentials.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Networking
{
namespace Sockets
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IStreamSocketListenerControl;
typedef System::DelphiInterface<IStreamSocketListenerControl> _di_IStreamSocketListenerControl;
__interface DELPHIINTERFACE IStreamSocketListenerInformation;
typedef System::DelphiInterface<IStreamSocketListenerInformation> _di_IStreamSocketListenerInformation;
__interface DELPHIINTERFACE IStreamSocketControl;
typedef System::DelphiInterface<IStreamSocketControl> _di_IStreamSocketControl;
__interface DELPHIINTERFACE IStreamSocketInformation;
typedef System::DelphiInterface<IStreamSocketInformation> _di_IStreamSocketInformation;
__interface DELPHIINTERFACE IStreamSocket;
typedef System::DelphiInterface<IStreamSocket> _di_IStreamSocket;
__interface DELPHIINTERFACE IStreamSocketListenerConnectionReceivedEventArgs;
typedef System::DelphiInterface<IStreamSocketListenerConnectionReceivedEventArgs> _di_IStreamSocketListenerConnectionReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs> _di_TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs;
__interface DELPHIINTERFACE IStreamSocketListener;
typedef System::DelphiInterface<IStreamSocketListener> _di_IStreamSocketListener;
__interface DELPHIINTERFACE IDatagramSocketControl;
typedef System::DelphiInterface<IDatagramSocketControl> _di_IDatagramSocketControl;
__interface DELPHIINTERFACE IDatagramSocketInformation;
typedef System::DelphiInterface<IDatagramSocketInformation> _di_IDatagramSocketInformation;
__interface DELPHIINTERFACE IDatagramSocketMessageReceivedEventArgs;
typedef System::DelphiInterface<IDatagramSocketMessageReceivedEventArgs> _di_IDatagramSocketMessageReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs> _di_TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs;
__interface DELPHIINTERFACE IDatagramSocket;
typedef System::DelphiInterface<IDatagramSocket> _di_IDatagramSocket;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IStreamSocket_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IStreamSocket_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IStreamSocket_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IStreamSocket;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IStreamSocket> _di_AsyncOperationCompletedHandler_1__IStreamSocket;
__interface DELPHIINTERFACE IAsyncOperation_1__IStreamSocket_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IStreamSocket_Base> _di_IAsyncOperation_1__IStreamSocket_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IStreamSocket;
typedef System::DelphiInterface<IAsyncOperation_1__IStreamSocket> _di_IAsyncOperation_1__IStreamSocket;
__interface DELPHIINTERFACE ISocketActivityContext;
typedef System::DelphiInterface<ISocketActivityContext> _di_ISocketActivityContext;
__interface DELPHIINTERFACE IMessageWebSocketMessageReceivedEventArgs;
typedef System::DelphiInterface<IMessageWebSocketMessageReceivedEventArgs> _di_IMessageWebSocketMessageReceivedEventArgs;
__interface DELPHIINTERFACE IMessageWebSocketMessageReceivedEventArgs2;
typedef System::DelphiInterface<IMessageWebSocketMessageReceivedEventArgs2> _di_IMessageWebSocketMessageReceivedEventArgs2;
__interface DELPHIINTERFACE IWebSocketClosedEventArgs;
typedef System::DelphiInterface<IWebSocketClosedEventArgs> _di_IWebSocketClosedEventArgs;
__interface DELPHIINTERFACE IDatagramSocketControl2;
typedef System::DelphiInterface<IDatagramSocketControl2> _di_IDatagramSocketControl2;
__interface DELPHIINTERFACE IDatagramSocketControl3;
typedef System::DelphiInterface<IDatagramSocketControl3> _di_IDatagramSocketControl3;
__interface DELPHIINTERFACE IDatagramSocketStatics;
typedef System::DelphiInterface<IDatagramSocketStatics> _di_IDatagramSocketStatics;
__interface DELPHIINTERFACE IDatagramSocket2;
typedef System::DelphiInterface<IDatagramSocket2> _di_IDatagramSocket2;
__interface DELPHIINTERFACE IDatagramSocket3;
typedef System::DelphiInterface<IDatagramSocket3> _di_IDatagramSocket3;
__interface DELPHIINTERFACE IStreamSocketInformation2;
typedef System::DelphiInterface<IStreamSocketInformation2> _di_IStreamSocketInformation2;
__interface DELPHIINTERFACE IStreamSocketControl2;
typedef System::DelphiInterface<IStreamSocketControl2> _di_IStreamSocketControl2;
__interface DELPHIINTERFACE IStreamSocketControl3;
typedef System::DelphiInterface<IStreamSocketControl3> _di_IStreamSocketControl3;
__interface DELPHIINTERFACE IStreamSocketControl4;
typedef System::DelphiInterface<IStreamSocketControl4> _di_IStreamSocketControl4;
__interface DELPHIINTERFACE IStreamSocket2;
typedef System::DelphiInterface<IStreamSocket2> _di_IStreamSocket2;
__interface DELPHIINTERFACE IStreamSocket3;
typedef System::DelphiInterface<IStreamSocket3> _di_IStreamSocket3;
__interface DELPHIINTERFACE IStreamSocketStatics;
typedef System::DelphiInterface<IStreamSocketStatics> _di_IStreamSocketStatics;
__interface DELPHIINTERFACE IStreamSocketListenerControl2;
typedef System::DelphiInterface<IStreamSocketListenerControl2> _di_IStreamSocketListenerControl2;
__interface DELPHIINTERFACE IStreamSocketListener2;
typedef System::DelphiInterface<IStreamSocketListener2> _di_IStreamSocketListener2;
__interface DELPHIINTERFACE IStreamSocketListener3;
typedef System::DelphiInterface<IStreamSocketListener3> _di_IStreamSocketListener3;
__interface DELPHIINTERFACE IWebSocketServerCustomValidationRequestedEventArgs;
typedef System::DelphiInterface<IWebSocketServerCustomValidationRequestedEventArgs> _di_IWebSocketServerCustomValidationRequestedEventArgs;
__interface DELPHIINTERFACE IWebSocketControl;
typedef System::DelphiInterface<IWebSocketControl> _di_IWebSocketControl;
__interface DELPHIINTERFACE IWebSocketControl2;
typedef System::DelphiInterface<IWebSocketControl2> _di_IWebSocketControl2;
__interface DELPHIINTERFACE IWebSocketInformation;
typedef System::DelphiInterface<IWebSocketInformation> _di_IWebSocketInformation;
__interface DELPHIINTERFACE IWebSocketInformation2;
typedef System::DelphiInterface<IWebSocketInformation2> _di_IWebSocketInformation2;
__interface DELPHIINTERFACE TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs> _di_TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs;
__interface DELPHIINTERFACE IWebSocket;
typedef System::DelphiInterface<IWebSocket> _di_IWebSocket;
__interface DELPHIINTERFACE IMessageWebSocketControl;
typedef System::DelphiInterface<IMessageWebSocketControl> _di_IMessageWebSocketControl;
__interface DELPHIINTERFACE IMessageWebSocketControl2;
typedef System::DelphiInterface<IMessageWebSocketControl2> _di_IMessageWebSocketControl2;
__interface DELPHIINTERFACE TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs> _di_TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs;
__interface DELPHIINTERFACE IMessageWebSocket;
typedef System::DelphiInterface<IMessageWebSocket> _di_IMessageWebSocket;
__interface DELPHIINTERFACE TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs> _di_TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;
__interface DELPHIINTERFACE IMessageWebSocket2;
typedef System::DelphiInterface<IMessageWebSocket2> _di_IMessageWebSocket2;
__interface DELPHIINTERFACE IStreamWebSocketControl;
typedef System::DelphiInterface<IStreamWebSocketControl> _di_IStreamWebSocketControl;
__interface DELPHIINTERFACE IStreamWebSocketControl2;
typedef System::DelphiInterface<IStreamWebSocketControl2> _di_IStreamWebSocketControl2;
__interface DELPHIINTERFACE IStreamWebSocket;
typedef System::DelphiInterface<IStreamWebSocket> _di_IStreamWebSocket;
__interface DELPHIINTERFACE TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs> _di_TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;
__interface DELPHIINTERFACE IStreamWebSocket2;
typedef System::DelphiInterface<IStreamWebSocket2> _di_IStreamWebSocket2;
__interface DELPHIINTERFACE ISocketErrorStatics;
typedef System::DelphiInterface<ISocketErrorStatics> _di_ISocketErrorStatics;
__interface DELPHIINTERFACE IWebSocketErrorStatics;
typedef System::DelphiInterface<IWebSocketErrorStatics> _di_IWebSocketErrorStatics;
__interface DELPHIINTERFACE IControlChannelTriggerResetEventDetails;
typedef System::DelphiInterface<IControlChannelTriggerResetEventDetails> _di_IControlChannelTriggerResetEventDetails;
class DELPHICLASS TDatagramSocket;
class DELPHICLASS TStreamSocket;
class DELPHICLASS TStreamSocketListener;
class DELPHICLASS TMessageWebSocket;
class DELPHICLASS TStreamWebSocket;
class DELPHICLASS TSocketError;
class DELPHICLASS TWebSocketError;
//-- type declarations -------------------------------------------------------
typedef _di_IStreamSocketListenerControl *PIStreamSocketListenerControl;

typedef _di_IStreamSocketListenerInformation *PIStreamSocketListenerInformation;

typedef _di_IStreamSocketControl *PIStreamSocketControl;

typedef _di_IStreamSocketInformation *PIStreamSocketInformation;

typedef _di_IStreamSocket *PIStreamSocket;

typedef _di_IStreamSocketListenerConnectionReceivedEventArgs *PIStreamSocketListenerConnectionReceivedEventArgs;

typedef _di_TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs *PTypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs;

typedef _di_IStreamSocketListener *PIStreamSocketListener;

typedef _di_IDatagramSocketControl *PIDatagramSocketControl;

typedef _di_IDatagramSocketInformation *PIDatagramSocketInformation;

typedef _di_IDatagramSocketMessageReceivedEventArgs *PIDatagramSocketMessageReceivedEventArgs;

typedef _di_TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs *PTypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs;

typedef _di_IDatagramSocket *PIDatagramSocket;

typedef _di_AsyncOperationCompletedHandler_1__IStreamSocket *PAsyncOperationCompletedHandler_1__IStreamSocket;

typedef _di_IAsyncOperation_1__IStreamSocket *PIAsyncOperation_1__IStreamSocket;

typedef _di_ISocketActivityContext *PISocketActivityContext;

typedef _di_IMessageWebSocketMessageReceivedEventArgs *PIMessageWebSocketMessageReceivedEventArgs;

typedef _di_IMessageWebSocketMessageReceivedEventArgs2 *PIMessageWebSocketMessageReceivedEventArgs2;

typedef _di_IWebSocketClosedEventArgs *PIWebSocketClosedEventArgs;

typedef _di_IDatagramSocketControl2 *PIDatagramSocketControl2;

typedef _di_IDatagramSocketControl3 *PIDatagramSocketControl3;

typedef _di_IDatagramSocketStatics *PIDatagramSocketStatics;

typedef _di_IDatagramSocket2 *PIDatagramSocket2;

typedef _di_IDatagramSocket3 *PIDatagramSocket3;

typedef _di_IStreamSocketInformation2 *PIStreamSocketInformation2;

typedef _di_IStreamSocketControl2 *PIStreamSocketControl2;

typedef _di_IStreamSocketControl3 *PIStreamSocketControl3;

typedef _di_IStreamSocketControl4 *PIStreamSocketControl4;

typedef _di_IStreamSocket2 *PIStreamSocket2;

typedef _di_IStreamSocket3 *PIStreamSocket3;

typedef _di_IStreamSocketStatics *PIStreamSocketStatics;

typedef _di_IStreamSocketListenerControl2 *PIStreamSocketListenerControl2;

typedef _di_IStreamSocketListener2 *PIStreamSocketListener2;

typedef _di_IStreamSocketListener3 *PIStreamSocketListener3;

typedef _di_IWebSocketServerCustomValidationRequestedEventArgs *PIWebSocketServerCustomValidationRequestedEventArgs;

typedef _di_IWebSocketControl *PIWebSocketControl;

typedef _di_IWebSocketControl2 *PIWebSocketControl2;

typedef _di_IWebSocketInformation *PIWebSocketInformation;

typedef _di_IWebSocketInformation2 *PIWebSocketInformation2;

typedef _di_TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs *PTypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs;

typedef _di_IWebSocket *PIWebSocket;

typedef _di_IMessageWebSocketControl *PIMessageWebSocketControl;

typedef _di_IMessageWebSocketControl2 *PIMessageWebSocketControl2;

typedef _di_TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs *PTypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs;

typedef _di_IMessageWebSocket *PIMessageWebSocket;

typedef _di_TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs *PTypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;

typedef _di_IMessageWebSocket2 *PIMessageWebSocket2;

typedef _di_IStreamWebSocketControl *PIStreamWebSocketControl;

typedef _di_IStreamWebSocketControl2 *PIStreamWebSocketControl2;

typedef _di_IStreamWebSocket *PIStreamWebSocket;

typedef _di_TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs *PTypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs;

typedef _di_IStreamWebSocket2 *PIStreamWebSocket2;

typedef _di_ISocketErrorStatics *PISocketErrorStatics;

typedef _di_IWebSocketErrorStatics *PIWebSocketErrorStatics;

typedef _di_IControlChannelTriggerResetEventDetails *PIControlChannelTriggerResetEventDetails;

__interface  INTERFACE_UUID("{20D8C576-8D8A-4DBA-9722-A16C4D984980}") IStreamSocketListenerControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_QualityOfService(Winapi::Commontypes::SocketQualityOfService &__get_QualityOfService_result) = 0 ;
	virtual HRESULT __safecall put_QualityOfService(Winapi::Commontypes::SocketQualityOfService value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketQualityOfService _scw_get_QualityOfService() { Winapi::Commontypes::SocketQualityOfService __r; HRESULT __hr = get_QualityOfService(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketQualityOfService QualityOfService = {read=_scw_get_QualityOfService, write=put_QualityOfService};
};

__interface  INTERFACE_UUID("{E62BA82F-A63A-430B-BF62-29E93E5633B4}") IStreamSocketListenerInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LocalPort(HSTRING &__get_LocalPort_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LocalPort() { HSTRING __r; HRESULT __hr = get_LocalPort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LocalPort = {read=_scw_get_LocalPort};
};

__interface  INTERFACE_UUID("{FE25ADF1-92AB-4AF3-9992-0F4C85E36CC4}") IStreamSocketControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NoDelay(bool &__get_NoDelay_result) = 0 ;
	virtual HRESULT __safecall put_NoDelay(bool value) = 0 ;
	virtual HRESULT __safecall get_KeepAlive(bool &__get_KeepAlive_result) = 0 ;
	virtual HRESULT __safecall put_KeepAlive(bool value) = 0 ;
	virtual HRESULT __safecall get_OutboundBufferSizeInBytes(unsigned &__get_OutboundBufferSizeInBytes_result) = 0 ;
	virtual HRESULT __safecall put_OutboundBufferSizeInBytes(unsigned value) = 0 ;
	virtual HRESULT __safecall get_QualityOfService(Winapi::Commontypes::SocketQualityOfService &__get_QualityOfService_result) = 0 ;
	virtual HRESULT __safecall put_QualityOfService(Winapi::Commontypes::SocketQualityOfService value) = 0 ;
	virtual HRESULT __safecall get_OutboundUnicastHopLimit(System::Byte &__get_OutboundUnicastHopLimit_result) = 0 ;
	virtual HRESULT __safecall put_OutboundUnicastHopLimit(System::Byte value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_KeepAlive() { bool __r; HRESULT __hr = get_KeepAlive(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool KeepAlive = {read=_scw_get_KeepAlive, write=put_KeepAlive};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_NoDelay() { bool __r; HRESULT __hr = get_NoDelay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool NoDelay = {read=_scw_get_NoDelay, write=put_NoDelay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_OutboundBufferSizeInBytes() { unsigned __r; HRESULT __hr = get_OutboundBufferSizeInBytes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned OutboundBufferSizeInBytes = {read=_scw_get_OutboundBufferSizeInBytes, write=put_OutboundBufferSizeInBytes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_OutboundUnicastHopLimit() { System::Byte __r; HRESULT __hr = get_OutboundUnicastHopLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte OutboundUnicastHopLimit = {read=_scw_get_OutboundUnicastHopLimit, write=put_OutboundUnicastHopLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketQualityOfService _scw_get_QualityOfService() { Winapi::Commontypes::SocketQualityOfService __r; HRESULT __hr = get_QualityOfService(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketQualityOfService QualityOfService = {read=_scw_get_QualityOfService, write=put_QualityOfService};
};

__interface  INTERFACE_UUID("{3B80AE30-5E68-4205-88F0-DC85D2E25DED}") IStreamSocketInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LocalAddress(Winapi::Commontypes::_di_IHostName &__get_LocalAddress_result) = 0 ;
	virtual HRESULT __safecall get_LocalPort(HSTRING &__get_LocalPort_result) = 0 ;
	virtual HRESULT __safecall get_RemoteHostName(Winapi::Commontypes::_di_IHostName &__get_RemoteHostName_result) = 0 ;
	virtual HRESULT __safecall get_RemoteAddress(Winapi::Commontypes::_di_IHostName &__get_RemoteAddress_result) = 0 ;
	virtual HRESULT __safecall get_RemoteServiceName(HSTRING &__get_RemoteServiceName_result) = 0 ;
	virtual HRESULT __safecall get_RemotePort(HSTRING &__get_RemotePort_result) = 0 ;
	virtual HRESULT __safecall get_RoundTripTimeStatistics(Winapi::Commontypes::RoundTripTimeStatistics &__get_RoundTripTimeStatistics_result) = 0 ;
	virtual HRESULT __safecall get_BandwidthStatistics(Winapi::Commontypes::BandwidthStatistics &__get_BandwidthStatistics_result) = 0 ;
	virtual HRESULT __safecall get_ProtectionLevel(Winapi::Commontypes::SocketProtectionLevel &__get_ProtectionLevel_result) = 0 ;
	virtual HRESULT __safecall get_SessionKey(Winapi::Commontypes::_di_IBuffer &__get_SessionKey_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BandwidthStatistics _scw_get_BandwidthStatistics() { Winapi::Commontypes::BandwidthStatistics __r; HRESULT __hr = get_BandwidthStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BandwidthStatistics BandwidthStatistics = {read=_scw_get_BandwidthStatistics};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_LocalAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_LocalAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName LocalAddress = {read=_scw_get_LocalAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LocalPort() { HSTRING __r; HRESULT __hr = get_LocalPort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LocalPort = {read=_scw_get_LocalPort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketProtectionLevel _scw_get_ProtectionLevel() { Winapi::Commontypes::SocketProtectionLevel __r; HRESULT __hr = get_ProtectionLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketProtectionLevel ProtectionLevel = {read=_scw_get_ProtectionLevel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_RemoteAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_RemoteAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName RemoteAddress = {read=_scw_get_RemoteAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_RemoteHostName() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_RemoteHostName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName RemoteHostName = {read=_scw_get_RemoteHostName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RemotePort() { HSTRING __r; HRESULT __hr = get_RemotePort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RemotePort = {read=_scw_get_RemotePort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RemoteServiceName() { HSTRING __r; HRESULT __hr = get_RemoteServiceName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RemoteServiceName = {read=_scw_get_RemoteServiceName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::RoundTripTimeStatistics _scw_get_RoundTripTimeStatistics() { Winapi::Commontypes::RoundTripTimeStatistics __r; HRESULT __hr = get_RoundTripTimeStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::RoundTripTimeStatistics RoundTripTimeStatistics = {read=_scw_get_RoundTripTimeStatistics};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_SessionKey() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_SessionKey(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer SessionKey = {read=_scw_get_SessionKey};
};

__interface  INTERFACE_UUID("{69A22CF3-FC7B-4857-AF38-F6E7DE6A5B49}") IStreamSocket  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Control(_di_IStreamSocketControl &__get_Control_result) = 0 ;
	virtual HRESULT __safecall get_Information(_di_IStreamSocketInformation &__get_Information_result) = 0 ;
	virtual HRESULT __safecall get_InputStream(Winapi::Commontypes::_di_IInputStream &__get_InputStream_result) = 0 ;
	virtual HRESULT __safecall get_OutputStream(Winapi::Commontypes::_di_IOutputStream &__get_OutputStream_result) = 0 ;
	virtual HRESULT __safecall ConnectAsync(Winapi::Networking::_di_IEndpointPair endpointPair, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall ConnectAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall ConnectAsync(Winapi::Networking::_di_IEndpointPair endpointPair, Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall ConnectAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall UpgradeToSslAsync(Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_IHostName validationHostName, Winapi::Commontypes::_di_IAsyncAction &__UpgradeToSslAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamSocketControl _scw_get_Control() { _di_IStreamSocketControl __r; HRESULT __hr = get_Control(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamSocketControl Control = {read=_scw_get_Control};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamSocketInformation _scw_get_Information() { _di_IStreamSocketInformation __r; HRESULT __hr = get_Information(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamSocketInformation Information = {read=_scw_get_Information};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInputStream _scw_get_InputStream() { Winapi::Commontypes::_di_IInputStream __r; HRESULT __hr = get_InputStream(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInputStream InputStream = {read=_scw_get_InputStream};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IOutputStream _scw_get_OutputStream() { Winapi::Commontypes::_di_IOutputStream __r; HRESULT __hr = get_OutputStream(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IOutputStream OutputStream = {read=_scw_get_OutputStream};
};

__interface  INTERFACE_UUID("{0C472EA9-373F-447B-85B1-DDD4548803BA}") IStreamSocketListenerConnectionReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Socket(_di_IStreamSocket &__get_Socket_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamSocket _scw_get_Socket() { _di_IStreamSocket __r; HRESULT __hr = get_Socket(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamSocket Socket = {read=_scw_get_Socket};
};

__interface  INTERFACE_UUID("{33D00D41-C94F-5A61-9AB7-280DCEFA0B08}") TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{53211835-FF9E-59A6-AB04-69DD8BA5D368}") TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs  : public TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IStreamSocketListener sender, _di_IStreamSocketListenerConnectionReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{FF513437-DF9F-4DF0-BF82-0EC5D7B35AAE}") IStreamSocketListener  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Control(_di_IStreamSocketListenerControl &__get_Control_result) = 0 ;
	virtual HRESULT __safecall get_Information(_di_IStreamSocketListenerInformation &__get_Information_result) = 0 ;
	virtual HRESULT __safecall BindServiceNameAsync(HSTRING localServiceName, Winapi::Commontypes::_di_IAsyncAction &__BindServiceNameAsync_result) = 0 ;
	virtual HRESULT __safecall BindEndpointAsync(Winapi::Commontypes::_di_IHostName localHostName, HSTRING localServiceName, Winapi::Commontypes::_di_IAsyncAction &__BindEndpointAsync_result) = 0 ;
	virtual HRESULT __safecall add_ConnectionReceived(_di_TypedEventHandler_2__IStreamSocketListener__IStreamSocketListenerConnectionReceivedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_ConnectionReceived_result) = 0 ;
	virtual HRESULT __safecall remove_ConnectionReceived(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamSocketListenerControl _scw_get_Control() { _di_IStreamSocketListenerControl __r; HRESULT __hr = get_Control(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamSocketListenerControl Control = {read=_scw_get_Control};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamSocketListenerInformation _scw_get_Information() { _di_IStreamSocketListenerInformation __r; HRESULT __hr = get_Information(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamSocketListenerInformation Information = {read=_scw_get_Information};
};

__interface  INTERFACE_UUID("{52AC3F2E-349A-4135-BB58-B79B2647D390}") IDatagramSocketControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_QualityOfService(Winapi::Commontypes::SocketQualityOfService &__get_QualityOfService_result) = 0 ;
	virtual HRESULT __safecall put_QualityOfService(Winapi::Commontypes::SocketQualityOfService value) = 0 ;
	virtual HRESULT __safecall get_OutboundUnicastHopLimit(System::Byte &__get_OutboundUnicastHopLimit_result) = 0 ;
	virtual HRESULT __safecall put_OutboundUnicastHopLimit(System::Byte value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_OutboundUnicastHopLimit() { System::Byte __r; HRESULT __hr = get_OutboundUnicastHopLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte OutboundUnicastHopLimit = {read=_scw_get_OutboundUnicastHopLimit, write=put_OutboundUnicastHopLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketQualityOfService _scw_get_QualityOfService() { Winapi::Commontypes::SocketQualityOfService __r; HRESULT __hr = get_QualityOfService(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketQualityOfService QualityOfService = {read=_scw_get_QualityOfService, write=put_QualityOfService};
};

__interface  INTERFACE_UUID("{5F1A569A-55FB-48CD-9706-7A974F7B1585}") IDatagramSocketInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LocalAddress(Winapi::Commontypes::_di_IHostName &__get_LocalAddress_result) = 0 ;
	virtual HRESULT __safecall get_LocalPort(HSTRING &__get_LocalPort_result) = 0 ;
	virtual HRESULT __safecall get_RemoteAddress(Winapi::Commontypes::_di_IHostName &__get_RemoteAddress_result) = 0 ;
	virtual HRESULT __safecall get_RemotePort(HSTRING &__get_RemotePort_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_LocalAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_LocalAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName LocalAddress = {read=_scw_get_LocalAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_LocalPort() { HSTRING __r; HRESULT __hr = get_LocalPort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING LocalPort = {read=_scw_get_LocalPort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_RemoteAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_RemoteAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName RemoteAddress = {read=_scw_get_RemoteAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RemotePort() { HSTRING __r; HRESULT __hr = get_RemotePort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RemotePort = {read=_scw_get_RemotePort};
};

__interface  INTERFACE_UUID("{9E2DDCA2-1712-4CE4-B179-8C652C6D107E}") IDatagramSocketMessageReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RemoteAddress(Winapi::Commontypes::_di_IHostName &__get_RemoteAddress_result) = 0 ;
	virtual HRESULT __safecall get_RemotePort(HSTRING &__get_RemotePort_result) = 0 ;
	virtual HRESULT __safecall get_LocalAddress(Winapi::Commontypes::_di_IHostName &__get_LocalAddress_result) = 0 ;
	virtual HRESULT __safecall GetDataReader(Winapi::Storage::Streams::_di_IDataReader &__GetDataReader_result) = 0 ;
	virtual HRESULT __safecall GetDataStream(Winapi::Commontypes::_di_IInputStream &__GetDataStream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_LocalAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_LocalAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName LocalAddress = {read=_scw_get_LocalAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_RemoteAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_RemoteAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName RemoteAddress = {read=_scw_get_RemoteAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RemotePort() { HSTRING __r; HRESULT __hr = get_RemotePort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RemotePort = {read=_scw_get_RemotePort};
};

__interface  INTERFACE_UUID("{4482E19B-2389-5767-9B0B-8D7A8EF55743}") TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{0A89BF8D-AD86-5D61-957C-6E8AC88380B4}") TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs  : public TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IDatagramSocket sender, _di_IDatagramSocketMessageReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{7FE25BBB-C3BC-4677-8446-CA28A465A3AF}") IDatagramSocket  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Control(_di_IDatagramSocketControl &__get_Control_result) = 0 ;
	virtual HRESULT __safecall get_Information(_di_IDatagramSocketInformation &__get_Information_result) = 0 ;
	virtual HRESULT __safecall get_OutputStream(Winapi::Commontypes::_di_IOutputStream &__get_OutputStream_result) = 0 ;
	virtual HRESULT __safecall ConnectAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall ConnectAsync(Winapi::Networking::_di_IEndpointPair endpointPair, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall BindServiceNameAsync(HSTRING localServiceName, Winapi::Commontypes::_di_IAsyncAction &__BindServiceNameAsync_result) = 0 ;
	virtual HRESULT __safecall BindEndpointAsync(Winapi::Commontypes::_di_IHostName localHostName, HSTRING localServiceName, Winapi::Commontypes::_di_IAsyncAction &__BindEndpointAsync_result) = 0 ;
	virtual HRESULT __safecall JoinMulticastGroup(Winapi::Commontypes::_di_IHostName host) = 0 ;
	virtual HRESULT __safecall GetOutputStreamAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Storage::Streams::_di_IAsyncOperation_1__IOutputStream &__GetOutputStreamAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetOutputStreamAsync(Winapi::Networking::_di_IEndpointPair endpointPair, Winapi::Storage::Streams::_di_IAsyncOperation_1__IOutputStream &__GetOutputStreamAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall add_MessageReceived(_di_TypedEventHandler_2__IDatagramSocket__IDatagramSocketMessageReceivedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_MessageReceived_result) = 0 ;
	virtual HRESULT __safecall remove_MessageReceived(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDatagramSocketControl _scw_get_Control() { _di_IDatagramSocketControl __r; HRESULT __hr = get_Control(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDatagramSocketControl Control = {read=_scw_get_Control};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDatagramSocketInformation _scw_get_Information() { _di_IDatagramSocketInformation __r; HRESULT __hr = get_Information(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDatagramSocketInformation Information = {read=_scw_get_Information};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IOutputStream _scw_get_OutputStream() { Winapi::Commontypes::_di_IOutputStream __r; HRESULT __hr = get_OutputStream(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IOutputStream OutputStream = {read=_scw_get_OutputStream};
};

__interface  INTERFACE_UUID("{71B5D99E-3854-5E9A-B4DC-D1B58BF198FC}") AsyncOperationCompletedHandler_1__IStreamSocket_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{A5755FC7-E478-5709-91EB-F4DE6C94B875}") AsyncOperationCompletedHandler_1__IStreamSocket  : public AsyncOperationCompletedHandler_1__IStreamSocket_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IStreamSocket asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{FB3E3D3C-6FE5-5E27-A132-902247E2A93E}") IAsyncOperation_1__IStreamSocket_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{673D41A9-FA65-5D68-A1A0-DC2E97A32F4A}") IAsyncOperation_1__IStreamSocket  : public IAsyncOperation_1__IStreamSocket_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IStreamSocket handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IStreamSocket &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IStreamSocket &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IStreamSocket _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IStreamSocket __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IStreamSocket Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{43B04D64-4C85-4396-A637-1D973F6EBD49}") ISocketActivityContext  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Data(Winapi::Commontypes::_di_IBuffer &__get_Data_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Data() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Data = {read=_scw_get_Data};
};

__interface  INTERFACE_UUID("{478C22AC-4C4B-42ED-9ED7-1EF9F94FA3D5}") IMessageWebSocketMessageReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MessageType(Winapi::Commontypes::SocketMessageType &__get_MessageType_result) = 0 ;
	virtual HRESULT __safecall GetDataReader(Winapi::Storage::Streams::_di_IDataReader &__GetDataReader_result) = 0 ;
	virtual HRESULT __safecall GetDataStream(Winapi::Commontypes::_di_IInputStream &__GetDataStream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketMessageType _scw_get_MessageType() { Winapi::Commontypes::SocketMessageType __r; HRESULT __hr = get_MessageType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketMessageType MessageType = {read=_scw_get_MessageType};
};

__interface  INTERFACE_UUID("{89CE06FD-DD6F-4A07-87F9-F9EB4D89D83D}") IMessageWebSocketMessageReceivedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsMessageComplete(bool &__get_IsMessageComplete_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsMessageComplete() { bool __r; HRESULT __hr = get_IsMessageComplete(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsMessageComplete = {read=_scw_get_IsMessageComplete};
};

__interface  INTERFACE_UUID("{CEB78D07-D0A8-4703-A091-C8C2C0915BC3}") IWebSocketClosedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Code(System::Word &__get_Code_result) = 0 ;
	virtual HRESULT __safecall get_Reason(HSTRING &__get_Reason_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_Code() { System::Word __r; HRESULT __hr = get_Code(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word Code = {read=_scw_get_Code};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Reason() { HSTRING __r; HRESULT __hr = get_Reason(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Reason = {read=_scw_get_Reason};
};

__interface  INTERFACE_UUID("{33EAD5C2-979C-4415-82A1-3CFAF646C192}") IDatagramSocketControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_InboundBufferSizeInBytes(unsigned &__get_InboundBufferSizeInBytes_result) = 0 ;
	virtual HRESULT __safecall put_InboundBufferSizeInBytes(unsigned value) = 0 ;
	virtual HRESULT __safecall get_DontFragment(bool &__get_DontFragment_result) = 0 ;
	virtual HRESULT __safecall put_DontFragment(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_DontFragment() { bool __r; HRESULT __hr = get_DontFragment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool DontFragment = {read=_scw_get_DontFragment, write=put_DontFragment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_InboundBufferSizeInBytes() { unsigned __r; HRESULT __hr = get_InboundBufferSizeInBytes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned InboundBufferSizeInBytes = {read=_scw_get_InboundBufferSizeInBytes, write=put_InboundBufferSizeInBytes};
};

__interface  INTERFACE_UUID("{D4EB8256-1F6D-4598-9B57-D42A001DF349}") IDatagramSocketControl3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MulticastOnly(bool &__get_MulticastOnly_result) = 0 ;
	virtual HRESULT __safecall put_MulticastOnly(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_MulticastOnly() { bool __r; HRESULT __hr = get_MulticastOnly(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool MulticastOnly = {read=_scw_get_MulticastOnly, write=put_MulticastOnly};
};

__interface  INTERFACE_UUID("{E9C62AEE-1494-4A21-BB7E-8589FC751D9D}") IDatagramSocketStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair &__GetEndpointPairsAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::HostNameSortOptions sortOptions, Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair &__GetEndpointPairsAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D83BA354-9A9D-4185-A20A-1424C9C2A7CD}") IDatagramSocket2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall BindServiceNameAsync(HSTRING localServiceName, Winapi::Commontypes::_di_INetworkAdapter adapter, Winapi::Commontypes::_di_IAsyncAction &__BindServiceNameAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{37544F09-AB92-4306-9AC1-0C381283D9C6}") IDatagramSocket3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CancelIOAsync(Winapi::Commontypes::_di_IAsyncAction &__CancelIOAsync_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#else /* _WIN64 */
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#endif /* _WIN64 */
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId) = 0 /* overload */;
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId, _di_ISocketActivityContext data) = 0 /* overload */;
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId, _di_ISocketActivityContext data, Winapi::Commontypes::TimeSpan keepAliveTime) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{12C28452-4BDC-4EE4-976A-CF130E9D92E3}") IStreamSocketInformation2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ServerCertificateErrorSeverity(Winapi::Commontypes::SocketSslErrorSeverity &__get_ServerCertificateErrorSeverity_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificateErrors(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult &__get_ServerCertificateErrors_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ServerCertificate_result) = 0 ;
	virtual HRESULT __safecall get_ServerIntermediateCertificates(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate &__get_ServerIntermediateCertificates_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ServerCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ServerCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ServerCertificate = {read=_scw_get_ServerCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketSslErrorSeverity _scw_get_ServerCertificateErrorSeverity() { Winapi::Commontypes::SocketSslErrorSeverity __r; HRESULT __hr = get_ServerCertificateErrorSeverity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketSslErrorSeverity ServerCertificateErrorSeverity = {read=_scw_get_ServerCertificateErrorSeverity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult _scw_get_ServerCertificateErrors() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_ServerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult ServerCertificateErrors = {read=_scw_get_ServerCertificateErrors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate _scw_get_ServerIntermediateCertificates() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate __r; HRESULT __hr = get_ServerIntermediateCertificates(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate ServerIntermediateCertificates = {read=_scw_get_ServerIntermediateCertificates};
};

__interface  INTERFACE_UUID("{C2D09A56-060F-44C1-B8E2-1FBF60BD62C5}") IStreamSocketControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IgnorableServerCertificateErrors(Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult &__get_IgnorableServerCertificateErrors_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult _scw_get_IgnorableServerCertificateErrors() { Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_IgnorableServerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult IgnorableServerCertificateErrors = {read=_scw_get_IgnorableServerCertificateErrors};
};

__interface  INTERFACE_UUID("{C56A444C-4E74-403E-894C-B31CAE5C7342}") IStreamSocketControl3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SerializeConnectionAttempts(bool &__get_SerializeConnectionAttempts_result) = 0 ;
	virtual HRESULT __safecall put_SerializeConnectionAttempts(bool value) = 0 ;
	virtual HRESULT __safecall get_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ClientCertificate_result) = 0 ;
	virtual HRESULT __safecall put_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ClientCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ClientCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ClientCertificate = {read=_scw_get_ClientCertificate, write=put_ClientCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SerializeConnectionAttempts() { bool __r; HRESULT __hr = get_SerializeConnectionAttempts(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SerializeConnectionAttempts = {read=_scw_get_SerializeConnectionAttempts, write=put_SerializeConnectionAttempts};
};

__interface  INTERFACE_UUID("{964E2B3D-EC27-4888-B3CE-C74B418423AD}") IStreamSocketControl4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MinProtectionLevel(Winapi::Commontypes::SocketProtectionLevel &__get_MinProtectionLevel_result) = 0 ;
	virtual HRESULT __safecall put_MinProtectionLevel(Winapi::Commontypes::SocketProtectionLevel value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketProtectionLevel _scw_get_MinProtectionLevel() { Winapi::Commontypes::SocketProtectionLevel __r; HRESULT __hr = get_MinProtectionLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketProtectionLevel MinProtectionLevel = {read=_scw_get_MinProtectionLevel, write=put_MinProtectionLevel};
};

__interface  INTERFACE_UUID("{29D0E575-F314-4D09-ADF0-0FBD967FBD9F}") IStreamSocket2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ConnectAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_INetworkAdapter adapter, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{3F430B00-9D28-4854-BAC3-2301941EC223}") IStreamSocket3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CancelIOAsync(Winapi::Commontypes::_di_IAsyncAction &__CancelIOAsync_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#else /* _WIN64 */
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#endif /* _WIN64 */
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId) = 0 /* overload */;
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId, _di_ISocketActivityContext data) = 0 /* overload */;
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId, _di_ISocketActivityContext data, Winapi::Commontypes::TimeSpan keepAliveTime) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{A420BC4A-6E2E-4AF5-B556-355AE0CD4F29}") IStreamSocketStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair &__GetEndpointPairsAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::HostNameSortOptions sortOptions, Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair &__GetEndpointPairsAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{948BB665-2C3E-404B-B8B0-8EB249A2B0A1}") IStreamSocketListenerControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NoDelay(bool &__get_NoDelay_result) = 0 ;
	virtual HRESULT __safecall put_NoDelay(bool value) = 0 ;
	virtual HRESULT __safecall get_KeepAlive(bool &__get_KeepAlive_result) = 0 ;
	virtual HRESULT __safecall put_KeepAlive(bool value) = 0 ;
	virtual HRESULT __safecall get_OutboundBufferSizeInBytes(unsigned &__get_OutboundBufferSizeInBytes_result) = 0 ;
	virtual HRESULT __safecall put_OutboundBufferSizeInBytes(unsigned value) = 0 ;
	virtual HRESULT __safecall get_OutboundUnicastHopLimit(System::Byte &__get_OutboundUnicastHopLimit_result) = 0 ;
	virtual HRESULT __safecall put_OutboundUnicastHopLimit(System::Byte value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_KeepAlive() { bool __r; HRESULT __hr = get_KeepAlive(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool KeepAlive = {read=_scw_get_KeepAlive, write=put_KeepAlive};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_NoDelay() { bool __r; HRESULT __hr = get_NoDelay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool NoDelay = {read=_scw_get_NoDelay, write=put_NoDelay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_OutboundBufferSizeInBytes() { unsigned __r; HRESULT __hr = get_OutboundBufferSizeInBytes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned OutboundBufferSizeInBytes = {read=_scw_get_OutboundBufferSizeInBytes, write=put_OutboundBufferSizeInBytes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_OutboundUnicastHopLimit() { System::Byte __r; HRESULT __hr = get_OutboundUnicastHopLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte OutboundUnicastHopLimit = {read=_scw_get_OutboundUnicastHopLimit, write=put_OutboundUnicastHopLimit};
};

__interface  INTERFACE_UUID("{658DC13E-BB3E-4458-B232-ED1088694B98}") IStreamSocketListener2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall BindServiceNameAsync(HSTRING localServiceName, Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_IAsyncAction &__BindServiceNameAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall BindServiceNameAsync(HSTRING localServiceName, Winapi::Commontypes::SocketProtectionLevel protectionLevel, Winapi::Commontypes::_di_INetworkAdapter adapter, Winapi::Commontypes::_di_IAsyncAction &__BindServiceNameAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4798201C-BDF8-4919-8542-28D450E74507}") IStreamSocketListener3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CancelIOAsync(Winapi::Commontypes::_di_IAsyncAction &__CancelIOAsync_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(GUID taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#else /* _WIN64 */
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId) = 0 /* overload */;
	virtual HRESULT __safecall EnableTransferOwnership(const GUID &taskId, Winapi::Commontypes::SocketActivityConnectedStandbyAction connectedStandbyAction) = 0 /* overload */;
#endif /* _WIN64 */
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId) = 0 /* overload */;
	virtual HRESULT __safecall TransferOwnership(HSTRING socketId, _di_ISocketActivityContext data) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{FFEFFE48-022A-4AB7-8B36-E10AF4640E6B}") IWebSocketServerCustomValidationRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ServerCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ServerCertificate_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificateErrorSeverity(Winapi::Commontypes::SocketSslErrorSeverity &__get_ServerCertificateErrorSeverity_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificateErrors(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult &__get_ServerCertificateErrors_result) = 0 ;
	virtual HRESULT __safecall get_ServerIntermediateCertificates(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate &__get_ServerIntermediateCertificates_result) = 0 ;
	virtual HRESULT __safecall Reject() = 0 ;
	virtual HRESULT __safecall GetDeferral(Winapi::Commontypes::_di_IDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ServerCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ServerCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ServerCertificate = {read=_scw_get_ServerCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketSslErrorSeverity _scw_get_ServerCertificateErrorSeverity() { Winapi::Commontypes::SocketSslErrorSeverity __r; HRESULT __hr = get_ServerCertificateErrorSeverity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketSslErrorSeverity ServerCertificateErrorSeverity = {read=_scw_get_ServerCertificateErrorSeverity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult _scw_get_ServerCertificateErrors() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_ServerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult ServerCertificateErrors = {read=_scw_get_ServerCertificateErrors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate _scw_get_ServerIntermediateCertificates() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate __r; HRESULT __hr = get_ServerIntermediateCertificates(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate ServerIntermediateCertificates = {read=_scw_get_ServerIntermediateCertificates};
};

__interface  INTERFACE_UUID("{2EC4BDC3-D9A5-455A-9811-DE24D45337E9}") IWebSocketControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_OutboundBufferSizeInBytes(unsigned &__get_OutboundBufferSizeInBytes_result) = 0 ;
	virtual HRESULT __safecall put_OutboundBufferSizeInBytes(unsigned value) = 0 ;
	virtual HRESULT __safecall get_ServerCredential(Winapi::Security::Credentials::_di_IPasswordCredential &__get_ServerCredential_result) = 0 ;
	virtual HRESULT __safecall put_ServerCredential(Winapi::Security::Credentials::_di_IPasswordCredential value) = 0 ;
	virtual HRESULT __safecall get_ProxyCredential(Winapi::Security::Credentials::_di_IPasswordCredential &__get_ProxyCredential_result) = 0 ;
	virtual HRESULT __safecall put_ProxyCredential(Winapi::Security::Credentials::_di_IPasswordCredential value) = 0 ;
	virtual HRESULT __safecall get_SupportedProtocols(Winapi::Networking::_di_IVector_1__HSTRING &__get_SupportedProtocols_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_OutboundBufferSizeInBytes() { unsigned __r; HRESULT __hr = get_OutboundBufferSizeInBytes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned OutboundBufferSizeInBytes = {read=_scw_get_OutboundBufferSizeInBytes, write=put_OutboundBufferSizeInBytes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IPasswordCredential _scw_get_ProxyCredential() { Winapi::Security::Credentials::_di_IPasswordCredential __r; HRESULT __hr = get_ProxyCredential(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IPasswordCredential ProxyCredential = {read=_scw_get_ProxyCredential, write=put_ProxyCredential};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IPasswordCredential _scw_get_ServerCredential() { Winapi::Security::Credentials::_di_IPasswordCredential __r; HRESULT __hr = get_ServerCredential(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IPasswordCredential ServerCredential = {read=_scw_get_ServerCredential, write=put_ServerCredential};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IVector_1__HSTRING _scw_get_SupportedProtocols() { Winapi::Networking::_di_IVector_1__HSTRING __r; HRESULT __hr = get_SupportedProtocols(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IVector_1__HSTRING SupportedProtocols = {read=_scw_get_SupportedProtocols};
};

__interface  INTERFACE_UUID("{79C3BE03-F2CA-461E-AF4E-9665BC2D0620}") IWebSocketControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IgnorableServerCertificateErrors(Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult &__get_IgnorableServerCertificateErrors_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult _scw_get_IgnorableServerCertificateErrors() { Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_IgnorableServerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVector_1__Certificates_ChainValidationResult IgnorableServerCertificateErrors = {read=_scw_get_IgnorableServerCertificateErrors};
};

__interface  INTERFACE_UUID("{5E01E316-C92A-47A5-B25F-07847639D181}") IWebSocketInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_LocalAddress(Winapi::Commontypes::_di_IHostName &__get_LocalAddress_result) = 0 ;
	virtual HRESULT __safecall get_BandwidthStatistics(Winapi::Commontypes::BandwidthStatistics &__get_BandwidthStatistics_result) = 0 ;
	virtual HRESULT __safecall get_Protocol(HSTRING &__get_Protocol_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::BandwidthStatistics _scw_get_BandwidthStatistics() { Winapi::Commontypes::BandwidthStatistics __r; HRESULT __hr = get_BandwidthStatistics(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::BandwidthStatistics BandwidthStatistics = {read=_scw_get_BandwidthStatistics};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_LocalAddress() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_LocalAddress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName LocalAddress = {read=_scw_get_LocalAddress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Protocol() { HSTRING __r; HRESULT __hr = get_Protocol(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Protocol = {read=_scw_get_Protocol};
};

__interface  INTERFACE_UUID("{CE1D39CE-A1B7-4D43-8269-8D5B981BD47A}") IWebSocketInformation2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ServerCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ServerCertificate_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificateErrorSeverity(Winapi::Commontypes::SocketSslErrorSeverity &__get_ServerCertificateErrorSeverity_result) = 0 ;
	virtual HRESULT __safecall get_ServerCertificateErrors(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult &__get_ServerCertificateErrors_result) = 0 ;
	virtual HRESULT __safecall get_ServerIntermediateCertificates(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate &__get_ServerIntermediateCertificates_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ServerCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ServerCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ServerCertificate = {read=_scw_get_ServerCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketSslErrorSeverity _scw_get_ServerCertificateErrorSeverity() { Winapi::Commontypes::SocketSslErrorSeverity __r; HRESULT __hr = get_ServerCertificateErrorSeverity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketSslErrorSeverity ServerCertificateErrorSeverity = {read=_scw_get_ServerCertificateErrorSeverity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult _scw_get_ServerCertificateErrors() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_ServerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult ServerCertificateErrors = {read=_scw_get_ServerCertificateErrors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate _scw_get_ServerIntermediateCertificates() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate __r; HRESULT __hr = get_ServerIntermediateCertificates(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate ServerIntermediateCertificates = {read=_scw_get_ServerIntermediateCertificates};
};

__interface  INTERFACE_UUID("{03CF8F90-1669-5F4D-9404-2B784678E6DD}") TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{90FF48E9-4B0F-595B-A91E-E6669261220C}") TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs  : public TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IWebSocket sender, _di_IWebSocketClosedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{F877396F-99B1-4E18-BC08-850C9ADF156E}") IWebSocket  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_OutputStream(Winapi::Commontypes::_di_IOutputStream &__get_OutputStream_result) = 0 ;
	virtual HRESULT __safecall ConnectAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri, Winapi::Commontypes::_di_IAsyncAction &__ConnectAsync_result) = 0 ;
	virtual HRESULT __safecall SetRequestHeader(HSTRING headerName, HSTRING headerValue) = 0 ;
	virtual HRESULT __safecall add_Closed(_di_TypedEventHandler_2__IWebSocket__IWebSocketClosedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_Closed_result) = 0 ;
	virtual HRESULT __safecall remove_Closed(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	virtual HRESULT __safecall Close(System::Word code, HSTRING reason) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IOutputStream _scw_get_OutputStream() { Winapi::Commontypes::_di_IOutputStream __r; HRESULT __hr = get_OutputStream(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IOutputStream OutputStream = {read=_scw_get_OutputStream};
};

__interface  INTERFACE_UUID("{8118388A-C629-4F0A-80FB-81FC05538862}") IMessageWebSocketControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MaxMessageSize(unsigned &__get_MaxMessageSize_result) = 0 ;
	virtual HRESULT __safecall put_MaxMessageSize(unsigned value) = 0 ;
	virtual HRESULT __safecall get_MessageType(Winapi::Commontypes::SocketMessageType &__get_MessageType_result) = 0 ;
	virtual HRESULT __safecall put_MessageType(Winapi::Commontypes::SocketMessageType value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxMessageSize() { unsigned __r; HRESULT __hr = get_MaxMessageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxMessageSize = {read=_scw_get_MaxMessageSize, write=put_MaxMessageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketMessageType _scw_get_MessageType() { Winapi::Commontypes::SocketMessageType __r; HRESULT __hr = get_MessageType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketMessageType MessageType = {read=_scw_get_MessageType, write=put_MessageType};
};

__interface  INTERFACE_UUID("{E30FD791-080C-400A-A712-27DFA9E744D8}") IMessageWebSocketControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DesiredUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan &__get_DesiredUnsolicitedPongInterval_result) = 0 ;
	virtual HRESULT __safecall put_DesiredUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall get_ActualUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan &__get_ActualUnsolicitedPongInterval_result) = 0 ;
	virtual HRESULT __safecall get_ReceiveMode(Winapi::Commontypes::MessageWebSocketReceiveMode &__get_ReceiveMode_result) = 0 ;
	virtual HRESULT __safecall put_ReceiveMode(Winapi::Commontypes::MessageWebSocketReceiveMode value) = 0 ;
	virtual HRESULT __safecall get_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ClientCertificate_result) = 0 ;
	virtual HRESULT __safecall put_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_ActualUnsolicitedPongInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_ActualUnsolicitedPongInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan ActualUnsolicitedPongInterval = {read=_scw_get_ActualUnsolicitedPongInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ClientCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ClientCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ClientCertificate = {read=_scw_get_ClientCertificate, write=put_ClientCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_DesiredUnsolicitedPongInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_DesiredUnsolicitedPongInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan DesiredUnsolicitedPongInterval = {read=_scw_get_DesiredUnsolicitedPongInterval, write=put_DesiredUnsolicitedPongInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MessageWebSocketReceiveMode _scw_get_ReceiveMode() { Winapi::Commontypes::MessageWebSocketReceiveMode __r; HRESULT __hr = get_ReceiveMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MessageWebSocketReceiveMode ReceiveMode = {read=_scw_get_ReceiveMode, write=put_ReceiveMode};
};

__interface  INTERFACE_UUID("{DE980538-6DCD-52B0-802F-4B6CF59A01AB}") TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4648E17B-49F1-5F4F-ADCE-761EC022B556}") TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs  : public TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IMessageWebSocket sender, _di_IMessageWebSocketMessageReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{33727D08-34D5-4746-AD7B-8DDE5BC2EF88}") IMessageWebSocket  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Control(_di_IMessageWebSocketControl &__get_Control_result) = 0 ;
	virtual HRESULT __safecall get_Information(_di_IWebSocketInformation &__get_Information_result) = 0 ;
	virtual HRESULT __safecall add_MessageReceived(_di_TypedEventHandler_2__IMessageWebSocket__IMessageWebSocketMessageReceivedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_MessageReceived_result) = 0 ;
	virtual HRESULT __safecall remove_MessageReceived(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMessageWebSocketControl _scw_get_Control() { _di_IMessageWebSocketControl __r; HRESULT __hr = get_Control(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMessageWebSocketControl Control = {read=_scw_get_Control};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWebSocketInformation _scw_get_Information() { _di_IWebSocketInformation __r; HRESULT __hr = get_Information(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWebSocketInformation Information = {read=_scw_get_Information};
};

__interface  INTERFACE_UUID("{2C34C585-9CF6-56C7-8DD1-5DA26E322078}") TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{BCDA6FC2-B686-54FF-81E8-235E7421473B}") TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs  : public TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IMessageWebSocket sender, _di_IWebSocketServerCustomValidationRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{BED0CEE7-F9C8-440A-9AD5-737281D9742E}") IMessageWebSocket2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ServerCustomValidationRequested(_di_TypedEventHandler_2__IMessageWebSocket__IWebSocketServerCustomValidationRequestedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_ServerCustomValidationRequested_result) = 0 ;
	virtual HRESULT __safecall remove_ServerCustomValidationRequested(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
};

__interface  INTERFACE_UUID("{B4F478B1-A45A-48DB-953A-645B7D964C07}") IStreamWebSocketControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NoDelay(bool &__get_NoDelay_result) = 0 ;
	virtual HRESULT __safecall put_NoDelay(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_NoDelay() { bool __r; HRESULT __hr = get_NoDelay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool NoDelay = {read=_scw_get_NoDelay, write=put_NoDelay};
};

__interface  INTERFACE_UUID("{215D9F7E-FA58-40DA-9F11-A48DAFE95037}") IStreamWebSocketControl2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DesiredUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan &__get_DesiredUnsolicitedPongInterval_result) = 0 ;
	virtual HRESULT __safecall put_DesiredUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall get_ActualUnsolicitedPongInterval(Winapi::Commontypes::TimeSpan &__get_ActualUnsolicitedPongInterval_result) = 0 ;
	virtual HRESULT __safecall get_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_ClientCertificate_result) = 0 ;
	virtual HRESULT __safecall put_ClientCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_ActualUnsolicitedPongInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_ActualUnsolicitedPongInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan ActualUnsolicitedPongInterval = {read=_scw_get_ActualUnsolicitedPongInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_ClientCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_ClientCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate ClientCertificate = {read=_scw_get_ClientCertificate, write=put_ClientCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_DesiredUnsolicitedPongInterval() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_DesiredUnsolicitedPongInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan DesiredUnsolicitedPongInterval = {read=_scw_get_DesiredUnsolicitedPongInterval, write=put_DesiredUnsolicitedPongInterval};
};

__interface  INTERFACE_UUID("{BD4A49D8-B289-45BB-97EB-C7525205A843}") IStreamWebSocket  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Control(_di_IStreamWebSocketControl &__get_Control_result) = 0 ;
	virtual HRESULT __safecall get_Information(_di_IWebSocketInformation &__get_Information_result) = 0 ;
	virtual HRESULT __safecall get_InputStream(Winapi::Commontypes::_di_IInputStream &__get_InputStream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IStreamWebSocketControl _scw_get_Control() { _di_IStreamWebSocketControl __r; HRESULT __hr = get_Control(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IStreamWebSocketControl Control = {read=_scw_get_Control};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWebSocketInformation _scw_get_Information() { _di_IWebSocketInformation __r; HRESULT __hr = get_Information(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWebSocketInformation Information = {read=_scw_get_Information};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInputStream _scw_get_InputStream() { Winapi::Commontypes::_di_IInputStream __r; HRESULT __hr = get_InputStream(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInputStream InputStream = {read=_scw_get_InputStream};
};

__interface  INTERFACE_UUID("{18B143D3-897E-595E-ACC1-EF35614B4CEC}") TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E56170FE-9025-5791-9FD9-BC68D49563E1}") TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs  : public TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IStreamWebSocket sender, _di_IWebSocketServerCustomValidationRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{AA4D08CB-93F5-4678-8236-57CCE5417ED5}") IStreamWebSocket2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ServerCustomValidationRequested(_di_TypedEventHandler_2__IStreamWebSocket__IWebSocketServerCustomValidationRequestedEventArgs eventHandler, Winapi::Commontypes::EventRegistrationToken &__add_ServerCustomValidationRequested_result) = 0 ;
	virtual HRESULT __safecall remove_ServerCustomValidationRequested(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
};

__interface  INTERFACE_UUID("{828337F4-7D56-4D8E-B7B4-A07DD7C1BCA9}") ISocketErrorStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetStatus(int hresult, Winapi::Commontypes::SocketErrorStatus &__GetStatus_result) = 0 ;
};

__interface  INTERFACE_UUID("{27CDF35B-1F61-4709-8E02-61283ADA4E9D}") IWebSocketErrorStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetStatus(int hresult, Winapi::Commontypes::WebErrorStatus &__GetStatus_result) = 0 ;
};

__interface  INTERFACE_UUID("{6851038E-8EC4-42FE-9BB2-21E91B7BFCB1}") IControlChannelTriggerResetEventDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ResetReason(Winapi::Commontypes::ControlChannelTriggerResetReason &__get_ResetReason_result) = 0 ;
	virtual HRESULT __safecall get_HardwareSlotReset(bool &__get_HardwareSlotReset_result) = 0 ;
	virtual HRESULT __safecall get_SoftwareSlotReset(bool &__get_SoftwareSlotReset_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HardwareSlotReset() { bool __r; HRESULT __hr = get_HardwareSlotReset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HardwareSlotReset = {read=_scw_get_HardwareSlotReset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ControlChannelTriggerResetReason _scw_get_ResetReason() { Winapi::Commontypes::ControlChannelTriggerResetReason __r; HRESULT __hr = get_ResetReason(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ControlChannelTriggerResetReason ResetReason = {read=_scw_get_ResetReason};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SoftwareSlotReset() { bool __r; HRESULT __hr = get_SoftwareSlotReset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SoftwareSlotReset = {read=_scw_get_SoftwareSlotReset};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDatagramSocket : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_IDatagramSocketStatics,_di_IDatagramSocket>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_IDatagramSocketStatics,_di_IDatagramSocket> inherited;
	
public:
	static Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair __fastcall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName)/* overload */;
	static Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair __fastcall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::HostNameSortOptions sortOptions)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDatagramSocket() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_IDatagramSocketStatics,_di_IDatagramSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDatagramSocket() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStreamSocket : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_IStreamSocketStatics,_di_IStreamSocket>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_IStreamSocketStatics,_di_IStreamSocket> inherited;
	
public:
	static Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair __fastcall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName)/* overload */;
	static Winapi::Networking::_di_IAsyncOperation_1__IVectorView_1__IEndpointPair __fastcall GetEndpointPairsAsync(Winapi::Commontypes::_di_IHostName remoteHostName, HSTRING remoteServiceName, Winapi::Commontypes::HostNameSortOptions sortOptions)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TStreamSocket() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_IStreamSocketStatics,_di_IStreamSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStreamSocket() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStreamSocketListener : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamSocketListener>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamSocketListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TStreamSocketListener() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamSocketListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStreamSocketListener() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMessageWebSocket : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMessageWebSocket>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMessageWebSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMessageWebSocket() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMessageWebSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMessageWebSocket() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStreamWebSocket : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamWebSocket>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamWebSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TStreamWebSocket() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IStreamWebSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStreamWebSocket() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSocketError : public System::Win::Winrt::TWinRTGenericImportS__1<_di_ISocketErrorStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_ISocketErrorStatics> inherited;
	
public:
	static Winapi::Commontypes::SocketErrorStatus __fastcall GetStatus(int hresult);
public:
	/* TObject.Create */ inline __fastcall TSocketError() : System::Win::Winrt::TWinRTGenericImportS__1<_di_ISocketErrorStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSocketError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebSocketError : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IWebSocketErrorStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IWebSocketErrorStatics> inherited;
	
public:
	static Winapi::Commontypes::WebErrorStatus __fastcall GetStatus(int hresult);
public:
	/* TObject.Create */ inline __fastcall TWebSocketError() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IWebSocketErrorStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWebSocketError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sockets */
}	/* namespace Networking */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Networking_SocketsHPP
