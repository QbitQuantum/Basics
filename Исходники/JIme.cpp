void JIme::SetImeMode(const DWORD mode)
{
	HWND hWnd = JMain::GetInstance().GetJWindow().GetWindowHandle();
	HIMC hImc = ImmGetContext(hWnd);
	DWORD dwConv, dwSent;
	ImmGetConversionStatus(hImc, &dwConv, &dwSent);
	ImmSetConversionStatus(hImc, mode, dwSent);
	ImmReleaseContext(hWnd, hImc);
}