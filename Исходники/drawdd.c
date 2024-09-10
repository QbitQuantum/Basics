static void blit_to_primary(win_window_info *window, int srcwidth, int srcheight)
{
	dd_info *dd = (dd_info *)window->drawdata;
	IDirectDrawSurface7 *target = (dd->back != NULL) ? dd->back : dd->primary;
	win_monitor_info *monitor = winwindow_video_window_monitor(window, NULL);
	DDBLTFX blitfx = { sizeof(DDBLTFX) };
	RECT clear, outer, dest, source;
	INT32 dstwidth, dstheight;
	HRESULT result;

	// compute source rect
	source.left = source.top = 0;
	source.right = srcwidth;
	source.bottom = srcheight;

	// compute outer rect -- windowed version
	if (!window->fullscreen)
	{
		GetClientRect(window->hwnd, &outer);
		ClientToScreen(window->hwnd, &((LPPOINT)&outer)[0]);
		ClientToScreen(window->hwnd, &((LPPOINT)&outer)[1]);

		// adjust to be relative to the monitor
		outer.left -= monitor->info.rcMonitor.left;
		outer.right -= monitor->info.rcMonitor.left;
		outer.top -= monitor->info.rcMonitor.top;
		outer.bottom -= monitor->info.rcMonitor.top;
	}

	// compute outer rect -- full screen version
	else
	{
		calc_fullscreen_margins(window, dd->primarydesc.dwWidth, dd->primarydesc.dwHeight, &outer);
	}

	// if we're respecting the aspect ratio, we need to adjust to fit
	dstwidth = rect_width(&outer);
	dstheight = rect_height(&outer);
	if (!video_config.hwstretch)
	{
		// trim the source if necessary
		if (rect_width(&outer) < srcwidth)
		{
			source.left += (srcwidth - rect_width(&outer)) / 2;
			source.right = source.left + rect_width(&outer);
		}
		if (rect_height(&outer) < srcheight)
		{
			source.top += (srcheight - rect_height(&outer)) / 2;
			source.bottom = source.top + rect_height(&outer);
		}

		// match the destination and source sizes
		dstwidth = srcwidth = source.right - source.left;
		dstheight = srcheight = source.bottom - source.top;
	}
	else if (video_config.keepaspect)
	{
		// compute the appropriate visible area
		window->target->compute_visible_area(rect_width(&outer), rect_height(&outer), winvideo_monitor_get_aspect(monitor), window->target->orientation(), dstwidth, dstheight);
	}

	// center within
	dest.left = outer.left + (rect_width(&outer) - dstwidth) / 2;
	dest.right = dest.left + dstwidth;
	dest.top = outer.top + (rect_height(&outer) - dstheight) / 2;
	dest.bottom = dest.top + dstheight;

	// compare against last destination; if different, force a redraw
	if (dest.left != dd->lastdest.left || dest.right != dd->lastdest.right || dest.top != dd->lastdest.top || dest.bottom != dd->lastdest.bottom)
	{
		dd->lastdest = dest;
		update_outer_rects(dd);
	}

	// clear outer rects if we need to
	if (dd->clearouter != 0)
	{
		dd->clearouter--;

		// clear the left edge
		if (dest.left > outer.left)
		{
			clear = outer;
			clear.right = dest.left;
			result = IDirectDrawSurface_Blt(target, &clear, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &blitfx);
			if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X clearing the screen\n", (int)result);
		}

		// clear the right edge
		if (dest.right < outer.right)
		{
			clear = outer;
			clear.left = dest.right;
			result = IDirectDrawSurface_Blt(target, &clear, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &blitfx);
			if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X clearing the screen\n", (int)result);
		}

		// clear the top edge
		if (dest.top > outer.top)
		{
			clear = outer;
			clear.bottom = dest.top;
			result = IDirectDrawSurface_Blt(target, &clear, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &blitfx);
			if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X clearing the screen\n", (int)result);
		}

		// clear the bottom edge
		if (dest.bottom < outer.bottom)
		{
			clear = outer;
			clear.top = dest.bottom;
			result = IDirectDrawSurface_Blt(target, &clear, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &blitfx);
			if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X clearing the screen\n", (int)result);
		}
	}

	// do the blit
	result = IDirectDrawSurface7_Blt(target, &dest, dd->blit, &source, DDBLT_WAIT, NULL);
	if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X blitting to the screen\n", (int)result);

	// page flip if triple buffered
	if (window->fullscreen && dd->back != NULL)
	{
		result = IDirectDrawSurface7_Flip(dd->primary, NULL, DDFLIP_WAIT);
		if (result != DD_OK) mame_printf_verbose("DirectDraw: Error %08X waiting for VBLANK\n", (int)result);
	}
}