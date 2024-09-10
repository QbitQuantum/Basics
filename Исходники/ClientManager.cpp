/* 2016.05.24 */
void ClientManager::recv_packet_user_exit_room(ObjectUser* info, CStreamSP* pStreamSP)
{
	bool b_success = false;

	if (pRoommanager == NULL)
	{
		pRoommanager = new Croom_manager;
	}

#if 1
	//16.06.07 by lsy
	pRoommanager->exit_room(info->sUser_info.room_num, info->sUser_info.id);

	//16.06.07 by lsy RPC send/return test

	p_mysql->rpc_send("30");

	pRoommanager->broadcast_room(info, pStreamSP, 1);

	//16.06.07

#endif
	/**********************/
	/* packet return      */
	/**********************/
	CStream* p_wStream = *pStreamSP;
	BYTE send_packet[24];
	USHORT p_Head = P_LOBBY_MSG;
	USHORT p_s_Head = P_S_QUIT_ROOM;

	/****************/
	/* Open Stream  */
	/****************/
	memset(send_packet, 0, sizeof(send_packet));
	p_wStream->StartWrite(send_packet);
	p_wStream->WriteData(&p_Head);
	p_wStream->WriteData(&p_s_Head);
	/****************/
	/* Close Stream */
	/****************/
	p_wStream->EndWrite();
	memcpy(pc_socket_info->dataBuf.buf, send_packet, sizeof(send_packet));

	DWORD writen = 0;
	/* return message by send socket */
	if (WSASend(info->sUser_info.id,
		(WSABUF*)&pc_socket_info->dataBuf,
		1,
		(DWORD *)&writen,
		0,
		&pc_socket_info->overlapped,
		NULL) == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			printf("WSASend Error.. [%d] \n", WSAGetLastError());
		}
	}

}