void CPathWatcher::WorkerThread()
{
	DWORD numBytes;
	CDirWatchInfo * pdi = NULL;
	LPOVERLAPPED lpOverlapped;
	WCHAR buf[MAX_PATH*4] = {0};
	while (m_bRunning)
	{
		if (watchedPaths.GetCount())
		{
			if (!GetQueuedCompletionStatus(m_hCompPort,
											&numBytes,
											(PULONG_PTR) &pdi,
											&lpOverlapped,
											INFINITE))
			{
				// Error retrieving changes
				// Clear the list of watched objects and recreate that list
				if (!m_bRunning)
					return;
				{
					AutoLocker lock(m_critSec);
					ClearInfoMap();
				}
				DWORD lasterr = GetLastError();
				if ((m_hCompPort)&&(lasterr!=ERROR_SUCCESS)&&(lasterr!=ERROR_INVALID_HANDLE))
				{
					m_hCompPort.CloseHandle();
				}
				// Since we pass m_hCompPort to CreateIoCompletionPort, we
				// have to set this to NULL to have that API create a new
				// handle.
				m_hCompPort = NULL;
				for (int i=0; i<watchedPaths.GetCount(); ++i)
				{
					CAutoFile hDir = CreateFile(watchedPaths[i].GetWinPath(),
											FILE_LIST_DIRECTORY,
											FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
											NULL, //security attributes
											OPEN_EXISTING,
											FILE_FLAG_BACKUP_SEMANTICS | //required privileges: SE_BACKUP_NAME and SE_RESTORE_NAME.
											FILE_FLAG_OVERLAPPED,
											NULL);
					if (!hDir)
					{
						// this could happen if a watched folder has been removed/renamed
						m_hCompPort.CloseHandle();
						AutoLocker lock(m_critSec);
						watchedPaths.RemovePath(watchedPaths[i]);
						i--; if (i<0) i=0;
						break;
					}

					CDirWatchInfo * pDirInfo = new CDirWatchInfo(hDir, watchedPaths[i]);
					hDir.Detach();  // the new CDirWatchInfo object owns the handle now
					m_hCompPort = CreateIoCompletionPort(pDirInfo->m_hDir, m_hCompPort, (ULONG_PTR)pDirInfo, 0);
					if (m_hCompPort == NULL)
					{
						AutoLocker lock(m_critSec);
						ClearInfoMap();
						delete pDirInfo;
						pDirInfo = NULL;
						watchedPaths.RemovePath(watchedPaths[i]);
						i--; if (i<0) i=0;
						break;
					}
					if (!ReadDirectoryChangesW(pDirInfo->m_hDir,
												pDirInfo->m_Buffer,
												READ_DIR_CHANGE_BUFFER_SIZE,
												TRUE,
												FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
												&numBytes,// not used
												&pDirInfo->m_Overlapped,
												NULL))	//no completion routine!
					{
						AutoLocker lock(m_critSec);
						ClearInfoMap();
						delete pDirInfo;
						pDirInfo = NULL;
						watchedPaths.RemovePath(watchedPaths[i]);
						i--; if (i<0) i=0;
						break;
					}
					AutoLocker lock(m_critSec);
					watchInfoMap[pDirInfo->m_hDir] = pDirInfo;
					ATLTRACE(_T("watching path %s\n"), pDirInfo->m_DirName.GetWinPath());
				}
			}
			else
			{
				if (!m_bRunning)
					return;
				// NOTE: the longer this code takes to execute until ReadDirectoryChangesW
				// is called again, the higher the chance that we miss some
				// changes in the file system!
				if (pdi)
				{
					if (numBytes == 0)
					{
						goto continuewatching;
					}
					PFILE_NOTIFY_INFORMATION pnotify = (PFILE_NOTIFY_INFORMATION)pdi->m_Buffer;
					if ((ULONG_PTR)pnotify - (ULONG_PTR)pdi->m_Buffer > READ_DIR_CHANGE_BUFFER_SIZE)
						goto continuewatching;
					DWORD nOffset = pnotify->NextEntryOffset;
					do
					{
						nOffset = pnotify->NextEntryOffset;
						SecureZeroMemory(buf, MAX_PATH*4*sizeof(TCHAR));
						_tcsncpy_s(buf, MAX_PATH*4, pdi->m_DirPath, MAX_PATH*4);
						errno_t err = _tcsncat_s(buf+pdi->m_DirPath.GetLength(), (MAX_PATH*4)-pdi->m_DirPath.GetLength(), pnotify->FileName, _TRUNCATE);
						if (err == STRUNCATE)
						{
							pnotify = (PFILE_NOTIFY_INFORMATION)((LPBYTE)pnotify + nOffset);
							continue;
						}
						buf[min(MAX_PATH*4-1, pdi->m_DirPath.GetLength()+(pnotify->FileNameLength/sizeof(WCHAR)))] = 0;
						pnotify = (PFILE_NOTIFY_INFORMATION)((LPBYTE)pnotify + nOffset);
						ATLTRACE(_T("change notification: %s\n"), buf);
						m_changedPaths.AddPath(CTGitPath(buf));
						if ((ULONG_PTR)pnotify - (ULONG_PTR)pdi->m_Buffer > READ_DIR_CHANGE_BUFFER_SIZE)
							break;
					} while (nOffset);
continuewatching:
					SecureZeroMemory(pdi->m_Buffer, sizeof(pdi->m_Buffer));
					SecureZeroMemory(&pdi->m_Overlapped, sizeof(OVERLAPPED));
					if (!ReadDirectoryChangesW(pdi->m_hDir,
												pdi->m_Buffer,
												READ_DIR_CHANGE_BUFFER_SIZE,
												TRUE,
												FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
												&numBytes,// not used
												&pdi->m_Overlapped,
												NULL))	//no completion routine!
					{
						// Since the call to ReadDirectoryChangesW failed, just
						// wait a while. We don't want to have this thread
						// running using 100% CPU if something goes completely
						// wrong.
						Sleep(200);
					}
				}
			}
		}// if (watchedPaths.GetCount())
		else
			Sleep(200);
	}// while (m_bRunning)
}