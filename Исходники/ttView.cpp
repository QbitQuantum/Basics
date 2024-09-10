void CttView::LineCai(const CPoint &x, const CPoint &y){
	int c[2][4];
	int cnum[2];
	CDC* pDC = GetWindowDC();
	CPen pen1(0, 0, RGB(255, 0, 0));
	CPen pen2(0, 3, RGB(0, 0, 0));
	CPen pen3(0, 2, RGB(0, 0, 0));
	GetC(c[0],cnum[0],x);
	GetC(c[1],cnum[1],y);
	if (cnum[0] & cnum[1]){
		pDC->SelectObject(&pen1);
		pDC->MoveTo(x);
		pDC->LineTo(y);
		return;
	}
	if ((cnum[0] | cnum[1])==0){
		pDC->SelectObject(&pen2);
		pDC->MoveTo(x);
		pDC->LineTo(y);
		return;
	}
	pDC->SelectObject(&pen1);
	pDC->MoveTo(x);
	pDC->LineTo(y);
	CPoint a[2];
	int an = 0;
	if (c[0][0] != c[1][0])//与下边有交
	{
		int jx = x.x + (1.0*m_d - x.y) / (y.y - x.y)  *(y.x - x.x);
		if (jx > m_l && jx < m_r) a[an++] = CPoint(jx, m_d);
	}
	if (c[0][1] != c[1][1])//与上边有交
	{
		int jx = x.x + (1.0*m_u - x.y) / (y.y - x.y)  *(y.x - x.x);
		if (jx > m_l && jx < m_r) a[an++] = CPoint(jx, m_u);
	}
	if (c[0][2] != c[1][2])//与右边有交
	{
		int jy = x.y + (1.0*m_r - x.x) / (y.x - x.x)  *(y.y - x.y);
		if (jy < m_d && jy > m_u) a[an++] = CPoint(m_r, jy);
	}
	if (c[0][3] != c[1][3])//与左边有交
	{
		int jy = x.y + (1.0*m_l - x.x) / (y.x - x.x)  *(y.y - x.y);
		if (jy < m_d && jy > m_u) a[an++] = CPoint(m_l, jy);
	}
	if (an == 1){
		if (cnum[0] == 0)a[an++] = x;
		else a[an++] = y;
	}
	pDC->SelectObject(&pen2);
	pDC->MoveTo(a[0]);
	pDC->LineTo(a[1]);
}