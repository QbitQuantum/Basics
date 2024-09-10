void OverlayControl::MouseUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (!ActiveOverlay)
		return;

	//	Release mouse.
	ClipCursor(0);
	ReleaseCapture();
	ResetCursor();
}