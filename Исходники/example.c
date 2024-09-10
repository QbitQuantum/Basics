/// Main loop and input handling
int main() {
	hidecursor();
	gen(level);
	setColor(2);
	printf("Welcome! Use WASD to move.\n");
	setColor(6);
	printf("Hit any key to start.\n");
	anykey();
	draw();
	while (1) {
		// Input
		if (kbhit()) {
			char k = getch();

			int oldx = x, oldy = y;
			if (k == 'a') { --x; ++moves; }
			else if (k == 'd') { ++x; ++moves; }
			else if (k == 'w') { --y; ++moves; }
			else if (k == 's') { ++y; ++moves; }
			else if (k == 27) break;
			// Collisions
			if (lvl[x][y] & WALL) { x = oldx; y = oldy; }
			else if (lvl[x][y] & COIN) { coins++; lvl[x][y] ^= COIN; }
			else if (lvl[x][y] & TORCH) { torch+=20; lvl[x][y] ^= TORCH; }
			else if (lvl[x][y] & STAIRS_DOWN) gen(++level);
			// Drawing
			draw();
			// Die
			if (--torch <= 0) break;
		}
	}
	showcursor();
	return 0;
}