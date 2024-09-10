void FreeFinderResources()
{
	DeleteObject(hBitmapDrag1);
	DeleteObject(hBitmapDrag2);

	DestroyCursor(hCursor);
}