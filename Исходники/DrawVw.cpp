void CDrawView::OnDraw(CDC* pDC)
{	
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	CDC dc;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(client);				//检取当前裁剪边界的最近限定矩形的大小
	CRect rect = client;
	DocToClient(rect);
	rect.NormalizeRect();

	TRACE("CDrawView::OnDraw\n");

	if (!pDC->IsPrinting())//不加会闪屏
	{
		// draw to offscreen bitmap for fast looking repaints
		if (dc.CreateCompatibleDC(pDC))				//创建一个与指定设备兼容的内存设备上下文环境
		{
			if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))//创建与指定的设备环境相关的设备兼容的位图
			{
				OnPrepareDC(&dc, NULL);
				pDrawDC = &dc;

				// offset origin more because bitmap is just piece of the whole drawing
				dc.OffsetViewportOrg(-rect.left, -rect.top);//相对于当前视区起点坐标修正视区起点坐标
				pOldBitmap = dc.SelectObject(&bitmap);		//选择一对象到指定的设备上下文环境中
				dc.SetBrushOrg(rect.left % 8, rect.top % 8);//指定GDI将分配给下画笔应用程序选择到设备上下文的原点

				// might as well clip to the same rectangle
				dc.IntersectClipRect(client);				//创建了一个新的剪切区域，该区域是当前剪切区域和一个特定矩形的交集
			}
		}
	}

	// paint background
	CBrush brush;
	if (!brush.CreateSolidBrush(pDoc->GetPaperColor()))
		return;

	brush.UnrealizeObject();				//重置一个逻辑调色板
	pDrawDC->FillRect(client, &brush);		//用指定的画刷填充矩形


	Painter::GetInstancePtr()->SetCDC(pDrawDC);
	Painter::GetInstancePtr()->SetCWnd(this);

	if (!pDC->IsPrinting() && m_bGrid)
		DrawGrid(pDrawDC);

	g_pGuiManager->Draw();

	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}