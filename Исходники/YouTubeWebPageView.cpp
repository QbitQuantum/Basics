void YouTubeWebPageView::LoadVideo(const VideoInfo& info)
{
   m_bLoaded = false;

   ATLTRACE(_T("%08x: LoadVideo: \"%s\" (%s)\n"),
      m_hWnd,
      info.Name(),
      info.Address());

   m_iLastError = 0;

   CString cszHtml = GetHtmlTemplate();

   cszHtml.Replace(_T("{..$address..}"), info.Address());
   cszHtml.Replace(_T("{..$name..}"), info.Name());
   cszHtml.Replace(_T("\r\n"), _T("\n"));

   // generate temp name
   CString cszTempFolder;
   GetTempPath(MAX_PATH, cszTempFolder.GetBuffer(MAX_PATH));
   cszTempFolder.ReleaseBuffer();

   CString cszFilename;
   GetTempFileName(cszTempFolder, _T("YTP"), 0, cszFilename.GetBuffer(MAX_PATH));
   cszFilename.ReleaseBuffer();

   // write to temporary file
   {
      FILE* fd = NULL;
	  errno_t err = _tfopen_s(&fd, cszFilename, _T("wt"));
	  ATLVERIFY(err == 0 && fd != NULL);

      USES_CONVERSION;
      fprintf(fd, T2CA(cszHtml));
      fclose(fd);
   }

   // navigate to page
   CComPtr<IWebBrowser2> spWebBrowser2;
   HRESULT hr = GetWebBrowser2(spWebBrowser2);
   if (SUCCEEDED(hr))
   {
      CString cszURL = _T("file:///") + cszFilename;
      cszURL.Replace(_T("\\"), _T("/"));

      CComBSTR bstrURL = cszURL;

      CComVariant varFlags(static_cast<int>(navNoHistory | navNoWriteToCache));

      hr = spWebBrowser2->Navigate(bstrURL, &varFlags, NULL, NULL, NULL);
   }

   if (!m_cszHtmlFilename.IsEmpty())
      DeleteFile(m_cszHtmlFilename);
   m_cszHtmlFilename = cszFilename;
}