void CShellUpdater::WorkerThread()
{
	HANDLE hWaitHandles[2];
	hWaitHandles[0] = m_hTerminationEvent;
	hWaitHandles[1] = m_hWakeEvent;

	for(;;)
	{
		DWORD waitResult = WaitForMultipleObjects(_countof(hWaitHandles), hWaitHandles, FALSE, INFINITE);

		// exit event/working loop if the first event (m_hTerminationEvent)
		// has been signaled or if one of the events has been abandoned
		// (i.e. ~CShellUpdater() is being executed)
		if(waitResult == WAIT_OBJECT_0 || waitResult == WAIT_ABANDONED_0 || waitResult == WAIT_ABANDONED_0+1)
		{
			// Termination event
			break;
		}
		// wait some time before we notify the shell
		Sleep(50);
		for(;;)
		{
			CTGitPath workingPath;
			if (!m_bRunning)
				return;
			Sleep(0);
			{
				AutoLocker lock(m_critSec);
				if(m_pathsToUpdate.empty())
				{
					// Nothing left to do
					break;
				}

				if(m_bItemsAddedSinceLastUpdate)
				{
					m_pathsToUpdate.erase(std::unique(m_pathsToUpdate.begin(), m_pathsToUpdate.end(), &CTGitPath::PredLeftEquivalentToRight), m_pathsToUpdate.end());
					m_bItemsAddedSinceLastUpdate = false;
				}

				workingPath = m_pathsToUpdate.front();
				m_pathsToUpdate.pop_front();
			}
			if (workingPath.IsEmpty())
				continue;
			ATLTRACE(_T("Update notifications for: %s\n"), workingPath.GetWinPath());
			if (workingPath.IsDirectory())
			{
				// check if the path is monitored by the watcher. If it isn't, then we have to invalidate the cache
				// for that path and add it to the watcher.
				if (!CGitStatusCache::Instance().IsPathWatched(workingPath))
				{
					if (workingPath.HasAdminDir())
						CGitStatusCache::Instance().AddPathToWatch(workingPath);
				}
				// first send a notification about a sub folder change, so explorer doesn't discard
				// the folder notification. Since we only know for sure that the subversion admin
				// dir is present, we send a notification for that folder.
				CString admindir = workingPath.GetWinPathString() + _T("\\") + g_GitAdminDir.GetAdminDirName();
				if(::PathFileExists(admindir))
					SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH | SHCNF_FLUSHNOWAIT, (LPCTSTR)admindir, NULL);

				SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH | SHCNF_FLUSHNOWAIT, workingPath.GetWinPath(), NULL);
				// Sending an UPDATEDIR notification somehow overwrites/deletes the UPDATEITEM message. And without
				// that message, the folder overlays in the current view don't get updated without hitting F5.
				// Drawback is, without UPDATEDIR, the left tree view isn't always updated...

				SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH | SHCNF_FLUSHNOWAIT, workingPath.GetWinPath(), NULL);
			}
			else
				SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH | SHCNF_FLUSHNOWAIT, workingPath.GetWinPath(), NULL);
		}
	}
	_endthread();
}