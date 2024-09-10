void ChangeJournalWatcher::watchDir(const std::wstring &dir)
{
	WCHAR volume_path[MAX_PATH]; 
	BOOL ok = GetVolumePathNameW(dir.c_str(), volume_path, MAX_PATH);
	if(!ok)
	{
		Server->Log("GetVolumePathName(dir, volume_path, MAX_PATH) failed in ChangeJournalWatcher::watchDir", LL_ERROR);
		listener->On_ResetAll(dir);
		has_error=true;
		error_dirs.push_back(dir);
		return;
	}

	std::wstring vol=volume_path;

	if(vol.size()>0)
	{
		if(vol[vol.size()-1]=='\\')
		{
			vol.erase(vol.size()-1,1);
		}
	}

	std::map<std::wstring, SChangeJournal>::iterator it=wdirs.find(vol);
	if(it!=wdirs.end())
	{
		it->second.path.push_back(dir);
		return;
	}

	bool do_index=false;

	_i64 rid=hasRoot(vol);
	if(rid==-1)
	{
		listener->On_ResetAll(vol);
		do_index=true;
		rid=addRoot(vol);
		setIndexDone(vol, 0);
	}

	HANDLE hVolume=CreateFileW((L"\\\\.\\"+vol).c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hVolume==INVALID_HANDLE_VALUE)
	{
		Server->Log(L"CreateFile of volume '"+vol+L"' failed. - watchDir", LL_ERROR);
		listener->On_ResetAll(vol);
		error_dirs.push_back(vol);
		CloseHandle(hVolume);
		has_error=true;
		return;
	}
	
	USN_JOURNAL_DATA data;
	DWORD r_bytes;
	BOOL b=DeviceIoControl(hVolume, FSCTL_QUERY_USN_JOURNAL, NULL, 0, &data, sizeof(USN_JOURNAL_DATA), &r_bytes, NULL);
	if(b==0)
	{
		DWORD err=GetLastError();
		if(err==ERROR_INVALID_FUNCTION)
		{
			Server->Log(L"Change Journals not supported for Volume '"+vol+L"'", LL_ERROR);
			listener->On_ResetAll(vol);
			error_dirs.push_back(vol);
			CloseHandle(hVolume);
			has_error=true;
			return;
		}
		else if(err==ERROR_JOURNAL_DELETE_IN_PROGRESS)
		{
			Server->Log(L"Change Journals for Volume '"+vol+L"' is being deleted", LL_ERROR);
			listener->On_ResetAll(vol);
			error_dirs.push_back(vol);
			CloseHandle(hVolume);
			has_error=true;
			return;
		}
		else if(err==ERROR_JOURNAL_NOT_ACTIVE)
		{
			CREATE_USN_JOURNAL_DATA dat;
			dat.AllocationDelta=10485760; //10 MB
			dat.MaximumSize=73400320; // 70 MB
			DWORD bret;
			BOOL r=DeviceIoControl(hVolume, FSCTL_CREATE_USN_JOURNAL, &dat, sizeof(CREATE_USN_JOURNAL_DATA), NULL, 0, &bret, NULL);
			if(r==0)
			{
				Server->Log(L"Error creating change journal for Volume '"+vol+L"'", LL_ERROR);
				listener->On_ResetAll(vol);
				error_dirs.push_back(vol);
				CloseHandle(hVolume);
				has_error=true;
				return;
			}
			b=DeviceIoControl(hVolume, FSCTL_QUERY_USN_JOURNAL, NULL, 0, &data, sizeof(USN_JOURNAL_DATA), &r_bytes, NULL);
			if(b==0)
			{
				Server->Log(L"Unknown error for Volume '"+vol+L"' after creation - watchDir", LL_ERROR);
				listener->On_ResetAll(vol);
				error_dirs.push_back(vol);
				CloseHandle(hVolume);
				has_error=true;
				return;
			}
		}
		else
		{
			Server->Log(L"Unknown error for Volume '"+vol+L"' - watchDir ec: "+convert((int)err), LL_ERROR);
			listener->On_ResetAll(vol);
			error_dirs.push_back(vol);
			CloseHandle(hVolume);
			has_error=true;
			return;
		}
	}

	SDeviceInfo info=getDeviceInfo(vol);

	if(info.has_info)
	{
		if(info.journal_id!=data.UsnJournalID)
		{
			Server->Log(L"Journal id for '"+vol+L"' wrong - reindexing", LL_WARNING);
			listener->On_ResetAll(vol);
			do_index=true;
			setIndexDone(vol, 0);
			info.last_record=data.NextUsn;

			q_update_journal_id->Bind((_i64)data.UsnJournalID);
			q_update_journal_id->Bind(vol);
			q_update_journal_id->Write();
			q_update_journal_id->Reset();
		}

		bool needs_reindex=false;

		if( do_index==false && (info.last_record<data.FirstUsn || info.last_record>data.NextUsn) )
		{
			Server->Log(L"Last record not readable at '"+vol+L"' - reindexing", LL_WARNING);
			needs_reindex=true;
		}

		if( do_index==false && data.NextUsn-info.last_record>usn_reindex_num )
		{
			Server->Log(L"There are "+convert(data.NextUsn-info.last_record)+L" new USN entries at '"+vol+L"' - reindexing", LL_WARNING);
			needs_reindex=true;
		}

		if(needs_reindex)
		{
			
			listener->On_ResetAll(vol);
			do_index=true;
			setIndexDone(vol, 0);
			info.last_record=data.NextUsn;
		}

		if(do_index==false && info.index_done==0)
		{
			Server->Log(L"Indexing was not finished at '"+vol+L"' - reindexing", LL_WARNING);
			do_index=true;
			setIndexDone(vol, 0);
			info.last_record=data.NextUsn;
		}
	}
	else
	{
		listener->On_ResetAll(vol);
		Server->Log(L"Info not found at '"+vol+L"' - reindexing", LL_WARNING);
		do_index=true;
	}

	SChangeJournal cj;
	cj.journal_id=data.UsnJournalID;
	if(!info.has_info)
		cj.last_record=data.NextUsn;
	else
		cj.last_record=info.last_record;

	cj.path.push_back(dir);
	cj.hVolume=hVolume;
	cj.rid=rid;
	cj.last_record_update=false;
	cj.vol_str=vol;

	if(!info.has_info)
	{
		q_add_journal->Bind((_i64)data.UsnJournalID);
		q_add_journal->Bind(vol);
		q_add_journal->Bind(cj.last_record);
		q_add_journal->Write();
		q_add_journal->Reset();

		setIndexDone(vol, 0);
	}

	wdirs.insert(std::pair<std::wstring, SChangeJournal>(vol, cj) );

	if(do_index)
	{
		reindex(rid, vol, &cj);
		Server->Log(L"Reindexing of '"+vol+L"' done.", LL_INFO);
	}
}