int front_panel_open()
{
	fd = openport(fp_tty, B115200);
	if (fd <= 0) {
		trace_err("failed to open port!");
		return -1;
	}
	wu_swait_init(&fp_swait);
	trace_info("success open front panel port");

	return 0;
}