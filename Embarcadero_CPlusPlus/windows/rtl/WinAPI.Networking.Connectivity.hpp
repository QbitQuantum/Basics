// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Networking.Connectivity.pas' rev: 34.00 (Windows)

#ifndef Winapi_Networking_ConnectivityHPP
#define Winapi_Networking_ConnectivityHPP

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
#include <Winapi.Foundation.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Networking
{
namespace Connectivity
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IConnectionCost2;
typedef System::DelphiInterface<IConnectionCost2> _di_IConnectionCost2;
__interface DELPHIINTERFACE IWlanConnectionProfileDetails;
typedef System::DelphiInterface<IWlanConnectionProfileDetails> _di_IWlanConnectionProfileDetails;
__interface DELPHIINTERFACE IConnectivityInterval;
typedef System::DelphiInterface<IConnectivityInterval> _di_IConnectivityInterval;
__interface DELPHIINTERFACE INetworkUsage;
typedef System::DelphiInterface<INetworkUsage> _di_INetworkUsage;
__interface DELPHIINTERFACE IAttributedNetworkUsage;
typedef System::DelphiInterface<IAttributedNetworkUsage> _di_IAttributedNetworkUsage;
__interface DELPHIINTERFACE IProviderNetworkUsage;
typedef System::DelphiInterface<IProviderNetworkUsage> _di_IProviderNetworkUsage;
__interface DELPHIINTERFACE IWwanConnectionProfileDetails;
typedef System::DelphiInterface<IWwanConnectionProfileDetails> _di_IWwanConnectionProfileDetails;
__interface DELPHIINTERFACE IIterator_1__INetworkUsage_Base;
typedef System::DelphiInterface<IIterator_1__INetworkUsage_Base> _di_IIterator_1__INetworkUsage_Base;
__interface DELPHIINTERFACE IIterator_1__INetworkUsage;
typedef System::DelphiInterface<IIterator_1__INetworkUsage> _di_IIterator_1__INetworkUsage;
__interface DELPHIINTERFACE IIterable_1__INetworkUsage_Base;
typedef System::DelphiInterface<IIterable_1__INetworkUsage_Base> _di_IIterable_1__INetworkUsage_Base;
__interface DELPHIINTERFACE IIterable_1__INetworkUsage;
typedef System::DelphiInterface<IIterable_1__INetworkUsage> _di_IIterable_1__INetworkUsage;
__interface DELPHIINTERFACE IVectorView_1__INetworkUsage;
typedef System::DelphiInterface<IVectorView_1__INetworkUsage> _di_IVectorView_1__INetworkUsage;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage> _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__INetworkUsage_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__INetworkUsage_Base> _di_IAsyncOperation_1__IVectorView_1__INetworkUsage_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__INetworkUsage;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__INetworkUsage> _di_IAsyncOperation_1__IVectorView_1__INetworkUsage;
__interface DELPHIINTERFACE IIterator_1__IConnectivityInterval_Base;
typedef System::DelphiInterface<IIterator_1__IConnectivityInterval_Base> _di_IIterator_1__IConnectivityInterval_Base;
__interface DELPHIINTERFACE IIterator_1__IConnectivityInterval;
typedef System::DelphiInterface<IIterator_1__IConnectivityInterval> _di_IIterator_1__IConnectivityInterval;
__interface DELPHIINTERFACE IIterable_1__IConnectivityInterval_Base;
typedef System::DelphiInterface<IIterable_1__IConnectivityInterval_Base> _di_IIterable_1__IConnectivityInterval_Base;
__interface DELPHIINTERFACE IIterable_1__IConnectivityInterval;
typedef System::DelphiInterface<IIterable_1__IConnectivityInterval> _di_IIterable_1__IConnectivityInterval;
__interface DELPHIINTERFACE IVectorView_1__IConnectivityInterval;
typedef System::DelphiInterface<IVectorView_1__IConnectivityInterval> _di_IVectorView_1__IConnectivityInterval;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IConnectivityInterval_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IConnectivityInterval_Base> _di_IAsyncOperation_1__IVectorView_1__IConnectivityInterval_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IConnectivityInterval;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IConnectivityInterval> _di_IAsyncOperation_1__IVectorView_1__IConnectivityInterval;
__interface DELPHIINTERFACE IConnectionProfile2;
typedef System::DelphiInterface<IConnectionProfile2> _di_IConnectionProfile2;
__interface DELPHIINTERFACE IIterator_1__IAttributedNetworkUsage_Base;
typedef System::DelphiInterface<IIterator_1__IAttributedNetworkUsage_Base> _di_IIterator_1__IAttributedNetworkUsage_Base;
__interface DELPHIINTERFACE IIterator_1__IAttributedNetworkUsage;
typedef System::DelphiInterface<IIterator_1__IAttributedNetworkUsage> _di_IIterator_1__IAttributedNetworkUsage;
__interface DELPHIINTERFACE IIterable_1__IAttributedNetworkUsage_Base;
typedef System::DelphiInterface<IIterable_1__IAttributedNetworkUsage_Base> _di_IIterable_1__IAttributedNetworkUsage_Base;
__interface DELPHIINTERFACE IIterable_1__IAttributedNetworkUsage;
typedef System::DelphiInterface<IIterable_1__IAttributedNetworkUsage> _di_IIterable_1__IAttributedNetworkUsage;
__interface DELPHIINTERFACE IVectorView_1__IAttributedNetworkUsage;
typedef System::DelphiInterface<IVectorView_1__IAttributedNetworkUsage> _di_IVectorView_1__IAttributedNetworkUsage;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage_Base> _di_IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage> _di_IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage;
__interface DELPHIINTERFACE IConnectionProfile3;
typedef System::DelphiInterface<IConnectionProfile3> _di_IConnectionProfile3;
__interface DELPHIINTERFACE IIterator_1__IProviderNetworkUsage_Base;
typedef System::DelphiInterface<IIterator_1__IProviderNetworkUsage_Base> _di_IIterator_1__IProviderNetworkUsage_Base;
__interface DELPHIINTERFACE IIterator_1__IProviderNetworkUsage;
typedef System::DelphiInterface<IIterator_1__IProviderNetworkUsage> _di_IIterator_1__IProviderNetworkUsage;
__interface DELPHIINTERFACE IIterable_1__IProviderNetworkUsage_Base;
typedef System::DelphiInterface<IIterable_1__IProviderNetworkUsage_Base> _di_IIterable_1__IProviderNetworkUsage_Base;
__interface DELPHIINTERFACE IIterable_1__IProviderNetworkUsage;
typedef System::DelphiInterface<IIterable_1__IProviderNetworkUsage> _di_IIterable_1__IProviderNetworkUsage;
__interface DELPHIINTERFACE IVectorView_1__IProviderNetworkUsage;
typedef System::DelphiInterface<IVectorView_1__IProviderNetworkUsage> _di_IVectorView_1__IProviderNetworkUsage;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage_Base> _di_IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage> _di_IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage;
__interface DELPHIINTERFACE IConnectionProfile4;
typedef System::DelphiInterface<IConnectionProfile4> _di_IConnectionProfile4;
__interface DELPHIINTERFACE ILanIdentifierData;
typedef System::DelphiInterface<ILanIdentifierData> _di_ILanIdentifierData;
__interface DELPHIINTERFACE ILanIdentifier;
typedef System::DelphiInterface<ILanIdentifier> _di_ILanIdentifier;
__interface DELPHIINTERFACE NetworkStatusChangedEventHandler;
typedef System::DelphiInterface<NetworkStatusChangedEventHandler> _di_NetworkStatusChangedEventHandler;
__interface DELPHIINTERFACE IIterator_1__IConnectionProfile_Base;
typedef System::DelphiInterface<IIterator_1__IConnectionProfile_Base> _di_IIterator_1__IConnectionProfile_Base;
__interface DELPHIINTERFACE IIterator_1__IConnectionProfile;
typedef System::DelphiInterface<IIterator_1__IConnectionProfile> _di_IIterator_1__IConnectionProfile;
__interface DELPHIINTERFACE IIterable_1__IConnectionProfile_Base;
typedef System::DelphiInterface<IIterable_1__IConnectionProfile_Base> _di_IIterable_1__IConnectionProfile_Base;
__interface DELPHIINTERFACE IIterable_1__IConnectionProfile;
typedef System::DelphiInterface<IIterable_1__IConnectionProfile> _di_IIterable_1__IConnectionProfile;
__interface DELPHIINTERFACE IVectorView_1__IConnectionProfile;
typedef System::DelphiInterface<IVectorView_1__IConnectionProfile> _di_IVectorView_1__IConnectionProfile;
__interface DELPHIINTERFACE IIterator_1__ILanIdentifier_Base;
typedef System::DelphiInterface<IIterator_1__ILanIdentifier_Base> _di_IIterator_1__ILanIdentifier_Base;
__interface DELPHIINTERFACE IIterator_1__ILanIdentifier;
typedef System::DelphiInterface<IIterator_1__ILanIdentifier> _di_IIterator_1__ILanIdentifier;
__interface DELPHIINTERFACE IIterable_1__ILanIdentifier_Base;
typedef System::DelphiInterface<IIterable_1__ILanIdentifier_Base> _di_IIterable_1__ILanIdentifier_Base;
__interface DELPHIINTERFACE IIterable_1__ILanIdentifier;
typedef System::DelphiInterface<IIterable_1__ILanIdentifier> _di_IIterable_1__ILanIdentifier;
__interface DELPHIINTERFACE IVectorView_1__ILanIdentifier;
typedef System::DelphiInterface<IVectorView_1__ILanIdentifier> _di_IVectorView_1__ILanIdentifier;
__interface DELPHIINTERFACE IProxyConfiguration;
typedef System::DelphiInterface<IProxyConfiguration> _di_IProxyConfiguration;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IProxyConfiguration_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IProxyConfiguration_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IProxyConfiguration_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IProxyConfiguration;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IProxyConfiguration> _di_AsyncOperationCompletedHandler_1__IProxyConfiguration;
__interface DELPHIINTERFACE IAsyncOperation_1__IProxyConfiguration_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IProxyConfiguration_Base> _di_IAsyncOperation_1__IProxyConfiguration_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IProxyConfiguration;
typedef System::DelphiInterface<IAsyncOperation_1__IProxyConfiguration> _di_IAsyncOperation_1__IProxyConfiguration;
__interface DELPHIINTERFACE INetworkInformationStatics;
typedef System::DelphiInterface<INetworkInformationStatics> _di_INetworkInformationStatics;
__interface DELPHIINTERFACE IConnectionProfileFilter;
typedef System::DelphiInterface<IConnectionProfileFilter> _di_IConnectionProfileFilter;
__interface DELPHIINTERFACE IConnectionProfileFilter2;
typedef System::DelphiInterface<IConnectionProfileFilter2> _di_IConnectionProfileFilter2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IConnectionProfile_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IConnectionProfile_Base> _di_IAsyncOperation_1__IVectorView_1__IConnectionProfile_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IConnectionProfile;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IConnectionProfile> _di_IAsyncOperation_1__IVectorView_1__IConnectionProfile;
__interface DELPHIINTERFACE INetworkInformationStatics2;
typedef System::DelphiInterface<INetworkInformationStatics2> _di_INetworkInformationStatics2;
__interface DELPHIINTERFACE IConnectionSession;
typedef System::DelphiInterface<IConnectionSession> _di_IConnectionSession;
__interface DELPHIINTERFACE IRoutePolicy;
typedef System::DelphiInterface<IRoutePolicy> _di_IRoutePolicy;
__interface DELPHIINTERFACE IRoutePolicyFactory;
typedef System::DelphiInterface<IRoutePolicyFactory> _di_IRoutePolicyFactory;
__interface DELPHIINTERFACE ICellularApnContext;
typedef System::DelphiInterface<ICellularApnContext> _di_ICellularApnContext;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IConnectionSession_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IConnectionSession_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IConnectionSession_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IConnectionSession;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IConnectionSession> _di_AsyncOperationCompletedHandler_1__IConnectionSession;
__interface DELPHIINTERFACE IAsyncOperation_1__IConnectionSession_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IConnectionSession_Base> _di_IAsyncOperation_1__IConnectionSession_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IConnectionSession;
typedef System::DelphiInterface<IAsyncOperation_1__IConnectionSession> _di_IAsyncOperation_1__IConnectionSession;
__interface DELPHIINTERFACE IConnectivityManagerStatics;
typedef System::DelphiInterface<IConnectivityManagerStatics> _di_IConnectivityManagerStatics;
__interface DELPHIINTERFACE INetworkStateChangeEventDetails;
typedef System::DelphiInterface<INetworkStateChangeEventDetails> _di_INetworkStateChangeEventDetails;
__interface DELPHIINTERFACE INetworkStateChangeEventDetails2;
typedef System::DelphiInterface<INetworkStateChangeEventDetails2> _di_INetworkStateChangeEventDetails2;
class DELPHICLASS TConnectionProfileFilter;
class DELPHICLASS TRoutePolicy;
class DELPHICLASS TCellularApnContext;
class DELPHICLASS TNetworkInformation;
class DELPHICLASS TConnectivityManager;
//-- type declarations -------------------------------------------------------
typedef _di_IConnectionCost2 *PIConnectionCost2;

typedef _di_IWlanConnectionProfileDetails *PIWlanConnectionProfileDetails;

typedef _di_IConnectivityInterval *PIConnectivityInterval;

typedef _di_INetworkUsage *PINetworkUsage;

typedef _di_IAttributedNetworkUsage *PIAttributedNetworkUsage;

typedef _di_IProviderNetworkUsage *PIProviderNetworkUsage;

typedef _di_IWwanConnectionProfileDetails *PIWwanConnectionProfileDetails;

typedef _di_IIterator_1__INetworkUsage *PIIterator_1__INetworkUsage;

typedef _di_IIterable_1__INetworkUsage *PIIterable_1__INetworkUsage;

typedef _di_IVectorView_1__INetworkUsage *PIVectorView_1__INetworkUsage;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage *PAsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage;

typedef _di_IAsyncOperation_1__IVectorView_1__INetworkUsage *PIAsyncOperation_1__IVectorView_1__INetworkUsage;

typedef _di_IIterator_1__IConnectivityInterval *PIIterator_1__IConnectivityInterval;

typedef _di_IIterable_1__IConnectivityInterval *PIIterable_1__IConnectivityInterval;

typedef _di_IVectorView_1__IConnectivityInterval *PIVectorView_1__IConnectivityInterval;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval *PAsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval;

typedef _di_IAsyncOperation_1__IVectorView_1__IConnectivityInterval *PIAsyncOperation_1__IVectorView_1__IConnectivityInterval;

typedef _di_IConnectionProfile2 *PIConnectionProfile2;

typedef _di_IIterator_1__IAttributedNetworkUsage *PIIterator_1__IAttributedNetworkUsage;

typedef _di_IIterable_1__IAttributedNetworkUsage *PIIterable_1__IAttributedNetworkUsage;

typedef _di_IVectorView_1__IAttributedNetworkUsage *PIVectorView_1__IAttributedNetworkUsage;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage *PAsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage;

typedef _di_IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage *PIAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage;

typedef _di_IConnectionProfile3 *PIConnectionProfile3;

typedef _di_IIterator_1__IProviderNetworkUsage *PIIterator_1__IProviderNetworkUsage;

typedef _di_IIterable_1__IProviderNetworkUsage *PIIterable_1__IProviderNetworkUsage;

typedef _di_IVectorView_1__IProviderNetworkUsage *PIVectorView_1__IProviderNetworkUsage;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage *PAsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage;

typedef _di_IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage *PIAsyncOperation_1__IVectorView_1__IProviderNetworkUsage;

typedef _di_IConnectionProfile4 *PIConnectionProfile4;

typedef _di_ILanIdentifierData *PILanIdentifierData;

typedef _di_ILanIdentifier *PILanIdentifier;

typedef _di_NetworkStatusChangedEventHandler *PNetworkStatusChangedEventHandler;

typedef _di_IIterator_1__IConnectionProfile *PIIterator_1__IConnectionProfile;

typedef _di_IIterable_1__IConnectionProfile *PIIterable_1__IConnectionProfile;

typedef _di_IVectorView_1__IConnectionProfile *PIVectorView_1__IConnectionProfile;

typedef _di_IIterator_1__ILanIdentifier *PIIterator_1__ILanIdentifier;

typedef _di_IIterable_1__ILanIdentifier *PIIterable_1__ILanIdentifier;

typedef _di_IVectorView_1__ILanIdentifier *PIVectorView_1__ILanIdentifier;

typedef _di_IProxyConfiguration *PIProxyConfiguration;

typedef _di_AsyncOperationCompletedHandler_1__IProxyConfiguration *PAsyncOperationCompletedHandler_1__IProxyConfiguration;

typedef _di_IAsyncOperation_1__IProxyConfiguration *PIAsyncOperation_1__IProxyConfiguration;

typedef _di_INetworkInformationStatics *PINetworkInformationStatics;

typedef _di_IConnectionProfileFilter *PIConnectionProfileFilter;

typedef _di_IConnectionProfileFilter2 *PIConnectionProfileFilter2;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile *PAsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile;

typedef _di_IAsyncOperation_1__IVectorView_1__IConnectionProfile *PIAsyncOperation_1__IVectorView_1__IConnectionProfile;

typedef _di_INetworkInformationStatics2 *PINetworkInformationStatics2;

typedef _di_IConnectionSession *PIConnectionSession;

typedef _di_IRoutePolicy *PIRoutePolicy;

typedef _di_IRoutePolicyFactory *PIRoutePolicyFactory;

typedef _di_ICellularApnContext *PICellularApnContext;

typedef _di_AsyncOperationCompletedHandler_1__IConnectionSession *PAsyncOperationCompletedHandler_1__IConnectionSession;

typedef _di_IAsyncOperation_1__IConnectionSession *PIAsyncOperation_1__IConnectionSession;

typedef _di_IConnectivityManagerStatics *PIConnectivityManagerStatics;

typedef _di_INetworkStateChangeEventDetails *PINetworkStateChangeEventDetails;

typedef _di_INetworkStateChangeEventDetails2 *PINetworkStateChangeEventDetails2;

__interface  INTERFACE_UUID("{8E113A05-E209-4549-BB25-5E0DB691CB05}") IConnectionCost2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_BackgroundDataUsageRestricted(bool &__get_BackgroundDataUsageRestricted_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_BackgroundDataUsageRestricted() { bool __r; HRESULT __hr = get_BackgroundDataUsageRestricted(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool BackgroundDataUsageRestricted = {read=_scw_get_BackgroundDataUsageRestricted};
};

__interface  INTERFACE_UUID("{562098CB-B35A-4BF1-A884-B7557E88FF86}") IWlanConnectionProfileDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetConnectedSsid(HSTRING &__GetConnectedSsid_result) = 0 ;
};

__interface  INTERFACE_UUID("{4FAA3FFF-6746-4824-A964-EED8E87F8709}") IConnectivityInterval  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_StartTime(Winapi::Commontypes::DateTime &__get_StartTime_result) = 0 ;
	virtual HRESULT __safecall get_ConnectionDuration(Winapi::Commontypes::TimeSpan &__get_ConnectionDuration_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_ConnectionDuration() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_ConnectionDuration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan ConnectionDuration = {read=_scw_get_ConnectionDuration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_StartTime() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_StartTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime StartTime = {read=_scw_get_StartTime};
};

__interface  INTERFACE_UUID("{49DA8FCE-9985-4927-BF5B-072B5C65F8D9}") INetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_BytesSent(unsigned __int64 &__get_BytesSent_result) = 0 ;
	virtual HRESULT __safecall get_BytesReceived(unsigned __int64 &__get_BytesReceived_result) = 0 ;
	virtual HRESULT __safecall get_ConnectionDuration(Winapi::Commontypes::TimeSpan &__get_ConnectionDuration_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesReceived() { unsigned __int64 __r; HRESULT __hr = get_BytesReceived(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesReceived = {read=_scw_get_BytesReceived};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesSent() { unsigned __int64 __r; HRESULT __hr = get_BytesSent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesSent = {read=_scw_get_BytesSent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_ConnectionDuration() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_ConnectionDuration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan ConnectionDuration = {read=_scw_get_ConnectionDuration};
};

__interface  INTERFACE_UUID("{F769B039-ECA2-45EB-ADE1-B0368B756C49}") IAttributedNetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_BytesSent(unsigned __int64 &__get_BytesSent_result) = 0 ;
	virtual HRESULT __safecall get_BytesReceived(unsigned __int64 &__get_BytesReceived_result) = 0 ;
	virtual HRESULT __safecall get_AttributionId(HSTRING &__get_AttributionId_result) = 0 ;
	virtual HRESULT __safecall get_AttributionName(HSTRING &__get_AttributionName_result) = 0 ;
	virtual HRESULT __safecall get_AttributionThumbnail(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_AttributionThumbnail_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AttributionId() { HSTRING __r; HRESULT __hr = get_AttributionId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AttributionId = {read=_scw_get_AttributionId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AttributionName() { HSTRING __r; HRESULT __hr = get_AttributionName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AttributionName = {read=_scw_get_AttributionName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_AttributionThumbnail() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_AttributionThumbnail(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference AttributionThumbnail = {read=_scw_get_AttributionThumbnail};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesReceived() { unsigned __int64 __r; HRESULT __hr = get_BytesReceived(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesReceived = {read=_scw_get_BytesReceived};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesSent() { unsigned __int64 __r; HRESULT __hr = get_BytesSent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesSent = {read=_scw_get_BytesSent};
};

__interface  INTERFACE_UUID("{5EC69E04-7931-48C8-B8F3-46300FA42728}") IProviderNetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_BytesSent(unsigned __int64 &__get_BytesSent_result) = 0 ;
	virtual HRESULT __safecall get_BytesReceived(unsigned __int64 &__get_BytesReceived_result) = 0 ;
	virtual HRESULT __safecall get_ProviderId(HSTRING &__get_ProviderId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesReceived() { unsigned __int64 __r; HRESULT __hr = get_BytesReceived(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesReceived = {read=_scw_get_BytesReceived};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_BytesSent() { unsigned __int64 __r; HRESULT __hr = get_BytesSent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 BytesSent = {read=_scw_get_BytesSent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ProviderId() { HSTRING __r; HRESULT __hr = get_ProviderId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ProviderId = {read=_scw_get_ProviderId};
};

__interface  INTERFACE_UUID("{0E4DA8FE-835F-4DF3-82FD-DF556EBC09EF}") IWwanConnectionProfileDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_HomeProviderId(HSTRING &__get_HomeProviderId_result) = 0 ;
	virtual HRESULT __safecall get_AccessPointName(HSTRING &__get_AccessPointName_result) = 0 ;
	virtual HRESULT __safecall GetNetworkRegistrationState(Winapi::Commontypes::WwanNetworkRegistrationState &__GetNetworkRegistrationState_result) = 0 ;
	virtual HRESULT __safecall GetCurrentDataClass(Winapi::Commontypes::WwanDataClass &__GetCurrentDataClass_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AccessPointName() { HSTRING __r; HRESULT __hr = get_AccessPointName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AccessPointName = {read=_scw_get_AccessPointName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HomeProviderId() { HSTRING __r; HRESULT __hr = get_HomeProviderId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HomeProviderId = {read=_scw_get_HomeProviderId};
};

__interface  INTERFACE_UUID("{5FAFB57B-9C82-50A1-9970-69F9CB069695}") IIterator_1__INetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{932F485D-2603-5593-BAED-C56FEE5A0EE1}") IIterator_1__INetworkUsage  : public IIterator_1__INetworkUsage_Base 
{
	virtual HRESULT __safecall get_Current(_di_INetworkUsage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PINetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_INetworkUsage _scw_get_Current() { _di_INetworkUsage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_INetworkUsage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{DD2656B1-8360-5772-B272-C47F7F0FC7A6}") IIterable_1__INetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F45D00D7-BCA3-5892-916A-7B9EB87C4FCB}") IIterable_1__INetworkUsage  : public IIterable_1__INetworkUsage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__INetworkUsage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{081441AB-4EA5-5F39-9A7D-3F9124CD22A0}") IVectorView_1__INetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_INetworkUsage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_INetworkUsage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PINetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{E31D7E7E-4173-5C71-B04B-A09658002590}") AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{34C7CFF2-F4A8-5936-AD75-041DA70D4BBA}") AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage  : public AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__INetworkUsage asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{05C9E081-6229-5049-8EEA-A498407C00D5}") IAsyncOperation_1__IVectorView_1__INetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F5F7F8A3-E501-5378-A56C-21A4BF9F2118}") IAsyncOperation_1__IVectorView_1__INetworkUsage  : public IAsyncOperation_1__IVectorView_1__INetworkUsage_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__INetworkUsage &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__INetworkUsage Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{741CEA48-651C-5FD9-931E-4F91B521E182}") IIterator_1__IConnectivityInterval_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1D8205F6-A78E-533F-9450-1BD5B39E6A63}") IIterator_1__IConnectivityInterval  : public IIterator_1__IConnectivityInterval_Base 
{
	virtual HRESULT __safecall get_Current(_di_IConnectivityInterval &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIConnectivityInterval items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IConnectivityInterval _scw_get_Current() { _di_IConnectivityInterval __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IConnectivityInterval Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{58051A8B-B259-5414-9B9A-CAA0789E833E}") IIterable_1__IConnectivityInterval_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CCFAFDA3-D747-52F7-8D78-538C34753194}") IIterable_1__IConnectivityInterval  : public IIterable_1__IConnectivityInterval_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IConnectivityInterval &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{33332F56-9B64-569F-BA8C-040BA0E8B249}") IVectorView_1__IConnectivityInterval  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IConnectivityInterval &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IConnectivityInterval value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIConnectivityInterval items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{B475014C-95F1-5310-B5D1-C2309D944440}") AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{85A0B45C-52E3-58C8-81DC-4B1B5335FF42}") AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval  : public AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IConnectivityInterval asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{AF96D70B-41C7-5DC6-9895-EA043A885D8D}") IAsyncOperation_1__IVectorView_1__IConnectivityInterval_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2156BF20-8540-5CAB-BFE6-2BC40D70271D}") IAsyncOperation_1__IVectorView_1__IConnectivityInterval  : public IAsyncOperation_1__IVectorView_1__IConnectivityInterval_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IConnectivityInterval &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectivityInterval Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{E2045145-4C9F-400C-9150-7EC7D6E2888A}") IConnectionProfile2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsWwanConnectionProfile(bool &__get_IsWwanConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall get_IsWlanConnectionProfile(bool &__get_IsWlanConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall get_WwanConnectionProfileDetails(_di_IWwanConnectionProfileDetails &__get_WwanConnectionProfileDetails_result) = 0 ;
	virtual HRESULT __safecall get_WlanConnectionProfileDetails(_di_IWlanConnectionProfileDetails &__get_WlanConnectionProfileDetails_result) = 0 ;
	virtual HRESULT __safecall get_ServiceProviderGuid(Winapi::Networking::_di_IReference_1__TGuid &__get_ServiceProviderGuid_result) = 0 ;
	virtual HRESULT __safecall GetSignalBars(Winapi::Networking::_di_IReference_1__Byte &__GetSignalBars_result) = 0 ;
	virtual HRESULT __safecall GetDomainConnectivityLevel(Winapi::Commontypes::DomainConnectivityLevel &__GetDomainConnectivityLevel_result) = 0 ;
	virtual HRESULT __safecall GetNetworkUsageAsync(Winapi::Commontypes::DateTime startTime, Winapi::Commontypes::DateTime endTime, Winapi::Commontypes::DataUsageGranularity granularity, Winapi::Commontypes::NetworkUsageStates states, _di_IAsyncOperation_1__IVectorView_1__INetworkUsage &__GetNetworkUsageAsync_result) = 0 ;
	virtual HRESULT __safecall GetConnectivityIntervalsAsync(Winapi::Commontypes::DateTime startTime, Winapi::Commontypes::DateTime endTime, Winapi::Commontypes::NetworkUsageStates states, _di_IAsyncOperation_1__IVectorView_1__IConnectivityInterval &__GetConnectivityIntervalsAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsWlanConnectionProfile() { bool __r; HRESULT __hr = get_IsWlanConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsWlanConnectionProfile = {read=_scw_get_IsWlanConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsWwanConnectionProfile() { bool __r; HRESULT __hr = get_IsWwanConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsWwanConnectionProfile = {read=_scw_get_IsWwanConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IReference_1__TGuid _scw_get_ServiceProviderGuid() { Winapi::Networking::_di_IReference_1__TGuid __r; HRESULT __hr = get_ServiceProviderGuid(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IReference_1__TGuid ServiceProviderGuid = {read=_scw_get_ServiceProviderGuid};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWlanConnectionProfileDetails _scw_get_WlanConnectionProfileDetails() { _di_IWlanConnectionProfileDetails __r; HRESULT __hr = get_WlanConnectionProfileDetails(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWlanConnectionProfileDetails WlanConnectionProfileDetails = {read=_scw_get_WlanConnectionProfileDetails};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWwanConnectionProfileDetails _scw_get_WwanConnectionProfileDetails() { _di_IWwanConnectionProfileDetails __r; HRESULT __hr = get_WwanConnectionProfileDetails(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWwanConnectionProfileDetails WwanConnectionProfileDetails = {read=_scw_get_WwanConnectionProfileDetails};
};

__interface  INTERFACE_UUID("{4070C40F-AB2F-56F2-B54C-8232AE86AACD}") IIterator_1__IAttributedNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{508BCE21-0428-5091-AFDD-8C4D874A5D6E}") IIterator_1__IAttributedNetworkUsage  : public IIterator_1__IAttributedNetworkUsage_Base 
{
	virtual HRESULT __safecall get_Current(_di_IAttributedNetworkUsage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIAttributedNetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAttributedNetworkUsage _scw_get_Current() { _di_IAttributedNetworkUsage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAttributedNetworkUsage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D061DCB9-6854-5EF9-8E03-008A7A704C48}") IIterable_1__IAttributedNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4574423F-9395-5B9B-9AC4-BB37D94BFDE8}") IIterable_1__IAttributedNetworkUsage  : public IIterable_1__IAttributedNetworkUsage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IAttributedNetworkUsage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{C36D6E40-B6DC-5757-82BE-F85FF7C12E3F}") IVectorView_1__IAttributedNetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IAttributedNetworkUsage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IAttributedNetworkUsage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIAttributedNetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{96AF15CC-F060-5667-9223-E054D14239EC}") AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1FEDF355-F8A3-5011-BF62-91BEC9E31A2D}") AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage  : public AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9D8A4113-E7F3-552D-9A8C-1C25E2137253}") IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{7A91DEFA-3E58-59C8-A392-4FCF0A4A501D}") IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage  : public IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IAttributedNetworkUsage &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IAttributedNetworkUsage Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{578C2528-4CD9-4161-8045-201CFD5B115C}") IConnectionProfile3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAttributedNetworkUsageAsync(Winapi::Commontypes::DateTime startTime, Winapi::Commontypes::DateTime endTime, Winapi::Commontypes::NetworkUsageStates states, _di_IAsyncOperation_1__IVectorView_1__IAttributedNetworkUsage &__GetAttributedNetworkUsageAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{D7090752-AB5F-506F-8F15-56B37552FBEA}") IIterator_1__IProviderNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{96296236-588F-543D-9D87-FCAB239226B2}") IIterator_1__IProviderNetworkUsage  : public IIterator_1__IProviderNetworkUsage_Base 
{
	virtual HRESULT __safecall get_Current(_di_IProviderNetworkUsage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIProviderNetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IProviderNetworkUsage _scw_get_Current() { _di_IProviderNetworkUsage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IProviderNetworkUsage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{F79BC7BA-01DF-51EC-BFAF-FD883F698E07}") IIterable_1__IProviderNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{43A19450-432A-5872-B87E-D0F9B51FFD4B}") IIterable_1__IProviderNetworkUsage  : public IIterable_1__IProviderNetworkUsage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IProviderNetworkUsage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{929B60C0-C750-511D-BC65-C28830357D91}") IVectorView_1__IProviderNetworkUsage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IProviderNetworkUsage &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IProviderNetworkUsage value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIProviderNetworkUsage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{C310276B-3932-5DA9-9A3B-C5C423586B42}") AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{34A1E924-9B74-5F17-81A0-F5EC58E6C806}") AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage  : public AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{7EBA5A8F-E4FD-5201-A4F4-9567596F213C}") IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{794F1B0C-9525-5FD4-9F83-F2454289B7A9}") IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage  : public IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IProviderNetworkUsage &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IProviderNetworkUsage Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{7A2D42CD-81E0-4AE6-ABED-AB9CA13EB714}") IConnectionProfile4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetProviderNetworkUsageAsync(Winapi::Commontypes::DateTime startTime, Winapi::Commontypes::DateTime endTime, Winapi::Commontypes::NetworkUsageStates states, _di_IAsyncOperation_1__IVectorView_1__IProviderNetworkUsage &__GetProviderNetworkUsageAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{A74E83C3-D639-45BE-A36A-C4E4AEAF6D9B}") ILanIdentifierData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Type(unsigned &__get_Type_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Networking::_di_IVectorView_1__Byte &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Type() { unsigned __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Type = {read=_scw_get_Type};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IVectorView_1__Byte _scw_get_Value() { Winapi::Networking::_di_IVectorView_1__Byte __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IVectorView_1__Byte Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{48AA53AA-1108-4546-A6CB-9A74DA4B7BA0}") ILanIdentifier  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_InfrastructureId(_di_ILanIdentifierData &__get_InfrastructureId_result) = 0 ;
	virtual HRESULT __safecall get_PortId(_di_ILanIdentifierData &__get_PortId_result) = 0 ;
	virtual HRESULT __safecall get_NetworkAdapterId(GUID &__get_NetworkAdapterId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILanIdentifierData _scw_get_InfrastructureId() { _di_ILanIdentifierData __r; HRESULT __hr = get_InfrastructureId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILanIdentifierData InfrastructureId = {read=_scw_get_InfrastructureId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline GUID _scw_get_NetworkAdapterId() { GUID __r; HRESULT __hr = get_NetworkAdapterId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property GUID NetworkAdapterId = {read=_scw_get_NetworkAdapterId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILanIdentifierData _scw_get_PortId() { _di_ILanIdentifierData __r; HRESULT __hr = get_PortId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILanIdentifierData PortId = {read=_scw_get_PortId};
};

__interface  INTERFACE_UUID("{71BA143F-598E-49D0-84EB-8FEBAEDCC195}") NetworkStatusChangedEventHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender) = 0 ;
};

__interface  INTERFACE_UUID("{89913732-A08B-5CB2-AF16-BBBB2223839E}") IIterator_1__IConnectionProfile_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{ECF00CAE-BF0D-5D30-89EF-A3403CB22EAC}") IIterator_1__IConnectionProfile  : public IIterator_1__IConnectionProfile_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IConnectionProfile &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIConnectionProfile items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IConnectionProfile _scw_get_Current() { Winapi::Commontypes::_di_IConnectionProfile __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IConnectionProfile Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{34DABEF9-87D0-5B1C-A7AC-9D290ADEB0C8}") IIterable_1__IConnectionProfile_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{8BC9CBFB-ADC3-5C9A-902E-CA4F4958113E}") IIterable_1__IConnectionProfile  : public IIterable_1__IConnectionProfile_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IConnectionProfile &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{3C724EDA-2AC8-5E49-945F-E242F6EE16D4}") IVectorView_1__IConnectionProfile  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IConnectionProfile &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IConnectionProfile value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIConnectionProfile items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{2C5D2F7E-CE9C-5253-A0F4-01E5BDC11988}") IIterator_1__ILanIdentifier_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E50F2506-05FF-5248-B0BF-998C91B0C9A6}") IIterator_1__ILanIdentifier  : public IIterator_1__ILanIdentifier_Base 
{
	virtual HRESULT __safecall get_Current(_di_ILanIdentifier &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PILanIdentifier items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ILanIdentifier _scw_get_Current() { _di_ILanIdentifier __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ILanIdentifier Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{ACCEF3CD-5D92-5C01-8AC4-79FE74CD733E}") IIterable_1__ILanIdentifier_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{81266A25-E204-54FF-8B8E-3B30DA27BC35}") IIterable_1__ILanIdentifier  : public IIterable_1__ILanIdentifier_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ILanIdentifier &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{43442CEB-9A1C-5799-9C42-8A7FBB36ADB7}") IVectorView_1__ILanIdentifier  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ILanIdentifier &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ILanIdentifier value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PILanIdentifier items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{EF3A60B4-9004-4DD6-B7D8-B3E502F4AAD0}") IProxyConfiguration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ProxyUris(Winapi::Foundation::_di_IVectorView_1__IUriRuntimeClass &__get_ProxyUris_result) = 0 ;
	virtual HRESULT __safecall get_CanConnectDirectly(bool &__get_CanConnectDirectly_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_CanConnectDirectly() { bool __r; HRESULT __hr = get_CanConnectDirectly(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool CanConnectDirectly = {read=_scw_get_CanConnectDirectly};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::_di_IVectorView_1__IUriRuntimeClass _scw_get_ProxyUris() { Winapi::Foundation::_di_IVectorView_1__IUriRuntimeClass __r; HRESULT __hr = get_ProxyUris(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::_di_IVectorView_1__IUriRuntimeClass ProxyUris = {read=_scw_get_ProxyUris};
};

__interface  INTERFACE_UUID("{035B2567-EFB9-5BC3-B609-F9A8C20B7001}") AsyncOperationCompletedHandler_1__IProxyConfiguration_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6EB17802-BF19-5CEB-9A91-5D78B23E0D8F}") AsyncOperationCompletedHandler_1__IProxyConfiguration  : public AsyncOperationCompletedHandler_1__IProxyConfiguration_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IProxyConfiguration asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{1E7651F6-6562-59C7-9AF3-8756636EEEE2}") IAsyncOperation_1__IProxyConfiguration_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A945C381-57EE-5A60-BC54-8A3729E42737}") IAsyncOperation_1__IProxyConfiguration  : public IAsyncOperation_1__IProxyConfiguration_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IProxyConfiguration handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IProxyConfiguration &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IProxyConfiguration &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IProxyConfiguration _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IProxyConfiguration __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IProxyConfiguration Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{5074F851-950D-4165-9C15-365619481EEA}") INetworkInformationStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetConnectionProfiles(_di_IVectorView_1__IConnectionProfile &__GetConnectionProfiles_result) = 0 ;
	virtual HRESULT __safecall GetInternetConnectionProfile(Winapi::Commontypes::_di_IConnectionProfile &__GetInternetConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall GetLanIdentifiers(_di_IVectorView_1__ILanIdentifier &__GetLanIdentifiers_result) = 0 ;
	virtual HRESULT __safecall GetHostNames(Winapi::Commontypes::_di_IVectorView_1__IHostName &__GetHostNames_result) = 0 ;
	virtual HRESULT __safecall GetProxyConfigurationAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri, _di_IAsyncOperation_1__IProxyConfiguration &__GetProxyConfigurationAsync_result) = 0 ;
	virtual HRESULT __safecall GetSortedEndpointPairs(Winapi::Networking::_di_IIterable_1__IEndpointPair destinationList, Winapi::Commontypes::HostNameSortOptions sortOptions, Winapi::Networking::_di_IVectorView_1__IEndpointPair &__GetSortedEndpointPairs_result) = 0 ;
	virtual HRESULT __safecall add_NetworkStatusChanged(_di_NetworkStatusChangedEventHandler networkStatusHandler, Winapi::Commontypes::EventRegistrationToken &__add_NetworkStatusChanged_result) = 0 ;
	virtual HRESULT __safecall remove_NetworkStatusChanged(Winapi::Commontypes::EventRegistrationToken eventCookie) = 0 ;
};

__interface  INTERFACE_UUID("{204C7CC8-BD2D-4E8D-A4B3-455EC337388A}") IConnectionProfileFilter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_IsConnected(bool value) = 0 ;
	virtual HRESULT __safecall get_IsConnected(bool &__get_IsConnected_result) = 0 ;
	virtual HRESULT __safecall put_IsWwanConnectionProfile(bool value) = 0 ;
	virtual HRESULT __safecall get_IsWwanConnectionProfile(bool &__get_IsWwanConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall put_IsWlanConnectionProfile(bool value) = 0 ;
	virtual HRESULT __safecall get_IsWlanConnectionProfile(bool &__get_IsWlanConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall put_NetworkCostType(Winapi::Commontypes::NetworkCostType value) = 0 ;
	virtual HRESULT __safecall get_NetworkCostType(Winapi::Commontypes::NetworkCostType &__get_NetworkCostType_result) = 0 ;
	virtual HRESULT __safecall put_ServiceProviderGuid(Winapi::Networking::_di_IReference_1__TGuid value) = 0 ;
	virtual HRESULT __safecall get_ServiceProviderGuid(Winapi::Networking::_di_IReference_1__TGuid &__get_ServiceProviderGuid_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsConnected() { bool __r; HRESULT __hr = get_IsConnected(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsConnected = {read=_scw_get_IsConnected, write=put_IsConnected};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsWlanConnectionProfile() { bool __r; HRESULT __hr = get_IsWlanConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsWlanConnectionProfile = {read=_scw_get_IsWlanConnectionProfile, write=put_IsWlanConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsWwanConnectionProfile() { bool __r; HRESULT __hr = get_IsWwanConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsWwanConnectionProfile = {read=_scw_get_IsWwanConnectionProfile, write=put_IsWwanConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::NetworkCostType _scw_get_NetworkCostType() { Winapi::Commontypes::NetworkCostType __r; HRESULT __hr = get_NetworkCostType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::NetworkCostType NetworkCostType = {read=_scw_get_NetworkCostType, write=put_NetworkCostType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IReference_1__TGuid _scw_get_ServiceProviderGuid() { Winapi::Networking::_di_IReference_1__TGuid __r; HRESULT __hr = get_ServiceProviderGuid(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IReference_1__TGuid ServiceProviderGuid = {read=_scw_get_ServiceProviderGuid, write=put_ServiceProviderGuid};
};

__interface  INTERFACE_UUID("{CD068EE1-C3FC-4FAD-9DDC-593FAA4B7885}") IConnectionProfileFilter2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_IsRoaming(Winapi::Networking::_di_IReference_1__Boolean value) = 0 ;
	virtual HRESULT __safecall get_IsRoaming(Winapi::Networking::_di_IReference_1__Boolean &__get_IsRoaming_result) = 0 ;
	virtual HRESULT __safecall put_IsOverDataLimit(Winapi::Networking::_di_IReference_1__Boolean value) = 0 ;
	virtual HRESULT __safecall get_IsOverDataLimit(Winapi::Networking::_di_IReference_1__Boolean &__get_IsOverDataLimit_result) = 0 ;
	virtual HRESULT __safecall put_IsBackgroundDataUsageRestricted(Winapi::Networking::_di_IReference_1__Boolean value) = 0 ;
	virtual HRESULT __safecall get_IsBackgroundDataUsageRestricted(Winapi::Networking::_di_IReference_1__Boolean &__get_IsBackgroundDataUsageRestricted_result) = 0 ;
	virtual HRESULT __safecall get_RawData(Winapi::Commontypes::_di_IBuffer &__get_RawData_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IReference_1__Boolean _scw_get_IsBackgroundDataUsageRestricted() { Winapi::Networking::_di_IReference_1__Boolean __r; HRESULT __hr = get_IsBackgroundDataUsageRestricted(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IReference_1__Boolean IsBackgroundDataUsageRestricted = {read=_scw_get_IsBackgroundDataUsageRestricted, write=put_IsBackgroundDataUsageRestricted};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IReference_1__Boolean _scw_get_IsOverDataLimit() { Winapi::Networking::_di_IReference_1__Boolean __r; HRESULT __hr = get_IsOverDataLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IReference_1__Boolean IsOverDataLimit = {read=_scw_get_IsOverDataLimit, write=put_IsOverDataLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Networking::_di_IReference_1__Boolean _scw_get_IsRoaming() { Winapi::Networking::_di_IReference_1__Boolean __r; HRESULT __hr = get_IsRoaming(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Networking::_di_IReference_1__Boolean IsRoaming = {read=_scw_get_IsRoaming, write=put_IsRoaming};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_RawData() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_RawData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer RawData = {read=_scw_get_RawData};
};

__interface  INTERFACE_UUID("{C523D9DD-4EA6-5115-80E9-4E7AD4769798}") AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D7DB932C-AF75-5E4A-9689-0320303401DF}") AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile  : public AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IConnectionProfile asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{C0023294-C2CB-52F0-A9F4-21916032F69D}") IAsyncOperation_1__IVectorView_1__IConnectionProfile_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{650097D7-D5A3-559F-B864-B5E1C7576775}") IAsyncOperation_1__IVectorView_1__IConnectionProfile  : public IAsyncOperation_1__IVectorView_1__IConnectionProfile_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IConnectionProfile &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IConnectionProfile Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{459CED14-2832-49B6-BA6E-E265F04786A8}") INetworkInformationStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FindConnectionProfilesAsync(_di_IConnectionProfileFilter pProfileFilter, _di_IAsyncOperation_1__IVectorView_1__IConnectionProfile &__FindConnectionProfilesAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{FF905D4C-F83B-41B0-8A0C-1462D9C56B73}") IConnectionSession  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ConnectionProfile(Winapi::Commontypes::_di_IConnectionProfile &__get_ConnectionProfile_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IConnectionProfile _scw_get_ConnectionProfile() { Winapi::Commontypes::_di_IConnectionProfile __r; HRESULT __hr = get_ConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IConnectionProfile ConnectionProfile = {read=_scw_get_ConnectionProfile};
};

__interface  INTERFACE_UUID("{11ABC4AC-0FC7-42E4-8742-569923B1CA11}") IRoutePolicy  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ConnectionProfile(Winapi::Commontypes::_di_IConnectionProfile &__get_ConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall get_HostName(Winapi::Commontypes::_di_IHostName &__get_HostName_result) = 0 ;
	virtual HRESULT __safecall get_HostNameType(Winapi::Commontypes::DomainNameType &__get_HostNameType_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IConnectionProfile _scw_get_ConnectionProfile() { Winapi::Commontypes::_di_IConnectionProfile __r; HRESULT __hr = get_ConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IConnectionProfile ConnectionProfile = {read=_scw_get_ConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IHostName _scw_get_HostName() { Winapi::Commontypes::_di_IHostName __r; HRESULT __hr = get_HostName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IHostName HostName = {read=_scw_get_HostName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DomainNameType _scw_get_HostNameType() { Winapi::Commontypes::DomainNameType __r; HRESULT __hr = get_HostNameType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DomainNameType HostNameType = {read=_scw_get_HostNameType};
};

__interface  INTERFACE_UUID("{36027933-A18E-4DB5-A697-F58FA7364E44}") IRoutePolicyFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateRoutePolicy(Winapi::Commontypes::_di_IConnectionProfile connectionProfile, Winapi::Commontypes::_di_IHostName hostName, Winapi::Commontypes::DomainNameType type, _di_IRoutePolicy &__CreateRoutePolicy_result) = 0 ;
};

__interface  INTERFACE_UUID("{6FA529F4-EFFD-4542-9AB2-705BBF94943A}") ICellularApnContext  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ProviderId(HSTRING &__get_ProviderId_result) = 0 ;
	virtual HRESULT __safecall put_ProviderId(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_AccessPointName(HSTRING &__get_AccessPointName_result) = 0 ;
	virtual HRESULT __safecall put_AccessPointName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_UserName(HSTRING &__get_UserName_result) = 0 ;
	virtual HRESULT __safecall put_UserName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Password(HSTRING &__get_Password_result) = 0 ;
	virtual HRESULT __safecall put_Password(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_IsCompressionEnabled(bool &__get_IsCompressionEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsCompressionEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_AuthenticationType(Winapi::Commontypes::CellularApnAuthenticationType &__get_AuthenticationType_result) = 0 ;
	virtual HRESULT __safecall put_AuthenticationType(Winapi::Commontypes::CellularApnAuthenticationType value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AccessPointName() { HSTRING __r; HRESULT __hr = get_AccessPointName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AccessPointName = {read=_scw_get_AccessPointName, write=put_AccessPointName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CellularApnAuthenticationType _scw_get_AuthenticationType() { Winapi::Commontypes::CellularApnAuthenticationType __r; HRESULT __hr = get_AuthenticationType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CellularApnAuthenticationType AuthenticationType = {read=_scw_get_AuthenticationType, write=put_AuthenticationType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCompressionEnabled() { bool __r; HRESULT __hr = get_IsCompressionEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCompressionEnabled = {read=_scw_get_IsCompressionEnabled, write=put_IsCompressionEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Password() { HSTRING __r; HRESULT __hr = get_Password(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Password = {read=_scw_get_Password, write=put_Password};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ProviderId() { HSTRING __r; HRESULT __hr = get_ProviderId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ProviderId = {read=_scw_get_ProviderId, write=put_ProviderId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UserName() { HSTRING __r; HRESULT __hr = get_UserName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UserName = {read=_scw_get_UserName, write=put_UserName};
};

__interface  INTERFACE_UUID("{3BC680D8-9E83-5086-8F49-7A29BFB1C7E1}") AsyncOperationCompletedHandler_1__IConnectionSession_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D1813A09-BE5C-5845-A642-627024C4F8D4}") AsyncOperationCompletedHandler_1__IConnectionSession  : public AsyncOperationCompletedHandler_1__IConnectionSession_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IConnectionSession asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{94FC6211-4702-5D24-81BF-170CA7818995}") IAsyncOperation_1__IConnectionSession_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{31FC98D3-FD1F-5E31-BBAA-11B2B9707382}") IAsyncOperation_1__IConnectionSession  : public IAsyncOperation_1__IConnectionSession_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IConnectionSession handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IConnectionSession &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IConnectionSession &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IConnectionSession _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IConnectionSession __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IConnectionSession Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{5120D4B1-4FB1-48B0-AFC9-42E0092A8164}") IConnectivityManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AcquireConnectionAsync(_di_ICellularApnContext cellularApnContext, _di_IAsyncOperation_1__IConnectionSession &__AcquireConnectionAsync_result) = 0 ;
	virtual HRESULT __safecall AddHttpRoutePolicy(_di_IRoutePolicy routePolicy) = 0 ;
	virtual HRESULT __safecall RemoveHttpRoutePolicy(_di_IRoutePolicy routePolicy) = 0 ;
};

__interface  INTERFACE_UUID("{1F0CF333-D7A6-44DD-A4E9-687C476B903D}") INetworkStateChangeEventDetails  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_HasNewInternetConnectionProfile(bool &__get_HasNewInternetConnectionProfile_result) = 0 ;
	virtual HRESULT __safecall get_HasNewConnectionCost(bool &__get_HasNewConnectionCost_result) = 0 ;
	virtual HRESULT __safecall get_HasNewNetworkConnectivityLevel(bool &__get_HasNewNetworkConnectivityLevel_result) = 0 ;
	virtual HRESULT __safecall get_HasNewDomainConnectivityLevel(bool &__get_HasNewDomainConnectivityLevel_result) = 0 ;
	virtual HRESULT __safecall get_HasNewHostNameList(bool &__get_HasNewHostNameList_result) = 0 ;
	virtual HRESULT __safecall get_HasNewWwanRegistrationState(bool &__get_HasNewWwanRegistrationState_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewConnectionCost() { bool __r; HRESULT __hr = get_HasNewConnectionCost(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewConnectionCost = {read=_scw_get_HasNewConnectionCost};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewDomainConnectivityLevel() { bool __r; HRESULT __hr = get_HasNewDomainConnectivityLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewDomainConnectivityLevel = {read=_scw_get_HasNewDomainConnectivityLevel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewHostNameList() { bool __r; HRESULT __hr = get_HasNewHostNameList(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewHostNameList = {read=_scw_get_HasNewHostNameList};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewInternetConnectionProfile() { bool __r; HRESULT __hr = get_HasNewInternetConnectionProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewInternetConnectionProfile = {read=_scw_get_HasNewInternetConnectionProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewNetworkConnectivityLevel() { bool __r; HRESULT __hr = get_HasNewNetworkConnectivityLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewNetworkConnectivityLevel = {read=_scw_get_HasNewNetworkConnectivityLevel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewWwanRegistrationState() { bool __r; HRESULT __hr = get_HasNewWwanRegistrationState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewWwanRegistrationState = {read=_scw_get_HasNewWwanRegistrationState};
};

__interface  INTERFACE_UUID("{D643C0E8-30D3-4F6A-AD47-6A1873CEB3C1}") INetworkStateChangeEventDetails2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_HasNewTetheringOperationalState(bool &__get_HasNewTetheringOperationalState_result) = 0 ;
	virtual HRESULT __safecall get_HasNewTetheringClientCount(bool &__get_HasNewTetheringClientCount_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewTetheringClientCount() { bool __r; HRESULT __hr = get_HasNewTetheringClientCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewTetheringClientCount = {read=_scw_get_HasNewTetheringClientCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasNewTetheringOperationalState() { bool __r; HRESULT __hr = get_HasNewTetheringOperationalState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasNewTetheringOperationalState = {read=_scw_get_HasNewTetheringOperationalState};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TConnectionProfileFilter : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IConnectionProfileFilter>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IConnectionProfileFilter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TConnectionProfileFilter() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IConnectionProfileFilter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TConnectionProfileFilter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRoutePolicy : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IRoutePolicyFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IRoutePolicyFactory> inherited;
	
public:
	static _di_IRoutePolicy __fastcall CreateRoutePolicy(Winapi::Commontypes::_di_IConnectionProfile connectionProfile, Winapi::Commontypes::_di_IHostName hostName, Winapi::Commontypes::DomainNameType type);
public:
	/* TObject.Create */ inline __fastcall TRoutePolicy() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IRoutePolicyFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRoutePolicy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCellularApnContext : public System::Win::Winrt::TWinRTGenericImportI__1<_di_ICellularApnContext>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_ICellularApnContext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TCellularApnContext() : System::Win::Winrt::TWinRTGenericImportI__1<_di_ICellularApnContext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCellularApnContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNetworkInformation : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_INetworkInformationStatics,_di_INetworkInformationStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_INetworkInformationStatics,_di_INetworkInformationStatics2> inherited;
	
public:
	static _di_IVectorView_1__IConnectionProfile __fastcall GetConnectionProfiles();
	static Winapi::Commontypes::_di_IConnectionProfile __fastcall GetInternetConnectionProfile();
	static _di_IVectorView_1__ILanIdentifier __fastcall GetLanIdentifiers();
	static Winapi::Commontypes::_di_IVectorView_1__IHostName __fastcall GetHostNames();
	static _di_IAsyncOperation_1__IProxyConfiguration __fastcall GetProxyConfigurationAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri);
	static Winapi::Networking::_di_IVectorView_1__IEndpointPair __fastcall GetSortedEndpointPairs(Winapi::Networking::_di_IIterable_1__IEndpointPair destinationList, Winapi::Commontypes::HostNameSortOptions sortOptions);
	static Winapi::Commontypes::EventRegistrationToken __fastcall add_NetworkStatusChanged(_di_NetworkStatusChangedEventHandler networkStatusHandler);
	static void __fastcall remove_NetworkStatusChanged(const Winapi::Commontypes::EventRegistrationToken &eventCookie);
	static _di_IAsyncOperation_1__IVectorView_1__IConnectionProfile __fastcall FindConnectionProfilesAsync(_di_IConnectionProfileFilter pProfileFilter);
public:
	/* TObject.Create */ inline __fastcall TNetworkInformation() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_INetworkInformationStatics,_di_INetworkInformationStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNetworkInformation() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TConnectivityManager : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IConnectivityManagerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IConnectivityManagerStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IConnectionSession __fastcall AcquireConnectionAsync(_di_ICellularApnContext cellularApnContext);
	static void __fastcall AddHttpRoutePolicy(_di_IRoutePolicy routePolicy);
	static void __fastcall RemoveHttpRoutePolicy(_di_IRoutePolicy routePolicy);
public:
	/* TObject.Create */ inline __fastcall TConnectivityManager() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IConnectivityManagerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TConnectivityManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Connectivity */
}	/* namespace Networking */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Networking_ConnectivityHPP
