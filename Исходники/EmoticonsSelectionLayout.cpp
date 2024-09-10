void EmoticonsSelectionLayout::DrawEmoticon(HDC hdc, int index, RECT fullRc)
{	
	Emoticon *e = ssd->module->emoticons[index];

	int width, height;
	GetEmoticonSize(e, width, height);

	RECT rc = fullRc;
	rc.left += (rc.right - rc.left - width) / 2;
	rc.top += (rc.bottom - rc.top - height) / 2;
	rc.right = rc.left + width;
	rc.bottom = rc.top + height;

	if (e->img == NULL || e->img->img == NULL)
	{
		if (e->texts.getCount() > 0)
		{
			DrawEmoticonText(hdc, e->texts[0], rc);
		}
		else
		{
			DrawEmoticonText(hdc, e->description, rc);
		}
	}
	else
	{
		HDC hdc_img = CreateCompatibleDC(hdc);
		HBITMAP old_bmp = (HBITMAP) SelectObject(hdc_img, e->img->img);

		if (e->img->transparent)
		{
			BLENDFUNCTION bf = {0};
			bf.SourceConstantAlpha = 255;
			bf.AlphaFormat = AC_SRC_ALPHA;
			AlphaBlend(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
				hdc_img, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
		}
		else
		{
			BitBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
				hdc_img, 0, 0, SRCCOPY);
		}

		SelectObject(hdc_img, old_bmp);
		DeleteDC(hdc_img);
	}

	if (selection == index)
	{
		rc = fullRc;
		rc.left -= 2;
		rc.right += 2;
		rc.top -= 2;
		rc.bottom += 2;
		FrameRect(hdc, &rc, (HBRUSH) GetStockObject(GRAY_BRUSH));
	}
}