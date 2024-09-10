void CPatchListCtrl::OnDropFiles(HDROP hDropInfo)
{
	UINT nNumFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, nullptr, 0);
	for (UINT i = 0; i < nNumFiles; ++i)
	{
		CString file;
		DragQueryFile(hDropInfo, i, file.GetBufferSetLength(MAX_PATH), MAX_PATH);
		file.ReleaseBuffer();
		if (PathIsDirectory(file))
			continue;

		// no duplicates
		LVFINDINFO lvInfo;
		lvInfo.flags = LVFI_STRING;
		lvInfo.psz = file;
		if (FindItem(&lvInfo, -1) != -1)
			continue;

		int index = InsertItem(GetItemCount(), file);
		if (index >= 0)
			SetCheck(index, true);
	}
	DragFinish(hDropInfo);
	SetColumnWidth(0, LVSCW_AUTOSIZE);
}