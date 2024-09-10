void CHeadCtrol::PaintDragLine(int pos, bool bOne ) //ÍÏ×§ÏßÌõ
{
	CDC* pDC = CWnd::FromHandle(m_hListWnd)->GetWindowDC();
	int nRop = pDC->SetROP2(R2_NOTXORPEN);
	CRect lrect;
	CWnd::FromHandle(m_hListWnd)->GetClientRect( &lrect );

	CPen  pen;
	pen.CreatePen(0, 1, RGB(0, 0, 0));
	CPen *pOP = pDC->SelectObject(&pen);



	if( posPre != -1  ) 
	{
		pDC->MoveTo( posPre,0 );
		pDC->LineTo( posPre,lrect.bottom );
	}

	if(  !bOne  ) 
	{
		pDC->MoveTo( pos,0 );
		pDC->LineTo( pos,lrect.bottom );
	}


	pDC->SetROP2(nRop);
	pDC->SelectObject(pOP);
	pen.DeleteObject();

	ReleaseDC(pDC);

	posPre = pos;
}