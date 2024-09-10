CSize vmsUiLinkWindow::getSize() const
{
	CDC *pdc = getDC ();
	if (pdc == NULL)
	{
		return CSize (0,0);
	}

	CFont *pfntOld = pdc->SelectObject (m_pfntLnk ? m_pfntLnk : vmsUiFonts::Tahoma_11underline ());

	CSize s;

	if (m_uDrawTextFormat == 0)
	{
		s = pdc->GetTextExtent (m_tstrText.c_str ());
	}
	else
	{
		CRect rc = m_rcPos;
		pdc->DrawText (m_tstrText.c_str (), &rc, DT_CALCRECT | m_uDrawTextFormat);
		s = CSize (rc.Width (), rc.Height ());
	}

	pdc->SelectObject (pfntOld);
	releaseDC (pdc);

	return s;
}