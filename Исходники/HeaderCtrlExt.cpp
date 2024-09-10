void CHeaderCtrlExt::DrawDragDivider()
{
	CWnd* pParent = GetParent();

	CDC* pDC = pParent->GetDCEx(NULL, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	int nROP2 = pDC->SetROP2(R2_NOT);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pPenOld = pDC->SelectObject(&pen);

	CRect rc;
	pParent->GetWindowRect(&rc);
	ScreenToClient(&rc);

	CRect rcItem;
	GetItemRect(m_nDraggingItem, &rcItem);

	int dx = m_ptDragMove.x - m_ptDragStart.x;
	int x = max(rcItem.left, rcItem.right + dx);
	pDC->MoveTo(x, rc.top);
	pDC->LineTo(x, rc.bottom);

	pDC->SelectObject(pPenOld);
	pDC->SetROP2(nROP2);
	pParent->ReleaseDC(pDC);
}