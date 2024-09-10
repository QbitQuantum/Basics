int32_t CWGDConn::DealBuffer(CSimpleBuffer & simpleBuffer)
{
	uchar_t* pBuffer = simpleBuffer.GetBuffer();
	WGDHEAD* pHead = (WGDHEAD*)pBuffer;
	int32_t nTotalSize = sizeof(WGDHEAD) + pHead->nDataLen;

	//m_pBaseSocket->m_pBaseServer->OnStatisticEnd();

	m_pServer->OnReceivedNotify(m_pBaseSocket->GetSocket(), pBuffer, nTotalSize);

	simpleBuffer.Read(NULL, nTotalSize);

	return 0;

#if 0
	uchar_t* pBuffer = simpleBuffer.GetBuffer();
	WGDHEAD* pHead = (WGDHEAD*)pBuffer;

	char* name = pHead->szFileName;

	switch (pHead->type)
	{
	case eNet_Upload:
		{
			std::string strFilePath = RECEIVE_DIR + std::string(pHead->szFileName);
			int nHeadLen = pHead->nDataLen;
			m_in_buf.Read(NULL, sizeof(WGDHEAD));
			int32_t nWrite = WriteFile(strFilePath, m_in_buf.GetBuffer(), nHeadLen);
			if (nWrite > 0 && nWrite == nHeadLen)
			{
				m_in_buf.Read(NULL, nWrite);
			}

			return 0;
		}
		break;
	case eNet_Download:
		{
			std::string strFilePath = RECEIVE_DIR + std::string(name);
			m_in_buf.Read(NULL, sizeof(WGDHEAD));

			CSimpleBuffer tmpBuffer;

			WGDHEAD head;
			head.type = eNet_Download;
			//strncpy(head.szFileName, pHead->szFileName, sizeof(head.szFileName));

			tmpBuffer.Write((void*)&head, sizeof(WGDHEAD));

			int32_t nRead = ReadFile(strFilePath, tmpBuffer);

			WGDHEAD* pHead = (WGDHEAD*)tmpBuffer.GetBuffer();
			pHead->nDataLen = nRead;

			Send(tmpBuffer.GetBuffer(), tmpBuffer.GetWriteOffset());
		}
		break;
	case eNet_GetDirectory:
		{

		}
		break;
	default:
		break;
	}

	return int32_t(0);
#endif
}