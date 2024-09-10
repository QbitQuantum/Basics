void CPropPageFrame::Draw(CDC *pDc)
{
	if (GetShowCaption())
		DrawCaption(pDc, CalcCaptionArea(), m_strCaption, m_hCaptionIcon);
	DrawMsg(pDc, CalcMsgArea(), m_strMsg, m_dwMsgFormat);
}