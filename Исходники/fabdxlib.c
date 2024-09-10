//
// Print a text to the surface
//
VOID TextPrint(int x, int y, LPCSTR message)
{
	HRESULT hr;
	HDC hdc = NULL;

	// Get the device context handle.
	hr = IDirectDrawSurface_GetDC(ScreenVirtual,&hdc);
	if (hr != DD_OK)
		return;

	// Write the message.
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOutA(hdc, x, y, message, (int)strlen(message));

	// Release the device context.
	hr = IDirectDrawSurface_ReleaseDC(ScreenVirtual,hdc);
}