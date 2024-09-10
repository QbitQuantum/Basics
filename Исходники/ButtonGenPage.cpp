BOOL GetPicture(HWND hwnd, IPictureDisp** ppPicture)
{
	USES_CONVERSION;

	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof OPENFILENAME);			
	ofn.lStructSize = sizeof OPENFILENAME;
	ofn.lpstrFile =  (TCHAR*) _alloca(_MAX_PATH * sizeof TCHAR);
	ofn.nMaxFile = _MAX_PATH;	
	ofn.hwndOwner = hwnd;				
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
	
	memset(ofn.lpstrFile, 0, _MAX_PATH * sizeof TCHAR); 

	ofn.lpstrFilter = _T("所有图片文件\0*.bmp;*.dib;*.gif;*.jpg;*.wmf;*.emf;*.ico;*.cur\0")
		_T("位图 (*.bmp;*.dib)\0*.bmp;*.dib\0")
		_T("GIF 图像 (*.gif)\0*.gif\0")
		_T("JPEG 图像 (*.jpg)\0*.jpg\0")
		_T("元文件 (*.wmf;*.emf)\0*.wmf;*.emf\0")
		_T("Icons (*.ico;*.cur)\0*.ico;*.cur\0")
		_T("所有文件(*.*)\0*.*\0");
	ofn.lpstrTitle = _T("加载图片");
	
	if (GetOpenFileName(&ofn))
	{
		CComBSTR bstr(ofn.lpstrFile);

		if (*ppPicture)
			(*ppPicture)->Release();

		HRESULT hr = OleLoadPicturePath(bstr.m_str, 0, 0, 0, IID_IDispatch, (void**)ppPicture);

		return TRUE;
	}

	return FALSE;
}