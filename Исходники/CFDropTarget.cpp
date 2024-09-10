BOOL CCFDropTarget::OnDrop( CWnd* pWnd,COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point )
{
	if (!pDataObject->IsDataAvailable(CF_HDROP))
	{
		return S_FALSE;
	}

	HGLOBAL hData =pDataObject->GetGlobalData(CF_HDROP);
	if (hData)
	{
		TCHAR szBuffer[MAX_PATH];
		ZeroMemory(szBuffer, sizeof(szBuffer));
		HDROP hdrop = (HDROP)GlobalLock(hData);
		DragQueryFile((HDROP)hdrop, 0, szBuffer, MAX_PATH);
		GlobalUnlock(hData);
		if (szBuffer[0] != L'\0')
		{
			CRect rcSrc, rcDes;
			CConfigUtilityDlg* pDlg = (CConfigUtilityDlg*)pWnd;
			pDlg->m_edtSrcPath.GetWindowRect(rcSrc);
			pDlg->ScreenToClient(rcSrc);
			pDlg->m_edtDesPath.GetWindowRect(rcDes);
			pDlg->ScreenToClient(rcDes);
			if (rcSrc.PtInRect(point) )
			{
				pDlg->m_edtSrcPath.SetWindowText(szBuffer);
			}
			else if (rcDes.PtInRect(point))
			{
				pDlg->m_edtDesPath.SetWindowText(szBuffer);
			}
		}
		
	}
	return S_OK;
}