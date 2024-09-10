void SetWidthByContentInListBox(CDialog* pDlg, int nID)
{
	if (nID <= 0|| pDlg == NULL) return;
	CWnd* pWnd = (CWnd*)pDlg;

	CListBox* pCB = (CListBox*)pWnd->GetDlgItem(nID);
	if (pCB == NULL) return;

	int origSize = pCB->GetHorizontalExtent();
	int maxSize = origSize;

	CDC* pDC = pWnd->GetDC();
	CString cStr;
	int str_num = pCB->GetCount();
	for (int i = 0; i < str_num; i++)
	{
		pCB->GetText(i, cStr);

		CSize strSize = pDC->GetOutputTextExtent(cStr);
		if (strSize.cx > maxSize)
			maxSize = strSize.cx;
	}

	// in case when adding to list, existing items may be
	// longer than newer ones, so may not want to resize
	if (maxSize > origSize)
		pCB->SetHorizontalExtent(maxSize);
}