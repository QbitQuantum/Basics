void CFeedIcoItemListCtrl::DrawItems(CDC & dcMem, const CRect & rectClip, const CRect & rectClient)
{
	//CImageList* pImgList = GetImageList(LVSIL_NORMAL);

	CFont * pListFont = GetFont();
	dcMem.SelectObject(pListFont);
	dcMem.SetTextColor(RGB(0,0,0));

	CRect itemRect(0,0,0,0);

	CString strTaskName;

	int nItemCount  = GetItemCount() - 1;
	int nHoverIndex = GetHotItem();//Hover
	for ( ; nItemCount >= 0; nItemCount-- )
	{
		int nItemIndex = nItemCount;
		GetItemRect(nItemIndex, &itemRect, LVIR_BOUNDS);

		CRect rtIntersect;
		rtIntersect.IntersectRect(rectClip,itemRect);
		if (rtIntersect.IsRectEmpty())//判断此ITEM是否在重绘区域内,不在的话则直接continue
			continue;

		CRect rectPoster;//封面RECT
		GetItemRect(nItemIndex, &rectPoster, LVIR_ICON);

		//绘制海报
		if( nHoverIndex == nItemIndex || GetItemState(nItemIndex, ODA_SELECT) == ODA_SELECT )
		{//Hover
			if (m_imageRss_PosterSelBg)
				m_imageRss_PosterSelBg->Draw(dcMem.m_hDC, rectPoster.left + 11, rectPoster.top - 8);
		}
		else
		{//Normal
			if (m_imageRss_PosterBg)
				m_imageRss_PosterBg->Draw(dcMem.m_hDC, rectPoster.left + 15, rectPoster.top - 4);
		}

		CRssFeed* pFeed = (CRssFeed*)GetItemData(nItemIndex);

		if (pFeed->m_pPosterImage)//绘制海报
			pFeed->m_pPosterImage->Draw(dcMem.m_hDC, rectPoster.left + 20, rectPoster.top + 1);
		else if (m_imageRss_PosterDefault)//绘制默认海报
				m_imageRss_PosterDefault->Draw(dcMem.m_hDC, rectPoster.left + 20, rectPoster.top + 1);

		//strTaskName = pFeed->m_strTitle;
		strTaskName = GetItemText(nItemCount, 0);

		CRect rectNameStr;//宽度146
		GetItemRect(nItemIndex, &rectNameStr, LVIR_LABEL);
		rectNameStr.OffsetRect(0,5);//拉开标题和Poster的距离 

		dcMem.DrawText(strTaskName, -1, &rectNameStr, DT_CENTER | DT_WORDBREAK );

		//if (pImgList)
		//	pImgList->Draw(&MemDC,nItem,CPoint(itemRect.left+5,itemRect.top+5),ILD_TRANSPARENT);
	}
}