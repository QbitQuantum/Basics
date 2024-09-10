void draw_preview_block(char x, char y) {
	byte x_start, y_start, x1, y1;
	byte i;

	x_start = PREVIEW_X + BLOCK_SIZE * x;
	y_start = PREVIEW_Y + BLOCK_SIZE * y;

	x1 = x_start;
	y1 = y_start + BLOCK_SIZE - 1;
	for (i = 0; i < BLOCK_SIZE; i++) {
		setpixel(x1, y_start);
		setpixel(x1, y1);
		x1++;
	}

	x1 = x_start + BLOCK_SIZE - 1;
	y1 = y_start + 1;
	for (i = 0; i < BLOCK_SIZE - 2; i++) {
		setpixel(x_start, y1);
		setpixel(x1, y1);
		y1++;
	}

	setpixel(x_start + 2, y_start + 2);
}