int CEncryptedStreamSocket::Receive(void* lpBuf, int nBufLen, int nFlags){
	m_nObfuscationBytesReceived = CAsyncSocketEx::Receive(lpBuf, nBufLen, nFlags);
	m_bFullReceive = m_nObfuscationBytesReceived == (uint32_t)nBufLen;

	if(m_nObfuscationBytesReceived == SOCKET_ERROR || m_nObfuscationBytesReceived <= 0){
		return m_nObfuscationBytesReceived;
	}
	switch (m_StreamCryptState) {
		case ECS_NONE: // disabled, just pass it through
			return m_nObfuscationBytesReceived;
		case ECS_PENDING:
		case ECS_PENDING_SERVER:
			ASSERT( false );
			DebugLogError(_T("CEncryptedStreamSocket Received data before sending on outgoing connection"));
			m_StreamCryptState = ECS_NONE;
			return m_nObfuscationBytesReceived;
		case ECS_UNKNOWN:{
			uint32_t nRead = 1;
			bool bNormalHeader = false;
			switch (((uchar*)lpBuf)[0]){
				case OP_EDONKEYPROT:
				case OP_PACKEDPROT:
				case OP_EMULEPROT:
					bNormalHeader = true;
					break;
			}
			if (!bNormalHeader){
				StartNegotiation(false);
				const uint32_t nNegRes = Negotiate((uchar*)lpBuf + nRead, m_nObfuscationBytesReceived - nRead);
				if (nNegRes == (-1))
					return 0;
				nRead += nNegRes;
				if (nRead != (uint32_t)m_nObfuscationBytesReceived){
					// this means we have more data then the current negotiation step required (or there is a bug) and this should never happen
					// (note: even if it just finished the handshake here, there still can be no data left, since the other client didnt received our response yet)
					DebugLogError(_T("CEncryptedStreamSocket: Client %s sent more data then expected while negotiating, disconnecting (1)"), DbgGetIPString());
					OnError(ERR_ENCRYPTION);
				}
				return 0;
			}
			else{
				// doesn't seems to be encrypted
				m_StreamCryptState = ECS_NONE;

				// if we require an encrypted connection, cut the connection here. This shouldn't happen that often
				// at least with other up-to-date eMule clients because they check for incompability before connecting if possible
				if (thePrefs.IsClientCryptLayerRequired()){
					// TODO: Remove me when i have been solved
					// Even if the Require option is enabled, we currently have to accept unencrypted connection which are made
					// for lowid/firewall checks from servers and other from us selected client. Otherwise, this option would
					// always result in a lowid/firewalled status. This is of course not nice, but we can't avoid this walkarround
					// untill servers and kad completely support encryption too, which will at least for kad take a bit
					// only exception is the .ini option ClientCryptLayerRequiredStrict which will even ignore test connections
					// Update: New server now support encrypted callbacks

					SOCKADDR_IN sockAddr = {0};
					int nSockAddrLen = sizeof(sockAddr);
					GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);		
					if (thePrefs.IsClientCryptLayerRequiredStrict() || (!theApp.serverconnect->AwaitingTestFromIP(sockAddr.sin_addr.S_un.S_addr)
						&& !theApp.clientlist->IsKadFirewallCheckIP(sockAddr.sin_addr.S_un.S_addr)) )
					{
#if defined(_DEBUG) || defined(_BETA)
					// TODO: Remove after testing
					AddDebugLogLine(DLP_DEFAULT, false, _T("Rejected incoming connection because Obfuscation was required but not used %s"), DbgGetIPString() );
#endif
						OnError(ERR_ENCRYPTION_NOTALLOWED);
						return 0;
					}
					else
						AddDebugLogLine(DLP_DEFAULT, false, _T("Incoming unencrypted firewallcheck connection permitted despite RequireEncryption setting  - %s"), DbgGetIPString() );
				}

				return m_nObfuscationBytesReceived; // buffer was unchanged, we can just pass it through
			}
		}
		case ECS_ENCRYPTING:
			// basic obfuscation enabled and set, so decrypt and pass along
			RC4Crypt((uchar*)lpBuf, (uchar*)lpBuf, m_nObfuscationBytesReceived, m_pRC4ReceiveKey);
			return m_nObfuscationBytesReceived;
		case ECS_NEGOTIATING:{
			const uint32_t nRead = Negotiate((uchar*)lpBuf, m_nObfuscationBytesReceived);
			if (nRead == (-1))
				return 0;
			else if (nRead != (uint32_t)m_nObfuscationBytesReceived && m_StreamCryptState != ECS_ENCRYPTING){
				// this means we have more data then the current negotiation step required (or there is a bug) and this should never happen
				DebugLogError(_T("CEncryptedStreamSocket: Client %s sent more data then expected while negotiating, disconnecting (2)"), DbgGetIPString());
				OnError(ERR_ENCRYPTION);
				return 0;
			}
			else if (nRead != (uint32_t)m_nObfuscationBytesReceived && m_StreamCryptState == ECS_ENCRYPTING){
				// we finished the handshake and if we this was an outgoing connection it is allowed (but strange and unlikely) that the client sent payload
				DebugLogWarning(_T("CEncryptedStreamSocket: Client %s has finished the handshake but also sent payload on a outgoing connection"), DbgGetIPString());
				memmove(lpBuf, (uchar*)lpBuf + nRead, m_nObfuscationBytesReceived - nRead);
				return m_nObfuscationBytesReceived - nRead;
			}
			else
				return 0;
		}
		default:
			ASSERT( false );
			return m_nObfuscationBytesReceived;
	}
}