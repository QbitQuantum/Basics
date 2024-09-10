void TaskSortFieldSelector::OnShow(WPARAM wParam, LPARAM lParam)
{
	if(wParam && !lParam)
	{
		AnimateWindow(m_hwnd, 300, AW_BLEND);
	}
	else
	{
		AnimateWindow(m_hwnd, 200, AW_BLEND | AW_HIDE);
	}
}