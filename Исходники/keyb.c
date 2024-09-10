int kb_init(int bufsz)
{
	if(DONE_INIT) {
		fprintf(stderr, "keyboard driver already initialized!\n");
		return 0;
	}

	buffer_size = bufsz;
	if(buffer_size && !(buffer = malloc(buffer_size * sizeof *buffer))) {
		fprintf(stderr, "failed to allocate input buffer, continuing without\n");
		buffer_size = 0;
	}
	buf_ridx = buf_widx = 0;
	last_key = -1;

	memset(keystate, 0, sizeof keystate);
	num_pressed = 0;

	/* set our interrupt handler */
	_disable();
	prev_handler = _dos_getvect(KB_INTR);
	_dos_setvect(KB_INTR, kbintr);
	_enable();

	return 0;
}