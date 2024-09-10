STDMETHODIMP CPdnWnd::animate(DWORD flags, DWORD duration)
{
	if(!AnimateWindow(m_hWnd, duration, flags))
	{
		hide(false);
	}
	return S_OK;
}