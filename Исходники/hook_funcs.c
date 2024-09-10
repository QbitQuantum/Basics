SECURITY_STATUS SEC_ENTRY _EncryptMessage(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo) {
	SECURITY_STATUS ret;
	LPBYTE data;
	int i;
	
	if(pMessage) {
		i = pMessage->cBuffers;

		while(i--)
			if(pMessage->pBuffers[i].BufferType == SECBUFFER_DATA) {
				data = (LPBYTE) malloc(pMessage->pBuffers[i].cbBuffer*sizeof(BYTE) + 1);
				strncpy((LPSTR) data, (LPCSTR) pMessage->pBuffers[i].pvBuffer, pMessage->pBuffers[i].cbBuffer);
				data[pMessage->pBuffers[i].cbBuffer] = NULL;
				OutputDebugStringA((LPCSTR) data);
				free(data);
			}
	}

	UnHookAPI("EncryptMessage", "secur32.dll", _EncryptMsg);
	ret = EncryptMessage(phContext, fQOP, pMessage, MessageSeqNo);
	_EncryptMsg = HookAPI("EncryptMessage", "secur32.dll", (DWORD) _EncryptMessage);
	return ret;
}