int CAICHSyncThread::Run()
{
	//MORPH START SLUGFILLER: SafeHash
	CReadWriteLock lock(&theApp.m_threadlock);
	if (!lock.ReadLock(0))
		return 0;
	// MORPH END SLUGFILLER: SafeHash
	if ( !theApp.emuledlg->IsRunning() )
		return 0;
	// we need to keep a lock on this file while the thread is running
	CSingleLock lockKnown2Met(&CAICHRecoveryHashSet::m_mutKnown2File);
	lockKnown2Met.Lock();
	
	CSafeFile file;
	bool bJustCreated = ConvertToKnown2ToKnown264(&file);
	
	// we collect all masterhashs which we find in the known2.met and store them in a list
	CList<CAICHHash> liKnown2Hashs;
	CString fullpath = thePrefs.GetMuleDirectory(EMULE_CONFIGDIR);
	fullpath.Append(KNOWN2_MET_FILENAME);
	
	CFileException fexp;
	uint32 nLastVerifiedPos = 0;

	if (!bJustCreated && !file.Open(fullpath,CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate|CFile::osSequentialScan|CFile::typeBinary|CFile::shareDenyNone, &fexp)){
		if (fexp.m_cause != CFileException::fileNotFound){
			CString strError(_T("Failed to load ") KNOWN2_MET_FILENAME _T(" file"));
			TCHAR szError[MAX_CFEXP_ERRORMSG];
			if (fexp.GetErrorMessage(szError, ARRSIZE(szError))){
				strError += _T(" - ");
				strError += szError;
			}
			LogError(LOG_STATUSBAR, _T("%s"), strError);
		}
		return false;
	}
	try {
		if (file.GetLength() >= 1){
			uint8 header = file.ReadUInt8();
			if (header != KNOWN2_MET_VERSION){
				AfxThrowFileException(CFileException::endOfFile, 0, file.GetFileName());
			}
			//setvbuf(file.m_pStream, NULL, _IOFBF, 16384);
			uint32 nExistingSize = (UINT)file.GetLength();
			uint32 nHashCount;
			while (file.GetPosition() < nExistingSize){
				liKnown2Hashs.AddTail(CAICHHash(&file));
				nHashCount = file.ReadUInt32();
				if (file.GetPosition() + nHashCount*CAICHHash::GetHashSize() > nExistingSize){
					AfxThrowFileException(CFileException::endOfFile, 0, file.GetFileName());
				}
				// skip the rest of this hashset
				file.Seek(nHashCount*CAICHHash::GetHashSize(), CFile::current);
				nLastVerifiedPos = (UINT)file.GetPosition();
			}
		}
		else
			file.WriteUInt8(KNOWN2_MET_VERSION);
	}
	catch(CFileException* error){
		if (error->m_cause == CFileException::endOfFile){
			LogError(LOG_STATUSBAR,GetResString(IDS_ERR_MET_BAD), KNOWN2_MET_FILENAME);
			// truncate the file to the size to the last verified valid pos
			try{
				file.SetLength(nLastVerifiedPos);
				if (file.GetLength() == 0){
					file.SeekToBegin();
					file.WriteUInt8(KNOWN2_MET_VERSION);
				}
			}
			catch(CFileException* error2){
				error2->Delete();
			}
		}
		else{
			TCHAR buffer[MAX_CFEXP_ERRORMSG];
			error->GetErrorMessage(buffer, ARRSIZE(buffer));
			LogError(LOG_STATUSBAR,GetResString(IDS_ERR_SERVERMET_UNKNOWN),buffer);
		}
		error->Delete();
		return false;
	}
	
	// now we check that all files which are in the sharedfilelist have a corresponding hash in out list
	// those who don'T are added to the hashinglist
	CList<CAICHHash> liUsedHashs;	
	CSingleLock sharelock(&theApp.sharedfiles->m_mutWriteList);
	sharelock.Lock();

	bool bDbgMsgCreatingPartHashs = true;
	for (int i = 0; i < theApp.sharedfiles->GetCount(); i++){
		CKnownFile* pCurFile = theApp.sharedfiles->GetFileByIndex(i);
		if (pCurFile != NULL && !pCurFile->IsPartFile() )
		{
			if (theApp.emuledlg==NULL || !theApp.emuledlg->IsRunning()) // in case of shutdown while still hashing
				return 0;
			if (pCurFile->GetFileIdentifier().HasAICHHash()){
				bool bFound = false;
				for (POSITION pos = liKnown2Hashs.GetHeadPosition();pos != 0;)
				{
					CAICHHash current_hash = liKnown2Hashs.GetNext(pos);
					if (current_hash == pCurFile->GetFileIdentifier().GetAICHHash()){
						bFound = true;
						liUsedHashs.AddTail(current_hash);
						pCurFile->SetAICHRecoverHashSetAvailable(true);
						// Has the file the proper AICH Parthashset? If not probably upgrading, create it
						if (!pCurFile->GetFileIdentifier().HasExpectedAICHHashCount())
						{
							if (bDbgMsgCreatingPartHashs)
							{
								bDbgMsgCreatingPartHashs = false;
								DebugLogWarning(_T("Missing AICH Part Hashsets for known files - maybe upgrading from earlier version. Creating them out of full AICH Recovery Hashsets, shouldn't take too long"));
							}
							CAICHRecoveryHashSet tempHashSet(pCurFile, pCurFile->GetFileSize());
							tempHashSet.SetMasterHash(pCurFile->GetFileIdentifier().GetAICHHash(), AICH_HASHSETCOMPLETE);
							if (!tempHashSet.LoadHashSet())
							{
								ASSERT( false );
								DebugLogError(_T("Failed to load full AICH Recovery Hashset - known2.met might be corrupt. Unable to create AICH Part Hashset - %s"), pCurFile->GetFileName());
							}
							else
							{
								if (!pCurFile->GetFileIdentifier().SetAICHHashSet(tempHashSet))
								{
									DebugLogError(_T("Failed to create AICH Part Hashset out of full AICH Recovery Hashset - %s"), pCurFile->GetFileName());
									ASSERT( false );
								}
								ASSERT(pCurFile->GetFileIdentifier().HasExpectedAICHHashCount());
							}
						}
						//theApp.QueueDebugLogLine(false, _T("%s - %s"), current_hash.GetString(), pCurFile->GetFileName());
						/*#ifdef _DEBUG
						// in debugmode we load and verify all hashsets
						CAICHRecoveryHashSet* pTempHashSet = new CAICHRecoveryHashSet(pCurFile);
						pTempHashSet->SetFileSize(pCurFile->GetFileSize());
						pTempHashSet->SetMasterHash(pCurFile->GetFileIdentifier().GetAICHHash(), AICH_HASHSETCOMPLETE)
						ASSERT( pTempHashSet->LoadHashSet() );
						delete pTempHashSet;
#endif*/
						break;
					}
				}
				if (bFound) // hashset is available, everything fine with this file
					continue;
			}
			pCurFile->SetAICHRecoverHashSetAvailable(false);
			m_liToHash.AddTail(pCurFile);
		}
	}
	sharelock.Unlock();

	// removed all unused AICH hashsets from known2.met
	if (liUsedHashs.GetCount() != liKnown2Hashs.GetCount() && 
		// EastShare START - Added by TAHO, .met file control
		/*
		(!thePrefs.IsRememberingDownloadedFiles() || thePrefs.DoPartiallyPurgeOldKnownFiles()))
		*/
			(!thePrefs.IsRememberingDownloadedFiles() ||
			  thePrefs.DoPartiallyPurgeOldKnownFiles() || 
			  thePrefs.DoCompletlyPurgeOldKnownFiles() ||
			  thePrefs.DoRemoveAichImmediatly()
			)
		)
		// EastShare END   - Added by TAHO, .met file control
	{
		file.SeekToBegin();
		try {
			uint8 header = file.ReadUInt8();
			if (header != KNOWN2_MET_VERSION){
				AfxThrowFileException(CFileException::endOfFile, 0, file.GetFileName());
			}

			uint32 nExistingSize = (UINT)file.GetLength();
			uint32 nHashCount;
			ULONGLONG posWritePos = file.GetPosition();
			ULONGLONG posReadPos = file.GetPosition();
			uint32 nPurgeCount = 0;
			uint32 nPurgeBecauseOld = 0;
			while (file.GetPosition() < nExistingSize){
				CAICHHash aichHash(&file);
				nHashCount = file.ReadUInt32();
				if (file.GetPosition() + nHashCount*CAICHHash::GetHashSize() > nExistingSize){
					AfxThrowFileException(CFileException::endOfFile, 0, file.GetFileName());
				}
				if (!thePrefs.IsRememberingDownloadedFiles() && liUsedHashs.Find(aichHash) == NULL)
				{
					// unused hashset skip the rest of this hashset
					file.Seek(nHashCount*CAICHHash::GetHashSize(), CFile::current);
					nPurgeCount++;
				}
				else if (thePrefs.IsRememberingDownloadedFiles() && theApp.knownfiles->ShouldPurgeAICHHashset(aichHash))
				{
					// EastShare START - Added by TAHO, .met file control
					/*
					ASSERT( thePrefs.DoPartiallyPurgeOldKnownFiles() );
					*/
					ASSERT( thePrefs.DoPartiallyPurgeOldKnownFiles() || thePrefs.DoRemoveAichImmediatly());
					// EastShare END   - Added by TAHO, .met file control
					// also unused (purged) hashset skip the rest of this hashset
					file.Seek(nHashCount*CAICHHash::GetHashSize(), CFile::current);
					nPurgeCount++;
					nPurgeBecauseOld++;
				}
				else if(nPurgeCount == 0){
					// used Hashset, but it does not need to be moved as nothing changed yet
					file.Seek(nHashCount*CAICHHash::GetHashSize(), CFile::current);
					posWritePos = file.GetPosition();
					CAICHRecoveryHashSet::AddStoredAICHHash(aichHash);
				}
				else{
					// used Hashset, move position in file
					BYTE* buffer = new BYTE[nHashCount*CAICHHash::GetHashSize()];
					file.Read(buffer, nHashCount*CAICHHash::GetHashSize());
					posReadPos = file.GetPosition();
					file.Seek(posWritePos, CFile::begin);
					file.Write(aichHash.GetRawHash(), CAICHHash::GetHashSize());
					file.WriteUInt32(nHashCount);
					file.Write(buffer, nHashCount*CAICHHash::GetHashSize());
					delete[] buffer;
					posWritePos = file.GetPosition();
					file.Seek(posReadPos, CFile::begin);
					CAICHRecoveryHashSet::AddStoredAICHHash(aichHash);
				}
			}
			posReadPos = file.GetPosition();
			file.SetLength(posWritePos);
			theApp.QueueDebugLogLine(false, _T("Cleaned up known2.met, removed %u hashsets and purged %u hashsets of old known files (%s)")
				, nPurgeCount - nPurgeBecauseOld, nPurgeBecauseOld, CastItoXBytes(posReadPos-posWritePos)); 

			file.Flush();
			file.Close();
		}
		catch(CFileException* error){
			if (error->m_cause == CFileException::endOfFile){
				// we just parsed this files some ms ago, should never happen here
				ASSERT( false );
			}
			else{
				TCHAR buffer[MAX_CFEXP_ERRORMSG];
				error->GetErrorMessage(buffer, ARRSIZE(buffer));
				LogError(LOG_STATUSBAR,GetResString(IDS_ERR_SERVERMET_UNKNOWN),buffer);
			}
			error->Delete();
			return false;
		}
	}
	else
	{
		// remember (/index) all hashs which are stored in the file for faster checking lateron
		for (POSITION pos = liKnown2Hashs.GetHeadPosition();pos != 0;)
		{
			CAICHRecoveryHashSet::AddStoredAICHHash(liKnown2Hashs.GetNext(pos));
		}
	}
	lockKnown2Met.Unlock();
	// warn the user if he just upgraded
	if (thePrefs.IsFirstStart() && !m_liToHash.IsEmpty() && !bJustCreated){
		LogWarning(GetResString(IDS_AICH_WARNUSER));
	}	
	if (!m_liToHash.IsEmpty()){
		theApp.QueueLogLine(true, GetResString(IDS_AICH_SYNCTOTAL), m_liToHash.GetCount() );
		theApp.emuledlg->sharedfileswnd->sharedfilesctrl.SetAICHHashing(m_liToHash.GetCount());
		// let first all normal hashing be done before starting out synchashing
		CSingleLock sLock1(&theApp.hashing_mut); // only one filehash at a time
		while (theApp.sharedfiles->GetHashingCount() != 0){
			Sleep(100);
			if (!CemuleDlg::IsRunning())
				return 0;
		}
		sLock1.Lock();
		uint32 cDone = 0;
		for (POSITION pos = m_liToHash.GetHeadPosition();pos != 0; cDone++)
		{
			if (!CemuleDlg::IsRunning()){ // in case of shutdown while still hashing
				return 0;
			}
			theApp.emuledlg->sharedfileswnd->sharedfilesctrl.SetAICHHashing(m_liToHash.GetCount()-cDone);
			if (theApp.emuledlg->sharedfileswnd->sharedfilesctrl.m_hWnd != NULL)
				theApp.emuledlg->sharedfileswnd->sharedfilesctrl.ShowFilesCount();
			CKnownFile* pCurFile = m_liToHash.GetNext(pos);
			// just to be sure that the file hasnt been deleted lately
			if (!(theApp.knownfiles->IsKnownFile(pCurFile) && theApp.sharedfiles->GetFileByID(pCurFile->GetFileHash())) )
				continue;
			theApp.QueueLogLine(false, GetResString(IDS_AICH_CALCFILE), pCurFile->GetFileName());
			if(!pCurFile->CreateAICHHashSetOnly())
				theApp.QueueDebugLogLine(false, _T("Failed to create AICH Hashset while sync. for file %s"), pCurFile->GetFileName());
		}

		theApp.emuledlg->sharedfileswnd->sharedfilesctrl.SetAICHHashing(0);
		if (theApp.emuledlg->sharedfileswnd->sharedfilesctrl.m_hWnd != NULL)
			theApp.emuledlg->sharedfileswnd->sharedfilesctrl.ShowFilesCount();
		sLock1.Unlock();
	}

	theApp.QueueDebugLogLine(false, _T("AICHSyncThread finished"));
	return 0;
}