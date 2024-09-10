	void CModelFormItem::DrawField(CPaintDC & dc)
	{
		CRect rectItem;
		GetClientRect(rectItem);
		int eff = m_param.GetEndFirstField();
		int bsf = m_param.GetBeginSecondField();

		dc.MoveTo(eff, rectItem.top + 2);
		dc.LineTo(eff, rectItem.bottom - 2);
		dc.MoveTo(bsf, rectItem.top + 2);
		dc.LineTo(bsf, rectItem.bottom - 2);

	}