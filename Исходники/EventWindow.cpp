LRESULT CSkypeAPIEventWindow::OnFireBinaryTransferEnd(UINT nMsg, WPARAM wLPWSTRTransferID, LPARAM lPtrSafeArray, BOOL& bHandled)
{
	try {
		SAFEARRAY * psa = (SAFEARRAY *) lPtrSafeArray;
		m_ptrAccess->BinaryTransferEnd(SysAllocString((LPWSTR) wLPWSTRTransferID), & psa);
		free((LPWSTR) wLPWSTRTransferID);
		SafeArrayDestroy(psa);
	} catch(...) {
	}

	bHandled = true;
	return 0;
}