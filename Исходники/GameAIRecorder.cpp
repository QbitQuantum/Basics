bool CGameAIRecorder::AddFileToRemoteArchive(const char* szFile)
{
	bool bResult = false;

	ICryPak *pCryPak = gEnv->pSystem->GetIPak();
	assert(pCryPak);

	if (m_pRemoteArchive && pCryPak)
	{
		string sLocalPath = PathUtil::Make("..", szFile);

		AZ::IO::HandleType fileHandle = pCryPak->FOpen(sLocalPath.c_str(), "rb");
		if (fileHandle != AZ::IO::InvalidHandle)
		{
			// Add the file to the PAK
			size_t iFileSize = pCryPak->FGetSize(fileHandle);
			BYTE* pBuffer = (BYTE*)pCryPak->PoolMalloc(iFileSize);
			if (!pBuffer)
			{
				CryLogAlways("[Warning] Failed when packing file to remote archive: Out of memory. (\'%s\')", szFile);
			}
			else
			{
				pCryPak->FReadRaw(pBuffer, iFileSize, 1, fileHandle);
				int iResult = m_pRemoteArchive->UpdateFile(PathUtil::GetFile(szFile), pBuffer, iFileSize, ICryArchive::METHOD_DEFLATE, ICryArchive::LEVEL_BETTER);
				if (0 != iResult)
				{
				CryLogAlways("[Warning] Failed when packing file to remote archive: File update failed. (\'%s\')", szFile);
				}
				else
				{
					bResult = true;
				}

				pCryPak->PoolFree(pBuffer);
			}

			pCryPak->FClose(fileHandle);
		}
	}

	return bResult;
}