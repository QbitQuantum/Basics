TaskArea::TaskArea(bool pVertical, LPCSTR p_itemName): Collection(pVertical, p_itemName, 0, 2),
		stretchTaskarea(s_settingsManager.AssociateBool(m_pluginPrefix, m_itemPrefix, "Stretch", true)),
		m_basePrefix(p_itemName)
{
	m_basePrefix.resize(m_basePrefix.find_first_of("."));
	m_dragTask = NULL;
	m_dragTimer = getTimerID();
	readSettings();
	populateTasks();
	m_dropTarget = new DropTarget(this, DragAction);
	RegisterDragDrop(barWnd, m_dropTarget);

}