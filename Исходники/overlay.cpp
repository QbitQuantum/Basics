void OverlayFunctions::CreateWindowOverlay()
{
	Overlay.Window = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, Overlay.Name, Overlay.Name, WS_POPUP, 1, 1, Overlay.Width, Overlay.Height, 0, 0, hInstance, 0);
	SetLayeredWindowAttributes(Overlay.Window, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
	ShowWindow(Overlay.Window, SW_SHOW);
	DwmExtendFrameIntoClientArea(Overlay.Window, &Overlay.Margin);
}