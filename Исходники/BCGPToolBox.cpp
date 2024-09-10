//*********************************************************************************
HRESULT CBCGPToolBoxPage::get_accParent(IDispatch **ppdispParent)
{
	if (ppdispParent == NULL)
	{
		return E_INVALIDARG;
	}

	*ppdispParent = NULL;

	if (m_pToolBoxEx->GetSafeHwnd() != NULL)
	{
		return AccessibleObjectFromWindow(m_pToolBoxEx->GetSafeHwnd(), (DWORD)OBJID_WINDOW, IID_IAccessible, (void**)ppdispParent);
	}

	if (m_pToolBox->GetSafeHwnd() != NULL)
	{
		return AccessibleObjectFromWindow(m_pToolBox->GetSafeHwnd(), (DWORD)OBJID_WINDOW, IID_IAccessible, (void**)ppdispParent);
	}

	return S_FALSE;
}