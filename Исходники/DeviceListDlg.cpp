void CDeviceListDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd = GetOwner();
	char szTmp[MAX_PATH] = {0};
	if (FALSE == m_bDragging || NULL == pWnd || 0 == m_hItemDrag)
	{
		CDialog::OnLButtonUp(nFlags, point);
		return;
	}
	m_bDragging = FALSE;
	CImageList::DragLeave( pWnd );
	CImageList::EndDrag();
	ReleaseCapture();
	SAFE_DELETE(m_pDragImage);

	CIVS_VDemoDlg* pTestDlg = reinterpret_cast<CIVS_VDemoDlg*>(pWnd);
	CRect rc = pTestDlg->GetTaskDlg()->GetTaskListRect();

	pWnd->ClientToScreen(&point);

	sprintf(szTmp, "OnLButtonUp 2 (%d,%d) ",point.x, point.y);
	OutputDebugString(szTmp);
	sprintf(szTmp, "OnLButtonUp 3 (%d,%d)(%d,%d) ",rc.left, rc.top, rc.right, rc.bottom);
	OutputDebugString(szTmp);
	if (PtInRect(&rc,point))
	{
		DWORD dwRet = m_TreeDevices.GetItemData(m_hItemDrag);
		if (dwRet>1024)
		{
			int nChildCount = 0;
			HTREEITEM hItem = m_TreeDevices.GetChildItem(m_hItemDrag);
			while(hItem) 
			{ 
				nChildCount++;
				hItem = m_TreeDevices.GetNextSiblingItem(hItem);
			}

			CFG_TAST_SOURCES* pSource = reinterpret_cast<CFG_TAST_SOURCES*>(dwRet-1024);
			pTestDlg->GetTaskDlg()->SetOneDeviceInfo(pSource, -1, nChildCount);
		}
		else
		{
			HTREEITEM hParent = m_TreeDevices.GetParentItem(m_hItemDrag);
			DWORD dwParent = m_TreeDevices.GetItemData(hParent);
			CFG_TAST_SOURCES* pSource = reinterpret_cast<CFG_TAST_SOURCES*>(dwParent-1024);
			pTestDlg->GetTaskDlg()->SetOneDeviceInfo(pSource, dwRet-1);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}