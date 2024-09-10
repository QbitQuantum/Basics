void user(void) {
	Putc(COM2, 'u');

	Putc(COM1, 0x61);
	Putc(COM1, 0x60);
	Putc(COM1, 0x61);
	Putc(COM1, 0x60);
	Putc(COM1, 0x61);
	Putc(COM1, 0x60);

	Exit();
}