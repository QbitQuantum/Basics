// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdStackConsts.pas' rev: 34.00 (Android)

#ifndef IdstackconstsHPP
#define IdstackconstsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdVCLPosixSupplemental.hpp>
#include <Posix.Errno.hpp>
#include <Posix.NetDB.hpp>
#include <Posix.NetinetIn.hpp>
#include <Posix.SysSocket.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idstackconsts
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef int TIdStackSocketHandle;

typedef int TIdSocketType;

typedef int TIdSocketProtocol;

typedef int TIdSocketOption;

typedef int TIdSocketOptionLevel;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int Id_SO_True;
extern DELPHI_PACKAGE int Id_SO_False;
static constexpr System::Int8 Id_IPV6_UNICAST_HOPS = System::Int8(0x10);
static constexpr System::Int8 Id_IPV6_MULTICAST_IF = System::Int8(0x11);
static constexpr System::Int8 Id_IPV6_MULTICAST_HOPS = System::Int8(0x12);
static constexpr System::Int8 Id_IPV6_MULTICAST_LOOP = System::Int8(0x13);
static constexpr System::Int8 Id_IPV6_ADD_MEMBERSHIP = System::Int8(0x14);
static constexpr System::Int8 Id_IPV6_DROP_MEMBERSHIP = System::Int8(0x15);
static constexpr System::Int8 Id_IPV6_PKTINFO = System::Int8(0x32);
static constexpr System::Int8 Id_IPV6_HOPLIMIT = System::Int8(0x34);
static constexpr System::Int8 Id_IP_MULTICAST_TTL = System::Int8(0x21);
static constexpr System::Int8 Id_IP_MULTICAST_LOOP = System::Int8(0x22);
static constexpr System::Int8 Id_IP_ADD_MEMBERSHIP = System::Int8(0x23);
static constexpr System::Int8 Id_IP_DROP_MEMBERSHIP = System::Int8(0x24);
static constexpr System::Int8 Id_IP_HDR_INCLUDED = System::Int8(0x3);
static constexpr System::Int8 TCP_NODELAY = System::Int8(0x1);
static constexpr System::Int8 Id_PF_INET4 = System::Int8(0x2);
static constexpr System::Int8 Id_PF_INET6 = System::Int8(0xa);
static constexpr int Id_SOCK_UNKNOWN = int(0);
static constexpr int Id_SOCK_STREAM = int(1);
static constexpr int Id_SOCK_DGRAM = int(2);
static constexpr int Id_SOCK_RAW = int(3);
static constexpr System::Int8 Id_SOCK_SEQPACKET = System::Int8(0x5);
static constexpr System::Int8 Id_IPPROTO_GGP = System::Int8(0x3);
static constexpr System::Int8 Id_IPPROTO_ICMP = System::Int8(0x1);
static constexpr System::Int8 Id_IPPROTO_ICMPV6 = System::Int8(0x3a);
static constexpr System::Int8 Id_IPPROTO_IP = System::Int8(0x0);
static constexpr System::Int8 Id_IPPROTO_IPv6 = System::Int8(0x29);
static constexpr System::Int8 Id_IPPROTO_ND = System::Int8(0x4d);
static constexpr System::Int8 Id_IPPROTO_PUP = System::Int8(0xc);
static constexpr System::Byte Id_IPPROTO_RAW = System::Byte(0xff);
static constexpr System::Int8 Id_IPPROTO_TCP = System::Int8(0x6);
static constexpr System::Int8 Id_IPPROTO_UDP = System::Int8(0x11);
static constexpr System::Word Id_IPPROTO_MAX = System::Word(0x100);
static constexpr System::Int8 Id_SOL_SOCKET = System::Int8(0x1);
static constexpr System::Int8 Id_SOL_IP = System::Int8(0x0);
static constexpr System::Int8 Id_SOL_IPv6 = System::Int8(0x29);
static constexpr System::Int8 Id_SOL_TCP = System::Int8(0x6);
static constexpr System::Int8 Id_SOL_UDP = System::Int8(0x11);
static constexpr System::Int8 Id_SO_BROADCAST = System::Int8(0x6);
static constexpr System::Int8 Id_SO_DEBUG = System::Int8(0x1);
static constexpr System::Int8 Id_SO_DONTLINGER = System::Int8(-14);
static constexpr System::Int8 Id_SO_DONTROUTE = System::Int8(0x5);
static constexpr System::Int8 Id_SO_ERROR = System::Int8(0x4);
static constexpr System::Int8 Id_SO_KEEPALIVE = System::Int8(0x9);
static constexpr System::Int8 Id_SO_LINGER = System::Int8(0xd);
static constexpr System::Int8 Id_SO_OOBINLINE = System::Int8(0xa);
static constexpr System::Int8 Id_SO_RCVBUF = System::Int8(0x8);
static constexpr System::Int8 Id_SO_REUSEADDR = System::Int8(0x2);
static constexpr System::Int8 Id_SO_SNDBUF = System::Int8(0x7);
static constexpr System::Int8 Id_SO_TYPE = System::Int8(0x3);
static constexpr System::Int8 Id_SO_RCVTIMEO = System::Int8(0x14);
static constexpr System::Int8 Id_SO_SNDTIMEO = System::Int8(0x15);
static constexpr System::Int8 Id_SO_IP_TTL = System::Int8(0x2);
static constexpr System::Int8 Id_INADDR_ANY = System::Int8(0x0);
static constexpr unsigned Id_INADDR_NONE = unsigned(0xffffffff);
static constexpr System::Int8 INVALID_SOCKET = System::Int8(-1);
static constexpr System::Int8 SOCKET_ERROR = System::Int8(-1);
static constexpr System::Int8 Id_TCP_NODELAY = System::Int8(0x1);
static constexpr System::Int8 Id_INVALID_SOCKET = System::Int8(-1);
static constexpr System::Int8 Id_SOCKET_ERROR = System::Int8(-1);
static constexpr System::Int8 Id_SOCKETOPTIONLEVEL_TCP = System::Int8(0x6);
static constexpr System::Int8 Id_TCP_NOPUSH = System::Int8(0x4);
static constexpr System::Int8 Id_SD_Recv = System::Int8(0x0);
static constexpr System::Int8 Id_SD_Send = System::Int8(0x1);
static constexpr System::Int8 Id_SD_Both = System::Int8(0x2);
static constexpr System::Int8 Id_WSAEINTR = System::Int8(0x4);
static constexpr System::Int8 Id_WSAEBADF = System::Int8(0x9);
static constexpr System::Int8 Id_WSAEACCES = System::Int8(0xd);
static constexpr System::Int8 Id_WSAEFAULT = System::Int8(0xe);
static constexpr System::Int8 Id_WSAEINVAL = System::Int8(0x16);
static constexpr System::Int8 Id_WSAEMFILE = System::Int8(0x18);
static constexpr System::Int8 Id_WSAEAGAIN = System::Int8(0xb);
static constexpr System::Int8 Id_WSAEWOULDBLOCK = System::Int8(0xb);
static constexpr System::Int8 Id_WSAEINPROGRESS = System::Int8(0x73);
static constexpr System::Int8 Id_WSAEALREADY = System::Int8(0x72);
static constexpr System::Int8 Id_WSAENOTSOCK = System::Int8(0x58);
static constexpr System::Int8 Id_WSAEDESTADDRREQ = System::Int8(0x59);
static constexpr System::Int8 Id_WSAEMSGSIZE = System::Int8(0x5a);
static constexpr System::Int8 Id_WSAEPROTOTYPE = System::Int8(0x5b);
static constexpr System::Int8 Id_WSAENOPROTOOPT = System::Int8(0x5c);
static constexpr System::Int8 Id_WSAEPROTONOSUPPORT = System::Int8(0x5d);
static constexpr System::Int8 Id_WSAESOCKTNOSUPPORT = System::Int8(0x2c);
static constexpr System::Int8 Id_WSAEOPNOTSUPP = System::Int8(0x5f);
static constexpr System::Int8 Id_WSAEPFNOSUPPORT = System::Int8(0x2e);
static constexpr System::Int8 Id_WSAEAFNOSUPPORT = System::Int8(0x61);
static constexpr System::Int8 Id_WSAEADDRINUSE = System::Int8(0x62);
static constexpr System::Int8 Id_WSAEADDRNOTAVAIL = System::Int8(0x63);
static constexpr System::Int8 Id_WSAENETDOWN = System::Int8(0x64);
static constexpr System::Int8 Id_WSAENETUNREACH = System::Int8(0x65);
static constexpr System::Int8 Id_WSAENETRESET = System::Int8(0x66);
static constexpr System::Int8 Id_WSAECONNABORTED = System::Int8(0x67);
static constexpr System::Int8 Id_WSAECONNRESET = System::Int8(0x68);
static constexpr System::Int8 Id_WSAENOBUFS = System::Int8(0x69);
static constexpr System::Int8 Id_WSAEISCONN = System::Int8(0x6a);
static constexpr System::Int8 Id_WSAENOTCONN = System::Int8(0x6b);
static constexpr System::Int8 Id_WSAESHUTDOWN = System::Int8(0x3a);
static constexpr System::Int8 Id_WSAETOOMANYREFS = System::Int8(0x3b);
static constexpr System::Int8 Id_WSAETIMEDOUT = System::Int8(0x6e);
static constexpr System::Int8 Id_WSAECONNREFUSED = System::Int8(0x6f);
static constexpr System::Int8 Id_WSAELOOP = System::Int8(0x28);
static constexpr System::Int8 Id_WSAENAMETOOLONG = System::Int8(0x24);
static constexpr System::Int8 Id_WSAEHOSTDOWN = System::Int8(0x40);
static constexpr System::Int8 Id_WSAEHOSTUNREACH = System::Int8(0x71);
static constexpr System::Int8 Id_WSAENOTEMPTY = System::Int8(0x27);
}	/* namespace Idstackconsts */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSTACKCONSTS)
using namespace Idstackconsts;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdstackconstsHPP
