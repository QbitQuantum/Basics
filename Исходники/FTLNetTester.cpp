void CFTLNetTester::test_DownloadMethods()
{
    BOOL bRet = FALSE;
    HRESULT hr = E_FAIL;
    CFElapseCounter counter;

    LPCTSTR STR_DOWNLOAD_FILE_URL = TEXT("http://vaccine.dn.naver.com/naver/vaccine/NaverSecurity64/toolbar/NaverTBVaccine64.exe");

    TCHAR szLocalPath[MAX_PATH] = {0};
    API_VERIFY( 0 < GetModuleFileName(NULL, szLocalPath, _countof(szLocalPath)));
    CPath   path(szLocalPath);
    API_VERIFY(path.RemoveFileSpec());
    CAtlString strLocalFolderPath = path;

    API_VERIFY(path.Append(TEXT("UrlDownloadFile_NaverTBVaccine64.exe")));

    API_VERIFY(DeleteUrlCacheEntry(STR_DOWNLOAD_FILE_URL));     //如果不调用该函数, 已经下载过的话,不会重新下载

    API_VERIFY(counter.Start());
    COM_VERIFY(URLDownloadToFile(NULL, STR_DOWNLOAD_FILE_URL, path, 0, NULL));
    API_VERIFY(counter.Stop());
    FTLTRACE(TEXT("URLDownloadToFile Elapse %d(ms)\n"), counter.GetElapseTime() / NANOSECOND_PER_MILLISECOND);
}