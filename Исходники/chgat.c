static void
update_status(WINDOW *win, STATUS * sp)
{
    switch (sp->ch) {
    case ' ':			/* next test-iteration */
	if (has_colors()) {
	    if ((sp->c_msg = color_params(++(sp->c), &(sp->pair))) == 0) {
		sp->c_msg = color_params(sp->c = 0, &(sp->pair));
		if ((sp->v_msg = video_params(++(sp->v), &(sp->attr))) == 0) {
		    sp->v_msg = video_params(sp->v = 0, &(sp->attr));
		}
	    }
	} else {
	    if ((sp->v_msg = video_params(++(sp->v), &(sp->attr))) == 0) {
		sp->v_msg = video_params(sp->v = 0, &(sp->attr));
	    }
	}
	sp->count = 0;
	show_status(win, sp);
	break;
    case KEY_LEFT:
    case 'h':
	if (sp->x_val > 0)
	    wmove(win, sp->y_val, --(sp->x_val));
	break;
    case KEY_DOWN:
    case 'j':
	if (sp->y_val < sp->y_max)
	    wmove(win, ++(sp->y_val), sp->x_val);
	break;
    case KEY_UP:
    case 'k':
	if (sp->y_val > 0)
	    wmove(win, --(sp->y_val), sp->x_val);
	break;
    case KEY_RIGHT:
    case 'l':
	if (sp->x_val < sp->x_max)
	    wmove(win, sp->y_val, ++(sp->x_val));
	break;
    case 't':
	touchline(win, sp->y_val, 1);
	break;
    case '=':
	sp->count = 0;
	show_status(win, sp);
	break;
    case '-':
	sp->count = -(sp->count);
	show_status(win, sp);
	break;
    case '?':
	do_subwindow(win, sp, show_help);
	break;
    default:
	if (isdigit(sp->ch)) {
	    sp->count = (sp->count * 10) + (sp->ch - '0');
	    show_status(win, sp);
	} else {
	    beep();
	}
	break;
    }
}