// Change an image in the list (return TRUE on success)
BOOL ImageArray_ChangeImage(LP_IMAGE_ARRAY_DATA iad, HBITMAP hBmp, int pos)
{
	BITMAP bm;
	int new_width, new_height;
	HBITMAP hNewBmp;
	HDC hdc_old;
	int i;

	if (hBmp == NULL)
		return FALSE;

	if (pos < 0)
		return FALSE;

	if (pos >= iad->nodes_size)
		return FALSE;

	EnterCriticalSection(&iad->cs);

	// Get bounds
	if (!GetObject(hBmp,sizeof(BITMAP),&bm))
	{
		LeaveCriticalSection(&iad->cs);
		return FALSE;
	}

	if (iad->width_based)
	{
		new_width = max(bm.bmWidth, iad->width);
		new_height = iad->height + bm.bmHeight - iad->nodes[pos].height;
	}
	else
	{
		new_width = bm.bmWidth + iad->width - iad->nodes[pos].width;
		new_height = max(iad->height, bm.bmHeight);
	}

	// Alloc image
	hNewBmp = ImageArray_CreateBitmap(new_width, new_height);
	if (hNewBmp == NULL)
	{
		LeaveCriticalSection(&iad->cs);
		return FALSE;
	}
	
	// Move image...

	// Set some draw states
	SelectObject(iad->hdc, hNewBmp);
	hdc_old = CreateCompatibleDC(iad->hdc); 

	SetBkMode(iad->hdc, TRANSPARENT);
	{
		POINT org;
		GetBrushOrgEx(iad->hdc, &org);
		SetStretchBltMode(iad->hdc, HALFTONE);
		SetBrushOrgEx(iad->hdc, org.x, org.y, NULL);
	}

	{
		int x = 0, y = 0, w = 0, h = 0;

		// 1- old data
		if (pos > 0)
		{
			SelectObject(hdc_old, iad->img);

			if (iad->width_based)
			{
				w = iad->width;
				h = 0;
				for(i = 0; i < pos; i++)
				{
					h += iad->nodes[i].height;
				}
			}
			else
			{
				h = iad->height;
				w = 0;
				for(i = 0; i < pos; i++)
				{
					w += iad->nodes[i].width;
				}
			}
			BitBlt(iad->hdc, 0, 0, w, h, hdc_old, 0, 0, SRCCOPY);
		}

		// 2- new image
		if (iad->width_based)
		{
			x = 0;
			y = h;
		}
		else
		{
			x = w;
			y = 0;
		}
		SelectObject(hdc_old, hBmp);
		BitBlt(iad->hdc, x, y, bm.bmWidth, bm.bmHeight, hdc_old, 0, 0, SRCCOPY);

		// 3- old data
		if (pos < iad->nodes_size - 1)
		{
			int ox, oy;

			SelectObject(hdc_old, iad->img);

			if (iad->width_based)
			{
				ox = 0;
				oy = y + iad->nodes[pos].height;

				x = 0;
				y += bm.bmHeight;

				w = iad->width;
				h = iad->height - h - iad->nodes[pos].height;
			}
			else
			{
				ox = x + iad->nodes[pos].width;
				oy = 0;

				x += bm.bmWidth;
				y = 0;

				w = iad->width - w - iad->nodes[pos].width;
				h = iad->height;
			}
			BitBlt(iad->hdc, x, y, w, h, hdc_old, ox, oy, SRCCOPY);
		}
	}

	// restore things
	DeleteDC(hdc_old);
	if (iad->img != NULL) DeleteObject(iad->img);
	iad->img = hNewBmp;

	// Move array
	iad->nodes[pos].width = bm.bmWidth;
	iad->nodes[pos].height = bm.bmHeight;

	iad->width = new_width;
	iad->height = new_height;

	// Finished it!
	LeaveCriticalSection(&iad->cs);

	return pos;
}