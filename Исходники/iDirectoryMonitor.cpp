void CDirectoryMonitor::WatchDirectoryInternal(ULONG_PTR dwParam)
{
	CDirInfo	*pDirInfo = NULL;

	pDirInfo = reinterpret_cast<CDirInfo *>(dwParam);

	if(pDirInfo->m_hDirectory == INVALID_HANDLE_VALUE)
	{
		free(pDirInfo->m_pData);

		return;
	}

	pDirInfo->m_FileNotifyBuffer = (FILE_NOTIFY_INFORMATION *)malloc(PRIMARY_BUFFER_SIZE);

	pDirInfo->m_bDirMonitored = ReadDirectoryChangesW(pDirInfo->m_hDirectory,
	pDirInfo->m_FileNotifyBuffer,PRIMARY_BUFFER_SIZE,
	pDirInfo->m_bWatchSubTree,pDirInfo->m_WatchFlags,NULL,&pDirInfo->m_Async,
	CompletionRoutine);

	if(!pDirInfo->m_bDirMonitored)
	{
		free(pDirInfo->m_FileNotifyBuffer);
		CancelIo(pDirInfo->m_hDirectory);
		CloseHandle(pDirInfo->m_hDirectory);
	}
}