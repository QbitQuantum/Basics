bool DownloadFile(CString strFileUrl,CString strSavePath,bool bReplace)
{
	if ( PathFileExists(strSavePath) )
	{
		if ( bReplace )
		{
			return false;
		}
		else
		{
			DeleteFile(strSavePath);
		}
	}

	HRESULT hr = URLDownloadToFileW(NULL,strFileUrl,strSavePath,0,NULL);
	return hr==S_OK;
}