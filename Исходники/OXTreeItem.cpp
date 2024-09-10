BOOL COXTreeItem::Expand(UINT nCode,COXTreeCtrl *pCtrl)
{

	ASSERT(pCtrl!=NULL);

	BOOL bWasVisible=IsVisible();

	switch(nCode)
	{
		case TVE_TOGGLE:
			m_bExpand = !m_bExpand;
			break;

		case TVE_COLLAPSE:
			if(!m_bExpand)
			{
				TRACE(_T("COXTreeItem::Expand: the item is already in collapsed state!\n"));
				return TRUE;
			}
			m_bExpand = FALSE;
			break;

		case TVE_EXPAND:
			if(m_bExpand)
			{
				TRACE(_T("COXTreeItem::Expand: the item is already in expanded state!\n"));
				return TRUE;
			}
			m_bExpand = TRUE;
			break;
		
		case TVE_COLLAPSERESET:
			pCtrl->DeleteChildrenItems(this);
			m_bExpand=FALSE;
			m_bExpandedOnce=FALSE;
			m_tvi.cChildren=0;
			return TRUE;
		
		default:
			TRACE(_T("COXTreeItem::Expand: unexpected case found!\n"));
			return FALSE;
	}
	
	if(m_bExpand)
		m_bExpandedOnce=TRUE;

	if(!bWasVisible && !m_bExpand)
		return TRUE;

	if(!IsVisible() && m_bExpand)
	{
		COXTreeItem* xtiParent=pxParent;
		ASSERT(xtiParent!=NULL && xtiParent!=&pCtrl->m_xtiRoot);
		xtiParent->Expand(TVE_EXPAND,pCtrl);
	}
	else
		Exp(pCtrl);
	
	return TRUE;
}