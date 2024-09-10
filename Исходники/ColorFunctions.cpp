//give some 3D 
void Draw3DBorder(HDC hDC,RECT rRect,COLORREF clrDrawingColor,bool bSinked)
{
	HPEN hPenHilight,hPenShadow; 
	int iSaveDCState;
	iSaveDCState=SaveDC(hDC);

	if (!bSinked)
	{
		hPenHilight=CreatePen(PS_SOLID,1,ColorAdjustLuma(clrDrawingColor,400));
		hPenShadow=CreatePen(PS_SOLID,1,ColorAdjustLuma(clrDrawingColor,-400));
		
	}
	else
	{
		hPenHilight=CreatePen(PS_SOLID,1,ColorAdjustLuma(clrDrawingColor,-400));
		hPenShadow=CreatePen(PS_SOLID,1,ColorAdjustLuma(clrDrawingColor,400));
	}

	MoveToEx(hDC,rRect.left,rRect.bottom,NULL);
		
	SelectObject(hDC,hPenHilight);
	LineTo(hDC,rRect.left,rRect.top);
	LineTo(hDC,rRect.right,rRect.top);

	SelectObject(hDC,hPenShadow);
	LineTo(hDC,rRect.right,rRect.bottom);
	LineTo(hDC,rRect.left,rRect.bottom);

	DeleteObject(hPenHilight);
	DeleteObject(hPenShadow);

	//clean up and return
	RestoreDC(hDC,iSaveDCState);

}