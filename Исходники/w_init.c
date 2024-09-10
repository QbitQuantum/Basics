/* Make window w the current window. NULL is allowed */
void w_curwin(struct w_window *w) {
    struct w_window *ow;


    ow = notes.cur_win != NULL ? &notes.cur_win->w : NULL;
    notes.cur_win = (struct wi_window *)w;
    drawmenubar();

    if (ow) {
        w_refreshwin(ow);
    }

    if (w) {
        w_refreshwin(w);
    }
}