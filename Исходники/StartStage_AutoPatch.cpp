bool StartStage_AutoPatch::processMessage(unsigned int uiMsgID, void* pParam)
{
	WriteConWarning("Entry Proecess Message For C++\n");

	switch (uiMsgID)
	{
	case MSG_DOWNLOAD_URL:
		{
			NDMsg_DownloadUrl* pkUrl = (NDMsg_DownloadUrl*) pParam;
			m_bRequestedDownload = true;

			if (pkUrl->getMsgID() != uiMsgID)
			{
				return false;
			}

			if (!pkUrl->getNeedDownload())
			{
				setDone();
				return true;
			}

			m_pkStageUI->showProgress(true);

			const StringVector& kVec = pkUrl->getUrlVector();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			char szExeFileName[500] = {0};
			GetModuleFileNameA(0, szExeFileName, sizeof(szExeFileName));
			string strCurrentDir = getPath(szExeFileName);
			SetCurrentDirectoryA(strCurrentDir.c_str());
			strCurrentDir.erase(strCurrentDir.end() - 1);
			strCurrentDir = getUpFolder(strCurrentDir);
#endif

			WriteConWarning("Will Download Patch From Server!\n");

			for (unsigned int uiIndex = 0; uiIndex < kVec.size(); uiIndex++)
			{
				const string& strUrl = kVec[uiIndex];

				if (0 == strUrl.size())
				{
					continue;
				}

				int nPos = strUrl.find_last_of('/');

				if (-1 == nPos)
				{
					continue;
				}

				string strFileName = strUrl.substr(nPos + 1, strUrl.length());

				DownloadPackage* pkPackage = new DownloadPackage;
				pkPackage->FromUrl(strUrl.c_str());

				string strPath = "";
				char szTempPath[2048] = { 0 };
				//SDCARD_GAME_NAME_SLASH
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				strPath = string(SDCARD_GAME_NAME_SLASH) + strFileName;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				strPath = strCurrentDir + strFileName;
#endif

				WriteCon(
					"%d:%s will be download...Add to download task list.\n Save to %s...\n",
					uiIndex + 1, strUrl.c_str(), strPath.c_str());

				pkPackage->ToPath(strPath.c_str());
				pkPackage->setDownloadListener(this);

				m_kDownloadList.push_back(pkPackage);

				beginDownload();
			}
		}
		break;
	default:
		return false;
	}

	return true;
}