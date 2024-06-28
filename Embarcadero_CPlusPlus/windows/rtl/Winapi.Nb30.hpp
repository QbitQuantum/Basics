// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Nb30.pas' rev: 34.00 (Windows)

#ifndef Winapi_Nb30HPP
#define Winapi_Nb30HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Nb30
{
//-- forward type declarations -----------------------------------------------
struct TNCB;
struct TAdapterStatus;
struct TNameBuffer;
struct TSessionHeader;
struct TSessionBuffer;
struct TLanaEnum;
struct TFindNameHeader;
struct TFindNameBuffer;
struct TActionHeader;
//-- type declarations -------------------------------------------------------
typedef TNCB *PNCB;

typedef void __fastcall (*TNCBPostProc)(PNCB P);

struct DECLSPEC_DRECORD TNCB
{
public:
	char ncb_command;
	char ncb_retcode;
	char ncb_lsn;
	char ncb_num;
	char *ncb_buffer;
	System::Word ncb_length;
	System::StaticArray<char, 16> ncb_callname;
	System::StaticArray<char, 16> ncb_name;
	char ncb_rto;
	char ncb_sto;
	TNCBPostProc ncb_post;
	char ncb_lana_num;
	char ncb_cmd_cplt;
#ifndef _WIN64
	System::StaticArray<char, 10> ncb_reserve;
#else /* _WIN64 */
	System::StaticArray<char, 18> ncb_reserve;
#endif /* _WIN64 */
	NativeUInt ncb_event;
};


typedef TAdapterStatus *PAdapterStatus;

struct DECLSPEC_DRECORD TAdapterStatus
{
public:
	System::StaticArray<char, 6> adapter_address;
	char rev_major;
	char reserved0;
	char adapter_type;
	char rev_minor;
	System::Word duration;
	System::Word frmr_recv;
	System::Word frmr_xmit;
	System::Word iframe_recv_err;
	System::Word xmit_aborts;
	unsigned xmit_success;
	unsigned recv_success;
	System::Word iframe_xmit_err;
	System::Word recv_buff_unavail;
	System::Word t1_timeouts;
	System::Word ti_timeouts;
	unsigned reserved1;
	System::Word free_ncbs;
	System::Word max_cfg_ncbs;
	System::Word max_ncbs;
	System::Word xmit_buf_unavail;
	System::Word max_dgram_size;
	System::Word pending_sess;
	System::Word max_cfg_sess;
	System::Word max_sess;
	System::Word max_sess_pkt_size;
	System::Word name_count;
};


typedef TNameBuffer *PNameBuffer;

struct DECLSPEC_DRECORD TNameBuffer
{
public:
	System::StaticArray<char, 16> name;
	char name_num;
	char name_flags;
};


typedef TSessionHeader *PSessionHeader;

struct DECLSPEC_DRECORD TSessionHeader
{
public:
	char sess_name;
	char num_sess;
	char rcv_dg_outstanding;
	char rcv_any_outstanding;
};


typedef TSessionBuffer *PSessionBuffer;

struct DECLSPEC_DRECORD TSessionBuffer
{
public:
	char lsn;
	char state;
	System::StaticArray<char, 16> local_name;
	System::StaticArray<char, 16> remote_name;
	char rcvs_outstanding;
	char sends_outstanding;
};


typedef TLanaEnum *PLanaEnum;

struct DECLSPEC_DRECORD TLanaEnum
{
public:
	char length;
	System::StaticArray<char, 255> lana;
};


typedef TFindNameHeader *PFindNameHeader;

struct DECLSPEC_DRECORD TFindNameHeader
{
public:
	System::Word node_count;
	char reserved;
	char unique_group;
};


typedef TFindNameBuffer *PFindNameBuffer;

struct DECLSPEC_DRECORD TFindNameBuffer
{
public:
	char length;
	char access_control;
	char frame_control;
	System::StaticArray<char, 6> destination_addr;
	System::StaticArray<char, 6> source_addr;
	System::StaticArray<char, 18> routing_info;
};


typedef TActionHeader *PActionHeader;

struct DECLSPEC_DRECORD TActionHeader
{
public:
	int transport_id;
	System::Word action_code;
	System::Word reserved;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Nb30 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_NB30)
using namespace Winapi::Nb30;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Nb30HPP
