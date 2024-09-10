bool CKnownFileList::SafeAddKFile(CKnownFile* toadd)
{
	bool bRemovedDuplicateSharedFile = false;
	CCKey key(toadd->GetFileHash());
	CKnownFile* pFileInMap;
	if (m_Files_map.Lookup(key, pFileInMap))
	{
		TRACE(_T("%hs: Already in known list:   %s %I64u \"%s\"\n"), __FUNCTION__, md4str(pFileInMap->GetFileHash()), pFileInMap->GetFileSize(), pFileInMap->GetFileName());
		TRACE(_T("%hs: Old entry replaced with: %s %I64u \"%s\"\n"), __FUNCTION__, md4str(toadd->GetFileHash()), toadd->GetFileSize(), toadd->GetFileName());

		// if we hash files which are already in known file list and add them later (when the hashing thread is finished),
		// we can not delete any already available entry from known files list. that entry can already be used by the
		// shared file list -> crash.

		m_Files_map.RemoveKey(CCKey(pFileInMap->GetFileHash()));
		m_mapKnownFilesByAICH.RemoveKey(pFileInMap->GetAICHHashset()->GetMasterHash());
		//This can happen in a couple situations..
		//File was renamed outside of eMule.. 
		//A user decided to redownload a file he has downloaded and unshared..
		//RemovingKeyWords I believe is not thread safe if I'm looking at this right.
		//Not sure of a good solution yet..
		if (theApp.sharedfiles)
		{
#if 0
			// This may crash the client because of dangling ptr in shared files ctrl.
			// This may happen if a file is re-shared which is also currently downloaded.
			// After the file was downloaded (again) there is a dangl. ptr in shared files 
			// ctrl.
			// Actually that's also wrong in some cases: Keywords are not always removed
			// because the wrong ptr is used to search for in keyword publish list.
			theApp.sharedfiles->RemoveKeywords(pFileInMap);
#else
			// This solves the problem with dangl. ptr in shared files ctrl,
			// but creates a new bug. It may lead to unshared files! Even 
			// worse it may lead to files which are 'shared' in GUI but 
			// which are though not shared 'logically'.
			//
			// To reduce the harm, remove the file from shared files list, 
			// only if really needed. Right now this 'harm' applies for files
			// which are re-shared and then completed (again) because they were
			// also in download queue (they were added there when the already
			// available file was not in shared file list).
			if (theApp.sharedfiles->IsFilePtrInList(pFileInMap))
				bRemovedDuplicateSharedFile = theApp.sharedfiles->RemoveFile(pFileInMap);
#endif
			ASSERT( !theApp.sharedfiles->IsFilePtrInList(pFileInMap) );
		}
		//Double check to make sure this is the same file as it's possible that a two files have the same hash.
		//Maybe in the furture we can change the client to not just use Hash as a key throughout the entire client..
		ASSERT( toadd->GetFileSize() == pFileInMap->GetFileSize() );
		ASSERT( toadd != pFileInMap );
		if (toadd->GetFileSize() == pFileInMap->GetFileSize())
			toadd->statistic.MergeFileStats(&pFileInMap->statistic);

		ASSERT( theApp.sharedfiles==NULL || !theApp.sharedfiles->IsFilePtrInList(pFileInMap) );
		ASSERT( theApp.downloadqueue==NULL || !theApp.downloadqueue->IsPartFile(pFileInMap) );

		// Quick fix: If we downloaded already downloaded files again and if those files all had the same file names
		// and were renamed during file completion, we have a pending ptr in transfer window.
		if (theApp.emuledlg && theApp.emuledlg->transferwnd && theApp.emuledlg->transferwnd->downloadlistctrl.m_hWnd)
			theApp.emuledlg->transferwnd->downloadlistctrl.RemoveFile((CPartFile*)pFileInMap);

		delete pFileInMap;
	}
	m_Files_map.SetAt(key, toadd);
	if (bRemovedDuplicateSharedFile) {
		theApp.sharedfiles->SafeAddKFile(toadd);
	}
	if (toadd->GetAICHHashset()->HasValidMasterHash())
		m_mapKnownFilesByAICH.SetAt(toadd->GetAICHHashset()->GetMasterHash(), toadd);
	return true;
}