void CATextView::setContentSize(const DSize& contentSize)
{
    CAView::setContentSize(contentSize);
    
	if (m_pBackgroundView)
	{
		m_pBackgroundView->setFrame(this->getBounds());
	}
	if (m_pShowImageView)
	{
		m_pShowImageView->setFrame(this->getBounds());
	}
	if (m_pTextView)
	{
		DRect r = this->getBounds();
		r.InflateRect(-5);
		((CATextViewWin32*)m_pTextView)->setFrame(r);
	}
}