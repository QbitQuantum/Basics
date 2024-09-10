void CXTPCustomizeToolbarsPageCheckListBox::PreDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DRAWITEMSTRUCT drawItem;
	memcpy(&drawItem, lpDrawItemStruct, sizeof(DRAWITEMSTRUCT));

	if ((((LONG)drawItem.itemID) >= 0) &&
		((drawItem.itemAction & (ODA_DRAWENTIRE | ODA_SELECT)) != 0))
	{
		int cyItem = GetItemHeight(drawItem.itemID);

		CDC* pDC = CDC::FromHandle(drawItem.hDC);

		int nCheck = GetCheck(drawItem.itemID);

		CRect rectCheck = drawItem.rcItem;
		rectCheck.left += 1;
		rectCheck.top += 1 + max(0, (cyItem - m_sizeCheck.cy) / 2);
		rectCheck.right = rectCheck.left + m_sizeCheck.cx;
		rectCheck.bottom = rectCheck.top + m_sizeCheck.cy;

		CRect rectItem = drawItem.rcItem;
		rectItem.right = rectItem.left + m_sizeCheck.cx + 2;
		CRect rectCheckBox = OnGetCheckPosition(rectItem, rectCheck);

		if (m_themeHelper.IsAppThemeReady())
		{
			m_themeHelper.DrawThemeBackground(pDC->m_hDC, BP_CHECKBOX,
				nCheck ? CBS_CHECKEDNORMAL : CBS_UNCHECKEDNORMAL, &rectCheckBox, NULL);
		}
		else
		{
			ASSERT(rectCheck.IntersectRect(rectItem, rectCheckBox));
			ASSERT((rectCheck == rectCheckBox) && (rectCheckBox.Size() == m_sizeCheck));

			pDC->DrawFrameControl(rectCheckBox, DFC_BUTTON, DFCS_BUTTONCHECK | (nCheck ? DFCS_CHECKED : 0));
		}
	}

	drawItem.rcItem.left = drawItem.rcItem.left + m_sizeCheck.cx + 3;

	DrawItem(&drawItem);
}