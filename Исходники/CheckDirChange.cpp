bool CCheckDirChange::WatchDirChanges(PReadDirChangeInfo pChangeInfo)
{
	pChangeInfo->pFileNotification = (FILE_NOTIFY_INFORMATION*)(new char[pChangeInfo->dwMaxBufferLen]);
	memset(pChangeInfo->pFileNotification,0,pChangeInfo->dwMaxBufferLen);

	return ReadDirectoryChangesW(m_hDirectory,
		pChangeInfo->pFileNotification,
		pChangeInfo->dwMaxBufferLen,
		TRUE,
		FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_DIR_NAME, 
		&pChangeInfo->dwReturnLen,
		&pChangeInfo->overlapped,
		NULL)?true:false;
}