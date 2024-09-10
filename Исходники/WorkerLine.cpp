void CWorkerLine::OnMouseMove(UINT nFlags, CPoint point)
{
	CGlobalAgent::showMessageOnStatusBar("CWorkerLine::OnMouseMove");
	if (started == FALSE)
	{
		return;
	}

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDemo8View *pView = (CDemo8View *)pFrame->GetActiveView();
	//CPaintDC dc(pView);
	//CPen pen;
	CDC *pDC = pView->GetDC();
	//pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	//pDC->SelectObject(pen);
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->MoveTo(start);
	pDC->LineTo(last_mouse_location);
	pDC->MoveTo(start);
	pDC->LineTo(point);
	last_mouse_location = point;
}