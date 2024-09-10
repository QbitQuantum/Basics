int newtOpenWindow(int left, int top, int width, int height,
			  const char * title) {
    int j, row, col;
    int n;
    int i;

    newtFlushInput();

    if (!currentWindow) {
	currentWindow = windowStack;
    } else {
	currentWindow++;
    }

    currentWindow->left = left;
    currentWindow->top = top;
    currentWindow->width = width;
    currentWindow->height = height;
    currentWindow->title = title ? strdup(title) : NULL;

    currentWindow->buffer = malloc(sizeof(SLsmg_Char_Type) * (width + 3) * (height + 3));

    row = top - 1;
    col = left - 1;
    /* clip to the current screen bounds - msw */
    if (row < 0)
	row = 0;
    if (col < 0)
	col = 0;
    if (left + width > SLtt_Screen_Cols)
	width = SLtt_Screen_Cols - left;
    if (top + height > SLtt_Screen_Rows)
	height = SLtt_Screen_Rows - top;
    n = 0;
    for (j = 0; j < height + 3; j++, row++) {
	SLsmg_gotorc(row, col);
	SLsmg_read_raw(currentWindow->buffer + n,
		       currentWindow->width + 3);
	n += currentWindow->width + 3;
    }

    newtTrashScreen();

    SLsmg_set_color(NEWT_COLORSET_BORDER);
    SLsmg_draw_box(top - 1, left - 1, height + 2, width + 2);

    if (currentWindow->title) {
	i = wstrlen(currentWindow->title,-1) + 4;
	i = ((width - i) / 2) + left;
	SLsmg_gotorc(top - 1, i);
	SLsmg_set_char_set(1);
	SLsmg_write_char(SLSMG_RTEE_CHAR);
	SLsmg_set_char_set(0);
	SLsmg_write_char(' ');
	SLsmg_set_color(NEWT_COLORSET_TITLE);
	SLsmg_write_string((char *)currentWindow->title);
	SLsmg_set_color(NEWT_COLORSET_BORDER);
	SLsmg_write_char(' ');
	SLsmg_set_char_set(1);
	SLsmg_write_char(SLSMG_LTEE_CHAR);
	SLsmg_set_char_set(0);
    }

    SLsmg_set_color(NEWT_COLORSET_WINDOW);
    SLsmg_fill_region(top, left, height, width, ' ');

    SLsmg_set_color(NEWT_COLORSET_SHADOW);
    SLsmg_fill_region(top + height + 1, left, 1, width + 2, ' ');
    SLsmg_fill_region(top, left + width + 1, height + 1, 1, ' ');

    for (i = top; i < (top + height + 1); i++) {
	SLsmg_gotorc(i, left + width + 1);
	SLsmg_write_string(" ");
    }

    return 0;
}