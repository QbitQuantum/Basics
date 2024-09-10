void CEdgedWin::Redraw(const TRect& aRect)
	{
	iWsGc.Activate(*iWindow);
	iWsGc.Reset();
	iWsGc.SetPenStyle(iPenStyle);
	iWsGc.SetBrushStyle(iBrushStyle);
	TBool redraw = EFalse;
	//redraw outer rectangle if in rect
	if (aRect.iTl.iX < iOpaqueRect.iTl.iX ||
	    aRect.iTl.iY < iOpaqueRect.iTl.iY ||
	    aRect.iBr.iX > iOpaqueRect.iBr.iX ||
	    aRect.iBr.iY > iOpaqueRect.iBr.iY)
	    {
	    redraw = ETrue;
	    iRedrawWindow->BeginRedraw();
		iWsGc.SetPenColor(iTransFgColor);
		iWsGc.SetBrushColor(iTransBgColor);
		iWsGc.DrawRect(TRect(TPoint(0,0), iSize));
	//	iRedrawWindow->EndRedraw() will be taken care of below
	    }
	//redraw inner rectangle
	if (redraw || aRect.Intersects(iOpaqueRect))
		{
		if (!redraw)
			{
			iRedrawWindow->BeginRedraw(iOpaqueRect);//iOpaqueRect);
			}
		iWsGc.SetPenColor(iFgColor);
		iWsGc.SetBrushColor(iBgColor);
		iWsGc.DrawRect(iOpaqueRect);
		iRedrawWindow->EndRedraw();
		}
	iWsGc.Deactivate();
	}