HRESULT CMatrixBox::OnItemDrag(CMatrixItem* pEventSource)
{
	if(m_pParentFrame == NULL)
	{
		return E_FAIL;
	}
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcScreen = GetScreenRect();
	CRect rcScreenParent = m_pParentFrame->GetScreenRect();
	CRect rcClip;
	::IntersectRect(&rcClip,&rcScreen,&rcScreenParent);

	CRect rcDrag = pEventSource->GetDragRect();

	int nWidth = rcDrag.Width()/2 + 9 ;
	int nHeight = rcDrag.Height()/2 + 3;
	CRect rcDragItem = pEventSource->GetRect();


	int nOverFlow = 0;
	if(pt.x < rcClip.left + nWidth)
	{
		nOverFlow = 1;
		pt.x = rcClip.left + nWidth;
	}
	if(pt.y < rcClip.top + nHeight)
	{
		nOverFlow = 2;
		pt.y = rcClip.top + nHeight;
	}
	if(pt.x > rcClip.right - (rcDragItem.Width() - nWidth))
	{
		nOverFlow = 3;
		pt.x = rcClip.right - (rcDragItem.Width() - nWidth);
	}
	if(pt.y > rcClip.bottom - (rcDragItem.Height() - nHeight))
	{
		nOverFlow = 4;
		pt.y = rcClip.bottom - (rcDragItem.Height() - nHeight);
	}

	pt.x = pt.x - nWidth - rcScreen.left ;
	pt.y = pt.y - nHeight - rcScreen.top ;
	
	CRect rcOldPaint = pEventSource->GetPaintRect();
	pEventSource->SetPosition(pt);

	pt.x += nWidth;
	pt.y += nHeight;

	vector<CXFrame*> vec = m_vecItem;
	int nIndexMine = 0;
	for(vector<CXFrame*>::iterator it = vec.begin();it != vec.end();it++)
	{
		if(*it == pEventSource)
		{
			vec.erase(it);
			break;
		}
		nIndexMine ++;
	}

	BOOL bMoved = FALSE;

	int nIndex = 0;
	for(vector<CXFrame*>::iterator it = vec.begin();it != vec.end();it++)
	{
		CMatrixItem* pItem = (CMatrixItem*)*it;

		CRect rcItem = pItem->GetRect();
		if(pItem->GetEnableDrag() && rcItem.PtInRect(pt))
		{
			if(nIndex < nIndexMine)
			{
				vec.insert(it,pEventSource);
			}
			else if(nIndex == vec.size() - 1)
			{
				vec.push_back(pEventSource);
			}
			else
			{
				vec.insert(it+1,pEventSource);
			}
			
			bMoved = TRUE;
			break;
		}
		nIndex ++;
	}
	if(bMoved)
	{
		m_vecItem.clear();
		m_vecItem = vec;
		Relayout();
		QuickPaint(GetPaintRect());
	}
	else
	{
		pEventSource->Relayout();
		CRect rcDst;
		CRect rcCur = pEventSource->GetPaintRect();
		UnionRect(&rcDst,&rcOldPaint,&rcCur);
		QuickPaint(rcDst);
	}
	if(nOverFlow)
	{
		ThrowEvent(EVENT_MATRIX_DRAG_OVERFLOW,&nOverFlow);
	}

	return S_OK;
}