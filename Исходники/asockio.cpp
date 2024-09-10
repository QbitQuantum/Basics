static VOID CALLBACK SocketIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
	PAIO_CONTEXT pctx = (PAIO_CONTEXT)lpOverlapped;
	switch(pctx->operation) {
		case SIOP_ACCEPT:
			{
				PACCEPT_CONTEXT pactx = (PACCEPT_CONTEXT)pctx;
				PTCP_END_POINT pep = (PTCP_END_POINT)pctx->hep;
				PCONNECTION pconn = (PCONNECTION)pctx->hconn;
				PSOCKADDR_IN psainLocal, psainRemote;
				INT llen, rlen;
				if(dwErrorCode==STATUS_SUCCESS) {
					setsockopt(pconn->s, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)&pep->s, sizeof(pep->s));
					lpfnGetAcceptExSockaddrs(pactx->buf, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (LPSOCKADDR *)&psainLocal, &llen, (LPSOCKADDR *)&psainRemote, &rlen);
					pconn->rcving = TRUE;
					if(pconn->handler.OnConnect((HCONNECT)pconn, psainLocal, psainRemote, pconn->key)) {
						pconn->Recv();
					} else {
						pconn->rcving = FALSE;
						Disconnect((HCONNECT)pconn);
					}
				} else {
					EnterCriticalSection(&pep->cs_free_list);
					pep->free_conns.push_front((HCONNECT)pconn);
					LeaveCriticalSection(&pep->cs_free_list);
				}
				pep->Accept();
			}
			break;
		case SIOP_CONNECT:
			{
				PCONNECTION pconn = (PCONNECTION)pctx->hconn;
				SOCKADDR_IN sainLocal, sainRemote;
				INT llen, rlen;
				if(dwErrorCode==STATUS_SUCCESS) {
					setsockopt(pconn->s, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);
					llen = rlen = sizeof(SOCKADDR_IN);
					getsockname(pconn->s, (PSOCKADDR)&sainLocal, &llen);
					getpeername(pconn->s, (PSOCKADDR)&sainRemote, &rlen);
					pconn->rcving = TRUE;
					if(pconn->handler.OnConnect((HCONNECT)pconn, &sainLocal, &sainRemote, pconn->key)) {
						pconn->Recv(pctx);
					} else {
						pconn->rcving = FALSE;
						Disconnect((HCONNECT)pconn);
						UnlockInputBuffer(BufOfCtx(pctx));
					}
				} else {
					pconn->handler.OnConnectFailed(pconn->key);
					EnterCriticalSection(&cs_free_olist);
					free_oconns.push_front((HCONNECT)pconn);
					LeaveCriticalSection(&cs_free_olist);
					UnlockInputBuffer(BufOfCtx(pctx));
				}
			}
			break;
		case SIOP_DISCONNECT:
			{
				PTCP_END_POINT pep = (PTCP_END_POINT)pctx->hep;
				PCONNECTION pconn = (PCONNECTION)pctx->hconn;
				if(dwErrorCode==STATUS_SUCCESS) {
					while(pconn->rcving) SwitchToThread();
					pconn->handler.OnDisconnect((HCONNECT)pconn, pconn->key);
					if(pep) {
						EnterCriticalSection(&pep->cs_free_list);
						pep->free_conns.push_front((HCONNECT)pconn);
						LeaveCriticalSection(&pep->cs_free_list);
					} else {
						EnterCriticalSection(&cs_free_olist);
						free_oconns.push_front((HCONNECT)pconn);
						LeaveCriticalSection(&cs_free_olist);
					}
				}
				UnlockOutputBuffer(BufOfCtx(pctx));
			}
			break;
		case SIOP_RECV:
			{
				PCONNECTION pconn = (PCONNECTION)pctx->hconn;
				if(dwErrorCode==STATUS_SUCCESS && dwNumberOfBytesTransfered) {
					pconn->handler.OnData((HCONNECT)pconn, dwNumberOfBytesTransfered, BufOfCtx(pctx), pconn->key);
					pconn->Recv(pctx);
				} else {
					pconn->rcving = FALSE;
					Disconnect((HCONNECT)pconn);
					UnlockInputBuffer(BufOfCtx(pctx));
				}
			}
			break;
		case SIOP_RECVFROM:
			{
				PUDP_END_POINT pep = (PUDP_END_POINT)pctx->hep;
				if(dwErrorCode==STATUS_SUCCESS && dwNumberOfBytesTransfered) {
					pep->handler.OnDatagram((HEP)pep, &pep->sainSrc, dwNumberOfBytesTransfered, BufOfCtx(pctx), pep->key);
					pep->RecvFrom(pctx);
				} else {
					UnlockInputBuffer(BufOfCtx(pctx));
				}
			}
			break;
		case SIOP_SEND:
		case SIOP_SENDTO:
			UnlockOutputBuffer(BufOfCtx(pctx));
			break;
	}
}