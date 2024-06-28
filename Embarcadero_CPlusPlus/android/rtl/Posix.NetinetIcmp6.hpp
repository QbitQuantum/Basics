// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetinetIcmp6.pas' rev: 34.00 (Android)

#ifndef Posix_Netineticmp6HPP
#define Posix_Netineticmp6HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.NetinetIn.hpp>

//-- user supplied -----------------------------------------------------------
#include <netinet/icmp6.h>

namespace Posix
{
namespace Netineticmp6
{
//-- forward type declarations -----------------------------------------------
struct nd_opt_adv_interval;
struct nd_opt_home_agent_info;
//-- type declarations -------------------------------------------------------
typedef icmp6_filter *Picmp6_filter;

typedef icmp6_hdr *Picmp6_hdr;

typedef nd_router_solicit *Pnd_router_solicit;

typedef nd_router_advert *Pnd_router_advert;

typedef nd_neighbor_solicit *Pnd_neighbor_solicit;

typedef nd_neighbor_advert *Pnd_neighbor_advert;

typedef nd_redirect *Pnd_redirect;

typedef nd_opt_hdr *Pnd_opt_hdr;

typedef nd_opt_prefix_info *Pnd_opt_prefix_info;

typedef nd_opt_rd_hdr *Pnd_opt_rd_hdr;

typedef nd_opt_mtu *Pnd_opt_mtu;

typedef mld_hdr *Pmld_hdr;

typedef icmp6_router_renum *Picmp6_router_renum;

typedef rr_pco_match *Prr_pco_match;

typedef rr_pco_use *Prr_pco_use;

typedef rr_result *Prr_result;

struct DECLSPEC_DRECORD nd_opt_adv_interval
{
public:
	System::Byte nd_opt_adv_interval_type;
	System::Byte nd_opt_adv_interval_len;
	System::Word nd_opt_adv_interval_reserved;
	unsigned nd_opt_adv_interval_ival;
};


typedef nd_opt_adv_interval *Pnd_opt_adv_interval;

struct DECLSPEC_DRECORD nd_opt_home_agent_info
{
public:
	System::Byte nd_opt_home_agent_info_type;
	System::Byte nd_opt_home_agent_info_len;
	System::Word nd_opt_home_agent_info_reserved;
	short nd_opt_home_agent_info_preference;
	System::Word nd_opt_home_agent_info_lifetime;
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 _ICMP6_FILTER = System::Int8(0x1);
static constexpr System::Byte _ND_ROUTER_SOLICIT = System::Byte(0x85);
static constexpr System::Byte _ND_ROUTER_ADVERT = System::Byte(0x86);
static constexpr System::Byte _ND_NEIGHBOR_SOLICIT = System::Byte(0x87);
static constexpr System::Byte _ND_NEIGHBOR_ADVERT = System::Byte(0x88);
static constexpr System::Byte _ND_REDIRECT = System::Byte(0x89);
}	/* namespace Netineticmp6 */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_Netineticmp6HPP
