void CLocalListView::DisplayShares(wxString computer)
{
	SHARE_INFO_1* pShareInfo = 0;

	DWORD read, total;
	DWORD resume_handle = 0;

	if (computer.Last() == '\\')
		computer.RemoveLast();

	int j = m_fileData.size();
	int res = 0;
	do
	{
		const wxWX2WCbuf buf = computer.wc_str(wxConvLocal);
		res = NetShareEnum((wchar_t*)(const wchar_t*)buf, 1, (LPBYTE*)&pShareInfo, MAX_PREFERRED_LENGTH, &read, &total, &resume_handle);

		if (res != ERROR_SUCCESS && res != ERROR_MORE_DATA)
			break;

		SHARE_INFO_1* p = pShareInfo;
		for (unsigned int i = 0; i < read; i++, p++)
		{
			if (p->shi1_type != STYPE_DISKTREE)
				continue;

			t_fileData data;
			data.name = p->shi1_netname;
			data.dir = true;
			data.icon = -2;
			data.size = -1;
			data.hasTime = false;

			m_fileData.push_back(data);
			m_indexMapping.push_back(j++);
		}

		NetApiBufferFree(pShareInfo);
	}
	while (res == ERROR_MORE_DATA);
}