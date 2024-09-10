STDMETHODIMP CGfxRMI::SetScnRect(const RECT *pRect)
{
	if(pRect==0)
	{
		m_bScnClip = FALSE;
		return S_OK;
	}
	if(EqualRect(pRect,&m_rectScn))// && m_bScnClip)
		return S_OK;
	m_rectScn = *pRect;
	m_bScnClip = TRUE;
	return Update();
}