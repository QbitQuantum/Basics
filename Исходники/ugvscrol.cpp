/***************************************************
Moved
	Updates vertical scrolbar's position and redraws the grid.
Params:
	<none>
Returns:
	<none>
*****************************************************/
void CUGVScroll::Moved()
{
	if ( m_GI->m_paintMode == FALSE )
		return;

	BOOL bScrolled = FALSE;

	//set the scroll range
	if(	m_lastMaxTopRow != m_GI->m_maxTopRow ||
		m_lastScrollMode != m_GI->m_vScrollMode ||
		m_lastNumLockRow != m_GI->m_numLockRows)
	{
		//set the last value vars
		m_lastMaxTopRow = m_GI->m_maxTopRow;
		m_lastScrollMode = m_GI->m_vScrollMode;
		m_lastNumLockRow = m_GI->m_numLockRows;

		//set up the scrollbar if the number of rows is less than 1000
		if(m_GI->m_maxTopRow <=1000)
		{
			if(UG_SCROLLJOYSTICK == m_GI->m_vScrollMode)
			{
				SCROLLINFO ScrollInfo;
				ScrollInfo.cbSize =sizeof(SCROLLINFO);
				ScrollInfo.fMask = SIF_PAGE | SIF_RANGE |SIF_POS;
				ScrollInfo.nPage = 0;
				ScrollInfo.nMin = 0;
				ScrollInfo.nMax = 2;
				ScrollInfo.nPos = 1;
				SetScrollInfo(&ScrollInfo,FALSE);
				Invalidate();
			}
			else
			{
				SCROLLINFO ScrollInfo;

				ScrollInfo.cbSize =sizeof(SCROLLINFO);
				ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;

				if( m_GI->m_defRowHeight < 1 )
					m_GI->m_defRowHeight =  1;

				ScrollInfo.nPage = m_GI->m_gridHeight / m_GI->m_defRowHeight;

				ScrollInfo.nMin = m_GI->m_numLockRows;
				ScrollInfo.nMax = m_GI->m_maxTopRow + ScrollInfo.nPage -1;
				SetScrollInfo(&ScrollInfo,FALSE);
				Invalidate();
			}
			bScrolled = TRUE;
			m_multiRange = 1;
			m_multiPos	= 1;			
		}
		//set up the scrollbar if the number of rows is greater than 1000
		else
		{
			m_multiRange = (double)1000 / (double)m_GI->m_maxTopRow;
			m_multiPos   = (double)m_GI->m_maxTopRow / (double)1000;
			if(UG_SCROLLJOYSTICK==m_GI->m_vScrollMode)
			{
				SetScrollRange(0,2,FALSE);
				m_multiRange = 1;
				m_multiPos	= 1;
			}
			else
			{
				SCROLLINFO ScrollInfo;
				ScrollInfo.cbSize =sizeof(SCROLLINFO);
				ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;
				ScrollInfo.nPage = 1;
				ScrollInfo.nMin = 0;//m_GI->m_numLockRows;
				ScrollInfo.nMax = 1000;
				SetScrollInfo(&ScrollInfo,FALSE);
			}
			bScrolled = TRUE;
		}
	}

	//set the scroll pos
	if( m_GI->m_lastTopRow != m_GI->m_topRow || bScrolled == TRUE )
	{
		if(UG_SCROLLJOYSTICK == m_GI->m_vScrollMode)
			SetScrollPos(1,TRUE);
		else
			SetScrollPos((int)(m_GI->m_topRow * m_multiRange),TRUE);

		m_ctrl->OnViewMoved( UG_VSCROLL, m_GI->m_lastTopRow, m_GI->m_topRow );
	}
}