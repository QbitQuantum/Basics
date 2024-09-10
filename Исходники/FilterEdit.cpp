CSize CFilterEdit::GetIconSize(HICON hIcon)
{
	CSize size(0, 0);
	ICONINFO iconinfo;
	if (GetIconInfo(hIcon, &iconinfo))
	{
		BITMAP bmp;
		if (GetObject(iconinfo.hbmColor, sizeof(BITMAP), &bmp))
		{
			size.cx = bmp.bmWidth;
			size.cy = bmp.bmHeight;
		}
	}
	return size;
}