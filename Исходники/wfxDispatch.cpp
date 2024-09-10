BOOL Dispatcher::destroy( HWID& hWid )
{
	std::map<HWID, Widget*>::iterator it =
		m_Handle2Object.find(hWid);
	if (it == m_Handle2Object.end())
	{
		return FALSE;
	}
	Widget* pWid = it->second;
	WFX_CONDITION(pWid != NULL);
	Widget* pParent = pWid->getParent();
	if (pParent != NULL)
	{
		pParent->removeChild(pWid);
	}
	m_Handle2Object.erase(it);
	std::map<HWID, Widget*>::iterator itPaint = 
		m_h2oOrphan.find(hWid);
	if (itPaint != m_h2oOrphan.end())
	{
		m_h2oOrphan.erase(itPaint);
	}
	if (m_h2oCaptured.first == hWid)
	{
		clearH2O(m_h2oCaptured);
	}
	m_pTimer->destroy(pWid);
	recycleHwid(hWid);
	return TRUE;
}