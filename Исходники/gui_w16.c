    void
gui_mch_draw_string(
    int		row,
    int		col,
    char_u	*text,
    int		len,
    int		flags)
{
#ifndef MSWIN16_FASTTEXT
    static int	*padding = NULL;
    static int	pad_size = 0;
    int		i;
#endif
    HPEN	hpen, old_pen;
    int		y;

#ifndef MSWIN16_FASTTEXT
    /*
     * Italic and bold text seems to have an extra row of pixels at the bottom
     * (below where the bottom of the character should be).  If we draw the
     * characters with a solid background, the top row of pixels in the
     * character below will be overwritten.  We can fix this by filling in the
     * background ourselves, to the correct character proportions, and then
     * writing the character in transparent mode.  Still have a problem when
     * the character is "_", which gets written on to the character below.
     * New fix: set gui.char_ascent to -1.  This shifts all characters up one
     * pixel in their slots, which fixes the problem with the bottom row of
     * pixels.	We still need this code because otherwise the top row of pixels
     * becomes a problem. - webb.
     */
    HBRUSH	hbr;
    RECT	rc;

    if (!(flags & DRAW_TRANSP))
    {
	/*
	 * Clear background first.
	 * Note: FillRect() excludes right and bottom of rectangle.
	 */
	rc.left = FILL_X(col);
	rc.top = FILL_Y(row);
#ifdef FEAT_MBYTE
	if (has_mbyte)
	{
	    /* Compute the length in display cells. */
	    rc.right = FILL_X(col + mb_string2cells(text, len));
	}
	else
#endif
	    rc.right = FILL_X(col + len);
	rc.bottom = FILL_Y(row + 1);
	hbr = CreateSolidBrush(gui.currBgColor);
	FillRect(s_hdc, &rc, hbr);
	DeleteBrush(hbr);

	SetBkMode(s_hdc, TRANSPARENT);

	/*
	 * When drawing block cursor, prevent inverted character spilling
	 * over character cell (can happen with bold/italic)
	 */
	if (flags & DRAW_CURSOR)
	{
	    pcliprect = &rc;
	    foptions = ETO_CLIPPED;
	}
    }
#else
    /*
     * Alternative: write the characters in opaque mode, since we have blocked
     * bold or italic fonts.
     */
    /* The OPAQUE mode and backcolour have already been set */
#endif
    /* The forecolor and font have already been set */

#ifndef MSWIN16_FASTTEXT

    if (pad_size != Columns || padding == NULL || padding[0] != gui.char_width)
    {
	vim_free(padding);
	pad_size = Columns;

	padding = (int *)alloc(pad_size * sizeof(int));
	if (padding != NULL)
	    for (i = 0; i < pad_size; i++)
		padding[i] = gui.char_width;
    }
#endif

    /*
     * We have to provide the padding argument because italic and bold versions
     * of fixed-width fonts are often one pixel or so wider than their normal
     * versions.
     * No check for DRAW_BOLD, Windows will have done it already.
     */
#ifndef MSWIN16_FASTTEXT
    ExtTextOut(s_hdc, TEXT_X(col), TEXT_Y(row), 0, NULL,
						     (char *)text, len, padding);
#else
    TextOut(s_hdc, TEXT_X(col), TEXT_Y(row), (char *)text, len);
#endif

    if (flags & DRAW_UNDERL)
    {
	hpen = CreatePen(PS_SOLID, 1, gui.currFgColor);
	old_pen = SelectObject(s_hdc, hpen);
	/* When p_linespace is 0, overwrite the bottom row of pixels.
	 * Otherwise put the line just below the character. */
	y = FILL_Y(row + 1) - 1;
#ifndef MSWIN16_FASTTEXT
	if (p_linespace > 1)
	    y -= p_linespace - 1;
#endif
	MoveToEx(s_hdc, FILL_X(col), y, NULL);
	/* Note: LineTo() excludes the last pixel in the line. */
	LineTo(s_hdc, FILL_X(col + len), y);
	DeleteObject(SelectObject(s_hdc, old_pen));
    }
}