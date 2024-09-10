void CALLBACK CBoxHttpServer::SendFile(ULONG_PTR dwParam)
{
	CSendFile* pSend = (CSendFile*)dwParam;
	BOOL bRet = 0;

	if(pSend->m_pBuf == NULL)
	{
		if(pSend->m_nPos == pSend->m_nSize)
		{
			//long l = sizeof(pSend->buf);
			long l = pSend->sizeofbuf;

			if(l > pSend->m_ullLen)
				l = pSend->m_ullLen;

			pSend->m_nPos = 0;
			pSend->m_nSize = pSend->m_pFile->Read(pSend->buf, l);
		}

		if(pSend->m_nSize)
			bRet = WriteFileEx((HANDLE)pSend->m_pSocket->m_hSocket, pSend->buf + pSend->m_nPos,
				pSend->m_nSize - pSend->m_nPos, pSend, IoCompletionRoutine);
	}else
		bRet = WriteFileEx((HANDLE)pSend->m_pSocket->m_hSocket, pSend->m_pBuf + pSend->m_ullStart,
				pSend->m_ullLen, pSend, IoCompletionRoutine);

	if(!bRet)
	{
		pSend->m_pSocket->Break();
		delete pSend;
	}
}