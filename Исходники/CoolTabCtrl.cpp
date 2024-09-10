////调整尺寸////
void CCoolTabCtrl::AutoSize()
{
	UINT PageCount = m_PageList.GetCount();
	if(PageCount < 1) return;
	CPageItem	*pItem;
	POSITION	pos;
	CRect		rect,ClientRect,ItemRect;

	GetClientRect(ClientRect);
	ClientRect.DeflateRect(m_nBorder+1,m_nBorder+1);
	GetWindowRect(rect);
	ScreenToClient(rect);

	CDC* pDC = GetDC();
	CFont	*pOldFont = pDC->SelectObject(&m_font);

	if(m_nStyle&TCS_DOWN)
	{
		rect.left += 6;
		rect.right -= 6;
		rect.bottom -= 1;
		rect.top = rect.bottom - ITEMBUTTON_HEIGHT + 1;
	}
	else if(m_nStyle&TCS_UP)
	{
		rect.left += 2;
		rect.right -= 6;
		rect.bottom = rect.top + ITEMBUTTON_HEIGHT;
	}
	ItemRect = rect;
	int AreaWidth = 0,ItemMaxWidth,ItemIndex=0;
	ItemMaxWidth = rect.Width()/m_PageList.GetCount();
	BOOL	bMonoSpace = ((m_nStyle&TCS_MONOSPACE) == TCS_MONOSPACE)?1:0;
	////////设置按钮初始宽度，并得到按钮所需占用的总宽度///////
	for(pos=m_PageList.GetHeadPosition();pos!=NULL;ItemIndex++)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{
			if(!bMonoSpace)
				ItemMaxWidth = pItem->GetAreaWidth(pDC);
			AreaWidth += ItemMaxWidth;
			ItemRect.right = ItemRect.left+ItemMaxWidth-1;
			pItem->m_rect = ItemRect;
			ItemRect.left = ItemRect.right + 1;
			if(pItem->m_pWnd)
				pItem->m_pWnd->MoveWindow(ClientRect);
		}
	}
	////////当需要的空间大于实际空间时进行调整////
	if(AreaWidth > rect.Width() && !bMonoSpace)
	{
		ItemRect = rect;
		int AreaWidth,MaxWidth = rect.Width()/PageCount;
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				AreaWidth = pItem->GetAreaWidth(pDC);
				ItemMaxWidth = (ItemMaxWidth < AreaWidth)?MaxWidth:AreaWidth;
				ItemRect.right = ItemRect.left+ItemMaxWidth;
				pItem->m_rect = ItemRect;
				ItemRect.left = ItemRect.right + 1;
			}
		}
	}
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
}