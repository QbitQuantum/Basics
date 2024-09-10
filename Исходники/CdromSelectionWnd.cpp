void CCdromSelectionWnd::SelectImage()
{
	Framework::Win32::CFileDialog Dialog;

	Dialog.m_OFN.lpstrFilter = DISKIMAGE_FILTER;

	if(Dialog.SummonOpen(m_hWnd) != IDOK)
	{
		return;
	}

	std::string sPath(string_cast<std::string>(Dialog.GetPath()));
	m_sImagePath = sPath.c_str();
}