// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetIf.pas' rev: 34.00 (Android)

#ifndef Posix_NetifHPP
#define Posix_NetifHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.SysSocket.hpp>

//-- user supplied -----------------------------------------------------------
#include <net/if.h>

namespace Posix
{
namespace Netif
{
//-- forward type declarations -----------------------------------------------
struct _if_nameindex;
struct if_settings;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD _if_nameindex
{
public:
	unsigned if_index;
	char *if_name;
};


typedef _if_nameindex *PIfNameIndex;

typedef sync_serial_settings *Psync_serial_settings;

typedef te1_settings *Pte1_settings;

typedef raw_hdlc_proto *Praw_hdlc_proto;

typedef fr_proto *Pfr_proto;

typedef fr_proto_pvc *Pfr_proto_pvc;

typedef fr_proto_pvc_info *Pfr_proto_pvc_info;

typedef cisco_proto *Pcisco_proto;

typedef ifmap *Pifmap;

struct DECLSPEC_DRECORD if_settings
{
	
private:
	struct DECLSPEC_DRECORD _if_settings__1
	{
		
	public:
		union
		{
			struct 
			{
				te1_settings *te1;
			};
			struct 
			{
				sync_serial_settings *sync;
			};
			struct 
			{
				fr_proto_pvc_info *fr_pvc_info;
			};
			struct 
			{
				fr_proto_pvc *fr_pvc;
			};
			struct 
			{
				fr_proto *fr;
			};
			struct 
			{
				cisco_proto *cisco;
			};
			struct 
			{
				raw_hdlc_proto *raw_hdlc;
			};
			
		};
	};
	
	
	
public:
	unsigned _type;
	unsigned size;
	_if_settings__1 ifs_ifsu;
};


typedef ifreq *Pifreq;

typedef ifconf *Pifconf;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netif */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_NetifHPP
