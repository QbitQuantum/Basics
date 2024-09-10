void CWidgetSplitter::DrawSplitterBar(CDCHandle dc)
{
TRY_CATCH

	RECT rect;
	if ( GetSplitterBarRect(&rect) )
	{
		RECT rc;
		GetClientRect(&rc);
		HRGN rgnWnd = CreateRectRgnIndirect(&rc);
		HRGN rgnBar = CreateRectRgnIndirect(&rect);
		CombineRgn(rgnWnd,rgnWnd,rgnBar,RGN_XOR);

		rc = rect;
		rc.left = rect.left + (rect.right - rect.left)/2;
		rc.right = rc.left + 1;

		HRGN rgnLine = CreateRectRgnIndirect(&rc);
		CombineRgn(rgnWnd,rgnWnd,rgnLine,RGN_OR);

		SetWindowRgn(rgnWnd,TRUE);

		DeleteObject(rgnBar);
		DeleteObject(rgnLine);
		DeleteObject(rgnWnd);

		dc.MoveTo(rc.left,rc.top);
		dc.LineTo(rc.left,rc.bottom);
	}

CATCH_THROW()
}