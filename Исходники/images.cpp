HICON BindOverlayIcon(HICON SourceIcon,HICON OverlayIcon)
{
	ICONINFO OverlayIconInfo, TargetIconInfo;
	BITMAP OverlayBitmapInfo, TargetBitmapInfo;
	HBITMAP OldOverlayBitmap, OldTargetBitmap;
	HICON TargetIcon, TempIcon;
	HDC OverlayDC, TargetDC;
	BLENDFUNCTION bf = {0,0,255,1};

	TempIcon = CopyIcon(SourceIcon);
	if ( !GetIconInfo( TempIcon, &TargetIconInfo ))
		return NULL;

	MakeBitmap32(&TargetIconInfo.hbmColor);
	CorrectBitmap32Alpha(TargetIconInfo.hbmColor, FALSE);
	GetObject(TargetIconInfo.hbmColor, sizeof(BITMAP), &TargetBitmapInfo);

	if ( !GetIconInfo(OverlayIcon, &OverlayIconInfo) || !GetObject(OverlayIconInfo.hbmColor, sizeof(BITMAP), &OverlayBitmapInfo))
		return NULL;

	TargetDC = CreateCompatibleDC(NULL);
	OldTargetBitmap = (HBITMAP)SelectObject(TargetDC, TargetIconInfo.hbmColor);

	OverlayDC = CreateCompatibleDC(NULL);
	OldOverlayBitmap = (HBITMAP)SelectObject(OverlayDC, OverlayIconInfo.hbmColor);

	AlphaBlend(TargetDC, 0, 0, TargetBitmapInfo.bmWidth, TargetBitmapInfo.bmHeight,
		   OverlayDC, 0, 0, OverlayBitmapInfo.bmWidth, OverlayBitmapInfo.bmHeight, bf);

	SelectObject(TargetDC, TargetIconInfo.hbmMask);
	SelectObject(OverlayDC, OverlayIconInfo.hbmMask);

	BitBlt(TargetDC, 0, 0, TargetBitmapInfo.bmWidth, TargetBitmapInfo.bmHeight,
	       OverlayDC, 0, 0, SRCCOPY);

	TargetIcon = CreateIconIndirect(&TargetIconInfo);
	DestroyIcon(TempIcon);

	SelectObject(TargetDC, OldTargetBitmap);
	DeleteObject(TargetIconInfo.hbmColor);
	DeleteObject(TargetIconInfo.hbmMask);
	DeleteDC(TargetDC);

	SelectObject(OverlayDC, OldOverlayBitmap);
	DeleteObject(OverlayIconInfo.hbmColor);
	DeleteObject(OverlayIconInfo.hbmMask);
	DeleteDC(OverlayDC);

	return TargetIcon;
}