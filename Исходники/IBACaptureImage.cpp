bool CIBACaptureImage::CaptureImage(LPCTSTR lpszName)
{
	if (!m_bInitOK || !m_pCap->IsOpened())
	{
		IBA_LOG0(_T("CIBACaptureImage::CaptureImage(采集图片失败-未初始化)"));
		return false;
	}

	g_eCapEvent.ResetEvent();
	m_pCap->GrabOneFrame(TRUE);
	if( WaitForSingleObject( g_eCapEvent, 5 * 1000 ) != WAIT_OBJECT_0 )
	{
		IBA_LOG0(_T("设备超时"));
		return false;
	}


	bool bFlag = false;
	try
	{
		GdiplusStartupInput gdiplusStartupInput; 
		ULONG_PTR gdiplusToken = NULL;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); 

		BMPScale( m_strBmpFilePath2, m_strBmpFilePath1, 320, 240 );

		BMP2JPG( m_strBmpFilePath2, m_strPath + lpszName + _T(".jpg"));

		// 2014-7-7 - qsc
		DeleteFile(m_strBmpFilePath1);
		DeleteFile(m_strBmpFilePath2);

		GdiplusShutdown(gdiplusToken);

		Sleep( 50 );
		bFlag = true;
	}
	catch (...)
	{
		bFlag = false;
		IBA_LOG0(_T("照片转换成jpg出现错误！"));
	}
	return bFlag;
}