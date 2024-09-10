	/**
	 * @brief   Scroll vertically a section of the screen.
	 * @note    Optional.
	 * @note    If x,y + cx,cy is off the screen, the result is undefined.
	 * @note    If lines is >= cy, it is equivelent to a area fill with bgcolor.
	 *
	 * @param[in] x, y     The start of the area to be scrolled
	 * @param[in] cx, cy   The size of the area to be scrolled
	 * @param[in] lines    The number of lines to scroll (Can be positive or negative)
	 * @param[in] bgcolor  The color to fill the newly exposed area.
	 *
	 * @notapi
	 */
	void GDISP_LLD(verticalscroll)(coord_t x, coord_t y, coord_t cx, coord_t cy, int lines, color_t bgcolor) {
		RECT	rect, frect, srect;
		HBRUSH	hbr;
		
		#if GDISP_NEED_VALIDATION || GDISP_NEED_CLIP
			// Clip pre orientation change
			if (x < GDISP.clipx0) { cx -= GDISP.clipx0 - x; x = GDISP.clipx0; }
			if (y < GDISP.clipy0) { cy -= GDISP.clipy0 - y; y = GDISP.clipy0; }
			if (!lines || cx <= 0 || cy <= 0 || x >= GDISP.clipx1 || y >= GDISP.clipy1) return;
			if (x+cx > GDISP.clipx1)	cx = GDISP.clipx1 - x;
			if (y+cy > GDISP.clipy1)	cy = GDISP.clipy1 - y;
		#endif
		
		if (lines > cy) lines = cy;
		else if (-lines > cy) lines = -cy;

		bgcolor = COLOR2BGR(bgcolor);
		hbr = CreateSolidBrush(bgcolor);

		#if GDISP_NEED_CONTROL
			switch(GDISP.Orientation) {
			case GDISP_ROTATE_0:
				rect.top = y;
				rect.bottom = rect.top+cy;
				rect.left = x;
				rect.right = rect.left+cx;
				lines = -lines;
				goto vertical_scroll;
			case GDISP_ROTATE_90:
				rect.top = x;
				rect.bottom = rect.top+cx;
				rect.right = GDISP.Height - y;
				rect.left = rect.right-cy;
				goto horizontal_scroll;
			case GDISP_ROTATE_180:
				rect.bottom = GDISP.Height - y;
				rect.top = rect.bottom-cy;
				rect.right = GDISP.Width - x;
				rect.left = rect.right-cx;
			vertical_scroll:
				srect.left = frect.left = rect.left;
				srect.right = frect.right = rect.right;
				if (lines > 0) {
					srect.top = frect.top = rect.top;
					frect.bottom = rect.top+lines;
					srect.bottom = rect.bottom-lines;
				} else {
					srect.bottom = frect.bottom = rect.bottom;
					frect.top = rect.bottom+lines;
					srect.top = rect.top-lines;
				}
				if (cy >= lines && cy >= -lines)
					ScrollDC(dcBuffer, 0, lines, &srect, 0, 0, 0);
				break;
			case GDISP_ROTATE_270:
				rect.bottom = GDISP.Width - x;
				rect.top = rect.bottom-cx;
				rect.left = y;
				rect.right = rect.left+cy;
				lines = -lines;
			horizontal_scroll:
				srect.top = frect.top = rect.top;
				srect.bottom = frect.bottom = rect.bottom;
				if (lines > 0) {
					srect.left = frect.left = rect.left;
					frect.right = rect.left+lines;
					srect.right = rect.right-lines;
				} else {
					srect.right = frect.right = rect.right;
					frect.left = rect.right+lines;
					srect.left = rect.left-lines;
				}
				if (cy >= lines && cy >= -lines)
					ScrollDC(dcBuffer, lines, 0, &srect, 0, 0, 0);
				break;
			}
		#else
			rect.top = y;
			rect.bottom = rect.top+cy;
			rect.left = x;
			rect.right = rect.left+cx;
			lines = -lines;
			srect.left = frect.left = rect.left;
			srect.right = frect.right = rect.right;
			if (lines > 0) {
				srect.top = frect.top = rect.top;
				frect.bottom = rect.top+lines;
				srect.bottom = rect.bottom-lines;
			} else {
				srect.bottom = frect.bottom = rect.bottom;
				frect.top = rect.bottom+lines;
				srect.top = rect.top-lines;
			}
			if (cy >= lines && cy >= -lines)
				ScrollDC(dcBuffer, 0, lines, &srect, 0, 0, 0);
		#endif
		
		if (hbr)
			FillRect(dcBuffer, &frect, hbr);
		InvalidateRect(winRootWindow, &rect, FALSE);
		UpdateWindow(winRootWindow);
	}