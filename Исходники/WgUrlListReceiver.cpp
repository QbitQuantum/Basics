STDMETHODIMP CWgUrlListReceiver::ShowAddUrlListDialog()
{
	if (m_vUrls.size () == 0)
		return S_FALSE;

	UIThread *thr = (UIThread*) RUNTIME_CLASS (UIThread)->CreateObject ();

	threadAddUrlListDialogParam *param = new threadAddUrlListDialogParam;
	param->pthis = this;
	AddRef ();
	CComObject <CFdmUiWindow> *pUiWindow = NULL;
	CComObject <CFdmUiWindow>::CreateInstance (&pUiWindow);
	param->pUiWindow = pUiWindow;
	if (pUiWindow)
		pUiWindow->AddRef ();
	vmsAUTOLOCKSECTION (m_csLastUiWindow);
	m_spLastUiWindow = pUiWindow;
	vmsAUTOLOCKSECTION_UNLOCK (m_csLastUiWindow);
	thr->set_Thread (_threadAddUrlListDialog, param);
	thr->CreateThread ();

	return S_OK;
}