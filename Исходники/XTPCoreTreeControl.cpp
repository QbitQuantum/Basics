BOOL CXTPCoreTreeControl::DragItem(CXTPCoreTreeItem* pItem, DROPEFFECT dropEffectMask)
{
	ASSERT(pItem);
	if (!pItem)
		return FALSE;

	COleDataSource ds;
	if (!pItem->PrepareDrag(ds))
		return FALSE;

	m_pDraggingItem = pItem;


	DROPEFFECT dropEffect = ds.DoDragDrop(dropEffectMask);

	BOOL bRemoved = FALSE;

	if ((dropEffect == DROPEFFECT_MOVE) && (dropEffectMask & DROPEFFECT_MOVE))
	{
		if (m_pDraggingItem)
		{
			m_pDraggingItem->Remove();
			bRemoved = TRUE;
		}
	}


	m_pDraggingItem = NULL;

	return bRemoved;
}