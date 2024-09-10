void onRenderFormat(HWND hWnd, WPARAM wParam, HBITMAP currentBitmap)
{
	if (wParam == CF_BITMAP)
	{
		HBITMAP newBitmap;
		newBitmap = (HBITMAP) CopyImage(currentBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		SetClipboardData(CF_BITMAP, newBitmap);
		//DeleteObject(newBitmap);
		
	}
}