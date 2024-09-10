STDMETHODIMP CGraphAnnotation::put_LabelColor(OLE_COLOR newVal)
{
	HRESULT hr;
	COLORREF col;
	hr = OleTranslateColor(newVal, NULL, &col);

	if(m_Color == col)
		return S_FALSE;

	m_Color = col;

	if(m_pCtrl)
		m_pCtrl->Refresh(FALSE);
	return S_OK;
}