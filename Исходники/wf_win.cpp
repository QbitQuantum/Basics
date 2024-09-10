static RD_HCURSOR
l_ui_create_cursor(struct rdp_inst * inst, uint32 x, uint32 y,
	int width, int height, uint8 * andmask, uint8 * xormask, int bpp)
{
	wfInfo * wfi;
	HCURSOR cursor;
	ICONINFO iconinfo;
	uint8 * cdata;

	wfi = GET_WFI(inst);
	if (bpp == 1)
	{
		cursor = CreateCursor(g_hInstance, x, y, width, height, andmask, xormask);
	}
	else
	{
		iconinfo.fIcon = FALSE;
		iconinfo.xHotspot = x;
		iconinfo.yHotspot = y;
		cdata = wf_cursor_mask_convert(wfi, width, height, andmask);
		iconinfo.hbmMask = CreateBitmap(width, height, 1, 1, cdata);
		iconinfo.hbmColor = wf_create_dib(wfi, width, height, bpp, 0, xormask);
		cursor = CreateIconIndirect(&iconinfo);
		DeleteObject(iconinfo.hbmMask);
		DeleteObject(iconinfo.hbmColor);
		free(cdata);
	}
	return (RD_HCURSOR)cursor;
}