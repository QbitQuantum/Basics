int NetlibSslRead(SslHandle *ssl, char *buf, int num, int peek)
{
	if (ssl == NULL) return SOCKET_ERROR;

	if (num <= 0) return 0;

	if (ssl->state != sockOpen || (ssl->cbRecDataBuf != 0 && (!peek || ssl->cbRecDataBuf >= num)))
		return NetlibSslReadSetResult(ssl, buf, num, peek);

	SECURITY_STATUS scRet = SEC_E_OK;

	while (true) {
		if (0 == ssl->cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE) {
			if (ssl->sbIoBuffer <= ssl->cbIoBuffer) {
				ssl->sbIoBuffer += 2048;
				ssl->pbIoBuffer = (PUCHAR)mir_realloc(ssl->pbIoBuffer, ssl->sbIoBuffer);
			}

			if (peek) {
				static const TIMEVAL tv = { 0 };
				fd_set fd;
				FD_ZERO(&fd);
				FD_SET(ssl->s, &fd);

				DWORD cbData = select(1, &fd, NULL, NULL, &tv);
				if (cbData == SOCKET_ERROR) {
					ssl->state = sockError;
					return NetlibSslReadSetResult(ssl, buf, num, peek);
				}

				if (cbData == 0 && ssl->cbRecDataBuf)
					return NetlibSslReadSetResult(ssl, buf, num, peek);
			}

			DWORD cbData = recv(ssl->s, (char*)ssl->pbIoBuffer + ssl->cbIoBuffer, ssl->sbIoBuffer - ssl->cbIoBuffer, 0);
			if (cbData == SOCKET_ERROR) {
				Netlib_Logf(NULL, "SSL failure recieving data (%d)", WSAGetLastError());
				ssl->state = sockError;
				return NetlibSslReadSetResult(ssl, buf, num, peek);
			}

			if (cbData == 0) {
				Netlib_Logf(NULL, "SSL connection gracefully closed");
				if (peek && ssl->cbRecDataBuf) {
					ssl->state = sockClosed;
					return NetlibSslReadSetResult(ssl, buf, num, peek);
				}

				// Server disconnected.
				if (ssl->cbIoBuffer) {
					ssl->state = sockError;
					return NetlibSslReadSetResult(ssl, buf, num, peek);
				}

				return 0;
			}
			ssl->cbIoBuffer += cbData;
		}

		// Attempt to decrypt the received data.
		SecBuffer Buffers[4];
		Buffers[0].pvBuffer = ssl->pbIoBuffer;
		Buffers[0].cbBuffer = ssl->cbIoBuffer;
		Buffers[0].BufferType = SECBUFFER_DATA;

		Buffers[1].BufferType = SECBUFFER_EMPTY;
		Buffers[2].BufferType = SECBUFFER_EMPTY;
		Buffers[3].BufferType = SECBUFFER_EMPTY;

		SecBufferDesc Message;
		Message.ulVersion = SECBUFFER_VERSION;
		Message.cBuffers = _countof(Buffers);
		Message.pBuffers = Buffers;

		if (g_pSSPI->DecryptMessage != NULL && g_pSSPI->DecryptMessage != PVOID(0x80000000))
			scRet = g_pSSPI->DecryptMessage(&ssl->hContext, &Message, 0, NULL);
		else
			scRet = ((DECRYPT_MESSAGE_FN)g_pSSPI->Reserved4)(&ssl->hContext, &Message, 0, NULL);

		// The input buffer contains only a fragment of an
		// encrypted record. Loop around and read some more
		// data.
		if (scRet == SEC_E_INCOMPLETE_MESSAGE)
			continue;

		if (scRet != SEC_E_OK && scRet != SEC_I_RENEGOTIATE && scRet != SEC_I_CONTEXT_EXPIRED) {
			ReportSslError(scRet, __LINE__);
			ssl->state = sockError;
			return NetlibSslReadSetResult(ssl, buf, num, peek);
		}

		// Locate data and (optional) extra buffers.
		SecBuffer *pDataBuffer = NULL;
		SecBuffer *pExtraBuffer = NULL;
		for (int i = 1; i < _countof(Buffers); i++) {
			if (pDataBuffer == NULL && Buffers[i].BufferType == SECBUFFER_DATA)
				pDataBuffer = &Buffers[i];

			if (pExtraBuffer == NULL && Buffers[i].BufferType == SECBUFFER_EXTRA)
				pExtraBuffer = &Buffers[i];
		}

		// Return decrypted data.
		DWORD resNum = 0;
		if (pDataBuffer) {
			DWORD bytes = peek ? 0 : min((DWORD)num, pDataBuffer->cbBuffer);
			DWORD rbytes = pDataBuffer->cbBuffer - bytes;
			if (rbytes > 0) {
				int nbytes = ssl->cbRecDataBuf + rbytes;
				if (ssl->sbRecDataBuf < nbytes) {
					ssl->sbRecDataBuf = nbytes;
					ssl->pbRecDataBuf = (PUCHAR)mir_realloc(ssl->pbRecDataBuf, nbytes);
				}
				memcpy(ssl->pbRecDataBuf + ssl->cbRecDataBuf, (char*)pDataBuffer->pvBuffer + bytes, rbytes);
				ssl->cbRecDataBuf = nbytes;
			}

			if (peek) {
				resNum = bytes = min(num, ssl->cbRecDataBuf);
				memcpy(buf, ssl->pbRecDataBuf, bytes);
			}
			else {
				resNum = bytes;
				memcpy(buf, pDataBuffer->pvBuffer, bytes);
			}
		}

		// Move any "extra" data to the input buffer.
		if (pExtraBuffer) {
			memmove(ssl->pbIoBuffer, pExtraBuffer->pvBuffer, pExtraBuffer->cbBuffer);
			ssl->cbIoBuffer = pExtraBuffer->cbBuffer;
		}
		else ssl->cbIoBuffer = 0;

		if (pDataBuffer && resNum)
			return resNum;

		// Server signaled end of session
		if (scRet == SEC_I_CONTEXT_EXPIRED) {
			Netlib_Logf(NULL, "SSL Server signaled SSL Shutdown");
			ssl->state = sockClosed;
			return NetlibSslReadSetResult(ssl, buf, num, peek);
		}

		if (scRet == SEC_I_RENEGOTIATE) {
			// The server wants to perform another handshake
			// sequence.

			scRet = ClientHandshakeLoop(ssl, FALSE);
			if (scRet != SEC_E_OK) {
				ssl->state = sockError;
				return NetlibSslReadSetResult(ssl, buf, num, peek);
			}
		}
	}
}