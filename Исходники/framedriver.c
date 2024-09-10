void ICACHE_FLASH_ATTR set_buffer(int buffer, int val1, int val2, int val3) {
	for(int i = 0; i < COLUMNS; i++) {
		for(int x = 0; x < ROWS; x++) {
			setpixel(buffer, i, x, val1, val2, val3);
		}
	}
}