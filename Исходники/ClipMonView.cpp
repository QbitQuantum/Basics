void CClipMonView::ReDrawRemainTime(CDC* pDC)
{
	CRect rcClient;
	TxGetClientRect(rcClient);
	if (m_scBar[SB_VERT].IsShowing())
	{
		rcClient.DeflateRect(0,0,m_scBar[SB_VERT].GetBarWidth(), 0);
	}
	if (m_scBar[SB_HORZ].IsShowing())
	{
		rcClient.DeflateRect(0,0, 0, m_scBar[SB_HORZ].GetBarWidth());
	}
// 	Rect rCet = CRect2Rect(rcClient);
// 	gc.FillRectangle(&bkBrush, rCet);
	CSize szView = GetScrollViewSize();
	CRect rcView(0, 0, szView.cx, szView.cy);
	rcView.OffsetRect(rcClient.left, rcClient.top);

	if (rcView.IsRectEmpty())
	{
		return;
	}
	rcView.OffsetRect(-GetScrollPos(SB_HORZ), -GetScrollPos(SB_VERT));

	int nBegin = (rcClient.top - rcView.top) / m_drawParam.nItemHeight;
	int nCount = rcClient.Height() /m_drawParam.nItemHeight +1;
	VECTMPITEM vData;
	g_monDataMgr.GetRangeData(nBegin, nCount, vData);
	nCount = vData.size();
	if (nCount <= 0)
	{
		return;
	}
	CTxListHeader& headerCtrl = GetListHeader();

	int nLeftPos = rcView.left;
	int nRightPos = 0;
	for (int cIdx = 0;  cIdx < m_ColSetting.m_vTmpCols.size(); cIdx++)
	{

		ENUM_MONTYPE nMonType =  (ENUM_MONTYPE)(m_ColSetting.m_vTmpCols[cIdx].nPosInType);
		if (nMonType == MONTYPE_TIMEREMAIN)
		{
			nRightPos = nLeftPos + headerCtrl.GetHeaderWidth(cIdx);
			break;
		}
		else
		{
			nLeftPos += headerCtrl.GetHeaderWidth(cIdx);
		}
	}

	if (nRightPos < rcClient.left || nLeftPos > rcClient.right)
	{
		return;
	}

	CPoint ptOffSetBmp;
	int nTopPos = rcView.top + (nBegin * m_drawParam.nItemHeight);
	ptOffSetBmp.x = nLeftPos < 0? -nLeftPos:0;
	ptOffSetBmp.y = nTopPos < rcClient.top? rcClient.top - nTopPos: 0;
	CRect rcRemainTimeClient(nLeftPos, rcClient.top, nRightPos-1, rcClient.bottom);
	Graphics gc(m_pBmpRemainTime);
	SolidBrush bkBrush(m_drawParam.bkColor);
	GraphicsContainer container = gc.BeginContainer();
	int nClipHeight = m_drawParam.nItemHeight*nCount;
	if (nClipHeight < rcClient.Height())
	{
		nClipHeight = rcClient.Height();
	}
	Rect rClip(0,0, rcRemainTimeClient.Width(), nClipHeight);
	gc.SetClip(rClip);
	Rect rDes(nLeftPos, nTopPos, rClip.Width, rClip.Height);
	gc.FillRectangle(&bkBrush, rClip);
	Gdiplus::StringFormat fmt;
	fmt.SetAlignment(StringAlignmentCenter);
	fmt.SetLineAlignment(StringAlignmentCenter);
	fmt.SetTrimming(StringTrimmingEllipsisCharacter);
	fmt.SetFormatFlags(StringFormatFlagsLineLimit);
	Pen pen(g_globalInfo.viewSetting.clrSeparateLine, 1.0);
	Rect rRowBk(0, 0, rcRemainTimeClient.Width(), m_drawParam.nItemHeight);
	CRect rcItem(0,0, rRowBk.Width,rRowBk.Height);
	for (int i = 0; i < nCount; i++)
	{
		ARGB clr = 0xff000000;
		ARGB clrBk = 0xffffffff;
		vData[i].GetMonColor(clr, clrBk);
		bkBrush.SetColor(clrBk);
		gc.FillRectangle(&bkBrush, rRowBk);
		CString strText = vData[i].GetValue(MONTYPE_TIMEREMAIN);
		GPDrawShadowTextSimple(gc, strText, rcItem, *m_drawParam.pFont, clr, 0, 2,2, &fmt);
		//GPDrawShadowText(gc, strText, rcItem, *m_drawParam.pFont, clr, 0xff000000,0,0,0,0,&fmt);
		gc.DrawLine(&pen, rcItem.left, rcItem.bottom-1, rcItem.right, rcItem.bottom-1);
		nTopPos += m_drawParam.nItemHeight;
		rcItem.OffsetRect(0, m_drawParam.nItemHeight);
		rRowBk.Offset(0, m_drawParam.nItemHeight);
	}

	gc.EndContainer(container);

	Graphics gcDes(pDC->GetSafeHdc());
	CRect rcDesClip(rcRemainTimeClient);
	Rect rDesClip = CRect2Rect(rcDesClip);
	gcDes.SetClip(rDesClip);
	gcDes.DrawImage(m_pBmpRemainTime, rDesClip, ptOffSetBmp.x, ptOffSetBmp.y, (INT)rDesClip.Width, (INT)rDesClip.Height, UnitPixel);

}