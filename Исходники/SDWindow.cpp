CSDWindow::CSDWindow(POINT point, SIZE size)
{
	CRect rectTemp(point, size);

	CopyRect(rectTemp);
}