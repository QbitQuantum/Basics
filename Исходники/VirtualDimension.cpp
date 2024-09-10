LRESULT VirtualDimension::OnLeftButtonUp(HWND /*hWnd*/, UINT /*message*/, WPARAM /*wParam*/, LPARAM lParam)
{
	POINT pt;

	//If not dragging a window, nothing to do
	if (m_draggedWindow == NULL)
		return 0;

	//Release capture
	ReleaseCapture();

	//Free the cursor
	DestroyCursor(m_dragCursor);

	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);

	//Find out the target desktop
	Desktop * desk = deskMan->GetDesktopFromPoint(pt.x, pt.y);
	if (m_draggedWindow->IsOnDesk(desk))
		return 0;	//window already on the target desk

	//Move the window to this desktop
	m_draggedWindow->MoveToDesktop(desk);

	//Refresh the window
	Refresh();

	return 0;
}