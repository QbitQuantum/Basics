void LSSLContext::Shutdown(LSockByteStream* SockByteStream, const TCHAR* TargetName)
{
	//SSPI: отключение от сервера
	//сначала выставим нужный статус у контекста
	DWORD ShutdownToken = SCHANNEL_SHUTDOWN;
	SecBufferDesc ShutDownBufferDesc;
	SecBuffer     ShutDownBuffers[1];
	ShutDownBufferDesc.cBuffers = 1;
	ShutDownBufferDesc.pBuffers = ShutDownBuffers;
	ShutDownBufferDesc.ulVersion = SECBUFFER_VERSION;
	ShutDownBuffers[0].pvBuffer   = &ShutdownToken;
	ShutDownBuffers[0].BufferType = SECBUFFER_TOKEN;
	ShutDownBuffers[0].cbBuffer   = sizeof(ShutdownToken);

	//VERIFY(SEC_E_OK==ApplyControlToken(GetContextHandle(), &ShutDownBufferDesc));

	//затем получим данные для отправки
	ShutDownBuffers[0].BufferType = SECBUFFER_TOKEN;
	ShutDownBuffers[0].pvBuffer   = 0;
	ShutDownBuffers[0].cbBuffer   = 0;

	/*VERIFY(SEC_E_OK==*/InitializeSecurityContext(&m_hUserCred, GetContextHandle(), const_cast<TCHAR*>(TargetName),
		                                       m_ReqContextAttr, 0, 0, 0, 0, 0,
		                                       &ShutDownBufferDesc, &m_ContextAttr, &m_ContextExpiry)/*)*/;

	//ASSERT(ShutDownBuffers[0].pvBuffer&&ShutDownBuffers[0].cbBuffer);

	//WS: отправим обработанные SCHANNEL данные
	SockByteStream->RawSend(ShutDownBuffers[0].pvBuffer, ShutDownBuffers[0].cbBuffer);

	FreeContextBuffer(ShutDownBuffers[0].pvBuffer);
	ShutDownBuffers[0].pvBuffer=0;
	ShutDownBuffers[0].cbBuffer=0;
}