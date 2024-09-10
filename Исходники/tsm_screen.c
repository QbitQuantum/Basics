int tsm_screen_resize(struct tsm_screen *con, unsigned int x,
		      unsigned int y)
{
	struct line **cache;
	unsigned int i, j, width, diff;
	int ret;
	bool *tab_ruler;

	if (!con || !x || !y)
		return -EINVAL;

	if (con->size_x == x && con->size_y == y)
		return 0;

	/* First make sure the line buffer is big enough for our new screen.
	 * That is, allocate all new lines and make sure each line has enough
	 * cells to hold the new screen or the current screen. If we fail, we
	 * can safely return -ENOMEM and the buffer is still valid. We must
	 * allocate the new lines to at least the same size as the current
	 * lines. Otherwise, if this function fails in later turns, we will have
	 * invalid lines in the buffer. */
	if (y > con->line_num) {
		/* resize main buffer */
		cache = realloc(con->main_lines, sizeof(struct line*) * y);
		if (!cache)
			return -ENOMEM;

		if (con->lines == con->main_lines)
			con->lines = cache;
		con->main_lines = cache;

		/* resize alt buffer */
		cache = realloc(con->alt_lines, sizeof(struct line*) * y);
		if (!cache)
			return -ENOMEM;

		if (con->lines == con->alt_lines)
			con->lines = cache;
		con->alt_lines = cache;

		/* allocate new lines */
		if (x > con->size_x)
			width = x;
		else
			width = con->size_x;

		while (con->line_num < y) {
			ret = line_new(con, &con->main_lines[con->line_num],
				       width);
			if (ret)
				return ret;

			ret = line_new(con, &con->alt_lines[con->line_num],
				       width);
			if (ret) {
				line_free(con->main_lines[con->line_num]);
				return ret;
			}

			++con->line_num;
		}
	}

	/* Resize all lines in the buffer if we increase screen width. This
	 * will guarantee that all lines are big enough so we can resize the
	 * buffer without reallocating them later. */
	if (x > con->size_x) {
		tab_ruler = realloc(con->tab_ruler, sizeof(bool) * x);
		if (!tab_ruler)
			return -ENOMEM;
		con->tab_ruler = tab_ruler;

		for (i = 0; i < con->line_num; ++i) {
			ret = line_resize(con, con->main_lines[i], x);
			if (ret)
				return ret;

			ret = line_resize(con, con->alt_lines[i], x);
			if (ret)
				return ret;
		}
	}

	for (j = 0; j < con->line_num; ++j) {
		if (j >= con->size_y)
			i = 0;
		else
			i = con->size_x;

		if (x < con->main_lines[j]->size)
			width = x;
		else
			width = con->main_lines[j]->size;
		for (; i < width; ++i)
			cell_init(con, &con->main_lines[j]->cells[i]);

		if (x < con->alt_lines[j]->size)
			width = x;
		else
			width = con->alt_lines[j]->size;
		for (; i < width; ++i)
			cell_init(con, &con->alt_lines[j]->cells[i]);
	}

	/* xterm destroys margins on resize, so do we */
	con->margin_top = 0;
	con->margin_bottom = con->size_y - 1;

	/* reset tabs */
	for (i = 0; i < x; ++i) {
		if (i % 8 == 0)
			con->tab_ruler[i] = true;
		else
			con->tab_ruler[i] = false;
	}

	/* We need to adjust x-size first as screen_scroll_up() and friends may
	 * have to reallocate lines. The y-size is adjusted after them to avoid
	 * missing lines when shrinking y-size.
	 * We need to carefully look for the functions that we call here as they
	 * have stronger invariants as when called normally. */

	con->size_x = x;
	if (con->cursor_x >= con->size_x)
		con->cursor_x = con->size_x - 1;

	/* scroll buffer if screen height shrinks */
	if (con->size_y != 0 && y < con->size_y) {
		diff = con->size_y - y;
		screen_scroll_up(con, diff);
		if (con->cursor_y > diff)
			con->cursor_y -= diff;
		else
			con->cursor_y = 0;
	}

	con->size_y = y;
	con->margin_bottom = con->size_y - 1;
	if (con->cursor_y >= con->size_y)
		con->cursor_y = con->size_y - 1;

	return 0;
}