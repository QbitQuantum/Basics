void CEditView::UnlockBuffer() const
{
	ASSERT_VALID(this);
	ASSERT(m_hWnd != NULL);
#ifndef _UNICODE
	if (afxData.bWin32s)
		return;
#endif
	HLOCAL hLocal = GetEditCtrl().GetHandle();
	ASSERT(hLocal != NULL);
	LocalUnlock(hLocal);
}