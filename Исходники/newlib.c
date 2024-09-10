void abort(void) {
	vfs_console_write(NULL, 0, "Abort called.\n", sizeof ("Abort called.\n") - 1);
	_exit(1);
}