// Similar to DrawText win32 api function
// Pass uFormat | DT_CALCRECT to calc rectangle to be returned by lpRect
// parseInfo is optional (pass NULL and it will be calculated and deleted inside function
int Smileys_DrawText(HDC hDC, LPCTSTR lpString, int nCount, LPRECT lpRect, UINT uFormat, const char *protocol, SmileysParseInfo parseInfo)
{
	SmileysParseInfo info;
	int ret;

	if (nCount < 0)
		nCount = (int)mir_tstrlen(lpString);

	// Get parse info
	if (parseInfo == NULL)
		info = Smileys_PreParse(lpString, nCount, protocol);
	else
		info = parseInfo;

	if (uFormat & DT_CALCRECT)
	{
		SIZE text_size = GetTextSize(hDC, lpString, info->pieces, uFormat, info->max_height);

		lpRect->bottom = min(lpRect->bottom, lpRect->top + text_size.cy);

		if (text_size.cx < lpRect->right - lpRect->left)
		{
			if (uFormat & DT_RIGHT)
				lpRect->left = lpRect->right - text_size.cx;
			else
				lpRect->right = lpRect->left + text_size.cx;
		}

		ret = text_size.cy;
	}
	else
	{
		// Clipping rgn
		HRGN oldRgn = CreateRectRgn(0, 0, 1, 1);
		if (GetClipRgn(hDC, oldRgn) != 1)
		{
			DeleteObject(oldRgn);
			oldRgn = NULL;
		}

		HRGN rgn = CreateRectRgnIndirect(lpRect);
		ExtSelectClipRgn(hDC, rgn, RGN_AND);

		// Draw
		if (info->pieces == NULL)
		{
			ret = skin_DrawText(hDC, lpString, nCount, lpRect, uFormat);
		}
		else
		{
			RECT rc = *lpRect;

			SIZE text_size = GetTextSize(hDC, lpString, info->pieces, uFormat, info->max_height);

			if (text_size.cx < rc.right - rc.left)
			{
				if (uFormat & DT_RIGHT)
					rc.left = rc.right - text_size.cx;
				else
					rc.right = rc.left + text_size.cx;
			}

			ret = text_size.cy;

			DrawTextSmiley(hDC, rc, lpString, nCount, info->pieces, uFormat, info->max_height);
		}

		// Clipping rgn
		SelectClipRgn(hDC, oldRgn);
		DeleteObject(rgn);
		if (oldRgn) DeleteObject(oldRgn);
	}


	// Free parse info
	if (parseInfo == NULL)
		Smileys_FreeParse(info);

	return ret;
}