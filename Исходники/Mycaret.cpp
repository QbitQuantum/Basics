void CBaseCaret::CaretPos()
{
	SetCaretPos ( (int)(m_XPosition - m_ScrollXPosition), (int)(m_YPosition - m_ScrollYPosition) );
	// for status bar updates
//	TRACE ( "CaretPos: X = %d, Y = %d\n", (int)(m_XPosition - m_ScrollXPosition), (int)(m_YPosition - m_ScrollYPosition) );
}