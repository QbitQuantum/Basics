// call before the bar window is destroyed
void exit_drop_targ (class TinyDropTarget *m_TinyDropTarget)
{
	RevokeDragDrop(m_TinyDropTarget->m_hwnd);
	m_TinyDropTarget->Release();
}