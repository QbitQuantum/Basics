void cgGdiplusRender::Display()
{
	SIZE size={m_nWidth, m_nHeight};
	POINT pt={0, 0};

	//更新窗口
	if (!UpdateLayeredWindow( m_hWnd, NULL, NULL,
		&size, (HDC)m_pkBkSurface->GetContent(), &pt, 0, &m_kBlend, 2))
	{
		DWORD dwError = ::GetLastError();
		dwError = dwError;
	}
}