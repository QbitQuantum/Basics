void CReadChangesRequest::ProcessNotification()
{
	BYTE* pBase = m_BackupBuffer.data();

	for (;;)
	{
		FILE_NOTIFY_INFORMATION& fni = (FILE_NOTIFY_INFORMATION&)*pBase;

		CStringW wstrFilename(fni.FileName, fni.FileNameLength/sizeof(wchar_t));
		// Handle a trailing backslash, such as for a root directory.
		if (wstrFilename.Right(1) != L"\\")
			wstrFilename = m_wstrDirectory + L"\\" + wstrFilename;
		else
			wstrFilename = m_wstrDirectory + wstrFilename;

		// If it could be a short filename, expand it.
		LPCWSTR wszFilename = PathFindFileNameW(wstrFilename);
		int len = lstrlenW(wszFilename);
		// The maximum length of an 8.3 filename is twelve, including the dot.
		if (len <= 12 && wcschr(wszFilename, L'~'))
		{
			// Convert to the long filename form. Unfortunately, this
			// does not work for deletions, so it's an imperfect fix.
			wchar_t wbuf[MAX_PATH];
			if (::GetLongPathNameW(wstrFilename, wbuf, _countof(wbuf)) > 0)
				wstrFilename = wbuf;
		}

		m_pServer->m_pBase->Push(fni.Action, wstrFilename);

		if (!fni.NextEntryOffset)
			break;
		pBase += fni.NextEntryOffset;
	};
}