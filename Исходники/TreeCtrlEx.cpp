INT CTreeCtrlEx::AddIcon(HICON hIcon)
{
	ASSERT(hIcon);
	if(m_hImageList == 0)
	{
		m_hImageList = ImageList_Create(16, 16, ILC_COLOR16, 10, 256);
		ImageList_SetBkColor(m_hImageList, GetSysColor(COLOR_WINDOW));
		PostMessage(TVM_SETIMAGELIST, 0, (LPARAM)m_hImageList);
	}

	return ImageList_AddIcon(m_hImageList, hIcon);
}