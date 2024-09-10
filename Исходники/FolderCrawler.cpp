void CFolderCrawler::WorkerThread()
{
	HANDLE hWaitHandles[2];
	hWaitHandles[0] = m_hTerminationEvent;
	hWaitHandles[1] = m_hWakeEvent;
	CTGitPath workingPath;
	bool bFirstRunAfterWakeup = false;
	DWORD currentTicks = 0;

	for(;;)
	{
		bool bRecursive = !!(DWORD)CRegStdDWORD(_T("Software\\TortoiseGit\\RecursiveOverlay"), TRUE);

		if (SysInfo::Instance().IsVistaOrLater())
		{
			SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END);
		}
		DWORD waitResult = WaitForMultipleObjects(_countof(hWaitHandles), hWaitHandles, FALSE, INFINITE);

		// exit event/working loop if the first event (m_hTerminationEvent)
		// has been signaled or if one of the events has been abandoned
		// (i.e. ~CFolderCrawler() is being executed)
		if(m_bRun == false || waitResult == WAIT_OBJECT_0 || waitResult == WAIT_ABANDONED_0 || waitResult == WAIT_ABANDONED_0+1)
		{
			// Termination event
			break;
		}

		if (SysInfo::Instance().IsVistaOrLater())
		{
			SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);
		}

		// If we get here, we've been woken up by something being added to the queue.
		// However, it's important that we don't do our crawling while
		// the shell is still asking for items
		bFirstRunAfterWakeup = true;
		for(;;)
		{
			if (!m_bRun)
				break;
			// Any locks today?
			if (CGitStatusCache::Instance().m_bClearMemory)
			{
				CGitStatusCache::Instance().WaitToWrite();
				CGitStatusCache::Instance().ClearCache();
				CGitStatusCache::Instance().Done();
				CGitStatusCache::Instance().m_bClearMemory = false;
			}
			if(m_lCrawlInhibitSet > 0)
			{
				// We're in crawl hold-off
				ATLTRACE("Crawl hold-off\n");
				Sleep(50);
				continue;
			}
			if (bFirstRunAfterWakeup)
			{
				Sleep(20);
				ATLTRACE("Crawl bFirstRunAfterWakeup\n");
				bFirstRunAfterWakeup = false;
				continue;
			}
			if ((m_blockReleasesAt < GetTickCount())&&(!m_blockedPath.IsEmpty()))
			{
				ATLTRACE(_T("Crawl stop blocking path %s\n"), m_blockedPath.GetWinPath());
				m_blockedPath.Reset();
			}
			CGitStatusCache::Instance().RemoveTimedoutBlocks();

			if ((m_foldersToUpdate.size() == 0) && (m_pathsToUpdate.size() == 0))
			{
				// Nothing left to do
				break;
			}
			currentTicks = GetTickCount();
			if (m_pathsToUpdate.size())
			{
				{
					AutoLocker lock(m_critSec);

					m_bPathsAddedSinceLastCrawl = false;

					workingPath = m_pathsToUpdate.Pop();
					if ((!m_blockedPath.IsEmpty()) && (m_blockedPath.IsAncestorOf(workingPath)))
					{
						// move the path to the end of the list
						m_pathsToUpdate.Push(workingPath);
						if (m_pathsToUpdate.size() < 3)
							Sleep(50);
						continue;
					}
				}

				// don't crawl paths that are excluded
				if (!CGitStatusCache::Instance().IsPathAllowed(workingPath))
					continue;
				if (!CGitStatusCache::Instance().IsPathGood(workingPath))
					continue;
				// check if the changed path is inside an .git folder
				CString projectroot;
				if ((workingPath.HasAdminDir(&projectroot)&&workingPath.IsDirectory()) || workingPath.IsAdminDir())
				{
					// we don't crawl for paths changed in a tmp folder inside an .git folder.
					// Because we also get notifications for those even if we just ask for the status!
					// And changes there don't affect the file status at all, so it's safe
					// to ignore notifications on those paths.
					if (workingPath.IsAdminDir())
					{
						// TODO: add git specific filters here. is there really any change besides index file in .git
						//       that is relevant for overlays?
						/*CString lowerpath = workingPath.GetWinPathString();
						lowerpath.MakeLower();
						if (lowerpath.Find(_T("\\tmp\\"))>0)
							continue;
						if (lowerpath.Find(_T("\\tmp")) == (lowerpath.GetLength()-4))
							continue;
						if (lowerpath.Find(_T("\\log"))>0)
							continue;*/
						// Here's a little problem:
						// the lock file is also created for fetching the status
						// and not just when committing.
						// If we could find out why the lock file was changed
						// we could decide to crawl the folder again or not.
						// But for now, we have to crawl the parent folder
						// no matter what.

						//if (lowerpath.Find(_T("\\lock"))>0)
						//	continue;
					}
					else if (!workingPath.Exists())
					{
						CGitStatusCache::Instance().WaitToWrite();
						CGitStatusCache::Instance().RemoveCacheForPath(workingPath);
						CGitStatusCache::Instance().Done();
						continue;
					}

					do
					{
						workingPath = workingPath.GetContainingDirectory();
					} while(workingPath.IsAdminDir());

					ATLTRACE(_T("Invalidating and refreshing folder: %s\n"), workingPath.GetWinPath());
					{
						AutoLocker print(critSec);
						_stprintf_s(szCurrentCrawledPath[nCurrentCrawledpathIndex], MAX_CRAWLEDPATHSLEN, _T("Invalidating and refreshing folder: %s"), workingPath.GetWinPath());
						nCurrentCrawledpathIndex++;
						if (nCurrentCrawledpathIndex >= MAX_CRAWLEDPATHS)
							nCurrentCrawledpathIndex = 0;
					}
					InvalidateRect(hWnd, NULL, FALSE);
					CGitStatusCache::Instance().WaitToRead();
					// Invalidate the cache of this folder, to make sure its status is fetched again.
					CCachedDirectory * pCachedDir = CGitStatusCache::Instance().GetDirectoryCacheEntry(workingPath);
					if (pCachedDir)
					{
						git_wc_status_kind status = pCachedDir->GetCurrentFullStatus();
						pCachedDir->Invalidate();
						if (workingPath.Exists())
						{
							pCachedDir->RefreshStatus(bRecursive);
							// if the previous status wasn't normal and now it is, then
							// send a notification too.
							// We do this here because GetCurrentFullStatus() doesn't send
							// notifications for 'normal' status - if it would, we'd get tons
							// of notifications when crawling a working copy not yet in the cache.
							if ((status != git_wc_status_normal)&&(pCachedDir->GetCurrentFullStatus() != status))
							{
								CGitStatusCache::Instance().UpdateShell(workingPath);
								ATLTRACE(_T("shell update in crawler for %s\n"), workingPath.GetWinPath());
							}
						}
						else
						{
							CGitStatusCache::Instance().Done();
							CGitStatusCache::Instance().WaitToWrite();
							CGitStatusCache::Instance().RemoveCacheForPath(workingPath);
						}
					}
					CGitStatusCache::Instance().Done();
					//In case that svn_client_stat() modified a file and we got
					//a notification about that in the directory watcher,
					//remove that here again - this is to prevent an endless loop
					AutoLocker lock(m_critSec);
					m_pathsToUpdate.erase(workingPath);
				}
				else if (workingPath.HasAdminDir())
				{
					if (!workingPath.Exists())
					{
						CGitStatusCache::Instance().WaitToWrite();
						CGitStatusCache::Instance().RemoveCacheForPath(workingPath);
						CGitStatusCache::Instance().Done();
						continue;
					}
					if (!workingPath.Exists())
						continue;
					ATLTRACE(_T("Updating path: %s\n"), workingPath.GetWinPath());
					{
						AutoLocker print(critSec);
						_stprintf_s(szCurrentCrawledPath[nCurrentCrawledpathIndex], MAX_CRAWLEDPATHSLEN, _T("Updating path: %s"), workingPath.GetWinPath());
						nCurrentCrawledpathIndex++;
						if (nCurrentCrawledpathIndex >= MAX_CRAWLEDPATHS)
							nCurrentCrawledpathIndex = 0;
					}
					InvalidateRect(hWnd, NULL, FALSE);
					// HasAdminDir() already checks if the path points to a dir
					DWORD flags = TGITCACHE_FLAGS_FOLDERISKNOWN;
					flags |= (workingPath.IsDirectory() ? TGITCACHE_FLAGS_ISFOLDER : 0);
					flags |= (bRecursive ? TGITCACHE_FLAGS_RECUSIVE_STATUS : 0);
					CGitStatusCache::Instance().WaitToRead();
					// Invalidate the cache of folders manually. The cache of files is invalidated
					// automatically if the status is asked for it and the file times don't match
					// anymore, so we don't need to manually invalidate those.
					if (workingPath.IsDirectory())
					{
						CCachedDirectory * cachedDir = CGitStatusCache::Instance().GetDirectoryCacheEntry(workingPath);
						if (cachedDir)
							cachedDir->Invalidate();
					}
					CStatusCacheEntry ce = CGitStatusCache::Instance().GetStatusForPath(workingPath, flags);
					if (ce.GetEffectiveStatus() > git_wc_status_unversioned)
					{
						CGitStatusCache::Instance().UpdateShell(workingPath);
						ATLTRACE(_T("shell update in folder crawler for %s\n"), workingPath.GetWinPath());
					}
					CGitStatusCache::Instance().Done();
					AutoLocker lock(m_critSec);
					m_pathsToUpdate.erase(workingPath);
				}
				else
				{
					if (!workingPath.Exists())
					{
						CGitStatusCache::Instance().WaitToWrite();
						CGitStatusCache::Instance().RemoveCacheForPath(workingPath);
						CGitStatusCache::Instance().Done();
					}
				}
			}
			else if (m_foldersToUpdate.size())
			{
				{
					AutoLocker lock(m_critSec);
					m_bItemsAddedSinceLastCrawl = false;

					// create a new CTSVNPath object to make sure the cached flags are requested again.
					// without this, a missing file/folder is still treated as missing even if it is available
					// now when crawling.
					workingPath = CTGitPath(m_foldersToUpdate.Pop().GetWinPath());

					if ((!m_blockedPath.IsEmpty())&&(m_blockedPath.IsAncestorOf(workingPath)))
					{
						// move the path to the end of the list
						m_foldersToUpdate.Push(workingPath);
						if (m_foldersToUpdate.size() < 3)
							Sleep(50);
						continue;
					}
				}
				if (DWORD(workingPath.GetCustomData()) >= currentTicks)
				{
					Sleep(50);
					continue;
				}
				if ((!m_blockedPath.IsEmpty())&&(m_blockedPath.IsAncestorOf(workingPath)))
					continue;
				if (!CGitStatusCache::Instance().IsPathAllowed(workingPath))
					continue;
				if (!CGitStatusCache::Instance().IsPathGood(workingPath))
					continue;

				ATLTRACE(_T("Crawling folder: %s\n"), workingPath.GetWinPath());
				{
					AutoLocker print(critSec);
					_stprintf_s(szCurrentCrawledPath[nCurrentCrawledpathIndex], MAX_CRAWLEDPATHSLEN, _T("Crawling folder: %s"), workingPath.GetWinPath());
					nCurrentCrawledpathIndex++;
					if (nCurrentCrawledpathIndex >= MAX_CRAWLEDPATHS)
						nCurrentCrawledpathIndex = 0;
				}
				InvalidateRect(hWnd, NULL, FALSE);
				CGitStatusCache::Instance().WaitToRead();
				// Now, we need to visit this folder, to make sure that we know its 'most important' status
				CCachedDirectory * cachedDir = CGitStatusCache::Instance().GetDirectoryCacheEntry(workingPath.GetDirectory());
				// check if the path is monitored by the watcher. If it isn't, then we have to invalidate the cache
				// for that path and add it to the watcher.
				if (!CGitStatusCache::Instance().IsPathWatched(workingPath))
				{
					if (workingPath.HasAdminDir())
					{
						ATLTRACE(_T("Add watch path %s\n"), workingPath.GetWinPath());
						CGitStatusCache::Instance().AddPathToWatch(workingPath);
					}
					if (cachedDir)
						cachedDir->Invalidate();
					else
					{
						CGitStatusCache::Instance().Done();
						CGitStatusCache::Instance().WaitToWrite();
						CGitStatusCache::Instance().RemoveCacheForPath(workingPath);
					}
				}
				if (cachedDir)
					cachedDir->RefreshStatus(bRecursive);

#if 0
				// While refreshing the status, we could get another crawl request for the same folder.
				// This can happen if the crawled folder has a lower status than one of the child folders
				// (recursively). To avoid double crawlings, remove such a crawl request here
				AutoLocker lock(m_critSec);
				if (m_bItemsAddedSinceLastCrawl)
				{
					m_foldersToUpdate.erase(workingPath);
				}
#endif
				CGitStatusCache::Instance().Done();
			}
		}
	}
	_endthread();
}