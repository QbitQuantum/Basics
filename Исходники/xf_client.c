void xf_window_free(xfContext* xfc)
{
	if (xfc->gc_mono)
	{
		XFreeGC(xfc->display, xfc->gc_mono);
		xfc->gc_mono = 0;
	}

	if (xfc->window)
	{
		xf_DestroyDesktopWindow(xfc, xfc->window);
		xfc->window = NULL;
	}

	if (xfc->hdc)
	{
		gdi_DeleteDC(xfc->hdc);
		xfc->hdc = NULL;
	}

	if (xfc->xv_context)
	{
		xf_tsmf_uninit(xfc, NULL);
		xfc->xv_context = NULL;
	}

	if (xfc->bitmap_buffer)
	{
		_aligned_free(xfc->bitmap_buffer);
		xfc->bitmap_buffer = NULL;
		xfc->bitmap_size = 0;
	}

	if (xfc->image)
	{
		xfc->image->data = NULL;
		XDestroyImage(xfc->image);
		xfc->image = NULL;
	}

	if (xfc->bitmap_mono)
	{
		XFreePixmap(xfc->display, xfc->bitmap_mono);
		xfc->bitmap_mono = 0;
	}

	if (xfc->primary)
	{
		XFreePixmap(xfc->display, xfc->primary);
		xfc->primary = 0;
	}

	if (xfc->gc)
	{
		XFreeGC(xfc->display, xfc->gc);
		xfc->gc = 0;
	}

	if (xfc->modifierMap)
	{
		XFreeModifiermap(xfc->modifierMap);
		xfc->modifierMap = NULL;
	}
}