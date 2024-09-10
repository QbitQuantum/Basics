bool ISimpleDropTarget::Unregister()
{
	RevokeDragDrop(m_hwnd);
	OleUninitialize();
	m_hwnd = NULL;
	return true;
}