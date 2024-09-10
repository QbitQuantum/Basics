BOOL ImageArray_DrawImage(IMAGE_ARRAY_DATA *iad, int pos, HDC hdcDest, int nXDest, int nYDest, BYTE Alpha)
{
	if (hdcDest == NULL || pos < 0 || pos >= iad->nodes_size)
		return FALSE;

	EnterCriticalSection(&iad->cs);
	{
		int w, h, i;

		if (iad->width_based) {
			w = 0;
			h = 0;
			for (i = 0; i < pos; i++) {
				h += iad->nodes[i].height;
			}
		}
		else {
			h = 0;
			w = 0;
			for (i = 0; i < pos; i++) {
				w += iad->nodes[i].width;
			}
		}

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, Alpha, AC_SRC_ALPHA };
		AlphaBlend(hdcDest, nXDest, nYDest, iad->nodes[pos].width, iad->nodes[pos].height, iad->hdc, w, h, iad->nodes[pos].width, iad->nodes[pos].height, bf);
	}

	LeaveCriticalSection(&iad->cs);
	return FALSE;
}