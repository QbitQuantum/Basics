static void initconio(void)
{
	int x, y;
	initialized = 1;

	initscr();
	start_color();
	nonl();
	raw();
	noecho();
	win = newwin(0,0,0,0);
	keypad(win,TRUE);
	meta(win,TRUE);
	idlok(win,TRUE);
	scrollok(win,TRUE);

	getmaxyx(win, height, width);

	/* Color initialization */

	for (x = 0; x < 8; x++) {
		for (y = 0; y < 8; y++) {
			init_pair((y<<3)+x, x, y);
		}
	}
	settextcolor(WHITE, BLACK);
}