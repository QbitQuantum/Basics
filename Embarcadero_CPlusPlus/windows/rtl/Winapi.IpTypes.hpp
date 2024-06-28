// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.IpTypes.pas' rev: 34.00 (Windows)

#ifndef Winapi_IptypesHPP
#define Winapi_IptypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinSock.hpp>

//-- user supplied -----------------------------------------------------------

#include "iptypes.h"

namespace Winapi
{
namespace Iptypes
{
typedef IP_ADAPTER_UNICAST_ADDRESS TIpAdapterUnicastAddress;
typedef IP_ADAPTER_ANYCAST_ADDRESS TIpAdapterAnycaseAddress;
typedef IP_ADAPTER_MULTICAST_ADDRESS TIpAdapterMulticastAddress;
typedef IP_ADAPTER_DNS_SERVER_ADDRESS TIpAdapterDnsServerAddress;
typedef IP_ADAPTER_PREFIX TIpAdapterPrefix;
typedef IP_ADAPTER_ADDRESSES TIpAdapterAddresses;
typedef IP_PER_ADAPTER_INFO TIpPerAdapterInfo;
}
}

namespace Winapi
{
namespace Iptypes
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _SOCKET_ADDRESS TSocketAddress;

typedef PSOCKET_ADDRESS PSocketAddress;

typedef IP_ADDRESS_STRING TIpAddressString;

typedef PIP_MASK_STRING PIpAddressString;

typedef _IP_ADDR_STRING TIpAddrString;

typedef PIP_ADDR_STRING PIpAddrString;

typedef _IP_ADAPTER_INFO TIpAdapterInfo;

typedef PIP_ADAPTER_INFO PIpAdapterInfo;

typedef IP_PREFIX_ORIGIN TIpPrefixOrigin;

typedef IP_SUFFIX_ORIGIN TIpSuffixOrigin;

typedef IP_DAD_STATE TIpDadState;

typedef PIP_ADAPTER_UNICAST_ADDRESS PIpAdapterUnicastAddress;

typedef PIP_ADAPTER_ANYCAST_ADDRESS PIpAdapterAnycaseAddress;

typedef PIP_ADAPTER_MULTICAST_ADDRESS PIpAdapterMulticastAddress;

typedef PIP_ADAPTER_DNS_SERVER_ADDRESS PIpAdapterDnsServerAddress;

typedef PIP_ADAPTER_PREFIX PIpAdapterPrefix;

typedef IF_OPER_STATUS TIfOperStatus;

enum DECLSPEC_DENUM TNetIfConnectionType : unsigned int { NetIfConnectionDedicated = 1, NetIfConnectionPassive, NetIfConnectionDemand, NetIfConnectionMaximum };

enum DECLSPEC_DENUM TTunnelType : unsigned int { TunnelTypeNone, TunnelTypeOther, TunnelTypeDirect, TunnelType6To4 = 11, TunnelTypeIsatap = 13, TunnelTypeTeredo, TunnelTypeIPHTTPS };

typedef PIP_ADAPTER_ADDRESSES PIpAdapterAddresses;

typedef PIP_PER_ADAPTER_INFO PIpPerAdapterInfo;

typedef FIXED_INFO TFixedInfo;

typedef PFIXED_INFO PFixedInfo;

typedef IP_INTERFACE_NAME_INFO TIpInterfaceNameInfo;

typedef IP_INTERFACE_NAME_INFO *PIpInterfaceNameInfo;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iptypes */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_IPTYPES)
using namespace Winapi::Iptypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_IptypesHPP
