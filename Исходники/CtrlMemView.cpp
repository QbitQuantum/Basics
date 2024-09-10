void CtrlMemView::onVScroll(WPARAM wParam, LPARAM lParam)
{
	switch (wParam & 0xFFFF)
	{
	case SB_LINEDOWN:
		scrollWindow(1);
		break;
	case SB_LINEUP:
		scrollWindow(-1);
		break;
	case SB_PAGEDOWN:
		scrollWindow(visibleRows);
		break;
	case SB_PAGEUP:
		scrollWindow(-visibleRows);
		break;
	default:
		return;
	}
}