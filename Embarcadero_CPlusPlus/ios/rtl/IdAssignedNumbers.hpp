// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAssignedNumbers.pas' rev: 34.00 (iOS)

#ifndef IdassignednumbersHPP
#define IdassignednumbersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idassignednumbers
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 IdPORT_TCPMUX = System::Int8(0x1);
static constexpr System::Int8 IdPORT_COMPRESSNET_MGM = System::Int8(0x2);
static constexpr System::Int8 IdPORT_COMPRESSNET_CMP = System::Int8(0x3);
static constexpr System::Int8 IdPORT_RJE = System::Int8(0x5);
static constexpr System::Int8 IdPORT_ECHO = System::Int8(0x7);
static constexpr System::Int8 IdPORT_DISCARD = System::Int8(0x9);
static constexpr System::Int8 IdPORT_SYSTAT = System::Int8(0xb);
static constexpr System::Int8 IdPORT_DAYTIME = System::Int8(0xd);
static constexpr System::Int8 IdPORT_NETSTAT = System::Int8(0xf);
static constexpr System::Int8 IdPORT_QOTD = System::Int8(0x11);
static constexpr System::Int8 IdPORT_MSP = System::Int8(0x12);
static constexpr System::Int8 IdPORT_CHARGEN = System::Int8(0x13);
static constexpr System::Int8 IdPORT_FTP_DATA = System::Int8(0x14);
static constexpr System::Int8 IdPORT_FTP = System::Int8(0x15);
static constexpr System::Int8 IdPORT_SSH = System::Int8(0x16);
static constexpr System::Int8 IdPORT_TELNET = System::Int8(0x17);
static constexpr System::Int8 IdPORT_ANYTERMINIL = System::Int8(0x18);
static constexpr System::Int8 IdPORT_SMTP = System::Int8(0x19);
static constexpr System::Int8 IdPORT_NSW_FE = System::Int8(0x1b);
static constexpr System::Int8 IdPORT_MSG_ICMP = System::Int8(0x1d);
static constexpr System::Int8 IdPORT_MSG_AUTH = System::Int8(0x1f);
static constexpr System::Int8 IdPORT_DSP = System::Int8(0x21);
static constexpr System::Int8 IdPORT_ANYPRINTER = System::Int8(0x22);
static constexpr System::Int8 IdPORT_TIME = System::Int8(0x25);
static constexpr System::Int8 IdPORT_RAP = System::Int8(0x26);
static constexpr System::Int8 IdPORT_RLP = System::Int8(0x27);
static constexpr System::Int8 IdPORT_GRAPHICS = System::Int8(0x29);
static constexpr System::Int8 IdPORT_NAMESERVER = System::Int8(0x2a);
static constexpr System::Int8 IdPORT_WHOIS = System::Int8(0x2b);
static constexpr System::Int8 IdPORT_MPM_FLAGS = System::Int8(0x2c);
static constexpr System::Int8 IdPORT_MPM = System::Int8(0x2d);
static constexpr System::Int8 IdPORT_MPM_SND = System::Int8(0x2e);
static constexpr System::Int8 IdPORT_NI_FTP = System::Int8(0x2f);
static constexpr System::Int8 IdPORT_AUDITD = System::Int8(0x30);
static constexpr System::Int8 IdPORT_BBN_LOGIN = System::Int8(0x31);
static constexpr System::Int8 IdPORT_RE_MAIL_CK = System::Int8(0x32);
static constexpr System::Int8 IdPORT_LA_MAINT = System::Int8(0x33);
static constexpr System::Int8 IdPORT_XNS_TIME = System::Int8(0x34);
static constexpr System::Int8 IdPORT_DOMAIN = System::Int8(0x35);
static constexpr System::Int8 IdPORT_XNS_CH = System::Int8(0x36);
static constexpr System::Int8 IdPORT_ISI_GL = System::Int8(0x37);
static constexpr System::Int8 IdPORT_XNS_AUTH = System::Int8(0x38);
static constexpr System::Int8 IdPORT_ANYPRIVATE_TERMINAL = System::Int8(0x39);
static constexpr System::Int8 IdPORT_XNS_MAIL = System::Int8(0x3a);
static constexpr System::Int8 IdPORT_ANY_FILE = System::Int8(0x3b);
static constexpr System::Int8 IdPORT_NI_MAIL = System::Int8(0x3d);
static constexpr System::Int8 IdPORT_ACAS = System::Int8(0x3e);
static constexpr System::Int8 IdPORT_WHOIS_PLUS = System::Int8(0x3f);
static constexpr System::Int8 IdPORT_COVIA = System::Int8(0x40);
static constexpr System::Int8 IdPORT_TACACS_DS = System::Int8(0x41);
static constexpr System::Int8 IdPORT_SQLNET = System::Int8(0x42);
static constexpr System::Int8 IdPORT_BOOTPS = System::Int8(0x43);
static constexpr System::Int8 IdPORT_BOOTPC = System::Int8(0x44);
static constexpr System::Int8 IdPORT_TFTP = System::Int8(0x45);
static constexpr System::Int8 IdPORT_GOPHER = System::Int8(0x46);
static constexpr System::Int8 IdPORT_NETRJS1 = System::Int8(0x47);
static constexpr System::Int8 IdPORT_NETRJS2 = System::Int8(0x48);
static constexpr System::Int8 IdPORT_NETRJS3 = System::Int8(0x49);
static constexpr System::Int8 IdPORT_NETRJS4 = System::Int8(0x4a);
static constexpr System::Int8 IdPORT_ANYDIAL = System::Int8(0x4b);
static constexpr System::Int8 IdPORT_DEOS = System::Int8(0x4c);
static constexpr System::Int8 IdPORT_ANYRJE = System::Int8(0x4d);
static constexpr System::Int8 IdPORT_VETTCP = System::Int8(0x4e);
static constexpr System::Int8 IdPORT_FINGER = System::Int8(0x4f);
static constexpr System::Int8 IdPORT_HTTP = System::Int8(0x50);
static constexpr System::Int8 IdPORT_HOSTS2_NS = System::Int8(0x51);
static constexpr System::Int8 IdPORT_XFER = System::Int8(0x52);
static constexpr System::Int8 IdPORT_MIT_ML_DEV = System::Int8(0x53);
static constexpr System::Int8 IdPORT_CTF = System::Int8(0x54);
static constexpr System::Int8 IdPORT_MIT_ML_DEV2 = System::Int8(0x55);
static constexpr System::Int8 IdPORT_MFCOBOL = System::Int8(0x56);
static constexpr System::Int8 IdPORT_ANYTERMINALLINK = System::Int8(0x57);
static constexpr System::Int8 IdPORT_KERBEROS = System::Int8(0x58);
static constexpr System::Int8 IdPORT_SU_MIT_TG = System::Int8(0x59);
static constexpr System::Int8 IdPORT_DNSIX = System::Int8(0x5a);
static constexpr System::Int8 IdPORT_MIT_DOV = System::Int8(0x5b);
static constexpr System::Int8 IdPORT_NPP = System::Int8(0x5c);
static constexpr System::Int8 IdPORT_DCP = System::Int8(0x5d);
static constexpr System::Int8 IdPORT_OBJCALL = System::Int8(0x5e);
static constexpr System::Int8 IdPORT_SUPDUP = System::Int8(0x5f);
static constexpr System::Int8 IdPORT_DIXIE = System::Int8(0x60);
static constexpr System::Int8 IdPORT_SWIFT_RVF = System::Int8(0x61);
static constexpr System::Int8 IdPORT_TACNEWS = System::Int8(0x62);
static constexpr System::Int8 IdPORT_METAGRAM = System::Int8(0x63);
static constexpr System::Int8 IdPORT_NEWACCT = System::Int8(0x64);
static constexpr System::Int8 IdPORT_HOSTNAME = System::Int8(0x65);
static constexpr System::Int8 IdPORT_ISO_TSAP = System::Int8(0x66);
static constexpr System::Int8 IdPORT_GPPITNP = System::Int8(0x67);
static constexpr System::Int8 IdPORT_ACR_NAME = System::Int8(0x68);
static constexpr System::Int8 IdPORT_CSNET_NS = System::Int8(0x69);
static constexpr System::Int8 IdPORT_3COM_TSMUX = System::Int8(0x6a);
static constexpr System::Int8 IdPORT_RTELNET = System::Int8(0x6b);
static constexpr System::Int8 IdPORT_SNAGAS = System::Int8(0x6c);
static constexpr System::Int8 IdPORT_POP2 = System::Int8(0x6d);
static constexpr System::Int8 IdPORT_POP3 = System::Int8(0x6e);
static constexpr System::Int8 IdPORT_SUNRPC = System::Int8(0x6f);
static constexpr System::Int8 IdPORT_McIDAS = System::Int8(0x70);
static constexpr System::Int8 IdPORT_AUTH = System::Int8(0x71);
static constexpr System::Int8 IdPORT_AUDIONEWS = System::Int8(0x72);
static constexpr System::Int8 IdPORT_SFTP = System::Int8(0x73);
static constexpr System::Int8 IdPORT_ANSANOTIFY = System::Int8(0x74);
static constexpr System::Int8 IdPORT_UUCP_PATH = System::Int8(0x75);
static constexpr System::Int8 IdPORT_SQLSERV = System::Int8(0x76);
static constexpr System::Int8 IdPORT_NNTP = System::Int8(0x77);
static constexpr System::Int8 IdPORT_CFDPTKT = System::Int8(0x78);
static constexpr System::Int8 IdPORT_ERPC = System::Int8(0x79);
static constexpr System::Int8 IdPORT_SMAKYNET = System::Int8(0x7a);
static constexpr System::Int8 IdPORT_SNTP = System::Int8(0x7b);
static constexpr System::Int8 IdPORT_ANASTRADER = System::Int8(0x7c);
static constexpr System::Int8 IdPORT_LOCUS_MAP = System::Int8(0x7d);
static constexpr System::Int8 IdPORT_UNITARY = System::Int8(0x7e);
static constexpr System::Int8 IdPORT_locus_con = System::Int8(0x7f);
static constexpr System::Byte IdPORT_GSS_XLICEN = System::Byte(0x80);
static constexpr System::Byte IdPORT_PWDGEN = System::Byte(0x81);
static constexpr System::Byte IdPORT_CISCO_FNA = System::Byte(0x82);
static constexpr System::Byte IdPORT_cisco_tna = System::Byte(0x83);
static constexpr System::Byte IdPORT_cisco_sys = System::Byte(0x84);
static constexpr System::Byte IdPORT_statsrv = System::Byte(0x85);
static constexpr System::Byte IdPORT_ingres_net = System::Byte(0x86);
static constexpr System::Byte IdPORT_loc_srv = System::Byte(0x87);
static constexpr System::Byte IdPORT_profile = System::Byte(0x88);
static constexpr System::Byte IdPORT_netbios_ns = System::Byte(0x89);
static constexpr System::Byte IdPORT_netbios_dgm = System::Byte(0x8a);
static constexpr System::Byte IdPORT_netbios_ssn = System::Byte(0x8b);
static constexpr System::Byte IdPORT_emfis_data = System::Byte(0x8c);
static constexpr System::Byte IdPORT_emfis_cntl = System::Byte(0x8d);
static constexpr System::Byte IdPORT_bl_idm = System::Byte(0x8e);
static constexpr System::Byte IdPORT_IMAP4 = System::Byte(0x8f);
static constexpr System::Byte IdPORT_news = System::Byte(0x90);
static constexpr System::Byte IdPORT_uaac = System::Byte(0x91);
static constexpr System::Byte IdPORT_iso_tp0 = System::Byte(0x92);
static constexpr System::Byte IdPORT_iso_ip = System::Byte(0x93);
static constexpr System::Byte IdPORT_cronus = System::Byte(0x94);
static constexpr System::Byte IdPORT_aed_512 = System::Byte(0x95);
static constexpr System::Byte IdPORT_sql_net = System::Byte(0x96);
static constexpr System::Byte IdPORT_hems = System::Byte(0x97);
static constexpr System::Byte IdPORT_bftp = System::Byte(0x98);
static constexpr System::Byte IdPORT_sgmp = System::Byte(0x99);
static constexpr System::Byte IdPORT_netsc_prod = System::Byte(0x9a);
static constexpr System::Byte IdPORT_netsc_dev = System::Byte(0x9b);
static constexpr System::Byte IdPORT_sqlsrv = System::Byte(0x9c);
static constexpr System::Byte IdPORT_knet_cmp = System::Byte(0x9d);
static constexpr System::Byte IdPORT_pcmail_srv = System::Byte(0x9e);
static constexpr System::Byte IdPORT_nss_routing = System::Byte(0x9f);
static constexpr System::Byte IdPORT_sgmp_traps = System::Byte(0xa0);
static constexpr System::Byte IdPORT_snmp = System::Byte(0xa1);
static constexpr System::Byte IdPORT_snmptrap = System::Byte(0xa2);
static constexpr System::Byte IdPORT_cmip_man = System::Byte(0xa3);
static constexpr System::Byte IdPORT_cmip_agent = System::Byte(0xa4);
static constexpr System::Byte IdPORT_xns_courier = System::Byte(0xa5);
static constexpr System::Byte IdPORT_s_net = System::Byte(0xa6);
static constexpr System::Byte IdPORT_namp = System::Byte(0xa7);
static constexpr System::Byte IdPORT_rsvd = System::Byte(0xa8);
static constexpr System::Byte IdPORT_send = System::Byte(0xa9);
static constexpr System::Byte IdPORT_print_srv = System::Byte(0xaa);
static constexpr System::Byte IdPORT_multiplex = System::Byte(0xab);
static constexpr System::Byte IdPORT_cl_1 = System::Byte(0xac);
static constexpr System::Byte IdPORT_xyplex_mux = System::Byte(0xad);
static constexpr System::Byte IdPORT_mailq = System::Byte(0xae);
static constexpr System::Byte IdPORT_vmnet = System::Byte(0xaf);
static constexpr System::Byte IdPORT_genrad_mux = System::Byte(0xb0);
static constexpr System::Byte IdPORT_xdmcp = System::Byte(0xb1);
static constexpr System::Byte IdPORT_NextStep = System::Byte(0xb2);
static constexpr System::Byte IdPORT_bgp = System::Byte(0xb3);
static constexpr System::Byte IdPORT_ris = System::Byte(0xb4);
static constexpr System::Byte IdPORT_unify = System::Byte(0xb5);
static constexpr System::Byte IdPORT_audit = System::Byte(0xb6);
static constexpr System::Byte IdPORT_ocbinder = System::Byte(0xb7);
static constexpr System::Byte IdPORT_ocserver = System::Byte(0xb8);
static constexpr System::Byte IdPORT_remote_kis = System::Byte(0xb9);
static constexpr System::Byte IdPORT_kis = System::Byte(0xba);
static constexpr System::Byte IdPORT_aci = System::Byte(0xbb);
static constexpr System::Byte IdPORT_mumps = System::Byte(0xbc);
static constexpr System::Byte IdPORT_qft = System::Byte(0xbd);
static constexpr System::Byte IdPORT_gacp = System::Byte(0xbe);
static constexpr System::Byte IdPORT_prospero = System::Byte(0xbf);
static constexpr System::Byte IdPORT_osu_nms = System::Byte(0xc0);
static constexpr System::Byte IdPORT_srmp = System::Byte(0xc1);
static constexpr System::Byte IdPORT_dn6_nlm_aud = System::Byte(0xc3);
static constexpr System::Byte IdPORT_dn6_smm_red = System::Byte(0xc4);
static constexpr System::Byte IdPORT_dls = System::Byte(0xc5);
static constexpr System::Byte IdPORT_dls_mon = System::Byte(0xc6);
static constexpr System::Byte IdPORT_smux = System::Byte(0xc7);
static constexpr System::Byte IdPORT_src = System::Byte(0xc8);
static constexpr System::Byte IdPORT_at_rtmp = System::Byte(0xc9);
static constexpr System::Byte IdPORT_at_nbp = System::Byte(0xca);
static constexpr System::Byte IdPORT_at_3 = System::Byte(0xcb);
static constexpr System::Byte IdPORT_at_echo = System::Byte(0xcc);
static constexpr System::Byte IdPORT_at_5 = System::Byte(0xcd);
static constexpr System::Byte IdPORT_at_zis = System::Byte(0xce);
static constexpr System::Byte IdPORT_at_7 = System::Byte(0xcf);
static constexpr System::Byte IdPORT_at_8 = System::Byte(0xd0);
static constexpr System::Byte IdPORT_qmtp = System::Byte(0xd1);
static constexpr System::Byte IdPORT_z39_50 = System::Byte(0xd2);
static constexpr System::Byte IdPORT_914c_g = System::Byte(0xd3);
static constexpr System::Byte IdPORT_anet = System::Byte(0xd4);
static constexpr System::Byte IdPORT_ipx = System::Byte(0xd5);
static constexpr System::Byte IdPORT_vmpwscs = System::Byte(0xd6);
static constexpr System::Byte IdPORT_softpc = System::Byte(0xd7);
static constexpr System::Byte IdPORT_CAIlic = System::Byte(0xd8);
static constexpr System::Byte IdPORT_dbase = System::Byte(0xd9);
static constexpr System::Byte IdPORT_mpp = System::Byte(0xda);
static constexpr System::Byte IdPORT_uarps = System::Byte(0xdb);
static constexpr System::Byte IdPORT_imap3 = System::Byte(0xdc);
static constexpr System::Byte IdPORT_fln_spx = System::Byte(0xdd);
static constexpr System::Byte IdPORT_rsh_spx = System::Byte(0xde);
static constexpr System::Byte IdPORT_cdc = System::Byte(0xdf);
static constexpr System::Byte Id_PORT_masqdialer = System::Byte(0xe0);
static constexpr System::Byte Id_PORT_direct = System::Byte(0xf2);
static constexpr System::Byte IdPORT_sur_meas = System::Byte(0xf3);
static constexpr System::Byte Id_PORT_inbusiness = System::Byte(0xf4);
static constexpr System::Byte IdPORT_link = System::Byte(0xf5);
static constexpr System::Byte IdPORT_dsp3270 = System::Byte(0xf6);
static constexpr System::Word IdPORT_pdap = System::Word(0x158);
static constexpr System::Word IdPORT_pawserv = System::Word(0x159);
static constexpr System::Word IdPORT_zserv = System::Word(0x15a);
static constexpr System::Word IdPORT_fatserv = System::Word(0x15b);
static constexpr System::Word IdPORT_csi_sgwp = System::Word(0x15c);
static constexpr System::Word Id_PORT_mftp = System::Word(0x15d);
static constexpr System::Word Id_PORT_matip_type_a = System::Word(0x15e);
static constexpr System::Word Id_PORT_matip_type_b = System::Word(0x15f);
static constexpr System::Word Id_PORT_dtag_ste_sb = System::Word(0x160);
static constexpr System::Word Id_PORT_ndsauth = System::Word(0x161);
static constexpr System::Word Id_PORT_bh611 = System::Word(0x162);
static constexpr System::Word Id_PORT_datex_asn = System::Word(0x163);
static constexpr System::Word Id_PORT_cloanto_net_1 = System::Word(0x164);
static constexpr System::Word Id_PORT_bhevent = System::Word(0x165);
static constexpr System::Word Id_PORT_shrinkwrap = System::Word(0x166);
static constexpr System::Word Id_PORT_nsrmp = System::Word(0x167);
static constexpr System::Word Id_PORT_scoi2odialog = System::Word(0x168);
static constexpr System::Word Id_PORT_semantix = System::Word(0x169);
static constexpr System::Word Id_PORT_srssend = System::Word(0x16a);
static constexpr System::Word Id_PORT_rsvp_tunnel = System::Word(0x16b);
static constexpr System::Word Id_PORT_aurora_cmgr = System::Word(0x16c);
static constexpr System::Word Id_PORT_dtk = System::Word(0x16d);
static constexpr System::Word Id_PORT_odmr = System::Word(0x16e);
static constexpr System::Word Id_PORT_mortgageware = System::Word(0x16f);
static constexpr System::Word Id_PORT_qbikgdp = System::Word(0x170);
static constexpr System::Word Id_PORT_rpc2portmap = System::Word(0x171);
static constexpr System::Word Id_PORT_codaauth2 = System::Word(0x172);
static constexpr System::Word IdPORT_clearcase = System::Word(0x173);
static constexpr System::Word IdPORT_ulistserv = System::Word(0x174);
static constexpr System::Word IdPORT_legent_1 = System::Word(0x175);
static constexpr System::Word IdPORT_legent_2 = System::Word(0x176);
static constexpr System::Word IdPORT_hassle = System::Word(0x177);
static constexpr System::Word IdPORT_nip = System::Word(0x178);
static constexpr System::Word IdPORT_tnETOS = System::Word(0x179);
static constexpr System::Word IdPORT_dsETOS = System::Word(0x17a);
static constexpr System::Word IdPORT_is99c = System::Word(0x17b);
static constexpr System::Word IdPORT_is99s = System::Word(0x17c);
static constexpr System::Word IdPORT_hp_collector = System::Word(0x17d);
static constexpr System::Word IdPORT_hp_managed_node = System::Word(0x17e);
static constexpr System::Word IdPORT_hp_alarm_mgr = System::Word(0x17f);
static constexpr System::Word IdPORT_arns = System::Word(0x180);
static constexpr System::Word IdPORT_ibm_app = System::Word(0x181);
static constexpr System::Word IdPORT_asa = System::Word(0x182);
static constexpr System::Word IdPORT_aurp = System::Word(0x183);
static constexpr System::Word IdPORT_unidata_ldm = System::Word(0x184);
static constexpr System::Word IdPORT_ldap = System::Word(0x185);
static constexpr System::Word IdPORT_uis = System::Word(0x186);
static constexpr System::Word IdPORT_synotics_relay = System::Word(0x187);
static constexpr System::Word IdPORT_synotics_broker = System::Word(0x188);
static constexpr System::Word IdPORT_dis = System::Word(0x189);
static constexpr System::Word IdPORT_embl_ndt = System::Word(0x18a);
static constexpr System::Word IdPORT_etcp = System::Word(0x18b);
static constexpr System::Word IdPORT_netware_ip = System::Word(0x18c);
static constexpr System::Word IdPORT_mptn = System::Word(0x18d);
static constexpr System::Word IdPORT_kryptolan = System::Word(0x18e);
static constexpr System::Word IdPORT_iso_tsap_c2 = System::Word(0x18f);
static constexpr System::Word IdPORT_work_sol = System::Word(0x190);
static constexpr System::Word IdPORT_ups = System::Word(0x191);
static constexpr System::Word IdPORT_genie = System::Word(0x192);
static constexpr System::Word IdPORT_decap = System::Word(0x193);
static constexpr System::Word IdPORT_nced = System::Word(0x194);
static constexpr System::Word IdPORT_ncld = System::Word(0x195);
static constexpr System::Word IdPORT_imsp = System::Word(0x196);
static constexpr System::Word IdPORT_timbuktu = System::Word(0x197);
static constexpr System::Word IdPORT_prm_sm = System::Word(0x198);
static constexpr System::Word IdPORT_prm_nm = System::Word(0x199);
static constexpr System::Word IdPORT_decladebug = System::Word(0x19a);
static constexpr System::Word IdPORT_rmt = System::Word(0x19b);
static constexpr System::Word IdPORT_synoptics_trap = System::Word(0x19c);
static constexpr System::Word IdPORT_smsp = System::Word(0x19d);
static constexpr System::Word IdPORT_infoseek = System::Word(0x19e);
static constexpr System::Word IdPORT_bnet = System::Word(0x19f);
static constexpr System::Word IdPORT_silverplatter = System::Word(0x1a0);
static constexpr System::Word IdPORT_onmux = System::Word(0x1a1);
static constexpr System::Word IdPORT_hyper_g = System::Word(0x1a2);
static constexpr System::Word IdPORT_ariel1 = System::Word(0x1a3);
static constexpr System::Word IdPORT_smpte = System::Word(0x1a4);
static constexpr System::Word IdPORT_ariel2 = System::Word(0x1a5);
static constexpr System::Word IdPORT_ariel3 = System::Word(0x1a6);
static constexpr System::Word IdPORT_opc_job_start = System::Word(0x1a7);
static constexpr System::Word IdPORT_opc_job_track = System::Word(0x1a8);
static constexpr System::Word IdPORT_icad_el = System::Word(0x1a9);
static constexpr System::Word IdPORT_smartsdp = System::Word(0x1aa);
static constexpr System::Word IdPORT_svrloc = System::Word(0x1ab);
static constexpr System::Word IdPORT_ocs_cmu = System::Word(0x1ac);
static constexpr System::Word IdPORT_ocs_amu = System::Word(0x1ad);
static constexpr System::Word IdPORT_utmpsd = System::Word(0x1ae);
static constexpr System::Word IdPORT_utmpcd = System::Word(0x1af);
static constexpr System::Word IdPORT_iasd = System::Word(0x1b0);
static constexpr System::Word IdPORT_nnsp = System::Word(0x1b1);
static constexpr System::Word IdPORT_mobileip_agent = System::Word(0x1b2);
static constexpr System::Word IdPORT_mobilip_mn = System::Word(0x1b3);
static constexpr System::Word IdPORT_dna_cml = System::Word(0x1b4);
static constexpr System::Word IdPORT_comscm = System::Word(0x1b5);
static constexpr System::Word IdPORT_dsfgw = System::Word(0x1b6);
static constexpr System::Word IdPORT_dasp = System::Word(0x1b7);
static constexpr System::Word IdPORT_sgcp = System::Word(0x1b8);
static constexpr System::Word IdPORT_decvms_sysmgt = System::Word(0x1b9);
static constexpr System::Word IdPORT_cvc_hostd = System::Word(0x1ba);
static constexpr System::Word IdPORT_https = System::Word(0x1bb);
static constexpr System::Word IdPORT_npp2 = System::Word(0x1bc);
static constexpr System::Word IdPORT_microsoft_ds = System::Word(0x1bd);
static constexpr System::Word IdPORT_ddm_rdb = System::Word(0x1be);
static constexpr System::Word IdPORT_ddm_dfm = System::Word(0x1bf);
static constexpr System::Word IdPORT_ddm_byte = System::Word(0x1c0);
static constexpr System::Word IdPORT_as_servermap = System::Word(0x1c1);
static constexpr System::Word IdPORT_tserver = System::Word(0x1c2);
static constexpr System::Word IdPORT_sfs_smp_net = System::Word(0x1c3);
static constexpr System::Word IdPORT_sfs_config = System::Word(0x1c4);
static constexpr System::Word IdPORT_creativeserver = System::Word(0x1c5);
static constexpr System::Word IdPORT_contentserver = System::Word(0x1c6);
static constexpr System::Word IdPORT_creativepartnr = System::Word(0x1c7);
static constexpr System::Word IdPORT_macon_tcp = System::Word(0x1c8);
static constexpr System::Word IdPORT_scohelp = System::Word(0x1c9);
static constexpr System::Word IdPORT_appleqtc = System::Word(0x1ca);
static constexpr System::Word IdPORT_ampr_rcmd = System::Word(0x1cb);
static constexpr System::Word IdPORT_skronk = System::Word(0x1cc);
static constexpr System::Word IdPORT_datasurfsrv = System::Word(0x1cd);
static constexpr System::Word IdPORT_datasurfsrvsec = System::Word(0x1ce);
static constexpr System::Word IdPORT_alpes = System::Word(0x1cf);
static constexpr System::Word IdPORT_kpasswd = System::Word(0x1d0);
static constexpr System::Word IdPORT_ssmtp = System::Word(0x1d1);
static constexpr System::Word IdPORT_digital_vrc = System::Word(0x1d2);
static constexpr System::Word IdPORT_mylex_mapd = System::Word(0x1d3);
static constexpr System::Word IdPORT_photuris = System::Word(0x1d4);
static constexpr System::Word IdPORT_rcp = System::Word(0x1d5);
static constexpr System::Word IdPORT_scx_proxy = System::Word(0x1d6);
static constexpr System::Word IdPORT_mondex = System::Word(0x1d7);
static constexpr System::Word IdPORT_ljk_login = System::Word(0x1d8);
static constexpr System::Word IdPORT_hybrid_pop = System::Word(0x1d9);
static constexpr System::Word IdPORT_tn_tl_w1 = System::Word(0x1da);
static constexpr System::Word IdPORT_tn_tl_w2 = System::Word(0x1da);
static constexpr System::Word IdPORT_tcpnethaspsrv = System::Word(0x1db);
static constexpr System::Word IdPORT_tn_tl_fd1 = System::Word(0x1dc);
static constexpr System::Word IdPORT_ss7ns = System::Word(0x1dd);
static constexpr System::Word IdPORT_spsc = System::Word(0x1de);
static constexpr System::Word IdPORT_iafserver = System::Word(0x1df);
static constexpr System::Word IdPORT_iafdbase = System::Word(0x1e0);
static constexpr System::Word IdPORT_ph = System::Word(0x1e1);
static constexpr System::Word IdPORT_bgs_nsi = System::Word(0x1e2);
static constexpr System::Word IdPORT_ulpnet = System::Word(0x1e3);
static constexpr System::Word IdPORT_integra_sme = System::Word(0x1e4);
static constexpr System::Word IdPORT_powerburst = System::Word(0x1e5);
static constexpr System::Word IdPORT_avian = System::Word(0x1e6);
static constexpr System::Word IdPORT_saft = System::Word(0x1e7);
static constexpr System::Word IdPORT_gss_http = System::Word(0x1e8);
static constexpr System::Word IdPORT_nest_protocol = System::Word(0x1e9);
static constexpr System::Word IdPORT_micom_pfs = System::Word(0x1ea);
static constexpr System::Word IdPORT_go_login = System::Word(0x1eb);
static constexpr System::Word IdPORT_ticf_1 = System::Word(0x1ec);
static constexpr System::Word IdPORT_ticf_2 = System::Word(0x1ed);
static constexpr System::Word IdPORT_pov_ray = System::Word(0x1ee);
static constexpr System::Word IdPORT_intecourier = System::Word(0x1ef);
static constexpr System::Word Id_PORT_pim_rp_disc = System::Word(0x1f0);
static constexpr System::Word Id_PORT_dantz = System::Word(0x1f1);
static constexpr System::Word Id_PORT_siam = System::Word(0x1f2);
static constexpr System::Word Id_PORT_ISO_ILL = System::Word(0x1f3);
static constexpr System::Word Id_PORT_isakmp = System::Word(0x1f4);
static constexpr System::Word Id_PORT_stmf = System::Word(0x1f5);
static constexpr System::Word Id_PORT_asa_appl_proto = System::Word(0x1f6);
static constexpr System::Word Id_PORT_intrinsa = System::Word(0x1f7);
static constexpr System::Word Id_PORT_citadel = System::Word(0x1f8);
static constexpr System::Word Id_PORT_mailbox_lm = System::Word(0x1f9);
static constexpr System::Word Id_PORT_ohimsrv = System::Word(0x1fa);
static constexpr System::Word Id_PORT_crs = System::Word(0x1fb);
static constexpr System::Word Id_PORT_xvttp = System::Word(0x1fc);
static constexpr System::Word Id_PORT_snare = System::Word(0x1fd);
static constexpr System::Word Id_PORT_FirstClass = System::Word(0x1fe);
static constexpr System::Word Id_PORT_passgo = System::Word(0x1ff);
static constexpr System::Word Id_PORT_exec = System::Word(0x200);
static constexpr System::Word Id_PORT_biff = System::Word(0x200);
static constexpr System::Word Id_PORT_login = System::Word(0x201);
static constexpr System::Word IdPORT_who = System::Word(0x201);
static constexpr System::Word IdPORT_cmd = System::Word(0x202);
static constexpr System::Word IdPORT_syslog = System::Word(0x202);
static constexpr System::Word IdPORT_LPD = System::Word(0x203);
static constexpr System::Word IdPORT_talk = System::Word(0x205);
static constexpr System::Word IdPORT_ntalk = System::Word(0x206);
static constexpr System::Word IdPORT_utime = System::Word(0x207);
static constexpr System::Word IdPORT_efs = System::Word(0x208);
static constexpr System::Word IdPORT_router = System::Word(0x208);
static constexpr System::Word IdPORT_timed = System::Word(0x20d);
static constexpr System::Word IdPORT_tempo = System::Word(0x20e);
static constexpr System::Word IdPORT_courier = System::Word(0x212);
static constexpr System::Word IdPORT_conference = System::Word(0x213);
static constexpr System::Word IdPORT_netnews = System::Word(0x214);
static constexpr System::Word IdPORT_netwall = System::Word(0x215);
static constexpr System::Word IdPORT_apertus_ldp = System::Word(0x21b);
static constexpr System::Word IdPORT_uucp = System::Word(0x21c);
static constexpr System::Word IdPORT_uucp_rlogin = System::Word(0x21d);
static constexpr System::Word IdPORT_klogin = System::Word(0x21f);
static constexpr System::Word IdPORT_kshell = System::Word(0x220);
static constexpr System::Word IdPORT_appleqtcsrvr = System::Word(0x221);
static constexpr System::Word IdPORT_dhcp_client_v6 = System::Word(0x222);
static constexpr System::Word IdPORT_dhcp_server_v6 = System::Word(0x223);
static constexpr System::Word Id_PORT_afpovertcp = System::Word(0x224);
static constexpr System::Word Id_PORT_idfp = System::Word(0x225);
static constexpr System::Word IdPORT_new_rwho = System::Word(0x226);
static constexpr System::Word IdPORT_cybercash = System::Word(0x227);
static constexpr System::Word IdPORT_deviceshare = System::Word(0x228);
static constexpr System::Word IdPORT_pirp = System::Word(0x229);
static constexpr System::Word IdPORT_rtsp = System::Word(0x22a);
static constexpr System::Word IdPORT_dsf = System::Word(0x22b);
static constexpr System::Word IdPORT_remotefs = System::Word(0x22c);
static constexpr System::Word IdPORT_openvms_sysipc = System::Word(0x22d);
static constexpr System::Word IdPORT_sdnskmp = System::Word(0x22e);
static constexpr System::Word IdPORT_teedtap = System::Word(0x22f);
static constexpr System::Word IdPORT_rmonitor = System::Word(0x230);
static constexpr System::Word IdPORT_monitor = System::Word(0x231);
static constexpr System::Word IdPORT_chshell = System::Word(0x232);
static constexpr System::Word IdPORT_SNEWS = System::Word(0x233);
static constexpr System::Word IdPORT_9pfs = System::Word(0x234);
static constexpr System::Word IdPORT_whoami = System::Word(0x235);
static constexpr System::Word IdPORT_streettalk = System::Word(0x236);
static constexpr System::Word IdPORT_banyan_rpc = System::Word(0x237);
static constexpr System::Word IdPORT_ms_shuttle = System::Word(0x238);
static constexpr System::Word IdPORT_ms_rome = System::Word(0x239);
static constexpr System::Word IdPORT_meter = System::Word(0x23a);
static constexpr System::Word IdPORT_meter_udemon = System::Word(0x23b);
static constexpr System::Word IdPORT_sonar = System::Word(0x23c);
static constexpr System::Word IdPORT_banyan_vip = System::Word(0x23d);
static constexpr System::Word IdPORT_ftp_agent = System::Word(0x23e);
static constexpr System::Word IdPORT_vemmi = System::Word(0x23f);
static constexpr System::Word Id_PORT_ipcd = System::Word(0x240);
static constexpr System::Word Id_PORT_vnas = System::Word(0x241);
static constexpr System::Word Id_PORT_ipdd = System::Word(0x242);
static constexpr System::Word Id_PORT_decbsrv = System::Word(0x243);
static constexpr System::Word Id_PORT_sntp_heartbeat = System::Word(0x244);
static constexpr System::Word Id_PORT_bdp = System::Word(0x245);
static constexpr System::Word Id_PORT_scc_security = System::Word(0x246);
static constexpr System::Word Id_PORT_philips_vc = System::Word(0x247);
static constexpr System::Word Id_PORT_keyserver = System::Word(0x248);
static constexpr System::Word Id_PORT_imap4_ssl_dp = System::Word(0x249);
static constexpr System::Word Id_PORT_password_chg = System::Word(0x24a);
static constexpr System::Word Id_PORT_submission = System::Word(0x24b);
static constexpr System::Word Id_PORT_cal = System::Word(0x24c);
static constexpr System::Word Id_PORT_eyelink = System::Word(0x24d);
static constexpr System::Word Id_PORT_tns_cml = System::Word(0x24e);
static constexpr System::Word Id_PORT_http_alt = System::Word(0x24f);
static constexpr System::Word Id_PORT_eudora_set = System::Word(0x250);
static constexpr System::Word Id_PORT_http_rpc_epmap = System::Word(0x251);
static constexpr System::Word Id_PORT_tpip = System::Word(0x252);
static constexpr System::Word Id_PORT_cab_protocol = System::Word(0x253);
static constexpr System::Word Id_PORT_smsd = System::Word(0x254);
static constexpr System::Word Id_PORT_ptcnameservice = System::Word(0x255);
static constexpr System::Word Id_PORT_sco_websrvrmg3 = System::Word(0x256);
static constexpr System::Word Id_PORT_acp = System::Word(0x257);
static constexpr System::Word IdPORT_ipcserver = System::Word(0x258);
static constexpr System::Word Id_PORT_syslog_conn = System::Word(0x259);
static constexpr System::Word IdPORT_urm = System::Word(0x25e);
static constexpr System::Word IdPORT_nqs = System::Word(0x25f);
static constexpr System::Word IdPORT_sift_uft = System::Word(0x260);
static constexpr System::Word IdPORT_npmp_trap = System::Word(0x261);
static constexpr System::Word IdPORT_npmp_local = System::Word(0x262);
static constexpr System::Word IdPORT_npmp_gui = System::Word(0x263);
static constexpr System::Word Id_PORT_hmmp_ind = System::Word(0x264);
static constexpr System::Word Id_PORT_hmmp_op = System::Word(0x265);
static constexpr System::Word Id_PORT_sshell = System::Word(0x266);
static constexpr System::Word Id_PORT_sco_inetmgr = System::Word(0x267);
static constexpr System::Word Id_PORT_sco_sysmgr = System::Word(0x268);
static constexpr System::Word Id_PORT_sco_dtmgr = System::Word(0x269);
static constexpr System::Word Id_PORT_dei_icda = System::Word(0x26a);
static constexpr System::Word Id_PORT_compaq_evm = System::Word(0x26b);
static constexpr System::Word Id_PORT_sco_websrvrmgr = System::Word(0x26c);
static constexpr System::Word Id_PORT_escp_ip = System::Word(0x26d);
static constexpr System::Word Id_PORT_collaborator = System::Word(0x26e);
static constexpr System::Word Id_PORT_aux_bus_shunt = System::Word(0x26f);
static constexpr System::Word Id_PORT_cryptoadmin = System::Word(0x270);
static constexpr System::Word Id_PORT_dec_dlm = System::Word(0x271);
static constexpr System::Word Id_PORT_asia = System::Word(0x272);
static constexpr System::Word Id_PORT_passgo_tivoli = System::Word(0x273);
static constexpr System::Word Id_PORT_qmqp = System::Word(0x274);
static constexpr System::Word Id_PORT_3com_amp3 = System::Word(0x275);
static constexpr System::Word Id_PORT_rda = System::Word(0x276);
static constexpr System::Word Id_PORT_ipp = System::Word(0x277);
static constexpr System::Word Id_PORT_bmpp = System::Word(0x278);
static constexpr System::Word IdPORT_servstat = System::Word(0x279);
static constexpr System::Word IdPORT_ginad = System::Word(0x27a);
static constexpr System::Word Id_PORT_rlzdbase = System::Word(0x27b);
static constexpr System::Word Id_PORT_ldaps = System::Word(0x27c);
static constexpr System::Word Id_PORT_lanserver = System::Word(0x27d);
static constexpr System::Word Id_PORT_mcns_sec = System::Word(0x27e);
static constexpr System::Word Id_PORT_msdp = System::Word(0x27f);
static constexpr System::Word Id_PORT_entrust_sps = System::Word(0x280);
static constexpr System::Word Id_PORT_repcmd = System::Word(0x281);
static constexpr System::Word Id_PORT_esro_emsdp = System::Word(0x282);
static constexpr System::Word Id_PORT_sanity = System::Word(0x283);
static constexpr System::Word Id_PORT_dwr = System::Word(0x284);
static constexpr System::Word Id_PORT_pssc = System::Word(0x285);
static constexpr System::Word Id_PORT_ldp = System::Word(0x286);
static constexpr System::Word Id_PORT_dhcp_failover = System::Word(0x287);
static constexpr System::Word Id_PORT_rrp = System::Word(0x288);
static constexpr System::Word Id_PORT_aminet = System::Word(0x289);
static constexpr System::Word Id_PORT_obex = System::Word(0x28a);
static constexpr System::Word Id_PORT_ieee_mms = System::Word(0x28b);
static constexpr System::Word Id_PORT_hello_port = System::Word(0x28c);
static constexpr System::Word Id_PORT_repscmd = System::Word(0x28d);
static constexpr System::Word Id_PORT_aodv = System::Word(0x28e);
static constexpr System::Word Id_PORT_tinc = System::Word(0x28f);
static constexpr System::Word Id_PORT_spmp = System::Word(0x290);
static constexpr System::Word Id_PORT_rmc = System::Word(0x291);
static constexpr System::Word Id_PORT_tenfold = System::Word(0x292);
static constexpr System::Word Id_PORT_mac_srvr_admin = System::Word(0x294);
static constexpr System::Word Id_PORT_hap = System::Word(0x295);
static constexpr System::Word Id_PORT_pftp = System::Word(0x296);
static constexpr System::Word Id_PORT_purenoise = System::Word(0x297);
static constexpr System::Word Id_PORT_secure_aux_bus = System::Word(0x298);
static constexpr System::Word Id_PORT_sun_dr = System::Word(0x299);
static constexpr System::Word IdPORT_mdqs = System::Word(0x29a);
static constexpr System::Word IdPORT_doom = System::Word(0x29a);
static constexpr System::Word Id_PORT_disclose = System::Word(0x29b);
static constexpr System::Word Id_PORT_mecomm = System::Word(0x29c);
static constexpr System::Word Id_PORT_meregister = System::Word(0x29d);
static constexpr System::Word Id_PORT_vacdsm_sws = System::Word(0x29e);
static constexpr System::Word Id_PORT_vacdsm_app = System::Word(0x29f);
static constexpr System::Word Id_PORT_vpps_qua = System::Word(0x2a0);
static constexpr System::Word Id_PORT_cimplex = System::Word(0x2a1);
static constexpr System::Word Id_PORT_acap = System::Word(0x2a2);
static constexpr System::Word Id_PORT_dctp = System::Word(0x2a3);
static constexpr System::Word Id_PORT_vpps_via = System::Word(0x2a4);
static constexpr System::Word Id_PORT_vpp = System::Word(0x2a5);
static constexpr System::Word Id_PORT_gnf_ncp = System::Word(0x2a6);
static constexpr System::Word Id_PORT_mrm = System::Word(0x2a7);
static constexpr System::Word Id_PORT_entrust_aaas = System::Word(0x2a8);
static constexpr System::Word Id_PORT_entrust_aams = System::Word(0x2a9);
static constexpr System::Word Id_PORT_xfr = System::Word(0x2aa);
static constexpr System::Word Id_PORT_corba_iiop = System::Word(0x2ab);
static constexpr System::Word Id_PORT_corba_iiop_ssl = System::Word(0x2ac);
static constexpr System::Word Id_PORT_mdc_portmapper = System::Word(0x2ad);
static constexpr System::Word Id_PORT_hcp_wismar = System::Word(0x2ae);
static constexpr System::Word Id_PORT_asipregistry = System::Word(0x2af);
static constexpr System::Word Id_PORT_realm_rusd = System::Word(0x2b0);
static constexpr System::Word Id_PORT_nmap = System::Word(0x2b1);
static constexpr System::Word Id_PORT_vatp = System::Word(0x2b2);
static constexpr System::Word Id_PORT_msexch_routing = System::Word(0x2b3);
static constexpr System::Word Id_PORT_hyperwave_isp = System::Word(0x2b4);
static constexpr System::Word Id_PORT_connendp = System::Word(0x2b5);
static constexpr System::Word Id_PORT_ha_cluster = System::Word(0x2b6);
static constexpr System::Word Id_PORT_ieee_mms_ssl = System::Word(0x2b7);
static constexpr System::Word Id_PORT_rushd = System::Word(0x2b8);
static constexpr System::Word Id_PORT_uuidgen = System::Word(0x2b9);
static constexpr System::Word Id_PORT_olsr = System::Word(0x2ba);
static constexpr System::Word Id_PORT_accessnetwork = System::Word(0x2bb);
static constexpr System::Word IdPORT_elcsd = System::Word(0x2c0);
static constexpr System::Word Id_PORT_agentx = System::Word(0x2c1);
static constexpr System::Word Id_PORT_silc = System::Word(0x2c2);
static constexpr System::Word Id_PORT_borland_dsj = System::Word(0x2c3);
static constexpr System::Word IdPORT_entrustmanager = System::Word(0x2c5);
static constexpr System::Word Id_PORT_entrust_ash = System::Word(0x2c6);
static constexpr System::Word Id_PORT_cisco_tdp = System::Word(0x2c7);
static constexpr System::Word IdPORT_netviewdm1 = System::Word(0x2d9);
static constexpr System::Word IdPORT_netviewdm2 = System::Word(0x2da);
static constexpr System::Word IdPORT_netviewdm3 = System::Word(0x2db);
static constexpr System::Word IdPORT_netgw = System::Word(0x2e5);
static constexpr System::Word IdPORT_netrcs = System::Word(0x2e6);
static constexpr System::Word IdPORT_flexlm = System::Word(0x2e8);
static constexpr System::Word IdPORT_fujitsu_dev = System::Word(0x2eb);
static constexpr System::Word IdPORT_ris_cm = System::Word(0x2ec);
static constexpr System::Word IdPORT_kerberos_adm = System::Word(0x2ed);
static constexpr System::Word IdPORT_rfile = System::Word(0x2ee);
static constexpr System::Word IdPORT_loadav = System::Word(0x2ee);
static constexpr System::Word IdPORT_pump = System::Word(0x2ef);
static constexpr System::Word IdPORT_qrh = System::Word(0x2f0);
static constexpr System::Word IdPORT_rrh = System::Word(0x2f1);
static constexpr System::Word IdPORT_tell = System::Word(0x2f2);
static constexpr System::Word IdPORT_nlogin = System::Word(0x2f6);
static constexpr System::Word IdPORT_con = System::Word(0x2f7);
static constexpr System::Word IdPORT_ns = System::Word(0x2f8);
static constexpr System::Word IdPORT_rxe = System::Word(0x2f9);
static constexpr System::Word IdPORT_quotad = System::Word(0x2fa);
static constexpr System::Word IdPORT_cycleserv = System::Word(0x2fb);
static constexpr System::Word IdPORT_omserv = System::Word(0x2fc);
static constexpr System::Word IdPORT_webster = System::Word(0x2fd);
static constexpr System::Word IdPORT_phonebook = System::Word(0x2ff);
static constexpr System::Word IdPORT_vid = System::Word(0x301);
static constexpr System::Word IdPORT_cadlock = System::Word(0x302);
static constexpr System::Word IdPORT_rtip = System::Word(0x303);
static constexpr System::Word IdPORT_cycleserv2 = System::Word(0x304);
static constexpr System::Word IdPORT_submit = System::Word(0x305);
static constexpr System::Word IdPORT_notify = System::Word(0x305);
static constexpr System::Word IdPORT_rpasswd = System::Word(0x306);
static constexpr System::Word IdPORT_acmaint_dbd = System::Word(0x306);
static constexpr System::Word IdPORT_entomb = System::Word(0x307);
static constexpr System::Word IdPORT_acmaint_transd = System::Word(0x307);
static constexpr System::Word IdPORT_wpages = System::Word(0x308);
static constexpr System::Word IdPORT_wpgs = System::Word(0x30c);
static constexpr System::Word IdPORT_concert = System::Word(0x312);
static constexpr System::Word IdPORT_qsc = System::Word(0x313);
static constexpr System::Word IdPORT_mdbs_daemon = System::Word(0x320);
static constexpr System::Word IdPORT_device = System::Word(0x321);
static constexpr System::Word Id_PORT_fcp = System::Word(0x32a);
static constexpr System::Word Id_PORT_itm_mcell_s = System::Word(0x33c);
static constexpr System::Word Id_PORT_pkix_3_ca_ra = System::Word(0x33d);
static constexpr System::Word Id_PORT_dhcp_failover2 = System::Word(0x34f);
static constexpr System::Word Id_PORT_rsync = System::Word(0x369);
static constexpr System::Word Id_PORT_iclcnet_locate = System::Word(0x376);
static constexpr System::Word Id_PORT_iclcnet_svinfo = System::Word(0x377);
static constexpr System::Word IdPORT_accessbuilder = System::Word(0x378);
static constexpr System::Word Id_PORT_omginitialrefs = System::Word(0x384);
static constexpr System::Word Id_PORT_smpnameres = System::Word(0x385);
static constexpr System::Word Id_PORT_ideafarm_chat = System::Word(0x386);
static constexpr System::Word Id_PORT_ideafarm_catch = System::Word(0x387);
static constexpr System::Word IdPOPRT_xact_backup = System::Word(0x38f);
static constexpr System::Word IdPORT_ftps_data = System::Word(0x3dd);
static constexpr System::Word IdPORT_ftps = System::Word(0x3de);
static constexpr System::Word IdPORT_nas = System::Word(0x3df);
static constexpr System::Word IdPORT_TelnetS = System::Word(0x3e0);
static constexpr System::Word IdPORT_IMAP4S = System::Word(0x3e1);
static constexpr System::Word IdPORT_IRCS = System::Word(0x3e2);
static constexpr System::Word IdPORT_POP3S = System::Word(0x3e3);
static constexpr System::Word IdPORT_vsinet = System::Word(0x3e4);
static constexpr System::Word IdPORT_maitrd = System::Word(0x3e5);
static constexpr System::Word IdPORT_busboy = System::Word(0x3e6);
static constexpr System::Word IdPORT_puparp = System::Word(0x3e6);
static constexpr System::Word IdPORT_garcon = System::Word(0x3e7);
static constexpr System::Word IdPORT_applix = System::Word(0x3e7);
static constexpr System::Word IdPORT_puprouter = System::Word(0x3e7);
static constexpr System::Word IdPORT_cadlock2 = System::Word(0x3e8);
static constexpr System::Word IdPORT_ock = System::Word(0x3e8);
static constexpr System::Word ID_PORT_surf = System::Word(0x3f2);
static constexpr System::Word IdPORT_SOCKS = System::Word(0x438);
static constexpr System::Word IdPORT_DICT = System::Word(0xa44);
static constexpr System::Word IdPORT_IRC = System::Word(0x1a0b);
#define IdGSKSSN_rcmd u"rcmd"
#define IdGSKSSN_imap u"imap"
#define IdGSKSSN_pop u"pop"
#define IdGSKSSN_acap u"acap"
#define IdGSKSSN_nfs u"nfs"
#define IdGSKSSN_ftp u"ftp"
#define IdGSKSSN_ldap u"ldap"
#define IdGSKSSN_smtp u"smtp"
#define IdGSKSSN_beep u"beep"
#define IdGSKSSN_mupdate u"mupdate"
#define IdGSKSSN_sacred u"sacred"
#define IdGSKSSN_xmpp u"xmpp"
#define IdGSKSSN_nntp u"nntp"
static constexpr System::Int8 Id_AIVN_Rserved = System::Int8(0x0);
static constexpr System::Int8 Id_AIVN_IP = System::Int8(0x4);
static constexpr System::Int8 Id_AIVN_ST = System::Int8(0x5);
static constexpr System::Int8 Id_AIVN_SIP = System::Int8(0x6);
static constexpr System::Int8 Id_AIVN_TP_IX = System::Int8(0x7);
static constexpr System::Int8 Id_AIVN_PIP = System::Int8(0x8);
static constexpr System::Int8 Id_AIVN_Tuba = System::Int8(0x9);
static constexpr System::Int8 Id_AIVN_Reserved2 = System::Int8(0xf);
static constexpr System::Int8 Id_AIPN_Reserved = System::Int8(0x0);
static constexpr System::Int8 Id_AIPN_ICMP = System::Int8(0x1);
static constexpr System::Int8 Id_AIPN_IGMP = System::Int8(0x2);
static constexpr System::Int8 Id_AIPN_GGP = System::Int8(0x3);
static constexpr System::Int8 Id_AIPN_IP = System::Int8(0x4);
static constexpr System::Int8 Id_AIPN_ST = System::Int8(0x5);
static constexpr System::Int8 Id_AIPN_TCP = System::Int8(0x6);
static constexpr System::Int8 Id_AIPN_UCL = System::Int8(0x7);
static constexpr System::Int8 Id_AIPN_EGP = System::Int8(0x8);
static constexpr System::Int8 Id_AIPN_IGP = System::Int8(0x9);
static constexpr System::Int8 Id_AIPN_BBN_RCC_MON = System::Int8(0xa);
static constexpr System::Int8 Id_AIPN_NVP_II = System::Int8(0xb);
static constexpr System::Int8 Id_AIPN_PUP = System::Int8(0xc);
static constexpr System::Int8 Id_AIPN_ARGUS = System::Int8(0xd);
static constexpr System::Int8 Id_AIPN_EMCON = System::Int8(0xe);
static constexpr System::Int8 Id_AIPN_XNET = System::Int8(0xf);
static constexpr System::Int8 Id_AIPN_CHAOS = System::Int8(0x10);
static constexpr System::Int8 Id_AIPN_UDP = System::Int8(0x11);
static constexpr System::Int8 Id_AIPN_MUX = System::Int8(0x12);
static constexpr System::Int8 Id_AIPN_DCN_MEAS = System::Int8(0x13);
static constexpr System::Int8 Id_AIPN_HMP = System::Int8(0x14);
static constexpr System::Int8 Id_AIPN_PRM = System::Int8(0x15);
static constexpr System::Int8 Id_AIPN_XNS_IDP = System::Int8(0x16);
static constexpr System::Int8 Id_AIPN_TRUNK_1 = System::Int8(0x17);
static constexpr System::Int8 Id_AIPN_TRUNK_2 = System::Int8(0x18);
static constexpr System::Int8 Id_AIPN_LEAF_1 = System::Int8(0x19);
static constexpr System::Int8 Id_AIPN_LEAF_2 = System::Int8(0x1a);
static constexpr System::Int8 Id_AIPN_RDP = System::Int8(0x1b);
static constexpr System::Int8 Id_AIPN_IRTP = System::Int8(0x1c);
static constexpr System::Int8 Id_AIPN_ISO_TP4 = System::Int8(0x1d);
static constexpr System::Int8 Id_AIPN_NETBLT = System::Int8(0x1e);
static constexpr System::Int8 Id_AIPN_NFE_NSP = System::Int8(0x1f);
static constexpr System::Int8 Id_AIPN_MERIT_IMP = System::Int8(0x20);
static constexpr System::Int8 Id_AIPN_SEP = System::Int8(0x21);
static constexpr System::Int8 Id_AIPN_3PC = System::Int8(0x22);
static constexpr System::Int8 Id_AIPN_IDPR = System::Int8(0x23);
static constexpr System::Int8 Id_AIPN_XTP = System::Int8(0x24);
static constexpr System::Int8 Id_AIPN_DDP = System::Int8(0x25);
static constexpr System::Int8 Id_AIPN_IDPR_CMTP = System::Int8(0x26);
static constexpr System::Int8 Id_AIPN_TP_PLUS_PLUS = System::Int8(0x27);
static constexpr System::Int8 Id_AIPN_IL = System::Int8(0x28);
static constexpr System::Int8 Id_AIPN_SIP = System::Int8(0x29);
static constexpr System::Int8 Id_AIPN_SDRP = System::Int8(0x2a);
static constexpr System::Int8 Id_AIPN_SIP_SR = System::Int8(0x2b);
static constexpr System::Int8 Id_AIPN_SIP_FRAG = System::Int8(0x2c);
static constexpr System::Int8 Id_AIPN_IDRP = System::Int8(0x2d);
static constexpr System::Int8 Id_AIPN_RSVP = System::Int8(0x2e);
static constexpr System::Int8 Id_AIPN_GRE = System::Int8(0x2f);
static constexpr System::Int8 Id_AIPN_MHRP = System::Int8(0x30);
static constexpr System::Int8 Id_AIPN_BNA = System::Int8(0x31);
static constexpr System::Int8 Id_AIPN_SIPP_ESB = System::Int8(0x32);
static constexpr System::Int8 Id_AIPN_SIPP_AH = System::Int8(0x33);
static constexpr System::Int8 Id_AIPN_I_NLSP = System::Int8(0x34);
static constexpr System::Int8 Id_AIPN_SWIPE = System::Int8(0x35);
static constexpr System::Int8 Id_AIPN_NHRP = System::Int8(0x36);
static constexpr System::Int8 Id_AIPN_MOBILE = System::Int8(0x37);
static constexpr System::Int8 Id_AIPN_TLSP = System::Int8(0x38);
static constexpr System::Int8 Id_AIPN_Kryptonet = System::Int8(0x3a);
static constexpr System::Int8 Id_AIPN_SKIP = System::Int8(0x39);
static constexpr System::Int8 Id_AIPN_IPV6_ICMP = System::Int8(0x3a);
static constexpr System::Int8 Id_AIPN_IPV6_NO_NEXT = System::Int8(0x3b);
static constexpr System::Int8 Id_AIPN_IPV6_OPTS = System::Int8(0x3c);
static constexpr System::Int8 Id_AIPN_Any_Host_Internal = System::Int8(0x3d);
static constexpr System::Int8 Id_AIPN_CFTP = System::Int8(0x3e);
static constexpr System::Int8 Id_AIPN_Any_LAN = System::Int8(0x3f);
static constexpr System::Int8 Id_AIPN_SAT_EXPACK = System::Int8(0x40);
static constexpr System::Int8 Id_AIPN_KRYPTOLAN = System::Int8(0x41);
static constexpr System::Int8 Id_AIPN_RVD = System::Int8(0x42);
static constexpr System::Int8 Id_AIPN_IPPC = System::Int8(0x43);
static constexpr System::Int8 Id_AIPN_Any_Distributed_File_System = System::Int8(0x44);
static constexpr System::Int8 Id_AIPN_SAT_MON = System::Int8(0x45);
static constexpr System::Int8 Id_AIPN_VISA = System::Int8(0x46);
static constexpr System::Int8 Id_AIPN_IPCV = System::Int8(0x47);
static constexpr System::Int8 Id_AIPN_CPNX = System::Int8(0x48);
static constexpr System::Int8 Id_AIPN_CPHB = System::Int8(0x49);
static constexpr System::Int8 Id_AIPN_WSM = System::Int8(0x4a);
static constexpr System::Int8 Id_AIPN_PVP = System::Int8(0x4b);
static constexpr System::Int8 Id_AIPN_BR_SAT_MON = System::Int8(0x4c);
static constexpr System::Int8 Id_AIPN_SUN_ND = System::Int8(0x4d);
static constexpr System::Int8 Id_AIPN_WB_MON = System::Int8(0x4e);
static constexpr System::Int8 Id_AIPN_EXPAK = System::Int8(0x4f);
static constexpr System::Int8 Id_AIPN_ISO_IP = System::Int8(0x50);
static constexpr System::Int8 Id_AIPN_VMTP = System::Int8(0x51);
static constexpr System::Int8 Id_AIPN_SECURE_VMTP = System::Int8(0x52);
static constexpr System::Int8 Id_AIPN_VINES = System::Int8(0x53);
static constexpr System::Int8 Id_AIPN_TTP = System::Int8(0x54);
static constexpr System::Int8 Id_AIPN_NSFNET_IGP = System::Int8(0x55);
static constexpr System::Int8 Id_AIPN_DGP = System::Int8(0x56);
static constexpr System::Int8 Id_AIPN_TCF = System::Int8(0x57);
static constexpr System::Int8 Id_AIPN_IGRP = System::Int8(0x58);
static constexpr System::Int8 Id_AIPN_OSPFIGP = System::Int8(0x59);
static constexpr System::Int8 Id_AIPN_Sprite_RPC = System::Int8(0x5a);
static constexpr System::Int8 Id_AIPN_LARP = System::Int8(0x5b);
static constexpr System::Int8 Id_AIPN_MTP = System::Int8(0x5c);
static constexpr System::Int8 Id_AIPN_AX_25 = System::Int8(0x5d);
static constexpr System::Int8 Id_AIPN_IPIP = System::Int8(0x5e);
static constexpr System::Int8 Id_AIPN_MICP = System::Int8(0x5f);
static constexpr System::Int8 Id_AIPN_SCC_SP = System::Int8(0x60);
static constexpr System::Int8 Id_AIPN_ETHERIP = System::Int8(0x61);
static constexpr System::Int8 Id_AIPN_ENCAP = System::Int8(0x62);
static constexpr System::Int8 Id_AIPN_Any_Private_Encryption = System::Int8(0x63);
static constexpr System::Int8 Id_AIPN_GMTP = System::Int8(0x64);
static constexpr System::Int8 Id_AIPN_IFMP = System::Int8(0x65);
static constexpr System::Int8 Id_AIPN_PNNI = System::Int8(0x66);
static constexpr System::Int8 Id_AIPN_PIM = System::Int8(0x67);
static constexpr System::Int8 Id_AIPN_ARIS = System::Int8(0x68);
static constexpr System::Int8 Id_AIPN_SCPS = System::Int8(0x69);
static constexpr System::Int8 Id_AIPN_QNX = System::Int8(0x6a);
static constexpr System::Int8 Id_AIPN_A_N = System::Int8(0x6b);
static constexpr System::Int8 Id_AIPN_IPComp = System::Int8(0x6c);
static constexpr System::Int8 Id_AIPN_SNP = System::Int8(0x6d);
static constexpr System::Int8 Id_AIPN_Compaq_Peer = System::Int8(0x6e);
static constexpr System::Int8 Id_AIPN_IPX_In_IP = System::Int8(0x6f);
static constexpr System::Int8 Id_AIPN_VRRP = System::Int8(0x70);
static constexpr System::Int8 Id_AIPN_PGM = System::Int8(0x71);
static constexpr System::Int8 Id_AIPN_0_HOP = System::Int8(0x72);
static constexpr System::Int8 Id_AIPN_L2TP = System::Int8(0x73);
static constexpr System::Int8 Id_AIPN_DDX = System::Int8(0x74);
static constexpr System::Int8 Id_AIPN_IATP = System::Int8(0x75);
static constexpr System::Int8 Id_AIPN_STP = System::Int8(0x76);
static constexpr System::Int8 Id_AIPN_SRP = System::Int8(0x77);
static constexpr System::Int8 Id_AIPN_UTI = System::Int8(0x78);
static constexpr System::Int8 Id_AIPN_SMP = System::Int8(0x79);
static constexpr System::Int8 Id_AIPN_SM = System::Int8(0x7a);
static constexpr System::Int8 Id_AIPN_PTP = System::Int8(0x7b);
static constexpr System::Int8 Id_AIPN_ISIS = System::Int8(0x7c);
static constexpr System::Int8 Id_AIPN_FIRE = System::Int8(0x7d);
static constexpr System::Int8 Id_AIPN_CRTP = System::Int8(0x7e);
static constexpr System::Int8 Id_AIPN_CRUDP = System::Int8(0x7f);
static constexpr System::Byte Id_AIPN_SSCOPMCE = System::Byte(0x80);
static constexpr System::Byte Id_AIPN_IPLT = System::Byte(0x81);
static constexpr System::Byte Id_AIPN_SPS = System::Byte(0x82);
static constexpr System::Byte Id_AIPN_PIPE = System::Byte(0x83);
static constexpr System::Byte Id_AIPN_SCTP = System::Byte(0x84);
static constexpr System::Byte Id_AIPN_FC = System::Byte(0x85);
static constexpr System::Byte Id_AIPN_RSVP_E2E_IGNORE = System::Byte(0x86);
static constexpr System::Byte Id_AIPN_Reserved2 = System::Byte(0xff);
#define Id_OS_Aegis u"AEGIS"
#define Id_OS_Amiga_1_2 u"AMIGA-OS-1.2"
#define Id_OS_Amiga_1_3 u"AMIGA-OS-1.3"
#define Id_OS_Amiga_2_0 u"AMIGA-OS-2.0"
#define Id_OS_Amiga_2_1 u"AMIGA-OS-2.1"
#define Id_OS_Amiga_3_0 u"AMIGA-OS-3.0"
#define Id_OS_Amiga_3_1 u"AMIGA-OS-3.1"
#define Id_OS_Amiga_3_5 u"AMIGA-OS-3.5"
#define Id_OS_Amiga_3_9 u"AMIGA-OS-3.9"
#define Id_OS_Apollo u"APOLLO"
#define Id_OS_AIX_370 u"AIX/370"
#define Id_OS_AIX_PS2 u"AIX-PS/2"
#define Id_OS_BEOS_4_5_2 u"BEOS-4.5.2"
#define Id_OS_BEOS_5_0 u"BEOS-5.0"
#define Id_OS_BS_2000 u"BS-2000"
#define Id_OS_Cedar u"CEDAR"
#define Id_OS_CGW u"CGW"
#define Id_OS_CHORUS u"CHORUS"
#define Id_OS_Chrysalis u"CHRYSALIS"
#define Id_OS_CMOS u"CMOS"
#define Id_OS_CMS u"CMS"
#define Id_OS_COS u"COS"
#define Id_OS_CPIX u"CPIX"
#define Id_OS_CTOS u"CTOS"
#define Id_OS_CTSS u"CTSS"
#define Id_OS_DCN u"DCN"
#define Id_OS_DDNOS u"DDNOS"
#define Id_OS_DOMAIN u"DOMAIN"
#define Id_OS_DOS u"DOS"
#define Id_OS_EDX u"EDX"
#define Id_OS_ELF u"ELF"
#define Id_OS_EMBOS u"EMBOS"
#define Id_OS_EMMOS u"EMMOS"
#define Id_OS_EPOS u"EPOS"
#define Id_OS_FOONEX u"FOONEX"
#define Id_OS_FORTH u"FORTH"
#define Id_OS_FUZZ u"FUZZ"
#define Id_OS_GCOS u"GCOS"
#define Id_OS_GPOS u"GPOS"
#define Id_OS_HDOS u"HDOS"
#define Id_OS_Imagen u"IMAGEN"
#define Id_OS_Instant_Internet u"INSTANT-INTERNET"
#define Id_OS_Intercom u"INTERCOM"
#define Id_OS_Impress u"IMPRESS"
#define Id_OS_Interlisp u"INTERLISP"
#define Id_OS_IOS u"IOS"
#define Id_OS_IRIX u"IRIX"
#define Id_OS_ISI u"ISI-68020"
#define Id_OS_ITS u"ITS"
#define Id_OS_KOSOS u"KOSOS"
#define Id_OS_Linux u"LINUX"
#define Id_OS_Linux_1_0 u"LINUX-1.0"
#define Id_OS_Linux_1_2 u"LINUX-1.2"
#define Id_OS_Linux_2_0 u"LINUX-2.0"
#define Id_OS_Linux_2_2 u"LINUX-2.2"
#define Id_OS_LISP u"LISP"
#define Id_OS_LISPM u"LISPM"
#define Id_OS_LOCUS u"LOCUS"
#define Id_OS_MACOS u"MACOS"
#define Id_OS_MINOS u"MINOS"
#define Id_OS_MOS u"MOS"
#define Id_OS_MPE5 u"MPE5"
#define Id_OS_MPEV u"MPE/V"
#define Id_OS_MPEIX u"MPE/IX"
#define Id_OS_MSDOS u"MSDOS"
#define Id_OS_MULTICS u"MULTICS"
#define Id_OS_MUSIC u"MUSIC"
#define Id_OS_MUSICSP u"MUSIC/SP"
#define Id_OS_MVS u"MVS"
#define Id_OS_MVSSP u"MVS/SP"
#define Id_NET_BSD_1_0 u"NETBSD-1.0"
#define Id_NET_BSD_1_1 u"NETBSD-1.1"
#define Id_NET_BSD_1_2 u"NETBSD-1.2"
#define Id_NET_BSD_1_3 u"NETBSD-1.3"
#define Id_NET_BSD_3_0 u"NETWARE-3"
#define Id_NET_BSD_3_11 u"NETWARE-3.11"
#define Id_NET_BSD_4_0 u"NETWARE-4.0"
#define Id_NET_BSD_4_1 u"NETWARE-4.1"
#define Id_NET_BSD_5_0 u"NETWARE-5.0"
#define Id_OS_NEXUS u"NEXUS"
#define Id_OS_NMS u"NMS"
#define Id_OS_NONSTOP u"NONSTOP"
#define Id_OS_NOS_2 u"NOS-2"
#define Id_OS_NTOS u"NTOS"
#define Id_OS_OpenBSD u"OPENBSD"
#define Id_OS_OpenVMS u"OPENVMS"
#define Id_OS_OSDDP u"OS/DDP"
#define Id_OS_OS_2 u"OS/2"
#define Id_OS_OS_4 u"OS4"
#define Id_OS_OS_6 u"OS86"
#define Id_OS_OSX u"OSX"
#define Id_OS_PCDOS u"PCDOS"
#define Id_OS_PERQOS u"PERQ/OS"
#define Id_OS_PLI u"PLI"
#define Id_OS_PSDDOSMIT u"PSDOS/MIT"
#define Id_OS_Primos u"PRIMOS"
#define Id_OS_RISC_OS u"RISC-OS"
#define Id_OS_RISC_OS_3_10 u"RISC-OS-3.10"
#define Id_OS_RISC_OS_3_50 u"RISC-OS-3.50"
#define Id_OS_RISC_OS_3_60 u"RISC-OS-3.60"
#define Id_OS_RISC_OS_3_70 u"RISC-OS-3.70"
#define Id_OS_RISC_OS_4_00 u"RISC-OS-4.00"
#define Id_OS_RMXRDOS u"RMX/RDOS"
#define Id_OS_ROS u"ROS"
#define Id_OS_RSX11M u"RSX11M"
#define Id_OS_RTE_A u"RTE-A"
#define Id_OS_Satops u"SATOPS"
#define Id_OS_Sinix u"SINIX"
#define Id_OS_SCO_Open_Desktop_1_0 u"SCO-OPEN-DESKTOP-1.0"
#define Id_OS_SCO_Open_Desktop_1_1 u"SCO-OPEN-DESKTOP-1.1"
#define Id_OS_SCO_Open_Desktop_2_0 u"SCO-OPEN-DESKTOP-2.0"
#define Id_OS_SCO_Open_Desktop_3_0 u"SCO-OPEN-DESKTOP-3.0"
#define Id_OS_SCO_Open_Desktop_Lite_3_0 u"SCO-OPEN-DESKTOP-LITE-3.0"
#define Id_OS_SCO_Open_Server_3_0 u"SCO-OPEN-SERVER-3.0"
#define Id_OS_SCO_Unix_3_2_0 u"SCO-UNIX-3.2.0"
#define Id_OS_SCO_Unix_3_2V2_0 u"SCO-UNIX-3.2V2.0"
#define Id_OS_SCO_Unix_3_2V1_0 u"SCO-UNIX-3.2V2.1"
#define Id_OS_SCO_Unix_S_2V4_0 u"SCO-UNIX-3.2V4.0"
#define Id_OS_SCO_Unix_3_2V4_1 u"SCO-UNIX-3.2V4.1"
#define Id_OS_SCO_Unix_3_2V4_2 u"SCO-UNIX-3.2V4.2"
#define Id_OS_SCO_Xenix_386_2_3_2 u"SCO-XENIX-386-2.3.2"
#define Id_OS_SCO_Xenix_386_2_3_3 u"SCO-XENIX-386-2.3.3"
#define Id_OS_SCO_Xenix_386_2_3_4 u"SCO-XENIX-386-2.3.4"
#define Id_OS_SCS u"SCS"
#define Id_OS_SIMP u"SIMP"
#define Id_OS_SUN u"SUN"
#define Id_OS_SUN_OS_3_5 u"SUN-OS-3.5"
#define Id_OS_SUN_OS_4_0 u"SUN-OS-4.0"
#define Id_OS_Swift u"SWIFT"
#define Id_OS_Tac u"TAC"
#define Id_OS_Tandem u"TANDEM"
#define Id_OS_Tenex u"TENEX"
#define Id_OS_The_Major_BBS u"THE-MAJOR-BBS"
#define Id_OS_Tops10 u"TOPS10"
#define Id_OS_Tops20 u"TOPS20"
#define Id_OS_TOS u"TOS"
#define Id_OS_TP3010 u"TP3010"
#define Id_OS_TRSDOS u"TRSDOS"
#define Id_OS_Ultrix u"ULTRIX"
#define Id_OS_Unix u"UNIX"
#define Id_OS_Unix_BSD u"UNIX-BSD"
#define Id_OS_Unix_V1AT u"UNIX-V1AT"
#define Id_OS_Unix_V u"UNIX-V"
#define Id_OS_Unix_V_1 u"UNIX-V.1"
#define Id_OS_Unix_V_2 u"UNIX-V.2"
#define Id_OS_Unix_V_3 u"UNIX-V.3"
#define Id_OS_Unix_PC u"UNIX-PC"
#define Id_OS_Unix_Unknown u"UNKNOWN"
#define Id_OS_UT2D u"UT2D"
static constexpr System::WideChar Id_OS_V = (System::WideChar)(0x56);
#define Id_OS_VM u"VM"
#define Id_OS_VM_370 u"VM/370"
#define Id_OS_VM_CMS u"VM/CMS"
#define Id_OS_VM_SP u"VM/SP"
#define Id_OS_VMS u"VMS"
#define Id_OS_VMS_Eunice u"VMS/EUNICE"
#define Id_OS_VRTX u"VRTX"
#define Id_OS_Waits u"WAITS"
#define Id_OS_Wang u"WANG"
#define Id_OS_Win32 u"WIN32"
#define Id_OS_Windows_95 u"WINDOWS-95"
#define Id_OS_Windows_95OSR1 u"WINDOWS-95-OSR1"
#define Id_OS_Windows_95OSR2 u"WINDOWS-95-OSR2"
#define Id_OS_Windows_98 u"WINDOWS-98"
#define Id_OS_Windows_CE u"WINDOWS-CE"
#define Id_OS_Windows_NT u"WINDOWS-NT"
#define Id_OS_Windows_NT_2 u"WINDOWS-NT-2"
#define Id_OS_Windows_NT_3 u"WINDOWS-NT-3"
#define Id_OS_Windows_NT_3_5 u"WINDOWS-NT-3.5"
#define Id_OS_Windows_NT_3_51 u"WINDOWS-NT-3.51"
#define Id_OS_Windows_NT_4 u"WINDOWS-NT-4"
#define Id_OS_Windows_NT_5 u"WINDOWS-NT-5"
#define Id_OS_WorldGroup u"WORLDGROUP"
#define Id_OS_Wyse_Wyxware u"WYSE-WYXWARE"
#define Id_OS_X11R3 u"X11R3"
#define Id_OS_XDE u"XDE"
#define Id_OS_Xenix u"XENIX"
#define Id_MN_Amiga_500 u"AMIGA-500"
#define Id_MN_Amiga_500_010 u"AMIGA-500/010"
#define Id_MN_Amiga_500_020 u"AMIGA-500/020"
#define Id_MN_Amiga_500_EC030 u"AMIGA-500/EC030"
#define Id_MN_Amiga_500_030 u"AMIGA-500/030"
#define Id_MN_Amiga_600 u"AMIGA-600"
#define Id_MN_Amiga_1000 u"AMIGA-1000"
#define Id_MN_Amiga_1000_010 u"AMIGA-1000/010"
#define Id_MN_Amiga_1000_020 u"AMIGA-1000/020"
#define Id_MN_Amiga_1000_EC030 u"AMIGA-1000/EC030"
#define Id_MN_Amiga_1000_030 u"AMIGA-1000/030"
#define Id_MN_Amiga_1200 u"AMIGA-1200"
#define Id_MN_Amiga_1200_EC030 u"AMIGA-1200/EC030"
#define Id_MN_Amiga_1200_030 u"AMIGA-1200/030"
#define Id_MN_Amiga_1200_EC040 u"AMIGA-1200/EC040"
#define Id_MN_Amiga_1200_LC040 u"AMIGA-1200/LC040"
#define Id_MN_Amiga_1200_040 u"AMIGA-1200/040"
#define Id_MN_Amiga_2000 u"AMIGA-2000"
#define Id_MN_Amiga_2000_010 u"AMIGA-2000/010"
#define Id_MN_Amiga_2000_020 u"AMIGA-2000/020"
#define Id_MN_Amiga_2000_EC030 u"AMIGA-2000/EC030"
#define Id_MN_Amiga_2000_030 u"AMIGA-2000/030"
#define Id_MN_Amiga_2000_LC040 u"AMIGA-2000/LC040"
#define Id_MN_Amiga_2000_EC040 u"AMIGA-2000/EC040"
#define Id_MN_Amiga_2000_040 u"AMIGA-2000/040"
#define Id_MN_Amiga_3000 u"AMIGA-3000"
#define Id_MN_Amiga_3000_EC040 u"AMIGA-3000/EC040"
#define Id_MN_Amiga_3000_LC040 u"AMIGA-3000/LC040"
#define Id_MN_Amiga_3000_040 u"AMIGA-3000/040"
#define Id_MN_Amiga_3000_060 u"AMIGA-3000/060"
#define Id_MN_Amiga_4000_EC030 u"AMIGA-4000/EC030"
#define Id_MN_Amiga_4000_030 u"AMIGA-4000/030"
#define Id_MN_Amiga_4000_LC040 u"AMIGA-4000/LC040"
#define Id_MN_Amiga_4000_040 u"AMIGA-4000/040"
#define Id_MN_Amiga_4000_060 u"AMIGA-4000/060"
#define Id_MN_Alto u"ALTO"
#define Id_MN_Altos_6800 u"ALTOS-6800"
#define Id_MN_Amdahl_V7 u"AMDAHL-V7"
#define Id_MN_Apollo u"APOLLO"
#define Id_MN_Apple_Macintosh u"APPLE-MACINTOSH"
#define Id_MN_Apple_Powerbook u"APPLE-POWERBOOK"
#define Id_MN_Atari_104ST u"ATARI-104ST"
#define Id_MN_ATT_3B1 u"ATT-3B1"
#define Id_MN_ATT_3B2 u"ATT-3B2"
#define Id_MN_ATT_3B20 u"ATT-3B20"
#define Id_MN_ATT_7300 u"ATT-7300"
#define Id_MN_AXP u"AXP"
#define Id_MN_BBN_C_60 u"BBN-C/60"
#define Id_MN_Burroughs_B_29 u"BURROUGHS-B/29"
#define Id_MN_Burroughs_B_4800 u"BURROUGHS-B/4800"
#define Id_MN_Butterfly u"BUTTERFLY"
#define Id_MN_C_30 u"C/30"
#define Id_MN_C_70 u"C/70"
#define Id_MN_Cadlinc u"CADLINC"
#define Id_MN_CadR u"CADR"
#define Id_MN_CDC_170 u"CDC-170"
#define Id_MN_CDC_170_750 u"CDC-170/750"
#define Id_MN_CDC_173 u"CDC-173"
#define Id_MN_CDTV u"CDTV"
#define Id_MN_CDTV_060 u"CDTV/060"
#define Id_MN_CD32 u"CD32"
#define Id_MN_Celerity_1200 u"CELERITY-1200"
#define Id_MN_Club_386 u"CLUB-386"
#define Id_MN_Compaq_386_20 u"COMPAQ-386/20"
#define Id_MN_Comten_3690 u"COMTEN-3690"
#define Id_MN_CP8040 u"CP8040"
#define Id_MN_Cray_1 u"CRAY-1"
#define Id_MN_Cray_X_MP u"CRAY-X/MP"
#define Id_MN_Cray_2 u"CRAY-2"
#define Id_MN_CTIWS_117 u"CTIWS-117"
#define Id_MN_Dandelion u"DANDELION"
#define Id_MN_DEC_10 u"DEC-10"
#define Id_MN_DEC_1050 u"DEC-1050"
#define Id_MN_DEC_1077 u"DEC-1077"
#define Id_MN_DEC_1080 u"DEC-1080"
#define Id_MN_DEC_1090 u"DEC-1090"
#define Id_MN_DEC_1090B u"DEC-1090B"
#define Id_MN_DEC_1090T u"DEC-1090T"
#define Id_MN_DEC_2020T u"DEC-2020T"
#define Id_MN_DEC_2040 u"DEC-2040"
#define Id_MN_DEC_2040T u"DEC-2040T"
#define Id_MN_DEC_2050T u"DEC-2050T"
#define Id_MN_DEC_2060 u"DEC-2060"
#define Id_MN_DEC_2060T u"DEC-2060T"
#define Id_MN_DEC_2065 u"DEC-2065"
#define Id_MN_DEC_AXP u"DEC-AXP"
#define Id_MN_DEC_Falcon u"DEC-FALCON"
#define Id_MN_DEC_KS10 u"DEC-KS10"
#define Id_MN_DECStation u"DECSTATION"
#define Id_MN_DEC_VAX u"DEC-VAX"
#define Id_MN_DEC_VAXCluster u"DEC-VAXCLUSTER"
#define Id_MN_DEC_VAXStation u"DEC-VAXSTATION"
#define Id_MN_DEC_VAX_11730 u"DEC-VAX-11730"
#define Id_MN_Dorado u"DORADO"
#define Id_MN_DPS8_70M u"DPS8/70M"
#define Id_MN_Elxsi_6400 u"ELXSI-6400"
#define Id_MN_EverEx_386 u"EVEREX-386"
#define Id_MN_Foonly_F2 u"FOONLY-F2"
#define Id_MN_Foonly_F3 u"FOONLY-F3"
#define Id_MN_Foonly_F4 u"FOONLY-F4"
#define Id_MN_Gould u"GOULD"
#define Id_MN_Gould_6050 u"GOULD-6050"
#define Id_MN_Gould_6080 u"GOULD-6080"
#define Id_MN_Gould_9050 u"GOULD-9050"
#define Id_MN_Gould_9080 u"GOULD-9080"
#define Id_MN_H_316 u"H-316"
#define Id_MN_H_60_68 u"H-60/68"
#define Id_MN_H_68 u"H-68"
#define Id_MN_H_68_80 u"H-68/80"
#define Id_MN_H_89 u"H-89"
#define Id_MN_Honeywell_DPS_6 u"HONEYWELL-DPS-6"
#define Id_MN_Honeywell_BPS_8_70 u"HONEYWELL-DPS-8/70"
#define Id_MN_HP3000 u"HP3000"
#define Id_MN_HP3000_64 u"HP3000/64"
#define Id_MN_IBM_158 u"IBM-158"
#define Id_MN_IBM_360_67 u"IBM-360/67"
#define Id_MN_IBM_370_3033 u"IBM-370/3033"
#define Id_MN_IBM_3081 u"IBM-3081"
#define Id_MN_IBM_3084QX u"IBM-3084QX"
#define Id_MN_IBM_3101 u"IBM-3101"
#define Id_MN_IBM_4331 u"IBM-4331"
#define Id_MN_IBM_4341 u"IBM-4341"
#define Id_MN_IBM_4361 u"IBM-4361"
#define Id_MN_IBM_4381 u"IBM-4381"
#define Id_MN_IBM_4956 u"IBM-4956"
#define Id_MN_IBM_6152 u"IBM-6152"
#define Id_MN_IBM_PC u"IBM-PC"
#define Id_MN_IBM_PC_AT u"IBM-PC/AT"
#define Id_MN_IBM_PC_RT u"IBM-PC/RT"
#define Id_MN_IBM_PC_XT u"IBM-PC/XT"
#define Id_MN_IBM_RS_6000 u"IBM-RS/6000"
#define Id_MN_IBM_Series_1 u"IBM-SERIES/1"
#define Id_MN_Imagen u"IMAGEN"
#define Id_MN_Imagen_8_300 u"IMAGEN-8/300"
#define Id_MN_Imsai u"IMSAI"
#define Id_MN_Integrated_Solutions u"INTEGRATED-SOLUTIONS"
#define Id_MN_Integrated_Solutions_68K u"INTEGRATED-SOLUTIONS-68K"
#define Id_MN_Integrated_Solutions_Creator u"INTEGRATED-SOLUTIONS-CREATOR"
#define Id_MN_Integrated_Solutions_Creator_8 u"INTEGRATED-SOLUTIONS-CREATOR-8"
#define Id_MN_INTEL_386 u"INTEL-386"
#define Id_MN_INTEL_IPSC u"INTEL-IPSC"
#define Id_MN_Is_1 u"IS-1"
#define Id_MN_Is_68010 u"IS-68010"
#define Id_MN_LMI u"LMI"
#define Id_MN_LSI_11 u"LSI-11"
#define Id_MN_LSI_11_2 u"LSI-11/2"
#define Id_MN_LSI_11_23 u"LSI-11/23"
#define Id_MN_LSI_11_73 u"LSI-11/73"
#define Id_MN_M68000 u"M68000"
#define Id_MN_Mac_II u"MAC-II"
#define Id_MN_Mac_Powerbook u"MAC-POWERBOOK"
#define Id_MN_MacIntosh u"MACINTOSH"
#define Id_MN_MassComp u"MASSCOMP"
#define Id_MN_MC500 u"MC500"
#define Id_MN_68000 u"MC68000"
#define Id_MN_Microport u"MICROPORT"
#define Id_MN_MicroVAX u"MICROVAX"
#define Id_MN_MicroVAX_I u"MICROVAX-I"
#define Id_MN_MV_8000 u"MV/8000"
#define Id_MN_NAS3_5 u"NAS3-5"
#define Id_MN_NCR_Comten_3690 u"NCR-COMTEN-3690"
#define Id_MN_Next_N1000_316 u"NEXT/N1000-316"
#define Id_MN_Now u"NOW"
#define Id_MN_Onyx_Z8000 u"ONYX-Z8000"
#define Id_MN_PDP_11 u"PDP-11"
#define Id_MN_PDP_11_3 u"PDP-11/3"
#define Id_MN_PDP_11_23 u"PDP-11/23"
#define Id_MN_PDP_11_24 u"PDP-11/24"
#define Id_MN_PDP_11_34 u"PDP-11/34"
#define Id_MN_PDP_11_40 u"PDP-11/40"
#define Id_MN_PDP_11_44 u"PDP-11/44"
#define Id_MN_PDP_11_45 u"PDP-11/45"
#define Id_MN_PDP_11_50 u"PDP-11/50"
#define Id_MN_PDP_11_70 u"PDP-11/70"
#define Id_MN_PDP_11_73 u"PDP-11/73"
#define Id_MN_PE_7_32 u"PE-7/32"
#define Id_MN_PE_3205 u"PE-3205"
#define Id_MN_PE_Perq u"PERQ"
#define Id_MN_Plexus_P_60 u"PLEXUS-P/60"
#define Id_MN_PLI u"PLI"
#define Id_MN_Pluribus u"PLURIBUS"
#define Id_MN_Prime_2350 u"PRIME-2350"
#define Id_MN_Prime_2450 u"PRIME-2450"
#define Id_MN_Prime_2755 u"PRIME-2755"
#define Id_MN_Prime_9655 u"PRIME-9655"
#define Id_MN_Prime_9755 u"PRIME-9755"
#define Id_MN_Prime_9955II u"PRIME-9955II"
#define Id_MN_Prime_2250 u"PRIME-2250"
#define Id_MN_Prime_2655 u"PRIME-2655"
#define Id_MN_Prime_9955 u"PRIME-9955"
#define Id_MN_Prime_9950 u"PRIME-9950"
#define Id_MN_Prime_9650 u"PRIME-9650"
#define Id_MN_Prime_9750 u"PRIME-9750"
#define Id_MN_Prime_750 u"PRIME-750"
#define Id_MN_Prime_850 u"PRIME-850"
#define Id_MN_Prime_550II u"PRIME-550II"
#define Id_MN_Pyramid_90 u"PYRAMID-90"
#define Id_MN_Pyramid_90MX u"PYRAMID-90MX"
#define Id_MN_Pyramid_90X u"PYRAMID-90X"
#define Id_MN_Ridge u"RIDGE"
#define Id_MN_Ridge_32 u"RIDGE-32"
#define Id_MN_Ridge_32C u"RIDGE-32C"
#define Id_MN_ROLM_1666 u"ROLM-1666"
#define Id_MN_RS_6000 u"RS/6000"
#define Id_MN_S1_MKIIA u"S1-MKIIA"
#define Id_MN_SMI u"SMI"
#define Id_MN_Sequent_Balance_8000 u"SEQUENT-BALANCE-8000"
#define Id_MN_Emens u"SIEMENS"
#define Id_MN_Silicon_Graphics u"SILICON-GRAPHICS"
#define Id_MN_Silicon_Graphics_Iris u"SILICON-GRAPHICS-IRIS"
#define Id_MN_SGI_Iris_2400 u"SGI-IRIS-2400"
#define Id_MN_SGI_Iris_2500 u"SGI-IRIS-2500"
#define Id_MN_SGI_Iris_3010 u"SGI-IRIS-3010"
#define Id_MN_SGI_Iris_3020 u"SGI-IRIS-3020"
#define Id_MN_SGI_Iris_3030 u"SGI-IRIS-3030"
#define Id_MN_SGI_Iris_3110 u"SGI-IRIS-3110"
#define Id_MN_SGI_Iris_3115 u"SGI-IRIS-3115"
#define Id_MN_SGI_Iris_3120 u"SGI-IRIS-3120"
#define Id_MN_SGI_Iris_3130 u"SGI-IRIS-3130"
#define Id_MN_SGI_Iris_4D_20 u"SGI-IRIS-4D/20"
#define Id_MN_SGI_Iris_4D_20G u"SGI-IRIS-4D/20G"
#define Id_MN_SGI_Iris_4D_25 u"SGI-IRIS-4D/25"
#define Id_MN_SGI_Iris_4D_25G u"SGI-IRIS-4D/25G"
#define Id_MN_SGI_Iris_4D_25S u"SGI-IRIS-4D/25S"
#define Id_MN_SGI_Iris_4D_50 u"SGI-IRIS-4D/50"
#define Id_MN_SGI_Iris_4D_50G u"SGI-IRIS-4D/50G"
#define Id_MN_SGI_Iris_4D_50GT u"SGI-IRIS-4D/50GT"
#define Id_MN_SGI_Iris_4D_60 u"SGI-IRIS-4D/60"
#define Id_MN_SGI_Iris_4D_60G u"SGI-IRIS-4D/60G"
#define Id_MN_SGI_Iris_4D_60T u"SGI-IRIS-4D/60T"
#define Id_MN_SGI_Iris_4D_60GT u"SGI-IRIS-4D/60GT"
#define Id_MN_SGI_Iris_4D_70 u"SGI-IRIS-4D/70"
#define Id_MN_SGI_Iris_4D_70G u"SGI-IRIS-4D/70G"
#define Id_MN_SGI_Iris_4D_70GT u"SGI-IRIS-4D/70GT"
#define Id_MN_SGI_Iris_4D_80GT u"SGI-IRIS-4D/80GT"
#define Id_MN_SGI_Iris_4D_80S u"SGI-IRIS-4D/80S"
#define Id_MN_SGI_Iris_4D_120GTX u"SGI-IRIS-4D/120GTX"
#define Id_MN_SGI_Iris_4D_120S u"SGI-IRIS-4D/120S"
#define Id_MN_SGI_Iris_4D_210GTX u"SGI-IRIS-4D/210GTX"
#define Id_MN_SGI_Iris_4D_210S u"SGI-IRIS-4D/210S"
#define Id_MN_SGI_Iris_4D_220GTX u"SGI-IRIS-4D/220GTX"
#define Id_MN_SGI_Iris_4D_220S u"SGI-IRIS-4D/220S"
#define Id_MN_SGI_Iris_4D_240GTX u"SGI-IRIS-4D/240GTX"
#define Id_MN_SGI_Iris_4D_240S u"SGI-IRIS-4D/240S"
#define Id_MN_SGI_Iris_4D_280GTX u"SGI-IRIS-4D/280GTX"
#define Id_MN_SGI_Iris_4D_280S u"SGI-IRIS-4D/280S"
#define Id_MN_SGI_Iris_CS_12 u"SGI-IRIS-CS/12"
#define Id_MN_SGI_Iris_4Server_8 u"SGI-IRIS-4SERVER-8"
#define Id_MN_Sperry_DCP_10 u"SPERRY-DCP/10"
#define Id_MN_Sun u"SUN"
#define Id_MN_Sun_2 u"SUN-2"
#define Id_MN_Sun_2_50 u"SUN-2/50"
#define Id_MN_Sun_2_100 u"SUN-2/100"
#define Id_MN_Sun_2_120 u"SUN-2/120"
#define Id_MN_Sun_2_130 u"SUN-2/130"
#define Id_MN_Sun_2_140 u"SUN-2/140"
#define Id_MN_Sun_2_150 u"SUN-2/150"
#define Id_MN_Sun_2_160 u"SUN-2/160"
#define Id_MN_Sun_2_170 u"SUN-2/170"
#define Id_MN_Sun_3_50 u"SUN-3/50"
#define Id_MN_Sun_3_60 u"SUN-3/60"
#define Id_MN_Sun_3_75 u"SUN-3/75"
#define Id_MN_Sun_3_80 u"SUN-3/80"
#define Id_MN_Sun_3_110 u"SUN-3/110"
#define Id_MN_Sun_3_140 u"SUN-3/140"
#define Id_MN_Sun_3_150 u"SUN-3/150"
#define Id_MN_Sun_3_160 u"SUN-3/160"
#define Id_MN_Sun_3_180 u"SUN-3/180"
#define Id_MN_Sun_3_200 u"SUN-3/200"
#define Id_MN_Sun_3_260 u"SUN-3/260"
#define Id_MN_Sun_3_280 u"SUN-3/280"
#define Id_MN_Sun_3_470 u"SUN-3/470"
#define Id_MN_Sun_3_480 u"SUN-3/480"
#define Id_MN_Sun_4_60 u"SUN-4/60"
#define Id_MN_Sun_4_110 u"SUN-4/110"
#define Id_MN_Sun_4_150 u"SUN-4/150"
#define Id_MN_Sun_4_200 u"SUN-4/200"
#define Id_MN_Sun_4_260 u"SUN-4/260"
#define Id_MN_Sun_4_280 u"SUN-4/280"
#define Id_MN_Sun_4_330 u"SUN-4/330"
#define Id_MN_Sun_4_370 u"SUN-4/370"
#define Id_MN_Sun_4_390 u"SUN-4/390"
#define Id_MN_Sun_50 u"SUN-50"
#define Id_MN_Sun_100 u"SUN-100"
#define Id_MN_Sun_120 u"SUN-120"
#define Id_MN_Sun_130 u"SUN-130"
#define Id_MN_Sun_150 u"SUN-150"
#define Id_MN_Sun_170 u"SUN-170"
#define Id_MN_Sun_386i_250 u"SUN-386i/250"
#define Id_MN_Sun_68000 u"SUN-68000"
#define Id_MN_Symbolics_3600 u"SYMBOLICS-3600"
#define Id_MN_Symbolics_3670 u"SYMBOLICS-3670"
#define Id_MN_Symmetric_375 u"SYMMETRIC-375"
#define Id_MN_Symult u"SYMULT"
#define Id_MN_Tandem_TXP u"TANDEM-TXP"
#define Id_MN_Tandy_6000 u"TANDY-6000"
#define Id_MN_Tek_6130 u"TEK-6130"
#define Id_MN_TI_Explorer u"TI-EXPLORER"
#define Id_MN_TP_4000 u"TP-4000"
#define Id_MN_TRS_80 u"TRS-80"
#define Id_MN_Univac_1100 u"UNIVAC-1100"
#define Id_MN_Univac_1100_60 u"UNIVAC-1100/60"
#define Id_MN_Univac_1100_62 u"UNIVAC-1100/62"
#define Id_MN_Univac_1100_63 u"UNIVAC-1100/63"
#define Id_MN_Univac_1100_64 u"UNIVAC-1100/64"
#define Id_MN_Univac_1100_70 u"UNIVAC-1100/70"
#define Id_MN_Univac_1160 u"UNIVAC-1160"
#define Id_MN_Unknown u"UNKNOWN"
#define Id_MN_VAX u"VAX"
#define Id_MN_VAX_11_725 u"VAX-11/725"
#define Id_MN_VAX_11_730 u"VAX-11/730"
#define Id_MN_VAX_11_750 u"VAX-11/750"
#define Id_MN_VAX_11_780 u"VAX-11/780"
#define Id_MN_VAX_11_785 u"VAX-11/785"
#define Id_MN_VAX_11_790 u"VAX-11/790"
#define Id_MN_VAX_11_8600 u"VAX-11/8600"
#define Id_MN_VAX_8600 u"VAX-8600"
#define Id_MN_VAXCluster u"VAXCLUSTER"
#define Id_MN_VAXStation u"VAXSTATION"
#define Id_MN_Wang_PC002 u"WANG-PC002"
#define Id_MN_Wang_VS100 u"WANG-VS100"
#define Id_MN_Wang_VS400 u"WANG-VS400"
#define Id_MN_Wyse_386 u"WYSE-386"
#define Id_MN_Wyse_WN5004 u"WYSE-WN5004"
#define Id_MN_Wyse_WN5008 u"WYSE-WN5008"
#define Id_MN_Wyse_WN5104 u"WYSE-WN5104"
#define Id_MN_Wyse_WN5108 u"WYSE-WN5108"
#define Id_MN_Wyse_WX15C u"WYSE-WX15C"
#define Id_MN_Wyse_WX17C u"WYSE-WX17C"
#define Id_MN_Wyse_WX17M u"WYSE-WX17M"
#define Id_MN_Wyse_WX19C u"WYSE-WX19C"
#define Id_MN_Wyse_WX19M u"WYSE-WX19M"
#define Id_MN_Wyse_WYX14M u"WYSE-WYX14M"
#define Id_MN_Wyse_WYX5 u"WYSE-WYX5"
#define Id_MN_Xerox_1108 u"XEROX-1108"
#define Id_MN_Xerox_8010 u"XEROX-8010"
#define Id_MN_Zenith_148 u"ZENITH-148"
#define Id_CS_US_ASCII u"US-ASCII"
#define Id_CS_ISO_8859_1 u"ISO-8859-1"
#define Id_CS_ISO_8859_2 u"ISO-8859-2"
#define Id_CS_ISO_8859_3 u"ISO-8859-3"
#define Id_CS_ISO_8859_4 u"ISO-8859-4"
#define Id_CS_ISO_8859_5 u"ISO-8859-5"
#define Id_CS_ISO_8859_6 u"ISO-8859-6"
#define Id_CS_ISO_8859_7 u"ISO-8859-7"
#define Id_CS_ISO_8859_8 u"ISO-8859-8"
#define Id_CS_ISO_8859_9 u"ISO-8859-9"
#define Id_IPMC_Base_Address u"224.0.0.0"
#define Id_IPMC_All_Systems u"224.0.0.1"
#define Id_IPMC_All_Routers u"224.0.0.2"
#define Id_IPMC_Unassigned u"224.0.0.3"
#define Id_IPMC_DVMRP_Routers u"224.0.0.4"
#define Id_IPMC_OSPFIGP_All_Routers u"224.0.0.5"
#define Id_IPMC_OSPFIGP_Designated_Routers u"224.0.0.6"
#define Id_IPMC_ST_Routers u"224.0.0.7"
#define Id_IPMC_ST_Hosts u"224.0.0.8"
#define Id_IPMC_RIP2_Routers u"224.0.0.9"
#define Id_IPMC_IGRP_Routers u"224.0.0.10"
#define Id_IPMC_Mobile_Agents u"224.0.0.11"
#define Id_IPMC_DHCP_Server u"224.0.0.12"
#define Id_IPMC_DHCP_All_PIM_Routers u"224.0.0.13"
#define Id_IPMC_RSVP_ENCAPSULATION u"224.0.0.14"
#define Id_IPMC_All_CDT_Routers u"224.0.0.15"
#define Id_IPMC_designated_sbm u"224.0.0.16"
#define Id_IPMC_ll_sbms u"224.0.0.17"
#define Id_IPMC_VRRP u"224.0.0.18"
#define Id_IPMC_IPAllL1ISs u"224.0.0.19"
#define Id_IPMC_IPAllL2ISs u"224.0.0.20"
#define Id_IPMC_IPAllIntermediate_Systems u"224.0.0.21"
#define Id_IPMC_IGMP u"224.0.0.22"
#define Id_IPMC_GLOBECAST_ID u"224.0.0.23"
#define Id_IPMC_router_to_switch u"224.0.0.25"
#define Id_IPMC_Al_MPP_Hello u"224.0.0.27"
#define Id_IPMC_ETC_Control u"224.0.0.28"
#define Id_IPMC_GE_FANUC u"224.0.0.29"
#define Id_IPMC_INDIGO_VHDP u"224.0.0.30"
#define Id_IPMC_shinbroadband u"224.0.0.31"
#define Id_IPMC_digistar u"224.0.0.32"
#define Id_IPMC_ff_system_Management u"224.0.0.33"
#define Id_IPMC_pt2_discover u"224.0.0.34"
#define Id_IPMC_DXCLUSTER u"224.0.0.35"
#define Id_IPMC_DTC_Announcement u"224.0.0.36"
#define Id_IPMC_zeroconfaddr_Min u"224.0.0.37"
#define Id_IPMC_zeroconfaddr_Max u"224.0.0.68"
#define Id_IPMC_Cisco_nhap u"224.0.0.101"
#define Id_IPMC_HSPP u"224.0.0.102"
#define Id_IPMC_MDAP u"224.0.0.103"
#define Id_IPMC_mDNS u"224.0.0.251"
#define Id_IPMC_VMTP_Managers u"224.0.1.0"
#define Id_IPMC_NTP_Protocol u"224.0.1.1"
#define Id_IPMC_SGI_Dogfight u"224.0.1.2"
#define Id_IPMC_Rwhod u"224.0.1.3"
#define Id_IPMC_VNP u"224.0.1.4"
#define Id_IPMC_Artificial_Horizons u"224.0.1.5"
#define Id_IPMC_NSS u"224.0.1.6"
#define Id_IPMC_AUDIONEWS u"224.0.1.7"
#define Id_IPMC_SUN_NIS_Plus_Information u"224.0.1.8"
#define Id_IPMC_MTP_Protocol u"224.0.1.9"
#define Id_IPMC_IETF_1_Low_Audio u"224.0.1.10"
#define Id_IPMC_IETF_1_Audio u"224.0.1.11"
#define Id_IPMC_IETF_1_Video u"224.0.1.12"
#define Id_IPMC_IETF_2_Low_Audio u"224.0.1.13"
#define Id_IPMC_IETF_2_Audio u"224.0.1.14"
#define Id_IPMC_IETF_2_Video u"224.0.1.15"
#define Id_IPMC_Music_Service u"224.0.1.16"
#define Id_IPMC_SEANET_TELEMETRY u"224.0.1.17"
#define Id_IPMC_SEANET_IMAGE u"224.0.1.18"
#define Id_IPMC_MLOADD u"224.0.1.19"
#define Id_IPMC_Private_Expiriment u"224.0.1.20"
#define Id_IPMC_DVMRP_on_MOSPF u"224.0.1.21"
#define Id_IPMC_SVRLOC u"224.0.1.22"
#define Id_IPMC_XINGTV u"224.0.1.23"
#define Id_IPMC_Microsoft_DS u"224.0.1.24"
#define Id_IPMC_NBC_Pro u"224.0.1.25"
#define Id_IPMC_NBC_Pfn u"224.0.1.26"
#define Id_IPMC_lmsc_calren_1 u"224.0.1.27"
#define Id_IPMC_lmsc_calren_2 u"224.0.1.28"
#define Id_IPMC_lmsc_calren_3 u"224.0.1.29"
#define Id_IPMC_lmsc_calren_4 u"224.0.1.30"
#define Id_IPMC_ampr_info u"224.0.1.31"
#define Id_IPMC_mtrace u"224.0.1.32"
#define Id_IPMC_RSVP_encap_1 u"224.0.1.33"
#define Id_IPMC_RSVP_encap_2 u"224.0.1.34"
#define Id_IPMC_SVRLOC_DA u"224.0.1.35"
#define Id_IPMC_rln_server u"224.0.1.36"
#define Id_IPMC_proshare_mc u"224.0.1.37"
#define Id_IPMC_dantz u"224.0.1.38"
#define Id_IPMC_cisco_rp_announce u"224.0.1.39"
#define Id_IPMC_cisco_rp_discovery u"224.0.1.40"
#define Id_IPMC_gatekeeper u"224.0.1.41"
#define Id_IPMC_iberiagames u"224.0.1.42"
#define Id_IPMC_nwn_discovery u"224.0.1.43"
#define Id_IPMC_nwn_adaptor u"224.0.1.44"
#define Id_IPMC_isma_1 u"224.0.1.45"
#define Id_IPMC_isma_2 u"224.0.1.46"
#define Id_IPMC_telerate u"224.0.1.47"
#define Id_IPMC_ciena u"224.0.1.48"
#define Id_IPMC_dcap_servers u"224.0.1.49"
#define Id_IPMC_dcap_clients u"224.0.1.50"
#define Id_IPMC_mcntp_directory u"224.0.1.51"
#define Id_IPMC_mbone_vcr_directory u"224.0.1.52"
#define Id_IPMC_heartbeat u"224.0.1.53"
#define Id_IPMC_sun_mc_grp u"224.0.1.54"
#define Id_IPMC_extended_sys u"224.0.1.55"
#define Id_IPMC_pdrncs u"224.0.1.56"
#define Id_IPMC_tns_adv_multi u"224.0.1.57"
#define Id_IPMC_vcals_dmu u"224.0.1.58"
#define Id_IPMC_zuba u"224.0.1.59"
#define Id_IPMC_hp_device_disc u"224.0.1.60"
#define Id_IPMC_tms_production u"224.0.1.61"
#define Id_IPMC_sunscalar u"224.0.1.62"
#define Id_IPMC_mmtp_poll u"224.0.1.63"
#define Id_IPMC_compaq_peer u"224.0.1.64"
#define Id_IPMC_iapp u"224.0.1.65"
#define Id_IPMC_multihasc_com u"224.0.1.66"
#define Id_IPMC_serv_discovery u"224.0.1.67"
#define Id_IPMC_mdhcpdisover u"224.0.1.68"
#define Id_IPMC_MMP_bundle_discovery1 u"224.0.1.69"
#define Id_IPMC_MMP_bundle_discovery2 u"224.0.1.70"
#define Id_IPMC_XYPOINT u"224.0.1.71"
#define Id_IPMC_GilatSkySurfer u"224.0.1.72"
#define Id_IPMC_SharesLive u"224.0.1.73"
#define Id_IPMC_NorthernData u"224.0.1.74"
#define Id_IPMC_SIP u"224.0.1.75"
#define Id_IPMC_IAPP2 u"224.0.1.76"
#define Id_IPMC_AGENTVIEW u"224.0.1.77"
#define Id_IPMC_Tibco_1 u"224.0.1.78"
#define Id_IPMC_Tibco_2 u"224.0.1.79"
#define Id_IPMC_MSP u"224.0.1.80"
#define Id_IPMC_OTT u"224.0.1.81"
#define Id_IPMC_TRACKTICKER u"224.0.1.82"
#define Id_IPMC_dtn_mc u"224.0.1.83"
#define Id_IPMC_jini_announcement u"224.0.1.84"
#define Id_IPMC_jini_request u"224.0.1.85"
#define Id_IPMC_sde_discovery u"224.0.1.86"
#define Id_IPMC_DirecPC_SI u"224.0.1.87"
#define Id_IPMC_B1RMonitor u"224.0.1.88"
#define Id_IPMC_3Com_AMP3 u"224.0.1.89"
#define Id_IPMC_imFtmSvc u"224.0.1.90"
#define Id_IPMC_NQDS4 u"224.0.1.91"
#define Id_IPMC_NQDS5 u"224.0.1.92"
#define Id_IPMC_NQDS6 u"224.0.1.93"
#define Id_IPMC_NLVL12 u"224.0.1.94"
#define Id_IPMC_NTDS1 u"224.0.1.95"
#define Id_IPMC_NTDS2 u"224.0.1.96"
#define Id_IPMC_NODSA u"224.0.1.97"
#define Id_IPMC_NODSB u"224.0.1.98"
#define Id_IPMC_NODSC u"224.0.1.99"
#define Id_IPMC_NODSD u"224.0.1.100"
#define Id_IPMC_NQDS4R u"224.0.1.101"
#define Id_IPMC_NQDS5R u"224.0.1.102"
#define Id_IPMC_NQDS6R u"224.0.1.103"
#define Id_IPMC_NLVL12R u"224.0.1.104"
#define Id_IPMC_NTDS1R u"224.0.1.105"
#define Id_IPMC_NTDS2R u"224.0.1.106"
#define Id_IPMC_NODSAR u"224.0.1.107"
#define Id_IPMC_NODSBR u"224.0.1.108"
#define Id_IPMC_NODSCR u"224.0.1.109"
#define Id_IPMC_NODSDR u"224.0.1.110"
#define Id_IPMC_MRM u"224.0.1.111"
#define Id_IPMC_TVE_FILE u"224.0.1.112"
#define Id_IPMC_TVE_ANNOUNCE u"224.0.1.113"
#define Id_IPMC_Mac u"224.0.1.114"
#define Id_IPMC_Simple u"224.0.1.115"
#define Id_IPMC_SpectraLinkGW u"224.0.1.116"
#define Id_IPMC_dieboldmcast u"224.0.1.117"
#define Id_IPMC_Tivoli u"224.0.1.118"
#define Id_IPMC_pq_lic_mcast u"224.0.1.119"
#define Id_IPMC_HYPERFEED u"224.0.1.120"
#define Id_IPMC_Pipesplatform u"224.0.1.121"
#define Id_IPMC_LiebDevMgmg_DM u"224.0.1.122"
#define Id_IPMC_TRIBALVOICE u"224.0.1.123"
#define Id_IPMC_PolyCom u"224.0.1.125"
#define Id_IPMC_Infront u"224.0.1.126"
#define Id_IPMC_XRX u"224.0.1.127"
#define Id_IPMC_CNN u"224.0.1.128"
#define Id_IPMC_PTP_primary u"224.0.1.129"
#define Id_IPMC_PTP_alternate1 u"224.0.1.130"
#define Id_IPMC_PTP_alternate2 u"224.0.1.131"
#define Id_IPMC_PTP_alternate3 u"224.0.1.132"
#define Id_IPMC_ProCast u"224.0.1.133"
#define Id_IPMC_3Com u"224.0.1.134"
#define Id_IPMC_CS_Multicasting u"224.0.1.135"
#define Id_IPMC_TS_MC_1 u"224.0.1.136"
#define Id_IPMC_Make u"224.0.1.137"
#define Id_IPMC_Teleborsa u"224.0.1.138"
#define Id_IPMC_SUMAConfig u"224.0.1.139"
#define Id_IPMC_DHCP_SERVERS u"224.0.1.141"
#define Id_IPMC_CN u"224.0.1.142"
#define Id_IPMC_EMWIN u"224.0.1.143"
#define Id_IPMC_Alchemy u"224.0.1.144"
#define Id_IPMC_Satcast_1 u"224.0.1.145"
#define Id_IPMC_Satcast_2 u"224.0.1.146"
#define Id_IPMC_Satcast_3 u"224.0.1.147"
#define Id_IPMC_Intline u"224.0.1.148"
#define Id_IPMC_8x8 u"224.0.1.149"
#define Id_IPMC_Intline_1 u"224.0.1.151"
#define Id_IPMC_Intline_2 u"224.0.1.152"
#define Id_IPMC_Intline_3 u"224.0.1.153"
#define Id_IPMC_Intline_4 u"224.0.1.154"
#define Id_IPMC_Intline_5 u"224.0.1.155"
#define Id_IPMC_Intline_6 u"224.0.1.156"
#define Id_IPMC_Intline_7 u"224.0.1.157"
#define Id_IPMC_Intline_8 u"224.0.1.158"
#define Id_IPMC_Intline_9 u"224.0.1.159"
#define Id_IPMC_Intline_10 u"224.0.1.160"
#define Id_IPMC_Intline_11 u"224.0.1.161"
#define Id_IPMC_Intline_12 u"224.0.1.162"
#define Id_IPMC_Intline_13 u"224.0.1.163"
#define Id_IPMC_Intline_14 u"224.0.1.164"
#define Id_IPMC_Intline_15 u"224.0.1.165"
#define Id_IPMC_marratech_cc u"224.0.1.166"
#define Id_IPMC_EMS_InterDev u"224.0.1.167"
#define Id_IPMC_itb301 u"224.0.1.168"
#define Id_IPMC_rtv_audio u"224.0.1.169"
#define Id_IPMC_rtv_video u"224.0.1.170"
#define Id_IPMC_HAVI_Sim u"224.0.1.171"
#define Id_IPMC_Nokia u"224.0.1.172"
#define Id_IPMC_host_request u"224.0.1.173"
#define Id_IPMC_host_announce u"224.0.1.174"
#define Id_IPMC_ptk_cluster u"224.0.1.175"
#define Id_IPMC_Proxim u"224.0.1.176"
#define Id_IPMC_rwho u"224.0.2.1"
#define Id_IPMC_SUN u"224.0.2.2"
#define Id_IPMC_SIAC_Min u"224.0.2.064"
#define Id_IPMC_SIAC_Max u"224.0.2.095"
#define Id_IPMC_CoolCast_Min u"224.0.2.096"
#define Id_IPMC_CoolCast_Max u"224.0.2.127"
#define Id_IPMC_WOZ_Garage_Min u"224.0.2.128"
#define Id_IPMC_WOZ_Garage_Max u"224.0.2.191"
#define Id_IPMC_SIAC_Market_Min u"224.0.2.192"
#define Id_IPMC_SIAC_Market_Max u"224.0.2.255"
#define Id_IPMC_RFE_Generic_Min u"224.0.3.000"
#define Id_IPMC_RFE_Generic_Max u"224.0.3.255"
#define Id_IPMC_RFE_Individual_Min u"224.0.4.000"
#define Id_IPMC_RFE_Individual_Max u"224.0.4.255"
#define Id_IPMC_CDPD_Min u"224.0.5.000"
#define Id_IPMC_CDPD_Max u"224.0.5.127"
#define Id_IPMC_SIAC_Market2_Min u"224.0.5.128"
#define Id_IPMC_SIAC_Market2_Max u"224.0.5.191"
#define Id_IPMC_SIAC_MYSE_Min u"224.0.5.192"
#define Id_IPMC_SIAC_MYSE_Max u"224.0.5.255"
#define Id_IPMC_Cornell_Min u"224.0.6.000"
#define Id_IPMC_Cornell_Max u"224.0.6.127"
#define Id_IPMC_Where_Are_You_Min u"224.0.7.000"
#define Id_IPMC_Where_Are_You_Max u"224.0.7.255"
#define Id_IPMC_INTV_Min u"224.0.8.000"
#define Id_IPMC_INTV_Max u"224.0.8.255"
#define Id_IPMC_Invisible_Min u"224.0.9.000"
#define Id_IPMC_Invisible_Max u"224.0.9.255"
#define Id_IPMC_DLSw_Min u"224.0.10.000"
#define Id_IPMC_DLSw_Max u"224.0.10.255"
#define Id_IPMC_NCC_NET_Min u"224.0.11.000"
#define Id_IPMC_NCC_NET_Max u"224.0.11.255"
#define Id_IPMC_Microsoft_Min u"224.0.12.000"
#define Id_IPMC_Microsoft_Max u"224.0.12.063"
#define Id_IPMC_UUNET_Min u"224.0.13.000"
#define Id_IPMC_UUNET_Max u"224.0.13.255"
#define Id_IPMC_NLANR_Min u"224.0.14.000"
#define Id_IPMC_NLANR_Max u"224.0.14.255"
#define Id_IPMC_Hewlett_Min u"224.0.15.000"
#define Id_IPMC_Hewlett_Max u"224.0.15.255"
#define Id_IPMC_XingNet_Min u"224.0.16.000"
#define Id_IPMC_XingNet_Max u"224.0.16.255"
#define Id_IPMC_Mercantile_Min u"224.0.17.000"
#define Id_IPMC_Mercantile_Max u"224.0.17.031"
#define Id_IPMC_NDQMD1_Min u"224.0.17.032"
#define Id_IPMC_NDQMD1_Max u"224.0.17.063"
#define Id_IPMC_ODN_DTV_Min u"224.0.17.064"
#define Id_IPMC_ODN_DTV_Max u"224.0.17.127"
#define Id_IPMC_Dow_Min u"224.0.18.000"
#define Id_IPMC_Dow_Max u"224.0.18.255"
#define Id_IPMC_Walt_Min u"224.0.19.000"
#define Id_IPMC_Walt_Max u"224.0.19.063"
#define Id_IPMC_Cal_Min u"224.0.19.064"
#define Id_IPMC_Cal_Max u"224.0.19.095"
#define Id_IPMC_SIAC_Market3_Min u"224.0.19.096"
#define Id_IPMC_SIAC_Market3_Max u"224.0.19.127"
#define Id_IPMC_IIG_Min u"224.0.19.128"
#define Id_IPMC_IIG_Max u"224.0.19.191"
#define Id_IPMC_Metropol_Min u"224.0.19.192"
#define Id_IPMC_Metropol_Max u"224.0.19.207"
#define Id_IPMC_Xenoscience_Min u"224.0.19.208"
#define Id_IPMC_Xenoscience_Max u"224.0.19.239"
#define Id_IPMC_HYPERFEED_Min u"224.0.19.240"
#define Id_IPMC_HYPERFEED_Max u"224.0.19.255"
#define Id_IPMC_MS_IP_TV_Min u"224.0.20.000"
#define Id_IPMC_MS_IP_TV_Max u"224.0.20.063"
#define Id_IPMC_Reliable_Min u"224.0.20.064"
#define Id_IPMC_Reliable_Max u"224.0.20.127"
#define Id_IPMC_TRACKTICKER_Min u"224.0.20.128"
#define Id_IPMC_TRACKTICKER_Max u"224.0.20.143"
#define Id_IPMC_CNR_Min u"224.0.20.144"
#define Id_IPMC_CNR_Max u"224.0.20.207"
#define Id_IPMC_Talarian_Min u"224.0.21.000"
#define Id_IPMC_Talarian_Max u"224.0.21.127"
#define Id_IPMC_WORLD_Min u"224.0.22.000"
#define Id_IPMC_WORLD_Max u"224.0.22.255"
#define Id_IPMC_Domain_Min u"224.0.252.000"
#define Id_IPMC_Domain_Max u"224.0.252.000-224.0.252.255"
#define Id_IPMC_Report_Min u"224.0.253.000"
#define Id_IPMC_Report_Max u"224.0.253.255"
#define Id_IPMC_Query_Min u"224.0.254.000"
#define Id_IPMC_Query_Max u"224.0.254.255"
#define Id_IPMC_Border_Min u"224.0.255.000"
#define Id_IPMC_Border_Max u"224.0.255.255"
#define Id_IPMC_Multimedia_Min u"224.2.0.0"
#define Id_IPMC_Multimedia_Max u"224.2.127.253"
#define Id_IPMC_SAPv1 u"224.2.127.254"
#define Id_IPMC_SAPv0 u"224.2.127.255"
#define Id_IPMC_SAP_Min u"224.2.128.0"
#define Id_IPMC_SAP_Max u"224.2.255.255"
#define Id_IPMC_DIS_Min u"224.252.000.000"
#define Id_IPMC_DIS_Max u"224.255.255.255"
#define Id_IPMC_Source_Min u"232.000.000.000"
#define Id_IPMC_Source_Max u"232.255.255.255"
#define Id_IPMC_GLOP_Min u"233.000.000.000"
#define Id_IPMC_GLOP_Max u"233.255.255.255"
#define Id_IPMC_Administratively_Min u"239.000.000.000"
#define Id_IPMC_Administratively_Max u"239.255.255.255"
#define Id_IPMC_Organization_Local_Min u"239.192.000.000"
#define Id_IPMC_Organization_Local_Max u"239.251.255.255"
#define Id_IPMC_Site_Local1_Min u"239.252.000.000"
#define Id_IPMC_Site_Local1_Max u"239.252.255.255"
#define Id_IPMC_Site_Local2_Min u"239.253.000.000"
#define Id_IPMC_Site_Local2_Max u"239.253.255.255"
#define Id_IPMC_Site_Local3_Min u"239.254.000.000"
#define Id_IPMC_Site_Local3_Max u"239.254.255.255"
#define Id_IPMC_Site_Local4_Min u"239.255.000.000"
#define Id_IPMC_Site_Local4_Max u"239.255.255.255"
#define Id_IPMC_rasadv u"239.255.002.002"
static constexpr System::Int8 Id_IPREL_SAP = System::Int8(0x0);
static constexpr System::Int8 Id_IPREL_MADCAP = System::Int8(0x1);
static constexpr System::Int8 Id_IPREL_SLPV2 = System::Int8(0x2);
static constexpr System::Int8 Id_IPREL_MZAP = System::Int8(0x3);
static constexpr System::Int8 Id_IPREL_DNS = System::Int8(0x4);
static constexpr System::Int8 Id_IPREL_SSDP = System::Int8(0x5);
static constexpr System::Int8 Id_IPREL_DHCPV4 = System::Int8(0x6);
static constexpr System::Int8 Id_IPREL_AAP = System::Int8(0x7);
static constexpr System::Int8 Id_IPREL_MBUS = System::Int8(0x8);
#define Id_IPv6MC_NL_All_Nodes_Address u"FF01:0:0:0:0:0:0:1"
#define Id_IPv6MC_NL_All_Routers_Address u"FF01:0:0:0:0:0:0:2"
#define Id_IPv6MC_NL_mDNSv6 u"FF01:0:0:0:0:0:0:FB"
#define Id_IPv6MC_LL_All_Nodes_Address u"FF02:0:0:0:0:0:0:1"
#define Id_IPv6MC_LL_All_Routers_Address u"FF02:0:0:0:0:0:0:2"
#define Id_IPv6MC_LL_DVMRP_Routers u"FF02:0:0:0:0:0:0:4"
#define Id_IPv6MC_LL_OSPFIGP u"FF02:0:0:0:0:0:0:5"
#define Id_IPv6MC_LL_OSPFIGP_Designated_Routers u"FF02:0:0:0:0:0:0:6"
#define Id_IPv6MC_LL_ST_Routers u"FF02:0:0:0:0:0:0:7"
#define Id_IPv6MC_LL_ST_Hosts u"FF02:0:0:0:0:0:0:8"
#define Id_IPv6MC_LL_RIP_Routers u"FF02:0:0:0:0:0:0:9"
#define Id_IPv6MC_LL_EIGRP_Routers u"FF02:0:0:0:0:0:0:A"
#define Id_IPv6MC_LL_Mobile_Agents u"FF02:0:0:0:0:0:0:B"
#define Id_IPv6MC_LL_SSDP u"FF02:0:0:0:0:0:0:C"
#define Id_IPv6MC_LL_All_PIM_Routers u"FF02:0:0:0:0:0:0:D"
#define Id_IPv6MC_LL_RSVP_ENCAPSULATION u"FF02:0:0:0:0:0:0:E"
#define Id_IPv6MC_LL_UPnP u"FF02:0:0:0:0:0:0:F"
#define Id_IPv6MC_LL_All_MLDv2_capable_routers u"FF02:0:0:0:0:0:0:16"
#define Id_IPv6MC_LL_All_Snoopers u"FF02:0:0:0:0:0:0:6A"
#define Id_IPv6MC_LL_PTP_pdelay u"FF02:0:0:0:0:0:0:6B"
#define Id_IPv6MC_LL_Saratoga u"FF02:0:0:0:0:0:0:6C"
#define Id_IPv6MC_LL_LL_MANET_Routers u"FF02:0:0:0:0:0:0:6D"
#define Id_IPv6MC_LL_mDNSv6 u"FF02:0:0:0:0:0:0:FB"
#define Id_IPv6MC_LL_Link_Name u"FF02:0:0:0:0:0:1:1"
#define Id_IPv6MC_LL_All_dhcp_agents u"FF02:0:0:0:0:0:1:2"
#define Id_IPv6MC_LL_Link_local_Multicast_Name_Resolution u"FF02:0:0:0:0:0:1:3"
#define Id_IPv6MC_LL_DTCP_Announcement u"FF02:0:0:0:0:0:1:4"
#define Id_IPv6MC_SL_All_Routers_Address u"FF05:0:0:0:0:0:0:2"
#define Id_IPv6MC_SL_mDNSv6 u"FF05:0:0:0:0:0:0:FB"
#define Id_IPv6MC_SL_All_dhcp_servers u"FF05:0:0:0:0:0:1:3"
#define Id_IPv6MC_SL_Deprecated u"FF05:0:0:0:0:0:1:4"
#define Id_IPv6MC_V_Reserved_Multicast_Address u"FF0X:0:0:0:0:0:0:0"
#define Id_IPv6MC_V_SSDP u"FF0X:0:0:0:0:0:0:C"
#define Id_IPv6MC_V_mDNSv6 u"FF0X:0:0:0:0:0:0:FB"
#define Id_IPv6MC_V_VMTP_Managers_Group u"FF0X:0:0:0:0:0:0:100"
#define Id_IPv6MC_V_NTP u"FF0X:0:0:0:0:0:0:101"
#define Id_IPv6MC_V_SGI_Dogfight u"FF0X:0:0:0:0:0:0:102"
#define Id_IPv6MC_V_Rwhod u"FF0X:0:0:0:0:0:0:103"
#define Id_IPv6MC_V_VMP u"FF0X:0:0:0:0:0:0:104"
#define Id_IPv6MC_V_Artificial_Horizons u"FF0X:0:0:0:0:0:0:105"
#define Id_IPv6MC_V_NSS u"FF0X:0:0:0:0:0:0:106"
#define Id_IPv6MC_V_AUDIONEWS u"FF0X:0:0:0:0:0:0:107"
#define Id_IPv6MC_V_SUN_NIS_Plus u"FF0X:0:0:0:0:0:0:108"
#define Id_IPv6MC_V_MTP u"FF0X:0:0:0:0:0:0:109"
#define Id_IPv6MC_V_IETF_1_LOW_AUDIO u"FF0X:0:0:0:0:0:0:10A"
#define Id_IPv6MC_V_IETF_1_AUDIO u"FF0X:0:0:0:0:0:0:10B"
#define Id_IPv6MC_V_IETF_1_VIDEO u"FF0X:0:0:0:0:0:0:10C"
#define Id_IPv6MC_V_IETF_2_LOW_AUDIO u"FF0X:0:0:0:0:0:0:10D"
#define Id_IPv6MC_V_IETF_2_AUDIO u"FF0X:0:0:0:0:0:0:10E"
#define Id_IPv6MC_V_IETF_2_VIDEO u"FF0X:0:0:0:0:0:0:10F"
#define Id_IPv6MC_V_MUSIC_SERVICE u"FF0X:0:0:0:0:0:0:110"
#define Id_IPv6MC_V_SEANET_TELEMETRY u"FF0X:0:0:0:0:0:0:111"
#define Id_IPv6MC_V_SEANET_IMAGE u"FF0X:0:0:0:0:0:0:112"
#define Id_IPv6MC_V_MLOADD u"FF0X:0:0:0:0:0:0:113"
#define Id_IPv6MC_V_any_private_experiment u"FF0X:0:0:0:0:0:0:114"
#define Id_IPv6MC_V_DVMRP_on_MOSPF u"FF0X:0:0:0:0:0:0:115"
#define Id_IPv6MC_V_SVRLOC u"FF0X:0:0:0:0:0:0:116"
#define Id_IPv6MC_V_XINGTV u"FF0X:0:0:0:0:0:0:117"
#define Id_IPv6MC_V_microsoft_ds u"FF0X:0:0:0:0:0:0:118"
#define Id_IPv6MC_V_nbc_pro u"FF0X:0:0:0:0:0:0:119"
#define Id_IPv6MC_V_nbc_pfn u"FF0X:0:0:0:0:0:0:11A"
#define Id_IPv6MC_V_lmsc_calren_1 u"FF0X:0:0:0:0:0:0:11B"
#define Id_IPv6MC_V_lmsc_calren_2 u"FF0X:0:0:0:0:0:0:11C"
#define Id_IPv6MC_V_lmsc_calren_3 u"FF0X:0:0:0:0:0:0:11D"
#define Id_IPv6MC_V_lmsc_calren_4 u"FF0X:0:0:0:0:0:0:11E"
#define Id_IPv6MC_V_ampr_info u"FF0X:0:0:0:0:0:0:11F"
#define Id_IPv6MC_V_mtrace u"FF0X:0:0:0:0:0:0:120"
#define Id_IPv6MC_V_RSVP_encap_1 u"FF0X:0:0:0:0:0:0:121"
#define Id_IPv6MC_V_RSVP_encap_2 u"FF0X:0:0:0:0:0:0:122"
#define Id_IPv6MC_V_SVRLOC_DA u"FF0X:0:0:0:0:0:0:123"
#define Id_IPv6MC_V_rln_server u"FF0X:0:0:0:0:0:0:124"
#define Id_IPv6MC_V_proshare_mc u"FF0X:0:0:0:0:0:0:125"
#define Id_IPv6MC_V_dantz u"FF0X:0:0:0:0:0:0:126"
#define Id_IPv6MC_V_cisco_rp_announce u"FF0X:0:0:0:0:0:0:127"
#define Id_IPv6MC_V_cisco_rp_discovery u"FF0X:0:0:0:0:0:0:128"
#define Id_IPv6MC_V_gatekeeper u"FF0X:0:0:0:0:0:0:129"
#define Id_IPv6MC_V_iberiagames u"FF0X:0:0:0:0:0:0:12A"
#define Id_IPv6MC_V_X_Display u"FF0X:0:0:0:0:0:0:12B"
#define Id_IPv6MC_V_oap_multicast u"FF0X:0:0:0:0:0:0:12C"
#define Id_IPv6MC_V_DvbServDisc u"FF0X:0:0:0:0:0:0:12D"
#define Id_IPv6MC_V_Ricoh_device_ctrl u"FF0X:0:0:0:0:0:0:12E"
#define Id_IPv6MC_V_Ricoh_device_ctrl2 u"FF0X:0:0:0:0:0:0:12F"
#define Id_IPv6MC_V_UPnP u"FF0X:0:0:0:0:0:0:130"
#define Id_IPv6MC_V_Systech_Mcast u"FF0X:0:0:0:0:0:0:131"
#define Id_IPv6MC_V_omasg u"FF0X:0:0:0:0:0:0:132"
#define Id_IPv6MC_V_PTP_primary u"FF0X:0:0:0:0:0:0:181"
#define Id_IPv6MC_V_PTP_alternate1 u"FF0X:0:0:0:0:0:0:182"
#define Id_IPv6MC_V_PTP_alternate2 u"FF0X:0:0:0:0:0:0:183"
#define Id_IPv6MC_V_PTP_alternate3 u"FF0X:0:0:0:0:0:0:184"
#define Id_IPv6MC_V_rwho_Group u"FF0X:0:0:0:0:0:0:201"
#define Id_IPv6MC_V_SUN_RPC_PMAPPROC_CALLIT u"FF0X:0:0:0:0:0:0:202"
#define Id_IPv6MC_V_Mbus_ipv6 u"FF0X:0:0:0:0:0:0:300"
#define Id_IPv6MC_V_SAPv1_Announcements u"FF0X:0:0:0:0:0:2:7FFE"
#define Id_IPv6MC_V_SAPv0_Announcements_deprecated u"FF0X:0:0:0:0:0:2:7FFF"
}	/* namespace Idassignednumbers */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDASSIGNEDNUMBERS)
using namespace Idassignednumbers;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdassignednumbersHPP
