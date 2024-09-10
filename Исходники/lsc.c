int
process_command(Point mouse) {
	button *bp = buttons;

	while (bp && (bp->state == Hidden || !ptinrect(mouse, bp->r)))
		bp = bp->next;
	if (!bp)
		return 0;

	if (bp == undo_button) {
		if (nhist > 0) {
			nhist--;
			show_hist();
		}
	} else if (bp == startover_button) {
		unfreeze();
		nhist = 0;
		show_hist();
	} else if (bp == freeze_button) {
		switch (state) {
		case Live:
			state = Frozen;
			freeze_button->state = On;
			paint_fancy_button(freeze_button);
			break;
		case Frozen:
			unfreeze();
			break;
		default:
			break;
		}
		flush_screen();
	} else if (bp == primary_buttons[Cat_change_color].b ||
	   bp == primary_buttons[Cat_change_look].b ||
	   bp == primary_buttons[Cat_change_shape].b) {
		set_category(bp);
	} else {
		if (bp && nhist < MAXHIST) {
			history[nhist++] = bp;
			show_hist();
		}
	}
	flush_screen();
	return 1;
}