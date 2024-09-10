STDMETHODIMP CMyCom1::DrawOffset(unsigned long m_pDC, unsigned long m_pOffset, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CClientDC * pDC = (CClientDC*) m_pDC;
	GraphInfo * pGraphInfo;

	//设置
	if ( m_pGraphInfo != NULL )
	{
		pGraphInfo = (GraphInfo*)m_pGraphInfo;
		m_GraphInfo.SetGraphInfo(*pGraphInfo);
	}
	else
		pGraphInfo = &m_GraphInfo;
	
		
	//计算偏移量
	if ( m_pOffset != NULL )
	{
		CPoint * offset = (CPoint *)m_pOffset;
		OffsetRgn((unsigned long)offset);
	}

	//设置激活标志
	isActive = m_active_flag;

	double scale = 0;
	m_scale_flag = scale_flag;
	if ( m_scale_flag )
		scale = m_Scale;
	else
		scale = 1;

	CFont * sysFont = pDC->SelectObject(&(pGraphInfo->font));
	CPen * pen = new CPen( pGraphInfo->normal_penStyle, pGraphInfo->normal_linewidth, pGraphInfo->normal_linecolor );	//构造画笔
	CPen * sysPen = pDC->SelectObject(pen);
	CBrush * normalBrush = new CBrush( pGraphInfo->normal_regioncolor );	//普通显示的画刷
	CBrush * activeBrush = new CBrush( pGraphInfo->active_regioncolor );	//激活后的画刷
	CBrush * blackBrush = new CBrush( BLACKBRUSHCOLOR );
	
	CRgn outRgn;
	outRgn.CreateRectRgn(0, 0, 5, 5);
	CRect smallRect;
	
	//判断是否激活了，如果激活，添加outRect
	if ( isActive )	//激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//选中后，在外边画一个方框
			outRgn.CombineRgn(&upRgn, &downRgn, RGN_OR);
			outRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);
			
			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);

			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);
						
			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
		else	//如果是在comview区域
		{
			//选中后，在外边画一个方框
			downRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);

			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);

			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);

			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
	}
	else	//未激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);
		}
		else	//如果是在comview区域
		{
			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);
		}
	}

		//释放
	pDC->SelectObject(sysFont);
	pDC->SelectObject(sysPen);
	
	delete(pen);
	delete(normalBrush);
	delete(activeBrush);
	delete(blackBrush);
	
	return S_OK;
}