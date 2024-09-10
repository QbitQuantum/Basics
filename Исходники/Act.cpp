unsigned int WINAPI Proactor::ThreadProc(LPVOID lpParam)
{
	SOCKETINFO *sInfo;
	int flags;
	int readn;
	Proactor *p_Pa = (Proactor*)lpParam;
	network *p_Net;

	/* initialize networking */
	p_Net = Singleton<network>::getInstancePtr();

	while (1) {
		if ((p_Net->client_fd = WSAAccept(p_Net->listen_fd, NULL, NULL, NULL, 0)) == INVALID_SOCKET) {
			printf("Accept Error\n");
			return 1;
		}
		printf(" Accepted client fd[%d] ", p_Net->client_fd);

		sInfo = pClientManager->GetEmptySocketinfo();
		pClientManager->PushUser(p_Net->client_fd);


		sInfo->fd = p_Net->client_fd;
		sInfo->dataBuf.len = MAX_BUFF;
		sInfo->dataBuf.buf = sInfo->buf;
		sInfo->IOOperation = ClientIoRead;

		/**************************/
		/* CreateIoCompletionPort */
		/**************************/
		HANDLE check = CreateIoCompletionPort((HANDLE)p_Net->client_fd, p_Pa->g_hIOCP, (DWORD)sInfo, 0);

		flags = 0;

		if (WSARecv(sInfo->fd, &sInfo->dataBuf, 1, (DWORD *)&readn, (DWORD *)&flags, &(sInfo->overlapped), NULL) == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				printf("[%d] wsarecv error %d\n", __LINE__, WSAGetLastError());
			}
		}
		/* 최초 반환패킷은 수신패킷 전용 스레드에서 처리하기로
#if 0
		ObjectUser* pObjUser = pClientManager->FindUser(p_Net->client_fd);
		if (send(sInfo->fd,
			(char*)&pObjUser->sUser_info,
			sizeof(pObjUser->sUser_info),
			0) == SOCKET_ERROR){
			printf("Send Error\n");
		}

		pClientManager->broadcast_success_login(sInfo->fd);
#else
		//ObjectUser* pObjUser = pClientManager->FindUser(p_Net->client_fd);
		DWORD writen = 0;
		// return message by send socket
		if (WSASend(sInfo->fd,
			(WSABUF*)&sInfo->dataBuf,
			1,
			(DWORD *)&writen,
			0,
			&sInfo->overlapped,
			NULL) == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				printf("WSASend Error.. [%d] \n", WSAGetLastError());
			}
		}

#endif
		*/
	}
	return 1;
}