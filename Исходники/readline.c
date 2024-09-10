/**
 * Key backspace.
 */
static void
case_key_backspace(volatile struct readline_session_context *ctx)
{
    struct current_cursor_pos yx;

    if (ctx->bufpos == 0) {
	term_beep();
	return;
    }

    if (loLim_isset(ctx->act, ctx->prompt_size)) {
	magic_swap_panels(ctx, false);
    }

    if (ctx->insert_mode) {
	wchar_t *ptr = &ctx->buffer[ctx->bufpos--];

	(void) wmemmove(ptr - 1, ptr, wcslen(ptr));
	ctx->buffer[--ctx->n_insert] = 0L;
	yx = term_get_pos(ctx->act);

	if (wmove(ctx->act, yx.cury, yx.curx - 1) == ERR ||
	    wdelch(ctx->act) == ERR || wclrtoeol(ctx->act) == ERR) {
	    readline_error(EPERM, "wmove, wdelch or wclrtoeol");
	}

	readline_winsnstr(ctx->act, &ctx->buffer[ctx->bufpos], -1);
    } else { /* not insert_mode */
	ctx->buffer[--ctx->bufpos] = 0L;
	ctx->n_insert--;
	yx = term_get_pos(ctx->act);

	if (wmove(ctx->act, yx.cury, yx.curx - 1) == ERR ||
	    wdelch(ctx->act) == ERR) {
	    readline_error(EPERM, "wmove or wdelch");
	}
    }

    update_panels();
    (void) doupdate();
}