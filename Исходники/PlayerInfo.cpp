BOOL playerInfo::SendPacket(CHAR *packet, WORD size)
{
	SEND_STRUCT *Send = new SEND_STRUCT;

	CopyMemory(Send->m_SendBuffer, packet, size);

	Send->m_SendWSABuf.buf = Send->m_SendBuffer;
	Send->m_SendWSABuf.len = size;

	ZeroMemory(&Send->m_OverExSend, sizeof(OVERLAPPED_EX));
	Send->m_OverExSend.m_io_type = IO_SEND;

	DWORD SendBytes;

	INT Result = WSASend(	m_socket,
							&Send->m_SendWSABuf,
							1,
							&SendBytes,
							0,
							reinterpret_cast<LPWSAOVERLAPPED> (&Send->m_OverExSend),
							NULL);

	if (Result == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			printf("send() error!!\n");
			return FALSE;
		}
	}

	return TRUE;
}