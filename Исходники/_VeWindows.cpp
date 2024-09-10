//--------------------------------------------------------------------------
bool VeWindows::IMEHandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM& lParam)
{
	bool bRes(false);

	switch(uMessage)
	{
	case WM_INPUTLANGCHANGE:
		break;
	case WM_IME_SETCONTEXT:
		//lParam = 0;
		break;
	case WM_IME_COMPOSITION:
		{
			HIMC hImc = ImmGetContext(hWnd);
			if(hImc)
			{
				LONG lRet;
				VeChar16 szCompStr[VE_UINT8_MAX];
				if(lParam & GCS_RESULTSTR)
				{
					lRet = ImmGetCompositionStringW(hImc, GCS_RESULTSTR, szCompStr, VE_UINT8_MAX) / sizeof(VeChar16);
					szCompStr[lRet] = 0;
					m_kInputMethodEvent.Callback(szCompStr, VeUInt32(lRet));
					bRes = true;
				}
				ImmReleaseContext(hWnd, hImc);
			}
		}
		break;
	case WM_CHAR:
		{
			VeChar16 acChar[2] = { (VeChar16)wParam, L'\0' };
			m_kInputMethodEvent.Callback(acChar, 1);
			bRes = true;
		}
		break;
	default:
		break;
	}
	return bRes;
}