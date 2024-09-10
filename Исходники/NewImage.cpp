CNewImage::CNewImage()
{
	MSG msg;
	BOOL ret;

	m_hWnd = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_NEWIMAGE), CRenderer::Get()->GetHWnd(), DialogProc, 0);

	SetWindowTextA(GetDlgItem(m_hWnd, IDC_NWIDTH), "300");
	SetWindowTextA(GetDlgItem(m_hWnd, IDC_NHEIGHT), "200");

	SetWindowTextA(GetDlgItem(m_hWnd, IDC_NR), "255");
	SetWindowTextA(GetDlgItem(m_hWnd, IDC_NG), "255");
	SetWindowTextA(GetDlgItem(m_hWnd, IDC_NB), "255");

	ShowWindow(m_hWnd, SW_SHOW);

	while ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (ret == -1)
			return;

		if (!IsDialogMessage(m_hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}