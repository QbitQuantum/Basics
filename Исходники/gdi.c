static BOOL gdi_mem3blt(rdpContext* context, MEM3BLT_ORDER* mem3blt)
{
	BYTE* data;
	rdpBrush* brush;
	UINT32 foreColor;
	UINT32 backColor;
	gdiBitmap* bitmap;
	GDI_COLOR originalColor;
	HGDI_BRUSH originalBrush;
	rdpGdi* gdi = context->gdi;
	BOOL ret = TRUE;

	brush = &mem3blt->brush;
	bitmap = (gdiBitmap*) mem3blt->bitmap;

	foreColor = freerdp_convert_gdi_order_color(mem3blt->foreColor, gdi->srcBpp, gdi->format, gdi->palette);
	backColor = freerdp_convert_gdi_order_color(mem3blt->backColor, gdi->srcBpp, gdi->format, gdi->palette);

	originalColor = gdi_SetTextColor(gdi->drawing->hdc, foreColor);

	if (brush->style == GDI_BS_SOLID)
	{
		originalBrush = gdi->drawing->hdc->brush;
		gdi->drawing->hdc->brush = gdi_CreateSolidBrush(foreColor);
		if (!gdi->drawing->hdc->brush)
		{
			ret = FALSE;
			goto out_fail;
		}

		gdi_BitBlt(gdi->drawing->hdc, mem3blt->nLeftRect, mem3blt->nTopRect,
				mem3blt->nWidth, mem3blt->nHeight, bitmap->hdc,
				mem3blt->nXSrc, mem3blt->nYSrc, gdi_rop3_code(mem3blt->bRop));

		gdi_DeleteObject((HGDIOBJECT) gdi->drawing->hdc->brush);
		gdi->drawing->hdc->brush = originalBrush;
	}
	else if (brush->style == GDI_BS_PATTERN)
	{
		HGDI_BITMAP hBmp;
		UINT32 brushFormat;

		if (brush->bpp > 1)
		{
			brushFormat = gdi_get_pixel_format(brush->bpp, FALSE);

			data = (BYTE*) _aligned_malloc(8 * 8 * gdi->bytesPerPixel, 16);
			if (!data)
			{
				ret = FALSE;
				goto out_fail;
			}

			freerdp_image_copy(data, gdi->format, -1, 0, 0,
					8, 8, brush->data, brushFormat, -1, 0, 0, gdi->palette);
		}
		else
		{
			data = (BYTE*) _aligned_malloc(8 * 8 * gdi->bytesPerPixel, 16);
			if (!data)
			{
				ret = FALSE;
				goto out_fail;
			}

			freerdp_image_copy_from_monochrome(data, gdi->format, -1, 0, 0, 8, 8,
					brush->data, backColor, foreColor, gdi->palette);
		}

		hBmp = gdi_CreateBitmap(8, 8, gdi->drawing->hdc->bitsPerPixel, data);
		if (!hBmp)
		{
			_aligned_free(data);
			ret = FALSE;
			goto out_fail;
		}

		originalBrush = gdi->drawing->hdc->brush;
		gdi->drawing->hdc->brush = gdi_CreatePatternBrush(hBmp);
		if (!gdi->drawing->hdc->brush)
		{
			gdi_DeleteObject((HGDIOBJECT) hBmp);
			goto out_fail;
		}
		gdi->drawing->hdc->brush->nXOrg = brush->x;
		gdi->drawing->hdc->brush->nYOrg = brush->y;

		gdi_BitBlt(gdi->drawing->hdc, mem3blt->nLeftRect, mem3blt->nTopRect,
				mem3blt->nWidth, mem3blt->nHeight, bitmap->hdc,
				mem3blt->nXSrc, mem3blt->nYSrc, gdi_rop3_code(mem3blt->bRop));

		gdi_DeleteObject((HGDIOBJECT) gdi->drawing->hdc->brush);
		gdi->drawing->hdc->brush = originalBrush;
	}
	else
	{
		WLog_ERR(TAG,  "Mem3Blt unimplemented brush style:%d", brush->style);
	}

out_fail:
	gdi_SetTextColor(gdi->drawing->hdc, originalColor);
	return ret;
}