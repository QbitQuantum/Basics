// CMeshExporterDlg message handlers
bool CMeshExporterDlg::get_saved_filename(wchar_t* file_name)
{
	OPENFILENAMEW ofn; 
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = ::GetActiveWindow();
	ofn.lpstrFile = file_name;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"XEvol模型文件(*.xrm)\0*.xrm\0XEvol网格文件(*.mesh)\0*.mesh\0所有文件(*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrDefExt = L"mesh";
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if(GetSaveFileNameW(&ofn) == FALSE)
	{
		return false;
	}
	return true;
}