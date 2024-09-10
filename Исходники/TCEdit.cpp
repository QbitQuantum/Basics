void CTCEdit::TCSetVertiScroll(bool set)
{
	m_Verti = set;
	if(m_isMulityLine && m_Verti)
		ShowScrollBar(SB_VERT,TRUE);
	else
		ShowScrollBar(SB_VERT,FALSE);
}