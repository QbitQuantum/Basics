// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.IpRtrMib.pas' rev: 34.00 (Windows)

#ifndef Winapi_IprtrmibHPP
#define Winapi_IprtrmibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

#include <iprtrmib.h>
#include <udpmib.h>
#include <tcpmib.h>


namespace Winapi
{
namespace Iprtrmib
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _MIB_OPAQUE_QUERY TMibOpaqueQuery;

typedef PMIB_OPAQUE_QUERY PMibOpaqueQuery;

typedef _MIB_IFNUMBER TMibIfnumber;

typedef PMIB_IFNUMBER PMibIfnumber;

typedef _MIB_IFROW TMibIfRow;

typedef PMIB_IFROW PMibIfRow;

typedef _MIB_IFTABLE TMibIftable;

typedef PMIB_IFTABLE PMibIftable;

typedef _MIBICMPSTATS *PMibIcmpStats;

typedef _MIBICMPSTATS TMibIcmpStats;

typedef _MIBICMPINFO TMibIcmpInfo;

typedef _MIB_ICMP TMibIcmp;

typedef PMIB_ICMP PMibIcmp;

typedef unsigned TIcmp6Type;

typedef PICMP6_TYPE PIcmp6Type;

typedef unsigned TIcmp4Type;

typedef PICMP4_TYPE PIcmp4Type;

typedef _MIBICMPSTATS_EX_XPSP1 TMibIcmpStatsEx;

typedef PMIBICMPSTATS_EX PMibIcmpStatsEx;

typedef _MIB_ICMP_EX_XPSP1 TMibIcmpEx;

typedef PMIB_ICMP_EX PMibIcmpEx;

typedef _MIB_UDPSTATS TMibUdpStats;

typedef PMIB_UDPSTATS PMibUdpStats;

typedef _MIB_UDPROW TMibUdpRow;

typedef PMIB_UDPROW PMibUdpRow;

typedef _MIB_UDPTABLE TMibUdpTable;

typedef PMIB_UDPTABLE PMibUdpTable;

typedef _MIB_TCPSTATS_LH TMibTcpStats;

typedef PMIB_TCPSTATS PMibTcpStats;

typedef _MIB_TCPROW_W2K TMibTcpRow;

typedef PMIB_TCPROW PMibTcpRow;

typedef _MIB_TCPTABLE TMibTcpTable;

typedef PMIB_TCPTABLE PMibTcpTable;

typedef _MIB_IPSTATS_W2K TMibIpStats;

typedef PMIB_IPSTATS PMibIpStats;

typedef _MIB_IPADDRROW_XP TMibIpAddrRow;

typedef PMIB_IPADDRROW PMibIpAddrRow;

typedef _MIB_IPADDRTABLE TMibIpAddrTable;

typedef PMIB_IPADDRTABLE PMibIpAddrTable;

typedef _MIB_IPFORWARDNUMBER TMibIpForwardNumber;

typedef PMIB_IPFORWARDNUMBER PMibIpForwardNumber;

typedef _MIB_IPFORWARDROW TMibIpForwardRow;

typedef PMIB_IPFORWARDROW PMibIpForwardRow;

typedef _MIB_IPFORWARDTABLE TMibIpForwardTable;

typedef PMIB_IPFORWARDTABLE PMibIpForwardTable;

typedef _MIB_IPNETROW_W2K TMibIpNetRow;

typedef PMIB_IPNETROW PMibIpNetRow;

typedef _MIB_IPNETTABLE TMibIpNetTable;

typedef PMIB_IPNETTABLE PMibIpNetTable;

typedef _MIB_IPMCAST_OIF_XP TMibIpmCastOif;

typedef PMIB_IPMCAST_OIF PMibIpmCastOif;

typedef _MIB_IPMCAST_MFE TMibIpmCastMfe;

typedef PMIB_IPMCAST_MFE PMibIpmCastMfe;

typedef _MIB_MFE_TABLE TMibMfeTable;

typedef PMIB_MFE_TABLE PMibMfeTable;

typedef _MIB_IPMCAST_OIF_STATS_LH TMibIpmCastOifStats;

typedef PMIB_IPMCAST_OIF_STATS PMibIpmCastOifStats;

typedef _MIB_IPMCAST_MFE_STATS TMibIpmCastMfeStats;

typedef PMIB_IPMCAST_MFE_STATS PMibIpmCastMfeStats;

typedef _MIB_MFE_STATS_TABLE TMibMfeStatsTable;

typedef PMIB_MFE_STATS_TABLE PMibMfeStatsTable;

typedef _MIB_IPMCAST_MFE_STATS_EX_XP TMibIpMCastMfeStatsEx;

typedef PMIB_IPMCAST_MFE_STATS_EX PMibIpMCastMfeStatsEx;

typedef System::StaticArray<_MIB_IPMCAST_MFE_STATS_EX_XP, 1> TArrayMibIpMCastMfeStatsEx;

typedef TArrayMibIpMCastMfeStatsEx *PArrayMibIpMCastMfeStatsEx;

typedef _MIB_MFE_STATS_TABLE_EX_XP TMibMfeStatsTableEx;

typedef PMIB_MFE_STATS_TABLE_EX PMibMfeStatsTableEx;

typedef _MIB_IPMCAST_GLOBAL TMibIpmCastGlobal;

typedef PMIB_IPMCAST_GLOBAL PMibIpmCastGlobal;

typedef _MIB_IPMCAST_IF_ENTRY TMibIpmCastIfEntry;

typedef PMIB_IPMCAST_IF_ENTRY PMibIpmCastIfEntry;

typedef _MIB_IPMCAST_IF_TABLE TMibIpmCastIfTable;

typedef PMIB_IPMCAST_IF_TABLE PMibIpmCastIfTable;

typedef _MIB_IPMCAST_BOUNDARY TMibIpmCastBoundary;

typedef PMIB_IPMCAST_BOUNDARY PMibIpmCastBoundary;

typedef _MIB_IPMCAST_BOUNDARY_TABLE TMibIpmCastBoundaryTable;

typedef PMIB_IPMCAST_BOUNDARY_TABLE PMibIpmCastBoundaryTable;

typedef MIB_BOUNDARYROW TMibBoundaryRow;

typedef PMIB_BOUNDARYROW PMibBoundaryRow;

typedef MIB_MCAST_LIMIT_ROW TMibMcastLimitRow;

typedef PMIB_MCAST_LIMIT_ROW PMibMcastLimitRow;

typedef _MIB_IPMCAST_SCOPE TMibIpmCastScope;

typedef PMIB_IPMCAST_SCOPE PMibIpmCastScope;

typedef _MIB_IPDESTROW TMibIpDestRow;

typedef PMIB_IPDESTROW PMibIpDestRow;

typedef _MIB_IPDESTTABLE TMibIpDestTable;

typedef PMIB_IPDESTTABLE PMibIpDestTable;

typedef _MIB_BEST_IF TMibBestIf;

typedef PMIB_BEST_IF PMibBestIf;

typedef _MIB_PROXYARP TMibProxyArp;

typedef PMIB_PROXYARP PMibProxyArp;

typedef _MIB_IFSTATUS TMibIfStatus;

typedef PMIB_IFSTATUS PMibIfStatus;

typedef _MIB_ROUTESTATE TMibRouteState;

typedef PMIB_ROUTESTATE PMibRouteState;

typedef _MIB_OPAQUE_INFO *PMibOpaqueInfo;

typedef _MIB_OPAQUE_INFO TMibOpaqueInfo;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iprtrmib */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_IPRTRMIB)
using namespace Winapi::Iprtrmib;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_IprtrmibHPP
