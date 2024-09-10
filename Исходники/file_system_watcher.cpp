	static void CALLBACK callback(DWORD errorCode,
								  DWORD tferred,
								  LPOVERLAPPED over)
	{
		if (errorCode > 0)
		{
			return;
		}
		FileSystemWatcherPC* watcher = (FileSystemWatcherPC*)over->hEvent;
		if (tferred > 0)
		{
			FILE_NOTIFY_INFORMATION* info = &watcher->m_info[0];
			while (info)
			{
				switch (info->Action)
				{
					case FILE_ACTION_RENAMED_NEW_NAME:
					case FILE_ACTION_ADDED:
					case FILE_ACTION_MODIFIED:
					{
						char tmp[MAX_PATH];
						wcharToCharArray(
							info->FileName, tmp, info->FileNameLength);
						watcher->m_callback.invoke(tmp);
						//								watcher->m_asset_browser->emitFileChanged(tmp);
					}
					break;
					case FILE_ACTION_RENAMED_OLD_NAME:
					case FILE_ACTION_REMOVED:
						// do not do anything
						break;
					default:
						ASSERT(false);
						break;
				}
				info = info->NextEntryOffset == 0
						   ? nullptr
						   : (FILE_NOTIFY_INFORMATION*)(((char*)info) +
														info->NextEntryOffset);
			}
		}
		BOOL b = ReadDirectoryChangesW(watcher->m_handle,
									   watcher->m_info,
									   sizeof(watcher->m_info),
									   TRUE,
									   READ_DIR_CHANGE_FILTER,
									   &watcher->m_received,
									   &watcher->m_overlapped,
									   callback);
		ASSERT(b);
	}