STDMETHODIMP CGfxSAMSUNG::SetAlpha(DWORD dwAlpha)
{
	m_uAlpha = (unsigned char)dwAlpha*0xf/MAX_ALPHA_VAL;
	if(m_uAlpha > 0xf)
		m_uAlpha = 0xf;

	if(!ExtEscape( ::GetDC( NULL ), IOCTL_WIN1_SETALPHA, sizeof(m_uAlpha),(LPCSTR)&m_uAlpha,0,NULL))
	{
	   RETAILMSG(1,(L"$$$$$$ SetAlpha Failed ! $$$$$$$$$$$$$$$$$$\n"));
		return E_FAIL;
	}
	return S_OK;
}