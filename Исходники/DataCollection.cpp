/// <summary>
/// Get the name of the file where screenshot will be stored.
/// </summary>
/// <param name="screenshotName">
/// [out] String buffer that will receive screenshot file name.
/// </param>
/// <param name="screenshotNameSize">
/// [in] Number of characters in screenshotName string buffer.
/// </param>
/// <returns>
/// S_OK on success, otherwise failure code.
/// </returns>
HRESULT GetScreenshotFileName(wchar_t *screenshotName, UINT screenshotNameSize,int shotType)
{
   wchar_t *knownPath = NULL;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &knownPath);
	
      knownPath=L"..\\output";
    if (SUCCEEDED(hr))
    {
        // Get the time
        wchar_t timeString[MAX_PATH];
        GetTimeFormatEx(NULL,TIME_FORCE24HOURFORMAT, NULL, L"hh'-'mm'-'ss", timeString, _countof(timeString));

		// File name will be KinectColorShot-HH-MM-SS(shotType==0)
		//                or KinectDepthShot-HH-MM-SS(shotType==1)
        if(shotType==0)
        StringCchPrintfW(screenshotName, screenshotNameSize, L"%s\\KinectColorShot-%s.bmp", knownPath, timeString);
		else if(shotType==1)
        StringCchPrintfW(screenshotName, screenshotNameSize, L"%s\\KinectDepthShot-%s.bmp", knownPath, timeString);
    }

   // CoTaskMemFree(knownPath);
    return hr;
}