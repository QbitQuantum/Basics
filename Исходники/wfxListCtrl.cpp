LONG HeaderCtrl::getSelected( POINT pt )
{
	LONG nStartCol = sendParentMessage(WUM_LC_GET_PROPERTIES, LCP_START_COL);
	LONG nEndCol = sendParentMessage(WUM_LC_GET_PROPERTIES, LCP_END_COL);
	Rect rcItem;
	for (LONG nCol = nStartCol; nCol <= nEndCol; nCol++)
	{
		rcItem = m_rgpHdi[nCol]->rcPos;
		if (rcItem.PtInRect(pt))
		{
			return nCol;
		}
	}
	return -1;
}