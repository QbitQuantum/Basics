/***************************************************
OnHScroll
	The framework calls this member function when the user clicks a window's
	horizontal scroll bar.
Params:
	nSBCode		- please see MSDN for more information on the parameters.
	nPos
	pScrollBar
Returns:
	<none>
*****************************************************/
void CUGHScroll::HScroll(UINT nSBCode, UINT nPos) 
{
	if(GetFocus() != m_ctrl->m_CUGGrid)
		m_ctrl->m_CUGGrid->SetFocus();

	m_ctrl->m_GI->m_moveType = 4;

	switch(nSBCode)
	{
	case SB_LINEDOWN:
		m_ctrl->MoveLeftCol(UG_COLRIGHT);
		break;
	case SB_LINEUP:
		m_ctrl->MoveLeftCol(UG_COLLEFT);
		break;
	case SB_PAGEUP:
		m_ctrl->MoveLeftCol(UG_PAGELEFT);
		break;
	case SB_PAGEDOWN:
		m_ctrl->MoveLeftCol(UG_PAGERIGHT);
		break;
	case SB_TOP:
		m_ctrl->MoveLeftCol(UG_LEFT);
		break;
	case SB_BOTTOM:
		m_ctrl->MoveLeftCol(UG_RIGHT);
		break;
	case SB_THUMBTRACK:
		if(m_GI->m_hScrollMode == UG_SCROLLTRACKING)	//tracking
			m_ctrl->SetLeftCol(nPos+m_GI->m_numLockCols);

		m_trackColPos = nPos+m_GI->m_numLockCols;

		//if enabled then show scroll hints
		#ifdef UG_ENABLE_SCROLLHINTS
			if(m_GI->m_enableHScrollHints)
			{
				CString string;
				RECT rect;
				GetWindowRect(&rect);
				rect.left = LOWORD(GetMessagePos());
				m_ctrl->ScreenToClient(&rect);
				m_ctrl->m_CUGHint->SetWindowAlign(UG_ALIGNCENTER|UG_ALIGNBOTTOM);
				m_ctrl->m_CUGHint->SetTextAlign(UG_ALIGNCENTER);

				m_ctrl->OnHScrollHint(m_trackColPos,&string);
				// set text before move window...
				m_ctrl->m_CUGHint->SetText(string,FALSE);

				m_ctrl->m_CUGHint->MoveHintWindow(rect.left,rect.top-1,20);
				m_ctrl->m_CUGHint->Show();				
			}
		#endif // UG_ENABLE_SCROLLHINTS
		break;
	case SB_ENDSCROLL:
		break;
	case SB_THUMBPOSITION:
		#ifdef UG_ENABLE_SCROLLHINTS
		if(m_GI->m_enableHScrollHints)
		{
			m_ctrl->m_CUGHint->Hide();				
		}
		#endif

		m_ctrl->SetLeftCol(nPos+m_GI->m_numLockCols);

		break;
	}
}