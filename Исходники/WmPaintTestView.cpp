void CWmPaintTestView::OnMenuGMJoin() 
{
	CDC* pDC = GetDC();
	int nStyle[3];
	nStyle[0] = PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL;
	nStyle[1] = PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND;
	nStyle[2] = PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_MITER;

	CPen* pNewPen = NULL;
	CPen* pOldPen = NULL;

	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 0, 255);

	for(int i = 0; i < 3; i++)
	{
		pNewPen = new CPen(nStyle[i], 16, &lb);
		pOldPen = pDC->SelectObject(pNewPen);

		//ㄱ자 모양으로 선을 그리되 이 두 선을 서로 패스로 묶어준다.
		// BeginPath EndPath의 역할 : 사이의 선이 연결선음을 암시 
		pDC->BeginPath();
		pDC->MoveTo(100 + i * 120, 200);
		pDC->LineTo(200 + i * 120, 200);
		pDC->LineTo(200 + i * 120, 200 + 50);
		pDC->EndPath();
		//두 연결된 선의 꺽어진 부분에 대해 Join 스타일을 적용하여 랜더링한다.
		// 여기서 그려주게 됨 
		pDC->StrokePath();

		pDC->SelectObject(pOldPen);
		delete pNewPen;
	}

	ReleaseDC(pDC);
}