// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DirectPlay8.pas' rev: 34.00 (Windows)

#ifndef Winapi_Directplay8HPP
#define Winapi_Directplay8HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinSock.hpp>
#include <Winapi.DirectSound.hpp>

//-- user supplied -----------------------------------------------------------
#include "dplay8.h"
#include "dplobby8.h"
#include "dvoice.h"
DECLARE_DINTERFACE_TYPE(IDirectPlay8Address);
typedef _di_IDirectPlay8Address *PIDirectPlay8Address;
DECLARE_DINTERFACE_TYPE(IDirectPlay8AddressIP);
typedef PFNDPNMESSAGEHANDLER TFNDPNMessageHandler;
DECLARE_DINTERFACE_TYPE(IDirectPlay8Client);
DECLARE_DINTERFACE_TYPE(IDirectPlay8Server);
DECLARE_DINTERFACE_TYPE(IDirectPlay8Peer);
DECLARE_DINTERFACE_TYPE(IDirectPlay8ThreadPool);
DECLARE_DINTERFACE_TYPE(IDirectPlay8NATResolver);
DECLARE_DINTERFACE_TYPE(IDirectPlay8LobbyClient);
DECLARE_DINTERFACE_TYPE(IDirectPlay8LobbiedApplication);
typedef PDVMESSAGEHANDLER TDVMessageHandler;
DECLARE_DINTERFACE_TYPE(IDirectPlayVoiceClient);
DECLARE_DINTERFACE_TYPE(IDirectPlayVoiceServer);
DECLARE_DINTERFACE_TYPE(IDirectPlayVoiceTest);

namespace Winapi
{
namespace Directplay8
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef GUID TDPNARefIID;

typedef DPNID TDPNID;

typedef DPNHANDLE *PDPNHandle;

typedef DPNHANDLE TDPNHandle;

typedef _DPN_APPLICATION_DESC *PDPNApplicationDesc;

typedef _DPN_APPLICATION_DESC TDPNApplicationDesc;

typedef _BUFFERDESC *PBufferDesc;

typedef _BUFFERDESC TBufferDesc;

typedef _BUFFERDESC *PDPNBufferDesc;

typedef _BUFFERDESC TDPNBufferDesc;

typedef _DPN_CAPS *PDPNCaps;

typedef _DPN_CAPS TDPNCaps;

typedef _DPN_CAPS_EX *PDPNCapsEx;

typedef _DPN_CAPS_EX TDPNCapsEx;

typedef _DPN_CONNECTION_INFO *PDPNConnectionInfo;

typedef _DPN_CONNECTION_INFO TDPNConnectionInfo;

typedef _DPN_GROUP_INFO *PDPNGroupInfo;

typedef _DPN_GROUP_INFO TDPNGroupInfo;

typedef _DPN_PLAYER_INFO *PDPNPlayerInfo;

typedef _DPN_PLAYER_INFO TDPNPlayerInfo;

typedef _DPN_SECURITY_CREDENTIALS *PDPNSecurityCredentials;

typedef _DPN_SECURITY_CREDENTIALS TDPNSecurityCredentials;

typedef _DPN_SECURITY_DESC *PDPNSecurityDesc;

typedef _DPN_SECURITY_DESC TDPNSecurityDesc;

typedef _DPN_SERVICE_PROVIDER_INFO *PDPNServiceProviderInfo;

typedef _DPN_SERVICE_PROVIDER_INFO TDPNServiceProviderInfo;

typedef _DPN_SP_CAPS *PDPNSpCaps;

typedef _DPN_SP_CAPS TDPNSpCaps;

typedef _DPNMSG_ADD_PLAYER_TO_GROUP *PDPNMsgAddPlayerToGroup;

typedef _DPNMSG_ADD_PLAYER_TO_GROUP TDPNMsgAddPlayerToGroup;

typedef _DPNMSG_ASYNC_OP_COMPLETE *PDPNMsgAsyncOpComplete;

typedef _DPNMSG_ASYNC_OP_COMPLETE TDPNMsgAsyncOpComplete;

typedef _DPNMSG_CLIENT_INFO *PDPNMsgClientInfo;

typedef _DPNMSG_CLIENT_INFO TDPNMsgClientInfo;

typedef _DPNMSG_CONNECT_COMPLETE *PDPNMsgConnectComplete;

typedef _DPNMSG_CONNECT_COMPLETE TDPNMsgConnectComplete;

typedef _DPNMSG_CREATE_GROUP *PDPNMsgCreateGroup;

typedef _DPNMSG_CREATE_GROUP TDPNMsgCreateGroup;

typedef _DPNMSG_CREATE_PLAYER *PDPNMsgCreatePlayer;

typedef _DPNMSG_CREATE_PLAYER TDPNMsgCreatePlayer;

typedef _DPNMSG_DESTROY_GROUP *PDPNMsgDestroyGroup;

typedef _DPNMSG_DESTROY_GROUP TDPNMsgDestroyGroup;

typedef _DPNMSG_DESTROY_PLAYER *PDPNMsgDestroyPlayer;

typedef _DPNMSG_DESTROY_PLAYER TDPNMsgDestroyPlayer;

typedef _DPNMSG_ENUM_HOSTS_QUERY *PDPNMsgEnumHostsQuery;

typedef _DPNMSG_ENUM_HOSTS_QUERY TDPNMsgEnumHostsQuery;

typedef _DPNMSG_ENUM_HOSTS_RESPONSE *PDPNMsgEnumHostsResponse;

typedef _DPNMSG_ENUM_HOSTS_RESPONSE TDPNMsgEnumHostsResponse;

typedef _DPNMSG_GROUP_INFO *PDPNMsgGroupInfo;

typedef _DPNMSG_GROUP_INFO TDPNMsgGroupInfo;

typedef _DPNMSG_HOST_MIGRATE *PDPNMsgHostMigrate;

typedef _DPNMSG_HOST_MIGRATE TDPNMsgHostMigrate;

typedef _DPNMSG_INDICATE_CONNECT *PDPNMsgIndicateConnect;

typedef _DPNMSG_INDICATE_CONNECT TDPNMsgIndicateConnect;

typedef _DPNMSG_INDICATED_CONNECT_ABORTED *PDPNMsgIndicatedConnectAborted;

typedef _DPNMSG_INDICATED_CONNECT_ABORTED TDPNMsgIndicatedConnectAborted;

typedef _DPNMSG_PEER_INFO *PDPNMsgPeerInfo;

typedef _DPNMSG_PEER_INFO TDPNMsgPeerInfo;

typedef _DPNMSG_RECEIVE *PDPNMsgReceive;

typedef _DPNMSG_RECEIVE TDPNMsgReceive;

typedef _DPNMSG_REMOVE_PLAYER_FROM_GROUP *PDPNMsgRemovePlayerFromGroup;

typedef _DPNMSG_REMOVE_PLAYER_FROM_GROUP TDPNMsgRemovePlayerFromGroup;

typedef _DPNMSG_RETURN_BUFFER *PDPNMsgReturnBuffer;

typedef _DPNMSG_RETURN_BUFFER TDPNMsgReturnBuffer;

typedef _DPNMSG_SEND_COMPLETE *PDPNMsgSendComplete;

typedef _DPNMSG_SEND_COMPLETE TDPNMsgSendComplete;

typedef _DPNMSG_SERVER_INFO *PDPNMsgServerInfo;

typedef _DPNMSG_SERVER_INFO TDPNMsgServerInfo;

typedef _DPNMSG_TERMINATE_SESSION *PDPNMsgTerminateSession;

typedef _DPNMSG_TERMINATE_SESSION TDPNMsgTerminateSession;

typedef _DPNMSG_CREATE_THREAD *PDPNMsgCreateThread;

typedef _DPNMSG_CREATE_THREAD TDPNMsgCreateThread;

typedef _DPNMSG_DESTROY_THREAD *PDPNMsgDestroyThread;

typedef _DPNMSG_DESTROY_THREAD TDPNMsgDestroyThread;

typedef _DPNMSG_NAT_RESOLVER_QUERY *PDPNMsgNatResolverQuery;

typedef _DPNMSG_NAT_RESOLVER_QUERY TDPNMsgNatResolverQuery;

typedef _DPL_APPLICATION_INFO *PDPLApplicationInfo;

typedef _DPL_APPLICATION_INFO TDPLApplicationInfo;

typedef _DPL_CONNECTION_SETTINGS *PDPLConnectionSettings;

typedef _DPL_CONNECTION_SETTINGS TDPLConnectionSettings;

typedef _DPL_CONNECT_INFO *PDPLConnectInfo;

typedef _DPL_CONNECT_INFO TDPLConnectInfo;

typedef _DPL_PROGRAM_DESC *PDPLProgramDesc;

typedef _DPL_PROGRAM_DESC TDPLProgramDesc;

typedef _DPL_MESSAGE_CONNECT *PDPLMessageConnect;

typedef _DPL_MESSAGE_CONNECT TDPLMessageConnect;

typedef _DPL_MESSAGE_CONNECTION_SETTINGS *PDPLMessageConnectionSettings;

typedef _DPL_MESSAGE_CONNECTION_SETTINGS TDPLMessageConnectionSettings;

typedef _DPL_MESSAGE_DISCONNECT *PDPLMessageDisconnect;

typedef _DPL_MESSAGE_DISCONNECT TDPLMessageDisconnect;

typedef _DPL_MESSAGE_RECEIVE *PDPLMessageReceive;

typedef _DPL_MESSAGE_RECEIVE TDPLMessageReceive;

typedef _DPL_MESSAGE_SESSION_STATUS *PDPLMessageSessionStatus;

typedef _DPL_MESSAGE_SESSION_STATUS TDPLMessageSessionStatus;

typedef unsigned *PDVID;

typedef unsigned TDVID;

typedef DVCAPS *PDVCaps;

typedef DVCAPS TDVCaps;

typedef DVCLIENTCONFIG *PDVClientConfig;

typedef DVCLIENTCONFIG TDVClientConfig;

typedef DVCOMPRESSIONINFO *PDVCompressionInfo;

typedef DVCOMPRESSIONINFO TDVCompressionInfo;

typedef DVSESSIONDESC *PDVSessionDesc;

typedef DVSESSIONDESC TDVSessionDesc;

typedef DVSOUNDDEVICECONFIG *PDVSoundDeviceConfig;

typedef DVSOUNDDEVICECONFIG TDVSoundDeviceConfig;

typedef DVMSG_CONNECTRESULT *PDVMsgConnectResult;

typedef DVMSG_CONNECTRESULT TDVMsgConnectResult;

typedef DVMSG_CREATEVOICEPLAYER *PDVMsgCreateVoicePlayer;

typedef DVMSG_CREATEVOICEPLAYER TDVMsgCreateVoicePlayer;

typedef DVMSG_DELETEVOICEPLAYER *PDVMsgDeleteVoicePlayer;

typedef DVMSG_DELETEVOICEPLAYER TDVMsgDeleteVoicePlayer;

typedef DVMSG_DISCONNECTRESULT *PDVMsgDisconnectResult;

typedef DVMSG_DISCONNECTRESULT TDVMsgDisconnectResult;

typedef DVMSG_HOSTMIGRATED *PDVMsgHostMigrated;

typedef DVMSG_HOSTMIGRATED TDVMsgHostMigrated;

typedef DVMSG_INPUTLEVEL *PDVMsgInputlevel;

typedef DVMSG_INPUTLEVEL TDVMsgInputlevel;

typedef DVMSG_LOCALHOSTSETUP *PDVMsgLocalHostSetup;

typedef DVMSG_LOCALHOSTSETUP TDVMsgLocalHostSetup;

typedef DVMSG_OUTPUTLEVEL *PDVMsgOutputLevel;

typedef DVMSG_OUTPUTLEVEL TDVMsgOutputLevel;

typedef DVMSG_PLAYEROUTPUTLEVEL *PDVMsgPlayerOutputLevel;

typedef DVMSG_PLAYEROUTPUTLEVEL TDVMsgPlayerOutputLevel;

typedef DVMSG_PLAYERVOICESTART *PDVMsgPlayerVoiceStart;

typedef DVMSG_PLAYERVOICESTART TDVMsgPlayerVoiceStart;

typedef DVMSG_PLAYERVOICESTOP *PDVMsgPlayerVoiceStop;

typedef DVMSG_PLAYERVOICESTOP TDVMsgPlayerVoiceStop;

typedef DVMSG_RECORDSTART *PDVMsgRecordStart;

typedef DVMSG_RECORDSTART TDVMsgRecordStart;

typedef DVMSG_RECORDSTOP *PDVMsgRecordStop;

typedef DVMSG_RECORDSTOP TDVMsgRecordStop;

typedef DVMSG_SESSIONLOST *PDVMsgSessionLost;

typedef DVMSG_SESSIONLOST TDVMsgSessionLost;

typedef DVMSG_SETTARGETS *PDVMsgSetTargets;

typedef DVMSG_SETTARGETS TDVMsgSetTargets;

typedef PDVMsgConnectResult PDvmsg_Connectresult;

typedef DVMSG_CONNECTRESULT TDvmsg_Connectresult;

typedef PDVMsgCreateVoicePlayer PDvmsg_Createvoiceplayer;

typedef DVMSG_CREATEVOICEPLAYER TDvmsg_Createvoiceplayer;

typedef PDVMsgDeleteVoicePlayer PDvmsg_Deletevoiceplayer;

typedef DVMSG_DELETEVOICEPLAYER TDvmsg_Deletevoiceplayer;

typedef PDVMsgDisconnectResult PDvmsg_Disconnectresult;

typedef DVMSG_DISCONNECTRESULT TDvmsg_Disconnectresult;

typedef PDVMsgHostMigrated PDvmsg_Hostmigrated;

typedef DVMSG_HOSTMIGRATED TDvmsg_Hostmigrated;

typedef PDVMsgInputlevel PDvmsg_Inputlevel;

typedef DVMSG_INPUTLEVEL TDvmsg_Inputlevel;

typedef PDVMsgLocalHostSetup PDvmsg_Localhostsetup;

typedef DVMSG_LOCALHOSTSETUP TDvmsg_Localhostsetup;

typedef PDVMsgOutputLevel PDvmsg_Outputlevel;

typedef DVMSG_OUTPUTLEVEL TDvmsg_Outputlevel;

typedef PDVMsgPlayerOutputLevel PDvmsg_Playeroutputlevel;

typedef DVMSG_PLAYEROUTPUTLEVEL TDvmsg_Playeroutputlevel;

typedef PDVMsgPlayerVoiceStart PDvmsg_Playervoicestart;

typedef DVMSG_PLAYERVOICESTART TDvmsg_Playervoicestart;

typedef PDVMsgPlayerVoiceStop PDvmsg_Playervoicestop;

typedef DVMSG_PLAYERVOICESTOP TDvmsg_Playervoicestop;

typedef PDVMsgRecordStart PDvmsg_Recordstart;

typedef DVMSG_RECORDSTART TDvmsg_Recordstart;

typedef PDVMsgRecordStop PDvmsg_Recordstop;

typedef DVMSG_RECORDSTOP TDvmsg_Recordstop;

typedef PDVMsgSessionLost PDvmsg_Sessionlost;

typedef DVMSG_SESSIONLOST TDvmsg_Sessionlost;

typedef PDVMsgSetTargets PDvmsg_Settargets;

typedef DVMSG_SETTARGETS TDvmsg_Settargets;

typedef PDPNApplicationDesc PDPN_Application_Desc;

typedef _DPN_APPLICATION_DESC TDPN_Application_Desc;

typedef PDPNCaps PDPN_Caps;

typedef _DPN_CAPS TDPN_Caps;

typedef PDPNCapsEx PDPN_Caps_Ex;

typedef _DPN_CAPS_EX TDPN_Caps_Ex;

typedef PDPNConnectionInfo PDPN_Connection_Info;

typedef _DPN_CONNECTION_INFO TDPN_Connection_Info;

typedef PDPNGroupInfo PDPN_Group_Info;

typedef _DPN_GROUP_INFO TDPN_Group_Info;

typedef PDPNPlayerInfo PDPN_Player_Info;

typedef _DPN_PLAYER_INFO TDPN_Player_Info;

typedef PDPNSecurityCredentials PDPN_Security_Credentials;

typedef _DPN_SECURITY_CREDENTIALS TDPN_Security_Credentials;

typedef PDPNSecurityDesc PDPN_Security_Desc;

typedef _DPN_SECURITY_DESC TDPN_Security_Desc;

typedef PDPNServiceProviderInfo PDPN_Service_Provider_Info;

typedef _DPN_SERVICE_PROVIDER_INFO TDPN_Service_Provider_Info;

typedef PDPNSpCaps PDPN_Sp_Caps;

typedef _DPN_SP_CAPS TDPN_Sp_Caps;

typedef PDPNMsgAddPlayerToGroup PDPNMsg_Add_Player_To_Group;

typedef _DPNMSG_ADD_PLAYER_TO_GROUP TDPNMsg_Add_Player_To_Group;

typedef PDPNMsgAsyncOpComplete PDPNMsg_Async_Op_Complete;

typedef _DPNMSG_ASYNC_OP_COMPLETE TDPNMsg_Async_Op_Complete;

typedef PDPNMsgClientInfo PDPNMsg_Client_Info;

typedef _DPNMSG_CLIENT_INFO TDPNMsg_Client_Info;

typedef PDPNMsgConnectComplete PDPNMsg_Connect_Complete;

typedef _DPNMSG_CONNECT_COMPLETE TDPNMsg_Connect_Complete;

typedef PDPNMsgCreateGroup PDPNMsg_Create_Group;

typedef _DPNMSG_CREATE_GROUP TDPNMsg_Create_Group;

typedef PDPNMsgCreatePlayer PDPNMsg_Create_Player;

typedef _DPNMSG_CREATE_PLAYER TDPNMsg_Create_Player;

typedef PDPNMsgDestroyGroup PDPNMsg_Destroy_Group;

typedef _DPNMSG_DESTROY_GROUP TDPNMsg_Destroy_Group;

typedef PDPNMsgDestroyPlayer PDPNMsg_Destroy_Player;

typedef _DPNMSG_DESTROY_PLAYER TDPNMsg_Destroy_Player;

typedef PDPNMsgEnumHostsQuery PDPNMsg_Enum_Hosts_Query;

typedef _DPNMSG_ENUM_HOSTS_QUERY TDPNMsg_Enum_Hosts_Query;

typedef PDPNMsgEnumHostsResponse PDPNMsg_Enum_Hosts_Response;

typedef _DPNMSG_ENUM_HOSTS_RESPONSE TDPNMsg_Enum_Hosts_Response;

typedef PDPNMsgGroupInfo PDPNMsg_Group_Info;

typedef _DPNMSG_GROUP_INFO TDPNMsg_Group_Info;

typedef PDPNMsgHostMigrate PDPNMsg_Host_Migrate;

typedef _DPNMSG_HOST_MIGRATE TDPNMsg_Host_Migrate;

typedef PDPNMsgIndicateConnect PDPNMsg_Indicate_Connect;

typedef _DPNMSG_INDICATE_CONNECT TDPNMsg_Indicate_Connect;

typedef PDPNMsgIndicatedConnectAborted PDPNMsg_Indicated_Connect_Aborted;

typedef _DPNMSG_INDICATED_CONNECT_ABORTED TDPNMsg_Indicated_Connect_Aborted;

typedef PDPNMsgPeerInfo PDPNMsg_Peer_Info;

typedef _DPNMSG_PEER_INFO TDPNMsg_Peer_Info;

typedef PDPNMsgReceive PDPNMsg_Receive;

typedef _DPNMSG_RECEIVE TDPNMsg_Receive;

typedef PDPNMsgRemovePlayerFromGroup PDPNMsg_Remove_Player_From_Group;

typedef _DPNMSG_REMOVE_PLAYER_FROM_GROUP TDPNMsg_Remove_Player_From_Group;

typedef PDPNMsgReturnBuffer PDPNMsg_Return_Buffer;

typedef _DPNMSG_RETURN_BUFFER TDPNMsg_Return_Buffer;

typedef PDPNMsgSendComplete PDPNMsg_Send_Complete;

typedef _DPNMSG_SEND_COMPLETE TDPNMsg_Send_Complete;

typedef PDPNMsgServerInfo PDPNMsg_Server_Info;

typedef _DPNMSG_SERVER_INFO TDPNMsg_Server_Info;

typedef PDPNMsgTerminateSession PDPNMsg_Terminate_Session;

typedef _DPNMSG_TERMINATE_SESSION TDPNMsg_Terminate_Session;

typedef PDPNMsgCreateThread PDPNMsg_Create_Thread;

typedef _DPNMSG_CREATE_THREAD TDPNMsg_Create_Thread;

typedef PDPNMsgDestroyThread PDPNMsg_Destroy_Thread;

typedef _DPNMSG_DESTROY_THREAD TDPNMsg_Destroy_Thread;

typedef PDPNMsgNatResolverQuery PDPNMsg_Nat_Resolver_Query;

typedef _DPNMSG_NAT_RESOLVER_QUERY TDPNMsg_Nat_Resolver_Query;

//-- var, const, procedure ---------------------------------------------------
static const int MAKE_DPNHRESULT_R = int(-2146074624);
static const int MAKE_DVHRESULT_R = int(-2146107392);
}	/* namespace Directplay8 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECTPLAY8)
using namespace Winapi::Directplay8;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Directplay8HPP
