void CBSumCaret::CaretPos()
{
	SetCaretPos ( (int)(m_XPosition - m_ScrollXPosition), (int)(m_YPosition - m_ScrollYPosition) );
	// for status bar updates
}