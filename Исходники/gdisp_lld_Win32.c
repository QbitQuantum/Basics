	LLDSPEC void gdisp_lld_vertical_scroll(GDisplay *g) {
		winPriv	*	priv;
		RECT		rect;
		coord_t		lines;

		priv = g->priv;

		#if GDISP_NEED_CONTROL
			switch(g->g.Orientation) {
			case GDISP_ROTATE_0:
			default:
				rect.top = g->p.y;
				rect.bottom = rect.top+g->p.cy;
				rect.left = g->p.x;
				rect.right = rect.left+g->p.cx;
				lines = -g->p.y1;
				goto vertical_scroll;
			case GDISP_ROTATE_90:
				rect.bottom = g->g.Width - g->p.x;
				rect.top = rect.bottom-g->p.cx;
				rect.left = g->p.y;
				rect.right = rect.left+g->p.cy;
				lines = -g->p.y1;
				goto horizontal_scroll;
			case GDISP_ROTATE_180:
				rect.bottom = g->g.Height - g->p.y;
				rect.top = rect.bottom-g->p.cy;
				rect.right = g->g.Width - g->p.x;
				rect.left = rect.right-g->p.cx;
				lines = g->p.y1;
			vertical_scroll:
				if (lines > 0) {
					rect.bottom -= lines;
				} else {
					rect.top -= lines;
				}
				if (g->p.cy >= lines && g->p.cy >= -lines) {
					WaitForSingleObject(drawMutex, INFINITE);
					ScrollDC(priv->dcBuffer, 0, lines, &rect, 0, 0, 0);
					#if GDISP_WIN32_USE_INDIRECT_UPDATE
						ReleaseMutex(drawMutex);
						InvalidateRect(priv->hwnd, &rect, FALSE);
					#else
						{
							HDC		dc;
							dc = GetDC(priv->hwnd);
							ScrollDC(dc, 0, lines, &rect, 0, 0, 0);
							ReleaseDC(priv->hwnd, dc);
							ReleaseMutex(drawMutex);
						}
					#endif
				}
				break;
			case GDISP_ROTATE_270:
				rect.top = g->p.x;
				rect.bottom = rect.top+g->p.cx;
				rect.right = g->g.Height - g->p.y;
				rect.left = rect.right-g->p.cy;
				lines = g->p.y1;
			horizontal_scroll:
				if (lines > 0) {
					rect.right -= lines;
				} else {
					rect.left -= lines;
				}
				if (g->p.cy >= lines && g->p.cy >= -lines) {
					WaitForSingleObject(drawMutex, INFINITE);
					ScrollDC(priv->dcBuffer, lines, 0, &rect, 0, 0, 0);
					#if GDISP_WIN32_USE_INDIRECT_UPDATE
						ReleaseMutex(drawMutex);
						InvalidateRect(priv->hwnd, &rect, FALSE);
					#else
						{
							HDC		dc;
							dc = GetDC(priv->hwnd);
							ScrollDC(dc, lines, 0, &rect, 0, 0, 0);
							ReleaseDC(priv->hwnd, dc);
							ReleaseMutex(drawMutex);
						}
					#endif
				}
				break;
			}
		#else
			rect.top = g->p.y;
			rect.bottom = rect.top+g->p.cy;
			rect.left = g->p.x;
			rect.right = rect.left+g->p.cx;
			lines = -g->p.y1;
			if (lines > 0) {
				rect.bottom -= lines;
			} else {
				rect.top -= lines;
			}
			if (g->p.cy >= lines && g->p.cy >= -lines) {
				WaitForSingleObject(drawMutex, INFINITE);
				ScrollDC(priv->dcBuffer, 0, lines, &rect, 0, 0, 0);
				#if GDISP_WIN32_USE_INDIRECT_UPDATE
					ReleaseMutex(drawMutex);
					InvalidateRect(priv->hwnd, &rect, FALSE);
				#else
					{
						HDC		dc;
						dc = GetDC(priv->hwnd);
						ScrollDC(dc, 0, lines, &rect, 0, 0, 0);
						ReleaseDC(priv->hwnd, dc);
						ReleaseMutex(drawMutex);
					}
				#endif
			}
		#endif
	}