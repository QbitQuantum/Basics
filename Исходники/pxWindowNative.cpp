void pxWindow::setVisibility(bool visible)
{
	if (visible) ShowWindow(mWindowRef);
	else HideWindow(mWindowRef);
}