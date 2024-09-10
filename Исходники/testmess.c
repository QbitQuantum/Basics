void osd_update(running_machine &machine, int skip_redraw)
{
	int i;
	attotime time_limit;
	attotime current_time;

	target->get_primitives();

	/* don't do anything if we are initializing! */
	switch(machine.phase())
	{
		case MACHINE_PHASE_PREINIT:
		case MACHINE_PHASE_INIT:
		case MACHINE_PHASE_RESET:
			return;
		default: break;
	}

	/* if we have already aborted or completed, our work is done */
	if ((state == STATE_ABORTED) || (state == STATE_DONE))
	{
		machine.schedule_exit();
		return;
	}

	/* have we hit the time limit? */
	current_time = machine.time();
	time_limit = (current_testcase.time_limit != attotime::zero) ? current_testcase.time_limit
		: attotime::from_seconds(600);
	if (current_time > time_limit)
	{
		state = STATE_ABORTED;
		report_message(MSG_FAILURE, "Time limit of %s attoseconds exceeded", time_limit.as_string(9));
		return;
	}

	for (i = 0; i < ARRAY_LENGTH(commands); i++)
	{
		if (current_command->command_type == commands[i].command_type)
		{
			commands[i].proc(machine);
			break;
		}
	}

	/* if we are ready for the next command, advance to it */
	if (state == STATE_READY)
	{
		/* if we are at the end, and we are dumping screenshots, and we didn't
         * just dump a screenshot, dump one now
         */
		if ((test_flags & MESSTEST_ALWAYS_DUMP_SCREENSHOT) &&
			(current_command[0].command_type != MESSTEST_COMMAND_SCREENSHOT) &&
			(current_command[1].command_type == MESSTEST_COMMAND_END))
		{
			dump_screenshot(machine, TRUE);
		}

		current_command++;
	}
}