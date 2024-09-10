void CLuaRemoteDebug::ReceiveFileContentsRequest(CSerializationHelper &buffer)
{
	const char* fileName = buffer.ReadString();
	ICryPak* pCryPak = gEnv->pCryPak;
	FILE* pFile = pCryPak->FOpen(fileName + 1, "rb");
	if (pFile != NULL)
	{
		m_sendBuffer.Write((char)ePT_FileContents);
		m_sendBuffer.WriteString(fileName);

		// Get file length
		pCryPak->FSeek(pFile, 0, SEEK_END);
		uint32 length = (uint32)pCryPak->FTell(pFile);
		pCryPak->FSeek(pFile, 0, SEEK_SET);

		m_sendBuffer.Write(length);

		const int CHUNK_BUF_SIZE = 1024;
		char buf[CHUNK_BUF_SIZE];
		size_t lenRead;

		while (!pCryPak->FEof(pFile))
		{
			lenRead = pCryPak->FRead(buf, CHUNK_BUF_SIZE, pFile);
			m_sendBuffer.WriteBuffer(buf, (int)lenRead);
		}

		SendBuffer();
	}
	else
	{
		assert(false);
	}
}