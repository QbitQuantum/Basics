// 重置
void CInstrumentGraph::OnReset(void)
{
	m_iRightMovePos = 0;
	m_iLeftMovePos = 0;
	m_iHScrPos = 0;
	m_bLButtonSelect = false;
	m_rectGraph = m_rectClient;
	m_rectGraph.right -= m_iVScrBarInterval;
	m_rectGraph.bottom -= m_iHScrBarInterval;

	m_iLauxPosX = m_rectGraph.right / 2;
	m_iLauxPosY = m_rectGraph.bottom / 2;
	CClientDC dc(this) ;  
	CBitmap bitmapGrid;
	// 如果还没有绘图DC，则为其设置一个内存DC
	if (m_dcGraph.GetSafeHdc() != NULL)
	{
		if (m_pbitmapOldGrid != NULL)
		{
			m_dcGraph.SelectObject(m_pbitmapOldGrid) ; 
		}
		m_dcGraph.DeleteDC();
	}
	m_dcGraph.CreateCompatibleDC(&dc) ;
	bitmapGrid.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height()) ;
	m_pbitmapOldGrid = m_dcGraph.SelectObject(&bitmapGrid) ;
	OnFillBkColor(&m_dcGraph, m_rectGraph);
	m_oInstrumentGraphRectList.RemoveAll();
	m_pWndVScr->EnableWindow(FALSE);
	m_pWndHScr->EnableWindow(FALSE);
	m_bDrawUnit = false;
}