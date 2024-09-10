//*******************************************************************************
BOOL CBCGPLinearGaugeImpl::HitTestValue(const CBCGPPoint& pt, double& dblValue, int nScale, BOOL bInsideGauge) const
{
	CBCGPGaugeScaleObject* pScale = GetScale(nScale);
	if (pScale == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	CBCGPRect rect = m_rect;
	rect.OffsetRect(-m_ptScrollOffset);

	if (m_bIsVertical)
	{
		rect.DeflateRect((pScale->m_dblOffsetFromFrame + m_nFrameSize) * m_sizeScaleRatio.cx, m_sizeMaxLabel.cy / 2 + (m_nFrameSize + 1) * m_sizeScaleRatio.cy);
	}
	else
	{
		rect.DeflateRect(m_sizeMaxLabel.cx / 2 + (m_nFrameSize + 1) * m_sizeScaleRatio.cx, (pScale->m_dblOffsetFromFrame + m_nFrameSize) * m_sizeScaleRatio.cy);
	}

	if (bInsideGauge && !rect.PtInRect(pt))
	{
		return FALSE;
	}

	if (m_bIsVertical)
	{
		const double dblTotalSize = rect.Height();
		dblValue = pScale->m_dblStart + (rect.bottom - pt.y) * fabs(pScale->m_dblFinish - pScale->m_dblStart) / dblTotalSize;
	}
	else
	{
		const double dblTotalSize = rect.Width();
		dblValue = pScale->m_dblStart + (pt.x - rect.left) * fabs(pScale->m_dblFinish - pScale->m_dblStart) / dblTotalSize;
	}

	return TRUE;
}