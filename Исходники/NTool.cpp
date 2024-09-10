void CNPainterView::OnDraw(CDC* pDC)
{
	CNPainterDoc* pdoc = GetDocument();
	ASSERT_VALID(pdoc);
	if (!pdoc)
		return;

	CRect client, rect;
	
	CDC dc;
	CDC *pdrawdc = pDC;
	CBitmap bitmap;
	CBitmap* poldbmp = nullptr;
	pDC->GetClipBox(client);
	rect = client;
	docToClient(rect);
	CString str;
	str.Format(_T("CNPainterView::OnDraw clipRect:<%d,%d,%d,%d %d,%d>"), rect.left, rect.top, rect.right, rect.bottom, rect.Width(), rect.Height());
	AfxGetMainWnd()->SetWindowText(str);
	if(!pDC->IsPrinting())
	{
		if(dc.CreateCompatibleDC(pDC))
		{
			if(bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				OnPrepareDC(&dc, NULL);
				pdrawdc = &dc;
				dc.OffsetViewportOrg(-rect.left, -rect.top);
				poldbmp = dc.SelectObject(&bitmap);
				dc.SetBrushOrg(rect.left % 8, rect.top % 8);

				// might as well clip to the same rectangle
				//dc.SelectClipRgn(NULL);
				dc.IntersectClipRect(client);
			}
		}
	}
	//// 更新背景
	//if(!pdrawdc->IsPrinting())
	//	DoDrawBackground(pdrawdc);
	//// 背景图片
	//pdoc->m_adminObjs.DrawPaperBack(pdrawdc);
	////// 画网格 VSP3.1 网格线已经集成到itobjPage::Draw()
	////if(!pdrawdc->IsPrinting() && pdoc->m_adminObjs.IsVisibleGrid())
	////	DoDrawGrid(pdrawdc);
	//pdoc->m_adminObjs.DrawObjects(pdrawdc);
	//// 绘制选中标识
	//DoDrawSelectItems(pdrawdc);
	// 
	pdoc->getAdminer().drawBackground(pdrawdc, m_szWorker);
	//// 画对象
	pdoc->getAdminer().draw(pdrawdc, this);
	pdoc->draw(pdrawdc);
	// 刷新客户区
	
	//if(pdrawdc != pDC)
	//{	
	//	pDC->BitBlt(client.left, client.top, client.Width(), client.Height(), pdrawdc, client.left, client.top, SRCCOPY);
	//	if(poldbmp)
	//		pdrawdc->SelectObject(poldbmp);
	//}
	if (pdrawdc != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(poldbmp);
	}

	

}