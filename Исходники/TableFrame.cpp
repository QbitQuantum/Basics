//滚动消息
void CTableFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
	//获取参数
	RECT rcClientRect;
	int iLastPos=m_iCurrentPos;
	GetClientRect(&rcClientRect);

	//移动坐标
	switch (nSBCode)
	{
	case SB_TOP:
		{
			m_iCurrentPos=0;
			break;
		}
	case SB_BOTTOM:
		{
			m_iCurrentPos=m_iMaxScrollPos-m_iCountVisibleLine*m_TableResource.m_wHeight;
			break;
		}
	case SB_LINEUP:
		{
			m_iCurrentPos-=m_iScrollPos;
			break;
		}
	case SB_PAGEUP:
		{
			m_iCurrentPos-=rcClientRect.bottom;
			break;
		}
	case SB_LINEDOWN:
		{
			m_iCurrentPos+=m_iScrollPos;
			break;
		}
	case SB_PAGEDOWN:
		{
			m_iCurrentPos+=rcClientRect.bottom;
			break;
		}
	case SB_THUMBTRACK:
		{
			m_iCurrentPos=nPos;
			break;
		}
	}
	
	//调整位置
	SetFocus();
	m_iCurrentPos=__min(m_iCurrentPos,m_iMaxScrollPos-rcClientRect.bottom);
	if (m_iCurrentPos<0) m_iCurrentPos=0;
	if (iLastPos!=m_iCurrentPos)
	{
		SetScrollPos(SB_VERT,m_iCurrentPos);
		ScrollWindow(0,iLastPos-m_iCurrentPos,NULL,NULL);
	}

	return;
}