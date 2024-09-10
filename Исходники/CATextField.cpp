void CATextField::setContentSize(const DSize& contentSize)
{
    CAView::setContentSize(contentSize);

	if (m_pTextField)
	{
		DRect r = this->getBounds();
		r.InflateRect(-m_iMarginLeft, 0, -m_iMarginRight, 0);
		((CATextFieldWin32*)m_pTextField)->setFrame(r);
	}
}