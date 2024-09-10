void debug_console_init(running_machine &machine)
{
	/* allocate text buffers */
	console_textbuf = text_buffer_alloc(CONSOLE_BUF_SIZE, CONSOLE_MAX_LINES);
	if (!console_textbuf)
		return;

	errorlog_textbuf = text_buffer_alloc(ERRORLOG_BUF_SIZE, ERRORLOG_MAX_LINES);
	if (!errorlog_textbuf)
		return;

	/* print the opening lines */
	debug_console_printf(machine, "%s debugger version %s\n", emulator_info::get_appname(), build_version);
	debug_console_printf(machine, "Currently targeting %s (%s)\n", machine.system().name, machine.system().description);

	/* request callback upon exiting */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(debug_console_exit), &machine));
}