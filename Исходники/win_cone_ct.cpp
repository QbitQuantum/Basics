BOOL MainWindow::SetDimText()
{
	WCHAR szText[64];
	WCHAR szText2[32];
	INT nxy, nz;
	FLOAT res, size_xy, size_z;
	SendMessage(m_hDimensions[0],WM_GETTEXT,64,(LPARAM)szText);
	nxy = _wtoi(szText);
	SendMessage(m_hDimensions[1],WM_GETTEXT,64,(LPARAM)szText);
	nz = _wtoi(szText);
	SendMessage(m_hDimensions[2],WM_GETTEXT,64,(LPARAM)szText);
	res = _wtof(szText);

	size_xy = nxy * res;
	size_z = nz * res;
	if(size_xy>1000)
	{
		size_xy /= 1000.0;
		StringCchPrintf(szText,64,L"Reconstruction volume:\n%1.3f m \u00D7 %1.3f m ", size_xy, size_xy);
	}
	else
		StringCchPrintf(szText,64,L"Reconstruction volume:\n%3.1f mm \u00D7 %3.1f mm ", size_xy, size_xy);
	if(size_z>1000)
	{
		size_z /= 1000.0;
		StringCchPrintf(szText2,32,L"\u00D7 %1.3f m", size_z);
	}
	else
		StringCchPrintf(szText2,32,L"\u00D7 %3.1f mm", size_z);
	StringCchCat(szText,sizeof(szText),szText2);
	SendMessage(m_hReconText[5],WM_SETTEXT,NULL,(LPARAM)szText);

	return TRUE;
}