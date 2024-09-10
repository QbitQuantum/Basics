void CStaffManageView::ClearPhotoView()
{
	CWnd *pPictureWnd = GetDlgItem(IDC_STATIC_PHOTO);
	if (!pPictureWnd)
		return;

	CRect rect;
	pPictureWnd->GetClientRect(rect);

	CDC  *pDC  = pPictureWnd->GetDC();
	CBrush brush(RGB(255,255,255));
	CBrush * pOldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);
}