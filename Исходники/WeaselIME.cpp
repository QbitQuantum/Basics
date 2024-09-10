HRESULT WeaselIME::_AddIMEMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	if(!m_hIMC)
		return S_FALSE;

	LPINPUTCONTEXT lpIMC = (LPINPUTCONTEXT)ImmLockIMC(m_hIMC);
	if(!lpIMC)
		return E_FAIL;

	HIMCC hBuf = ImmReSizeIMCC(lpIMC->hMsgBuf, 
		sizeof(TRANSMSG) * (lpIMC->dwNumMsgBuf + 1));
	if(!hBuf)
	{
		ImmUnlockIMC(m_hIMC);
		return E_FAIL;
	}
	lpIMC->hMsgBuf = hBuf;

	LPTRANSMSG pBuf = (LPTRANSMSG)ImmLockIMCC(hBuf);
	if(!pBuf)
	{
		ImmUnlockIMC(m_hIMC);
		return E_FAIL;
	}

	DWORD last = lpIMC->dwNumMsgBuf;
	pBuf[last].message = msg;
	pBuf[last].wParam = wp;
	pBuf[last].lParam = lp;
	lpIMC->dwNumMsgBuf++;
	ImmUnlockIMCC(hBuf);

	ImmUnlockIMC(m_hIMC);

	if (!ImmGenerateMessage(m_hIMC))
	{
		return E_FAIL;
	}

	return S_OK;
}