void WinCopyRectangle (int left, int top, int right, int bottom, int dx, int dy, OSPictContext context)
{
	RECT scrollRect;

	scrollRect.left   = left;
	scrollRect.top    = top;
	scrollRect.right  = right;
	scrollRect.bottom = bottom;

	if (!ScrollDC (context->hDC, dx,dy, &scrollRect, &scrollRect, NULL, NULL))
	{
		rMessageBox (NULL,MB_APPLMODAL,"WinCopyRectangle","ScrollDC failed");
	}
}	/* WinCopyRectangle */