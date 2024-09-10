void CKeyControl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu rbMenu;
	rbMenu.CreatePopupMenu();

	CLinkListNode<KEY> *pNode = PtInKey(point);
	
	if (pNode)
	{
		rbMenu.AppendMenu(MF_STRING, 5000, "&Edit Key");
		if ((pNode->m_pPrev) && (pNode->m_pNext))
		{
			rbMenu.AppendMenu(MF_SEPARATOR, 5001, "");
			rbMenu.AppendMenu(MF_STRING, 5002, "&Delete Key");
		}
		
		m_pMenuKey = pNode;			

		ClientToScreen(&point);
		rbMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}

	
	CStatic::OnRButtonDown(nFlags, point);
}