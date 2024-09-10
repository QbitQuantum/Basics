/*
 * Print one screeful to the GDI printer.
 */
static int
gdi_screenful(struct ea *ea, unsigned short rows, unsigned short cols,
	const char **fail)
{
    HDC dc = pstate.dlg.hDC;
    LPDEVMODE devmode;
    int row, col, baddr;
    int rc = 0;
    int status;
    int fa_addr = find_field_attribute_ea(0, ea);
    unsigned char fa = ea[fa_addr].fa;
    bool fa_high, high;
    bool fa_underline, underline;
    bool fa_reverse, reverse;
    unsigned long uc;
    bool is_dbcs;
    char c;
    int usable_rows;
    HFONT got_font = NULL, want_font;
#if defined(GDI_DEBUG) /*[*/
    const char *want_font_name;
#endif /*]*/
    enum { COLOR_NONE, COLOR_NORMAL, COLOR_REVERSE } got_color = COLOR_NONE,
	want_color;

    devmode = (LPDEVMODE)GlobalLock(pstate.dlg.hDevMode);

    /* Compute the usable rows, including the caption. */
    usable_rows = pstate.usable_rows;
    if (pstate.caption) {
	usable_rows -= 2;
    }

    /*
     * Does this screen fit?
     * (Note that the first test, "pstate.out_row", is there so that if the
     * font is so big the image won't fit at all, we still print as much
     * of it as we can.)
     */
    if (pstate.out_row && pstate.out_row + ROWS > usable_rows) {
	if (EndPage(dc) <= 0) {
	    *fail = "EndPage failed";
	    rc = -1;
	    goto done;
	}
	pstate.out_row = 0;
	pstate.screens = 0;
    }

    /* If there is a caption, put it on the last line. */
    if (pstate.out_row == 0 && pstate.caption != NULL) {
	SelectObject(dc, pstate.caption_font);
	status = ExtTextOut(dc,
		pstate.hmargin_pixels - pchar.poffX,
		pstate.vmargin_pixels +
		    ((pstate.usable_rows - 1) * pstate.space_size.cy) -
		    pchar.poffY,
		0, NULL,
		pstate.caption, (UINT)strlen(pstate.caption), NULL);
	if (status <= 0) {
	    *fail = "ExtTextOut failed";
	    rc = -1;
	    goto done;
	}
    }

    /* Draw a line separating the screens. */
    if (pstate.out_row) {
	HPEN pen;

	pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(dc, pen);
	status = MoveToEx(dc, 
		pstate.hmargin_pixels - pchar.poffX,
		pstate.vmargin_pixels +
		    (pstate.out_row * pstate.space_size.cy) +
		    (pstate.space_size.cy / 2) - pchar.poffY,
		    NULL);
	if (status == 0) {
	    *fail = "MoveToEx failed";
	    rc = -1;
	    goto done;
	}
	status = LineTo(dc,
		pstate.hmargin_pixels - pchar.poffX + pstate.usable_xpixels,
		pstate.vmargin_pixels +
		    (pstate.out_row * pstate.space_size.cy) +
		    (pstate.space_size.cy / 2) - pchar.poffY);
	if (status == 0) {
	    *fail = "LineTo failed";
	    rc = -1;
	    goto done;
	}
	DeleteObject(pen);
    }

    /* Now dump out a screen's worth. */
    if (ea[fa_addr].gr & GR_INTENSIFY) {
	fa_high = true;
    } else {
	fa_high = FA_IS_HIGH(fa);
    }
    fa_reverse = ((ea[fa_addr].gr & GR_REVERSE) != 0);
    fa_underline = ((ea[fa_addr].gr & GR_UNDERLINE) != 0);

    for (baddr = 0, row = 0; row < ROWS; row++) {
	if (pstate.out_row + row >= usable_rows) {
	    break;
	}
	for (col = 0; col < COLS; col++, baddr++) {
	    if (ea[baddr].fa) {
		fa = ea[baddr].fa;
		if (ea[baddr].gr & GR_INTENSIFY) {
		    fa_high = true;
		} else {
		    fa_high = FA_IS_HIGH(fa);
		}
		fa_reverse = ((ea[fa_addr].gr & GR_REVERSE) != 0);
		fa_underline = ((ea[fa_addr].gr & GR_UNDERLINE) != 0);

		/* Just skip it. */
		continue;
	    }
	    if (col >= pstate.usable_cols) {
		continue;
	    }
	    is_dbcs = FALSE;
	    if (FA_IS_ZERO(fa)) {
		if (ctlr_dbcs_state_ea(baddr, ea) == DBCS_LEFT) {
		    uc = 0x3000;
		} else {
		    uc = ' ';
		}
	    } else {
		/* Convert EBCDIC to Unicode. */
		switch (ctlr_dbcs_state(baddr)) {
		case DBCS_NONE:
		case DBCS_SB:
		    uc = ebcdic_to_unicode(ea[baddr].cc, ea[baddr].cs,
			    EUO_NONE);
		    if (uc == 0) {
			uc = ' ';
		    }
		    break;
		case DBCS_LEFT:
		    is_dbcs = TRUE;
		    uc = ebcdic_to_unicode((ea[baddr].cc << 8) |
				ea[baddr + 1].cc,
			    CS_BASE, EUO_NONE);
		    if (uc == 0) {
			uc = 0x3000;
		    }
		    break;
		case DBCS_RIGHT:
		    /* skip altogether, we took care of it above */
		    continue;
		default:
		    uc = ' ';
		    break;
		}
	    }

	    /* Figure out the attributes of the current buffer position. */
	    high = ((ea[baddr].gr & GR_INTENSIFY) != 0);
	    if (!high) {
		high = fa_high;
	    }
	    reverse = ((ea[fa_addr].gr & GR_REVERSE) != 0);
	    if (!reverse) {
		reverse = fa_reverse;
	    }
	    underline = ((ea[fa_addr].gr & GR_UNDERLINE) != 0);
	    if (!underline) {
		underline = fa_underline;
	    }

	    /* Set the bg/fg color and font. */
	    if (reverse) {
		want_color = COLOR_REVERSE;
	    } else {
		want_color = COLOR_NORMAL;
	    }
	    if (want_color != got_color) {
		switch (want_color) {
		case COLOR_REVERSE:
		    SetTextColor(dc, 0xffffff);
		    SetBkColor(dc, 0);
		    SetBkMode(dc, OPAQUE);
		    break;
		case COLOR_NORMAL:
		    SetTextColor(dc, 0);
		    SetBkColor(dc, 0xffffff);
		    SetBkMode(dc, TRANSPARENT);
		    break;
		default:
		    break;
		}
		got_color = want_color;
	    }
	    if (!high && !underline) {
		want_font = pstate.font;
#if defined(GDI_DEBUG) /*[*/
		want_font_name = "Roman";
#endif /*]*/
	    } else if (high && !underline) {
		want_font = pstate.bold_font;
#if defined(GDI_DEBUG) /*[*/
		want_font_name = "Bold";
#endif /*]*/
	    } else if (!high && underline) {
		want_font = pstate.underscore_font;
#if defined(GDI_DEBUG) /*[*/
		want_font_name = "Underscore";
#endif /*]*/
	    } else {
		want_font = pstate.bold_underscore_font;
#if defined(GDI_DEBUG) /*[*/
		want_font_name = "Underscore";
#endif /*]*/
	    }
	    if (want_font != got_font) {
		SelectObject(dc, want_font);
		got_font = want_font;
#if defined(GDI_DEBUG) /*[*/
		vtrace("[gdi] selecting %s\n", want_font_name);
#endif /*]*/
	    }

	    /*
	     * Handle spaces and DBCS spaces (U+3000).
	     * If not reverse or underline, just skip over them.
	     * Otherwise, print a space or two spaces, using the
	     * right font and modes.
	     */
	    if (uc == ' ' || uc == 0x3000) {
		if (reverse || underline) {
		    status = ExtTextOut(dc, pstate.hmargin_pixels +
				(col * pstate.space_size.cx) -
				pchar.poffX,
			    pstate.vmargin_pixels +
				((pstate.out_row + row + 1) *
				 pstate.space_size.cy) -
				pchar.poffY,
			    0, NULL,
			    "  ",
			    (uc == 0x3000)? 2: 1,
			    pstate.dx);
		    if (status <= 0) {
			*fail = "ExtTextOut failed";
			rc = -1;
			goto done;
		    }
		}
		continue;
	    }

	    /*
	     * Emit one character at a time. This should be optimized to print
	     * strings of characters with the same attributes.
	     */
	    if (is_dbcs) {
		wchar_t w;
		INT wdx;

		w = (wchar_t)uc;
		wdx = pstate.space_size.cx;

		status = ExtTextOutW(dc,
			pstate.hmargin_pixels + (col * pstate.space_size.cx) -
			    pchar.poffX,
			pstate.vmargin_pixels +
			    ((pstate.out_row + row + 1) *
			     pstate.space_size.cy) -
			    pchar.poffY,
			0, NULL,
			&w, 1, &wdx);
		if (status <= 0) {
		    *fail = "ExtTextOutW failed";
		    rc = -1;
		    goto done;
		}
		continue;
	    }
	    c = (char)uc;
	    status = ExtTextOut(dc,
		    pstate.hmargin_pixels + (col * pstate.space_size.cx) -
			pchar.poffX,
		    pstate.vmargin_pixels +
			((pstate.out_row + row + 1) * pstate.space_size.cy) -
			pchar.poffY,
		    0, NULL,
		    &c, 1, pstate.dx);
#if defined(GDI_DEBUG) /*[*/
	    if (c != ' ') {
		vtrace("[gdi] row %d col %d x=%ld y=%ld '%c'\n",
			row, col,
			pstate.hmargin_pixels + (col * pstate.space_size.cx) -
			    pchar.poffX,
			pstate.vmargin_pixels +
			    ((pstate.out_row + row + 1) * pstate.space_size.cy) -
			    pchar.poffY,
			c);
	    }
#endif /*]*/
	    if (status <= 0) {
		*fail = "ExtTextOut failed";
		rc = -1;
		goto done;
	    }
	}
    }

    /* Tally the current screen and see if we need to go to a new page. */
    pstate.out_row += (row + 1); /* current screen plus a gap */
    pstate.screens++;
    if (pstate.out_row >= usable_rows || pstate.screens >= uparm.spp) {
	if (EndPage(dc) <= 0) {
	    *fail = "EndPage failed";
	    rc = -1;
	    goto done;
	}
	pstate.out_row = 0;
	pstate.screens = 0;
    }

done:
    GlobalUnlock(devmode);
    return rc;
}