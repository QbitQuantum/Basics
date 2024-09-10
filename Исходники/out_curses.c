static void curses_draw(void)
{
	if (NULL == get_current_node()) {
		first_node();
		first_item();
	}

	row = 0;
	move(0,0);
	
	getmaxyx(stdscr, rows, cols);
	
	if (cols < 80) {
		clear();
		putl("Screen must be at least 80 columns wide");
		refresh();
		return;
	}

	if (c_use_colors)
		attrset(COLOR_PAIR(LAYOUT_STATUSBAR) | layout[LAYOUT_STATUSBAR].attr);
	else
		attrset(A_REVERSE);

	if (get_current_node() && get_current_item()) {
		putl(" %s on %s",
			get_current_item()->i_name, get_current_node()->n_name);
	}

	move(row, COLS - strlen(PACKAGE_STRING) - 1);
	putl("%s", PACKAGE_STRING);
	move(row, 0);
	
	if (c_use_colors)
		attrset(COLOR_PAIR(LAYOUT_DEFAULT) | layout[LAYOUT_DEFAULT].attr);
	else
		attroff(A_REVERSE);
	
	print_content();

	if (quit_mode)
		print_quit();
	else if (print_help) {
		if (help_page == 0)
			draw_help();
		else
			draw_help_2();
	}

	for (; row < rows-2;) {
		move(++row, 0);
		putl("");
	}
	
	row = rows-1;
	move(row, 0);

	if (c_use_colors)
		attrset(COLOR_PAIR(LAYOUT_STATUSBAR) | layout[LAYOUT_STATUSBAR].attr);
	else
		attrset(A_REVERSE);

	if (1) {
		char s[27];
		time_t t = time(0);
		double d;
		int h, m;

		asctime_r(localtime(&t), s);
		s[strlen(s) - 1] = '\0';
		d = difftime(time(0), start_time);

		if (d / 3600) {
			h = (int) d / 3600;
			m = (int) d % 3600;
			m /= 60;
		} else {
			h = 0;
			m = (int) d / 60;
		}
		
		putl(" %s (%dh/%dm)", s, h, m);
		move(row, COLS - strlen("Press ? for help") - 1);
		putl("%s", "Press ? for help");
		move(row, 0);
	}
	
	attrset(0);
	refresh();
}